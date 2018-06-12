/*******************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;
using CyDesigner.Extensions.Common;

namespace MDIO_Interface_v1_20
{
    [Serializable]
    public class CyRegSpace
    {
        public const string DEFAULT_NAME = "REGISTER_SPACE";
        public const ushort DEFAULT_ADDRESS_START = 0x8000;
        public const ushort DEFAULT_ADDRESS_END = 0x8004;

        #region Serializable fields
        // These fields should not be used by external classes, use properties instead
        [XmlElement("Name")]
        public string m_name;
        [XmlElement("StartAddress")]
        public ushort? m_startAddress;
        [XmlElement("EndAddress")]
        public ushort? m_endAddress;
        [XmlElement("DataWidth")]
        public CyEDataWidthType m_dataWidth;
        [XmlElement("MemoryType")]
        public CyEMemoryType m_memoryType;
        [XmlElement("ConfigType")]
        public CyEMemoryType m_configType;
        [XmlElement("AC")]
        public List<CyRegAddress> m_addressConfig;
        [XmlIgnore]
        public int m_paramIndex;
        #endregion

        // Array to keep already input data after changing Start-End address
        private Dictionary<ushort, CyRegAddress> m_tmpAddressConfig;

        #region Class properties
        [XmlIgnore]
        public string Name
        {
            get { return m_name; }
            set { m_name = value; }
        }
        [XmlIgnore]
        public ushort? StartAddress
        {
            get { return m_startAddress; }
            set
            {
                m_startAddress = value;
                UpdateAddressConfigTable();
            }
        }
        [XmlIgnore]
        public ushort? EndAddress
        {
            get { return m_endAddress; }
            set
            {
                m_endAddress = value;
                UpdateAddressConfigTable();
            }
        }
        [XmlIgnore]
        public CyEDataWidthType DataWidth
        {
            get { return m_dataWidth; }
            set
            {
                m_dataWidth = value;
                UpdateAddressConfigTable();
            }
        }
        [XmlIgnore]
        public CyEMemoryType MemoryType
        {
            get { return m_memoryType; }
            set { m_memoryType = value; }
        }
        [XmlIgnore]
        public CyEMemoryType ConfigType
        {
            get { return m_configType; }
            set { m_configType = value; }
        }
        [XmlIgnore]
        public List<CyRegAddress> AddressConfig
        {
            get { return m_addressConfig; }
        }
        #endregion

        #region Constructor(s)
        public CyRegSpace()
        {
            m_addressConfig = new List<CyRegAddress>(UInt16.MaxValue);
            m_tmpAddressConfig = new Dictionary<ushort, CyRegAddress>(UInt16.MaxValue);
            m_name = DEFAULT_NAME;
            m_dataWidth = CyEDataWidthType.BIT_8;
            m_memoryType = CyEMemoryType.SRAM;
            m_configType = CyEMemoryType.FLASH;
        }
        public CyRegSpace(string name)
            : this()
        {
            m_name = name;
            m_startAddress = DEFAULT_ADDRESS_START;
            m_endAddress = DEFAULT_ADDRESS_END;
            UpdateAddressConfigTable();
        }
        public CyRegSpace(int paramIndex, ushort startAddress, ushort endAddress, CyEDataWidthType dataWidth)
            : this()
        {
            m_name = GetDefaultName(paramIndex + 1);
            m_startAddress = startAddress;
            m_endAddress = endAddress;
            m_dataWidth = dataWidth;
            m_paramIndex = paramIndex;
            UpdateAddressConfigTable();
        }
        #endregion

        #region Methods
        public void InitGenericData(int parameterIndex)
        {
            this.m_paramIndex = parameterIndex;
            for (ushort i = 0; i < this.AddressConfig.Count; i++)
            {
                this.AddressConfig[i].m_parentObject = this;
                this.AddressConfig[i].m_address = (ushort)(this.StartAddress.Value + i);
            }
        }

        public static string GetDefaultName(int index)
        {
            return String.Format("{0}_{1}", DEFAULT_NAME, index);
        }

        private void UpdateAddressConfigTable()
        {
            // Do not do anything if one of the addresses is invalid or start address is greater than end address
            if (m_startAddress < CyParamRanges.START_END_ADDRESS_MIN ||
                m_startAddress > CyParamRanges.START_END_ADDRESS_MAX ||
                m_endAddress < CyParamRanges.START_END_ADDRESS_MIN ||
                m_endAddress > CyParamRanges.START_END_ADDRESS_MAX ||
                m_startAddress > m_endAddress)
            {
                return;
            }
            // Start address was increased
            while (m_addressConfig.Count > 0 && m_addressConfig[0].Address < StartAddress)
            {
                if (m_tmpAddressConfig.ContainsKey(m_addressConfig[0].Address))
                    m_tmpAddressConfig.Remove(m_addressConfig[0].Address);
                m_tmpAddressConfig.Add(m_addressConfig[0].Address, m_addressConfig[0]);
                m_addressConfig.RemoveAt(0);
            }
            // End address was increased
            while (m_addressConfig.Count > 0 && m_addressConfig[m_addressConfig.Count - 1].Address < EndAddress)
            {
                ushort key = (ushort)(m_addressConfig[m_addressConfig.Count - 1].Address + 1);
                CyRegAddress newReg = new CyRegAddress(key, this);
                if (m_tmpAddressConfig.ContainsKey(key))
                {
                    newReg = m_tmpAddressConfig[key];
                }
                m_addressConfig.Add(newReg);
            }
            // End address was decreased
            while (m_addressConfig.Count > 0 && m_addressConfig[m_addressConfig.Count - 1].Address > EndAddress)
            {
                ushort key = m_addressConfig[m_addressConfig.Count - 1].Address;
                if (m_tmpAddressConfig.ContainsKey(key))
                    m_tmpAddressConfig.Remove(key);
                m_tmpAddressConfig.Add(key, m_addressConfig[m_addressConfig.Count - 1]);
                m_addressConfig.RemoveAt(m_addressConfig.Count - 1);
            }
            // Start address was decreased
            while (m_addressConfig.Count > 0 && m_addressConfig[0].Address > StartAddress)
            {
                CyRegAddress newReg = new CyRegAddress((ushort)(m_addressConfig[0].Address - 1), this);
                ushort key = newReg.Address;
                if (m_tmpAddressConfig.ContainsKey(key))
                {
                    newReg = m_tmpAddressConfig[key];
                }
                m_addressConfig.Insert(0, newReg);
            }
            // Create default rows if table does not contain rows
            if (m_addressConfig.Count == 0)
            {
                for (ushort? i = StartAddress; i <= EndAddress; i++)
                {
                    CyRegAddress newReg = new CyRegAddress(i.Value, this);
                    m_addressConfig.Add(newReg);
                }
            }
        }
        #endregion
    }

    [Serializable]
    public class CyRegSpaceConfig
    {
        public const int MAX_REG_SPACE_NUM = 8;
        [XmlElement("EnableAuxBits")]
        public bool m_enableAuxBits;
        [XmlElement("RegisterSpace")]
        public List<CyRegSpace> m_regSpaces;

        #region Constructor(s)
        public CyRegSpaceConfig()
        {
            m_regSpaces = new List<CyRegSpace>();
        }
        #endregion

        #region Methods
        public string GetNextDefaultName()
        {
            int currentIndex = 0;
            bool exists = true;
            string name = CyRegSpace.GetDefaultName(currentIndex);
            while (currentIndex == 0 || exists == true)
            {
                currentIndex++;
                exists = false;
                name = CyRegSpace.GetDefaultName(currentIndex);
                for (int i = 0; i < m_regSpaces.Count; i++)
                {
                    if (m_regSpaces[i].Name == name)
                    {
                        exists = true;
                    }
                }
            }
            return name;
        }

        public List<CyCustErr> GetRegSpacesErrors()
        {
            List<CyCustErr> result = new List<CyCustErr>();
            System.Text.StringBuilder sb = new System.Text.StringBuilder();
            for (int regSpaceIndex = 0; regSpaceIndex < m_regSpaces.Count; regSpaceIndex++)
            {
                CyRegSpace regSpace = m_regSpaces[regSpaceIndex];
                // Check start and end addresses
                if (regSpace.StartAddress.HasValue == false)
                {
                    result.Add(new CyCustErr(String.Format(
                                             Resources.RegSpaceStartAddressError, m_regSpaces[regSpaceIndex].Name)));
                }
                if (regSpace.EndAddress.HasValue == false)
                {
                    result.Add(new CyCustErr(String.Format(
                                             Resources.RegSpaceEndAddressError, m_regSpaces[regSpaceIndex].Name)));
                }

                // Check table
                for (int addrConfigIndex = 0; addrConfigIndex < regSpace.AddressConfig.Count; addrConfigIndex++)
                {
                    if (regSpace.AddressConfig[addrConfigIndex].InitValue == null ||
                        (regSpace.AddressConfig[addrConfigIndex].Mask == null &&
                         regSpace.MemoryType == CyEMemoryType.SRAM) ||
                        ((regSpace.AddressConfig[addrConfigIndex].AuxBits == null) &&
                         (regSpace.MemoryType == CyEMemoryType.SRAM) && m_enableAuxBits))
                    {
                        if (sb.Length > 0)
                        {
                            sb.Append(string.Concat(", ", CyParameters.ConvertDecToHex(
                                                   (ushort)(regSpace.AddressConfig[addrConfigIndex].m_address))));
                        }
                        else
                        {
                            sb.Append(CyParameters.ConvertDecToHex(
                                                   (ushort)(regSpace.AddressConfig[addrConfigIndex].m_address)));
                        }
                    }
                }
                if (sb.Length > 0)
                {
                    result.Add(new CyCustErr(string.Format(Resources.DataGridError,
                                                           m_regSpaces[regSpaceIndex].Name, sb.ToString())));
                    sb.Length = 0;
                }
            }
            return result;
        }

        public string GetNameError(CyRegSpace regSpace)
        {
            string errorText;
            if (string.IsNullOrEmpty(regSpace.Name) == false && (System.Text.RegularExpressions.Regex.Match(
                regSpace.Name, @"([A-Za-z0-9_]*)").Length == regSpace.Name.Length))
            {
                bool nameExists = false;
                for (int i = 0; i < m_regSpaces.Count; i++)
                {
                    if (m_regSpaces[i] != regSpace)
                    {
                        if (regSpace.Name.ToUpper() == m_regSpaces[i].Name.ToUpper())
                        {
                            nameExists = true;
                            break;
                        }
                    }
                }
                errorText = nameExists ? Resources.NameExists : string.Empty;
            }
            else
            {
                errorText = Resources.RegisterSpaceNameInvalid;
            }
            return errorText;
        }
        #endregion
    }

    [Serializable]
    public class CyRegAddress
    {
        public const byte AUX_BIT_7_MASK = 0x08;
        public const byte AUX_BIT_6_MASK = 0x04;
        public const byte AUX_BIT_5_MASK = 0x02;
        public const byte AUX_BIT_4_MASK = 0x01;
        public const int AUX_BITS_COUNT = 4;

        [XmlIgnore]
        public CyRegSpace m_parentObject = null;

        #region Constructor(s)
        public CyRegAddress() { }
        public CyRegAddress(ushort address, CyRegSpace parentObject)
        {
            m_address = address;
            this.m_parentObject = parentObject;
        }
        #endregion

        #region Serializable fields
        // These fields should not be used by external classes, use properties instead
        [Browsable(false)]
        [XmlIgnore]
        public ushort m_address;
        [Browsable(false)]
        [XmlAttribute("IV")]
        public string m_initValue = "0";
        [Browsable(false)]
        [XmlAttribute("Msk")]
        public string m_mask = "0";
        [Browsable(false)]
        [XmlAttribute("COR")]
        public bool m_clearOnRead;
        [Browsable(false)]
        [XmlAttribute("WO")]
        public bool m_writeOnly;
        [Browsable(false)]
        [XmlAttribute("TOW")]
        public bool m_triggerOnWrite;
        [Browsable(false)]
        [XmlAttribute("TOR")]
        public bool m_triggerOnRead;
        [Browsable(false)]
        [XmlAttribute("ABt")]
        public string m_auxBits = "".PadLeft(AUX_BITS_COUNT, '0');
        #endregion

        #region Datagrid columns fields
        [XmlIgnore]
        [DisplayName("Address")]
        public ushort Address
        {
            get { return m_address; }
            set { m_address = value; }
        }

        [XmlIgnore]
        [DisplayName("Initial value")]
        public string InitValueDisplay
        {
            get { return GetDisplayValue(m_initValue); }
            set { m_initValue = FormatDisplayValue(value); }
        }
        [XmlIgnore]
        [Browsable(false)]
        public ushort? InitValue
        {
            get { return ConvertToUInt16(m_initValue); }
        }

        [XmlIgnore]
        [DisplayName(" ")]
        public string MaskDisplay
        {
            get { return GetDisplayValue(m_mask); }
            set { m_mask = FormatDisplayValue(value); }
        }
        [XmlIgnore]
        [Browsable(false)]
        public ushort? Mask
        {
            get { return ConvertToUInt16(m_mask); }
        }

        [XmlIgnore]
        [DisplayName(" ")]
        public bool ClearOnRead
        {
            get { return m_clearOnRead; }
            set { m_clearOnRead = value; }
        }

        [XmlIgnore]
        [DisplayName(" ")]
        public bool WriteOnly
        {
            get { return m_writeOnly; }
            set { m_writeOnly = value; }
        }

        [XmlIgnore]
        [DisplayName(" ")]
        public bool TriggerOnWrite
        {
            get { return m_triggerOnWrite; }
            set { m_triggerOnWrite = value; }
        }

        [XmlIgnore]
        [DisplayName(" ")]
        public bool TriggerOnRead
        {
            get { return m_triggerOnRead; }
            set { m_triggerOnRead = value; }
        }

        [XmlIgnore]
        [Browsable(false)]
        public byte? AuxBits
        {
            get { return ConvertToByte(m_auxBits); }
        }
        [XmlIgnore]
        [DisplayName("Aux bits")]
        public string AuxBitsDisplay
        {
            get { return GetDisplayBinaryValue(m_auxBits); }
            set { m_auxBits = GetDisplayBinaryValue(value); }
        }
        #endregion

        #region Methods
        private string FormatDisplayValue(string value)
        {
            string result;
            try
            {
                result = string.Format("0x{0}", value.Replace("0x", "").PadLeft(AUX_BITS_COUNT, '0'));
            }
            catch (Exception)
            {
                result = value ?? string.Empty;
            }
            return result;
        }

        private string GetDisplayValue(string value)
        {
            string res;
            try
            {
                string format = "X4";
                ushort uValue = Convert.ToUInt16(value.Replace("0x", ""), 16);
                if (m_parentObject.m_dataWidth == CyEDataWidthType.BIT_8)
                {
                    uValue = (byte)uValue;
                    format = "X2";
                }
                res = string.Format("0x{0}", uValue.ToString(format));
            }
            catch (Exception)
            {
                res = value;
            }
            return res;
        }

        private string GetDisplayBinaryValue(string value)
        {
            return value.PadLeft(AUX_BITS_COUNT, '0');
        }

        private byte? ConvertToByte(string value)
        {
            byte? bValue;
            try
            {
                bValue = Convert.ToByte(value, 2);
            }
            catch (Exception)
            {
                bValue = null;
            }
            return bValue;
        }

        private ushort? ConvertToUInt16(string value)
        {
            ushort? uValue;
            try
            {
                uValue = Convert.ToUInt16(value.Replace("0x", ""), 16);
                if (m_parentObject.m_dataWidth == CyEDataWidthType.BIT_8)
                    uValue = (byte)uValue;
            }
            catch (Exception)
            {
                uValue = null;
            }
            return uValue;
        }
        #endregion Methods
    }
}
