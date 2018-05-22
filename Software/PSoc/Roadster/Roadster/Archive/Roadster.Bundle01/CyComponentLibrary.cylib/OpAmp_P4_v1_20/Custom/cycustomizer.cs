/*******************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Diagnostics;

namespace OpAmp_P4_v1_20
{
    [CyCompDevCustomizer]
    public class CyCustomizer : ICyParamEditHook_v1
    {
        private const string BUILT_IN_TAB_NAME = "Built-in";

        #region ICyParamEditHook_v1 Members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit);

            CyConfigureTab configureTab = new CyConfigureTab(parameters); // create tab page

            CyParamExprDelegate configureTabDataChanged = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                configureTab.UpdateUI();
                parameters.GlobalEditMode = true;
            };


            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();

            // Add tabs to the customizer 
            editor.AddCustomPage(Resources.ConfigureTabDisplayName, configureTab, configureTabDataChanged,
                configureTab.TabName);
            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, BUILT_IN_TAB_NAME);

            configureTab.UpdateUI();

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

    }
}
