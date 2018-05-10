/*******************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Windows.Forms;
using System.Diagnostics;
using MDIO_Interface_v1_20.Tabs;

namespace MDIO_Interface_v1_20
{
    public class CyCustomizer : ICyParamEditHook_v1, ICyAPICustomize_v1, ICyShapeCustomize_v1
    {
        public const string GENERAL_TAB_NAME = "General";
        public const string ADVANCED_TAB_NAME = "Advanced";

        #region ICyParamEditHook_v1 Members
        DialogResult ICyParamEditHook_v1.EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery,
            ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit);
            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            editor.UseBigEditor = true;
            parameters.m_editor = editor;
            CyBasicTab basicTab = new CyBasicTab(parameters);
            CyAdvancedTab advancedTab = new CyAdvancedTab(parameters);
            CyParamExprDelegate exprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                if (param.TabName == basicTab.TabName)
                {
                    basicTab.UpdateUI();
                }
                else if (param.TabName == advancedTab.TabName)
                {
                    advancedTab.UpdateUIFromExprView();
                }
                parameters.GlobalEditMode = true;
            };
            editor.AddCustomPage(Resources.GeneralTabDisplayName, basicTab, exprDelegate, basicTab.TabName);
            editor.AddCustomPage(Resources.AdvancedTabDisplayName, advancedTab, exprDelegate, advancedTab.TabName);
            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");
            basicTab.UpdateUI();
            parameters.GlobalEditMode = true;
            return editor.ShowDialog();
        }

        bool ICyParamEditHook_v1.EditParamsOnDrop
        {
            get { return false; }
        }

        CyCompDevParamEditorMode ICyParamEditHook_v1.GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }
        #endregion

        #region ICyAPICustomize_v1 Members
        const string REGISTER_PAGE_NAME = "registerPage";
        const string REGISTER_CONFIG_NAME = "registerConfig";
        bool m_isPSoC5;
        string m_instanceName;
        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery,
            IEnumerable<CyAPICustomizer> apis)
        {
            List<CyAPICustomizer> customizers = new List<CyAPICustomizer>(apis);
            Dictionary<string, string> paramDict = new Dictionary<string, string>();
            if (customizers.Count > 0) paramDict = customizers[0].MacroDictionary;
            m_isPSoC5 = query.DeviceQuery.IsPSoC5;
            CyParameters parameters = new CyParameters(query);
            m_instanceName = parameters.InstanceName;

            // Do not generate *_REG.c and *_REG.h files in basic mode
            if (parameters.OperationMode == CyEOperationModeType.BASIC)
            {
                for (int i = customizers.Count - 1; i >= 0; i--)
                {
                    if (customizers[i].OutputName.ToLower().EndsWith((m_instanceName + "_REG.c").ToLower()) ||
                        customizers[i].OutputName.ToLower().EndsWith((m_instanceName + "_REG.h").ToLower()))
                    {
                        customizers.RemoveAt(i);
                    }
                }
            }

            BitArray baDataWidth = new BitArray(CyRegSpaceConfig.MAX_REG_SPACE_NUM);
            BitArray baMemoryType = new BitArray(CyRegSpaceConfig.MAX_REG_SPACE_NUM);
            BitArray baConfigType = new BitArray(CyRegSpaceConfig.MAX_REG_SPACE_NUM);

            StringBuilder sbGenCode = new StringBuilder();
            StringBuilder sbRegTableCode = new StringBuilder();

            // Generate data width define
            // Generate memory type define
            for (int i = 0; i < parameters.m_regSpaceList.m_regSpaces.Count; i++)
            {
                CyRegSpace regSpace = parameters.m_regSpaceList.m_regSpaces[i];
                baDataWidth[i] = regSpace.DataWidth == CyEDataWidthType.BIT_16;
                baMemoryType[i] = regSpace.MemoryType == CyEMemoryType.SRAM;
                baConfigType[i] = regSpace.ConfigType == CyEMemoryType.SRAM;
            }

            paramDict.Add("DataWidth", string.Concat(CyParameters.ConvertDecToHex(
                                                                  ConvertByteArrayToByte(baDataWidth)), "u"));
            paramDict.Add("MemoryType", string.Concat(CyParameters.ConvertDecToHex(
                                                                  ConvertByteArrayToByte(baMemoryType)), "u"));
            paramDict.Add("ConfigType", string.Concat(CyParameters.ConvertDecToHex(
                                                                  ConvertByteArrayToByte(baConfigType)), "u"));

            // Generate defines with register space name
            // Generate defines with start address
            // Generate defines with end address
            for (int regSpaceIndex = 0; regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count; regSpaceIndex++)
            {
                CyRegSpace regSpace = parameters.m_regSpaceList.m_regSpaces[regSpaceIndex];
                sbGenCode.AppendLine(string.Format("    /* Register space {0} definition */", regSpaceIndex + 1));
                sbGenCode.AppendLine(string.Format("    #define {0}_{1}_IDX ({2}u)", m_instanceName, regSpace.Name,
                    regSpaceIndex + 1));
                sbGenCode.AppendLine(string.Format("    #define {0}_{1}_START ({2}u)", m_instanceName, regSpace.Name,
                    CyParameters.ConvertDecToHex(regSpace.StartAddress.Value)));
                sbGenCode.AppendLine(string.Format("    #define {0}_{1}_END ({2}u)", m_instanceName, regSpace.Name,
                    CyParameters.ConvertDecToHex(regSpace.EndAddress.Value)));
                sbGenCode.AppendLine(string.Format("    #define {0}_{1}_PTR {2}", m_instanceName, regSpace.Name,
                    String.Format("{0}_{1}_{2}", m_instanceName, REGISTER_PAGE_NAME, regSpaceIndex + 1)));
                sbGenCode.AppendLine(string.Format("    #define {0}_{1}_CONFIG_PTR {2}", m_instanceName, regSpace.Name,
                    String.Format("{0}_{1}_{2}", m_instanceName, REGISTER_CONFIG_NAME, regSpaceIndex + 1)));
                sbGenCode.AppendLine();
            }
            paramDict.Add("RegSpaceInfo", sbGenCode.ToString());

            // Generate register page size
            sbGenCode.Length = 0;
            for (int regSpaceIndex = 0; regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count; regSpaceIndex++)
            {
                CyRegSpace regSpace = parameters.m_regSpaceList.m_regSpaces[regSpaceIndex];
                sbGenCode.AppendLine(string.Format("#define {0} ({1}u)", GetRegisterPageSizeDefine(m_instanceName,
                    regSpaceIndex), regSpace.AddressConfig.Count));
            }
            paramDict.Add("RegPagesSize", sbGenCode.ToString());

            // Generate register page declarations
            sbGenCode.Length = 0;
            for (int regSpaceIndex = 0; regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count; regSpaceIndex++)
            {
                CyRegSpace regSpace = parameters.m_regSpaceList.m_regSpaces[regSpaceIndex];
                sbGenCode.AppendLine(GetRegisterPageDeclaration(regSpaceIndex, regSpace, true));
            }
            // Generate register configuration declarations
            for (int regSpaceIndex = 0; regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count; regSpaceIndex++)
            {
                CyRegSpace regSpace = parameters.m_regSpaceList.m_regSpaces[regSpaceIndex];
                sbGenCode.AppendLine(string.Format("/* Page {0} register configuration */", regSpaceIndex + 1));
                sbGenCode.AppendLine(string.Format("extern {0}{1}_REG_CONFIG_STRUCT {2}{1}_{3}_{4}[{5}];",
                    regSpace.ConfigType == CyEMemoryType.FLASH ? "const " : string.Empty,
                    m_instanceName,
                    regSpace.ConfigType == CyEMemoryType.FLASH ? "CYCODE " : string.Empty,
                    REGISTER_CONFIG_NAME,
                    regSpaceIndex + 1,
                    GetRegisterPageSizeDefine(m_instanceName, regSpaceIndex)));
            }
            paramDict.Add("RegisterDeclaration", sbGenCode.ToString());

            // Generate register page array
            sbRegTableCode.Length = 0;
            for (int regSpaceIndex = 0; regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count; regSpaceIndex++)
            {
                CyRegSpace regSpace = parameters.m_regSpaceList.m_regSpaces[regSpaceIndex];
                sbGenCode.Length = 0;
                // Check if all init values equal to zero
                bool allZeros = true;
                if (regSpace.MemoryType == CyEMemoryType.SRAM)
                {
                    for (int addressIndex = 0; addressIndex < regSpace.AddressConfig.Count; addressIndex++)
                    {
                        if (regSpace.AddressConfig[addressIndex].InitValue != 0)
                        {
                            allZeros = false;
                            break;
                        }
                    }
                }
                // All init values equal to 0. Initialization is not necessary, create declaration only
                if (allZeros && regSpace.MemoryType == CyEMemoryType.SRAM)
                {
                    if (regSpaceIndex > 0)
                    {
                        sbRegTableCode.AppendLine();
                    }
                    sbRegTableCode.AppendLine(GetRegisterPageDeclaration(regSpaceIndex, regSpace));
                }
                else // some of elements contain values different from 0. Array must be initialized
                {
                    int elementsPerLine = regSpace.DataWidth == CyEDataWidthType.BIT_8 ? 16 : 12;
                    for (int addrIndex = 0; addrIndex < regSpace.AddressConfig.Count; addrIndex++)
                    {
                        UInt16 initValue = regSpace.AddressConfig[addrIndex].InitValue.Value;
                        if (m_isPSoC5 && (regSpace.DataWidth == CyEDataWidthType.BIT_16))
                        {
                            initValue = SwapBytes(initValue);
                        }
                        if ((addrIndex % elementsPerLine) == 0)
                        {
                            sbGenCode.AppendLine();
                            sbGenCode.Append("    ");
                        }
                        string str = (regSpace.DataWidth == CyEDataWidthType.BIT_16) ?
                            CyParameters.ConvertDecToHex(initValue) : CyParameters.ConvertDecToHex((byte)initValue);
                        sbGenCode.Append(string.Concat(str,
                                                   (addrIndex < regSpace.AddressConfig.Count - 1) ? "u, " : "u"));
                    }
                    if (regSpaceIndex > 0)
                    {
                        sbRegTableCode.AppendLine();
                    }
                    sbRegTableCode.AppendLine(string.Format("/* Page {0} register data */", regSpaceIndex + 1));
                    sbRegTableCode.AppendLine(string.Format("{0}uint{1} {2}{3}_{4}_{5}[{6}] ={7}{{{8}{7}}};",
                        regSpace.MemoryType == CyEMemoryType.FLASH ? "const " : string.Empty,
                        regSpace.m_dataWidth == CyEDataWidthType.BIT_8 ? 8 : 16,
                        regSpace.MemoryType == CyEMemoryType.FLASH ? "CYCODE " : string.Empty,
                        m_instanceName,
                        REGISTER_PAGE_NAME,
                        regSpaceIndex + 1,
                        GetRegisterPageSizeDefine(m_instanceName, regSpaceIndex),
                        Environment.NewLine,
                        sbGenCode));
                }
            }
            paramDict.Add("RegisterTable", sbRegTableCode.ToString());

            // Registers configuration (all table values except init value)
            sbGenCode.Length = 0;
            for (int regSpaceIndex = 0; regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count; regSpaceIndex++)
            {
                // Register configuration header
                CyRegSpace regSpace = parameters.m_regSpaceList.m_regSpaces[regSpaceIndex];
                if (regSpaceIndex > 0)
                {
                    sbGenCode.AppendLine();
                }
                sbGenCode.AppendLine(string.Format("/* Page {0} register configuration */", regSpaceIndex + 1));
                sbGenCode.AppendLine(string.Format("{0}{1}_REG_CONFIG_STRUCT {2}{1}_{3}_{4}[{5}] =",
                    regSpace.ConfigType == CyEMemoryType.FLASH ? "const " : string.Empty,
                    m_instanceName,
                    regSpace.ConfigType == CyEMemoryType.FLASH ? "CYCODE " : string.Empty,
                    REGISTER_CONFIG_NAME,
                    regSpaceIndex + 1,
                    GetRegisterPageSizeDefine(m_instanceName, regSpaceIndex)));
                sbGenCode.Append("{");
                // Register configuration elements
                for (int addrConfigIdx = 0; addrConfigIdx < regSpace.AddressConfig.Count; addrConfigIdx++)
                {
                    if ((addrConfigIdx % 4) == 0)
                    {
                        sbGenCode.AppendLine();
                        sbGenCode.Append("    ");
                    }
                    sbGenCode.Append(string.Format("{{{0}u, {1}u, {2}u}}{3} ",
                        // Mask
                        (regSpace.MemoryType == CyEMemoryType.FLASH) ? "0x0000" : GetMask(regSpace, addrConfigIdx),
                        // Control values
                        (regSpace.MemoryType == CyEMemoryType.FLASH) ? "0x00" :
                                  CyParameters.ConvertDecToHex(GetCtlRegValue(regSpace.AddressConfig[addrConfigIdx],
                                                                              parameters.EnableAuxBits)),
                        // Reserved byte
                        0,
                        // Comma between array elements
                        (addrConfigIdx < regSpace.AddressConfig.Count - 1) ? "," : ""));
                }
                // Register configuration footer
                sbGenCode.AppendLine();
                sbGenCode.Append("};");
            }
            paramDict.Add("RegisterConfigurations", sbGenCode.ToString());

            // Info list of all register spaces
            sbGenCode.Length = 0;
            sbGenCode.AppendLine(string.Format("const uint16 * const CYCODE {0}_pageInfoPtr[{0}_PAGE_INFO_SIZE] =",
                                                                   m_instanceName));
            sbGenCode.AppendLine("{");
            for (int regSpaceIndex = 0; regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count; regSpaceIndex++)
            {
                sbGenCode.AppendLine(string.Format("    (const uint16 *) {0}_{1}_{2}, (const uint16 *) {0}_{3}_{2}{4}",
                    m_instanceName,
                    REGISTER_PAGE_NAME,
                    regSpaceIndex + 1,
                    REGISTER_CONFIG_NAME,
                    (regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count - 1) ? "," : ""));
            }
            //sbConfig.AppendLine();
            sbGenCode.Append("};");
            paramDict.Add("PageInfoList", sbGenCode.ToString());

            // Start addresses of register spaces array
            sbGenCode.Length = 0;
            sbGenCode.AppendLine("    /* Start addresses of register spaces */");
            sbGenCode.AppendLine(string.Format("    static uint16 {0}_pageStartAddr[{0}_NUMBER_OF_PAGES] =",
                m_instanceName));
            sbGenCode.AppendLine("    {");
            sbGenCode.Append("        ");
            for (int regSpaceIndex = 0; regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count; regSpaceIndex++)
            {
                if (regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count - 1)
                {
                    sbGenCode.Append(string.Concat(CyParameters.ConvertDecToHex(
                        parameters.m_regSpaceList.m_regSpaces[regSpaceIndex].StartAddress.Value), "u, "));
                }
                else
                {
                    sbGenCode.Append(string.Concat(CyParameters.ConvertDecToHex(
                        parameters.m_regSpaceList.m_regSpaces[regSpaceIndex].StartAddress.Value), "u"));
                }
            }
            sbGenCode.AppendLine();
            sbGenCode.Append("    };");
            paramDict.Add("StartAddresses", sbGenCode.ToString());

            // End addresses of register spaces array
            sbGenCode.Length = 0;
            sbGenCode.AppendLine("    /* End addresses of register spaces */");
            sbGenCode.AppendLine(string.Format("    static uint16 {0}_pageEndAddr[{0}_NUMBER_OF_PAGES] =",
                m_instanceName));
            sbGenCode.AppendLine("    {");
            sbGenCode.Append("        ");
            for (int regSpaceIndex = 0; regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count; regSpaceIndex++)
            {
                if (regSpaceIndex < parameters.m_regSpaceList.m_regSpaces.Count - 1)
                {
                    sbGenCode.Append(string.Concat(CyParameters.ConvertDecToHex(
                        parameters.m_regSpaceList.m_regSpaces[regSpaceIndex].EndAddress.Value), "u, "));
                }
                else
                {
                    sbGenCode.Append(string.Concat(CyParameters.ConvertDecToHex(
                        parameters.m_regSpaceList.m_regSpaces[regSpaceIndex].EndAddress.Value), "u"));
                }
            }
            sbGenCode.AppendLine();
            sbGenCode.Append("    };");
            paramDict.Add("EndAddresses", sbGenCode.ToString());

            for (int i = 0; i < customizers.Count; i++)
            {
                customizers[i].MacroDictionary = paramDict;
            }
            return customizers;
        }

        private string GetMask(CyRegSpace regSpace, int addrConfigIdx)
        {
            string result;
            if (regSpace.DataWidth == CyEDataWidthType.BIT_8)
            {
                UInt16 mergedBytes;
                if (regSpace.AddressConfig.Count > (addrConfigIdx + 1))
                {
                    mergedBytes = MergeBytes(regSpace.AddressConfig[addrConfigIdx].Mask.Value,
                        regSpace.AddressConfig[addrConfigIdx + 1].Mask.Value, true);
                }
                else
                {
                    mergedBytes = (UInt16)(regSpace.AddressConfig[addrConfigIdx].Mask.Value << 8);
                }
                result = CyParameters.ConvertDecToHex(mergedBytes);
            }
            else
            {
                result = CyParameters.ConvertDecToHex(regSpace.AddressConfig[addrConfigIdx].Mask.Value);
            }
            return result;
        }

        private string GetRegisterPageDeclaration(int regSpaceIndex, CyRegSpace regSpace)
        {
            return GetRegisterPageDeclaration(regSpaceIndex, regSpace, false);
        }
        private string GetRegisterPageDeclaration(int regSpaceIndex, CyRegSpace regSpace, bool addExtern)
        {
            string result = string.Format("/* Page {0} register data */", regSpaceIndex + 1);
            result = string.Concat(result, Environment.NewLine, string.Format("{0}{1}uint{2} {3}{4}_{5}_{6}[{7}];",
                addExtern ? "extern " : string.Empty,
                regSpace.MemoryType == CyEMemoryType.FLASH ? "const " : string.Empty,
                regSpace.m_dataWidth == CyEDataWidthType.BIT_8 ? 8 : 16,
                regSpace.MemoryType == CyEMemoryType.FLASH ? "CYCODE " : string.Empty,
                m_instanceName,
                REGISTER_PAGE_NAME,
                regSpaceIndex + 1,
                GetRegisterPageSizeDefine(m_instanceName, regSpaceIndex)));
            return result;
        }

        private UInt16 GetMergedMasks(CyRegSpace regSpace, int addrConfigIdx)
        {
            UInt16 mergedBytes;
            if (m_isPSoC5)
            {
                if (regSpace.AddressConfig.Count > (addrConfigIdx + 1))
                {
                    mergedBytes = MergeBytes(regSpace.AddressConfig[addrConfigIdx].Mask.Value,
                        regSpace.AddressConfig[addrConfigIdx + 1].Mask.Value, true);
                }
                else
                {
                    mergedBytes = (UInt16)(regSpace.AddressConfig[addrConfigIdx].Mask.Value << 8);
                }
            }
            else
            {
                if (regSpace.AddressConfig.Count > (addrConfigIdx + 1))
                {
                    mergedBytes = MergeBytes(regSpace.AddressConfig[addrConfigIdx].Mask.Value,
                        regSpace.AddressConfig[addrConfigIdx + 1].Mask.Value, false);
                }
                else
                {
                    mergedBytes = (UInt16)(regSpace.AddressConfig[addrConfigIdx].Mask.Value);
                }
            }
            return mergedBytes;
        }

        /// <summary>
        /// Gets byte value where 7-4 bits are Aux bits and 3-0 bits are ClearOnRead, WriteOnly, TriggerOnWrite and
        /// TriggerOnRead respectively
        /// </summary>
        /// <param name="regAddress">Register space configuration table</param>
        /// <param name="enableAuxBits">Indicates whether auxiliary bits are enabled</param>
        /// <returns>Byte value where 7-4 bits are 0 and 3-0 bits are ClearOnRead, WriteOnly, TriggerOnWrite and
        /// TriggerOnRead respectively</returns>
        private static byte GetCtlRegValue(CyRegAddress regAddress, bool enableAuxBits)
        {
            byte auxBits = enableAuxBits ? regAddress.AuxBits.Value : (byte)0;
            BitArray bitCollection = new BitArray(new bool[]
            {
                regAddress.TriggerOnRead,
                regAddress.TriggerOnWrite,
                regAddress.WriteOnly,
                regAddress.ClearOnRead,
                (auxBits & CyRegAddress.AUX_BIT_4_MASK) > 0,
                (auxBits & CyRegAddress.AUX_BIT_5_MASK) > 0,
                (auxBits & CyRegAddress.AUX_BIT_6_MASK) > 0,
                (auxBits & CyRegAddress.AUX_BIT_7_MASK) > 0,
            });

            return ConvertByteArrayToByte(bitCollection);
        }

        private static string GetRegisterPageSizeDefine(string instanceName, int regSpaceIndex)
        {
            return string.Format("{0}_REG_PAGE_{1}_SIZE", instanceName, regSpaceIndex + 1);
        }

        private static byte ConvertByteArrayToByte(BitArray inputArray)
        {
            Debug.Assert(inputArray.Count <= 8, "Array of bit values cannot contain more than 8 bits.");
            byte theByte = 0;
            for (int i = inputArray.Count - 1; i >= 0; i--)
            {
                if (inputArray[i]) theByte |= 0x01;
                if (i > 0) theByte <<= 1;
            }
            return theByte;
        }

        /// <summary>
        /// Swaps LSB and MSB of UInt16 value
        /// </summary>
        /// <param name="value">Value that has to be swaped</param>
        /// <returns>Swaped value</returns>
        public static UInt16 SwapBytes(UInt16 value)
        {
            return (UInt16)(((0xFF00 & value) >> 8) | ((0x00FF & value) << 8));
        }

        /// <summary>
        /// Merges less significant byte of the value1 with the less significant byte of the value2
        /// </summary>
        /// <param name="value1">Value 1 which less significant byte has to be merged</param>
        /// <param name="value2">Value 2 which less significant byte has to be merged</param>
        /// <param name="shiftLeft">If true than LSBs of the value1 and value2 will be merged in order v1+v2, 
        /// otherwise in order v2+v1.</param>
        /// <returns>Merged less significant bytes of the value1 and value2 in order that set the 
        /// shiftLeft argument</returns>
        public static UInt16 MergeBytes(UInt16 value1, UInt16 value2, bool shiftLeft)
        {
            return (shiftLeft) ? (UInt16)(((0x00FF & value1) << 8) | (0x00FF & value2)) :
                (UInt16)(((0x00FF & value1)) | (0x00FF & value2) << 8);
        }
        #endregion

        #region ICyShapeCustomize_v1 Members
        private const string EN_PAGE_BUS_NAME = "en_page";
        private const string PHY_ADDR_TERM_NAME = "phy_addr";
        private const string TERM_PATERN = "{0}[{1}:{2}]";
        private const int EN_PAGE_LOW_RANGE = 1;
        private const int PHY_ADDR_LOW_RANGE = 0;
        private const int PHY_ADDR_HIGH_RANGE_3BIT = 2;
        private const int PHY_ADDR_HIGH_RANGE_5BIT = 4;

        public CyCustErr CustomizeShapes(ICyInstQuery_v1 instQuery, ICySymbolShapeEdit_v1 shapeEdit,
            ICyTerminalEdit_v1 termEdit)
        {
            CyParameters parameters = new CyParameters();
            parameters.m_query = instQuery;
            CyCustErr err = termEdit.TerminalRename(termEdit.GetTermName(EN_PAGE_BUS_NAME), string.Format(
                TERM_PATERN, EN_PAGE_BUS_NAME, parameters.NumRegSpace, EN_PAGE_LOW_RANGE));
            if (err.IsNotOK) return err;

            int phyAddrHighRange = parameters.PhysicalAddressWidth == CyEPhysicalAddressWidth.BIT_3
                ? PHY_ADDR_HIGH_RANGE_3BIT
                : PHY_ADDR_HIGH_RANGE_5BIT;
            err = termEdit.TerminalRename(termEdit.GetTermName(PHY_ADDR_TERM_NAME), string.Format(
               TERM_PATERN, PHY_ADDR_TERM_NAME, phyAddrHighRange, PHY_ADDR_LOW_RANGE));
            if (err.IsNotOK) return err;

            return CyCustErr.OK;
        }
        #endregion
    }
}
