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

namespace Cypress.Semiconductor.CyDesigner.cy_constant_v1_0
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
            uint value = uint.Parse(instQuery.GetCommittedParam("Value").Value);
            uint terminalWidth = uint.Parse(instQuery.GetCommittedParam("Width").Value);
            string suffix = CyBuilder.GetTermSuffix(terminalWidth);
            
            CyVerilogBuilder vGen = new CyVerilogBuilder();

            string valSigSegName = termQuery.GetTermSigSegName("val" + suffix);

            vGen.AddAssignStatement(valSigSegName, String.Format("{0}'h{1:X}", terminalWidth, value));

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

            CyCompDevParam  width_param = instQuery.GetCommittedParam("Width");
            byte terminalWidth;
            err = width_param.TryGetValueAs<byte>(out terminalWidth);
            if (err.IsNotOk) return err;
            
            CyCompDevParam  value_param = instQuery.GetCommittedParam("Value");
            uint value;
            err = value_param.TryGetValueAs<uint>(out value);
            if (err.IsNotOk) return err;
			
			CyCompDevParam  hex_param = instQuery.GetCommittedParam("DisplayAsHex");
            bool dispAsHex;
            err = hex_param.TryGetValueAs<bool>(out dispAsHex);
            if (err.IsNotOk) return err;

            string suffix = CyBuilder.GetTermSuffix(terminalWidth);
            string newValTermName = "val" + suffix;
            string valTermName = termEdit.GetTermName("val");
            
            termEdit.TerminalRename(valTermName, newValTermName);
            
            string rectTag = "Rect";
            string[] rectTags = new string[] {rectTag};
            string lineTag = "Line";
            string[] lineTags = new string[] {lineTag};
            string labelTag = "Label";
            string[] labelTags = new string[] {labelTag};
			string widthTag = "Width";
            string[] widthTags = new string[] {widthTag};
            
            float boxWidth = 24f;
			string valString;
			if (dispAsHex)
			{
	            string formatString = String.Format("0x{{0:X{0}}}",(terminalWidth + 3)/ 4);
	            valString = String.Format(formatString, value);
			}
			else
			{
				valString = value.ToString();
			}
			
			StringFormat fmt = new StringFormat();
            fmt.LineAlignment = StringAlignment.Center;
            fmt.Alignment = StringAlignment.Center;
			
            shapeEdit.CreateAnnotation(labelTags, valString, new PointF(0f, 0f), new Font(FontFamily.GenericSansSerif, 10, FontStyle.Regular), fmt);
            boxWidth = shapeEdit.GetShapeBounds(labelTag).Width + 1f;
			
			// round boxWidth up to mult. of 6 (min 18)
			boxWidth = boxWidth < 18f ? 18f : (float)Math.Ceiling(boxWidth / 6) * 6f;
			
            shapeEdit.CreateRectangle(rectTags, new PointF(6 - boxWidth, -5f), boxWidth, 10f);
			shapeEdit.ShapesMoveTo(labelTag, new PointF(6f - boxWidth / 2, 0f));
			shapeEdit.BringToFront(labelTag);
                        
            if (terminalWidth > 1)
            {
                float quarterUnit = shapeEdit.UserBaseUnit / 4;
                shapeEdit.CreateLine(lineTags,
                            new PointF(9 + quarterUnit, 0 - quarterUnit),
                            new PointF(9 - quarterUnit, 0 + quarterUnit));
                            
                StringFormat widthFmt = new StringFormat();
                widthFmt.LineAlignment = StringAlignment.Far;
                widthFmt.Alignment = StringAlignment.Center;
                shapeEdit.CreateAnnotation(widthTags, terminalWidth.ToString(), new PointF(9f, 0f), new Font(FontFamily.GenericSansSerif, 6, FontStyle.Regular), widthFmt);
            }

            shapeEdit.ClearOutline(labelTag);
            shapeEdit.SetFillColor(labelTag, Color.Black);
			shapeEdit.ClearOutline(widthTag);
            shapeEdit.SetFillColor(widthTag, Color.Black);
            shapeEdit.SetFillColor(rectTag, Color.Gainsboro);
            
            return CyCustErr.OK;
        }

        #endregion
    }
}
//[]//

