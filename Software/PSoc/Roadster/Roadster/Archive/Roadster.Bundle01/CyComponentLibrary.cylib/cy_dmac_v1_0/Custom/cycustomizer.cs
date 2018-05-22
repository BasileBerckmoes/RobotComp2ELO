/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
using System;
using System.Collections.Generic;
using System.Windows.Forms;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using System.Diagnostics;

namespace cy_dmac_v1_0
{
    public class CyCustomizer: ICyDWComponent_v1
    {
        #region Class constants
        private const string DMA_IP = "m0s8cpussv2";
        private const string DMAC_PRESENT = "CPUMEMSS.DMAC_PRESENT";
        private const string CY_BOOT = "cy_boot";
        private const string DWC_NOT_VALID_MSG = "Only supported when cy_boot_v5.0 or newer is used.";
        #endregion

        #region ICyDWComponent_v1 Members
        public CyCustErr IsSupported(ICyDWComponentSupportedArgs_v1 args)
        {
            if (args.DeviceQureyV1.GetFeatureParameter(DMA_IP, DMAC_PRESENT) > 0)
                return CyCustErr.Ok;
            else
                return new CyCustErr(String.Empty);
        }
        
        public CyCustErr IsValid(ICyDWComponentValidArgs_v1 args)
        {
            IList<string> bootComps;
            if (args.CompNames.TryGetValue(CY_BOOT, out bootComps) &&
             bootComps.Count == 1)
            {
                Version validVersion = new Version(5, 0);
                Version bootVersion = args.GetVersion(bootComps[0]);
                if (bootVersion < validVersion)
                {
                    return new CyCustErr(DWC_NOT_VALID_MSG);
                }
            }
            return CyCustErr.Ok;
        }

        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDWComponentDRCArgs_v1 args)
        {
            return new CyDRCInfo_v1[0];
        }

        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyDWComponentAPIArgs_v1 args)
        {
            return args.Apis;
        }
        #endregion
    }
}
