/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Xml.Serialization;
using System.Collections.Generic;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using DMA_PDL_v2_0.Utils;

namespace DMA_PDL_v2_0
{
    internal class CyParamNames
    {
        internal const string TRIGGER_INPUT = "TRIG_INPUT";
        internal const string TRIGGER_OUTPUT = "TRIG_OUTPUT";
        internal const string CHANNEL_PRIORITY = "CHANNEL_PRIORITY";
        internal const string NUMBER_OF_DESCRIPTOR = "NUM_OF_DESCRIPTORS";
        internal const string PREEMPTABLE = "PREEMPTABLE";
        internal const string DESCRIPTORS_XML_STR = "DESCRIPTORS_XML_STR";
    }
    public delegate void NumberOfDescriptorsEventHandler();
    public delegate void DescriptorNameGUIEventHandler(string oldName, string newName);
    [Serializable]
    [XmlType("DMA_PDL_v2_0")]
    public class CyParameters
    {
        public event NumberOfDescriptorsEventHandler NumberOfDescriptorsChanged;
        public event DescriptorNameGUIEventHandler DescriptorNameGUIChanged;
        #region Private members
        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyInstEdit_v1 m_instEdit;
        #endregion

        #region Constructor(s)
        private CyParameters(ICyInstQuery_v1 instQuery, ICyInstEdit_v1 instEdit)
        {
            m_instQuery = instQuery;
            m_instEdit = instEdit;
            DeSerializeDescriptors();
            UpdateDescriptors(NumberOfDescriptors);
        }

        public CyParameters(ICyInstQuery_v1 instQuery)
            : this(instQuery, null)
        {
        }

        public CyParameters(ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery)
            : this(instEdit, instEdit)
        {
        }
        #endregion

        
        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        }

        /// <summary>
        /// Indicates whether parameters modifying is allowed.
        /// During the first UI update this variable equals to False. This means that 
        /// assigning values to the form controls will not immediately overwrite the 
        /// parameters with the same values.
        /// </summary>
        public bool GlobalEditMode { get; set; }

        #region Properties
        public bool TriggerInput
        {
            get { return GetValue<bool>(CyParamNames.TRIGGER_INPUT); }
            set { SetValue(CyParamNames.TRIGGER_INPUT, value); }
        }

        public bool TriggerOutput
        {
            get { return GetValue<bool>(CyParamNames.TRIGGER_OUTPUT); }
            set { SetValue(CyParamNames.TRIGGER_OUTPUT, value); }
        }

        public int ChannelPriority
        {
            get { return GetValue<int>(CyParamNames.CHANNEL_PRIORITY); }
            set { SetValue(CyParamNames.CHANNEL_PRIORITY, value); }
        }

        internal string GetInstanceName()
        {
            return GetValue<string>("INSTANCE_NAME");
        }

        public byte NumberOfDescriptors
        {
            get { return GetValue<byte>(CyParamNames.NUMBER_OF_DESCRIPTOR); }
            set
            {
                if(value != m_descriptors.Count)
                {
                    UpdateDescriptors(value);
                    NumberOfDescriptorsChanged();
                }
                SetValue(CyParamNames.NUMBER_OF_DESCRIPTOR, value);
            }
        }

        public bool Preemptable
        {
            get { return GetValue<bool>(CyParamNames.PREEMPTABLE); }
            set { SetValue(CyParamNames.PREEMPTABLE, value); }
        }

        public string DescriptorsXML
        {
            get { return GetValue<string>(CyParamNames.DESCRIPTORS_XML_STR); }
            set
            {
                string valueToSet = value.Replace(Environment.NewLine, " ");
                SetValue(CyParamNames.DESCRIPTORS_XML_STR, valueToSet);
            }
        }

        private List<CyDmaDescriptionProperties> m_descriptors;
        [XmlArray("Descriptors")]
        [XmlArrayItem("Descriptor")]
        public List<CyDmaDescriptionProperties> Descriptors
        {
            get
            {
                if (m_descriptors == null)
                {
                    m_descriptors = new List<CyDmaDescriptionProperties>();
                }
                return m_descriptors;
            }
        }
        #endregion

        #region Descriptors methods
        public void SerializeDescriptors()
        {
            string descriptorsXML = CySerializer.Serialize(Descriptors);
            DescriptorsXML = descriptorsXML;
        }

        private void UnsubscribeDescriptorNameEventHandler()
        {
            foreach (CyDmaDescriptionProperties descriptor in Descriptors)
            {
                descriptor.DescriptorNameChange -= new DescriptorNameEventHandler(DescriptorNameChanged);
            }
        }

        private void SubscribeDescriptorNameEventHandler()
        {
            foreach (CyDmaDescriptionProperties descriptor in Descriptors)
            {
                descriptor.DescriptorNameChange += new DescriptorNameEventHandler(DescriptorNameChanged);
            }
        }

        public void DeSerializeDescriptors()
        {
            string descriptorsXML = DescriptorsXML;
            UnsubscribeDescriptorNameEventHandler();
            m_descriptors = CySerializer.Deserialize<List<CyDmaDescriptionProperties>>(descriptorsXML);
            SubscribeDescriptorNameEventHandler();
        }

        private void DescriptorNameChanged(string oldName, string newName)
        {
            DescriptorNameGUIChanged(oldName, newName);
            foreach (CyDmaDescriptionProperties descriptor in Descriptors)
            {
                if (descriptor.ChainToDescriptor == oldName)
                {
                    descriptor.ChainToDescriptor = newName;
                }
            }
        }

        private int AddDescriptor()
        {
            string name = "Descriptor_" + (Descriptors.Count + 1);
            CyDmaDescriptionProperties descriptor = new CyDmaDescriptionProperties();
            descriptor.DescriptorName = name;
            Descriptors.Add(descriptor);
            descriptor.DescriptorNameChange += new DescriptorNameEventHandler(DescriptorNameChanged);
            return (Descriptors.Count - 1);
        }

        public void UpdateDescriptors(int numberOfDescriptors)
        {
            if (numberOfDescriptors < Descriptors.Count)
            {
                for (int i = Descriptors.Count - 1; i >= numberOfDescriptors; i--)
                {
                    Descriptors.Remove(Descriptors[i]);
                }
            }
            for (int i = Descriptors.Count; i < numberOfDescriptors; i++)
            {
                AddDescriptor();
            }
            SerializeDescriptors();
            CyDmaDescriptionProperties.Descriptors = Descriptors;
            if (Descriptors.Count > 0)
            {
                Descriptors[0].FillDescriptorsNameList();
            }
        }
        #endregion

        #region Getting parameters
        /// <summary>
        /// Gets parameter value from the symbol.
        /// </summary>
        private T GetValue<T>(string paramName)
        {
            T value = default(T);
            if (m_instQuery == null) return default(T);
            CyCompDevParam param = m_instQuery.GetCommittedParam(paramName);
            CyCustErr err = (param != null) ? param.TryGetValueAs<T>(out value) : CyCustErr.OK;
            return (err != null && err.IsOK && value != null) ? value : default(T);
        }
        #endregion

        #region Setting Parameters
        /// <summary>
        /// Sets parameter value into the symbol.
        /// </summary>
        private CyCustErr SetValue<T>(string paramName, T value)
        {
            if (GlobalEditMode == false || m_instEdit == null)
                return CyCustErr.OK;

            string valueToSet = String.Empty;
            if (value != null)
            {
                valueToSet = value.ToString();
            }
            if (value is bool)
                valueToSet = valueToSet.ToLower();
            if (m_instEdit.SetParamExpr(paramName, valueToSet))
            {
                m_instEdit.CommitParamExprs();
            }

            CyCompDevParam param = m_instEdit.GetCommittedParam(paramName);
            if (param == null)
            {
                return new CyCustErr("Could not get {0} parameter.", paramName);
            }
            return param.ErrorCount > 0 ? new CyCustErr(param.ErrorMsgs) : CyCustErr.OK;
        }
        #endregion
    }
}
