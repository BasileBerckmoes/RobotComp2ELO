/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System.Drawing;
using System.Windows.Forms;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using TCPWM_Counter_PDL_v1_0.Controls;

namespace TCPWM_Counter_PDL_v1_0
{
    public class CyCustomizer : ICyParamEditHook_v1
    {
        #region ICyParamEditHook_v1 members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            // Create control with dynamicaly calculated labels
            CyDynamicDataControl dynamicDataControl = new CyDynamicDataControl();
            CyDefaultPageUserControl userControl = new CyDefaultPageUserControl(dynamicDataControl,
                false, SizeType.Absolute, 200);

            // Create image control
            using (CyImagePageControl imageControl = new CyImagePageControl(new Bitmap(700, 500),
                PictureBoxSizeMode.Zoom, false, SizeType.Percent, 100))
            {
                CyTabParamEditorDefaultPageExtender extender = new CyTabParamEditorDefaultPageExtender();
                extender.InnerLeftBottomControl = imageControl;
                extender.InnerRightBottomControl = userControl;

                ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
                
                editor.ParamExprFilter = (param, enumDisplayName) =>
                {
                   if (param.Name == CyParamNames.STOP_INPUT
                    || param.Name == CyParamNames.RELOAD_INPUT
                    || param.Name == CyParamNames.START_INPUT
                    || param.Name == CyParamNames.CAPTURE_INPUT)
                    {
                        if (enumDisplayName == "Level")
                        {
                            return false;
                        }
                    }
                    return true;
                };
                
                editor.AddDefaultPage(Resources.BasicTabDisplayName, extender);
                editor.AddDefaultPage(Resources.InputsTabDisplayName);
                editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");
                edit.NotifyWhenDesignUpdates(dynamicDataControl.UpdateClock);
                editor.UseBigEditor = true;

                return editor.ShowDialog();
            }
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
