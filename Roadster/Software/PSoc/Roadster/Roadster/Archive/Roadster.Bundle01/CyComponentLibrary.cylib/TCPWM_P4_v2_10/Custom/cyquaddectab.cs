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

namespace TCPWM_P4_v2_10
{
    public partial class CyQuadDecTab : CyEditingWrapperControl
    {
        enum CySignals  
        {
            [Description("stop")]
            STOP,
            [Description("index")]
            INDEX,
            [Description("phiA")]
            PHIA,
            [Description("phiB")]
            PHIB
        };

        public override string TabName
        {
            get { return "QuadDec"; }
        }

        public CyQuadDecTab(CyParameters prms)
            : base(prms)
        {
            InitializeComponent();

            Prms.m_quaddecTab = this;

            CyParameters.FillComboFromEnum(m_cbEncodingMode, typeof(CyEQuadMode));
            InitAdvTable();

            m_cbEncodingMode.SelectedIndexChanged += delegate(object sender, EventArgs e)
            {
                Prms.QuadEncodingModes = CyParameters.GetEnum<CyEQuadMode>((sender as Control).Text);
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

        private void InitAdvTable()
        {
            DataGridViewCellStyle readOnlyCellStyle = new DataGridViewCellStyle();
            readOnlyCellStyle.BackColor = SystemColors.Control;
            readOnlyCellStyle.SelectionBackColor = SystemColors.Control;
            
            ColumnMode.Items.AddRange(CyParameters.GetDescriptionList(typeof(CyETriggerMode)));

            string[] signals = CyParameters.GetDescriptionList(typeof(CySignals));
            for (int i = 0; i < signals.Length; i++)
            {
                dgvAdvanced.Rows.Add(signals[i], false, ColumnMode.Items[0]);
            }
            dgvAdvanced[1, (int)CySignals.PHIA].ReadOnly = true;
            dgvAdvanced[1, (int)CySignals.PHIB].ReadOnly = true;
            dgvAdvanced[1, (int)CySignals.PHIA].Style = readOnlyCellStyle;
            dgvAdvanced[1, (int)CySignals.PHIB].Style = readOnlyCellStyle;
            dgvAdvanced[1, (int)CySignals.PHIA].Value = true;
            dgvAdvanced[1, (int)CySignals.PHIB].Value = true;
        }

        public void UpdateFormFromParams()
        {
            CyParameters.SetComboValue(m_cbEncodingMode, Prms.QuadEncodingModes);

            bool both = Prms.InterruptMask == CyEInterruptMask.INTR_MASK_TC_CC;
            m_cbInterruptOnCC.Checked = (Prms.InterruptMask == CyEInterruptMask.INTR_MASK_CC_MATCH) || both;
            m_cbInterruptOnTC.Checked = (Prms.InterruptMask == CyEInterruptMask.INTR_MASK_TC) || both;

            dgvAdvanced[1, (int)CySignals.STOP].Value = Prms.StopPresent;
            dgvAdvanced[1, (int)CySignals.INDEX].Value = Prms.IndexPresent;

            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.STOP], Prms.StopMode);
            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.INDEX], Prms.IndexMode);
            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.PHIA], Prms.PhiAMode);
            CyParameters.SetComboCellValue((DataGridViewComboBoxCell)dgvAdvanced[2, 
                (int)CySignals.PHIB], Prms.PhiBMode);
        }

        void dgvAdvanced_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == ColumnPresent.Index)
            {
                bool selValue = (bool)((DataGridViewCheckBoxCell)dgvAdvanced[e.ColumnIndex, e.RowIndex]).Value;
                switch ((CySignals)e.RowIndex)
                {
                    case CySignals.STOP:
                        Prms.StopPresent = selValue;
                        break;
                    case CySignals.INDEX:
                        Prms.IndexPresent = selValue;
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
                    case CySignals.STOP:
                        Prms.StopMode = selValue;
                        break;
                    case CySignals.INDEX:
                        Prms.IndexMode = selValue;
                        break;
                    case CySignals.PHIA:
                        Prms.PhiAMode = selValue;
                        break;
                    case CySignals.PHIB:
                        Prms.PhiBMode = selValue;
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
    }
}
