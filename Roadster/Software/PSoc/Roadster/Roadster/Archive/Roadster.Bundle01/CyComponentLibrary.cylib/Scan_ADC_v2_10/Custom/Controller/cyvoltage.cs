using System;
using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace Scan_ADC_v2_10
{
    public static class CyVoltage
    {
        /// <summary>
        /// Queries Creator for available Design Wide Resource Voltage Values.
        /// Only used for voltages that can be queried.
        /// </summary>
        /// <param name="vrefSource">CyEVrefSource </param>
        /// <param name="m_params">CyParameters </param>
        /// <returns>double value of given reference</returns>
        public static double GetDesignVrefValue(CyParameters m_params, CyEVrefSource vrefSource)
        {
            double vrefAmt = 0.0;

            try
            {
                switch (vrefSource)
                {
                    case CyEVrefSource.VREFSOURCE_VDDA:
                        vrefAmt = m_params.InstQuery.VoltageQuery.VDDA;
                        break;
                    case CyEVrefSource.VREFSOURCE_HALFVDDA:
                        vrefAmt = m_params.InstQuery.VoltageQuery.VDDA / 2;
                        break;
                    case CyEVrefSource.VREFSOURCE_VBGR:
                        if(m_params.SarType == CyESarType.SAR_M0S8PASS4B)
                        {
                            vrefAmt = m_params.InstQuery.VoltageQuery.BandgapReference;
                        }
                        else
                        {
                            vrefAmt = m_params.InstQuery.VoltageQuery.SystemReference;
                        }
                        
                        break;
                    case CyEVrefSource.VREFSOURCE_PVREF:
                        vrefAmt = m_params.InstQuery.VoltageQuery.SystemReference;
                        break;
                    default:
                        break;
                }
            }
            catch { vrefAmt = 0.0; }
            return vrefAmt;
        }
    }
}