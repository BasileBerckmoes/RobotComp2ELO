/*******************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
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
using CyDesigner.Extensions.Scc;

namespace TCPWM_P4_v2_0
{
    public partial class CyPWMTab : CyEditingWrapperControl
    {
        enum CySignals
        {
            [Description("reload")]
            RELOAD,
            [Description("start")]
            START,
            [Description("stop")]
            STOP,
            [Description("switch")]
            SWITCH,
            [Description("count")]
            COUNT
        };
        
        private CyImagePWM m_pwmGraph;

        public override string TabName
        {
            get { return "PWM"; }
        }

        #region Constructor(s)
        public CyPWMTab(CyParameters prms)
            :base(prms)
        {
            InitializeComponent();

            Prms.m_pwmTab = this;
            registerGrid.m_prms = prms;

            CyParameters.FillComboFromEnum(m_cbPwmMode, typeof(CyEPWMMode));
            CyParameters.FillComboFromEnum(m_cbKillEvent, typeof(CyEPWMEvent));
            CyParameters.FillComboFromEnum(m_cbStopEvent, typeof(CyEPWMStop));
            CyParameters.FillComboFromEnum(m_cbOutCCInvert, typeof(CyPWMInvert));
            CyParameters.FillComboFromEnum(m_cbOutLineInvert, typeof(CyPWMInvert));
            CyParameters.FillComboFromEnum(m_cbAlign, typeof(CyEPWMAlign));
            CyParameters.FillComboFromEnum(m_cbRunMode, typeof(CyERunMode));

            m_cbPrescaler.Items.Clear();
            m_cbPrescaler.Items.AddRange(CyParameters.PRESCALER_ITEMS_LIST);

            InitAdvTable();

            m_pwmGraph = new CyImagePWM();
            m_pbPWMGraph.Image = m_pwmGraph.ImageBmp;
            m_pbPWMGraph.SizeMode = PictureBoxSizeMode.Normal;

            m_cbPrescaler.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                if ((sender as ComboBox).SelectedIndex != -1)
                    Prms.Prescaler = (byte)(sender as ComboBox).SelectedIndex;
            };
            m_cbPwmMode.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                Prms.PWMMode = CyParameters.GetEnum<CyEPWMMode>((sender as Control).Text);

                // If PWM Mode is "PWM_DT", Prescaler value is fixed "1x"
                if (Prms.PWMMode == CyEPWMMode.PWM_DT)
                {
                    m_cbPrescaler.SelectedIndex = 0;
                }

                UpdateVisibility();
                UpdatePWMGraph();
            };
            m_cbKillEvent.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                Prms.PWMKillEvent = CyParameters.GetEnum<CyEPWMEvent>((sender as Control).Text);
            };
            m_cbStopEvent.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                Prms.PWMStopEvent = CyParameters.GetEnum<CyEPWMStop>((sender as Control).Text);
                UpdateVisibility();
            };
            m_cbOutCCInvert.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                Prms.PWMOutCCInvert = CyParameters.GetEnum<CyPWMInvert>((sender as Control).Text);
                UpdatePWMGraph();
            };
            m_cbOutLineInvert.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                Prms.PWMOutInvert = CyParameters.GetEnum<CyPWMInvert>((sender as Control).Text);
                UpdatePWMGraph();
            };
            m_cbAlign.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                Prms.PWMSetAlign = CyParameters.GetEnum<CyEPWMAlign>((sender as Control).Text);
                UpdatePWMGraph();
            };
            m_cbRunMode.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                Prms.RunMode = CyParameters.GetEnum<CyERunMode>((sender as Control).Text);
            };
            m_pbPWMGraph.SizeChanged += delegate(object sender, EventArgs e)
            {
                UpdatePWMGraph();
            };

            numUpDownDeadTime.ValueChanged += delegate(object sender, EventArgs e)
            {
                Prms.PWMDeadTimeCycle = (byte)numUpDownDeadTime.Value;
                UpdatePWMGraph();
            };

            EventHandler interruptCheckChanged = delegate(object sender, EventArgs e)
            {
                if (m_cbInterruptOnCC.Checked && m_cbInterruptOnTC.Checked)
                    Prms.InterruptMask = CyEInterruptMask.INTR_MASK_TC_CC;
                else if (m_cbInterruptOnCC.Checked)
                    Prms.InterruptMask = CyEInterruptMask.INTR_MASK_CC_MATCH;
                else if (m_cbInterruptOnTC.Checked)
                    Prms.InterruptMask = CyEInterruptMask.INTR_MASK_TC;
                else
                    Prms.InterruptMask = CyEInterruptMask.INTR_MASK_NONE;
            };
            m_cbInterruptOnCC.CheckedChanged += interruptCheckChanged;
            m_cbInterruptOnTC.CheckedChanged += interruptCheckChanged;

            dgvAdvanced.CellValueChanged += new DataGridViewCellEventHandler(dgvAdvanced_CellValueChanged);
        }
        #endregion Constructor(s)

        #region Public functions
        public override IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errs = new List<CyCustErr>(base.GetErrors());
            errs.AddRange(registerGrid.GetErrors());
            return errs;
        }
       
        public void UpdateFormFromParams()
        {
            if (Prms == null) return;

            try
            {
                m_cbPrescaler.SelectedIndex = (int)Prms.Prescaler;
            }
            catch
            {
                m_cbPrescaler.SelectedIndex = 0;
            }

            CyParameters.SetComboValue(m_cbPwmMode, Prms.PWMMode);
            CyParameters.SetComboValue(m_cbKillEvent, Prms.PWMKillEvent);
            CyParameters.SetComboValue(m_cbStopEvent, Prms.PWMStopEvent);
            CyParameters.SetComboValue(m_cbOutCCInvert, Prms.PWMOutCCInvert);
            CyParameters.SetComboValue(m_cbOutLineInvert, Prms.PWMOutInvert);
            CyParameters.SetComboValue(m_cbAlign, Prms.PWMSetAlign);
            CyParameters.SetComboValue(m_cbRunMode, Prms.RunMode);

            numUpDownDeadTime.Value = Prms.PWMDeadTimeCycle;

            bool both = Prms.InterruptMask == CyEInterruptMask.INTR_MASK_TC_CC;
            m_cbInterruptOnCC.Checked = (Prms.InterruptMask == CyEInterruptMask.INTR_MASK_CC_MATCH) || both;
            m_cbInterruptOnTC.Checked = (Prms.InterruptMask == CyEInterruptMask.INTR_MASK_TC) || both;

            dgvAdvanced[1, (int)CySignals.RELOAD].Value = Prms.ReloadPresent;
            dgvAdvanced[1, (int)CySignals.START].Value = Prms.StartPresent;
            dgvAdvanced[1, (int)CySignals.STOP].Value = Prms.StopPresent;
            dgvAdvanced[1, (int)CySignals.COUNT].Value = Prms.CountPresent;
            dgvAdvanced[1, (int)CySignals.SWITCH].Value = Prms.SwitchPresent;

            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.RELOAD], Prms.ReloadMode);
            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.START], Prms.StartMode);
            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.STOP], Prms.StopMode);
            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.COUNT], Prms.CountMode);
            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.SWITCH], Prms.SwitchMode);

            registerGrid.UpdateFromParams();

            UpdateVisibility();
        }
        #endregion Public functions

        #region Private functions
        private void InitAdvTable()
        {
            ColumnMode.Items.AddRange(CyParameters.GetDescriptionList(typeof(CyETriggerMode)));

            string[] signals = CyParameters.GetDescriptionList(typeof(CySignals));
            for (int i = 0; i < signals.Length; i++)
            {
                dgvAdvanced.Rows.Add(signals[i], false, ColumnMode.Items[0]);
            }
            DataGridViewComboBoxCell switchModeCell = (DataGridViewComboBoxCell)
                                                dgvAdvanced.Rows[(int)CySignals.SWITCH].Cells[ColumnMode.Index];
            // Remove "Level" option for switch signal
            switchModeCell.Items.RemoveAt(3);
        }

        private void UpdateVisibility()
        {
            if (Prms == null) return;

            numUpDownDeadTime.Enabled = Prms.PWMMode == CyEPWMMode.PWM_DT;
            labelDtCycle.Visible = Prms.PWMMode != CyEPWMMode.PWM_PR;
            numUpDownDeadTime.Visible = Prms.PWMMode != CyEPWMMode.PWM_PR;
            m_labelRunMode.Visible = Prms.PWMMode == CyEPWMMode.PWM_PR;
            m_cbRunMode.Visible = Prms.PWMMode == CyEPWMMode.PWM_PR;

            m_cbPrescaler.Enabled = Prms.PWMMode != CyEPWMMode.PWM_DT;
            m_cbAlign.Enabled = (Prms.PWMMode != CyEPWMMode.PWM_PR);
            m_cbKillEvent.Enabled = (Prms.PWMMode != CyEPWMMode.PWM_PR);

            dgvAdvanced[0, (int)CySignals.STOP].Value = (Prms.PWMMode == CyEPWMMode.PWM_DT) ? "kill" : "stop";
            Prms.DisableRow(dgvAdvanced.Rows[(int)CySignals.COUNT], Prms.PWMMode == CyEPWMMode.PWM_PR);

            registerGrid.UpdateVisibility();
        }

        private void UpdatePWMGraph()
        {
            if (Prms.PWMMode == CyEPWMMode.PWM_PR)
            {
                m_pbPWMGraph.Image = null;
                m_pbPWMGraph.BackColor = SystemColors.Control;
                return; 
            }
            m_pbPWMGraph.BackColor = Color.White;
            m_pwmGraph.ImagePWMAlign = Prms.PWMSetAlign;
            m_pwmGraph.ImagePeriod = Prms.Period1;
            m_pwmGraph.ImagePeriod2 = Prms.Period2;
            m_pwmGraph.ImageSwapPeriod = Prms.PeriodSwap == CyESwapEnable.SWAP_ENABLE;
            m_pwmGraph.ImageCompare1 = Prms.Compare1;
            m_pwmGraph.ImageCompare2 = Prms.Compare2;
            m_pwmGraph.ImageSwapCompare = Prms.CompareSwap == CyESwapEnable.SWAP_ENABLE;
            m_pwmGraph.ImagePWMMode = Prms.PWMMode;
            m_pwmGraph.ImagePWMDeadTime = Prms.PWMDeadTimeCycle;
            m_pwmGraph.ImagePWMOutInvert = Prms.PWMOutInvert;
            m_pwmGraph.ImagePWMOutCCInvert = Prms.PWMOutCCInvert;
            m_pwmGraph.ImageSize = m_pbPWMGraph.Size;
            m_pwmGraph.ImageReloadPresent = Prms.ReloadPresent;
            m_pwmGraph.ImageIsTcpwmIpV2Ble = Prms.IsTcpwmIpV2BLE;
            m_pwmGraph.UpdateBmp();
            m_pbPWMGraph.Image = m_pwmGraph.ImageBmp;
        }
        #endregion Private functions

        #region Event handlers
        void dgvAdvanced_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == ColumnPresent.Index)
            {
                bool selValue = (bool)((DataGridViewCheckBoxCell)dgvAdvanced[e.ColumnIndex, e.RowIndex]).Value;
                switch ((CySignals)e.RowIndex)
                {
                    case CySignals.RELOAD:
                        Prms.ReloadPresent = selValue;
                        UpdatePWMGraph();
                        break;
                    case CySignals.START:
                        Prms.StartPresent = selValue;
                        break;
                    case CySignals.STOP:
                        Prms.StopPresent = selValue;
                        break;
                    case CySignals.SWITCH:
                        Prms.SwitchPresent = selValue;
                        break;
                    case CySignals.COUNT:
                        Prms.CountPresent = selValue;
                        break;
                    default:
                        break;
                }                
            }
            else if (e.ColumnIndex == ColumnMode.Index)
            {
                CyETriggerMode selValue = CyParameters.GetEnum<CyETriggerMode>(
                                               dgvAdvanced[e.ColumnIndex, e.RowIndex].Value.ToString());
                switch ((CySignals)e.RowIndex)
                {
                    case CySignals.RELOAD:
                        Prms.ReloadMode = selValue;
                        break;
                    case CySignals.START:
                        Prms.StartMode = selValue;
                        break;
                    case CySignals.STOP:
                        Prms.StopMode = selValue;
                        break;
                    case CySignals.SWITCH:
                        Prms.SwitchMode = selValue;
                        break;
                    case CySignals.COUNT:
                        Prms.CountMode = selValue;
                        break;
                    default:
                        break;
                }
            }           
        }

        private void dgvAdvanced_CurrentCellDirtyStateChanged(object sender, EventArgs e)
        {
            CommitCellValueImmediately(sender as DataGridView);
        }

        private void registerGrid_DataChanged(object sender, EventArgs e)
        {
            UpdatePWMGraph();
        }
        #endregion Event handlers    
    }
}

