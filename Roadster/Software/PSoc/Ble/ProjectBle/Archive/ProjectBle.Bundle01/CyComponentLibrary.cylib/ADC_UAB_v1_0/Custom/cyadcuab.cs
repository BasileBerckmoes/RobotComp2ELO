/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

// The namespace is required to have the same name as the component for a customizer.
namespace ADC_UAB_v1_0
{
    public class CyAdcUab
    {
        public const int MIN_CODE = -8192;
        public const int MID_CODE = 0;
        public const int MAX_CODE = 8191;
        public const double MAX_CONVERSION_MS = 1.0;
        public const double MIN_VOLTAGE = -0.15;
        public const double MAX_VOLTAGE_OVER_VDDA = 0.0;
        public const double VREF_VAGND_RATIO = 2.0;
        public const double VREF_VAGND_LIMIT_V = 0.060;
        public const double VREF_VDDA_LIMIT_V = 0.6;
        public const double VAGND_VSSA_LIMIT_V = 0.6;
        public const double MIN_SYS_CLK_MHZ = 3000000.0;
        public const double SYS_CLK_TOLERANCE = 0.001;
        public const double VREF_BANDGAP_V = 1.2;
        public const double UAB_SRAM_CLK_HZ = 1000000.0;
        public const double INPUT_CAP_DEFAULT_VALUE = 12.0;
        public const double UAB_UNIT_CAP_SIZE = 0.000000000000050;
        public const double TAU_14_BITS = 10.4;
        public const double IMP_SETTLE_MARGIN = 5.0;
        public const double ROUTING_RESISTANCE = 5.0;
        public const double FILTER_ORDER = 2.0;
        public const double CONVERT_CPU_CYCLES = 179;

        private ADC_UAB_Parameters m_params;

        public CyAdcUab(ADC_UAB_Parameters parameters)
        {
            m_params = parameters;
        }

        private double Gain()
        {
            double value;

            switch (this.m_params.VRange)
            {
                case CyEGain.DoubleVref:
                    value = 2.0;
                    break;
                case CyEGain.OneVref:
                    value = 1.0;
                    break;
                case CyEGain.HalfVref:
                    value = 0.5;
                    break;
                case CyEGain.FourthVref:
                    value = 0.25;
                    break;
                default:
                    value = 0.125;
                    break;
            }

            return value;
        }

        private double Vref_V()
        {
            double vref_V = VREF_BANDGAP_V;
            if (this.m_params.VrefSource == CyEVrefSource.Vdda)
            {
                vref_V = this.m_params.VddaVolts / 2;
            }

            return vref_V;
        }

        private string ScaleText()
        {
            string text;

            switch (this.m_params.VRange)
            {
                case CyEGain.DoubleVref:
                    text = "2 * ";
                    break;
                case CyEGain.OneVref:
                    text = "";
                    break;
                case CyEGain.HalfVref:
                    text = "/ 2";
                    break;
                case CyEGain.FourthVref:
                    text = "/ 4";
                    break;
                default:
                    text = "/ 8";
                    break;
            }

            return text;
        }

        private double SwingVref_V()
        {
            double vref_V = this.Vref_V();
            double value = this.Gain() * vref_V;

            return value;
        }

        private double Vmid_V()
        {
            double base_V = this.Vref_V();

            return base_V;
        }

        private string VbaseText()
        {
            string name = "Vref";

            if (this.m_params.Endedness == CyEInputEndedness.SingleEnded)
            {
                // Keep Vref
            }
            else
            {
                name = "0";
            }

            return name;
        }

        public double Vmin_V()
        {
            double min_V = this.Vmid_V() - this.SwingVref_V();

            return min_V;
        }

        public double Vmax_V()
        {
            double max_V = this.Vmid_V() + this.SwingVref_V();

            return max_V;
        }

        public string Vlabel()
        {
            if (this.m_params.Endedness == CyEInputEndedness.Differential)
                return "Vdiff";
            else
                return "Vin";
        }

        public bool IsSaturateMax()
        {
            return (this.Vmax_V() > VmaxSaturate_V());            
        }

        public bool IsSaturateMin()
        {
            return (this.Vmin_V() < MIN_VOLTAGE);
        }

        private double VmaxSaturate_V()
        {
            return this.m_params.VddaVolts + MAX_VOLTAGE_OVER_VDDA;
        }

        public string MaxCode()
        {
            int maxCode = MAX_CODE;

            if(this.IsSaturateMax())
            {
                double scaledMax = (this.VmaxSaturate_V() - this.Vref_V()) / this.SwingVref_V(); 
                maxCode =  (int) (scaledMax *  MAX_CODE);
                
            }

            string text = maxCode.ToString();
            return text;
        }

        public string MinCode()
        {
            int minCode = MIN_CODE;

            if (this.IsSaturateMin())
            {
                double scaledMin = (this.Vref_V() - MIN_VOLTAGE) / this.SwingVref_V();
                minCode = (int) (scaledMin * MIN_CODE);
            }
            
            string text = minCode.ToString();
            return text;
        }

        public string VminVolts()
        {
            double volts = this.Vmin_V();

            if(this.IsSaturateMin())
            {
                volts = MIN_VOLTAGE;
            }

            string text = string.Format("{0:F3} V", volts);
            return text;
        }

        public string VmidVolts()
        {
            double volts = this.Vmid_V();
            string text = string.Format("{0:F3} V", volts);
            return text;
        }

        public string VmaxVolts()
        {
            double volts = this.Vmax_V();

            if(this.IsSaturateMax())
            {
                volts = this.VmaxSaturate_V();
            }
            string text = string.Format("{0:F3} V", volts);
            return text;
        }

        public string VlimitFormula(string sign)
        {
            string text = "Vref";
            string scale = this.ScaleText();
            if (scale.StartsWith("/"))
            {
                text = text + scale;
            }
            else
            {
                text = scale + text;
            }

            text = sign + text;

            string mid = this.VbaseText();

            if (mid != "0")
            {
                text = mid + text;
            }

            return text;
        }

        public string VminFormula()
        {
            string text = this.VlimitFormula(" - ");
            return text;
        }

        public string VmidFormula()
        {
            return this.VbaseText();
        }

        public string VmaxFormula()
        {
            string text = this.VlimitFormula(" + ");
            return text;
        }

        /// </summary>
        /// Decimation ratio lowered to meet a 1ms conversion at worst-case clock setup.
        /// Worst case is 6 MHz hfclk (allowing 2 MHz UAB clock) and 3 MHz CPU clock.
        /// Calculation is based on a sync2 filter and 179 cycles required to get a value
        /// from GetResult16() in an ISR.
        /// Return -1 if UAB clock is null.

        public double ConvTime_ms()
        {
            double convertTime = CyClock.UNKNOWN_FREQUENCY;
            double uabClk_kHz = CyClock.GetClockRate_Hz(this.m_params.m_termQuery, "HALF_A", "clock");

            if (uabClk_kHz > 0)
            {
                uabClk_kHz = uabClk_kHz / 2000.0;
                double sysClk_kHz = CyClock.GetSysClk_MHz(this.m_params) / 1000.0;
                double sampleTime = ((double) this.m_params.OSR * FILTER_ORDER) / uabClk_kHz;
                convertTime = CONVERT_CPU_CYCLES / sysClk_kHz;

                convertTime = (sampleTime + convertTime);
            }
            
            return convertTime;
        }

        public bool IsConvTimeInBounds()
        {
            bool result = false;
            double conv = ConvTime_ms();

            if (conv > 0 && conv < CyAdcUab.MAX_CONVERSION_MS)
            {
                result = true;
            }

            return result;
        }
        public string ConvTime()
        {
            double convertTime = this.ConvTime_ms();
            string text = string.Format("{0:0.00} ms", convertTime);
            return text;
        }

        public string MaxSourceImp()
        {
            double gain = this.Gain();
            //Input cap for 1/8 range is the same as 1/4, the reference caps area adjusted.
            if( gain == 0.125)
            {
                gain = 0.25;
            }

            // Source impedance is 1/fC
            // First, store C
            double impedance = (INPUT_CAP_DEFAULT_VALUE / gain) * UAB_UNIT_CAP_SIZE;
            impedance =  1 / (UAB_SRAM_CLK_HZ * impedance * TAU_14_BITS * IMP_SETTLE_MARGIN);

            // Display value in k
            impedance = (impedance / 1000.0) - ROUTING_RESISTANCE;

            string text = String.Format("{0:0} k", impedance);
            return text;
        }

        public bool IsSysClk3xUabClk()
        {
            double sysClk_MHz = CyClock.GetSysClk_MHz(this.m_params);
            double uabClk_kHz = CyClock.GetClockRate_Hz(this.m_params.m_termQuery, "HALF_A", "clock");

            if( sysClk_MHz >= (uabClk_kHz * 1.5))
            {
                return true;
            }

            return false;
        }

        public bool IsSysClkOK()
        {
            double sysClk_MHz = CyClock.GetSysClk_MHz(this.m_params);

            if (sysClk_MHz < (1.0 - CyAdcUab.SYS_CLK_TOLERANCE) * CyAdcUab.MIN_SYS_CLK_MHZ)
            {
                return false;
            }

            return true;
        }

        public string ConversionTimeErrorMessage()
        {
            var message = string.Format(
                global::ADC_UAB_v1_0.ADC_UAB_Errors.conversionTimeError, 
                this.ConvTime_ms());

            return message;
        }

        public static string SysClkErrorMessage()
        {
            var message = string.Format(
                global::ADC_UAB_v1_0.ADC_UAB_Errors.sysClkError,
                CyAdcUab.MIN_SYS_CLK_MHZ / 1000000.0);

            return message;
        }

        public static string SaturateMaxErrorMessage()
        {
            return global::ADC_UAB_v1_0.ADC_UAB_Errors.saturateHighError;
        }

		public List<CyDisplayValue<CyVrefGainPair>> GetSingleEndedRanges()
		{
            // Saturate the single ended range when over Vdda + 0.15 V
            string twoVrefMax = (this.VmaxSaturate_V() > 3.6) ? "3.6 V" : string.Format("{0:F3} V", this.VmaxSaturate_V());
            string oneVrefMax = (this.VmaxSaturate_V() > 2.4) ? "2.4 V" : string.Format("{0:F3} V", this.VmaxSaturate_V());

            List<CyDisplayValue<CyVrefGainPair>> singleEndedRanges = new List<CyDisplayValue<CyVrefGainPair>>
			{
			    new CyDisplayValue<CyVrefGainPair>(string.Concat("-0.15 V to ", twoVrefMax),
				    new CyVrefGainPair(CyEVrefSource.Bandgap, CyEGain.DoubleVref)),
			    new CyDisplayValue<CyVrefGainPair>(string.Concat("0 V to ", oneVrefMax),
				    new CyVrefGainPair(CyEVrefSource.Bandgap, CyEGain.OneVref)),
			    new CyDisplayValue<CyVrefGainPair>("0.6 V to 1.8 V",
				    new CyVrefGainPair(CyEVrefSource.Bandgap, CyEGain.HalfVref)),
			    new CyDisplayValue<CyVrefGainPair>("0.9 V to 1.5 V",
				    new CyVrefGainPair(CyEVrefSource.Bandgap, CyEGain.FourthVref)),
			    new CyDisplayValue<CyVrefGainPair>("1.05 V to 1.35 V",
				    new CyVrefGainPair(CyEVrefSource.Bandgap, CyEGain.EighthVref)),

			    new CyDisplayValue<CyVrefGainPair>("-0.15 V to Vdda V",
				    new CyVrefGainPair(CyEVrefSource.Vdda, CyEGain.DoubleVref)),
			    new CyDisplayValue<CyVrefGainPair>("0 V to Vdda",
				    new CyVrefGainPair(CyEVrefSource.Vdda, CyEGain.OneVref)),
			    new CyDisplayValue<CyVrefGainPair>("0.25 Vdda to 0.75 Vdda",
				    new CyVrefGainPair(CyEVrefSource.Vdda, CyEGain.HalfVref)),
			    new CyDisplayValue<CyVrefGainPair>("0.375 Vdda to 0.625 Vdda",
				    new CyVrefGainPair(CyEVrefSource.Vdda, CyEGain.FourthVref)),
			    new CyDisplayValue<CyVrefGainPair>("0.4375 Vdda to 0.5625 Vdda",
				    new CyVrefGainPair(CyEVrefSource.Vdda, CyEGain.EighthVref)),
		    };
            return singleEndedRanges;
		}

        public List<CyDisplayValue<CyVrefGainPair>> GetDifferentialRanges()
        {
            List<CyDisplayValue<CyVrefGainPair>> differentialRanges
                = new List<CyDisplayValue<CyVrefGainPair>>
            {
                new CyDisplayValue<CyVrefGainPair>("±2.4V",
                    new CyVrefGainPair(CyEVrefSource.Bandgap, CyEGain.DoubleVref)),
                new CyDisplayValue<CyVrefGainPair>("±1.2V",
                    new CyVrefGainPair(CyEVrefSource.Bandgap, CyEGain.OneVref)),
                new CyDisplayValue<CyVrefGainPair>("±0.6V",
                    new CyVrefGainPair(CyEVrefSource.Bandgap, CyEGain.HalfVref)),
                new CyDisplayValue<CyVrefGainPair>("±0.3V",
                    new CyVrefGainPair(CyEVrefSource.Bandgap, CyEGain.FourthVref)),
                new CyDisplayValue<CyVrefGainPair>("±0.15V",
                    new CyVrefGainPair(CyEVrefSource.Bandgap, CyEGain.EighthVref)),

                new CyDisplayValue<CyVrefGainPair>("±Vdda",
                    new CyVrefGainPair(CyEVrefSource.Vdda, CyEGain.DoubleVref)),
                new CyDisplayValue<CyVrefGainPair>("±Vdda/2",
                    new CyVrefGainPair(CyEVrefSource.Vdda, CyEGain.OneVref)),
                new CyDisplayValue<CyVrefGainPair>("±Vdda/4",
                    new CyVrefGainPair(CyEVrefSource.Vdda, CyEGain.HalfVref)),
                new CyDisplayValue<CyVrefGainPair>("±Vdda/8",
                    new CyVrefGainPair(CyEVrefSource.Vdda, CyEGain.FourthVref)),
                new CyDisplayValue<CyVrefGainPair>("±Vdda/16",
                    new CyVrefGainPair(CyEVrefSource.Vdda, CyEGain.EighthVref)),
            };
            return differentialRanges;
        }
	}

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

    public class CyRange
    {
        static public int VrefTap(CyEVrefSource vrefSource, CyEBandgapGain bandgapGain)
        {
            int tapNum
                = ((vrefSource == CyEVrefSource.Vdda) || (bandgapGain == CyEBandgapGain.Two))
                ? ADC_UAB_Parameters.MID_TAP : ADC_UAB_Parameters.HIGH_TAP;

            return tapNum;
        }
    }
}

