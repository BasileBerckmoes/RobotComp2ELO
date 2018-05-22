/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System.Windows.Forms;
using CyDesigner.Toolkit;
using CyDesigner.Extensions.Common;
using TCPWM_Counter_PDL_v1_0.Controls;

namespace TCPWM_Counter_PDL_v1_0
{
    public class CyDefaultPageUserControl : CyTabParamEditorDefaultPageControl<CyDynamicDataControl>
    {
        public CyDefaultPageUserControl(CyDynamicDataControl control, bool onTop, SizeType sizeType, int height)
            : base(control, onTop, sizeType, height)
        {
        }

        public override void Refresh(CyQueryArgs args)
        {
            TypeSpecificControl.UpdateUI(args.InstQuery, args.TermQuery);
            base.Refresh(args);
        }
    }
}