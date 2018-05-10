/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using TCPWM_PWM_PDL_v1_0.Controls;
using TCPWM_PWM_PDL_v1_0.Utils;

namespace TCPWM_PWM_PDL_v1_0
{
    public class CyCustomizer : ICyParamEditHook_v1
    {
        #region ICyParamEditHook_v1 members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyTabParamEditorDefaultPageExtender extender = new CyTabParamEditorDefaultPageExtender();

            // Create control with dynamicaly calculated labels
            CyDynamicDataControl dynamicDataControl = new CyDynamicDataControl();
            CyDefaultPageUserControl userControl = new CyDefaultPageUserControl(dynamicDataControl, false, 
                SizeType.Absolute, 200);

            // Create image control
            using (CyImagePageControl imageControl = new CyImagePageControl(new Bitmap(544, 138),
                PictureBoxSizeMode.Zoom, false, SizeType.Percent, 50))
            {
                extender.InnerLeftBottomControl = imageControl;
                extender.InnerRightBottomControl = userControl;

                ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
                
                editor.ParamExprFilter = (param, enumDisplayName) =>
                {
                    // For Swap/Reload/Start Input parameters, "Level" option should be absent 
                    if (param.Name == CyParamNames.SWAP_INPUT ||
                        param.Name == CyParamNames.RELOAD_INPUT ||
                        param.Name == CyParamNames.START_INPUT)
                    {
                        if (enumDisplayName == CyEnums.ENUM_VALUE_INPUT_LEVEL)
                        {
                            return false;
                        }
                    }
                    // Kill Input parameter dependency on KillMode:
                    // KillMode = Stop on Kill -> "Level" is absent 
                    // KillMode = Synchronous Kill -> only "Level" available
                    // KillMode = Asynchronous Kill -> only "Rising Edge" available
                    else if (param.Name == CyParamNames.KILL_INPUT)
                    {
                        CyEnums.CyKillMode killMode = CyParameters.GetKillMode(edit);
                        switch (killMode)
                        {
                            case CyEnums.CyKillMode.ASYNC_KILL:
                                // Only "Level" available
                                if (enumDisplayName != CyEnums.ENUM_VALUE_INPUT_LEVEL)
                                {
                                    return false;
                                }
                                break;
                            case CyEnums.CyKillMode.SYNCH_KILL:
                                // Only "Rising Edge" available
                                if (enumDisplayName != CyEnums.ENUM_VALUE_INPUT_RISING_EDGE)
                                {
                                    return false;
                                }
                                break;
                            case CyEnums.CyKillMode.STOP_ON_KILL:
                                // All except "Level" available
                                if (enumDisplayName == CyEnums.ENUM_VALUE_INPUT_LEVEL)
                                {
                                    return false;
                                }
                                break;
                            default:
                                Debug.Fail("Unhandled enum item " + killMode);
                                break;
                        }
                    }
                    // For pseudo-random PWM, Kill Mode should not contain "Synchronous" option
                    else if (param.Name == CyParamNames.KILL_MODE)
                    {
                        if ((CyParameters.GetMode(edit) == CyEnums.CyMode.MODE_PSEUDORANDOM) &&
                            (enumDisplayName == CyEnums.ENUM_VALUE_KILLMODE_SYNCHRONOUS))
                        {
                            return false;
                        }
                    }

                    return true;
                };
                
                editor.AddDefaultPage(Resources.BasicTabDisplayName, extender);
                editor.AddDefaultPage(Resources.AdvancedTabDisplayName);
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
