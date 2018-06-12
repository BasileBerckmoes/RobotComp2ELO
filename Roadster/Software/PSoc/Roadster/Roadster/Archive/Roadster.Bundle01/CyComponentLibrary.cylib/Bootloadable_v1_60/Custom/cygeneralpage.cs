/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;

namespace Bootloadable_v1_60
{
    public partial class CyGeneralPage : CyEditingWrapperControl
    {
        const uint MIN_VAL = 0;
        const uint MAX_VAL_16 = UInt16.MaxValue;
        const uint MAX_VAL_32 = UInt32.MaxValue;
        const string MAX_VAL_16_STR = "0xFFFF";
        const string MAX_VAL_32_STR = "0xFFFFFFFF";
        const string HEX_PREFIX = "0x";

        public override string TabName
        {
            get { return "General"; }
        }

        public CyGeneralPage()
        {
            InitializeComponent();
        }

        public CyGeneralPage(CyParameters parameters)
        {
            InitializeComponent();
            m_parameters = parameters;
            InitFields();
        }

        public void InitFields()
        {
            textBoxAppVersion.Text = String.Format("0x{0:X4}", m_parameters.AppVersion);
            textBoxAppID.Text = String.Format("0x{0:X4}", m_parameters.AppID);
            textBoxAppCustomID.Text = String.Format("0x{0:X8}", m_parameters.AppCustomID);

            textBoxPlacementAddress.Text = String.Format("0x{0:X8}", m_parameters.PlacementAddress);
            checkBoxAutoImage.Checked = !m_parameters.AutoPlacement;

            numUpDownChecksumExcludeSize.Maximum = MAX_VAL_32;
            numUpDownChecksumExcludeSize.Value = m_parameters.ChecksumExcludeSize;

            VerifyPlacementAddress();
        }

        private void checkBoxAutoImage_CheckedChanged(object sender, EventArgs e)
        {
            textBoxPlacementAddress.Enabled = checkBoxAutoImage.Checked;
            labelPlacementAddress.Enabled = textBoxPlacementAddress.Enabled;
            m_parameters.AutoPlacement = !checkBoxAutoImage.Checked;

            // Remove error for textBoxPlacementAddress if it's disabled
            if (textBoxPlacementAddress.Enabled)
                textBoxHex_TextChanged(textBoxPlacementAddress, EventArgs.Empty);
            else
                errProvider.SetError(textBoxPlacementAddress, "");
        }

        private void textBoxHex_TextChanged(object sender, EventArgs e)
        {
            TextBox tb = (TextBox)sender;
            uint val;
            if (!CyUtils.IsHex(tb.Text))
            {
                errProvider.SetError(tb, String.Format(Properties.Resources.ErrTBFormat,
                                     (tb == textBoxAppCustomID) || (tb == textBoxPlacementAddress) ? 4 : 2));
            }
            else if ((tb == textBoxAppVersion) || (tb == textBoxAppID))
            {
                if (CyUtils.TryParseHex(tb.Text, out val))
                {
                    if (!CyUtils.CheckRange(val, MIN_VAL, MAX_VAL_16))
                    {
                        errProvider.SetError(tb, String.Format(Properties.Resources.ErrTBRange,
                                                               MIN_VAL, MAX_VAL_16_STR));
                    }
                    else
                    {
                        ApplyTBValue(tb);
                    }
                }
                else
                {
                    errProvider.SetError(tb, String.Format(Properties.Resources.ErrTBRange, MIN_VAL, MAX_VAL_16_STR));
                }
            }
            else if ((tb == textBoxAppCustomID) || (tb == textBoxPlacementAddress))
            {
                if (CyUtils.TryParseHex(tb.Text, out val))
                {
                    if (!CyUtils.CheckRange(val, MIN_VAL, MAX_VAL_32))
                    {
                        errProvider.SetError(tb, String.Format(Properties.Resources.ErrTBRange,
                                                               MIN_VAL, MAX_VAL_32_STR));
                    }
                    else
                    {
                        ApplyTBValue(tb);

                        if (tb == textBoxPlacementAddress)
                        {
                            VerifyPlacementAddress();
                        }
                    }
                }
                else
                {
                    errProvider.SetError(tb, String.Format(Properties.Resources.ErrTBRange, MIN_VAL, MAX_VAL_32_STR));
                }
            }
        }

        private void numUpDownChecksumExcludeSize_ValueChanged(object sender, EventArgs e)
        {
            UInt32 val;
            try
            {
                val = Convert.ToUInt32(numUpDownChecksumExcludeSize.Value);
            }
            catch (Exception)
            {
                return;
            }
            m_parameters.ChecksumExcludeSize = val;
        }

        // Check if Placement Address is a multiple of FlashRowLength
        private void VerifyPlacementAddress()
        {
            if ((m_parameters.AutoPlacement == false) && 
                (m_parameters.PlacementAddress % m_parameters.FlashRowLength != 0))
            {
                errProvider.SetError(textBoxPlacementAddress, String.Format(Properties.Resources.ErrPlacementAddress,
                                     m_parameters.FlashRowLength));
            }
            else
            {
                errProvider.SetError(textBoxPlacementAddress, "");
            }
        }

        private void ApplyTBValue(TextBox tb)
        {
            uint val;
            errProvider.SetError(tb, "");
            CyUtils.TryParseHex(tb.Text, out val);
            if (tb == textBoxAppVersion)
                m_parameters.AppVersion = (UInt16)val;
            else if (tb == textBoxAppID)
                m_parameters.AppID = (UInt16)val;
            else if (tb == textBoxAppCustomID)
                m_parameters.AppCustomID = (UInt32)val;
            else if (tb == textBoxPlacementAddress)
                m_parameters.PlacementAddress = (UInt32)val;
        }

        public override IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errorList = new List<CyCustErr>();
            errorList.AddRange(base.GetErrors());
            if (!String.IsNullOrEmpty(errProvider.GetError(textBoxAppVersion)) ||
                !String.IsNullOrEmpty(errProvider.GetError(textBoxAppID)) ||
                !String.IsNullOrEmpty(errProvider.GetError(textBoxAppCustomID)) ||
                (!String.IsNullOrEmpty(errProvider.GetError(textBoxPlacementAddress)) &&
                 (m_parameters.AutoPlacement == false)))
            {
                errorList.Add(new CyCustErr(Properties.Resources.ErrTBWrongValue));
            }

            return errorList.ToArray();
        }
    }
}
