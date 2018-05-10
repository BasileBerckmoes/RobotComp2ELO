/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;

namespace WaveDAC8_v2_10
{
    public static class CyAuxFunctions
    {        
        #region Enumerations
        public static string[] GetDescriptionList(Type _enumType)
        {
            List<string> res = new List<string>();
            foreach (object item in Enum.GetValues(_enumType))
            {
                res.Add(GetDescription(item));
            }
            return res.ToArray();
        }
        static string GetDescription(object value)
        {
            Type _enumType = value.GetType();
            FieldInfo fi = _enumType.GetField(Enum.GetName(_enumType, value));
            DescriptionAttribute dna =
                (DescriptionAttribute)Attribute.GetCustomAttribute(
                fi, typeof(DescriptionAttribute));

            if (dna != null)
                return dna.Description;
            else
                return value.ToString();
        }
        public static T GetEnum<T>(string value)
        {
            return (T)GetEnum(value, typeof(T));
        }
        /// <summary>
        /// Convert enum description string to enum value
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        static object GetEnum(string value, Type enumType)
        {
            foreach (FieldInfo fi in enumType.GetFields())
            {
                DescriptionAttribute dna =
                (DescriptionAttribute)Attribute.GetCustomAttribute(
                fi, typeof(DescriptionAttribute));

                if ((dna != null) && (value == dna.Description))
                {
                    object res = Enum.Parse(enumType, fi.Name);
                    return res;
                }
            }

            return Enum.Parse(enumType, value);
        }
        #endregion

        #region Combobox, Numeric
        public static void FillComboFromEnum(ComboBox cb, Type enumType)
        {
            cb.Items.Clear();
            cb.Items.AddRange(GetDescriptionList(enumType));
        }
        public static void FillComboFromList<T>(ComboBox cb, T[] list)
        {
            cb.Items.Clear();
            for (int i = 0; i < list.Length; i++)
            {
                cb.Items.Add(GetDescription(list[i]));   
            }
        }
        public static void SetComboValue(ComboBox cb, object value)
        {
            string descr = GetDescription(value);
            if (cb.Items.Contains(descr))
                cb.SelectedItem = descr;
        }
        public static T GetComboValue<T>(ComboBox cb)
        {
            return GetEnum<T>(cb.Text);
        }

        public static void SetNudValue(NumericUpDown nud, decimal value)
        {
            if (value < nud.Minimum)
                value = nud.Minimum;
            else if (value > nud.Maximum)
                value = nud.Maximum;

            nud.Value = value;
        }

        /// <summary>
        /// Validates the text entered in the NumericUpDown. 
        /// </summary>
        /// <typeparam name="T">type of resulting value (double, int, byte, etc.)</typeparam>
        /// <param name="numericUpDown">Control to validate</param>
        /// <param name="hasError">Indicates if the input text has errors</param>
        /// <param name="msg">Error message. Empty in case of valid input text</param>
        /// <returns>Converted input value</returns>
        public static T GetNumUpDownTextValue<T>(object numericUpDown, out bool hasError, ref string msg)
            where T : IConvertible
        {
            hasError = false;
            T val = default(T);
            try
            {
                val = (T)Convert.ChangeType(((NumericUpDown)numericUpDown).Text, typeof(T));
            }
            catch
            {
                hasError = true;
                if (String.IsNullOrEmpty(((NumericUpDown)numericUpDown).Text))
                {
                    msg = cywavedacresource.ErrorEmptyField;
                }
                else
                {
                    msg = cywavedacresource.ErrorIncorrectValue;
                }
            }
            return val;
        }
        #endregion

        #region Waveforms
        /// <summary>
        /// Generates the byte array of waveform points
        /// </summary>
        public static List<byte> CreateWaveform(CyEWaveFormType waveType, uint numSamples, double maxVoltage,
                                                double amplitude, double dcOffset, ushort degreeShift)
        {
            List<byte> data = new List<byte>();
            double pointY = 0;
            byte value;
            double xShift = CalcXOffset(degreeShift); // Shift from 0 to 1
            for (int i = 0; i < numSamples; i++)
            {
                // maxXPos = numSamples (except for Sawtooth)
                double maxXPos = (waveType == CyEWaveFormType.Sawtooth) ? numSamples - 1 : numSamples;
                // Relative X position from 0 to 1
                double xPos = i / maxXPos + xShift;
                if (xPos > 1) xPos--;
                
                switch (waveType)
                {
                    case CyEWaveFormType.Sine:
                        pointY = CreateSineWaveform(xPos, amplitude);
                        break;
                    case CyEWaveFormType.Square:
                        pointY = CreateSquareWaveform(xPos, amplitude);
                        break;
                    case CyEWaveFormType.Triangle:
                        pointY = CreateTriangleWaveform(xPos, amplitude);
                        break;
                    case CyEWaveFormType.Sawtooth:
                        pointY = CreateSawtoothWaveform(xPos, amplitude);
                        break;
                    default:
                        Debug.Fail(String.Empty);
                        break;
                }
                pointY += dcOffset;                                           // Add DC offset
                pointY *= (CyParamConst.MAX_DATA_VALUE / maxVoltage);         // Scale from 0 to 255
                value = Convert.ToByte((pointY >= CyParamConst.MAX_DATA_VALUE) ? CyParamConst.MAX_DATA_VALUE : 
                                       (pointY <= 0) ? 0 : Math.Round(pointY));
                data.Add(value);
            }
            return data;
        }

        private static double CreateSineWaveform(double xPos, double amplitude)
        {
            double pointY = (amplitude / 2) * Math.Sin(xPos * (Math.PI * 2));
            return pointY;
        }

        private static double CreateTriangleWaveform(double xPos, double amplitude)
        {
            double oneQuarter = 0.25;
            double threeQuarter = 0.75;
            double pointY;

            if (xPos < oneQuarter) // First quarter of triangle wave
            {
                pointY = (((amplitude / 2) / oneQuarter) * xPos);  
            }
            else if (xPos < threeQuarter) // Second and third quarters
            {
                pointY = (amplitude - (((amplitude / 2) / oneQuarter) * (xPos - oneQuarter))) - (amplitude / 2);  
            }
            else // last quarter of triangle wave
            {
                pointY = (((amplitude / 2) / oneQuarter) * (xPos - threeQuarter)) - (amplitude / 2); 
            }
            return pointY;
        }

        private static double CreateSawtoothWaveform(double xPos, double amplitude)
        {
            // Create Triangle at amplitude at zero offset
            double pointY = amplitude * xPos - amplitude / 2;  
            return pointY;
        }

        private static double CreateSquareWaveform(double xPos, double amplitude)
        {
            double pointY;
            if (xPos < 0.5)
            {
                pointY = amplitude / 2;  // Positive half of square wave
            }
            else
            {
                pointY = -amplitude / 2;  // Negative half of square wave

            }
            return pointY;
        }

        private static double CalcXOffset(ushort degreeShift)
        {
            if (degreeShift > CyParamConst.MAX_DEGREE_SHIFT)
            {
                Debug.Fail(String.Empty);
                return 0;
            }
            if ((degreeShift == 0) || (degreeShift / CyParamConst.MAX_DEGREE_SHIFT == 1))
            {
                return 0;
            }

            return ((double)degreeShift) / CyParamConst.MAX_DEGREE_SHIFT;
        }
        #endregion

        #region Import / Export
        const string CSV_FILES_FILTER = "CSV Files (*.csv)|*.csv|";
        const string ALL_FILES_FILTER = "All Files (*.*)|*.*";
        const string REGEX_NUMBERS = @"[\d]+";
        const string REGEX_WORDS = @"[a-zA-Z]";

        #region Import functions
        /// <summary>
        /// Imports waveform data from the file. The file should contain separated decimal numbers from 0 to 255. 
        /// Any separators can be used. The number of samples is limited from 4 to 4000.
        /// </summary>
        /// <returns>Array of data points. Null in case of error</returns>
        public static List<byte> Import()
        {
            List<byte> loadedList = null;
            string errorMsg = String.Empty;

            string content = OpenFile();
            if (String.IsNullOrEmpty(content))
            {
                return null;
            }

            try
            {
                loadedList = new List<byte>();
                // Since different separators are supported, regex matches all numbers and then they are packed into
                // the array. Everything between numbers is omitted.
                Regex regexNumbers = new Regex(REGEX_NUMBERS);
                MatchCollection matches = regexNumbers.Matches(content);
                // If text contains word characters, it means, the format is wrong.
                Regex regexWords = new Regex(REGEX_WORDS);
                Match wrongFormatMatch = regexWords.Match(content);
                
                if (wrongFormatMatch.Success)
                {
                    errorMsg = cywavedacresource.ErrorParseDataValue;
                }
                else if ((matches.Count < CyParamConst.MIN_NUM_SAMPLES) || 
                         (matches.Count > CyParamConst.MAX_NUM_SAMPLES))
                {
                    errorMsg = String.Format(cywavedacresource.ErrorNumOfSamples, CyParamConst.MIN_NUM_SAMPLES,
                                                 CyParamConst.MAX_NUM_SAMPLES);
                }
                else
                {
                    foreach (Match match in matches)
                    {
                        byte number;
                        string numberStr = match.Value;
                        if (Byte.TryParse(numberStr, out number))
                        {
                            loadedList.Add(number);
                        }
                        else
                        {
                            errorMsg = cywavedacresource.ErrorParseDataValue;
                            break;
                        }
                    }
                }
            }
            catch (Exception)
            {
                Debug.Fail(String.Empty);
            }

            if (String.IsNullOrEmpty(errorMsg) == false)
            {
                MessageBox.Show(errorMsg, cywavedacresource.MsgErrorTitle, MessageBoxButtons.OK, MessageBoxIcon.Error);
                return null;
            }
            return loadedList;
        }
        #endregion

        /// <summary>
        /// Returns the string content of the file chosen with openFileDialog
        /// </summary>
        /// <returns>File text</returns>
        private static string OpenFile()
        {
            string content = "";
            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                openFileDialog.Filter = CSV_FILES_FILTER + ALL_FILES_FILTER;
                openFileDialog.Title = cywavedacresource.DialogImportTitle;
                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    try
                    {
                        content = File.ReadAllText(openFileDialog.FileName);
                    }
                    catch (Exception)
                    {
                        string errorMsg = String.Format(cywavedacresource.FileReadError, openFileDialog.FileName);
                        MessageBox.Show(errorMsg, cywavedacresource.MsgErrorTitle, MessageBoxButtons.OK, 
                                        MessageBoxIcon.Error);
                    }
                }
            }
            return content;
        }
        #endregion

        #region DRC
        public static CyCustErr VerifyExternalClock(CyParameters parameters)
        {
            CyCustErr error = CyCustErr.OK;
            CyClocking clocking = new CyClocking(parameters);
            error = clocking.VerifyExternalClock();               
            return error;
        }
        #endregion
    }

    /// <summary>
    /// This class stores the main characteristics of the voltage (current) range
    /// </summary>
    public class CyWaveRange
    {
        private const double DEFAULT_MAX_RANGE = 5.0;
        private const bool DEFAULT_VOLTS = true;
        public const string UNITS_VOLT = "V";
        public const string UNITS_mA = "mA";
        public const string UNITS_uA = "uA";
        public const string UNITS_Vpp = "pp";
        public const string UNITS_App = " p-p";

        private double m_maxRange;
        private double m_default;
        private bool m_volts;
        private string m_units;

        public CyWaveRange()
        {
            m_maxRange = DEFAULT_MAX_RANGE;
            m_default = DEFAULT_MAX_RANGE;
            m_volts = DEFAULT_VOLTS;
        }

        public CyWaveRange(double maxRange, bool volts)
        {
            m_maxRange = maxRange;
            m_volts = volts;
        }

        public double MaxRange
        {
            get { return m_maxRange; }
            set { m_maxRange = value; }
        }

        public double DefaultValue
        {
            get { return m_default; }
            set { m_default = value; }
        }

        public string Units
        {
            get { return m_units; }
            set { m_units = value; }
        }

        public string UnitsPP
        {
            get { return m_units + ((UNITS_VOLT == m_units) ? UNITS_Vpp : UNITS_App); }
        }

        public string GetFormattedValueStr(double value)
        {
            string format = ((value > 0) && (Units != UNITS_uA)) ? "f3" : "g";
            return string.Format("{0} {1}", value.ToString(format), Units);
        }
    }
}
