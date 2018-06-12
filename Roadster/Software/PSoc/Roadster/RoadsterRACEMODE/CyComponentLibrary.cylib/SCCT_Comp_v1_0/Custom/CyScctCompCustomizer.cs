/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace SCCT_Comp_v1_0
{
   [CyCompDevCustomizer()]
    public class CyCustomizer : ICyParamEditHook_v1
    { 
        #region ICyParamEditHook_v1 Members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery,ICyExpressMgr_v1 mgr)
        {
            CyScctCompParameters parameters = new CyScctCompParameters(edit);//get current component parameters
            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor(); //create customizer dialog
            // Create tabs
            CyScctComparatorControl generalTab = new CyScctComparatorControl(parameters, Resources.GeneralTabName);

            CyParamExprDelegate dataChanged = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                generalTab.UpdateFormFromParams();
                parameters.GlobalEditMode = true;
            };

            // Add tabs to the customizer
            editor.AddCustomPage(Resources.GeneralTabName, generalTab, new CyParamExprDelegate(dataChanged), Resources.GeneralTabName);
            editor.AddDefaultPage("Built-in", "Built-in");
            //Update tabs
            generalTab.UpdateFormFromParams();
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
