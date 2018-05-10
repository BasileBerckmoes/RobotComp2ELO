/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using System.ComponentModel;
using System.Windows.Forms;
using System.Reflection;


namespace WaveDAC8_v2_10
{
    /// <summary>
    /// Wrapper for tabs
    /// </summary>
    public class CyEditingWrapperControl : UserControl, ICyParamEditingControl
    {
        protected CyParameters m_parameters = null;
        protected ErrorProvider m_errorProvider = null;

        public virtual string TabName
        {
            get { return String.Empty; }
        }

        public CyEditingWrapperControl()
        {
        }

        public CyEditingWrapperControl(CyParameters parameters)
        {
            m_parameters = parameters;

            m_errorProvider = new ErrorProvider();
            m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;

            this.AutoScroll = true;
            this.Dock = DockStyle.Fill;
        }

        #region ICyParamEditingControl Members
        public Control DisplayControl
        {
            get { return this; }
        }

        // Gets any errors that exist for parameters on the DisplayControl.
        public virtual IEnumerable<CyCustErr> GetErrors()
        {
            if (m_parameters.m_instQuery != null)
            {
                foreach (string paramName in m_parameters.m_instQuery.GetParamNames())
                {
                    CyCompDevParam param = m_parameters.m_instQuery.GetCommittedParam(paramName);
                    if (param.TabName.Equals(TabName))
                    {
                        if (param.ErrorCount > 0)
                        {
                            foreach (string errMsg in param.Errors)
                            {
                                yield return new CyCustErr(errMsg);
                            }
                        }
                    }
                }
            }

        }
        #endregion
    }
}
