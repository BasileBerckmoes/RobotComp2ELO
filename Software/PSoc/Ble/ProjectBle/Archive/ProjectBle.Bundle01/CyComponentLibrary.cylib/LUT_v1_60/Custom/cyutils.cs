/*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.IO;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;

namespace LUT_v1_60
{
    public class CyUtils
    {
        public const double EPS = 1E-5;

        #region Numeric
        /// <summary>
        /// Assigns minimum and maximum values to the NumericUpDown
        /// </summary>
        public static void SetNumericMinMax(NumericUpDown num, double min, double max)
        {
            num.Maximum = (decimal)max;
            num.Minimum = (decimal)min;
        }
        public static bool ValidateDoubleString(string text, double min, double max)
        {
            double value;
            bool isOK = Double.TryParse(text, out value);
            if (isOK)
            {
                if (value < min - EPS || value > max + EPS)
                    isOK = false;
            }
            return isOK;
        }

        /// <summary>
        /// Validates the text entered in the NumericUpDown and shows error in the error provider. 
        /// Return 'true' if validation passed.
        /// </summary>
        public static bool ValidateNumeric(NumericUpDown num, double min, double max, ErrorProvider errProvider)
        {
            bool isOK = ValidateDoubleString(num.Text, min, max);
            // Tag contains units of measurement
            string units = (num.Tag != null) ? num.Tag.ToString() : String.Empty;
            string msg = isOK ? String.Empty : String.Format("The value range is from {0} to {1}{2}.", min, max, units);
            SetError(errProvider, num, msg);
            return isOK;
        }

        public static bool ValidateNumeric(NumericUpDown num, decimal min, decimal max, ErrorProvider errProvider)
        {
            return ValidateNumeric(num, (double)min, (double)max, errProvider);
        }

        /// <summary>
        /// Set value to NumericUpDown. Verifies if it doesn't exceed Minimum and Maximum and if so, sets either 
        /// minimum or maximum.
        /// </summary>
        /// <param name="nud">NumericUpDown</param>
        /// <param name="value">Value to set</param>
        public static void SetNudValue(NumericUpDown nud, double value)
        {
            decimal decimalValue = (decimal)value;
            if (decimalValue < nud.Minimum)
                decimalValue = nud.Minimum;
            else if (decimalValue > nud.Maximum)
                decimalValue = nud.Maximum;

            nud.Value = decimalValue;
        }
        #endregion Numeric

        #region ErrorProvider
        /// <summary>
        /// Set the error to the control using error provider. 
        /// Performs additional checks (enable state, previously assigned error)
        /// </summary>
        public static void SetError(ErrorProvider errorProvider, Control control, string message, bool overwrite)
        {
            if (control.Enabled == false)
            {
                // Hide error provider if the control is disabled
                errorProvider.SetError(control, String.Empty);
            }
            else if (String.IsNullOrEmpty(errorProvider.GetError(control)) == false && overwrite == false)
            {
                // Do nothing if some error has been assigned to this control earlier
            }
            else
            {
                errorProvider.SetError(control, message);
            }
        }

        /// <summary>
        /// Set the error to the control using error provider. 
        /// Performs additional checks (enable state)
        /// </summary>
        public static void SetError(ErrorProvider errorProvider, Control control, string message)
        {
            SetError(errorProvider, control, message, true);
        }
        #endregion

        #region Conversion

        /// <summary>
        /// Converts a byte value to the hex string "0x00"
        /// </summary>
        public static string ToHexStr(byte value)
        {
            return String.Format("0x{0:X2}", value);
        }

        /// <summary>
        /// Converts a byte value to the hex string "FF"
        /// </summary>
        public static string ToHexStrNoPrefix(byte value)
        {
            return value.ToString("X2");
        }

        public static CyCustErr ConvertHexStrToByte(string s, out byte res)
        {
            res = 0;
            try
            {
                s = s.Trim();
                if (s.StartsWith("0x"))
                {
                    s = s.Substring("0x".Length);
                }
                res = Convert.ToByte(s, 16);
            }
            catch (Exception ex)
            {
                return new CyCustErr(ex.Message);
            }
            return CyCustErr.OK;
        }

        /// <summary>
        /// Checks if a char is a hexadecimal symbol
        /// </summary>
        public static bool IsHexChar(char c)
        {
            const string HEX_CHARS = "ABCDEFabcdef0123456789";
            return (HEX_CHARS.IndexOf(c) >= 0);
        }

        /// <summary>
        /// Checks if string starts with "0x" and is a correct hex string
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
        public static bool IsHexStr(string str)
        {
            bool result = str.StartsWith("0x") && str.Length > 2;
            for (int i = 2; i < str.Length; i++)
            {
                result &= IsHexChar(str[i]);
            }
            return result;
        }

        /// <summary>
        /// Checks if string contains only hexadecimal characters
        /// </summary>
        public static bool ContainsOnlyHexChars(string str)
        {
            for (int i = 0; i < str.Length; i++)
            {
                if (IsHexChar(str[i]) == false)
                    return false;
            }
            return true;
        }
        #endregion

        #region Export
        public static string ExportDataGridToCsv(DataGridView dgv)
        {
            const string CSV_SEPARATOR = ",";
            StringBuilder sb = new StringBuilder();

            for (int i = 0; i < dgv.Columns.Count; i++)
            {
                if (dgv.Columns[i].Visible)
                {
                    string headerText = dgv.Columns[i].HeaderText == null
                        ? ""
                        : dgv.Columns[i].HeaderText.Replace(Environment.NewLine, " ");
                    sb.Append(headerText).Append(CSV_SEPARATOR);
                }
            }
            sb.AppendLine();

            for (int i = 0; i < dgv.Rows.Count; i++)
            {
                for (int j = 0; j < dgv.Columns.Count; j++)
                {
                    if (dgv.Columns[j].Visible)
                        sb.Append(dgv.Rows[i].Cells[j].Value).Append(CSV_SEPARATOR);
                }
                sb.AppendLine();
            }
            return sb.ToString();
        }

        public static void SaveToFile(string text)
        {
            using (SaveFileDialog saveFileDialog = new SaveFileDialog())
            {
                saveFileDialog.Title = ResourceMsg.SaveFileDialogTitle;
                saveFileDialog.DefaultExt = ".csv";
                saveFileDialog.Filter = "CSV files (*.csv)|*.csv|All files (*.*)|*.*";
                saveFileDialog.FilterIndex = 1;
                saveFileDialog.RestoreDirectory = true;
                saveFileDialog.FileName = "LutTable";

                if (saveFileDialog.ShowDialog() == DialogResult.OK)
                {
                    try
                    {
                        using (StreamWriter writer = new StreamWriter(saveFileDialog.FileName))
                        {
                            writer.Write(text);
                        }
                    }
                    catch
                    {
                        MessageBox.Show(String.Format(ResourceMsg.FileWriteError, saveFileDialog.FileName),
                            ResourceMsg.ErrorWindowTitle, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
            }
        }
        #endregion
    }
}
