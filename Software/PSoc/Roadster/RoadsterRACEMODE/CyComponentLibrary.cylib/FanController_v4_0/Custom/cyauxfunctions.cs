/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


using CyDesigner.Extensions.Common;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Reflection;
using System.Text;
using System.Windows.Forms;

namespace FanController_v4_0
{
    public class CyAuxFunctions
    {
        /// <summary>
        /// Applies a bit mask to the byte value
        /// </summary>
        /// <param name="initialValue"></param>
        /// <param name="mask"></param>
        /// <param name="on">Turn bits on or off</param>
        /// <returns></returns>
        public static byte SetBits(byte initialValue, byte mask, bool on)
        {
            byte result = initialValue;
            if (on) // set bits
            {
                result |= mask;
            }
            else // clear bits 
            {
                result &= (byte)((~mask) & 0xFF);
            }
            return result;
        }

        /// <summary>
        /// Returns enum value by its string representation
        /// </summary>
        /// <typeparam name="T">enum type</typeparam>
        /// <param name="value"></param>
        /// <returns></returns>
        public static T GetEnum<T>(string value)
        {
            return (T)GetEnum(value, typeof(T));
        }
        /// <summary>
        /// Convert enum description string to enum value
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        static object GetEnum(string value, Type _enumType)
        {
            foreach (FieldInfo fi in _enumType.GetFields())
            {
                DescriptionAttribute dna =
                (DescriptionAttribute)Attribute.GetCustomAttribute(
                fi, typeof(DescriptionAttribute));

                if ((dna != null) && (value == dna.Description))
                    return Enum.Parse(_enumType, fi.Name);
            }
            object res;
            try
            {
                res = Enum.Parse(_enumType, value);
            }
            catch
            {
                Debug.Assert(false);
                res = Enum.GetValues(_enumType).GetValue(0);
            }
            return res; 
        }

        /// <summary>
        /// Fills combo box with descriptions of all possible enumeration values
        /// </summary>
        /// <param name="cb"></param>
        /// <param name="enumType"></param>
        public static void FillComboByEnum(ComboBox cb, Type enumType)
        {
            cb.Items.Clear();
            cb.Items.AddRange(GetDescriptionList(enumType));
        }
        /// <summary>
        /// Selects a particular item in the combo box by enum value
        /// </summary>
        /// <param name="cb"></param>
        /// <param name="value"></param>
        public static void SetComboValue(ComboBox cb, object value)
        {
            string descr = GetDescription(value);
            SetString(cb, descr);
        }
        /// <summary>
        /// Looks for a string item in the combo box and selects it
        /// </summary>
        /// <param name="cb"></param>
        /// <param name="str"></param>
        static void SetString(ComboBox cb, string str)
        {
            for (int i = 0; i < cb.Items.Count; i++)
            {
                string item = cb.Items[i].ToString();
                if (item == str)
                {
                    cb.SelectedIndex = i;
                    return;
                }
            }
        }
        /// <summary>
        /// Returns a list of descriptions of all items in the enum
        /// </summary>
        /// <param name="_enumType">typeof([enumeration])</param>
        /// <returns>Array of descriptions</returns>
        static string[] GetDescriptionList(Type _enumType)
        {
            List<string> res = new List<string>();
            foreach (object item in Enum.GetValues(_enumType))
            {
                res.Add(GetDescription(item));
            }
            return res.ToArray();
        }
        /// <summary>
        /// Returns a description attribute of a particular item in the enum
        /// </summary>
        /// <param name="value">enum value</param>
        /// <returns>Description attribute value</returns>
        static string GetDescription(object value)
        {
            Type _enumType = value.GetType();
            FieldInfo fi = _enumType.GetField(Enum.GetName(_enumType, value));
            DescriptionAttribute dna = (DescriptionAttribute)Attribute.GetCustomAttribute(
                fi, typeof(DescriptionAttribute));

            if (dna != null)
                return dna.Description;
            else
                return value.ToString();
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
            where T: IConvertible
        {
            hasError = false;
            T val = default(T);
            string textValue = ((NumericUpDown)numericUpDown).Text;
            try
            {
                val = (T)Convert.ChangeType(textValue, typeof(T));
            }
            catch
            {
                hasError = true;
                if (String.IsNullOrEmpty(textValue))
                {
                    msg = Resources.ErrorEmptyField;
                }
                else
                {
                    msg = Resources.ErrorIncorrectValue;
                }
            }
            return val;
        }

        /// <summary>
        /// Validates text entered in the numericUpDown control. In case of wrong input format or value 
        /// out of range, an error provider is displayed.
        /// </summary>
        /// <returns>Returns null if the input format is wrong and converted decimal value in other case 
        /// (even if it is out of range).</returns>
        public static decimal? ValidateNumUpDown(NumericUpDown nud, ErrorProvider errProvider)
        {
            decimal? result = null;
            decimal value;
            decimal min = nud.Minimum;
            decimal max = nud.Maximum;
            bool parsed = decimal.TryParse(nud.Text, out value);
            if ((parsed == false) || (value < min - CyParamConst.EPS) || (value > max + CyParamConst.EPS))
            {
                string message = string.Format(Resources.ErrorValueLimit, min, max);
                if (errProvider != null)
                    errProvider.SetError(nud, message);
            }
            else
            {
                if (errProvider != null)
                    errProvider.SetError(nud, String.Empty);
                result = value;
            }
            return result;
        }

        #region DRC verification for PSoC 4 device
        public static List<CyCustErr> VerifyPSoC4Settings(CyParameters parameters)
        {
            List<CyCustErr> errorList = new List<CyCustErr>();
            
            if (parameters.IsPSoC4 == false)
                return errorList;

            // Verify Fan control mode
            if (parameters.GetFanMode() == CyFanModeDisplayType.AUTO_HARDWARE)
                errorList.Add(new CyCustErr(Resources.MsgHardwareModePSoC4));

            // The maximum number of PWM (fans or banks number) for PSoC4 is 4
            if ((parameters.BankMode == false) && (parameters.NumberOfFans > CyParamConst.MAX_PWM_PSOC4))
            {
                errorList.Add(new CyCustErr(Resources.ErrorFanBanksPSoC4));
            }
            // The maximum number of fans for PSoC4 is 8
            else if (parameters.NumberOfFans > CyParamConst.MAX_FAN_PSOC4)
            {
                errorList.Add(new CyCustErr(Resources.ErrorFanPSoC4)); 
            }

            return errorList;
        }
        #endregion DRC verification for PSoC 4 device
    }
}
