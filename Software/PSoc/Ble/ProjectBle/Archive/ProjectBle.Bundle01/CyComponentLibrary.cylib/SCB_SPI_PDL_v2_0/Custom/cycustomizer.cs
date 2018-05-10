/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Linq;
using System.Drawing;
using System.Diagnostics;
using System.Windows.Forms;
using System.Collections.Generic;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using SCB_SPI_PDL_v2_0.Controls;

namespace SCB_SPI_PDL_v2_0
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
                false, SizeType.Percent, 60);

            using (CyImagePageControl imageControl = new CyImagePageControl(new Bitmap(570, 158),
                PictureBoxSizeMode.Normal, false, SizeType.Percent, 60, parameters))
            {
                CyTabParamEditorDefaultPageExtender extender = new CyTabParamEditorDefaultPageExtender();
                extender.InnerLeftBottomControl = imageControl;
                extender.InnerRightBottomControl = userControl;

                ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
                editor.UseBigEditor = true;

                editor.AddDefaultPage(Resources.BasicTabDisplayName, extender);
                editor.AddDefaultPage(Resources.AdvancedTabDisplayName, "Advanced");
                editor.AddDefaultPage(Resources.PinsTabDisplayName, "Pins");
                editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");

                edit.NotifyWhenDesignUpdates(parameters.UpdateDesigns);
                parameters.EditMode = true;

                return editor.ShowDialog();
            }
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

        object GetScbClock(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
           ICyExprTypeConverter typeConverter)
        {
            if (args.Length == 4)
            {
                CyEModeType mode = (CyEModeType)typeConverter.GetAsInt(args[0]);
                ushort dataRateKHz = typeConverter.GetAsUShort(args[1]);
                byte ovs = typeConverter.GetAsByte(args[2]);
                bool enableInputGlitchFilter = typeConverter.GetAsBool(args[3]);

                if (dataRateKHz > 0)
                {
                    double scbClk = 0;

                    switch (mode)
                    {
                        case CyEModeType.SPI_SLAVE:

                            // How many SCB clocks are needed to get MISO output
                            byte scbClocksToOutput = CyParameters.GetClockCyclesToOutput(enableInputGlitchFilter);

                            // Get SPI SCLK period (units ns)
                            double spiClkPeriod = (1000000.0 / dataRateKHz);

                            // Get time availalbe for tDSO (units ns)
                            double spiTdso = (spiClkPeriod / 2) - (double)(CyParamRanges.T_DSO_INTERNAL + CyParamRanges.T_MASTER_DELAYS);

                            if (spiTdso > 0)
                            {
                                // Get SCB clock (units kHz)
                                scbClk = 1000000 * (scbClocksToOutput / spiTdso);
                            }
                            else
                            {
                                // There is no space for spiTso. Select max PERI clock
                                scbClk = CyParamRanges.PERICLK_MAX_FREQ;
                            }

                            break;

                        case CyEModeType.SPI_MASTER:
                            scbClk = ovs * dataRateKHz;
                            break;

                        default:
                            return new CyCustErr(Resources.ExprModeCheck, mode);
                    }

                    //Align with maximum PERI clock value
                    scbClk = Math.Round(scbClk, 3);
                    if (scbClk > CyParamRanges.PERICLK_MAX_FREQ)
                    {
                        scbClk = CyParamRanges.PERICLK_MAX_FREQ;
                    }

                    return scbClk;
                }
                else
                {
                    return new CyCustErr(Resources.ExprDataRateCheck);
                }
            }
            else
            {
                return new CyCustErr(Resources.ExprScbClkArgCheck);
            }
        }

        object GetScbClockMinusTolerance(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (args.Length == 1)
            {
                try
                {
                    CyEModeType mode = (CyEModeType)typeConverter.GetAsByte(args[0]);

                    return (mode == CyEModeType.SPI_MASTER) ? (double)CyETolerance.MINUS_MAX :
                                                              (double)CyETolerance.DEFAULT;
                }
                catch (InvalidCastException ex)
                {
                    Debug.Fail(ex.Message);

                    return (double)CyETolerance.MINUS_MAX;
                }
            }
            else
            {
                return new CyCustErr(Resources.ExprModeArgCheck);
            }
        }

        object GetScbClockPlusTolerance(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (args.Length == 1)
            {
                try
                {
                    CyEModeType mode = (CyEModeType)typeConverter.GetAsByte(args[0]);

                    return (mode == CyEModeType.SPI_MASTER) ? (double)CyETolerance.DEFAULT :
                                                              (double)CyETolerance.PLUS_MAX;
                }
                catch (InvalidCastException ex)
                {
                    Debug.Fail(ex.Message);

                    return CyETolerance.PLUS_MAX;
                }
            }
            else
            {
                return new CyCustErr(Resources.ExprModeArgCheck);
            }
        }

        public IEnumerable<CyExprEvalCustomFunctionData> GetCustomFunctionData()
        {
            yield return new CyExprEvalCustomFunctionData(GET_SCB_CLOCK_FUNC_NAME,
                String.Format("{0}(dataRate, oversampling) : double", GET_SCB_CLOCK_FUNC_NAME),
                "Gets SCB clock frequency.");

            yield return new CyExprEvalCustomFunctionData(GET_SCB_CLOCK_MINUS_TOLERANCE_FUNC_NAME,
                String.Format("{0}(mode) : double", GET_SCB_CLOCK_MINUS_TOLERANCE_FUNC_NAME),
                "Gets SCB clock minus tolerance.");

            yield return new CyExprEvalCustomFunctionData(GET_SCB_CLOCK_PLUS_TOLERANCE_FUNC_NAME,
                String.Format("{0}(mode) : double", GET_SCB_CLOCK_PLUS_TOLERANCE_FUNC_NAME),
                "Gets SCB clock plus tolerance.");
        }
        #endregion

        #region ICyDRCProvider_v1 members
        private const int WARNING_CODE = 100;
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CyParameters parameters = new CyParameters(args.InstQueryV1, args.TermQueryV1);

            List<CyCustErr> errorList = new List<CyCustErr>(GetSpiDrcErrors(parameters));

            for (int i = 0; i < errorList.Count; i++)
            {
                if (errorList[i] != CyCustErr.OK)
                {
                    CyDRCInfo_v1.CyDRCType_v1 errorType = errorList[i].ErrorId == WARNING_CODE
                        ? CyDRCInfo_v1.CyDRCType_v1.Warning
                        : CyDRCInfo_v1.CyDRCType_v1.Error;
                    yield return new CyDRCInfo_v1(errorType, errorList[i].Message);
                }
            }
        }

        private static List<CyCustErr> GetSpiDrcErrors(CyParameters parameters)
        {
            List<CyCustErr> errorList = new List<CyCustErr>();

            // Check DMA Rx Tx outputs
            if (parameters.IsDmaCapable == false)
            {
                if (parameters.RxOutput || parameters.TxOutput)
                    errorList.Add(new CyCustErr(Resources.DMASupportError));
            }

            return errorList;
        }
        #endregion
    }
}
