/*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
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

namespace Cypress.Semiconductor.CyDesigner.cy_sync_v1_0
{
    public class CyCustomizer :
        ICyShapeCustomize_v1
    {
        const string S_IN_TERM_BASE_NAME = "s_in";
        const string S_OUT_TERM_BASE_NAME = "s_out";

        #region ICyShapeCustomize_v1 Members

        public CyCustErr CustomizeShapes(
            ICyInstQuery_v1 instQuery,
            ICySymbolShapeEdit_v1 shapeEdit,
            ICyTerminalEdit_v1 termEdit)
        {
            CyCompDevParam terminalWidth_param = instQuery.GetCommittedParam("SignalWidth");
            uint terminalWidth = uint.Parse(terminalWidth_param.Value);

            string suffix = CyBuilder.GetTermSuffix(terminalWidth);

            string newSInName = S_IN_TERM_BASE_NAME + suffix;
            string newSOutName = S_OUT_TERM_BASE_NAME + suffix;

            string sInName = termEdit.GetTermName(S_IN_TERM_BASE_NAME);
            string sOutName = termEdit.GetTermName(S_OUT_TERM_BASE_NAME);

            termEdit.TerminalRename(sInName, newSInName);
            termEdit.TerminalRename(sOutName, newSOutName);

            return CyCustErr.OK;
        }

        #endregion
    }
}
