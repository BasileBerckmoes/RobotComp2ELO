/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Diagnostics;
using System.Windows.Forms;
using System.Collections.Generic;
using CyDesigner.Toolkit;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using SCB_I2C_PDL_v2_0.Controls;

namespace SCB_I2C_PDL_v2_0
{
    sealed public class CyCustomizer : ICyParamEditHook_v1, ICyDRCProvider_v1, ICyExprEval_v3,
        ICyAPICustomize_v1
    {
        #region ICyParamEditHook_v1 members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit, termQuery);

            // Create control with dynamicaly calculated labels
            CyDynamicDataControl dynamicDataControl = new CyDynamicDataControl(parameters);
            CyDefaultPageUserControl userControl = new CyDefaultPageUserControl(dynamicDataControl,
                false, SizeType.Absolute, 200);

            CyTabParamEditorDefaultPageExtender extender = new CyTabParamEditorDefaultPageExtender();
            extender.InnerRightBottomControl = userControl;

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            editor.UseBigEditor = true;

            editor.AddDefaultPage(Resources.BasicTabDisplayName, extender);
            editor.AddDefaultPage(Resources.PinsTabDisplayName, "Pins");
            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");

            edit.NotifyWhenDesignUpdates(parameters.OnDesignUpdated);

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

        #region ICyExprEval_v3 members
        const string GET_SCB_CLOCK_FUNC_NAME = "GetScbClock";
        const string GET_SCB_CLOCK_MINUS_TOLERANCE_FUNC_NAME = "GetScbClockMinusTolerance";
        const string GET_SCB_CLOCK_PLUS_TOLERANCE_FUNC_NAME = "GetScbClockPlusTolerance";

        const int GET_FUNC_ARG_LENGTH = 2;

        public CyExprEvalFuncEx GetFunction(string exprFuncName)
        {
            switch (exprFuncName)
            {
                case GET_SCB_CLOCK_FUNC_NAME:
                    return new CyExprEvalFuncEx(GetScbClock);
                case GET_SCB_CLOCK_MINUS_TOLERANCE_FUNC_NAME:
                    return new CyExprEvalFuncEx(GetScbClockMinusTolerance);
                case GET_SCB_CLOCK_PLUS_TOLERANCE_FUNC_NAME:
                    return new CyExprEvalFuncEx(GetScbClockPlusTolerance);
                default:
                    return null;
            }
        }

        private double GetMinClock(CyEModeType mode, ushort dataRate)
        {
            double clkScb = 0;

            switch (mode)
            {
                case CyEModeType.SLAVE:
                    clkScb = (double)((dataRate <= CyRanges.DATA_RATE_100)  ? (CyRanges.SLAVE_FSCB_MIN_100KBPS)  :
                                      (dataRate <= CyRanges.DATA_RATE_400)  ? (CyRanges.SLAVE_FSCB_MIN_400KBPS)  :
                                      (dataRate <= CyRanges.DATA_RATE_1000) ? (CyRanges.SLAVE_FSCB_MIN_1000KBPS) :
                                      (CyRanges.SLAVE_FSCB_MAX_100KBPS));
                    break;
                case CyEModeType.MASTER:
                case CyEModeType.MASTER_SLAVE:
                    clkScb = (double)((dataRate <= CyRanges.DATA_RATE_100)  ? (CyRanges.MASTER_FSCB_MIN_100KBPS)  :
                                      (dataRate <= CyRanges.DATA_RATE_400)  ? (CyRanges.MASTER_FSCB_MIN_400KBPS)  :
                                      (dataRate <= CyRanges.DATA_RATE_1000) ? (CyRanges.MASTER_FSCB_MIN_1000KBPS) :
                                      (CyRanges.MASTER_FSCB_MIN_100KBPS));
                    break;
                default:
                    Debug.Fail(String.Format(Resources.UnknownMode, mode));
                    break;
            }

            return clkScb;
        }

        private double GetMaxClock(CyEModeType mode, ushort dataRate)
        {
            double clkScb = 0;

            switch (mode)
            {
                case CyEModeType.SLAVE:
                    clkScb = (double)((dataRate <= CyRanges.DATA_RATE_100)  ? (CyRanges.SLAVE_FSCB_MAX_100KBPS) :
                                      (dataRate <= CyRanges.DATA_RATE_400)  ? (CyRanges.SLAVE_FSCB_MAX_400KBPS) :
                                      (dataRate <= CyRanges.DATA_RATE_1000) ? (CyRanges.SLAVE_FSCB_MAX_1000KBPS) :
                                      (CyRanges.SLAVE_FSCB_MAX_100KBPS));
                    break;
                case CyEModeType.MASTER:
                case CyEModeType.MASTER_SLAVE:
                    clkScb = (double)((dataRate <= CyRanges.DATA_RATE_100)  ? (CyRanges.MASTER_FSCB_MAX_100KBPS) :
                                      (dataRate <= CyRanges.DATA_RATE_400)  ? (CyRanges.MASTER_FSCB_MAX_400KBPS) :
                                      (dataRate <= CyRanges.DATA_RATE_1000) ? (CyRanges.MASTER_FSCB_MAX_1000KBPS) :
                                      (CyRanges.MASTER_FSCB_MAX_100KBPS));
                    break;
                default:
                    Debug.Fail(String.Format(Resources.UnknownMode, mode));
                    break;
            }

            return clkScb;
        }

        private double GetTolerance(CyEModeType mode, double clkMin, double clkMax)
        {
            double tolerance;

            if (mode == CyEModeType.SLAVE)
            {

                // Clock is defined as max - tolerance (takes into account IMO accuracy)
                tolerance = (double)CyRanges.CyTolerance.MINUS_MAX - ((clkMin / clkMax) * 100);
            }
            else
            {
                // Clock is defined as max + tolerance (Take into account max IMO accuracy)
                tolerance = (double)((clkMax / clkMin) * 100);
            }

            return tolerance;
        }

        object GetScbClock(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (args.Length == GET_FUNC_ARG_LENGTH)
            {
                try
                {
                    CyEModeType mode = (CyEModeType)typeConverter.GetAsByte(args[0]);
                    ushort dataRate = typeConverter.GetAsUShort(args[1]);

                    double clkScb = (mode == CyEModeType.SLAVE) ? GetMaxClock(mode, dataRate) : GetMinClock(mode, dataRate);

                    return clkScb;
                }
                catch (InvalidCastException ex)
                {
                    Debug.Fail(ex.Message);
                }
            }
            else
            {
                return new CyCustErr(Resources.ExprArgsNumCheck);
            }

            return (double)CyRanges.SLAVE_FSCB_MAX_100KBPS;
        }

        object GetScbClockPlusTolerance(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (args.Length == GET_FUNC_ARG_LENGTH)
            {
                try
                {
                    CyEModeType mode = (CyEModeType)typeConverter.GetAsByte(args[0]);
                    ushort dataRate = typeConverter.GetAsUShort(args[1]);

                    double tolerance = (mode == CyEModeType.SLAVE) ?
                                           CyRanges.CyTolerance.DEFAULT : 
                                           GetTolerance(mode, GetMinClock(mode, dataRate), GetMaxClock(mode, dataRate));
                    
                    return tolerance;
                }
                catch (InvalidCastException ex)
                {
                    Debug.Fail(ex.Message);
                }
            }
            else
            {
                return new CyCustErr(Resources.ExprArgsNumCheck);
            }

            return CyRanges.CyTolerance.DEFAULT;
        }

        object GetScbClockMinusTolerance(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (args.Length == GET_FUNC_ARG_LENGTH)
            {
                try
                {
                    CyEModeType mode = (CyEModeType)typeConverter.GetAsByte(args[0]);
                    ushort dataRate = typeConverter.GetAsUShort(args[1]);

                    double tolerance = (mode == CyEModeType.SLAVE) ?
                                            GetTolerance(mode, GetMinClock(mode, dataRate), GetMaxClock(mode, dataRate)) : 
                                            CyRanges.CyTolerance.DEFAULT;

                    return tolerance;
                }
                catch (InvalidCastException ex)
                {
                    Debug.Fail(ex.Message);
                }
            }
            else
            {
                return new CyCustErr(Resources.ExprArgsNumCheck);
            }

            return CyRanges.CyTolerance.DEFAULT;
        }

        public IEnumerable<CyExprEvalCustomFunctionData> GetCustomFunctionData()
        {
            yield return new CyExprEvalCustomFunctionData(GET_SCB_CLOCK_FUNC_NAME,
                String.Format("{0}(mode, dataRate, oversampling, isManualOvs) : double", GET_SCB_CLOCK_FUNC_NAME),
                "Gets SCB clock frequency.");

            yield return new CyExprEvalCustomFunctionData(GET_SCB_CLOCK_MINUS_TOLERANCE_FUNC_NAME,
                String.Format("{0}(mode, isManualOvs) : double", GET_SCB_CLOCK_MINUS_TOLERANCE_FUNC_NAME),
                "Gets SCB clock minus tolerance.");

            yield return new CyExprEvalCustomFunctionData(GET_SCB_CLOCK_PLUS_TOLERANCE_FUNC_NAME,
                String.Format("{0}(mode, dataRate, isManualOvs) : double", GET_SCB_CLOCK_PLUS_TOLERANCE_FUNC_NAME),
                "Gets SCB clock plus tolerance.");
        }
        #endregion

        #region ICyDRCProvider_v1 members
        const int WARNING_CODE = 100;
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CyParameters parameters = new CyParameters(args.InstQueryV1, args.TermQueryV1);

            List<CyCustErr> errorList = new List<CyCustErr>();
            errorList.AddRange(GetDrcErrors(parameters));

            for (int i = 0; i < errorList.Count; i++)
            {
                if (errorList[i].IsNotOk)
                {
                    CyDRCInfo_v1.CyDRCType_v1 errorType = errorList[i].ErrorId == WARNING_CODE
                        ? CyDRCInfo_v1.CyDRCType_v1.Warning
                        : CyDRCInfo_v1.CyDRCType_v1.Error;
                    yield return new CyDRCInfo_v1(errorType, errorList[i].Message);
                }
            }
        }

        public List<CyCustErr> GetDrcErrors(CyParameters parameters)
        {
            List<CyCustErr> errorList = new List<CyCustErr>();
            string errorMessage = String.Empty;

            // Check scb clock frequency ranges
            double actualScbClk;
            CyCustErr errClk = parameters.GetScbClock(out actualScbClk);

            if (errClk.IsNotOK)
            {
                switch (errClk.ErrorId)
                {
                    case (int)CyParameters.CyEClockErrorID.ERROR_SLAVE_CLK_BELOW_MIN:
                    case (int)CyParameters.CyEClockErrorID.ERROR_SLAVE_CLK_IN_GAP:
                    case (int)CyParameters.CyEClockErrorID.ERROR_SLAVE_CLK_ABOVE_MAX:
                        errorList.Add(new CyCustErr(errClk.Message));
                        break;

                    case (int)CyParameters.CyEClockErrorID.NOTE_MASTER_CLK_OUT_OF_RANGE:
                    case (int)CyParameters.CyEClockErrorID.NOTE_SLAVE_CLK_SUPPORT_TWO_DR:
                    case (int)CyParameters.CyEClockErrorID.UNKNOWN_CLK:
                        // Do nothing: these cases do not require DRC
                        break;

                    default:
                        Debug.Fail(String.Format(Resources.UnhandledSwitchValue, "CyEClockErrorID", errClk.ErrorId));
                        break;
                }
            }

            //Get Oversampling factor for master modes
            uint customOvsFactor = 0;
            if (parameters.Mode != CyEModeType.SLAVE)
            {
                if (parameters.ManualSclControl)
                {
                    customOvsFactor = (uint)(parameters.SclLowPhase + parameters.SclHighPhase);
                }
                else
                {
                    byte lowPhase;
                    byte highPhase;
                    parameters.GetAutoOversamplingLowHigh(out lowPhase, out highPhase);
                    customOvsFactor = (uint)(lowPhase + highPhase);
                }
            }

            // Calculate actual data rate
            uint actualDataRate;
            CyCustErr errDataRate = parameters.GetActualDataRate(customOvsFactor, out actualDataRate);
            if (errDataRate.IsNotOK)
            {
                switch (errDataRate.ErrorId)
                { 
                    case (int) CyParameters.CyEDataRateErrorID.ERROR_MASTER_DR_ABOVE_MAX:
                        errorList.Add(new CyCustErr(errDataRate.Message));
                        break;

                    case (int) CyParameters.CyEDataRateErrorID.WARNING_SLAVE_DR_NOT_MATCH:
                    case (int) CyParameters.CyEDataRateErrorID.WARNING_MASTER_DR_NOT_MATCH:
                        errorList.Add(new CyCustErr(WARNING_CODE, errDataRate.Message));
                        break;

                    case (int) CyParameters.CyEDataRateErrorID.NOTE_MASTER_DR_NOT_MATCH:
                    case (int)  CyParameters.CyEDataRateErrorID.UNKNOWN_CLK:
                        // Do nothing: these cases do not require DRC
                        break;

                    default:
                        Debug.Fail(String.Format(Resources.UnhandledSwitchValue, "CyEDataRateErrorID", errClk.ErrorId));
                        break;
                }
            }

            return errorList;
        }
        #endregion

        #region ICyAPICustomize_v1 members
        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery,
          IEnumerable<CyAPICustomizer> apis)
        {
            List<CyAPICustomizer> customizers = new List<CyAPICustomizer>(apis);
            Dictionary<string, string> paramDict = customizers[0].MacroDictionary;
            CyParameters parameters = new CyParameters(query, termQuery);

            // Set invisible formal parameters to 0.
            // If formal parameter is not visible that means that the parameter is not applicable in 
            // current configuration. Parameter with 0 value will be ignored by the firmware.
            foreach (string item in query.GetParamNames())
            {
                if (item != CyParamNames.INSTANCE_NAME && parameters.IsParamFormalAndHidden(item))
                {
                    paramDict[item] = "0";
                }
            }

            // Replace SCL phases with auto values if manual scl control is off. It is only 
            // applicable in the non-slave modes, in the slave mode ignore the SCL phase values.
            if (parameters.Mode != CyEModeType.SLAVE)
            {
                SetAutoLowHighOversampling(paramDict, parameters);
            }

            uint dataRateHz = 0;
            if (parameters.ClockFromTerm == false)
            {
                // Get desired data rate in Hz
                dataRateHz = parameters.DataRate;
            }
            else
            {
                // Get ac data rate in Hz
                uint ovsFactor = (uint)(parameters.SclLowPhase + parameters.SclHighPhase);

                parameters.GetActualDataRate(ovsFactor, out dataRateHz);            
            }
            // Add to dictionary
            dataRateHz *= 1000;
            paramDict.Add("DataRateHz", dataRateHz.ToString());

            // Get Component clock in Hz
            uint scbClockHz = (uint) Math.Truncate(1000 * parameters.GetClockKhz());
            paramDict.Add("ScbClockHz", scbClockHz.ToString());

            // Replace macro dictionaries with paramDict
            foreach (CyAPICustomizer file in customizers)
            {
                file.MacroDictionary = paramDict;
            }

            return customizers;
        }

        private void SetAutoLowHighOversampling(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            byte lowPhase;
            byte highPhase;

            if (parameters.ManualSclControl)
            {
                lowPhase = parameters.SclLowPhase;
                highPhase = parameters.SclHighPhase;
            }
            else
            {
                parameters.GetAutoOversamplingLowHigh(out lowPhase, out highPhase);
            }

            paramDict[CyParamNames.LOW_PHASE_DUTY_CYCLE] = lowPhase.ToString();
            paramDict[CyParamNames.HIGH_PHASE_DUTY_CYCLE] = highPhase.ToString();
        }
        #endregion
    }
}
