/******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using System.Diagnostics;

namespace ADC_DelSig_v3_20
{
    [CyCompDevCustomizer]
    public partial class CyCustomizer : ICyParamEditHook_v1, ICyExprEval_v2, ICyDRCProvider_v1
    {
        #region ICyParamEditHook_v1 members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit, termQuery);

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            parameters.m_editor = editor;
            // Create tab pages
            CyCommonTab commonTab = new CyCommonTab(parameters);
            CyConfigurationTab[] configTabList = new CyConfigurationTab[CyParamRanges.NUM_MAX_CONFIG];

            CyParamExprDelegate paramChanged =
            delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                try
                {
                    if (param.TabName == commonTab.TabName)
                    {
                        commonTab.UpdateUI();
                    }
                    else
                    {
                        for (int i = 0; i < CyParamRanges.NUM_MAX_CONFIG; i++)
                        {
                            if (param.TabName == configTabList[i].TabName)
                            {
                                configTabList[i].UpdateUI();
                            }
                        }
                    }
                } 
                catch
                {
                    Debug.Assert(false);
                }
                parameters.GlobalEditMode = true;
            };

            for (byte i = 1; i <= CyParamRanges.NUM_MAX_CONFIG; i++)
            {
                CyConfigurationTab configTab = new CyConfigurationTab(parameters, i);
                configTabList[i-1] = configTab;
                editor.AddCustomPage(configTab.TabDisplayName, configTab, paramChanged, configTab.TabName);
            }
            editor.AddCustomPage(Resource.CommonTabDisplayName, commonTab, paramChanged, commonTab.TabName);
            editor.AddDefaultPage(Resource.BuiltInTabDisplayName, "Built-in");

            commonTab.UpdateUI();
            foreach (CyConfigurationTab configTab in parameters.m_configTabs)
            {
                configTab.UpdateUI();
            }
            parameters.UpdateTabVisibility();
            
            parameters.GlobalEditMode = true;

            edit.NotifyWhenDesignUpdates(parameters.UpdateDesign);
            editor.UseBigEditor = true;

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
                case "AdcClockFrequency":
                    return new CyExprEvalFuncEx(AdcClockFrequency);

                case "GetVDDA":
                    return new CyExprEvalFuncEx(GetVDDA);

                default:
                    return null;
            }
        }

        /// <summary>
        /// Calculate the ADC clock frequency as a expression evaluator method.
        /// </summary>
        /// <param name="exprFuncName">Name of the function.</param>
        /// <param name="args">arguments to the function</param>
        /// <param name="typeConverter">Converts types to strings</param>
        /// <returns></returns>
        object AdcClockFrequency(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (args.Length != 3)  
            {
                Debug.Assert(false);
                return CyParamRanges.MAX_16_20_CLOCK_FREQ;
            }
            else
            {
                uint resolution = typeConverter.GetAsUInt(args[0]);
                uint sampleRate = typeConverter.GetAsUInt(args[1]);
                uint conversionMode = typeConverter.GetAsUInt(args[2]);

                // Call the actual frequency with the given parameters
                uint frequency = SetClock(resolution, sampleRate, (CyEConversionMode)conversionMode);
                return frequency;
            }
        }

        object GetVDDA(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (custArgs.InstQuery == null)
            {
                return CyParamRanges.DEFAULT_VDDA_VALUE;    
            }
            CyParameters prms = new CyParameters(custArgs.InstQuery);
            return prms.VDDA;
        }
        #endregion

        #region ICyDRCProvider_v1 Members
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CyParameters parameters = new CyParameters(args.InstQueryV1, args.TermQueryV1);

            List<CyCustErr> errorList = new List<CyCustErr>();
            List<CyCustErr> warningList = new List<CyCustErr>();

            for (byte i = 1; i <= parameters.NumConfigurations; i++)
            {
                warningList.Add(parameters.VerifyExternalClock(i));
                errorList.Add(parameters.VerifySampleRate(i));
                warningList.Add(parameters.VerifyMasterClockFrequency(i));
                errorList.Add(parameters.VerifyVrefValue(i));
                warningList.Add(parameters.VerifyBufferGain(i));
            }

            for (int i = 0; i < errorList.Count; i++)
            {
                if (errorList[i] != CyCustErr.OK)
                    yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, errorList[i].Message);
            }
            for (int i = 0; i < warningList.Count; i++)
            {
                if (warningList[i] != CyCustErr.OK)
                    yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Warning, warningList[i].Message);
            }
        }
        #endregion
    }
}
