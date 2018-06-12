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
using SCB_EZI2C_PDL_v2_0.Controls;

namespace SCB_EZI2C_PDL_v2_0
{
    sealed public class CyCustomizer : ICyParamEditHook_v1, ICyDRCProvider_v1, ICyExprEval_v3
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
            editor.AddDefaultPage(Resources.PinsTabDisplayName,"Pins");
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

        private double GetMinClock(ushort dataRate)
        {
            double clkScb = (double) 
                    ((dataRate <= CyRanges.DATA_RATE_100)  ? (CyRanges.SLAVE_FSCB_MIN_100KBPS) : 
                     (dataRate <= CyRanges.DATA_RATE_400)  ? (CyRanges.SLAVE_FSCB_MIN_400KBPS) : 
                     (dataRate <= CyRanges.DATA_RATE_1000) ? (CyRanges.SLAVE_FSCB_MIN_1000KBPS) : 
                                                             (CyRanges.SLAVE_FSCB_MIN_100KBPS));

            return clkScb;
        }

        private double GetMaxClock(ushort dataRate)
        {
            double clkScb = (double)
                    ((dataRate <= CyRanges.DATA_RATE_100)  ? (CyRanges.SLAVE_FSCB_MAX_100KBPS) :
                     (dataRate <= CyRanges.DATA_RATE_400)  ? (CyRanges.SLAVE_FSCB_MAX_400KBPS) :
                     (dataRate <= CyRanges.DATA_RATE_1000) ? (CyRanges.SLAVE_FSCB_MAX_1000KBPS) :
                                                             (CyRanges.SLAVE_FSCB_MAX_100KBPS));

            return clkScb;
        }

        object GetScbClock(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (args.Length == 1)
            {
                try
                {
                    ushort dataRate = typeConverter.GetAsUShort(args[0]);

                    return GetMaxClock(dataRate);
                }
                catch (InvalidCastException ex)
                {
                    Debug.Fail(ex.Message);

                    return (double)CyRanges.SLAVE_FSCB_MAX_100KBPS;
                }
            }
            else
            {
                return new CyCustErr(Resources.ExprDataRateArgCheck);
            }
        }

        object GetScbClockMinusTolerance(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (args.Length == 1)
            {
                try
                {
                    ushort dataRate = typeConverter.GetAsUShort(args[0]);

                    double tolerance;
                    double clkMin = GetMinClock(dataRate);
                    double clkMax = GetMaxClock(dataRate);

                    // Clock is defined as max - tolerance (takes into account IMO accuracy)
                    tolerance = (double)CyRanges.CyTolerance.MINUS_MAX - ((clkMin / clkMax) * 100);

                    return tolerance;
                }
                catch (InvalidCastException ex)
                {
                    Debug.Fail(ex.Message);
                    return CyRanges.CyTolerance.MINUS_MAX;
                }
            }
            else
            {
                return new CyCustErr(Resources.ExprDataRateArgCheck);
            }
        }

        object GetScbClockPlusTolerance(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (args.Length == 0)
            {
                return CyRanges.CyTolerance.DEFAULT;
            }
            else
            {
                return new CyCustErr(Resources.ExprNoArgCheck);
            }
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
            
            uint actualDataRate;
            CyCustErr err = parameters.GetActualDataRate(out actualDataRate);

            // Do not trigger DRC if clock is unknown
            if (err.ErrorId != (int) CyParameters.CyEClockErrorID.UNKNOWN_CLK)
            {
                // Actual data rate was calcualted: got EZI2C clock
                if (err.IsNotOK)
                {
                    errorList.Add(err);
                }
                else
                {
                    // Check if desired data rate is reached
                    if ((parameters.ClockFromTerm == false) && (actualDataRate < parameters.DataRate))
                    {
                        CyCustErr warn = new CyCustErr(WARNING_CODE, Resources.DataRateWarning);
                        errorList.Add(warn);
                    }
                }
            }

            return errorList;
        }
        #endregion

    }
}
