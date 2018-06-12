/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace bScanComp_v1_10
{
    [CyCompDevCustomizer()]
    public class CyCustomizer : ICyExprEval_v2
    {
        enum CyEChannelIntMode { INTR_RISING, INTR_FALLING, INTR_BOTH, INTR_DISABLE, INTR_LEVEL }

        #region ICyExprEval_v2 Members
        public CyExprEvalFuncEx GetFunction(string exprFuncName)
        {
            switch (exprFuncName)
            {
                case "GetInterruptMode":
                    return new CyExprEvalFuncEx(GetInterruptMode);
                default:
                    return null;
            }
        }

        /// <summary>
        /// Method is intended to be run by local parameter. After performing method parameter will contain
        /// value of interrupt mode for the selected channel
        /// </summary>
        /// <param name="exprFuncName">The name of the function</param>
        /// <param name="args">Arguments passed into the method during its call from parameter expression</param>
        /// <param name="custArgs">Contains references (sometimes null) to various customizer interface objects</param>
        /// <param name="typeConverter">Used to convert individual arguments from the args array into normal C# types 
        /// (bool, int, string, etc)</param>
        /// <returns>Interrupt mode for the selected channel</returns>
        private object GetInterruptMode(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            byte result = (byte)CyEChannelIntMode.INTR_DISABLE;

            if (custArgs.InstQuery == null)
                return result;

            if (args == null || args.Length < 1)
            {
                Debug.Assert(false, "Argument error");
                return result;
            }

            CyCompDevParam parameter = custArgs.InstQuery.GetCommittedParam("IntModeList");
            string intModeParam = (parameter.ErrorCount == 0) ? parameter.Value.ToString() : String.Empty;

            if (String.IsNullOrEmpty(intModeParam))
                return result;

            int index = Convert.ToInt32(args[0]);
            try
            {
                XmlSerializer serializer = new XmlSerializer(typeof(List<string>));
                List<string> intModeList = new List<string>();
                intModeList = (List<string>)serializer.Deserialize(new StringReader(intModeParam));

                if (intModeList != null && intModeList.Count > index)
                {
                    result = (byte)(CyEChannelIntMode)Enum.Parse(typeof(CyEChannelIntMode), intModeList[index]);
                }
            }
            catch
            {
                Debug.Assert(false,
                    String.Format("Error during deserialization: {0}; index = {1}", intModeParam, index));
            }

            return result;
        }
        #endregion
    }
}
