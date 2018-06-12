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
using System.IO;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using CyCustomizer.CyControlReg_v1_80;

namespace CyCustomizer.CyControlReg_v1_80
{
    [CyCompDevCustomizer()]
    public class CyCustomizer :
        ICyParamEditHook_v1,
        ICyDRCProvider_v1,
        ICyExprEval_v2,
        ICyShapeCustomize_v1
    {
        public const int FIRST_BITMODE_INDEX = 0;
        public const int DEFAULT_NUMOUTPUT = 1;
        public const int PULSE_MODE = 3;
        public const string PSOC5A = "PSoC5A";

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
                if (comp.Name == CyControlReg_v1_80.ControlRegParameters.NUMOUTPUTS)
                {
                    int outputs;

                    if (!Int32.TryParse(
                                m_Component.GetCommittedParam(CyControlReg_v1_80.ControlRegParameters.NUMOUTPUTS).Value,
                                out outputs))
                    {
                        // Minimum number of output
                        outputs = DEFAULT_NUMOUTPUT;
                    }

                    m_Component.SetParamExpr(CyControlReg_v1_80.ControlRegParameters.BIT0MODE, Resources.DIRECTMODE);
                    m_Component.SetParamExpr(CyControlReg_v1_80.ControlRegParameters.BIT1MODE, Resources.DIRECTMODE);
                    m_Component.SetParamExpr(CyControlReg_v1_80.ControlRegParameters.BIT2MODE, Resources.DIRECTMODE);
                    m_Component.SetParamExpr(CyControlReg_v1_80.ControlRegParameters.BIT3MODE, Resources.DIRECTMODE);
                    m_Component.SetParamExpr(CyControlReg_v1_80.ControlRegParameters.BIT4MODE, Resources.DIRECTMODE);
                    m_Component.SetParamExpr(CyControlReg_v1_80.ControlRegParameters.BIT5MODE, Resources.DIRECTMODE);
                    m_Component.SetParamExpr(CyControlReg_v1_80.ControlRegParameters.BIT6MODE, Resources.DIRECTMODE);
                    m_Component.SetParamExpr(CyControlReg_v1_80.ControlRegParameters.BIT7MODE, Resources.DIRECTMODE);
                }
            };

            CyParamExprDelegate ExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                // When parameters are edited in the expression view
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

        #region ICyDRCProvider_v1 Members

        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CyCustErr err = VerifyBitField(args);
            if (err.IsOk == false) { yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err.Message); }
        }

        CyCustErr VerifyBitField(ICyDRCProviderArgs_v1 drcQuery)
        {
            int outputs;
            outputs = Convert.ToInt16
                     (drcQuery.InstQueryV1.GetCommittedParam(CyControlReg_v1_80.ControlRegParameters.NUMOUTPUTS).Value);

            if (drcQuery.DeviceQueryV1.IsPSoC5 == true && drcQuery.DeviceQueryV1.ArchFamilyMember == PSOC5A)
            {
                for (int i = FIRST_BITMODE_INDEX; i < outputs; i++)
                {
                    CyCompDevParam BitMode = drcQuery.InstQueryV1.GetCommittedParam(Resources.BIT + i.ToString() +
                                                Resources.MODE);
                    if (Convert.ToInt32(BitMode.Value) == PULSE_MODE)
                    {
                        return new CyCustErr(Resources.VerifyBitFieldParamErrorMsg);
                    }
                }
            }

            return CyCustErr.OK;
        }

        #endregion

        #region ICyExprEval_v2 Members

        CyExprEvalFuncEx ICyExprEval_v2.GetFunction(string exprFuncName)
        {
            switch (exprFuncName)
            {
                case "ExternalResetValidate":
                    return new CyExprEvalFuncEx(ExternalResetValidate);

                default:
                    return null;
            }
        }

        Object ExternalResetValidate(string exprFuncName,
            object[] args,
            ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            object retValue = 0;
            bool a = true;
            int numOutputs = typeConverter.GetAsInt(args[0]);

            for (int i = 0; i < numOutputs && args.Length > 1 && 8 >= numOutputs; i++)
            {
                a &= !(typeConverter.GetAsBool(args[i + 1]));
            }

            retValue = Convert.ToInt16(a);

            if (!a)
            {
                if ((custArgs != null) && (custArgs.InstQuery.DeviceQuery.ArchFamilyMember == PSOC5A) &&
                    (custArgs.InstQuery.DeviceQuery.IsPSoC5 == true))
                {
                    retValue = 2;
                    for (int i = 0; i < numOutputs && args.Length > 1 && 8 >= numOutputs; i++)
                    {
                        if (typeConverter.GetAsInt(args[i + 1]) == 3)
                        {
                            retValue = Convert.ToInt16(a);
                            break;
                        }
                    }
                }
            }

            return retValue;
        }

        #endregion

        #region ICyShapeCustomize_v1 Members

        public CyCustErr CustomizeShapes(ICyInstQuery_v1 instQuery,
            ICySymbolShapeEdit_v1 shapeEdit,
            ICyTerminalEdit_v1 termEdit)
        {
            CyCompDevParam busDisplay = instQuery.GetCommittedParam(CyControlReg_v1_80.ControlRegParameters.BUS);
            int outputs = Convert.ToInt16(
                                 instQuery.GetCommittedParam(CyControlReg_v1_80.ControlRegParameters.NUMOUTPUTS).Value);

            if (busDisplay.Value == Resources.TRUE && outputs != 1)
            {
                // Co-ordinates of the terminal control_bus
                float X = 42f;
                float Y = -6f;
                string suf = string.Empty;
                suf = string.Format("[{0}:0]", outputs-1);

                termEdit.TerminalAdd("control_bus" + suf, CyCompDevTermDir.OUTPUT, CyCompDevTermType.DIGITAL,
                                        new PointF(X, Y), string.Empty, 0f, false);
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
            return new CyCustErr[] { };    // return an empty array 
        }

        #endregion
    }
}
