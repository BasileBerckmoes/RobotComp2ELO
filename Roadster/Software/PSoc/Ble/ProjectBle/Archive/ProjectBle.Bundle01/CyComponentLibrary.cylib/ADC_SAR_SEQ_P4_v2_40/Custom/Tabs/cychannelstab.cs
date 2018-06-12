/*******************************************************************************
* Copyright 2011-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using CyDesigner.Extensions.Common;
using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace ADC_SAR_SEQ_P4_v2_40.Tabs
{
    public partial class CyChannelsTab : CyTabControlWrapper
    {
        #region CyTabControlWrapper Members
        public override string TabName
        {
            get
            {
                return "Channels";
            }
        }
        #endregion

        #region Constructor(s)
        public CyChannelsTab(CyParameters param) : base(param)
        {
            m_params.m_channelsTab = this;

            InitializeComponent();

            #region Initialize NumericUpDown ranges
            m_numUpDownAcqTimeA.Minimum = 0;
            m_numUpDownAcqTimeA.Maximum = decimal.MaxValue;
            m_numUpDownAcqTimeB.Minimum = 0;
            m_numUpDownAcqTimeB.Maximum = decimal.MaxValue;
            m_numUpDownAcqTimeC.Minimum = 0;
            m_numUpDownAcqTimeC.Maximum = decimal.MaxValue;
            m_numUpDownAcqTimeD.Minimum = 0;
            m_numUpDownAcqTimeD.Maximum = decimal.MaxValue;
            m_numUpDownSeqChannels.Minimum = 0;
            m_numUpDownSeqChannels.Maximum = decimal.MaxValue;
            #endregion

            #region Add event handlers
            m_numUpDownSeqChannels.TextChanged += new EventHandler(m_numUpDownSeqChannels_TextChanged);

            m_numUpDownAcqTimeA.TextChanged += new EventHandler(m_numUpDown_TextChanged);
            m_numUpDownAcqTimeB.TextChanged += new EventHandler(m_numUpDown_TextChanged);
            m_numUpDownAcqTimeC.TextChanged += new EventHandler(m_numUpDown_TextChanged);
            m_numUpDownAcqTimeD.TextChanged += new EventHandler(m_numUpDown_TextChanged);
            #endregion

            #region Initialize data grid view
            CyParameters.InitializeDataGrid(m_dgvChannelsConfig);

            // Add items for Polarity columns
            colResolution.Items.Clear();
            colResolution.Items.AddRange(CyEnumConverter.GetEnumDescList(typeof(CyEResolution)));
            colMode.Items.Clear();
            colMode.Items.AddRange(CyEnumConverter.GetEnumDescList(typeof(CyEMode)));
            colAcqTime.Items.Clear();
            colAcqTime.Items.AddRange(CyEnumConverter.GetEnumDescList(typeof(CyEAcquisionTime)));
            colAcqTime.Items.Remove(CyEnumConverter.GetEnumDesc(CyEAcquisionTime.FourClocks));

            // Set readonly columns grayed out style
            CyParameters.SetReadOnlyState(colChannel);
            CyParameters.SetReadOnlyState(colConvTime);

            m_dgvChannelsConfig.CurrentCellDirtyStateChanged += delegate(object sender, EventArgs e)
            {
                CommitCellValueImmediately(sender as DataGridView);
            };

            m_dgvChannelsConfig.CellValueChanged += new DataGridViewCellEventHandler(m_dgv_CellValueChanged);

            int width = 3;
            foreach (DataGridViewColumn col in m_dgvChannelsConfig.Columns)
            {
                width += col.Width;
            }
            m_dgvChannelsConfig.Width = width;
            #endregion
        }
        #endregion

        #region Event handlers
        private void m_numUpDownSeqChannels_TextChanged(object sender, EventArgs e)
        {
            if (sender == m_numUpDownSeqChannels)
            {
                string errorMsg = string.Empty;

                byte value;

                bool parsed = byte.TryParse(m_numUpDownSeqChannels.Text, out value);

                if (parsed && m_params.GlobalEditMode)
                {
                    m_params.SequencedChannels = value;
                    m_params.UpdateMaxResolutionUsed();
                    UpdateResolutionErrors();
                    UpdateAvgLeftDataErrors();
                }

                if (parsed && value >= CyParamRanges.NUM_MIN_CHANNELS && value <= m_params.NumMaxChannels)
                {
                    // Add new channels
                    int seqChannelsPresent = m_params.ChannelsConfigTable.Count - 1; // Exclude Injection channel
                    if (seqChannelsPresent < value)
                    {
                        int cntRowsToAdd = value - seqChannelsPresent;
                        for (int i = 0; i < cntRowsToAdd; i++)
                        {
                            m_params.ChannelsConfigTable.Add(
                                CyChannelsConfigTableRow.CreateDefaultRow(m_params.ChannelsConfigTable.Count));
                        }
                    }

                    UpdateUIFromTable();

                    if (!string.IsNullOrEmpty(HardwareMuxChannelsUsedError))
                    {
                        errorMsg = HardwareMuxChannelsUsedError;
                    }
                    else
                    {
                        if (m_params.m_generalTab != null && m_params.GlobalEditMode)
                        {
                            m_params.m_generalTab.UpdateTimimgParams();
                        }
                    }
                }
                else
                {
                    errorMsg = string.Format(Resources.NumSeqChannelsFormatErrorDescription,
                        CyParamRanges.NUM_MIN_CHANNELS, m_params.NumMaxChannels);
                }

                if (string.IsNullOrEmpty(errorMsg))
                {
                    m_params.SetChannelsConfigTable();
                }

                m_errorProvider.SetError(m_numUpDownSeqChannels, errorMsg);
            }
        }

        private void m_numUpDown_TextChanged(object sender, EventArgs e)
        {
            NumericUpDown currentControl = sender as NumericUpDown;
            UInt16 value;
            bool parseSuccess = UInt16.TryParse(currentControl.Text, out value);

            if (parseSuccess && m_params.GlobalEditMode)
            {
                if (sender == m_numUpDownAcqTimeA)
                {
                    m_params.AClock = value;
                    m_labelAcqTimeAValue.Text = CyParameters.GetNormalizedString(
                        m_params.GetAcquisionTime(CyEAcquisionTime.AClocks));
                }
                else if (sender == m_numUpDownAcqTimeB)
                {
                    m_params.BClock = value;
                    m_labelAcqTimeBValue.Text = CyParameters.GetNormalizedString(
                        m_params.GetAcquisionTime(CyEAcquisionTime.BClocks));
                }
                else if (sender == m_numUpDownAcqTimeC)
                {
                    m_params.CClock = value;
                    m_labelAcqTimeCValue.Text = CyParameters.GetNormalizedString(
                        m_params.GetAcquisionTime(CyEAcquisionTime.CClocks));
                }
                else if (sender == m_numUpDownAcqTimeD)
                {
                    m_params.DClock = value;
                    m_labelAcqTimeDValue.Text = CyParameters.GetNormalizedString(
                        m_params.GetAcquisionTime(CyEAcquisionTime.DClocks));
                }
                if (m_params.m_generalTab != null)
                {
                    m_params.m_generalTab.UpdateTimimgParams();
                }
            }

            if (parseSuccess && value >= CyParamRanges.ADC_CLOCK_MIN_VALUE &&
                value <= CyParamRanges.ADC_CLOCK_MAX_VALUE)
            {
                m_errorProvider.SetError(currentControl, string.Empty);
            }
            else
            {
                m_errorProvider.SetError(currentControl, string.Format(Resources.AcqTimeErrorDescription,
                    CyParamRanges.ADC_CLOCK_MIN_VALUE, CyParamRanges.ADC_CLOCK_MAX_VALUE));
            }

            if (string.IsNullOrEmpty(m_errorProvider.GetError(currentControl)))
            {
                UpdateConvTimeValues();
            }
        }

        private void m_dgv_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            int columnIndex = e.ColumnIndex;

            if (columnIndex == colChannel.Index || columnIndex == colConvTime.Index)
            {
                return;
            }

            if (m_params.GlobalEditMode)
            {
                UpdateTableRowFromUI(e.RowIndex);

                if (columnIndex == colChannelEnable.Index || columnIndex == colMode.Index)
                {
                    m_params.SetAuxiliaryData();
                    m_errorProvider.SetError(m_numUpDownSeqChannels, HardwareMuxChannelsUsedError);
                }

                if (columnIndex == colChannelEnable.Index || columnIndex == colAcqTime.Index ||
                    columnIndex == colResolution.Index || columnIndex == colAveraged.Index)
                {
                    UpdateConvTimeValues();
                }

                if (m_params.m_generalTab != null &&
                    (columnIndex == colChannelEnable.Index || columnIndex == colResolution.Index ||
                    columnIndex == colAveraged.Index || columnIndex == colAcqTime.Index))
                {
                    m_params.m_generalTab.UpdateTimimgParams();
                }

                if (columnIndex == colChannelEnable.Index || columnIndex == colResolution.Index)
                {
                    m_params.UpdateMaxResolutionUsed();
                    UpdateResolutionErrors();
                    UpdateAvgLeftDataErrors();
                }

                m_params.SetChannelsConfigTable();

                if (columnIndex == colAveraged.Index)
                {
                    UpdateResolutionErrors();
                    UpdateAvgLeftDataErrors();
                }
            }
        }
        #endregion

        #region Update UI
        public void UpdateUI()
        {
            if (m_params != null)
            {
                // Clocks
                m_numUpDownAcqTimeA.Value = m_params.AClock;
                m_numUpDownAcqTimeB.Value = m_params.BClock;
                m_numUpDownAcqTimeC.Value = m_params.CClock;
                m_numUpDownAcqTimeD.Value = m_params.DClock;

                // Sequenced channels
                m_numUpDownSeqChannels.Value = m_params.SequencedChannels;

                // Channels configuration table
                UpdateUIFromTable();
                UpdateAcqTimeValues();
            }
        }

        public void UpdateUIFromTable()
        {
            bool prevGEM = m_params.GlobalEditMode;
            m_params.GlobalEditMode = false;

            m_dgvChannelsConfig.Rows.Clear();

            // Add all sequenced channels
            int numChannels = m_params.SequencedChannels + 1;
            for (int dgvRowIndex = 0; dgvRowIndex < numChannels; dgvRowIndex++)
            {
                object[] newRow = new object[m_dgvChannelsConfig.ColumnCount];
                m_dgvChannelsConfig.Rows.Add(newRow);

                UpdateUIFromTable(dgvRowIndex);
            }

            // Correct DataGridView height
            m_dgvChannelsConfig.Height = m_dgvChannelsConfig.ColumnHeadersHeight + numChannels *
                m_dgvChannelsConfig.RowTemplate.Height + 2;

            UpdateResolutionErrors();
            UpdateAvgLeftDataErrors();

            m_params.GlobalEditMode = prevGEM;
        }

        public void UpdateUIFromTable(int row)
        {
            int actualTableRow = m_params.TableRowIndex(row);

            m_dgvChannelsConfig[colChannel.Index, row].Value =
                (actualTableRow == CyChannelsConfigTable.INJ_CHANNEL_INDEX) ? "INJ" : row.ToString();
            m_dgvChannelsConfig[colChannelEnable.Index, row].Value =
                m_params.ChannelsConfigTable[actualTableRow].m_enabled;
            m_dgvChannelsConfig[colResolution.Index, row].Value =
                CyEnumConverter.GetEnumDesc(m_params.ChannelsConfigTable[actualTableRow].m_resolution);
            m_dgvChannelsConfig[colMode.Index, row].Value =
                CyEnumConverter.GetEnumDesc(m_params.ChannelsConfigTable[actualTableRow].m_mode);
            m_dgvChannelsConfig[colAveraged.Index, row].Value =
                m_params.ChannelsConfigTable[actualTableRow].m_averaged;
            m_dgvChannelsConfig[colAcqTime.Index, row].Value =
                CyEnumConverter.GetEnumDesc(m_params.ChannelsConfigTable[actualTableRow].m_acqTime);
            m_dgvChannelsConfig[colConvTime.Index, row].Value =
                CyParameters.GetNormalizedString(m_params.GetConversionTime(actualTableRow));
            m_dgvChannelsConfig[colLimitDetect.Index, row].Value =
                m_params.ChannelsConfigTable[actualTableRow].m_limitsDetectIntrEnabled;
            m_dgvChannelsConfig[colSaturation.Index, row].Value =
                m_params.ChannelsConfigTable[actualTableRow].m_saturationIntrEnabled;
        }

        public void UpdateTableRowFromUI(int row)
        {
            if (row >= 0 && row < m_dgvChannelsConfig.RowCount)
            {
                int actualTableRow = m_params.TableRowIndex(row);

                m_params.ChannelsConfigTable[actualTableRow].m_enabled = CyParameters.ParseNullableBool(
                    m_dgvChannelsConfig.Rows[row].Cells[colChannelEnable.Index].Value);
                m_params.ChannelsConfigTable[actualTableRow].m_resolution =
                    (CyEResolution)CyEnumConverter.GetEnumValue(m_dgvChannelsConfig[colResolution.Index, row].Value,
                    typeof(CyEResolution));
                m_params.ChannelsConfigTable[actualTableRow].m_mode = (CyEMode)CyEnumConverter.GetEnumValue(
                    m_dgvChannelsConfig[colMode.Index, row].Value, typeof(CyEMode));
                m_params.ChannelsConfigTable[actualTableRow].m_averaged = CyParameters.ParseNullableBool(
                    m_dgvChannelsConfig.Rows[row].Cells[colAveraged.Index].Value);
                m_params.ChannelsConfigTable[actualTableRow].m_acqTime =
                    (CyEAcquisionTime)CyEnumConverter.GetEnumValue(m_dgvChannelsConfig[colAcqTime.Index, row].Value,
                    typeof(CyEAcquisionTime));
                m_params.ChannelsConfigTable[actualTableRow].m_limitsDetectIntrEnabled =
                    CyParameters.ParseNullableBool(m_dgvChannelsConfig.Rows[row].Cells[colLimitDetect.Index].Value);
                m_params.ChannelsConfigTable[actualTableRow].m_saturationIntrEnabled =
                    CyParameters.ParseNullableBool(m_dgvChannelsConfig.Rows[row].Cells[colSaturation.Index].Value);

                m_dgvChannelsConfig[colConvTime.Index, row].Value =
                    CyParameters.GetNormalizedString(m_params.GetConversionTime(actualTableRow));
            }
        }

        public void UpdateAcqTimeValues()
        {
            // Acquisition times
            m_labelAcqTimeAValue.Text = CyParameters.GetNormalizedString(m_params.GetAcquisionTime(
                CyEAcquisionTime.AClocks));
            m_labelAcqTimeBValue.Text = CyParameters.GetNormalizedString(m_params.GetAcquisionTime(
                CyEAcquisionTime.BClocks));
            m_labelAcqTimeCValue.Text = CyParameters.GetNormalizedString(m_params.GetAcquisionTime(
                CyEAcquisionTime.CClocks));
            m_labelAcqTimeDValue.Text = CyParameters.GetNormalizedString(m_params.GetAcquisionTime(
                CyEAcquisionTime.DClocks));

            UpdateConvTimeValues();
        }

        public void UpdateConvTimeValues()
        {
            foreach (DataGridViewRow row in m_dgvChannelsConfig.Rows)
            {
                row.Cells[colConvTime.Index].Value = CyParameters.GetNormalizedString(
                    m_params.GetConversionTime(m_params.TableRowIndex(row.Index)));
            }
        }
        #endregion

        #region CyTabControlWrapper members
        public override IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errs = new List<CyCustErr>();
            string errorMessage = string.Empty;

            if (m_errorProvider != null)
            {
                // Check controls for errors
                foreach (Control control in this.Controls)
                {
                    errorMessage = m_errorProvider.GetError(control);
                    if (string.IsNullOrEmpty(errorMessage) == false)
                        yield return new CyCustErr(errorMessage);

                    // Check controls inside groupbox
                    foreach (Control internalControl in control.Controls)
                    {
                        errorMessage = m_errorProvider.GetError(internalControl);
                        if (string.IsNullOrEmpty(errorMessage) == false)
                            yield return new CyCustErr(errorMessage);
                    }
                }
            }

            for (int i = 0; i < m_dgvChannelsConfig.RowCount; i++)
            {
                DataGridViewCell resCell = m_dgvChannelsConfig[colResolution.Index, i];
                int channelIndex = m_params.TableRowIndex(i);

                if (!string.IsNullOrEmpty(resCell.ErrorText))
                {
                    yield return new CyCustErr(resCell.ErrorText);
                    break;
                }
            }

            for (int i = 0; i < m_dgvChannelsConfig.RowCount; i++)
            {
                DataGridViewCell avgCell = m_dgvChannelsConfig[colAveraged.Index, i];

                if (!string.IsNullOrEmpty(avgCell.ErrorText))
                {
                    yield return new CyCustErr(avgCell.ErrorText);
                    break;
                }
            }
        }
        #endregion

        #region Private functions
        private string HardwareMuxChannelsUsedError
        {
            get
            {
                string errorMsg = string.Empty;
                //byte hdwMuxChannels = m_params.NumberMuxLinesUsed;

                //if (m_params.SequencedChannels < CyParamRanges.NUM_MIN_CHANNELS ||
                //    hdwMuxChannels > m_params.NumMaxChannels)
                //{
                //    errorMsg = Resources.NumSeqChannelsErrorDescription;
                //}

                return errorMsg;
            }
        }

        private string GetChannelResolutionError(int rowIndex)
        {
            CyChannelsConfigTableRow channel = m_params.ChannelsConfigTable[m_params.TableRowIndex(rowIndex)];
            string errorMsg = string.Empty;

            if (channel.m_averaged && m_params.GetResolution(channel.m_resolution) != m_params.MaxResolutionUsed)
            {
                errorMsg = string.Format(Resources.AveragedChannelResolutionErrorDescription,
                    m_params.MaxResolutionUsed);
            }

            return errorMsg;
        }

        private string GetChannelAveragedError(int rowIndex)
        {
            CyChannelsConfigTableRow channel = m_params.ChannelsConfigTable[m_params.TableRowIndex(rowIndex)];
            string errorMsg = string.Empty;

            if (channel.m_averaged && m_params.DataFormatJustification == CyEFormatJustify.Left)
            {
                errorMsg = Resources.AvgLeftJustificationError;
            }

            return errorMsg;
        }
        #endregion Private functions

        #region Public functions
        public void UpdateResolutionErrors()
        {
            for (int i = 0; i < m_dgvChannelsConfig.RowCount; i++)
            {
                DataGridViewCell resCell = m_dgvChannelsConfig[colResolution.Index, i];
                int channelIndex = m_params.TableRowIndex(i);

                if (channelIndex == CyChannelsConfigTable.INJ_CHANNEL_INDEX &&
                    m_params.InjectionChannelEnabled == false)
                {
                    resCell.ErrorText = string.Empty;
                }
                else
                {
                    resCell.ErrorText = GetChannelResolutionError(i);
                }
            }
        }

        public void UpdateAvgLeftDataErrors()
        {
            for (int i = 0; i < m_dgvChannelsConfig.RowCount; i++)
            {
                DataGridViewCell avgCell = m_dgvChannelsConfig[colAveraged.Index, i];
                int channelIndex = m_params.TableRowIndex(i);

                if (channelIndex == CyChannelsConfigTable.INJ_CHANNEL_INDEX &&
                    m_params.InjectionChannelEnabled == false)
                {
                    avgCell.ErrorText = string.Empty;
                }
                else
                {
                    avgCell.ErrorText = GetChannelAveragedError(i);
                }
            }

            m_params.m_generalTab.UpdateAvgLeftDataComboBoxError();
        }

        public int GetEnabledAvgNum()
        {
            int num = 0;

            for (int i = 0; i < m_dgvChannelsConfig.RowCount; i++)
            {
                DataGridViewCell avgCell = m_dgvChannelsConfig[colAveraged.Index, i];
                int channelIndex = m_params.TableRowIndex(i);

                if (channelIndex != CyChannelsConfigTable.INJ_CHANNEL_INDEX ||
                    m_params.InjectionChannelEnabled == true)
                {
                    if ((bool)avgCell.Value)
                    {
                        num++;
                    }
                }
            }

            return num;
        }
        #endregion Public functions
    }
}
