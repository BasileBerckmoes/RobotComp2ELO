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

using Cypress.Semiconductor.CyDesigner.cy_logic_gate_customizer;

namespace Cypress.Semiconductor.CyDesigner.cy_dffe_v1_0
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

            CyCompDevParam terminalWidth_param = instQuery.GetCommittedParam("ArrayWidth");
            uint terminalWidth = uint.Parse(terminalWidth_param.Value);
            string suffix = CyBuilder.GetTermSuffix(terminalWidth);
            
            CyVerilogBuilder vGen = new CyVerilogBuilder();
            vGen.AddComment("-- DFFE Start --");

            string dSigSegName = termQuery.GetTermSigSegName("d" + suffix);
			string qSigSegName = termQuery.GetTermSigSegName("q" + suffix);
			string enSigSegName = termQuery.GetTermSigSegName("en");

            //declare a register to hold the value in the always block
            vGen.DeclareReg(instQuery.InstanceName, suffix);

            List<string> SensitivityList = new List<string>();
            List<CyVerilogBuilder.EdgeTypeEnum> signalEdgeList = new List<CyVerilogBuilder.EdgeTypeEnum>();
            
            string clkSigSegName = termQuery.GetTermSigSegScalarName("clk");
			if (termQuery.GetTermSigSegName("clk").Contains("["))
			{
				string tmpClockName = CyVerilogBuilder.GetTmpName("tmp", instQuery.InstanceName, "clk");
				vGen.DeclareWire(tmpClockName, "");
				vGen.AddAssignStatement(tmpClockName, clkSigSegName);
				clkSigSegName = tmpClockName;
			}
            SensitivityList.Add(clkSigSegName);
            signalEdgeList.Add(CyVerilogBuilder.EdgeTypeEnum.POSITIVE);

            vGen.DefineAlways(SensitivityList, signalEdgeList);
            vGen.BeginBlock();
            
            string ternAssign = enSigSegName + " ? " + dSigSegName + " : " + instQuery.InstanceName;
            vGen.AddNonBlockingStatement(instQuery.InstanceName, ternAssign);

            vGen.EndBlock();
            vGen.AddAssignStatement(qSigSegName, instQuery.InstanceName);

            vGen.AddComment("-- DFFE End --");
            codeSnippet = vGen.VerilogString;

            return CyCustErr.OK;
        }
        #endregion

        #region ICyShapeCustomize_v1 Members

        public CyCustErr CustomizeShapes(
            ICyInstQuery_v1 instQuery,
            ICySymbolShapeEdit_v1 shapeEdit,
            ICyTerminalEdit_v1 termEdit)
        {
            CyCustErr err;

            CyCompDevParam terminalWidth_param = instQuery.GetCommittedParam("ArrayWidth");
            uint terminalWidth;
            err = terminalWidth_param.TryGetValueAs<uint>(out terminalWidth);
            if (err.IsNotOk) return err;

            string suffix = CyBuilder.GetTermSuffix(terminalWidth);

            string newDTermName = "d" + suffix;
            string newQTermName = "q" + suffix;
                        
            string dTermName = termEdit.GetTermName("d");
            string qTermName = termEdit.GetTermName("q");
            
            termEdit.TerminalRename(dTermName, newDTermName);
            termEdit.TerminalRename(qTermName, newQTermName);
            
            if (terminalWidth > 1)
            {
                string labelTag = "Label";
                string[] labelTags = new string[] {labelTag};
                string lineTag = "Line";
                string[] lineTags = new string[] {lineTag};
            
                float quarterUnit = shapeEdit.UserBaseUnit / 4;
                shapeEdit.CreateLine(lineTags,
                    new PointF(-15 + quarterUnit, -18 - quarterUnit),
                    new PointF(-15 - quarterUnit, -18 + quarterUnit));
                shapeEdit.CreateLine(lineTags,
                    new PointF(15 + quarterUnit, -18 - quarterUnit),
                    new PointF(15 - quarterUnit, -18 + quarterUnit));
                    
                StringFormat widthFmt = new StringFormat();
                widthFmt.LineAlignment = StringAlignment.Far;
                widthFmt.Alignment = StringAlignment.Center;
                
                shapeEdit.CreateAnnotation(labelTags, terminalWidth.ToString(), new PointF(-15, -18), new Font(FontFamily.GenericSansSerif, 6, FontStyle.Regular), widthFmt);
                shapeEdit.CreateAnnotation(labelTags, terminalWidth.ToString(), new PointF(15, -18), new Font(FontFamily.GenericSansSerif, 6, FontStyle.Regular), widthFmt);
                
                shapeEdit.ClearOutline(labelTag);
                shapeEdit.SetFillColor(labelTag, Color.Black);
            }
            return CyCustErr.OK;
        }

        #endregion
    }
}
//[]//

