/*******************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Windows.Forms;

namespace TMP05Intf_v1_10
{
    [CyCompDevCustomizer()]
    public class CyCustomizer : ICyParamEditHook_v1, ICyDRCProvider_v1
    {
        #region ICyParamEditHook_v1 Members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit);
            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();

            // Create tab page
            CyGeneralTab generalTab = new CyGeneralTab(parameters);

            CyParamExprDelegate dataChanged = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.m_globalEditMode = false;
                generalTab.UpdateUI();
                parameters.m_globalEditMode = true;
            };

            // Add tabs to the customizer
            editor.AddCustomPage(Resources.GeneralTabDisplayName, generalTab, dataChanged, generalTab.TabName);
            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");

            generalTab.UpdateUI();
            parameters.m_globalEditMode = true;

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
            CyCustErr err = VerifyClockFrequency(args.TermQueryV1);
            if (err.IsOk == false)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err.Message);
        }

        private CyCustErr VerifyClockFrequency(ICyTerminalQuery_v1 termQuery)
        {
            double externalClockFrequency = CyClockReader.GetExternalClockInKHz(termQuery);
            if (externalClockFrequency > 0)
            {
                if (externalClockFrequency < CyParameters.CLOCK_FREQ_MIN ||
                    externalClockFrequency > CyParameters.CLOCK_FREQ_MAX)
                {
                    return new CyCustErr(string.Format(Resources.ExternalClockFrequencyValidator,
                        CyParameters.CLOCK_FREQ_MIN, CyParameters.CLOCK_FREQ_MAX));
                }
            }
            return CyCustErr.OK;
        }
        #endregion
    }
}
