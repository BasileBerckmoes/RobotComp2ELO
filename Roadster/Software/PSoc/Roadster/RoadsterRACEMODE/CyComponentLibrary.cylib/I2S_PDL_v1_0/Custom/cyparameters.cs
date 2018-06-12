/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using I2S_PDL_v1_0.Utils;

namespace I2S_PDL_v1_0
{
    #region Component Parameters Names
    public class CyParamNames
    {
        // common parameters
        public const string CLOCK_FROM_TERM = "ExtClk";
        public const string CLOCK_DIV = "ClockDiv";

        // rx parameters
        public const string RX_CHANNEL_LENGTH = "RxChannelLength";
        public const string RX_DMA_TRIGGER = "RxDmaTrigger";
        public const string RX_ENABLED = "RxEnabled";
        public const string RX_WORD_LENGTH = "RxWordLength";
        public const string RX_BIT_EXTENSION = "RxBitExtension";
        public const string RX_FIFO_TRIGGER_LEVEL = "RxFifoTriggerLevel";
        // rx interrupts
        public const string RX_FULL_INT = "RxFull";
        public const string RX_NOT_EMPTY_INT = "RxNotEmpty";
        public const string RX_OVERFLOW_INT = "RxOverFlow";
        public const string RX_TRIGGER_INT = "RxTrig";
        public const string RX_UNDERFLOW_INT = "RxUnderFlow";

        // tx parameters
        public const string TX_CHANNEL_LENGTH = "TxChannelLength";
        public const string TX_DMA_TRIGGER = "TxDmaTrigger";
        public const string TX_ENABLED = "TxEnabled";
        public const string TX_WORD_LENGTH = "TxWordLength";
        public const string TX_FIFO_TRIGGER_LEVEL = "TxFifoTriggerLevel";
        public const string TX_OVERHEAD_VALUE = "TxOverheadValue";
        // tx interrupts
        public const string TX_EMPTY_INT = "TxEmpty";
        public const string TX_NOT_FULL_INT = "TxNotFull";
        public const string TX_OVERFLOW_INT = "TxOverFlow";
        public const string TX_TRIGGER_INT = "TxTrig";
        public const string TX_UNDERFLOW_INT = "TxUnderFlow";
    }
    #endregion

    public class CyParameters
    {
        #region Private fields
        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyInstEdit_v1 m_instEdit;
        private readonly ICyTerminalQuery_v1 m_termQuery;
        #endregion

        #region Events declaration
        /// <summary>
        /// An event that clients can use to be notified whenever the PSoC Creator design updates.
        /// </summary>
        public event EventHandler DesignUpdates;
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
        /// During first getting of parameters this variable is false, what means that assigning
        /// values to form controls will not immediately overwrite parameters with the same values.
        /// </summary>
        public bool GlobalEditMode { get; set; }

        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        }

        public ICyTerminalQuery_v1 TermQuery
        {
            get { return m_termQuery; }
        }

        //
        // Common parameters properties
        //
        public bool ClockFromTerminal
        {
            get { return GetValue<bool>(CyParamNames.CLOCK_FROM_TERM); }
            set { SetValue(CyParamNames.CLOCK_FROM_TERM, value); }
        }

        public int ClockDivider
        {
            get { return GetValue<int>(CyParamNames.CLOCK_DIV); }
            set { SetValue(CyParamNames.CLOCK_DIV, value); }
        }

        //
        // TX parameters properties
        //
        public bool TxEnabled
        {
            get { return GetValue<bool>(CyParamNames.TX_ENABLED); }
            set { SetValue(CyParamNames.TX_ENABLED, value); }
        }

        public CyDataLength TxChannelLength
        {
            get { return GetValue<CyDataLength>(CyParamNames.TX_CHANNEL_LENGTH); }
            set { SetValue(CyParamNames.TX_CHANNEL_LENGTH, value); }
        }

        public CyDataLength TxWordLength
        {
            get { return GetValue<CyDataLength>(CyParamNames.TX_WORD_LENGTH); }
            set { SetValue(CyParamNames.TX_WORD_LENGTH, value); }
        }

        public int TxOverheadValue
        {
            get { return GetValue<int>(CyParamNames.TX_OVERHEAD_VALUE); }
            set { SetValue(CyParamNames.TX_OVERHEAD_VALUE, value); }
        }

        public byte TxFifoTriggerLevel
        {
            get { return GetValue<byte>(CyParamNames.TX_FIFO_TRIGGER_LEVEL); }
            set { SetValue(CyParamNames.TX_FIFO_TRIGGER_LEVEL, value); }
        }

        public bool TxDmaTrigger
        {
            get { return GetValue<bool>(CyParamNames.TX_DMA_TRIGGER); }
            set { SetValue(CyParamNames.TX_DMA_TRIGGER, value); }
        }

        public bool TxTriggerInt
        {
            get { return GetValue<bool>(CyParamNames.TX_TRIGGER_INT); }
            set { SetValue(CyParamNames.TX_TRIGGER_INT, value); }
        }

        public bool TxNotFullInt
        {
            get { return GetValue<bool>(CyParamNames.TX_NOT_FULL_INT); }
            set { SetValue(CyParamNames.TX_NOT_FULL_INT, value); }
        }

        public bool TxEmptyInt
        {
            get { return GetValue<bool>(CyParamNames.TX_EMPTY_INT); }
            set { SetValue(CyParamNames.TX_EMPTY_INT, value); }
        }

        public bool TxOverflowInt
        {
            get { return GetValue<bool>(CyParamNames.TX_OVERFLOW_INT); }
            set { SetValue(CyParamNames.TX_OVERFLOW_INT, value); }
        }

        public bool TxUnderflowInt
        {
            get { return GetValue<bool>(CyParamNames.TX_UNDERFLOW_INT); }
            set { SetValue(CyParamNames.TX_UNDERFLOW_INT, value); }
        }

        //
        // RX parameters properties
        //
        public bool RxEnabled
        {
            get { return GetValue<bool>(CyParamNames.RX_ENABLED); }
            set { SetValue(CyParamNames.RX_ENABLED, value); }
        }

        public CyDataLength RxChannelLength
        {
            get { return GetValue<CyDataLength>(CyParamNames.RX_CHANNEL_LENGTH); }
            set { SetValue(CyParamNames.RX_CHANNEL_LENGTH, value); }
        }

        public CyDataLength RxWordLength
        {
            get { return GetValue<CyDataLength>(CyParamNames.RX_WORD_LENGTH); }
            set { SetValue(CyParamNames.RX_WORD_LENGTH, value); }
        }

        public CyBitExtension RxBitExtension
        {
            get { return GetValue<CyBitExtension>(CyParamNames.RX_BIT_EXTENSION); }
            set { SetValue(CyParamNames.RX_BIT_EXTENSION, value); }
        }

        public byte RxFifoTriggerLevel
        {
            get { return GetValue<byte>(CyParamNames.RX_FIFO_TRIGGER_LEVEL); }
            set { SetValue(CyParamNames.RX_FIFO_TRIGGER_LEVEL, value); }
        }

        public bool RxDmaTrigger
        {
            get { return GetValue<bool>(CyParamNames.RX_DMA_TRIGGER); }
            set { SetValue(CyParamNames.RX_DMA_TRIGGER, value); }
        }

        public bool RxTriggerInt
        {
            get { return GetValue<bool>(CyParamNames.RX_TRIGGER_INT); }
            set { SetValue(CyParamNames.RX_TRIGGER_INT, value); }
        }

        public bool RxNotEmptyInt
        {
            get { return GetValue<bool>(CyParamNames.RX_NOT_EMPTY_INT); }
            set { SetValue(CyParamNames.RX_NOT_EMPTY_INT, value); }
        }

        public bool RxFullInt
        {
            get { return GetValue<bool>(CyParamNames.RX_FULL_INT); }
            set { SetValue(CyParamNames.RX_FULL_INT, value); }
        }

        public bool RxOverflowInt
        {
            get { return GetValue<bool>(CyParamNames.RX_OVERFLOW_INT); }
            set { SetValue(CyParamNames.RX_OVERFLOW_INT, value); }
        }

        public bool RxUnderflowInt
        {
            get { return GetValue<bool>(CyParamNames.RX_UNDERFLOW_INT); }
            set { SetValue(CyParamNames.RX_UNDERFLOW_INT, value); }
        }

        //
        // Internal use properties
        //
        public bool IsDeviceRevision2
        {
            get { return false; }
        }
        #endregion

        #region Events
        // Invoke the DesignUpdates event; called whenever PSoC Creator design updates.
        protected virtual void OnDesignUpdates(EventArgs e)
        {
            if (DesignUpdates != null)
                DesignUpdates(this, e);
        }

        public void UpdateDesigns(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            OnDesignUpdates(EventArgs.Empty);
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

        #region Setting Parameters
        public void SetValue<T>(string paramName, T value)
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

            if (value != null)
            {
                string valueToSet = value.ToString();
                if (value is bool)
                    valueToSet = valueToSet.ToLower();
                if (value is byte || value is UInt16 || value is UInt32 || value is UInt64)
                    valueToSet += "u";

                if (instEdit.SetParamExpr(paramName, valueToSet) && instEdit.CommitParamExprs())
                {
                    return CyCustErr.OK;
                }
            }
            CyCompDevParam param = instEdit.GetCommittedParam(paramName);
            return param.ErrorCount > 0 ? new CyCustErr(param.ErrorMsgs) : CyCustErr.OK;
        }
        #endregion
    }

    public class CyEnum<T>
    {
        CyParameters m_prm;
        string m_paramName;

        public event EventHandler<EventArgs> ValueChanged;

        public CyEnum(CyParameters prm, string paramName)
        {
            m_prm = prm;
            m_paramName = paramName;
        }

        /// <summary>
        /// Gets and sets the parameter's value
        /// </summary>
        public T Value
        {
            get
            {
                return m_prm.GetValue<T>(m_paramName);
            }
            set
            {
                m_prm.SetValue<T>(m_paramName, value);
                OnValueChanged(EventArgs.Empty);
            }
        }

        /// <summary>
        /// Gets the enum item description or sets the parameter's value by enum item description.
        /// </summary>
        public string Description
        {
            get
            {
                string res = string.Empty;

                CyCompDevParam param = m_prm.InstQuery.GetCommittedParam(m_paramName);
                if (param != null)
                {
                    m_prm.InstQuery.ResolveEnumParamToDisplay(param, out res);
                }

                return res;
            }
            set
            {
                string enumItemName = m_prm.InstQuery.ResolveEnumDisplayToId(m_paramName, value);

                try
                {
                    Value = (T)Enum.Parse(typeof(T), enumItemName);
                }
                catch { }
            }
        }

        /// <summary>
        /// Gets the array of strings - descriptions of the enumeration that is a type of the parameter.
        /// </summary>
        public string[] EnumDescriptionsList
        {
            get
            {
                return new List<string>(m_prm.InstQuery.GetPossibleEnumValues(m_paramName)).ToArray();
            }
        }

        /// <summary>
        /// Get the enum item description by the specified enum item value.
        /// </summary>
        /// <param name="value">Enum item value</param>
        /// <returns>Enum item description</returns>
        public string GetDescription(T value)
        {
            string res = string.Empty;

            CyCompDevParam prm = m_prm.InstQuery.GetCommittedParam(m_paramName);

            if (prm != null)
            {
                CyCompDevParam newParam = new CyCompDevParam(prm.Name, prm.Expr, prm.ExprType, value.ToString(),
                    prm.TypeName, prm.DefaultExpr, prm.TabName, prm.CategoryName, prm.Description, prm.IsVisible,
                    prm.IsReadOnly, prm.IsHardware, prm.IsFormal, prm.IsDisplayEvaluated, prm.ErrorCount, value,
                    prm.Errors);

                if (newParam != null)
                {
                    m_prm.InstQuery.ResolveEnumParamToDisplay(newParam, out res);
                }
            }

            return res;
        }

        protected virtual void OnValueChanged(EventArgs e)
        {
            EventHandler<EventArgs> handler = ValueChanged;
            if (handler != null)
                handler(this, e);
        }
    }
}
