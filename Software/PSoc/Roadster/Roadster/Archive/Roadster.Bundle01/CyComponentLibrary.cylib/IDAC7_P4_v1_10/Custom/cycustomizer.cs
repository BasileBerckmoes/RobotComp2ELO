/*******************************************************************************
* Copyright 2015-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace IDAC7_P4_v1_10
{
    [CyCompDevCustomizer]
    public class CyCustomizer : ICyParamEditHook_v1, ICyDRCProvider_v1
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
        
        #region ICyDRCProvider_v1 members
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CyParameters parameters = new CyParameters(args.InstQueryV1);

            if ((parameters.IsS8CSDV2_Ver2 == false) && (parameters.IDACRange == CyEIDACRangeType.RNG_152_4UA))
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, Resources.ErrMsgrRange_152_4);
            }
        }
        #endregion
        
    }
}
