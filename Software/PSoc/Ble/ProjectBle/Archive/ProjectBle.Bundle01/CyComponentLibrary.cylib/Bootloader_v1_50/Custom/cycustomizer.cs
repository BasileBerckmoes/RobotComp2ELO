/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace Bootloader_v1_50
{
    [CyCompDevCustomizer]
    sealed public partial class CyCustomizer : ICyParamEditHook_v1, ICyBootloaderProvider_v1
    {
        #region ICyParamEditHook_v1 Members
        DialogResult ICyParamEditHook_v1.EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery,
                                                    ICyExpressMgr_v1 mgr)
        {
            const string PAPAM_TAB_NAME_BUILTIN = "Built-in";
            CyParameters prms = new CyParameters(edit);
            CyGeneralPage generalPage = new CyGeneralPage(prms);
            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            editor.UseBigEditor = true;

            CyParamExprDelegate exprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                prms.m_globalEditMode = false;
                if (param.TabName == generalPage.TabName)
                    generalPage.InitFields();
                prms.m_globalEditMode = true;
            };

            editor.AddCustomPage(Properties.Resources.PageTitleGeneral, generalPage, exprDelegate, generalPage.TabName);
            editor.AddDefaultPage(Properties.Resources.PageTitleBuiltIn, PAPAM_TAB_NAME_BUILTIN);

            prms.m_globalEditMode = true;

            return editor.ShowDialog();
        }

        bool ICyParamEditHook_v1.EditParamsOnDrop
        {
            get { return false; }
        }

        CyCompDevParamEditorMode ICyParamEditHook_v1.GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }
        #endregion

        #region ICyBootloaderProvider_v1 Members
        public CyCustErr GetBootloaderData(ICyBootloaderProviderArgs_v1 args, out CyBootloaderData_v1 data)
        {
            CyParameters prms = new CyParameters(args.InstQuery);
            string comm = prms.IOComponent;

            CyBootloaderChecksumType_v1 checksum = CyBootloaderChecksumType_v1.BasicChecksum;
            if (prms.PacketChecksumType == true)
            {
                checksum = CyBootloaderChecksumType_v1.CRC16;
            }

            CyBootloaderType_v1 type = CyBootloaderType_v1.NotSet;
            if (prms.Launcher == true)
            {
                type = CyBootloaderType_v1.Launcher;
            }
            else if (prms.MultiAppBootloader == true)
            {
                type = CyBootloaderType_v1.MultiApp;
            }
            else
            {
                type = CyBootloaderType_v1.SingleApp;
            }

            data = new CyBootloaderData_v1(prms.Version, checksum, comm, type, prms.Copier);

            return CyCustErr.OK;
        }
        #endregion
    }
}
