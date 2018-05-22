/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;

namespace cy_lfclk_v1_0
{
    public class CyCustomizer : ICyDWComponent_v1
    {
        #region ICyDWComponent_v1 members

        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyDWComponentAPIArgs_v1 args)
        {
            return args.Apis;
        }

        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDWComponentDRCArgs_v1 args)
        {
            return new CyDRCInfo_v1[0];
        }

        public CyCustErr IsSupported(ICyDWComponentSupportedArgs_v1 args)
        {
            return (args.DeviceQureyV1.IsPSoC3 || args.DeviceQureyV1.IsPSoC5) ? new CyCustErr("") : CyCustErr.OK;
        }

        public CyCustErr IsValid(ICyDWComponentValidArgs_v1 args)
        {
            IList<string> bootComps;
            if (args.CompNames.TryGetValue("cy_boot", out bootComps) && bootComps.Count == 1)
            {
                Version validVersion = new Version(5, 0);
                Version currentVersion = args.GetVersion(bootComps[0]);
                if (currentVersion < validVersion)
                {
                    return new CyCustErr(Resources.NotSupportedCyBoot);
                }
            }
            Debug.Assert(bootComps != null && bootComps.Count == 1);
            return CyCustErr.OK;
        }

        #endregion
    }
}
