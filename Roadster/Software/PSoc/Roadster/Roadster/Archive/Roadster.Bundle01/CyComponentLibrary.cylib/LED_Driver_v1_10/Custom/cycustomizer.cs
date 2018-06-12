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
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace LED_Driver_v1_10
{
    public class CyCustomizer : ICyParamEditHook_v1, ICyShapeCustomize_v1, ICyDRCProvider_v1
    {
        #region ICyParamEditHook_v1 implementation
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit, termQuery);
            parameters.GlobalEditMode = false;

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();

            CyGeneralTab generalTab = new CyGeneralTab(parameters);

            CyParamExprDelegate generalChanged =
            delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                generalTab.UpdateUI();
                parameters.GlobalEditMode = true;
            };

            editor.AddCustomPage(Resources.GeneralTabDisplayName, generalTab, generalChanged, generalTab.TabName);
            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");

            generalTab.UpdateUI();

            parameters.GlobalEditMode = true;

            edit.NotifyWhenDesignUpdates(generalTab.UpdateRefreshRate);

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

        #region ICyShapeCustomize_v1 implementation
        private const string TERM_PATERN = "{0}[{1}:0]";
        private const string SEGMENTS_TERMINAL_BASE_NAME = "seg";
        private const string COMMONS_TERMINAL_BASE_NAME = "com";

        public CyCustErr CustomizeShapes(ICyInstQuery_v1 query, ICySymbolShapeEdit_v1 shapeEdit,
            ICyTerminalEdit_v1 termEdit)
        {
            CyCustErr err;

            CyParameters parameters = new CyParameters(query, termEdit);

            // Rename segments terminal
            err = SetTermName(termEdit, SEGMENTS_TERMINAL_BASE_NAME, parameters.NumberOfSegments);
            if (err.IsNotOK)
            {
                return err;
            }

            // Rename commons terminal
            err = SetTermName(termEdit, COMMONS_TERMINAL_BASE_NAME, parameters.NumberOfCommons);
            if (err.IsNotOK)
            {
                return err;
            }

            return CyCustErr.OK;
        }

        private CyCustErr SetTermName(ICyTerminalEdit_v1 termEdit, string termBaseName, byte width)
        {
            string busName = termEdit.GetTermName(termBaseName);
            CyCustErr err = termEdit.TerminalRename(busName, (width > 1) ?
                string.Format(TERM_PATERN, termBaseName, width - 1) : termBaseName);

            return err;
        }
        #endregion

        #region ICyDRCProvider_v1 implementation
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CyParameters parameters = new CyParameters(args.InstQueryV1, args.TermQueryV1);

            CyCustErr warningBusClock = parameters.VerifyBusClock();
            if (warningBusClock != CyCustErr.OK)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Warning, warningBusClock.Message);
        }
        #endregion ICyDRCProvider_v1 implementation
    }
}
