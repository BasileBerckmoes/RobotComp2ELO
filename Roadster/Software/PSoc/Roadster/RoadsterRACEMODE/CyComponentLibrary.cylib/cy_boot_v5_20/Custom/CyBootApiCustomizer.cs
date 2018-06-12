/*******************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace cy_boot_v5_20
{
    public class CyCustomizer : ICyDWComponent_v1
    {
        #region ICyDWComponent_v1 Members
        #region API Customizer File Constants and Variables

        // Startup code files
        const string STARTUP_8051_KEIL = "KeilStart.a51";
        const string STARTUP_CM0_GCC = "cm0gcc.ld";
        const string STARTUP_CM0_RVDS = "Cm0RealView.scat";
        const string STARTUP_CM0_IAR = "Cm0Iar.icf";
        const string STARTUP_CM3_GCC = "cm3gcc.ld";
        const string STARTUP_CM3_RVDS = "Cm3RealView.scat";
        const string STARTUP_CM3_IAR = "Cm3Iar.icf";

        // CMSIS files
        const string CMSIS_CORE_CM0_HFILE = "core_cm0.h";
        const string CMSIS_PSOC4_HFILE = "core_cm0_psoc4.h";
        const string CMSIS_CORE_CM3_HFILE = "core_cm3.h";
        const string CMSIS_CORE_CM3_CFILE = "core_cm3.c";
        const string CMSIS_PSOC5_HFILE = "core_cm3_psoc5.h";
        const string CMSIS_CORE_FUNC_HFILE = "core_cmFunc.h";
        const string CMSIS_CORE_INSTR_HFILE = "core_cmInstr.h";

        const string PROJ_TYPE = "CYDEV_PROJ_TYPE";
        const string PROJ_TYPE_STANDARD = "Standard";
        const string PROJ_TYPE_LOADER = "Bootloader";
        const string PROJ_TYPE_LOADER_MULTIAPP = "MultiAppBootloader";
        const string PROJ_TYPE_LOADABLE = "Loadable";
        const string PROJ_TYPE_LOADABLEANDBOOTLOADER = "LoadableAndBootloader";
        const string PROJ_APP_COUNT = "CYDEV_APPLICATION_IMAGES";
        const string FIRST_AVAILABLE_META_ROW = "FIRST_AVAILABLE_META_ROW";
        const string OTA_PROJ_FLAG = "CY_APP_FOR_STACK_AND_COPIER";
        const string IS_IMPORTING_CODE = "CYDEV_IS_IMPORTING_CODE";
        const string IS_EXPORTING_CODE = "CYDEV_IS_EXPORTING_CODE";

        const string GCC_CHECKSUM_EXCLUDE_SECTION_PARAM = "CY_GCC_CHECKSUM_EXCLUDE_SECTION";
        const string GCC_CHECKSUM_EXCLUDE_SECTION_BTLDBL_PARAM = "CY_GCC_CHECKSUM_EXCLUDE_SECTION_BTLDBL";

        const string GCC_CHECKSUM_EXCLUDE_SECTION_BTLDBL_APP_1_OF_2 =
            ".cy_checksum_exclude (appl2_start - CY_CHECKSUM_EXCLUDE_SIZE): { KEEP(*(.cy_checksum_exclude)) }";
        const string GCC_CHECKSUM_EXCLUDE_SECTION_BTLDBL_APP_1_OF_1 =
            ".cy_checksum_exclude ((LENGTH(rom) - CY_FLASH_ROW_SIZE * CY_APPL_MAX) - CY_CHECKSUM_EXCLUDE_SIZE): { KEEP(*(.cy_checksum_exclude)) }";
        const string GCC_CHECKSUM_EXCLUDE_SECTION_BTLDBL_APP_2_OF_2 = GCC_CHECKSUM_EXCLUDE_SECTION_BTLDBL_APP_1_OF_1;
        const string GCC_CHECKSUM_EXCLUDE_SECTION_BTLDBL_APP_IMPORT =
            ".cy_checksum_exclude ((LENGTH(rom) - CY_FLASH_ROW_SIZE * 2) - CY_CHECKSUM_EXCLUDE_SIZE): { KEEP(*(.cy_checksum_exclude)) }";
        const string GCC_CHECKSUM_EXCLUDE_SECTION_BTLDBL_APP_EXPORT =
            ".cy_checksum_exclude : { KEEP(*(.cy_checksum_exclude)) } >rom";

        const string USE_BUNDLED_CMSIS = "CYDEV_USE_BUNDLED_CMSIS";

        #endregion

        public CyCustErr IsSupported(ICyDWComponentSupportedArgs_v1 args)
        {
            return CyCustErr.OK;
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
            List<CyAPICustomizer> inputCustomizers = new List<CyAPICustomizer>(args.Apis);
            List<CyAPICustomizer> outputCustomizers = new List<CyAPICustomizer>();

            // Get a parameter dictionary.  Any one will do because they all come identical
            // (Yes I am assuming there will be at least one)
            Dictionary<string, string> paramDict = inputCustomizers[0].MacroDictionary;

            bool enableCmsis = "0" != (args.ApiFitterQueryV2.GetFitterAPIEntry(USE_BUNDLED_CMSIS) ?? "1").TrimEnd('u');

            // CMSIS_PSOC5_HFILE or CMSIS_PSOC4_HFILE must be included BEFORE CMSIS_CORE file,
            // to prevent build failures
            bool foundPsocCmsis = false;

            uint appCount; // Application images count
            uint firstAvailableMetaRow; // First available meta row
            string projType; // Project type
            bool isExportingCode, isImportingCode; // If any component is sharing the code
            // Temporary variables that are used to extract values from paramDict
            string appCountStr, firstAvailableMetaRowStr, isImportingCodeStr, isExportingCodeStr;

            List<CyAPICustomizer> cmsisCustomizers = new List<CyAPICustomizer>();

            paramDict.TryGetValue(PROJ_TYPE, out projType);
            paramDict.TryGetValue(PROJ_APP_COUNT, out appCountStr);
            paramDict.TryGetValue(FIRST_AVAILABLE_META_ROW, out firstAvailableMetaRowStr);
            paramDict.TryGetValue(IS_IMPORTING_CODE, out isImportingCodeStr);
            paramDict.TryGetValue(IS_EXPORTING_CODE, out isExportingCodeStr);
            uint.TryParse(appCountStr, out appCount);
            uint.TryParse(firstAvailableMetaRowStr, out firstAvailableMetaRow);
            isImportingCode = isImportingCodeStr == "1";
            isExportingCode = isExportingCodeStr == "1";

            // Now copy the customizers to the output list following the simple rules
            // If it is not a special file, copy it.  Otherwise the rules are based on PROJ_TYPE
            foreach (CyAPICustomizer api in inputCustomizers)
            {
                switch (api.OutputName)
                {
                    case CMSIS_CORE_FUNC_HFILE:
                    case CMSIS_CORE_INSTR_HFILE:
                    case CMSIS_CORE_CM0_HFILE:
                    case CMSIS_CORE_CM3_CFILE:
                    case CMSIS_CORE_CM3_HFILE:
                        if (!foundPsocCmsis)
                            cmsisCustomizers.Add(api);
                        else
                            outputCustomizers.Add(api);
                        break;

                    case CMSIS_PSOC4_HFILE:
                    case CMSIS_PSOC5_HFILE:
                        if (enableCmsis)
                        {
                            foundPsocCmsis = true;
                            outputCustomizers.Add(api);
                            foreach (CyAPICustomizer c in cmsisCustomizers)
                                outputCustomizers.Add(c);
                        }
                        break;

                    case STARTUP_8051_KEIL:
                    case STARTUP_CM0_GCC:
                    case STARTUP_CM0_RVDS:
                    case STARTUP_CM0_IAR:
                    case STARTUP_CM3_GCC:
                    case STARTUP_CM3_RVDS:
                    case STARTUP_CM3_IAR:
                        if ((projType == PROJ_TYPE_LOADABLE || projType == PROJ_TYPE_LOADABLEANDBOOTLOADER) && appCount > 1)
                        {
                            CyAPICustomizer newApi;

                            for (uint i = 1; i <= appCount; i++)
                            {
                                string newName = Path.GetFileNameWithoutExtension(api.OutputName);
                                newName += "_" + i;
                                newName += Path.GetExtension(api.OutputName);

                                string newContent = api.OriginalContent;
                                string appImageDefine = string.Format("APP_IMAGE_{0}_START", i);
                                newContent = newContent.Replace("PROJ_FIRST_FLS_BYTE", appImageDefine);
                                newContent = newContent.Replace("`$CYAPPL_NUM`", i.ToString());
                                newContent = newContent.Replace("`$CYAPPL_MAX`", appCount.ToString());

                                string gccChecksumExcludeSectionBtldblParamValue = (i == 1) ?
                                    GCC_CHECKSUM_EXCLUDE_SECTION_BTLDBL_APP_1_OF_2 :
                                    GCC_CHECKSUM_EXCLUDE_SECTION_BTLDBL_APP_2_OF_2;
                                newContent = newContent.Replace(string.Format("`${0}`",
                                    GCC_CHECKSUM_EXCLUDE_SECTION_BTLDBL_PARAM),
                                    gccChecksumExcludeSectionBtldblParamValue);

                                newApi = new CyAPICustomizer(
                                    api.OriginalName, newName, newContent, api.MacroDictionary, api.BuildType);
                                outputCustomizers.Add(newApi);
                            }
                        }
                        else
                        {
                            string newContent = api.OriginalContent;
                            newContent = newContent.Replace("`$CYAPPL_NUM`", "1");
                            newContent = newContent.Replace("`$CYAPPL_MAX`", "1");
                            api.OutputContent = newContent;
                            outputCustomizers.Add(api);
                        }
                        break;

                    default:
                        outputCustomizers.Add(api);
                        break;
                }
            }
            // Add the code here if any of the parameters need to be modified by the customizer
            // Make the changes to paramDict.  The completion code updates all of the customizer
            // to dictionaries with paramDict


            // Add define if the project is in the OTA structure
            bool isOtaStack = (appCount <= 1) && (projType == PROJ_TYPE_LOADABLEANDBOOTLOADER) && isExportingCode;
            bool isOtaApp = (appCount <= 1) && (projType == PROJ_TYPE_LOADABLE) && (firstAvailableMetaRow == 2) &&
                            isImportingCode;
            paramDict.Add(OTA_PROJ_FLAG, isOtaApp ? "1" : "0");

            // Add GCC checksum exclude section parameters
            switch (projType)
            {
                case PROJ_TYPE_LOADABLE:
                case PROJ_TYPE_LOADABLEANDBOOTLOADER:
                    if (isOtaStack)
                    {
                        paramDict.Add(GCC_CHECKSUM_EXCLUDE_SECTION_BTLDBL_PARAM,
                                      GCC_CHECKSUM_EXCLUDE_SECTION_BTLDBL_APP_EXPORT);
                    }
                    else if (isOtaApp)
                    {
                        paramDict.Add(GCC_CHECKSUM_EXCLUDE_SECTION_BTLDBL_PARAM,
                                      GCC_CHECKSUM_EXCLUDE_SECTION_BTLDBL_APP_IMPORT);
                    }
                    else
                    {
                        // The dual-application bootloadables are handled above
                        paramDict.Add(GCC_CHECKSUM_EXCLUDE_SECTION_BTLDBL_PARAM,
                                      GCC_CHECKSUM_EXCLUDE_SECTION_BTLDBL_APP_1_OF_1);
                    }

                    break;
                default:
                    paramDict.Add(GCC_CHECKSUM_EXCLUDE_SECTION_PARAM,
                                  ".cy_checksum_exclude : { KEEP(*(.cy_checksum_exclude)) } >rom");
                    break;
            }

            //Save result
            foreach (CyAPICustomizer api in outputCustomizers)
            {
                api.MacroDictionary = paramDict;
            }

            return outputCustomizers;
        }

        #endregion
    }
}
