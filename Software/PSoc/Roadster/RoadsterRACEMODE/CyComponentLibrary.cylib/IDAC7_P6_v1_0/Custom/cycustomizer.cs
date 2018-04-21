/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace IDAC7_P6_v1_0
{
    [CyCompDevCustomizer]
    public class CyCustomizer : ICyParamEditHook_v1
    {
        public const string CONFIGURE_TAB_NAME = "Configure";
        public const string BUILT_IN_TAB_NAME = "Built-in";

        #region ICyParamEditHook_v1 Members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit);

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();

            // Create tab page
            CyConfigureTab configureTab = new CyConfigureTab(parameters);

            // This delegate refreshes parameters on the Configure tab of customizer.
            CyParamExprDelegate configureTabExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                configureTab.UpdateUI();
                parameters.GlobalEditMode = true;
            };

            //Add tabs to the customizer 
            editor.AddCustomPage(Resources.ConfigureTabDisplayName, configureTab, configureTabExprDelegate,
                CONFIGURE_TAB_NAME);
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
