/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Windows.Forms;
using System.Diagnostics;
using System.Xml.Serialization;
using System.IO;
using System;

namespace ScanComp_v1_10
{
    [CyCompDevCustomizer()]
    public partial class CyCustomizer : ICyParamEditHook_v1, ICyAPICustomize_v2, ICyShapeCustomize_v1, ICyExprEval_v2,
        ICyDRCProvider_v1
    {
        #region ICyParamEditHook_v1 members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit, termQuery);
            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();

            // Create tabs
            CyGeneralTab generalTab = new CyGeneralTab(parameters);
            CyChannelsTab channelsTab = new CyChannelsTab(parameters);

            CyParamExprDelegate dataChanged = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                generalTab.UpdateUI();
                channelsTab.UpdateUI();
                parameters.GlobalEditMode = true;
            };

            // Add tabs to the customizer
            editor.AddCustomPage(Resources.GeneralTabDisplayName, generalTab, dataChanged, generalTab.TabName);
            editor.AddCustomPage(Resources.ChanelsTabDisplayName, channelsTab, dataChanged, channelsTab.TabName);
            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");

            // Update tabs
            generalTab.UpdateUI();
            channelsTab.UpdateUI();
            parameters.GlobalEditMode = true;
            edit.NotifyWhenDesignUpdates(generalTab.UpdateClockData);

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

        #region ICyExprEval_v2 members
        public CyExprEvalFuncEx GetFunction(string exprFuncName)
        {
            switch (exprFuncName)
            {
                case "GetInterruptModeList":
                    return new CyExprEvalFuncEx(GetInterruptModeList);
                default:
                    return null;
            }
        }

        /// <summary>
        /// Method is intended to be run by local parameter. After performing method parameter will contain
        /// XML with a list of interrupt mode values for the selected number of channels.
        /// </summary>
        /// <param name="exprFuncName">The name of the function</param>
        /// <param name="args">Arguments passed into the method during its call from parameter expression</param>
        /// <param name="custArgs">Contains references (sometimes null) to various customizer interface objects</param>
        /// <param name="typeConverter">Used to convert individual arguments from the args array into normal C# types 
        /// (bool, int, string, etc)</param>
        /// <returns>Serialized list of interrupt mode values for current number of channels.</returns>
        private object GetInterruptModeList(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            string result = String.Empty;
            if (custArgs == null || custArgs.InstQuery == null)
                return result;
            try
            {
                XmlSerializer m_listSerializer = new XmlSerializer(typeof(List<string>));
                CyParameters parameters = new CyParameters(custArgs.InstQuery);
                List<string> intModeList = new List<string>();
                // Create a list of channels interrupt mode
                for (int i = 0; i < parameters.ChannelsTable.Count; i++)
                {
                    intModeList.Add(parameters.ChannelsTable[i].InterruptMode.ToString());
                }
                // Serialize the list and convert into string
                using (StringWriter sw = new StringWriter(System.Globalization.CultureInfo.InvariantCulture))
                {
                    m_listSerializer.Serialize(sw, intModeList);
                    result = sw.ToString();
                }
            }
            catch (System.Exception ex)
            {
                Debug.Fail(ex.ToString());
            }
            return result;
        }
        #endregion

        #region ICyDRCProvider_v1 members
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CyParameters parameters = new CyParameters(args.InstQueryV1);

            if (parameters.NegativeInput == CyENegativeInput.INTERN)
            {
                if (parameters.VdacVoltageMode == CyEVdacVoltageMode.FIXED)
                {
                    if ((parameters.VdacVoltageMv % parameters.GetVdacRangeCoeff()) != 0)
                    {
                        yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Warning,
                            String.Format(Resources.VdacVoltageNotMultiple, parameters.GetVdacRangeCoeff()));
                    }
                }
                else
                {
                    for (int i = 0; i < parameters.ChannelsTable.Count; i++)
                    {
                        if ((parameters.ChannelsTable[i].DacVoltage % parameters.GetVdacRangeCoeff()) != 0)
                        {
                            yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Warning,
                            String.Format(Resources.VDACVoltageTableNotMultiple, parameters.GetVdacRangeCoeff()));
                        }
                    }
                }
            }

            if (parameters.ClockSource == CyEClockSource.EXTERNAL)
            {
                string err = parameters.GetClockFrequencyError(CyClock.GetClockFrequencyHz(args.TermQueryV1, false));
                if (String.IsNullOrEmpty(err) == false)
                    yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Warning, err);
            }

            if (parameters.IsPSoC4 && parameters.NegativeInput == CyENegativeInput.INTERN)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, Resources.InternalVDACForPSoC4);
            }
        }
        #endregion
    }
}
