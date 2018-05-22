/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Windows.Forms;

namespace SMBusSlave_v5_20
{
    [CyCompDevCustomizer()]
    public partial class CyCustomizer : 
        ICyParamEditHook_v1, 
        ICyDRCProvider_v1
    {
        private CyParameters m_parameters;

        #region ICyParamEditHook_v1 Members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            m_parameters = new CyParameters(edit, termQuery);
            m_parameters.GlobalEditMode = false;

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();

            // Create tab pages
            CyGeneralTab generalTab = new CyGeneralTab(m_parameters, termQuery);
            CyPmBusCmdsTab pmBusCmdsTab = new CyPmBusCmdsTab(m_parameters, editor);
            CyCustomCmdsTab customCmdsTab = new CyCustomCmdsTab(m_parameters, edit.DesignQuery.ApplicationType);
            CyI2cConfigTab i2cConfigTab = null;
            CyI2cConfigP4Tab i2cConfigP4Tab = null;

            CyParamExprDelegate generalDataChanged = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                m_parameters.GlobalEditMode = false;
                generalTab.UpdateUI();
                m_parameters.GlobalEditMode = true;
            };

            // Add tabs to the customizer 
            editor.AddCustomPage(Resources.GeneralTabDisplayName, generalTab, generalDataChanged, generalTab.TabName);
            editor.AddCustomPage(Resources.PMBusCmdsTabDisplayName, pmBusCmdsTab, null, pmBusCmdsTab.TabName);
            pmBusCmdsTab.SetPMBusCmdsTabVisibility(m_parameters.Mode);
            editor.AddCustomPage(Resources.CustomCmdsTabDisplayName, customCmdsTab, null, customCmdsTab.TabName);

            if (m_parameters.IsPSoC4)
            {
                i2cConfigP4Tab = new CyI2cConfigP4Tab(m_parameters);
                CyParamExprDelegate i2CP4DataChanged = delegate(ICyParamEditor custEditor, CyCompDevParam param)
                {
                    m_parameters.GlobalEditMode = false;
                    i2cConfigP4Tab.UpdateUI();
                    m_parameters.GlobalEditMode = true;
                };
                editor.AddCustomPage(Resources.I2cConfTabDisplayName, i2cConfigP4Tab, i2CP4DataChanged, 
                    i2cConfigP4Tab.TabName);
            }
            else
            {
                i2cConfigTab = new CyI2cConfigTab(m_parameters);
                CyParamExprDelegate i2CDataChanged = delegate(ICyParamEditor custEditor, CyCompDevParam param)
                {
                    m_parameters.GlobalEditMode = false;
                    i2cConfigTab.UpdateUI();
                    m_parameters.GlobalEditMode = true;
                };
                editor.AddCustomPage(Resources.I2cConfTabDisplayName, i2cConfigTab, i2CDataChanged, 
                    i2cConfigTab.TabName);
            }

            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");

            edit.NotifyWhenDesignUpdates(m_parameters.UpdateClock);
            editor.UseBigEditor = true;

            generalTab.UpdateUI();
            if (i2cConfigTab != null)
                i2cConfigTab.UpdateUI();
            if (i2cConfigP4Tab != null)
                i2cConfigP4Tab.UpdateUI();

            m_parameters.GlobalEditMode = true;
           
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
            m_parameters = new CyParameters(args.InstQueryV1);

            if (m_parameters.CheckPmBusTableNullValues() == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, string.Format(
                    Resources.DrcNullValuesError, Resources.PMBusCmdsTabDisplayName));
            }
            if (m_parameters.CheckCustomTableNullValues() == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, string.Format(
                    Resources.DrcNullValuesError, Resources.CustomCmdsTabDisplayName));
            }
            if (m_parameters.CheckBootloaderCommands() == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, Resources.BootloadCommandNotEnabled);
            }
        }
        #endregion
    }
}
