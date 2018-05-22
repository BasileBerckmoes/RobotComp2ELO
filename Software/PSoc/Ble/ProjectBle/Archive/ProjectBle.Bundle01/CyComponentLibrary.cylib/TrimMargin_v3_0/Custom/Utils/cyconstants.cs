/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

namespace TrimMargin_v3_0
{
    internal class CyConstants
    {
        //
        // Basic tab parameters
        //
        public const byte NUM_CONVERTERS_MIN = 1;
        public const byte NUM_CONVERTERS_MAX = 24;
        public const byte PWM_RESOLUTION_MIN = 8;
        public const byte PWM_RESOLUTION_MAX = 10;

        //
        // Voltages tab parameters
        //
        public const double VOLTAGE_MIN = 0.001;
        public const double VOLTAGE_MAX = 65.535;
        public const double MARGIN_LOW_PERCENT_MIN = -100;
        public const double MARGIN_LOW_PERCENT_MAX = 0;
        public const double MARGIN_HIGH_PERCENT_MIN = 0;
        public const double MARGIN_HIGH_PERCENT_MAX = 100;
        public const ushort CONTROL_SAMPLE_TIME_MIN = 1;
        public const ushort CONTROL_SAMPLE_TIME_MAX = 65535;
        // Voltages defaults
        public const double NOMINAL_VOLTAGE_DEFAULT = 2.25;
        public const double MAX_VOLTAGE_DEFAULT = 2.7;
        public const double MIN_VOLTAGE_DEFAULT = 1.8;
        public const double STARTUP_VOLTAGE_DEFAULT = 2.25;
        public const int MARGIN_HIGH_PERCENTAGE_DEFAULT = 10;
        public const int MARGIN_LOW_PERCENTAGE_DEFAULT = -10;
        public const ushort CONTROL_SAMPLE_TIME_DEFAULT = 100;
        public const CyEFeedback FEEDBACK_DEFAULT = CyEFeedback.Negative;

        //
        // Harware tab parameters
        //
        public const double VDDIO_MIN = 0.001;
        public const double VDDIO_MAX = 5.5;
        public const double CONTROL_VOLTAGE_MIN = 0.001;
        public const double CONTROL_VOLTAGE_MAX = 65.535;
        public const double VREF_VOLTAGE_MIN = 0.001;
        public const double VREF_VOLTAGE_MAX = 65.535;
        public const double CAPACITOR_MIN = 0.001;
        public const double CAPACITOR_MAX = 1000;
        public const double RESISTOR_MIN = 0.001;
        public const double RESISTOR_MAX = 100000;
        public const double MAX_RIPPLE_MIN = 0.001;
        public const double MAX_RIPPLE_MAX = 100;
        public const double NUM_CONVERTERS_WITH_PWM_RESOLUTION_MAX = 12;
        public const double PWM_RESOLUTION_WITH_NUM_CONVERTERS_MIN = 8;
        public const int E24_SERIES = 24;
        // Harware defaults
        public const double VOH_DEFAULT = 3.3;
        public const double VADJ_DEFAULT = 0.8;
        public const double VREF_DEFAULT = 0.8;
        public const double MAXRIPPLE_DEFAULT = 1;
        public const double R1_DEFAULT = 1;
        public const double R2_DEFAULT = 0.5;
        public const double R3_DEFAULT = 5;
        public const double R4_DEFAULT = 1;
        public const double C1_DEFAULT = 0.01;
        public const bool R2EN_DEFAULT = true;
        public const bool R3EN_DEFAULT = true;
        public const bool R4EN_DEFAULT = true;
        public const bool C1EN_DEFAULT = true;
        public const CyESeriesType RESISTORESERIES_DEFAULT = CyESeriesType.E192;
        public const CyESeriesType CAPACITORESERIES_DEFAULT = CyESeriesType.E192;

        //
        // General constants
        //
        public const double EPS = 0.0005;   // used for double values less/greater check
        public const double EPSILON = 1e-8; // used for double values equality check
        public const string FORM_TEXT_STRF = "Configure V{0}";
        public const string DEFAULT_CONVERTER_NAME_FMT = "Converter {0}";
    }
}