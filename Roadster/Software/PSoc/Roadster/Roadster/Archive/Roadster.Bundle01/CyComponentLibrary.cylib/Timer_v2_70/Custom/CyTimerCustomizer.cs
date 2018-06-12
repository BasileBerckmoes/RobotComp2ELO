/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System.Collections.Generic;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace Timer_v2_70
{
    [CyCompDevCustomizer()]
    public class CyCustomizer : ICyParamEditHook_v1, ICyDRCProvider_v1
    {
        #region ICyParamEditHook_v1 Members
        ICyInstEdit_v1 m_component = null;
        private const string m_builtin = "Built-in";
        const string PSOC5A = "PSoC5A";
        const string OneShotHaltOnInterruptMode = "2";
        const string OneShotMode = "1";
        const string HardwareAndSoftwareMode = "2";
        const string FixedFunctionMode = "true";
        const string OneShotHaltOnInterruptErrMsg = "One Shot (Halt on Interrupt) not supported for Fixed Function " +
                                                    "Timer implementations. The UDB implementation can be used for " +
                                                    "this functionality.";
        const string OneShotModeErrMsg = "One Shot mode with a hardware enable not supported for the Fixed Function " +
                                         "Timer implementation on PSoC 5. The UDB implementation can be used for " +
                                         "this functionality.";

        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyTimerControl m_control = null;
            CyTimerEditingControl m_timerEditingControl = null;
            m_component = edit;
            m_control = new CyTimerControl(edit, termQuery);
            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            m_timerEditingControl = new CyTimerEditingControl(edit, termQuery, m_control);
            CyParamExprDelegate ExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                m_control.UpdateFormFromParams(edit);
            };
            editor.AddCustomPage(CyTimerParameters.S_CONFIGURE, m_timerEditingControl,
                new CyParamExprDelegate(ExprDelegate), CyTimerParameters.S_BASIC);
            editor.AddDefaultPage(m_builtin, m_builtin);

            edit.NotifyWhenDesignUpdates(new CyDesignUpdated_v1(m_control.UpdateClock));
            DialogResult result = editor.ShowDialog();
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
            string fixedFunction = args.InstQueryV1.GetCommittedParam(CyTimerParameters.S_FIXEDFUNCTION).Value;
            string runMode = args.InstQueryV1.GetCommittedParam(CyTimerParameters.S_RUNMODE).Value;
            string hardwareEnable = args.InstQueryV1.GetCommittedParam(CyTimerParameters.S_ENABLEMODE).Value;

            List<CyCustErr> err = new List<CyCustErr>();
            err.Add(VerifyRunMode(args, fixedFunction, runMode, hardwareEnable));
            err.Add(VerifyImplementation(args.InstQueryV1));

            for (int i = 0; i < err.Count; i++)
            {
                if (err[i].IsOk == false)
                    yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err[i].Message);
            }
        }

        CyCustErr VerifyRunMode(ICyDRCProviderArgs_v1 drcQuery, string fixedFunction, string runMode,
                                 string hardwareEnable)
        {
            if (runMode.Equals(OneShotHaltOnInterruptMode) && fixedFunction.Equals(FixedFunctionMode))
            {
                return new CyCustErr(OneShotHaltOnInterruptErrMsg);
            }

            if ((drcQuery.DeviceQueryV1.ArchFamilyMember == PSOC5A && drcQuery.DeviceQueryV1.IsPSoC5 == true) &&
                fixedFunction.Equals(FixedFunctionMode) && runMode.Equals(OneShotMode) &&
                hardwareEnable.Equals(HardwareAndSoftwareMode))
            {
                return new CyCustErr(OneShotModeErrMsg);
            }
            return CyCustErr.OK;
        }

        CyCustErr VerifyImplementation(ICyInstQuery_v1 instQuery)
        {
            if (instQuery.DeviceQuery.IsPSoC4)
            {
                bool fixedFunction;
                bool.TryParse(instQuery.GetCommittedParam(CyTimerParameters.S_FIXEDFUNCTION).Expr, out fixedFunction);

                if (fixedFunction)
                    return new CyCustErr(Resources.ImplementationDrcError);
            }
            return CyCustErr.OK;
        }
        #endregion

        //Create a new control to add to a tab
        public class CyTimerEditingControl : ICyParamEditingControl
        {
            CyTimerControl m_control;
            Panel displayControl = new Panel();
            ICyInstEdit_v1 m_component = null;

            public CyTimerEditingControl(ICyInstEdit_v1 inst, ICyTerminalQuery_v1 termquery, CyTimerControl control)
            {
                m_component = inst;
                m_control = control;
                displayControl.Dock = DockStyle.Fill;
                displayControl.AutoScroll = true;
                displayControl.AutoScrollMinSize = m_control.Size;

                m_control.Dock = DockStyle.Fill;
                displayControl.Controls.Add(m_control);
            }

            #region ICyParamEditingControl Members
            public Control DisplayControl
            {
                get { return displayControl; }
            }

            public IEnumerable<CyCustErr> GetErrors()
            {
                List<CyCustErr> errors = new List<CyCustErr>();

                if (m_component != null)
                {
                    foreach (string paramName in m_component.GetParamNames())
                    {
                        CyCompDevParam param = m_component.GetCommittedParam(paramName);
                        if (param.TabName.Equals(CyTimerParameters.S_BASIC))
                        {
                            if (param.ErrorCount > 0)
                            {
                                foreach (string errMsg in param.Errors)
                                {
                                    CyCustErr error = new CyCustErr(errMsg);
                                    if (errors.Contains(error) == false)
                                        errors.Add(error);
                                }
                            }
                        }
                    }
                }

                return errors;
            }

            #endregion
        }
    }
}
