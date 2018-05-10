/*******************************************************************************
* Copyright 2011-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Reflection;
using System.Windows.Forms;

namespace Scan_ADC_v2_0
{
    /// <summary>
    /// Display value pairs for ComboBox data source.
    /// </summary>
    /// <typeparam name="T">ComboBox value type</typeparam>
    public class CyDisplayValue<T>
    {
        public CyDisplayValue(string display, T value)
        {
            Display = display;
            Value = value;
        }

        public string Display { get; private set; }
        public T Value { get; private set; }
    }

    /// <summary>
    /// Utility functions for Scan_ADC model GUI combo boxes.
    /// </summary>
    public static class CyComboUtils
    {
        /// <summary>
        /// Make list of enum description value pairs.
        /// 
        /// A values description is either the value's "Description" attribute
        /// or the value's name.
        /// </summary>
        /// <typeparam name="T">ComboBox value enum type</typeparam>
        /// <returns>Enum description value pairs</returns>
        public static List<CyDisplayValue<T>> GetEnumMenuItems<T>()
        {
            string enumName = CyEnumUtils.GetEnumDescription<T>();

            var displayValues = new List<CyDisplayValue<T>>();

            foreach (T value in Enum.GetValues(typeof(T)))
            {
                string desc = CyEnumUtils.GetEnumDescription<T>(value);
                displayValues.Add(new CyDisplayValue<T>(desc, value));
            }

            return displayValues;
        }

        /// <summary>
        /// Set ComboBox data source to a list from an enum type.
        /// </summary>
        /// <typeparam name="T">Enum type for data source</typeparam>
        /// <param name="combo">ComboBox</param>
        public static void SetEnumDataSource<T>(ComboBox combo)
        {
            combo.DisplayMember = "Display";
            combo.ValueMember = "Value";
            combo.DataSource = CyComboUtils.GetEnumMenuItems<T>();
        }
    }
}