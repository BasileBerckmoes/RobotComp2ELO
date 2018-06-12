/*******************************************************************************
* Copyright 2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Collections.Generic;
using System.Linq;

namespace Em_EEPROM_v2_0
{
    public partial class CyCustomizer : ICyAPICustomize_v2
    {
        readonly static string[] PSOC6_EXCLUDE_FILE_LIST = { "cy_em_eeprom.c", "cy_em_eeprom.h" };

        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyAPICustomizeArgs_v2 args, IEnumerable<CyAPICustomizer> apis)
        {
            List<CyAPICustomizer> inputCustomizers = new List<CyAPICustomizer>(apis);
            List<CyAPICustomizer> outputCustomizers = new List<CyAPICustomizer>();

            // Exclude files from PSOC6_EXCLUDE_FILE_LIST for PSoC 6
            foreach (CyAPICustomizer api in inputCustomizers)
            {
                if ((PSOC6_EXCLUDE_FILE_LIST.Any(x => api.OutputName.Contains(x)) == false) || 
                    (args.InstQuery.DeviceQuery.IsPSoC6 == false))
                {
                    outputCustomizers.Add(api);
                }
            }

            return outputCustomizers;
        }
    }
}
