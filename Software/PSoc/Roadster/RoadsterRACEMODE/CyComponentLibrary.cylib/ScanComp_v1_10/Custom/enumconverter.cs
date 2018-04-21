/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using System.ComponentModel;

namespace ScanComp_v1_10
{
    static class CyEnumConverter
    {
        /// <summary>
        /// Converts enum description to value
        /// </summary>
        /// <param name="value"></param>
        /// <param name="enumType"></param>
        /// <returns></returns>
        public static T GetEnumValue<T>(object value)
        {
            Type enumType = typeof(T);
            foreach (FieldInfo fi in enumType.GetFields())
            {
                DescriptionAttribute dna =
                (DescriptionAttribute)Attribute.GetCustomAttribute(
                fi, typeof(DescriptionAttribute));

                if ((dna != null) && (value.ToString() == dna.Description))
                    return (T)Enum.Parse(enumType, fi.Name);
            }
            return (T)Enum.Parse(enumType, value.ToString());
        }

        /// <summary>
        /// Converts enum value to description
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public static string GetEnumDesc(object value)
        {
            Type enumType = value.GetType();
            FieldInfo fi = enumType.GetField(Enum.GetName(enumType, value));
            DescriptionAttribute dna = (DescriptionAttribute)Attribute.GetCustomAttribute(fi,
                typeof(DescriptionAttribute));

            return (dna != null) ? dna.Description : value.ToString();
        }

        /// <summary>
        /// Gets all enum descriptions
        /// </summary>
        /// <param name="enumType"></param>
        /// <returns></returns>
        public static string[] GetEnumDescList(Type enumType)
        {
            List<string> res = new List<string>();
            foreach (object item in Enum.GetValues(enumType))
            {
                res.Add(GetEnumDesc(item));
            }
            return res.ToArray();
        }
    }
}
