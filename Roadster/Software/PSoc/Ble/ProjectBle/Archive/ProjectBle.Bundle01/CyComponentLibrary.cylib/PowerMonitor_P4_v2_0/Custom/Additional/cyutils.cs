using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using CyDesigner.Extensions.Gde;

namespace PowerMonitor_P4_v2_0.Additional
{
    class cyutils
    {
        /// <summary>
        /// Return the range of the ADC. Limited to Vdda for external Vref.
        /// </summary>
        /// <param name="inst">Instance query object</param>
        /// <returns>String of the ADC range in volts.</returns>
        public static string GetAdcRangeText(ICyInstQuery_v1 inst, CyParameters m_params)
        {
            decimal range = 0;

            if (inst != null)
            {
                range = GetVrefValue(inst, m_params) * 2;
                if (m_params.VrefSelect == CyEVrefSelect.Vref_External)
                {
                    //Limit Range to Vdda
                    decimal vrefMax = Convert.ToDecimal(m_params.ChipVdda);
                    if (range > vrefMax) range = vrefMax;
                }
            }
            return range.ToString("#.000");
        }

        /// <summary>
        /// Return the range of the ADC. Limited to Vdda for external Vref.
        /// </summary>
        /// <param name="inst">Instance query object</param>
        /// <returns>Int32 millivolt value of the ADC range.</returns>
        public static Int32 GetAdcRange_mV(ICyInstQuery_v1 inst, CyParameters m_params)
        {
            decimal range = 0;

            if (inst != null)
            {
                range = GetVrefValue(inst, m_params) * 2;
                if (m_params.VrefSelect == CyEVrefSelect.Vref_External)
                {
                    //Limit Range to Vdda
                    decimal vrefMax = Convert.ToDecimal(m_params.ChipVdda);
                    if (range > vrefMax) range = vrefMax;
                }
            }
            return Convert.ToInt32(range * 1000);
        }

        /// <summary>
        /// Return the value of Vref, querying the device unless an external
        /// Vref is used. 
        /// </summary>
        /// <param name="inst">Instance query object</param>
        /// <returns>decimal value in volts of Vref.</returns>
        public static decimal GetVrefValue(ICyInstQuery_v1 inst, CyParameters m_params)
        {
            decimal vref = 0;

            if(inst != null)
                { 
                if(m_params.VrefSelect == CyEVrefSelect.Vref_External)
                {
                    //Limit Vref to 1.0V to Vdda
                    decimal vrefMax = Convert.ToDecimal(m_params.ChipVdda);
                    vref = m_params.VrefValue;
                    if (vref < CyParamRanges.ADC_VREF_MIN_V) vref =
                        CyParamRanges.ADC_VREF_MIN_V;
                    if (vref > vrefMax) vref = vrefMax;
                }
                else
                {
                    if(IsPSoC4AS2(inst))
                    {
                        vref = 1.200m;
                    }
                    else
                    {
                        vref = 1.024m;
                    }
                }
            }
            return vref;
        }
        /// <summary>
        /// Return true if the project uses PSoC4A-S2. 
        /// This is the same logic used in the ADC_SAR_SEQ_P4. Note that this will need to be updated
        /// if any other PSoC4A parts use SRSS-Lite with the 1.2V Bandgap.
        /// </summary>
        /// <param name="inst">Instance query object</param>
        /// <returns>boolean true if PSoC4A-S2.</returns>
        public static bool IsPSoC4AS2(ICyInstQuery_v1 inst)
        {
            return inst.DeviceQuery.IsPSoC4
                       && inst.DeviceQuery.DeviceFamilyAvailable
                       && inst.DeviceQuery.ArchFamilyMember == CyParamNames.PSOC4AS2_ARCH_FAMILY;
        }

        /// <summary>
        /// Return true if the project uses PSoC41 family. 
        /// This is the same logic used in the ADC_SAR_SEQ_P4. Note that this will need to be updated
        /// if any other PSoC4A parts that for some reason limit the clock.
        /// </summary>
        /// <param name="inst">Instance query object</param>
        /// <returns>boolean true if PSoC41*.</returns>
        public static bool IsCY8C41(ICyInstQuery_v1 inst)
        {
            return inst.DeviceQuery.PartNumberAvailable 
                && inst.DeviceQuery.PartNumber.StartsWith(CyParamNames.PART_NUMBER_CY8C41);
        }

        /// <summary>
        /// Converts VrefSelect to VrefDisplay. ADC_SAR_SEQ_P4 has four selection options
        /// for choosing the Bandgap as Vref. This component only displays two and sets the
        /// correct selection based on the chip type. 
        /// </summary>
        /// <param name="inst">CyEVrefSelect</param>
        /// <returns>CyEVrefDisplay</returns>
        public static CyEVrefDisplay VrefSelectToDisplay(CyEVrefSelect select)
        {
            CyEVrefDisplay display;

            if((select == CyEVrefSelect.Vref_Internal) || (select == CyEVrefSelect.Vref_1024mV))
            {
                display = CyEVrefDisplay.Vref_Internal;
            }
            else if((select == CyEVrefSelect.Vref_InternalBypass) || (select == CyEVrefSelect.Vref_1024mVBypass))
            {
                display = CyEVrefDisplay.Vref_InternalBypass;
            }
            else
            {
                display = CyEVrefDisplay.Vref_External;
            }
            return display;
        }

        /// <summary>
        /// Converts VrefDisplay to VrefSelect. ADC_SAR_SEQ_P4 has four selection options
        /// for choosing the Bandgap as Vref. This component only displays two and sets the
        /// correct selection based on the chip type. 
        /// </summary>
        /// <param name="inst">CyEVrefDisplay, ICyInstQuery_v1</param>
        /// <returns>CyEVrefSelect</returns>
        public static CyEVrefSelect VrefDisplayToSelect(CyEVrefDisplay display, ICyInstQuery_v1 inst)
        {
            CyEVrefSelect select;

            if(display == CyEVrefDisplay.Vref_Internal)
            {
                if(IsPSoC4AS2(inst))
                {
                    select = CyEVrefSelect.Vref_Internal;
                }
                else
                {
                    select = CyEVrefSelect.Vref_1024mV;
                }
            }
            else if(display == CyEVrefDisplay.Vref_InternalBypass)
            {
                if (IsPSoC4AS2(inst))
                {
                    select = CyEVrefSelect.Vref_InternalBypass;
                } 
                else
                {
                    select = CyEVrefSelect.Vref_1024mVBypass;
                }
            }
            else
            {
                select = CyEVrefSelect.Vref_External;
            }
            return select;
        }
    }
}
