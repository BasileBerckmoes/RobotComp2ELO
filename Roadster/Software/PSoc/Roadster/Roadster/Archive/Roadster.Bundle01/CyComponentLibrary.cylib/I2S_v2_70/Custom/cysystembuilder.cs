/*******************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using System.Diagnostics;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System;
using System.Collections.Generic;
using System.Windows.Forms;
using CyDesigner.Toolkit.TerminalControl_v1;
using CyTerminalControl_v1 = CyDesigner.Toolkit.TerminalControl_v1.CyTerminalControl_v1;

namespace I2S_v2_70
{
    public partial class CyCustomizer : 
        ICySystemBuilderComp_v1,
        ICyClockControlData_v1<ICyInstEdit_v1>
    {
        #region Interconnect tab
        void UpdateInterconnectDisplay(CyTerminalControl_v1 termControl)
        {
            CyTermMode_v1[] termModeInternalUnused = new CyTermMode_v1[] {CyTermMode_v1.Internal, CyTermMode_v1.Unused};
            CyTermMode_v1[] termModeInternal = new CyTermMode_v1[] { CyTermMode_v1.Internal };

            CyTermControlRow_v1[] clocks = new CyTermControlRow_v1[1];
            clocks[0] = new CyTermControlRow_v1(CyTermName.CLOCK, CyTermName.CLOCK,
                                                new CyTermMode_v1[] { CyTermMode_v1.Internal },
                                                Properties.Resources.TermDescriptionClock);
            termControl.Clocks = clocks;

            List<CyTermControlRow_v1> interrupts = new List<CyTermControlRow_v1>();
            foreach (string terminal in CyTermName.InterruptList)
            {
                if (CyI2SParameters.GetValue<bool>(CyTermName.TERM_VISIBILITY_PARAM_PREFIX + terminal,
                    m_parameters.InstQuery))
                {
                    interrupts.Add(new CyTermControlRow_v1(terminal, terminal, termModeInternalUnused, 
                        String.Format(Properties.Resources.TermDescriptionInterrupt, terminal)));
                }
            }
            termControl.Interrupts = interrupts;

            List<CyTermControlRow_v1> other = new List<CyTermControlRow_v1>();
            foreach (string terminal in CyTermName.OtherTerminalList)
            {
                if (CyI2SParameters.GetValue<bool>(CyTermName.TERM_VISIBILITY_PARAM_PREFIX + terminal,
                                                   m_parameters.InstQuery))
                {
                    bool isDisableable = (terminal != CyTermName.SDI);
                    string description = String.Format((terminal == CyTermName.SDI)
                        ? Properties.Resources.TermDescriptionSdi
                        : Properties.Resources.TermDescriptionMultiOption, terminal);
                    other.Add(new CyTermControlRow_v1(terminal, terminal,
                        (isDisableable ? termModeInternalUnused : termModeInternal), description));
                }
            }
            termControl.Other = other;
        }
        #endregion

        #region ICySystemBuilderComp_v1 members

        public CyCustErr GetTitleText(ICySystemBuilderCompArgs_v1 args, out string title)
        {
            title = Properties.Resources.SBHeaderText;
            return CyCustErr.OK;
        }

        public CyCustErr GetBodyText(ICySystemBuilderCompArgs_v1 args, out string bodyText)
        {
            CyI2SParameters parameters = new CyI2SParameters(args.InstQuery);
            string direction = "";
            switch (parameters.Direction)
            {
                case CyEDirection.Rx:
                    direction = "Rx";
                    break;
                case CyEDirection.Tx:
                    direction = "Tx";
                    break;
                case CyEDirection.Rx_and_Tx:
                    direction = "Rx and Tx";
                    break;
                default:
                    Debug.Fail(Properties.Resources.DebugUnexpectedCase + typeof(CyEDirection).Name);
                    break;
            }
            bodyText = String.Format(Properties.Resources.SBBodyText, direction,
                parameters.DataBits, parameters.WordSelectPeriod);
            return CyCustErr.OK;
        }
        #endregion

        #region ICyClockControlData_v1<ICyInstEdit_v1> members
        bool ICyClockControlData_v1<ICyInstEdit_v1>.GetCheckTolerance(ICyInstEdit_v1 edit)
        {
            return CyI2SParameters.GetValue<bool>(CyClockParamName.CHECK_TOLERANCE, edit);
        }

        uint ICyClockControlData_v1<ICyInstEdit_v1>.GetDivider(ICyInstEdit_v1 edit)
        {
            return CyI2SParameters.GetValue<uint>(CyClockParamName.DIVISOR, edit);
        }

        uint ICyClockControlData_v1<ICyInstEdit_v1>.GetFractDividerDenominator(ICyInstEdit_v1 edit)
        {
            return CyI2SParameters.GetValue<uint>(CyClockParamName.FRACT_DIVIDER_DENOMINATOR, edit);
        }

        uint ICyClockControlData_v1<ICyInstEdit_v1>.GetFractDividerNumerator(ICyInstEdit_v1 edit)
        {
            return CyI2SParameters.GetValue<uint>(CyClockParamName.FRACT_DIVIDER_NUMERATOR, edit);
        }

        bool ICyClockControlData_v1<ICyInstEdit_v1>.GetFractDividerUsed(ICyInstEdit_v1 edit)
        {
            return CyI2SParameters.GetValue<bool>(CyClockParamName.FRACT_DIVIDER_USED, edit);
        }

        byte ICyClockControlData_v1<ICyInstEdit_v1>.GetFrequencyUnit(ICyInstEdit_v1 edit)
        {
            return CyI2SParameters.GetValue<byte>(CyClockParamName.DESIRED_FREQ_UNIT, edit);
        }

        double ICyClockControlData_v1<ICyInstEdit_v1>.GetFrequencyValue(ICyInstEdit_v1 edit)
        {
            return CyI2SParameters.GetValue<double>(CyClockParamName.DESIRED_FREQ, edit);
        }

        bool ICyClockControlData_v1<ICyInstEdit_v1>.GetIsExistingClock(ICyInstEdit_v1 edit)
        {
            return CyI2SParameters.GetValue<bool>(CyClockParamName.IS_DIRECT, edit);
        }

        bool ICyClockControlData_v1<ICyInstEdit_v1>.GetIsNewDividerClock(ICyInstEdit_v1 edit)
        {
            return CyI2SParameters.GetValue<bool>(CyClockParamName.IS_DIVIDER, edit);
        }

        bool ICyClockControlData_v1<ICyInstEdit_v1>.GetIsNewFreqClock(ICyInstEdit_v1 edit)
        {
            return CyI2SParameters.GetValue<bool>(CyClockParamName.IS_DESIRED_FREQ, edit);
        }

        double ICyClockControlData_v1<ICyInstEdit_v1>.GetMinusTolerance(ICyInstEdit_v1 edit)
        {
            return CyI2SParameters.GetValue<double>(CyClockParamName.MINUS_TOLERANCE, edit);
        }

        double ICyClockControlData_v1<ICyInstEdit_v1>.GetPlusTolerance(ICyInstEdit_v1 edit)
        {
            return CyI2SParameters.GetValue<double>(CyClockParamName.PLUS_TOLERANCE, edit);
        }

        string ICyClockControlData_v1<ICyInstEdit_v1>.GetSrcClkID(ICyInstEdit_v1 edit)
        {
            return CyI2SParameters.GetValue<string>(CyClockParamName.SOURCE_CLOCK_ID, edit);
        }

        string ICyClockControlData_v1<ICyInstEdit_v1>.GetSrcClkName(ICyInstEdit_v1 edit)
        {
            return CyI2SParameters.GetValue<string>(CyClockParamName.SOURCE_CLOCK_NAME, edit);
        }

        CyCustErr ICyClockControlData_v1<ICyInstEdit_v1>.IsDividerValid(ICyInstEdit_v1 edit, string value)
        {
            return ValidateParam(edit, CyClockParamName.DIVISOR, value);
        }

        CyCustErr ICyClockControlData_v1<ICyInstEdit_v1>.IsFreqUnitValid(ICyInstEdit_v1 edit, string value)
        {
            return ValidateParam(edit, CyClockParamName.DESIRED_FREQ_UNIT, value);
        }

        CyCustErr ICyClockControlData_v1<ICyInstEdit_v1>.IsFreqValid(ICyInstEdit_v1 edit, string value)
        {
            return ValidateParam(edit, CyClockParamName.DESIRED_FREQ, value);
        }

        CyCustErr ICyClockControlData_v1<ICyInstEdit_v1>.IsMinusToleranceValid(ICyInstEdit_v1 edit, string value)
        {
            return ValidateParam(edit, CyClockParamName.MINUS_TOLERANCE, value);
        }

        CyCustErr ICyClockControlData_v1<ICyInstEdit_v1>.IsPlusToleranceValid(ICyInstEdit_v1 edit, string value)
        {
            return ValidateParam(edit, CyClockParamName.PLUS_TOLERANCE, value);
        }

        CyCustErr ICyClockControlData_v1<ICyInstEdit_v1>.IsSourceClkIdValid(ICyInstEdit_v1 edit, string value)
        {
            return ValidateParam(edit, CyClockParamName.SOURCE_CLOCK_ID, value);
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnCheckToleranceChanged(ICyInstEdit_v1 edit, bool checkTolerance)
        {
            CyI2SParameters.SetValue(edit, CyClockParamName.CHECK_TOLERANCE, checkTolerance);
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnDividerChanged(ICyInstEdit_v1 edit, uint divider)
        {
            CyI2SParameters.SetValue(edit, CyClockParamName.DIVISOR, divider);
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnFractDividerNumeratorChanged(ICyInstEdit_v1 edit, uint numerator,
            uint denominator)
        {
            CyI2SParameters.SetValue(edit, CyClockParamName.FRACT_DIVIDER_NUMERATOR, numerator);
            CyI2SParameters.SetValue(edit, CyClockParamName.FRACT_DIVIDER_DENOMINATOR, denominator);
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnFractDividerUsedChanged(ICyInstEdit_v1 edit, bool used,
            uint denominator)
        {
            CyI2SParameters.SetValue(edit, CyClockParamName.FRACT_DIVIDER_USED, used);
            CyI2SParameters.SetValue(edit, CyClockParamName.FRACT_DIVIDER_DENOMINATOR, (used ? denominator : 0));
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnFreqChanged(ICyInstEdit_v1 edit, double frequencyValue,
            byte frequencyUnit)
        {
            CyI2SParameters.SetValue(edit, CyClockParamName.DESIRED_FREQ, frequencyValue);
            CyI2SParameters.SetValue(edit, CyClockParamName.DESIRED_FREQ_UNIT, frequencyUnit);
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnIsNewChanged(ICyInstEdit_v1 edit, bool isExistingClock)
        {
            CyI2SParameters.SetValue(edit, CyClockParamName.IS_DIRECT, isExistingClock);
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnMinusToleranceChanged(ICyInstEdit_v1 edit, double minusTolerance)
        {
            CyI2SParameters.SetValue(edit, CyClockParamName.MINUS_TOLERANCE, minusTolerance);
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnPlusToleranceChanged(ICyInstEdit_v1 edit, double plusTolerance)
        {
            CyI2SParameters.SetValue(edit, CyClockParamName.PLUS_TOLERANCE, plusTolerance);
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnSourceClkChanged(ICyInstEdit_v1 edit, string srcClkId,
            string srcClkName)
        {
            CyI2SParameters.SetValue(edit, CyClockParamName.SOURCE_CLOCK_ID, srcClkId);
            CyI2SParameters.SetValue(edit, CyClockParamName.SOURCE_CLOCK_NAME, srcClkName);
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnUseDividerChanged(ICyInstEdit_v1 edit, bool isNewDividerClock)
        {
            CyI2SParameters.SetValue(edit, CyClockParamName.IS_DIVIDER, isNewDividerClock);
        }

        void ICyClockControlData_v1<ICyInstEdit_v1>.OnUseFreqChanged(ICyInstEdit_v1 edit, bool isNewFreqClock)
        {
            CyI2SParameters.SetValue(edit, CyClockParamName.IS_DESIRED_FREQ, isNewFreqClock);
        }

        /// <summary>
        /// This function tries to save the parameter value and checkes if it was saved without errors
        /// </summary>
        /// <param name="edit"></param>
        /// <param name="paramName"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        CyCustErr ValidateParam(ICyInstEdit_v1 edit, string paramName, string value)
        {
            return CyI2SParameters.SetValue(edit, paramName, value);
        }
        #endregion

        #region CyClockParamEditingControl which represents Clock tab
        public class CyClockParamEditingControl : ICyParamEditingControl
        {
            private readonly ICyInstEdit_v1 m_instEdit;
            private readonly Control m_displayControl;

            public CyClockParamEditingControl(ICyInstEdit_v1 editObj, Control displayControl)
            {
                m_instEdit = editObj;
                m_displayControl = displayControl;
            }

            public Control DisplayControl
            {
                get { return m_displayControl; }
            }

            public string TabName
            {
                get { return "Clock"; }
            }

            public IEnumerable<CyCustErr> GetErrors()
            {
                foreach (string paramName in m_instEdit.GetParamNames())
                {
                    CyCompDevParam param = m_instEdit.GetCommittedParam(paramName);
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
        }
        #endregion
    }

    #region Parameters necessary to control the cy_clock component and clock terminal
    internal class CyClockParamName
    {
        internal const string IS_DESIRED_FREQ = "Clock_is_freq";
        internal const string DESIRED_FREQ = "Clock_desired_freq";
        internal const string DESIRED_FREQ_UNIT = "Clock_desired_freq_unit";
        internal const string IS_DIVIDER = "Clock_is_divider";
        internal const string DIVISOR = "Clock_divisor";

        internal const string SOURCE_CLOCK_ID = "Clock_source_clock_id";
        internal const string SOURCE_CLOCK_NAME = "Clock_source_clock_name";

        internal const string IS_DIRECT = "Clock_is_direct";
        internal const string MINUS_TOLERANCE = "Clock_minus_tolerance";
        internal const string PLUS_TOLERANCE = "Clock_plus_tolerance";
        internal const string CHECK_TOLERANCE = "Clock_CheckTolerance";

        internal const string FRACT_DIVIDER_USED = "Clock_FractDividerUsed";
        internal const string FRACT_DIVIDER_NUMERATOR = "Clock_FractDividerNumerator";
        internal const string FRACT_DIVIDER_DENOMINATOR = "Clock_FractDividerDenominator";
    }

    internal class CyTermParamName
    {
        internal const string TERM_MODE_CLOCK = "TermMode_clock";
    }
    #endregion

    #region Component terminals names
    internal class CyTermName
    {
        //Inputs
        internal const string CLOCK = "clock";
        internal const string SDI = "sdi";
        //Outputs
        internal const string SDO = "sdo";
        internal const string SCK = "sck";
        internal const string WS = "ws";
        internal const string RX_INTERRUPT = "rx_interrupt";
        internal const string TX_INTERRUPT = "tx_interrupt";
        internal const string RX_DMA_0 = "rx_dma0";
        internal const string TX_DMA_0 = "tx_dma0";
        internal const string RX_DMA_1 = "rx_dma1";
        internal const string TX_DMA_1 = "tx_dma1";
        internal const string CLIP = "clip";

        public static readonly string[] InterruptList = { RX_INTERRUPT, TX_INTERRUPT};
        public static readonly string[] OtherTerminalList = { SDI, SDO, SCK, WS, CLIP };

        public const string TERM_VISIBILITY_PARAM_PREFIX = "TermVisibility_";
    }
    #endregion
}
