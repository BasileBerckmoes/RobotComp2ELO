/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System;
using System.Collections;
using System.Diagnostics;
using System.Text;

namespace I2S_v2_70
{
    #region Component Parameter Names
    public static class CyParamNames
    {
        // Basic tab parameners
        public const string DIRECTION = "Direction";
        public const string DATA_BITS = "DataBits";
        public const string WORD_SELECT = "WordSelect";

        public const string BIT_RESOLUTION = "StaticBitResolution";
        public const string RX_BYTE_SWAP = "EnableRxByteSwap";
        public const string TX_BYTE_SWAP = "EnableTxByteSwap";

        // Advanced tab parameters
        public const string RX_DATA_INTERLEAVING = "RxDataInterleaving";
        public const string TX_DATA_INTERLEAVING = "TxDataInterleaving";
        public const string RX_DMA_PRESENT = "RxDMA_present";
        public const string TX_DMA_PRESENT = "TxDMA_present";
        public const string INTERRUPT_SOURCE = "InterruptSource";

        public const string RX_NUMBER_OF_CHANNELS = "NumRxChannels";
        public const string TX_NUMBER_OF_CHANNELS = "NumTxChannels";

        public const string RX_CLIP_DETECTION = "EnableClipDetect";
        public const string COMMON_THRESHOLDS = "CommonClipThresholds";
        public const string NEG_THRESHOLDS = "NegThresholds";
        public const string POS_THRESHOLDS = "PosThresholds";

        public const string CLOCK_SYNC_MODE = "ClockSyncMode";
    }
    #endregion

    #region Component Parameter Ranges
    public static class CyParamRanges
    {
        public const int DATA_BITS_MIN = 8;
        public const int DATA_BITS_MAX = 32;

        public const int BYTE_SWAP_DATA_BITS_MIN = 9;
        public const int BYTE_SWAP_DATA_BITS_MAX = 24;
        public const int BYTE_SWAP_WORD_SELECT_PERIOD = 64;

        public static readonly byte[] WordSelectPeriodValues = {16, 32, 48, 64};

        public const int NUM_THRESHOLD = 5;
        public const sbyte MIN_POS_THRESHOLD = 0;
        public const sbyte MAX_POS_THRESHOLD = 127;
        public const sbyte MAX_NEG_THRESHOLD = -1;
        public const sbyte MIN_NEG_THRESHOLD = -128;
        public const sbyte POS_THRESHOLD_DEFAULT = 64;
        public const sbyte NEG_THRESHOLD_DEFAULT = -64;

        public const sbyte NUM_INTERRUPT_BITS = 6;

        public const int DATA_BITS_MULT_8 = 8;
    }
    #endregion

    #region Component Enums
    
    // Enumeration items names correspond to enumerations declared in the symbol

    public enum CyEDirection
    {
        Rx = 1, 
        Tx = 2, 
        Rx_and_Tx = 3
    }

    public enum CyEBitResolution
    {
        Static,
        Dynamic
    }

    public enum CyEDmaPresent
    {
        DMA = 1,
        NO_DMA = 2
    }

    public enum CyEDataInterleaving
    {
        Separate,
        Interleaved
    }

    public enum CyENumberOfChannels
    {
        MONO_LEFT = 0,
        MONO_RIGHT = 1, 
        STEREO = 2,
        CHANNEL_4 = 4, 
        CHANNEL_6 = 6,
        CHANNEL_8 = 8,
        CHANNEL_10 = 10,
    }
    #endregion

    public class CyI2SParameters
    {
        private readonly ICyInstEdit_v1 m_instEdit;
        private readonly ICyInstQuery_v1 m_instQuery;
        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        }

        private CyI2SBasicTab m_generalTab;
        public CyI2SBasicTab GeneralTab
        {
            get { return m_generalTab; }
            set { m_generalTab = value; }
        }

        private CyI2SAdvancedTab m_advancedTab;
        public CyI2SAdvancedTab AdvancedTab
        {
            get { return m_advancedTab; }
            set { m_advancedTab = value; }
        }

        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediatly overwrite parameters with the same values.

        private bool m_globalEditMode = false;
        public bool GlobalEditMode
        {
            get { return m_globalEditMode; }
            set { m_globalEditMode = value; }
        }

        public const string UNSIGNED_PREFIX = "u";
        public const char DATA_SEPARATOR = ',';

        #region Constructor(s)
        public CyI2SParameters(ICyInstEdit_v1 inst)
        {
            this.m_instEdit = inst;
            this.m_instQuery = inst;
        }

        public CyI2SParameters(ICyInstQuery_v1 inst)
        {
            this.m_instEdit = null;
            this.m_instQuery = inst;
        }
        #endregion

        #region Class Properties

        #region General tab parameters
        public CyEDirection Direction
        {
            get { return GetValue<CyEDirection>(CyParamNames.DIRECTION); }
            set { SetValue(CyParamNames.DIRECTION, value); }
        }

        public bool BitResolutionStatic
        {
            get { return GetValue<bool>(CyParamNames.BIT_RESOLUTION); }
            set { SetValue(CyParamNames.BIT_RESOLUTION, value); }
        }

        public byte DataBits
        {
            get { return GetValue<byte>(CyParamNames.DATA_BITS); }
            set { SetValue(CyParamNames.DATA_BITS, value); }
        }

        public byte WordSelectPeriod
        {
            get { return GetValue<byte>(CyParamNames.WORD_SELECT); }
            set { SetValue(CyParamNames.WORD_SELECT, value); }
        }

        public bool RxByteSwap
        {
            get { return GetValue<bool>(CyParamNames.RX_BYTE_SWAP); }
            set { SetValue(CyParamNames.RX_BYTE_SWAP, value); }
        }

        public bool TxByteSwap
        {
            get { return GetValue<bool>(CyParamNames.TX_BYTE_SWAP); }
            set { SetValue(CyParamNames.TX_BYTE_SWAP, value); }
        }
        #endregion

        #region Advanced tab parameters
        public CyENumberOfChannels RxNumChannels
        {
            get { return GetValue<CyENumberOfChannels>(CyParamNames.RX_NUMBER_OF_CHANNELS); }
            set { SetValue(CyParamNames.RX_NUMBER_OF_CHANNELS, value); }
        }

        public CyENumberOfChannels TxNumChannels
        {
            get { return GetValue<CyENumberOfChannels>(CyParamNames.TX_NUMBER_OF_CHANNELS); }
            set { SetValue(CyParamNames.TX_NUMBER_OF_CHANNELS, value); }
        }

        public CyEDataInterleaving RxDataInterleaving
        {
            get { return GetValue<CyEDataInterleaving>(CyParamNames.RX_DATA_INTERLEAVING); }
            set { SetValue(CyParamNames.RX_DATA_INTERLEAVING, value); }
        }

        public CyEDataInterleaving TxDataInterleaving
        {
            get { return GetValue<CyEDataInterleaving>(CyParamNames.TX_DATA_INTERLEAVING); }
            set { SetValue(CyParamNames.TX_DATA_INTERLEAVING, value); }
        }

        public CyEDmaPresent RxDMA
        {
            get { return GetValue<CyEDmaPresent>(CyParamNames.RX_DMA_PRESENT); }
            set { SetValue(CyParamNames.RX_DMA_PRESENT, value); }
        }

        public CyEDmaPresent TxDMA
        {
            get { return GetValue<CyEDmaPresent>(CyParamNames.TX_DMA_PRESENT); }
            set { SetValue(CyParamNames.TX_DMA_PRESENT, value); }
        }

        public BitArray InterruptSource
        {
            get { return ByteToBitArray(GetValue<byte>(CyParamNames.INTERRUPT_SOURCE)); }
            set { SetValue(CyParamNames.INTERRUPT_SOURCE, BitArrayToByte(value)); }
        }

        public bool RxClipDetection
        {
            get { return GetValue<bool>(CyParamNames.RX_CLIP_DETECTION); }
            set { SetValue(CyParamNames.RX_CLIP_DETECTION, value); }
        }

        public bool ClockSyncMode
        {
            get { return GetValue<bool>(CyParamNames.CLOCK_SYNC_MODE); }
            set { SetValue(CyParamNames.CLOCK_SYNC_MODE, value); }
        }

        public bool CommonThreshold
        {
            get { return GetValue<bool>(CyParamNames.COMMON_THRESHOLDS); }
            set { SetValue(CyParamNames.COMMON_THRESHOLDS, value); }
        }

        public sbyte[] PosThresholds
        {
            get { return ParseThresholdString(GetValue<string>(CyParamNames.POS_THRESHOLDS), true); }
            set { SetValue(CyParamNames.POS_THRESHOLDS, SByteArrayToString(value)); }
        }

        public sbyte[] NegThresholds
        {
            get { return ParseThresholdString(GetValue<string>(CyParamNames.NEG_THRESHOLDS), false); }
            set { SetValue(CyParamNames.NEG_THRESHOLDS, SByteArrayToString(value)); }
        }
        #endregion

        public bool IsPSoC4
        {
            get { return InstQuery.DeviceQuery.IsPSoC4; }
        }
        #endregion

        #region Getting parameters
        /// <summary>
        /// Load parameter value from the symbol
        /// </summary>
        private T GetValue<T>(string paramName)
        {
            return GetValue<T>(paramName, m_instQuery);
        }

        public static T GetValue<T>(string paramName, ICyInstQuery_v1 instQuery)
        {
            if (instQuery == null)
                return default(T);

            if (instQuery.ContainsParam(paramName) == false)
            {
                Debug.Fail(String.Format(Properties.Resources.ErrorParamName, paramName));
                return default(T);
            }

            CyCompDevParam prm = instQuery.GetCommittedParam(paramName);
            T value = default(T);
            CyCustErr err = CyCustErr.OK;
            if (typeof(T).BaseType == typeof(Enum))
            {
                err = prm.TryGetValueAs<T>(out value);
                if ((err == null) || (err.IsOK == false) || (Enum.IsDefined(typeof(T), value) == false))
                {
                    value = (T)Enum.GetValues(typeof(T)).GetValue(0);
                    err = CyCustErr.OK;
                }
            }
            else
                err = prm.TryGetValueAs<T>(out value);
            if (err != null && err.IsOK)
            {
                return value;
            }
            else
            {
                return default(T);
            }
        }
        #endregion

        #region Setting parameters
        /// <summary>
        /// Save parameter value in the symbol
        /// </summary>
        private void SetValue<T>(string paramName, T value)
        {
            if (GlobalEditMode)
            {
                SetValue(m_instEdit, paramName, value);
            }
        }

        public static CyCustErr SetValue<T>(ICyInstEdit_v1 instEdit, string paramName, T value)
        {
            if (instEdit == null)
            {
                return CyCustErr.OK;
            }

            string valueToSet = value.ToString();
           
            if (value is bool)
                valueToSet = valueToSet.ToLower();
            if (value is byte || value is UInt16 || value is UInt32 || value is UInt64)
                valueToSet += "u";
            
            if (instEdit.SetParamExpr(paramName, valueToSet) && instEdit.CommitParamExprs())
            {
                return CyCustErr.OK;
            }

            CyCompDevParam param = instEdit.GetCommittedParam(paramName);
            return param.ErrorCount > 0 ? new CyCustErr(param.ErrorMsgs) : CyCustErr.OK;
        }
        #endregion

        #region Conversions
        private string SByteArrayToString(sbyte[] data)
        {
            StringBuilder dataString = new StringBuilder();
            for (int i = 0; i < data.Length; i++)
            {
                dataString.Append(data[i].ToString());
                if (data[i] >= 0)
                {
                    dataString.Append(UNSIGNED_PREFIX);
                }
                dataString.Append(DATA_SEPARATOR + " ");
            }
            return dataString.ToString().TrimEnd(DATA_SEPARATOR, ' ');
        }

        private sbyte[] ParseThresholdString(string dataString, bool isPositive)
        {
            sbyte[] data = new sbyte[CyParamRanges.NUM_THRESHOLD];
            if (String.IsNullOrEmpty(dataString))
                return data;

            string[] splitData = dataString.Split(DATA_SEPARATOR);
            for (int i = 0; i < Math.Min(data.Length, splitData.Length); i++)
            {
                try
                {
                    data[i] = Convert.ToSByte(splitData[i].Replace(UNSIGNED_PREFIX, String.Empty).Trim());
                }
                catch
                {
                    Debug.Fail(String.Empty);
                }
            }
            for (int i = Math.Min(data.Length, splitData.Length); i < data.Length; i++)
            {
                data[i] = isPositive ? CyParamRanges.POS_THRESHOLD_DEFAULT : CyParamRanges.NEG_THRESHOLD_DEFAULT;
            }
            return data;
        }

        private BitArray ByteToBitArray(byte value)
        {
            BitArray bitArray = new BitArray(CyParamRanges.NUM_INTERRUPT_BITS);
            for (int i = 0; i < CyParamRanges.NUM_INTERRUPT_BITS; i++)
            {
                bitArray[i] = (value & (1 << i)) > 0;
            }
            return bitArray;
        }

        private byte BitArrayToByte(BitArray bitArray)
        {
            byte value = 0;
            for (int i = 0; i < CyParamRanges.NUM_INTERRUPT_BITS; i++)
            {
                if (bitArray[i])
                    value |= (byte)(1 << i);
            }
            return value;
        }
        #endregion Conversions
    }
}
