/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System.Windows.Forms;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using Em_EEPROM_v2_0.Controls;

namespace Em_EEPROM_v2_0
{
    sealed public partial class CyCustomizer : ICyParamEditHook_v1
    {
        #region ICyParamEditHook_v1 members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit);

            // Create control with dynamicaly calculated labels
            CyDynamicDataControl dynamicDataControl = new CyDynamicDataControl(parameters);
            CyDefaultPageUserControl embeddedControl = new CyDefaultPageUserControl(dynamicDataControl,
                false, SizeType.Percent, 60);

                CyTabParamEditorDefaultPageExtender extender = new CyTabParamEditorDefaultPageExtender();
                extender.InnerRightBottomControl = embeddedControl;

                ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
                editor.UseBigEditor = true;

                editor.AddDefaultPage("Basic", extender);
                editor.AddDefaultPage("Built-in", "Built-in");

                parameters.EditMode = true;

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
