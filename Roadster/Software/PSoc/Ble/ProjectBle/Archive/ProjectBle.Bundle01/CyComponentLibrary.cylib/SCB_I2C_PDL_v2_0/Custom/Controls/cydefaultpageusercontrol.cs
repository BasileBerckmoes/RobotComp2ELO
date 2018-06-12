/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System.Windows.Forms;
using CyDesigner.Toolkit;
using CyDesigner.Extensions.Common;

namespace SCB_I2C_PDL_v2_0.Controls
{
    public class CyDefaultPageUserControl : CyTabParamEditorDefaultPageControl<CyDynamicDataControl>
    {
        public CyDefaultPageUserControl(CyDynamicDataControl control, bool onTop, SizeType sizeType, int height)
            : base(control, onTop, sizeType, height)
        {
        }

        public override void Refresh(CyQueryArgs args)
        {
            base.Refresh(args);
            TypeSpecificControl.UpdateUI();
        }
    }
}
