/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using RTC_P4_v1_10.Tabs;

namespace RTC_P4_v1_10
{
    public class CyCustomizer : ICyParamEditHook_v1, ICyDRCProvider_v1
    {
        public const string BUILTIN_TAB_NAME = "Built-in";
        
        #region ICyParamEditHook_v1 Members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit);

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            parameters.Editor = editor;

            CyBasicConfigTab basicConfigTab = new CyBasicConfigTab(parameters);

            CyParamExprDelegate exprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                basicConfigTab.UpdateUI();
                parameters.GlobalEditMode = true;
            };

            editor.AddCustomPage(Resource.BasicTabDisplayName, basicConfigTab, exprDelegate, basicConfigTab.TabName);
            editor.AddDefaultPage(Resource.BuiltInTabDisplayName, BUILTIN_TAB_NAME);
            
            basicConfigTab.UpdateUI();
            
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
        #endregion

        #region ICyDRCProvider_v1 Members
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CyParameters parameters = new CyParameters(args.InstQueryV1);

            // Manual RTC implementation is not applicable when WCO clock doesn't exist
            if (parameters.WcoClockExists == false && parameters.UpdateManually)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Warning, Resource.ErrorRtcUpdateManually);
            }
        }
        #endregion
    }
}
