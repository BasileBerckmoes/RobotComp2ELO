/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Drawing;
using System.Windows.Forms;
using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using TrimMargin_v3_0.Tabs;
using TrimMargin_v3_0.Utils;
using TrimMargin_v3_0.DataStructures;

namespace TrimMargin_v3_0
{
    public partial class CyCustomizer : ICyParamEditHook_v1, ICyAPICustomize_v1, ICyShapeCustomize_v1,
        ICyDRCProvider_v1
    {
        public const string BASIC_TAB_NAME = "General";
        public const string BUILTIN_TAB_NAME = "Built-in";

        private const int API_VALUE_MULT = 1000;

        #region ICyParamEditHook_v1 Members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            //System.Diagnostics.Debugger.Launch();
            CyParameters parameters = new CyParameters(edit, termQuery, edit.DeviceQuery);
            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            CySummaryTab voltagesTab = new CySummaryTab(parameters);

            CyParamExprDelegate exprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                voltagesTab.UpdateUI();
                parameters.GlobalEditMode = true;
            };

            editor.AddCustomPage(Resources.SummaryTabName, voltagesTab, exprDelegate, BASIC_TAB_NAME,
                voltagesTab.TabName);

            editor.AddDefaultPage(Resources.BuiltInTabName, BUILTIN_TAB_NAME);
            editor.UseBigEditor = true;

            edit.NotifyWhenDesignUpdates(voltagesTab.UpdateClockDependedValues);

            parameters.GlobalEditMode = true;

            return editor.ShowDialog();
        }

        public bool EditParamsOnDrop
        {
            get
            {
                return false;
            }
        }

        public CyCompDevParamEditorMode GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }
        #endregion

        #region ICyShapeCustomize_v1 Members
        public CyCustErr CustomizeShapes(ICyInstQuery_v1 instQuery, ICySymbolShapeEdit_v1 shapeEdit,
            ICyTerminalEdit_v1 termEdit)
        {
            const string BODY_SHAPE = "Symbol_body";
            const string GENERATED_SHAPE = "Symbol_body_gen";

            CyCustErr err = CyCustErr.OK;

            RectangleF bodyRect = shapeEdit.GetShapeBounds(BODY_SHAPE);
            err = shapeEdit.ShapesRemove(BODY_SHAPE);
            if (err.IsNotOk) return err;

            byte numVoltages = 0;
            err = instQuery.GetCommittedParam(CyParamNames.NUM_CONVERTERS).TryGetValueAs<byte>(out numVoltages);
            if (err.IsNotOk) return err;

            float offset = 12.0F;
            PointF bodyLoc = bodyRect.Location;
            float bodyWidth = bodyRect.Width;
            float basicBodyHeight = offset * 2.5F;
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
            List<CyAPICustomizer> customizers = new List<CyAPICustomizer>(apis);
            Dictionary<string, string> paramDict = new Dictionary<string, string>();

            if (customizers.Count > 0) paramDict = customizers[0].MacroDictionary;

            CyParameters parameters = new CyParameters(query, termQuery, query.DeviceQuery);
            CyMath math = new CyMath(parameters);

            string element = String.Empty;
            string instName = parameters.InstanceName;
            UInt32 pwmMax = Convert.ToUInt32(Math.Pow(2, parameters.PWMResolution) - 1);

            // Voltages declarations
            string vMarginLow = "const uint16 CYCODE " + instName + "_VMARGIN_LOW[] = { ";
            string vMarginHigh = "const uint16 CYCODE " + instName + "_VMARGIN_HIGH[] = { ";
            string vDDIO = "const uint16 CYCODE " + instName + "_VDDIO[] = { ";

            string r1 = "const uint32 CYCODE " + instName + "_R1[] = { ";
            string r2 = "const uint32 CYCODE " + instName + "_R2[] = { ";
            string r3 = "const uint32 CYCODE " + instName + "_R3[] = { ";

            string vAdj = "const uint16 CYCODE " + instName + "_VADJ[] = { ";
            string vNominal = "const uint16 CYCODE " + instName + "_VNOMINAL[] = { ";
            string vMax = "const uint16 CYCODE " + instName + "_VMAX[] = { ";
            string vMin = "const uint16 CYCODE " + instName + "_VMIN[] = { ";
            string vDelta = "const uint16 CYCODE " + instName + "_VDELTA[] = { ";
            string vRangeArray = "static const uint16 CYCODE vRange[] = { ";
            string vKi = "static const int16 CYCODE Ki[] = { ";

            string dcType = (parameters.PWMResolution > 8) ? "uint16" : "uint8";
            string pwmNom = String.Format("const {0} CYCODE {1}_VNOMINAL_DUTYCYCLE[] = {{ ", dcType, instName);
            string pwmPre = String.Format("const {0} CYCODE {1}_PRE_RUN_DUTYCYCLE[] = {{ ", dcType, instName);
            string pwmStartup = String.Format("const {0} CYCODE {1}_STARTUP_DUTYCYCLE[] = {{ ", dcType, instName);
            string pwmStartupPre = String.Format("const {0} CYCODE {1}_STARTUP_PRE_RUN_DUTYCYCLE[] = {{ ", dcType, instName);
            string pwmVMarginLow = String.Format("const {0} CYCODE {1}_VMARGIN_LOW_DUTYCYCLE[] = {{ ", dcType, instName);
            string pwmVMarginHigh = String.Format("const {0} CYCODE {1}_VMARGIN_HIGH_DUTYCYCLE[] = {{ ", dcType, instName);
            string preCoef = String.Format("const uint16 CYCODE {0}_PRE_COEF[] = {{ ", instName);

            for (int i = 0; i < parameters.NumConverters; i++)
            {
                math.CalculateTableValues(i);
                double calcVmin = math.GetCalculatedVMin(i).Value;
                double calcVmax = math.GetCalculatedVMax(i).Value;
                bool isLast = (i == parameters.NumConverters - 1);

                try
                {
                    element = Convert.ToUInt16(math.GetVRange(i)).ToString();
                    CyApiGenUtils.AddUnsignedStringElement(ref vRangeArray, element, isLast);
                }
                catch (OverflowException)
                {
                    throw new OverflowException("vRange element was either too large or too small for a UInt16.");
                }

                try
                {
                    element = Convert.ToUInt16(parameters.VoltagesTable[i].MarginLow * API_VALUE_MULT).ToString();
                    CyApiGenUtils.AddUnsignedStringElement(ref vMarginLow, element, isLast);
                }
                catch (OverflowException)
                {
                    throw new OverflowException("VMARGIN_LOW element was either too large or too small for a UInt16.");
                }

                try
                {
                    element = Convert.ToUInt16(parameters.VoltagesTable[i].MarginHigh * API_VALUE_MULT).ToString();
                    CyApiGenUtils.AddUnsignedStringElement(ref vMarginHigh, element, isLast);
                }
                catch (OverflowException)
                {
                    throw new OverflowException("VMARGIN_HIGH element was either too large or too small for a UInt16.");
                }

                try
                {
                    element = Convert.ToUInt16(parameters.HardwareTable[i].m_vOh * API_VALUE_MULT).ToString();
                    CyApiGenUtils.AddUnsignedStringElement(ref vDDIO, element, isLast);
                }
                catch (OverflowException)
                {
                    throw new OverflowException("VDDIO element was either too large or too small for a UInt16.");
                }

                try
                {
                    element = Convert.ToUInt32(parameters.HardwareTable[i].m_r1 * API_VALUE_MULT).ToString();
                    CyApiGenUtils.AddUnsignedStringElement(ref r1, element, isLast);
                }
                catch (OverflowException)
                {
                    throw new OverflowException("R1 element was either too large or too small for a UInt16.");
                }

                try
                {
                    element = Convert.ToUInt32(parameters.HardwareTable[i].m_r2 * API_VALUE_MULT).ToString();
                    CyApiGenUtils.AddUnsignedStringElement(ref r2, element, isLast);
                }
                catch (OverflowException)
                {
                    throw new OverflowException("R2 element was either too large or too small for a UInt16.");
                }

                try
                {
                    element = Convert.ToUInt32(parameters.HardwareTable[i].m_r3 * API_VALUE_MULT).ToString();
                    CyApiGenUtils.AddUnsignedStringElement(ref r3, element, isLast);
                }
                catch (OverflowException)
                {
                    throw new OverflowException("R3 element was either too large or too small for a UInt16.");
                }

                try
                {
                    element = Convert.ToUInt16(parameters.HardwareTable[i].m_vAdj * API_VALUE_MULT).ToString();
                    CyApiGenUtils.AddUnsignedStringElement(ref vAdj, element, isLast);
                }
                catch (OverflowException)
                {
                    throw new OverflowException("_VADJ element was either too large or too small for a UInt16.");
                }

                double dc = math.GetPwmDutyCycle(i, parameters.VoltagesTable[i].m_nominalVoltage).Value;
                UInt16 pwmNomElement = (UInt16)Math.Round(dc, MidpointRounding.AwayFromZero);
                CyApiGenUtils.AddUnsignedStringElement(ref pwmNom, pwmNomElement.ToString(), isLast);

                // Generate PRE_COEF
                double preCoefValue = math.GetPreCoef(parameters.HardwareTable[i]).Value;
                element = Convert.ToUInt16(Math.Round(preCoefValue * API_VALUE_MULT,
                    MidpointRounding.AwayFromZero)).ToString();
                CyApiGenUtils.AddUnsignedStringElement(ref preCoef, element, isLast);

                // Generation pwmPre array
                UInt32 pwmPreElement = Convert.ToUInt32(Math.Round(pwmNomElement * preCoefValue, MidpointRounding.AwayFromZero));
                if (pwmPreElement > pwmMax) pwmPreElement = pwmMax;
                element = pwmPreElement.ToString();
                CyApiGenUtils.AddUnsignedStringElement(ref pwmPre, element, isLast);

                // Generation VNominal array
                element = Convert.ToUInt16(parameters.VoltagesTable[i].m_nominalVoltage * API_VALUE_MULT).ToString();
                CyApiGenUtils.AddUnsignedStringElement(ref vNominal, element, isLast);

                // Generation VMax array
                element = Convert.ToUInt16(calcVmax * API_VALUE_MULT).ToString();
                CyApiGenUtils.AddUnsignedStringElement(ref vMax, element, isLast);

                // Generation VMin array
                element = Convert.ToUInt16(calcVmin * API_VALUE_MULT).ToString();
                CyApiGenUtils.AddUnsignedStringElement(ref vMin, element, isLast);

                // Generate Ki array
                double k = math.GetKi(i).Value;
                CyApiGenUtils.AddStringElement(ref vKi, ((Int16)k).ToString(), isLast);

                double pwmVMarginLowElement = (double)math.GetPwmDutyCycle(i, parameters.VoltagesTable[i].MarginLow);
                if (pwmVMarginLowElement < 0) pwmVMarginLowElement = 0;
                if (pwmVMarginLowElement > pwmMax) pwmVMarginLowElement = pwmMax;
                element = Convert.ToUInt16(Math.Round(pwmVMarginLowElement, MidpointRounding.AwayFromZero)).ToString();
                CyApiGenUtils.AddUnsignedStringElement(ref pwmVMarginLow, element, isLast);

                double pwmVMarginHighElement = (double)math.GetPwmDutyCycle(i, parameters.VoltagesTable[i].MarginHigh);
                if (pwmVMarginHighElement < 0) pwmVMarginHighElement = 0;
                if (pwmVMarginHighElement > pwmMax) pwmVMarginHighElement = pwmMax;
                element = Convert.ToUInt16(Math.Round(pwmVMarginHighElement, MidpointRounding.AwayFromZero)).ToString();
                CyApiGenUtils.AddUnsignedStringElement(ref pwmVMarginHigh, element, isLast);

                double vDeltaElement = math.GetVDelta(i).Value;
                if (vDeltaElement < 1) vDeltaElement = 1;
                if (vDeltaElement > pwmMax) vDeltaElement = pwmMax;
                element = Convert.ToUInt16(Math.Round(vDeltaElement, MidpointRounding.AwayFromZero)).ToString();
                CyApiGenUtils.AddUnsignedStringElement(ref vDelta, element, isLast);

                // Calc PWM duty cycles for Startup voltage
                double pwmStartupElement = (double)math.GetPwmDutyCycle(i, parameters.VoltagesTable[i].m_startupVoltage);
                if (pwmStartupElement < 0) pwmStartupElement = 0;
                if (pwmStartupElement > pwmMax) pwmStartupElement = pwmMax;
                element = Convert.ToUInt16(Math.Round(pwmStartupElement, MidpointRounding.AwayFromZero)).ToString();
                CyApiGenUtils.AddUnsignedStringElement(ref pwmStartup, element, isLast);

                UInt32 pwmStartupPreElement = Convert.ToUInt32(Math.Round(pwmStartupElement * preCoefValue,
                    MidpointRounding.AwayFromZero));
                if (pwmStartupPreElement > pwmMax) pwmStartupPreElement = pwmMax;
                element = pwmStartupPreElement.ToString();
                CyApiGenUtils.AddUnsignedStringElement(ref pwmStartupPre, element, isLast);
            }

            paramDict.Add("PWMInclude", CyApiGenUtils.GetIncludes(parameters));
            paramDict.Add("PWMInit", CyApiGenUtils.GetInits(parameters));
            paramDict.Add("PWMEnable", CyApiGenUtils.GetEnables(parameters));
            paramDict.Add("PWMStop", CyApiGenUtils.GetStops(parameters));
            paramDict.Add("FeedbackValue", CyApiGenUtils.GetFeedbackValue(parameters));
            paramDict.Add("PWMCompareArray", CyApiGenUtils.GetPwmCompareArray(parameters));
            paramDict.Add("PWMCounterArray", CyApiGenUtils.GetPwmCounterArray(parameters));

            paramDict.Add("vRangeArray", CyApiGenUtils.WordWrap(vRangeArray));
            paramDict.Add("VMarginLowArray", CyApiGenUtils.WordWrap(vMarginLow));
            paramDict.Add("VMarginHighArray", CyApiGenUtils.WordWrap(vMarginHigh));
            paramDict.Add("VDDIOArray", CyApiGenUtils.WordWrap(vDDIO));

            paramDict.Add("R1Array", CyApiGenUtils.WordWrap(r1));
            paramDict.Add("R2Array", CyApiGenUtils.WordWrap(r2));
            paramDict.Add("R3Array", CyApiGenUtils.WordWrap(r3));

            paramDict.Add("VAdjArray", CyApiGenUtils.WordWrap(vAdj));
            paramDict.Add("VNominalArray", CyApiGenUtils.WordWrap(vNominal));
            paramDict.Add("VMaxArray", CyApiGenUtils.WordWrap(vMax));
            paramDict.Add("VMinArray", CyApiGenUtils.WordWrap(vMin));
            paramDict.Add("vDeltaArray", CyApiGenUtils.WordWrap(vDelta));

            paramDict.Add("PWMNomArray", CyApiGenUtils.WordWrap(pwmNom));
            paramDict.Add("PWMPreArray", CyApiGenUtils.WordWrap(pwmPre));
            paramDict.Add("PWMStartupArray", CyApiGenUtils.WordWrap(pwmStartup));
            paramDict.Add("PWMStartupPreArray", CyApiGenUtils.WordWrap(pwmStartupPre));

            paramDict.Add("pwmVMarginLowArray", CyApiGenUtils.WordWrap(pwmVMarginLow));
            paramDict.Add("pwmVMarginHighArray", CyApiGenUtils.WordWrap(pwmVMarginHigh));

            paramDict.Add("preCoefArray", CyApiGenUtils.WordWrap(preCoef));
            paramDict.Add("PIDCoefficients", CyApiGenUtils.WordWrap(vKi));

            for (int i = 0; i < customizers.Count; i++)
            {
                customizers[i].MacroDictionary = paramDict;
            }

            return customizers;
        }
        #endregion

        #region ICyDRCProvider_v1 Members
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CyParameters parameters = new CyParameters(args.InstQueryV1, args.DeviceQueryV1);

            // Check whether tables contain null values
            if ((parameters.CheckVoltagesTableNullValues() == false) ||
                (parameters.CheckHardwareTableNullValues() == false))
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, String.Format(
                    Resources.DrcNullValuesError, Resources.SummaryTabName));
            }

            // Do tables values range and sanity check
            if (DrcValidateTables(parameters) == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, Resources.InvalidTableData);
            }

            // Implementation validation
            string message = CyErrors.GetImplementationError(parameters);
            if (String.IsNullOrEmpty(message) == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, message);
            }
        }

        private static bool DrcValidateTables(CyParameters parameters)
        {
            CyMath math = new CyMath(parameters);
            for (int i = 0; i < parameters.NumConverters; i++)
            {
                CyVoltagesTableRow voltRow = parameters.VoltagesTable[i];
                CyHardwareTableRow hwRow = parameters.HardwareTable[i];

                List<CyCustErr> voltRangeErrors = new List<CyCustErr>(voltRow.ValidateRange());
                List<CyCustErr> hwRangeErrors = new List<CyCustErr>(hwRow.ValidateRange());
                if (voltRangeErrors.Count > 0 || hwRangeErrors.Count > 0)
                {
                    return false;
                }
                else
                {
                    double? calcMinVoltage = math.GetCalculatedVMin(voltRow, hwRow);
                    double? calcMaxVoltage = math.GetCalculatedVMax(voltRow, hwRow);
                    Dictionary<CyESanityCheck, CyCustErr> errors = voltRow.SanityCheck(calcMinVoltage, calcMaxVoltage);
                    foreach (KeyValuePair<CyESanityCheck, CyCustErr> item in errors)
                    {
                        if (item.Value.IsNotOk)
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
        #endregion
    }
}
