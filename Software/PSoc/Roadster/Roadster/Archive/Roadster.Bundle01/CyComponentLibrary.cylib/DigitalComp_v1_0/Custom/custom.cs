/*******************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;
using System;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace Cypress.Semiconductor.CyDesigner.DigitalComp_v1_0
{
    public class CyCustomizer :
        ICyVerilogCustomize_v1,
        ICyShapeCustomize_v1
    {
        #region ICyVerilogCustomize_v1 Members

        public CyCustErr CustomizeVerilog(
            ICyInstQuery_v1 instQuery,
            ICyTerminalQuery_v1 termQuery,
            out string codeSnippet)
        {
            Debug.Assert(instQuery != null);
            if (instQuery == null)
            {
                codeSnippet = string.Empty;
                return new CyCustErr("Invalid instance query parameter");
            }
            
            CyCompDevParam width_param = instQuery.GetCommittedParam("Width");
            uint terminalWidth = uint.Parse(width_param.Value);
            string suffix = (terminalWidth > 1) ? string.Format("[{0}:0]", terminalWidth - 1) : string.Empty;
            
            CyCompDevParam cmpType_param = instQuery.GetCommittedParam("CmpType");
            uint cmpType = uint.Parse(cmpType_param.Value);
            string cmpString;
            switch (cmpType)
            {
                default:
                case 0:
                    cmpString = "==";
                    break;
                case 1:
                    cmpString = "!= ";
                    break;
                case 2:
                    cmpString = "<";
                    break;
                case 3:
                    cmpString = "<=";
                    break;
                case 4:
                    cmpString = ">";
                    break;
                case 5:
                    cmpString = ">=";
                    break;
            }
			
			StringWriter stringWriter = new StringWriter();
			
            string aSigSegName = termQuery.GetTermSigSegName("a" + suffix);
            string bSigSegName = termQuery.GetTermSigSegName("b" + suffix);
            string cmpSigSegName = termQuery.GetTermSigSegName("cmp");

            stringWriter.WriteLine(String.Format("    assign {0} = ({1} {2} {3});", cmpSigSegName, aSigSegName, cmpString, bSigSegName));

            codeSnippet = stringWriter.ToString();

            return CyCustErr.OK;
        }
        #endregion

        #region ICyShapeCustomize_v1 Members

        public CyCustErr CustomizeShapes(
            ICyInstQuery_v1 instQuery,
            ICySymbolShapeEdit_v1 shapeEdit,
            ICyTerminalEdit_v1 termEdit)
        {
            CyCompDevParam  width_param = instQuery.GetCommittedParam("Width");
            byte terminalWidth;
            CyCustErr err = width_param.TryGetValueAs<byte>(out terminalWidth);
            if (err.IsNotOk) return err;

            string suffix = (terminalWidth > 1) ? string.Format("[{0}:0]", terminalWidth - 1) : string.Empty;
            string newATermName = "a" + suffix;
            string aTermName = termEdit.GetTermName("a");
            string newBTermName = "b" + suffix;
            string bTermName = termEdit.GetTermName("b");
            
            termEdit.TerminalRename(aTermName, newATermName);
            termEdit.TerminalRename(bTermName, newBTermName);
            
            return CyCustErr.OK;
        }

        #endregion
    }
}
//[]//

