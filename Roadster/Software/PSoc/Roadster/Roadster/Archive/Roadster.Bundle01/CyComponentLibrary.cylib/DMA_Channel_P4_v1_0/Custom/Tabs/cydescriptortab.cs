/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Windows.Forms;

namespace DMA_Channel_P4_v1_0.Tabs
{
    public partial class CyDescriptorTab : CyTabControlWrapper
    {
        public const int MAX_DATA_ELEMENTS_TO_TRANFER = 65536;
        public const int DESCRIPTOR0 = 0;
        public const int DESCRIPTOR1 = 1;

        private readonly int m_descriptorID = 0;
        
        #region Class Properties
        public override string TabName
        {
            get 
            {
                if (m_descriptorID == DESCRIPTOR0)
                    return "Descriptor 0";
                if (m_descriptorID == DESCRIPTOR1)
                    return "Descriptor 1";
                else
                    return "Empty";
            } 
        }
        #endregion

        #region Constructor
        public CyDescriptorTab(CyParameters param, int tabNum)
            : base(param)
        {
            m_descriptorID = tabNum;

            if (m_descriptorID == DESCRIPTOR0)
                m_params.m_descriptor0Tab = this;
            if (m_descriptorID == DESCRIPTOR1)
                m_params.m_descriptor1Tab = this;
            
            InitializeComponent();
            
            #region Add event handlers
            m_rbByte.CheckedChanged += rb_CheckedChanged;
            m_rbElementToElement.CheckedChanged += rb_CheckedChanged;
            m_rbElementToWord.CheckedChanged += rb_CheckedChanged;
            m_rbEntierDescriptor.CheckedChanged += rb_CheckedChanged;
            m_rbEntierDescriptorChain.CheckedChanged += rb_CheckedChanged;
            m_rbHalfword.CheckedChanged += rb_CheckedChanged;
            m_rbPulseStandart.CheckedChanged += rb_CheckedChanged;
            m_rbPulseUnknown.CheckedChanged += rb_CheckedChanged;
            m_rbSensitiveWat4.CheckedChanged += rb_CheckedChanged;
            m_rbSensitiveWat8.CheckedChanged += rb_CheckedChanged;
            m_rbSingleDataElement .CheckedChanged += rb_CheckedChanged;
            m_rbWord.CheckedChanged += rb_CheckedChanged;
            m_rbWordToElement.CheckedChanged += rb_CheckedChanged;
            m_rbWordToWord.CheckedChanged += rb_CheckedChanged;

            m_cbChainToDescriptor.CheckedChanged += chb_CheckedChanged;
            m_cbDescriptorIsPreemptable.CheckedChanged += chb_CheckedChanged;
            m_cbGenerateInterruptRequest.CheckedChanged += chb_CheckedChanged;
            m_cbIncDestinetionAddr.CheckedChanged += chb_CheckedChanged;
            m_cbIncSourceAddr.CheckedChanged += chb_CheckedChanged;
            m_cbInvalidateDescriptor.CheckedChanged += chb_CheckedChanged;

            m_numOfDataElementsToTranfer.ValueChanged += num_ValueChanghed;
            m_numOfDataElementsToTranfer.KeyUp += num_ValueChanghed;
            #endregion    
                        
            this.m_cbChainToDescriptor.Text = string.Format(Resources.ChainToDescriptor, 1 - m_descriptorID);
            this.m_cbDescriptorIsPreemptable.Text = string.Format(Resources.DescriptorIsPreemptable, m_descriptorID);
            this.m_cbInvalidateDescriptor.Text = string.Format(Resources.InvalidateDescriptor,  m_descriptorID);
        }
        #endregion    
                
        #region Update UI
        public void UpdateUI()
        {
            // Data element size
            m_rbByte.Checked = (m_params.GetDataSize(m_descriptorID) == CyEDataSizeType.BYTE);
            m_rbWord.Checked = (m_params.GetDataSize(m_descriptorID) == CyEDataSizeType.WORD);
            m_rbHalfword.Checked = (m_params.GetDataSize(m_descriptorID) == CyEDataSizeType.HALFWORD);

            // Source and destination transfer width
            m_rbElementToElement.Checked = 
                (m_params.GetSrcDstTransferSize(m_descriptorID) == CyESrcDstTransferSize.ELEMENT_ELEMENT);
            m_rbElementToWord.Checked = 
                (m_params.GetSrcDstTransferSize(m_descriptorID) == CyESrcDstTransferSize.ELEMENT_WORD);
            m_rbWordToElement.Checked = 
                (m_params.GetSrcDstTransferSize(m_descriptorID) == CyESrcDstTransferSize.WORD_ELEMENT);
            m_rbWordToWord.Checked =
                (m_params.GetSrcDstTransferSize(m_descriptorID) == CyESrcDstTransferSize.WORD_WORD);

            m_cbIncSourceAddr.Checked = m_params.GetIncrementSrcAddress(m_descriptorID);
            m_cbIncDestinetionAddr.Checked = m_params.GetIncrementDstAddress(m_descriptorID);

            // Trigger type
            m_rbPulseStandart.Checked = (m_params.GetTriggerType(m_descriptorID) == CyETriggerType.PULSE);
            m_rbPulseUnknown.Checked = (m_params.GetTriggerType(m_descriptorID) == CyETriggerType.LEVEL_UNKNOWN);
            m_rbSensitiveWat4.Checked = (m_params.GetTriggerType(m_descriptorID) == CyETriggerType.LEVEL_FOUR);
            m_rbSensitiveWat8.Checked = (m_params.GetTriggerType(m_descriptorID) == CyETriggerType.LEVEL_EIGHT);

            // Transfer mode
            m_rbSingleDataElement.Checked = 
                (m_params.GetTransferMode(m_descriptorID) == CyETransferMode.SINGLE_DATA_ELEMENT);
            m_rbEntierDescriptor.Checked = 
                (m_params.GetTransferMode(m_descriptorID) == CyETransferMode.ENTIRE_DESCRIPTOR);
            m_rbEntierDescriptorChain.Checked =
                (m_params.GetTransferMode(m_descriptorID) == CyETransferMode.ENTIRE_DESCRIPTOR_CHAIN);
            
            m_cbDescriptorIsPreemptable.Checked = m_params.GetIsPreemtable(m_descriptorID);

            // Post descriptor actions
            m_cbChainToDescriptor.Checked = m_params.GetChainTo(m_descriptorID);
            m_cbInvalidateDescriptor.Checked = m_params.GetInvalidate(m_descriptorID);
            m_cbGenerateInterruptRequest.Checked = m_params.GetGenerateIrq(m_descriptorID);

            // Number of data elements to transfer
            m_numOfDataElementsToTranfer.Value = m_params.GetNumDataElements(m_descriptorID);
        }

        public void UpdateTdChanged(int tdNum)
        {
            if (m_descriptorID != DESCRIPTOR0)
                return;

            if (tdNum == DESCRIPTOR0 + 1)
            {
                if (m_rbEntierDescriptorChain.Checked)
                {
                    m_errorProvider.SetError(m_rbEntierDescriptorChain, Resources.EntireDescriptorChainError);
                }
                else
                {
                    m_rbEntierDescriptorChain.Enabled = false;
                }

                if (m_cbChainToDescriptor.Checked)
                {
                    m_cbChainToDescriptor.Enabled = true;
                    m_errorProvider.SetError(m_cbChainToDescriptor, Resources.ChainToDescripto1Error);
                }
                else
                {
                    m_cbChainToDescriptor.Enabled = false;
                }

            }
            else if (tdNum == DESCRIPTOR1 + 1)
            {
                m_rbEntierDescriptorChain.Enabled = true;

                if (!m_rbEntierDescriptorChain.Checked)
                    m_cbChainToDescriptor.Enabled = true;
                else
                {
                    m_cbChainToDescriptor.Checked = true;
                    m_cbChainToDescriptor.Enabled = false;
                }

                m_errorProvider.SetError(m_cbChainToDescriptor, Resources.ErrorClear);
                m_errorProvider.SetError(m_rbEntierDescriptorChain, Resources.ErrorClear);
            }           
        }

        private void UpdateRbText()
        {
            if (m_rbWord.Checked)
            {
                m_rbElementToElement.Enabled = false;
                m_rbElementToWord.Enabled = false;
                m_rbWordToElement.Enabled = false;
                m_rbWordToWord.Checked = true;
                this.m_cbIncSourceAddr.Text = Resources.IncSrcByFour;
                this.m_cbIncDestinetionAddr.Text = Resources.IncDstByFour;
            }
            else
            {
                m_rbElementToElement.Enabled = true;
                m_rbElementToWord.Enabled = true;
                m_rbWordToElement.Enabled = true;

                if (m_rbByte.Checked)
                {
                    m_rbElementToElement.Text = Resources.ByteToByte;
                    m_rbElementToWord.Text = Resources.ByteToWord;
                    m_rbWordToElement.Text = Resources.WordToByte;

                    if (m_rbElementToElement.Checked)
                    {
                        this.m_cbIncSourceAddr.Text = Resources.IncSrcByOne;
                        this.m_cbIncDestinetionAddr.Text = Resources.IncDstByOne;
                    }
                    else if (m_rbElementToWord.Checked)
                    {
                        this.m_cbIncSourceAddr.Text = Resources.IncSrcByOne;
                        this.m_cbIncDestinetionAddr.Text = Resources.IncDstByFour;
                    }
                    else if (m_rbWordToElement.Checked)
                    {
                        this.m_cbIncSourceAddr.Text = Resources.IncSrcByFour;
                        this.m_cbIncDestinetionAddr.Text = Resources.IncDstByOne;
                    }
                    else
                    {
                        this.m_cbIncSourceAddr.Text = Resources.IncSrcByFour;
                        this.m_cbIncDestinetionAddr.Text = Resources.IncDstByFour;
                    }
                }
                else if (m_rbHalfword.Checked)
                {
                    m_rbElementToElement.Text = Resources.HalfwordToHalfword;
                    m_rbElementToWord.Text = Resources.HalfwordToWord;
                    m_rbWordToElement.Text = Resources.WordToHalfword;

                    if (m_rbElementToElement.Checked)
                    {
                        this.m_cbIncSourceAddr.Text = Resources.IncSrcByTwo;
                        this.m_cbIncDestinetionAddr.Text = Resources.IncDstByTwo;
                    }
                    else if (m_rbElementToWord.Checked)
                    {
                        this.m_cbIncSourceAddr.Text = Resources.IncSrcByTwo;
                        this.m_cbIncDestinetionAddr.Text = Resources.IncDstByFour;
                    }
                    else if (m_rbWordToElement.Checked)
                    {
                        this.m_cbIncSourceAddr.Text = Resources.IncSrcByFour;
                        this.m_cbIncDestinetionAddr.Text = Resources.IncDstByTwo;
                    }
                    else
                    {
                        this.m_cbIncSourceAddr.Text = Resources.IncSrcByFour;
                        this.m_cbIncDestinetionAddr.Text = Resources.IncDstByFour;
                    }
                }
            }
        }
        #endregion

        #region Event Handlers
        private void num_ValueChanghed(object sender, EventArgs e)
        {            
            NumericUpDown num = (NumericUpDown)sender;
            
            if (num == m_numOfDataElementsToTranfer)
            {
                if (num.Value <= MAX_DATA_ELEMENTS_TO_TRANFER && num.Value > 0 && 
                    m_numOfDataElementsToTranfer.Text != "")
                {
                    m_params.SetNumDataElements(m_descriptorID, (UInt32)m_numOfDataElementsToTranfer.Value);
                    m_errorProvider.SetError(num, Resources.ErrorClear);
                }
                else
                {
                    m_errorProvider.SetError(num, Resources.NumOfDataElementError);
                }
            }
        }
        
        private void chb_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox chb = (CheckBox)sender;
            
            if(chb == m_cbIncSourceAddr)
                m_params.SetIncrementSrcAddress(m_descriptorID, m_cbIncSourceAddr.Checked);
            else if(chb == m_cbIncDestinetionAddr)
                m_params.SetIncrementDstAddress(m_descriptorID, m_cbIncDestinetionAddr.Checked);
            else if(chb == m_cbDescriptorIsPreemptable)
                m_params.SetIsPreemtable(m_descriptorID, m_cbDescriptorIsPreemptable.Checked);
            else if(chb == m_cbChainToDescriptor)
            {
                if (m_params.TdNum == 1)
                {
                    m_errorProvider.SetError(m_cbChainToDescriptor, Resources.ErrorClear);
                    m_cbChainToDescriptor.Enabled = false;
                }
                m_params.SetChainTo(m_descriptorID, m_cbChainToDescriptor.Checked);
            }
            else if(chb == m_cbInvalidateDescriptor)
                m_params.SetInvalidate(m_descriptorID, m_cbInvalidateDescriptor.Checked);
            else if (chb == m_cbGenerateInterruptRequest)
                m_params.SetGenerateIrq(m_descriptorID, m_cbGenerateInterruptRequest.Checked);
        }

        private void rb_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = (RadioButton)sender;
            if (rb.Checked == false)
            {
                if (rb == m_rbEntierDescriptorChain)
                {
                    m_errorProvider.SetError(m_rbEntierDescriptorChain, Resources.ErrorClear);
                    
                    if(m_params.TdNum != 1)
                        m_cbChainToDescriptor.Enabled = true;
                    else
                        m_rbEntierDescriptorChain.Enabled = false;
                }
                return;
            }

            // Data element size
            if (rb == m_rbWord)
            {
                UpdateRbText();
                m_params.SetDataSize(m_descriptorID, CyEDataSizeType.WORD);
                m_pbSourceAndDestTransWidth.Image = Resources.imgWord;
            }
            else if (rb == m_rbByte)
            {
                UpdateRbText();
                m_params.SetDataSize(m_descriptorID, CyEDataSizeType.BYTE);
                m_pbSourceAndDestTransWidth.Image = Resources.imgByte;
            }
            else if (rb == m_rbHalfword)
            {
                UpdateRbText();
                m_params.SetDataSize(m_descriptorID, CyEDataSizeType.HALFWORD);
                m_pbSourceAndDestTransWidth.Image = Resources.imgHalfword;
            }

            // Source and destination transfer width
            else if (rb == m_rbElementToElement)
            {
                UpdateRbText();
                m_params.SetSrcDstTransferSize(m_descriptorID, CyESrcDstTransferSize.ELEMENT_ELEMENT);
            }
            else if (rb == m_rbElementToWord)
            {
                UpdateRbText();
                m_params.SetSrcDstTransferSize(m_descriptorID, CyESrcDstTransferSize.ELEMENT_WORD);
            }
            else if (rb == m_rbWordToElement)
            {
                UpdateRbText();
                m_params.SetSrcDstTransferSize(m_descriptorID, CyESrcDstTransferSize.WORD_ELEMENT);
            }
            else if (rb == m_rbWordToWord)
            {
                UpdateRbText();
                m_params.SetSrcDstTransferSize(m_descriptorID, CyESrcDstTransferSize.WORD_WORD);
            }

            // Trigger type
            else if (rb == m_rbPulseStandart)
                m_params.SetTriggerType(m_descriptorID, CyETriggerType.PULSE);
            else if (rb == m_rbPulseUnknown)
                m_params.SetTriggerType(m_descriptorID, CyETriggerType.LEVEL_UNKNOWN);
            else if (rb == m_rbSensitiveWat4)
                m_params.SetTriggerType(m_descriptorID, CyETriggerType.LEVEL_FOUR);
            else if (rb == m_rbSensitiveWat8)
                m_params.SetTriggerType(m_descriptorID, CyETriggerType.LEVEL_EIGHT);

            // Transfer mode
            else if (rb == m_rbSingleDataElement)
                m_params.SetTransferMode(m_descriptorID, CyETransferMode.SINGLE_DATA_ELEMENT);
            else if (rb == m_rbEntierDescriptor)
                m_params.SetTransferMode(m_descriptorID, CyETransferMode.ENTIRE_DESCRIPTOR);
            else if (rb == m_rbEntierDescriptorChain)
            {
                m_params.SetTransferMode(m_descriptorID, CyETransferMode.ENTIRE_DESCRIPTOR_CHAIN);
                m_cbChainToDescriptor.Enabled = false;
                m_cbChainToDescriptor.Checked = true;
            }
        }
        #endregion

    }
}
