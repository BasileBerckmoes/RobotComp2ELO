/*******************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
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

namespace USBFS_v3_20
{
    public partial class CyDetailsEPMngt : UserControl
    {
        public CyUSBFSParameters m_parameters;

        public CyDetailsEPMngt(CyUSBFSParameters parameters)
        {
            InitializeComponent();
            m_parameters = parameters;
            InitFields();

            rbManualDynamicAlloc.CheckedChanged += new EventHandler(rbMemoryMgmt_CheckedChanged);
            rbManualStaticAlloc.CheckedChanged += new EventHandler(rbMemoryMgmt_CheckedChanged);
            rbDMAManual.CheckedChanged += new EventHandler(rbMemoryMgmt_CheckedChanged);
            rbDMAAutomatic.CheckedChanged += new EventHandler(rbMemoryMgmt_CheckedChanged);
        }

        private void InitFields()
        {
            // Memory management
            switch (m_parameters.EPMemoryMgmt)
            {
                case CyUSBFSParameters.CyMemoryManagement.EP_Manual:
                    if (m_parameters.EPMemoryAlloc == CyUSBFSParameters.CyMemoryAllocation.MA_Static)
                        rbManualStaticAlloc.Checked = true;
                    else if (m_parameters.EPMemoryAlloc == CyUSBFSParameters.CyMemoryAllocation.MA_Dynamic)
                        rbManualDynamicAlloc.Checked = true;
                    break;
                case CyUSBFSParameters.CyMemoryManagement.EP_DMAmanual:
                    rbDMAManual.Checked = true;
                    break;
                case CyUSBFSParameters.CyMemoryManagement.EP_DMAauto:
                    rbDMAAutomatic.Checked = true;
                    break;
                default:
                    break;
            }  
        }

        private void rbMemoryMgmt_CheckedChanged(object sender, EventArgs e)
        {
            if (!((RadioButton)sender).Checked)
                return;

            CyUSBFSParameters.CyMemoryAllocation alloc = CyUSBFSParameters.CyMemoryAllocation.MA_Static;
            CyUSBFSParameters.CyMemoryManagement res = CyUSBFSParameters.CyMemoryManagement.EP_Manual;

            if (rbManualDynamicAlloc == sender)
            {
                alloc = CyUSBFSParameters.CyMemoryAllocation.MA_Dynamic;
            }
            if (rbDMAManual == sender)
            {
                alloc = CyUSBFSParameters.CyMemoryAllocation.MA_Static;
                res = CyUSBFSParameters.CyMemoryManagement.EP_DMAmanual;
            }
            if (rbDMAAutomatic == sender)
            {
                alloc = CyUSBFSParameters.CyMemoryAllocation.MA_Static;
                res = CyUSBFSParameters.CyMemoryManagement.EP_DMAauto;
            }

            m_parameters.EPMemoryMgmt = res;
            m_parameters.EPMemoryAlloc = alloc;

            if (m_parameters.InterrPage != null)
                m_parameters.InterrPage.UpdateInterruptsTableView();
        }

    }
}
