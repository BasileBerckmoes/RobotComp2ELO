/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Diagnostics;

namespace DVDAC_v2_10
{
    [CyCompDevCustomizer()]
    public class CyCustomizer : ICyParamEditHook_v1, ICyAPICustomize_v1, ICyDRCProvider_v1
    {
        #region ICyParamEditHook_v1 Members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit, termQuery);

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();

            // Create tab page
            CyConfigureTab configureTab = new CyConfigureTab(parameters);

            CyParamExprDelegate dataChanged = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.m_globalEditMode = false;
                configureTab.UpdateUI();
                parameters.m_globalEditMode = true;
            };

            // Add tabs to the customizer 
            editor.AddCustomPage(Resources.ConfigureTabDisplayName, configureTab, dataChanged, configureTab.TabName);
            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");

            configureTab.UpdateUI();

            parameters.m_globalEditMode = true;
            edit.NotifyWhenDesignUpdates(configureTab.UpdateDesign);

            return editor.ShowDialog();
        }

        public bool EditParamsOnDrop
        {
            get { return false; }
        }

        public CyCompDevParamEditorMode GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }
        #endregion

        #region ICyAPICustomize_v1 Members
        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery, 
                                                          IEnumerable<CyAPICustomizer> apis)
        {
            Dictionary<string, string> paramDict = null;
            foreach (CyAPICustomizer api in apis)
            {
                // Get parameter dictionary
                paramDict = api.MacroDictionary;
            }
            CyParameters parameters = new CyParameters(query, termQuery);
            string instName = query.GetCommittedParam("INSTANCE_NAME").Value;

            byte[] dArray = GenDitheredValues(parameters.VDACValue, (byte)parameters.Resolution);
            string dArrayParam = Generate1DArray(dArray, 8, instName, "ditheredValues", false);
            paramDict.Add("ditheredValues", dArrayParam);
            // Assign dictionary back to API customizers
            foreach (CyAPICustomizer api in apis)
            {
                api.MacroDictionary = paramDict;
            }
            return apis;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="value">DVDAC converted value</param>
        /// <param name="resolution">DVDAC resolution</param>
        /// <returns></returns>
        private byte[] GenDitheredValues(UInt16 value, byte resolution)
        {
            byte shiftLen = (byte)(resolution - 8);
            byte ditherSize = (byte)(1 << shiftLen);
            byte lsbMask = (byte)(ditherSize - 1);
            byte[] dArray = new byte[ditherSize];

            byte msb = (byte)(value >> shiftLen);
            byte lsb = (byte)(value & lsbMask);  // Mask off the two LSBs 

            // If DAC is at max value force limit
            if (msb == 0xFF)     
            {
                for (int i = 0; i < ditherSize; i++)
                {
                    dArray[i] = 0xFF;
                }
            }
            else
            {
                // The algorithm fills an array with msb values and then with (msb+1)
                for (int i = 0; i < ditherSize; i++ )
                {
                    if (i < (ditherSize - lsb))
                    {
                        dArray[i] = msb;
                    }
                    else
                    {
                        dArray[i] = (byte)(msb + 1);
                    }
                }
            }
            return dArray;
        }

        /// <summary>
        /// Converts the byte array to string hex representation in C
        /// </summary>
        /// <param name="array">Array of byte values</param>
        /// <param name="dim">Size of integer (8, 16, 32)</param>
        /// <param name="instName">Instance name</param>
        /// <param name="arrName">Name of generated array</param>
        /// <param name="eachNewline">If each value is generated in the new line</param>
        /// <returns></returns>
        private string Generate1DArray(byte[] array, int dim, string instName, string arrName, bool eachNewline)
        {
            string arrType = String.Format("uint{0}", dim);
            string[] arrayStr = new string[array.Length];
            string hexFormat = "X" + (dim / 4).ToString();
            for (int i = 0; i < arrayStr.Length; i++)
            {
                arrayStr[i] = String.Format("0x{0}u", array[i].ToString(hexFormat));
            }
            string retValue = Generate1DArray(arrayStr, arrType, instName, arrName, eachNewline);
            return retValue;
        }

        /// <summary>
        /// Generates a string with array declaration that will be passed to C file.
        /// </summary>
        /// <param name="array"></param>
        /// <param name="arrType">C type of array</param>
        /// <param name="instName">Instance name</param>
        /// <param name="arrName">Name of generated array</param>
        /// <param name="eachNewline">If each value is generated in the new line</param>
        /// <returns></returns>
        private string Generate1DArray(string[] array, string arrType, string instName, string arrName,
                                      bool eachNewline)
        {
            const int MAX_LINE_LEN = 120;
            const int ONE_ELEM_MAXLEN = 8;
            int lastNewLineIndex = 0;

            StringBuilder builder = new StringBuilder();
            int count = array.Length;
            builder.AppendFormat("static {0} {1}_{2}[{3}u] = {{", arrType, instName, arrName, count);
            int shift = builder.ToString().Length;
            for (int i = 0; i < count; i++)
            {
                builder.Append(array[i]);
                if (i < count - 1)
                {
                    builder.Append(", ");
                    // If each element is generated in the new line or string is too long, start a new line.
                    if (eachNewline || builder.Length - lastNewLineIndex >= MAX_LINE_LEN - ONE_ELEM_MAXLEN)
                    {
                        builder.AppendLine();
                        lastNewLineIndex = builder.Length - 1;
                        builder.Append("".PadLeft(shift));
                    }
                }
                else
                {
                    builder.AppendLine("};");
                }
            }
            return builder.ToString();
        }

        #endregion

        #region ICyDRCProvider_v1 Members
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CyParameters parameters = new CyParameters(args.InstQueryV1, args.TermQueryV1);

            CyCustErr externalClockErr = parameters.VerifyExternalClock();
            CyCustErr busClockErr = parameters.VerifyBusClock();

            if (externalClockErr != CyCustErr.OK)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, externalClockErr.Message);

            if (busClockErr != CyCustErr.OK)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Warning, busClockErr.Message);
        }
        #endregion
    }
}
