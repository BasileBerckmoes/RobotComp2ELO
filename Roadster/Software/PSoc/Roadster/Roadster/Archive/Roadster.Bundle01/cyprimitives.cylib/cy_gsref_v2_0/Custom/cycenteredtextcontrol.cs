/*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
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
using System.Diagnostics;

namespace Cypress.Components.System.cy_gsref_v2_0
{
    public partial class CyCenteredTextControl : UserControl
    {
        public CyCenteredTextControl()
        {
            InitializeComponent();
            this.Dock = DockStyle.Fill;

            SetLabelMaxSize();
        }

        /// <summary>
        /// Gets or sets the message to display centered on the control.
        /// </summary>
        [Browsable(true)]
        public override string Text
        {
            get
            {
                return m_messageLabel.Text;
            }
            set
            {
                m_messageLabel.Text = value;
                base.Text = m_messageLabel.Text;
            }
        }

        public override Font Font
        {
            get
            {
                return m_messageLabel.Font;
            }
            set
            {
                m_messageLabel.Font = value;
            }
        }

        /// <summary>
        /// If the text is longer than the max width then the text will
        /// wrap to the next line which is what we want.
        /// </summary>
        void SetLabelMaxSize()
        {
            m_messageLabel.MaximumSize = new Size((int)(this.Width * .85), (int)(this.Height * .85));
        }

        protected override void OnResize(EventArgs e)
        {
            SetLabelMaxSize();
            base.OnResize(e);
        }
    }
}
