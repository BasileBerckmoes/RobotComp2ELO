/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System.Windows.Forms;
using CyDesigner.Toolkit;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using TCPWM_QuadDec_PDL_v1_0.Utils;

namespace TCPWM_QuadDec_PDL_v1_0.Controls
{
    public class CyDefaultPageUserControl : CyTabParamEditorDefaultPageControl<CyWaveform>
    {
        public CyDefaultPageUserControl(CyWaveform control, bool onTop, SizeType sizeType, int height)
            : base(control, onTop, sizeType, height)
        {
            Control.Dock = DockStyle.Fill;
        }

        public override void Refresh(CyQueryArgs args)
        {

            CyEnums.CyCounterResolution counterResolution = CyParameters.GetCounterResolution(args.InstQuery);
            CyEnums.CyInputMode indexInput = CyParameters.GetIndexInput(args.InstQuery);

            TypeSpecificControl.CounterResolution = CyEnums.ToDisplayValue(counterResolution);
            TypeSpecificControl.UseIndexInput = indexInput != CyEnums.CyInputMode.INPUT_DISABLED;
            TypeSpecificControl.Refresh();

            base.Refresh(args);
        }
    }
}