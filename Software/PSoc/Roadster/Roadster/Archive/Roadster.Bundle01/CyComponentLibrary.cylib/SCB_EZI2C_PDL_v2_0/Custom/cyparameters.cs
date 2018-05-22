/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Diagnostics;
using CyDesigner.Toolkit;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;

namespace SCB_EZI2C_PDL_v2_0
{
    #region Component Parameters Names
    public class CyParamNames
    {
        public const string DATA_RATE = "DataRate";
        public const string CLOCK_FROM_TERM = "ClockFromTerm";

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

        public const double EPS = 1E-5;

        public class CyTolerance
        {
            public const double DEFAULT = 5;
            public const double ZERO_ACCURACY = 0;
            public const double PLUS_MAX = 1000;
            public const double MINUS_MAX = 100;
        }
    }
    #endregion

    #region Component Enums
    public enum CyEToleranceMode { MINUS_TOLERANCE = 0, PLUS_TOLERANCE = 1 };
    #endregion

    public class CyParameters
    {
        #region Enums
        public enum CyEClockErrorID { UNKNOWN_CLK = 1, BELOW_MIN_CLK = 2, IN_GAP_CLK = 3, ABOVE_MAX = 4};
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
        /// <summary>
        /// Indicates whether it is allowed to edit the parameters.
        /// </summary>
        public bool EditMode { get; set; }

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
        public UInt16 DataRate
        {
            get { return GetValue<UInt16>(CyParamNames.DATA_RATE); }
        }

        public bool ClockFromTerm
        {
            get { return GetValue<bool>(CyParamNames.CLOCK_FROM_TERM); }
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
        public CyCustErr GetActualDataRate(out uint actualDataRate)
        {
            actualDataRate = 0;
            CyCustErr err  = CyCustErr.OK;
            double scbClk = GetClockKhz();

            if (CyClock.IsFrequencyKnown(scbClk))
            {
                if (scbClk < (CyRanges.SLAVE_FSCB_MIN_100KBPS - CyRanges.EPS))
                {
                    // Clock frequency is less than 1.55MHz
                    err = new CyCustErr((int) CyEClockErrorID.BELOW_MIN_CLK, 
                                String.Format(Resources.ClockTooLowError, CyRanges.SLAVE_FSCB_MIN_100KBPS_MHZ));
                }
                else if (scbClk < (CyRanges.SLAVE_FSCB_MIN_400KBPS + CyRanges.EPS))
                {
                    actualDataRate = CyRanges.DATA_RATE_100;
                }
                else if (scbClk < (CyRanges.SLAVE_FSCB_MAX_400KBPS + CyRanges.EPS))
                {
                    actualDataRate = CyRanges.DATA_RATE_400;
                }
                else if (scbClk < (CyRanges.SLAVE_FSCB_MIN_1000KBPS - CyRanges.EPS))
                {
                    // Clock frequency is in the gap between 400kpbs and 1000 kpbs: 15.38 - 15.84 MHz
                    err = new CyCustErr((int) CyEClockErrorID.ABOVE_MAX, 
                                String.Format(Resources.ClockInGapError, CyRanges.SLAVE_FSCB_MAX_400KBPS_MHZ, 
                                 CyRanges.SLAVE_FSCB_MIN_1000KBPS_MHZ));
                }
                else if (scbClk < (CyRanges.SLAVE_FSCB_MAX_1000KBPS + CyRanges.EPS))
                {
                    actualDataRate = CyRanges.DATA_RATE_1000;
                }
                else
                {
                    // Clock frequency above max supported: 89MHz
                    err = new CyCustErr((int)CyEClockErrorID.ABOVE_MAX,
                                String.Format(Resources.ClockOutOfRangeError, CyRanges.SLAVE_FSCB_MAX_1000KBPS_MHZ));
                }
            }
            else
            {
                err = new CyCustErr((int)CyEClockErrorID.UNKNOWN_CLK, "Cannot get clock frequency");
            }

            return err;
        }
        #endregion
    }
}
