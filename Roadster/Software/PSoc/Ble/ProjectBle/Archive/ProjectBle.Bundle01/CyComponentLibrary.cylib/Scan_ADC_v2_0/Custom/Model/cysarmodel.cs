/*******************************************************************************
* Copyright 2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Linq;
using System.Windows.Forms;

namespace Scan_ADC_v2_0
{
    public class CySarRanges
    {
        public const int NUM_CHANNEL_MIN = 1;
        public const int NUM_CHANNEL_MAX = 16;

        public const int APERTURE_TIMER_COUNT = 4;
        public const int APERTURE_TIMER_MIN = 2;
        public const int APERTURE_TIMER_MAX = 1024;
        public const double APERTURE_MIN_ADC_CLOCKS = 3.5;
        public const double APERTURE_ADC_CLOCKS_NOT_SAMPLING = 0.5;
        public const double APERTURE_MIN_NS = 194;
        public const double APERTURE_FILTER_MIN_NS = 194;   // CDT 230992, KVCP
        public const double MIN_VREF = 1.0;                 // CDT 246998
        public const int MIN_ADC_CLOCK_DIV = 2;

        public const double SAR_SAMPLE_RATE_KSPS = 1000;
        public const int SAR_FREQ_MAX_NO_BYPASS_HZ = 1600000;
        public const int SAR_FREQ_MIN_HZ = 1000000;
        public const int SAR_MIN_ADC_CLOCKS_PER_CONVERSION = 18;

        public const int SAR_2000_KSPS_CLOCK_HZ = 36000000;
        public const int SAR_1500_KSPS_CLOCK_HZ = 27000000;
        public const int SAR_1000_KSPS_CLOCK_HZ = 18000000;
        public const int SAR_500_KSPS_CLOCK_HZ = 9000000;
        public const int SAR_300_KSPS_CLOCK_HZ = 5400000;
        public const int SAR_250_KSPS_CLOCK_HZ = 4500000;
        public const int SAR_200_KSPS_CLOCK_HZ = 3600000;
        public const int SAR_150_KSPS_CLOCK_HZ = 2700000;
        public const int SAR_100_KSPS_CLOCK_HZ = 1800000;

        public const long SAR_UNACHIEVABLE_RATE = 6000000;

        //PSoC6 specific ranges
        public const double P6_MIN_VREF = 0.85;     
        public const int P6_SAR_FREQ_MAX_NO_BYPASS_HZ = 1800000;        
        public const int P6_SAR_FREQ_MIN_HZ = 1700000;
        public const double P6_APERTURE_MIN_ADC_CLOCKS = 3;
        public const double P6_APERTURE_ADC_CLOCKS_NOT_SAMPLING = 1.0;

        public const int VREF_PWR_100 = 0;
        public const int VREF_PWR_80  = 1;
        public const int VREF_PWR_60  = 2;
        public const int VREF_PWR_50  = 3;
        public const int VREF_PWR_40  = 4;
        public const int VREF_PWR_30  = 5;
        public const int VREF_PWR_20  = 6;
        public const int VREF_PWR_10  = 7;

        public const int COMP_DLY_2p5 = 0;
        public const int COMP_DLY_4   = 1;
        public const int COMP_DLY_10  = 2;
        public const int COMP_DLY_12  = 3;

        public const int COMP_PWR_100 = 0;
        public const int COMP_PWR_80  = 1;
        public const int COMP_PWR_60  = 2;
        public const int COMP_PWR_50  = 3;
        public const int COMP_PWR_40  = 4;
        public const int COMP_PWR_30  = 5;
        public const int COMP_PWR_20  = 6;
        public const int COMP_PWR_10  = 7;
    }

    public class CySar
    {
        private bool hasAltRes = true;
        private bool hasExtVrefConnection = false;
        
        public CyEVrefSource VrefSource {get; set;}
        public bool VrefBypass { get; set; }
        public double SampleRate_ksps { get; set; }
        public int MinAdcClockDivider { get; set; }

        public CySar()
        {
            this.VrefSource = CyEVrefSource.VREFSOURCE_VBGR;
            this.VrefBypass = false;
            this.hasAltRes = true;
            this.SampleRate_ksps = CySarRanges.SAR_SAMPLE_RATE_KSPS;
            this.MinAdcClockDivider = CySarRanges.MIN_ADC_CLOCK_DIV;
        }

        public CySar(CyEVrefSource vrefSource, bool vrefBypass, double sampleRate_ksps, bool isExtVrefSourceConnected)
        {
            this.VrefSource = vrefSource;
            this.VrefBypass = vrefBypass;
            this.hasAltRes = true;
            this.hasExtVrefConnection = isExtVrefSourceConnected;
            this.SampleRate_ksps = sampleRate_ksps;
            this.MinAdcClockDivider = CySarRanges.MIN_ADC_CLOCK_DIV;
        }

        #region CySar properties

        public virtual bool HasAltResolution
        {
            get
            {
                return hasAltRes;
            }
            
        }

        public virtual bool HasExtVrefConnection
        {
            get
            {
                return hasExtVrefConnection;
            }
        }

        /// <summary>
        /// Returns the maximum frequency the SAR can run at.
        /// </summary>
        public virtual int UpperLimitAdcFrequency
        {
            get
            {
                return (Convert.ToInt32(this.SampleRate_ksps) * 1000 * CySarRanges.SAR_MIN_ADC_CLOCKS_PER_CONVERSION);
            }
        }

        /// <summary>
        /// Minimum SAR frequency in Hz.
        /// </summary>
        public virtual int MinSarFrequency
        {
            get
            {
                return CySarRanges.SAR_FREQ_MIN_HZ;
            }
        }

        /// <summary>
        /// Maximum SAR frequency in Hz.
        /// </summary>
        public virtual int MaxSarFrequency
        {
            get
            {
                switch (VrefSource)
                {
                    case CyEVrefSource.VREFSOURCE_DEVPIN:
                    case CyEVrefSource.VREFSOURCE_VDDA:
                        return this.UpperLimitAdcFrequency;
                    case CyEVrefSource.VREFSOURCE_EXTERNAL:
                    case CyEVrefSource.VREFSOURCE_PVREF:
                    case CyEVrefSource.VREFSOURCE_VBGR:
                    case CyEVrefSource.VREFSOURCE_HALFVDDA:
                    default:
                        return VrefBypass ? this.UpperLimitAdcFrequency : CySarRanges.SAR_FREQ_MAX_NO_BYPASS_HZ;


                }
            }
        }

        /// <summary>
        /// Minimum Vref voltage.
        /// </summary>
        public virtual double MinVrefVoltage
        {
            get
            {
                return CySarRanges.MIN_VREF;
            }
        }

        /// <summary>
        /// The minimum acquisition time in nanoseconds
        /// </summary>
        public virtual double MinAcqTime_ns
        {
            get
            {
                double adcClock_ns = (1 / Convert.ToDouble(this.UpperLimitAdcFrequency));
                return Math.Round((adcClock_ns * CySarRanges.APERTURE_MIN_ADC_CLOCKS) * 1000000000);
            }

        }

        /// <summary>
        /// Not all of the aperture clocks are used to sample the signal. 
        /// This is the number of clocks not used to sample the signal.
        /// </summary>
        public virtual double ApertureAdcClocksNotSampling
        {
            get
            {
                return CySarRanges.APERTURE_ADC_CLOCKS_NOT_SAMPLING;
            }
        }
        #endregion CySar properties

        #region CySar methods
        public virtual void SetVrefComboBox(ComboBox m_cmbVrefSource)
        {
            CyComboUtils.SetEnumDataSource<CyEVrefSource>(m_cmbVrefSource);
        }

        /// <summary>
        /// True if the Vref Voltage can be queried
        /// </summary>
        public virtual bool IsVrefQueriable()
        {
            return (this.VrefSource != CyEVrefSource.VREFSOURCE_EXTERNAL
                    && this.VrefSource != CyEVrefSource.VREFSOURCE_DEVPIN);
        }

        /// <summary>
        /// Set the VREF buffer settings for a given ADC clock rate
        /// </summary>
        public virtual int GetPwrCtrlVref(long adcClock_Hz)
        {
            return 0;
        }

        /// <summary>
        /// Set the Comparator power settings for a given ADC clock rate
        /// </summary>
        public virtual int GetCompPower(long adcClock_Hz)
        {
            return 0;
        }

        /// <summary>
        /// Set the Comparator delay settings for a given ADC clock rate
        /// </summary>
        public virtual int GetCompDelay(long adcClock_Hz)
        {
            return 0;
        }

        #endregion CySar methods      
    }

    public class CySar_P6 : CySar
    {
        private bool hasAltRes = false;
        private bool hasExtVrefConnection = false;

        public CySar_P6()
        {
            this.VrefSource = CyEVrefSource.VREFSOURCE_VBGR;
            this.VrefBypass = false;
            hasAltRes = false;
            
            this.SampleRate_ksps = CySarRanges.SAR_SAMPLE_RATE_KSPS;
        }

        public CySar_P6(CyEVrefSource vrefSource, bool vrefBypass, double sampleRate_ksps, bool isExtVrefSourceConnected)
        {
            this.VrefSource = vrefSource;
            this.VrefBypass = vrefBypass;
            this.hasAltRes = false;
            this.hasExtVrefConnection = isExtVrefSourceConnected;
            this.SampleRate_ksps = sampleRate_ksps;
        }

        #region CySar_P6 properties

        /// <summary>
        /// Returns true if the SAR can have alternate resolutions
        /// </summary>
        public override bool HasAltResolution
        {
            get
            {
                return hasAltRes;
            }            
        }

        public override bool HasExtVrefConnection
        {
            get
            {
                return hasExtVrefConnection;
            }
        }
        /// <summary>
        /// Minimum SAR frequency in Hz.
        /// </summary>
        public override int MinSarFrequency
        {
            get
            {
                return CySarRanges.P6_SAR_FREQ_MIN_HZ;
            }
        }

        /// <summary>
        /// Maximum SAR frequency in Hz.
        /// </summary>
        public override int MaxSarFrequency
        {
            get
            {
                switch (VrefSource)
                {
                    case CyEVrefSource.VREFSOURCE_DEVPIN:
                    case CyEVrefSource.VREFSOURCE_VDDA:
                        return this.UpperLimitAdcFrequency;
                    case CyEVrefSource.VREFSOURCE_EXTERNAL:
                    case CyEVrefSource.VREFSOURCE_PVREF:
                    case CyEVrefSource.VREFSOURCE_VBGR:
                    case CyEVrefSource.VREFSOURCE_HALFVDDA:
                    default:
                        return VrefBypass ? this.UpperLimitAdcFrequency : CySarRanges.P6_SAR_FREQ_MAX_NO_BYPASS_HZ;


                }
            }
        }

        /// <summary>
        /// Minimum Vref voltage.
        /// </summary>
        public override double MinVrefVoltage
        {
            get
            {
                return CySarRanges.P6_MIN_VREF;
            }
        }

        /// <summary>
        /// The minimum acquisition time in nanoseconds
        /// </summary>
        public override double MinAcqTime_ns
        {
            get
            {
                double adcClock_ns = (1 / Convert.ToDouble(this.UpperLimitAdcFrequency));
                return Math.Round((adcClock_ns * CySarRanges.P6_APERTURE_MIN_ADC_CLOCKS) * 1000000000);
            }

        }

        /// <summary>
        /// Not all of the aperture clocks are used to sample the signal. 
        /// This is the number of clocks not used to sample the signal.
        /// </summary>
        public override double ApertureAdcClocksNotSampling
        {
            get
            {
                return CySarRanges.P6_APERTURE_ADC_CLOCKS_NOT_SAMPLING;
            }
        }
        #endregion CySar_P6 properties

        #region CySar_P6 methods
        /// <summary>
        /// P6 has fewer selections than PSoC4B-S0. Sets the combobox accordingly
        /// </summary>
        public override void SetVrefComboBox(ComboBox m_cmbVrefSource)
        {
            var fullVrefList = CyComboUtils.GetEnumMenuItems<CyEVrefSource>();
            var noArouteList = fullVrefList
                .Where(m => m.Value != CyEVrefSource.VREFSOURCE_PVREF).ToList();
            noArouteList = noArouteList
                .Where(m => m.Value != CyEVrefSource.VREFSOURCE_EXTERNAL).ToList();

            //Remove the External device pin for parts without that connection
            if(!this.hasExtVrefConnection)
            {
                noArouteList = noArouteList
                    .Where(m => m.Value != CyEVrefSource.VREFSOURCE_DEVPIN).ToList();
            }
            m_cmbVrefSource.DisplayMember = "Display";
            m_cmbVrefSource.ValueMember = "Value";
            m_cmbVrefSource.DataSource = noArouteList;
        }

        /// <summary>
        /// Set the Comparator delay settings for a given ADC clock rate
        /// </summary>
        public override int GetCompDelay(long adcClock_Hz)
        {
            int delay = 0;


            if (adcClock_Hz > CySarRanges.SAR_2000_KSPS_CLOCK_HZ)
            {
                delay = CySarRanges.COMP_DLY_2p5;
            }
            else if (adcClock_Hz > CySarRanges.SAR_1500_KSPS_CLOCK_HZ)
            {
                delay = CySarRanges.COMP_DLY_4;
            }
            else if (adcClock_Hz > CySarRanges.SAR_1000_KSPS_CLOCK_HZ)
            {
                delay = CySarRanges.COMP_PWR_10;
            }
            else
            {
                delay = CySarRanges.COMP_DLY_12;
            }

            return delay;
        }

        /// <summary>
        /// Set the Comparator power settings for a given ADC clock rate
        /// </summary>
        public override int GetCompPower(long adcClock_Hz)
        {
            int power = 0;


            if (adcClock_Hz > CySarRanges.SAR_2000_KSPS_CLOCK_HZ)
            {
                power = CySarRanges.VREF_PWR_100;
            }
            else if (adcClock_Hz >= CySarRanges.SAR_1500_KSPS_CLOCK_HZ)
            {
                power = CySarRanges.VREF_PWR_80;
            }
            else if (adcClock_Hz >= CySarRanges.SAR_1000_KSPS_CLOCK_HZ)
            {
                power = CySarRanges.VREF_PWR_60;
            }
            else if (adcClock_Hz >= CySarRanges.SAR_500_KSPS_CLOCK_HZ)
            {
                power = CySarRanges.VREF_PWR_50;
            }
            else if (adcClock_Hz >= CySarRanges.SAR_250_KSPS_CLOCK_HZ)
            {
                power = CySarRanges.VREF_PWR_40;
            }
            else if (adcClock_Hz >= CySarRanges.SAR_100_KSPS_CLOCK_HZ)
            {
                power = CySarRanges.VREF_PWR_30;
            }
            else
            {
                power = CySarRanges.VREF_PWR_20;
            }

            return power;
        }

        /// <summary>
        /// Set the VREF buffer settings for a given ADC clock rate
        /// </summary>
        public override int GetPwrCtrlVref(long adcClock_Hz)
        {
            int power = 0;

            if(this.VrefBypass)
            {
                if(adcClock_Hz > CySarRanges.SAR_2000_KSPS_CLOCK_HZ)
                {
                    power = CySarRanges.VREF_PWR_100;
                }
                else if(adcClock_Hz >= CySarRanges.SAR_1500_KSPS_CLOCK_HZ)
                {
                    power = CySarRanges.VREF_PWR_80;
                }
                else if(adcClock_Hz >= CySarRanges.SAR_1000_KSPS_CLOCK_HZ)
                {
                    power = CySarRanges.VREF_PWR_60;
                }
                else if(adcClock_Hz >= CySarRanges.SAR_500_KSPS_CLOCK_HZ)
                {
                    power = CySarRanges.VREF_PWR_50;
                }
                else if(adcClock_Hz >= CySarRanges.SAR_250_KSPS_CLOCK_HZ)
                {
                    power = CySarRanges.VREF_PWR_40;
                }
                else if(adcClock_Hz >= CySarRanges.SAR_100_KSPS_CLOCK_HZ)
                {
                    power = CySarRanges.VREF_PWR_30;
                }
                else
                {
                    power = CySarRanges.VREF_PWR_20;
                }
            } 
            else
            {
                if(adcClock_Hz >= CySarRanges.SAR_300_KSPS_CLOCK_HZ)
                {
                    power = CySarRanges.VREF_PWR_60;
                }
                else if(adcClock_Hz >= CySarRanges.SAR_250_KSPS_CLOCK_HZ)
                {
                    power = CySarRanges.VREF_PWR_50;
                }
                else if(adcClock_Hz >= CySarRanges.SAR_200_KSPS_CLOCK_HZ)
                {
                    power = CySarRanges.VREF_PWR_40;
                }
                else if (adcClock_Hz >= CySarRanges.SAR_150_KSPS_CLOCK_HZ)
                {
                    power = CySarRanges.VREF_PWR_30;
                }
                else
                {
                    power = CySarRanges.VREF_PWR_20;
                }
            }      

            return power;
        }
        #endregion CySar_P6 methods
    }

    public class CySar_P4B : CySar
    {
        private bool hasAltRes = true;
        private bool hasExtVrefConnection = true;
        CySar_P4B()
        {
            this.VrefSource = CyEVrefSource.VREFSOURCE_VBGR;
            this.VrefBypass = false;
            this.hasAltRes = true;
            this.SampleRate_ksps = CySarRanges.SAR_SAMPLE_RATE_KSPS;
            this.MinAdcClockDivider = CySarRanges.MIN_ADC_CLOCK_DIV;
        }

        public CySar_P4B(CyEVrefSource vrefSource, bool vrefBypass, double sampleRate_ksps, bool isExtVrefSourceConnected)
        {
            this.VrefSource = vrefSource;
            this.VrefBypass = vrefBypass;
            this.hasAltRes = true;
            this.hasExtVrefConnection = isExtVrefSourceConnected;
            this.SampleRate_ksps = sampleRate_ksps;
            this.MinAdcClockDivider = CySarRanges.MIN_ADC_CLOCK_DIV;
        }

        public override bool HasExtVrefConnection
        {
            get
            {
                return hasExtVrefConnection;
            }
        }

        public override bool HasAltResolution
        {
            get 
            { 
                return this.hasAltRes;
            }
        }
    }
}
