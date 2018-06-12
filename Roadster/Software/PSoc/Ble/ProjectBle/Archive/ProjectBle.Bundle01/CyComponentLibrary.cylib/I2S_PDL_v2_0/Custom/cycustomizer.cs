/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System.Windows.Forms;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using I2S_PDL_v2_0.Tabs;

namespace I2S_PDL_v2_0
{
    sealed public class CyCustomizer : ICyParamEditHook_v1
    {
        #region ICyParamEditHook_v1 members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit, termQuery);
            parameters.GlobalEditMode = false;

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            editor.UseBigEditor = true;

            #region Create tab pages
            CyBasicTab basicTab = new CyBasicTab(parameters);
            #endregion

            #region Interaction between expression view and custom view
            CyParamExprDelegate dataChanged = delegate (ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                basicTab.UpdateUI();
                parameters.GlobalEditMode = true;
            };
            #endregion

            #region Add tabs to the customizer
            editor.AddCustomPage(basicTab.TabDisplayName, basicTab, dataChanged, basicTab.TabName);
            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, Resources.BuiltInTabDisplayName);
            #endregion

            // Update all tabs
            basicTab.UpdateUI();
            parameters.GlobalEditMode = true;

            edit.NotifyWhenDesignUpdates(parameters.UpdateDesigns);

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
