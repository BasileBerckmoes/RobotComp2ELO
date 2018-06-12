/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using CyDesigner.Extensions.Gde;
using System.ComponentModel;
using CyDesigner.Extensions.Common;
using System.Diagnostics;
using DMA_Channel_P4_v1_0.Tabs;

namespace DMA_Channel_P4_v1_0
{
    #region Component Enums
    public enum CyEDataSizeType
    {
        [Description("Byte")]
        BYTE,

        [Description("Halfword (2 bytes)")]
        HALFWORD,

        [Description("Word (4 bytes)")]
        WORD
    }

    public enum CyESrcDstTransferSize
    {
        [Description("Element to element")]
        ELEMENT_ELEMENT,

        [Description("Element to word")]
        ELEMENT_WORD,
        
        [Description("Word to element")]
        WORD_ELEMENT,

        [Description("Word to word")]
        WORD_WORD
    }

    public enum CyETransferMode
    {
        [Description("Single data element")]
        SINGLE_DATA_ELEMENT,

        [Description("Entire descriptor")]
        ENTIRE_DESCRIPTOR,

        [Description("Entire descriptor chain")]
        ENTIRE_DESCRIPTOR_CHAIN
    }

    public enum CyETriggerType
    {
        [Description("Pulse – Standard width")]
        PULSE,

        [Description("Level sensitive – Wait 4 SYSCLK")]
        LEVEL_FOUR,

        [Description("Level sensitive – Wait 8 SYSCLK")]
        LEVEL_EIGHT,

        [Description("Pulse – Unknown width")]
        LEVEL_UNKNOWN
    }
    #endregion

    public class CyParameters
    {
        #region Parameters Names
        //Channel
        public const string P_CHANNELPRIORITY = "ChanPriority";
        public const string P_ENABLETRIN = "EnableTrIn";
        public const string P_TDNUM = "TdNum";

        //Descriptors 0-1
        public readonly string[] P_INVALIDATE = new string[2] { "InvalidateTd0", "InvalidateTd1" };
        public readonly string[] P_CHAINTO = new string[2] { "Td0ChainToTd1", "Td1ChainToTd0" };
        public readonly string[] P_DATASIZE = new string[2] { "Td0DataSize", "Td1DataSize" };
        public readonly string[] P_GENERATEIRQ = new string[2] { "Td0GenerateIrq", "Td1GenerateIrq" };
        public readonly string[] P_INCREMENTDSTADDRESS = new string[2] { "Td0IncrementDstAddress", 
            "Td1IncrementDstAddress" };
        public readonly string[] P_INCREMENTSRCADDRESS = new string[2] { "Td0IncrementSrcAddress", 
            "Td1IncrementSrcAddress" };
        public readonly string[] P_ISPREEMTABLE = new string[2] { "Td0IsPreemptable", "Td1IsPreemptable" };
        public readonly string[] P_NUMDATAELEMENTS = new string[2] { "Td0NumDataElements", "Td1NumDataElements" };
        public readonly string[] P_SRCDSTTRANSFERSIZE = new string[2] { "Td0SrcDstTransferSize", 
            "Td1SrcDstTransferSize" };
        public readonly string[] P_TRANSFERMODE = new string[2] { "Td0TransferMode", "Td1TransferMode" };
        public readonly string[] P_TRIGGERTYPE = new string[2] { "Td0TriggerType", "Td1TriggerType" };

        #endregion

        #region Class members
        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyInstEdit_v1 m_instEdit;
        private ICyTabbedParamEditor m_editor;

        // When parameters are first obtained, this variable is false, which means that assigned
        // values to form the controls will not immediately overwrite parameters with the same values.
        private bool m_globalEditMode = false;

        // References to tabs used in the customizer
        public CyDescriptorTab m_descriptor0Tab;
        public CyDescriptorTab m_descriptor1Tab;
        public CyGeneralTab m_generalTab;
        #endregion

        #region Constructor(s)
        private CyParameters(ICyInstQuery_v1 instQuery, ICyInstEdit_v1 instEdit)
        {
            m_instQuery = instQuery;
            m_instEdit = instEdit;
        }

        public CyParameters(ICyInstQuery_v1 instQuery)
            : this(instQuery, null)
        {
        }

        public CyParameters(ICyInstEdit_v1 instEdit)
            : this(instEdit, instEdit)
        {
        }
        #endregion

        #region Class properties
        public ICyTabbedParamEditor Editor
        {
            get { return m_editor; }
            set { m_editor = value; }
        }

        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        }

        public bool GlobalEditMode
        {
            get { return m_globalEditMode; }
            set { m_globalEditMode = value; }
        }
        
        public byte ChanPriority
        {
            get { return GetValue<byte>(P_CHANNELPRIORITY); }
            set { SetValue(P_CHANNELPRIORITY, value); }
        }
        
        public bool EnableTrIn
        {
            get { return GetValue<bool>(P_ENABLETRIN); }
            set { SetValue(P_ENABLETRIN, value); }
        }

        public byte TdNum
        {
            get { return GetValue<byte>(P_TDNUM); }
            set { SetValue(P_TDNUM, value); }
        }
        #endregion

        #region Getting Parameters functions
        public CyEDataSizeType GetDataSize(int id)
        {
            return GetValue<CyEDataSizeType>(P_DATASIZE[id]);
        }

        public CyESrcDstTransferSize GetSrcDstTransferSize(int id)
        {
            return GetValue<CyESrcDstTransferSize>(P_SRCDSTTRANSFERSIZE[id]);
        }

        public CyETransferMode GetTransferMode(int id)
        {
            return GetValue<CyETransferMode>(P_TRANSFERMODE[id]);
        }

        public CyETriggerType GetTriggerType(int id)
        {
            return GetValue<CyETriggerType>(P_TRIGGERTYPE[id]);
        }

        public bool GetInvalidate(int id)
        {
            return GetValue<bool>(P_INVALIDATE[id]);
        }

        public bool GetChainTo(int id)
        {
            return GetValue<bool>(P_CHAINTO[id]);
        }

        public bool GetGenerateIrq(int id)
        {
            return GetValue<bool>(P_GENERATEIRQ[id]);
        }

        public bool GetIncrementDstAddress(int id)
        {
            return GetValue<bool>(P_INCREMENTDSTADDRESS[id]);
        }

        public bool GetIncrementSrcAddress(int id)
        {
            return GetValue<bool>(P_INCREMENTSRCADDRESS[id]);
        }

        public bool GetIsPreemtable(int id)
        {
            return GetValue<bool>(P_ISPREEMTABLE[id]);
        }

        public UInt32 GetNumDataElements(int id)
        {
            return GetValue<UInt32>(P_NUMDATAELEMENTS[id]);
        }

        #endregion

        #region Setting Parameters functions
        public void SetDataSize(int id, CyEDataSizeType value)
        {
            SetValue(P_DATASIZE[id], value);
        }

        public void SetSrcDstTransferSize(int id, CyESrcDstTransferSize value)
        {
            SetValue(P_SRCDSTTRANSFERSIZE[id], value); 
        }

        public void SetTransferMode(int id, CyETransferMode value)
        {
            SetValue(P_TRANSFERMODE[id], value); 
        }

        public void SetTriggerType(int id, CyETriggerType value)
        {
            SetValue(P_TRIGGERTYPE[id], value); 
        }

        public void SetInvalidate(int id, bool value)
        {
            SetValue(P_INVALIDATE[id], value);
        }
        
        public void SetChainTo(int id, bool value)
        {
            SetValue(P_CHAINTO[id], value);
        }
        
        public void SetGenerateIrq(int id, bool value)
        {
            SetValue(P_GENERATEIRQ[id], value);
        }
        
        public void SetIncrementDstAddress(int id, bool value)
        {
            SetValue(P_INCREMENTDSTADDRESS[id], value);
        }
        
        public void SetIncrementSrcAddress(int id, bool value)
        {
            SetValue(P_INCREMENTSRCADDRESS[id], value);
        }
        
        public void SetIsPreemtable(int id, bool value)
        {
            SetValue(P_ISPREEMTABLE[id], value);
        }

        public void SetNumDataElements(int id, UInt32 value)
        {
            SetValue(P_NUMDATAELEMENTS[id], value);
        }
        #endregion

        #region Getting Parameter
        private T GetValue<T>(string paramName)
        {
            if (m_instQuery == null) return default(T);
            T value;
            CyCustErr err = m_instQuery.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            return (err != null && err.IsOK) ? value : default(T);
        }
        #endregion

        #region Setting Parameter
        private void SetValue<T>(string paramName, T value)
        {                             
            if (m_instEdit != null && m_globalEditMode)
            {
                string valueToSet = (value == null) ? String.Empty : value.ToString();
                if (value is bool)
                    valueToSet = valueToSet.ToLower();
                if ((value is byte) || (value is UInt16) || (value is UInt32) || (value is UInt64))
                    valueToSet += "u";
                if (m_instEdit.SetParamExpr(paramName, valueToSet))
                {
                    m_instEdit.CommitParamExprs();
                }
            }
        }
        #endregion

        #region Class functions
        public void UpdateTabVisibility()
        {
            if ((m_descriptor0Tab == null) || (m_descriptor1Tab == null) || (m_generalTab == null))
                return;

            if (TdNum == 2)
            {
                m_editor.ShowCustomPage(Resources.Descriptor1TabName);
            }
            else if (TdNum == 1)
            {
                m_editor.HideCustomPage(Resources.Descriptor1TabName); 
            }

            m_descriptor0Tab.UpdateTdChanged(TdNum);
        }
        #endregion
    }
}
