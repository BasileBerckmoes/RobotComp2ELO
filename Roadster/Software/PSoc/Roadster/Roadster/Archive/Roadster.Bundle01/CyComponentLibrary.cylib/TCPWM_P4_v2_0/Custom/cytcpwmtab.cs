/*******************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace TCPWM_P4_v2_0
{
    public partial class CyTCPWMTab : CyEditingWrapperControl
    {
        public override string TabName
        {
            get { return "TCPWM"; }
        }

        public CyTCPWMTab(CyParameters prms)
            : base(prms)
        {
            InitializeComponent();
            Prms.m_tcpwmTab = this;
        }

        public void UpdateFormFromParams()
        {
            cbSignalReload.Checked = Prms.ReloadPresent;
            cbSignalCount.Checked = Prms.CountPresent;
            cbSignalStart.Checked = Prms.StartPresent;
            cbSignalStop.Checked = Prms.StopPresent;
            cbSignalCapture.Checked = Prms.CapturePresent;
        }

        private void cbSignal_CheckedChanged(object sender, EventArgs e)
        {
            if (sender == cbSignalReload)
                Prms.ReloadPresent = cbSignalReload.Checked;

            else if (sender == cbSignalCount)
                Prms.CountPresent = cbSignalCount.Checked;

            else if (sender == cbSignalStart)
                Prms.StartPresent = cbSignalStart.Checked;

            else if (sender == cbSignalStop)
                Prms.StopPresent = cbSignalStop.Checked;

            else if (sender == cbSignalCapture)
                Prms.CapturePresent = cbSignalCapture.Checked;

        }
    }
}
