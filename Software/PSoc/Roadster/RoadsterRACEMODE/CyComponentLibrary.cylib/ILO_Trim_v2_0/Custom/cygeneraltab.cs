using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace ILO_Trim_v2_0
{
    public partial class CyGeneralTab : UserControl, ICyParamEditingControl
    {
        protected CyParameters m_params = null;

        public string TabName
        {
            get { return "General"; }
        }

        public CyGeneralTab(CyParameters param)
        {
            InitializeComponent();

            this.Dock = DockStyle.Fill;
            this.AutoScroll = true;

            m_params = param;
            m_errorProvider.Icon = SystemIcons.Information;

            #region Assigning event handlers
            m_rbFixedFunction.CheckedChanged += new EventHandler(m_rbCheckedChanged);
            m_rbUDB.CheckedChanged += new EventHandler(m_rbCheckedChanged);
            #endregion
        }

        public void UpdateUI()
        {
            if (m_params.IsFixedFunction)
            {
                m_rbFixedFunction.Checked = true;
            }
            else
            {
                m_rbUDB.Checked = true;
            }

            UpdateClockData(m_params.m_inst, m_params.m_term);
        }

        #region ICyParamEditingControl Members
        public Control DisplayControl
        {
            get { return this; }
        }

        public IEnumerable<CyCustErr> GetErrors()
        {
            return new List<CyCustErr>();
        }
        #endregion

        #region Event handlers
        private void m_rbCheckedChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                RadioButton rb = sender as RadioButton;

                if (rb == null || rb.Checked == false)
                    return;

                if (sender == m_rbFixedFunction || sender == m_rbUDB)
                {
                    m_params.IsFixedFunction = m_rbFixedFunction.Checked;
                    UpdateClockData();
                }
            }
        }
        #endregion

        public void UpdateClockData()
        {
            UpdateClockData(m_params.m_inst, m_params.m_term);
        }

        public void UpdateClockData(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            // Reference clock nominal frequency
            string frequencyStr = Resources.UnknownStr;
            double refFrequency = m_params.ReferenceClockKHz;
            if (CyParameters.IsFrequencyKnown(refFrequency))
            {
                frequencyStr = refFrequency.ToString(Resources.FreqKHzFormat);
            }
            m_lblRefClkFreq.Text = string.Format(Resources.RefClkFrequencyDisplayFmt, frequencyStr);

            // ILO clock nominal frequency
            frequencyStr = Resources.UnknownStr;
            double iloFrequency = m_params.ILOClockKHz;
            if (CyParameters.IsFrequencyKnown(iloFrequency))
            {
                frequencyStr = iloFrequency.ToString(Resources.FreqKHzFormat);
            }
            m_lblILOFreq.Text = string.Format(Resources.ILOClkFrequencyDisplayFmt, frequencyStr);

            // Ratio
            m_lblRatio.Text = string.Format(Resources.RatioDisplayFmt,
                CyParameters.GetRatio(refFrequency, iloFrequency));
            AddWarningInfo(m_params.RatioErrorDescription);
        }

        private void AddWarningInfo(string text)
        {
            int bottomPadding = 10;
            if (string.IsNullOrEmpty(text) && !string.IsNullOrEmpty(m_lblWarningMsg.Text))
            {
                m_grpClkInfo.Height -= m_errorProvider.Icon.Height + bottomPadding;
            }
            else if (!string.IsNullOrEmpty(text) && string.IsNullOrEmpty(m_lblWarningMsg.Text))
            {
                m_grpClkInfo.Height += m_errorProvider.Icon.Height + bottomPadding;
            }
            m_lblWarningMsg.Text = text;
            m_errorProvider.SetError(m_lblWarningMsg, text);
        }
    }
}
