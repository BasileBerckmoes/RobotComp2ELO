/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;

namespace cy_dmac_v1_10
{
    public class CyCustomizer: ICyDWComponent_v1
    {
        #region Class constants
        private const string PARAMNAME_TRIGGER_CONTROL_MASK = "triggerControlMask";
        private const string PARAMNAME_DEFAULT_INTERRUPT_CALLBACKS = "DefaultInterruptCallbacks";

        // PSoC 4AL devices have 3 trigger groups: 
        // GROUP0 - CH0..CH7 (mask 0xC0020000U), 
        // GROUP1 - CH8..CH16  (mask 0xC0020100U), 
        // GROUP2 - CH17..CH26 (mask 0xC0020200U), CH27..CH32 (mask 0xC0020208U).
        private const string P4AL_TRIGGER_CONTROL_MASK = "0xC0020000U, 0xC0020100U, 0xC0020200U, 0xC0020208U";
        // In other case TR_GROUP is always 0 and channel number directly applies to TR_SEL field. 
        private const string NOTP4AL_TRIGGER_CONTROL_MASK = "0xC0020000U";


        private const string PSOC4AL_ARCHMEMBER_NAME = "PSoC4_2";
        private const string CPUSSV2_NAME = "m0s8cpussv2";
        private const string CPUSSV3_NAME = "m0s8cpussv3";
        private const string DMAC_PRESENT = "CPUMEMSS.DMAC_PRESENT";
        private const string DMAC_CH_NR = "DMAC.CH_NR";
        private const string CY_BOOT = "cy_boot";
        private const string DWC_NOT_VALID_MSG = "Only supported when cy_boot_v5.0 or newer is used.";
        #endregion

        #region ICyDWComponent_v1 Members
        public CyCustErr IsSupported(ICyDWComponentSupportedArgs_v1 args)
        {
            if (args.DeviceQureyV1.GetFeatureParameter(GetCpuName(args.DeviceQureyV1), DMAC_PRESENT) > 0)
                return CyCustErr.Ok;
            else
                return new CyCustErr(String.Empty); // No message. In this case component is invisible in CUT.
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
            List<CyAPICustomizer> customizers = new List<CyAPICustomizer>(args.Apis);
            Dictionary<string, string> paramDict = new Dictionary<string, string>();

            // Get dict from main file. 
            if (customizers.Count > 0)
                paramDict = customizers[0].MacroDictionary;

            // Generate trigger control mask
            if (args.DeviceQueryV1.ArchFamilyMember == PSOC4AL_ARCHMEMBER_NAME)
                paramDict.Add(PARAMNAME_TRIGGER_CONTROL_MASK, P4AL_TRIGGER_CONTROL_MASK);
            else
                paramDict.Add(PARAMNAME_TRIGGER_CONTROL_MASK, NOTP4AL_TRIGGER_CONTROL_MASK);

            // Generate CyDmaInterruptCallback array content
            StringBuilder sbIntCallback = new StringBuilder();
            int numChannels = args.DeviceQueryV1.GetFeatureParameter(GetCpuName(args.DeviceQueryV1), DMAC_CH_NR);
            for (int i = 0; i < numChannels; i += 2)
            {
                sbIntCallback.AppendLine("    &CyDmaDefaultInterruptCallback, &CyDmaDefaultInterruptCallback,");
            }
            paramDict.Add(PARAMNAME_DEFAULT_INTERRUPT_CALLBACKS, sbIntCallback.ToString().TrimEnd(',', '\r', '\n'));

            // Save result
            for (int i = 0; i < customizers.Count; i++)
            {
                customizers[i].MacroDictionary = paramDict;
            }

            return customizers;
        }
        #endregion

        #region Private Methods
        private string GetCpuName(ICyDeviceQuery_v1 deviceQuery)
        {
            if (deviceQuery.GetFeatureCount(CPUSSV2_NAME) > 0)
                return CPUSSV2_NAME;
            else if (deviceQuery.GetFeatureCount(CPUSSV3_NAME) > 0)
                return CPUSSV3_NAME;
            else
                return string.Empty;
        }
        #endregion Private Methods
    }
}
