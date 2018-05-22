/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System.Windows.Forms;
using System.Collections.Generic;
using TrimMargin_v3_0.Controls;

namespace TrimMargin_v3_0.Forms
{
    internal partial class CyVisibleColumnsDialog : Form
    {
        #region Constructor(s)
        public CyVisibleColumnsDialog(DataGridView dgv, List<DataGridViewColumn> notIncludedColumns,
            List<DataGridViewColumn> grayOutColumns)
        {
            InitializeComponent();

            CyColumnVisibilityCheckedListBox checkBox = new CyColumnVisibilityCheckedListBox(dgv, notIncludedColumns,
                grayOutColumns);
            checkBox.Bounds = m_placeHolderPanel.Bounds;
            checkBox.Anchor = m_placeHolderPanel.Anchor;
            this.Controls.Remove(m_placeHolderPanel);
            this.Controls.Add(checkBox);
        }
        #endregion

        #region Overrides
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (keyData == Keys.Escape)
            {
                this.Close();
                return true;
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }
        #endregion
    }
}
