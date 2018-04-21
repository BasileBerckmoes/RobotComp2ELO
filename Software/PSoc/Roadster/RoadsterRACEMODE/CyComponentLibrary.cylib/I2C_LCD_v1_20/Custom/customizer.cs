/*******************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System.Collections.Generic;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using System.Windows.Forms;
using System;
using System.Diagnostics;
using CyDesigner.Toolkit.TerminalControl_v1;
using CyTerminalControl_v1 = CyDesigner.Toolkit.TerminalControl_v1.CyTerminalControl_v1;

namespace I2C_LCD_v1_20
{
    [CyCompDevCustomizer]
    sealed public partial class CyCustomizer : ICyParamEditHook_v1, ICyDRCProvider_v1, ICySystemBuilderComp_v1
    {
        public const string GENERAL_TAB_NAME = "General";
        public const string CUSTOM_COMMANDS_TAB_NAME = "Custom Commands";

        #region ICyParamEditHook_v1 Members
        DialogResult ICyParamEditHook_v1.EditParams(ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery,
            ICyExpressMgr_v1 mgr)
        {
            ICyTabbedParamEditor editor = instEdit.CreateTabbedParamEditor();
            editor.UseBigEditor = true;
            CyParameters parameters = new CyParameters(instEdit);
            CyGeneralTab generalTab = new CyGeneralTab(parameters);
            CyCustomCommandsTab custCmdTab = new CyCustomCommandsTab(parameters);
            CyTerminalControl_v1 interconnectTab = null;

            CyParamExprDelegate genExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                generalTab.InitializeUI();
                parameters.GlobalEditMode = true;
            };
            CyParamExprDelegate custExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                custCmdTab.UpdateUI(false);
            };
            editor.AddCustomPage(Resources.GeneralTabDisplayName, generalTab, genExprDelegate, generalTab.TabName);
            editor.AddCustomPage(Resources.CustomCmdTabDisplayName, custCmdTab, custExprDelegate, custCmdTab.TabName);

            // System Builder support
            if (parameters.InstQuery.DeviceQuery.IsPSoC4 && instEdit.IsInSystemBuilder)
            {
                interconnectTab = new CyTerminalControl_v1(instEdit);
                editor.AddCustomPage(Resources.InterconnectTabDisplayName, interconnectTab, genExprDelegate,
                    "Interconnect");
            }

            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");
            generalTab.InitializeUI();
            custCmdTab.UpdateUI();
            parameters.GlobalEditMode = true;
            return editor.ShowDialog();
        }

        CyCompDevParamEditorMode ICyParamEditHook_v1.GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }

        bool ICyParamEditHook_v1.EditParamsOnDrop
        {
            get { return false; }
        }
        #endregion

        #region ICyDRCProvider_v1 Members
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CyParameters parameters = new CyParameters(args.InstQueryV1);
            if (parameters.CheckRequiredCommandsNullValues() == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, Resources.DrcRequiredNullValues);
            }
            if (parameters.CheckCustomCommandsNullValues() == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, Resources.DrcCustomNullValues);
            }
        }
        #endregion

        #region ICySystemBuilderComp_v1 members
        public CyCustErr GetTitleText(ICySystemBuilderCompArgs_v1 args, out string title)
        {
            title = Resources.SBComponentTitle;
            return CyCustErr.OK;
        }

        public CyCustErr GetBodyText(ICySystemBuilderCompArgs_v1 args, out string bodyText)
        {
            string customCharSet = String.Empty;
            string commandFormat = Resources.SBCommandFormatNXP;            

            CyParameters parameters = new CyParameters(args.InstQuery);

            switch (parameters.CustomCharacterSet)
            {
                case CyECustomCharacterSet.None:
                    customCharSet = Resources.SBCustomCharacterSetLabelNone;
                    break;
                case CyECustomCharacterSet.Horizontal:
                    customCharSet = Resources.SBCustomCharacterSetLabelHorizontalBarGraph;
                    break;
                case CyECustomCharacterSet.Vertical:
                    customCharSet = Resources.SBCustomCharacterSetLabelVerticalBarGraph;
                    break;
                case CyECustomCharacterSet.UserDefined:
                    customCharSet = Resources.SBCustomCharacterSetLabelUserDefined;
                    break;
                default:
                    customCharSet = Resources.SBCustomCharacterSetLabelUnknown;
                    Debug.Fail("Unhandled custom character set.");
                    break;
            }

            if (parameters.CommandFormat == CyECommandFormat.Custom)
            {
                   commandFormat = Resources.SBCommandFormatCustom;
            }            

            bodyText = String.Format(Resources.SBComponentBodyText, customCharSet, commandFormat);

            return CyCustErr.OK;
        }
        #endregion
    }
}
