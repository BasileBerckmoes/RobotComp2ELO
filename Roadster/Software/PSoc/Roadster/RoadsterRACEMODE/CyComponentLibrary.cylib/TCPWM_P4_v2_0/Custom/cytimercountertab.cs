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
    public partial class CyTimerCounterTab : CyEditingWrapperControl
    {
        enum CySignals
        {
            [Description("reload")]
            RELOAD,
            [Description("start")]
            START,
            [Description("stop")]
            STOP,
            [Description("capture")]
            CAPTURE,
            [Description("count")]
            COUNT
        };

        private CyImageTC m_counterGraph;

        public override string TabName
        {
            get { return "Timer/Counter"; }
        }

        #region Constructor(s)
        public CyTimerCounterTab(CyParameters prms)
            : base(prms)
        {
            InitializeComponent();

            Prms.m_tcTab = this;
            registerGrid.m_prms = prms;

            CyParameters.FillComboFromEnum(m_cbCounterMode, typeof(CyECounterMode));
            CyParameters.FillComboFromEnum(m_cbCompareCapture, typeof(CyECompCapMode));
            CyParameters.FillComboFromEnum(m_cbRunMode, typeof(CyERunMode));
            m_cbPrescaler.Items.Clear();
            m_cbPrescaler.Items.AddRange(CyParameters.PRESCALER_ITEMS_LIST);

            InitAdvTable();

            m_counterGraph = new CyImageTC();
            m_pbCounterGraph.Image = m_counterGraph.ImageBmp;
            m_pbCounterGraph.SizeMode = PictureBoxSizeMode.Normal;

            m_cbPrescaler.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                if ((sender as ComboBox).SelectedIndex != -1)
                    Prms.Prescaler = (byte)(sender as ComboBox).SelectedIndex;
            };
            m_cbCounterMode.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                Prms.CountingModes = CyParameters.GetEnum<CyECounterMode>((sender as Control).Text);
                UpdateCounterGraph();
            };
            m_cbCompareCapture.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                Prms.CompCapMode = CyParameters.GetEnum<CyECompCapMode>((sender as Control).Text);
                registerGrid.ValidatePeriodVsCompare();
                UpdateVisibility();
                UpdateCounterGraph();
            };
            m_cbRunMode.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                Prms.RunMode = CyParameters.GetEnum<CyERunMode>((sender as Control).Text);
            };
            m_pbCounterGraph.SizeChanged += delegate(object sender, EventArgs e)
            {
                UpdateCounterGraph();
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
            CyParameters.SetComboValue(m_cbCounterMode, Prms.CountingModes);
            CyParameters.SetComboValue(m_cbCompareCapture, Prms.CompCapMode);
            CyParameters.SetComboValue(m_cbRunMode, Prms.RunMode);

            bool both = Prms.InterruptMask == CyEInterruptMask.INTR_MASK_TC_CC;
            m_cbInterruptOnCC.Checked = (Prms.InterruptMask == CyEInterruptMask.INTR_MASK_CC_MATCH) || both;
            m_cbInterruptOnTC.Checked = (Prms.InterruptMask == CyEInterruptMask.INTR_MASK_TC) || both;

            dgvAdvanced[1, (int)CySignals.RELOAD].Value = Prms.ReloadPresent;
            dgvAdvanced[1, (int)CySignals.START].Value = Prms.StartPresent;
            dgvAdvanced[1, (int)CySignals.STOP].Value = Prms.StopPresent;
            dgvAdvanced[1, (int)CySignals.CAPTURE].Value = Prms.CapturePresent;
            dgvAdvanced[1, (int)CySignals.COUNT].Value = Prms.CountPresent;

            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.RELOAD], Prms.ReloadMode);
            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.START], Prms.StartMode);
            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.STOP], Prms.StopMode);
            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.CAPTURE], Prms.CaptureMode);
            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.COUNT], Prms.CountMode);

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
        }

        private void UpdateVisibility()
        {
            if (Prms == null) return;
            registerGrid.UpdateVisibility();
            Prms.DisableRow(dgvAdvanced.Rows[(int)CySignals.CAPTURE], Prms.CompCapMode == CyECompCapMode.Compare);
        }

        private void UpdateCounterGraph()
        {
            m_counterGraph.ImageCounterMode = Prms.CountingModes;
            m_counterGraph.ImagePeriod = Prms.Period1;
            m_counterGraph.ImageCompare1 = Prms.Compare1;
            m_counterGraph.ImageCompare2 = Prms.Compare2;
            m_counterGraph.ImageSwapCompare = Prms.CompareSwap == CyESwapEnable.SWAP_ENABLE;
            m_counterGraph.ImageTCCmpCapMode = Prms.CompCapMode;
            m_counterGraph.ImageSize = m_pbCounterGraph.Size;
            m_counterGraph.ImageReloadPresent = Prms.ReloadPresent;
            m_counterGraph.ImageIsTcpwmIpV2Ble = Prms.IsTcpwmIpV2BLE;
            m_counterGraph.UpdateBmp();
            m_pbCounterGraph.Image = m_counterGraph.ImageBmp;
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
                        UpdateCounterGraph();
                        break;
                    case CySignals.START:
                        Prms.StartPresent = selValue;
                        break;
                    case CySignals.STOP:
                        Prms.StopPresent = selValue;
                        break;
                    case CySignals.CAPTURE:
                        Prms.CapturePresent = selValue;
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
                    case CySignals.CAPTURE:
                        Prms.CaptureMode = selValue;
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

        void registerGrid_DataChanged(object sender, EventArgs e)
        {
            UpdateCounterGraph();
        }
        #endregion Event handlers
    }
}

