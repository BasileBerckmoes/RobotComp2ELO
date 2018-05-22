/*******************************************************************************
* Copyright 2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.IO;
using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace SMIF_PDL_v1_10
{
    [CyCompDevCustomizer]
    public class CyCustomizer : ICyAPICustomize_v2, ICyContextMenuItemProvider_v1
    {
        #region const
        private const string HEADER_FILE = "cy_smif_memconfig.h";
        private const string C_FILE = "cy_smif_memconfig.c";
        private const string CY_MEM_FILE = "cy_smif.cysmif";
        private const string SHIELD = "\"{0}\"";
        private const string CY_MEM_FILE_PATH = "${CyPrjDirPath}\\" + CY_MEM_FILE;
        private const string TOOL_PATH = @"${CyPdlPath}\tools\win\smif_config\";

        private const string FILE_NOT_EXIST = "#error File {0} does not exist.";
        private const string FILE_EMPTY = "#error File {0} is empty.";
        #endregion

        #region ICyAPICustomize_v2 members
        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyAPICustomizeArgs_v2 args,
                                                          IEnumerable<CyAPICustomizer> apis)
        {
            // Return all standard APIs
            foreach (CyAPICustomizer api in apis)
            {
                yield return api;
            }
            bool enabled = false;
            args.InstQuery.GetCommittedParam("cymemGen").TryGetValueAs<bool>(out enabled);
            if (enabled)
            {
                string tempPath = Path.Combine(Path.GetTempPath(), "{" + Guid.NewGuid() + "}");
                while (Directory.Exists(tempPath))
                {
                    tempPath = Path.Combine(Path.GetTempPath(), "{" + Guid.NewGuid() + "}");
                }
                Directory.CreateDirectory(tempPath);

                CyCustErr err = args.Run.ProcessStartWithNoWindow(
                    TOOL_PATH + "cysmifcodegen.exe",
                    @" --generate " + String.Format(SHIELD, CY_MEM_FILE_PATH) +
                    @" --output " + tempPath, 5 * 1000);
                if (err.IsNotOK)
                {
                    yield return InitAPICustomizer(HEADER_FILE, "#error " + err.Message, CyCustBuildTypeEnum.NONE);
                }
                else
                {
                    string contentHFilePath = Path.Combine(tempPath, HEADER_FILE);
                    string contentCFilePath = Path.Combine(tempPath, C_FILE);
                    if (!File.Exists(contentHFilePath))
                    {
                        yield return InitAPICustomizer(HEADER_FILE, string.Format(FILE_NOT_EXIST, contentHFilePath), CyCustBuildTypeEnum.NONE);
                    }
                    else if (!File.Exists(contentCFilePath))
                    {
                        string hContent = File.ReadAllText(contentHFilePath);
                        if (!hContent.StartsWith("#error "))
                        {
                            yield return InitAPICustomizer(HEADER_FILE, string.Format(FILE_NOT_EXIST, contentCFilePath), CyCustBuildTypeEnum.NONE);
                        }
                        else
                        {
                            yield return ParseAndGenerateFiles(contentHFilePath, HEADER_FILE, CyCustBuildTypeEnum.NONE);
                        }
                    }
                    else
                    {
                        yield return ParseAndGenerateFiles(contentHFilePath, HEADER_FILE, CyCustBuildTypeEnum.NONE);
                        yield return ParseAndGenerateFiles(contentCFilePath, C_FILE, CyCustBuildTypeEnum.C_FILE);
                    }
                }
                if (Directory.Exists(tempPath))
                {
                    Directory.Delete(tempPath, true);
                }
            }
        }
        #endregion
        #region private methods for ICyAPICustomize_v2
        private CyAPICustomizer InitAPICustomizer(string fileName, string content, CyCustBuildTypeEnum type)
        {
            CyAPICustomizer api = new CyAPICustomizer(
                    fileName,
                    fileName,
                    content,
                    new Dictionary<string, string>(),
                    type,
                    new List<string>() { CY_MEM_FILE_PATH });
            return api;
        }

        private CyAPICustomizer ParseAndGenerateFiles(string filePath, string fileName, CyCustBuildTypeEnum type)
        {
            string content = File.ReadAllText(filePath);
            if (String.IsNullOrEmpty(content))
            {
                content = string.Format(FILE_EMPTY, filePath);
            }
            return InitAPICustomizer(fileName, content, type);
        }
        #endregion

        #region ICyContextMenuItemProvider_v1
        public IEnumerable<CyContextMenuItem_v1> GetContextMenuItems(ICyContextMenuItemArgs_v1 args)
        {
            bool enabled = false;
            args.InstQueryV1.GetCommittedParam("cymemGen").TryGetValueAs<bool>(out enabled);
            yield return new CySmifConfigToolMenuItem(enabled);
        }

        class CySmifConfigToolMenuItem : CyContextMenuItem_v1
        {
            public CySmifConfigToolMenuItem(bool enabled)
                : base("SMIF Configuration Tool", null, enabled)
            {
            }

            public override CyCustErr OnClicked(ICyContextMenuItemArgs_v1 args)
            {
                return args.Run.ProcessStart(TOOL_PATH + "cysmifconfigtool.exe", @"-input " + String.Format(SHIELD, CY_MEM_FILE_PATH));
            }
        }
        #endregion
    }
}
