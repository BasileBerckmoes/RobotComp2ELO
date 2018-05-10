using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace ADC_UAB_v1_0
{
    [CyCompDevCustomizer()]
    public partial class CyCustomizer :
        ICyDesignClient_v2,
        ICyDRCProvider_v1,
        ICyParamEditHook_v1,
        ICyShapeCustomize_v2,
        ICyExprEval_v2
    {
        private const bool editParamsOnDrop = false;
        private const CyCompDevParamEditorMode mode = CyCompDevParamEditorMode.COMPLETE;
        private ADC_UAB_Parameters parameters;
        private CyAdcUab adcUab;

        #region ICyParamEditHook_v1

        DialogResult ICyParamEditHook_v1.EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            parameters = new ADC_UAB_Parameters(edit, edit, termQuery);
            CyParamExprDelegate paramChange = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GetParams();
            };

            parameters.GetParams();
            adcUab = new CyAdcUab(parameters);

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();

            editor.AddCustomPage("Basic", new ADC_UAB_EditingControl(parameters, adcUab), paramChange, "Basic");

            editor.AddDefaultPage("Built-in", "Built-in");


            return editor.ShowDialog();
        }

        bool ICyParamEditHook_v1.EditParamsOnDrop
        {
            get
            {
                return editParamsOnDrop;
            }
        }

        CyCompDevParamEditorMode ICyParamEditHook_v1.GetEditorMode()
        {
            return mode;
        }

        #endregion ICyParamEditHook_v1

        #region ICyDesignClient_v2

        public string GetDesignClientState(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            return string.Empty;
        }

        public bool RequiresTooltipUpdate(string designClientState, ICyInstQuery_v1 query,
            ICyTerminalQuery_v1 termQuery)
        {
            return false;
        }

        public bool RequiresShapeUpdate(string designClientState, ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            return true;
        }

        #endregion ICyDesignClient_v2

        #region ICyDRCProvider_v1

        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            if (this.parameters == null)
            {
                this.parameters = new ADC_UAB_Parameters(null, args.InstQueryV1, args.TermQueryV1);
            }

            if (this.adcUab == null)
            {
                this.adcUab = new CyAdcUab(parameters);
            }

            if(this.adcUab.IsSaturateMax() == true)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Info,
                    global::ADC_UAB_v1_0.ADC_UAB_Errors.saturateHighError);
            }

            if (this.adcUab.IsSaturateMin() == true)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Info,
                    global::ADC_UAB_v1_0.ADC_UAB_Errors.saturateLowError);
            }

            if (this.adcUab.IsSysClkOK() == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Warning,
                    CyAdcUab.SysClkErrorMessage());
            }

            if (this.adcUab.IsConvTimeInBounds() == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Warning,
                    this.adcUab.ConversionTimeErrorMessage());
            }

            if (this.adcUab.IsSysClk3xUabClk() == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                    (string.Format(global::ADC_UAB_v1_0.ADC_UAB_Errors.sysClk3xUabError,
                    args.InstQueryV1.InstanceName)));
            }
        }

        #endregion ICyDRCProvider_v1

        #region ICyShapeCustomize_v2

        public CyCustErr CustomizeShapes(ICyShapeCustomizeArgs_v1 args)
        {
            ICyInstQuery_v1 query = args.InstQuery;
            ICySymbolShapeEdit_v2 shapeEdit = args.ShapeEdit;

            var tag = "analog_wire";
            var color = query.Preferences.AnalogWireColor;
            float lineWidth = query.Preferences.WireSize;
            shapeEdit.SetOutlineColor(tag, color);
            shapeEdit.SetFillColor(tag, color);
            shapeEdit.SetOutlineWidth(tag, lineWidth);

            return CyCustErr.OK;
        }

        #endregion ICyShapeCustomize_v2

        #region ICyExprEval_v2
        public CyExprEvalFuncEx GetFunction(string exprFuncName)
        {
            switch(exprFuncName)
            {
                case "InputRangeText":
                    return new CyExprEvalFuncEx(InputRangeText);
                default:
                    return null;
            }
        }

        object InputRangeText(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (callingArgs.Length != 0)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (no arguments expected).",
                    exprFuncName));
            }
            ADC_UAB_Parameters myParams = new ADC_UAB_Parameters(creatorArgs.InstQuery);
            CyAdcUab adcUab = new CyAdcUab(myParams);
            List<CyDisplayValue<CyVrefGainPair>> wordList;
            if(myParams.Endedness == CyEInputEndedness.SingleEnded)
            {
                wordList = adcUab.GetSingleEndedRanges();
            }
            else
            {
                wordList = adcUab.GetDifferentialRanges();
            }
            int text_idx = myParams.VrefSource == CyEVrefSource.Bandgap ?
                0 :
                5;
            text_idx += (int)myParams.VRange;
            string result = wordList[text_idx].Display;

            return result;
        }
        #endregion
    }

    public class ADC_UAB_EditingControl : ICyParamEditingControl
    {
        private ADC_UAB_Control control;

        public ADC_UAB_EditingControl(ADC_UAB_Parameters parameters, CyAdcUab adcUab)
        {
            control = new ADC_UAB_Control(parameters, adcUab);
            parameters.control = control;
            control.Dock = DockStyle.Fill;
        }

        Control ICyParamEditingControl.DisplayControl
        {
            get { return control; }
        }

        IEnumerable<CyCustErr> ICyParamEditingControl.GetErrors()
        {
            return new CyCustErr[] { };
        }
    }
}
