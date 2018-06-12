/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/


using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace USBFS_v3_10
{
    public partial class CyInterruptsPage : CyEditingWrapperControl
    {
        #region CyEditingWrapperControl override
        public override string TabName
        {
            get { return CyCustomizer.PARAM_TAB_NAME_INTERRUPTS; }
        }
        #endregion

        #region Constants
        private const int EP0_OFFSET = 0;
        private const int ENDPOINTS_OFFSET = 1;
        private const int ARB_OFFSET = 9;
        private const int BUSRESET_OFFSET = 10;
        private const int SOF_OFFSET = 11;
        private const int LPM_OFFSET = 12;

        private const int MAX_INTERRUPTS = 13;
        private const int MAX_ENDPOINTS_NUM = 9;
        private const int MAX_INTERRUPT_GROUP_NUM = 3;

        private Color m_oddRowColor = Color.Gainsboro;
        private Color m_evenRowColor = Color.White;
        #endregion

        #region Members
        private readonly RadioButton[,] m_endpointRadioButtons;
        private readonly RadioButton[] m_lpmRadioButtons;
        private readonly RadioButton[] m_arbiterRadioButtons;
        private readonly RadioButton[] m_busResetRadioButtons;
        private readonly RadioButton[] m_startOfFrameRadioButtons;

        private readonly Panel[] m_interrTableRowPanels;
        #endregion

        #region Constructors
        public CyInterruptsPage(CyUSBFSParameters parameters)
            : base(parameters)
        {
            parameters.InterrPage = this;

            #region Initialization
            InitializeComponent();

            m_endpointRadioButtons = new RadioButton[MAX_ENDPOINTS_NUM, MAX_INTERRUPT_GROUP_NUM] {
                                                            {rbEp0High, rbEp0Medium, rbEp0Low},
                                                            {rbEp1High, rbEp1Medium, rbEp1Low},
                                                            {rbEp2High, rbEp2Medium, rbEp2Low},
                                                            {rbEp3High, rbEp3Medium, rbEp3Low},
                                                            {rbEp4High, rbEp4Medium, rbEp4Low},
                                                            {rbEp5High, rbEp5Medium, rbEp5Low},
                                                            {rbEp6High, rbEp6Medium, rbEp6Low},
                                                            {rbEp7High, rbEp7Medium, rbEp7Low},
                                                            {rbEp8High, rbEp8Medium, rbEp8Low}
                                                          };
            m_lpmRadioButtons = new RadioButton[MAX_INTERRUPT_GROUP_NUM] { rbLpmHigh, rbLpmMedium, 
                rbLpmLow };
            m_arbiterRadioButtons = new RadioButton[MAX_INTERRUPT_GROUP_NUM] { rbArbiterHigh, rbArbiterMedium, 
                rbArbiterLow };
            m_busResetRadioButtons = new RadioButton[MAX_INTERRUPT_GROUP_NUM] { rbBusResetHigh, rbBusResetMedium, 
                rbBusResetLow };
            m_startOfFrameRadioButtons = new RadioButton[MAX_INTERRUPT_GROUP_NUM] { rbStartOfFrameHigh, 
                rbStartOfFrameMedium, rbStartOfFrameLow };

            m_interrTableRowPanels = new Panel[MAX_INTERRUPTS] { panelEP0, panelEP1, panelEP2, panelEP3, panelEP4, 
                panelEP5, panelEP6, panelEP7, panelEP8, panelArbiter, panelBusReset, panelStartOfFrame, panelLpm };
            #endregion
            
            #region Add Event Handlers
            for (uint interruptGroupIndex = 0; interruptGroupIndex < MAX_INTERRUPT_GROUP_NUM; interruptGroupIndex++)
            {
                for (uint endpointNum = 0; endpointNum < MAX_ENDPOINTS_NUM; endpointNum++)
                {
                    m_endpointRadioButtons[endpointNum, interruptGroupIndex].CheckedChanged +=
                         RadioButtonEndPoint_CheckedChanged;
                }

                m_lpmRadioButtons[interruptGroupIndex].CheckedChanged += RadioButtonLpm_CheckedChanged;
                m_arbiterRadioButtons[interruptGroupIndex].CheckedChanged += RadioButtonArbiter_CheckedChanged;
                m_busResetRadioButtons[interruptGroupIndex].CheckedChanged += RadioButtonBusReset_CheckedChanged;
                m_startOfFrameRadioButtons[interruptGroupIndex].CheckedChanged +=  RadioButtonSof_CheckedChanged;
            }
            #endregion

            #region Update UI
            UpdateUI();
            #endregion
        }
        #endregion

        #region Event Handlers

        private void CyInterruptsPage_Load(object sender, EventArgs e)
        {
            UpdateInterruptsTableView();
        }

        private void RadioButtonEndPoint_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if (rb.Checked == false)
                return;

            for (uint interruptGroupIndex = 0; interruptGroupIndex < MAX_INTERRUPT_GROUP_NUM; interruptGroupIndex++)
            {
                for (uint endpointNum = 0; endpointNum < MAX_ENDPOINTS_NUM; endpointNum++)
                {
                    // If checked EP0-EP8 radiobutton
                    if (rb == m_endpointRadioButtons[endpointNum, interruptGroupIndex])
                    {
                        m_parameters.SetParamEndpointInterruptGroup(endpointNum,
                            (CyUSBFSParameters.CyEnumInterruptGroup)interruptGroupIndex);
                        return;
                    }
                }
            }
        }

        private void RadioButtonLpm_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if (rb.Checked == false)
                return;

            for (uint interruptGroupIndex = 0; interruptGroupIndex < MAX_INTERRUPT_GROUP_NUM; interruptGroupIndex++)
            {
                // If checked LPM radiobutton
                if (rb == m_lpmRadioButtons[interruptGroupIndex])
                {
                    m_parameters.LpmIntrGroup = (CyUSBFSParameters.CyEnumInterruptGroup)interruptGroupIndex;
                    return;
                }
            }
        }

        private void RadioButtonArbiter_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if (rb.Checked == false)
                return;

            for (uint interruptGroupIndex = 0; interruptGroupIndex < MAX_INTERRUPT_GROUP_NUM; interruptGroupIndex++)
            {
                // If checked Arbiter radiobutton
                if (rb == m_arbiterRadioButtons[interruptGroupIndex])
                {
                    m_parameters.ArbiterIntrGroup = (CyUSBFSParameters.CyEnumInterruptGroup)interruptGroupIndex;
                    return;
                }
            }
        }

        private void RadioButtonBusReset_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if (rb.Checked == false)
                return;

            for (uint interruptGroupIndex = 0; interruptGroupIndex < MAX_INTERRUPT_GROUP_NUM; interruptGroupIndex++)
            {
                // If checked Bus Reset radiobutton
                if (rb == m_busResetRadioButtons[interruptGroupIndex])
                {
                    m_parameters.BusResetIntrGroup = (CyUSBFSParameters.CyEnumInterruptGroup)interruptGroupIndex;
                    return;
                }
            }
        }

        private void RadioButtonSof_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if (rb.Checked == false)
                return;

            for (uint interruptGroupIndex = 0; interruptGroupIndex < MAX_INTERRUPT_GROUP_NUM; interruptGroupIndex++)
            {
                // If checked Start of Frame radiobutton
                if (rb == m_startOfFrameRadioButtons[interruptGroupIndex])
                {
                    m_parameters.StartOfFrameIntrGroup = (CyUSBFSParameters.CyEnumInterruptGroup)interruptGroupIndex;
                    return;
                }
            }
        }
        #endregion

        #region Update UI
        public void UpdateUI()
        {
            for (uint endpointNum = 0; endpointNum < MAX_ENDPOINTS_NUM; endpointNum++)
            {
                m_endpointRadioButtons[endpointNum, 
                    (int)m_parameters.GetParamEndpointInterruptGroup(endpointNum)].Checked = true;
            }

            m_lpmRadioButtons[(int)m_parameters.LpmIntrGroup].Checked = true;
            m_arbiterRadioButtons[(int)m_parameters.ArbiterIntrGroup].Checked = true;
            m_busResetRadioButtons[(int)m_parameters.BusResetIntrGroup].Checked = true;
            m_startOfFrameRadioButtons[(int)m_parameters.StartOfFrameIntrGroup].Checked = true;

            UpdateInterruptsTableView();
        }

        public void UpdateInterruptsTableView()
        {
            List<Panel> visiblePanels = new List<Panel>();

            if (m_parameters.IsEp0)
                visiblePanels.Add(m_interrTableRowPanels[EP0_OFFSET]);

            for (uint endpointNum = ENDPOINTS_OFFSET; endpointNum < MAX_ENDPOINTS_NUM; endpointNum++)
            {
                if (m_parameters.UsedEp[endpointNum])
                    visiblePanels.Add(m_interrTableRowPanels[endpointNum]);
            }

            if (m_parameters.EPMemoryMgmt != CyUSBFSParameters.CyMemoryManagement.EP_Manual)
                visiblePanels.Add(m_interrTableRowPanels[ARB_OFFSET]);
            if (m_parameters.IsBusReset)
                visiblePanels.Add(m_interrTableRowPanels[BUSRESET_OFFSET]);
            if (m_parameters.EnableSofInterrupt)
                visiblePanels.Add(m_interrTableRowPanels[SOF_OFFSET]);
            if (m_parameters.IsLpm)
                visiblePanels.Add(m_interrTableRowPanels[LPM_OFFSET]);

            for (int i = 0; i < m_interrTableRowPanels.Length; i++)
            {
                m_interrTableRowPanels[i].Visible = false;
            }

            int tableHeight = panelHeader.Size.Height;

            for (int i = 0; i < visiblePanels.Count; i++)
            {
                visiblePanels[i].Visible = true;
                tableHeight += visiblePanels[i].Size.Height;

                if(i%2 == 0)
                    visiblePanels[i].BackColor = m_evenRowColor;
                else
                    visiblePanels[i].BackColor = m_oddRowColor;
            }

            tableLayoutPanel1.Size = new Size(tableLayoutPanel1.Size.Width, tableHeight);
        }
        #endregion

    }
}
