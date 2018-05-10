/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System.Windows.Forms;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using TCPWM_QuadDec_PDL_v1_0.Controls;
using TCPWM_QuadDec_PDL_v1_0.Utils;

namespace TCPWM_QuadDec_PDL_v1_0
{
    public class CyCustomizer : ICyParamEditHook_v1
    {
        #region ICyParamEditHook_v1 members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyDefaultPageUserControl userControl = new CyDefaultPageUserControl(new CyWaveform(), false,
                SizeType.Percent, 100);

            CyTabParamEditorDefaultPageExtender extender = new CyTabParamEditorDefaultPageExtender();
            extender.InnerLeftBottomControl = userControl;

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();

            editor.ParamExprFilter = (param, enumDisplayName) =>
            {
                // For Index/Stop Input parameters, "Level" option should be absent 
                if (param.Name == CyParamNames.INDEX_INPUT ||
                    param.Name == CyParamNames.STOP_INPUT)
                {
                    if (enumDisplayName == CyEnums.ENUM_VALUE_INPUT_LEVEL)
                    {
                        return false;
                    }
                }

                return true;
            };

            editor.AddDefaultPage(Resources.BasicTabDisplayName, extender);
            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");
            editor.UseBigEditor = true;

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
