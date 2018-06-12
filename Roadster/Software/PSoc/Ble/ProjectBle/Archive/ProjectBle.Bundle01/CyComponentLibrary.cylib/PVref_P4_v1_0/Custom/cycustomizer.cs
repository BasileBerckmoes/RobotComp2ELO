/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using System.Windows.Forms;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using PVref_P4_v1_0.Tabs;
using System.Collections.Generic;
using System.Drawing;

namespace PVref_P4_v1_0
{
    public class CyCustomizer : ICyParamEditHook_v1, ICyAPICustomize_v2, ICyDesignClient_v2, ICyShapeCustomize_v2
    {
        #region Class Consts

        // ParamEditHook
        public const string BUILTIN_TAB_NAME = "Built-in";
        public const string BASIC_TAB_NAME = "Basic";

        // APICustomize
        private const string API_PARAMNAME_VDDAMVOLTS = "VddaMVolts";
        private const string API_PARAMNAME_BGMVOLTS = "BgMVolts";

        // ShapeCustomize
        private const string VOUT_SHAPETAG = "Vout";
        private const string TERMSCONTAINER_SHAPETAG = "TermsContainer";

        #endregion Class Consts

        #region ICyParamEditHook_v1 Members

        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit);

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            parameters.Editor = editor;

            CyBasicConfigTab basicTab = new CyBasicConfigTab(parameters);

            CyParamExprDelegate exprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                basicTab.UpdateUiFromTable();
                parameters.GlobalEditMode = true;
            };

            editor.AddCustomPage(Properties.Resources.TAB_NAME_BASIC, basicTab, exprDelegate, BASIC_TAB_NAME);
            editor.AddDefaultPage(Properties.Resources.TAB_NAME_BUILTIN, BUILTIN_TAB_NAME);

            parameters.GlobalEditMode = true;
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

        #endregion ICyParamEditHook_v1 Members

        #region ICyAPICustomize_v2 Members

        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyAPICustomizeArgs_v2 args, 
            IEnumerable<CyAPICustomizer> apis)
        {
            List<CyAPICustomizer> customizers = new List<CyAPICustomizer>(apis);
            Dictionary<string, string> paramDict = new Dictionary<string, string>();
            CyParameters prms = new CyParameters(args.InstQuery);

            if (customizers.Count > 0)
            {
                paramDict = customizers[0].MacroDictionary;
            }

            paramDict.Add(API_PARAMNAME_VDDAMVOLTS, (prms.Vdda * 1000).ToString());
            paramDict.Add(API_PARAMNAME_BGMVOLTS, (prms.Bandgap * 1000).ToString());

            for (int i = 0; i < customizers.Count; i++)
            {
                customizers[i].MacroDictionary = paramDict;
                yield return customizers[i];
            }
        }

        #endregion ICyAPICustomize_v2 Members

        #region ICyShapeCustomize_v2 Members

        public CyCustErr CustomizeShapes(ICyShapeCustomizeArgs_v1 args)
        {
            try
            {
                const int EM_SIZE = 10;

                CyCustErr err;
                CyParameters prms = new CyParameters(args.InstQuery);
                string vOutString = string.Format(CyBasicConfigTab.VREF_DISPLAY_FORMAT + " V",
                    prms.GetVref());

                List<string> tags = new List<string>();
                tags.Add(VOUT_SHAPETAG);

                Font font = new Font(FontFamily.GenericSansSerif, EM_SIZE, FontStyle.Regular);
                StringFormat stringFormat = new StringFormat();
                stringFormat.Alignment = StringAlignment.Far;
                stringFormat.LineAlignment = StringAlignment.Center;
                int vOutLocationX = (int)(args.ShapeEdit.GetShapeBounds(TERMSCONTAINER_SHAPETAG).Width / 2);
                int vOutLocationY = 0;

                args.ShapeEdit.ShapesRemove(VOUT_SHAPETAG);
                err = args.ShapeEdit.CreateAnnotation(tags, vOutString, new PointF(vOutLocationX, vOutLocationY), font,
                    stringFormat, Color.Black);

                return err;
            }
            catch(System.Exception ex)
            {
                return new CyCustErr(ex);
            }
        }

        #endregion ICyShapeCustomize_v2 Members

        #region ICyDesignClient_v2 Members

        public string GetDesignClientState(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            return string.Empty;
        }

        public bool RequiresShapeUpdate(string designClientState, ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            return true;
        }

        public bool RequiresTooltipUpdate(string designClientState, ICyInstQuery_v1 query, 
            ICyTerminalQuery_v1 termQuery)
        {
            return false;
        }

        #endregion ICyDesignClient_v2 Members
    }
}
