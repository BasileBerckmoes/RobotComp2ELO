/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Windows.Forms;
using System.Diagnostics;

namespace ADC_SAR_v3_0
{
    [CyCompDevCustomizer()]
    public class CyCustomizer : ICyParamEditHook_v1, ICyDRCProvider_v1, ICyInstValidateHook_v1, ICyAPICustomize_v1
    {
        public const string CONFIGURE_TAB_NAME = "Configure";

        #region ICyParamEditHook_v1 Members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit, termQuery);
            CyConfigureTab configureTab = new CyConfigureTab(parameters);
            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();

            CyParamExprDelegate ExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.LoadParameters();
            };

            editor.AddCustomPage(Resources.ConfigureTabCaption, configureTab, ExprDelegate, CONFIGURE_TAB_NAME);
            editor.AddDefaultPage(Resources.BuiltInTabCaption, "Built-in");

            edit.NotifyWhenDesignUpdates(new CyDesignUpdated_v1(parameters.UpdateClock));

            parameters.LoadParameters();
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

        #region ICyDRCProvider_v1 Members
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CyParameters parameters = new CyParameters(args.InstQueryV1, args.TermQueryV1);
            CyCustErr err;

            // These verifications depend on silicon and cannot be calculated when silicon is unknown
            if (parameters.IsArchMemberAvailable)
            {
                err = VerifyClock(args.InstQueryV1.DesignQuery, args.TermQueryV1, parameters);
                if (err.IsOk == false)
                    yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err.Message);
                else
                {
                    err = VerifySourceClock(args.TermQueryV1, parameters.AdcClockSource);
                    if (err.IsOk == false)
                        yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err.Message);
                }
            }

            err = VerifyVoltage(args.InstQueryV1, parameters.RefVoltage, parameters.AdcReference,
                parameters.AdcInputRange);
            if (err.IsOk == false)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err.Message);

            err = VerifyReference(parameters);
            if (err.IsOk == false)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err.Message);

            err = VerifyVDACExternalRef(parameters);
            if (err.IsOk == false)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err.Message);
        }

        CyCustErr VerifySourceClock(ICyTerminalQuery_v1 termQuery, CyEAdcClockSrcType clockSource)
        {
            List<CyClockData> clkdata = (clockSource == CyEAdcClockSrcType.External)
                ? termQuery.GetClockData(CyClockReader.EXTERNAL_CLK, 0)
                : termQuery.GetClockData(CyClockReader.INTERNAL_CLK_OR_GATE, "term1", 0);

            CyClockData sarClk = clkdata.Count > 0 ? clkdata[0] : null;

            if (sarClk.IsFrequencyKnown == false) return CyCustErr.OK; // there is no clock connected

            CyClockData sarClkSource = termQuery.GetSourceClockData(sarClk);
            CyClockData sarClkRootSource = termQuery.GetSourceClockData(sarClkSource);

            uint div = sarClk.Divider;
            CyClockData src = sarClkSource;

            while (src.Divider > 0 && sarClkRootSource != null)  // a src.div of 0 will stop us at the source without a divider
            {                                                    // should be fine for an IMO with a source of XTAL since the rule
                div *= src.Divider;                              // check still works...  null check in case the clocks are in error state
                src = sarClkRootSource;
            }

            double freqMHz = CyClockReader.GetClockFrequencyMHz(src);

            if (freqMHz > CyParamRange.UNDIVIDED_CLOCK_SOURCE_MAX_MHZ && div == 1) // NOTE: IMO has discrete frequencies, 12 and 24 bound this check
                return new CyCustErr(Resources.DRCSourceClockFreq);                // PLL min is 24MHz, which is greater than max SAR clock rate

            return CyCustErr.OK;
        }

        CyCustErr VerifyClock(ICyDesignQuery_v1 designQuery, ICyTerminalQuery_v1 termQuery, CyParameters parameters)
        {
            double clockFrequencyHz;
            string clockName = String.Empty;
            string clockID = String.Empty;
            string message = String.Empty;

            if (parameters.AdcClockSource == CyEAdcClockSrcType.Internal)
            {
                clockName = parameters.InstanceName + CyClockReader.INTERNAL_CLK;
                clockID = CyClockReader.GetClockID(designQuery, clockName);
                message = Resources.DRCInternalClockFreq;
                clockFrequencyHz = CyClockReader.GetInternalClockInHz(designQuery, parameters.InstanceName);
            }
            else
            {
                List<string> clockIDsList = termQuery.GetClockIds(CyClockReader.EXTERNAL_CLK, 0);
                if (clockIDsList.Count > 0)
                    clockID = clockIDsList[0];
                message = Resources.DRCExternalClockFreq;
                clockFrequencyHz = CyClockReader.GetExternalClockInHz(termQuery);
            }

            if (clockFrequencyHz > 0)
            {
                if (clockFrequencyHz < CyParamRange.MIN_FREQ_HZ || clockFrequencyHz > parameters.MaxClockFrequencyHz)
                {
                    return new CyCustErr(String.Format(message,
                        CyParamRange.MIN_FREQ_MHZ, parameters.MaxClockFrequencyMHz));
                }
                else
                {
                    double pulseWidth = GetPulseWidth(designQuery, clockFrequencyHz, clockID);
                    return (pulseWidth < CyParamRange.MIN_PULSE_WIDTH)
                        ? new CyCustErr(String.Format(Resources.DRCMinimumPulseWidth, CyParamRange.MIN_PULSE_WIDTH))
                        : CyCustErr.OK;
                }
            }
            return CyCustErr.OK;
        }

        private double GetPulseWidth(ICyDesignQuery_v1 designQuery, double clockFrequencyHz, string clockID)
        {
            double pulseWidth = -1;
            uint clockDivider = 0;
            try
            {
                if (String.IsNullOrEmpty(clockID) == false)
                    clockDivider = designQuery.GetClockDivider(clockID);
                else
                    throw new Exception("Invalid clock ID.");

                pulseWidth = (clockDivider == 1)
                    ? (1 / clockFrequencyHz) / 2
                    : (1 / clockFrequencyHz) * Math.Floor((double)clockDivider / 2) / clockDivider;
            }
            catch (Exception ex)
            {
                Debug.Fail(ex.Message);
            }

            return pulseWidth * 1000000000;
        }

        CyCustErr VerifyVoltage(ICyInstQuery_v1 instQuery, double refVoltage, CyEAdcRefType reference,
            CyEAdcInputRangeType inputRange)
        {
            double vdda = 0;

            try
            {
                vdda = Convert.ToDouble(Math.Round(instQuery.VoltageQuery.VDDA, 4));
            }
            catch
            {
                vdda = 0;
            }
            if (vdda > 0)
            {
                double maxVoltage;
                string message;
                // External voltage reference should be limited to Vdda/2 for "Vssa to Vdda(Single)" 
                // and "0.0 +/- Vdda/2(Differential)" input ranges

                if (reference == CyEAdcRefType.Ext_Ref && (inputRange == CyEAdcInputRangeType.Vssa_to_Vdda ||
                    inputRange == CyEAdcInputRangeType.Vneg_Vdda_2_Diff))
                {
                    maxVoltage = vdda / 2;
                    message = Resources.VoltageReferenceVddaDiv2;
                }
                else
                {
                    maxVoltage = vdda;
                    message = Resources.VoltageReference;
                }

                if (refVoltage < CyParamRange.REF_VOLTAGE_MIN || refVoltage > maxVoltage)
                {
                    return new CyCustErr(message, CyParamRange.REF_VOLTAGE_MIN, maxVoltage);
                }
            }
            return CyCustErr.OK;
        }

        CyCustErr VerifyReference(CyParameters parameters)
        {
            uint maxSampleRate = parameters.GetMaxSampleRateForInternalVref();
            return (parameters.AdcReference == CyEAdcRefType.Int_Ref_Not_Bypassed &&
                    parameters.AdcClockSource == CyEAdcClockSrcType.Internal &&
                    parameters.AdcSampleRate > parameters.GetMaxSampleRateForInternalVref())
                        ? new CyCustErr(String.Format(parameters.GetInvalidConvRateIntVrefMessage(), maxSampleRate))
                        : CyCustErr.OK;
        }

        CyCustErr VerifyVDACExternalRef(CyParameters parameters)
        {
            if (parameters.AdcReference == CyEAdcRefType.Ext_Ref &&
                (parameters.AdcInputRange == CyEAdcInputRangeType.Vneg_VDAC_Diff ||
               parameters.AdcInputRange == CyEAdcInputRangeType.Vssa_to_VDAC))
            {
                string currentInputRange = CyDictParser.GetDictValue(parameters.m_dnDict, parameters.AdcInputRange);
                return new CyCustErr(string.Format(Resources.VDACExternalRef, currentInputRange.Substring(0,
                    currentInputRange.IndexOf('(') - 1)));
            }
            else
                return CyCustErr.OK;
        }
        #endregion

        #region ICyInstValidateHook_v1 Members
        public void ValidateParams(ICyInstValidate_v1 instVal)
        {
            CyParameters parameters = new CyParameters(instVal);
            if (parameters.IsArchMemberAvailable)
            {
                // Conversion rate validation
                if (parameters.AdcClockSource == CyEAdcClockSrcType.Internal &&
                    (parameters.AdcSampleRate < parameters.GetMinSampleRate() ||
                    parameters.AdcSampleRate > parameters.GetMaxSampleRate()))
                {
                    CyCustErr err = new CyCustErr(string.Format(Resources.DRCConversionRate,
                        CyParamRange.MIN_FREQ_MHZ, parameters.MaxClockFrequencyMHz));
                    instVal.AddError(CyParamNames.SAMPLE_RATE, err);
                }
            }
        }
        #endregion

        #region ICyAPICustomize_v1 Members
        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery,
            IEnumerable<CyAPICustomizer> apis)
        {
            List<CyAPICustomizer> customizers = new List<CyAPICustomizer>(apis);
            Dictionary<string, string> paramDict = new Dictionary<string, string>();

            if (customizers.Count > 0) paramDict = customizers[0].MacroDictionary;

            CyParameters parameters = new CyParameters(query, termQuery);
            double clockFrequency;
            double pulseWidth = 0;
            string clockID = String.Empty;
            if (parameters.AdcClockSource == CyEAdcClockSrcType.Internal)
            {
                string clockName = query.InstanceName + CyClockReader.INTERNAL_CLK;
                clockID = CyClockReader.GetClockID(query.DesignQuery, clockName);
                clockFrequency = CyClockReader.GetInternalClockInHz(query.DesignQuery, query.InstanceName);
            }
            else
            {
                List<string> clockIDsList = termQuery.GetClockIds(CyClockReader.EXTERNAL_CLK, 0);
                if (clockIDsList.Count > 0)
                    clockID = clockIDsList[0];
                clockFrequency = CyClockReader.GetExternalClockInHz(termQuery);
            }

            if (clockFrequency >= 0)
            {
                pulseWidth = GetPulseWidth(query.DesignQuery, clockFrequency, clockID);
            }

            paramDict.Add("HighPowerPulse", (pulseWidth > CyParamRange.HIGH_POWER_PULSE_WIDTH ? 1 : 0).ToString());
            paramDict.Add("NominalClockFrequency", Convert.ToInt32(clockFrequency >= 0 ? clockFrequency :
                (-1)).ToString());

            for (int i = 0; i < customizers.Count; i++)
            {
                customizers[i].MacroDictionary = paramDict;
            }

            return customizers;
        }
        #endregion
    }
}
