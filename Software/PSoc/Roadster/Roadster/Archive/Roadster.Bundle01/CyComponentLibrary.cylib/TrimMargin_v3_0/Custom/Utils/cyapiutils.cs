/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Text;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;

namespace TrimMargin_v3_0.Utils
{
    internal static class CyApiGenUtils
    {
        private const int EXPR_PER_LINE = 2;
        private const int MAX_LINE_LENGTH = 120;

        public static void AddUnsignedStringElement(ref string baseStr, string element, bool last)
        {
            element += "u";
            AddStringElement(ref baseStr, element, last);
        }

        public static void AddStringElement(ref string baseStr, string element, bool last)
        {
            baseStr += (last == false) ? (element + ", ") : (element + " }");
        }

        public static string WordWrap(string str)
        {
            StringBuilder result = new StringBuilder();
            StringBuilder line = new StringBuilder();
            string[] splitted = str.Split(',');
            for (int i = 0; i < splitted.Length; i++)
            {
                if ((line.Length + splitted[i].Length + 1) <= MAX_LINE_LENGTH)
                {
                    line.Append(splitted[i]).Append(",");
                }
                else
                {
                    line.AppendLine();
                    result.Append(line.ToString());

                    line.Remove(0, line.Length);
                    line.Append(splitted[i]).Append(",");
                }
            }
            result.Append(line.Remove(line.Length - 1, 1).ToString());

            return result.ToString();
        }

        public static string GetIncludes(CyParameters parameters)
        {
            StringBuilder sb = new StringBuilder();
            if (parameters.PwmImplementation == CyEImplementation.FixedFunction)
            {
                for (int i = 0; i < parameters.NumConverters; i++)
                {
                    sb.AppendFormat("#include \"{0}_TrimTCPWM_{1}.h\"", parameters.InstanceName, i + 1).AppendLine();
                }
            }
            return sb.ToString();
        }

        public static string GetInits(CyParameters parameters)
        {
            StringBuilder sb = new StringBuilder();
            if (parameters.PwmImplementation == CyEImplementation.FixedFunction)
            {
                sb.AppendLine();
                for (int i = 0; i < parameters.NumConverters; i++)
                {
                    sb.AppendFormat("    {0}_TrimTCPWM_{1}_Init();", parameters.InstanceName, i + 1).AppendLine();
                }
            }
            return sb.ToString();
        }

        public static string GetEnables(CyParameters parameters)
        {
            StringBuilder sb = new StringBuilder();
            if (parameters.PwmImplementation == CyEImplementation.FixedFunction)
            {
                for (int i = 0; i < parameters.NumConverters; i++)
                {
                    sb.AppendFormat("    {0}_TrimTCPWM_{1}_Enable();", parameters.InstanceName, i + 1);
                    if (i < parameters.NumConverters - 1)
                    {
                        sb.AppendLine();
                    }
                }
            }
            return sb.ToString();
        }

        public static string GetStops(CyParameters parameters)
        {
            StringBuilder sb = new StringBuilder();
            if (parameters.PwmImplementation == CyEImplementation.FixedFunction)
            {
                for (int i = 0; i < parameters.NumConverters; i++)
                {
                    sb.AppendFormat("    {0}_TrimTCPWM_{1}_Stop();", parameters.InstanceName, i + 1);
                    if (i < parameters.NumConverters - 1)
                    {
                        sb.AppendLine();
                    }
                }
            }
            return sb.ToString();
        }

        public static string GetPwmCompareArray(CyParameters parameters)
        {
            StringBuilder array = new StringBuilder();
            string instName = parameters.InstanceName;
            bool is8bitResolution = parameters.PWMResolution == 8;
            string regSize = (parameters.PwmImplementation == CyEImplementation.FixedFunction)
                ? "reg32" : is8bitResolution ? "reg8" : "reg16";

            array.AppendFormat("static {0} * const CYCODE pwmCompare[] = {{", regSize).AppendLine();
            if (parameters.PwmImplementation == CyEImplementation.FixedFunction)
            {
                for (int i = 0; i < parameters.NumConverters; i++)
                {
                    string declaration = String.Format("{0}_TrimTCPWM_{1}_COMP_CAP_PTR,", instName, i + 1);
                    if (i % 2 == 0)
                    {
                        array.AppendFormat("    {0}", declaration);
                    }
                    else
                    {
                        array.AppendFormat(" {0}", declaration).AppendLine();
                    }
                }

                if (parameters.NumConverters % 2 != 0)
                {
                    array.AppendLine();
                }
            }
            else
            {
                int trimPwmCount = (parameters.NumConverters + EXPR_PER_LINE - 1) / EXPR_PER_LINE;

                string pwmCompare0 = is8bitResolution ? "_PWM8_PWM8dp_u0__D0_REG" : (parameters.IsPSoC4) ? 
                    "_PWM16_PWM16dp_u0__16BIT_D0_REG" : "_PWM16_PWM16dp_u0__D0_REG";
                string pwmCompare1 = is8bitResolution ? "_PWM8_PWM8dp_u0__D1_REG" : (parameters.IsPSoC4) ? 
                    "_PWM16_PWM16dp_u0__16BIT_D1_REG" : "_PWM16_PWM16dp_u0__D1_REG";


                for (int i = 0; i < trimPwmCount; i++)
                {
                    string tabulation = (i == trimPwmCount - 1) ? "" : ",";
                    string declaration;
                    declaration = String.Format("({0}*) {1}_TrimPWM_{2}", regSize, instName, i + 1);

                    array.AppendFormat("    {0}{1}", declaration, pwmCompare0);
                    if ((parameters.NumConverters % 2 == 0) || (i != trimPwmCount - 1)) 
                    {
                        array.AppendFormat(", {0}{1}", declaration, pwmCompare1);
                    }
                    array.Append(tabulation);
                    array.AppendLine();
                }
            }
            array.Append("}");
            return array.ToString();
        }

        public static string GetPwmCounterArray(CyParameters parameters)
        {
            StringBuilder array = new StringBuilder();
            bool is8bitResolution = parameters.PWMResolution == 8;
            int trimPwmCount = (parameters.NumConverters + EXPR_PER_LINE - 1) / EXPR_PER_LINE;
            string regSize = is8bitResolution ? "reg8" : "reg16";
            string element = is8bitResolution ? "_PWM8_PWM8dp_u0__A0_REG" : "_PWM16_PWM16dp_u0__A0_REG";

            array.AppendFormat("static {0} * const CYCODE pwmCounter[] = {{", regSize);
            array.AppendLine().Append("    ");
            for (int i = 0; i < trimPwmCount; i++)
            {
                string declaration = String.Format("({0}*) {1}_TrimPWM_{2}", regSize, parameters.InstanceName, i + 1);
                string tabulation = (i == trimPwmCount - 1)
                    ? Environment.NewLine
                    : "," + (((i % 2) == 0) ? " " : (Environment.NewLine + "    "));
                array.AppendFormat("{0}{1}{2}", declaration, element, tabulation);
            }
            array.Append("}");
            return array.ToString();
        }

        /// <summary>
        /// Gets a string with hexadecimal value, which represents converters feedback. 
        /// LSB corresponds to the first converter.
        /// </summary>
        public static string GetFeedbackValue(CyParameters parameters)
        {
            UInt32 value = 0;
            for (int i = 0; i < parameters.VoltagesTable.Count; i++)
            {
                if (parameters.VoltagesTable[i].Feedback == CyEFeedback.Negative)
                    value |= (1u << i);
            }

            // Return hex representation of UInt32 value
            string hex = CyHelper.ToHex(value);
            return (value > UInt16.MaxValue) ? String.Concat(hex, "ul") : String.Concat(hex, "u");
        }
    }
}
