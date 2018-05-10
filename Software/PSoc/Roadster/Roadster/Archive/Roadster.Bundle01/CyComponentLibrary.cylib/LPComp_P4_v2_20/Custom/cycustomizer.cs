/*******************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
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

namespace LPComp_P4_v2_20
{
    sealed public partial class CyCustomizer : ICyParamEditHook_v1
    {
        public const string BUILTIN_TAB_NAME = "Built-in";

        #region ICyParamEditHook_v1 Members
        DialogResult ICyParamEditHook_v1.EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery,
            ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit);
            CyBasicTab basicTab = new CyBasicTab(parameters); // create Basic tab
            CyAdvancedTab advancedTab = new CyAdvancedTab(parameters); //created Advanced Tab
        
            CyParamExprDelegate basicTabExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                basicTab.UpdateUI();
                parameters.GlobalEditMode = true;
            };

            CyParamExprDelegate advancedTabExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                advancedTab.UpdateUI();
                parameters.GlobalEditMode = true;
            };

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();

            editor.AddCustomPage(Resources.BasicTabDisplayName, basicTab, basicTabExprDelegate, basicTab.TabName);
            editor.AddCustomPage(Resources.AdvancedTabDisplayName, advancedTab, advancedTabExprDelegate, advancedTab.TabName);
            editor.AddDefaultPage(Resources.BuiltinTabDisplayName, BUILTIN_TAB_NAME);

            editor.UseBigEditor = true;

            basicTab.UpdateUI();
            advancedTab.UpdateUI();
            parameters.GlobalEditMode = true;
            return editor.ShowDialog();
        }

        bool ICyParamEditHook_v1.EditParamsOnDrop
        {
            get
            {
                return false;
            }
        }

        CyCompDevParamEditorMode ICyParamEditHook_v1.GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }
        #endregion
    }
}
