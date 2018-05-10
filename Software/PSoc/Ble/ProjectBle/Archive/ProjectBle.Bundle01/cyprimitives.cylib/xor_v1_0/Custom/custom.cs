/*******************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;
using System.Diagnostics;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

using Cypress.Semiconductor.CyDesigner.cy_logic_gate_customizer;

namespace Cypress.Semiconductor.CyDesigner.xor_v1_0
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
            string generatedCodeSnippet;
            CyCustErr err = CyGateVerilogBuilder.BuildVerilog(CyGateType.XOR, termQuery, out generatedCodeSnippet);
            codeSnippet = generatedCodeSnippet;

            return err;
        }
        #endregion

        #region ICyShapeCustomize_v1 Members

        public CyCustErr CustomizeShapes(
            ICyInstQuery_v1 query, ICySymbolShapeEdit_v1 shapeEdit, ICyTerminalEdit_v1 termEdit)
        {
            return CyShapeCustomizer.CustomizeGateShapesWithArcs(query, shapeEdit, termEdit, CyGateType.XOR);
        }

        #endregion
    }
}
