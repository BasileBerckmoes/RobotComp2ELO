/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System.Windows.Forms;

namespace TrimMargin_v3_0.DataStructures
{
    internal class CyConfigGridControls
    {
        public CyConfigGridControls(Control dependentControl, Control errorControl)
        {
            DependentControl = dependentControl;
            ErrorControl = errorControl;
        }

        public Control DependentControl { get; set; }
        public Control ErrorControl { get; set; }
    }
}