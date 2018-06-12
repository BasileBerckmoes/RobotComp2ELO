/*******************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


using System;
using System.Diagnostics;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Collections.Generic;
using System.Windows.Forms;


namespace I2S_v2_70
{
    /// <summary>
    /// Wrapper for tabs
    /// </summary>
    public class CyEditingWrapperControl : UserControl, ICyParamEditingControl
    {
        protected CyI2SParameters m_parameters = null;
        protected ErrorProvider m_errorProvider = null;

        public virtual string TabName 
        {
            get { return string.Empty; }
        }

        protected CyEditingWrapperControl()
        {
        }

        public CyEditingWrapperControl(CyI2SParameters parameters)
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

        // Returns errors that exist for parameters on the DisplayControl.
        public virtual IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errs = new List<CyCustErr>();

            errs = CheckControlForErrors(this.Controls);

            if (m_parameters.InstQuery != null)
            {
                foreach (string paramName in m_parameters.InstQuery.GetParamNames())
                {
                    CyCompDevParam param = m_parameters.InstQuery.GetCommittedParam(paramName);
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
            }
            return errs;
        }

        /// <summary>
        /// Recursively grabs error messages from error provider for all controls
        /// </summary>
        /// <param name="controls">List of controls to check</param>
        /// <returns>List of found errors</returns>
        private List<CyCustErr> CheckControlForErrors(ControlCollection controls)
        {
            string errorMessage = string.Empty;
            List<CyCustErr> errs = new List<CyCustErr>();
            foreach (Control control in controls)
            {
                errorMessage = m_errorProvider.GetError(control);
                if (string.IsNullOrEmpty(errorMessage) == false)
                    errs.Add(new CyCustErr(errorMessage));

                // Recursively call itself again to make sure that nested controls does not contain errors
                if (control.Controls.Count > 0)
                    errs.AddRange(CheckControlForErrors(control.Controls));
            }
            return errs;
        }
        #endregion

        #region Utils
        /// <summary>
        /// Assign the dictionary as a data source to combobox items.
        /// </summary>
        /// <typeparam name="T">Type that represent combobox value </typeparam>
        /// <param name="cb">Combobox</param>
        /// <param name="dict">Dictionary - Key: combobox values; Value: string representation of values</param>
        public static void FillComboFromDictionary<T>(ComboBox cb, Dictionary<T, string> dict)
        {
            cb.DataSource = new BindingSource(dict, null);
            cb.ValueMember = "Key";
            cb.DisplayMember = "Value";
        }

        public static void SetComboValue(ComboBox cb, object value)
        {
            cb.SelectedValue = value;
        }
        /// <summary>
        /// Returns the selected comboBox value where comboBox item is a dictionary
        /// </summary>
        /// <typeparam name="T">T should be enum</typeparam>
        /// <param name="cb">ComboBox</param>
        /// <returns></returns>
        public static T GetComboValue<T>(ComboBox cb)
        {
            if (cb.SelectedItem == null)
            {
                return (T)Enum.GetValues(typeof(T)).GetValue(0);
            }

            return ((KeyValuePair<T, string>)cb.SelectedItem).Key;
        }

        /// <summary>
        /// Creates a dictionary that contains enumeration values and their text representation
        /// </summary>
        /// <typeparam name="T">Enumeration type</typeparam>
        /// <param name="descriptions">String descriptions separated by ';'</param>
        /// <returns>Dictionary that contains all enumeration values and their text representation</returns>
        public static Dictionary<T, string> GetEnumDictionary<T>(string descriptions)
        {
            Dictionary<T, string> dict = new Dictionary<T, string>();
            string[] descriptionList = descriptions.Split(';');
            T[] enumValues = (T[])Enum.GetValues(typeof(T));
            if (enumValues.Length != descriptionList.Length)
            {
                Debug.Assert(false);
                return dict;
            }
            for (int i = 0; i < enumValues.Length; i++)
            {
                dict.Add(enumValues[i], descriptionList[i].Trim());
            }
            return dict;
        }

        public static void SetNumValue(NumericUpDown num, double value)
        {
            decimal decimalValue = (decimal)value;
            if (decimalValue < num.Minimum)
                decimalValue = num.Minimum;
            else if (decimalValue > num.Maximum)
                decimalValue = num.Maximum;

            num.Value = decimalValue;
        }
        #endregion
    }
}
