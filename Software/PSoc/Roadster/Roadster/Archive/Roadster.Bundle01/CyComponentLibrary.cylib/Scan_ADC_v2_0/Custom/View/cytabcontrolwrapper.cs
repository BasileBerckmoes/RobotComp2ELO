/*******************************************************************************
* Copyright 2011-2015, Cypress Semiconductor Corporation.  All rights reserved.
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

namespace Scan_ADC_v2_0
{
    public class CyTabControlWrapper : UserControl, ICyParamEditingControl
    {
        protected CyParameters m_params = null;
        protected ErrorProvider m_noteProvider = null;
        protected ErrorProvider m_warningProvider = null;
        protected ErrorProvider m_errorProvider = null;
        
        public virtual string TabName
        {
            get { return string.Empty; }
        }
        public CyTabControlWrapper() { }

        public CyTabControlWrapper(CyParameters param)
        {
            m_params = param;

            m_noteProvider = new ErrorProvider();
            m_noteProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;
            m_noteProvider.Icon = Scan_ADC_v2_0.View.cyguierrors.InformationIconIco;
            m_warningProvider = new ErrorProvider();
            m_warningProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;
            m_warningProvider.Icon = Scan_ADC_v2_0.View.cyguierrors.WarningIco;
            m_errorProvider = new ErrorProvider();
            m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;


            this.Load += new EventHandler(this.CyTabControlWrapper_Load);
        }

        private void CyTabControlWrapper_Load(object sender, EventArgs e)
        {
            this.Dock = DockStyle.Fill;
            this.AutoScroll = true;
        }

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

        protected override Point ScrollToControl(Control activeControl)
        {
            return AutoScrollPosition;
        }

        #region ICyParamEditingControl Members
        public Control DisplayControl
        {
            get { return this; }
        }

        public virtual IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errs = new List<CyCustErr>();
            string errorMessage = string.Empty;

            if (m_noteProvider != null)
            {
                // Check controls for errors
                foreach (Control control in this.Controls)
                {
                    errorMessage = m_noteProvider.GetError(control);
                    if (string.IsNullOrEmpty(errorMessage) == false)
                        errs.Add(new CyCustErr(errorMessage));

                    // Check controls inside groupbox
                    foreach (Control internalControl in control.Controls)
                    {
                        errorMessage = m_noteProvider.GetError(internalControl);
                        if (string.IsNullOrEmpty(errorMessage) == false)
                            errs.Add(new CyCustErr(errorMessage));
                    }
                }
            }

            foreach (string paramName in m_params.InstQuery.GetParamNames())
            {
                CyCompDevParam param = m_params.InstQuery.GetCommittedParam(paramName);
                if (param.TabName.Equals(TabName))
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
        #endregion
    }
}
