/*******************************************************************************
* Copyright 2011-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;

namespace Bus_Connect_v2_40
{
    class CyCustomizer : ICyShapeCustomize_v1
    {
        const string OUTPUT_TERM_NAME = "out_bus";
        const string INPUT_TERM_NAME = "in_bus";
		const string TERM_NAME_CHANGE_PATTERN = "{0}[{1}:0]";

        public CyCustErr CustomizeShapes(ICyInstQuery_v1 instQuery, ICySymbolShapeEdit_v1 shapeEdit,
            ICyTerminalEdit_v1 termEdit)
        {
            CyCustErr err;

            // We leave the symbol as it is for symbol preview
            if (instQuery.IsPreviewCanvas)
                return CyCustErr.OK;

            // Read Parameters
            CyCompDevParam inWidthParam = instQuery.GetCommittedParam("in_width");
            CyCompDevParam outWidthParam = instQuery.GetCommittedParam("out_width");
            byte inWidth = byte.Parse(inWidthParam.Value);
            byte outWidth = byte.Parse(outWidthParam.Value);

            string inTermName = termEdit.GetTermName(INPUT_TERM_NAME);
            string outTermName = termEdit.GetTermName(OUTPUT_TERM_NAME);

            byte maxOutBitIndex = (byte)(outWidth - 1);
            byte maxInBitIndex = (byte)(inWidth - 1);

            err = termEdit.TerminalRename(outTermName, string.Format(TERM_NAME_CHANGE_PATTERN,
                OUTPUT_TERM_NAME, maxOutBitIndex.ToString()));
            if (err.IsNotOK)
            {
                return err;
            }
            err = termEdit.TerminalRename(inTermName, string.Format(TERM_NAME_CHANGE_PATTERN,
                INPUT_TERM_NAME, maxInBitIndex.ToString()));
            if (err.IsNotOK)
            {
                return err;
            }

            return CyCustErr.OK;
        }
    }
}
