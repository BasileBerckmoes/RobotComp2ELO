/*******************************************************************************
* Copyright 2012-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace cy_mxs40_lcd_v1_0
{
    [CyCompDevCustomizer()]
    public partial class CyCustomizer : ICyShapeCustomize_v1
    {
        #region Parameters names
        const string PARAM_COMMON_WIDTH = "common_width";
        const string PARAM_SEGMENT_WIDTH = "segment_width";
        #endregion

        #region ICyShapeCustomize_v1
        const string COMMON_BUS_NAME = "com";
        const string SEGMENT_BUS_NAME = "seg";
        const string TERM_PATERN = "{0}[{1}:0]";
        public CyCustErr CustomizeShapes(ICyInstQuery_v1 instQuery, ICySymbolShapeEdit_v1 shapeEdit,
            ICyTerminalEdit_v1 termEdit)
        {
            CyCustErr err;
            // We leave the symbol as it is for symbol preview
            if (instQuery.IsPreviewCanvas)
                return CyCustErr.OK;

            // Read Parameter(s)
            CyCompDevParam param = instQuery.GetCommittedParam(PARAM_COMMON_WIDTH);
            byte commonWidth = (byte)(byte.Parse(param.Value) - 1);
            param = instQuery.GetCommittedParam(PARAM_SEGMENT_WIDTH);
            byte segmentWidth = (byte)(byte.Parse(param.Value) - 1);

            // Rename terminal(s)
            string common_bus = termEdit.GetTermName(COMMON_BUS_NAME);
            err = termEdit.TerminalRename(common_bus, string.Format(TERM_PATERN, COMMON_BUS_NAME, commonWidth));
            if (err.IsNotOK) return err;
            string segment_bus = termEdit.GetTermName(SEGMENT_BUS_NAME);
            err = termEdit.TerminalRename(segment_bus, string.Format(TERM_PATERN, SEGMENT_BUS_NAME, segmentWidth));
            if (err.IsNotOK) return err;
            return CyCustErr.OK;
        }
        #endregion
    }
}
