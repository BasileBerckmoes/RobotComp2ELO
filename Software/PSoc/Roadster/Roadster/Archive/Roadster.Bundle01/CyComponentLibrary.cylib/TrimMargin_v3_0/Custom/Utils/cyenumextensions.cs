/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Diagnostics;
using TrimMargin_v3_0.DataStructures;

namespace TrimMargin_v3_0.Utils
{
    internal static class CyEnumExtensions
    {
        public static string ToDisplayName(CyEFeedback item)
        {
            switch (item)
            {
                case CyEFeedback.Positive:
                    return Resources.FeedbackPositive;
                case CyEFeedback.Negative:
                    return Resources.FeedbackNegative;
                default:
                    Debug.Fail(String.Format("Unhandled enumeration item {0}", item));
                    return String.Empty;
            }
        }

        public static string ToDisplayName(CyEControllerMethod item)
        {
            switch (item)
            {
                case CyEControllerMethod.Incremental:
                    return Resources.ControllerMethodIncremental;
                case CyEControllerMethod.Integral:
                    return Resources.ControllerMethodIntegral;
                default:
                    Debug.Fail(String.Format("Unhandled enumeration item {0}", item));
                    return String.Empty;
            }
        }

        public static string ToDisplayName(CyEImplementation item)
        {
            switch (item)
            {
                case CyEImplementation.UDB:
                    return Resources.ImplementationUDB;
                case CyEImplementation.FixedFunction:
                    return Resources.ImplementationFixedFunction;
                default:
                    Debug.Fail(String.Format("Unhandled enumeration item {0}", item));
                    return String.Empty;
            }
        }

        public static string ToDisplayName(CyESeriesType item)
        {
            switch (item)
            {
                case CyESeriesType.E24:
                    return "E24";
                case CyESeriesType.E48:
                    return "E48";
                case CyESeriesType.E96:
                    return "E96";
                case CyESeriesType.E192:
                    return "E192";
                default:
                    Debug.Fail(String.Format("Unhandled enumeration item {0}", item));
                    return String.Empty;
            }
        }

        /// <summary>
        /// Returns a range for the specified field.
        /// </summary>
        public static CyRange GetRange(CyEFields field)
        {
            switch (field)
            {
                // Voltages table fields
                case CyEFields.NominalVoltage:
                case CyEFields.MinVoltage:
                case CyEFields.MaxVoltage:
                case CyEFields.StartupVoltage:
                case CyEFields.MarginLow:
                case CyEFields.MarginHigh:
                    return new CyRange(CyConstants.VOLTAGE_MIN, CyConstants.VOLTAGE_MAX);
                case CyEFields.MarginLowPercent:
                    return new CyRange(CyConstants.MARGIN_LOW_PERCENT_MIN, CyConstants.MARGIN_LOW_PERCENT_MAX);
                case CyEFields.MarginHighPercent:
                    return new CyRange(CyConstants.MARGIN_HIGH_PERCENT_MIN, CyConstants.MARGIN_HIGH_PERCENT_MAX);
                case CyEFields.ControlSampleTime:
                    return new CyRange(CyConstants.CONTROL_SAMPLE_TIME_MIN, CyConstants.CONTROL_SAMPLE_TIME_MAX);

                // Hardware table fields
                case CyEFields.VhPwmOutput:
                    return new CyRange(CyConstants.VDDIO_MIN, CyConstants.VDDIO_MAX);
                case CyEFields.Vadj:
                    return new CyRange(CyConstants.CONTROL_VOLTAGE_MIN, CyConstants.CONTROL_VOLTAGE_MAX);
                case CyEFields.R1:
                case CyEFields.R2:
                case CyEFields.R3:
                case CyEFields.R4:
                    return new CyRange(CyConstants.RESISTOR_MIN, CyConstants.RESISTOR_MAX);
                case CyEFields.DesiredVoutRipple:
                    return new CyRange(CyConstants.MAX_RIPPLE_MIN, CyConstants.MAX_RIPPLE_MAX);
                case CyEFields.C1:
                    return new CyRange(CyConstants.CAPACITOR_MIN, CyConstants.CAPACITOR_MAX);

                default:
                    Debug.Fail(String.Format("Unhandled field {0}.", field));
                    return new CyRange(Double.MinValue, Double.MaxValue);
            }
        }

        public static string GetRangeErrorFmt(CyEFields field)
        {
            switch (field)
            {
                // Voltages table fields
                case CyEFields.NominalVoltage:
                    return Resources.NominalOutputVoltageError;
                case CyEFields.MinVoltage:
                    return Resources.MinVoltageError;
                case CyEFields.MaxVoltage:
                    return Resources.MaxVoltageError;
                case CyEFields.StartupVoltage:
                    return Resources.StartupVoltageError;
                case CyEFields.MarginLowPercent:
                    return Resources.MarginLowPercentageError;
                case CyEFields.MarginHighPercent:
                    return Resources.MarginHighPercentageError;
                case CyEFields.MarginLow:
                    return Resources.MarginLowVoltageError;
                case CyEFields.MarginHigh:
                    return Resources.MarginHighVoltageError;
                case CyEFields.ControlSampleTime:
                    return Resources.ControlSampleTime;

                // Hardware table fields
                case CyEFields.VhPwmOutput:
                    return Resources.VDDIOVoltageError;
                case CyEFields.Vadj:
                    return Resources.ControlVoltageError;
                case CyEFields.R1:
                    return Resources.R1ResistorError;
                case CyEFields.R2:
                    return Resources.R2ResistorError;
                case CyEFields.R3:
                    return Resources.R3ResistorError;
                case CyEFields.R4:
                    return Resources.R4ResistorError;
                case CyEFields.DesiredVoutRipple:
                    return Resources.MaxRippleError;
                case CyEFields.C1:
                    return Resources.C1CapacitorError;

                default:
                    Debug.Fail(String.Format("Unhandled field {0}.", field));
                    return String.Empty;
            }
        }
    }
}