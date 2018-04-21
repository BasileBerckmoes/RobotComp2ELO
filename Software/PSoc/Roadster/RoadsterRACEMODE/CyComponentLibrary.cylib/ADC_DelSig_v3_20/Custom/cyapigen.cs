/******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Windows.Forms;
using System.IO;
using System.Collections;


namespace ADC_DelSig_v3_20
{
    partial class CyCustomizer : ICyAPICustomize_v1
    {
        #region ParameterNamesValues
        string[] DEC_CR_ParamName = { "DFLT_DEC_CR", "DFLT_DEC_CR_CFG2", "DFLT_DEC_CR_CFG3", "DFLT_DEC_CR_CFG4" };
        string[] DEC_SR_ParamName = { "DFLT_DEC_SR", "DFLT_DEC_SR_CFG2", "DFLT_DEC_SR_CFG3", "DFLT_DEC_SR_CFG4" };
        string[] DEC_SHIFT1_ParamName = {"DFLT_DEC_SHIFT1", "DFLT_DEC_SHIFT1_CFG2", "DFLT_DEC_SHIFT1_CFG3", 
                                          "DFLT_DEC_SHIFT1_CFG4"};
        string[] DEC_SHIFT2_ParamName = {"DFLT_DEC_SHIFT2", "DFLT_DEC_SHIFT2_CFG2", "DFLT_DEC_SHIFT2_CFG3", 
                                          "DFLT_DEC_SHIFT2_CFG4"};
        string[] DEC_DR2_ParamName = {"DFLT_DEC_DR2", "DFLT_DEC_DR2_CFG2", "DFLT_DEC_DR2_CFG3", 
                                             "DFLT_DEC_DR2_CFG4"};
        string[] DEC_DR2H_ParamName = {"DFLT_DEC_DR2H", "DFLT_DEC_DR2H_CFG2", "DFLT_DEC_DR2H_CFG3", 
                                             "DFLT_DEC_DR2H_CFG4"};
        string[] DEC_DR1_ParamName = {"DFLT_DEC_DR1", "DFLT_DEC_DR1_CFG2", "DFLT_DEC_DR1_CFG3", 
                                             "DFLT_DEC_DR1_CFG4"};
        string[] DEC_OCOR_ParamName = {"DFLT_DEC_OCOR", "DFLT_DEC_OCOR_CFG2", "DFLT_DEC_OCOR_CFG3", 
                                             "DFLT_DEC_OCOR_CFG4"};
        string[] DEC_OCORM_ParamName = {"DFLT_DEC_OCORM", "DFLT_DEC_OCORM_CFG2", "DFLT_DEC_OCORM_CFG3", 
                                             "DFLT_DEC_OCORM_CFG4"};
        string[] DEC_OCORH_ParamName = {"DFLT_DEC_OCORH", "DFLT_DEC_OCORH_CFG2", "DFLT_DEC_OCORH_CFG3", 
                                             "DFLT_DEC_OCORH_CFG4"};
        string[] DEC_GVAL_ParamName = {"DFLT_DEC_GVAL", "DFLT_DEC_GVAL_CFG2","DFLT_DEC_GVAL_CFG3", 
                                             "DFLT_DEC_GVAL_CFG4"};
        string[] DEC_GCOR_ParamName = {"DFLT_DEC_GCOR", "DFLT_DEC_GCOR_CFG2", "DFLT_DEC_GCOR_CFG3", 
                                             "DFLT_DEC_GCOR_CFG4"};
        string[] DEC_GCORH_ParamName = {"DFLT_DEC_GCORH", "DFLT_DEC_GCORH_CFG2", "DFLT_DEC_GCORH_CFG3", 
                                             "DFLT_DEC_GCORH_CFG4"};
        string[] DEC_COHER_ParamName = {"DFLT_DEC_COHER", "DFLT_DEC_COHER_CFG2", "DFLT_DEC_COHER_CFG3", 
                                             "DFLT_DEC_COHER_CFG4"};

        string[] DSM_CR0_ParamName = { "DFLT_DSM_CR0", "DFLT_DSM_CR0_CFG2", "DFLT_DSM_CR0_CFG3", "DFLT_DSM_CR0_CFG4" };
        string[] DSM_CR1_ParamName = { "DFLT_DSM_CR1", "DFLT_DSM_CR1_CFG2", "DFLT_DSM_CR1_CFG3", "DFLT_DSM_CR1_CFG4" };
        string[] DSM_CR2_ParamName = { "DFLT_DSM_CR2", "DFLT_DSM_CR2_CFG2", "DFLT_DSM_CR2_CFG3", "DFLT_DSM_CR2_CFG4" };
        string[] DSM_CR3_ParamName = { "DFLT_DSM_CR3", "DFLT_DSM_CR3_CFG2", "DFLT_DSM_CR3_CFG3", "DFLT_DSM_CR3_CFG4" };
        string[] DSM_CR4_ParamName = { "DFLT_DSM_CR4", "DFLT_DSM_CR4_CFG2", "DFLT_DSM_CR4_CFG3", "DFLT_DSM_CR4_CFG4" };
        string[] DSM_CR5_ParamName = { "DFLT_DSM_CR5", "DFLT_DSM_CR5_CFG2", "DFLT_DSM_CR5_CFG3", "DFLT_DSM_CR5_CFG4" };
        string[] DSM_CR6_ParamName = { "DFLT_DSM_CR6", "DFLT_DSM_CR6_CFG2", "DFLT_DSM_CR6_CFG3", "DFLT_DSM_CR6_CFG4" };
        string[] DSM_CR7_ParamName = { "DFLT_DSM_CR7", "DFLT_DSM_CR7_CFG2", "DFLT_DSM_CR7_CFG3", "DFLT_DSM_CR7_CFG4" };
        string[] DSM_CR8_ParamName = { "DFLT_DSM_CR8", "DFLT_DSM_CR8_CFG2", "DFLT_DSM_CR8_CFG3", "DFLT_DSM_CR8_CFG4" };
        string[] DSM_CR9_ParamName = { "DFLT_DSM_CR9", "DFLT_DSM_CR9_CFG2", "DFLT_DSM_CR9_CFG3", "DFLT_DSM_CR9_CFG4" };

        string[] DSM_CR10_ParamName = {"DFLT_DSM_CR10", "DFLT_DSM_CR10_CFG2", "DFLT_DSM_CR10_CFG3", 
                                          "DFLT_DSM_CR10_CFG4"};
        string[] DSM_CR11_ParamName = {"DFLT_DSM_CR11", "DFLT_DSM_CR11_CFG2", "DFLT_DSM_CR11_CFG3", 
                                          "DFLT_DSM_CR11_CFG4"};
        string[] DSM_CR12_ParamName = {"DFLT_DSM_CR12", "DFLT_DSM_CR12_CFG2", "DFLT_DSM_CR12_CFG3", 
                                          "DFLT_DSM_CR12_CFG4"};
        string[] DSM_CR13_ParamName = {"DFLT_DSM_CR13", "DFLT_DSM_CR13_CFG2", "DFLT_DSM_CR13_CFG3", 
                                          "DFLT_DSM_CR13_CFG4"};
        string[] DSM_CR14_ParamName = {"DFLT_DSM_CR14", "DFLT_DSM_CR14_CFG2", "DFLT_DSM_CR14_CFG3", 
                                          "DFLT_DSM_CR14_CFG4"};
        string[] DSM_CR15_ParamName = {"DFLT_DSM_CR15", "DFLT_DSM_CR15_CFG2", "DFLT_DSM_CR15_CFG3", 
                                          "DFLT_DSM_CR15_CFG4"};
        string[] DSM_CR16_ParamName = {"DFLT_DSM_CR16", "DFLT_DSM_CR16_CFG2", "DFLT_DSM_CR16_CFG3", 
                                          "DFLT_DSM_CR16_CFG4"};
        string[] DSM_CR17_ParamName = {"DFLT_DSM_CR17", "DFLT_DSM_CR17_CFG2", "DFLT_DSM_CR17_CFG3", 
                                          "DFLT_DSM_CR17_CFG4"};

        string[] DSM_REF0_ParamName = {"DFLT_DSM_REF0", "DFLT_DSM_REF0_CFG2", "DFLT_DSM_REF0_CFG3", 
                                          "DFLT_DSM_REF0_CFG4"};
        string[] DSM_REF2_ParamName = {"DFLT_DSM_REF2", "DFLT_DSM_REF2_CFG2", "DFLT_DSM_REF2_CFG3", 
                                          "DFLT_DSM_REF2_CFG4"};
        string[] DSM_REF3_ParamName = {"DFLT_DSM_REF3", "DFLT_DSM_REF3_CFG2", "DFLT_DSM_REF3_CFG3", 
                                          "DFLT_DSM_REF3_CFG4"};

        string[] DSM_DEM0_ParamName = {"DFLT_DSM_DEM0", "DFLT_DSM_DEM0_CFG2", "DFLT_DSM_DEM0_CFG3", 
                                          "DFLT_DSM_DEM0_CFG4"};
        string[] DSM_DEM1_ParamName = {"DFLT_DSM_DEM1", "DFLT_DSM_DEM1_CFG2", "DFLT_DSM_DEM1_CFG3", 
                                          "DFLT_DSM_DEM1_CFG4"};
        string DSM_MISC_ParamName = "DFLT_DSM_MISC";
        string DSM_CLK_ParamName = "DFLT_DSM_CLK";
        string DSM_REF1_ParamName = "DFLT_DSM_REF1";

        string[] DSM_BUF0_ParamName = {"DFLT_DSM_BUF0", "DFLT_DSM_BUF0_CFG2", "DFLT_DSM_BUF0_CFG3", 
                                          "DFLT_DSM_BUF0_CFG4"};
        string[] DSM_BUF1_ParamName = {"DFLT_DSM_BUF1", "DFLT_DSM_BUF1_CFG2", "DFLT_DSM_BUF1_CFG3", 
                                          "DFLT_DSM_BUF1_CFG4"};
        string[] DSM_BUF2_ParamName = {"DFLT_DSM_BUF2", "DFLT_DSM_BUF2_CFG2", "DFLT_DSM_BUF2_CFG3", 
                                          "DFLT_DSM_BUF2_CFG4"};
        string[] DSM_BUF3_ParamName = {"DFLT_DSM_BUF3", "DFLT_DSM_BUF3_CFG2", "DFLT_DSM_BUF3_CFG3", 
                                          "DFLT_DSM_BUF3_CFG4"};
        string[] DSM_OUT0_ParamName = {"DFLT_DSM_OUT0", "DFLT_DSM_OUT0_CFG2", "DFLT_DSM_OUT0_CFG3", 
                                          "DFLT_DSM_OUT0_CFG4"};
        string[] DSM_OUT1_ParamName = {"DFLT_DSM_OUT1", "DFLT_DSM_OUT1_CFG2", "DFLT_DSM_OUT1_CFG3", 
                                          "DFLT_DSM_OUT1_CFG4"};
        string[] adcClockFrequency_ParamName = {"DFLT_CLK_FREQ", "DFLT_CLK_FREQ_CFG2", "DFLT_CLK_FREQ_CFG3", 
                                                "DFLT_CLK_FREQ_CFG4"};
        string[] chargePumpClockFrequency_ParamName = {"DFLT_CP_CLK_FREQ", "DFLT_CP_CLK_FREQ_CFG2", 
                                                       "DFLT_CP_CLK_FREQ_CFG3", "DFLT_CP_CLK_FREQ_CFG4"};
        string[] clocksPerSample_ParamName = {"DFLT_CLOCKS_PER_SAMPLE", "DFLT_CLOCKS_PER_SAMPLE_CFG2", 
                                                 "DFLT_CLOCKS_PER_SAMPLE_CFG3", "DFLT_CLOCKS_PER_SAMPLE_CFG4"};
        string[] adcClockDivider_ParamName = {"DFLT_ADC_CLK_DIVIDER", "DFLT_ADC_CLK_DIVIDER_CFG2", 
                                                 "DFLT_ADC_CLK_DIVIDER_CFG3", "DFLT_ADC_CLK_DIVIDER_CFG4"};
        string[] cpClockDivider_ParamName = {"DFLT_CP_CLK_DIVIDER", "DFLT_CP_CLK_DIVIDER_CFG2", 
                                                 "DFLT_CP_CLK_DIVIDER_CFG3", "DFLT_CP_CLK_DIVIDER_CFG4"};
        // Commenting out this since this is no more used in the new version CDT 50250 
        string[] DSM_SW3_ParamName = { "DFLT_DSM_SW3", "DFLT_DSM_SW3_CFG2", "DFLT_DSM_SW3_CFG3", "DFLT_DSM_SW3_CFG4" };

        string[] leftBitShift_ParamName = { "BIT_SHIFT_CFG1", "BIT_SHIFT_CFG2", "BIT_SHIFT_CFG3", "BIT_SHIFT_CFG4" };

        string[] CountsPerVoltParamName ={"DFLT_COUNTS_PER_VOLT", "DFLT_COUNTS_PER_VOLT_CFG2", 
                                             "DFLT_COUNTS_PER_VOLT_CFG3", "DFLT_COUNTS_PER_VOLT_CFG4"};
        string[] RefVoltage_ParamName = {"DFLT_REF_VOLTAGE", "DFLT_REF_VOLTAGE_CFG2", "DFLT_REF_VOLTAGE_CFG3", 
                                            "DFLT_REF_VOLTAGE_CFG4"};
        string[] IdealDecGain_ParamName = {"DFLT_IDEAL_DEC_GAIN", "DFLT_IDEAL_DEC_GAIN_CFG2", 
                                              "DFLT_IDEAL_DEC_GAIN_CFG3", "DFLT_IDEAL_DEC_GAIN_CFG4"};
        string[] IdealOddDecGain_ParamName = {"DFLT_IDEAL_ODDDEC_GAIN", "DFLT_IDEAL_ODDDEC_GAIN_CFG2", 
                                                 "DFLT_IDEAL_ODDDEC_GAIN_CFG3", "DFLT_IDEAL_ODDDEC_GAIN_CFG4"};
        string[] IPCap1Value_ParamName = {"DFLT_IPCap1Value", "DFLT_IPCap1Value_CFG2", "DFLT_IPCap1Value_CFG3", 
                                             "DFLT_IPCap1Value_CFG4"};
        string[] DACCapValue_ParamName = {"DFLT_DACCapValue", "DFLT_DACCapValue_CFG2", "DFLT_DACCapValue_CFG3", 
                                             "DFLT_DACCapValue_CFG4"};

        uint ADC_Clock;
        uint[] ADC_Input_Range = new uint[4] { 0, 0, 0, 0 };
        uint[] ADC_Reference = new uint[4] { 0, 0, 0, 0 };
        uint[] ADC_Resolution = new uint[4] { 0, 0, 0, 0 };
        CyEConversionMode[] Conversion_Mode = new CyEConversionMode[4] { 0, 0, 0, 0 };
        uint[] Input_Buffer_Gain = new uint[4] { 0, 0, 0, 0 };
        uint[] Sample_Rate = new uint[4] { 0, 0, 0, 0 };
        CyEAlignment[] Alignment = new CyEAlignment[4] { 0, 0, 0, 0 };
        uint Start_of_Conversion;
        float[] Ref_Voltage = new float[4] { 0, 0, 0, 0 };
        uint[] CountsPerVolt = new uint[4] { 0, 0, 0, 0 };
        CyEBufferMode[] Input_Buffer_Mode = new CyEBufferMode[4] { 0, 0, 0, 0 };
        //uint NumConfigs;
        uint ADC_Input_Mode;
        uint[] ADC_Input_ModeValue = new uint[4] { 0, 0, 0, 0 };
        double[] ADC_Input_RangeValue = new double[4] { 0, 0, 0, 0 };
        uint ADC_ChargePump;

        uint[] LeftBitShift = new uint[4] { 0, 0, 0, 0 };
        uint[] AdcClockDivider = new uint[4] { 0, 0, 0, 0 };
        uint[] CpClockDivider = new uint[4] { 0, 0, 0, 0 };

        uint[] DecCrReg = new uint[4] { 0, 0, 0, 0 };
        uint[] DecSrReg = new uint[4] { 0, 0, 0, 0 };
        uint[] DecShift1Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DecShift2Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DecDr2Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DecDr2hReg = new uint[4] { 0, 0, 0, 0 };
        uint[] DecDr1Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DecOcorReg = new uint[4] { 0, 0, 0, 0 };
        uint[] DecOcormReg = new uint[4] { 0, 0, 0, 0 };
        uint[] DecOcorhReg = new uint[4] { 0, 0, 0, 0 };
        uint[] DecGvalReg = new uint[4] { 0, 0, 0, 0 };
        uint[] DecGcorReg = new uint[4] { 0, 0, 0, 0 };
        uint[] DecGcorhReg = new uint[4] { 0, 0, 0, 0 };
        uint[] DecCoherReg = new uint[4] { 0, 0, 0, 0 };

        uint[] DsmCr0Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmCr1Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmCr2Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmCr3Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmCr4Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmCr5Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmCr6Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmCr7Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmCr8Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmCr9Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmCr10Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmCr11Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmCr12Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmCr13Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmCr14Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmCr15Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmCr16Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmCr17Reg = new uint[4] { 0, 0, 0, 0 };

        uint[] DsmRef0Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmRef2Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmRef3Reg = new uint[4] { 0, 0, 0, 0 };

        uint[] DsmDem0Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmDem1Reg = new uint[4] { 0, 0, 0, 0 };
        uint DsmMiscReg;
        uint DsmClkReg;
        uint DsmRef1Reg;


        uint[] DsmBuf0Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmBuf1Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmBuf2Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmBuf3Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmOut0Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] DsmOut1Reg = new uint[4] { 0, 0, 0, 0 };

        // Commenting this due to CDT 50250 
        uint[] DsmSw3Reg = new uint[4] { 0, 0, 0, 0 };
        uint[] Ideal_Dec_Gain = new uint[4] { 0, 0, 0, 0 };
        uint[] Ideal_OddDec_Gain = new uint[4] { 0, 0, 0, 0 };
        uint[] IPCap1Value = new uint[4] { 0, 0, 0, 0 };
        uint[] DACCapValue = new uint[4] { 0, 0, 0, 0 };

        ICyTerminalQuery_v1 m_termQuery;
        ICyInstQuery_v1 m_instQuery;
        CyParameters m_params;

        #endregion

        #region ICyAPICustomize_v1 Members
        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery,
                                                           IEnumerable<CyAPICustomizer> apis)
        {
            Dictionary<string, string> paramDict = null;
            m_termQuery = termQuery;
            m_instQuery = query;
            foreach (CyAPICustomizer api in apis)
            {
                // Get parameter dictionary
                paramDict = api.MacroDictionary;
            }
            m_params = new CyParameters(m_instQuery, termQuery);
            float vdda = (float)m_params.VDDA;
            // Calculate values
            CalcValues(ref paramDict, vdda);
            // Assign dictionary back to API customizers
            foreach (CyAPICustomizer api in apis)
            {
                api.MacroDictionary = paramDict;
            }
            // Return customizers
            return apis;
        }
        #endregion

        /// <summary>
        /// Set ADC resolution.
        /// </summary>
        /// <param name="resolutionIndex">Set the ADC resolution </param>
        /// <param name="inputRange">Input range selected.</param>
        /// <param name="config">ADC configuration number</param>
        void SetResolution(uint resolution, uint inputRange, CyEAlignment alignment, uint config)
        {
            uint rShiftOffset = 0;

            ADC_Resolution[config] = resolution;
            // Offset correction 
            // This could be used to offset result for signed and unsigned results 
            DecOcorReg[config] = 0;
            DecOcormReg[config] = 0;
            DecOcorhReg[config] = 0;

            // Gain correction 
            // DecGvalReg[config] = 0;
            DecGcorReg[config] = 0;
            DecGcorhReg[config] = 0;

            if (resolution < Cyrc.MIN_RESOLUTION) resolution = Cyrc.MIN_RESOLUTION;
            if (resolution > Cyrc.MAX_RESOLUTION) resolution = Cyrc.MAX_RESOLUTION;

            // If single ended mode, don't shift an additional bit 
            if ((ADC_Input_Range[config] == Cyrc.ADC_IR_VSSA_TO_VREF) |
                (ADC_Input_Range[config] == Cyrc.ADC_IR_VSSA_TO_VDDA) |
                (ADC_Input_Range[config] == Cyrc.ADC_IR_VSSA_TO_6VREF)) 
            {
                rShiftOffset = 1;
            }

            uint resolutionIndex = resolution - Cyrc.MIN_RESOLUTION;

            // Set resolution constants from table 
            DecDr1Reg[config] = CyresSettings.dr1[resolutionIndex];
            DecDr2Reg[config] = CyresSettings.dr2[resolutionIndex];
            DecDr2hReg[config] = CyresSettings.dr2h[resolutionIndex];

            switch (alignment)  
            {
                case CyEAlignment.Right:
                    DecShift1Reg[config] = CyresSettings.shift1_def[resolutionIndex];
                    DecShift2Reg[config] = CyresSettings.shift2_def[resolutionIndex];
                    
                    break;
                case CyEAlignment.Left_OVF_Protected:
                    DecShift1Reg[config] = CyresSettings.shift1_OVF[resolutionIndex];
                    DecShift2Reg[config] = CyresSettings.shift2_OVF[resolutionIndex];
                    break;
                case CyEAlignment.Left_Not_OVF_Protected:
                    DecShift1Reg[config] = CyresSettings.shift1_nOVF[resolutionIndex];
                    DecShift2Reg[config] = CyresSettings.shift2_nOVF[resolutionIndex];
                    break;
                default:
                    Debug.Assert(false);
                    break;
            }

            // Number of left shifted bits
            LeftBitShift[config] = 0;
            if (alignment != CyEAlignment.Right)
            {
                int numBits = (int)(DecShift1Reg[config] - CyresSettings.shift1_def[resolutionIndex] -
                                            (DecShift2Reg[config] - CyresSettings.shift2_def[resolutionIndex]));
                LeftBitShift[config] = (uint)Math.Pow(2, numBits);
            }

            if (DecShift2Reg[config] > 0)
            {
                DecShift2Reg[config] -= rShiftOffset;
            }
            else
            {
                DecShift1Reg[config] += rShiftOffset;
            }

            // Coherency
            DecCoherReg[config] = CyParameters.GetCoherency(resolution, alignment);
        }

        /// <summary>
        /// Set input buffer range.
        /// </summary>
        /// <param name="gain">Two bit value to select a gain of 1, 2, 4, or 8</param>
        /// <param name="config">configuration selected</param> 
        void SetBufferGain(uint gain, uint config)
        {
            uint tmpReg;
            uint gainSetting = 1;

            switch (gain)
            {
                case 1:
                    gainSetting = Cyrc.DSM_GAIN_1X;
                    break;
                case 2:
                    gainSetting = Cyrc.DSM_GAIN_2X;
                    break;
                case 4:
                    gainSetting = Cyrc.DSM_GAIN_4X;
                    break;
                case 8:
                    gainSetting = Cyrc.DSM_GAIN_8X;
                    break;
                default:
                    gainSetting = Cyrc.ADC_IBG_1X;
                    break;
            }

            tmpReg = DsmBuf1Reg[config] & ~Cyrc.DSM_GAIN_MASK;
            tmpReg |= gainSetting;
            DsmBuf1Reg[config] = tmpReg;
        }

        void SetBufferMode(CyEBufferMode mode, uint config)
        {
            uint tmp = 0;

            if (mode == CyEBufferMode.Bypass_Buffer)
            {
                DsmBuf0Reg[config] = Cyrc.DSM_BYPASS_P;   // Bypass positive buffer channel
                DsmBuf1Reg[config] = Cyrc.DSM_BYPASS_N;   // Bypass negative buffer channel
                DsmBuf2Reg[config] = 0x00;              // Disable power and RC
                DsmBuf3Reg[config] = 0x00;              // Disable chopper
            }
            else if (mode == CyEBufferMode.Rail_to_Rail)
            {
                tmp |= Cyrc.DSM_ENABLE_P;//Enable positive buffer
                tmp |= Cyrc.DSM_RAIL_RAIL_EN;//Enables Rail to Rail operation
                DsmBuf0Reg[config] = tmp;
                if (ADC_Input_Mode == Cyrc.INPUT_MODE_SINGLE)
                {
                    tmp = DsmBuf1Reg[config] & Cyrc.DSM_GAIN_MASK;
                    tmp |= Cyrc.DSM_BYPASS_N;//Bypasses the negative buffer
                    DsmBuf1Reg[config] = tmp;
                }
                else
                {
                    tmp = DsmBuf1Reg[config] & Cyrc.DSM_GAIN_MASK;
                    tmp |= Cyrc.DSM_ENABLE_N;//Enable the negative buffer
                    DsmBuf1Reg[config] = tmp;
                }
            }
            else if (mode == CyEBufferMode.Level_Shift)
            {
                tmp |= Cyrc.DSM_ENABLE_P;//Enables positive buffer
                DsmBuf0Reg[config] = tmp;

                tmp = DsmBuf1Reg[config] & Cyrc.DSM_GAIN_MASK;
                tmp |= Cyrc.DSM_ENABLE_N;//Enable the negative buffer
                DsmBuf1Reg[config] = tmp;
            }

            // Enable the chopping only if both the input buffers are enabled 
            if (((DsmBuf0Reg[config] & Cyrc.DSM_ENABLE_P) != 0) && ((DsmBuf1Reg[config] & Cyrc.DSM_ENABLE_N) != 0))
            {
                DsmBuf3Reg[config] = Cyrc.DSM_BUF_CHOP_EN | Cyrc.DSM_BUF_FCHOP_FS8;
            }
            else
            {
                DsmBuf3Reg[config] = 0x00;
            }
        }


        /// <summary> 
        /// Sets reference for ADC
        /// </summary>
        /// <param name="refMode">Reference configuration.</param>
        /// <param name="inputMode">ipnut range selcted.</param>
        /// <param name="config">configuration selected.</param>
        /// <param name="vdda">vdda value entered in the system wide resource file. Based on this value
        ///                   reference will be selected.</param>
        void SetRef(uint refMode, uint inputMode, uint config, float vdda)
        {
            // Mask off reference 
            DsmRef0Reg[config] &= ~Cyrc.DSM_REFMUX_MASK;

            // Connect the switch matrix for the proper reference mode 
            if (inputMode != Cyrc.ADC_IR_VSSA_TO_VDDA)
            {
                switch (refMode)
                {
                    case Cyrc.ADC_INT_REF_NOT_BYPASSED:
                        DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;
                        DsmRef2Reg[config] = Cyrc.DSM_REF2_S3_EN | Cyrc.DSM_REF2_S4_EN | Cyrc.DSM_REF2_S6_EN;
                        DsmRef3Reg[config] = Cyrc.DSM_REF3_NO_SW;
                        DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                        break;

                    case Cyrc.ADC_INT_REF_BYPASSED_ON_P32:
                        DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;
                        DsmRef2Reg[config] = Cyrc.DSM_REF2_S0_EN | Cyrc.DSM_REF2_S1_EN | Cyrc.DSM_REF2_S2_EN |
                                             Cyrc.DSM_REF2_S6_EN;
                        DsmRef3Reg[config] = Cyrc.DSM_REF3_NO_SW;
                        DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                        break;

                    case Cyrc.ADC_INT_REF_BYPASSED_ON_P03:
                        DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;
                        DsmRef2Reg[config] = Cyrc.DSM_REF2_S6_EN | Cyrc.DSM_REF2_S7_EN;
                        DsmRef3Reg[config] = Cyrc.DSM_REF3_S8_EN | Cyrc.DSM_REF3_S9_EN;
                        DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                        break;

                    case Cyrc.ADC_EXT_REF_ON_P03:
                        DsmRef2Reg[config] = Cyrc.DSM_REF2_S6_EN;
                        if (inputMode == Cyrc.ADC_IR_VSSA_TO_2VREF)
                        {
                            DsmRef3Reg[config] = Cyrc.DSM_REF3_S9_EN | Cyrc.DSM_REF3_S11_EN | Cyrc.DSM_REF3_S12_EN;
                            DsmRef0Reg[config] &= ~Cyrc.DSM_EN_BUF_VREF_INN;
                        }
                        else
                        {
                            DsmRef3Reg[config] = Cyrc.DSM_REF3_S9_EN | Cyrc.DSM_REF3_S11_EN;
                        }
                        DsmCr17Reg[config] &= ~Cyrc.DSM_EN_BUF_VREF;  // Disable Int Ref Amp 
                        break;

                    case Cyrc.ADC_EXT_REF_ON_P32:
                        DsmRef2Reg[config] = Cyrc.DSM_REF2_S2_EN | Cyrc.DSM_REF2_S5_EN | Cyrc.DSM_REF2_S6_EN;
                        if (inputMode == Cyrc.ADC_IR_VSSA_TO_2VREF)
                        {
                            DsmRef3Reg[config] = Cyrc.DSM_REF3_S12_EN;
                            DsmRef0Reg[config] &= ~Cyrc.DSM_EN_BUF_VREF_INN;
                        }
                        else
                        {
                            DsmRef3Reg[config] = Cyrc.DSM_REF3_NO_SW;
                        }
                        DsmCr17Reg[config] &= ~Cyrc.DSM_EN_BUF_VREF;   // Disable Int Ref Amp 
                        break;

                    case Cyrc.ADC_INT_REF_VDDA_4:
                        DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_VDA_4 | Cyrc.DSM_VREF_RES_DIV_EN;
                        DsmRef2Reg[config] = Cyrc.DSM_REF2_S3_EN | Cyrc.DSM_REF2_S4_EN | Cyrc.DSM_REF2_S6_EN;
                        DsmRef3Reg[config] = Cyrc.DSM_REF3_NO_SW;
                        DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                        break;

                    case Cyrc.ADC_INT_REF_VDDA_4_BYPASSED_ON_P03:
                        DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_VDA_4 | Cyrc.DSM_VREF_RES_DIV_EN;
                        DsmRef2Reg[config] = Cyrc.DSM_REF2_S6_EN | Cyrc.DSM_REF2_S7_EN;
                        DsmRef3Reg[config] = Cyrc.DSM_REF3_S8_EN | Cyrc.DSM_REF3_S9_EN;
                        DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                        break;

                    case Cyrc.ADC_INT_REF_VDDA_4_BYPASSED_ON_P32:
                        DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_VDA_4 | Cyrc.DSM_VREF_RES_DIV_EN;
                        DsmRef2Reg[config] = Cyrc.DSM_REF2_S0_EN | Cyrc.DSM_REF2_S1_EN | Cyrc.DSM_REF2_S2_EN |
                                              Cyrc.DSM_REF2_S6_EN;
                        DsmRef3Reg[config] = Cyrc.DSM_REF3_NO_SW;
                        DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                        break;

                    case Cyrc.ADC_INT_REF_VDDA_3:
                        DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_VDA_3 | Cyrc.DSM_VREF_RES_DIV_EN;
                        DsmRef2Reg[config] = Cyrc.DSM_REF2_S3_EN | Cyrc.DSM_REF2_S4_EN | Cyrc.DSM_REF2_S6_EN;
                        DsmRef3Reg[config] = Cyrc.DSM_REF3_NO_SW;
                        DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                        break;

                    case Cyrc.ADC_INT_REF_VDDA_3_BYPASSED_ON_P03:
                        DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_VDA_3 | Cyrc.DSM_VREF_RES_DIV_EN;
                        DsmRef2Reg[config] = Cyrc.DSM_REF2_S6_EN | Cyrc.DSM_REF2_S7_EN;
                        DsmRef3Reg[config] = Cyrc.DSM_REF3_S8_EN | Cyrc.DSM_REF3_S9_EN;
                        DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                        break;

                    case Cyrc.ADC_INT_REF_VDDA_3_BYPASSED_ON_P32:
                        DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_VDA_3 | Cyrc.DSM_VREF_RES_DIV_EN;
                        DsmRef2Reg[config] = Cyrc.DSM_REF2_S0_EN | Cyrc.DSM_REF2_S1_EN | Cyrc.DSM_REF2_S2_EN |
                                             Cyrc.DSM_REF2_S6_EN;
                        DsmRef3Reg[config] = Cyrc.DSM_REF3_NO_SW;
                        DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                        break;

                    default:
                        break;
                }
            }
            else  // VSSA to VDDA
            {
                if (vdda < CyParamRanges.MAX_VDDA3_VALUE)
                {
                    DsmRef0Reg[config] = (Cyrc.DSM_REFMUX_VDA_3 | Cyrc.DSM_VREF_RES_DIV_EN | Cyrc.DSM_VCMSEL_0_8V);
                }
                else
                {
                    DsmRef0Reg[config] = (Cyrc.DSM_REFMUX_VDA_4 | Cyrc.DSM_VREF_RES_DIV_EN | Cyrc.DSM_VCMSEL_0_8V);
                }
               
                switch (refMode)
                {
                    case Cyrc.ADC_INT_REF_NOT_BYPASSED:
                    case Cyrc.ADC_INT_REF_VDDA_4:
                    case Cyrc.ADC_INT_REF_VDDA_3:
                        DsmRef2Reg[config] = Cyrc.DSM_REF2_S3_EN | Cyrc.DSM_REF2_S4_EN | Cyrc.DSM_REF2_S6_EN;
                        DsmRef3Reg[config] = Cyrc.DSM_REF3_NO_SW;
                        DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                        break;

                    case Cyrc.ADC_INT_REF_BYPASSED_ON_P32:
                    case Cyrc.ADC_INT_REF_VDDA_4_BYPASSED_ON_P32:
                    case Cyrc.ADC_INT_REF_VDDA_3_BYPASSED_ON_P32:
                        DsmRef2Reg[config] = Cyrc.DSM_REF2_S0_EN | Cyrc.DSM_REF2_S1_EN | Cyrc.DSM_REF2_S2_EN |
                                             Cyrc.DSM_REF2_S6_EN;
                        DsmRef3Reg[config] = Cyrc.DSM_REF3_NO_SW;
                        DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                        break;

                    case Cyrc.ADC_INT_REF_BYPASSED_ON_P03:
                    case Cyrc.ADC_INT_REF_VDDA_4_BYPASSED_ON_P03:
                    case Cyrc.ADC_INT_REF_VDDA_3_BYPASSED_ON_P03:
                        DsmRef2Reg[config] = Cyrc.DSM_REF2_S6_EN | Cyrc.DSM_REF2_S7_EN;
                        DsmRef3Reg[config] = Cyrc.DSM_REF3_S8_EN | Cyrc.DSM_REF3_S9_EN;
                        DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                        break;

                    case Cyrc.ADC_EXT_REF_ON_P03:
                    case Cyrc.ADC_EXT_REF_ON_P32:
                    default:
                        break;
                }
            }
        }

        /// <summary>
        /// Sets input range of the ADC independent of the input buffer gain.
        /// </summary>
        /// <param name="inputMode">ADC input configuration mode.</param>
        /// <param name="refVoltage">Reference voltage selected in the reference voltage numerical up down menu.</param>
        /// <param name="config">ADC configuration number.</param>
        /// <param name="vdda">Vdda value entered in the system wide resource file. Based on this value reference
        ///         will be selected for Vssa to Vdda input range.</param>
        void SetInputRange(uint inputMode, float refVoltage, uint config, float vdda)
        {
            //uint CapRatio;           vss/vref  *2  vs/vd  *6Sin   diff   *2di   *6Dif  /2dif /4dif  /8dif  /16dif
            double[] DesiredGain = { 1.000, 1.000, 0.250, 0.16667, 1.000, 0.500, 0.16667, 2.000, 4.000, 8.000, 16.000 };

            double DesiredGain_Vdda_3 = 0.333;
            // Resolution                      8       9      10      11      12     13      14     15
            double[] Decimator_Ratio_Gain = { 1.000, 0.8205, 0.9377, 0.9875, 1.000, 0.9066, 0.9368, 0.9866 };

            double Ideal_DecGain, DecGain;
            double CapRatio;
            uint OffsetCorrection, resolution;

            resolution = ADC_Resolution[config];
            resolution -= Cyrc.MIN_RESOLUTION;

            // Default setting
            if (ADC_Resolution[config] > 15)  // 16 to 20 bit resolution
            {
                if ((vdda < CyParamRanges.MAX_VDDA3_VALUE) && (inputMode == Cyrc.ADC_IR_VSSA_TO_VDDA))
                {
                    IPCap1Value[config] = Cyrc.IPCap1_Res16to20_Vdda_3_Real;
                    DACCapValue[config] = Cyrc.DACCap_Res16to20_Vdda_3_Real;
                    CapRatio = Math.Round((double)Cyrc.IPCap1_Res16to20_Vdda_3_Real / Cyrc.DACCap_Res16to20_Vdda_3_Real, 5);
                    DecGain = (DesiredGain_Vdda_3 / CapRatio);
                }
                else
                {
                    IPCap1Value[config] = Cyrc.IPCap1_Res16to20_Real[inputMode];
                    DACCapValue[config] = Cyrc.DACCap_Res16to20_Real[inputMode];
                    CapRatio = Math.Round((double)Cyrc.IPCap1_Res16to20_Real[inputMode] / Cyrc.DACCap_Res16to20_Real[inputMode], 5);
                    DecGain = (DesiredGain[inputMode] / CapRatio);

                }
                
                Ideal_DecGain = Math.Round((DecGain * 1.000), 5);
                Ideal_Dec_Gain[config] = (uint)Math.Truncate(Ideal_DecGain * Cyrc.IDEAL_GAIN_CONST);
                Ideal_OddDec_Gain[config] = (uint)Cyrc.IDEAL_GAIN_CONST;
            }
            else                              // 8 to 15 bits of resolution
            {
                if ((vdda < CyParamRanges.MAX_VDDA3_VALUE) && (inputMode == Cyrc.ADC_IR_VSSA_TO_VDDA))
                {
                    IPCap1Value[config] = Cyrc.IPCap1_Res8to15_Vdda_3_Real;
                    DACCapValue[config] = Cyrc.DACCap_Res8to15_Vdda_3_Real;
                    CapRatio = Math.Round((double)Cyrc.IPCap1_Res8to15_Vdda_3_Real / Cyrc.DACCap_Res8to15_Vdda_3_Real, 5);
                    DecGain = (DesiredGain_Vdda_3 / CapRatio);
                }
                else
                {
                    IPCap1Value[config] = Cyrc.IPCap1_Res8to15_Real[inputMode];
                    DACCapValue[config] = Cyrc.DACCap_Res8to15_Real[inputMode];
                    CapRatio = Math.Round((double)Cyrc.IPCap1_Res8to15_Real[inputMode] / Cyrc.DACCap_Res8to15_Real[inputMode], 5);
                    DecGain = (DesiredGain[inputMode] / CapRatio);
                }
                Ideal_DecGain = DecGain;
                //Ideal_DecGain = Math.Round(Ideal_DecGain * Decimator_Ratio_Gain[resolution], 5);
                Ideal_DecGain = Math.Round(Ideal_DecGain , 5);
                Ideal_Dec_Gain[config] = (uint)Math.Truncate(Ideal_DecGain * Cyrc.IDEAL_GAIN_CONST);

                Ideal_OddDec_Gain[config] = (uint)Math.Truncate(Decimator_Ratio_Gain[resolution] * 
                                            Cyrc.IDEAL_GAIN_CONST);
            }
            // Convert the double into hex value and feed that into the reg 

            // Configure Ref switches, reference, and input buffer
            switch (inputMode)
            {

                case Cyrc.ADC_IR_VSSA_TO_VREF: // Single ended, Vssa to Vref
                    // Set Single Ended input and disable negative buffer

                    // Set reference mux to 1.024V reference
                    DsmRef0Reg[config] &= ~Cyrc.DSM_REFMUX_MASK;
                    DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;

                    // Connect negative input to Vssa
                    DsmSw3Reg[config] = Cyrc.DSM_VN_VSSA;

                    // Set input mode and input range value 
                    ADC_Input_ModeValue[config] = 1;
                    ADC_Input_RangeValue[config] = Math.Round(refVoltage, 4);
                    break;

                case Cyrc.ADC_IR_VSSA_TO_2VREF: // Single ended, Vssa to 2*Vref                   
                    // Input is connected as differential with Vref conencted to negative input
                    // Set reference mux to 1.024V reference
                    DsmRef0Reg[config] &= ~Cyrc.DSM_REFMUX_MASK;
                    DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;
                    DsmRef0Reg[config] |= Cyrc.DSM_EN_BUF_VREF_INN;  // newly added as per CDT 93460.
                    if (Input_Buffer_Mode[config] != CyEBufferMode.Bypass_Buffer)
                    {
                        DsmBuf1Reg[config] = Cyrc.DSM_ENABLE_N;
                        DsmBuf3Reg[config] = Cyrc.DSM_BUF_CHOP_EN | Cyrc.DSM_BUF_FCHOP_FS8;
                        SetBufferGain(Input_Buffer_Gain[config], config);
                    }

                    if (ADC_Resolution[config] > 15)
                    {
                        OffsetCorrection = (uint)(Math.Pow(2, ADC_Resolution[config] - 1) *
                            ((LeftBitShift[config] > 0) ? LeftBitShift[config] : 1) / Ideal_DecGain);
                    }
                    else
                    {
                        Ideal_DecGain = Math.Round((DecGain * Decimator_Ratio_Gain[resolution]), 5); 
                        OffsetCorrection = (uint)(Math.Pow(2, ADC_Resolution[config] - 1) *
                            ((LeftBitShift[config] > 0) ? LeftBitShift[config] : 1) / Ideal_DecGain);
                    }
                    DecOcorReg[config] = BitConverter.GetBytes(OffsetCorrection)[0];
                    DecOcormReg[config] = BitConverter.GetBytes(OffsetCorrection)[1];
                    DecOcorhReg[config] = BitConverter.GetBytes(OffsetCorrection)[2];
                   
                    // Set input mode and input range value 
                    ADC_Input_ModeValue[config] = 1;
                    ADC_Input_RangeValue[config] = Math.Round(2 * refVoltage, 4);
                    break;

                case Cyrc.ADC_IR_VSSA_TO_6VREF:
                    DsmRef0Reg[config] &= ~Cyrc.DSM_REFMUX_MASK;
                    DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;

                    // Set modulator gain input caps to a gain of 6
                    // Default setting

                    // Connect negative input to Vssa
                    DsmSw3Reg[config] = Cyrc.DSM_VN_VSSA;

                    // Set input mode and input range value 
                    ADC_Input_ModeValue[config] = 1;
                    ADC_Input_RangeValue[config] = Math.Round(6 * refVoltage, 4);
                    break;

                case Cyrc.ADC_IR_VSSA_TO_VDDA:  // Single ended, Vssa to Vdda
                    // Vref = Vdda/4, Input gain = 1/2
                    // INN = Vref, differential mode

                    if (vdda < CyParamRanges.MAX_VDDA3_VALUE)
                    {
                        // Set reference mux to VDA/3 reference
                        DsmRef0Reg[config] = (Cyrc.DSM_REFMUX_VDA_3 | Cyrc.DSM_VREF_RES_DIV_EN | Cyrc.DSM_VCMSEL_0_8V);
                    }
                    else
                    {
                        // Set reference mux to VDA/4 reference
                        DsmRef0Reg[config] = (Cyrc.DSM_REFMUX_VDA_4 | Cyrc.DSM_VREF_RES_DIV_EN | Cyrc.DSM_VCMSEL_0_8V);
                    }
                  
                    ADC_Input_RangeValue[config] = Math.Round(vdda, 4);
                    // Connect negative input to Vssa
                    DsmSw3Reg[config] = Cyrc.DSM_VN_VSSA;

                    // Set input mode and input range value 
                    ADC_Input_ModeValue[config] = 1;
                    break;

                case Cyrc.ADC_IR_VNEG_VREF_DIFF:  // Diff, -Input +/- Vref

                    // Set reference mux to 1.024V reference
                    DsmRef0Reg[config] &= ~Cyrc.DSM_REFMUX_MASK;
                    DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;

                    // Set modulator gain input caps to a gain of 1
                    // disconnect references from -Input
                    DsmSw3Reg[config] = 0x00;

                    // Set input mode and input range value 
                    ADC_Input_ModeValue[config] = 2;
                    ADC_Input_RangeValue[config] = Math.Round(refVoltage, 4);
                    break;

                case Cyrc.ADC_IR_VNEG_2VREF_DIFF:  // Diff, -Input +/- 2*Vref

                    // Set reference mux to 1.024V reference
                    DsmRef0Reg[config] &= ~Cyrc.DSM_REFMUX_MASK;
                    DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;

                    // disconnect references from -Input
                    DsmSw3Reg[config] = 0x00;

                    // Set input mode and input range value 
                    ADC_Input_ModeValue[config] = 2;
                    ADC_Input_RangeValue[config] = Math.Round(2 * refVoltage, 4);
                    break;

                case Cyrc.ADC_IR_VNEG_6VREF_DIFF:

                    DsmRef0Reg[config] &= ~Cyrc.DSM_REFMUX_MASK;
                    DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;

                    // Set modulator gain input caps to a gain of 6
                    // Default setting

                    // Connect negative input to Vssa
                    DsmSw3Reg[config] = 0x00;

                    // Set input mode and input range value 
                    ADC_Input_ModeValue[config] = 2;
                    ADC_Input_RangeValue[config] = Math.Round(6 * refVoltage, 4);
                    break;

                case Cyrc.ADC_IR_VNEG_VREF_2_DIFF:  // Diff, -Input +/- Vref/2

                    // Set reference mux to 1.024V reference
                    DsmRef0Reg[config] &= ~Cyrc.DSM_REFMUX_MASK;
                    DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;

                    // disconnect references from -Input
                    DsmSw3Reg[config] = 0x00;

                    // Set input mode and input range value 
                    ADC_Input_ModeValue[config] = 2;
                    ADC_Input_RangeValue[config] = Math.Round(refVoltage / 2, 4);
                    break;


                case Cyrc.ADC_IR_VNEG_VREF_4_DIFF:  // Diff, -Input +/- Vref/4

                    // Set reference mux to 1.024V reference
                    DsmRef0Reg[config] &= ~Cyrc.DSM_REFMUX_MASK;
                    DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;

                    // disconnect references from -Input
                    DsmSw3Reg[config] = 0x00;

                    // Set input mode and input range value 
                    ADC_Input_ModeValue[config] = 2;
                    ADC_Input_RangeValue[config] = Math.Round(refVoltage / 4, 4);
                    break;

                case Cyrc.ADC_IR_VNEG_VREF_8_DIFF:

                    // Set reference mux to 1.024V reference
                    DsmRef0Reg[config] &= ~Cyrc.DSM_REFMUX_MASK;
                    DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;

                    // disconnect references from -Input
                    DsmSw3Reg[config] = 0x00;

                    // Set input mode and input range value 
                    ADC_Input_ModeValue[config] = 2;
                    ADC_Input_RangeValue[config] = Math.Round(refVoltage / 8, 4);
                    break;

                case Cyrc.ADC_IR_VNEG_VREF_16_DIFF:

                    // Set reference mux to 1.024V reference
                    DsmRef0Reg[config] &= ~Cyrc.DSM_REFMUX_MASK;
                    DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;

                    // disconnect references from -Input
                    DsmSw3Reg[config] = 0x00;

                    // Set input mode and input range value 
                    ADC_Input_ModeValue[config] = 2;
                    ADC_Input_RangeValue[config] = Math.Round(refVoltage / 16, 4);
                    break;

                default:
                    break;
            }
        }

        /// <summary>
        /// Sets operatonal mode of the Modulator input buffer.
        ///  Buffer modes   
        ///     Bypass P input => Bypass P input amp  ( Default, not bypassed )
        ///     Bypass N input => Bypass N input amp  ( Default, not bypassed )
        ///     Rail-To-Rail   => Enable mode for inputs to swiing rail to rail ( Default, not rail-to-rail)
        ///     Enable Filter  => Enable output R/C filter (Default, no filter )
        ///     Low Power      => Enable low power mode (Defalt, normal power mode )
        /// </summary>
        /// <param name="bufMode">Buffer mode value</param>
        /// <param name="config">Configuration selected</param>
        void SetBuffer(uint bufMode, uint config)
        {
            uint tmp = 0;

            // Setup BUF0 Register 
            // Check for positive buffer being bypassed 
            if ((bufMode & Cyrc.BUF_BYPASS_POS) > 0)
            {
                tmp |= Cyrc.DSM_BYPASS_P;
            }
            else /// POS buffer not bypassed, turn on buffer 
            {
                // If input gain is 0, then bypass positive channel buffer
                if (Input_Buffer_Gain[config] != 0)
                    tmp |= Cyrc.DSM_ENABLE_P;
                else
                    tmp |= Cyrc.DSM_BYPASS_P;
            }

            // Check for rail to rail operation 
            if ((bufMode & Cyrc.BUF_RAIL_TO_RAIL) > 0)
            {
                tmp |= Cyrc.DSM_RAIL_RAIL_EN;
            }

            DsmBuf0Reg[config] = tmp;   // Set Buf0 Register 

            // Setup BUF1 Register 
            // Check for negative buffer being bypassed, but don't mess with gain. 
            tmp = DsmBuf1Reg[config] & Cyrc.DSM_GAIN_MASK;
            if ((bufMode & Cyrc.BUF_BYPASS_NEG) > 0)
            {
                tmp |= Cyrc.DSM_BYPASS_N;
            }
            else // NEG buffer not bypassed, turn on buffer 
            {
                // If input buffer gain is 0, then disable negative channel buffer
                if (Input_Buffer_Gain[config] != 0)
                    tmp |= Cyrc.DSM_ENABLE_N;
                else
                    tmp |= Cyrc.DSM_BYPASS_N;
            }
            DsmBuf1Reg[config] = tmp;   // Set Buf1 Register 

            // Setup BUF2 Register 
            tmp = 0;
            // Check for Low Power 
            if (((bufMode & Cyrc.BUF_LOW_PWR) > 0) && ((Input_Buffer_Gain[config] == 1)))
            {
                tmp |= Cyrc.DSM_ENABLE_N;
            }

            // Check for Filer enable 
            if ((bufMode & Cyrc.BUF_FILTER_EN) > 0)
            {
                tmp |= Cyrc.DSM_ADD_EXTRA_RC;
            }

            DsmBuf2Reg[config] = tmp;   // Set Buf2 Register 

            // If both the positive and negative buffers are enabled, enable chopping.
            if (((DsmBuf0Reg[config] & Cyrc.DSM_ENABLE_P) != 0) && ((DsmBuf1Reg[config] & Cyrc.DSM_ENABLE_N) != 0))
            {
                DsmBuf3Reg[config] = Cyrc.DSM_BUF_CHOP_EN | Cyrc.DSM_BUF_FCHOP_FS8;
            }
            else
            {
                DsmBuf3Reg[config] = 0x00;
            }
        }

        private UInt16 SetClockDivider(uint clockFrequency, float minFreq, float maxFreq, uint config)
        {
            UInt16 clockDivider = 0;

            double masterClockFreq = m_params.GetMasterClockInHz();
            bool isMasterClockFrequencyKnown = CyParameters.IsFrequencyKnown(masterClockFreq);
            
            if (CyParameters.IsFrequencyKnown(clockFrequency) && isMasterClockFrequencyKnown)
            {
                CyParameters.GetClockDivider((float)masterClockFreq, clockFrequency, minFreq, maxFreq, out clockDivider);
                if (clockDivider > 0)
                    clockDivider -= 1;
            }
            return clockDivider;
        }

        /// <summary>
        /// Calculates the frequency required for the given resolution, sample rate,
        ///  and conversion mode.
        /// </summary>
        /// <param name="resolution">resolution selected</param>
        /// <param name="sampleRate">sample rate selected</param>
        /// <param name="conversionMode">conversion mode selected</param>
        /// <returns>Desired clock frequency.</returns>
        static public uint SetClock(uint resolution, uint sampleRate, CyEConversionMode conversionMode)
        {
            uint clocksPerSample = ClocksPerSample(resolution, conversionMode);
            return clocksPerSample * sampleRate;
        }

        /// <summary>
        /// Calculates the maximum/minimum sample rate required for the given resolution, frequency,
        ///  and conversion mode.
        /// </summary>
        /// <param name="resolution">resolution selected</param>
        /// <param name="frequency">Frequency calculated</param>
        /// <param name="conversionMode">Conversion mode selected</param>
        /// <param name="maximum">Maximum sample rate</param>
        /// <returns>Desired sample rate</returns>
        static public uint GetSampleRate(uint resolution, float frequency, CyEConversionMode conversionMode, 
                                         bool maximum)
        {
            uint sampleRate;
            uint clocksPerSample;

            clocksPerSample = ClocksPerSample(resolution, conversionMode);

            if (maximum)
            {
                sampleRate = (uint)(frequency / clocksPerSample);
            }
            else
            {
                sampleRate = (uint)Math.Ceiling(frequency / clocksPerSample);
            }

            return sampleRate;
        }


        /// <summary>
        /// Calculates how may ADC clocks are required per sample
        /// </summary>
        /// <param name="resolution">Resolution between 8 and 20</param>
        /// <param name="conversionMode">Mode of operation</param>
        /// <returns>Clocks required for a single sample.</returns>
        static public uint ClocksPerSample(uint resolution, CyEConversionMode conversionMode)
        {
            uint resIndex;
            uint clocksPerSample = 0;

            // Make sure resolution in not out of range.
            if (resolution < Cyrc.MIN_RESOLUTION)
            {
                resolution = Cyrc.MIN_RESOLUTION;
            }

            if (resolution > Cyrc.MAX_RESOLUTION)
            {
                resolution = Cyrc.MAX_RESOLUTION;
            }

            resIndex = resolution - Cyrc.MIN_RESOLUTION;
            switch (conversionMode)
            {
                case CyEConversionMode.Single_Sample:
                    if (resolution <= 16)
                    {
                        clocksPerSample = (((CyresSettings.dr1[resIndex] + 1) * 4) + 3) 
                            + (CyresSettings.gval[resIndex] + 1 + 1) + 4;
                    }
                    else
                    {
                        clocksPerSample = (CyresSettings.dr1[resIndex] + 1) * ((CyresSettings.dr2[resIndex] + 1) + 3)
                            + (CyresSettings.gval[resIndex] + 1 + 2) + 1 + 6;
                    }
                    break;

                case CyEConversionMode.Fast_Filter:
                    clocksPerSample = (((CyresSettings.dr1[resIndex] + 1) * 4) + 3) * (CyresSettings.dr2[resIndex] + 1);
                    break;

                case  CyEConversionMode.Continuous:
                    clocksPerSample = (CyresSettings.dr1[resIndex] + 1) * (CyresSettings.dr2[resIndex] + 1);
                    break;

                case CyEConversionMode.Fast_FIR:
                    if (resolution <= 16)
                    {
                        clocksPerSample = ((CyresSettings.dr1[resIndex] + 1) * 4 + 3)
                            + (CyresSettings.gval[resIndex] + 1 + 2) + 2;
                    }
                    else
                    {
                        clocksPerSample = (CyresSettings.dr1[resIndex] + 1) * ((CyresSettings.dr2[resIndex] + 1) + 3)
                            + (CyresSettings.gval[resIndex] + 1 + 1) + 1 + 6;
                    }
                    break;

                default:
                    Debug.Assert(false);
                    break;
            };

            return clocksPerSample;
        }

        /// <summary>
        /// Calculates the clocks per volt scale factor for the voltage conversion functions.
        /// </summary>
        /// <param name="resolution">Resolution between 8 and 20 </param>
        /// <param name="inputRange">input range selected</param>
        /// <param name="refVoltage">refVoltage set in the customizer</param>
        /// <param name="config">configuration selected</param>
        /// <param name="vdda">Vdda value set in the DWR file</param>
        /// <returns>Counts per Volt</returns>
        static public uint CalcCountsPerVolt(uint resolution, uint inputRange, float refVoltage, float vdda, uint gain)
        {
            float countsPerVolt;
            uint counts = 1;
            uint i;

            // Raise counts to the 2^resolution
            for (i = 0; i < resolution; i++)
            {
                counts *= 2;
            }

            switch (inputRange)
            {
                case Cyrc.ADC_IR_VSSA_TO_VREF:  // Vssa to Vref
                    countsPerVolt = counts / refVoltage;
                    break;

                case Cyrc.ADC_IR_VSSA_TO_2VREF:   // Vssa to 2*Vref
                    countsPerVolt = counts / (refVoltage * 2);
                    break;

                case Cyrc.ADC_IR_VSSA_TO_6VREF:   // Vssa to 6*Vref
                    countsPerVolt = counts / (refVoltage * 6);
                    break;

                case Cyrc.ADC_IR_VSSA_TO_VDDA:   // Vssa to Vdda
                    countsPerVolt = counts / vdda;
                    break;

                case Cyrc.ADC_IR_VNEG_VREF_DIFF:   // -Vin +/- Vref (Diff)
                    countsPerVolt = counts / (refVoltage * 2);
                    break;

                case Cyrc.ADC_IR_VNEG_2VREF_DIFF:  // -Vin +/- 2*Vref (Diff)
                    countsPerVolt = counts / (refVoltage * 4);
                    break;

                case Cyrc.ADC_IR_VNEG_6VREF_DIFF:  // -Vin +/- 6*Vref (Diff)
                    countsPerVolt = counts / (refVoltage * 12);
                    break;

                case Cyrc.ADC_IR_VNEG_VREF_2_DIFF:  // -Vin +/- 0.5Vref (Diff)
                    countsPerVolt = (counts * 2) / (refVoltage * 2);
                    break;

                case Cyrc.ADC_IR_VNEG_VREF_4_DIFF:  // -Vin +/- 0.25Vref (Diff)
                    countsPerVolt = (counts * 4) / (refVoltage * 2);
                    break;

                case Cyrc.ADC_IR_VNEG_VREF_8_DIFF:  // -Vin +/- 0.125Vref (Diff)
                    countsPerVolt = (counts * 8) / (refVoltage * 2);
                    break;

                case Cyrc.ADC_IR_VNEG_VREF_16_DIFF:  // -Vin +/- 0.0625Vref (Diff)
                    countsPerVolt = (counts * 16) / (refVoltage * 2);
                    break;

                default:
                    countsPerVolt = (counts * 2) / refVoltage;
                    break;
            };

            return Convert.ToUInt32(countsPerVolt);
        }

        /// <summary>
        /// Calculates the frequency required for the external charge pump clock
        /// </summary>
        /// <param name="resolution">adcClockFrequency calculated</param>
        /// <returns>Desired Charge pump clock frequency.</returns>
        static public uint GetChargePumpClock(uint adcClockFrequency)
        {
            return 4 * adcClockFrequency;
        }

        /// <summary>
        /// Calculate all register values.
        /// </summary>
        /// <param name="paramDict"></param>
        /// <param name="isPSOC3"></param>
        /// <param name="vdda"></param>
        void CalcValues(ref Dictionary<string, string> paramDict, float vdda)
        {
            byte i = 1;
            uint[] clockFrequency = new uint[4] { 0, 0, 0, 0 };
            uint[] cpClockFrequency = new uint[4] { 0, 0, 0, 0 };
            uint[] clocksPerCycle = new uint[4] { 0, 0, 0, 0 };

            ICyDesignQuery_v1 desquery = m_instQuery.DesignQuery;

            // Read all the parameters, since register values are based on them.
            ADC_Clock = (uint)m_params.ClockSourceType;
            ADC_Input_Mode = (uint)m_params.InputModeType;
            Start_of_Conversion = m_params.UseTriggeredSamplingMode ? 
                (byte)CyESamplingMode.Hardware : (byte)CyESamplingMode.Software;
            ADC_ChargePump = m_params.LowPowerChargePump ? 1u : 0u;

            DsmMiscReg = Cyrc.DSM_SEL_ECLK_CP;
            DsmClkReg |= (Cyrc.DSM_CLK_BYPASS_SYNC | Cyrc.DSM_CLK_CLK_EN);
            DsmRef1Reg = 0x00;

            if (m_params.EnableVrefVssa)
            {
                DsmRef1Reg = Cyrc.DSM_DAC_GND_SEL_EXT;
            }
            // Add code Here
            paramDict.Add(DSM_MISC_ParamName, FormatHex1B(DsmMiscReg));
            paramDict.Add(DSM_CLK_ParamName, FormatHex1B(DsmClkReg));
            paramDict.Add(DSM_REF1_ParamName, FormatHex1B(DsmRef1Reg));

            for (i = 0; i < Cyrc.MAX_CONFIGS; i++)
            {
                ADC_Input_Range[i] = (uint)m_params.GetInputRange((byte)(i + 1));
                ADC_Reference[i] = (uint)m_params.GetReference((byte)(i + 1));
                ADC_Resolution[i] = (uint)m_params.GetResolution((byte)(i + 1));
                Conversion_Mode[i] = m_params.GetConversionMode((byte)(i + 1));
                Input_Buffer_Mode[i] = m_params.GetBufferMode((byte)(i + 1));
                Input_Buffer_Gain[i] = (uint)m_params.GetBufferGain((byte)(i + 1));
                Sample_Rate[i] = (uint)m_params.GetScanRate((byte)(i + 1));
                Alignment[i] = m_params.GetAlignment((byte)(i + 1));
                Ref_Voltage[i] = (float)m_params.GetVrefValue((byte)(i + 1));
                
                if (Input_Buffer_Mode[i] == CyEBufferMode.Bypass_Buffer)
                {
                    Input_Buffer_Gain[i] = 1;
                }

                if (ADC_Input_Range[i] == Cyrc.ADC_IR_VSSA_TO_VDDA)
                {
                    if (vdda < CyParamRanges.MAX_VDDA3_VALUE)
                    {
                        Ref_Voltage[i] = vdda / 3;
                    }
                    else
                    {
                        Ref_Voltage[i] = vdda / 4;
                    }
                }
                else
                {
                    if ((ADC_Reference[i] == Cyrc.ADC_INT_REF_VDDA_3) ||
                        (ADC_Reference[i] == Cyrc.ADC_INT_REF_VDDA_3_BYPASSED_ON_P03) ||
                        (ADC_Reference[i] == Cyrc.ADC_INT_REF_VDDA_3_BYPASSED_ON_P32))
                    {
                        Ref_Voltage[i] = vdda / 3;
                    }
                    else if ((ADC_Reference[i] == Cyrc.ADC_INT_REF_VDDA_4) ||
                             (ADC_Reference[i] == Cyrc.ADC_INT_REF_VDDA_4_BYPASSED_ON_P03) ||
                             (ADC_Reference[i] == Cyrc.ADC_INT_REF_VDDA_4_BYPASSED_ON_P32))
                    {
                        Ref_Voltage[i] = vdda / 4;
                    }
                }

                // First, setup the default settings.
                //   DecCrReg    See below
                DecSrReg[i] = Cyrc.DEC_INTR_PULSE | Cyrc.DEC_INTR_CLEAR;
                DecOcorReg[i] = 0x00;
                DecOcormReg[i] = 0x00;
                DecOcorhReg[i] = 0x00;

                DecCoherReg[i] = Cyrc.DEC_SAMP_KEY_LOW;
                DsmCr0Reg[i] = Cyrc.DSM_QLEV_9 | Cyrc.DSM_NONOV_HIGH;
                DsmCr1Reg[i] = 0x00;
                // Chop freq must be higher than Decimation rate. (Divider lower) 
                DsmCr2Reg[i] = (Cyrc.DSM_MOD_CHOP_EN | Cyrc.DSM_FCHOP_DIV8) | Cyrc.DSM_RESET1_EN |
                                Cyrc.DSM_RESET2_EN | Cyrc.DSM_RESET3_EN;
                DsmCr3Reg[i] = 0x00;
                DsmCr13Reg[i] = 0x00;
                DsmRef0Reg[i] = Cyrc.DSM_VCMSEL_0_8V | Cyrc.DSM_REFMUX_1_024V;
                DsmRef2Reg[i] = 0x00;
                DsmRef3Reg[i] = 0x00;
                
                DsmDem0Reg[i] = Cyrc.DSM_EN_DEM;
                DsmDem1Reg[i] = 0x00;
                DsmBuf0Reg[i] = Cyrc.DSM_ENABLE_P | Cyrc.DSM_RAIL_RAIL_EN;
                DsmBuf1Reg[i] = Cyrc.DSM_ENABLE_N | (Input_Buffer_Gain[i] << 2);
                DsmBuf2Reg[i] = 0x00;
                DsmBuf3Reg[i] = 0x00;
                DsmOut0Reg[i] = 0;
                DsmOut1Reg[i] = 0;
                DecGvalReg[i] = 0x00;

                // GVAL reg setting based on Resolution 
                if (ADC_Resolution[i] > 13)
                {
                    DecGvalReg[i] = Cyrc.DEC_GVAL_MAX;
                }
                else
                {
                    DecGvalReg[i] = (ADC_Resolution[i] + 1);
                }

                clockFrequency[i] = SetClock(ADC_Resolution[i], Sample_Rate[i], Conversion_Mode[i]);
                cpClockFrequency[i] = GetChargePumpClock(clockFrequency[i]);

                // Clock dividers
                double masterClockFreq = m_params.GetMasterClockInHz();
                bool isMasterClockFrequencyKnown = CyParameters.IsFrequencyKnown(masterClockFreq);
                uint minRate, maxRate;
                double maxFreq, minFreq;
                m_params.GetMinMaxClockFreqSampleRate(i, out minFreq, out maxFreq, out minRate, out maxRate);
                if (isMasterClockFrequencyKnown)
                {
                    AdcClockDivider[i] = SetClockDivider(clockFrequency[i], (float)minFreq, (float)maxFreq, i);
                    CpClockDivider[i] = SetClockDivider(cpClockFrequency[i], Cyrc.MINCHARGEPUMPCLOCK,
                                                         Cyrc.MAXCHARGEPUMPCLOCK, i);
                }
                // Setup cap settings.
                if (ADC_Resolution[i] > 15)    // 16 to 20 bit Resolution
                {
                    DsmCr4Reg[i] = Cyrc.FCap1_16_20;
                    DsmCr8Reg[i] = Cyrc.IPCap2_FCap2_16_20;
                    DsmCr9Reg[i] = Cyrc.IPCap3_FCap3_16_20;
                    DsmCr10Reg[i] = Cyrc.SumCap12_16_20[ADC_Input_Range[i]];
                    DsmCr11Reg[i] = Cyrc.SumCap3Fb_16_20[ADC_Input_Range[i]];
                    DsmCr12Reg[i] = Cyrc.SumCapin16_20[ADC_Input_Range[i]];

                    if ((vdda < CyParamRanges.MAX_VDDA3_VALUE) && (ADC_Input_Range[i] == Cyrc.ADC_IR_VSSA_TO_VDDA))
                    {
                        DsmCr5Reg[i] = Cyrc.IpCap1_16_20_Vdda_3;
                        DsmCr6Reg[i] = Cyrc.DacCap_16_20_Vdda_3;
                    }
                    else
                    {
                        DsmCr5Reg[i] = Cyrc.IpCap1_16_20[ADC_Input_Range[i]];
                        DsmCr6Reg[i] = Cyrc.DacCap_16_20[ADC_Input_Range[i]];
                    }
                    DsmCr7Reg[i] = Cyrc.CapOffset_16_20[ADC_Input_Range[i]];

                    // Power settings 
                    if ((Cyrc.MAX_FREQ_16_20_BITS[ADC_Input_Range[i]] / 4) <= clockFrequency[i]) // HP
                    {
                        DsmCr14Reg[i] = Cyrc.DSM_POWER1_2 | Cyrc.DSM_OPAMP1_BW_0;
                        DsmCr15Reg[i] = Cyrc.DSM_POWER_NORMAL | Cyrc.DSM_POWER2_3_HIGH;
                        DsmCr16Reg[i] = Cyrc.DSM_POWER_SUM_HIGH | Cyrc.DSM_CP_PWRCTL_TURBO;
                        DsmCr17Reg[i] = Cyrc.DSM_EN_BUF_VCM | Cyrc.DSM_PWR_CTRL_VREF_2 | Cyrc.DSM_PWR_CTRL_VCM_2 |
                                         Cyrc.DSM_PWR_CTRL_VREF_INN_3;
                        DsmBuf2Reg[i] &= ~Cyrc.DSM_LOWPOWER_EN;
                    }
                    else if ((Cyrc.MAX_FREQ_16_20_BITS[ADC_Input_Range[i]] / 16) <= clockFrequency[i]) // MP
                    {
                        DsmCr14Reg[i] = Cyrc.DSM_POWER1_1 | Cyrc.DSM_OPAMP1_BW_0;
                        DsmCr15Reg[i] = Cyrc.DSM_POWER_NORMAL | Cyrc.DSM_POWER2_3_MED;
                        DsmCr16Reg[i] = Cyrc.DSM_POWER_SUM_MED | Cyrc.DSM_CP_PWRCTL_2X;
                        DsmCr17Reg[i] = Cyrc.DSM_EN_BUF_VCM | Cyrc.DSM_PWR_CTRL_VREF_1 | Cyrc.DSM_PWR_CTRL_VCM_1 |
                                        Cyrc.DSM_PWR_CTRL_VREF_INN_2;
//                        if(Input_Buffer_Gain[i] == 1) /* Do not use low power mode for Gain > 1 */
//                        {
//                            DsmBuf2Reg[i] |= Cyrc.DSM_LOWPOWER_EN;
//                        }    
                    }
                    else // LP
                    {
                        DsmCr14Reg[i] = Cyrc.DSM_POWER1_0 | Cyrc.DSM_OPAMP1_BW_0;
                        DsmCr15Reg[i] = Cyrc.DSM_POWER_VERYLOW | Cyrc.DSM_POWER2_3_LOW;
                        DsmCr16Reg[i] = Cyrc.DSM_POWER_SUM_LOW | Cyrc.DSM_CP_PWRCTL_HIGH;
                        DsmCr17Reg[i] = Cyrc.DSM_EN_BUF_VCM | Cyrc.DSM_PWR_CTRL_VREF_0 | Cyrc.DSM_PWR_CTRL_VCM_0 |
                                        Cyrc.DSM_PWR_CTRL_VREF_INN_1;
                       
                        //DsmBuf2Reg[i] |= Cyrc.DSM_LOWPOWER_EN;
                    }
                }
                else   // 8 to 15 bit resolution
                {
                    DsmCr4Reg[i] = Cyrc.FCap1_8_15;
                    DsmCr8Reg[i] = Cyrc.IPCap2_FCap2_8_15;
                    DsmCr9Reg[i] = Cyrc.IPCap3_FCap3_8_15;
                    DsmCr10Reg[i] = Cyrc.SumCap12_8_15[ADC_Input_Range[i]];
                    DsmCr11Reg[i] = Cyrc.SumCap3Fb_8_15[ADC_Input_Range[i]];
                    DsmCr12Reg[i] = Cyrc.SumCapin8_15[ADC_Input_Range[i]];
                    if ((vdda < CyParamRanges.MAX_VDDA3_VALUE) && (ADC_Input_Range[i] == Cyrc.ADC_IR_VSSA_TO_VDDA))
                    {
                        DsmCr5Reg[i] = Cyrc.IpCap1_8_15_Vdda_3;
                        DsmCr6Reg[i] = Cyrc.DacCap_8_15_Vdda_3;
                    }
                    else
                    {
                        DsmCr5Reg[i] = Cyrc.IpCap1_8_15[ADC_Input_Range[i]];
                        DsmCr6Reg[i] = Cyrc.DacCap_8_15[ADC_Input_Range[i]];
                    }
                    DsmCr7Reg[i] = 0x00;

                    // Power settings 
                    if ((Cyrc.MAX_FREQ_8_15_BITS[ADC_Input_Range[i]] / 4) <= clockFrequency[i]) // HP
                    {
                        DsmCr14Reg[i] = Cyrc.DSM_POWER1_2 | Cyrc.DSM_OPAMP1_BW_0;
                        DsmCr15Reg[i] = Cyrc.DSM_POWER_6MHZ | Cyrc.DSM_POWER2_3_HIGH;
                        DsmCr16Reg[i] = Cyrc.DSM_POWER_SUM_HIGH | Cyrc.DSM_CP_PWRCTL_TURBO;
                        DsmCr17Reg[i] = Cyrc.DSM_EN_BUF_VCM | Cyrc.DSM_PWR_CTRL_VREF_2 | Cyrc.DSM_PWR_CTRL_VCM_2 |
                                        Cyrc.DSM_PWR_CTRL_VREF_INN_3;
                        DsmBuf2Reg[i] &= ~Cyrc.DSM_LOWPOWER_EN;
                    }
                    else if ((Cyrc.MAX_FREQ_8_15_BITS[ADC_Input_Range[i]] / 16) <= clockFrequency[i]) // MP
                    {
                        DsmCr14Reg[i] = Cyrc.DSM_POWER1_1 | Cyrc.DSM_OPAMP1_BW_0;
                        DsmCr15Reg[i] = Cyrc.DSM_POWER_NORMAL | Cyrc.DSM_POWER2_3_MED;
                        DsmCr16Reg[i] = Cyrc.DSM_POWER_SUM_MED | Cyrc.DSM_CP_PWRCTL_2X;
                        DsmCr17Reg[i] = Cyrc.DSM_EN_BUF_VCM | Cyrc.DSM_PWR_CTRL_VREF_1 | Cyrc.DSM_PWR_CTRL_VCM_1 |
                                        Cyrc.DSM_PWR_CTRL_VREF_INN_2;
//                        if(Input_Buffer_Gain[i] == 1) // Do not use low power mode for Gain > 1 
//                        {
//                            DsmBuf2Reg[i] |= Cyrc.DSM_LOWPOWER_EN;
//                        }    
                    }
                    else // LP
                    {
                        DsmCr14Reg[i] = Cyrc.DSM_POWER1_0 | Cyrc.DSM_OPAMP1_BW_0;
                        DsmCr15Reg[i] = Cyrc.DSM_POWER_VERYLOW | Cyrc.DSM_POWER2_3_LOW;
                        DsmCr16Reg[i] = Cyrc.DSM_POWER_SUM_LOW | Cyrc.DSM_CP_PWRCTL_HIGH;
                        DsmCr17Reg[i] = Cyrc.DSM_EN_BUF_VCM | Cyrc.DSM_PWR_CTRL_VREF_0 | Cyrc.DSM_PWR_CTRL_VCM_0 |
                                        Cyrc.DSM_PWR_CTRL_VREF_INN_1;
                        
                       // DsmBuf2Reg[i] |= Cyrc.DSM_LOWPOWER_EN;
                    }
                }
               
                SetResolution(ADC_Resolution[i], ADC_Input_Range[i], Alignment[i], i);
                SetBufferMode(Input_Buffer_Mode[i], i);
                if (Input_Buffer_Mode[i] != CyEBufferMode.Bypass_Buffer)
                {
                    SetBufferGain(Input_Buffer_Gain[i], i);
                }
                SetInputRange(ADC_Input_Range[i], Ref_Voltage[i], i, vdda);
                SetRef(ADC_Reference[i], ADC_Input_Range[i], i, vdda);

                // If the second decimator is not used, don't turn on the FIR filter
                if ((DecDr2Reg[i] == 0) && (DecDr2hReg[i] == 0))
                {
                    DecCrReg[i] = ((uint)Conversion_Mode[i] << 2) | (Start_of_Conversion << 1) | Cyrc.DEC_OCOR_EN |
                                   Cyrc.DEC_GCOR_EN;
                }
                else
                {
                    DecCrReg[i] = ((uint)Conversion_Mode[i] << 2) | (Start_of_Conversion << 1) | Cyrc.DEC_FIR_EN |
                                   Cyrc.DEC_OCOR_EN | Cyrc.DEC_GCOR_EN;
                    // To check whether Conversion mode is Single sample with resolution > 16 
                    if ((DecCrReg[i] & 0x0C) == 0x00)
                    {
                        DecCrReg[i] |= ((uint)CyEConversionMode.Fast_FIR << 2);
                    }
                }
                if ((Alignment[i] == CyEAlignment.Left_OVF_Protected) && (ADC_Resolution[i] >= 16))
                {
                    // enable overflow protection for 24 bits OVF Protected mode
                    DecCrReg[i] |= Cyrc.DEC_SAT_EN;
                }    
                else if (Alignment[i] != CyEAlignment.Right) 
                { // When result is 16 bits, the "of_width" (Over Flow Width) should
                  //  be wet to 16 to limit positive overflows.
                }

                CountsPerVolt[i] = CalcCountsPerVolt(ADC_Resolution[i], ADC_Input_Range[i], Ref_Voltage[i], vdda,
                                                     Input_Buffer_Gain[i]);
                clocksPerCycle[i] = ClocksPerSample(ADC_Resolution[i], Conversion_Mode[i]);

                // Write out the register constants
                paramDict.Add(DEC_CR_ParamName[i], FormatHex1B(DecCrReg[i]));
                paramDict.Add(DEC_SR_ParamName[i], FormatHex1B(DecSrReg[i]));
                paramDict.Add(DEC_SHIFT1_ParamName[i], FormatHex1B(DecShift1Reg[i]));
                paramDict.Add(DEC_SHIFT2_ParamName[i], FormatHex1B(DecShift2Reg[i]));
                paramDict.Add(DEC_DR2_ParamName[i], FormatHex1B(DecDr2Reg[i]));
                paramDict.Add(DEC_DR2H_ParamName[i], FormatHex1B(DecDr2hReg[i]));
                paramDict.Add(DEC_DR1_ParamName[i], FormatHex1B(DecDr1Reg[i]));

                paramDict.Add(DEC_OCOR_ParamName[i], FormatHex1B(DecOcorReg[i]));
                paramDict.Add(DEC_OCORM_ParamName[i], FormatHex1B(DecOcormReg[i]));
                paramDict.Add(DEC_OCORH_ParamName[i], FormatHex1B(DecOcorhReg[i]));

                paramDict.Add(DEC_COHER_ParamName[i], FormatHex1B(DecCoherReg[i]));
                paramDict.Add(DSM_CR0_ParamName[i], FormatHex1B(DsmCr0Reg[i]));
                paramDict.Add(DSM_CR1_ParamName[i], FormatHex1B(DsmCr1Reg[i]));
                paramDict.Add(DSM_CR2_ParamName[i], FormatHex1B(DsmCr2Reg[i]));
                paramDict.Add(DSM_CR3_ParamName[i], FormatHex1B(DsmCr3Reg[i]));
                paramDict.Add(DSM_CR4_ParamName[i], FormatHex1B(DsmCr4Reg[i]));
                paramDict.Add(DSM_CR5_ParamName[i], FormatHex1B(DsmCr5Reg[i]));
                paramDict.Add(DSM_CR6_ParamName[i], FormatHex1B(DsmCr6Reg[i]));
                paramDict.Add(DSM_CR7_ParamName[i], FormatHex1B(DsmCr7Reg[i]));
                paramDict.Add(DSM_CR8_ParamName[i], FormatHex1B(DsmCr8Reg[i]));
                paramDict.Add(DSM_CR9_ParamName[i], FormatHex1B(DsmCr9Reg[i]));
                paramDict.Add(DSM_CR10_ParamName[i], FormatHex1B(DsmCr10Reg[i]));
                paramDict.Add(DSM_CR11_ParamName[i], FormatHex1B(DsmCr11Reg[i]));
                paramDict.Add(DSM_CR12_ParamName[i], FormatHex1B(DsmCr12Reg[i]));
                paramDict.Add(DSM_CR13_ParamName[i], FormatHex1B(DsmCr13Reg[i]));
                paramDict.Add(DSM_CR14_ParamName[i], FormatHex1B(DsmCr14Reg[i]));
                paramDict.Add(DSM_CR15_ParamName[i], FormatHex1B(DsmCr15Reg[i]));
                paramDict.Add(DSM_CR16_ParamName[i], FormatHex1B(DsmCr16Reg[i]));
                paramDict.Add(DSM_CR17_ParamName[i], FormatHex1B(DsmCr17Reg[i]));

                paramDict.Add(DSM_REF0_ParamName[i], FormatHex1B(DsmRef0Reg[i]));
                paramDict.Add(DSM_REF2_ParamName[i], FormatHex1B(DsmRef2Reg[i]));
                paramDict.Add(DSM_REF3_ParamName[i], FormatHex1B(DsmRef3Reg[i]));

                paramDict.Add(DSM_DEM0_ParamName[i], FormatHex1B(DsmDem0Reg[i]));
                paramDict.Add(DSM_DEM1_ParamName[i], FormatHex1B(DsmDem1Reg[i]));

                paramDict.Add(DSM_BUF0_ParamName[i], FormatHex1B(DsmBuf0Reg[i]));
                paramDict.Add(DSM_BUF1_ParamName[i], FormatHex1B(DsmBuf1Reg[i]));
                paramDict.Add(DSM_BUF2_ParamName[i], FormatHex1B(DsmBuf2Reg[i]));
                paramDict.Add(DSM_BUF3_ParamName[i], FormatHex1B(DsmBuf3Reg[i]));
                paramDict.Add(DSM_OUT0_ParamName[i], FormatHex1B(DsmOut0Reg[i]));
                paramDict.Add(DSM_OUT1_ParamName[i], FormatHex1B(DsmOut1Reg[i]));

                paramDict.Add(DSM_SW3_ParamName[i], FormatHex1B(DsmSw3Reg[i]));
                paramDict.Add(DEC_GVAL_ParamName[i], FormatHex1B(DecGvalReg[i]));
                paramDict.Add(DEC_GCOR_ParamName[i], FormatHex1B(DecGcorReg[i]));
                paramDict.Add(DEC_GCORH_ParamName[i], FormatHex1B(DecGcorhReg[i]));

                // Voltage conversion defaults
                paramDict.Add(RefVoltage_ParamName[i], Ref_Voltage[i].ToString("0.0000"));
                paramDict.Add(CountsPerVoltParamName[i], CountsPerVolt[i].ToString());
                paramDict.Add(adcClockFrequency_ParamName[i], clockFrequency[i].ToString());
                paramDict.Add(chargePumpClockFrequency_ParamName[i], cpClockFrequency[i].ToString());
                paramDict.Add(clocksPerSample_ParamName[i], FormatHex2B(clocksPerCycle[i]));
                paramDict.Add(adcClockDivider_ParamName[i], AdcClockDivider[i].ToString());
                paramDict.Add(cpClockDivider_ParamName[i], CpClockDivider[i].ToString());
                paramDict.Add(IdealDecGain_ParamName[i], FormatHex2B(Ideal_Dec_Gain[i]));
                paramDict.Add(IdealOddDecGain_ParamName[i], FormatHex2B(Ideal_OddDec_Gain[i]));
                paramDict.Add(IPCap1Value_ParamName[i], FormatHex2B(IPCap1Value[i]));
                paramDict.Add(DACCapValue_ParamName[i], FormatHex2B(DACCapValue[i]));

                // Input mode and input range values 
                paramDict.Add(CyParamNames.InputModeName((byte)(i + 1)), ADC_Input_ModeValue[i].ToString() +"u");
                paramDict.Add(CyParamNames.InputRangeValueName((byte)(i + 1)), ADC_Input_RangeValue[i].ToString());

                // Alignment
                paramDict.Add(leftBitShift_ParamName[i], LeftBitShift[i].ToString());
            }
        }

        /// <summary>
        /// Converts uint to hex string
        /// </summary>
        private string FormatHex1B(uint value)
        {
            return String.Format("0x{0:X2}u", value);
        }
        private string FormatHex2B(uint value)
        {
            return String.Format("0x{0:X4}u", value);
        }
    }
}
