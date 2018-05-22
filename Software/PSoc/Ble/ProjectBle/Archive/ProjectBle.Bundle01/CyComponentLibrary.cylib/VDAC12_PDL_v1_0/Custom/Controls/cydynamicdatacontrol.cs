/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Windows.Forms;
using CyDesigner.Toolkit;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using VDAC12_PDL_v1_0.Utils;

namespace VDAC12_PDL_v1_0.Controls
{
    public class CyDynamicDataControl : UserControl
    {
        private TableLayoutPanel tableLayoutPanel1;
        private Label lblVoutMax;
        private Label lblVoutMid;
        private Label lblVoutMin;
        private Label lblCodeMax;
        private Label lblCodeMid;
        private Label lblVoutTitle;
        private Label lblCodeMin;
        private Label lblCode;
        private Label lblRangeExpr;
        private Panel panel1;
        private Label lblLSB;
        private const string NO_VALUE = "-";

        #region Constructor(s)
        public CyDynamicDataControl()
        {
            InitializeComponent();
            this.Dock = DockStyle.Fill;
        }
        #endregion

        #region UI update
        public void UpdateUI(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            UpdateLabels(query, termQuery);
        }

        #endregion

        #region Calculated labels
        private void UpdateLabels(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            UpdateTransferLabels(query);
            UpdateLsbLabel(query);
        }

        private void UpdateLsbLabel(ICyInstQuery_v1 query)
        {
            double vref = CyParameters.GetVrefVoltage(query);
            double vlsb = 0;

            if(vref > 0)
            {
                vlsb = vref / 4096;
                vlsb = vlsb * 1000000;
                this.lblLSB.Text = "LSB = " + vlsb.ToString("000") + " uV";
            }
        }
        private void UpdateTransferLabels(ICyInstQuery_v1 query)
        {
            CyEnums.CyESignMode signMode = CyParameters.GetCodeMode(query);
            double vref = CyParameters.GetVrefVoltage(query);

            if(vref > 0)
            {
                double vMid = 0.5 * vref;
                double vMax = vref * 4095 / 4096;

                this.lblVoutMid.Text = vMid.ToString("0.0000");
                this.lblVoutMax.Text = vMax.ToString("0.0000");
            }
            if( signMode.Equals(CyEnums.CyESignMode.FormatSigned))
            {
                this.lblCodeMin.Text = "-2048";
                this.lblCodeMid.Text = "0";
                this.lblCodeMax.Text = "2047";
            }
            else
            {
                this.lblCodeMin.Text = "0";
                this.lblCodeMid.Text = "2048";
                this.lblCodeMax.Text = "4095";
            }
        }
        #endregion

        private void InitializeComponent()
        {
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.lblVoutMax = new System.Windows.Forms.Label();
            this.lblVoutMid = new System.Windows.Forms.Label();
            this.lblVoutMin = new System.Windows.Forms.Label();
            this.lblCodeMax = new System.Windows.Forms.Label();
            this.lblCodeMid = new System.Windows.Forms.Label();
            this.lblVoutTitle = new System.Windows.Forms.Label();
            this.lblCodeMin = new System.Windows.Forms.Label();
            this.lblCode = new System.Windows.Forms.Label();
            this.lblRangeExpr = new System.Windows.Forms.Label();
            this.lblLSB = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.tableLayoutPanel1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.AutoSize = true;
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 77F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 158F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.Controls.Add(this.lblVoutMax, 1, 6);
            this.tableLayoutPanel1.Controls.Add(this.lblVoutMid, 1, 5);
            this.tableLayoutPanel1.Controls.Add(this.lblVoutMin, 1, 4);
            this.tableLayoutPanel1.Controls.Add(this.lblCodeMax, 0, 6);
            this.tableLayoutPanel1.Controls.Add(this.lblCodeMid, 0, 5);
            this.tableLayoutPanel1.Controls.Add(this.lblVoutTitle, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.lblCodeMin, 0, 4);
            this.tableLayoutPanel1.Controls.Add(this.lblCode, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.lblRangeExpr, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.lblLSB, 0, 7);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(-5, 0);
            this.tableLayoutPanel1.Margin = new System.Windows.Forms.Padding(0, 4, 4, 4);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 8;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 25F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 25F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 25F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 38F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(235, 158);
            this.tableLayoutPanel1.TabIndex = 1;
            // 
            // lblVoutMax
            // 
            this.lblVoutMax.AutoSize = true;
            this.lblVoutMax.Location = new System.Drawing.Point(81, 88);
            this.lblVoutMax.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblVoutMax.Name = "lblVoutMax";
            this.lblVoutMax.Size = new System.Drawing.Size(115, 17);
            this.lblVoutMax.TabIndex = 7;
            this.lblVoutMax.Text = "Vref * 4095/4096";
            // 
            // lblVoutMid
            // 
            this.lblVoutMid.AutoSize = true;
            this.lblVoutMid.Location = new System.Drawing.Point(81, 63);
            this.lblVoutMid.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblVoutMid.Name = "lblVoutMid";
            this.lblVoutMid.Size = new System.Drawing.Size(67, 17);
            this.lblVoutMid.TabIndex = 5;
            this.lblVoutMid.Text = "0.5 * Vref";
            // 
            // lblVoutMin
            // 
            this.lblVoutMin.AutoSize = true;
            this.lblVoutMin.Location = new System.Drawing.Point(81, 42);
            this.lblVoutMin.Margin = new System.Windows.Forms.Padding(4, 4, 4, 0);
            this.lblVoutMin.Name = "lblVoutMin";
            this.lblVoutMin.Size = new System.Drawing.Size(16, 17);
            this.lblVoutMin.TabIndex = 3;
            this.lblVoutMin.Text = "0";
            // 
            // lblCodeMax
            // 
            this.lblCodeMax.AutoSize = true;
            this.lblCodeMax.Location = new System.Drawing.Point(4, 88);
            this.lblCodeMax.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblCodeMax.Name = "lblCodeMax";
            this.lblCodeMax.Size = new System.Drawing.Size(40, 17);
            this.lblCodeMax.TabIndex = 6;
            this.lblCodeMax.Text = "2047";
            // 
            // lblCodeMid
            // 
            this.lblCodeMid.AutoSize = true;
            this.lblCodeMid.Location = new System.Drawing.Point(4, 63);
            this.lblCodeMid.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblCodeMid.Name = "lblCodeMid";
            this.lblCodeMid.Size = new System.Drawing.Size(16, 17);
            this.lblCodeMid.TabIndex = 4;
            this.lblCodeMid.Text = "0";
            // 
            // lblVoutTitle
            // 
            this.lblVoutTitle.AutoSize = true;
            this.lblVoutTitle.Location = new System.Drawing.Point(81, 21);
            this.lblVoutTitle.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblVoutTitle.Name = "lblVoutTitle";
            this.lblVoutTitle.Size = new System.Drawing.Size(64, 17);
            this.lblVoutTitle.TabIndex = 1;
            this.lblVoutTitle.Text = "Vout (V):";
            // 
            // lblCodeMin
            // 
            this.lblCodeMin.AutoSize = true;
            this.lblCodeMin.Location = new System.Drawing.Point(4, 42);
            this.lblCodeMin.Margin = new System.Windows.Forms.Padding(4, 4, 4, 0);
            this.lblCodeMin.Name = "lblCodeMin";
            this.lblCodeMin.Size = new System.Drawing.Size(45, 17);
            this.lblCodeMin.TabIndex = 2;
            this.lblCodeMin.Text = "-2048";
            // 
            // lblCode
            // 
            this.lblCode.AutoSize = true;
            this.lblCode.Location = new System.Drawing.Point(4, 21);
            this.lblCode.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblCode.Name = "lblCode";
            this.lblCode.Size = new System.Drawing.Size(45, 17);
            this.lblCode.TabIndex = 8;
            this.lblCode.Text = "Code:";
            // 
            // lblRangeExpr
            // 
            this.lblRangeExpr.AutoSize = true;
            this.tableLayoutPanel1.SetColumnSpan(this.lblRangeExpr, 2);
            this.lblRangeExpr.ForeColor = System.Drawing.SystemColors.ControlText;
            this.lblRangeExpr.Location = new System.Drawing.Point(4, 0);
            this.lblRangeExpr.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblRangeExpr.Name = "lblRangeExpr";
            this.lblRangeExpr.Padding = new System.Windows.Forms.Padding(0, 0, 0, 4);
            this.lblRangeExpr.Size = new System.Drawing.Size(126, 21);
            this.lblRangeExpr.TabIndex = 0;
            this.lblRangeExpr.Text = "Range expression:";
            // 
            // lblLSB
            // 
            this.lblLSB.AutoSize = true;
            this.tableLayoutPanel1.SetColumnSpan(this.lblLSB, 2);
            this.lblLSB.Location = new System.Drawing.Point(4, 113);
            this.lblLSB.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblLSB.Name = "lblLSB";
            this.lblLSB.Padding = new System.Windows.Forms.Padding(0, 15, 0, 0);
            this.lblLSB.Size = new System.Drawing.Size(133, 32);
            this.lblLSB.TabIndex = 0;
            this.lblLSB.Text = "LSB = Vref * 1/4096";
            // 
            // panel1
            // 
            this.panel1.AutoSize = true;
            this.panel1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.panel1.Controls.Add(this.tableLayoutPanel1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Margin = new System.Windows.Forms.Padding(4);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(493, 250);
            this.panel1.TabIndex = 6;
            // 
            // CyDynamicDataControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.AutoSize = true;
            this.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Controls.Add(this.panel1);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "CyDynamicDataControl";
            this.Size = new System.Drawing.Size(493, 250);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }
    }
}
