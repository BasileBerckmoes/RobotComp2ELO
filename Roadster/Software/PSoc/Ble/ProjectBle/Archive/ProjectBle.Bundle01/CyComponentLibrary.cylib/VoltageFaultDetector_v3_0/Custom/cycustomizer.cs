/*******************************************************************************
* Copyright 2012 - 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Windows.Forms;
using System.Drawing;
using System.Diagnostics;

namespace VoltageFaultDetector_v3_0
{
    public partial class CyCustomizer : ICyParamEditHook_v1, ICyAPICustomize_v1, ICyShapeCustomize_v1,
                                        ICyDRCProvider_v1
    {
        public const string BASIC_TAB_NAME = "General";
        public const string VOLTAGE_TAB_NAME = "Voltages";
        public const string BUILTIN_TAB_NAME = "Built-in";

        #region ICyParamEditHook_v1 Members
        DialogResult ICyParamEditHook_v1.EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery,
            ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit, termQuery);
            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            CyBasicTab basicTab = new CyBasicTab(parameters);
            CyVoltagesTab voltagesTab = new CyVoltagesTab(parameters);            
            CyParamExprDelegate exprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                basicTab.UpdateUI();
                parameters.GlobalEditMode = true;
            };

            editor.AddCustomPage(Resources.GeneralTabDisplayName, basicTab, exprDelegate, BASIC_TAB_NAME);
            editor.AddCustomPage(Resources.VoltagesTabDisplayName, voltagesTab, exprDelegate, VOLTAGE_TAB_NAME);
            editor.AddDefaultPage(BUILTIN_TAB_NAME, BUILTIN_TAB_NAME);

            edit.NotifyWhenDesignUpdates(new CyDesignUpdated_v1(parameters.UpdateClock));

            basicTab.UpdateUI();
            parameters.GlobalEditMode = true;
            CyEditingWrapperControl.m_runMode = true;

            return editor.ShowDialog();
        }

        bool ICyParamEditHook_v1.EditParamsOnDrop
        {
            get { return false; }
        }

        bool UseBigEditor
        {
            get { return true; }
        }

        CyCompDevParamEditorMode ICyParamEditHook_v1.GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }
        #endregion

        #region ICyShapeCustomize_v1 Members
        public CyCustErr CustomizeShapes(ICyInstQuery_v1 instQuery, ICySymbolShapeEdit_v1 shapeEdit,
            ICyTerminalEdit_v1 termEdit)
        {
            const string BODY_SHAPE = "VFD_body";
            const string GENERATED_SHAPE = "VFD_body_gen";

            CyCustErr err = CyCustErr.OK;

            RectangleF bodyRect = shapeEdit.GetShapeBounds(BODY_SHAPE);
            err = shapeEdit.ShapesRemove(BODY_SHAPE);
            if (err.IsNotOk) return err;

            byte numVoltages = 0;
            err = instQuery.GetCommittedParam(CyParamNames.NUM_VOLTAGES).TryGetValueAs<byte>(out numVoltages);
            if (err.IsNotOk) return err;

            float offset = 12.0F;
            PointF bodyLoc = bodyRect.Location;
            float bodyWidth = bodyRect.Width;
            float basicBodyHeight = offset * 5F;
            float realBodyHeight = (basicBodyHeight + (numVoltages * offset));

            err = shapeEdit.CreateRectangle(new string[] { GENERATED_SHAPE }, bodyLoc, bodyWidth, realBodyHeight);
            if (err.IsNotOk) return err;

            // Set the color and outline width of symbol body
            err = shapeEdit.SetFillColor(GENERATED_SHAPE, Color.Gainsboro);
            if (err.IsNotOk) return err;
            err = shapeEdit.SetOutlineWidth(GENERATED_SHAPE, 1F);
            if (err.IsNotOk) return err;

            err = shapeEdit.SendToBack(GENERATED_SHAPE);
            if (err.IsNotOk) return err;

            return err;
        }
        #endregion

        #region ICyAPICustomize_v1 Members
        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery,
            IEnumerable<CyAPICustomizer> apis)
        {
            CyParameters parameters = new CyParameters(query);
            
            List<CyAPICustomizer> inputCustomizers = new List<CyAPICustomizer>(apis);
            Dictionary<string, string> paramDict = new Dictionary<string, string>();
            List<CyAPICustomizer> outputCustomizers = FilterAPI(inputCustomizers, parameters);

            if (inputCustomizers.Count > 0) 
                paramDict = inputCustomizers[0].MacroDictionary;                                   

            string element = string.Empty;
            double dacRange = (parameters.DACRange == CyDACRangeType.V1) ? CyParamRanges.DAC_1V_VOLTAGE : 
                                                                           CyParamRanges.DAC_4V_VOLTAGE;
            
            // Voltages declarations
            string uvFaultThreshold = "uint8 " + parameters.InstanceName + "_UVFaultThreshold[] = {\r\n    ";
            string ovFaultThreshold = "uint8 " + parameters.InstanceName + "_OVFaultThreshold[] = {\r\n    ";
            string uvFaultThresholdInit = "const uint16 CYCODE " + parameters.InstanceName + "_initUVFaultThreshold[] = {\r\n    ";
            string ovFaultThresholdInit = "const uint16 CYCODE " + parameters.InstanceName + "_initOVFaultThreshold[] = {\r\n    ";
            string voltageScale = "const uint16 CYCODE " + parameters.InstanceName + "_VoltageScale[] = {\r\n    ";

            for (int i = parameters.VoltagesTable.Count - 1; i >= 0; i--)
            {
                double mult = dacRange;
                double? scalingFactor;
                double? uvFaultThresholdValue;
                double? ovFaultThresholdValue;

                scalingFactor = CyParameters.TrimToMilliVolts(parameters.VoltagesTable[i].InputScalingFactor.Value);
                uvFaultThresholdValue = CyParameters.TrimToMilliVolts(parameters.VoltagesTable[i].UvFaultThreshold);
                ovFaultThresholdValue = CyParameters.TrimToMilliVolts(parameters.VoltagesTable[i].OvFaultThreshold);

                if (scalingFactor.HasValue)
                {
                    mult /= scalingFactor.Value;
                }

                uvFaultThreshold += ConvertValueToArrayElement(uvFaultThresholdValue, i,
                    parameters.VoltagesTable.Count, false, mult);

                ovFaultThreshold += ConvertValueToArrayElement(ovFaultThresholdValue, i,
                    parameters.VoltagesTable.Count, false, mult);

                mult = 1;

                voltageScale += ConvertValueToArrayElement(scalingFactor, i,
                    parameters.VoltagesTable.Count, true, mult);

                if (scalingFactor.HasValue)
                {
                    mult = scalingFactor.Value;
                }

                uvFaultThresholdInit += ConvertValueToArrayElement(uvFaultThresholdValue, i,
                    parameters.VoltagesTable.Count, true, mult);

                ovFaultThresholdInit += ConvertValueToArrayElement(ovFaultThresholdValue, i,
                    parameters.VoltagesTable.Count, true, mult);
            }

            // Voltages table arrays
            if (parameters.ExternalRef == false)
            {
                if (parameters.CompareType != CyCompareType.OV)
                {
                    paramDict.Add(CyParamNames.API_UV_FAULT_THRESHOLD, uvFaultThreshold);
                    paramDict.Add(CyParamNames.API_UV_FAULT_THRESHOLD_INIT, uvFaultThresholdInit);
                }
                if (parameters.CompareType != CyCompareType.UV)
                {
                    paramDict.Add(CyParamNames.API_OV_FAULT_THRESHOLD, ovFaultThreshold);
                    paramDict.Add(CyParamNames.API_OV_FAULT_THRESHOLD_INIT, ovFaultThresholdInit);
                }
                paramDict.Add(CyParamNames.API_VOLTAGE_SCALE, voltageScale);
            }

            const string DAC_MV_PER_LSB_1V_RANGE = "4";
            const string DAC_MV_PER_LSB_4V_RANGE = "16";
            const string DAC_SHIFTS_LSB_1V_RANGE = "2";
            const string DAC_SHIFTS_LSB_4V_RANGE = "4";

            string compTypeReplStr = (parameters.CompareType == CyCompareType.OV) ? "OV" : "UV";
            paramDict.Add(CyParamNames.API_COMP_TYPE_REPL_STR, compTypeReplStr);
            string dacmVperLSb = (parameters.DACRange == CyDACRangeType.V1) ? 
                DAC_MV_PER_LSB_1V_RANGE : DAC_MV_PER_LSB_4V_RANGE;
            paramDict.Add(CyParamNames.API_DAC_CM_V_PER_LSB, dacmVperLSb);
            string dacshiftsLSb = (parameters.DACRange == CyDACRangeType.V1) ? 
                DAC_SHIFTS_LSB_1V_RANGE : DAC_SHIFTS_LSB_4V_RANGE;
            paramDict.Add(CyParamNames.API_DAC_SHIFTS_LSB, dacshiftsLSb);
            string filtCountType = (parameters.CompareType != CyCompareType.UV) ? "uint16" : "uint8 ";
            paramDict.Add(CyParamNames.API_FILT_COUNT_TYPE, filtCountType);
            // Mask
            UInt32 statusMask = ~(0xFFFFFFFF << parameters.NumVoltages);
            paramDict.Add(CyParamNames.API_STATUS_MASK, String.Format("0x{0}u", statusMask.ToString("X8")));

            // Replace macro dictionaries with paramDict
            foreach (CyAPICustomizer file in outputCustomizers)
            {
                file.MacroDictionary = paramDict;
            }

            return outputCustomizers;
        }

        /// <summary>
        /// Filter API files depending on the Compare type.
        /// </summary>
        private List<CyAPICustomizer> FilterAPI(List<CyAPICustomizer> inputCustomizers, CyParameters parameters)
        {
            List<CyAPICustomizer> outputCustomizers = new List<CyAPICustomizer>();
            CyAPICustomizer vfdOv_h = null;
            CyAPICustomizer vfdOv_c = null;
            CyAPICustomizer vfdUv_h = null;
            CyAPICustomizer vfdUv_c = null;


            foreach (CyAPICustomizer file in inputCustomizers)
            {
                if (file.OriginalName.EndsWith("VFD_OV.h"))
                    vfdOv_h = file;
                else if (file.OriginalName.EndsWith("VFD_OV.c"))
                    vfdOv_c = file;
                else if (file.OriginalName.EndsWith("VFD_UV.h"))
                    vfdUv_h = file;
                else if (file.OriginalName.EndsWith("VFD_UV.c"))
                    vfdUv_c = file;
            }

            outputCustomizers.AddRange(inputCustomizers);

            if (parameters.ExternalRef)
            {
                outputCustomizers.Remove(vfdOv_c);
                outputCustomizers.Remove(vfdUv_c);

                if (parameters.CompareType == CyCompareType.UV)
                    outputCustomizers.Remove(vfdOv_h);
                else if (parameters.CompareType == CyCompareType.OV)
                    outputCustomizers.Remove(vfdUv_h);
            }
            else
            {
                if (parameters.CompareType == CyCompareType.UV)
                {
                    outputCustomizers.Remove(vfdOv_h);
                    outputCustomizers.Remove(vfdOv_c);
                }
                else if (parameters.CompareType == CyCompareType.OV)
                {
                    outputCustomizers.Remove(vfdUv_h);
                    outputCustomizers.Remove(vfdUv_c);
                }
            }

            return outputCustomizers;
        }

        private string ConvertValueToArrayElement(double? elem, int i, int count, bool isScale, double mult)
        {
            string element = string.Empty;

            if (elem.HasValue)
            {
                if (isScale)
                {
                    element = (Math.Round(elem.Value * 1000 * mult + CyParameters.EPSILON, 
                        MidpointRounding.AwayFromZero)).ToString();
                }
                else
                {
                    element = ((UInt16)Math.Round((elem.Value / mult) * 255.0 + CyParameters.EPSILON, 
                        MidpointRounding.AwayFromZero)).ToString();
                }
            }
            else
            {
                element = "0";
            }
            element = (i > 0) ? element + "u, " : element + "u\r\n};";

            return element;
        }
        #endregion

        #region ICyDRCProvider_v1 Members
        /// <summary>
        /// DRC checks if there are empty cells in the Voltages table.
        /// Note: Voltage Name column can have empty cells.
        /// </summary>
        /// <param name="args"></param>
        /// <returns></returns>
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CyParameters parameters = new CyParameters(args.InstQueryV1);

            if (parameters.CheckTableNullValues() == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, Resources.DrcNullValuesError);
            }
            if (!parameters.CheckSiliconRevision(args.DeviceQueryV1))
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, Resources.DrcPSoC5);
            }
            if (!parameters.CheckMinScanPerVoltageValueDRC(args.TermQueryV1, parameters.DACRange, parameters.ExternalRef))
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Warning,
                    CyParameters.GetWarningMaxClockMsg(false, parameters.DACRange));
            }
        }
        #endregion
    }
}
