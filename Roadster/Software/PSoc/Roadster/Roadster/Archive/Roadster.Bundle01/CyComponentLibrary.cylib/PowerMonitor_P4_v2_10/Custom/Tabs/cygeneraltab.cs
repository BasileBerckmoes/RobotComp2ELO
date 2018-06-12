/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace PowerMonitor_P4_v2_10
{
    public partial class CyGeneralTab : CyEditingWrapperControl
    {
        private const string FILE_EXTENSION_XML = "xml";
        private const string FILE_FILTER_XML = "XML files (*.xml)|*.xml|All files (*.*)|*.*";

        private byte m_previousNumConverters;
        private byte m_previousNumAuxChannels;

        //private decimal ExternalVrefValue;

        public override string TabName
        {
            get { return "General"; }
        }

        #region Constructor(s)
        public CyGeneralTab(CyParameters param)
            : base(param)
        {            
            m_params.m_generalTab = this;
            m_previousNumConverters = m_params.NumConverters;
            m_previousNumAuxChannels = m_params.NumAuxChannels;

            InitializeComponent();

            m_errorProvider = new ErrorProvider();
            m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;

            cbPgoodConfig.Items.AddRange(CyEnumConverter.GetEnumDescList(typeof(CyEPgoodType)));
            m_cbSamplesAve.Items.AddRange(CyEnumConverter.GetEnumDescList(typeof(CyESamples)));
            m_cbVrefDisplay.Items.AddRange(CyEnumConverter.GetEnumDescList(typeof(CyEVrefDisplay)));

            numNumConverters.TextChanged += new EventHandler(numNumConverters_TextChanged);
            numNumConverters.TextChanged += new EventHandler(m_lblRefreshTime_Update);
            numNumConverters.Validating += new CancelEventHandler(numNumConverters_Validating);

            m_cbSamplesAve.SelectedIndexChanged += new EventHandler(m_lblRefreshTime_Update);
            m_cbVrefDisplay.SelectedIndexChanged += new EventHandler(m_lblRefreshTime_Update);
            m_chbEnableDma.CheckedChanged += new EventHandler(m_lblRefreshTime_Update);

            numNumConverters.Minimum = 0;
            numNumConverters.Maximum = decimal.MaxValue;

            Load += delegate(object sender, EventArgs e)
            {
                UpdateClockData(m_params.m_inst, m_params.m_term);
            };
        }
        #endregion

        #region Assigning parameters values to controls
        public void UpdateUI(bool validateConvertersNumber)
        {
            numNumConverters.Value = m_params.NumConverters;

            // Disable the DMA Enable if not supported by the device
            bool globalEdit = m_params.GlobalEditMode;
            m_params.GlobalEditMode = true;
            if (m_params.DmacPresent && m_params.UdbPresent) 
            {
                m_chbEnableDma.Enabled = true;
                m_chbEnableDma.Checked = m_params.EnableDMA;
                if (m_params.EnableDMA)
                {
                    m_lblRspTime.Visible = true;
                }
                else
                {
                    m_lblRspTime.Visible = false;
                }
            }
            else
            {
                m_params.EnableDMA = false;
                m_chbEnableDma.Checked = false;
                m_chbEnableDma.Enabled = false;
                m_lblRspTime.Visible = false;
            }
            m_params.GlobalEditMode = globalEdit;

            //Disable the Pgood if UDBs are not supported by the device
            if(m_params.UdbPresent)
            {
                cbPgoodConfig.SelectedItem = CyEnumConverter.GetEnumDesc(m_params.PgoodConfig);
                cbPgoodConfig.Enabled = true;
            }
            else
            {
                cbPgoodConfig.SelectedItem = CyEnumConverter.GetEnumDesc(CyEPgoodType.pgood_hidden);
                cbPgoodConfig.Enabled = false;
            }

            m_chbExposeSoc.Checked = m_params.ExposeSOC;

            m_cbSamplesAve.SelectedItem = CyEnumConverter.GetEnumDesc(m_params.SamplesAveraged);
            m_cbVrefDisplay.SelectedItem = CyEnumConverter.GetEnumDesc(Additional.cyutils.VrefSelectToDisplay(m_params.VrefSelect));

            //Set Vref and range
            m_nudVrefVolts.Maximum = decimal.MaxValue;
            decimal vrefRead = Additional.cyutils.GetVrefValue(m_params.m_inst, m_params);
            m_nudVrefVolts.Value = vrefRead;
            m_lblAdcRangeValue.Text = Additional.cyutils.GetAdcRangeText(m_params.m_inst, m_params);

            chbFaultOv.Checked = m_params.FaultSourcesOV;
            chbFaultUv.Checked = m_params.FaultSourcesUV;
            chbWarningOv.Checked = m_params.WarningSourcesOV;
            chbWarningUv.Checked = m_params.WarningSourcesUV;

            if (validateConvertersNumber)
                numNumConverters_Validating(numNumConverters, null);

            m_params.m_voltagesTab.UpdateColumnsState();
            //m_params.m_currentsTab.UpdateColumnsState();
        }

        public void UpdateVref()
        {
            m_cbVrefDisplay_SelectedIndexChanged(m_cbVrefDisplay, null);
        }

        #endregion

        #region Event Handlers
        void numNumConverters_TextChanged(object sender, EventArgs e)
        {
            NumericUpDown currentControl = (NumericUpDown)sender;
            byte value = 0;
            try
            {
                value = byte.Parse(currentControl.Text);
                if (value < CyParamRanges.NUM_CONVERTERS_MIN || value > CyParamRanges.NUM_CONVERTERS_MAX)
                    throw new Exception();

                m_params.NumConverters = value;

                m_errorProvider.SetError(currentControl, string.Empty);
                numNumConverters_Validating(sender, null);
            }
            catch (Exception)
            {
                m_errorProvider.SetError(currentControl, string.Format(Resources.NumConvertersError,
                    CyParamRanges.NUM_CONVERTERS_MIN, CyParamRanges.NUM_CONVERTERS_MAX));
            }
            AssignClkInfoParams();
        }

        void numNumConverters_Validating(object sender, CancelEventArgs e)
        {
            NumericUpDown currentControl = (NumericUpDown)sender;

            if (string.IsNullOrEmpty(m_errorProvider.GetError(currentControl)))
            {
                if (m_previousNumConverters >= CyParamRanges.NUM_CONVERTERS_MIN &&
                    m_previousNumConverters <= CyParamRanges.NUM_CONVERTERS_MAX &&
                    m_previousNumConverters != m_params.NumConverters)
                {
                    // Create new row in Voltages table
                    if (m_params.NumConverters > m_previousNumConverters)
                    {
                        int missingItemsCount = m_params.NumConverters - m_params.VoltagesTable.Count;
                        if (m_params.VoltagesTable.Count < m_params.NumConverters)
                        {
                            for (int i = 1; i < (missingItemsCount+1); i++)
                            {
                                m_params.VoltagesTable.Add(new CyVoltagesTableRow(i + m_previousNumConverters ));
                            }
                        }
                    }
                    else
                    {
                        //Remove items from the table
                        int itemDiff = m_params.VoltagesTable.Count - m_params.NumConverters;
                        if(m_params.VoltagesTable.Count > m_params.NumConverters)
                        {
                            for (int i = m_params.VoltagesTable.Count - 1; i >= m_params.NumConverters; i--)
                            {
                                m_params.VoltagesTable.RemoveAt(i);
                            }
                        }

                    }

                    m_params.SetVoltagesTable(false);

                    m_params.m_voltagesTab.UpdateUIFromTable();
                    SyncTables();
                    if (m_params.NumConverters > m_previousNumConverters)
                    {
                        m_params.m_voltagesTab.ValidateAllCells();
                    }
                }
                m_previousNumConverters = m_params.NumConverters;
            }
        }

        //void numAuxChannels_TextChanged(object sender, EventArgs e)
        //{
        //    NumericUpDown currentControl = (NumericUpDown)sender;
        //    byte value = 0;
        //    try
        //    {
        //        value = byte.Parse(currentControl.Text);
        //        if (value < CyParamRanges.NUM_AUX_CHANNELS_MIN || value > CyParamRanges.NUM_AUX_CHANNELS_MAX)
        //            throw new Exception();
        //        m_errorProvider.SetError(currentControl, string.Empty);
        //        m_params.NumAuxChannels = value;
        //    }
        //    catch (Exception)
        //    {
        //        m_errorProvider.SetError(currentControl, string.Format(Resources.NumAuxChannelsError,
        //            CyParamRanges.NUM_AUX_CHANNELS_MAX));
        //    }

        //    // Create new row in Aux table
        //    if (string.IsNullOrEmpty(m_errorProvider.GetError(currentControl)))
        //    {
        //        if (m_previousNumAuxChannels >= CyParamRanges.NUM_AUX_CHANNELS_MIN &&
        //            m_previousNumAuxChannels <= CyParamRanges.NUM_AUX_CHANNELS_MAX)
        //        {
        //            if (value > m_previousNumAuxChannels)
        //            {
        //                int missingItemsCount = value - m_params.AuxTable.Count;
        //                if (m_params.AuxTable.Count < value)
        //                {
        //                    for (int i = 0; i < missingItemsCount; i++)
        //                    {
        //                        // Set default voltage measurement type of new row in Aux table depending 
        //                        // on voltage sensing ADC range from general tab
        //                        CyEAdcRangeInternalType adcRange =
        //                            (m_params.LowVoltageMode == CyELowVoltageMode.Range_2048mV) ?
        //                            CyEAdcRangeInternalType.SignleEnded_2V : CyEAdcRangeInternalType.SignleEnded_4V;
        //                        m_params.AuxTable.Add(new CyAuxTableRow(adcRange));
        //                    }
        //                }
        //            }
        //        }
        //        m_params.SetAuxTable();
        //        m_params.m_auxTab.UpdateUIFromTable();
        //        m_previousNumAuxChannels = value;
        //    }
        //}

        private void cbPgoodConfig_SelectedIndexChanged(object sender, EventArgs e)
        {
            CyEPgoodType pgoodValue = (CyEPgoodType)CyEnumConverter.GetEnumValue(((ComboBox)sender).Text, typeof(CyEPgoodType));
            m_params.PgoodConfig = pgoodValue;
        }

        private void chbFaultOv_CheckedChanged(object sender, EventArgs e)
        {
            if (m_params.FaultSourcesOV != ((CheckBox)sender).Checked)
            {
                m_params.FaultSourcesOV = ((CheckBox)sender).Checked;
                m_params.m_voltagesTab.UpdateColumnsVisibility();
                m_params.m_voltagesTab.UpdateColumnsState();
                m_params.m_voltagesTab.ValidateAllCells();
            }
        }

        private void chbFaultUv_CheckedChanged(object sender, EventArgs e)
        {
            if (m_params.FaultSourcesUV != ((CheckBox)sender).Checked)
            {
                m_params.FaultSourcesUV = ((CheckBox)sender).Checked;
                m_params.m_voltagesTab.UpdateColumnsVisibility();
                m_params.m_voltagesTab.UpdateColumnsState();
                m_params.m_voltagesTab.ValidateAllCells();
            }
        }

        private void chbWarningOv_CheckedChanged(object sender, EventArgs e)
        {
            if (m_params.WarningSourcesOV != ((CheckBox)sender).Checked)
            {
                m_params.WarningSourcesOV = ((CheckBox)sender).Checked;
                m_params.m_voltagesTab.UpdateColumnsVisibility();
                m_params.m_voltagesTab.UpdateColumnsState();
                m_params.m_voltagesTab.ValidateAllCells();
            }
        }

        private void chbWarningUv_CheckedChanged(object sender, EventArgs e)
        {
            if (m_params.WarningSourcesUV != ((CheckBox)sender).Checked)
            {
                m_params.WarningSourcesUV = ((CheckBox)sender).Checked;
                m_params.m_voltagesTab.UpdateColumnsVisibility();
                m_params.m_voltagesTab.UpdateColumnsState();
                m_params.m_voltagesTab.ValidateAllCells();
            }
        }

        private void m_cbSamplesAve_SelectedIndexChanged(object sender, EventArgs e)
        {
            CyESamples samplesValue = (CyESamples)CyEnumConverter.GetEnumValue(((ComboBox)sender).Text, typeof(CyESamples));
            m_params.SamplesAveraged = samplesValue;
            AssignClkInfoParams();
        }

        private void m_cbVrefDisplay_SelectedIndexChanged(object sender, EventArgs e)
        {
            CyEVrefDisplay vrefValue = (CyEVrefDisplay)CyEnumConverter.GetEnumValue(((ComboBox)sender).Text, typeof(CyEVrefDisplay));
            m_params.VrefSelect = Additional.cyutils.VrefDisplayToSelect(vrefValue, m_params.m_inst);

            m_lblExtVref.Enabled = vrefValue == CyEVrefDisplay.Vref_External;
            m_nudVrefVolts.Enabled = vrefValue == CyEVrefDisplay.Vref_External;

            if ((vrefValue == CyEVrefDisplay.Vref_Internal) || (vrefValue == CyEVrefDisplay.Vref_InternalBypass))
            {
                if(Additional.cyutils.IsSrssLite(m_params.m_inst))
                {
                    m_nudVrefVolts.Value = Convert.ToDecimal(1.200);
                }
                else
                {
                    m_nudVrefVolts.Value = Convert.ToDecimal(1.024);
                }
            }
            m_params.AdcClockDivider = CyClock.GetAdcClockDivider(m_params);
            AssignClkInfoParams();
        }

        private void AssignClkInfoParams()
        {
            CyClock.AdcClkInfo clkInfo = CyClock.OptimizeClockApertures(m_params);

            m_params.AdcAClock = clkInfo.AdcClockApertures[0];
            m_params.AdcBClock = clkInfo.AdcClockApertures[1];
            m_params.AdcCClock = clkInfo.AdcClockApertures[2];
            m_params.AdcDClock = clkInfo.AdcClockApertures[3];

            m_params.AdcScanTime = clkInfo.ScanTime;
            m_params.RspTime = clkInfo.ResponseTime;

            string apertureSelect = "{ ";
            for (int i = 0; i < clkInfo.ConverterAdcClockSelect.Length; i++)
            {
                apertureSelect += (i < clkInfo.ConverterAdcClockSelect.Length - 1) ?
                    clkInfo.ConverterAdcClockSelect[i].ToString() + "u, " :
                    clkInfo.ConverterAdcClockSelect[i].ToString() + "u }";
            }
            m_params.AdcClockSelect = apertureSelect;
        }

        public static decimal? GetNumUpDownValue(NumericUpDown control)
        {
            decimal value;
            if (control.ContainsFocus)
            {
                // There is a possibility that the value may be invalid (empty string) or
                // out of range during editing. Such values will be ignored.
                // If the control is focused, the Value getter will reset the text and cursor.
                // To avoid interfering with editing, read the Text property instead.
                string text = control.Text;
                if (!decimal.TryParse(text, out value))
                    return null;    // Ignore invalid value

                if (value < control.Minimum || value > control.Maximum)
                    return Math.Min(control.Maximum, Math.Max(control.Minimum, value));    // Saturate out-of-range values.
            }
            else
                value = control.Value;
            return value;
        }

        private void m_nudVrefVolts_TextChanged(object sender, EventArgs e)
        {
            NumericUpDown currentControl = (NumericUpDown)sender;
            decimal? newValueNullable = GetNumUpDownValue(currentControl);
            if (!newValueNullable.HasValue)
                return;
            decimal value = newValueNullable.Value;
            
            try
            {
                if (value < CyParamRanges.ADC_VREF_MIN_V || value > (decimal) m_params.ChipVdda)
                    throw new Exception();

                // Limit the VrefVolts to Chip Vdda
                if ((double) value > m_params.ChipVdda)
                {
                    this.m_nudVrefVolts.Value = Convert.ToDecimal(m_params.ChipVdda);
                }
                this.m_params.VrefValue = value;

                //Update ADC Range Label
                m_lblAdcRangeValue.Text = Additional.cyutils.GetAdcRangeText(m_params.m_inst, m_params);

                if (m_errorProvider != null)
                {
                    m_errorProvider.SetError(currentControl, string.Empty);
                }
                if(m_params.m_voltagesTab != null)
                {
                    m_params.m_voltagesTab.ValidateAllCells();
                }
            }
            catch (Exception)
            {
                m_errorProvider.SetError(currentControl, string.Format(Resources.ErrorVrefValueBounds,
                    CyParamRanges.ADC_VREF_MIN_V, m_params.ChipVdda));
            }
        }

        private void m_chbEnableDma_CheckedChanged(object sender, EventArgs e)
        {
            m_params.EnableDMA = ((CheckBox)sender).Checked;
            AssignClkInfoParams();
        }

        private void m_chbExposeSoc_CheckedChanged(object sender, EventArgs e)
        {
            m_params.ExposeSOC = ((CheckBox)sender).Checked;
        }
        
        public void m_lblRefreshTime_Update(object sender, EventArgs e)
        {
            /* Update the AdcClk values based on the latest voltage table data
             Needed since the params are updated by ExpEval only when the user hits Ok or Apply */
            CyClock.AdcClkInfo AdcClockConfig = CyClock.OptimizeClockApertures(m_params);
            AssignClkInfoParams();

            string refresh_template = "ADC scan time:        {0, 7:F1}us";
            
            if( AdcClockConfig.ScanTime > 0 && !(AdcClockConfig.ResponseTime < 0 && m_params.EnableDMA == true))
            {
                m_lblRefreshTime.Text = string.Format(refresh_template, (AdcClockConfig.ScanTime / 1000.0));
                
                if (m_params.EnableDMA)
                {
                    AssignClkInfoParams();
                    string response_template = "Max Response time: {0, 7:F1}us";
                    m_lblRspTime.Text = string.Format(response_template, (AdcClockConfig.ResponseTime / 1000.0));
                    m_lblRspTime.Visible = true;
                }
                else
                {
                    m_lblRspTime.Visible = false;
                }
            }
            else
            {
                m_lblRefreshTime.Text = "Max Response time: CLOCK UNKNOWN";
                m_lblRspTime.Text = "Press Apply to update clock information";
                m_lblRspTime.Visible = true;
            }
            
            
        }

        /// <summary>
        /// This method updates UI depending on external clock changes
        /// </summary>
        /// <param name="query">Reference to ICyInstQuery_v1 instance</param>
        /// <param name="termQuery">Reference to ICyTerminalQuery_v1 instance</param>
        public void UpdateClockData(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            m_params.m_generalTab.m_lblRefreshTime_Update(null, null);
        }

        private void CyBasicTab_Load(object sender, EventArgs e)
        {
            if (m_params.IsVoltagesTableDefault) m_params.SetVoltagesTable();
            //if (m_params.IsCurrentsTableDefault) m_params.SetCurrentsTable();
            //if (m_params.IsAuxTableDefault) m_params.SetAuxTable();
        }
        #endregion

        #region Sync dependent tables
        public void SyncTables()
        {
            for (int i = 0; i < m_params.VoltagesTable.Count; i++)
            {
                //if (m_params.VoltagesTable[i].m_voltageMeasurementType == CyEVInternalType.Differential)
                //   m_params.CurrentsTable[i].m_currentMeasurementType = CyECurrentMeasurementInternalType.None;
            }
        }
        #endregion

        #region Toolbar
        public override void LoadConfig(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Title = Resources.LoadDialogHeader;
            openFileDialog.FileName = string.Empty;
            openFileDialog.CheckFileExists = true;
            openFileDialog.CheckPathExists = true;
            openFileDialog.DefaultExt = FILE_EXTENSION_XML;
            openFileDialog.Filter = FILE_FILTER_XML;
            openFileDialog.FilterIndex = 1;
            openFileDialog.RestoreDirectory = true;
            openFileDialog.Multiselect = false;

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                DialogResult dr = MessageBox.Show(Resources.LoadConfirmation, m_params.m_inst.ComponentName,
                    MessageBoxButtons.YesNo, MessageBoxIcon.Warning);
                if (dr == DialogResult.Yes)
                {
                    string fileContent = CyImportExport.GetFileText(openFileDialog.FileName);
                    m_params.LoadAllParametersFromFile(fileContent);
                }
            }
        }

        public override void SaveConfig(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Title = Resources.SaveDialogHeader;
            saveFileDialog.DefaultExt = FILE_EXTENSION_XML;
            saveFileDialog.Filter = FILE_FILTER_XML;
            saveFileDialog.FilterIndex = 1;
            saveFileDialog.RestoreDirectory = true;
            saveFileDialog.FileName = m_params.m_inst.InstanceName;

            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                CyImportExport.SaveToFile(saveFileDialog.FileName, m_params.Serialize(m_params));
            }
        }
        #endregion Toolbar

        

    }
}
