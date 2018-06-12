/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Diagnostics;
using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace RTC_PDL_v2_0
{
    public class CyCustomizer : ICyExprEval_v3
    {
        const string RTC_GET_DATE_FUNC = "RTC_GetDateComponent";

        public IEnumerable<CyExprEvalCustomFunctionData> GetCustomFunctionData()
        {
            yield return new CyExprEvalCustomFunctionData(RTC_GET_DATE_FUNC,
                String.Format("{0}(dateComponent) : uint", RTC_GET_DATE_FUNC),
                "Gets the year/month/dayofmonth/dayofweek/hour component of the date.");
        }

        public CyExprEvalFuncEx GetFunction(string exprFuncName)
        {
            switch (exprFuncName)
            {
                case RTC_GET_DATE_FUNC:
                    return new CyExprEvalFuncEx(GetDate);
                default:
                    return null;
            }
        }

        object GetDate(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            string argument = "";
            if ((args.Length > 0) && (args[0] != null))
            {
                argument = typeConverter.GetAsString(args[0]);

                switch (argument)
                {
                    case "year":
                        return (uint)DateTime.Now.Year;
                    case "month":
                        return (uint)DateTime.Now.Month;
                    case "dayofmonth":
                        return (uint)DateTime.Now.Day;
                    case "dayofweek":
                        return (uint)((int)DateTime.Now.DayOfWeek) + 1; // RTC driver first day of week starts from 1
                    case "hour":
                        return (uint)DateTime.Now.Hour;
                    default:
                        return new CyCustErr("Unhandled argument has passed in function '{0}'.", RTC_GET_DATE_FUNC);
                }
            }
            else
            {
                return new CyCustErr("Incorrect argument to call function '{0}'.", RTC_GET_DATE_FUNC);
            }
        }
    }
}
