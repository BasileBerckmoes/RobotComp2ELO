/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Drawing;
using System.Diagnostics;
using System.Windows.Forms;
using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using TrimMargin_v3_0.Controls;

namespace TrimMargin_v3_0
{
    public class CyTabBase : UserControl, ICyParamEditingControl
    {
        #region Protected members
        protected CyParameters m_parameters = null;
        protected ErrorProvider m_errorProvider = null;
        protected DataGridView m_wrapperDataGridView = null;
        protected CyToolStrip m_wrapperToolStrip = null;
        #endregion

        #region Constructor(s)
        /// <summary>
        /// This constructor intended for correct control appearance in the designer mode.
        /// </summary>
        private CyTabBase() { }

        public CyTabBase(CyParameters parameters)
        {
            m_parameters = parameters;
            this.m_errorProvider = new ErrorProvider();
            this.m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;
            this.Dock = DockStyle.Fill;
            this.AutoScroll = true;
        }
        #endregion

        protected void UpdateErrorList(bool isCellValid, List<CyCustErr> errorList, CyCustErr errObj)
        {
            if (isCellValid)
            {
                if (errorList.Contains(errObj))
                    errorList.Remove(errObj);
            }
            else
            {
                if (errorList.Contains(errObj) == false)
                    errorList.Add(errObj);
            }
        }

        #region Data grid methods
        protected void CommitCellValueImmediately(DataGridView dataGridView)
        {
            if (dataGridView.CurrentCell != null)
                if (dataGridView.CurrentCell.GetType() == typeof(DataGridViewCheckBoxCell) ||
                    dataGridView.CurrentCell.GetType() == typeof(DataGridViewComboBoxCell))
                    if (dataGridView.IsCurrentCellDirty)
                    {
                        dataGridView.CommitEdit(DataGridViewDataErrorContexts.Commit);
                    }
        }

        protected int GetLessSelectedRow(DataGridViewSelectedRowCollection selectedRows)
        {
            // Get minimum value of selected rows
            int firstSelectedRow = 0;
            if (selectedRows.Count > 0)
            {
                int[] tmp = new int[selectedRows.Count];
                for (int i = 0; i < selectedRows.Count; i++)
                    tmp[i] = selectedRows[i].Index;

                firstSelectedRow = tmp[0];
                for (int i = 1; i < tmp.Length; i++)
                    if (tmp[i] < firstSelectedRow)
                        firstSelectedRow = tmp[i];
            }
            return firstSelectedRow;
        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (m_wrapperToolStrip == null || m_wrapperDataGridView == null)
                return base.ProcessCmdKey(ref msg, keyData);

            bool result = true;

            if (keyData == (Keys.Control | Keys.C))
            {
                if (m_wrapperDataGridView.SelectedRows.Count > 0)
                {
                    m_wrapperToolStrip.CopyRows();
                    result = true;
                }
                else
                    result = base.ProcessCmdKey(ref msg, keyData);
            }
            else if (keyData == (Keys.Control | Keys.V))
            {
                if (m_wrapperDataGridView.SelectedRows.Count > 0)
                {
                    m_wrapperToolStrip.PasteRows();
                    result = true;
                }
                else
                    result = base.ProcessCmdKey(ref msg, keyData);
            }
            else if (keyData == Keys.F2)
            {
                m_wrapperToolStrip.tsbConfigure_Click(null, null);
            }
            else if (keyData == (Keys.Control | Keys.Insert))
            {
                m_wrapperToolStrip.tsbAddConverter_Click(null, null);
            }
            else if (keyData == (Keys.Control | Keys.Delete))
            {
                m_wrapperToolStrip.tsbDelete_Click(null, null);
            }
            else if (keyData == (Keys.Alt | Keys.C))
            {
                m_wrapperToolStrip.tsbHideShowColumn_Click(null, null);
            }
            else if (keyData == (Keys.Control | Keys.S))
            {
                m_wrapperToolStrip.tsbSaveConfig_Click(null, null);
            }
            else if (keyData == (Keys.Control | Keys.O))
            {
                m_wrapperToolStrip.tsbOpenConfig_Click(null, null);
            }
            else
            {
                result = base.ProcessCmdKey(ref msg, keyData);
            }

            return result;
        }
        #endregion

        #region ICyParamEditingControl Members
        public Control DisplayControl
        {
            get { return this; }
        }

        // Gets any errors that exist for parameters on the DisplayControl.
        public virtual IEnumerable<CyCustErr> GetErrors()
        {
            Debug.Assert(this is ICyTab, String.Format("Class {0} must implement {1} interface.",
                this.Name, typeof(ICyTab).Name));

            List<CyCustErr> errs = new List<CyCustErr>();
            string tabName = (this as ICyTab).TabName;
            errs = GetControlErrors(this.Controls);

            List<string> dataGridErrors = GetAllDataGridErrors();
            if (dataGridErrors.Count > 0)
            {
                errs.Add(new CyCustErr(string.Format(Resources.DataGridError, tabName)));
            }

            // Look for errors in parameters
            foreach (string paramName in m_parameters.InstQuery.GetParamNames())
            {
                CyCompDevParam param = m_parameters.InstQuery.GetCommittedParam(paramName);
                if (param.TabName.Equals(tabName))
                {
                    if (param.ErrorCount > 0)
                    {
                        foreach (string errMsg in param.Errors)
                        {
                            errs.Add(new CyCustErr(errMsg));
                        }
                    }
                }
            }

            return errs;
        }

        public List<string> GetAllDataGridErrors()
        {
            List<string> errorList = new List<string>();
            for (int i = 0; i < m_wrapperDataGridView.RowCount; i++)
                for (int j = 0; j < m_wrapperDataGridView.ColumnCount; j++)
                {
                    if (String.IsNullOrEmpty(m_wrapperDataGridView[j, i].ErrorText) == false)
                    {
                        errorList.Add(m_wrapperDataGridView[j, i].ErrorText);
                    }
                }
            return errorList;
        }
        #endregion

        protected override Point ScrollToControl(Control activeControl)
        {
            if (activeControl.Height > ClientSize.Height
                || activeControl.Width > ClientSize.Width)
                return AutoScrollPosition;
            return base.ScrollToControl(activeControl);
        }

        #region Visibility
        private const string INVISIBLE_TAG = "Invisible";
        /// <summary>
        /// This function is used to set Visibility property for controls. It sets additionally the Tag value, 
        /// so the customizer can distinguish if a control is really hidden or just invisible at that moment  
        /// (it may happen if another tab is selected).
        /// </summary>
        protected static void SetVisible(Control c, bool isVisible)
        {
            c.Visible = isVisible;
            c.Tag = isVisible ? null : INVISIBLE_TAG;
        }

        /// <summary>
        /// Gets a value indicating whether the control is hidden.
        /// </summary>
        protected static bool IsControlHidden(Control c)
        {
            return (c.Visible == false) && (c.Tag != null) && (c.Tag.ToString() == INVISIBLE_TAG);
        }
        #endregion

        #region Controls errors check method(s)
        /// <summary>
        /// Clears the error provider error for the specifyed control.
        /// </summary>
        protected void ClearError(Control control)
        {
            m_errorProvider.SetError(control, String.Empty);
        }

        /// <summary>
        /// Gets the value indicating whether control contains an error.
        /// </summary>
        protected bool HasError(Control control)
        {
            return String.IsNullOrEmpty(m_errorProvider.GetError(control)) == false;
        }

        /// <summary>
        /// Sets the error provider error for the specified control.
        /// </summary>
        protected void SetError(Control control, string errorMessage)
        {
            m_errorProvider.SetError(control, errorMessage);
        }

        /// <summary>
        /// Gets a list of errors found on the control.
        /// </summary>
        protected List<CyCustErr> GetControlErrors(ControlCollection controls)
        {
            return GetControlErrors(m_errorProvider, controls);
        }

        public static List<CyCustErr> GetControlErrors(ErrorProvider errorProvider, ControlCollection controls)
        {
            string errorMessage = String.Empty;
            List<CyCustErr> errs = new List<CyCustErr>();
            foreach (Control control in controls)
            {
                if (control.Enabled && (IsControlHidden(control) == false))
                {
                    errorMessage = errorProvider.GetError(control);
                    if (String.IsNullOrEmpty(errorMessage) == false)
                        errs.Add(new CyCustErr(errorMessage));
                }
                // Recursively call itself again to make sure that nested controls do not contain errors
                if (control.Controls.Count > 0)
                    errs.AddRange(GetControlErrors(errorProvider, control.Controls));
            }
            return errs;
        }
        #endregion
    }
}
