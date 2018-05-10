/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace ScanComp_v1_10
{
    public partial class CyCustomizer
    {
        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyAPICustomizeArgs_v2 args,
            IEnumerable<CyAPICustomizer> apis)
        {
            List<CyAPICustomizer> customizers = new List<CyAPICustomizer>(apis);
            Dictionary<string, string> paramDict = new Dictionary<string, string>();

            if (customizers.Count > 0)
                paramDict = customizers[0].MacroDictionary;

            CyParameters parameters = new CyParameters(args.InstQuery, args.TermQuery);

            StringBuilder sb = new StringBuilder();
            sb.AppendFormat("uint8 {0}_DacVoltages[{0}_NUM_OF_CHANNELS] = {{", parameters.InstanceName);
            sb.AppendLine();
            sb.Append("    ");

            for (int i = parameters.ChannelsTable.Count - 1; i >= 0; i--)
            {
                sb.AppendFormat("{0}u, ",
                    CyParameters.ConvertDecToHex(parameters.GetDACByteValue(parameters.ChannelsTable[i].DacVoltage)));
            }
            sb.AppendLine();
            sb.AppendLine("};");

            paramDict.Add("DacVoltagesArray", sb.ToString());

            // Replace macro dictionaries with paramDict
            for (int i = 0; i < customizers.Count; i++)
                customizers[i].MacroDictionary = paramDict;

            return customizers;
        }
    }
}
