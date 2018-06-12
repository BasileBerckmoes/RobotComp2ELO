/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using CyDesigner.Toolkit;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using System.Diagnostics;

namespace SCB_I2C_PDL_v2_0
{
    #region Component Parameters Names
    public class CyParamNames
    {
        public const string ACCEPT_ADDRESS = "AcceptAddress";
        public const string ACCEPT_GENERAL_CALL = "AcceptGeneralCall";
        public const string DATA_RATE = "DataRate";
        public const string ENABLE_RX_FIFO = "EnableRxFifo";
        public const string ENABLE_TX_FIFO = "EnableTxFifo";
        public const string ENABLE_WAKEUP = "EnableWakeup";
        public const string MODE = "Mode";
        public const string HIGH_PHASE_DUTY_CYCLE = "HighPhaseDutyCycle";
        public const string LOW_PHASE_DUTY_CYCLE = "LowPhaseDutyCycle";
        public const string SLAVE_ADDRESS = "SlaveAddress";
        public const string SLAVE_ADDRESS_MASK = "SlaveAddressMask";
        public const string ENABLE_MANUAL_SCL_CONTROL = "EnableManualSclControl";
        public const string CLOCK_FROM_TERM = "ClockFromTerm";
        public const string SHOW_TERMINALS = "ShowTerminals";

        public const string INSTANCE_NAME = "INSTANCE_NAME";
    }
    #endregion

    #region Component Parameters Ranges
    public class CyRanges
    {
        public const ushort DATA_RATE_MIN = 1;
        public const ushort DATA_RATE_MAX = 1000;

        public const int DATA_RATE_100 = 100;
        public const int DATA_RATE_400 = 400;
        public const int DATA_RATE_1000 = 1000;

        public const int OVS_FACTOR = 32;
        public const int OVS_FACTOR_LOW_MAX = 16;
        public const int OVS_FACTOR_HIGH_MAX = 16;
        public const int OVS_FACTOR_MAX = OVS_FACTOR_LOW_MAX + OVS_FACTOR_HIGH_MAX;

        // Margins from 002-10901 Rev **, section 4.4.3.6.2 Internal-clocked slave, DF = 0 
        public const int SLAVE_FSCB_MIN_100KBPS = 1550;
        public const int SLAVE_FSCB_MAX_100KBPS = 12800;
        public const int SLAVE_FSCB_MIN_400KBPS = 7820;
        public const int SLAVE_FSCB_MAX_400KBPS = 15380;
        public const int SLAVE_FSCB_MIN_1000KBPS = 15840;
        public const int SLAVE_FSCB_MAX_1000KBPS = 89000;

        // These constants are used only for display purposes
        public const double SLAVE_FSCB_MIN_100KBPS_MHZ  = (double) SLAVE_FSCB_MIN_100KBPS / 1000;
        public const double SLAVE_FSCB_MAX_400KBPS_MHZ  = (double) SLAVE_FSCB_MAX_400KBPS / 1000;
        public const double SLAVE_FSCB_MIN_1000KBPS_MHZ = (double) SLAVE_FSCB_MIN_1000KBPS / 1000;
        public const double SLAVE_FSCB_MAX_1000KBPS_MHZ = (double) SLAVE_FSCB_MAX_1000KBPS / 1000;

        // Margins from 002-10901 Rev **, section 4.4.3.6.3 Master-Slave. 
        // Note, DF = 0 for 100 and 400kpbs, DF = 1 only for 1000 kbps
        public const int MASTER_FSCB_MIN_100KBPS = 1550;
        public const int MASTER_FSCB_MAX_100KBPS = 3200;
        public const int MASTER_FSCB_MIN_400KBPS = 7820;
        public const int MASTER_FSCB_MAX_400KBPS = 10000;
        public const int MASTER_FSCB_MIN_1000KBPS = 14320;
        public const int MASTER_FSCB_MAX_1000KBPS = 25800;

        public const int OVS_LOW_MIN_100KBPS = 8;
        public const int OVS_HIGH_MIN_100KBPS = 8;
        public const int OVS_LOW_MIN_400KBPS = 13;
        public const int OVS_HIGH_MIN_400KBPS = 8;
        public const int OVS_LOW_MIN_1000KBPS = 9;
        public const int OVS_HIGH_MIN_1000KBPS = 6;

        public const int SCL_LOW_IDEAL_100KBPS = 5000;  // tLOW  + tF = 4700 + 300;
        public const int SCL_HIGH_IDEAL_100KBPS = 5000; // tHIGH + tR = 4000 + 1000;
        public const int SCL_LOW_IDEAL_400KBPS = 1600;  // tLOW  + tF = 1300 + 300;
        public const int SCL_HIGH_IDEAL_400KBPS = 900;  // tHIGH + tR = 600  + 300;
        public const int SCL_LOW_IDEAL_1000KBPS = 620;  // tLOW  + tF = 500  + 120;
        public const int SCL_HIGH_IDEAL_1000KBPS = 380; // tHIGH + tR = 260  + 120;

        public const double EPS = 1E-5;

        public class CyTolerance
        {
            public const double DEFAULT = 5;
            public const double MINUS_MAX = 100;
            public const double PLUS_MAX = 1000;
            public const double ZERO_ACCURACY = 0;
        }
    }
    #endregion

    #region Component Enums
    public enum CyEModeType { SLAVE = 1, MASTER = 2, MASTER_SLAVE = 3 }
    public enum CyEToleranceMode { MINUS_TOLERANCE = 0, PLUS_TOLERANCE = 1 };
    #endregion

    public class CyParameters
    {
        #region Enums
        public enum CyEClockErrorID
        {
            UNKNOWN_CLK = 1, 
            NOTE_MASTER_CLK_OUT_OF_RANGE  = 2,
            NOTE_SLAVE_CLK_SUPPORT_TWO_DR = 3,
            ERROR_SLAVE_CLK_BELOW_MIN = 4,
            ERROR_SLAVE_CLK_IN_GAP = 5, 
            ERROR_SLAVE_CLK_ABOVE_MAX = 6,
        };

        public enum CyEDataRateErrorID
        {
            UNKNOWN_CLK = 1,
            ERROR_MASTER_DR_ABOVE_MAX = 2,
            WARNING_SLAVE_DR_NOT_MATCH = 3,
            WARNING_MASTER_DR_NOT_MATCH = 4,
            NOTE_MASTER_DR_NOT_MATCH = 5,
        };
        #endregion

        #region Private fields
        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyInstEdit_v1 m_instEdit;
        private readonly ICyTerminalQuery_v1 m_termQuery;
        #endregion

        #region Constructor(s)
        private CyParameters(ICyInstQuery_v1 instQuery, ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery)
        {
            m_instQuery = instQuery;
            m_instEdit = instEdit;
            m_termQuery = termQuery;
        }

        public CyParameters(ICyInstQuery_v1 instQuery)
            : this(instQuery, null, null)
        {
        }

        public CyParameters(ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery)
            : this(instEdit, instEdit, termQuery)
        {
        }

        public CyParameters(ICyInstQuery_v1 instQuery, ICyTerminalQuery_v1 termQuery)
            : this(instQuery, null, termQuery)
        {
        }
        #endregion

        #region Properties
        //
        // Common properties
        //
        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        }

        public ICyTerminalQuery_v1 TermQuery
        {
            get { return m_termQuery; }
        }

        //
        // Basic tab properties
        //
        public CyEModeType Mode
        {
            get { return GetValue<CyEModeType>(CyParamNames.MODE); }
        }

        public UInt16 DataRate
        {
            get { return GetValue<UInt16>(CyParamNames.DATA_RATE); }
        }

        public bool ClockFromTerm
        {
            get { return GetValue<bool>(CyParamNames.CLOCK_FROM_TERM); }
        }

        public byte SclLowPhase
        {
            get { return GetValue<byte>(CyParamNames.LOW_PHASE_DUTY_CYCLE); }
        }

        public byte SclHighPhase
        {
            get { return GetValue<byte>(CyParamNames.HIGH_PHASE_DUTY_CYCLE); }
        }

        public byte SlaveAddress
        {
            get { return GetValue<byte>(CyParamNames.SLAVE_ADDRESS); }
        }

        public byte SlaveAddressMask
        {
            get { return GetValue<byte>(CyParamNames.SLAVE_ADDRESS_MASK); }
        }

        public bool AcceptAddress
        {
            get { return GetValue<bool>(CyParamNames.ACCEPT_ADDRESS); }
        }

        public bool EnableTxFifo
        {
            get { return GetValue<bool>(CyParamNames.ENABLE_TX_FIFO); }
        }

        public bool EnableRxFifo
        {
            get { return GetValue<bool>(CyParamNames.ENABLE_RX_FIFO); }
        }

        public bool AcceptGeneralCallAddress
        {
            get { return GetValue<bool>(CyParamNames.ACCEPT_GENERAL_CALL); }
        }

        public bool EnableWakeup
        {
            get { return GetValue<bool>(CyParamNames.ENABLE_WAKEUP); }
        }

        public bool ManualSclControl
        {
            get { return GetValue<bool>(CyParamNames.ENABLE_MANUAL_SCL_CONTROL); }
        }

        //
        // Pins tab properties
        //
        public bool ShowTerminals
        {
            get { return GetValue<bool>(CyParamNames.SHOW_TERMINALS); }
        }
        #endregion

        #region Events
        /// <summary>
        /// An event that clients can use to be notified whenever the PSoC Creator design updates.
        /// </summary>
        public event EventHandler DesignUpdated;

        // Invoke the DesignUpdates event; called whenever PSoC Creator design updates.
        protected virtual void OnDesignUpdated(EventArgs e)
        {
            EventHandler handler = DesignUpdated;
            if (handler != null)
                handler(this, e);
        }

        public void OnDesignUpdated(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            OnDesignUpdated(EventArgs.Empty);
        }
        #endregion

        #region Getting Parameters
        public T GetValue<T>(string paramName)
        {
            return GetValue<T>(paramName, m_instQuery);
        }

        public static T GetValue<T>(string paramName, ICyInstQuery_v1 instQuery)
        {
            if (instQuery == null) return default(T);
            T value;
            CyCustErr err = instQuery.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            return (err != null && err.IsOK) ? value : default(T);
        }

        public bool IsParamFormalAndHidden(string paramName)
        {
            bool result = false;
            if (m_instQuery != null)
            {
                CyCompDevParam param = m_instQuery.GetCommittedParam(paramName);
                result = param != null && param.IsFormal && param.IsVisible == false;
            }
            return result;
        }
        #endregion

        #region Clock
        /// <summary>
        /// Gets external or internal clock frequency depending whether clock from terminal is selected.
        /// </summary>
        /// <returns>External or internal clock frequency in kHz.</returns>
        public double GetClockKhz()
        {
            return ClockFromTerm ? GetExternalClockKhz(TermQuery) : GetInternalClockKhz(TermQuery);
        }

        /// <summary>
        /// Gets internal clock value.
        /// </summary>
        public static double GetInternalClockKhz(ICyTerminalQuery_v1 termQuery)
        {
            return CyClock.GetInternalClockKhz(termQuery, "or_sclk");
        }

        /// <summary>
        /// Gets external (from terminal) clock value.
        /// </summary>
        public static double GetExternalClockKhz(ICyTerminalQuery_v1 termQuery)
        {
            return CyClock.GetExternalClockKhz(termQuery, "clock");
        }
        #endregion

        #region Data rate
        public CyCustErr GetScbClock(out double scbClk)
        {
            CyCustErr err = CyCustErr.OK;
            
            scbClk = GetClockKhz();

            if (CyClock.IsFrequencyKnown(scbClk))
            {
                if (Mode == CyEModeType.SLAVE)
                {
                    // Check applicable ranges for Slave clock
                    if (scbClk < (CyRanges.SLAVE_FSCB_MIN_100KBPS + CyRanges.EPS))
                    {
                        // Clock frequency is less than 1.55MHz
                        err = new CyCustErr((int)CyEClockErrorID.ERROR_SLAVE_CLK_BELOW_MIN,
                                    String.Format(Resources.SlaveClockTooLowError, CyRanges.SLAVE_FSCB_MIN_100KBPS_MHZ));
                    }
                    else if (scbClk > (CyRanges.SLAVE_FSCB_MAX_400KBPS + CyRanges.EPS) &&
                             scbClk < (CyRanges.SLAVE_FSCB_MIN_1000KBPS + CyRanges.EPS))
                    {
                        // Clock frequency is in the gap between 400kpbs and 1000 kpbs: 15.38 - 15.84 MHz
                        err = new CyCustErr((int)CyEClockErrorID.ERROR_SLAVE_CLK_IN_GAP,
                                    String.Format(Resources.SlaveClockInGapError, CyRanges.SLAVE_FSCB_MAX_400KBPS_MHZ,
                                     CyRanges.SLAVE_FSCB_MIN_1000KBPS_MHZ));
                    }
                    else if (scbClk > (CyRanges.SLAVE_FSCB_MAX_1000KBPS + CyRanges.EPS))
                    {
                        // Clock frequency above max supported: 89MHz
                        err = new CyCustErr((int)CyEClockErrorID.ERROR_SLAVE_CLK_ABOVE_MAX,
                                    String.Format(Resources.SlaveClockOutOfRangeError, CyRanges.SLAVE_FSCB_MAX_1000KBPS_MHZ));
                    }
                    else
                    { 
                        // No error: slave clock pass verification
                    }
                    
                    // Add note if Clock supports two data rates
                    if (scbClk > (CyRanges.SLAVE_FSCB_MIN_400KBPS - CyRanges.EPS) && scbClk < (CyRanges.SLAVE_FSCB_MAX_100KBPS + CyRanges.EPS))
                    {
                        err = new CyCustErr((int)CyEClockErrorID.NOTE_SLAVE_CLK_SUPPORT_TWO_DR, Resources.SlaveClockSupportsBothDataRates);
                    }
                }
                else
                {
                    // Check applicable ranges for Master and Master-Slave clock
                    if (false ==
                         ((scbClk > (CyRanges.MASTER_FSCB_MIN_100KBPS - CyRanges.EPS) && scbClk < (CyRanges.MASTER_FSCB_MAX_100KBPS + CyRanges.EPS)) ||
                          (scbClk > (CyRanges.MASTER_FSCB_MIN_400KBPS - CyRanges.EPS) && scbClk < (CyRanges.MASTER_FSCB_MAX_400KBPS + CyRanges.EPS)) ||
                          (scbClk > (CyRanges.MASTER_FSCB_MIN_1000KBPS - CyRanges.EPS) && scbClk < (CyRanges.MASTER_FSCB_MAX_1000KBPS + CyRanges.EPS)))
                    )
                    {
                        err = new CyCustErr((int)CyEClockErrorID.NOTE_MASTER_CLK_OUT_OF_RANGE, Resources.MasterClockNote);
                    }
                }

                // Adjust clock value to be displayed
                scbClk = Math.Round(scbClk, 3);
            }
            else
            {
                err = new CyCustErr((int)CyEClockErrorID.UNKNOWN_CLK, Resources.UnknownClkFreq);
            }

            return err;
        }

        public CyCustErr GetActualDataRate(uint ovsFactor, out uint actualDataRate)
        {
            actualDataRate = 0;
            CyCustErr err = CyCustErr.OK;
            double scbClk = GetClockKhz();

            if (CyClock.IsFrequencyKnown(scbClk))
            {
                if (Mode == CyEModeType.SLAVE)
                {
                    if (scbClk > (CyRanges.SLAVE_FSCB_MIN_100KBPS - CyRanges.EPS) &&
                        scbClk < (CyRanges.SLAVE_FSCB_MIN_400KBPS + CyRanges.EPS))
                    {
                        actualDataRate = CyRanges.DATA_RATE_100;
                    }
                    else if (scbClk < (CyRanges.SLAVE_FSCB_MAX_400KBPS + CyRanges.EPS))
                    {
                        actualDataRate = CyRanges.DATA_RATE_400;
                    }
                    else if (scbClk > (CyRanges.SLAVE_FSCB_MIN_1000KBPS - CyRanges.EPS) &&
                             scbClk < (CyRanges.SLAVE_FSCB_MAX_1000KBPS + CyRanges.EPS))
                    {
                        actualDataRate = CyRanges.DATA_RATE_1000;
                    }
                    else
                    {
                    }

                    // Check if actual data rate is not less than requested
                    if ((ClockFromTerm == false) && (DataRate > actualDataRate))
                    {
                        err = new CyCustErr((int)CyEDataRateErrorID.WARNING_SLAVE_DR_NOT_MATCH, Resources.SlaveDataRateWarning);
                    }
                }
                else
                {
                    // Get SCB clock frequency in kHz, discard Hz
                    uint scbClkKHz = (uint)Math.Truncate(scbClk);

                    // Get actual data rate in Hz
                    actualDataRate = scbClkKHz / ovsFactor;

                    // Check if actual data rate is not less than requested
                    if (ClockFromTerm)
                    {
                        if (actualDataRate > CyRanges.DATA_RATE_MAX)
                        {
                            err = new CyCustErr((int)CyEDataRateErrorID.ERROR_MASTER_DR_ABOVE_MAX,
                                String.Format(Resources.MasterDataRateAboveMax, CyRanges.DATA_RATE_MIN, CyRanges.DATA_RATE_MAX));
                        }
                    }
                    else
                    {
                        if (DataRate < actualDataRate)
                        {
                            err = new CyCustErr((int)CyEDataRateErrorID.WARNING_MASTER_DR_NOT_MATCH, Resources.MasterDataRateWarning);
                        }
                        else if (DataRate > actualDataRate)
                        {
                            err = new CyCustErr((int)CyEDataRateErrorID.NOTE_MASTER_DR_NOT_MATCH, Resources.MasterDataRateNote);
                        }
                        
                        else 
                        {
                            // Do nothing if actualDataRate equal to DataRate
                        }
                    }
                }
            }
            else
            {
                err = new CyCustErr((int)CyEDataRateErrorID.UNKNOWN_CLK, Resources.UnknownClkFreq);
            }

            return err;
        }
        #endregion

        #region Oversampling calculation
        /// <summary>
        /// Calculates auto oversampling.
        /// </summary>
        /// <param name="lowPhase">Calculated oversampling low value.</param>
        /// <param name="highPhase">Calculated oversampling high value.</param>
        /// <returns>Indicated whether clock was read successfully.</returns>
        public bool GetAutoOversamplingLowHigh(out byte lowPhase, out byte highPhase)
        {
            bool isScbClkvalid = (GetClockKhz() > 0);

            // Do all calculations in the Hz
            uint desiredDataRate = (uint)DataRate;
            uint actualDataRate;
            
            uint scbclk;
            uint period;

            uint sclLow;
            uint sclHigh;

            // Assign return values
            lowPhase = 0;
            highPhase = 0;

            // Check if there is a valid scb clock
            if (GetClockKhz() > 0)
            {
                // Get oversample Low and High from the table
                if (DataRate <= CyRanges.DATA_RATE_100)
                {
                    sclLow = CyRanges.SCL_LOW_IDEAL_100KBPS;
                    sclHigh = CyRanges.SCL_HIGH_IDEAL_100KBPS;
                }
                else if (DataRate <= CyRanges.DATA_RATE_400)
                {
                    sclLow = CyRanges.SCL_LOW_IDEAL_400KBPS;
                    sclHigh = CyRanges.SCL_HIGH_IDEAL_400KBPS;
                }
                else
                {
                    sclLow = CyRanges.SCL_LOW_IDEAL_1000KBPS;
                    sclHigh = CyRanges.SCL_HIGH_IDEAL_1000KBPS;
                }


                // Get scb clock in Hz
                scbclk = (uint)Math.Truncate(GetClockKhz() * 1000);

                // Get period in ns 
                period = 1000000000 / scbclk;

                // Get low phase minimum value for the provided clock
                lowPhase = (byte) (sclLow / period);
                if (lowPhase < CyRanges.OVS_FACTOR_LOW_MAX)
                {
                    while (((period * lowPhase) < sclLow) && (lowPhase < CyRanges.OVS_FACTOR_LOW_MAX))
                    {
                        ++lowPhase;
                    }
                }
                else
                {
                    lowPhase = (byte) CyRanges.OVS_FACTOR_LOW_MAX;
                }

                // Get high phase minimum value for the provided clock
                highPhase = (byte) (sclHigh / period);
                if (highPhase < CyRanges.OVS_FACTOR_HIGH_MAX)
                {
                    while (((period * highPhase) < sclHigh) && (highPhase < CyRanges.OVS_FACTOR_HIGH_MAX))
                    {
                        ++highPhase;
                    }
                }
                else
                {
                    highPhase = (byte)CyRanges.OVS_FACTOR_HIGH_MAX;
                }

                // Get SCB clock frequency in kHz
                scbclk /= 1000;

                // Get actuald data rate
                actualDataRate = (uint)(scbclk / (lowPhase + highPhase));

                int idx = 0;
                while ((actualDataRate > desiredDataRate) && 
                        ((lowPhase + highPhase) < CyRanges.OVS_FACTOR_MAX))
                {
                    // Updated OVS Low and High. Start from Low.
                    if ((idx % 2) == 0)
                    {
                        if (lowPhase < CyRanges.OVS_FACTOR_LOW_MAX)
                            lowPhase++;
                    }
                    else
                    {
                        if (highPhase < CyRanges.OVS_FACTOR_LOW_MAX)
                            highPhase++;
                    }
                    idx++;

                    // Get actual data rate 
                    actualDataRate = (uint)(scbclk / (lowPhase + highPhase));
                }
            }

            return (isScbClkvalid);
        }
        #endregion
    }
}
