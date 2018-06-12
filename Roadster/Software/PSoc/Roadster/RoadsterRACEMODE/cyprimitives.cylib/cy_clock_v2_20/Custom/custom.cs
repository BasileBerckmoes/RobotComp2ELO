/*******************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System.Diagnostics;

using CyDesigner.Common.Base;
using CyDesigner.Common.Base.Dialogs;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using CyDesigner.Framework;

namespace Cypress.Components.System.cy_clock_v2_20
{
    public class CyCustomizer :
        ICyParamEditHook_v1,
        ICyToolTipCustomize_v1,
        ICyVerilogCustomize_v1,
        ICyClockDataProvider_v1,
        ICyAPICustomize_v1,
        ICyDesignClient_v1,
        ICyDesignClient_v2,
        ICyShapeCustomize_v1,
        ICyClockControlData_v2<ICyInstEdit_v1>,
        ICyAdvClockControlData_v1<ICyInstEdit_v1>
    {
        const string RtlName = "cy_clock_v1_0";

        #region ICyParamEditHook_v1 Members

        public CyCompDevParamEditorMode GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }

        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyClockParamInfo info = new CyClockParamInfo(edit);
            ICyDesignQuery_v1 design = edit.DesignQuery;

            ICyClockControl_v2 control = design.CreateClockCustomizerControl(this, edit);
            CyClockParamEditingControl clkControl = new CyClockParamEditingControl(
                edit,
                control.DisplayControl,
                CyClockParamInfo.CheckToleranceParamName,
                CyClockParamInfo.DesiredFreqParamName,
                CyClockParamInfo.DesiredFreqUnitParamName,
                CyClockParamInfo.DivisorParamName,
                CyClockParamInfo.IsDesiredFreqParamName,
                CyClockParamInfo.IsDirectParamName,
                CyClockParamInfo.IsDividerParamName,
                CyClockParamInfo.MinusToleranceParamName,
                CyClockParamInfo.PlusToleranceParamName,
                CyClockParamInfo.SourceClockIdParamName,
                CyClockParamInfo.SourceClockNameParamName,
                CyClockParamInfo.FractDividerUsedParamName,
                CyClockParamInfo.FractDividerNumeratorParamName,
                CyClockParamInfo.FractDividerDenominatorParamName,
                CyClockParamInfo.PhaseAlignClockIdParamName,
                CyClockParamInfo.PhaseAlignClockNameParamName);

            ICyAdvClockControl_v1 advControl = design.CreateClockCustomizerAdvControl(this, edit);
            CyClockParamEditingControl advClkControl = new CyClockParamEditingControl(
                edit,
                advControl.DisplayControl,
                CyClockParamInfo.SyncWithBusClkParamName,
                CyClockParamInfo.UseDigitalDomainOutputParamName);

            CyParamExprDelegate configureExpressionViewDataChanged =
                delegate(ICyParamEditor custEditor, CyCompDevParam param)
                {
                    UpdateConfigureClkControl(edit, control, param);
                };

            CyParamExprDelegate advExpressionViewDataChanged =
                delegate(ICyParamEditor custEditor, CyCompDevParam param)
                {
                    UpdateAdvClkControl(edit, advControl, param);
                };

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();

            CyParamExprDelegate updateAdvancedTabVisibility =
                delegate(ICyParamEditor custEditor, CyCompDevParam param)
                {
                    if (param.Name == CyClockParamInfo.IsDirectParamName ||
                        param.Name == CyClockParamInfo.IsDividerParamName ||
                        param.Name == CyClockParamInfo.IsDesiredFreqParamName)
                    {
                        bool isDirectConnect = CyClockParamInfo.GetDirectConnect(edit);
                        if (isDirectConnect)
                        {
                            editor.HideCustomPage("Advanced");
                        }
                        else
                        {
                            editor.ShowCustomPage("Advanced");
                        }
                    }
                };

            editor.ParamExprCommittedDelegate = updateAdvancedTabVisibility;
            editor.AddCustomPage("Basic", clkControl, configureExpressionViewDataChanged, "Configure Clock");
            if (edit.DeviceQuery.DeviceFamilyAvailable && !edit.DeviceQuery.IsPSoC4)
            {
                editor.AddCustomPage("Advanced", advClkControl, advExpressionViewDataChanged, "Advanced");
            }
            editor.AddDefaultPage("Built-in", "Built-in");

            //initialize
            if (info.DirectConnect) editor.HideCustomPage("Advanced");

            DialogResult result = editor.ShowDialog();

            return result;
        }

        void UpdateAdvClkControl(ICyInstQuery_v1 query, ICyAdvClockControl_v1 ctrl, CyCompDevParam param)
        {
            CyClockParamInfo info = new CyClockParamInfo(query);
            CyCompDevParam tempParam;

            switch (param.Name)
            {
                case CyClockParamInfo.SyncWithBusClkParamName:
                    tempParam = query.GetCommittedParam(CyClockParamInfo.SyncWithBusClkParamName);
                    if (tempParam.ErrorCount == 0)
                    {
                        bool val = tempParam.GetValueAs<bool>();
                        ctrl.UpdateSync(val);
                    }
                    break;

                case CyClockParamInfo.UseDigitalDomainOutputParamName:
                    tempParam = query.GetCommittedParam(CyClockParamInfo.UseDigitalDomainOutputParamName);
                    if (tempParam.ErrorCount == 0)
                    {
                        bool val = tempParam.GetValueAs<bool>();
                        ctrl.UpdateUseAnalogDigitalOutput(val);
                    }
                    break;

                default:
                    Debug.Fail("unhandled param change");
                    break;
            }
        }

        /// <summary>
        /// Updated custom clock age when data is changed on the expression view of the page.
        /// </summary>
        /// <param name="query"></param>
        /// <param name="ctrl"></param>
        /// <param name="param"></param>
        void UpdateConfigureClkControl(ICyInstQuery_v1 query, ICyClockControl_v2 ctrl, CyCompDevParam param)
        {
            CyClockParamInfo info = new CyClockParamInfo(query);
            CyCompDevParam tempParam;

            switch (param.Name)
            {
                case CyClockParamInfo.DesiredFreqParamName:
                case CyClockParamInfo.DesiredFreqUnitParamName:
                    tempParam = query.GetCommittedParam(CyClockParamInfo.DesiredFreqUnitParamName);
                    if (tempParam.ErrorCount == 0)
                    {
                        byte freqUnit = tempParam.GetValueAs<byte>();

                        tempParam = query.GetCommittedParam(CyClockParamInfo.DesiredFreqParamName);
                        if (tempParam.ErrorCount == 0)
                        {
                            double freq = tempParam.GetValueAs<double>();
                            ctrl.UpdateDisplayedFrequency(freq, freqUnit);
                        }
                    }
                    break;

                case CyClockParamInfo.DivisorParamName:
                    tempParam = query.GetCommittedParam(CyClockParamInfo.DivisorParamName);
                    if (tempParam.ErrorCount == 0)
                    {
                        ctrl.UpdateDisplayedDivider(tempParam.GetValueAs<uint>());
                    }
                    break;

                case CyClockParamInfo.IsDesiredFreqParamName:
                case CyClockParamInfo.IsDirectParamName:
                case CyClockParamInfo.IsDividerParamName:
                    ctrl.UpdateDisplayedClockType(info.UseDesiredFreq, info.UseDivider, info.DirectConnect);
                    break;

                case CyClockParamInfo.MinusToleranceParamName:
                case CyClockParamInfo.PlusToleranceParamName:
                case CyClockParamInfo.CheckToleranceParamName:
                    ctrl.UpdateDisplayedToleranceInfo(info.PlusTolerancePercent, info.MinusTolerancePercent, info.CheckTolerance);
                    break;

                case CyClockParamInfo.SourceClockIdParamName:
                case CyClockParamInfo.SourceClockNameParamName:
                    CyCompDevParam inputIdParam = query.GetCommittedParam(CyClockParamInfo.SourceClockIdParamName);
                    CyCompDevParam inputNameParam = query.GetCommittedParam(CyClockParamInfo.SourceClockNameParamName);

                    ctrl.UpdateDisplayedSourceClockInfo(inputIdParam.Value, inputNameParam.Value);
                    break;
                case CyClockParamInfo.PhaseAlignClockIdParamName:
                case CyClockParamInfo.PhaseAlignClockNameParamName:
                    CyCompDevParam phAlignIdParam = query.GetCommittedParam(CyClockParamInfo.SourceClockIdParamName);
                    CyCompDevParam phAlignNameParam = query.GetCommittedParam(CyClockParamInfo.SourceClockNameParamName);
                    ctrl.UpdateDisplayedPhaseAlignClockInfo(phAlignIdParam.Value, phAlignNameParam.Value);
                    break;

                default:
                    Debug.Fail("unhandled param change");
                    break;
            }
        }

        CyCustErr SetAndValidateParam(ICyInstEdit_v1 edit, string paramName, string value)
        {
            edit.SetParamExpr(paramName, value);
            if (edit.CommitParamExprs())
                return CyCustErr.OK;
            CyCompDevParam param = edit.GetCommittedParam(paramName);

            if (param.ErrorCount > 0)
            {
                return new CyCustErr(param.ErrorMsgs);
            }
            return CyCustErr.OK;
        }

        public bool EditParamsOnDrop
        {
            get { return false; }
        }

        #endregion

        #region ICyClockControlData_v1<ICyInstEdit_v1> Members

        bool ICyClockControlData_v1<ICyInstEdit_v1>.GetIsNewFreqClock(ICyInstEdit_v1 edit)
        {
            CyClockParamInfo info = new CyClockParamInfo(edit);
            return info.UseDesiredFreq;
        }

        bool ICyClockControlData_v1<ICyInstEdit_v1>.GetIsNewDividerClock(ICyInstEdit_v1 edit)
        {
            CyClockParamInfo info = new CyClockParamInfo(edit);
            return info.UseDivider;
        }

        bool ICyClockControlData_v1<ICyInstEdit_v1>.GetIsExistingClock(ICyInstEdit_v1 edit)
        {
            CyClockParamInfo info = new CyClockParamInfo(edit);
            return info.DirectConnect;
        }

        double ICyClockControlData_v1<ICyInstEdit_v1>.GetPlusTolerance(ICyInstEdit_v1 edit)
        {
            CyClockParamInfo info = new CyClockParamInfo(edit);
            return info.PlusTolerancePercent;
        }

        double ICyClockControlData_v1<ICyInstEdit_v1>.GetMinusTolerance(ICyInstEdit_v1 edit)
        {
            CyClockParamInfo info = new CyClockParamInfo(edit);
            return info.MinusTolerancePercent;
        }

        bool ICyClockControlData_v1<ICyInstEdit_v1>.GetCheckTolerance(ICyInstEdit_v1 edit)
        {
            CyClockParamInfo info = new CyClockParamInfo(edit);
            return info.CheckTolerance;
        }

        double ICyClockControlData_v1<ICyInstEdit_v1>.GetFrequencyValue(ICyInstEdit_v1 edit)
        {
            CyClockParamInfo info = new CyClockParamInfo(edit);
            return info.DesiredFreq;
        }

        byte ICyClockControlData_v1<ICyInstEdit_v1>.GetFrequencyUnit(ICyInstEdit_v1 edit)
        {
            CyClockParamInfo info = new CyClockParamInfo(edit);
            return info.DesiredFreqUnit;
        }

        uint ICyClockControlData_v1<ICyInstEdit_v1>.GetDivider(ICyInstEdit_v1 edit)
        {
            CyClockParamInfo info = new CyClockParamInfo(edit);
            return info.Divider;
        }

        string ICyClockControlData_v1<ICyInstEdit_v1>.GetSrcClkID(ICyInstEdit_v1 edit)
        {
            CyClockParamInfo info = new CyClockParamInfo(edit);
            return info.InputClkId;
        }

        string ICyClockControlData_v1<ICyInstEdit_v1>.GetSrcClkName(ICyInstEdit_v1 edit)
        {
            CyClockParamInfo info = new CyClockParamInfo(edit);
            return info.InputClkName;
        }

        bool ICyClockControlData_v1<ICyInstEdit_v1>.GetFractDividerUsed(ICyInstEdit_v1 edit)
        {
            CyClockParamInfo info = new CyClockParamInfo(edit);
            return info.FractDividerUsed;
        }

        uint ICyClockControlData_v1<ICyInstEdit_v1>.GetFractDividerNumerator(ICyInstEdit_v1 edit)
        {
            CyClockParamInfo info = new CyClockParamInfo(edit);
            return info.FractDividerNumerator;
        }

        uint ICyClockControlData_v1<ICyInstEdit_v1>.GetFractDividerDenominator(ICyInstEdit_v1 edit)
        {
            CyClockParamInfo info = new CyClockParamInfo(edit);
            return info.FractDividerDenominator;
        }


        CyCustErr ICyClockControlData_v1<ICyInstEdit_v1>.IsFreqValid(
            ICyInstEdit_v1 edit, 
            string value)
        {
            //the string coming in is the expression for the freq
            return SetAndValidateParam(edit, CyClockParamInfo.DesiredFreqParamName, value);
        }

        CyCustErr ICyClockControlData_v1<ICyInstEdit_v1>.IsFreqUnitValid(
            ICyInstEdit_v1 edit, 
            string value)
        {
            return SetAndValidateParam(edit, CyClockParamInfo.DesiredFreqUnitParamName, value);
        }

        CyCustErr ICyClockControlData_v1<ICyInstEdit_v1>.IsDividerValid(
            ICyInstEdit_v1 edit, 
            string value)
        {
            //the string coming in is the expression for the divider
            return SetAndValidateParam(edit, CyClockParamInfo.DivisorParamName, value);
        }

        CyCustErr ICyClockControlData_v1<ICyInstEdit_v1>.IsSourceClkIdValid(
            ICyInstEdit_v1 edit, 
            string value)
        {
            return SetAndValidateParam(edit, CyClockParamInfo.SourceClockIdParamName, value);
        }

        CyCustErr ICyClockControlData_v1<ICyInstEdit_v1>.IsPlusToleranceValid(
            ICyInstEdit_v1 edit, 
            string value)
        {
            return SetAndValidateParam(edit, CyClockParamInfo.PlusToleranceParamName, value);
        }

        CyCustErr ICyClockControlData_v1<ICyInstEdit_v1>.IsMinusToleranceValid(
            ICyInstEdit_v1 edit, 
            string value)
        {
            return SetAndValidateParam(edit, CyClockParamInfo.MinusToleranceParamName, value);
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnFreqChanged(
            ICyInstEdit_v1 edit, 
            double frequencyValue, 
            byte frequencyUnit)
        {
            if (edit != null)
            {
                edit.SetParamExpr(CyClockParamInfo.DesiredFreqParamName, frequencyValue.ToString());
                edit.SetParamExpr(CyClockParamInfo.DesiredFreqUnitParamName, frequencyUnit.ToString());
                bool succeeded = edit.CommitParamExprs();
                Debug.Assert(succeeded);
            }
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnDividerChanged(
            ICyInstEdit_v1 edit, 
            uint divider)
        {
            if (edit != null)
            {
                edit.SetParamExpr(CyClockParamInfo.DivisorParamName, divider.ToString());
                bool succeeded = edit.CommitParamExprs();
                Debug.Assert(succeeded);
            }
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnSourceClkChanged(
            ICyInstEdit_v1 edit,
            string srcClkID,
            string srcClkName)
        {
            if (edit != null)
            {
                edit.SetParamExpr(CyClockParamInfo.SourceClockIdParamName, srcClkID);
                edit.SetParamExpr(CyClockParamInfo.SourceClockNameParamName, srcClkName);
                bool succeeded = edit.CommitParamExprs();
                Debug.Assert(succeeded);
            }
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnUseFreqChanged(ICyInstEdit_v1 edit, bool isNewFreqClock)
        {
            if (edit != null)
            {
                edit.SetParamExpr(CyClockParamInfo.IsDesiredFreqParamName,
                    (isNewFreqClock) ? "true" : "false");
                bool succeeded = edit.CommitParamExprs();
                Debug.Assert(succeeded);
            }
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnIsNewChanged(ICyInstEdit_v1 edit, bool isExistingClock)
        {
            if (edit != null)
            {
                edit.SetParamExpr(CyClockParamInfo.IsDirectParamName,
                    (isExistingClock) ? "true" : "false");
                bool succeeded = edit.CommitParamExprs();
                Debug.Assert(succeeded);
            }
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnUseDividerChanged(ICyInstEdit_v1 edit, bool isNewDividerClock)
        {
            if (edit != null)
            {
                edit.SetParamExpr(CyClockParamInfo.IsDividerParamName,
                    (isNewDividerClock) ? "true" : "false");
                bool succeeded = edit.CommitParamExprs();
                Debug.Assert(succeeded);
            }
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnPlusToleranceChanged(ICyInstEdit_v1 edit, double plusTolerance)
        {
            if (edit != null)
            {
                edit.SetParamExpr(CyClockParamInfo.PlusToleranceParamName, plusTolerance.ToString());
                bool succeeded = edit.CommitParamExprs();
                Debug.Assert(succeeded);
            }
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnMinusToleranceChanged(ICyInstEdit_v1 edit, double minusTolerance)
        {
            if (edit != null)
            {
                edit.SetParamExpr(CyClockParamInfo.MinusToleranceParamName, minusTolerance.ToString());
                bool succeeded = edit.CommitParamExprs();
                Debug.Assert(succeeded);
            }
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnCheckToleranceChanged(ICyInstEdit_v1 edit, bool checkTolerance)
        {
            if (edit != null)
            {
                edit.SetParamExpr(CyClockParamInfo.CheckToleranceParamName, (checkTolerance) ? "true" : "false");
                bool succeeded = edit.CommitParamExprs();
                Debug.Assert(succeeded);
            }
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnFractDividerUsedChanged(ICyInstEdit_v1 edit, bool used, uint denominator)
        {
            if (edit != null)
            {
                edit.SetParamExpr(CyClockParamInfo.FractDividerUsedParamName, (used) ? "true" : "false");
                edit.SetParamExpr(CyClockParamInfo.FractDividerDenominatorParamName, (used) ? denominator.ToString() : "0");
                bool succeeded = edit.CommitParamExprs();
                Debug.Assert(succeeded);
            }
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnFractDividerNumeratorChanged(ICyInstEdit_v1 edit, uint numerator, uint denominator)
        {
            if (edit != null)
            {
                edit.SetParamExpr(CyClockParamInfo.FractDividerNumeratorParamName, numerator.ToString());
                edit.SetParamExpr(CyClockParamInfo.FractDividerDenominatorParamName, denominator.ToString());
                bool succeeded = edit.CommitParamExprs();
                Debug.Assert(succeeded);
            }
        }

        #endregion

        #region ICyAdvClockControlData_v1<ICyInstEdit_v1> Members

        bool ICyAdvClockControlData_v1<ICyInstEdit_v1>.GetSync(ICyInstEdit_v1 edit)
        {
            CyClockParamInfo info = new CyClockParamInfo(edit);
            return info.SyncWithMasterClk;
        }

        bool ICyAdvClockControlData_v1<ICyInstEdit_v1>.GetUseAnalogDigitalOutput(ICyInstEdit_v1 edit)
        {
            CyClockParamInfo info = new CyClockParamInfo(edit);
            return info.UseDigitalDomainOutput;
        }

        void ICyAdvClockControlData_v1<ICyInstEdit_v1>.OnSyncChanged(ICyInstEdit_v1 edit, bool value)
        {
            if (edit != null)
            {
                edit.SetParamExpr(CyClockParamInfo.SyncWithBusClkParamName,
                    (value) ? "true" : "false");
                bool succeeded = edit.CommitParamExprs();
                Debug.Assert(succeeded);
            }
        }

        void ICyAdvClockControlData_v1<ICyInstEdit_v1>.OnUseAnalogDigitalOutputChanged(ICyInstEdit_v1 edit, bool value)
        {
            if (edit != null)
            {
                edit.SetParamExpr(CyClockParamInfo.UseDigitalDomainOutputParamName,
                    (value) ? "true" : "false");
                bool succeeded = edit.CommitParamExprs();
                Debug.Assert(succeeded);
            }
        }

        #endregion

        #region ICyClockControlData_v2<ICyInstEdit_v1> Members

        void ICyClockControlData_v2<ICyInstEdit_v1>.OnPhaseAlignClkChanged(
            ICyInstEdit_v1 edit, 
            string phaseAlignClkID, 
            string phaseAlignClkName)
        {
            if (edit != null)
            {
                edit.SetParamExpr(CyClockParamInfo.PhaseAlignClockIdParamName, phaseAlignClkID);
                edit.SetParamExpr(CyClockParamInfo.PhaseAlignClockNameParamName, phaseAlignClkName);
                bool succeeded = edit.CommitParamExprs();
                Debug.Assert(succeeded);
            }
        }

        CyCustErr ICyClockControlData_v2<ICyInstEdit_v1>.IsPhaseAlignClkIdValid(ICyInstEdit_v1 edit, string value)
        {
            return SetAndValidateParam(edit, CyClockParamInfo.PhaseAlignClockIdParamName, value);
        }

        string ICyClockControlData_v2<ICyInstEdit_v1>.GetPhaseAlignClkID(ICyInstEdit_v1 edit)
        {
            CyClockParamInfo info = new CyClockParamInfo(edit);
            return info.PhaseAlignClkId;
        }

        string ICyClockControlData_v2<ICyInstEdit_v1>.GetPhaseAlignClkName(ICyInstEdit_v1 edit)
        {
            CyClockParamInfo info = new CyClockParamInfo(edit);
            return info.PhaseAlignClkName;
        }

        #endregion

        #region ICyToolTipCustomize_v1 Members

        /// <summary>
        /// Adds the input clock name, and the desired frequency or the divider 
        /// (which ever one is used) to the default tooltip text.
        /// </summary>
        /// <param name="query"></param>
        /// <returns></returns>
        public string CustomizeToolTip(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            string newToolTip = query.DefaultToolTipText;
            CyClockParamInfo info = new CyClockParamInfo(query);

            // Show tolerance for Frequency clock
            if (info.UseDesiredFreq)
            {
                newToolTip += CyBasic.CompareDoubles(info.PlusTolerancePercent, info.MinusTolerancePercent) == 0
                                  ? string.Format("Tolerance: +/- {0}%\n", info.PlusTolerancePercent)
                                  : string.Format("Tolerance: -{0}%/+{1}%\n", info.MinusTolerancePercent,
                                                  info.PlusTolerancePercent);
            }

            //Show Input Clock
            string inputClkName = (string.IsNullOrEmpty(info.InputClkId)) ? "<Auto>" : info.InputClkName;
            newToolTip += string.Format("{0}: {1}\n", "Input Clock", inputClkName);

            //Show Desired Frequency
            if (info.UseDesiredFreq)
            {
                newToolTip += string.Format("{0}: {1}\n", "Desired Frequency", info.PrettyFreq);
            }

            //Show Divider
            if (info.UseDivider)
            {
                string divider = info.Divider.ToString();
                if (info.FractDividerUsed)
                {
                    divider += " " + info.FractDividerNumerator + "/" + info.FractDividerDenominator;
                }

                newToolTip += string.Format("{0}: {1}\n", "Divider", divider);
            }

            //Show that the clock is a direct connect
            if (info.DirectConnect)
            {
                newToolTip += string.Format("{0}\n", "Existing Clock");
            }

            //Show Sync with Master
            if (query.DesignQuery.DesignInfoAvailable)
            {
                CyTriStateBoolean sync = CyTriStateBoolean.Unknown;
                bool isValid = true;
                foreach (string id in termQuery.GetClockIds("clock_out", 0))
                {
                    if (!query.DesignQuery.IsValidClockID(id))
                    {
                        isValid = false;
                        break;
                    }
                }
                if (isValid)
                    sync = query.DesignQuery.GetClockSyncWithMasterClk();

                switch (sync)
                {
                    case CyTriStateBoolean.True:
                    case CyTriStateBoolean.False:
                        String masterClkName = query.DeviceQuery.IsPSoC4 ? "HFCLK" : "MASTER_CLK";
                        newToolTip += string.Format("Sync with {0}: {1}\n", masterClkName, sync);
                        break;

                    case CyTriStateBoolean.Unknown:
                        break;

                    default:
                        Debug.Fail("unhandled");
                        break;
                }
            }

            return newToolTip;
        }

        #endregion

        #region Inner Class

        public class CyClockParamEditingControl : ICyParamEditingControl
        {
            ICyInstEdit_v1 m_editObj;
            readonly Control m_displayControl;
            readonly string[] m_paramNames;

            public CyClockParamEditingControl(
                ICyInstEdit_v1 editObj, 
                Control displayControl, 
                params string[] paramNames)
            {
                m_editObj = editObj;
                m_displayControl = displayControl;
                m_paramNames = paramNames;
            }

            #region ICyParamEditingControl Members

            public Control DisplayControl
            {
                get { return m_displayControl; }
            }

            public IEnumerable<CyCustErr> GetErrors()
            {
                List<CyCustErr> errs = new List<CyCustErr>();

                foreach (string paramName in m_paramNames)
                {
                    CyCompDevParam param = m_editObj.GetCommittedParam(paramName);
                    if (param.ErrorCount > 0)
                    {
                        foreach (string errMsg in param.Errors)
                        {
                            errs.Add(new CyCustErr(errMsg));
                        }
                    }
                }

                return errs;
            }

            #endregion
        }

        class CyClockParamInfo
        {
            //------------------------------------

            #region Param Names

            public const string SyncWithBusClkParamName = "SyncWithBusClk";
            public const string InstanceNameParamName = "INSTANCE_NAME";
            public const string ShortInstanceNameParamName = "CY_INSTANCE_SHORT_NAME";
            public const string IsDesiredFreqParamName = "is_freq";
            public const string DesiredFreqParamName = "desired_freq";
            public const string DesiredFreqUnitParamName = "desired_freq_unit";
            public const string IsDividerParamName = "is_divider";
            public const string DivisorParamName = "divisor";

            public const string SourceClockIdParamName = "source_clock_id";
            public const string SourceClockNameParamName = "source_clock_name";

            public const string PhaseAlignClockIdParamName = "ph_align_clock_id";
            public const string PhaseAlignClockNameParamName = "ph_align_clock_name";

            public const string IsDirectParamName = "is_direct";
            public const string MinusToleranceParamName = "minus_tolerance";
            public const string PlusToleranceParamName = "plus_tolerance";
            public const string CheckToleranceParamName = "CheckTolerance";
            public const string UseDigitalDomainOutputParamName = "EnableDigitalDomainOutput";

            public const string FractDividerUsedParamName = "FractDividerUsed";
            public const string FractDividerNumeratorParamName = "FractDividerNumerator";
            public const string FractDividerDenominatorParamName = "FractDividerDenominator";

            #endregion

            //------------------------------------

            #region Member Variables

            bool m_useDesiredFreq;
            double m_desiredFreq;
            byte m_desiredFreqUnit;
            bool m_useDivider;
            string m_dividerExpr;
            uint m_divider;
            
            string m_inputClkId;
            string m_inputClkName;

            string m_phaseAlignClkId;
            string m_phaseAlignClkName;

            string m_desiredFreqExpr;
            bool m_directConnect;
            double m_minusTolerancePercent;
            double m_plusTolerancePercent;
            bool m_checkTolerance;
            string m_instanceName;
            bool m_syncWithBusClk;
            bool m_useDigitalDomainOutput;

            bool m_fractDividerUsed;
            uint m_fractDividerNumerator;
            uint m_fractDividerDenominator;

            #endregion

            //------------------------------------

            #region Properties

            public bool UseDigitalDomainOutput
            {
                get { return m_useDigitalDomainOutput; }
            }

            public bool SyncWithMasterClk
            {
                get { return m_syncWithBusClk; }
            }

            public string ShortInstanceName
            {
                get { return m_instanceName; }
                private set { m_instanceName = value; }
            }

            public bool CheckTolerance
            {
                get { return m_checkTolerance; }
            }

            public double MinusTolerancePercent
            {
                get { return m_minusTolerancePercent; }
            }

            public double PlusTolerancePercent
            {
                get { return m_plusTolerancePercent; }
            }

            public bool DirectConnect
            {
                get { return m_directConnect; }
            }

            public bool UseDesiredFreq
            {
                get { return m_useDesiredFreq; }
            }

            public double DesiredFreq
            {
                get { return m_desiredFreq; }
            }

            public string DesiredFreqExpr
            {
                get { return m_desiredFreqExpr; }
            }

            public byte DesiredFreqUnit
            {
                get { return m_desiredFreqUnit; }
            }

            public bool UseDivider
            {
                get { return m_useDivider; }
            }

            public string DividerExpr
            {
                get { return m_dividerExpr; }
            }

            public uint Divider
            {
                get { return m_divider; }
            }

            public string InputClkId
            {
                get { return m_inputClkId; }
            }

            public string InputClkName
            {
                get { return m_inputClkName; }
            }

            public string PhaseAlignClkId
            {
                get { return m_phaseAlignClkId; }
            }

            public string PhaseAlignClkName
            {
                get { return m_phaseAlignClkName; }
            }

            public string PrettyFreq
            {
                get
                {
                    CyFrequency freq = new CyFrequency(DesiredFreq, DesiredFreqUnit);
                    return freq.ToString();
                }
            }

            public bool FractDividerUsed
            {
                get { return m_fractDividerUsed; }
            }

            public uint FractDividerNumerator
            {
                get { return m_fractDividerNumerator; }
            }

            public uint FractDividerDenominator
            {
                get { return m_fractDividerDenominator; }
            }

            #endregion

            //------------------------------------

            #region Constructors

            public CyClockParamInfo(ICyInstQuery_v1 query)
            {
                CyCompDevParam instNameParam = query.GetCommittedParam(ShortInstanceNameParamName);
                Debug.Assert(instNameParam.ErrorCount == 0);
                ShortInstanceName = instNameParam.Value;

                m_useDesiredFreq = GetValue<bool>(query, IsDesiredFreqParamName, bool.TryParse);
                m_checkTolerance = GetValue<bool>(query, CheckToleranceParamName, bool.TryParse);
                m_syncWithBusClk = GetValue<bool>(query, SyncWithBusClkParamName, bool.TryParse);
                m_desiredFreq = GetValue<double>(query, DesiredFreqParamName, double.TryParse, out m_desiredFreqExpr);
                m_desiredFreqUnit = GetValue<byte>(query, DesiredFreqUnitParamName, byte.TryParse);
                m_useDivider = GetValue<bool>(query, IsDividerParamName, bool.TryParse);
                m_divider = GetValue<uint>(query, DivisorParamName, uint.TryParse, out m_dividerExpr);

                CyCompDevParam inputClkIdParam = query.GetCommittedParam(SourceClockIdParamName);
                if (inputClkIdParam.ErrorCount == 0)
                    m_inputClkId = inputClkIdParam.Value;

                CyCompDevParam inputClkNameParam = query.GetCommittedParam(SourceClockNameParamName);
                m_inputClkName = inputClkNameParam.Value;

                CyCompDevParam phaseAlignClkIdParam = query.GetCommittedParam(PhaseAlignClockIdParamName);
                if (phaseAlignClkIdParam.ErrorCount == 0)
                    m_phaseAlignClkId = phaseAlignClkIdParam.Value;

                CyCompDevParam phaseAlignClkNameParam = query.GetCommittedParam(PhaseAlignClockNameParamName);
                m_phaseAlignClkName = phaseAlignClkNameParam.Value;

                m_fractDividerUsed = GetValue<bool>(query, FractDividerUsedParamName, bool.TryParse);
                m_fractDividerNumerator = GetValue<uint>(query, FractDividerNumeratorParamName, uint.TryParse);
                m_fractDividerDenominator = GetValue<uint>(query, FractDividerDenominatorParamName, uint.TryParse);

                m_directConnect = GetDirectConnect(query);
                m_useDigitalDomainOutput = GetUseDigitalDomainOutput(query);

                m_plusTolerancePercent = GetValue<double>(query, PlusToleranceParamName, double.TryParse);
                m_minusTolerancePercent = GetValue<double>(query, MinusToleranceParamName, double.TryParse);

#if DEBUG
                if (UseDesiredFreq)
                {
                    Debug.Assert(!UseDivider && !DirectConnect, "only one should be set at a time");
                }
                else if (UseDivider)
                {
                    Debug.Assert(!UseDesiredFreq && !DirectConnect, "only one should be set at a time");
                }
                else if (DirectConnect)
                {
                    Debug.Assert(!UseDesiredFreq && !UseDivider, "only one should be set at a time");
                }
                else
                {
                    Debug.Fail("one of these should be true");
                }
#endif
            }

            #endregion

            delegate bool CyTryParse<T>(string text, out T value);

            static T GetValue<T>(ICyInstQuery_v1 query, string paramName, CyTryParse<T> parser)
            {
                string ignored;
                return GetValue<T>(query, paramName, parser, out ignored);
            }

            static T GetValue<T>(ICyInstQuery_v1 query, string paramName, CyTryParse<T> parser, out string expr)
            {
                CyCompDevParam param = query.GetCommittedParam(paramName);
                expr = param.Expr;
                if (param.ErrorCount == 0)
                {
                    return param.GetValueAs<T>();
                }
                else
                {
                    T value;
                    if (parser(param.Value, out value))
                    {
                        return value;
                    }
                    else
                    {
                        return default(T);
                    }
                }
            }

            public static bool GetDirectConnect(ICyInstQuery_v1 query)
            {
                return GetValue<bool>(query, IsDirectParamName, bool.TryParse);
            }

            public static bool GetUseDigitalDomainOutput(ICyInstQuery_v1 query)
            {
                return GetValue<bool>(query, UseDigitalDomainOutputParamName, bool.TryParse);
            }

            //------------------------------------
        }

        #endregion

        #region ICyVerilogCustomize_v1 Members

        CyCustErr ICyVerilogCustomize_v1.CustomizeVerilog(
            ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery, out string codeSnippet)
        {
            ICyDesignQuery_v1 design = query.DesignQuery;
            Debug.Assert(design.DesignInfoAvailable);

            string sigName, digDomainOutSigName;
            CyClockParamInfo info;

            try
            {
                sigName = termQuery.GetTermSigSegName("clock_out");
                digDomainOutSigName = termQuery.GetTermSigSegName("dig_domain_out");
                info = new CyClockParamInfo(query);
            }
            catch (Exception e)
            {
                codeSnippet = string.Empty;
                return new CyCustErr(e, "Error in clock customizer (malformed parameter): ", e.Message);
            }

            double period = CyFrequency.FreqToPeriod(info.DesiredFreq, info.DesiredFreqUnit);
            string isDigitalString = (design.IsClockDigital(query.InstanceIdPath)) ? "1" : "0";
            string sourceIdString = (string.IsNullOrEmpty(info.InputClkId)) ? "\"\"" : "\"" + info.InputClkId + "\"";
            string dividerString = (info.UseDivider) ? info.Divider.ToString() : "0";
            string periodString = (info.UseDivider || info.DirectConnect) ? "\"0\"" : "\"" + period.ToString() + "\"";
            string directConnectString = (info.DirectConnect) ? "1" : "0";

            CyVerilogWriter vw = new CyVerilogWriter(RtlName, query.InstanceName);
            vw.AddPort("clock_out", sigName);
            if (info.UseDigitalDomainOutput)
            {
                vw.AddPort("dig_domain_out", digDomainOutSigName);
            }
            vw.AddGeneric("id", "\"" + query.InstanceIdPath + "\"");
            vw.AddGeneric(CyClockParamInfo.SourceClockIdParamName, sourceIdString);
            vw.AddGeneric(CyClockParamInfo.DivisorParamName, dividerString);
            vw.AddGeneric("period", periodString);
            vw.AddGeneric(CyClockParamInfo.IsDirectParamName, directConnectString);
            vw.AddGeneric("is_digital", isDigitalString);
            codeSnippet = vw.ToString();

            return CyCustErr.Ok;
        }

        #endregion

        #region ICyClockDataProvider_v1 Members

        public CyClockData GetClockInfo(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery, string termName, int ix)
        {
            if (termQuery.DoesTermExist(termName) == false)
                return CyClockData.GetUnknownClock();

            if (termQuery.GetTermMinIdx(termName) < ix || ix > termQuery.GetTermMaxIdx(termName))
                return CyClockData.GetUnknownClock();

            ICyDesignQuery_v1 design = query.DesignQuery;
            if (design.DesignInfoAvailable == false)
                return CyClockData.GetUnknownClock();

            double freq;
            byte exp;

            bool exists = design.GetClockActualFreq(query.InstanceIdPath, out freq, out exp);
            if (!exists)
                return CyClockData.GetUnknownClock();

            return new CyClockData(freq, exp);
        }

        #endregion

        #region ICyAPICustomize_v1 Members

        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery,
            IEnumerable<CyAPICustomizer> apis)
        {
            //For design-wide clocks (which are always new clocks) query and termQuery will be null.
            //This is the ONLY case in which query and termQuery will be null.

            //Only generate an API for 'new' clocks. 'Existing' clocks do not get an API.

            if (query == null)
            {
                //Design-wide new clock, return the APIs unaltered.
                return apis;
            }

            CyClockParamInfo info = new CyClockParamInfo(query);
            if (info.DirectConnect)
            {
                //Existing clock, supress API generation.
                return new CyAPICustomizer[] { };
            }

            //The clock is a 'new' clock, return the APIs unaltered.
            return apis;
        }

        #endregion

        #region ICyShapeCustomize_v1 Members

        const string TitleShapeTag = "Title";
        const string BodyShapeTag = "Body";
        const string FreqShapeTag = "Freq";
        const string WaveformShapeTage = "waveform";
        const string ADigLineTag = "ADigLine";

        public CyCustErr CustomizeShapes(ICyInstQuery_v1 query, ICySymbolShapeEdit_v1 shapeEdit,
            ICyTerminalEdit_v1 termEdit)
        {
            CyCustErr err = CyCustErr.OK;

            //Waveform Color----------------------------------------

            err = shapeEdit.SetOutlineWidth(WaveformShapeTage, 0);
            if (err.IsNotOk) return err;

            //These default colors represent no design info available, set to white to indicate the domain is unknown.
            Color waveFormFillColor = Color.White;
            Color waveFormOutlineColor = Color.White;

            if (query.DesignQuery.DesignInfoAvailable)
            {
                //Get all the Ids assocaited with this clock by using the clock's terminal.
                List<string> ids = termEdit.GetClockIds("clock_out", 0);

                bool containsDigital = false;
                bool containsAnalog = false;
                bool containsFF = false;

                foreach (string id in ids)
                {
                    Debug.Assert(query.DesignQuery.IsValidClockID(id),
                        "termEdit.GetClockIds is returning invalid data");

                    if (query.DesignQuery.IsValidClockID(id))
                    {
                        containsDigital |= query.DesignQuery.IsClockDigital(id);
                        containsAnalog |= query.DesignQuery.IsClockAnalog(id);
                        containsFF |= query.DesignQuery.IsClockFF(id);
                    }
                }

                //This clock can be used in multiple places due to heirarchy.
                //If all the domains for this clock are the same, it can be displayed; otherwise the domain is
                //unknown and the default colors should be used.
                if (containsDigital && !containsAnalog && !containsFF)
                {
                    waveFormFillColor = query.Preferences.DigitalWireColor;
                    waveFormOutlineColor = Color.Black;
                }
                else if (containsAnalog && !containsDigital && !containsFF)
                {
                    waveFormFillColor = query.Preferences.AnalogWireColor;
                    waveFormOutlineColor = Color.Black;
                }
                else if (containsFF && !containsDigital && !containsAnalog)
                {
                    waveFormFillColor = Color.Purple;
                    waveFormOutlineColor = Color.Black;
                }
            }

            err = shapeEdit.SetFillColor(WaveformShapeTage, waveFormFillColor);
            if (err.IsNotOk) return err;

            err = shapeEdit.SetOutlineColor(WaveformShapeTage, waveFormOutlineColor);
            if (err.IsNotOk) return err;

            err = shapeEdit.SetOutlineWidth(WaveformShapeTage, 0);
            if (err.IsNotOk) return err;

            //Instance Name-----------------------------------------

            string srcName = GetStringSrcClkName(query);

            RectangleF bounds = shapeEdit.GetShapeBounds(BodyShapeTag);
            StringFormat fmt = new StringFormat();
            fmt.Alignment = StringAlignment.Far;
            fmt.LineAlignment = StringAlignment.Center;

            err = shapeEdit.CreateAnnotation(new string[] { TitleShapeTag },
                string.Format("`=($is_direct) ? \"{0}\" : $INSTANCE_NAME`", srcName),
                new PointF(bounds.Left, bounds.Top + (bounds.Height / 2.0f)),
                new Font(FontFamily.GenericSansSerif, 10, FontStyle.Regular),
                fmt);
            if (err.IsNotOk) return err;

            err = shapeEdit.SetFillColor(TitleShapeTag, Color.Black);
            if (err.IsNotOk) return err;

            err = shapeEdit.ClearOutline(TitleShapeTag);
            if (err.IsNotOk) return err;

            //Analog Digital Output Connecting Line
            bool useAClkDigOutput = CyClockParamInfo.GetUseDigitalDomainOutput(query);

            if (useAClkDigOutput)
            {
                err = shapeEdit.CreatePolyline(new string[] { ADigLineTag },
                    new PointF(-shapeEdit.UserBaseUnit, -shapeEdit.UserBaseUnit * 2),
                    new PointF(bounds.Right - bounds.Width / 2.0f, -shapeEdit.UserBaseUnit * 2),
                    new PointF(bounds.Right - bounds.Width / 2.0f, bounds.Top));
                if (err.IsNotOk) return err;

                err = shapeEdit.SetOutlineWidth(ADigLineTag, query.Preferences.WireSize);
                if (err.IsNotOk) return err;

                err = shapeEdit.SetOutlineColor(ADigLineTag, query.Preferences.SymbolDigitalTerminalColor);
                if (err.IsNotOk) return err;

                err = shapeEdit.SendToBack(ADigLineTag);
                if (err.IsNotOk) return err;
            }

            // Frequency Tag
            StringFormat freqFmt = new StringFormat();
            freqFmt.Alignment = StringAlignment.Far;
            freqFmt.LineAlignment = StringAlignment.Near;

            string srcFreqPretty = GetSrcFreqPretty(query);
            err = shapeEdit.CreateAnnotation(new string[] {FreqShapeTag},
                                             string.Format(
                                                 "`=($is_divider) ? $source_clock_name  . \" / \" . $pretty_divisor : ($is_direct) ? \"{0}\" : $pretty_desired_freq`",
                                                 srcFreqPretty),
                                             new PointF(-6.0f, 6.0f),
                                             new Font(FontFamily.GenericSansSerif, 6, FontStyle.Regular), freqFmt);
            if (err.IsNotOk) return err;

            err = shapeEdit.SetFillColor(FreqShapeTag, Color.Black);
            if (err.IsNotOk) return err;

            err = shapeEdit.ClearOutline(FreqShapeTag);
            if (err.IsNotOk) return err;

            return err;
        }

        private static string GetSrcFreqPretty(ICyInstQuery_v1 query)
        {
            string srcFreqPretty = "";
            CyClockParamInfo info = new CyClockParamInfo(query);
            if (query.DesignQuery.DesignInfoAvailable && query.DesignQuery.IsValidClockID(info.InputClkId))
            {
                byte freqUnit;
                double srcFreq;
                if (!query.DesignQuery.GetClockActualFreq(info.InputClkId, out srcFreq, out freqUnit))
                {
                    srcFreqPretty = "? MHz";
                }
                else
                {
                    string prettyUnit;
                    if (!CyFrequency.TryConvertUnitToString(freqUnit, out prettyUnit))
                        Debug.Fail("Failed to convert unit to string");

                    srcFreqPretty = Math.Round(srcFreq, 3) + " " + prettyUnit;
                }
            }
            return srcFreqPretty;
        }

        private static string GetStringSrcClkName(ICyInstQuery_v1 query)
        {
            string srcName;
            CyClockParamInfo info = new CyClockParamInfo(query);
            if (query.DesignQuery.DesignInfoAvailable && query.DesignQuery.IsValidClockID(info.InputClkId))
            {
                //Get the most up-to-date name if available.
                srcName = query.DesignQuery.GetClockName(info.InputClkId);
            }
            else
            {
                srcName = "Unknown Source Clock";
            }
            return srcName;
        }

        #endregion

        #region ICyDesignClient_v1 Members

        //Update the Sync with Master clock value in tooltip (cdt 75161)
        public bool IsToolTipDesignSensitive
        {
            get { return true; }
        }

        //The color is updated to show the domain results once calculated (cdt 46691).
        //The text is updated in the case where direct connect to a global clock that has been renamed (cdt 50021).
        public bool IsShapeDesignSensitive
        {
            get { return true; }
        }

        #endregion

        #region ICyDesignClient_v2 Members

        [Flags]
        enum CyDomain
        {
            None = 0,
            Digital = 1,
            Analog = 2,
        }

        class CyDesignClientData
        {
            CyDomain m_domain;
            CyTriStateBoolean m_synched;
            String m_srcName;
            private String m_srcFreqString;

            public CyDomain Domain { get { return m_domain; } set { m_domain = value; } }
            public CyTriStateBoolean SynchedWithMaster { get { return m_synched; } set { m_synched = value; } }
            public String SrcName { get { return m_srcName; } set { m_srcName = value; } }
            public String SrcFreqString { get { return m_srcFreqString; } set { m_srcFreqString = value; } }

                public CyDesignClientData(CyDomain domain, CyTriStateBoolean synched, String srcName, String srcFreqString)
            {
                m_domain = domain;
                m_synched = synched;
                m_srcName = srcName;
                m_srcFreqString = srcFreqString;
            }

            public override string ToString()
            {
                return string.Format("{0}, {1}, {2}", Domain.ToString(), SynchedWithMaster.ToString(), SrcName);
            }

            public static CyDesignClientData FromString(string value)
            {
                try
                {
                    string[] parts = value.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries);
                    CyDomain domain = (CyDomain)Enum.Parse(typeof(CyDomain), parts[0].Trim());
                    CyTriStateBoolean sync = (CyTriStateBoolean)Enum.Parse(typeof(CyTriStateBoolean), parts[1].Trim());
                    String srcName = parts.Length >= 3 ? parts[2].Trim() : "";
                    String srcFreqString = parts.Length >= 4 ? parts[3].Trim() : "";
                    return new CyDesignClientData(domain, sync, srcName, srcFreqString);
                }
                catch (Exception)
                {
                    return null;
                }
            }
        }

        string ICyDesignClient_v2.GetDesignClientState(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            return GetDesignClientData(query, termQuery).ToString();
        }

        CyDesignClientData GetDesignClientData(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            CyDomain domain = GetDomain(query, termQuery);
            CyTriStateBoolean synched = CyTriStateBoolean.Unknown;
            String srcName = GetStringSrcClkName(query);
            String srcFreqString = GetSrcFreqPretty(query);
            if (query.DesignQuery.DesignInfoAvailable)
            {
                bool isValid = true;
                foreach (string id in termQuery.GetClockIds("clock_out", 0))
                {
                    if (!query.DesignQuery.IsValidClockID(id))
                    {
                        isValid = false;
                        break;
                    }
                }

                if (isValid)
                    synched = query.DesignQuery.GetClockSyncWithMasterClk();
            }

            CyDesignClientData data = new CyDesignClientData(domain, synched, srcName, srcFreqString);
            return data;
        }

        private static CyDomain GetDomain(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            if (query.DesignQuery.DesignInfoAvailable)
            {
                //Get all the Ids assocaited with this clock by using the clock's terminal.
                List<string> ids = termQuery.GetClockIds("clock_out", 0);

                bool containsDigital = false;
                bool containsAnalog = false;

                foreach (string id in ids)
                {
                    Debug.Assert(query.DesignQuery.IsValidClockID(id),
                        "termEdit.GetClockIds is returning invalid data");

                    if (query.DesignQuery.IsValidClockID(id))
                    {
                        bool isDigital = query.DesignQuery.IsClockDigital(id);
                        containsDigital |= isDigital;
                        containsAnalog |= (!isDigital);
                    }
                }
                if (containsDigital)
                {
                    if (containsAnalog)
                    {
                        return CyDomain.Analog | CyDomain.Digital;
                    }
                    return CyDomain.Digital;
                }
                if (containsAnalog)
                {
                    return CyDomain.Analog;
                }
            }

            return CyDomain.None;
        }

        bool ICyDesignClient_v2.RequiresTooltipUpdate(string designClientState, ICyInstQuery_v1 query, 
            ICyTerminalQuery_v1 termQuery)
        {
            CyDesignClientData oldData = CyDesignClientData.FromString(designClientState);
            CyDesignClientData newData = GetDesignClientData(query, termQuery);

            if (oldData == null) return true;
            return oldData.SynchedWithMaster != newData.SynchedWithMaster || oldData.SrcName != newData.SrcName;
        }

        bool ICyDesignClient_v2.RequiresShapeUpdate(string designClientState, ICyInstQuery_v1 query, 
            ICyTerminalQuery_v1 termQuery)
        {
            CyDesignClientData oldData = CyDesignClientData.FromString(designClientState);
            CyDesignClientData newData = GetDesignClientData(query, termQuery);

            if (oldData == null) return true;
            return oldData.Domain != newData.Domain || oldData.SrcName != newData.SrcName ||
                   oldData.SrcFreqString != newData.SrcFreqString;
        }

        #endregion
    }
}
