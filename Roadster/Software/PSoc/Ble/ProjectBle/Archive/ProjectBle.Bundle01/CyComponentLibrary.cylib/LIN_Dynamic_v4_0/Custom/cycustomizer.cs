/*******************************************************************************
* Copyright 2015-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
using System;
using System.Collections.Generic;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using System.Diagnostics;

namespace LIN_Dynamic_v4_0
{
    public class CyCustomizer : ICyDWComponent_v1
    {
        #region Class Constants
        private readonly Version firstMultiInstVersion = new Version(3, 20);

        // Bundle data names
        private const string BDNAME_C_FILE = "LIN_DWC_C";                       // DWC component .c file
        private const string BDNAME_H_FILE = "LIN_DWC_H";                       // DWC component .h file
        private const string BDNAME_IFC_NUM = "ifcNumber";                      // interface number   
        private const string BDNAME_MULT_INST_SUPPORT = "multipleInstSupport";  // interface number   

        // Bundle ID
        private const string BUNDLE_ID_GENERAL = "LIN";
        private const string BUNDLE_ID_IFC1 = "LIN_IFC1";

        // Replacement string
        private const string SECOND_INST_NAME = "`$secondInstName`";

        private const string INSTANCE_1_NAME = "INSTANCE_1_NAME";
        private const string INSTANCE_2_NAME = "INSTANCE_2_NAME";
        private const string IS_MULTI_INSTANCE = "IsMultiInstance";

        // In multi-instance mode, interface with number 1 is required
        private const short IFC_NUM_1 = 1;
        #endregion


        #region ICyDWComponent_v1 Members
        public CyCustErr IsSupported(ICyDWComponentSupportedArgs_v1 args)
        {
            return (args.DeviceQureyV1.IsPSoC3 || args.DeviceQureyV1.IsPSoC5 ||
                args.DeviceQureyV1.GetFeatureParameter("m0s8scb", "UART") > 0)
                ? CyCustErr.OK : new CyCustErr(resource.DWC_DEVICE_ERROR);
        }

        public CyCustErr IsValid(ICyDWComponentValidArgs_v1 args)
        {
            IList<string> LinComps;
            if (args.CompNames.TryGetValue("LIN", out LinComps))
            {
                // check if multiple instance support component is present on the schematic
                for (int i = 0; i < LinComps.Count; i++)
                {
                    if (args.GetVersion(LinComps[i]) >= firstMultiInstVersion)
                    {
                        return CyCustErr.Ok;
                    }
                }
            }
            return new CyCustErr(resource.DWC_SUPPORT_ERROR);
        }

        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDWComponentDRCArgs_v1 args)
        {
            IList<CyPropertyBundle> ListBundle = args.GetPropertyBundlesFor(BUNDLE_ID_GENERAL);
            IList<string> linNames = args.GetInstNamesFor("LIN");

            string compName = typeof(CyCustomizer).Namespace;
            string compNameWithoutMinorVersion = compName.Substring(0, compName.LastIndexOf("_"));
            string minorVersion = compName.Substring(compName.LastIndexOf("_") + 1);
            string majorVersion = compNameWithoutMinorVersion.Substring(compNameWithoutMinorVersion.LastIndexOf("v") + 1);
            Version curentDWCVersion = new Version(Convert.ToInt32(majorVersion), Convert.ToInt32(minorVersion));

            bool isEqualVersion = true;

            Debug.Assert(linNames.Count > 0, "Should have been caught by ICyDWComponent_v1.IsValid");

            for (int i = 0; i < linNames.Count - 1; i++)
            {
                if (args.GetVersion(args.GetCompNameWithVersion(linNames[i])) !=
                    args.GetVersion(args.GetCompNameWithVersion(linNames[i + 1])))
                {
                    isEqualVersion = false;
                    break;
                }
            }

            if (isEqualVersion)
            {
                // if version of LIN instance is higher than version of DWC component
                if (args.GetVersion(args.GetCompNameWithVersion(linNames[0])) > curentDWCVersion)
                {
                    yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, resource.DWC_VERSION_ERROR);
                }
                else if (ListBundle.Count == 1) // if only one instance with valid version is present on schematic
                {
                    if (ListBundle[0].GetProperty<bool>(BDNAME_MULT_INST_SUPPORT)) // if Multiple instance support is checked 
                    {
                        yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                            string.Format(resource.MULTIPLE_SUPPORT_IS_CHECKED_ERROR, ListBundle[0].InstName));
                    }
                }
                else // if two instances with valid version are present on schematic
                {
                    for (int i = 0; i < ListBundle.Count; i++)
                    {
                        if (!ListBundle[i].GetProperty<bool>(BDNAME_MULT_INST_SUPPORT)) // if Multiple instance support is not checked
                        {
                            yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                                string.Format(resource.MULTIPLE_SUPPORT_IS_NOT_CHECKED_ERROR, ListBundle[i].InstName));
                        }
                    }

                    bool foundIfcNumber1 = false;
                    for (int i = 0; i < ListBundle.Count; i++)
                    {
                        ushort ifcNumber = ListBundle[i].GetProperty<ushort>(BDNAME_IFC_NUM);
                        if (ifcNumber == IFC_NUM_1)
                        {
                            foundIfcNumber1 = true;
                        }
                        for (int j = i + 1; j < ListBundle.Count; j++)
                        {
                            if (ifcNumber == ListBundle[j].GetProperty<ushort>(BDNAME_IFC_NUM))
                            {
                                // Found two LIN instances with the same interface number
                                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, resource.DIFERENT_IFC_ERROR);
                                // Avoid multiple DRCs thrown for the same issue
                                yield break;
                            }
                        }
                    }

                    if (foundIfcNumber1 == false)
                    {
                        yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, resource.IFC1_NOT_FOUND);
                    }
                }
            }
            else
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, resource.DIFERENT_VERSION_ERROR);
            }
        }

        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyDWComponentAPIArgs_v1 args)
        {
            List<CyAPICustomizer> customizers = new List<CyAPICustomizer>(args.Apis);
            Dictionary<string, string> paramDict = new Dictionary<string, string>();
            IList<CyPropertyBundle> listBundleIFC1 = args.GetPropertyBundlesFor(BUNDLE_ID_IFC1);
            IList<string> instNames = args.GetInstNamesFor("LIN");

            string isMultiInstance = "0";

            if (customizers.Count > 0)
            {
                paramDict = customizers[0].MacroDictionary;
            }

            Debug.Assert(listBundleIFC1.Count == 1, "Should have been caught by ICyDWComponent_v1.GetDRCs");

            // determine the second LIN instance name
            string secondInstName = "NOT_DEFINED";
            if (instNames.Count == 2)
            {
                isMultiInstance = "1";
                for (int i = 0; i < instNames.Count; i++)
                {
                    if (instNames[i] != listBundleIFC1[0].InstName)
                        secondInstName = instNames[i];
                }
            }

            // read input string
            string strH = listBundleIFC1[0].GetProperty<string>(BDNAME_H_FILE);
            string strC = listBundleIFC1[0].GetProperty<string>(BDNAME_C_FILE);

            // replace replacement string on the name of second instance
            if (strH.Contains(SECOND_INST_NAME))
                strH = strH.Replace(SECOND_INST_NAME, secondInstName);
            if (strC.Contains(SECOND_INST_NAME))
                strC = strC.Replace(SECOND_INST_NAME, secondInstName);

            paramDict.Add(IS_MULTI_INSTANCE, isMultiInstance);
            paramDict.Add(INSTANCE_1_NAME, listBundleIFC1[0].InstName);
            paramDict.Add(INSTANCE_2_NAME, secondInstName);

            // write in API output string
            paramDict.Add(BDNAME_H_FILE, strH);
            paramDict.Add(BDNAME_C_FILE, strC);

            for (int i = 0; i < customizers.Count; i++)
            {
                customizers[i].MacroDictionary = paramDict;
                yield return customizers[i];
            }
        }
        #endregion
    }
}
