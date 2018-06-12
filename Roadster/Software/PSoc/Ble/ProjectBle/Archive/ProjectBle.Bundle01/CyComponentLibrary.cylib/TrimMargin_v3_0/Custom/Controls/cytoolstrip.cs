/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Windows.Forms;
using System.Collections.Generic;
using TrimMargin_v3_0.Tabs;
using TrimMargin_v3_0.DataStructures;

namespace TrimMargin_v3_0.Controls
{
    public partial class CyToolStrip : UserControl
    {
        #region Constants
        private const string DEFAULT_EXTENSION = "xml";
        private const string FILTER_XML = "XML files (*.xml)|*.xml|All files (*.*)|*.*";
        #endregion

        #region Private fields
        private DataGridView m_dgv;
        private CyParameters m_params;
        #endregion

        #region Constructor(s)
        public CyToolStrip()
        {
            InitializeComponent();
        }
        #endregion

        #region Properties
        public bool DeleteConvertorEnable
        {
            get { return tsbDeleteConverter.Enabled; }
            set { tsbDeleteConverter.Enabled = value; }
        }

        public bool ConfigureConvertorEnable
        {
            get { return tsbConfigure.Enabled; }
            set { tsbConfigure.Enabled = value; }
        }
        #endregion

        public void Initialize(CyParameters param, DataGridView dgv)
        {
            m_params = param;
            m_dgv = dgv;
        }

        public void tsbAddConverter_Click(object sender, EventArgs e)
        {
            m_params.m_voltagesTab.AddConverter();
            ToggleAddConverter();
        }

        public void tsbDelete_Click(object sender, EventArgs e)
        {
            m_params.m_voltagesTab.DeleteSelectedRows();
        }

        private void tsbCopy_Click(object sender, EventArgs e)
        {
            CopyRows();
        }

        public void CopyRows()
        {
            if (this.Parent is CySummaryTab)
            {
                List<CyVoltagesTableRow> exportTableVoltages = new List<CyVoltagesTableRow>();
                List<CyHardwareTableRow> exportTableHardware = new List<CyHardwareTableRow>();
                for (int i = 0; i < m_dgv.RowCount; i++)
                {
                    if (m_dgv.Rows[i].Selected == true)
                    {
                        exportTableVoltages.Add(m_params.VoltagesTable[i]);
                        exportTableHardware.Add(m_params.HardwareTable[i]);
                    }
                }
                Clipboard.SetText(CyImportExport.Export(exportTableVoltages, exportTableHardware,
                    CyDataGridExtensions.GetColumnNames(m_dgv), m_params));
            }
        }

        private void tsbPaste_Click(object sender, EventArgs e)
        {
            PasteRows();
        }

        public void PasteRows()
        {
            string content = Clipboard.GetText();
            m_params.Import(content);
        }

        public void ToggleAddConverter()
        {
            tsbAddConverter.Enabled = m_params.VoltagesTable.Count < CyConstants.NUM_CONVERTERS_MAX;
        }

        public void ChangeCopyPasteEnabling(bool copyPasteButtonsEnabled)
        {
            tsbCopy.Enabled = copyPasteButtonsEnabled;
            tsbPaste.Enabled = copyPasteButtonsEnabled;
        }

        public void tsbConfigure_Click(object sender, EventArgs e)
        {
            m_params.m_voltagesTab.ConfigureConverter(m_dgv.SelectedCells[0].RowIndex);
        }
        public void tsbHideShowColumn_Click(object sender, EventArgs e)
        {
            m_params.m_voltagesTab.HideShowColumns();
        }

        public void tsbOpenConfig_Click(object sender, EventArgs e)
        {
            openFileDialog.Title = Resources.LoadDialogHeader;
            openFileDialog.FileName = string.Empty;
            openFileDialog.CheckFileExists = true;
            openFileDialog.CheckPathExists = true;
            openFileDialog.DefaultExt = DEFAULT_EXTENSION;
            openFileDialog.Filter = FILTER_XML;
            openFileDialog.FilterIndex = 1;
            openFileDialog.RestoreDirectory = true;
            openFileDialog.Multiselect = false;

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                DialogResult dr = MessageBox.Show(Resources.LoadConfirmation, m_params.InstQuery.ComponentName,
                    MessageBoxButtons.YesNo, MessageBoxIcon.Warning);
                if (dr == DialogResult.Yes)
                {
                    string fileContent = CyImportExport.GetFileText(openFileDialog.FileName);
                    m_params.LoadAllParametersFromFile(fileContent);
                }
            }
        }

        public void tsbSaveConfig_Click(object sender, EventArgs e)
        {
            saveFileDialog.Title = Resources.SaveDialogHeader;
            saveFileDialog.DefaultExt = DEFAULT_EXTENSION;
            saveFileDialog.Filter = FILTER_XML;
            saveFileDialog.FilterIndex = 1;
            saveFileDialog.RestoreDirectory = true;
            saveFileDialog.FileName = m_params.InstQuery.InstanceName;

            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                CyImportExport.SaveToFile(saveFileDialog.FileName, m_params.Serialize(m_params));
            }
        }
    }
}
