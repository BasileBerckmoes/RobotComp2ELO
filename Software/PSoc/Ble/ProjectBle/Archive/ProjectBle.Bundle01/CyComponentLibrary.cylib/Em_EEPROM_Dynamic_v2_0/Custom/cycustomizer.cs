/*******************************************************************************
* Copyright 2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

// The namespace is required to have the same name as the component for a customizer.
namespace Em_EEPROM_Dynamic_v2_0
{
    public class CyCustomizer : ICyDWComponent_v1
    {
        #region ICyDWComponent_v1 Members
        public CyCustErr IsSupported(ICyDWComponentSupportedArgs_v1 args)
        {
            return (args.DeviceQureyV1.IsPSoC3 || args.DeviceQureyV1.IsPSoC4 || args.DeviceQureyV1.IsPSoC5)
                ? CyCustErr.OK : new CyCustErr(resource.DWC_DEVICE_ERROR);
        }

        public CyCustErr IsValid(ICyDWComponentValidArgs_v1 args)
        {
            return CyCustErr.OK;
        }

        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDWComponentDRCArgs_v1 args)
        {
            return new List<CyDRCInfo_v1>();
        }

        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyDWComponentAPIArgs_v1 args)
        {
            List<CyAPICustomizer> customizers = new List<CyAPICustomizer>(args.Apis);
            Dictionary<string, string> paramDict = new Dictionary<string, string>();
          
            if (customizers.Count > 0)
            {
                paramDict = customizers[0].MacroDictionary;
            }

            for (int i = 0; i < customizers.Count; i++)
            {
                customizers[i].MacroDictionary = paramDict;
                yield return customizers[i];
            }
        }
        #endregion
    }
}