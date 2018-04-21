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
    public partial class CyConfigTab : CyEditingWrapperControl
    {
        public override string TabName
        {
            get { return "Configuration"; }
        }

        public CyConfigTab(CyParameters prms)
            : base(prms)
        {
            InitializeComponent();
            UpdateFormFromParams();
        }

        public void UpdateFormFromParams()
        {
            switch (Prms.TCPWMConfig)
            {
                case CyETCPWMConfig.UNCONFIG:
                    rbUnconfigured.Checked = true;
                    break;
                case CyETCPWMConfig.TIMER:
                    rbTimerCounter.Checked = true;
                    break;
                case CyETCPWMConfig.QUAD:
                    rbQuadDec.Checked = true;
                    break;
                case CyETCPWMConfig.PWM_SEL:
                    rbPWM.Checked = true;
                    break;
                default:
                    break;
            }
        }

        private void rbconfig_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = (RadioButton)sender;
            if (rb.Checked == false)  
            {
                return;
            }

            if (Prms.InstQuery.IsInSystemBuilder)
            {
                Prms.SetTermModesXml(Prms.TCPWMConfig);
            }

            if (rb == rbTimerCounter)
                Prms.TCPWMConfig = CyETCPWMConfig.TIMER;
            else if (rb == rbPWM)
                Prms.TCPWMConfig = CyETCPWMConfig.PWM_SEL;
            else if (rb == rbQuadDec)
                Prms.TCPWMConfig = CyETCPWMConfig.QUAD;
            else 
                Prms.TCPWMConfig = CyETCPWMConfig.UNCONFIG;

            Prms.UpdateTabVisibility();

            if (Prms.InstQuery.IsInSystemBuilder)
            {
                Prms.SetTermModesParams(Prms.TCPWMConfig);
            }
        }
    }
}
