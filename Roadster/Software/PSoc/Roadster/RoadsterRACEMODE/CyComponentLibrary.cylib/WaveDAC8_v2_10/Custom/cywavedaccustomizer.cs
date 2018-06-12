/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
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

namespace WaveDAC8_v2_10
{
    [CyCompDevCustomizer()]
    public class CyCustomizer : ICyParamEditHook_v1, ICyDRCProvider_v1
    {
        #region ICyParamEditHook_v1 Members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit, termQuery);
            CyWaveDacTab generalTab = new CyWaveDacTab(parameters);

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            editor.UseBigEditor = true;

            CyParamExprDelegate ExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                generalTab.UpdateUIFromParams();
                parameters.GlobalEditMode = true;
            };

            editor.AddCustomPage(cywavedacresource.GeneralTabDisplayName, generalTab, 
                                 new CyParamExprDelegate(ExprDelegate), generalTab.TabName);
            editor.AddDefaultPage(cywavedacresource.BuiltinTabDisplayName, "Built-in");

            parameters.GlobalEditMode = true;

            edit.NotifyWhenDesignUpdates(generalTab.UpdateDesign);

            DialogResult result = editor.ShowDialog();
            return result;
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
            CyParameters parameters = new CyParameters(args.InstQueryV1, args.TermQueryV1);

            CyCustErr externalClockErr = CyAuxFunctions.VerifyExternalClock(parameters);

            if (externalClockErr != CyCustErr.OK)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, externalClockErr.Message);
        }
        #endregion
    }
}
