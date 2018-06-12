/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System.Drawing;
using System.Windows.Forms;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;

namespace LPComp_PDL_v1_0
{
    sealed public class CyCustomizer : ICyParamEditHook_v1
    {
        #region ICyParamEditHook_v1 Members
        DialogResult ICyParamEditHook_v1.EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery,
            ICyExpressMgr_v1 mgr)
        {
            CyImagePageControl waveform = new CyImagePageControl(new CyWaveformImage(new Size(460, 210)),
                PictureBoxSizeMode.Zoom, false, SizeType.Percent, 100);
            CyImagePageControl symbol = new CyImagePageControl(new CySymbolImage(new Size(200, 200)),
                PictureBoxSizeMode.Zoom, false, SizeType.Percent, 100);

            CyTabParamEditorDefaultPageExtender extender = new CyTabParamEditorDefaultPageExtender();
            extender.InnerLeftBottomControl = waveform;
            extender.InnerRightBottomControl = symbol;

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            editor.AddDefaultPage(Resources.BasicTabDisplayName, extender);
            editor.AddDefaultPage(Resources.BuiltinTabDisplayName, "Built-in");
            editor.UseBigEditor = true;

            return editor.ShowDialog();
        }

        bool ICyParamEditHook_v1.EditParamsOnDrop
        {
            get
            {
                return false;
            }
        }

        CyCompDevParamEditorMode ICyParamEditHook_v1.GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }
        #endregion
    }
}
