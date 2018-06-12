/*******************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Globalization;
using System.IO;
using System.Reflection;
using System.Text;
using System.Windows.Forms;
using System.Xml.Serialization;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.ComponentModel;

namespace USBFS_v3_10
{
    public partial class CyUSBFSParameters
    {
        public enum CyEnumInterruptGroup
        {
            [XmlEnum("HIGH")]
            InterruptHigh,
            [XmlEnum("MEDIUM")]
            InterruptMedium,
            [XmlEnum("LOW")]
            InterruptLow
        } ;

        public enum CyMemoryManagement
        {
            [XmlEnum("MANUAL")]
            EP_Manual,
            [XmlEnum("DMA_MANUAL_MEMORY")]
            EP_DMAmanual,
            [XmlEnum("DMA_AUTOMATIC_MEMORY")]
            EP_DMAauto
        } ;

        public enum CyMemoryAllocation
        {
            [XmlEnum("STATIC")]
            MA_Static,
            [XmlEnum("DYNAMIC")]
            MA_Dynamic
        } ;

        #region Const
        public readonly string templatePath = string.Empty;

        public const int SERIAL_STRING_INDEX = 0x80;
        public const int MSOS_STRING_INDEX = 0xEE;

        public const string TYPE_TREE_NODE = "System.Windows.Forms.TreeNode";
        public const string MSOS_STRING = "MSFT100";

        public const string PARAM_DEVICEDESCRIPTORS = "DeviceDescriptors";
        public const string PARAM_STRINGDESCRIPTORS = "StringDescriptors";
        public const string PARAM_HIDREPORTDESCRIPTORS = "HIDReportDescriptors";
        public const string PARAM_AUDIODESCRIPTORS = "AudioDescriptors";
        public const string PARAM_MIDIDESCRIPTORS = "MidiDescriptors";
        public const string PARAM_CDCDESCRIPTORS = "CDCDescriptors";
        public const string PARAM_MSCDESCRIPTORS = "MscDescriptors";
        public const string PARAM_EXTERNCLS = "extern_cls";
        public const string PARAM_EXTERNVND = "extern_vnd";
        public const string PARAM_OUTSOF = "out_sof";
        public const string PARAM_ENABLEBATTCHARGDETECT = "EnableBatteryChargDetect";
        public const string PARAM_GEN16BITEPACCESSAPI = "Gen16bitEpAccessApi";
        public const string PARAM_MONVBUS = "mon_vbus";
        public const string PARAM_EXTERNVBUS = "extern_vbus";
        public const string PARAM_POWERPADVBUS = "powerpad_vbus";
        public const string PARAM_MAXINTERFACES = "max_interfaces_num";
        public const string PARAM_ENABLECDCAPI = "EnableCDCApi";
        public const string PARAM_ENABLEMIDIAPI = "EnableMidiApi";
        public const string HANDLEMSCREQUESTS = "HandleMscRequests";
        public const string PARAM_MSCLOGICALUNITSNUM = "MscLogicalUnitsNum";
        public const string PARAM_ENDPOINTMM = "endpointMM";
        public const string PARAM_ENDPOINTMA = "endpointMA";
        public const string PARAM_JACKCOUNT = "extJackCount";
        public const string PARAM_MODE = "Mode";
        public const string PARAM_VID = "Vid";
        public const string PARAM_PID = "Pid";
        public const string PARAM_ISRGROUPEP = "isrGroupEp{0}";
        public const string PARAM_ISRGROUP_EP = "isrGroupEp{0}";
        public const string PARAM_ISRGROUP_BUSRESET = "isrGroupBusReset";
        public const string PARAM_ISRGROUP_ARBITER = "isrGroupArbiter";
        public const string PARAM_ISRGROUP_LPM = "isrGroupLpm";
        public const string PARAM_ISRGROUP_STARTOFFRAME = "isrGroupSof";

        public const string NODEKEY_DEVICE = "Device";
        public const string NODEKEY_STRING = "String";
        public const string NODEKEY_AUDIO = "Audio";
        public const string NODEKEY_MIDI = "Midi";
        public const string NODEKEY_MSC = "MSC";
        public const string NODEKEY_CDC = "CDC";
        public const string NODEKEY_SPECIALSTRING = "SpecialString";
        public const string NODEKEY_HIDREPORT = "HIDReport";
        public const string NODEKEY_INTERFACE = "Interface";
        public const string NODEKEY_USBDESCRIPTOR = "USBDescriptor";
        public const string NODEKEY_MSOS_STRING = "EE";
        public const string NODEKEY_STRING_SERIAL = "Serial";
        public const string NODEKEY_STRING_LANGID = "LANGID";

        public const string PARAM_EP0_ISRGROUP = "isrGroupEp0";
        public const string PARAM_EP1_ISRGROUP = "isrGroupEp1";
        public const string PARAM_EP2_ISRGROUP = "isrGroupEp2";
        public const string PARAM_EP3_ISRGROUP = "isrGroupEp3";
        public const string PARAM_EP4_ISRGROUP = "isrGroupEp4";
        public const string PARAM_EP5_ISRGROUP = "isrGroupEp5";
        public const string PARAM_EP6_ISRGROUP = "isrGroupEp6";
        public const string PARAM_EP7_ISRGROUP = "isrGroupEp7";
        public const string PARAM_EP8_ISRGROUP = "isrGroupEp8";
        
        public const string PARAM_REMOVE_BUSRESET_INT = "rm_usb_int";
        public const string PARAM_REMOVE_ARB_INT = "rm_arb_int";
        public const string PARAM_REMOVE_LPM_INT = "rm_lpm_int";
        public const string PARAM_REMOVE_SOF_INT = "rm_sof_int";
        public const string PARAM_REMOVE_EP_ISR0 = "rm_ep_isr_0";

        public const string PARAM_REMOVE_EP_ISR1 = "rm_ep_isr_1";
        public const string PARAM_REMOVE_EP_ISR2 = "rm_ep_isr_2";
        public const string PARAM_REMOVE_EP_ISR3 = "rm_ep_isr_3";
        public const string PARAM_REMOVE_EP_ISR4 = "rm_ep_isr_4";
        public const string PARAM_REMOVE_EP_ISR5 = "rm_ep_isr_5";
        public const string PARAM_REMOVE_EP_ISR6 = "rm_ep_isr_6";
        public const string PARAM_REMOVE_EP_ISR7 = "rm_ep_isr_7";
        public const string PARAM_REMOVE_EP_ISR8 = "rm_ep_isr_8";
        public const string TEMPLATE_DIR = "Custom\\template";

        public Dictionary<string, string> HID_REPORT_TEMPLATE_LIST = new Dictionary<string, string>();
        private static string[,] HID_REPORT_TEMPLATE_LIST_STR = {
                          { "3ButtonMouse", "3-Button Mouse" }, 
                          { "5ButtonJoystick", "5-Button Joystick" }, 
                          { "keyboard", "Keyboard" },
                          { "GenericHID_8byte", "8-Byte Generic HID"},
                          { "GenericHID_64byte", "64-Byte Generic HID"}};

        public Dictionary<string, string> CLASS_SPECIFIC_DESCRIPTOR_TEMPLATE_LIST = new Dictionary<string, string>();
        private static string[,] CLASS_SPECIFIC__DESCRIPTOR_TEMPLATE_LIST_STR = {
                          { "AudioIn", "Audio In" }, 
                          { "AudioOut", "Audio Out" }, 
                          { "AudioInOut", "Audio InOut"},
                          { "USBUART_SingleComPort", "USBUART single COM port"},
                          { "USBUART_TwoComPorts", "USBUART two COM ports"},
                          { "MassStorage_BOT", "Mass Storage BOT"}};

        private const string PSOC4AL_IPBLOCK_NAME = "m0s8usbdss";
        #endregion Const

        #region Fields
        private CyInterruptsPage m_interrPage;

        private readonly ICyInstEdit_v1 m_instEdit;
        private readonly ICyInstQuery_v1 m_instQuery;
        private bool m_globalEditMode = false;

        private List<string> m_emptyFields; // Used to store information about fields that user should fill 
        //before closing the customizer

        private CyDescriptorTree m_deviceTree;
        private CyDescriptorTree m_stringTree;
        private CyDescriptorTree m_hidReportTree;
        private CyDescriptorTree m_audioTree;
        private CyDescriptorTree m_midiTree;
        private CyDescriptorTree m_cdcTree;
        private CyDescriptorTree m_mscTree;

        // Xml serialization parameters
        private XmlSerializer m_serializer;
        private XmlSerializerNamespaces m_customSerNamespace;

        public XmlSerializer Serializer
        {
            get { return m_serializer; }
            set { m_serializer = value; }
        }

        public XmlSerializerNamespaces CustomSerNamespace
        {
            get { return m_customSerNamespace; }
            set { m_customSerNamespace = value; }
        }

        public CyInterruptsPage InterrPage
        {
            get { return m_interrPage; }
            set { m_interrPage = value; }
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

        public List<string> EmptyFields
        {
            get { return m_emptyFields; }
            set { m_emptyFields = value; }
        }

        public CyDescriptorTree DeviceTree
        {
            get { return m_deviceTree; }
            set { m_deviceTree = value; }
        }

        public CyDescriptorTree StringTree
        {
            get { return m_stringTree; }
            set { m_stringTree = value; }
        }

        public CyDescriptorTree HidReportTree
        {
            get { return m_hidReportTree; }
            set { m_hidReportTree = value; }
        }

        public CyDescriptorTree AudioTree
        {
            get { return m_audioTree; }
            set { m_audioTree = value; }
        }

        public CyDescriptorTree MidiTree
        {
            get { return m_midiTree; }
            set { m_midiTree = value; }
        }

        public CyDescriptorTree CdcTree
        {
            get { return m_cdcTree; }
            set { m_cdcTree = value; }
        }

        public CyDescriptorTree MscTree
        {
            get { return m_mscTree; }
            set { m_mscTree = value; }
        }

        private bool[] m_usedEp = new bool[CyEndpointDescriptor.MAX_EP_NUM + 1];

        public bool[] UsedEp
        {
            get { return m_usedEp; }
        }
        private byte m_extJackCount;

        public bool IsEp1
        {
            get { return !GetValue<bool>(PARAM_REMOVE_EP_ISR1); }
        }

        public bool IsEp2
        {
            get { return !GetValue<bool>(PARAM_REMOVE_EP_ISR2); }
        }

        public bool IsEp3
        {
            get { return !GetValue<bool>(PARAM_REMOVE_EP_ISR3); }
        }

        public bool IsEp4
        {
            get { return !GetValue<bool>(PARAM_REMOVE_EP_ISR4); }
        }

        public bool IsEp5
        {
            get { return !GetValue<bool>(PARAM_REMOVE_EP_ISR5); }
        }

        public bool IsEp6
        {
            get { return !GetValue<bool>(PARAM_REMOVE_EP_ISR6); }
        }

        public bool IsEp7
        {
            get { return !GetValue<bool>(PARAM_REMOVE_EP_ISR7); }
        }

        public bool IsEp8
        {
            get { return !GetValue<bool>(PARAM_REMOVE_EP_ISR8); }
        }

        public bool IsEp0
        {
            get { return !GetValue<bool>(PARAM_REMOVE_EP_ISR0); }
        }

        public bool IsArb
        {
            get { return !GetValue<bool>(PARAM_REMOVE_ARB_INT); }
        }

        public bool IsLpm
        {
            get { return !GetValue<bool>(PARAM_REMOVE_LPM_INT); }
            set { SetValue(PARAM_REMOVE_LPM_INT, !value); }
        }

        public bool IsBusReset
        {
            get { return !GetValue<bool>(PARAM_REMOVE_BUSRESET_INT); }
        }

        public CyEnumInterruptGroup LpmIntrGroup
        {
            get { return GetValue<CyEnumInterruptGroup>(PARAM_ISRGROUP_LPM); }
            set { SetValue(PARAM_ISRGROUP_LPM, value); }
        }

        public bool EnableSofInterrupt
        {
            get { return !GetValue<bool>(PARAM_REMOVE_SOF_INT); }
            set { SetValue(PARAM_REMOVE_SOF_INT, !value); }
        }

        public CyEnumInterruptGroup ArbiterIntrGroup
        {
            get { return GetValue<CyEnumInterruptGroup>(PARAM_ISRGROUP_ARBITER); }
            set { SetValue(PARAM_ISRGROUP_ARBITER, value); }
        }
        
        public CyEnumInterruptGroup Ep0IntrGroup
        {
            get { return GetValue<CyEnumInterruptGroup>(PARAM_EP0_ISRGROUP); }
            set { SetValue(PARAM_EP0_ISRGROUP, value); }
        }

        public CyEnumInterruptGroup Ep1IntrGroup
        {
            get { return GetValue<CyEnumInterruptGroup>(PARAM_EP1_ISRGROUP); }
            set { SetValue(PARAM_EP1_ISRGROUP, value); }
        }

        public CyEnumInterruptGroup Ep2IntrGroup
        {
            get { return GetValue<CyEnumInterruptGroup>(PARAM_EP2_ISRGROUP); }
            set { SetValue(PARAM_EP2_ISRGROUP, value); }
        }

        public CyEnumInterruptGroup Ep3IntrGroup
        {
            get { return GetValue<CyEnumInterruptGroup>(PARAM_EP3_ISRGROUP); }
            set { SetValue(PARAM_EP3_ISRGROUP, value); }
        }

        public CyEnumInterruptGroup Ep4IntrGroup
        {
            get { return GetValue<CyEnumInterruptGroup>(PARAM_EP4_ISRGROUP); }
            set { SetValue(PARAM_EP4_ISRGROUP, value); }
        }

        public CyEnumInterruptGroup Ep5IntrGroup
        {
            get { return GetValue<CyEnumInterruptGroup>(PARAM_EP5_ISRGROUP); }
            set { SetValue(PARAM_EP5_ISRGROUP, value); }
        }

        public CyEnumInterruptGroup Ep6IntrGroup
        {
            get { return GetValue<CyEnumInterruptGroup>(PARAM_EP6_ISRGROUP); }
            set { SetValue(PARAM_EP6_ISRGROUP, value); }
        }

        public CyEnumInterruptGroup Ep7IntrGroup
        {
            get { return GetValue<CyEnumInterruptGroup>(PARAM_EP7_ISRGROUP); }
            set { SetValue(PARAM_EP7_ISRGROUP, value); }
        }

        public CyEnumInterruptGroup Ep8IntrGroup
        {
            get { return GetValue<CyEnumInterruptGroup>(PARAM_EP8_ISRGROUP); }
            set { SetValue(PARAM_EP8_ISRGROUP, value); }
        }

        public CyEnumInterruptGroup BusResetIntrGroup
        {
            get { return GetValue<CyEnumInterruptGroup>(PARAM_ISRGROUP_BUSRESET); }
            set { SetValue(PARAM_ISRGROUP_BUSRESET, value); }
        }

        public CyEnumInterruptGroup StartOfFrameIntrGroup
        {
            get { return GetValue<CyEnumInterruptGroup>(PARAM_ISRGROUP_STARTOFFRAME); }
            set { SetValue(PARAM_ISRGROUP_STARTOFFRAME, value); }
        }

        public string SerializedDeviceDesc
        {
            get { return GetValue<string>(PARAM_DEVICEDESCRIPTORS); }
            set { SetValue(PARAM_DEVICEDESCRIPTORS, value); }
        }

        public string SerializedStringDesc
        {
            get { return GetValue<string>(PARAM_STRINGDESCRIPTORS); }
            set { SetValue(PARAM_STRINGDESCRIPTORS, value); }
        }

        public string SerializedHIDReportDesc
        {
            get { return GetValue<string>(PARAM_HIDREPORTDESCRIPTORS); }
            set { SetValue(PARAM_HIDREPORTDESCRIPTORS, value); }
        }

        public string SerializedAudioDesc
        {
            get { return GetValue<string>(PARAM_AUDIODESCRIPTORS); }
            set { SetValue(PARAM_AUDIODESCRIPTORS, value); }
        }

        public string SerializedMidiDesc
        {
            get { return GetValue<string>(PARAM_MIDIDESCRIPTORS); }
            set { SetValue(PARAM_MIDIDESCRIPTORS, value); }
        }

        public string SerializedCDCDesc
        {
            get { return GetValue<string>(PARAM_CDCDESCRIPTORS); }
            set { SetValue(PARAM_CDCDESCRIPTORS, value); }
        }

        public string SerializedMscDesc
        {
            get { return GetValue<string>(PARAM_MSCDESCRIPTORS); }
            set { SetValue(PARAM_MSCDESCRIPTORS, value); }
        }

        public byte MaxInterfaces
        {
            get { return GetValue<byte>(PARAM_MAXINTERFACES); }
            set { SetValue(PARAM_MAXINTERFACES, value); }
        }

        public void SetExtJackCount(byte value)
        {
            m_extJackCount = value;
            SetValue(PARAM_JACKCOUNT, Mode ? m_extJackCount : (byte)0 ); 
        }

        public bool Mode
        {
            get { return GetValue<bool>(PARAM_MODE); }
            set 
            { 
                SetValue(PARAM_MODE, value);
                SetExtJackCount(m_extJackCount);
            }
        }

        public bool EnableCDCApi
        {
            get { return GetValue<bool>(PARAM_ENABLECDCAPI); }
            set { SetValue(PARAM_ENABLECDCAPI, value); }
        }

        public bool EnableMIDIApi
        {
            get { return GetValue<bool>(PARAM_ENABLEMIDIAPI); }
            set { SetValue(PARAM_ENABLEMIDIAPI, value); }
        }

        public bool EnableBattChargDetect
        {
            get { return GetValue<bool>(PARAM_ENABLEBATTCHARGDETECT); }
            set { SetValue(PARAM_ENABLEBATTCHARGDETECT, value); }
        }

        public bool Gen16bitEpAccessApi
        {
            get { return GetValue<bool>(PARAM_GEN16BITEPACCESSAPI); }
            set { SetValue(PARAM_GEN16BITEPACCESSAPI, value); }
        }

        public bool HandleMscRequests
        {
            get { return GetValue<bool>(HANDLEMSCREQUESTS); }
            set { SetValue(HANDLEMSCREQUESTS, value); }
        }

        public byte MscLogicalUnitsNum
        {
            get { return GetValue<byte>(PARAM_MSCLOGICALUNITSNUM); }
            set { SetValue(PARAM_MSCLOGICALUNITSNUM, value); }
        }

        public bool Extern_cls
        {
            get { return GetValue<bool>(PARAM_EXTERNCLS); }
            set { SetValue(PARAM_EXTERNCLS, value);  }
        }

        public bool Extern_vnd
        {
            get { return GetValue<bool>(PARAM_EXTERNVND); }
            set { SetValue(PARAM_EXTERNVND, value); }
        }

        public bool Out_sof
        {
            get { return GetValue<bool>(PARAM_OUTSOF); }
            set { SetValue(PARAM_OUTSOF, value); }
        }

        public bool Mon_vbus
        {
            get { return GetValue<bool>(PARAM_MONVBUS); }
            set { SetValue(PARAM_MONVBUS, value); }
        }

        public bool Extern_vbus
        {
            get { return GetValue<bool>(PARAM_EXTERNVBUS); }
            set { SetValue(PARAM_EXTERNVBUS, value); }
        }

        public bool PowerPad_vbus
        {
            get { return GetValue<bool>(PARAM_POWERPADVBUS); }
            set { SetValue(PARAM_POWERPADVBUS, value); }
        }

        public CyMemoryManagement EPMemoryMgmt
        {
            get { return GetValue<CyMemoryManagement>(PARAM_ENDPOINTMM); }
            set { SetValue(PARAM_ENDPOINTMM, value); }
        }

        public CyMemoryAllocation EPMemoryAlloc
        {
            get { return GetValue<CyMemoryAllocation>(PARAM_ENDPOINTMA); }
            set { SetValue(PARAM_ENDPOINTMA, value); }
        }

        public string Vid
        {
            get { return GetValue<string>(PARAM_VID); }
            set { SetValue(PARAM_VID, value); }
        }

        public string Pid
        {
            get { return GetValue<string>(PARAM_PID); }
            set { SetValue(PARAM_PID, value); }
        }

        public bool IsPSoC4AL_IpBlock
        {
            get
            {
                if (m_instQuery == null)
                {
                    return false;
                }
                else
                { 
                    return m_instQuery.DeviceQuery.GetFeatureCount(PSOC4AL_IPBLOCK_NAME)  >  0;
                }
            }
        }

        #endregion Fields

        #region Constructors

        public CyUSBFSParameters()
        {
            // Create XML Serializer
            m_serializer = new XmlSerializer(typeof(CyDescriptorTree));
            m_customSerNamespace = new XmlSerializerNamespaces();
            Type classType = typeof(CyUSBFSParameters);
            string curNamespace = classType.Namespace;
            string version = curNamespace.Substring(curNamespace.LastIndexOf("_v") + 2);
            m_customSerNamespace.Add("CustomizerVersion", version);

            // Init dictionary that contains list of HID report templates and display names of these templates
            HID_REPORT_TEMPLATE_LIST.Clear();
            for (int i = 0; i < HID_REPORT_TEMPLATE_LIST_STR.GetLength(0); i++)
            {
                HID_REPORT_TEMPLATE_LIST.Add(HID_REPORT_TEMPLATE_LIST_STR[i,0], HID_REPORT_TEMPLATE_LIST_STR[i,1]);
            }

            // Init dictionary that contains list of Audio descriptor templates and display names of these templates
            CLASS_SPECIFIC_DESCRIPTOR_TEMPLATE_LIST.Clear();
            for (int i = 0; i < CLASS_SPECIFIC__DESCRIPTOR_TEMPLATE_LIST_STR.GetLength(0); i++)
            {
                CLASS_SPECIFIC_DESCRIPTOR_TEMPLATE_LIST.Add(CLASS_SPECIFIC__DESCRIPTOR_TEMPLATE_LIST_STR[i, 0], 
                    CLASS_SPECIFIC__DESCRIPTOR_TEMPLATE_LIST_STR[i, 1]);
            }

            m_deviceTree = new CyDescriptorTree();
            m_stringTree = new CyDescriptorTree();
            m_hidReportTree = new CyDescriptorTree();
            m_audioTree = new CyDescriptorTree();
            m_midiTree = new CyDescriptorTree();
            m_cdcTree = new CyDescriptorTree();
            m_mscTree = new CyDescriptorTree();
            m_emptyFields = new List<string>();
        }

        public CyUSBFSParameters(ICyInstQuery_v1 instQuery)
            : this()
        {
            m_instQuery = instQuery;
            m_instEdit = null;
            DeserializeDescriptors();
            
            try
            {
                if (m_instQuery.SymbolFileName != null)
                    templatePath = Path.Combine(Path.GetDirectoryName(m_instQuery.SymbolFileName), TEMPLATE_DIR);
            }
            catch
            {
                templatePath = string.Empty;
            }
        }

        public CyUSBFSParameters(ICyInstEdit_v1 instEdit)
            : this()
        {
            m_instQuery = instEdit;
            m_instEdit = instEdit;
            DeserializeDescriptors();

            try
            {
                if (m_instQuery.SymbolFileName != null)
                    templatePath = Path.Combine(Path.GetDirectoryName(m_instQuery.SymbolFileName), TEMPLATE_DIR);
            }
            catch
            {
                templatePath = string.Empty;
            }
        }

        #endregion Constructors

        #region GetValue

        public CyEnumInterruptGroup GetParamEndpointInterruptGroup(uint endpointNum)
        {
            string paramName = string.Format(PARAM_ISRGROUPEP, endpointNum.ToString());

            return GetValue<CyEnumInterruptGroup>(paramName);
        }

        private T GetValue<T>(string paramName)
        {
            if (m_instQuery == null)
            {
                return default(T);
            }
            CyCompDevParam prm = m_instQuery.GetCommittedParam(paramName);
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
        #endregion GetValue

        #region SetValue
        private void SetValue<T>(string paramName, T value)
        {
            if (GlobalEditMode)
                if (m_instEdit != null)
                {
                    string valueToSet = value.ToString();
                    if (value is bool)
                        valueToSet = valueToSet.ToLower();
                    if (value is byte || value is UInt16 || value is UInt32 || value is UInt64)
                        valueToSet += "u";
                    if (m_instEdit.SetParamExpr(paramName, valueToSet))
                    {
                        m_instEdit.CommitParamExprs();
                    }
                }
        }

        public void SetParamEndpointInterruptGroup(uint endpointNum, CyEnumInterruptGroup interuptGroup)
        {
            string paramName = string.Format(PARAM_ISRGROUPEP, endpointNum.ToString());

            SetValue(paramName, interuptGroup);
        }

        public void SetParam_rm_ep_isr()
        {
            bool alwaysTrue = true; // for rm_dma params
                
            if (EPMemoryMgmt != CyMemoryManagement.EP_Manual)
                alwaysTrue = false;
                
            for (int i = 1; i < m_usedEp.Length; i++)
            {
                string param_rm_ep_isr = "rm_ep_isr_" + i;
                string param_rm_dma = "rm_dma_" + i;
                if (m_usedEp[i] == true)
                {
                    SetValue(param_rm_ep_isr, false);
                    SetValue(param_rm_dma, alwaysTrue); // if alwaysTrue=false then False
                }
                else
                {
                    SetValue(param_rm_ep_isr, true);
                    SetValue(param_rm_dma, true);
                }
            }
        }

        public void SetCdcVidPid(CyDescriptorNode node, string vid, string pid)
        {
            if ((node.Value != null) && (node.Value.bDescriptorType == CyUSBDescriptorType.INTERFACE))
            {
                CyInterfaceDescriptor interfaceDesc = (CyInterfaceDescriptor)node.Value;
                if (interfaceDesc.bInterfaceClass == (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_CDC)
                {
                    Vid = vid;
                    Pid = pid;
                }
            }
            else
            {
                if ((node.Value != null) && (node.Value.bDescriptorType == CyUSBDescriptorType.DEVICE))
                {
                    CyDeviceDescriptor deviceDesc = (CyDeviceDescriptor)node.Value;
                    vid = deviceDesc.idVendor.ToString("X4");
                    pid = deviceDesc.idProduct.ToString("X4");
                }

                for (int i = node.Nodes.Count-1; i >= 0; i--)
                {
                    SetCdcVidPid(node.Nodes[i], vid, pid);
                }
            }
        }
        #endregion SetValue

        #region Save tree descriptor
        public void ParamDeviceTreeChanged()
        {
            SerializedDeviceDesc = ParamTreeChanged(m_deviceTree);
        }

        public void ParamStringTreeChanged()
        {

            if (m_deviceTree.Nodes.Count > 0)
                RecalcDescriptors(m_deviceTree.Nodes[0]);
            SerializedStringDesc = ParamTreeChanged(m_stringTree);

        }

        public void ParamHIDReportTreeChanged()
        {
            SerializedHIDReportDesc = ParamTreeChanged(m_hidReportTree);
        }

        public void ParamAudioTreeChanged()
        {
            SerializedAudioDesc = ParamTreeChanged(m_audioTree);
            ParamDeviceTreeChanged();
        }

        public void ParamMidiTreeChanged()
        {
            SerializedMidiDesc = ParamTreeChanged(m_midiTree);
            ParamDeviceTreeChanged();
        }

        public void ParamCDCTreeChanged()
        {
            SerializedCDCDesc = ParamTreeChanged(m_cdcTree);
            ParamDeviceTreeChanged();
        }

        public void ParamMscTreeChanged()
        {
            SerializedMscDesc = ParamTreeChanged(m_mscTree);
            ParamDeviceTreeChanged();
        }

        private string ParamTreeChanged(CyDescriptorTree tree)
        {
            if (tree.Nodes.Count > 0)
                RecalcDescriptors(tree.Nodes[0]);

            //If customizer is opened and Interrupts page is created, then update Interupt table view
            if (m_interrPage != null)
                m_interrPage.UpdateInterruptsTableView();
            
            return SerializeDescriptorTree(tree);
        }
        #endregion Save tree descriptor

        #region Parameters serialization
        public string SerializeDescriptorTree(CyDescriptorTree tree)
        {
            string serializedXml = "";
            using (StringWriter sw = new StringWriter())
            {
                m_serializer.Serialize(sw, tree, m_customSerNamespace);
                serializedXml = sw.ToString();
            }
            return serializedXml;
        }

        public static CyDescriptorTree DeserializeDescriptorTree(string serializedXml, XmlSerializer s)
        {
            CyDescriptorTree tree = (CyDescriptorTree)s.Deserialize(new StringReader(serializedXml));
            return tree;
        }

        public void DeserializeDescriptors()
        {
            // Deserialize Device Tree
            if (!string.IsNullOrEmpty(SerializedDeviceDesc))
            {
                try
                {
                    m_deviceTree = DeserializeDescriptorTree(SerializedDeviceDesc, m_serializer);
                    CheckOldFormatCompability(m_deviceTree);
                }
                catch
                {
                    MessageBox.Show(String.Format(Properties.Resources.MSG_WRONG_PARAMETER, PARAM_DEVICEDESCRIPTORS),
                                     Properties.Resources.MSG_TITLE_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    InitDescriptors(true, false, false, false, false, false, false);
                }
            }
            else
            {
                InitDescriptors(true, false, false, false, false, false, false);
            }
            // Deserialize String Tree
            if (!string.IsNullOrEmpty(SerializedStringDesc))
            {
                try
                {
                    m_stringTree = DeserializeDescriptorTree(SerializedStringDesc, m_serializer);
                    CheckStringOldFormatCompability(m_stringTree);
                }
                catch
                {
                    MessageBox.Show(String.Format(Properties.Resources.MSG_WRONG_PARAMETER, PARAM_STRINGDESCRIPTORS),
                                     Properties.Resources.MSG_TITLE_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    InitDescriptors(false, true, false, false, false, false, false);
                }
            }
            else
            {
                InitDescriptors(false, true, false, false, false, false, false);
            }
            // Deserialize HID Report Tree
            if (!string.IsNullOrEmpty(SerializedHIDReportDesc))
            {
                try
                {
                    m_hidReportTree = DeserializeDescriptorTree(SerializedHIDReportDesc, m_serializer);
                    RestoreHIDReportUsageList();
                }
                catch
                {
                    MessageBox.Show(String.Format(Properties.Resources.MSG_WRONG_PARAMETER, PARAM_HIDREPORTDESCRIPTORS),
                                     Properties.Resources.MSG_TITLE_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    InitDescriptors(false, false, true, false, false, false, false);
                }
            }
            else
            {
                InitDescriptors(false, false, true, false, false, false, false);
            }
            // Deserialize Audio Tree
            if (!string.IsNullOrEmpty(SerializedAudioDesc))
            {
                try
                {
                    m_audioTree = DeserializeDescriptorTree(SerializedAudioDesc, m_serializer);
                }
                catch
                {
                    MessageBox.Show(String.Format(Properties.Resources.MSG_WRONG_PARAMETER, PARAM_AUDIODESCRIPTORS),
                                     Properties.Resources.MSG_TITLE_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    InitDescriptors(false, false, false, true, false, false, false);
                }
            }
            else
            {
                InitDescriptors(false, false, false, true, false, false, false);
            }

            // Deserialize Midi Tree
            if (!string.IsNullOrEmpty(SerializedMidiDesc))
            {
                try
                {
                    m_midiTree = DeserializeDescriptorTree(SerializedMidiDesc, m_serializer);
                }
                catch
                {
                    MessageBox.Show(String.Format(Properties.Resources.MSG_WRONG_PARAMETER, PARAM_MIDIDESCRIPTORS),
                                     Properties.Resources.MSG_TITLE_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    InitDescriptors(false, false, false, false, false, true, false);
                }
            }
            else
            {
                InitDescriptors(false, false, false, false, false, true, false);
            }

            // Deserialize CDC Tree
            if (!string.IsNullOrEmpty(SerializedCDCDesc))
            {
                try
                {
                    m_cdcTree = DeserializeDescriptorTree(SerializedCDCDesc, m_serializer);
                }
                catch
                {
                    MessageBox.Show(String.Format(Properties.Resources.MSG_WRONG_PARAMETER, PARAM_CDCDESCRIPTORS),
                                     Properties.Resources.MSG_TITLE_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    InitDescriptors(false, false, false, false, true, false, false);
                }
            }
            else
            {
                InitDescriptors(false, false, false, false, true, false, false);
            }

            // Deserialize Mass Storage Tree
            if (!string.IsNullOrEmpty(SerializedMscDesc))
            {
                try
                {
                    m_mscTree = DeserializeDescriptorTree(SerializedMscDesc, m_serializer);
                }
                catch
                {
                    MessageBox.Show(String.Format(Properties.Resources.MSG_WRONG_PARAMETER, PARAM_MSCDESCRIPTORS),
                                     Properties.Resources.MSG_TITLE_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    InitDescriptors(false, false, false, false, false, false, true);
                }
            }
            else
            {
                InitDescriptors(false, false, false, false, false, false, true);
            }

            // Check if Device tree has class specific interfaces and if so, merge them with audio or cdc or msc interfaces
            // to make one object
            for (int i = 0; i < m_deviceTree.Nodes[0].Nodes.Count; i++) //device level
            {
                CyDescriptorNode deviceNode = m_deviceTree.Nodes[0].Nodes[i];

                for (int j = 0; j < deviceNode.Nodes.Count; j++) // configuration level
                {
                    CyDescriptorNode configNode = deviceNode.Nodes[j];

                    // interface level
                    for (int k = 0; k < configNode.Nodes.Count; k++)
                    {
                        CyDescriptorNode interfaceNode = configNode.Nodes[k];

                        // alternate level
                        for (int m = 0; m < Math.Min(1, interfaceNode.Nodes.Count); m++)
                        {
                            CyDescriptorNode alternateNode = interfaceNode.Nodes[m];

                            // audio / midi
                            if (alternateNode.Value is CyAudioInterfaceDescriptor)
                            {
                                // audio tree
                                for (int l = 0; l < m_audioTree.Nodes[0].Nodes.Count; l++)
                                {
                                    // If node keys are equal, merge interface nodes
                                    if (interfaceNode.Key == m_audioTree.Nodes[0].Nodes[l].Key)
                                    {
                                        m_audioTree.Nodes[0].Nodes.RemoveAt(l);
                                        m_audioTree.Nodes[0].Nodes.Insert(l,
                                                                              m_deviceTree.Nodes[0].Nodes[i].
                                                                                  Nodes[j].Nodes[k]);
                                        break;
                                    }
                                }

                                // midi tree
                                for (int l = 0; l < m_midiTree.Nodes[0].Nodes.Count; l++)
                                {
                                    // If node keys are equal, merge interface nodes
                                    if (interfaceNode.Key == m_midiTree.Nodes[0].Nodes[l].Key)
                                    {
                                        m_midiTree.Nodes[0].Nodes.RemoveAt(l);
                                        m_midiTree.Nodes[0].Nodes.Insert(l,
                                                                              m_deviceTree.Nodes[0].Nodes[i].
                                                                                  Nodes[j].Nodes[k]);
                                        break;
                                    }
                                }
                            }

                            // cdc
                            else if (alternateNode.Value is CyCDCInterfaceDescriptor)
                            {
                                for (int l = 0; l < m_cdcTree.Nodes[0].Nodes.Count; l++)
                                {
                                    // If node keys are equal, merge interface nodes
                                    if (interfaceNode.Key == m_cdcTree.Nodes[0].Nodes[l].Key)
                                    {
                                        m_cdcTree.Nodes[0].Nodes.RemoveAt(l);
                                        m_cdcTree.Nodes[0].Nodes.Insert(l, m_deviceTree.Nodes[0].Nodes[i].
                                                                                  Nodes[j].Nodes[k]);
                                        break;
                                    }
                                }
                            }

                            // msc
                            else if (alternateNode.Value is CyMscInterfaceDescriptor)
                            {
                                for (int l = 0; l < m_mscTree.Nodes[0].Nodes.Count; l++)
                                {
                                    // If node keys are equal, merge interface nodes
                                    if (interfaceNode.Key == m_mscTree.Nodes[0].Nodes[l].Key)
                                    {
                                        m_mscTree.Nodes[0].Nodes.RemoveAt(l);
                                        m_mscTree.Nodes[0].Nodes.Insert(l, m_deviceTree.Nodes[0].Nodes[i].
                                                                                  Nodes[j].Nodes[k]);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            // Reassing Endpoint memory allocation value for compatibility with previous versions
            if (m_deviceTree.Nodes[0].Nodes.Count > 0)
            {
                CyDeviceDescriptor node = (CyDeviceDescriptor)m_deviceTree.Nodes[0].Nodes[0].Value;
                if (node.bMemoryMgmt != 0)
                {
                    node.bMemoryMgmt = 0;
                }
                if (node.bMemoryAlloc != 0)
                {
                    try
                    {
                        EPMemoryAlloc = (CyMemoryAllocation)node.bMemoryAlloc;
                    }
                    catch { Debug.Assert(false); }
                    node.bMemoryAlloc = 0;
                }
            }
        }
        #endregion Parameters serialization

        #region Manipulations with String descriptors

        /// <summary>
        /// Finds the index of the string that was selected in the descriptor.
        /// </summary>
        /// <param name="comboBox">Combobox where user selects the string descriptor</param>
        /// <param name="parameters">Reference to the Parameters</param>
        /// <returns>Unique index of the string</returns>
        public static uint SaveStringDescriptor(ComboBox comboBox, CyUSBFSParameters parameters)
        {
            CyStringDescriptor strDesc = null;
            uint strIndex = 0;

            if (comboBox.Text == "") return strIndex;

            if ((comboBox.SelectedIndex < 0) && (comboBox.Text != ""))
            {
                //Search for string in pre-defined array
                bool predefined = false;
                List<CyStringDescriptor> strList = parameters.GetStringDescList();
                for (int i = 0; i < strList.Count; i++)
                {
                    if (comboBox.Text == strList[i].ToString())
                    {
                        predefined = true;
                        strDesc = strList[i];
                        break;
                    }
                }
                if (!predefined)
                {
                    strDesc = CreateNewStringDescriptor(comboBox.Text, parameters);
                    parameters.ParamStringTreeChanged();
                }
            }
            else
            {
                strDesc = (CyStringDescriptor)comboBox.Items[comboBox.SelectedIndex];
            }

            //General USBDescriptor-based index
            strIndex = GetStringDescriptorIndex(strDesc, parameters);

            return strIndex;
        }

        public static CyStringDescriptor CreateNewStringDescriptor(string strValue, CyUSBFSParameters parameters)
        {
            CyDescriptorNode newNode = parameters.m_stringTree.AddNode(NODEKEY_STRING);
            ((CyStringDescriptor)newNode.Value).bString = strValue;
            return (CyStringDescriptor)newNode.Value;
        }

        /// <summary>
        /// This function returns a general USBDescriptor-based index of the String Descriptor.
        /// </summary>
        /// <param name="strDesc"></param>
        /// <param name="parameters"></param>
        /// <returns></returns>
        public static uint GetStringDescriptorIndex(CyStringDescriptor strDesc, CyUSBFSParameters parameters)
        {
            uint strIndex = 0;
            string strConfigKey = parameters.m_stringTree.GetKeyByNode(strDesc);
            if (strConfigKey != "")
            {
                strIndex = CyDescriptorNode.GetDescriptorIndex(strConfigKey);
            }
            return strIndex;
        }

        /// <summary>
        /// Gets the Serial String descriptor node from the m_stringTree
        /// </summary>
        /// <returns></returns>
        public CyStringDescriptor GetSerialDescriptor()
        {
            CyStringDescriptor res = null;
            if ((m_stringTree != null) &&
                (m_stringTree.Nodes.Count > 1) &&
                (m_stringTree.Nodes[1].Nodes.Count > 0))
            {
                res = (CyStringDescriptor)m_stringTree.Nodes[1].Nodes[0].Value;
            }
            return res;
        }

        public List<CyStringDescriptor> GetStringDescList()
        {
            List<CyStringDescriptor> strList = new List<CyStringDescriptor>();
            for (int i = 1; i < m_stringTree.Nodes[0].Nodes.Count; i++)
            {
                CyStringDescriptor strDesc =
                                        (CyStringDescriptor)m_stringTree.Nodes[0].Nodes[i].Value;
                if (strDesc.bString != null)
                {
                    strList.Add(strDesc);
                }
            }
            return strList;
        }

        public List<string> GetStringsList()
        {
            List<CyStringDescriptor> strDescList = GetStringDescList();
            List<string> strList = new List<string>();
            for (int i = 0; i < strDescList.Count; i++)
            {
                strList.Add(strDescList[i].bString);
            }
            return strList;
        }

        public uint SaveStringDescriptor(string value)
        {
            CyStringDescriptor strDesc = null;
            uint strIndex = 0;

            if (value == "") return strIndex;

            //Search for string in predefined array
            bool predefined = false;
            List<CyStringDescriptor> strDescList = GetStringDescList();
            for (int i = 0; i < strDescList.Count; i++)
            {
                if (strDescList[i].bString == value)
                {
                    predefined = true;
                    strDesc = strDescList[i];
                    break;
                }
            }

            if (!predefined)
            {
                strDesc = CreateNewStringDescriptor(value, this);
                ParamStringTreeChanged();
            }

            //General USBDescriptor-based index
            strIndex = GetStringDescriptorIndex(strDesc, this);
            return strIndex;
        }

        /// <summary>
        /// Finds the index of the special string that was selected in the descriptor.
        /// </summary>
        /// <param name="comboBox">Combobox where user selects the special string descriptor</param>
        /// <param name="type">Reference to the Parameters</param>
        /// <param name="parameters"></param>
        /// <returns>Unique index of the string</returns>
        public static byte SaveSpecialStringDescriptor(ComboBox comboBox, string type, CyUSBFSParameters parameters)
        {
            string strConfigKey = type;
            byte strIndex = 0;
            if ((comboBox.SelectedIndex < 0) && (comboBox.Text != ""))
            {
                CyDescriptorNode newNode;
                if (type == NODEKEY_STRING_SERIAL)
                {
                    newNode = parameters.m_stringTree.GetNodeByKey(strConfigKey);
                    ((CyStringDescriptor)newNode.Value).bString = comboBox.Text;
                }
                strIndex = Convert.ToByte(CyDescriptorNode.GetDescriptorIndex(strConfigKey));
            }
            else if (comboBox.SelectedIndex >= 0)
            {
                strIndex = Convert.ToByte(CyDescriptorNode.GetDescriptorIndex(strConfigKey));
            }
            return strIndex;
        }


        #endregion Manipulations with String descriptors

        #region Public Static functions

        /// <summary>
        /// Finds the index of the report that was selected in the descriptor.
        /// </summary>
        /// <param name="comboBox">Combobox where user selects the report</param>
        /// <param name="parameters">Reference to the Parameters</param>
        /// <returns>Unique index of the report</returns>
        public static uint SaveReportDescriptor(ComboBox comboBox, CyUSBFSParameters parameters)
        {
            CyHIDReportDescriptor reportDesc = null;
            string strConfigKey;
            uint strIndex = 0;

            if (comboBox.Text == "") return strIndex;


            reportDesc = (CyHIDReportDescriptor)comboBox.Items[comboBox.SelectedIndex];

            strConfigKey = parameters.m_hidReportTree.GetKeyByNode(reportDesc);
            if (strConfigKey != "")
            {
                strIndex = CyDescriptorNode.GetDescriptorIndex(strConfigKey);
            }
            return strIndex;
        }

        /// <summary>
        /// Determines if the string is a comment (empty sting or starts with "//").
        /// Used in HID reports.
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
        public static bool StringIsComment(string str)
        {
            bool res = false;
            if ((str.TrimStart(' ') == "") || str.TrimStart(' ').StartsWith("//"))
            {
                res = true;
            }
            return res;
        }

        public static bool ContainsOnlyHexChars(string str)
        {
            bool result = true;
            for (int i = 0; i < str.Length; i++)
            {
                result &= IsHexChar(str[i]);
            }
            return result;
        }

        public static bool IsHexChar(char c)
        {
            const string HEX_CHARS = "ABCDEFabcdef0123456789";
            return (HEX_CHARS.IndexOf(c) >= 0);
        }

        public static Int64 ConvertByteArrayToInt(List<byte> byteList, bool isUnsigned)
        {
            Int64 val = 0;
            bool isNegative = false;
            if (byteList.Count > 0)
            {
                if (!isUnsigned && byteList[byteList.Count - 1] > Math.Pow(2, 7))
                    isNegative = true;
                for (int i = byteList.Count; i < 8; i++)
                {
                    if (!isNegative) byteList.Add(0);
                    else byteList.Add(0xFF);
                }
                val = BitConverter.ToInt64(byteList.ToArray(), 0);
            }
            return val;
        }

        public static List<byte> ConvertIntToByteArray(Int64 val, bool isUnsigned)
        {
            List<byte> byteList = new List<byte>(BitConverter.GetBytes(val));
            //Remove extra bytes
            if (val >= 0)
            {
                while ((byteList[byteList.Count - 1] == 0) && (byteList.Count > 1))
                    byteList.RemoveAt(byteList.Count - 1);
            }
            else
            {
                while ((byteList[byteList.Count - 1] == 0xFF) && (byteList.Count > 1))
                    byteList.RemoveAt(byteList.Count - 1);
            }
            //For numbers such as 128(0x80) (with a significant high byte) add one more byte.
            if (!isUnsigned && Math.Abs(val) >= Math.Pow(2, (byteList.Count * 8 - 1)))
            {
                if (val >= 0) byteList.Add(0);
                else byteList.Add(0xFF);
            }
            // If value has 3 bytes, add 4th byte
            if (byteList.Count == 3)
            {
                if (val >= 0) byteList.Add(0);
                else byteList.Add(0xFF);
            }
            return byteList;
        }

        public static List<byte> ConvertInt3ToByteArray(Int64 val)
        {
            List<byte> byteList = ConvertIntToByteArray(val, false);
            while (byteList.Count < 3)
            {
                byteList.Add(0);
            }
            if (byteList.Count > 3)
                byteList.RemoveRange(3, byteList.Count - 3);
            return byteList;
        }

        public static bool CheckIntValue(string str, bool hex)
        {
            bool res;
            Int64 val;
            if (!hex)
            {
                res = Int64.TryParse(str, out val);
            }
            else
            {
                if (str.StartsWith("0x"))
                    str = str.Remove(0, 2);
                res = Int64.TryParse(str, NumberStyles.HexNumber, Application.CurrentCulture.NumberFormat, out val);
            }
            return res;
        }

        public static bool CheckIntRange(int val, int min, int max)
        {
            bool res = ((val >= min) && (val <= max)) ? true : false;
            return res;
        }

        public static void ChangeArrayLength(List<byte> arr, int len)
        {
            if (arr.Count < len)
            {
                int count = arr.Count;
                for (int i = 0; i < len - count; i++)
                    arr.Add(0);
            }
            else if (arr.Count > len)
                arr.RemoveRange(len, arr.Count - len);
        }

        public static int GetEPTransferType(CyEndpointDescriptor epDesc)
        {
            return (epDesc.bmAttributes & 0x03);
        }
        #endregion Public Static functions

        #region Public functions

        /// <summary>
        /// Fills Device, String and HIDReport trees with the default nodes.
        /// </summary>
        /// <param name="device">Apply to the m_deviceTree or no</param>
        /// <param name="str">Apply to the m_stringTree or no</param>
        /// <param name="hidReport">Apply to the m_hidReportTree or no</param>
        public void InitDescriptors(bool device, bool str, bool hidReport, bool audio, bool cdc, bool midi, bool msc)
        {
            if (device)
            {
                if (m_deviceTree.Nodes.Count > 0)
                    ParamDeviceTreeChanged();
                m_deviceTree.Nodes.Clear();
                m_deviceTree.AddNode(NODEKEY_DEVICE);
            }
            if (str)
            {
                if (m_stringTree.Nodes.Count > 0)
                    ParamStringTreeChanged();
                m_stringTree.Nodes.Clear();
                m_stringTree.Nodes.Clear();
                m_stringTree.AddNode(NODEKEY_STRING);
                m_stringTree.AddNode(NODEKEY_SPECIALSTRING);
            }
            if (hidReport)
            {
                if (m_hidReportTree.Nodes.Count > 0)
                    ParamHIDReportTreeChanged();
                m_hidReportTree.Nodes.Clear();
                m_hidReportTree.AddNode(NODEKEY_HIDREPORT);
            }
            if (audio)
            {
                if (m_audioTree.Nodes.Count > 0)
                    ParamAudioTreeChanged();
                m_audioTree.Nodes.Clear();
                m_audioTree.AddNode(NODEKEY_AUDIO);
            }
            if (cdc)
            {
                if (m_cdcTree.Nodes.Count > 0)
                    ParamCDCTreeChanged();
                m_cdcTree.Nodes.Clear();
                m_cdcTree.AddNode(NODEKEY_CDC);
            }
            if (midi)
            {
                if (m_midiTree.Nodes.Count > 0)
                    ParamMidiTreeChanged();
                m_midiTree.Nodes.Clear();
                m_midiTree.AddNode(NODEKEY_MIDI);
            }
            if (msc)
            {
                if (m_mscTree.Nodes.Count > 0)
                    ParamMscTreeChanged();
                m_mscTree.Nodes.Clear();
                m_mscTree.AddNode(NODEKEY_MSC);
            }
        }

        private void RecalcBInterfaceAndBAlternate(CyDescriptorNode node, bool isRecalcBInterface = true,
            bool isRecalcBAlternate = true)
        {
            byte interfaceIndex = 0;
            byte alternateIndex = 0;

            for (int i = 0; i < node.Nodes.Count; i++)
            {
                if (node.Nodes[i].m_value is CyInterfaceGeneralDescriptor)
                {
                    for (int j = 0; j < node.Nodes[i].Nodes.Count; j++)
                    {
                        CyInterfaceDescriptor interfaceDescr = node.Nodes[i].Nodes[j].m_value as CyInterfaceDescriptor;
                        if (interfaceDescr != null)
                        {
                            if (isRecalcBAlternate)
                                interfaceDescr.bAlternateSetting = alternateIndex;

                            if (isRecalcBInterface)
                                interfaceDescr.bInterfaceNumber = interfaceIndex;
                            alternateIndex++;
                        }
                    }

                    alternateIndex = 0;
                    interfaceIndex++;
                }

                RecalcBInterfaceAndBAlternate(node.Nodes[i], isRecalcBInterface, isRecalcBAlternate);
            }
        }

        /// <summary>
        /// Performs neccessary calculations in the descriptors when editing of descriptors is finished: 
        /// Removes unused controls;
        /// Sets string indexes;
        /// Updates interface numbers;
        /// Other.
        /// </summary>
        /// <param name="node"></param>
        public void RecalcDescriptors(CyDescriptorNode node)
        {
            if (node.Key == NODEKEY_DEVICE)
            {
                //Clean m_emptyFields array
                m_emptyFields.Clear();

                // Reset m_usedEp array 
                for (int i = 0; i < m_usedEp.Length; i++)
                {
                    m_usedEp[i] = false;
                }

                //Reset m_max_interfaces
                MaxInterfaces = 0;
                SetExtJackCount(0);

                IsLpm = CyUsb20ExtensionDeviceCapabilityDescriptor.IsAtLeastOneLpmEn(m_deviceTree.Nodes[0]);
                RecalcBInterfaceAndBAlternate(DeviceTree.Nodes[0]);
            }

            for (int i = 0; i < node.Nodes.Count; i++)
            {
                CyDescriptorNode node_child = node.Nodes[i];
                if (node_child.Value != null)
                {
                    switch (node_child.Value.bDescriptorType)
                    {
                        case CyUSBDescriptorType.DEVICE:
                            CyDeviceDescriptor deviceDescriptor = (CyDeviceDescriptor) node_child.Value;
                            deviceDescriptor.bNumConfigurations = 0;
                            for (int j = 0; j < node_child.Nodes.Count; j++)
                            {
                                if (node_child.Nodes[j].Value.bDescriptorType == CyUSBDescriptorType.CONFIGURATION)
                                    deviceDescriptor.bNumConfigurations++;
                                
                                deviceDescriptor.bcdUSB = node_child.Nodes[j].Value.bDescriptorType == 
                                    CyUSBDescriptorType.BOS ? CyDeviceDescriptor.BCDUSB_WITH_BOS :
                                    deviceDescriptor.bcdUSB = CyDeviceDescriptor.BCDUSB_WITHOUT_BOS;
                            }
                            
                            deviceDescriptor.bcdUSB = IsDescriptorPresent<CyBosDescriptor>(node_child) ? 
                                CyDeviceDescriptor.BCDUSB_WITH_BOS : CyDeviceDescriptor.BCDUSB_WITHOUT_BOS;

                            deviceDescriptor.iManufacturer = GetStringLocalIndex(deviceDescriptor.iwManufacturer);
                            deviceDescriptor.iProduct = GetStringLocalIndex(deviceDescriptor.iwProduct);
                            deviceDescriptor.sManufacturer = GetStringDescTextByIndex(deviceDescriptor.iwManufacturer);
                            deviceDescriptor.sProduct = GetStringDescTextByIndex(deviceDescriptor.iwProduct);
                            deviceDescriptor.sSerialNumber = (GetSerialDescriptor()).bString;
                            break;
                        case CyUSBDescriptorType.BOS:
                            CyBosDescriptor bosDescriptor = (CyBosDescriptor) node_child.Value;
                            bosDescriptor.bNumDeviceCaps = (byte)node_child.Nodes.Count;

                            ushort totLength = bosDescriptor.bLength;
                            for (int j = 0; j < node_child.Nodes.Count; j++)
                            {
                                CyDescriptorNode node_in_config = node_child.Nodes[j];
                                totLength += node_in_config.Value.bLength;
                            }
                            bosDescriptor.wTotalLength = totLength;
                            break;
                        case CyUSBDescriptorType.CONFIGURATION:
                            CyConfigDescriptor configDescriptor = (CyConfigDescriptor) node_child.Value;
                            configDescriptor.bNumInterfaces = GetInterfaceCount(node_child);

                            // Calculate max_interfaces 
                            if (configDescriptor.bNumInterfaces > MaxInterfaces)
                            {
                                MaxInterfaces =  configDescriptor.bNumInterfaces;
                            }

                            // Calculate bConfigurationValue
                            int configIndex = 0;
                            bool isBosPresent = false;
                            for (int j = 0; j < node.Nodes.Count; j++)
                            {
                                if (node.Nodes[j].Value.bDescriptorType == CyUSBDescriptorType.BOS)
                                {
                                    isBosPresent = true;
                                    continue;
                                }
                                else if (node_child == node.Nodes[j])
                                {
                                    if(isBosPresent)
                                        configIndex = j - 1;
                                    else
                                        configIndex = j;

                                    break;
                                }
                            }

                            configDescriptor.bConfigurationValue = configIndex >= 0 ? (byte)configIndex : (byte)0;

                            configDescriptor.iConfiguration = GetStringLocalIndex(configDescriptor.iwConfiguration);
                            configDescriptor.sConfiguration = 
                                GetStringDescTextByIndex(configDescriptor.iwConfiguration);
                            // Calculate the total length
                            ushort totalLength = configDescriptor.bLength;
                            for (int j = 0; j < node_child.Nodes.Count; j++)
                            {
                                CyDescriptorNode node_in_config = node_child.Nodes[j];
                                totalLength += node_in_config.Value.bLength;
                                for (int k = 0; k < node_in_config.Nodes.Count; k++)
                                {
                                    CyDescriptorNode node_in_interfaces = node_in_config.Nodes[k];
                                    totalLength += node_in_interfaces.Value.bLength;
                                    for (int l = 0; l < node_in_interfaces.Nodes.Count; l++)
                                    {
                                        CyDescriptorNode node_in_interface = node_in_interfaces.Nodes[l];
                                        totalLength += node_in_interface.Value.bLength;
                                        for (int m = 0; m < node_in_interface.Nodes.Count; m++)
                                        {
                                            CyDescriptorNode node_in_endpoint = node_in_interface.Nodes[m];
                                            totalLength += node_in_endpoint.Value.bLength;
                                        }
                                    }
                                }
                            }
                            configDescriptor.wTotalLength = totalLength;
                            break;
                        case CyUSBDescriptorType.INTERFACE:
                            CyInterfaceDescriptor interfaceDescriptor = (CyInterfaceDescriptor)node_child.Value;
                            //Calculate the number of Endpoints
                            byte numEndpt = 0;
                            for (int j = 0; j < node_child.Nodes.Count; j++)
                            {
                                CyDescriptorNode node_endpt = node_child.Nodes[j];
                                if (node_endpt.Value.bDescriptorType == CyUSBDescriptorType.ENDPOINT)
                                    numEndpt++;
                            }
                            //Calculate the number of External MIDI IN Jack, OUT Jack
                            if ((interfaceDescriptor.bInterfaceClass == 
                                 (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_AUDIO) &&
                                (interfaceDescriptor.bInterfaceSubClass == 
                                 (byte)CyUSBOtherTypes.CyAudioSubclassCodes.MIDISTREAMING))
                            {
                                byte numExtMidiIN = 0;
                                byte numExtMidiOUT = 0;
                                for (int j = 0; j < node_child.Nodes.Count; j++)
                                {
                                    CyDescriptorNode node_jack = node_child.Nodes[j];
                                    if (node_jack.Value is CyMSInJackDescriptor)
                                    {
                                        if (((CyMSInJackDescriptor)node_jack.Value).bJackType == 
                                              CyUSBOtherTypes.CyJackTypes.EXTERNAL)
                                            numExtMidiIN++;
                                    }
                                    else if (node_jack.Value is CyMSOutJackDescriptor)
                                    {
                                        if (((CyMSOutJackDescriptor)node_jack.Value).bJackType == 
                                              CyUSBOtherTypes.CyJackTypes.EXTERNAL)
                                            numExtMidiOUT++;
                                    }
                                }
                                SetExtJackCount(Math.Max(m_extJackCount, Math.Max(numExtMidiIN, numExtMidiOUT)));
                            }
                            interfaceDescriptor.bNumEndpoints = numEndpt;
                            interfaceDescriptor.iInterface = GetStringLocalIndex(interfaceDescriptor.iwInterface);
                            interfaceDescriptor.sInterface = GetStringDescTextByIndex(interfaceDescriptor.iwInterface);
                            // Set Interface Protocol for Audio 2.0
                            if (interfaceDescriptor.bInterfaceClass == 
                                 (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_AUDIO) 
                            {
                                bool isAudio20 = false;
                                for (int j = 0; j < node_child.Nodes.Count; j++)
                                {
                                    CyDescriptorNode node_cs = node_child.Nodes[j];
                                    if ((node_cs.Value.GetType()).ToString().EndsWith("_v2"))
                                    {
                                        isAudio20 = true;
                                        break;
                                    }
                                }
                                interfaceDescriptor.bInterfaceProtocol = isAudio20 ?
                                    (byte)CyUSBOtherTypes.CyAudioInterfaceProtocolCodes.IP_VERSION_02_00 : 
                                    (byte)CyUSBOtherTypes.CyAudioInterfaceProtocolCodes.INTERFACE_PROTOCOL_UNDEFINED;
                            }
                            
                            break;
                        case CyUSBDescriptorType.HID:
                            CyHIDDescriptor hidDescriptor = (CyHIDDescriptor)node_child.Value;
                            hidDescriptor.bNumDescriptors = 1;
                            hidDescriptor.bReportIndex = GetHIDReportLocalIndex(hidDescriptor.wReportIndex);

                            // Calculate wDescriptorLength
                            string reportKey = CyDescriptorNode.GetKeyByIndex(hidDescriptor.wReportIndex);
                            CyDescriptorNode nodeHIDReport = m_hidReportTree.GetNodeByKey(reportKey);
                            if (nodeHIDReport != null)
                            {
                                hidDescriptor.wDescriptorLength = 
                                                                ((CyHIDReportDescriptor)nodeHIDReport.Value).wLength;
                            }
                            else
                            {
                                hidDescriptor.wReportIndex = 0;
                            }

                            if ((hidDescriptor.wReportIndex == 0) && (!m_emptyFields.Contains(node_child.Key)))
                                m_emptyFields.Add(node_child.Key);
                            break;
                        case CyUSBDescriptorType.ENDPOINT:
                            CyEndpointDescriptor endpointDescriptor = (CyEndpointDescriptor)node_child.Value;
                            byte endpointNum = (byte)(endpointDescriptor.bEndpointAddress & 0x0F);
                            if (endpointNum < m_usedEp.Length)
                            {
                                m_usedEp[endpointNum] = true;
                            }
                            break;
                        case CyUSBDescriptorType.HID_REPORT:
                            CyHIDReportDescriptor hidRptDescriptor = (CyHIDReportDescriptor)node_child.Value;
                            ushort rptSize = 0;
                            for (int j = 0; j < node_child.Nodes.Count; j++)
                            {
                                CyDescriptorNode node_in_report = node_child.Nodes[j];
                                rptSize += ((CyHIDReportItemDescriptor)node_in_report.Value).Item.GetItemSize();
                            }
                            hidRptDescriptor.wLength = rptSize;
                            break;
                        case CyUSBDescriptorType.AUDIO:
                            // String indexes
                            try
                            {
                                Type nodeType = node_child.Value.GetType();
                                FieldInfo[] fi = nodeType.GetFields();
                                for (int j = 0; j < fi.Length; j++)
                                {
                                    if (fi[j].Name.StartsWith("iw"))
                                    {
                                        uint val = (uint) fi[j].GetValue(node_child.Value);
                                        string propName = fi[j].Name.Remove(0, 2).Insert(0, "i");
                                        PropertyInfo pi = nodeType.GetProperty(propName);
                                        if (pi != null)
                                            pi.SetValue(node_child.Value, GetStringLocalIndex(val), null);
                                    }
                                }
                            }
                            catch (Exception ex)
                            {
                                Debug.Assert(false, ex.ToString());
                            }
                            node_child.Value.UpdateLength();

                            // Calculate the total length of CyACHeaderDescriptor
                            if ((node_child.Value is CyACHeaderDescriptor) || 
                                (node_child.Value is CyACHeaderDescriptor_v2) ||
                                (node_child.Value is CyMSHeaderDescriptor))
                            {
                                ushort totalLengthAudio = 0;
                                for (int j = 0; j < node.Nodes.Count; j++)
                                {
                                    CyDescriptorNode node_audio = node.Nodes[j];
                                    if (node_audio.Value.bDescriptorType == CyUSBDescriptorType.AUDIO)
                                    {
                                        node_audio.Value.UpdateLength();
                                        totalLengthAudio += node_audio.Value.bLength;
                                    }
                                }
                                if (node_child.Value is CyACHeaderDescriptor)
                                {
                                    CyACHeaderDescriptor acHeaderDesc = (CyACHeaderDescriptor) node_child.Value;
                                    acHeaderDesc.wTotalLength = totalLengthAudio;
                                }
                                else if (node_child.Value is CyACHeaderDescriptor_v2)
                                {
                                    CyACHeaderDescriptor_v2 acHeaderDesc = (CyACHeaderDescriptor_v2)node_child.Value;
                                    acHeaderDesc.wTotalLength = totalLengthAudio;
                                }
                                else if (node_child.Value is CyMSHeaderDescriptor)
                                {
                                    CyMSHeaderDescriptor msHeaderDesc = (CyMSHeaderDescriptor)node_child.Value;
                                    msHeaderDesc.wTotalLength = totalLengthAudio;
                                }
                            }

                            break;
                    }
                }
                RecalcDescriptors(node_child);
            }
        }

        /// <summary>
        /// Calculates the total packet size of the Configuration Descriptor.
        /// </summary>
        /// <param name="configNode">The Configuration Descriptor</param>
        /// <returns>Total packet size</returns>
        public ushort GetSumPacketSize(CyDescriptorNode configNode)
        {
            ushort totalSize = 0;
            for (int i = 0; i < configNode.Nodes.Count; i++)
                for (int j = 0; j < configNode.Nodes[i].Nodes.Count; j++)
                {
                    CyDescriptorNode node_in_interface = configNode.Nodes[i].Nodes[j];
                
                    if (node_in_interface.Value is CyEndpointDescriptor)
                    {
                        totalSize += ((CyEndpointDescriptor)node_in_interface.Value).wMaxPacketSize;
                    }
                }
            return totalSize;
        }

        public bool CheckBootloaderReady()
        {
            bool res = false;
            // Parse device tree for all Interface descriptors and check if exists any one that has 
            // at least two endpoints: one In(EP2, MaxPktSize=64) and one Out(EP1, MaxPktSize=64).
            for (int i = 0; i < m_deviceTree.Nodes[0].Nodes.Count; i++)//device level
            {
                for (int j = 0; j < m_deviceTree.Nodes[0].Nodes[i].Nodes.Count; j++) // configuration level
                {
                    // alternate level
                    for (int k = 0; k < m_deviceTree.Nodes[0].Nodes[i].Nodes[j].Nodes.Count; k++) 
                    {
                        // interface level
                        for (int m = 0; m < m_deviceTree.Nodes[0].Nodes[i].Nodes[j].Nodes[k].Nodes.Count; m++)
                        {
                            CyDescriptorNode node = m_deviceTree.Nodes[0].Nodes[i].Nodes[j].Nodes[k].Nodes[m];
                            CyInterfaceDescriptor desc = (CyInterfaceDescriptor) node.Value;
                            
                            bool foundIN = false;
                            bool foundOUT = false;
                            for (int l = 0; l < node.Nodes.Count; l++)
                            {
                                if (node.Nodes[l].Value is CyEndpointDescriptor)
                                {
                                    CyEndpointDescriptor endptDesc = (CyEndpointDescriptor) node.Nodes[l].Value;
                                    if ((endptDesc.EndpointNum == CyUSBOtherTypes.CyEndptNumbers.EP1) &&
                                        (endptDesc.Direction == CyUSBOtherTypes.CyEndptDirections.OUT) &&
                                        (endptDesc.TransferType ==
                                                    CyUSBOtherTypes.CyEndptTransferTypes.TRANSFERTYPE_INTERRUPT) &&
                                        (endptDesc.wMaxPacketSize == CyEndpointDescriptor.MAX_PACKET_SIZE_GEN))
                                    {
                                        foundOUT = true;
                                    }
                                    else if ((endptDesc.EndpointNum == CyUSBOtherTypes.CyEndptNumbers.EP2) &&
                                             (endptDesc.Direction == CyUSBOtherTypes.CyEndptDirections.IN) &&
                                             (endptDesc.TransferType ==
                                                    CyUSBOtherTypes.CyEndptTransferTypes.TRANSFERTYPE_INTERRUPT) &&
                                             (endptDesc.wMaxPacketSize == CyEndpointDescriptor.MAX_PACKET_SIZE_GEN))
                                    {
                                        foundIN = true;
                                    }
                                }
                            }
                            if (foundIN && foundOUT)
                            {
                                res = true;
                                break;
                            }
                        }
                        if (res) break;
                    }
                    if (res) break;
                }
                if (res) break;
            }
            return res;
        }

        public void SetNodesISerialNumber()
        {
            bool m_showSerial = (GetSerialDescriptor()).bUsed;
            if (!m_showSerial)
            {
                // Set Serial Number in DeviceDescriptor to zero
                try
                {
                    for (int i = 0; i < m_deviceTree.Nodes[0].Nodes.Count; i++)
                    {
                        ((CyDeviceDescriptor)m_deviceTree.Nodes[0].Nodes[i].Value).iSerialNumber = 0;
                    }
                }
                catch (Exception)
                {
                    Debug.Assert(false);
                }
            }
            else
            {
                for (int i = 0; i < m_deviceTree.Nodes[0].Nodes.Count; i++)
                {
                    ((CyDeviceDescriptor)m_deviceTree.Nodes[0].Nodes[i].Value).iSerialNumber =
                       Convert.ToByte(CyDescriptorNode.GetDescriptorIndex(CyUSBFSParameters.NODEKEY_STRING_SERIAL));
                }
            }
        }

        /// <summary>
        /// Generate error when Endpoint MaxPacketSize is greater then 512 and EMM is not "DMA w/AutomaticMM".
        /// </summary>
        public bool CheckEPMaxPacketSize(CyDescriptorNode node)
        {
            bool res = true;

            if (EPMemoryMgmt == CyMemoryManagement.EP_DMAauto) 
                return true;
            
            if ((node.Value != null) && (node.Value.bDescriptorType == CyUSBDescriptorType.ENDPOINT))
            {
                CyEndpointDescriptor desc = (CyEndpointDescriptor)node.Value;
                if (desc.wMaxPacketSize > CyEndpointDescriptor.MAX_PACKET_SIZE_MANUAL_DMA)
                {
                    return false;
                }
            }
            else
            {
                for (int i = 0; i < node.Nodes.Count; i++)
                {
                    res &= CheckEPMaxPacketSize(node.Nodes[i]);
                }
            }
            return res;
        }

        /// <summary>
        /// Generate error when  total sum of the MaxPacketSize for all EPs in one Configuration is greater then 512 
        /// when EMM is "Manual (Static Allocation)" or "DMA with Manual BM (Static Allocation)".
        /// </summary>
        public bool CheckSumEpBuffSizeStatAlloc(CyDescriptorNode node)
        {
            bool res = true;

            if (EPMemoryMgmt == CyMemoryManagement.EP_DMAauto ||
                (EPMemoryAlloc != CyMemoryAllocation.MA_Static && EPMemoryMgmt == CyMemoryManagement.EP_Manual))
                return true;

            if (node.Value != null && node.Value.bDescriptorType == CyUSBDescriptorType.DEVICE)
            {
                for (int configNum = 0; configNum < node.Nodes.Count; configNum++)
                {
                    if (node.Nodes[configNum].Value.bDescriptorType != CyUSBDescriptorType.CONFIGURATION)
                        continue;

                    List<CyDescriptorNode> endPoinNodes = GetChildNodes(node.Nodes[configNum], 
                        CyUSBDescriptorType.ENDPOINT);
                    ushort[] epMaxPackedSizes = new ushort[CyEndpointDescriptor.MAX_EP_NUM + 1];

                    for (int i = 0; i < endPoinNodes.Count; i++)
                    {
                        CyEndpointDescriptor ep = (CyEndpointDescriptor)endPoinNodes[i].Value;

                        if (epMaxPackedSizes[(int)ep.EndpointNum] < ep.wMaxPacketSize)
                            epMaxPackedSizes[(int)ep.EndpointNum] = ep.wMaxPacketSize;
                    }

                    int sum = 0;
                    for (int i = 0; i < epMaxPackedSizes.Length; i++)
                    {
                        sum += epMaxPackedSizes[i];
                        if (epMaxPackedSizes[i] % 2 != 0 && IsPSoC4AL_IpBlock && Gen16bitEpAccessApi)
                            sum++;
                    }
                    if (sum > CyEndpointDescriptor.MAX_PACKET_SIZE_MANUAL_DMA)
                    {
                        return false;
                    }
                }
            }
            else
            {
                for (int i = 0; i < node.Nodes.Count; i++)
                {
                    res &= CheckSumEpBuffSizeStatAlloc(node.Nodes[i]);
                }
            }

            return res;
        }

        /// <summary>
        /// Generate error when  total sum of the MaxPacketSize for all EPs in one Alterante Setting is greater then 
        /// 512 when EMM is not "DMA w/AutomaticMM".
        /// </summary>
        public bool CheckSumEpBuffSizeNotAutoDma(CyDescriptorNode node)
        {
            bool res = true;

            if (EPMemoryMgmt != CyMemoryManagement.EP_Manual || EPMemoryAlloc != CyMemoryAllocation.MA_Dynamic)
                return true;

            if ((node.Value != null) && (node.Value.bDescriptorType == CyUSBDescriptorType.INTERFACE))
            {
                int sum = 0;
                for (int i = 0; i < node.Nodes.Count; i++)
                {
                    if (node.Nodes[i].Value.bDescriptorType == CyUSBDescriptorType.ENDPOINT)
                    {
                        CyEndpointDescriptor desc = (CyEndpointDescriptor)node.Nodes[i].Value;
                        sum += desc.wMaxPacketSize;
                        if (desc.wMaxPacketSize % 2 != 0 && IsPSoC4AL_IpBlock && Gen16bitEpAccessApi)
                            sum++;
                    }
                }
                if (sum > CyEndpointDescriptor.MAX_PACKET_SIZE_MANUAL_DMA)
                {
                    return false;
                }
            }
            else
            {
                for (int i = 0; i < node.Nodes.Count; i++)
                {
                    res &= CheckSumEpBuffSizeNotAutoDma(node.Nodes[i]);
                }
            }
            return res;
        }

        /// <summary>
        /// Generate error when  total sum of the MaxPacketSize for all EPs in one Device is greater then 1100. 
        /// </summary>
        public bool CheckSumEPMaxPacketSizeAll(CyDescriptorNode node)
        {
            bool res = true;

            if ((node.Value != null) && (node.Value.bDescriptorType == CyUSBDescriptorType.INTERFACE))
            {
                int sum = 0;
                for (int i = 0; i < node.Nodes.Count; i++)
                {
                    if (node.Nodes[i].Value.bDescriptorType == CyUSBDescriptorType.ENDPOINT)
                    {
                        CyEndpointDescriptor desc = (CyEndpointDescriptor)node.Nodes[i].Value;
                        sum += desc.wMaxPacketSize;
                    }
                }
                if (sum > CyEndpointDescriptor.MAX_PACKET_SIZE_SUM_DEVICE)
                {
                    return false;
                }
            }
            else
            {
                for (int i = 0; i < node.Nodes.Count; i++)
                {
                    res &= CheckSumEPMaxPacketSizeAll(node.Nodes[i]);
                }
            }
            return res;
        }

        /// <summary>
        /// Generate error when Bulk Endpoint MaxPacketSize is not from the list {8, 16, 32, 64}.
        /// </summary>
        public bool CheckEPBulkMaxPacketSize(CyDescriptorNode node)
        {
            bool res = true;

            if ((node.Value != null) && (node.Value.bDescriptorType == CyUSBDescriptorType.ENDPOINT))
            {
                CyEndpointDescriptor desc = (CyEndpointDescriptor)node.Value;
                if ((desc.TransferType == CyUSBOtherTypes.CyEndptTransferTypes.TRANSFERTYPE_BULK) &&
                    (CyEndpointDescriptor.PossibleMaxPacketValues.Contains(desc.wMaxPacketSize) == false))
                {
                    return false;
                }
            }
            else
            {
                for (int i = 0; i < node.Nodes.Count; i++)
                {
                    res &= CheckEPBulkMaxPacketSize(node.Nodes[i]);
                }
            }
            return res;
        }

        /// <summary>
        /// Generate error when Interrupt Endpoint Interval (ms) value is 0.
        /// </summary>
        public bool CheckEPInterruptInterval(CyDescriptorNode node)
        {
            bool res = true;

            if ((node.Value != null) && (node.Value.bDescriptorType == CyUSBDescriptorType.ENDPOINT))
            {
                CyEndpointDescriptor desc = (CyEndpointDescriptor)node.Value;

                if ((desc.TransferType == CyUSBOtherTypes.CyEndptTransferTypes.TRANSFERTYPE_INTERRUPT) &&
                    desc.bInterval == 0)
                {
                    return false;
                }
            }
            else
            {
                for (int i = 0; i < node.Nodes.Count; i++)
                {
                    res &= CheckEPInterruptInterval(node.Nodes[i]);
                }
            }
            return res;
        }

        /// <summary>
        /// Generate error when Container Id value is wrong.
        /// </summary>
        public bool CheckContainerIdFormat(CyDescriptorNode node)
        {
            bool res = true;

            if ((node.Value != null) && (node.Value.bDescriptorType == CyUSBDescriptorType.CONTAINER_ID))
            {
                CyContainerIdDescriptor desc = (CyContainerIdDescriptor)node.Value;

                if (!CyUSBFSParameters.ContainsOnlyHexChars(desc.ContainerId))
                {
                    return false;
                }
            }
            else
            {
                for (int i = 0; i < node.Nodes.Count; i++)
                {
                    res &= CheckContainerIdFormat(node.Nodes[i]);
                }
            }
            return res;
        }

        /// <summary>
        /// Generate error when Alternate Setting contains Endpoints with equal Endpoint Number
        /// </summary>
        public bool CheckUniqueEndpointNumber(CyDescriptorNode parentNode)
        {
            bool res = true;

            if ((parentNode.Value != null) && (parentNode.Value.bDescriptorType == CyUSBDescriptorType.INTERFACE))
            {
                for (int i = 0; i < parentNode.Nodes.Count; i++)
                {
                    CyEndpointDescriptor ep1 = parentNode.Nodes[i].m_value as CyEndpointDescriptor;
                    if (ep1 == null)
                        continue;

                    for (int j = i + 1; j < parentNode.Nodes.Count; j++)
                    {
                        CyEndpointDescriptor ep2 = parentNode.Nodes[j].m_value as CyEndpointDescriptor;
                        if (ep2 == null)
                            continue;

                        if (ep1.EndpointNum == ep2.EndpointNum)
                            return false;
                    }
                }
            }
            else
            {
                for (int i = 0; i < parentNode.Nodes.Count; i++)
                {
                    res &= CheckUniqueEndpointNumber(parentNode.Nodes[i]);
                }
            }
            return res;
        }

        /// <summary>
        /// Generate error when Battery Charging Detection is selected for not available devices
        /// </summary>
        public bool CheckBattChargDetectDevicesSupport()
        {
            if (!IsPSoC4AL_IpBlock && EnableBattChargDetect)
            {
                return false;
            }

            return true;
        }

        /// <summary>
        /// Generate error when VBUS Power Pad is selected for not available devices
        /// </summary>
        public bool CheckVbusPowerPadDevicesSupport()
        {
            if (!IsPSoC4AL_IpBlock && PowerPad_vbus && Mon_vbus)
            {
                return false;
            }

            return true;
        }

        /// <summary>
        /// Generate error when USB descriptor is present without interface descriptor
        /// </summary>
        public CyCustErr CheckAllDeviceDescsAreFull(CyDescriptorNode node)
        {
            if (node.Value is CyDeviceDescriptor && node.Nodes.Count == 0)
                return new CyCustErr(Properties.Resources.ERR_DEVICE_DESCRIPTOR_NOT_FULL);
            if (node.Value is CyDeviceDescriptor && node.Nodes.Count == 1 && 
                node.Nodes[0].Value.bDescriptorType == CyUSBDescriptorType.BOS)
                return new CyCustErr(Properties.Resources.ERR_DEVICE_DESCRIPTOR_NOT_FULL);
            else if (node.Value is CyConfigDescriptor && node.Nodes.Count == 0)
                return new CyCustErr(Properties.Resources.ERR_CONFIG_DESCRIPTOR_NOT_FULL);
            else if (node.Value is CyInterfaceGeneralDescriptor && node.Nodes.Count == 0)
                return new CyCustErr(Properties.Resources.ERR_INTERFACE_DESCRIPTOR_NOT_FULL);

            for (int i = 0; i < node.Nodes.Count; i++)
            {
                CyCustErr custErr = CheckAllDeviceDescsAreFull(node.Nodes[i]);
                if (custErr != CyCustErr.OK)
                    return custErr;
            }

            return CyCustErr.OK;
        }

        /// <summary>
        /// Generate error when BOS descriptor is not available for the selected devices
        /// </summary>
        public bool CheckBosDescIsPresent(CyDescriptorNode node)
        {
            if (node.Value is CyBosDescriptor)
                return true;

            for (int i = 0; i < node.Nodes.Count; i++)
            {
                if (CheckBosDescIsPresent(node.Nodes[i]))
                    return true;
            }

            return false;
        }

        /// <summary>
        /// Generate error when device is Bus Powered and Max Power is set as zero.
        /// </summary>
        public bool CheckMaxPower(CyDescriptorNode node)
        {
            CyConfigDescriptor config = node.Value as CyConfigDescriptor;
            if (config != null)
            {
                bool isBusPowered =  (config.bmAttributes & (1 << CyConfigDescriptor.DEVICE_POWER_OFFSET)) == 0;

                if (config.bMaxPower == 0 && isBusPowered)
                    return true;
            }

            for (int i = 0; i < node.Nodes.Count; i++)
            {
                if (CheckMaxPower(node.Nodes[i]))
                    return true;
            }

            return false;
        }
        
        #endregion Public functions

        #region Private functions

        /// <summary>
        /// Get all child nodes with selected type.
        /// </summary>
        private List<CyDescriptorNode> GetChildNodes(CyDescriptorNode parentNode, CyUSBDescriptorType desctType)
        {
            List<CyDescriptorNode> endPoints = new List<CyDescriptorNode>();

            for (int i = 0; i < parentNode.Nodes.Count; i++)
            {
                if (parentNode.Nodes[i].Value.bDescriptorType == desctType)
                    endPoints.Add(parentNode.Nodes[i]);

                endPoints.AddRange(GetChildNodes(parentNode.Nodes[i], desctType));
            }

            return endPoints;
        }

        /// <summary>
        /// Determine if Descriptor with selected Type is present in node root
        /// </summary>
        private bool IsDescriptorPresent<DescriptorType>(CyDescriptorNode node)
        {
            if (node.Value is DescriptorType)
                return true;

            for (int i = 0; i < node.Nodes.Count; i++)
            {
                if (IsDescriptorPresent<DescriptorType>(node.Nodes[i]))
                    return true;
            }

            return false;
        }

        /// <summary>
        /// Returns the index of the String Descriptor in the array of String Descriptors. 
        /// This index is used in API generation.
        /// </summary>
        /// <param name="keyIndex">Unique internal index</param>
        /// <returns>Index that is used in API generation</returns>
        private byte GetStringLocalIndex(uint keyIndex)
        {
            byte localIndex = 0;
            if (keyIndex > 0)
            {
                for (byte i = 0; i < m_stringTree.Nodes[0].Nodes.Count; i++)
                {
                    if (CyDescriptorNode.GetDescriptorIndex(m_stringTree.Nodes[0].Nodes[i].Key) == keyIndex)
                    {
                        localIndex = i;
                        break;
                    }
                }
            }
            return localIndex;
        }

        private string GetStringDescTextByIndex(uint keyIndex)
        {
            string res = null;
            if (keyIndex > 0)
            {
                string configStrKey = CyDescriptorNode.GetKeyByIndex(keyIndex);
                CyDescriptorNode node = m_stringTree.GetNodeByKey(configStrKey);
                if (node != null)
                {
                    res = ((CyStringDescriptor)node.Value).bString;
                }
            }
            return res;
        }

        /// <summary>
        /// Returns the index of the HID Report Descriptor in the array of HID Report Descriptors. 
        /// This index is used in API generation.
        /// </summary>
        /// <param name="keyIndex">Unique internal index</param>
        /// <returns>Index that is used in API generation</returns>
        private byte GetHIDReportLocalIndex(uint keyIndex)
        {
            byte localIndex = 0;
            if (keyIndex > 0)
            {
                for (byte i = 0; i < m_hidReportTree.Nodes[0].Nodes.Count; i++)
                {
                    if (CyDescriptorNode.GetDescriptorIndex(m_hidReportTree.Nodes[0].Nodes[i].Key) == keyIndex)
                    {
                        localIndex = (byte) (i + 1);
                        break;
                    }
                }
            }
            return localIndex;
        }

        /// <summary>
        /// Calculates the number of interfaces in Configuration descriptor
        /// </summary>
        /// <param name="configNode"></param>
        /// <returns></returns>
        public static byte GetInterfaceCount(CyDescriptorNode configNode)
        {
            byte count = 0;
            for (int j = 0; j < configNode.Nodes.Count; j++)
            {
                if (configNode.Nodes[j].Value.bDescriptorType == CyUSBDescriptorType.ALTERNATE)
                    count++;
            };
            return count;
        }

        /// <summary>
        /// For compability with the previous versions, checks 
        /// the presence of the ALTERNATE node in the Device Descriptor tree.
        /// </summary>
        /// <param name="dTree">Device Descriptor tree</param>
        private void CheckOldFormatCompability(CyDescriptorTree dTree)
        {
            bool oldFormat = false;
            for (int i = 0; i < dTree.Nodes.Count; i++) // Level 1
                for (int j = 0; j < dTree.Nodes[i].Nodes.Count; j++) // Level 2 - Device
                    for (int k = 0; k < dTree.Nodes[i].Nodes[j].Nodes.Count; k++) // Level 3 - Configuration
                        for (int m = 0; m < dTree.Nodes[i].Nodes[j].Nodes[k].Nodes.Count; m++) // Level 4 - Int.
                        {
                            CyDescriptorNode node = dTree.Nodes[i].Nodes[j].Nodes[k].Nodes[m];
                            if ((node.Value.bDescriptorType != CyUSBDescriptorType.ALTERNATE) &&
                                (node.Value.bDescriptorType != CyUSBDescriptorType.INTERFACE_ASSOCIATION) &&
                                (node.Value.bDescriptorType != CyUSBDescriptorType.DEVICE_CAPABILITY) &&
                                (node.Value.bDescriptorType != CyUSBDescriptorType.USB20_EXTENSION_DEVICE_CAPABILITY) &&
                                (node.Value.bDescriptorType != CyUSBDescriptorType.CONTAINER_ID))
                            {
                                oldFormat = true;
                            }
                        }
            //If the tree is in old format, add a node layer
            if (oldFormat)
            {
                for (int i = 0; i < dTree.Nodes.Count; i++) // Level 1
                    for (int j = 0; j < dTree.Nodes[i].Nodes.Count; j++) // Level 2 - Device
                        for (int k = 0; k < dTree.Nodes[i].Nodes[j].Nodes.Count; k++) // Level 3 - Configuration
                        {
                            // Search for interface numbers
                            List<byte> interfaceNums = new List<byte>();
                            for (int m = 0; m < dTree.Nodes[i].Nodes[j].Nodes[k].Nodes.Count; m++)
                                // Level 4 - Interface
                            {
                                CyDescriptorNode node = dTree.Nodes[i].Nodes[j].Nodes[k].Nodes[m];
                                byte interfaceNum = ((CyInterfaceDescriptor) node.Value).bInterfaceNumber;
                                if (!interfaceNums.Contains(interfaceNum))
                                    interfaceNums.Add(interfaceNum);
                            }
                            interfaceNums.Sort();

                            // Add interfaces to tree and attach alternate to them
                            for (int m = 0; m < interfaceNums.Count; m++)
                            {
                                CyDescriptorNode newNode = dTree.AddNode(dTree.Nodes[i].Nodes[j].Nodes[k].Key);
                                newNode.Nodes.Clear();
                                for (int n = 0; n < dTree.Nodes[i].Nodes[j].Nodes[k].Nodes.Count; n++)
                                {
                                    CyDescriptorNode interfaceNode = dTree.Nodes[i].Nodes[j].Nodes[k].Nodes[n];
                                    if ((interfaceNode.Value.bDescriptorType == CyUSBDescriptorType.INTERFACE) &&
                                        (((CyInterfaceDescriptor) interfaceNode.Value).bInterfaceNumber ==
                                         interfaceNums[m]))
                                    {
                                        dTree.Nodes[i].Nodes[j].Nodes[k].Nodes.Remove(interfaceNode);
                                        newNode.Nodes.Add(interfaceNode);
                                        n--;
                                    }
                                }
                            }
                        }
            }
        }

        /// <summary>
        /// For compability with the previous versions, checks
        /// if MS OS String Descriptor has the constant value. 
        /// </summary>
        /// <param name="sTree">String Descriptor tree</param>
        private void CheckStringOldFormatCompability(CyDescriptorTree sTree)
        {
            // Check if MS OS String Descriptor has its default value
            ((CyStringDescriptor) sTree.Nodes[1].Nodes[1].Value).bString = CyUSBFSParameters.MSOS_STRING;
        }

        /// <summary>
        /// For compatibility with previous versions, assigns correct 
        /// usage values list to USAGE HID report items.
        /// </summary>
        private void RestoreHIDReportUsageList()
        {
            for (int i = 0; i < m_hidReportTree.Nodes[0].Nodes.Count; i++)
			{
                UInt16 lastUsagePage = 0;
                for (int j = 0; j < m_hidReportTree.Nodes[0].Nodes[i].Nodes.Count; j++)
                {
                    try
                    {
                        CyHidReportItem item =
                            ((CyHIDReportItemDescriptor)m_hidReportTree.Nodes[0].Nodes[i].Nodes[j].Value).Item;
                        if ((item.Name == CyHidReportItem.RPTITEM_USAGE_PAGE) && (item.m_value.Count == 2))
                        {
                            lastUsagePage = item.m_value[1];
                        }
                        if ((item.Name == CyHidReportItem.RPTITEM_USAGE) && 
                            (item.m_valuesList.Count == CyHIDReportItemTables.ValuesGenericDesktopPage.Length/2))
                        {
                            CyHidDescriptorPage.SetListForItem(item, lastUsagePage);
                        }
                    }
                    catch
                    {
                        Debug.Assert(false);
                    }
                }
			}
        }

        /// <summary>
        /// Generates the list of strings available in the drop down list in property grid. 
        /// The list needs to be updated each time when string descriptors are changed
        /// </summary>
        public void RefreshStringsDropDownList()
        {
            CyStringDescConverter.m_strDescList = GetStringsList();
        }

        private static string GetTemplateFileExt(CyUSBDescriptorType kind, bool open)
        {
            string ext = String.Empty;
            switch (kind)
            {
                case CyUSBDescriptorType.DEVICE:
                    ext = "Device Descriptor Template Files (*.dev.xml)|*.dev.xml|";
                    break;
                case CyUSBDescriptorType.CONFIGURATION:
                    ext = "Configuration Descriptor Template Files (*.cfg.xml)|*.cfg.xml|";
                    break;
                case CyUSBDescriptorType.INTERFACE:
                    ext = "Interface Descriptor Template Files (*.inf.xml)|*.inf.xml|";
                    break;
                case CyUSBDescriptorType.HID_REPORT:
                    ext = "HID Template Files (*.hid.xml)|*.hid.xml|";
                    if (open)
                        ext += "HID Descriptor Tool (*.hid, *.dat, *.h)|*.hid;*.dat;*.h|";
                    break;
                case CyUSBDescriptorType.AUDIO:
                    ext = "Audio Interface Descriptor Template Files (*.audio.xml)|*.audio.xml|";
                    break;
                case CyUSBDescriptorType.MIDI:
                    ext = "MIDI Interface Descriptor Template Files (*.midi.xml)|*.midi.xml|";
                    break;
                case CyUSBDescriptorType.CDC:
                    ext = "CDC Interface Descriptor Template Files (*.cdc.xml)|*.cdc.xml|";
                    break;
                case CyUSBDescriptorType.MSC:
                    ext = "MSC Interface Descriptor Template Files (*.msc.xml)|*.msc.xml|";
                    break;
                case CyUSBDescriptorType.ALL:
                    ext = "Descriptor Tree Template Files (*.root.xml)|*.root.xml|";
                    break;
                case CyUSBDescriptorType.ENDPOINT:
                    ext = "Endpoint Descriptor Template Files (*.ep.xml)|*.ep.xml|";
                    break;
                case CyUSBDescriptorType.INTERFACE_ASSOCIATION:
                    ext = "Interface Association Descriptor Template Files (*.iad.xml)|*.iad.xml|";
                    break;
                case CyUSBDescriptorType.USB20_EXTENSION_DEVICE_CAPABILITY:
                    ext = "USB 2.0 Extension Descriptor Template Files (*.ext.xml)|*.ext.xml|";
                    break;
                case CyUSBDescriptorType.CONTAINER_ID:
                    ext = "Container ID Descriptor Template Files (*.cid.xml)|*.cid.xml|";
                    break;
            }
            return ext;
        }

        public List<string> GetTemplateFilesList(CyUSBDescriptorType descType)
        {
            List<string> files = new List<string>();
            string extension = string.Empty;

            switch (descType)
            {
                case CyUSBDescriptorType.HID: extension = "*.hid.xml"; break;
                case CyUSBDescriptorType.AUDIO: extension = "*.audio.xml"; break;
                case CyUSBDescriptorType.MIDI: extension = "*.midi.xml"; break;
                case CyUSBDescriptorType.CDC: extension = "*.cdc.xml"; break;
                case CyUSBDescriptorType.MSC: extension = "*.msc.xml"; break;
            }

            if (Directory.Exists(templatePath))
            {
                string[] filePaths = Directory.GetFiles(templatePath, extension, SearchOption.AllDirectories);
                files.AddRange(filePaths);
            }
            return files;
        }
        
        #endregion Private functions
    }

    //=================================================================================================================
    /// <summary>
    /// Describes a kind of Settings Panel for the HID Report Item.
    /// </summary>
    [XmlType("HIDReportItemKind")]
    public enum CyHidReportItemKind
    {
        [XmlEnum("Bits"), Description("Bits")]
        BITS,
        [XmlEnum("List"), Description("List")]
        LIST,
        [XmlEnum("Int"), Description("Int")]
        INT,
        [XmlEnum("Unit"), Description("Unit")]
        UNIT,
        [XmlEnum("None"), Description("None")]
        NONE,
        [XmlEnum("Custom"), Description("Custom")]
        CUSTOM
    } ;

    //=================================================================================================================

    #region CyCustomToolStripColors class
    /// <summary>
    /// CyCustomToolStripColors class is used to define colors for the toolStripMenu 
    /// </summary>
    internal class CyCustomToolStripColors : ProfessionalColorTable
    {
        public override Color ToolStripGradientBegin
        {
            get { return SystemColors.Control; }
        }

        public override Color ToolStripGradientMiddle
        {
            get { return SystemColors.Control; }
        }

        public override Color ToolStripGradientEnd
        {
            get { return SystemColors.ControlDark; }
        }

        public override Color ToolStripBorder
        {
            get { return SystemColors.ControlDark; }
        }

        public override Color ToolStripPanelGradientEnd
        {
            get { return SystemColors.ControlDark; }
        }
    }

    #endregion CyCustomToolStripColors class


    static class CyEnumTool
    {
        /// <summary>
        /// Converts enum description to value
        /// </summary>
        /// <param name="value"></param>
        /// <param name="_enumType"></param>
        /// <returns></returns>
        public static object GetEnumValue(object value, Type _enumType)
        {
            foreach (FieldInfo fi in _enumType.GetFields())
            {
                DescriptionAttribute dna =
                (DescriptionAttribute)Attribute.GetCustomAttribute(
                fi, typeof(DescriptionAttribute));

                if ((dna != null) && (value.ToString() == (string)dna.Description))
                    return Enum.Parse(_enumType, fi.Name);
            }
            return Enum.Parse(_enumType, value.ToString());
        }

        /// <summary>
        /// Converts enum value to description
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public static string GetEnumDesc(object value)
        {
            Type _enumType = value.GetType();
            FieldInfo fi = _enumType.GetField(Enum.GetName(_enumType, value));
            DescriptionAttribute dna =
                (DescriptionAttribute)Attribute.GetCustomAttribute(
                fi, typeof(DescriptionAttribute));

            if (dna != null)
                return dna.Description;
            else
                return value.ToString();
        }

        /// <summary>
        /// Gets all enum descriptions
        /// </summary>
        /// <param name="_enumType"></param>
        /// <returns></returns>
        public static string[] GetEnumDescList(Type _enumType)
        {
            List<string> res = new List<string>();
            foreach (object item in Enum.GetValues(_enumType))
            {
                res.Add(GetEnumDesc(item));
            }
            return res.ToArray();
        }

        public static void ChangeBrowsableAttributeValue(object sender, string propertyName, bool newValue)
        {
            try
            {
                PropertyDescriptor descriptor = TypeDescriptor.GetProperties(sender.GetType())[propertyName];
                BrowsableAttribute attribute = (BrowsableAttribute)
                                              descriptor.Attributes[typeof(BrowsableAttribute)];
                FieldInfo fieldToChange = attribute.GetType().GetField("browsable",
                                                 System.Reflection.BindingFlags.NonPublic |
                                                 System.Reflection.BindingFlags.Instance);
                fieldToChange.SetValue(attribute, newValue);
            }
            catch
            {
                Debug.Assert(false);
            }
        }
    }
    //=================================================================================================================

}
