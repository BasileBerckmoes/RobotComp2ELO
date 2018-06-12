/*******************************************************************************
* Copyright 2011-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;

namespace cy_psoc4_csd_v1_0
{
    class CyCustomizer : ICyShapeCustomize_v1
    {
        const string SOURCE_BASE_TERM_NAME = "source";
		const string TERM_NAME_CHANGE_PATTERN = "{0}[{1}:0]";

        public CyCustErr CustomizeShapes(ICyInstQuery_v1 instQuery, ICySymbolShapeEdit_v1 shapeEdit,
            ICyTerminalEdit_v1 termEdit)
        {
            CyCustErr err;

            // We leave the symbol as it is for symbol preview
            if (instQuery.IsPreviewCanvas)
                return CyCustErr.OK;

            // Read Parameters
            CyCompDevParam sensorsCountParam = instQuery.GetCommittedParam("sensors_count");
            byte sensorsCount = byte.Parse(sensorsCountParam.Value);

            string sourceTermName = termEdit.GetTermName(SOURCE_BASE_TERM_NAME);

            byte busWidth = (byte)(sensorsCount - 1);

            err = termEdit.TerminalRename(sourceTermName, busWidth > 0 ? string.Format(TERM_NAME_CHANGE_PATTERN,
                SOURCE_BASE_TERM_NAME, busWidth.ToString()) : SOURCE_BASE_TERM_NAME);

			if (err.IsNotOK)
            {
                return err;
            }

            return CyCustErr.OK;
        }
    }
}
