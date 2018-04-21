/*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
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

namespace Cypress.Semiconductor.CyDesigner.cydff_v1_30
{
    public class CyCustomizer :
        ICyVerilogCustomize_v1,
        ICyShapeCustomize_v1
    {
        const string GENERATED_SHAPE = "SymbolShape";
        const string RESET_VALUE = "0";
        const int APRESET = 1;
        const int ARESET = 2;        
        const int SPRESET = 3;
        const int SRESET = 4;
        const int SPRESETRESET = 5;

        #region ICyVerilogCustomize_v1 Members

        public CyCustErr CustomizeVerilog(
            ICyInstQuery_v1 instQuery,
            ICyTerminalQuery_v1 termQuery,
            out string codeSnippet)
        {
		    CyCustErr err;
            Debug.Assert(instQuery != null);
            if (instQuery == null)
            {
                codeSnippet = string.Empty;
                return new CyCustErr("Invalid instance query parameter");
            }

            CyCompDevParam terminalWidth_param = instQuery.GetCommittedParam("ArrayWidth");
            uint terminalWidth = uint.Parse(terminalWidth_param.Value);
            string suffix = CyBuilder.GetTermSuffix(terminalWidth);
			
			CyCompDevParam multiPresetReset_param = instQuery.GetCommittedParam("MultiPresetReset");
            bool multiPresetReset;
            err = multiPresetReset_param.TryGetValueAs<bool>(out multiPresetReset);

            CyVerilogBuilder vGen = new CyVerilogBuilder();
            vGen.AddComment("-- DFF Start --");
			
            CyCompDevParam presetOrReset_param = instQuery.GetCommittedParam("PresetOrReset");
            int presetOrReset = int.Parse(presetOrReset_param.Value);
            bool needAP = presetOrReset == APRESET;
            bool needAR = presetOrReset == ARESET;
            bool needSP = presetOrReset == SPRESET || presetOrReset == SPRESETRESET;
            bool needSR = presetOrReset == SRESET || presetOrReset == SPRESETRESET;
            
			string rstSuffix = multiPresetReset ? suffix : "";
			
			string dSigSegName = termQuery.GetTermSigSegName("d" + suffix);
            string qSigSegName = termQuery.GetTermSigSegName("q" + suffix);
			string clkSigSegName = termQuery.GetTermSigSegScalarName("clk");
			string apSigSegName = needAP ? termQuery.GetTermSigSegName("ap" + rstSuffix) : string.Empty;
            string arSigSegName = needAR ? termQuery.GetTermSigSegName("ar" + rstSuffix) : string.Empty;
            string spSigSegName = needSP ? termQuery.GetTermSigSegName("sp" + rstSuffix) : string.Empty;
            string srSigSegName = needSR ? termQuery.GetTermSigSegName("sr" + rstSuffix) : string.Empty;
			string regName = instQuery.InstanceName;
			
			//declare a register to hold the value in the always block
            vGen.DeclareReg(instQuery.InstanceName, suffix);
			
			int numAlwaysBlocks = (multiPresetReset && (needAR || needAP)) ? (int)terminalWidth : 1;
			
			for (int i = 0; i < numAlwaysBlocks; ++i)
			{
				if (i != 0)
					vGen.WriteLine("");
				
				string dSeg = numAlwaysBlocks > 1 ? getIndexInSigSeg(dSigSegName, i) : dSigSegName;
				string qSeg = numAlwaysBlocks > 1 ? getIndexInSigSeg(qSigSegName, i) : qSigSegName;
				string arSeg = numAlwaysBlocks > 1 ? getIndexInSigSeg(arSigSegName, i) : arSigSegName;
				string apSeg = numAlwaysBlocks > 1 ? getIndexInSigSeg(apSigSegName, i) : apSigSegName;
				string srSeg = numAlwaysBlocks > 1 ? getIndexInSigSeg(srSigSegName, i) : srSigSegName;
				string spSeg = numAlwaysBlocks > 1 ? getIndexInSigSeg(spSigSegName, i) : spSigSegName;
				string regSeg = numAlwaysBlocks > 1 ? regName + "[" + i + "]" : regName;
				
				List<string> SensitivityList = new List<string>();
            	List<CyVerilogBuilder.EdgeTypeEnum> signalEdgeList = new List<CyVerilogBuilder.EdgeTypeEnum>();

	            if (needAP)
	            {
					if (apSigSegName.Contains("["))
					{
						string tmpAP = CyVerilogBuilder.GetTmpName("tmp", instQuery.InstanceName, "ap_" + i);
						vGen.DeclareWire(tmpAP, "");
						vGen.AddAssignStatement(tmpAP, apSeg);
						apSeg = tmpAP;
					}
	                SensitivityList.Add(apSeg);
	                signalEdgeList.Add(CyVerilogBuilder.EdgeTypeEnum.POSITIVE);				
	            }
	            else if (needAR)
	            {
					if (arSigSegName.Contains("["))
					{
						string tmpAR = CyVerilogBuilder.GetTmpName("tmp", instQuery.InstanceName, "ar_" + i);
						vGen.DeclareWire(tmpAR, "");
						vGen.AddAssignStatement(tmpAR, arSeg);
						arSeg = tmpAR;
					}
	                SensitivityList.Add(arSeg);
	                signalEdgeList.Add(CyVerilogBuilder.EdgeTypeEnum.POSITIVE);
	            }
	            
				if (clkSigSegName.Contains("["))
				{
					string tmpClk = CyVerilogBuilder.GetTmpName("tmp", instQuery.InstanceName, "clk");
					vGen.DeclareWire(tmpClk, "");
					vGen.AddAssignStatement(tmpClk, clkSigSegName);
					clkSigSegName = tmpClk;
				}
	            SensitivityList.Add(clkSigSegName);
	            signalEdgeList.Add(CyVerilogBuilder.EdgeTypeEnum.POSITIVE);

	            vGen.DefineAlways(SensitivityList, signalEdgeList);
	            vGen.BeginBlock();

	            if (needAR)
	            {
	                vGen.AddIfStmt(arSeg);
	                vGen.AddNonBlockingStatement(regSeg, RESET_VALUE);
	                vGen.AddEndIfStmt();
					vGen.AddElseStmt();
	            }
	            else if (needAP)
	            {
	                vGen.AddIfStmt(apSeg);
	                vGen.AddNonBlockingStatement(regSeg, "~" + RESET_VALUE);
	                vGen.AddEndIfStmt();
					vGen.AddElseStmt();
	            }
					
				string rValue = dSeg;
				if (needSP)
					rValue = "(" + rValue + " | " + spSeg + ")";
					
				if (needSR)
					rValue = "(" + rValue + "& ~" + srSeg + ")";
				
	            vGen.AddNonBlockingStatement(regSeg, rValue);

	            if (needAP || needAR)
	                vGen.AddEndIfStmt();

	            vGen.EndBlock();
				
	            vGen.AddAssignStatement(qSeg, regSeg);
			}

            vGen.AddComment("-- DFF End --");
            codeSnippet = vGen.VerilogString;

            return CyCustErr.OK;
        }
		
		// Returns the single-bit net given the vector and the index (0 is lsb)
		// eg. (foo[8:4], 2) would return 5
		// (foo[4:8], 2) would return 7
		private static string getIndexInSigSeg(string sigSegName, int index)
		{	
			if (String.IsNullOrEmpty(sigSegName))
				return String.Empty;
			
			int msbIdxStart = sigSegName.IndexOf('[') + 1;
			int msbIdx = int.Parse(sigSegName.Substring(msbIdxStart, sigSegName.IndexOf(':') - msbIdxStart));
			
			int lsbIdxStart = sigSegName.IndexOf(':') + 1;
			int lsbIdx = int.Parse(sigSegName.Substring(lsbIdxStart, sigSegName.IndexOf(']') - lsbIdxStart));
			
			int reqIdx = msbIdx < lsbIdx ? lsbIdx - index : lsbIdx + index;
			return sigSegName.Substring(0, msbIdxStart - 1) + "[" + reqIdx + "]";
		}
		
        #endregion

        #region ICyShapeCustomize_v1 Members

        public CyCustErr CustomizeShapes(
            ICyInstQuery_v1 instQuery,
            ICySymbolShapeEdit_v1 shapeEdit,
            ICyTerminalEdit_v1 termEdit)
        {
            CyCustErr err;
            
            Font termLabelFont = new Font(FontFamily.GenericSansSerif, 10, FontStyle.Regular);
            
            string labelTag = "Label";
            string[] labelTags = new string[] {labelTag};
			string lineTag = "Line";
            string[] lineTags = new string[] {lineTag};
            string rectTag = "Rect";
            string[] rectTags = new string[] {rectTag};
			
            StringFormat fmt = new StringFormat();
            fmt.LineAlignment = StringAlignment.Near;
            fmt.Alignment = StringAlignment.Near;
            StringFormat rtFmt = new StringFormat();
            rtFmt.LineAlignment = StringAlignment.Near;
            rtFmt.Alignment = StringAlignment.Far;
            StringFormat ctrFmt = new StringFormat();
            ctrFmt.LineAlignment = StringAlignment.Center;
            ctrFmt.Alignment = StringAlignment.Center;
            
            CyCompDevParam smallMode_param = instQuery.GetCommittedParam("SmallMode");
            bool smallMode;
            err = smallMode_param.TryGetValueAs<bool>(out smallMode);
            if (err.IsNotOk) return err;
            
            CyCompDevParam terminalWidth_param = instQuery.GetCommittedParam("ArrayWidth");
            uint terminalWidth;
            err = terminalWidth_param.TryGetValueAs<uint>(out terminalWidth);
            if (err.IsNotOk) return err;

            string suffix = CyBuilder.GetTermSuffix(terminalWidth);
            
            CyCompDevParam MultiPresetReset_param = instQuery.GetCommittedParam("MultiPresetReset");
            bool multiPresetReset;
            err = MultiPresetReset_param.TryGetValueAs<bool>(out multiPresetReset);
            if (err.IsNotOk) return err;
            
            CyCompDevParam presetOrReset_param = instQuery.GetCommittedParam("PresetOrReset");
            int presetOrReset;
            err = presetOrReset_param.TryGetValueAs<int>(out presetOrReset);
            if (err.IsNotOk) return err;
            
            bool needAP = presetOrReset == APRESET;
            bool needAR = presetOrReset == ARESET;
            bool needSP = presetOrReset == SPRESET || presetOrReset == SPRESETRESET;
            bool needSR = presetOrReset == SRESET || presetOrReset == SPRESETRESET;
            
			string rstSuffix = (multiPresetReset) ? suffix : "";
            string apTermName = "ap" + rstSuffix;
            string arTermName = "ar" + rstSuffix;
            string spTermName = "sp" + rstSuffix;
            string srTermName = "sr" + rstSuffix;
            
            float leftEdge;
            float rightEdge;
            float topEdge;
            float bottomEdge;
            float dqHeight;
            float clkHeight;
            if (smallMode)
            {
                leftEdge = -12f;
                rightEdge = 12f;
                topEdge = (needAP || needSP) ? -30f : -18f;
                bottomEdge = (needAR || needSR) ? 30f : 18f;
                dqHeight = -12f;
                clkHeight = 12f;
            }
            else
            {
                leftEdge = -24f;
                rightEdge = 24f;
                topEdge = -42f;
                bottomEdge = 42f;
                dqHeight = -18f;
                clkHeight = 24f;
            }
            
            shapeEdit.CreateRectangle(rectTags, new PointF(leftEdge, topEdge), rightEdge - leftEdge, bottomEdge - topEdge);
            shapeEdit.CreatePolyline(lineTags, new PointF(leftEdge, clkHeight - 6), new PointF(leftEdge + 6, clkHeight), new PointF(leftEdge, clkHeight + 6));
            
            termEdit.TerminalAdd("d" + suffix, CyCompDevTermDir.INPUT, CyCompDevTermType.DIGITAL, new PointF(leftEdge - 6, dqHeight), String.Empty, 0, false);
            termEdit.TerminalAdd("q" + suffix, CyCompDevTermDir.OUTPUT, CyCompDevTermType.DIGITAL, new PointF(rightEdge + 6, dqHeight), String.Empty, 0, false);
            termEdit.TerminalAdd("clk", CyCompDevTermDir.INPUT, CyCompDevTermType.DIGITAL, new PointF(leftEdge - 6, clkHeight), String.Empty, 0, false);
            termEdit.SetMustConnectIfVisible("d" + suffix, false);
            termEdit.SetMustConnectIfVisible("q" + suffix, false);
            termEdit.SetMustConnectIfVisible("clock", false);
            
            if (smallMode)
                shapeEdit.CreateAnnotation(labelTags, "DFF", new PointF(0f,0f), new Font(FontFamily.GenericSansSerif, 8, FontStyle.Regular), ctrFmt);
            else
                shapeEdit.CreateAnnotation(labelTags, "DFF", new PointF(-14f,-11f), new Font(FontFamily.GenericSansSerif, 12, FontStyle.Regular), fmt);
                
            shapeEdit.CreateAnnotation(labelTags, "d", new PointF(leftEdge, dqHeight - 6), termLabelFont, fmt);
            shapeEdit.CreateAnnotation(labelTags, "q", new PointF(rightEdge, dqHeight - 6), termLabelFont, rtFmt);
            shapeEdit.CreateAnnotation(labelTags, (smallMode) ? "clk" : "clock", new PointF(leftEdge + 6,clkHeight - 6), termLabelFont, fmt);
            

            if (needAP)
            {
                termEdit.TerminalAdd(apTermName, CyCompDevTermDir.INPUT, CyCompDevTermType.DIGITAL, new PointF(-0f, topEdge - 6), String.Empty, 90, false);
                shapeEdit.CreateAnnotation(labelTags, "ap", new PointF(-7f, topEdge - 1), termLabelFont, fmt);
            }
            if (needAR)
            {
                termEdit.TerminalAdd(arTermName, CyCompDevTermDir.INPUT, CyCompDevTermType.DIGITAL, new PointF(-0f, bottomEdge + 6), String.Empty, -90, false);
                shapeEdit.CreateAnnotation(labelTags, "ar", new PointF(-6f, bottomEdge - 13), termLabelFont, fmt);
            }
            if (needSP)
            {
                termEdit.TerminalAdd(spTermName, CyCompDevTermDir.INPUT, CyCompDevTermType.DIGITAL, new PointF(-0f, topEdge - 6), String.Empty, 90, false);
                shapeEdit.CreateAnnotation(labelTags, "sp", new PointF(-7f, topEdge - 1), termLabelFont, fmt);
            }
            if (needSR)
            {
                termEdit.TerminalAdd(srTermName, CyCompDevTermDir.INPUT, CyCompDevTermType.DIGITAL, new PointF(-0f, bottomEdge + 6), String.Empty, -90, false);
                shapeEdit.CreateAnnotation(labelTags, "sr", new PointF(-6f, bottomEdge - 13), termLabelFont, fmt);
            }
            
            if (terminalWidth > 1)
            {
                if (smallMode)
                {
                    float quarterUnit = shapeEdit.UserBaseUnit / 4;
                    shapeEdit.CreateLine(lineTags,
                        new PointF(leftEdge - 3 + quarterUnit, dqHeight - quarterUnit),
                        new PointF(leftEdge - 3 - quarterUnit, dqHeight + quarterUnit));
                    shapeEdit.CreateLine(lineTags,
                        new PointF(rightEdge + 3 + quarterUnit, dqHeight - quarterUnit),
                        new PointF(rightEdge + 3 - quarterUnit, dqHeight + quarterUnit));
                        
                    StringFormat widthFmt = new StringFormat();
                    widthFmt.LineAlignment = StringAlignment.Far;
                    widthFmt.Alignment = StringAlignment.Center;
                    
                    shapeEdit.CreateAnnotation(labelTags, terminalWidth.ToString(), new PointF(leftEdge - 3, dqHeight), new Font(FontFamily.GenericSansSerif, 6, FontStyle.Regular), widthFmt);
                    shapeEdit.CreateAnnotation(labelTags, terminalWidth.ToString(), new PointF(rightEdge + 3, dqHeight), new Font(FontFamily.GenericSansSerif, 6, FontStyle.Regular), widthFmt);
                
                    if (multiPresetReset)
                    {
                        if (needAP || needSP)
                        {
                            shapeEdit.CreateLine(lineTags,
                                new PointF(0 + quarterUnit, topEdge - 3 - quarterUnit),
                                new PointF(0 - quarterUnit, topEdge - 3 + quarterUnit));
                                
                            shapeEdit.CreateAnnotation(labelTags, terminalWidth.ToString(), new PointF(0f, topEdge - 6f), new Font(FontFamily.GenericSansSerif, 6, FontStyle.Regular), rtFmt);
                        }
                        if (needAR || needSR)
                        {
                            shapeEdit.CreateLine(lineTags,
                                new PointF(0 + quarterUnit, bottomEdge + 3 - quarterUnit),
                                new PointF(0 - quarterUnit, bottomEdge + 3 + quarterUnit));
                                
                            shapeEdit.CreateAnnotation(labelTags, terminalWidth.ToString(), new PointF(0f, bottomEdge), new Font(FontFamily.GenericSansSerif, 6, FontStyle.Regular), rtFmt);
                        }
                    }
                }
                else
                {
                    shapeEdit.CreateAnnotation(labelTags, "/" + terminalWidth, new PointF(-37f,-16f), new Font(FontFamily.GenericSansSerif, 7, FontStyle.Regular), fmt);
                    shapeEdit.CreateAnnotation(labelTags, "/" + terminalWidth, new PointF(25f,-16f), new Font(FontFamily.GenericSansSerif, 7, FontStyle.Regular), fmt);
                    
                    if (multiPresetReset)
                    {
                        if (needAP || needSP)
                            shapeEdit.CreateAnnotation(labelTags, "/" + terminalWidth, new PointF(2f,-52f), new Font(FontFamily.GenericSansSerif, 7, FontStyle.Regular), fmt);
                        if (needAR || needSR)
                            shapeEdit.CreateAnnotation(labelTags, "/" + terminalWidth, new PointF(2f,44f), new Font(FontFamily.GenericSansSerif, 7, FontStyle.Regular), fmt);
                    }
                }
                
            }
            
            shapeEdit.ClearOutline(labelTag);
            shapeEdit.SetFillColor(labelTag, Color.Black);
            shapeEdit.SetFillColor(rectTag, Color.White);
            
            termEdit.ChangeTerminalDefVerilogValue(apTermName, (needAP) ? string.Empty : "1'b0");
            termEdit.ChangeTerminalDefVerilogValue(arTermName, (needAR) ? string.Empty : "1'b0");
            termEdit.ChangeTerminalDefVerilogValue(spTermName, (needSP) ? string.Empty : "1'b0");
            termEdit.ChangeTerminalDefVerilogValue(srTermName, (needSR) ? string.Empty : "1'b0");
            
            return CyCustErr.OK;
        }

        #endregion
    }
}
//[]//

