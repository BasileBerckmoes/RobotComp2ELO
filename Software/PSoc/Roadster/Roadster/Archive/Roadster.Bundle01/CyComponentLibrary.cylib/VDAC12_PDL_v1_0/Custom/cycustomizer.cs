/*******************************************************************************
* Copyright 2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using CyDesigner.Toolkit;

using VDAC12_PDL_v1_0.Controls;

// The namespace is required to have the same name as the component for a customizer.
namespace VDAC12_PDL_v1_0
{
    // CyCustomizer is the required class name for a customizer.
    public class CyCustomizer : 
        ICyParamEditHook_v1, 
        ICyInstValidateHook_v1,
        ICyExprEval_v2,
        ICyDRCProvider_v1
    {
        internal const double VDDA_DEFAULT = 3.3;
        internal const double DWR_DEFAULT = 1.2;
        internal const double MAX_VDAC_CLOCK_KHZ = 500;

        #region ICyParamEditHook_v1 Members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            double clkFreq;
            var clkData = termQuery.GetClockData("clock", 0);
            if (clkData.Count > 0 && clkData[0].IsFrequencyKnown)
            {
                clkFreq = clkData[0].Frequency;
            }

            CyTabParamEditorDefaultPageExtender extender = new CyTabParamEditorDefaultPageExtender();

            // Create control with dynamicaly calculated labels
            CyDynamicDataControl dynamicDataControl = new CyDynamicDataControl();
            
            CyDefaultPageUserControl userControl = new CyDefaultPageUserControl(dynamicDataControl, false, 
                SizeType.Percent, 50);

            // Create image control
            using (CyImagePageControl imageControl = new CyImagePageControl(new Bitmap(544, 138),
                PictureBoxSizeMode.Zoom, false, SizeType.Percent, 50))
            {
                ToolTip toolTipBufferOuput = new ToolTip();
                extender.InnerLeftBottomControl = imageControl; 
                extender.InnerRightBottomControl = userControl;
                toolTipBufferOuput.SetToolTip(extender.InnerLeftBottomControl.Control, Resources.LimitedBufferOutput);

                VrefUpdate(edit);

                ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();                
                
                editor.AddDefaultPage(Resources.BasicTabDisplayName, extender);
                editor.AddDefaultPage(Resources.AdvancedTabDisplayName, "Advanced");                
                editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");
                editor.UseBigEditor = true;
                                
                return editor.ShowDialog();
            }
        }

        //Catches the case where the DWR was edited after the component.
        private void VrefUpdate(ICyInstEdit_v1 edit)
        {
            double vrefVoltage;
            if (edit.VoltageQuery != null)
            {
                CyArefCurrent_v1 refCurrent = edit.VoltageQuery.ReferenceCurrent;
                vrefVoltage = edit.VoltageQuery.SystemReference;

                if (double.IsNaN(vrefVoltage))
                {
                    CyParameters.SetDwrExtVref(edit, true);
                }
                else
                {
                    CyParameters.SetDwrExtVref(edit, false);
                }

                if(refCurrent == CyArefCurrent_v1.HIGH)
                {
                    CyParameters.SetReferenceCurrentHigh(edit, true);
                }
                else
                {
                    CyParameters.SetReferenceCurrentHigh(edit, false);
                }
            }

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

        #region ICyInstValidateHook_v1
        public void ValidateParams(ICyInstValidate_v1 instVal)
        {
            if (instVal.VoltageQuery != null)
            {
                if (CyParameters.GetVrefVoltage(instVal) > instVal.VoltageQuery.VDDA)
                {
                    CyCustErr err = new CyCustErr(Resources.VrefOverVddaError);
                    instVal.AddError(CyParamNames.VREF_VOLTAGE, err);
                }
            }
        }
        #endregion

        #region ICyExprEval_v2
        public CyExprEvalFuncEx GetFunction(string exprName)
        {
            switch (exprName)
            {
                case "IsDesignRefExternal":
                    return new CyExprEvalFuncEx(IsDesignRefExternal);
                case "GetVddaVoltage":
                    return new CyExprEvalFuncEx(GetVddaVoltage);
                case "GetDwrVoltage":
                    return new CyExprEvalFuncEx(GetDwrVoltage);
                case "PartHasCtb":
                    return new CyExprEvalFuncEx(PartHasCtb);
                default:
                    return null;
            }
        }

        object PartHasCtb(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs, ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 0)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (no arguments expected).",
                    exprFuncName));
            }

            var result = (int)0;

            if ((creatorArgs != null) && (creatorArgs.InstQuery != null) && (creatorArgs.InstQuery.VoltageQuery != null))
            {                
                result = creatorArgs.InstQuery.DeviceQuery.GetFeatureParameter("mxs40pass", "NR_CTBS") == 0 ? 0 : 1;
            }

            return result;
        }

        object IsDesignRefExternal(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs, ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 0)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (no arguments expected).",
                    exprFuncName));
            }

            var result = (int) 0;

            if ((creatorArgs != null) && (creatorArgs.InstQuery != null) && (creatorArgs.InstQuery.VoltageQuery != null))
            {
                if(double.IsNaN(creatorArgs.InstQuery.VoltageQuery.SystemReference))
                {
                    result = (int) 1;
                }

            }

            return result;
        }

        object GetVddaVoltage(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs, ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 0)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (no arguments expected).",
                    exprFuncName));
            }

            // Return a non-zero default value so that when we are developing the library project
            // and InstQuery is Null, the validation of default values will not error.
            var result = VDDA_DEFAULT;

            if ((creatorArgs != null) && (creatorArgs.InstQuery != null) && (creatorArgs.InstQuery.VoltageQuery != null))
            {
                result = creatorArgs.InstQuery.VoltageQuery.VDDA;
            }

            return result;
        }

        object GetDwrVoltage(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs, ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 0)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (no arguments expected).",
                    exprFuncName));
            }

            // Return a non-zero default value so that when we are developing the library project
            // and InstQuery is Null, the validation of default values will not error.
            var result = DWR_DEFAULT;

            if ((creatorArgs != null) && (creatorArgs.InstQuery != null) && (creatorArgs.InstQuery.VoltageQuery != null))
            {
                result = creatorArgs.InstQuery.VoltageQuery.SystemReference;
            }

            return result;
        }
        #endregion

        #region ICyDRCProvider_v1 members

        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            Utils.CyEnums.CyEUpdateType updateType = CyParameters.GetUpdateMode(args.InstQueryV1);

            if(updateType.Equals(Utils.CyEnums.CyEUpdateType.BufferedWrite) 
                || updateType.Equals(Utils.CyEnums.CyEUpdateType.StrobeEdgeSync)
                || updateType.Equals(Utils.CyEnums.CyEUpdateType.StrobeLevel))
            {
                double clockFreq = CyParameters.GetExternalClockKhz(args.TermQueryV1);
                clockFreq = Math.Round(clockFreq, 2);
                if(clockFreq > MAX_VDAC_CLOCK_KHZ)
                {
                    yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                        String.Format("Clock frequency cannot be greater than {0} kHz", MAX_VDAC_CLOCK_KHZ));
                }
            }
        }


        #endregion
    }
}

//[] END OF FILE
