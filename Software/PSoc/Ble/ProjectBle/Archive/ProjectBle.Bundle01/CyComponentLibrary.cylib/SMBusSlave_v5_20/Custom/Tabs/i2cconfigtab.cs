/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Diagnostics;
using System.Windows.Forms;

namespace SMBusSlave_v5_20
{
    public partial class CyI2cConfigTab : CyTabWrapper
    {
        #region CyTabControlWrapper members
        public override string TabName
        {
            get { return "I2C Configuration"; }
        }
        #endregion

        #region Constructor(s)
        public CyI2cConfigTab(CyParameters parameters)
            : base(parameters)
        {
            InitializeComponent();
            m_params.I2cConfigTab = this;

            numMinusTolerance.TextChanged += new EventHandler(numMinusTolerance_TextChanged);
            numPlusTolerance.TextChanged += new EventHandler(numMinusTolerance_TextChanged);

            // Update dependent from implementation and clock source, controls appearence
            rbExternalClock_CheckedChanged(rbExternalClock, new EventArgs());
            rbFixedFunction_CheckedChanged(rbFixedFunction, new EventArgs());

            m_chbExternalIOBuff.CheckedChanged += new EventHandler(m_chbExternalIOBuff_CheckedChanged);
        }
        #endregion

        #region Assigning parameters values to controls
        public void UpdateUI()
        {
            bool prevGlobalEditMode = m_params.GlobalEditMode;
            m_params.GlobalEditMode = false;

            // Implementation
            switch (m_params.Implementation)
            {
                case CyEImplementationType.I2C__UDB:
                    rbUDB.Checked = true;
                    break;
                case CyEImplementationType.I2C__FixedFunction:
                    rbFixedFunction.Checked = true;
                    break;
                default:
                    Debug.Assert(false);
                    break;
            }

            // AddressDecode
            switch (m_params.AddressDecode)
            {
                case CyEAddressDecodeType.I2C__Software:
                    rbSoftware.Checked = true;
                    break;
                case CyEAddressDecodeType.I2C__Hardware:
                    rbHardware.Checked = true;
                    break;
                default:
                    Debug.Assert(false);
                    break;
            }

            // I2CBusPort
            switch (m_params.Pins)
            {
                case CyEBusPortType.I2C__Any:
                    rbAny.Checked = true;
                    break;
                case CyEBusPortType.I2C__I2C0:
                    rbI2C0.Checked = true;
                    break;
                case CyEBusPortType.I2C__I2C1:
                    rbI2C1.Checked = true;
                    break;
                default:
                    Debug.Assert(false);
                    break;
            }

            // InternalClock
            if (m_params.UdbInternalClock)
                rbInternalClock.Checked = true;
            else
                rbExternalClock.Checked = true;

            // FixedPlacement
            chbFixedPlacement.Checked = m_params.UdbSlaveFixedPlacementEnable;

            // Tolerance
            numMinusTolerance.Text = m_params.MinusTolerance.ToString();
            numPlusTolerance.Text = m_params.PlusTolerance.ToString();

            m_chbExternalIOBuff.Checked = m_params.ExternalIOBuffer;

            UpdateFixedPlacementAppearence();
            ImplementationAppearence();
            m_params.GlobalEditMode = prevGlobalEditMode;
        }
        #endregion

        #region Event handlers
        private void rbExternalClock_CheckedChanged(object sender, EventArgs e)
        {
            bool choise = ((RadioButton)sender).Checked;
            m_params.UdbInternalClock = (choise == false);

            panelTolerance.Enabled = (choise == false);
            m_params.GeneralTab.UpdateClockDependencies();
            m_params.UpdateTimeout();
        }

        private void rbFixedFunction_CheckedChanged(object sender, EventArgs e)
        {
            bool choise = ((RadioButton)sender).Checked;
            m_params.Implementation = choise ? CyEImplementationType.I2C__FixedFunction :
                CyEImplementationType.I2C__UDB;

            m_params.GeneralTab.UpdateClockDependencies();
            m_params.UpdateTimeout();
            gbUDBClockSource.Enabled = (choise == false);
            gbPinConnections.Enabled = choise;
            UpdateFixedPlacementAppearence();
            ImplementationAppearence();
        }

        private void rbHardware_CheckedChanged(object sender, EventArgs e)
        {
            m_params.AddressDecode = rbHardware.Checked ? CyEAddressDecodeType.I2C__Hardware :
                CyEAddressDecodeType.I2C__Software;
            m_params.GeneralTab.UpdateSmbAlertErrorProvider();
        }

        void m_chbExternalIOBuff_CheckedChanged(object sender, EventArgs e)
        {
            m_params.ExternalIOBuffer = m_chbExternalIOBuff.Checked;
        }

        private void rbPins_CheckedChanged(object sender, EventArgs e)
        {
            if (rbAny.Checked)
                m_params.Pins = CyEBusPortType.I2C__Any;
            else if (rbI2C0.Checked)
                m_params.Pins = CyEBusPortType.I2C__I2C0;
            else
                m_params.Pins = CyEBusPortType.I2C__I2C1;
        }

        private void chbFixedPlacement_CheckedChanged(object sender, EventArgs e)
        {
            bool state = ((CheckBox)sender).Checked;
            m_params.UdbSlaveFixedPlacementEnable = state;
            UpdateFixedPlacementAppearence();
        }

        private void numMinusTolerance_TextChanged(object sender, EventArgs e)
        {
            double minusToleranceValue = 0;
            double plusToleranceValue = 0;

            if (double.TryParse(numMinusTolerance.Text, out minusToleranceValue) &&
                double.TryParse(numPlusTolerance.Text, out plusToleranceValue))
            {
                minusToleranceValue *= -1;

                if ((minusToleranceValue < CyParamRange.TOLERANCE_MIN ||
                    minusToleranceValue > CyParamRange.TOLERANCE_MAX ||
                    plusToleranceValue < CyParamRange.TOLERANCE_MIN ||
                    plusToleranceValue > CyParamRange.TOLERANCE_MAX) &&
                    (m_params.Implementation == CyEImplementationType.I2C__UDB && m_params.UdbInternalClock == true))
                {
                    m_errorProvider.SetError(numPlusTolerance, string.Format(Resources.ToleranceOutOfRange,
                        CyParamRange.TOLERANCE_MIN, CyParamRange.TOLERANCE_MAX));
                }
                else
                    m_errorProvider.SetError(numPlusTolerance, string.Empty);
            }
            else
            {
                m_errorProvider.SetError(numPlusTolerance, string.Format(Resources.ToleranceOutOfRange,
                    CyParamRange.TOLERANCE_MIN, CyParamRange.TOLERANCE_MAX));
            }
            if (sender == numMinusTolerance)
                m_params.MinusTolerance = Math.Abs(minusToleranceValue);
            if (sender == numPlusTolerance)
                m_params.PlusTolerance = plusToleranceValue;
        }
        #endregion

        #region Fixed placement and implementation validation and enabling
        private void UpdateFixedPlacementAppearence()
        {
            if (m_params.UdbSlaveFixedPlacementEnable &&
                (m_params.Implementation == CyEImplementationType.I2C__FixedFunction))
            {
                m_errorProvider.SetError(chbFixedPlacement, Resources.FixedPlacementValidator);
            }
            else
            {
                m_errorProvider.SetError(chbFixedPlacement, string.Empty);
            }

            if (m_params.UdbSlaveFixedPlacementEnable == false &&
                (m_params.Implementation == CyEImplementationType.I2C__FixedFunction))
            {
                chbFixedPlacement.Enabled = false;
            }
            else
            {
                chbFixedPlacement.Enabled = true;
            }
        }

        private void ImplementationAppearence()
        {
            m_errorProvider.SetError(rbFixedFunction, string.Empty);
            rbFixedFunction.Enabled = true;
        }
        #endregion
    }

    public class CyPercentageUpDown : NumericUpDown
    {
        #region Overriden methods
        public override string Text
        {
            get { return base.Text.TrimEnd('%'); }
            set { base.Text = value + "%"; }
        }
        #endregion
    }
}
