/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;

namespace I2S_v2_70
{
    public partial class CyI2SBasicTab : CyEditingWrapperControl
    {
        private Dictionary<CyEBitResolution, string> m_cbBitResolutionDictionary;

        public CyI2SBasicTab(CyI2SParameters parameters)
            : base(parameters)
        {
            InitializeComponent();

            parameters.GeneralTab = this;

            InitBitResolutionCombobox();
            InitDataBitsCombobox();
            InitWordSelectPeriodCombobox();
        }

        #region CyTabControlWrapper Members
        public override string TabName
        {
            get { return "Basic"; }
        }
        #endregion

        #region Assigning parameters values to controls

        private void InitBitResolutionCombobox()
        {
            m_cbBitResolution.DataSource = null;
            m_cbBitResolutionDictionary = GetEnumDictionary<CyEBitResolution>(Properties.Resources.EnumBitResolution);
            FillComboFromDictionary(m_cbBitResolution, m_cbBitResolutionDictionary);
        }

        private void InitDataBitsCombobox()
        {
            m_cbDataBits.Items.Clear();
            for (byte i = CyParamRanges.DATA_BITS_MIN; i <= CyParamRanges.DATA_BITS_MAX; i++)
            {
                if (m_parameters.BitResolutionStatic)
                {
                    m_cbDataBits.Items.Add(i);
                }
                else if (i % CyParamRanges.DATA_BITS_MULT_8 == 0)
                {
                    m_cbDataBits.Items.Add(i);
                }
            }

            if (m_cbDataBits.Items.Contains(m_parameters.DataBits))
            {
                m_cbDataBits.SelectedItem = m_parameters.DataBits;
            }
            else
            {
                m_cbDataBits.SelectedIndex = 0;
            }
        }

        private void InitWordSelectPeriodCombobox()
        {
            m_cbWordSelectPeriod.Items.Clear();
            for (int i = 0; i < CyParamRanges.WordSelectPeriodValues.Length; i++)
            {
                m_cbWordSelectPeriod.Items.Add(CyParamRanges.WordSelectPeriodValues[i]);
            }
        }

        public void UpdateUI()
        {
            // Direction
            switch (m_parameters.Direction)
            {
                case CyEDirection.Rx:
                    m_rbDirectionRx.Checked = true;
                    break;
                case CyEDirection.Tx:
                    m_rbDirectionTx.Checked = true;
                    break;
                case CyEDirection.Rx_and_Tx:
                    m_rbDirectionRxTx.Checked = true;
                    break;
                default:
                    Debug.Fail(Properties.Resources.DebugUnexpectedCase + typeof(CyENumberOfChannels).Name);
                    break;
            }

            SetComboValue(m_cbBitResolution, m_parameters.BitResolutionStatic ? 
                CyEBitResolution.Static : CyEBitResolution.Dynamic);

            m_cbDataBits.SelectedItem = m_parameters.DataBits;
            m_cbWordSelectPeriod.SelectedItem = m_parameters.WordSelectPeriod;

            m_chbRxByteSwap.Checked = m_parameters.RxByteSwap;
            m_chbTxByteSwap.Checked = m_parameters.TxByteSwap;

            ValidateWordSelectPeriod();
            SetEnableState();
            ShowImage();
        }
        #endregion

        #region Event Handlers
        private void radioButtonDirection_CheckedChanged(object sender, EventArgs e)
        {
            if (m_parameters.GlobalEditMode)
            {
                if (m_rbDirectionRx.Checked)
                    m_parameters.Direction = CyEDirection.Rx;
                else if (m_rbDirectionTx.Checked)
                    m_parameters.Direction = CyEDirection.Tx;
                else
                    m_parameters.Direction = CyEDirection.Rx_and_Tx;

                SetEnableState();
                m_parameters.AdvancedTab.OnDirectionChanged();
            }
        }

        private void m_cbBitResolution_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_parameters.GlobalEditMode)
            {
                m_parameters.BitResolutionStatic =
                    GetComboValue<CyEBitResolution>(m_cbBitResolution) == CyEBitResolution.Static;
                InitDataBitsCombobox();
            }
        }

        private void comboBoxDataBits_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_parameters.GlobalEditMode)
            {
                if (m_cbDataBits.SelectedItem != null)
                    m_parameters.DataBits = Convert.ToByte(m_cbDataBits.SelectedItem);

                ValidateWordSelectPeriod();
                ShowImage();
                SetEnableState();
            }
        }

        private void comboBoxWordSelectPeriod_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_parameters.GlobalEditMode)
            {
                if (m_cbWordSelectPeriod.SelectedItem != null)
                    m_parameters.WordSelectPeriod = Convert.ToByte(m_cbWordSelectPeriod.SelectedItem);

                ValidateWordSelectPeriod();
                ShowImage();
                SetEnableState();
            }
        }

        private void m_chbByteSwap_CheckedChanged(object sender, EventArgs e)
        {
            m_parameters.RxByteSwap = m_chbRxByteSwap.Checked;
            m_parameters.TxByteSwap = m_chbTxByteSwap.Checked;
            if (m_parameters.GlobalEditMode)
            {
                m_parameters.AdvancedTab.OnByteSwapChanged();
            }
        }


        private void m_pbGraph_SizeChanged(object sender, EventArgs e)
        {
            ShowImage();
        }
        #endregion

        #region Validation
        private void ValidateWordSelectPeriod()
        {
            if (m_parameters.WordSelectPeriod < m_parameters.DataBits*2)
            {
                m_errorProvider.SetError(m_cbWordSelectPeriod, Properties.Resources.WordSelectEPMsg);
            }
            else
            {
                m_errorProvider.SetError(m_cbWordSelectPeriod, "");
            }
        }
        #endregion

        #region Enabling/Disabling Controls
        public void SetEnableState()
        {
            bool enableByteSwap = m_parameters.DataBits >= CyParamRanges.BYTE_SWAP_DATA_BITS_MIN &&
                                  m_parameters.DataBits <= CyParamRanges.BYTE_SWAP_DATA_BITS_MAX &&
                                  m_parameters.WordSelectPeriod == CyParamRanges.BYTE_SWAP_WORD_SELECT_PERIOD;
            m_gbByteSwap.Enabled = enableByteSwap;

            if (enableByteSwap == false)
            {
                m_chbRxByteSwap.Checked = false;
                m_chbTxByteSwap.Checked = false;
            }

            m_chbRxByteSwap.Enabled = m_parameters.Direction != CyEDirection.Tx;
            m_chbTxByteSwap.Enabled = m_parameters.Direction != CyEDirection.Rx;
        }
        #endregion

        #region Drawing
        /// <summary>
        /// Draws image according to selected parameters
        /// </summary>
        private void ShowImage()
        {
            Image image = null;
            Bitmap bt;

            int dataBits = m_parameters.DataBits;
            int ws = m_parameters.WordSelectPeriod;

            float x = 0;
            float y = 0;
            float koef = 0.0f;

            string title = "LSB";
            string bit0 = "bit0";

            switch (ws) // Word select period can have 4 possible values: 16/32/48/64
            {
                case 16:
                    m_pbGraph.Image = Properties.Resources.WS_16;
                    break;
                case 32:
                case 48:
                case 64:
                    image = Properties.Resources.WS;

                    bt = new Bitmap(image.Width, image.Height);
                    Graphics g = Graphics.FromImage(bt);
                    koef = 96 / g.DpiX; // Calculating coefficient to miniaturize font size depending on DPI
                    g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.AntiAlias;
                    FontFamily ff = new FontFamily("Arial");
                    
                    Font sizeFont = new Font(ff, 11 * koef);
                    Font lsbFont = new Font(ff, 13 * koef, FontStyle.Bold);
                    Font bitFont = new Font(ff, 14 * koef);
                    
                    g.DrawImage(image, 0, 0);
                    SolidBrush sizeBrush = new SolidBrush(Color.Black);
                    SolidBrush lsbBrush = new SolidBrush(Color.FromArgb(233,34,34));
                    SolidBrush bitBrush = new SolidBrush(Color.Black);

                    if (dataBits == (ws / 2))
                    {
                        string bitM1 = "bit" + (ws / 2 - 1).ToString();

                        // Number
                        x = 190.0f; y = 5.0f;
                        g.DrawString((ws - 1).ToString(), sizeFont, sizeBrush, x, y);
                        // First Row (SDI)
                        // LSB
                        x = 854.0f; y = 181.0f;
                        g.DrawString(title, lsbFont, lsbBrush, x, y);
                        x = 1541.0f; y = 181.0f;
                        g.DrawString(title, lsbFont, lsbBrush, x, y);
                        // bit0 under LSB
                        x = 854.0f;
                        y = 218.0f;
                        g.DrawString(bit0, bitFont, bitBrush, x, y);
                        x = 1541.0f;
                        y = 218.0f;
                        g.DrawString(bit0, bitFont, bitBrush, x, y);
                        // bit n-1 under MSB
                        x = 223.0f;
                        y = 218.0f;
                        g.DrawString(bitM1, bitFont, bitBrush, x, y);
                        x = 910.0f;
                        y = 218.0f;
                        g.DrawString(bitM1, bitFont, bitBrush, x, y);

                        // Second Row (SDO)
                        // LSB
                        x = 855.0f; y = 285.0f;
                        g.DrawString(title, lsbFont, lsbBrush, x, y);
                        x = 1542.0f; y = 285.0f;
                        g.DrawString(title, lsbFont, lsbBrush, x, y);
                        // bit0 under LSB
                        x = 854.0f;
                        y = 320.0f;
                        g.DrawString(bit0, bitFont, bitBrush, x, y);
                        x = 1541.0f;
                        y = 320.0f;
                        g.DrawString(bit0, bitFont, bitBrush, x, y);
                        // bit n-1 under MSB
                        x = 223.0f;
                        y = 320.0f;
                        g.DrawString(bitM1, bitFont, bitBrush, x, y);
                        x = 910.0f;
                        y = 320.0f;
                        g.DrawString(bitM1, bitFont, bitBrush, x, y);

                    }
                    else if (dataBits == (ws / 2 - 1))
                    {
                        string bitM1 = "bit" + (dataBits - 1).ToString();

                        // Number
                        x = 190.0f; y = 5.0f;
                        g.DrawString((ws - 1).ToString(), sizeFont, sizeBrush, x, y);
                        // First Row (SDI)
                        // LSB
                        x = 792.0f; y = 183.0f;
                        g.DrawString(title, lsbFont, lsbBrush, x, y);
                        x = 1479.0f; y = 183.0f;
                        g.DrawString(title, lsbFont, lsbBrush, x, y);
                        // bit0 under LSB
                        x = 792.0f;
                        y = 218.0f;
                        g.DrawString(bit0, bitFont, bitBrush, x, y);
                        x = 1477.0f;
                        y = 218.0f;
                        g.DrawString(bit0, bitFont, bitBrush, x, y);
                        // bit n-1 under MSB
                        x = 223.0f;
                        y = 218.0f;
                        g.DrawString(bitM1, bitFont, bitBrush, x, y);
                        x = 909.0f;
                        y = 218.0f;
                        g.DrawString(bitM1, bitFont, bitBrush, x, y);

                        // Second Row (SDO)
                        // LSB
                        x = 792.0f; y = 285.0f;
                        g.DrawString(title, lsbFont, lsbBrush, x, y);
                        x = 1479.0f; y = 285.0f;
                        g.DrawString(title, lsbFont, lsbBrush, x, y);
                        // bit0 under LSB
                        x = 792.0f;
                        y = 320.0f;
                        g.DrawString(bit0, bitFont, bitBrush, x, y);
                        x = 1477.0f;
                        y = 320.0f;
                        g.DrawString(bit0, bitFont, bitBrush, x, y);
                        // bit n-1 under MSB
                        x = 222.0f;
                        y = 320.0f;
                        g.DrawString(bitM1, bitFont, bitBrush, x, y);
                        x = 909.0f;
                        y = 320.0f;
                        g.DrawString(bitM1, bitFont, bitBrush, x, y);
                    }
                    else if (dataBits < (ws / 2 - 1))
                    {
                        string bitM1 = "bit" + (dataBits - 1).ToString();

                        // Number
                        x = 190.0f; y = 5.0f;
                        g.DrawString((ws - 1).ToString(), sizeFont, sizeBrush, x, y);
                        // First Row (SDI)
                        // LSB
                        x = 665.0f; y = 180.0f;
                        g.DrawString(title, lsbFont, lsbBrush, x, y);
                        x = 1352.0f; y = 180.0f;
                        g.DrawString(title, lsbFont, lsbBrush, x, y);
                        // bit0 under LSB
                        x = 665.0f;
                        y = 218.0f;
                        g.DrawString(bit0, bitFont, bitBrush, x, y);
                        x = 1352.0f;
                        y = 218.0f;
                        g.DrawString(bit0, bitFont, bitBrush, x, y);
                        // bit n-1 under MSB
                        x = dataBits > 10 ? 223.0f : 227.0f;
                        y = 218.0f;
                        g.DrawString(bitM1, bitFont, bitBrush, x, y);
                        x = dataBits > 10 ? 910.0f : 914.0f;
                        y = 218.0f;
                        g.DrawString(bitM1, bitFont, bitBrush, x, y);
                        // Zeros between channels
                        x = 802.0f;
                        y = 216.0f;
                        g.DrawString("0", bitFont, bitBrush, x, y);
                        x = 865.0f;
                        y = 216.0f;
                        g.DrawString("0", bitFont, bitBrush, x, y);

                        // Second Row (SDO)
                        // LSB
                        x = 665.0f; y = 283.0f;
                        g.DrawString(title, lsbFont, lsbBrush, x, y);
                        x = 1352.0f; y = 283.0f;
                        g.DrawString(title, lsbFont, lsbBrush, x, y);
                        // bit0 under LSB
                        x = 665.0f;
                        y = 320.0f;
                        g.DrawString(bit0, bitFont, bitBrush, x, y);
                        x = 1352.0f;
                        y = 320.0f;
                        g.DrawString(bit0, bitFont, bitBrush, x, y);
                        // bit n-1 under MSB
                        x = dataBits > 10 ? 223.0f : 227.0f;
                        y = 320.0f;
                        g.DrawString(bitM1, bitFont, bitBrush, x, y);
                        x = dataBits > 10 ? 910.0f : 914.0f;
                        y = 320.0f;
                        g.DrawString(bitM1, bitFont, bitBrush, x, y);
                        // Zeros between channels
                        x = 804.0f;
                        y = 320.0f;
                        g.DrawString("0", bitFont, bitBrush, x, y);
                        x = 867.0f;
                        y = 320.0f;
                        g.DrawString("0", bitFont, bitBrush, x, y);
                    }
                    lsbFont.Dispose();
                    lsbBrush.Dispose();
                    bitFont.Dispose();
                    bitBrush.Dispose();
                    g.Dispose();
                    m_pbGraph.Image = bt;
                    break;
                default:
                    image = null;
                    break;
            }
        }
        #endregion
    }
}
