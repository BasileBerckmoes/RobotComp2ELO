/*******************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;

using System.Windows.Forms;
using System.Diagnostics;
using System.Drawing;

using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;

using Cypress.Semiconductor.CyDesigner.cy_logic_gate_customizer;

namespace Cypress.Semiconductor.CyDesigner.not_v1_0
{
    public class CyCustomizer :
        ICyVerilogCustomize_v1,
        ICyShapeCustomize_v1
    {
        const string INPUT_TERM_BASE_NAME = "inTerminal";
        const string OUTPUT_TERM_BASE_NAME = "outTerminal";
        const string GENERATED_SHAPE = "SymbolShape";

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

            CyCompDevParam terminalWidth_param = instQuery.GetCommittedParam("TerminalWidth");
            uint terminalWidth = uint.Parse(terminalWidth_param.Value);
            string suffix = CyBuilder.GetTermSuffix(terminalWidth);

            string sigsegname_input = termQuery.GetTermSigSegName(INPUT_TERM_BASE_NAME + suffix);
            string sigsegname_output = termQuery.GetTermSigSegName(OUTPUT_TERM_BASE_NAME + suffix);

            StringBuilder sb = new StringBuilder();
            sb.Append(Environment.NewLine);
            string invocation = string.Format("    assign {0} = ~{1};{2}", 
                sigsegname_output, sigsegname_input, Environment.NewLine);

            sb.Append(invocation);
            codeSnippet = sb.ToString();

            return CyCustErr.OK;
        }

        #endregion

        #region ICyShapeCustomize_v1 Members

        public CyCustErr CustomizeShapes(
            ICyInstQuery_v1 instQuery,
            ICySymbolShapeEdit_v1 shapeEdit,
            ICyTerminalEdit_v1 termEdit)
        {
            // Remove existing shapes and terminals
            shapeEdit.ShapesRemove("SymbolName");
            termEdit.RemoveAllTerminals();

            CyCompDevParam terminalWidth_param = instQuery.GetCommittedParam("TerminalWidth");
            uint terminalWidth = uint.Parse(terminalWidth_param.Value);
            string suffix = CyBuilder.GetTermSuffix(terminalWidth);

            // Add input and output terminals
            CyCustErr err = termEdit.TerminalAdd(INPUT_TERM_BASE_NAME + suffix,
                CyCompDevTermDir.INPUT, CyCompDevTermType.DIGITAL,
                new PointF(0f, 0f), string.Empty, 0f, false);
            if (err.IsNotOk) return err;

            err = termEdit.TerminalAdd(OUTPUT_TERM_BASE_NAME + suffix,
                CyCompDevTermDir.OUTPUT, CyCompDevTermType.DIGITAL,
                new PointF(36f, 0f), string.Empty, 0f, false);
            if (err.IsNotOk) return err;
            List<string> tags = new List<string>();
            tags.Add(GENERATED_SHAPE);           
            shapeEdit.SetOutlineWidth(GENERATED_SHAPE, 0f);
            return CyCustErr.OK;
        }

        #endregion
    }
}
