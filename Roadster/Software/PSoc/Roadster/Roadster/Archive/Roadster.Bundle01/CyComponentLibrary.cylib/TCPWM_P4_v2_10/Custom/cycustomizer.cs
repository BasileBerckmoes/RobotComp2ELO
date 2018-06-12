/*******************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Scc;
using System.Diagnostics;
using CyDesigner.Toolkit.TerminalControl_v1;
using CyTerminalControl_v1 = CyDesigner.Toolkit.TerminalControl_v1.CyTerminalControl_v1;

namespace TCPWM_P4_v2_10
{
    [CyCompDevCustomizer]
    sealed public partial class CyCustomizer :
        ICyParamEditHook_v1,
        ICySystemBuilderComp_v1,
        ICyInstNameCustomizer_v1,
        ICyClockControlData_v1<ICyInstEdit_v1>           
    {            
        #region ICyParamEditHook_v1 Members
        public const string TERM_VISIBILITY_PARAM_PREFIX = "TermVisibility_";

        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery,
              ICyExpressMgr_v1 mgr)
        {            
            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            CyParameters m_prms = new CyParameters(edit, termQuery);
            m_prms.Editor = editor;            

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

            CyConfigTab configTab = new CyConfigTab(m_prms);
            CyTCPWMTab tcpwmTab = new CyTCPWMTab(m_prms);
            CyTimerCounterTab tcTab = new CyTimerCounterTab(m_prms);
            CyPWMTab pwmTab = new CyPWMTab(m_prms);
            CyQuadDecTab quaddecTab = new CyQuadDecTab(m_prms);            

            CyParamExprDelegate exprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                m_prms.GlobalEditMode = false;
                m_prms.UpdateTabVisibility();
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

            editor.ParamExprCommittedDelegate = onParamChangeDelegate;

            editor.AddCustomPage(Resources.TabNameConfig, configTab, exprDelegate, configTab.TabName);
            editor.AddCustomPage(Resources.TabNameTCPWM, tcpwmTab, exprDelegate, tcpwmTab.TabName);
            editor.AddCustomPage(Resources.TabNameTC, tcTab, exprDelegate, tcTab.TabName);
            editor.AddCustomPage(Resources.TabNamePWM, pwmTab, exprDelegate, pwmTab.TabName);
            editor.AddCustomPage(Resources.TabNameQuadDec, quaddecTab, exprDelegate, quaddecTab.TabName);
            
            // System Builder support
            if (m_prms.InstQuery.DeviceQuery.IsPSoC4 && edit.IsInSystemBuilder)
            {
                interconnectTab = new CyTerminalControl_v1(edit);
                UpdateInterconnectDisplay(m_prms, interconnectTab);

                editor.AddCustomPage(Resources.InterconnectTabDisplayName, interconnectTab, exprDelegate,
                                     "Interconnect");
                editor.AddCustomPage(Resources.ClockTabDisplayName, clockTabControl, null, "Clock");
            }

            editor.AddDefaultPage(Resources.TabBuiltIn, "Built-in");
            
            m_prms.UpdateTabVisibility();

            editor.UseBigEditor = true;
            m_prms.GlobalEditMode = true;
            return editor.ShowDialog();
        }

        void UpdateInterconnectDisplay(CyParameters param, CyTerminalControl_v1 termControl)
        {
            CyTermControlRow_v1[] clocks = new CyTermControlRow_v1[1];
            clocks[0] = new CyTermControlRow_v1(CyTermName.CLOCK, CyTermName.CLOCK,
                        new CyTermMode_v1[] { CyTermMode_v1.Internal }, Resources.ClockTermDescription);
            termControl.Clocks = clocks;

            if (param.TCPWMConfig == CyETCPWMConfig.UNCONFIG)
            {
                CyTermControlRow_v1[] interrupts = new CyTermControlRow_v1[1];
                interrupts[0] = new CyTermControlRow_v1(CyTermName.INTERRUPT, CyTermName.INTERRUPT,
                                new CyTermMode_v1[] { CyTermMode_v1.Internal, CyTermMode_v1.Unused },
                                Resources.InterruptTermDescription);
                termControl.Interrupts = interrupts;
                termControl.SetTerminalMode(CyTermName.INTERRUPT, CyTermMode_v1.Unused);
            }
            else
            {
                CyTermMode_v1 mode = (param.InterruptMask == CyEInterruptMask.INTR_MASK_NONE) ?
                                    CyTermMode_v1.Unused : CyTermMode_v1.Internal;
                CyTermMode_v1[] validIntModes = new CyTermMode_v1[] { mode };
                CyTermControlRow_v1[] interrupts = new CyTermControlRow_v1[1];
                interrupts[0] = new CyTermControlRow_v1(CyTermName.INTERRUPT, CyTermName.INTERRUPT,
                                validIntModes, Resources.InterruptTermDescription);
                termControl.Interrupts = interrupts;
                termControl.SetTerminalMode(CyTermName.INTERRUPT, mode);
            }

            List<CyTermControlRow_v1> otherTerminals = new List<CyTermControlRow_v1>();

            if (param.TCPWMConfig == CyETCPWMConfig.TIMER)
            {
                otherTerminals.Add(new CyTermControlRow_v1(CyTermName.OV, CyTermName.OV,
                                   new CyTermMode_v1[] { CyTermMode_v1.Internal, CyTermMode_v1.Unused },
                                   Resources.OVTermDescription));
                otherTerminals.Add(new CyTermControlRow_v1(CyTermName.UN, CyTermName.UN,
                                   new CyTermMode_v1[] { CyTermMode_v1.Internal, CyTermMode_v1.Unused },
                                   Resources.UNTermDescription));
            }
            else if ((param.TCPWMConfig == CyETCPWMConfig.UNCONFIG) || (param.TCPWMConfig == CyETCPWMConfig.PWM_SEL))
            {                
                otherTerminals.Add(new CyTermControlRow_v1(CyTermName.LINE, CyTermName.LINE,
                                   new CyTermMode_v1[] { CyTermMode_v1.Internal, CyTermMode_v1.Unused },
                                   Resources.LineTermDescription));
                otherTerminals.Add(new CyTermControlRow_v1(CyTermName.LINE_N, CyTermName.LINE_N,
                                   new CyTermMode_v1[] { CyTermMode_v1.Internal, CyTermMode_v1.Unused },
                                   Resources.LineNTermDescription));

                if (!((param.TCPWMConfig == CyETCPWMConfig.PWM_SEL) && (param.PWMMode == CyEPWMMode.PWM_PR)))
                {
                    otherTerminals.Add(new CyTermControlRow_v1(CyTermName.OV, CyTermName.OV,
                                       new CyTermMode_v1[] { CyTermMode_v1.Internal, CyTermMode_v1.Unused },
                                       Resources.OVTermDescription));
                    otherTerminals.Add(new CyTermControlRow_v1(CyTermName.UN, CyTermName.UN,
                                       new CyTermMode_v1[] { CyTermMode_v1.Internal, CyTermMode_v1.Unused },
                                       Resources.UNTermDescription));
                }
            }

            string capture = string.Empty;
            string stop = string.Empty;
            string start = string.Empty;
            string count = string.Empty;
            string reload = string.Empty;

            switch (param.TCPWMConfig)
            {
                case CyETCPWMConfig.QUAD:
                    stop = Resources.StopQDPWMTermDescription;
                    start = Resources.StartQDTermDescription;
                    count = Resources.CountQDTermDescription;
                    reload = Resources.ReloadQDTermDescription;
                    break;
                case CyETCPWMConfig.TIMER:
                    capture = Resources.CaptureTimerTermDescription;
                    stop = Resources.StopTimerTermDescription;
                    start = Resources.StartTimerPWMTermDescription;
                    count = Resources.CountTimerPWMTermDescription;
                    reload = Resources.ReloadTimerPWMTermDescription;
                    break;
                case CyETCPWMConfig.PWM_SEL:
                    capture = Resources.CapturePWMTermDescription;
                    start = Resources.StartTimerPWMTermDescription;
                    count = Resources.CountTimerPWMTermDescription;
                    reload = Resources.ReloadTimerPWMTermDescription;
                    if (param.PWMMode == CyEPWMMode.PWM_DT)
                        stop = Resources.StopPWMDTTermDescription;
                    else
                        stop = Resources.StopQDPWMTermDescription;
                    break;
                case CyETCPWMConfig.UNCONFIG:
                default:
                    capture = Resources.CaptureUnconfiguredTermDescription;
                    stop = Resources.StopUnconfiguredTermDescription;
                    start = Resources.StartUnconfiguredTermDescription;
                    count = Resources.CountUnconfiguredTermDescription;
                    reload = Resources.ReloadUnconfiguredTermDescription;
                    break;
            }                

            otherTerminals.Add(new CyTermControlRow_v1(CyTermName.CC, CyTermName.CC,
                    new CyTermMode_v1[] { CyTermMode_v1.Internal, CyTermMode_v1.Unused },
                    Resources.CCTermDescription));

            if (param.InstQuery.GetCommittedParam(TERM_VISIBILITY_PARAM_PREFIX + CyTermName.STOP).GetValueAs<bool>())
            {
                otherTerminals.Add(new CyTermControlRow_v1(((param.TCPWMConfig == CyETCPWMConfig.PWM_SEL) && 
                    (param.PWMMode == CyEPWMMode.PWM_DT)) ?
                    CyTermName.KILL : CyTermName.STOP, CyTermName.STOP,
                    new CyTermMode_v1[] { CyTermMode_v1.Internal }, stop));
            }
            if (param.InstQuery.GetCommittedParam(TERM_VISIBILITY_PARAM_PREFIX + CyTermName.CAPTURE).GetValueAs<bool>())
            {
                otherTerminals.Add(new CyTermControlRow_v1((param.TCPWMConfig == CyETCPWMConfig.PWM_SEL) ?
                    CyTermName.SWITCH : CyTermName.CAPTURE, CyTermName.CAPTURE,
                    new CyTermMode_v1[] { CyTermMode_v1.Internal }, capture));
            }
            if (param.InstQuery.GetCommittedParam(TERM_VISIBILITY_PARAM_PREFIX + CyTermName.RELOAD).GetValueAs<bool>())
            {
                otherTerminals.Add(new CyTermControlRow_v1((param.TCPWMConfig == CyETCPWMConfig.QUAD) ?
                    CyTermName.INDEX : CyTermName.RELOAD, CyTermName.RELOAD,
                    new CyTermMode_v1[] { CyTermMode_v1.Internal }, reload));
            }
            if (param.InstQuery.GetCommittedParam(TERM_VISIBILITY_PARAM_PREFIX + CyTermName.COUNT).GetValueAs<bool>())
            {
                otherTerminals.Add(new CyTermControlRow_v1((param.TCPWMConfig == CyETCPWMConfig.QUAD) ?
                    CyTermName.PHI_A : CyTermName.COUNT, CyTermName.COUNT,
                    new CyTermMode_v1[] { CyTermMode_v1.Internal }, count));
            }
            if (param.InstQuery.GetCommittedParam(TERM_VISIBILITY_PARAM_PREFIX + CyTermName.START).GetValueAs<bool>())
            {
                otherTerminals.Add(new CyTermControlRow_v1((param.TCPWMConfig == CyETCPWMConfig.QUAD) ?
                    CyTermName.PHI_B : CyTermName.START, CyTermName.START,
                    new CyTermMode_v1[] { CyTermMode_v1.Internal }, start));
            }

            termControl.Other = otherTerminals;
        }


        public bool EditParamsOnDrop
        {
            get { return false; }
        }

        public CyCompDevParamEditorMode GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }

        #region ICySystemBuilderComp_v1 members

        public CyCustErr GetTitleText(ICySystemBuilderCompArgs_v1 args, out string title)
        {
            CyParameters parameters = new CyParameters(args.InstQuery);
            switch (parameters.TCPWMConfig)
            {
                case CyETCPWMConfig.PWM_SEL:
                    title = "PWM";
                    break;
                case CyETCPWMConfig.QUAD:
                    title = "QuadDec";
                    break;
                case CyETCPWMConfig.TIMER:
                    title = "Timer/Counter";
                    break;
                case CyETCPWMConfig.UNCONFIG:
                default:
                    title = "TCPWM";
                    break;
            }
            return CyCustErr.OK;
        }        

        public CyCustErr GetBodyText(ICySystemBuilderCompArgs_v1 args, out string bodyText)
        {
            CyParameters parameters = new CyParameters(args.InstQuery);
            switch (parameters.TCPWMConfig)
            {
                case CyETCPWMConfig.PWM_SEL:
                    string pwmMode = "";
                    string periodMode = "";
                    string compareMode = "";
                    switch (parameters.PWMMode)
                    {
                        case CyEPWMMode.PWM:
                            pwmMode = "PWM";
                            break;
                        case CyEPWMMode.PWM_DT:
                            pwmMode = "PWM DT";
                            break;
                        case CyEPWMMode.PWM_PR:
                            pwmMode = "PWM PR";
                            break;
                    }
                    if (parameters.PeriodSwap == CyESwapEnable.SWAP_ENABLE)
                    {
                        periodMode = parameters.Period1.ToString() + "/" + parameters.Period2.ToString();
                    }
                    else
                    {
                        periodMode = parameters.Period1.ToString();
                    }
                    if (parameters.CompareSwap == CyESwapEnable.SWAP_ENABLE)
                    {
                        compareMode = parameters.Compare1.ToString() + "/" + parameters.Compare2.ToString();
                    }
                    else
                    {
                        compareMode = parameters.Compare1.ToString();
                    }
                    bodyText = String.Format(Resources.SBComponentBodyTextPWM, 
                        CyParameters.GetDescription(parameters.PWMSetAlign), pwmMode, Environment.NewLine, periodMode, 
                        Environment.NewLine, compareMode);
                    break;
                case CyETCPWMConfig.QUAD:
                    bodyText = String.Format(Resources.SBComponentBodyTextQUAD, 
                        CyParameters.GetDescription(parameters.QuadEncodingModes));
                    break;
                case CyETCPWMConfig.TIMER:
                    if (parameters.CompCapMode == CyECompCapMode.Compare)
                    {
                        if (parameters.CompareSwap == CyESwapEnable.SWAP_ENABLE)
                        {
                            compareMode = parameters.Compare1.ToString() + "/" + parameters.Compare2.ToString();
                        }
                        else
                        {
                            compareMode = parameters.Compare1.ToString();
                        }
                        bodyText = String.Format(Resources.SBComponentBodyTextTIMERCompare,
                                                CyParameters.GetDescription(parameters.CountingModes),
                                                CyParameters.GetDescription(parameters.RunMode), parameters.Period1,
                                                Environment.NewLine, compareMode);
                    }
                    else
                    {
                        bodyText = String.Format(Resources.SBComponentBodyTextTIMERCapture,
                                                CyParameters.GetDescription(parameters.CountingModes),
                                                CyParameters.GetDescription(parameters.RunMode), parameters.Period1);
                    }
                    break;
                case CyETCPWMConfig.UNCONFIG:
                default:
                    bodyText = String.Format(Resources.SBComponentBodyTextUNCONFIG);
                    break;
            }
            return CyCustErr.OK;
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

        #region ICyInstNameCustomizer_v1 Members        
        public CyCustErr GetDefaultInstNamePrefix(ICyInstNameCustomizerArgs_v1 args, out string instNamePrefix)
        {    
            CyParameters parameters = new CyParameters(args.InstQuery);

            switch (parameters.TCPWMConfig)
            {
                case CyETCPWMConfig.PWM_SEL:
                    instNamePrefix = "PWM";
                    break;
                case CyETCPWMConfig.QUAD:
                    instNamePrefix = "QuadDec";
                    break;
                case CyETCPWMConfig.TIMER:
                    instNamePrefix = "Timer";
                    break;
                case CyETCPWMConfig.UNCONFIG:
                default:
                    instNamePrefix = "TCPWM";
                    break;
            }
            return CyCustErr.OK;
        }
        #endregion

        #endregion
    }

    #region Wrapper for Tabs
    public class CyEditingWrapperControl : UserControl, ICyParamEditingControl
    {
        private CyParameters m_prms = null;

        protected CyParameters Prms
        {
            get { return m_prms; }
            set { m_prms = value; }
        }

        public virtual string TabName
        {
            get { return "Empty"; }
        }

        public CyEditingWrapperControl() { }

        public CyEditingWrapperControl(CyParameters prms)
        {
            m_prms = prms;
            this.AutoScroll = true;
            this.Dock = DockStyle.Fill;
        }

        #region ICyParamEditingControl Members
        public Control DisplayControl
        {
            get { return this; }
        }

        // Gets any errors that exist for parameters on the DisplayControl.
        public virtual IEnumerable<CyCustErr> GetErrors()
        {
            foreach (string paramName in m_prms.InstQuery.GetParamNames())
            {
                CyCompDevParam param = m_prms.InstQuery.GetCommittedParam(paramName);
                if (param.TabName.Equals(TabName))
                {
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

        protected static void CommitCellValueImmediately(DataGridView dataGridView)
        {
            if (dataGridView.CurrentCell != null)
                if (dataGridView.CurrentCell.GetType() == typeof(DataGridViewCheckBoxCell) ||
                    dataGridView.CurrentCell.GetType() == typeof(DataGridViewComboBoxCell))
                    if (dataGridView.IsCurrentCellDirty)
                    {
                        dataGridView.CommitEdit(DataGridViewDataErrorContexts.Commit);
                    }
        }
    }
    #endregion
}
