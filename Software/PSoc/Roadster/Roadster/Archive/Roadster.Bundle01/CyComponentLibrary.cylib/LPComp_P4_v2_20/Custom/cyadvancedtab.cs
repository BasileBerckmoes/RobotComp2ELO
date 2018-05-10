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

namespace LPComp_P4_v2_20
{
    public partial class CyAdvancedTab : CyEditingWrapperControl
    {
        CyImage m_symbol;

        public override string TabName
        {
            get { return "Advanced"; }
        }

        public CyAdvancedTab(CyParameters param)
            : base(param)
        {
            m_params.AdvancedTab = this;  

            InitializeComponent();
            chB_OutPosition.CheckedChanged += new EventHandler(chB_CheckedChanged);

            m_symbol = new CyImage();
            RedrawSymbol();
        }

        #region Update UI
        public void UpdateUI()
        {
            chB_OutPosition.Checked = m_params.LegacyOutputPosition;
        }

        public void RedrawSymbol()
        {
            m_symbol.UpdateParams(m_params, pbSymbol);
            m_symbol.UpdateSymbol();
            pbSymbol.Image = m_symbol.Bmp;
        }
        #endregion

        #region Event handlers
        void chB_CheckedChanged(object sender, EventArgs e)
        {
            m_params.LegacyOutputPosition = chB_OutPosition.Checked;

            m_params.BasicTab.RedrawGraphs();
        }
        #endregion Event handlers
    }
}
