/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
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
using System.Windows.Forms.VisualStyles;
using System.Diagnostics;


namespace FanController_v4_0
{
    public partial class CyPidTab : CyEditingWrapperControl
    {
        #region TabName override
        /// <summary>
        /// TabName property of parameters in symbol that are edited on this tab
        /// </summary>
        public override string TabName
        {
            get { return "PID"; }
        }
        #endregion TabName override

        #region Constructor
        public CyPidTab(CyParameters param)
            : base(param)
        {
            InitializeComponent();

            InitcbOutputAttenuation();

            m_nudProportional.TextChanged += nudPercent_TextChanged;
            m_nudIntegral.TextChanged += nudPercent_TextChanged;
            m_nudDerivative.TextChanged += nudPercent_TextChanged;
            m_nudUpperLimit.TextChanged += nudPercent_TextChanged;
            m_nudLowerLimit.TextChanged += nudPercent_TextChanged;

            UpdateFormFromParams();
        }
        #endregion Constructor

        #region Form Updating Routines
        /// <summary>
        /// Fill Output Attenuation combobox Items list
        /// </summary>
        private void InitcbOutputAttenuation()
        {
            m_cbOutputAttenuation.Items.Clear();
            for (sbyte i = CyParamConst.MIN_ATTENUATION; i <= CyParamConst.MAX_ATTENUATION; i++)
            {
                m_cbOutputAttenuation.Items.Add(i);
            }
        }

        public void UpdateFormFromParams()
        {
            if (m_prms == null) return;

            NumUpDownSetValue(m_nudProportional,  (decimal)m_prms.CoefProportional);
            NumUpDownSetValue(m_nudIntegral, (decimal)m_prms.CoefIntegral);
            NumUpDownSetValue(m_nudDerivative, (decimal)m_prms.CoefDerivative);
            NumUpDownSetValue(m_nudUpperLimit, (decimal)m_prms.CoefUpperOutputLimit);
            NumUpDownSetValue(m_nudLowerLimit, (decimal)m_prms.CoefLowerOutputLimit);
            m_cbOutputAttenuation.SelectedItem = m_prms.CoefOutputAttenuation;
        }

        #endregion

        #region Event handlers
        /// <summary>
        /// This event handler is assigned to all numUpDown controls that display value in percents
        /// </summary>
        void nudPercent_TextChanged(object sender, EventArgs e)
        {
            decimal? nudValue = CyAuxFunctions.ValidateNumUpDown((NumericUpDown)sender, m_errorProvider);
            if (nudValue.HasValue)
            {
                if (sender == m_nudProportional)
                    m_prms.CoefProportional = (double)nudValue.Value;
                else if (sender == m_nudIntegral)
                    m_prms.CoefIntegral = (double)nudValue.Value;
                else if (sender == m_nudDerivative)
                    m_prms.CoefDerivative = (double)nudValue.Value;
                else if (sender == m_nudUpperLimit)
                    m_prms.CoefUpperOutputLimit = (double)nudValue.Value;
                else if (sender == m_nudLowerLimit)
                    m_prms.CoefLowerOutputLimit = (double)nudValue.Value;
                else
                    Debug.Assert(false);
            }
            ValidateAll();
        }

        private void cbOutputAttenuation_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_cbOutputAttenuation.SelectedItem != null)
            {
                m_prms.CoefOutputAttenuation = Convert.ToSByte(m_cbOutputAttenuation.SelectedItem);
            }
            ValidateAttenuation();
        }

        /// <summary>
        /// Output Attenuation combobox items are drawn manually. 2^n is drawn.
        /// </summary>
        private void cbOutputAttenuation_DrawItem(object sender, DrawItemEventArgs e)
        {
            if (e.Index < 0)
                return;

            e.DrawBackground();

            // Draw "2" with 1 pixel shift to the bottom
            TextRenderer.DrawText(e.Graphics, "2", m_cbOutputAttenuation.Font, new Point(e.Bounds.X, e.Bounds.Y + 1), 
                                  e.ForeColor);

            using (Font smallFont = new System.Drawing.Font(m_cbOutputAttenuation.Font.FontFamily, 6.5f))
            {
                // Draw power near "2"
                TextRenderer.DrawText(e.Graphics, m_cbOutputAttenuation.Items[e.Index].ToString(), smallFont, 
                                      new Point(e.Bounds.X + 8, e.Bounds.Y - 1), e.ForeColor);
            }

            e.DrawFocusRectangle();
        }
        #endregion

        #region Private functions
        /// <summary>
        /// Validates values in all controls and displays error providers
        /// </summary>
        private void ValidateAll()
        {
            CyAuxFunctions.ValidateNumUpDown(m_nudProportional, m_errorProvider);
            CyAuxFunctions.ValidateNumUpDown(m_nudIntegral, m_errorProvider);
            CyAuxFunctions.ValidateNumUpDown(m_nudDerivative, m_errorProvider);

            ValidateOutputLimit();
        }
        /// <summary>
        /// Validates if values in output limit controls are in range and if the lower limit doesn't exceed the upper.
        /// </summary>
        private void ValidateOutputLimit()
        {
            decimal? upperLimit = CyAuxFunctions.ValidateNumUpDown(m_nudUpperLimit, m_errorProvider);
            decimal? lowerLimit = CyAuxFunctions.ValidateNumUpDown(m_nudLowerLimit, m_errorProvider);

            if ((upperLimit != null) && (lowerLimit != null))
            {
                if (m_prms.CoefLowerOutputLimit > m_prms.CoefUpperOutputLimit)
                {
                    m_errorProvider.SetError(m_nudUpperLimit, Resources.ErrorSaturationLimits);
                    m_errorProvider.SetError(m_nudLowerLimit, Resources.ErrorSaturationLimits);
                }
                else
                {
                    m_errorProvider.SetError(m_nudUpperLimit, String.Empty);
                    m_errorProvider.SetError(m_nudLowerLimit, String.Empty);
                }
            }
        }

        /// <summary>
        /// Validates if output attenuation value will not result in overflow
        /// </summary>
        public void ValidateAttenuation()
        {
            const int ATTENUATION_OVERFLOW_VALUE = -23;
            if ((m_prms.CoefOutputAttenuation == ATTENUATION_OVERFLOW_VALUE) && 
                (m_prms.FanPWMRes == CyPWMResType.TEN_BIT))
            {
                m_errorProvider.SetError(m_cbOutputAttenuation, 
                    String.Format(Resources.ErrorPidAttenuation, ATTENUATION_OVERFLOW_VALUE + 1));
            }
            else
            {
                m_errorProvider.SetError(m_cbOutputAttenuation, String.Empty);
            }
        }

        /// <summary>
        /// Verifies if value is between numericUpDown's Minimum and Maximum and sets it. If value is out of range, 
        /// Maximum or Minimum value is set.
        /// </summary>
        private void NumUpDownSetValue(NumericUpDown nud, decimal value)
        {
            if (value > nud.Maximum)
                nud.Value = nud.Maximum;
            else if (value < nud.Minimum)
                nud.Value = nud.Minimum;
            else
                nud.Value = value;
        }
        #endregion Private functions 

        #region GetErrors() override
        public override IEnumerable<CyCustErr> GetErrors()
        {
            // If the tab is visible, call standard function
            if (m_prms.GetFanMode() == CyFanModeDisplayType.AUTO_FIRMWARE)
                return base.GetErrors();
            else // If this tab is hidden, return no errors
                return new List<CyCustErr>();
        }
        #endregion GetErrors() override
    }
}

