/*******************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Drawing;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Windows.Forms;
using System.Diagnostics;

namespace Comp_PDL_v1_0
{
    sealed public class CyCustomizer : ICyParamEditHook_v1
    {
        public const string BUILTIN_TAB_NAME = "Built-in";

        #region ICyParamEditHook_v1 Members
        DialogResult ICyParamEditHook_v1.EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery,
            ICyExpressMgr_v1 mgr)
        {
            CyImagePageControl waveform = new CyImagePageControl(new CyWaveformImage(new Size(460, 210)),
                PictureBoxSizeMode.Zoom, false, SizeType.Percent, 100);

            CyTabParamEditorDefaultPageExtender extender = new CyTabParamEditorDefaultPageExtender();
            extender.InnerLeftBottomControl = waveform;

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            
            editor.AddDefaultPage(Resources.GeneralTabDisplayName, extender);
            editor.AddDefaultPage(Resources.BuiltinTabDisplayName, "Built-in");
            editor.UseBigEditor = true;

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
    }
}
