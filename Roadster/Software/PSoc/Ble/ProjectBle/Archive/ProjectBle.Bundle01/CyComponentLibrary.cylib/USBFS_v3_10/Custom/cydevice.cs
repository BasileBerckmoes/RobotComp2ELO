/*******************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/



using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Text;
using System.Xml.Serialization;

namespace USBFS_v3_10
{
    [XmlType("DeviceDescriptor")]
    public class CyDeviceDescriptor : CyUSBDescriptor
    {
        public const ushort BCDUSB_WITH_BOS = 0x0201;
        public const ushort BCDUSB_WITHOUT_BOS = 0x0200;

        private byte m_bDeviceClass;
        private byte m_bDeviceSubClass;
        private byte m_bDeviceProtocol;
        private byte m_bMaxPacketSize0;
        private ushort m_idVendor = 0x04B4;
        private ushort m_idProduct = 0x8051;
        private byte m_iManufacturer;
        private byte m_iProduct;
        private byte m_iSerialNumber;
        private byte m_bNumConfigurations;
        private ushort m_bcdDevice = 0x0000;
        private ushort m_bcdUSB = BCDUSB_WITHOUT_BOS;
        private byte m_bMemoryMgmt = 0;
        private byte m_bMemoryAlloc = 0;

        // For internal usage (absolute indexes)
        public uint iwManufacturer;
        public uint iwProduct;

        public string sManufacturer;
        public string sProduct;
        public string sSerialNumber;

        public CyDeviceDescriptor()
        {
            bDescriptorType = CyUSBDescriptorType.DEVICE;
            bLength = 18;
        }
                
        public override int GetLevel()
        {
            return DEVICE_LEVEL;
        }

        public override string ToString()
        {
            return "Device Descriptor";
        }

        #region Properties
        
        public byte bDeviceClass
        {
            get { return m_bDeviceClass; }
            set { m_bDeviceClass = value; }
        }

        public byte bDeviceSubClass
        {
            get { return m_bDeviceSubClass; }
            set { m_bDeviceSubClass = value; }
        }
        public byte bDeviceProtocol
        {
            get { return m_bDeviceProtocol; }
            set { m_bDeviceProtocol = value; }
        }
        public byte bMaxPacketSize0
        {
            get { return m_bMaxPacketSize0; }
            set { m_bMaxPacketSize0 = value; }
        }
        public ushort idVendor
        {
            get { return m_idVendor; }
            set { m_idVendor = value; }
        }
        public ushort idProduct
        {
            get { return m_idProduct; }
            set { m_idProduct = value; }
        }

        public ushort bcdDevice
        {
            get { return m_bcdDevice; }
            set { m_bcdDevice = value;   }
        }

        public ushort bcdUSB
        {
            get { return m_bcdUSB; }
            set { m_bcdUSB = value; }
        }

        public byte iManufacturer
        {
            get { return m_iManufacturer; }
            set { m_iManufacturer = value; }
        }

        public byte iProduct
        {
            get { return m_iProduct; }
            set { m_iProduct = value; }
        }

        public byte iSerialNumber
        {
            get { return m_iSerialNumber; }
            set { m_iSerialNumber = value; }
        }
        public byte bNumConfigurations
        {
            get { return m_bNumConfigurations; }
            set { m_bNumConfigurations = value; }
        }

        public byte bMemoryMgmt
        {
            get { return m_bMemoryMgmt; }
            set { m_bMemoryMgmt = value; }
        }

        public byte bMemoryAlloc
        {
            get { return m_bMemoryAlloc; }
            set { m_bMemoryAlloc = value; }
        }

        #endregion Properties
    }

    [XmlType("ConfigDescriptor")]
    public class CyConfigDescriptor : CyUSBDescriptor
    {
        public const byte MAX_POWER_DEFAULT_VALUE_MV = 50;
        public const int BMATTRIBUTES_RESERVED_OFFSET = 7;
        public const int DEVICE_POWER_OFFSET = 6;
        public const int REMOTE_WAKEUP_OFFSET = 5;

        private ushort m_wTotalLength;
        private byte m_bNumInterfaces;
        private byte m_bConfigurationValue;
        private byte m_iConfiguration; // index in array of strings
        public uint iwConfiguration; // absolute index (for internal usage)
        private byte m_bmAttributes;
        private byte m_bMaxPower;

        public string sConfiguration;

        public CyConfigDescriptor()
        {
            bDescriptorType = CyUSBDescriptorType.CONFIGURATION;
            bLength = 9;
            bmAttributes = 1 << BMATTRIBUTES_RESERVED_OFFSET;
            bMaxPower = MAX_POWER_DEFAULT_VALUE_MV / 2;
        }

        public override int GetLevel()
        {
            return CONFIG_LEVEL;
        }

        public override string ToString()
        {
            return "Configuration Descriptor";
        }

        #region Properties
        public ushort wTotalLength
        {
            get { return m_wTotalLength; }
            set { m_wTotalLength = value; }
        }

        public byte bNumInterfaces
        {
            get { return m_bNumInterfaces; }
            set { m_bNumInterfaces = value; }
        }

        public byte bConfigurationValue
        {
            get { return m_bConfigurationValue; }
            set { m_bConfigurationValue = value; }
        }

        public byte iConfiguration
        {
            get { return m_iConfiguration; }
            set { m_iConfiguration = value; }
        }

        public byte bmAttributes
        {
            get { return m_bmAttributes; }
            set { m_bmAttributes = value; }
        }

        public byte bMaxPower
        {
            get { return m_bMaxPower; }
            set { m_bMaxPower = value; }
        }

        #endregion
    }

    [XmlType("EndpointDescriptor")]
    public class CyEndpointDescriptor : CyUSBDescriptor
    {
        public const byte MAX_PACKET_SIZE_GEN = 64;
        public const ushort MAX_PACKET_SIZE_ISOC = 1023;
        public const ushort MAX_PACKET_SIZE_MANUAL_DMA = 512;
        public const int MAX_PACKET_SIZE_SUM_DEVICE = 1100;

        public const byte SYNCH_TYPE_BIT = 2;
        public const byte USAGE_TYPE_BIT = 4;
        public const byte EP_DIRECTION_BIT = 7;

        public const byte EP_NUM_MASK = 0x0F;
        public const byte TRANSFER_TYPE_MASK = 0x03;
        public const byte SYNCH_TYPE_MASK = 0x0C;
        public const byte USAGE_TYPE_MASK = 0x30;

        public const byte MAX_ISOC_BINTERVAL = 16;
        public const byte MIN_ISOC_BINTERVAL = 1;

        public const byte MAX_EP_NUM = 8;
        
        private byte m_bInterval = 10;
        private byte m_bEndpointAddress;
        private byte m_bmAttributes = 2;
        private ushort m_wMaxPacketSize = 8;
        public bool DoubleBuffer;

        public static readonly List<ushort> PossibleMaxPacketValues = new List<ushort>(new ushort[] { 8, 16, 32, 64 });

        public CyEndpointDescriptor()
        {
            bDescriptorType = CyUSBDescriptorType.ENDPOINT;
            bLength = 7;
            bEndpointAddress = 1;
        }

        public override int GetLevel()
        {
            return ENDPOINT_LEVEL;
        }

        public override string ToString()
        {
            return "Endpoint Descriptor";
        }


        #region Properties

        // Properties for PropertyGrid
        [XmlIgnore]
        [TypeConverter(typeof(CyEnumConverter))]
        [Category(CyUSBOtherTypes.CATEGORY_SPECIFIC)]
        [DefaultValue(typeof(CyUSBOtherTypes.CyEndptNumbers), "EP1")]
        public CyUSBOtherTypes.CyEndptNumbers EndpointNum
        {
            get { return (CyUSBOtherTypes.CyEndptNumbers)(bEndpointAddress & EP_NUM_MASK); }
            set { bEndpointAddress = (byte)((byte)value | ((byte)Direction << EP_DIRECTION_BIT)); }
        }

        [XmlIgnore]
        [TypeConverter(typeof(CyEnumConverter))]
        [Category(CyUSBOtherTypes.CATEGORY_SPECIFIC)]
        [DefaultValue(typeof(CyUSBOtherTypes.CyEndptDirections), "OUT")]
        public CyUSBOtherTypes.CyEndptDirections Direction
        {
            get { return (CyUSBOtherTypes.CyEndptDirections)(bEndpointAddress >> EP_DIRECTION_BIT); }
            set { bEndpointAddress = (byte)((byte)EndpointNum | ((byte)value << EP_DIRECTION_BIT)); }
        }

        [XmlIgnore]
        [TypeConverter(typeof(CyEnumConverter))]
        [RefreshProperties(System.ComponentModel.RefreshProperties.All)]
        [Category(CyUSBOtherTypes.CATEGORY_SPECIFIC)]
        [DefaultValue(typeof(CyUSBOtherTypes.CyEndptTransferTypes), "TRANSFERTYPE_BULK")]
        public CyUSBOtherTypes.CyEndptTransferTypes TransferType
        {
            get { return (CyUSBOtherTypes.CyEndptTransferTypes)(bmAttributes & TRANSFER_TYPE_MASK); }
            set
            {
                bmAttributes = CalcbmAttributes((byte)value, (byte)SynchType, (byte)UsageType);
                bool isISOC = (value == CyUSBOtherTypes.CyEndptTransferTypes.TRANSFERTYPE_ISOCHRONOUS);
                if ((isISOC == false) && (wMaxPacketSize > MAX_PACKET_SIZE_GEN))
                {
                    wMaxPacketSize = MAX_PACKET_SIZE_GEN;
                }
                UpdateBrowsableItems();
            }
        }

        [XmlIgnore]
        [Browsable(false)]
        [TypeConverter(typeof(CyEnumConverter))]
        [Category(CyUSBOtherTypes.CATEGORY_SPECIFIC)]
        [DefaultValue(typeof(CyUSBOtherTypes.CyEndptSynchType), "NOSYNCH")]
        public CyUSBOtherTypes.CyEndptSynchType SynchType
        {
            get
            {
                return (CyUSBOtherTypes.CyEndptSynchType)((bmAttributes & CyEndpointDescriptor.SYNCH_TYPE_MASK) >>
                           CyEndpointDescriptor.SYNCH_TYPE_BIT);
            }
            set
            {
                bmAttributes = CalcbmAttributes((byte)TransferType, (byte)value, (byte)UsageType);
            }
        }

        [XmlIgnore]
        [Browsable(false)]
        [TypeConverter(typeof(CyEnumConverter))]
        [Category(CyUSBOtherTypes.CATEGORY_SPECIFIC)]
        [DefaultValue(typeof(CyUSBOtherTypes.CyEndptUsageType), "DATAEP")]
        public CyUSBOtherTypes.CyEndptUsageType UsageType
        {
            get
            {
                return (CyUSBOtherTypes.CyEndptUsageType)((bmAttributes & CyEndpointDescriptor.USAGE_TYPE_MASK) >>
                           CyEndpointDescriptor.USAGE_TYPE_BIT);
            }
            set
            {
                bmAttributes = CalcbmAttributes((byte)TransferType, (byte)SynchType, (byte)value);
            }
        }

        [XmlIgnore]
        [Browsable(false)]
        [DisplayName("Interval (ms)")]
        [TypeConverter(typeof(CyEnumConverter))]
        [Category(CyUSBOtherTypes.CATEGORY_SPECIFIC)]
        [DefaultValue(typeof(CyUSBOtherTypes.CyIsocIntervalType), "ISOC_INTERVAL_512")]
        public CyUSBOtherTypes.CyIsocIntervalType Interval
        {
            get { return (CyUSBOtherTypes.CyIsocIntervalType)m_bInterval; }
            set { m_bInterval = (byte)(value); }
        }

        [Browsable(false)]
        [DisplayName("Interval (ms)")]
        [Category(CyUSBOtherTypes.CATEGORY_SPECIFIC)]
        [DefaultValue(typeof(byte), "10")]
        public byte bInterval
        {
            get { return m_bInterval; }
            set { m_bInterval = value; }
        }
        [Browsable(false)]
        [DisplayName("Endpoint Address")]
        [DefaultValue((byte)0)]
        public byte bEndpointAddress
        {
            get { return m_bEndpointAddress;}
            set { m_bEndpointAddress = value; }
        }
        [Browsable(false)]
        public byte bmAttributes
        {
            get { return m_bmAttributes; }
            set { m_bmAttributes = value; }
        }
        [Category(CyUSBOtherTypes.CATEGORY_SPECIFIC)]
        [DisplayName("Max Packet Size")]
        [DefaultValue(typeof(ushort), "8")]
        public ushort wMaxPacketSize
        {
            get { return m_wMaxPacketSize; }
            set
            {
                if ((TransferType != CyUSBOtherTypes.CyEndptTransferTypes.TRANSFERTYPE_ISOCHRONOUS) &&
                    (value > MAX_PACKET_SIZE_GEN))
                {
                    throw new ArgumentOutOfRangeException(String.Format(Properties.Resources.MSG_RANGE_ERROR, 
                        "selected transfer type", 0, CyEndpointDescriptor.MAX_PACKET_SIZE_GEN));
                }
                if ((TransferType == CyUSBOtherTypes.CyEndptTransferTypes.TRANSFERTYPE_ISOCHRONOUS) && 
                    (value > MAX_PACKET_SIZE_ISOC))
                {
                    throw new
                        ArgumentOutOfRangeException(String.Format(Properties.Resources.MSG_RANGE_ERROR, 
                        "isochronous transfer type", 0, CyEndpointDescriptor.MAX_PACKET_SIZE_ISOC));
                }
                m_wMaxPacketSize = value;
            }
        }

        private byte CalcbmAttributes(byte transferType, byte synchType, byte usageType)
        {
            if (transferType == (byte)CyUSBOtherTypes.CyEndptTransferTypes.TRANSFERTYPE_ISOCHRONOUS)
            {
                return (byte) (transferType |
                              (synchType << CyEndpointDescriptor.SYNCH_TYPE_BIT) |
                              (usageType << CyEndpointDescriptor.USAGE_TYPE_BIT));
            }
            return transferType;
        }
        public void UpdateBrowsableItems()
        {
            bool isISOC = (TransferType == CyUSBOtherTypes.CyEndptTransferTypes.TRANSFERTYPE_ISOCHRONOUS);
            if (isISOC)
            {
                if (m_bInterval > MAX_ISOC_BINTERVAL)
                {
                    m_bInterval = MAX_ISOC_BINTERVAL;
                }
                else if (m_bInterval < MIN_ISOC_BINTERVAL)
                {
                    m_bInterval = MIN_ISOC_BINTERVAL;
                }
            }
            bool isBulk = (TransferType == CyUSBOtherTypes.CyEndptTransferTypes.TRANSFERTYPE_BULK);
            CyEnumTool.ChangeBrowsableAttributeValue(this, "SynchType", isISOC);
            CyEnumTool.ChangeBrowsableAttributeValue(this, "UsageType", isISOC);
            CyEnumTool.ChangeBrowsableAttributeValue(this, "Interval", isISOC);
            CyEnumTool.ChangeBrowsableAttributeValue(this, "bInterval", !isISOC && !isBulk);
        }

        #endregion Properties


        /// <summary>
        /// All the Endpoints in one Alternate Setting must have a unique Endpoint Number.
        /// This algorithm returns a unique Endpoint Number if it is posible in other case EP8 is returned.
        /// </summary>
        static public CyUSBOtherTypes.CyEndptNumbers GetUniqueEndpointNumber(CyDescriptorNode parentNode)
        {
            CyUSBOtherTypes.CyEndptNumbers defaultEpNum = CyUSBOtherTypes.CyEndptNumbers.EP8;

            if (parentNode.m_value.bDescriptorType != CyUSBDescriptorType.INTERFACE)
            {
                Debug.Assert(false);
                return defaultEpNum;
            }

            for (CyUSBOtherTypes.CyEndptNumbers num = CyUSBOtherTypes.CyEndptNumbers.EP1;
                num <= (CyUSBOtherTypes.CyEndptNumbers)CyEndpointDescriptor.MAX_EP_NUM; num++)
            {
                bool isEpPresent = false;

                foreach (var node in parentNode.Nodes)
                {
                    CyEndpointDescriptor ep = node.m_value as CyEndpointDescriptor;
                    isEpPresent = ep != null && ep.EndpointNum == num;

                    if (isEpPresent)
                        break;
                }

                if (!isEpPresent)
                    return num;
            }

            return defaultEpNum;
        }
    }

    [XmlType("InterfaceDescriptor")]
    public class CyInterfaceDescriptor : CyUSBDescriptor
    {
        private byte m_bInterfaceClass;
        private byte m_bInterfaceSubClass;
        private byte m_bAlternateSetting;
        private byte m_bInterfaceNumber;
        private byte m_bNumEndpoints;
        private byte m_bInterfaceProtocol;
        private byte m_iInterface; 
        public uint iwInterface; // absolute index (for internal usage)
        private string m_sInterface;

        private string m_interfaceDisplayName;

        public CyInterfaceDescriptor(byte interfaceNum, byte alternateSettingNum) : this()
        {
            m_bInterfaceNumber = interfaceNum;
            m_bAlternateSetting = alternateSettingNum;
        }
        public CyInterfaceDescriptor()
        {
            bDescriptorType = CyUSBDescriptorType.INTERFACE;
            bLength = 9;
        }

        public override int GetLevel()
        {
            return INTERFACE_LEVEL;
        }

        public override string ToString()
        {
            return "Alternate Setting " + bAlternateSetting;
        }


        #region Properties
        [ReadOnly(true)]
        [Category(CyUSBOtherTypes.CATEGORY_COMMON),
        TypeConverter(typeof(CyInterfaceClassConverter))]
        public byte bInterfaceClass
        {
            get { return m_bInterfaceClass; }
            set
            {
                if (m_bInterfaceClass != value)
                {
                    m_bInterfaceClass = value;
                    m_bInterfaceSubClass = 0;                    
                }
            }
        }

        [Browsable(false)]
        public byte bAlternateSetting
        {
            get { return m_bAlternateSetting; }
            set { m_bAlternateSetting = value; }
        }

        [Browsable(false)]
        public byte bInterfaceNumber
        {
            get { return m_bInterfaceNumber; }
            set { m_bInterfaceNumber = value; }
        }

        [Browsable(false)]
        public byte bNumEndpoints
        {
            get { return m_bNumEndpoints; }
            set { m_bNumEndpoints = value; }
        }

        [Browsable(false)]
        public byte bInterfaceSubClass
        {
            get { return m_bInterfaceSubClass; }
            set { m_bInterfaceSubClass = value; }
        }

        [Browsable(false)]
        public byte bInterfaceProtocol
        {
            get { return m_bInterfaceProtocol; }
            set { m_bInterfaceProtocol = value; }
        }

        [Browsable(false)]
        public byte iInterface
        {
            get { return m_iInterface; }
            set { m_iInterface = value; }
        }

        [Category(CyUSBOtherTypes.CATEGORY_SPECIFIC),
         TypeConverter(typeof(CyStringDescConverter)),
         DisplayName("iInterface")]
        public string sInterface
        {
            get { return m_sInterface; }
            set { m_sInterface = value; }
        }

        [Browsable(false)]
        [XmlIgnore]
        public string InterfaceDisplayName
        {
            get { return m_interfaceDisplayName; }
            set { m_interfaceDisplayName = value; }
        }

        #endregion Properties
    }

    [XmlType("BosDescriptor")]
    public class CyBosDescriptor : CyUSBDescriptor
    {
        #region  Members
        private ushort m_wTotalLength;
        private byte m_bNumDeviceCaps;
        #endregion Members

        #region Properties

        public ushort wTotalLength
        {
            get { return m_wTotalLength; }
            set { m_wTotalLength = value; }
        }

        public byte bNumDeviceCaps
        {
            get { return m_bNumDeviceCaps; }
            set { m_bNumDeviceCaps = value; }
        }
        #endregion Properties

        public CyBosDescriptor()
        {
            bDescriptorType = CyUSBDescriptorType.BOS;
            bLength = 5;
        }

        public override int GetLevel()
        {
            return BOS_LEVEL;
        }

        public override string ToString()
        {
            return "BOS Descriptor";
        }
    }

    [XmlType("Usb20ExtensionDeviceCapabilityDescriptor")]
    public class CyUsb20ExtensionDeviceCapabilityDescriptor : CyUSBDescriptor
    {
        #region Consts
        public const byte DEVICE_CAPABILITY_TYPE_CODE = 16;
        public const int LPM_OFFSET = 1;
        public const int LPM_MASK = 1;

        public const int BESL_AND_ALERNATE_HIRD_OFFSET = 2;
        public const int BESL_AND_ALERNATE_HIRD_MASK = 1;

        public const int BASELINE_BESL_VALID_OFFSET = 3;
        public const int BASELINE_BESL_VALID_MASK = 1;

        public const int DEEP_BESL_VALID_OFFSET = 4;
        public const int DEEP_BESL_VALID_MASK = 1;

        public const int BASELINE_BESL_VALUE_OFFSET = 8;
        public const int BASELINE_BESL_VALUE_MASK = 0xF;

        public const int DEEP_BESL_VALUE_OFFSET = 12;
        public const int DEEP_BESL_VALUE_MASK = 0xF;
        #endregion Consts


        public CyUsb20ExtensionDeviceCapabilityDescriptor()
        {
            bDescriptorType = CyUSBDescriptorType.USB20_EXTENSION_DEVICE_CAPABILITY;
            bLength = 7;
            bDevCapabilityType = 2;

            Lpm = true;
            BaselineBeslValid = true;
            DeepBeslValid= true;

            DeepBeslValue = 6;
        }

        #region Members
        private byte m_bDevCapabilityType;
        private uint m_bmAttributes;
        #endregion Members

        #region Properties

        public byte bDevCapabilityType
        {
            get { return m_bDevCapabilityType; }
            set { m_bDevCapabilityType = value; }
        }

        public uint bmAttributes
        {
            get { return m_bmAttributes; }
            set { m_bmAttributes = value; }
        }

        [XmlIgnore]
        public bool Lpm
        {
            get 
            {
                return ((m_bmAttributes >> LPM_OFFSET) & LPM_MASK) == 1;
            }
            set 
            {
                if (value)
                {
                    m_bmAttributes |= 1 << LPM_OFFSET;
                    m_bmAttributes |= 1 << BESL_AND_ALERNATE_HIRD_OFFSET;
                }
                else
                {
                    m_bmAttributes &= ~((uint)(1 << LPM_OFFSET));
                    m_bmAttributes &= ~((uint)(1 << BESL_AND_ALERNATE_HIRD_OFFSET));
                }
            }
        }

        [XmlIgnore]
        public bool BaselineBeslValid
        {
            get
            {
                return ((m_bmAttributes >> BASELINE_BESL_VALID_OFFSET) & BASELINE_BESL_VALID_MASK) == 1;
            }
            set
            {
                if (value)
                {
                    m_bmAttributes |= 1 << BASELINE_BESL_VALID_OFFSET;
                }
                else
                {
                    m_bmAttributes &= ~((uint)(1 << BASELINE_BESL_VALID_OFFSET));
                }
            }
        }


        [XmlIgnore]
        public bool DeepBeslValid
        {
            get
            {
                return ((m_bmAttributes >> DEEP_BESL_VALID_OFFSET) & DEEP_BESL_VALID_MASK) == 1;
            }
            set
            {
                if (value)
                {
                    m_bmAttributes |= 1 << DEEP_BESL_VALID_OFFSET;
                }
                else
                {
                    m_bmAttributes &= ~((uint)(1 << DEEP_BESL_VALID_OFFSET));
                }
            }
        }

        [XmlIgnore]
        public uint BaselineBeslValue
        {
            get
            {
                return (m_bmAttributes >> BASELINE_BESL_VALUE_OFFSET) & BASELINE_BESL_VALUE_MASK;
            }
            set
            {
                m_bmAttributes &= ~((uint)(BASELINE_BESL_VALUE_MASK << BASELINE_BESL_VALUE_OFFSET));
                m_bmAttributes |= value << BASELINE_BESL_VALUE_OFFSET;
            }
        }

        [XmlIgnore]
        public uint DeepBeslValue
        {
            get
            {
                return (m_bmAttributes >> DEEP_BESL_VALUE_OFFSET) & BASELINE_BESL_VALUE_MASK;
            }
            set
            {
                m_bmAttributes &= ~((uint)(DEEP_BESL_VALUE_MASK << DEEP_BESL_VALUE_OFFSET));
                m_bmAttributes |= value << DEEP_BESL_VALUE_OFFSET;
            }
        }

        #endregion Properties


        static public bool IsAtLeastOneLpmEn(CyDescriptorNode node)
        {
            if (node.Value is CyUsb20ExtensionDeviceCapabilityDescriptor &&
                ((CyUsb20ExtensionDeviceCapabilityDescriptor)node.Value).Lpm)
            {
                return true;
            }

            for (int i = 0; i < node.Nodes.Count; i++)
            {
                if (node.Nodes[i].Value is CyUsb20ExtensionDeviceCapabilityDescriptor &&
                ((CyUsb20ExtensionDeviceCapabilityDescriptor)node.Nodes[i].Value).Lpm)
                {
                    return true;
                }
                else
                {
                    if (IsAtLeastOneLpmEn(node.Nodes[i])) 
                        return true;
                }
            }

            return false;
        }

        public override int GetLevel()
        {
            return USB20_EXTENSION_DEVICE_CAPABILITY_LEVEL;
        }

        public override string ToString()
        {
            return "USB 2.0 Extension Descriptor";
        }
    }

    [XmlType("ContainerIdDescriptor")]
    public class CyContainerIdDescriptor : CyUSBDescriptor
    {
        public const byte DEVICE_CAPABILITY_TYPE_CODE = 16;
        public const byte bReserved = 0;

        #region Members
        private byte m_bDevCapabilityType;
        private string m_uuidContainerId;
        #endregion Members

        #region Properties
        public byte bDevCapabilityType
        {
            get { return m_bDevCapabilityType; }
            set { m_bDevCapabilityType = value; }
        }

        public string ContainerId
        {
            get { return m_uuidContainerId; }
            set { m_uuidContainerId = value; }
        }

        #endregion Properties

        public CyContainerIdDescriptor()
        {
            bDescriptorType = CyUSBDescriptorType.CONTAINER_ID;
            bLength = 20;
            bDevCapabilityType = 4;
            m_uuidContainerId = "00000000000000000000000000000000";
        }

        public override int GetLevel()
        {
            return CONTAINER_ID_LEVEL;
        }

        public override string ToString()
        {
            return "Container ID Descriptor";
        }


        #region Static Methods
        /// <summary>
        /// Converts UUID string to the byte list. 
        /// </summary>
        public static List<byte> UuidToHexByteList(string sUuid)
        {
            List<byte> result = new List<byte>();
            if (String.IsNullOrEmpty(sUuid) || ! CyUSBFSParameters.ContainsOnlyHexChars(sUuid))
            {
                Debug.Fail("UUID is null or empty or has wrong format");
                return result;
            }

            try
            {
                for (int i = 0; i < sUuid.Length/2; i++)
                {
                    result.Insert(0, Convert.ToByte(sUuid.Substring(i * 2, 2), 16));
                }
            }
            catch
            {
                Debug.Assert(false);
            }

            return result;
        }

        #endregion Static Methods
    }

    [XmlType("InterfaceGeneralDescriptor")]
    public class CyInterfaceGeneralDescriptor : CyUSBDescriptor
    {
        private string m_displayName;
        public string DisplayName
        {
            get { return m_displayName; }
            set { m_displayName = value; }
        }

        public CyInterfaceGeneralDescriptor()
        {
            bDescriptorType = CyUSBDescriptorType.ALTERNATE;
            bLength = 0;
            DisplayName = string.Empty;
        }

        public CyInterfaceGeneralDescriptor(string displayName) : this()
        {
            DisplayName = displayName;
        }

        public override int GetLevel()
        {
            return NONE_LEVEL;
        }

        public override string ToString()
        {
            string res = String.IsNullOrEmpty(DisplayName) ? "Interface Descriptor" : DisplayName;
            return res;
        }
    }

    [XmlType("InterfaceAssociationDescriptor")]
    public class CyInterfaceAssociationDescriptor : CyUSBDescriptor
    {
        private byte m_bFirstInterface;
        private byte m_bInterfaceCount;
        private byte m_bFunctionClass;
        private byte m_bFunctionSubClass;
        private byte m_bFunctionProtocol;
        private byte m_iFunction;
        public uint iwFunction; // absolute index (for internal usage)
        public string sFunction;

        public CyInterfaceAssociationDescriptor()
        {
            bDescriptorType = CyUSBDescriptorType.INTERFACE_ASSOCIATION;
            bLength = 8;
        }

        public override int GetLevel()
        {
            return INTERFACE_LEVEL; //?
        }

        public override string ToString()
        {
            return "Interface Association Descriptor";
        }

        #region Properties
        public byte bFirstInterface
        {
            get { return m_bFirstInterface; }
            set { m_bFirstInterface = value; }
        }

        public byte bInterfaceCount
        {
            get { return m_bInterfaceCount; }
            set { m_bInterfaceCount = value; }
        }

        public byte bFunctionClass
        {
            get { return m_bFunctionClass; }
            set
            {
                if (m_bFunctionClass != value)
                {
                    m_bFunctionClass = value;
                    m_bFunctionSubClass = 0;
                }
            }
        }

        public byte bFunctionSubClass
        {
            get { return m_bFunctionSubClass; }
            set { m_bFunctionSubClass = value; }
        }

        public byte bFunctionProtocol
        {
            get { return m_bFunctionProtocol; }
            set { m_bFunctionProtocol = value; }
        }

        public byte iFunction
        {
            get { return m_iFunction; }
            set { m_iFunction = value; }
        }
        #endregion Properties
    }

    [XmlType("StringGenerationType")]
    public enum CyStringGenerationType { USER_ENTERED_TEXT, USER_CALL_BACK, SILICON_NUMBER } ;

    [XmlType("StringDescriptor")]
    public class CyStringDescriptor : CyUSBDescriptor
    {
        private string m_bString;
        private bool m_bUsed = false;
        public CyStringGenerationType snType; 

        public CyStringDescriptor()
        {
            bDescriptorType = CyUSBDescriptorType.STRING;
            bLength = 2; 
        }

        public override int GetLevel()
        {
            return STRING_LEVEL;
        }

        #region Properties       
        public string bString
        {
            get { return m_bString; }
            set
            {
                m_bString = value;
                if (m_bString != null)
                    bLength = (byte)(2 + m_bString.Length * 2);
                else bLength = 2;
            }
        }

        public bool bUsed
        {
            get { return m_bUsed; } 
            set { m_bUsed = value; } 
        }

        public override string ToString()
        {
            return m_bString;
        }

        #endregion Properties
    }

    [XmlType("StringZeroDescriptor")]
    public class CyStringZeroDescriptor : CyUSBDescriptor
    {
        private UInt16 m_wLANGID = 0x0409;

        public CyStringZeroDescriptor()
        {
            bDescriptorType = CyUSBDescriptorType.STRING;
            bLength = 4; 
        }

        public override int GetLevel()
        {
            return NONE_LEVEL;
        }

        #region Properties
        public UInt16 wLANGID
        {
            get { return m_wLANGID; }
            set { m_wLANGID = value; }
        }
        #endregion Properties
    }

    [XmlType("HIDDescriptor")]
    public class CyHIDDescriptor : CyUSBDescriptor
    {
        private ushort m_bcdHID;
        private byte m_bCountryCode;
        private byte m_bNumDescriptors;
        private byte m_bDescriptorType1 = 0x22;
        private ushort m_wDescriptorLength;
        public byte bReportIndex;
        public uint wReportIndex; // absolute index (for internal usage)

        public CyHIDDescriptor()
        {
            bDescriptorType = CyUSBDescriptorType.HID;
            bLength = 9; 
        }

        public override int GetLevel()
        {
            return HID_CLASS_LEVEL;
        }

        public override string ToString()
        {
            return "HID Class Descriptor";
        }

        #region Properties
        public ushort bcdHID
        {
            get { return m_bcdHID; }
            set { m_bcdHID = value; }
        }

        public byte bCountryCode
        {
            get { return m_bCountryCode; }
            set { m_bCountryCode = value; }
        }

        public byte bNumDescriptors
        {
            get { return m_bNumDescriptors; }
            set { m_bNumDescriptors = value; }
        }

        public byte bDescriptorType1
        {
            get { return m_bDescriptorType1; }
            set { m_bDescriptorType1 = value; }
        }

        public ushort wDescriptorLength
        {
            get { return m_wDescriptorLength; }
            set { m_wDescriptorLength = value; }
        }
        #endregion Properties
    }

    [XmlType("HIDReportDescriptor")]
    public class CyHIDReportDescriptor : CyUSBDescriptor
    {
        public string Name;
        public ushort wLength = 0;

        public CyHIDReportDescriptor()
            : this("HID Report Descriptor")
        {
        }

        public CyHIDReportDescriptor(string name)
        {
            bDescriptorType = CyUSBDescriptorType.HID_REPORT;
            bLength = 2; 
            Name = name;
        }

        public override int GetLevel()
        {
            return NONE_LEVEL;
        }

        public override string ToString()
        {
            return Name;
        }
    }

    [XmlType("HIDReportItemDescriptor")]
    public class CyHIDReportItemDescriptor : CyUSBDescriptor
    {

        public CyHidReportItem Item;

        public CyHIDReportItemDescriptor()
        {
            bDescriptorType = CyUSBDescriptorType.HID_REPORT_ITEM;
            bLength = 1; 
        }

        public override int GetLevel()
        {
            return NONE_LEVEL;
        }

        public override string ToString()
        {
            string res;
            if (Item != null)
            {
                res = Item.ToString();
            }
            else
            {
                res = "Undefined";
            }
            return res;
        }
    }

    /// <summary>
    /// HID Report Item class
    /// </summary>
    [XmlRootAttribute("HID_ITEM")]
    public class CyHidReportItem
    {
        #region Consts

        public const string RPTITEM_USAGE = "USAGE";
        public const string RPTITEM_USAGE_PAGE = "USAGE_PAGE";
        public const string RPTITEM_USAGE_MINIMUM = "USAGE_MINIMUM";
        public const string RPTITEM_USAGE_MAXIMUM = "USAGE_MAXIMUM";
        public const string RPTITEM_DESIGNATOR_INDEX = "DESIGNATOR_INDEX";
        public const string RPTITEM_DESIGNATOR_MINIMUM = "DESIGNATOR_MINIMUM";
        public const string RPTITEM_DESIGNATOR_MAXIMUM = "DESIGNATOR_MAXIMUM";
        public const string RPTITEM_STRING_INDEX = "STRING_INDEX";
        public const string RPTITEM_STRING_MINIMUM = "STRING_MINIMUM";
        public const string RPTITEM_STRING_MAXIMUM = "STRING_MAXIMUM";
        public const string RPTITEM_COLLECTION = "COLLECTION";
        public const string RPTITEM_END_COLLECTION = "END_COLLECTION";
        public const string RPTITEM_INPUT = "INPUT";
        public const string RPTITEM_OUTPUT = "OUTPUT";
        public const string RPTITEM_FEATURE = "FEATURE";
        public const string RPTITEM_LOGICAL_MINIMUM = "LOGICAL_MINIMUM";
        public const string RPTITEM_LOGICAL_MAXIMUM = "LOGICAL_MAXIMUM";
        public const string RPTITEM_PHYSICAL_MINIMUM = "PHYSICAL_MINIMUM";
        public const string RPTITEM_PHYSICAL_MAXIMUM = "PHYSICAL_MAXIMUM";
        public const string RPTITEM_UNIT_EXPONENT = "UNIT_EXPONENT";
        public const string RPTITEM_UNIT = "UNIT";
        public const string RPTITEM_REPORT_SIZE = "REPORT_SIZE";
        public const string RPTITEM_REPORT_ID = "REPORT_ID";
        public const string RPTITEM_REPORT_COUNT = "REPORT_COUNT";
        public const string RPTITEM_PUSH = "PUSH";
        public const string RPTITEM_POP = "POP";
        public const string RPTITEM_DELIMITER = "DELIMITER";
        public const string RPTITEM_CUSTOM = "CUSTOM";
        public const string RPTITEM_COMMENT = "COMMENT";

        private const int COL_NAME_INDEX = 0;
        private const int COL_PREFIX_INDEX = 1;
        private const int COL_KIND_INDEX = 2;

        private const byte SIZE_MASK = 0x03;
        public const byte PREFIX_MASK = 0xFC;
        public const byte PREFIX_SHIFT = 2;

        public static readonly string[] HID_ITEM_INFO = new string[]
        {
            Properties.Resources.INFO_HID_USAGE,
            Properties.Resources.INFO_HID_USAGE_PAGE,
            Properties.Resources.INFO_HID_USAGE_MINIMUM,
            Properties.Resources.INFO_HID_USAGE_MAXIMUM,
            Properties.Resources.INFO_HID_DESIGNATOR_INDEX,
            Properties.Resources.INFO_HID_DESIGNATOR_MINIMUM,
            Properties.Resources.INFO_HID_DESIGNATOR_MAXIMUM,
            Properties.Resources.INFO_HID_STRING_INDEX,
            Properties.Resources.INFO_HID_STRING_MINIMUM,
            Properties.Resources.INFO_HID_STRING_MAXIMUM,
            Properties.Resources.INFO_HID_COLLECTION,
            Properties.Resources.INFO_HID_END_COLLECTION,
            Properties.Resources.INFO_HID_INPUT,
            Properties.Resources.INFO_HID_OUTPUT,
            Properties.Resources.INFO_HID_FEATURE,
            Properties.Resources.INFO_HID_LOGICAL_MINIMUM,
            Properties.Resources.INFO_HID_LOGICAL_MAXIMUM,
            Properties.Resources.INFO_HID_PHYSICAL_MINIMUM,
            Properties.Resources.INFO_HID_PHYSICAL_MAXIMUM,
            Properties.Resources.INFO_HID_UNIT_EXPONENT,
            Properties.Resources.INFO_HID_UNIT,
            Properties.Resources.INFO_HID_REPORT_SIZE,
            Properties.Resources.INFO_HID_REPORT_ID,
            Properties.Resources.INFO_HID_REPORT_COUNT,
            Properties.Resources.INFO_HID_PUSH,
            Properties.Resources.INFO_HID_POP,
            Properties.Resources.INFO_HID_DELIMITER,
            Properties.Resources.INFO_HID_CUSTOM,
            Properties.Resources.INFO_HID_COMMENT,
        };

        private static readonly string[,] HID_ITEM_DATA = new string[,]{
            {RPTITEM_USAGE,                 "0x08", "List"},
            {RPTITEM_USAGE_PAGE,            "0x04", "List"},
            {RPTITEM_USAGE_MINIMUM,         "0x18", "Int"},
            {RPTITEM_USAGE_MAXIMUM,         "0x28", "Int"},
            {RPTITEM_DESIGNATOR_INDEX,      "0x38", "Int"},
            {RPTITEM_DESIGNATOR_MINIMUM,    "0x48", "Int"},
            {RPTITEM_DESIGNATOR_MAXIMUM,    "0x58", "Int"},
            {RPTITEM_STRING_INDEX,          "0x78", "Int"},
            {RPTITEM_STRING_MINIMUM,        "0x88", "Int"},
            {RPTITEM_STRING_MAXIMUM,        "0x98", "Int"},
            {RPTITEM_COLLECTION,            "0xA0", "List"},
            {RPTITEM_END_COLLECTION,        "0xC0", "None"},
            {RPTITEM_INPUT,                 "0x80", "Bits"},
            {RPTITEM_OUTPUT,                "0x90", "Bits"},
            {RPTITEM_FEATURE,               "0xB0", "Bits"},
            {RPTITEM_LOGICAL_MINIMUM,       "0x14", "Int"},
            {RPTITEM_LOGICAL_MAXIMUM,       "0x24", "Int"},
            {RPTITEM_PHYSICAL_MINIMUM,      "0x34", "Int"},
            {RPTITEM_PHYSICAL_MAXIMUM,      "0x44", "Int"},
            {RPTITEM_UNIT_EXPONENT,         "0x54", "List"},
            {RPTITEM_UNIT,                  "0x64", "Unit"},
            {RPTITEM_REPORT_SIZE,           "0x74", "Int"},
            {RPTITEM_REPORT_ID,             "0x84", "Int"},
            {RPTITEM_REPORT_COUNT,          "0x94", "Int"},
            {RPTITEM_PUSH,                  "0xA4", "None"},
            {RPTITEM_POP,                   "0xB4", "None"},
            {RPTITEM_DELIMITER,             "0xA8", "List"},
            {RPTITEM_CUSTOM,                "0x00", "Custom"},
            {RPTITEM_COMMENT,               "0x00", "None"}
        };

        #endregion Consts

        #region Fields, Properties

        private string m_name;
        [XmlElement("Description")]
        public string m_description;
        [XmlAttribute("Code")]
        public byte m_prefix;
        [XmlArray("Value")]
        public List<byte> m_value;
        [XmlIgnore]
        public Dictionary<ushort, string> m_valuesList;
        private CyHidReportItemKind m_kind;

        [XmlAttribute("Type")]
        public string Name
        {
            get { return m_name; }
            set
            {
                m_name = value;
                FillDictionary();
            }
        }

        public CyHidReportItemKind Kind
        {
            get { return m_kind; }
            set
            {
                m_kind = value;
                FillDictionary();
            }
        }

        #endregion Fields, Properties

        #region Constructors

        public CyHidReportItem()
        {
            m_valuesList = new Dictionary<ushort, string>();
            m_value = new List<byte>();
        }

        public CyHidReportItem(string name)
            : this()
        {
            m_name = name;
            m_description = "";
            m_prefix = GetPrefixByName(m_name);
            m_kind = GetItemKind();

            FillDictionary();
        }

        /// <summary>
        /// Used during importing the report.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="prefix"></param>
        /// <param name="size"></param>
        /// <param name="value"></param>
        public CyHidReportItem(string name, byte prefix, byte size, long value, string desc)
            : this(name)
        {
            m_description = desc;
            m_prefix = prefix;
            m_value.Add((byte)(prefix | size));

            List<byte> byteList;
            if ((m_kind == CyHidReportItemKind.INT) || (m_kind == CyHidReportItemKind.CUSTOM))
            {
                byteList = CyUSBFSParameters.ConvertIntToByteArray(value, IsUnsigned());
            }
            else
            {
                byteList = new List<byte>(BitConverter.GetBytes(value));
            }
            while ((byteList.Count > 0) && (byteList.Count > GetItemSize() - 1))
                byteList.RemoveAt(byteList.Count - 1);

            m_value.AddRange(byteList.ToArray());
        }

        public CyHidReportItem(CyHidReportItem item)
        {
            m_name = item.Name;
            m_prefix = item.m_prefix;
            m_description = item.m_description;
            m_kind = item.m_kind;
            m_valuesList = new Dictionary<ushort, string>(item.m_valuesList);
            m_value = new List<byte>(item.m_value);
        }

        #endregion Constructors

        #region ToString
        /// <summary>
        /// This string representation is used to display items in the Report tree and HID Items list.
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            StringBuilder output = new StringBuilder();
            
            // 1. CUSTOM item
            if (Name == RPTITEM_CUSTOM)
            {
                if (m_value.Count == 0)
                {
                    output.Append(Name);
                }
                else
                {
                    output.AppendFormat("0x{0} {1}     ", m_value[0].ToString("X2"), m_description);

                    for (int i = 0; i < m_value.Count; i++)
                    {
                        output.AppendFormat("{0} ", m_value[i].ToString("X2"));
                    }
                }
            }
            // 2. COMMENT item
            else if ((Name == RPTITEM_COMMENT) || this.IsComment())
            {
                output.Append(Name);
            }
            // 3. General case
            else
            {
                output.AppendFormat("{0} {1}     ", Name, m_description);
                for (int i = 0; i < m_value.Count; i++)
                {
                    output.AppendFormat("{0} ", m_value[i].ToString("X2"));
                }
            }
            return output.ToString();
        }
        #endregion ToString

        #region Public functions

        public static List<CyHidReportItem> CreateAllHidItems()
        {
            List<CyHidReportItem> itemList = new List<CyHidReportItem>();
            for (int i = 0; i < HID_ITEM_DATA.GetLength(0); i++)
            {
                itemList.Add(new CyHidReportItem(HID_ITEM_DATA[i, COL_NAME_INDEX]));
            }
            return itemList;
        }

        /// <summary>
        /// Gets kind of item's data (e.g. list, int value, bits etc.)
        /// </summary>
        /// <returns></returns>
        private CyHidReportItemKind GetItemKind()
        {
            CyHidReportItemKind kind = CyHidReportItemKind.NONE;
            int index = GetItemIndex(m_name);
            try
            {
                if (index >= 0)
                {
                    kind = (CyHidReportItemKind)CyEnumTool.GetEnumValue(HID_ITEM_DATA[index, COL_KIND_INDEX], 
                                                                        typeof(CyHidReportItemKind));
                }
            }
            catch
            {
                Debug.Assert(false);
            }
            return kind;
        }

        /// <summary>
        /// Gets default size of item (number of bytes) that is used for initialization
        /// </summary>
        /// <returns></returns>
        public byte GetSizeBitValue()
        {
            const byte SIZE_UNDEFINED = 0xFF;
            byte size = 0;

            if (m_value == null || m_value.Count == 0)
                return SIZE_UNDEFINED;

            size = (byte)(m_value[0] & SIZE_MASK);

            return size;
        }

        /// <summary>
        /// Gets size of item (number of bytes)
        /// </summary>
        /// <returns></returns>
        public byte GetItemSize()
        {
            //Per HID 1.1 Secion 6.2.2.2
            byte size = 0;
            switch (GetSizeBitValue())
            {
                case 0:
                    size = 1;
                    break;
                case 1:
                    size = 2;
                    break;
                case 2:
                    size = 3;
                    break;
                case 3:
                    size = 5;
                    break;
                default:
                    size = 0;
                    break;
            }
            return size;
        }

        /// <summary>
        /// Gets prefix of item by name
        /// </summary>
        /// <returns></returns>
        private static byte GetPrefixByName(string name)
        {
            byte prefix = 0;
            int index = GetItemIndex(name);
            try
            {
                if (index >= 0)
                {
                    prefix = CyDescriptorTemplate.StrToHex1B(HID_ITEM_DATA[index, COL_PREFIX_INDEX]);
                }
            }
            catch
            {
                Debug.Assert(false);
            }
            return prefix;
        }

        /// <summary>
        /// Returns the name (if exists) by prefix
        /// </summary>
        /// <returns></returns>
        public static string GetNameByPrefix(byte prefix)
        {
            string name = "";
            prefix = (byte)(prefix & PREFIX_MASK);

            for (int i = 0; i < HID_ITEM_DATA.GetLength(0); i++)
            {
                if ((byte)(CyDescriptorTemplate.StrToHex1B(HID_ITEM_DATA[i, COL_PREFIX_INDEX]) & PREFIX_MASK) == prefix)
                {
                    name = HID_ITEM_DATA[i, COL_NAME_INDEX];
                    break;
                }
            }

            return name;
        }

        public bool IsComment()
        {
            return CyUSBFSParameters.StringIsComment(Name);
        }

        /// <summary>
        /// Fills the item's m_valuesList depending on its name.
        /// </summary>
        public void FillDictionary()
        {
            const string RPTITEM_NONVOLATILE = "Non Volatile";
            const string RPTITEM_VOLATILE = "Volatile";

            if ((Kind == CyHidReportItemKind.LIST) || (Kind == CyHidReportItemKind.BITS))
            {
                m_valuesList.Clear();
                switch (Name)
                {
                    case RPTITEM_USAGE:
                        CopyItemsToDictionary(CyHIDReportItemTables.ValuesGenericDesktopPage);
                        break;
                    case RPTITEM_USAGE_PAGE:
                        CopyItemsToDictionary(CyHIDReportItemTables.ValuesUsagePage);
                        break;
                    case RPTITEM_COLLECTION:
                        CopyItemsToDictionary(CyHIDReportItemTables.ValuesCollection);
                        break;
                    case RPTITEM_INPUT:
                        CopyItemsToDictionary(CyHIDReportItemTables.ValuesInput);
                        break;
                    case RPTITEM_OUTPUT:
                        CopyItemsToDictionary(CyHIDReportItemTables.ValuesInput);
                        m_valuesList[14] = RPTITEM_NONVOLATILE;
                        m_valuesList[15] = RPTITEM_VOLATILE;
                        break;
                    case RPTITEM_FEATURE:
                        CopyItemsToDictionary(CyHIDReportItemTables.ValuesInput);
                        m_valuesList[14] = RPTITEM_NONVOLATILE;
                        m_valuesList[15] = RPTITEM_VOLATILE;
                        break;
                    case RPTITEM_UNIT_EXPONENT:
                        CopyItemsToDictionary(CyHIDReportItemTables.ValuesUnitExponent);
                        break;
                    case RPTITEM_DELIMITER:
                        CopyItemsToDictionary(CyHIDReportItemTables.ValuesDelimiter);
                        break;
                }
            }
        }

        public bool IsUnsigned()
        {
            bool res = false;
            if (m_name == RPTITEM_REPORT_COUNT || m_name == RPTITEM_REPORT_ID || m_name == RPTITEM_REPORT_SIZE)
            {
                res = true;
            }
            return res;
        }
        #endregion Public functions

        #region Private functions
        private static int GetItemIndex(string name)
        {
            int index = -1;
            for (int i = 0; i < HID_ITEM_DATA.GetLength(0); i++)
            {
                if (HID_ITEM_DATA[i, COL_NAME_INDEX] == name)
                {
                    index = i;
                    break;
                }
            }
            return index;
        }

        private Dictionary<ushort, string> CopyItemsToDictionary(string[] sourceArray)
        {
            Dictionary<ushort, string> dict = new Dictionary<ushort, string>();
            for (int i = 0; i < sourceArray.Length / 2; i++)
            {
                m_valuesList.Add(Convert.ToUInt16(sourceArray[i * 2 + 1], 16), sourceArray[i * 2]);
            }
            return dict;
        }
        #endregion Private functions
    }


    //--------------------------------------------------------------------------------------------------------------

    [XmlType("USBDescriptorType")]
    public enum CyUSBDescriptorType
    {
        DEVICE = 1,
        CONFIGURATION = 2,
        STRING = 3,
        INTERFACE = 4,
        ENDPOINT = 5,
        DEVICE_QUALIFIER = 6,
        OTHER_SPEED_CONFIGURATION = 7,
        INTERFACE_POWER = 8,
        OTG = 9,
        DEBUG = 10,
        INTERFACE_ASSOCIATION = 11,
        
        ALTERNATE = 0xE0,

        HID = 0x21,
        AUDIO = 0x24,
        CDC = 0x44, // Change to 0x24 (Duplicated value)
        CS_ENDPOINT = 0x25,
        HID_REPORT = 0xF0,
        HID_REPORT_ITEM = 0xF1,
        MIDI = 0xF2,

        ALL = 0,

        BOS = 0x0F,
        DEVICE_CAPABILITY = 0x10,
        USB20_EXTENSION_DEVICE_CAPABILITY = 0x11,
        CONTAINER_ID = 0x12,

        MSC = 0x45
    }

    //==============================================================================================================

    [XmlType("DescriptorNode")]
    public class CyDescriptorNode
    {
        #region Fields, Properties

        public CyUSBDescriptor m_value;
        private string m_key;
        private static uint m_keyIndex = 1;
        private List<CyDescriptorNode> m_nodes;

        [XmlElement("Value")]
        public CyUSBDescriptor Value
        {
            get { return m_value; }
            set { m_value = value; }
        }

        [XmlArray("Nodes")]
        public List<CyDescriptorNode> Nodes
        {
            get { return m_nodes; }
            set { m_nodes = value; }
        }

        [XmlAttribute]
        public string Key
        {
            get { return m_key; }
            set
            {
                m_key = value;
                if ((GetDescriptorIndex(value) >= m_keyIndex) && (value != CyUSBFSParameters.NODEKEY_STRING_SERIAL) &&
                    (value != CyUSBFSParameters.NODEKEY_MSOS_STRING))
                {
                    m_keyIndex = GetDescriptorIndex(value) + 1;
                    if (m_keyIndex == CyUSBFSParameters.SERIAL_STRING_INDEX ||
                       (m_keyIndex == CyUSBFSParameters.MSOS_STRING_INDEX))
                        m_keyIndex++;
                }
            }
        }

        #endregion Fields, Properties

        #region Constructors

        public CyDescriptorNode()
        {
            Nodes = new List<CyDescriptorNode>();
        }

        public CyDescriptorNode(CyUSBDescriptor value)
            : this()
        {
            m_key = CyUSBFSParameters.NODEKEY_USBDESCRIPTOR + m_keyIndex++;
            if ((m_keyIndex == CyUSBFSParameters.SERIAL_STRING_INDEX) ||
                (m_keyIndex == CyUSBFSParameters.MSOS_STRING_INDEX))
                m_keyIndex++;
            m_value = value;
        }

        public CyDescriptorNode(string key, CyUSBDescriptor value)
            : this()
        {
            m_key = key;
            m_value = value;
        }

        #endregion Constructors

        #region Public functions

        public static uint GetDescriptorIndex(string key)
        {
            uint res = 0;
            if (key.IndexOf(CyUSBFSParameters.NODEKEY_USBDESCRIPTOR) >= 0)
                res = Convert.ToUInt32(key.Replace(CyUSBFSParameters.NODEKEY_USBDESCRIPTOR, ""));
            else if (key.IndexOf(CyUSBFSParameters.NODEKEY_INTERFACE) >= 0)
                res = Convert.ToUInt32(key.Replace(CyUSBFSParameters.NODEKEY_INTERFACE, ""));
            else
            {
                switch (key)
                {
                    case CyUSBFSParameters.NODEKEY_STRING_LANGID:
                        res = 0;
                        break;
                    case CyUSBFSParameters.NODEKEY_STRING_SERIAL:
                        res = CyUSBFSParameters.SERIAL_STRING_INDEX;
                        break;
                    case CyUSBFSParameters.NODEKEY_MSOS_STRING:
                        res = CyUSBFSParameters.MSOS_STRING_INDEX;
                        break;
                }
            }
            return res;
        }

        public static void SetKeyIndex(uint index)
        {
            m_keyIndex = index;
        }

        public static string GetKeyByIndex(uint index)
        {
            return CyUSBFSParameters.NODEKEY_USBDESCRIPTOR + index;
        }

        public static string GetDescriptorLabel(CyDescriptorNode descriptor)
        {
            string nodeLabel = "";
            if (descriptor.m_value == null)
            {
                switch (descriptor.Key)
                {
                    case CyUSBFSParameters.NODEKEY_DEVICE:
                        nodeLabel = "Descriptor Root";
                        break;
                    case CyUSBFSParameters.NODEKEY_STRING:
                        nodeLabel = "String Descriptors";
                        break;
                    case CyUSBFSParameters.NODEKEY_SPECIALSTRING:
                        nodeLabel = "Special Strings";
                        break;
                    case CyUSBFSParameters.NODEKEY_HIDREPORT:
                        nodeLabel = "HID Report Descriptors";
                        break;
                    case CyUSBFSParameters.NODEKEY_AUDIO:
                        nodeLabel = "Audio Descriptors";
                        break;
                    case CyUSBFSParameters.NODEKEY_MIDI:
                        nodeLabel = "MIDI Descriptors";
                        break;
                    case CyUSBFSParameters.NODEKEY_CDC:
                        nodeLabel = "CDC Descriptors";
                        break;
                    case CyUSBFSParameters.NODEKEY_MSC:
                        nodeLabel = "MSC Descriptors";
                        break;
                    default:
                        nodeLabel = "Unknown Descriptor";
                        break;
                }
            }
            else
            {
                switch (descriptor.m_value.bDescriptorType)
                {
                    case CyUSBDescriptorType.STRING:
                        if (descriptor.Key == CyUSBFSParameters.NODEKEY_STRING_LANGID)
                            nodeLabel = "LANGID";
                        else if (descriptor.Key == CyUSBFSParameters.NODEKEY_STRING_SERIAL)
                            nodeLabel = "Serial Number String";
                        else if (descriptor.Key == CyUSBFSParameters.NODEKEY_MSOS_STRING)
                            nodeLabel = "MS OS String Descriptor";
                        else
                        {
                            nodeLabel = string.Format("String             \"{0}\"",
                                                      ((CyStringDescriptor)descriptor.m_value).bString);
                        }
                        break;

                    default:
                        nodeLabel = descriptor.m_value.ToString();
                        break;
                }
            }
            return nodeLabel;
        }

        public static bool IsDescriptorPresent(CyDescriptorNode descNode, CyUSBDescriptorType bTypte)
        {
            if (descNode == null)
                return false;
            else if (descNode.m_value != null && descNode.m_value.bDescriptorType == bTypte)
                return true;

            for (int i = 0; i < descNode.Nodes.Count; i++)
            {
                if (IsDescriptorPresent(descNode.Nodes[i], bTypte))
                    return true;
            }

            return false;
        }
        #endregion Public functions
    }

    //=================================================================================================================

    [XmlRootAttribute("Tree")]
    public class CyDescriptorTree
    {
        private const string HIDREPORT_DEF_NAME = "HID Report Descriptor ";

        private List<CyDescriptorNode> m_nodes;

        [XmlArray("Tree Descriptors")]
        public List<CyDescriptorNode> Nodes
        {
            get { return m_nodes; }
            set { m_nodes = value; }
        }

        public CyDescriptorTree()
        {
            Nodes = new List<CyDescriptorNode>();
        }

        #region Public functions

        public CyDescriptorNode GetNodeByKey(string key)
        {
            CyDescriptorNode resultNode = null;
            Queue<CyDescriptorNode> nodeList = new Queue<CyDescriptorNode>(Nodes);
            while (nodeList.Count > 0)
            {
                CyDescriptorNode node = nodeList.Dequeue();
                if (node.Key == key)
                {
                    resultNode = node;
                    break;
                }
                else
                {
                    for (int i = 0; i < node.Nodes.Count; i++)
                    {
                        nodeList.Enqueue(node.Nodes[i]);
                    }
                }
            }
            return resultNode;
        }

        public string GetKeyByNode(CyUSBDescriptor node)
        {
            string resultKey = "";
            Queue<CyDescriptorNode> nodeList = new Queue<CyDescriptorNode>(Nodes);
            while (nodeList.Count > 0)
            {
                CyDescriptorNode node_tmp = nodeList.Dequeue();
                if ((node_tmp.Value != null) && (node_tmp.Value.Equals(node)))
                {
                    resultKey = node_tmp.Key;
                    break;
                }
                else
                {
                    for (int i = 0; i < node_tmp.Nodes.Count; i++)
                    {
                        nodeList.Enqueue(node_tmp.Nodes[i]);
                    }
                }
            }
            return resultKey;
        }

        public CyDescriptorNode AddNode(string parentKey)
        {
            CyDescriptorNode parentNode = GetNodeByKey(parentKey);
            CyDescriptorNode newNode = null;
            if (parentNode != null)
            {
                if (parentNode.Value == null)
                {
                    switch (parentNode.Key)
                    {
                        case CyUSBFSParameters.NODEKEY_DEVICE:
                            newNode = new CyDescriptorNode(new CyDeviceDescriptor());
                            parentNode.Nodes.Add(newNode);
                            AddNode(newNode.Key);
                            break;
                        case CyUSBFSParameters.NODEKEY_STRING:
                            if (parentNode.Nodes.Count == 0)
                            {
                                newNode = new CyDescriptorNode(CyUSBFSParameters.NODEKEY_STRING_LANGID,
                                                               new CyStringZeroDescriptor());
                                parentNode.Nodes.Add(newNode);
                            }
                            newNode = new CyDescriptorNode(new CyStringDescriptor());
                            parentNode.Nodes.Add(newNode);
                            AddNode(newNode.Key);
                            break;
                        case CyUSBFSParameters.NODEKEY_SPECIALSTRING:
                            if (parentNode.Nodes.Count == 0)
                            {
                                newNode = new CyDescriptorNode(CyUSBFSParameters.NODEKEY_STRING_SERIAL,
                                                             new CyStringDescriptor());
                                parentNode.Nodes.Add(newNode);
                            }
                            if (parentNode.Nodes.Count == 1)
                            {
                                newNode = new CyDescriptorNode(CyUSBFSParameters.NODEKEY_MSOS_STRING,
                                                             new CyStringDescriptor());
                                ((CyStringDescriptor)newNode.Value).bString = CyUSBFSParameters.MSOS_STRING;
                                parentNode.Nodes.Add(newNode);
                            }
                            break;
                        case CyUSBFSParameters.NODEKEY_HIDREPORT:
                            //Name of Descriptor
                            int index = 1;
                            while (true)
                            {
                                int i;
                                for (i = 0; i < parentNode.Nodes.Count; i++)
                                {
                                    if (((CyHIDReportDescriptor)parentNode.Nodes[i].Value).Name ==
                                        HIDREPORT_DEF_NAME + index)
                                    {
                                        index++;
                                        break;
                                    }
                                }
                                if (i == parentNode.Nodes.Count) break;
                            }
                            newNode = new CyDescriptorNode(new CyHIDReportDescriptor(HIDREPORT_DEF_NAME + index));
                            parentNode.Nodes.Add(newNode);
                            break;
                        default:

                            break;
                    }
                }
                else
                {
                    switch (parentNode.Value.bDescriptorType)
                    {
                        case CyUSBDescriptorType.DEVICE:
                            newNode = new CyDescriptorNode(new CyConfigDescriptor());
                            parentNode.Nodes.Add(newNode);
                            AddNode(newNode.Key);
                            break;
                        case CyUSBDescriptorType.CONFIGURATION:
                            uint lastInterfaceKeyIndex = 0;
                            if (parentNode.Nodes.Count > 0)
                            {
                                lastInterfaceKeyIndex =
                                    CyDescriptorNode.GetDescriptorIndex(
                                        parentNode.Nodes[parentNode.Nodes.Count - 1].Key);
                                lastInterfaceKeyIndex++;
                            }
                            newNode = new CyDescriptorNode(new CyInterfaceGeneralDescriptor());
                            newNode.Key = newNode.Key.Replace(CyUSBFSParameters.NODEKEY_USBDESCRIPTOR,
                                                              CyUSBFSParameters.NODEKEY_INTERFACE);
                            parentNode.Nodes.Add(newNode);
                            AddNode(newNode.Key, parentNode.Key);
                            break;
                        case CyUSBDescriptorType.INTERFACE:
                            newNode = new CyDescriptorNode(new CyEndpointDescriptor());
                            ((CyEndpointDescriptor)newNode.m_value).EndpointNum = 
                                CyEndpointDescriptor.GetUniqueEndpointNumber(parentNode); 

                            parentNode.Nodes.Add(newNode);
                            break;
                        case CyUSBDescriptorType.ENDPOINT:
                            newNode = new CyDescriptorNode(new CyASEndpointDescriptor());
                            parentNode.Nodes.Add(newNode);
                            break;
                        case CyUSBDescriptorType.HID_REPORT:
                            newNode = new CyDescriptorNode(new CyHIDReportItemDescriptor());
                            parentNode.Nodes.Add(newNode);
                            break;
                        default:
                            break;
                    }
                }
            }
            else
            {
                newNode = new CyDescriptorNode(parentKey, null);
                Nodes.Add(newNode);
                if ((newNode.Key != CyUSBFSParameters.NODEKEY_STRING) &&
                    (newNode.Key != CyUSBFSParameters.NODEKEY_HIDREPORT) &&
                    (newNode.Key != CyUSBFSParameters.NODEKEY_AUDIO))
                    AddNode(newNode.Key);
            }
            return newNode;
        }

        public CyDescriptorNode AddNode(string parentKey, CyUSBDescriptorType type)
        {
            CyDescriptorNode parentNode = GetNodeByKey(parentKey);
            CyDescriptorNode newNode = null;
            if (parentNode != null)
            {
                switch (parentNode.Value.bDescriptorType)
                {
                    case CyUSBDescriptorType.DEVICE:
                        if (type == CyUSBDescriptorType.BOS)
                        {
                            newNode = new CyDescriptorNode(new CyBosDescriptor());
                            newNode.Nodes.Add(new CyDescriptorNode(new CyUsb20ExtensionDeviceCapabilityDescriptor()));
                            parentNode.Nodes.Add(newNode); 
                        }
                        break;
                    case CyUSBDescriptorType.BOS:
                        if (type == CyUSBDescriptorType.USB20_EXTENSION_DEVICE_CAPABILITY)
                        {
                            newNode = new CyDescriptorNode(new CyUsb20ExtensionDeviceCapabilityDescriptor());
                            parentNode.Nodes.Add(newNode);
                        }
                        else if (type == CyUSBDescriptorType.CONTAINER_ID)
                        {
                            newNode = new CyDescriptorNode(new CyContainerIdDescriptor());
                            parentNode.Nodes.Add(newNode);
                        }
                        break;
                    case CyUSBDescriptorType.CONFIGURATION:
                        if (type == CyUSBDescriptorType.INTERFACE_ASSOCIATION)
                        {
                            newNode = new CyDescriptorNode(new CyInterfaceAssociationDescriptor());
                            parentNode.Nodes.Add(newNode);
                        }
                        break;
                    case CyUSBDescriptorType.INTERFACE:
                        if (type == CyUSBDescriptorType.HID)
                        {
                            newNode = new CyDescriptorNode(new CyHIDDescriptor());
                            parentNode.Nodes.Insert(0, newNode);
                        }
                        break;
                    default:
                        break;
                }
            }
            else
            {
                newNode = new CyDescriptorNode(parentKey, null);
                Nodes.Add(newNode);
                AddNode(newNode.Key);
            }
            return newNode;
        }

        /// <summary>
        /// This function is used for alternate interfaces.
        /// </summary>
        /// <param name="parentKey"></param>
        /// <param name="index"> Key of parent config node. Is used to calculate interface number </param>
        public void AddNode(string parentKey, string configNodeKey)
        {
            CyDescriptorNode parentNode = GetNodeByKey(parentKey);
            CyDescriptorNode configNode = GetNodeByKey(configNodeKey);

            if ((parentNode == null) || (configNode == null))
                return;

            byte interfaceIndex = 0;
            for (int i = 0; i < configNode.Nodes.Count; i++)
            {
                if (configNode.Nodes[i] == parentNode)
                    break;

                if (configNode.Nodes[i].Value.bDescriptorType == CyUSBDescriptorType.ALTERNATE) 
                {
                    interfaceIndex++;
                }
            }

            CyDescriptorNode newNode = null;
            if ((parentNode != null) && parentNode.Key.Contains(CyUSBFSParameters.NODEKEY_INTERFACE))
            {
                newNode = new CyDescriptorNode(new CyInterfaceDescriptor(interfaceIndex, 
                                                (byte)parentNode.Nodes.Count));
                parentNode.Nodes.Add(newNode);
                AddNode(newNode.Key);
            }
        }

        public void RemoveNode(string key, string parentKey)
        {
            CyDescriptorNode node = GetNodeByKey(key);
            CyDescriptorNode parentNode = GetNodeByKey(parentKey);
            if (node != null)
            {
                if (parentNode != null)
                {
                    parentNode.Nodes.Remove(node);
                }
                else
                {
                    this.Nodes.Remove(node);
                }
            }
        }

        #endregion Public functions
    }


    //==============================================================================================================

    [XmlType("USBOtherTypes")]
    public class CyUSBOtherTypes
    {
        public const string CATEGORY_COMMON = "Common";
        public const string CATEGORY_SPECIFIC = "Specific";

        [XmlType("InterfaceClassCodes")]
        public enum CyInterfaceClassCodes
        {
            CLASS_NONE = 0x00,
            CLASS_AUDIO = 0x01,
            CLASS_CDC= 0x02,
            CLASS_HID = 0x03,
            CLASS_MASS_STORAGE = 0x08,
            CLASS_DATA = 0x0A,
            CLASS_APPLICATION_SPECIFIC = 0xFE,
            CLASS_VENDORSPEC = 0xFF
        }

        [XmlType("HIDClassDescriptorType")]
        public enum CyHIDClassDescriptorType
        {
            HID = 0x21,
            REPORT = 0x22,
            PHYSICAL = 0x23
        }

        [XmlType("CommunicationSubclassCodes")]
        public enum CyCommunicationSubclassCodes
        {
            [Description("No subclass")]
            SUBCLASS_UNDEFINED = 0x00,
            [Description("Direct Line Control Model")]
            DIRECT_LINE_CONTROL_MODEL = 0x01,
            [Description("Abstract Control Model")]
            ABSTRACT_CONTROL_MODEL = 0x02,
            [Description("Telephone Control Model")]
            TELEPHONE_CONTROL_MODEL = 0x03,
            [Description("Multi-Channel Control Model")]
            MULTI_CHANNEL_CONTROL_MODEL = 0x04,
            [Description("CAPI Control Model")]
            CAPI_CONTROL_MODEL = 0x05,
            [Description("Ethernet Networking Control Model")]
            ETHERNET_NETWORKING_CONTROL_MODEL = 0x06,
            [Description("ATM Networking Control Model")]
            ATM_NETWORKING_CONTROL_MODEL = 0x07,
            [Description("Wireless Handset Control Model")]
            WIRELESS_HANDSET_CONTROL_MODEL = 0x08,
            [Description("Device Management")]
            DEVICE_MANAGEMENT = 0x09,
            [Description("Mobile Direct Line Model")]
            MOBILE_DIRECT_LINE_MODEL = 0x0A,
            [Description("OBEX")]
            OBEX = 0x0B,
            [Description("Ethernet Emulation Model")]
            ETHERNET_EMULATION_MODEL = 0x0C,
            [Description("Network Control Model")]
            NETWORK_CONTROL_MODEL = 0x0D
        }

        [XmlType("MassStorageSubclassCodes")]
        public enum CyMassStorageSubclassCodes
        {
            [Description("SCSI Command Set Not Reported")]
            SCSI_COMMAND_SET_NOT_REPORTED = 0x00,
            [Description("RBC")]
            RBC = 0x01,
            [Description("MMC-5 (ATAPI)")]
            MMC_5 = 0x02,
            [Description("UFI")]
            UFI = 0x04,
            [Description("SCSI Transparent Command Set")]
            SCSI_TRANSPAREN_COMMAND_SET = 0x06,
            [Description("LSD FS")]
            LSD_FS = 0x07,
            [Description("IEEE 1667")]
            IEEE_1667 = 0x08,
            [Description("Vendor-Specific")]
            VENDOR_SPECIFIC = 0xFF
        }

        [XmlType("MassStorageProtocolCodes")]
        public enum CyMassStorageProtocolCodes
        {
            [Description("CBI (With Command Completion Interrupt)")]
            CBI_CCI = 0x00,
            [Description("CBI (With No Command Completion Interrupt)")]
            CBI = 0x01,
            [Description("BBB (Bulk-Only Transport)")]
            BBB = 0x50,
            [Description("UAS")]
            UAS = 0x62,
            [Description("Vendor-Specific")]
            VENDOR_SPECIFIC = 0xFF, 
        }

        [XmlType("CommunicationProtocolCodes")]
        public enum CyCommunicationProtocolCodes
        {
            [Description("No protocol")]
            NO_PROTOCOL = 0x00,
            [Description("V.250 etc")]
            V250 = 0x01,
            [Description("PCCA-101")]
            PCCA101 = 0x02,
            [Description("PCCA-101 & Annex O")]
            PCCA101_ANNEXO = 0x03,
            [Description("GSM 07.07")]
            GSM0707 = 0x04,
            [Description("3GPP 27.007")]
            GPP27007 = 0x05,
            [Description("TIA for CDMA")]
            TIA_CMDA = 0x06,
            [Description("Ethernet Emulation Model")]
            ETHERNET_EMULATION_MODEL = 0x07,
            [Description("External Protocol")]
            EXTERNAL = 0xFE,
            [Description("Vendor-Specific")]
            VENDOR_SPEC = 0xFF
        }

        [XmlType("DataProtocolCodes")]
        public enum CyDataProtocolCodes
        {
            [Description("No protocol")]
            NO_PROTOCOL = 0x00,
            [Description("Network Transfer Block")]
            NETWORK_TRANSFER_BLOCK = 0x01,
            [Description("ISDN BRI")]
            ISDN_BRI = 0x30,
            [Description("HDLC")]
            HDLC = 0x31,
            [Description("Transparent")]
            TRANSPARENT = 0x32,
            [Description("Management protocol for Q.921")]
            MGMTQ921 = 0x50,
            [Description("Data link protocol for Q.931")]
            Q931 = 0x51,
            [Description("TEI-multiplexor for Q.921")]
            TEI_Q921 = 0x52,
            [Description("Data compression procedures")]
            DATA_COMPRESSION = 0x90,
            [Description("Euro-ISDN protocol control")]
            EURO_ISDN = 0x91,
            [Description("V.24 rate adaptation to ISDN")]
            V24_ISDN= 0x92,
            [Description("CAPI Commands")]
            CAPI_COMMANDS = 0x93,
            [Description("Host based driver")]
            HOST_BASED_DRIVER = 0xFD,
            [Description("Described using a Protocol Unit Functional Descriptors")]
            UNIT_DESC = 0xFE,
            [Description("Vendor-Specific")] 
            VENDOR_SPEC = 0xFF
        }

        [XmlType("CommunicationClassSubtypeCodes")]
        public enum CyCommunicationClassSubtypeCodes
        {
            HEADER = 0x00,
            CALL_MANAGEMENT = 0x01,
            ABSTRACT_CONTROL_MANAGEMENT = 0x02,
            DIRECT_LINE_MANAGEMENT = 0x03,
            TELEPHONE_RINGER = 0x04,
            TELEPHONE_CALL = 0x05,
            UNION = 0x06,
            COUNTRY_SELECTION = 0x07,
            TELEPHONE_OPERATIONAL_MODES = 0x08,
            USB_TERMINAL = 0x09,
            NETWORK_CHANNEL_Terminal = 0x0A,
            PROTOCOL_UNIT = 0x0B,
            EXTENSION_UNIT = 0x0C,
            MULTICHANNEL_MANAGEMENT = 0x0D,
            CAPI_CONTROL_MANAGEMENT = 0x0E,
            ETHERNET_NETWORKING = 0x0F,
            ATM_NETWORKING = 0x10,
            WIRELESS_HANDSET_CONTROL_MODEL = 0x11,
            MOBILE_DIRECT_LINE_MODEL = 0x12,
            MDLM_DETAIL = 0x13,
            DEVICE_MANAGEMENT_MODEL = 0x14,
            OBEX = 0x15,
            COMMAND_SET = 0x16,
            COMMAND_SET_DETAIL = 0x17,
            TELEPHONE_CONTROL_MODEL = 0x18,
            OBEX_SERVICE_IDENTIFIER = 0x19,
            NCM = 0x1A,
        }

        [XmlType("AudioSubclassCodes")]
        public enum CyAudioSubclassCodes
        {
            SUBCLASS_UNDEFINED = 0x00,
            AUDIOCONTROL = 0x01,
            AUDIOSTREAMING = 0x02,
            MIDISTREAMING = 0x03
        }

        [XmlType("AudioClassSpecDescriptorTypes")]
        public enum CyAudioClassSpecDescriptorTypes
        {
            CS_UNDEFINED = 0x20,
            CS_DEVICE = 0x21,
            CS_CONFIGURATION = 0x22,
            CS_STRING = 0x23,
            CS_INTERFACE = 0x24,
            CS_ENDPOINT = 0x25
        }

        [XmlType("AudioClassSpecEPDescriptorTypes")]
        public enum CyAudioClassSpecEPDescriptorTypes
        {
            DESCRIPTOR_UNDEFINED = 0x00,
            EP_GENERAL = 0x01,
        }

        [XmlType("MSClassSpecEPDescriptorTypes")]
        public enum CyMSClassSpecEPDescriptorTypes
        {
            DESCRIPTOR_UNDEFINED = 0x00,
            MS_GENERAL = 0x01,
        }

        [XmlType("ACInterfaceDescriptorSubtypes")]
        public enum CyACInterfaceDescriptorSubtypes
        {
            AC_DESCRIPTOR_UNDEFINED = 0x00,
            HEADER = 0x01,
            INPUT_TERMINAL = 0x02,
            OUTPUT_TERMINAL = 0x03,
            MIXER_UNIT = 0x04,
            SELECTOR_UNIT = 0x05,
            FEATURE_UNIT = 0x06,
            PROCESSING_UNIT = 0x07,
            EXTENSION_UNIT = 0x08
        }

        [XmlType("ACInterfaceDescriptorSubtypes_v2")]
        public enum CyACInterfaceDescriptorSubtypes_v2
        {
            AC_DESCRIPTOR_UNDEFINED = 0x00,
            HEADER = 0x01,
            INPUT_TERMINAL = 0x02,
            OUTPUT_TERMINAL = 0x03,
            MIXER_UNIT = 0x04,
            SELECTOR_UNIT = 0x05,
            FEATURE_UNIT = 0x06,
            EFFECT_UNIT = 0x07,
            PROCESSING_UNIT = 0x08,
            EXTENSION_UNIT = 0x09,
            CLOCK_SOURCE = 0x0A,
            CLOCK_SELECTOR = 0x0B,
            CLOCK_MULTIPLIER = 0x0C,
            SAMPLE_RATE_CONVERTER = 0x0D
        }

        [XmlType("ASInterfaceDescriptorSubtypes")]
        public enum CyASInterfaceDescriptorSubtypes
        {
            AS_DESCRIPTOR_UNDEFINED = 0x00,
            AS_GENERAL = 0x01,
            FORMAT_TYPE = 0x02,
            FORMAT_SPECIFIC = 0x03
        }

        [XmlType("MSInterfaceDescriptorSubtypes")]
        public enum CyMSInterfaceDescriptorSubtypes
        {
            MS_DESCRIPTOR_UNDEFINED = 0x00,
            MS_HEADER = 0x01,
            MIDI_IN_JACK = 0x02,
            MIDI_OUT_JACK = 0x03,
            ELEMENT = 0x04
        }

        [XmlType("FormatTypeCodes")]
        public enum CyFormatTypeCodes
        {
            FORMAT_TYPE_UNDEFINED = 0x00,
            FORMAT_TYPE_1 = 0x01,
            FORMAT_TYPE_2 = 0x02,
            FORMAT_TYPE_3 = 0x03
        }

        [XmlType("AudioInterfaceProtocolCodes")]
        public enum CyAudioInterfaceProtocolCodes
        {
            INTERFACE_PROTOCOL_UNDEFINED = 0x00,
            IP_VERSION_02_00 = 0x20
        }


        public enum CyEndptTransferTypes
        {
            [Description("CONT")]
            TRANSFERTYPE_CONTROL = 0x00,
            [Description("INT")]
            TRANSFERTYPE_INTERRUPT = 0x03,
            [Description("BULK")]
            TRANSFERTYPE_BULK = 0x02,
            [Description("ISOC")]
            TRANSFERTYPE_ISOCHRONOUS = 0x01
        }

        public enum CyEndptDirections
        {
            [Description("IN")]
            IN = 0x01,
            [Description("OUT")]
            OUT = 0x00
        }

        public enum CyJackTypes
        {
            [Description("UNDEFINED")]
            JACK_TYPE_UNDEFINED = 0x00,
            [Description("EMBEDDED")]
            EMBEDDED = 0x01,
            [Description("EXTERNAL")]
            EXTERNAL = 0x02
        }

        public enum CyEndptNumbers
        {
            [Description("EP1")]
            EP1 = 0x01,
            [Description("EP2")]
            EP2 = 0x02,
            [Description("EP3")]
            EP3 = 0x03,
            [Description("EP4")]
            EP4 = 0x04,
            [Description("EP5")]
            EP5 = 0x05,
            [Description("EP6")]
            EP6 = 0x06,
            [Description("EP7")]
            EP7 = 0x07,
            [Description("EP8")]
            EP8 = 0x08
        }
        
        public enum CyEndptSynchType
        {
            [Description("No Synchronization")]
            NOSYNCH = 0x00,
            [Description("Asynchronous")]
            ASYNCH = 0x01,
            [Description("Adaptive")]
            ADAPTIVE = 0x02,
            [Description("Synchronous")]
            SYNCH = 0x03
        }

        public enum CyEndptUsageType
        {
            [Description("Data endpoint")]
            DATAEP = 0,
            [Description("Feedback endpoint")]
            FEEDBACKEP = 1,
            [Description("Implicit feedback Data endpoint")]
            IMPLICITEEP = 2
        }

        public enum CyEffectUnitEffectTypes
        {
            [Description("EFFECT_UNDEFINED")]
            EFFECT_UNDEFINED = 0x00,
            [Description("PARAM_EQ_SECTION_EFFECT")]
            PARAM_EQ_SECTION_EFFECT = 0x01,
            [Description("REVERBERATION_EFFECT")]
            REVERBERATION_EFFECT = 0x02,
            [Description("MOD_DELAY_EFFECT")]
            MOD_DELAY_EFFECT = 0x03,
            [Description("DYN_RANGE_COMP_EFFECT")]
            DYN_RANGE_COMP_EFFECT = 0x04
        }

        public enum CyIsocIntervalType
        {
            [Description("1")]
            ISOC_INTERVAL_1 = 1,
            [Description("2")]
            ISOC_INTERVAL_2 = 2,
            [Description("4")]
            ISOC_INTERVAL_4 = 3,
            [Description("8")]
            ISOC_INTERVAL_8 = 4,
            [Description("16")]
            ISOC_INTERVAL_16 = 5,
            [Description("32")]
            ISOC_INTERVAL_32 = 6,
            [Description("64")]
            ISOC_INTERVAL_64 = 7,
            [Description("128")]
            ISOC_INTERVAL_128 = 8,
            [Description("256")]
            ISOC_INTERVAL_256 = 9,
            [Description("512")]
            ISOC_INTERVAL_512 = 10,
            [Description("1024")]
            ISOC_INTERVAL_1024 = 11,
            [Description("2048")]
            ISOC_INTERVAL_2048 = 12,
            [Description("4096")]
            ISOC_INTERVAL_4096 = 13,
            [Description("8192")]
            ISOC_INTERVAL_8192 = 14,
            [Description("16384")]
            ISOC_INTERVAL_16384 = 15,
            [Description("32768")]
            ISOC_INTERVAL_32768 = 16
        }
    }

    //==============================================================================================================
}
