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

namespace Scan_ADC_v2_10
{
    /// <summary>
    /// Attribute class for overriding CyEnum symbol parameter type names.
    /// 
    /// Apply to enum like this:
    /// 
    ///     [ParamTypeAttribute("CyEVabc")]
    ///     public enum CyEVxyz
    ///     {
    ///         ...
    ///     }
    /// </summary>
    [AttributeUsage(AttributeTargets.Enum)]
    public sealed class CyEnumCNameAttribute : System.Attribute
    {
        public string EnumCName { get; private set; }

        /// <summary>
        /// Attribute constructor.
        /// </summary>
        /// <param name="typeName">PSoC Creator enum type name.</param>
        public CyEnumCNameAttribute(string typeName)
        {
            this.EnumCName = typeName;
        }
    }

    public static class CyEnumUtils
    {
        public static string GetEnumCName<T>()
        {
            System.Reflection.MemberInfo info = typeof(T);
            string cName = info.Name;

            // The default name can be overridden 
            object[] attributes = info.GetCustomAttributes(true);
            foreach (object rawAttribute in attributes)
            {
                if (rawAttribute is CyEnumCNameAttribute)
                {
                    CyEnumCNameAttribute attribute
                        = (CyEnumCNameAttribute)rawAttribute;
                    cName = attribute.EnumCName;
                    break;
                }
            }

            return cName;
        }

        public static string GetEnumDescription<T>()
        {
            System.Reflection.MemberInfo info = typeof(T);
            string desc = info.Name;

            DescriptionAttribute[] attributes =
                (DescriptionAttribute[])info.GetCustomAttributes(
                typeof(DescriptionAttribute),
                false);
            if (attributes != null && attributes.Length > 0)
            {
                desc = attributes[0].Description;
            }

            return desc;
        }

        /// <summary>
        /// Find enum value's description.
        /// 
        /// A values description is either the value's "Description" attribute
        /// or the value's name.
        /// </summary>
        /// <typeparam name="T">Enum type</typeparam>
        /// <param name="value">Enum value</param>
        /// <returns>Enum value description</returns>
        public static string GetEnumDescription<T>(T value)
        {
            string desc = value.ToString();

            FieldInfo info = typeof(T).GetField(value.ToString());
            DescriptionAttribute[] attributes =
                (DescriptionAttribute[])info.GetCustomAttributes(
                typeof(DescriptionAttribute),
                false);
            if (attributes != null && attributes.Length > 0)
            {
                desc = attributes[0].Description;
            }

            return desc;
        }

        public static Dictionary<T, string> GetEnumValueNames<T>()
        {
            var valueNames = new Dictionary<T, string>();

            foreach (T value in Enum.GetValues(typeof(T)))
            {
                valueNames.Add(value, value.ToString());
            }

            return valueNames;
        }

        public static Dictionary<T, string> GetEnumValueDescriptions<T>()
        {
            var ValueDescriptions = new Dictionary<T, string>();

            foreach (T value in Enum.GetValues(typeof(T)))
            {
                string desc = GetEnumDescription<T>(value);
                ValueDescriptions.Add(value, desc);
            }

            return ValueDescriptions;
        }
    }
}
