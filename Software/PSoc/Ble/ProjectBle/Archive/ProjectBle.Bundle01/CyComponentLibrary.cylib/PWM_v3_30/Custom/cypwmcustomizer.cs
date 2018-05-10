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
using System;
using CyDesigner.Toolkit.TerminalControl_v1;
using CyTerminalControl_v1 = CyDesigner.Toolkit.TerminalControl_v1.CyTerminalControl_v1;

namespace PWM_v3_30
{
    [CyCompDevCustomizer()]
    public class CyCustomizer : ICyParamEditHook_v1, ICyDRCProvider_v1,
        ICySystemBuilderComp_v1, ICyClockControlData_v1<ICyInstEdit_v1>, ICyDesignClient_v2
    {
        public const string CONFIGURE_TAB_NAME = "Basic";
        public const string ADVANCED_TAB_NAME = "Advanced";

        #region ICyParamEditHook_v1 Members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters m_prms = new CyParameters(edit, termQuery);
            CyConfigureTab m_control = new CyConfigureTab(m_prms);
            CyAdvancedTab m_controladv = new CyAdvancedTab(m_control, m_prms);

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();

            CyTerminalControl_v1 interconnectTab = null;
            ICyClockControl_v1 clockControl = edit.DesignQuery.CreateClockCustomizerControl(this, edit);

            CyClockParamEditingControl clockTabControl = new CyClockParamEditingControl(
                edit,
                clockControl.DisplayControl,
                CyClockParamName.CHECK_TOLERANCE,
                CyClockParamName.DESIRED_FREQ,
                CyClockParamName.DESIRED_FREQ_UNIT,
                CyClockParamName.DIVISOR,
                CyClockParamName.IS_DESIRED_FREQ,
                CyClockParamName.IS_DIRECT,
                CyClockParamName.IS_DIVIDER,
                CyClockParamName.MINUS_TOLERANCE,
                CyClockParamName.PLUS_TOLERANCE,
                CyClockParamName.SOURCE_CLOCK_ID,
                CyClockParamName.SOURCE_CLOCK_NAME,
                CyClockParamName.FRACT_DIVIDER_USED,
                CyClockParamName.FRACT_DIVIDER_NUMERATOR,
                CyClockParamName.FRACT_DIVIDER_DENOMINATOR);

            CyParamExprDelegate basicExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                m_prms.GlobalEditMode = false;
                m_control.UpdateFormFromParams();
                if (interconnectTab != null)
                {
                    UpdateInterconnectDisplay(m_prms, interconnectTab);
                }
                m_prms.GlobalEditMode = true;
            };
            CyParamExprDelegate advExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                m_prms.GlobalEditMode = false;
                m_controladv.UpdateFormFromParams();
                if (interconnectTab != null)
                {
                    UpdateInterconnectDisplay(m_prms, interconnectTab);
                }
                m_prms.GlobalEditMode = true;
            };
            // This code will be executed every time when any parameter is changed.
            CyParamExprDelegate onParamChangeDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                m_prms.GlobalEditMode = false;
                if (interconnectTab != null)
                {
                    UpdateInterconnectDisplay(m_prms, interconnectTab);
                }
                m_prms.GlobalEditMode = true;
            };
            CyParamExprDelegate onClockParamsChangeDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
            };
            editor.ParamExprCommittedDelegate = onParamChangeDelegate;

            editor.AddCustomPage(Resources.ConfigureTabDisplayName, m_control,
                                                   new CyParamExprDelegate(basicExprDelegate), CONFIGURE_TAB_NAME);
            editor.AddCustomPage(Resources.AdvancedTabDisplayName, m_controladv,
                                                   new CyParamExprDelegate(advExprDelegate), ADVANCED_TAB_NAME);
            
            if (m_prms.InstQuery.DeviceQuery.IsPSoC4 && edit.IsInSystemBuilder)
            {
                interconnectTab = new CyTerminalControl_v1(edit);
                UpdateInterconnectDisplay(m_prms, interconnectTab);

                editor.AddCustomPage(Resources.InterconnectTabDisplayName, interconnectTab, basicExprDelegate,
                                 "Interconnect");
                editor.AddCustomPage(Resources.ClockTabDisplayName, clockTabControl, onClockParamsChangeDelegate, 
                    "Clock");
            }

            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");
            edit.NotifyWhenDesignUpdates(new CyDesignUpdated_v1(m_control.UpdateClock));

            m_control.UpdateFormFromParams();
            m_controladv.UpdateFormFromParams();

            m_prms.GlobalEditMode = true;
            
            return editor.ShowDialog();
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

        void UpdateInterconnectDisplay(CyParameters param, CyTerminalControl_v1 termControl)
        {
            CyTermControlRow_v1[] clocks = new CyTermControlRow_v1[1];
            clocks[0] = new CyTermControlRow_v1(CyTermName.CLOCK, CyTermName.CLOCK,
                        new CyTermMode_v1[] { CyTermMode_v1.Internal }, Resources.ClockTermDescription);
            termControl.Clocks = clocks;
            
            CyTermControlRow_v1[] interrupts = new CyTermControlRow_v1[1];
            interrupts[0] = new CyTermControlRow_v1(CyTermName.INTERRUPT, CyTermName.INTERRUPT,
                            new CyTermMode_v1[] { CyTermMode_v1.Internal },
                            Resources.InterruptTermDescription);
            termControl.Interrupts = interrupts;
            if (param.UseInterrupt)
            {
                termControl.SetTerminalMode(CyTermName.INTERRUPT, CyTermMode_v1.Internal);
            }
            else
            {
                termControl.SetTerminalMode(CyTermName.INTERRUPT, CyTermMode_v1.Unused);
            }

            List<CyTermControlRow_v1> otherTerminals = new List<CyTermControlRow_v1>();

            if ((param.EnableMode.Value == CyEEnableMode.B_PWM__Software_And_Hardware) ||
                    (param.EnableMode.Value == CyEEnableMode.B_PWM__Hardware_Only))
                otherTerminals.Add(new CyTermControlRow_v1(CyTermName.ENABLE, CyTermName.ENABLE,
                                   new CyTermMode_v1[] { },
                                   Resources.EnableTermDescription));
            if (param.PwmMode.Value == CyEPwmMode.B_PWM__HardwareSelect)
                otherTerminals.Add(new CyTermControlRow_v1(CyTermName.CMP_SEL, CyTermName.CMP_SEL,
                                   new CyTermMode_v1[] { },
                                   Resources.CompareSelectTermDescription));
            if (param.KillMode.Value != CyEKillMode.B_PWM__Disabled)
                otherTerminals.Add(new CyTermControlRow_v1(CyTermName.KILL, CyTermName.KILL,
                                   new CyTermMode_v1[] { },
                                   Resources.KillTermDescription));
            if ((param.CaptureMode.Value != CyECaptureMode.B_PWM__None) && !param.FixedFunction)
                otherTerminals.Add(new CyTermControlRow_v1(CyTermName.CAPTURE, CyTermName.CAPTURE,
                                   new CyTermMode_v1[] { },
                                   Resources.CaptureTermDescription));
            if (param.TriggerMode.Value != CyETriggerMode.B_PWM__TMNone)
                otherTerminals.Add(new CyTermControlRow_v1(CyTermName.TRIGGER, CyTermName.TRIGGER,
                                   new CyTermMode_v1[] { },
                                   Resources.TriggerTermDescription));

            otherTerminals.Add(new CyTermControlRow_v1(CyTermName.RESET, CyTermName.RESET,
                                   new CyTermMode_v1[] { CyTermMode_v1.Internal, CyTermMode_v1.Unused },
                                   Resources.ResetTermDescription));
            otherTerminals.Add(new CyTermControlRow_v1(CyTermName.TC, CyTermName.TC,
                                   new CyTermMode_v1[] { CyTermMode_v1.Internal, CyTermMode_v1.Unused },
                                   Resources.TCTermDescription));

            if (param.PwmMode.Value != CyEPwmMode.B_PWM__Two_Outputs)
                otherTerminals.Add(new CyTermControlRow_v1(CyTermName.PWM, CyTermName.PWM,
                                   new CyTermMode_v1[] { CyTermMode_v1.Internal, CyTermMode_v1.Unused },
                                   Resources.PWMTermDescription));
            if (param.PwmMode.Value == CyEPwmMode.B_PWM__Two_Outputs)
                otherTerminals.Add(new CyTermControlRow_v1(CyTermName.PWM1, CyTermName.PWM1,
                                   new CyTermMode_v1[] { CyTermMode_v1.Internal, CyTermMode_v1.Unused },
                                   Resources.PWM1TermDescription));
            if ((param.PwmMode.Value == CyEPwmMode.B_PWM__Two_Outputs) && !param.FixedFunction)
                otherTerminals.Add(new CyTermControlRow_v1(CyTermName.PWM2, CyTermName.PWM2,
                                   new CyTermMode_v1[] { CyTermMode_v1.Internal, CyTermMode_v1.Unused },
                                   Resources.PWM2TermDescription));
            if ((param.DeadBand.Value != CyEDeadBandMode.B_PWM__DBMDisabled) && !param.FixedFunction)
            {
                otherTerminals.Add(new CyTermControlRow_v1(CyTermName.PH1, CyTermName.PH1,
                                   new CyTermMode_v1[] { CyTermMode_v1.Internal, CyTermMode_v1.Unused },
                                   Resources.Ph1TermDescription));
                otherTerminals.Add(new CyTermControlRow_v1(CyTermName.PH2, CyTermName.PH2,
                                   new CyTermMode_v1[] { CyTermMode_v1.Internal, CyTermMode_v1.Unused },
                                   Resources.Ph2TermDescription));
            }

            termControl.Other = otherTerminals;
        }

        #region ICySystemBuilderComp_v1 members

        public CyCustErr GetTitleText(ICySystemBuilderCompArgs_v1 args, out string title)
        {
            title = Resources.SBComponentTitle;
            return CyCustErr.OK;
        }

        private string GetCompareType(CyECompareType type)
        {
            string compareType = "";

            switch (type)
            {
                case CyECompareType.B_PWM__Less_Than:
                    compareType = Resources.Less;
                    break;
                case CyECompareType.B_PWM__Less_Than_Or_Equal:
                    compareType = Resources.LessOrEqual;
                    break;
                case CyECompareType.B_PWM__Greater_Than:
                    compareType = Resources.Greater;
                    break;
                case CyECompareType.B_PWM__Greater_Than_Or_Equal_To:
                    compareType = Resources.GreaterOrEqual;
                    break;
                case CyECompareType.B_PWM__Equal:
                    compareType = Resources.Equal;
                    break;
                case CyECompareType.B_PWM__Firmware:
                    compareType = Resources.FirmwareControl;
                    break;
            }

            return compareType;
        }

        public CyCustErr GetBodyText(ICySystemBuilderCompArgs_v1 args, out string bodyText)
        {
            CyParameters parameters = new CyParameters(args.InstQuery);

            switch (parameters.PwmMode.Value)
            {
                case CyEPwmMode.B_PWM__Center_Align:
                case CyEPwmMode.B_PWM__One_Output:                    
                    bodyText = String.Format(Resources.SBBodyTextOneOutput, parameters.Period, Environment.NewLine,
                        GetCompareType(parameters.CompareType1.Value), parameters.CompareValue1);
                    break;
                case CyEPwmMode.B_PWM__Dual_Edge:
                case CyEPwmMode.B_PWM__HardwareSelect:
                case CyEPwmMode.B_PWM__Two_Outputs:                    
                    bodyText = String.Format(Resources.SBBodyTextTwoOutputs, parameters.Period, Environment.NewLine,
                        GetCompareType(parameters.CompareType1.Value), parameters.CompareValue1, Environment.NewLine,
                        GetCompareType(parameters.CompareType2.Value), parameters.CompareValue2);
                    break;
                case CyEPwmMode.B_PWM__Dither:
                    bodyText = String.Format(Resources.SBBodyTextDither, parameters.Period, Environment.NewLine,
                        parameters.CompareValue1);
                    break;                
                default:
                    bodyText = "";
                    break;
            }
            return CyCustErr.OK;
        }
        #endregion

        #region ICyDesignClient_v2  members
        public string GetDesignClientState(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            return string.Empty;
        }

        public bool RequiresTooltipUpdate(string designClientState, ICyInstQuery_v1 query,
            ICyTerminalQuery_v1 termQuery)
        {
            return false;
        }

        public bool RequiresShapeUpdate(string designClientState, ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            return true;
        }
        #endregion

        #region ICyClockControlData_v1<ICyInstEdit_v1> members
        bool ICyClockControlData_v1<ICyInstEdit_v1>.GetCheckTolerance(ICyInstEdit_v1 edit)
        {
            return CyParameters.GetValue<bool>(CyClockParamName.CHECK_TOLERANCE, edit);
        }

        uint ICyClockControlData_v1<ICyInstEdit_v1>.GetDivider(ICyInstEdit_v1 edit)
        {
            return CyParameters.GetValue<uint>(CyClockParamName.DIVISOR, edit);
        }

        uint ICyClockControlData_v1<ICyInstEdit_v1>.GetFractDividerDenominator(ICyInstEdit_v1 edit)
        {
            return CyParameters.GetValue<uint>(CyClockParamName.FRACT_DIVIDER_DENOMINATOR, edit);
        }

        uint ICyClockControlData_v1<ICyInstEdit_v1>.GetFractDividerNumerator(ICyInstEdit_v1 edit)
        {
            return CyParameters.GetValue<uint>(CyClockParamName.FRACT_DIVIDER_NUMERATOR, edit);
        }

        bool ICyClockControlData_v1<ICyInstEdit_v1>.GetFractDividerUsed(ICyInstEdit_v1 edit)
        {
            return CyParameters.GetValue<bool>(CyClockParamName.FRACT_DIVIDER_USED, edit);
        }

        byte ICyClockControlData_v1<ICyInstEdit_v1>.GetFrequencyUnit(ICyInstEdit_v1 edit)
        {
            return CyParameters.GetValue<byte>(CyClockParamName.DESIRED_FREQ_UNIT, edit);
        }

        double ICyClockControlData_v1<ICyInstEdit_v1>.GetFrequencyValue(ICyInstEdit_v1 edit)
        {
            return CyParameters.GetValue<double>(CyClockParamName.DESIRED_FREQ, edit);
        }

        bool ICyClockControlData_v1<ICyInstEdit_v1>.GetIsExistingClock(ICyInstEdit_v1 edit)
        {
            return CyParameters.GetValue<bool>(CyClockParamName.IS_DIRECT, edit);
        }

        bool ICyClockControlData_v1<ICyInstEdit_v1>.GetIsNewDividerClock(ICyInstEdit_v1 edit)
        {
            return CyParameters.GetValue<bool>(CyClockParamName.IS_DIVIDER, edit);
        }

        bool ICyClockControlData_v1<ICyInstEdit_v1>.GetIsNewFreqClock(ICyInstEdit_v1 edit)
        {
            return CyParameters.GetValue<bool>(CyClockParamName.IS_DESIRED_FREQ, edit);
        }

        double ICyClockControlData_v1<ICyInstEdit_v1>.GetMinusTolerance(ICyInstEdit_v1 edit)
        {
            return CyParameters.GetValue<double>(CyClockParamName.MINUS_TOLERANCE, edit);
        }

        double ICyClockControlData_v1<ICyInstEdit_v1>.GetPlusTolerance(ICyInstEdit_v1 edit)
        {
            return CyParameters.GetValue<double>(CyClockParamName.PLUS_TOLERANCE, edit);
        }

        string ICyClockControlData_v1<ICyInstEdit_v1>.GetSrcClkID(ICyInstEdit_v1 edit)
        {
            return CyParameters.GetValue<string>(CyClockParamName.SOURCE_CLOCK_ID, edit);
        }

        string ICyClockControlData_v1<ICyInstEdit_v1>.GetSrcClkName(ICyInstEdit_v1 edit)
        {
            return CyParameters.GetValue<string>(CyClockParamName.SOURCE_CLOCK_NAME, edit);
        }

        CyCustErr ICyClockControlData_v1<ICyInstEdit_v1>.IsDividerValid(ICyInstEdit_v1 edit, string value)
        {
            return CyParameters.SetValue(edit, CyClockParamName.DIVISOR, value);
        }

        CyCustErr ICyClockControlData_v1<ICyInstEdit_v1>.IsFreqUnitValid(ICyInstEdit_v1 edit, string value)
        {
            return CyParameters.SetValue(edit, CyClockParamName.DESIRED_FREQ_UNIT, value);
        }

        CyCustErr ICyClockControlData_v1<ICyInstEdit_v1>.IsFreqValid(ICyInstEdit_v1 edit, string value)
        {
            return CyParameters.SetValue(edit, CyClockParamName.DESIRED_FREQ, value);
        }

        CyCustErr ICyClockControlData_v1<ICyInstEdit_v1>.IsMinusToleranceValid(ICyInstEdit_v1 edit, string value)
        {
            return CyParameters.SetValue(edit, CyClockParamName.MINUS_TOLERANCE, value);
        }

        CyCustErr ICyClockControlData_v1<ICyInstEdit_v1>.IsPlusToleranceValid(ICyInstEdit_v1 edit, string value)
        {
            return CyParameters.SetValue(edit, CyClockParamName.PLUS_TOLERANCE, value);
        }

        CyCustErr ICyClockControlData_v1<ICyInstEdit_v1>.IsSourceClkIdValid(ICyInstEdit_v1 edit, string value)
        {
            return CyParameters.SetValue(edit, CyClockParamName.SOURCE_CLOCK_ID, value);
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnCheckToleranceChanged(ICyInstEdit_v1 edit, bool checkTolerance)
        {
            CyParameters.SetValue(edit, CyClockParamName.CHECK_TOLERANCE, checkTolerance);
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnDividerChanged(ICyInstEdit_v1 edit, uint divider)
        {
            CyParameters.SetValue(edit, CyClockParamName.DIVISOR, divider);
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnFractDividerNumeratorChanged(ICyInstEdit_v1 edit, uint numerator,
            uint denominator)
        {
            CyParameters.SetValue(edit, CyClockParamName.FRACT_DIVIDER_NUMERATOR, numerator);
            CyParameters.SetValue(edit, CyClockParamName.FRACT_DIVIDER_DENOMINATOR, denominator);
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnFractDividerUsedChanged(ICyInstEdit_v1 edit, bool used,
            uint denominator)
        {
            CyParameters.SetValue(edit, CyClockParamName.FRACT_DIVIDER_USED, used);
            CyParameters.SetValue(edit, CyClockParamName.FRACT_DIVIDER_DENOMINATOR, (used ? denominator : 0));
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnFreqChanged(ICyInstEdit_v1 edit, double frequencyValue,
            byte frequencyUnit)
        {
            CyParameters.SetValue(edit, CyClockParamName.DESIRED_FREQ, frequencyValue);
            CyParameters.SetValue(edit, CyClockParamName.DESIRED_FREQ_UNIT, frequencyUnit);
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnIsNewChanged(ICyInstEdit_v1 edit, bool isExistingClock)
        {
            CyParameters.SetValue(edit, CyClockParamName.IS_DIRECT, isExistingClock);
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnMinusToleranceChanged(ICyInstEdit_v1 edit, double minusTolerance)
        {
            CyParameters.SetValue(edit, CyClockParamName.MINUS_TOLERANCE, minusTolerance);
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnPlusToleranceChanged(ICyInstEdit_v1 edit, double plusTolerance)
        {
            CyParameters.SetValue(edit, CyClockParamName.PLUS_TOLERANCE, plusTolerance);
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnSourceClkChanged(ICyInstEdit_v1 edit, string srcClkId,
            string srcClkName)
        {
            CyParameters.SetValue(edit, CyClockParamName.SOURCE_CLOCK_ID, srcClkId);
            CyParameters.SetValue(edit, CyClockParamName.SOURCE_CLOCK_NAME, srcClkName);
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnUseDividerChanged(ICyInstEdit_v1 edit, bool isNewDividerClock)
        {
            CyParameters.SetValue(edit, CyClockParamName.IS_DIVIDER, isNewDividerClock);
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnUseFreqChanged(ICyInstEdit_v1 edit, bool isNewFreqClock)
        {
            CyParameters.SetValue(edit, CyClockParamName.IS_DESIRED_FREQ, isNewFreqClock);
        }
        #endregion

        #region CyClockParamEditingControl which represents Clock tab
        class CyClockParamEditingControl : ICyParamEditingControl
        {
            private readonly ICyInstEdit_v1 m_instEdit;
            private readonly Control m_displayControl;
            private readonly string[] m_paramNames;

            public CyClockParamEditingControl(ICyInstEdit_v1 editObj, Control displayControl,
                params string[] paramNames)
            {
                m_instEdit = editObj;
                m_displayControl = displayControl;
                m_paramNames = paramNames;
            }

            public Control DisplayControl
            {
                get { return m_displayControl; }
            }

            public IEnumerable<CyCustErr> GetErrors()
            {
                foreach (string paramName in m_paramNames)
                {
                    CyCompDevParam param = m_instEdit.GetCommittedParam(paramName);
                    if (param.ErrorCount > 0)
                    {
                        foreach (string errMsg in param.Errors)
                        {
                            yield return new CyCustErr(errMsg);
                        }
                    }
                }
            }
        }
        #endregion

        #region ICyDRCProvider_v1 Members
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CyCustErr err = VerifyImplementation(args.InstQueryV1);
            if (err.IsOk == false)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err.Message);
        }

        CyCustErr VerifyImplementation(ICyInstQuery_v1 instQuery)
        {
            if (instQuery.DeviceQuery.IsPSoC4)
            {
                bool fixedFunction;
                bool.TryParse(instQuery.GetCommittedParam(CyParamNames.FIXED_FUNCTION).Expr, out fixedFunction);

                if (fixedFunction)
                    return new CyCustErr(Resources.ImplementationDrcError);
            }
            return CyCustErr.OK;
        }
        #endregion
    }
}
