/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using System;
using System.Collections;
using System.Collections.Generic;
using System.Windows.Forms;

namespace I2S_v2_70
{
    public partial class CyI2SAdvancedTab : CyEditingWrapperControl
    {
        private NumericUpDown[] m_numPosThresholdArray;
        private NumericUpDown[] m_numNegThresholdArray;
        private Label[] m_lblStereoArray;
        private List<CheckBox> m_chbInterruptArray;

        private Dictionary<CyENumberOfChannels, string> m_cbNumChannelsDictionary;
        private Dictionary<CyEDataInterleaving, string> m_cbDataInterleavingDictionary;

        public CyI2SAdvancedTab(CyI2SParameters parameters)
            : base(parameters)
        {
            InitializeComponent();

            parameters.AdvancedTab = this;

            InitNumChannelsComboboxes();
            InitInterleavingComboboxes();
            InitInterruptCheckbox();
            InitThresholdNumeric();
        }

        #region CyTabControlWrapper Members
        public override string TabName
        {
            get { return "Advanced"; }
        }
        #endregion

        #region Assigning parameters values to controls

        private void InitNumChannelsComboboxes()
        {
            m_cbRxNumChannels.DataSource = null;
            m_cbTxNumChannels.DataSource = null;
            m_cbNumChannelsDictionary = GetEnumDictionary<CyENumberOfChannels>(
                Properties.Resources.EnumNumChannelsDesc);
            FillComboFromDictionary(m_cbRxNumChannels, m_cbNumChannelsDictionary);
            FillComboFromDictionary(m_cbTxNumChannels, m_cbNumChannelsDictionary);
        }

        private void InitInterleavingComboboxes()
        {
            m_cbRxDataInterleaving.DataSource = null;
            m_cbTxDataInterleaving.DataSource = null;
            m_cbDataInterleavingDictionary = GetEnumDictionary<CyEDataInterleaving>(
                Properties.Resources.EnumInterleavingDesc);
            FillComboFromDictionary(m_cbRxDataInterleaving, m_cbDataInterleavingDictionary);
            FillComboFromDictionary(m_cbTxDataInterleaving, m_cbDataInterleavingDictionary);
        }

        private void InitInterruptCheckbox()
        {
            m_chbInterruptArray = new List<CheckBox>();
            m_chbInterruptArray.Add(m_chbTxInterruptUnderflow);
            m_chbInterruptArray.Add(m_chbTxInterruptFifo0);
            m_chbInterruptArray.Add(m_chbTxInterruptFifo1);
            m_chbInterruptArray.Add(m_chbRxInterruptOverflow);
            m_chbInterruptArray.Add(m_chbRxInterruptFifo0);
            m_chbInterruptArray.Add(m_chbRxInterruptFifo1);
        }

        private void InitThresholdNumeric()
        {
            m_numPosThresholdArray = new NumericUpDown[CyParamRanges.NUM_THRESHOLD];
            m_numPosThresholdArray[0] = m_numPos0;
            m_numPosThresholdArray[1] = m_numPos1;
            m_numPosThresholdArray[2] = m_numPos2;
            m_numPosThresholdArray[3] = m_numPos3;
            m_numPosThresholdArray[4] = m_numPos4;

            m_numNegThresholdArray = new NumericUpDown[CyParamRanges.NUM_THRESHOLD];
            m_numNegThresholdArray[0] = m_numNeg0;
            m_numNegThresholdArray[1] = m_numNeg1;
            m_numNegThresholdArray[2] = m_numNeg2;
            m_numNegThresholdArray[3] = m_numNeg3;
            m_numNegThresholdArray[4] = m_numNeg4;

            m_lblStereoArray = new Label[CyParamRanges.NUM_THRESHOLD];
            m_lblStereoArray[0] = m_lblStereo0;
            m_lblStereoArray[1] = m_lblStereo1;
            m_lblStereoArray[2] = m_lblStereo2;
            m_lblStereoArray[3] = m_lblStereo3;
            m_lblStereoArray[4] = m_lblStereo4;

            for (int i = 0; i < CyParamRanges.NUM_THRESHOLD; i++)
            {
                m_numPosThresholdArray[i].Minimum = CyParamRanges.MIN_POS_THRESHOLD;
                m_numPosThresholdArray[i].Maximum = CyParamRanges.MAX_POS_THRESHOLD;

                m_numNegThresholdArray[i].Minimum = CyParamRanges.MIN_NEG_THRESHOLD;
                m_numNegThresholdArray[i].Maximum = CyParamRanges.MAX_NEG_THRESHOLD;

                m_numPosThresholdArray[i].ValueChanged += m_numPosThreshold_ValueChanged;
                m_numNegThresholdArray[i].ValueChanged += m_numNegThreshold_ValueChanged;
            }
        }

        public void UpdateUI()
        {
            // Number of channels
            SetComboValue(m_cbRxNumChannels, m_parameters.RxNumChannels);
            SetComboValue(m_cbTxNumChannels, m_parameters.TxNumChannels);

            // Data Interleaving
            SetComboValue(m_cbRxDataInterleaving, m_parameters.RxDataInterleaving);
            SetComboValue(m_cbTxDataInterleaving, m_parameters.TxDataInterleaving);
         
            // DMA
            m_chbRxDMA.Checked = m_parameters.RxDMA == CyEDmaPresent.DMA;
            m_chbTxDMA.Checked = m_parameters.TxDMA == CyEDmaPresent.DMA;

            // Interrupt Source
            BitArray interruptSource = m_parameters.InterruptSource;
            for (int i = 0; i < m_chbInterruptArray.Count; i++)
            {
                m_chbInterruptArray[i].Checked = interruptSource.Get(i);
            }

            // Clip detection
            m_chbRxClipDetection.Checked = m_parameters.RxClipDetection;
            m_chbCommonThresholds.Checked = m_parameters.CommonThreshold;
            for (int i = 0; i < CyParamRanges.NUM_THRESHOLD; i++)
            {
                SetNumValue(m_numPosThresholdArray[i], m_parameters.PosThresholds[i]);
                SetNumValue(m_numNegThresholdArray[i], m_parameters.NegThresholds[i]);
            }

            // Asynchronous mode
            if (m_parameters.ClockSyncMode)
                m_rbSynch.Checked = true;
            else
                m_rbAsynch.Checked = true;

            SetEnableState();
            ValidateDataInterleaving();
        }
        #endregion

        #region Event Handlers
        private void m_cbRxNumChannels_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_parameters.GlobalEditMode)
            {
                m_parameters.RxNumChannels = GetComboValue<CyENumberOfChannels>(m_cbRxNumChannels);
                ValidateDataInterleaving();
                SetEnableState();
                // Update Threshold parameter to include proper number of thresholds
                m_numNegThreshold_ValueChanged(m_numNeg0, EventArgs.Empty);
                m_numPosThreshold_ValueChanged(m_numPos0, EventArgs.Empty);
            }
        }

        private void m_cbTxNumChannels_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_parameters.GlobalEditMode)
            {
                m_parameters.TxNumChannels = GetComboValue<CyENumberOfChannels>(m_cbTxNumChannels);
                ValidateDataInterleaving();
            }
        }

        private void m_cbRxDataInterleaving_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_parameters.GlobalEditMode)
            {
                m_parameters.RxDataInterleaving = GetComboValue<CyEDataInterleaving>(m_cbRxDataInterleaving);

                if (m_parameters.RxDataInterleaving == CyEDataInterleaving.Interleaved)
                {
                    m_chbRxInterruptFifo1.Checked = false;
                }

                ValidateDataInterleaving();
                SetEnableState();
            }
        }

        private void m_cbTxDataInterleaving_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_parameters.GlobalEditMode)
            {
                m_parameters.TxDataInterleaving = GetComboValue<CyEDataInterleaving>(m_cbTxDataInterleaving);

                if (m_parameters.TxDataInterleaving == CyEDataInterleaving.Interleaved)
                {
                    m_chbTxInterruptFifo1.Checked = false;
                }

                ValidateDataInterleaving();
                SetEnableState();
            }
        }

        private void checkBoxRxDMA_CheckedChanged(object sender, EventArgs e)
        {
            m_parameters.RxDMA = m_chbRxDMA.Checked ? CyEDmaPresent.DMA : CyEDmaPresent.NO_DMA;
        }

        private void checkBoxTxDMA_CheckedChanged(object sender, EventArgs e)
        {
            m_parameters.TxDMA = m_chbTxDMA.Checked ? CyEDmaPresent.DMA : CyEDmaPresent.NO_DMA;
        }

        private void checkBoxInterruptSource_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox chb = sender as CheckBox;
            BitArray interruptSource = m_parameters.InterruptSource;
            interruptSource.Set(m_chbInterruptArray.IndexOf(chb), chb.Checked);
            m_parameters.InterruptSource = interruptSource;
        }

        private void m_numPosThreshold_ValueChanged(object sender, EventArgs e)
        {
            if (m_parameters.CommonThreshold && sender == m_numPos0)
            {
                // Update values of rest threshold numerics based on the value of the first one
                for (int i = 1; i < CyParamRanges.NUM_THRESHOLD; i++)
                {
                    m_numPosThresholdArray[i].Value = m_numPosThresholdArray[0].Value;
                }
            }

            sbyte[] posThresholdArray = new sbyte[GetVisibleStereoNum()];
            for (int i = 0; i < posThresholdArray.Length; i++)
            {
                posThresholdArray[i] = Convert.ToSByte(m_numPosThresholdArray[i].Value);
            }
            m_parameters.PosThresholds = posThresholdArray;
        }

        private void m_numNegThreshold_ValueChanged(object sender, EventArgs e)
        {
            if (m_parameters.CommonThreshold && sender == m_numNeg0)
            {
                // Update values of rest threshold numerics based on the value of the first one
                for (int i = 1; i < CyParamRanges.NUM_THRESHOLD; i++)
                {
                    m_numNegThresholdArray[i].Value = m_numNegThresholdArray[0].Value;
                }
            }

            sbyte[] negThresholdArray = new sbyte[GetVisibleStereoNum()];
            for (int i = 0; i < negThresholdArray.Length; i++)
            {
                negThresholdArray[i] = Convert.ToSByte(m_numNegThresholdArray[i].Value);
            }
            m_parameters.NegThresholds = negThresholdArray;
        }

        private void m_chbRxClipDetection_CheckedChanged(object sender, EventArgs e)
        {
            if (m_parameters.GlobalEditMode)
            {
                m_parameters.RxClipDetection = m_chbRxClipDetection.Checked;

                SetEnableState();
            }
        }

        private void m_chbCommonThresholds_CheckedChanged(object sender, EventArgs e)
        {
            if (m_parameters.GlobalEditMode)
            {
                m_parameters.CommonThreshold = m_chbCommonThresholds.Checked;

                if (m_parameters.CommonThreshold)
                {
                    for (int i = 1; i < CyParamRanges.NUM_THRESHOLD; i++)
                    {
                        m_numPosThresholdArray[i].Value = m_numPosThresholdArray[0].Value;
                        m_numNegThresholdArray[i].Value = m_numNegThresholdArray[0].Value;
                    }
                }

                SetEnableState();
            }
        }

        private void m_rbSynchCheckedChanged(object sender, EventArgs e)
        {
            m_parameters.ClockSyncMode = m_rbSynch.Checked;
        }
        #endregion

        #region Enabling/Disabling Controls

        public void OnDirectionChanged()
        {
            SetEnableState();
            ValidateDataInterleaving();

            if (m_parameters.GlobalEditMode && m_parameters.Direction == CyEDirection.Tx)
            {
                m_chbRxClipDetection.Checked = false;
            }
        }

        public void OnByteSwapChanged()
        {
            ValidateDataInterleaving();
        }

        private void SetEnableState()
        {
            m_gbRx.Enabled = m_parameters.Direction != CyEDirection.Tx;
            m_gbTx.Enabled = m_parameters.Direction != CyEDirection.Rx;
            m_chbRxClipDetection.Enabled = m_parameters.Direction != CyEDirection.Tx;

            m_chbRxInterruptFifo1.Enabled = m_parameters.RxDataInterleaving == CyEDataInterleaving.Separate;
            m_chbTxInterruptFifo1.Enabled = m_parameters.TxDataInterleaving == CyEDataInterleaving.Separate;

            m_gbClipDetection.Enabled = m_parameters.RxClipDetection;
            int visibleStereoCount = GetVisibleStereoNum();
            for (int i = 1; i < CyParamRanges.NUM_THRESHOLD; i++)
            {
                bool isEnabled = m_parameters.CommonThreshold == false;
                m_numPosThresholdArray[i].Enabled = isEnabled;
                m_numNegThresholdArray[i].Enabled = isEnabled;

                bool isVisible = i < visibleStereoCount;
                m_numPosThresholdArray[i].Visible = isVisible;
                m_numNegThresholdArray[i].Visible = isVisible;
                m_lblStereoArray[i].Visible = isVisible;
            }
        }
        #endregion

        #region Private methods

        private int GetVisibleStereoNum()
        {
            // The number of visible stereo controls depends on number of channels and equals 1 for mono and stereo and
            // half of the selected number of channels for others.
            return Math.Max(1, (int)m_parameters.RxNumChannels/2);
        }

        private void ValidateDataInterleaving()
        {
            bool rxDataInterleavingMonoError = (m_parameters.RxDataInterleaving == CyEDataInterleaving.Separate) &&
                                           (m_parameters.RxNumChannels == CyENumberOfChannels.MONO_LEFT ||
                                            m_parameters.RxNumChannels == CyENumberOfChannels.MONO_RIGHT) &&
                                           (m_parameters.Direction != CyEDirection.Tx);
            bool txDataInterleavingMonoError = (m_parameters.TxDataInterleaving == CyEDataInterleaving.Separate) &&
                                           (m_parameters.TxNumChannels == CyENumberOfChannels.MONO_LEFT ||
                                            m_parameters.TxNumChannels == CyENumberOfChannels.MONO_RIGHT) &&
                                           (m_parameters.Direction != CyEDirection.Rx);

            bool rxDataInterleavingByteSwapError = (m_parameters.RxDataInterleaving == CyEDataInterleaving.Separate) &&
                                          (m_parameters.RxByteSwap) &&
                                          (m_parameters.Direction != CyEDirection.Tx);
            bool txDataInterleavingByteSwapError = (m_parameters.TxDataInterleaving == CyEDataInterleaving.Separate) &&
                                           (m_parameters.TxByteSwap) &&
                                           (m_parameters.Direction != CyEDirection.Rx); 

            m_errorProvider.SetError(m_cbRxDataInterleaving, rxDataInterleavingMonoError ? 
                                     Properties.Resources.ErrorInterleavingMonoAudio :
                                     rxDataInterleavingByteSwapError ? Properties.Resources.ErrorInterleavingByteSwap :
                                     String.Empty);
            m_errorProvider.SetError(m_cbTxDataInterleaving, txDataInterleavingMonoError ?
                                     Properties.Resources.ErrorInterleavingMonoAudio : 
                                     txDataInterleavingByteSwapError ? Properties.Resources.ErrorInterleavingByteSwap : 
                                     String.Empty);
        }

        #endregion

    }
}
