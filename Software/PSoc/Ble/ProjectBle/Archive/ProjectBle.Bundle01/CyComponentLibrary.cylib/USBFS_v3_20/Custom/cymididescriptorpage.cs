using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;

namespace USBFS_v3_20
{
    public partial class CyMidiDescriptorPage : CyBaseDescriptorPage
    {
        #region Constructors

        public CyMidiDescriptorPage()
        {
            InitializeComponent();
        }

        public CyMidiDescriptorPage(CyUSBFSParameters parameters)
            : base(parameters, CyUSBDescriptorType.MIDI)
        {
            InitializeComponent();
            InitAdditionalCheckBoxes();
        }

        #endregion Constructors

        //------------------------------------------------------------------------------------------------------------

        #region CyEditingWrapperControl override
        public override string TabName
        {
            get { return CyCustomizer.PARAM_TAB_NAME_MIDI; }
        }

        public override IEnumerable<CyCustErr> GetErrors()
        {
            // Save all changes before closing the customizer
            m_parameters.SerializedMidiDesc = m_parameters.SerializeDescriptorTree(m_parameters.MidiTree);

            return base.GetErrors();
        }
        #endregion

        //------------------------------------------------------------------------------------------------------------

        #region Initialization

        public void InitAdditionalCheckBoxes()
        {
            checkBoxEnableMIDIApi.Checked = m_parameters.EnableMIDIApi;
            checkBoxMode.Checked = m_parameters.Mode;
        }

        /// <summary>
        /// Initializes m_reportItems list and fills listBoxItems listBox.
        /// </summary>
        protected override void InitItems()
        {
            m_ItemsList = new List<CyUSBDescriptor>();

            m_ItemsList.Add(new CyAudioInterfaceDescriptor());
            m_ItemsList.Add(new CyAudioInterfaceDescriptor());

            for (int i = 0; i < 2; i++)
            {
                CyInterfaceDescriptor newDesc = (CyAudioInterfaceDescriptor)m_ItemsList[i];
                newDesc.bInterfaceClass = (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_AUDIO;
                newDesc.bInterfaceSubClass = (i == 0)
                                                 ? (byte)CyUSBOtherTypes.CyAudioSubclassCodes.AUDIOCONTROL
                                                 : (byte)CyUSBOtherTypes.CyAudioSubclassCodes.MIDISTREAMING;
            }

            m_ItemsList.Add(new CyACHeaderDescriptor());
            m_ItemsList.Add(new CyACInputTerminalDescriptor());
            m_ItemsList.Add(new CyACOutputTerminalDescriptor());
            m_ItemsList.Add(new CyACMixerUnitDescriptor());
            m_ItemsList.Add(new CyACSelectorUnitDescriptor());
            m_ItemsList.Add(new CyACFeatureUnitDescriptor());
            m_ItemsList.Add(new CyACProcessingUnitDescriptor());
            m_ItemsList.Add(new CyACExtensionDescriptor());

            m_ItemsList.Add(new CyACHeaderDescriptor_v2());
            m_ItemsList.Add(new CyACClockSourceDescriptor_v2());
            m_ItemsList.Add(new CyACClockSelectorDescriptor_v2());
            m_ItemsList.Add(new CyACClockMultiplierDescriptor_v2());
            m_ItemsList.Add(new CyACInputTerminalDescriptor_v2());
            m_ItemsList.Add(new CyACOutputTerminalDescriptor_v2());
            m_ItemsList.Add(new CyACMixerUnitDescriptor_v2());
            m_ItemsList.Add(new CyACSelectorUnitDescriptor_v2());
            m_ItemsList.Add(new CyACFeatureUnitDescriptor_v2());
            m_ItemsList.Add(new CyACSamplingRateConverterDescriptor_v2());
            m_ItemsList.Add(new CyACEffectUnitDescriptor_v2());
            m_ItemsList.Add(new CyACProcessingUnitDescriptor_v2());
            m_ItemsList.Add(new CyACExtensionDescriptor_v2());

            m_ItemsList.Add(new CyMSHeaderDescriptor());
            m_ItemsList.Add(new CyMSInJackDescriptor());
            m_ItemsList.Add(new CyMSOutJackDescriptor());
            m_ItemsList.Add(new CyMSElementDescriptor());

            m_ItemsList.Add(new CyAudioEndpointDescriptor());
            m_ItemsList.Add(new CyMSEndpointDescriptor());
        }

        protected override bool IncludeACListItems(CyDescriptorNode interfaceNode)
        {
            bool includeAC = false;
            if (interfaceNode.Value is CyAudioInterfaceDescriptor)
            {
                if (((CyAudioInterfaceDescriptor)interfaceNode.Value).bInterfaceSubClass ==
                    (byte)CyUSBOtherTypes.CyAudioSubclassCodes.AUDIOCONTROL)
                    includeAC = true;
            }
            return includeAC;
        }

        protected override bool IncludeASListItems(CyDescriptorNode interfaceNode)
        {
            bool includeMS = false;
            if (interfaceNode.Value is CyAudioInterfaceDescriptor)
            {
                if (((CyAudioInterfaceDescriptor)interfaceNode.Value).bInterfaceSubClass ==
                    (byte)CyUSBOtherTypes.CyAudioSubclassCodes.MIDISTREAMING)
                    includeMS = true;
            }
            return includeMS;
        }

        protected override bool IncludeASEPListItems(CyDescriptorNode interfaceNode, CyDescriptorNode selectedNode)
        {
            bool includeASEP = false;
            if (interfaceNode.Value is CyAudioInterfaceDescriptor)
            {
                if (((CyAudioInterfaceDescriptor)interfaceNode.Value).bInterfaceSubClass ==
                    (byte)CyUSBOtherTypes.CyAudioSubclassCodes.MIDISTREAMING)
                {
                    if ((selectedNode != null) && (selectedNode.Value is CyAudioEndpointDescriptor))
                        includeASEP = true;
                }
            }
            return includeASEP;
        }

        protected override void FillListViewItems(bool includeInterface, bool includeAC, bool includeAS, bool includeEP,
                                                  bool includeASEP)
        {
            listViewDescList.BeginUpdate();
            listViewDescList.Items.Clear();
            for (int i = 0; i < m_ItemsList.Count; i++)
            {
                ListViewItem item = new ListViewItem(m_ItemsList[i].ToString());
                item.ImageIndex = 5;
                item.Tag = i;

                if (m_ItemsList[i] is CyInterfaceDescriptor && includeInterface)
                {
                    item.Group = listViewDescList.Groups[LISTVIEW_GROUP_INTERACE];
                    item.Text = ((CyInterfaceDescriptor)m_ItemsList[i]).bInterfaceSubClass ==
                                (byte)CyUSBOtherTypes.CyAudioSubclassCodes.AUDIOCONTROL
                                    ? "Audio Control"
                                    : "MIDI Streaming";
                    listViewDescList.Items.Add(item);
                }
                else if (((m_ItemsList[i] is CyACHeaderDescriptor) ||
                     (m_ItemsList[i] is CyACInputTerminalDescriptor) ||
                     (m_ItemsList[i] is CyACOutputTerminalDescriptor) ||
                     (m_ItemsList[i] is CyACMixerUnitDescriptor) ||
                     (m_ItemsList[i] is CyACSelectorUnitDescriptor) ||
                     (m_ItemsList[i] is CyACFeatureUnitDescriptor) ||
                     (m_ItemsList[i] is CyACProcessingUnitDescriptor) ||
                     (m_ItemsList[i] is CyACExtensionDescriptor)) && includeAC)
                {
                    item.Group = listViewDescList.Groups[LISTVIEW_GROUP_AC];
                    listViewDescList.Items.Add(item);
                }
                else if (((m_ItemsList[i] is CyACHeaderDescriptor_v2) ||
                         (m_ItemsList[i] is CyACInputTerminalDescriptor_v2) ||
                         (m_ItemsList[i] is CyACOutputTerminalDescriptor_v2) ||
                         (m_ItemsList[i] is CyACClockSourceDescriptor_v2) ||
                         (m_ItemsList[i] is CyACClockSelectorDescriptor_v2) ||
                         (m_ItemsList[i] is CyACClockMultiplierDescriptor_v2) ||
                         (m_ItemsList[i] is CyACMixerUnitDescriptor_v2) ||
                         (m_ItemsList[i] is CyACSelectorUnitDescriptor_v2) ||
                         (m_ItemsList[i] is CyACFeatureUnitDescriptor_v2) ||
                         (m_ItemsList[i] is CyACProcessingUnitDescriptor_v2) ||
                         (m_ItemsList[i] is CyACEffectUnitDescriptor_v2) ||
                         (m_ItemsList[i] is CyACSamplingRateConverterDescriptor_v2) ||
                         (m_ItemsList[i] is CyACExtensionDescriptor_v2)) && includeAC)
                {
                    item.Group = listViewDescList.Groups[LISTVIEW_GROUP_AC2];
                    listViewDescList.Items.Add(item);
                }
                else if (((m_ItemsList[i] is CyMSHeaderDescriptor) ||
                         (m_ItemsList[i] is CyMSInJackDescriptor) ||
                         (m_ItemsList[i] is CyMSOutJackDescriptor) ||
                         (m_ItemsList[i] is CyMSElementDescriptor)) && includeAS)
                {
                    item.Group = listViewDescList.Groups[LISTVIEW_GROUP_MS];
                    listViewDescList.Items.Add(item);
                }
                else if ((m_ItemsList[i] is CyAudioEndpointDescriptor) && includeEP)
                {
                    item.Group = listViewDescList.Groups[LISTVIEW_GROUP_ENDPOINT];
                    listViewDescList.Items.Add(item);
                }
                else if ((m_ItemsList[i] is CyMSEndpointDescriptor) && includeASEP)
                {
                    item.Group = listViewDescList.Groups[LISTVIEW_GROUP_ENDPOINT];
                    listViewDescList.Items.Add(item);
                }
            }
            listViewDescList.EndUpdate();
        }

        #endregion Initialization

        #region Events

        private void checkBoxEnableMIDIApi_CheckedChanged(object sender, EventArgs e)
        {
            m_parameters.EnableMIDIApi = checkBoxEnableMIDIApi.Checked;
        }

        private void checkBoxMode_CheckedChanged(object sender, EventArgs e)
        {
            m_parameters.Mode = checkBoxMode.Checked;
        }

        #endregion Events
    }
}
