/*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.Drawing;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using CyCustomizer.CyStatusReg_v1_80;

namespace CyCustomizer.CyStatusReg_v1_80
{
    [CyCompDevCustomizer()]
    public class CyCustomizer : ICyParamEditHook_v1, ICyShapeCustomize_v1
    {

        #region ICyParamEditHook_v1 Members

        public ICyInstEdit_v1 m_Component = null;
        public CyBitFieldEditingControl m_bitFieldEdit = null;

        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            m_Component = edit;

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();

            m_bitFieldEdit = new CyBitFieldEditingControl(edit);

            CyParamExprDelegate ParamCommitted = delegate(ICyParamEditor custEditor, CyCompDevParam comp)
            {
                // For right now it needs to atleast set a default BitField of the correct Length
                if (comp.Name == CyStatusReg_v1_80.StatusRegParameters.NUMINPUTS)
                {
                    int inputs;

                    if(!Int32.TryParse(
                                m_Component.GetCommittedParam(CyStatusReg_v1_80.StatusRegParameters.NUMINPUTS).Value,
                                out inputs))
                    {
                        // Minimum number of input
                        inputs = CyBitfieldControl.MIN_INPUTS;
                    }

                    m_Component.SetParamExpr(CyStatusReg_v1_80.StatusRegParameters.BIT0MODE, Resource.TRANSPARENT);
                    m_Component.SetParamExpr(CyStatusReg_v1_80.StatusRegParameters.BIT1MODE, Resource.TRANSPARENT);                         
                    m_Component.SetParamExpr(CyStatusReg_v1_80.StatusRegParameters.BIT2MODE, Resource.TRANSPARENT);
                    m_Component.SetParamExpr(CyStatusReg_v1_80.StatusRegParameters.BIT3MODE, Resource.TRANSPARENT);
                    m_Component.SetParamExpr(CyStatusReg_v1_80.StatusRegParameters.BIT4MODE, Resource.TRANSPARENT);
                    m_Component.SetParamExpr(CyStatusReg_v1_80.StatusRegParameters.BIT5MODE, Resource.TRANSPARENT);
                    m_Component.SetParamExpr(CyStatusReg_v1_80.StatusRegParameters.BIT6MODE, Resource.TRANSPARENT);
                    m_Component.SetParamExpr(CyStatusReg_v1_80.StatusRegParameters.BIT7MODE, Resource.TRANSPARENT);
                }
            };
            CyParamExprDelegate ExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                m_bitFieldEdit.UpdateFormFromParams(edit);
            };

            editor.AddCustomPage("Configure", m_bitFieldEdit, new CyParamExprDelegate(ExprDelegate), "Basic",
                                    "Advanced");
            editor.AddDefaultPage("Built-in", "Built-in");
            DialogResult result = editor.ShowDialog();
            editor.ParamExprCommittedDelegate = ParamCommitted;
            return result;
        }

        public bool EditParamsOnDrop
        {
            get { return false; }
        }

        public CyCompDevParamEditorMode GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }

        #endregion

        #region ICyShapeCustomize_v1 Members

        public CyCustErr CustomizeShapes(ICyInstQuery_v1 instQuery,
            ICySymbolShapeEdit_v1 shapeEdit,
            ICyTerminalEdit_v1 termEdit)
        {
            CyCompDevParam busDisplay = instQuery.GetCommittedParam(CyStatusReg_v1_80.StatusRegParameters.BUS);
            int inputs = Convert.ToInt16(
                                    instQuery.GetCommittedParam(CyStatusReg_v1_80.StatusRegParameters.NUMINPUTS).Value);

            if (busDisplay.Value == "true" && inputs != 1 && inputs < 8)
            {
                // Remove the existing terminal and add new
                termEdit.TerminalDelete("status_bus[7:0]");

                // Co-ordinates of the terminal status_bus
                float X = -42f;
                float Y = 6f;
                string suf = string.Empty;
                suf = string.Format("[{0}:0]", inputs - 1);

                // Default Verilog Expression
                string vExpr = string.Empty;
                vExpr = string.Format("{0}'b0", inputs);

                termEdit.TerminalAdd("status_bus" + suf, CyCompDevTermDir.INPUT, CyCompDevTermType.DIGITAL,
                                        new PointF(X, Y), vExpr, 0f, false);
                termEdit.SetMustConnectIfVisible("status_bus" + suf, false);
            }

            return CyCustErr.OK;
        }

        #endregion
    }

    //Create a new control to add to a tab
    public class CyBitFieldEditingControl : ICyParamEditingControl
    {
        CyBitfieldControl m_control;

        public CyBitFieldEditingControl(ICyInstEdit_v1 inst)
        {
            m_control = new CyBitfieldControl(inst);
            m_control.Dock = DockStyle.Fill;
        }

        #region ICyParamEditingControl Members
        public Control DisplayControl
        {
            get { return m_control; }
        }

        public void UpdateFormFromParams(ICyInstEdit_v1 inst)
        {
            m_control.UpdateFormFromInst(inst);
        }
        
        public IEnumerable<CyCustErr> GetErrors()
        {
            return new CyCustErr[] { };    //return an empty array
        }

        #endregion
    }
}
