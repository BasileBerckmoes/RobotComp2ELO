/*******************************************************************************
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

namespace Cypress.Components.System.cy_vref_v1_70
{
    internal partial class CyVRefIDControl
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private global::System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                PerformDispose();
            }

            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.m_vRefComboBox = new global::System.Windows.Forms.ComboBox();
            this.label1 = new global::System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // m_vRefComboBox
            // 
            this.m_vRefComboBox.Anchor = ((global::System.Windows.Forms.AnchorStyles)(((global::System.Windows.Forms.AnchorStyles.Top | global::System.Windows.Forms.AnchorStyles.Left)
                        | global::System.Windows.Forms.AnchorStyles.Right)));
            this.m_vRefComboBox.FormattingEnabled = true;
            this.m_vRefComboBox.Location = new global::System.Drawing.Point(93, 3);
            this.m_vRefComboBox.Name = "m_vRefComboBox";
            this.m_vRefComboBox.Size = new global::System.Drawing.Size(171, 24);
            this.m_vRefComboBox.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new global::System.Drawing.Point(3, 6);
            this.label1.Name = "label1";
            this.label1.Size = new global::System.Drawing.Size(84, 17);
            this.label1.TabIndex = 1;
            this.label1.Text = "VRef Name:";
            // 
            // CyVRefIDControl
            // 
            this.AutoScaleDimensions = new global::System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = global::System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.label1);
            this.Controls.Add(this.m_vRefComboBox);
            this.Name = "CyVRefIDControl";
            this.Size = new global::System.Drawing.Size(267, 31);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private global::System.Windows.Forms.ComboBox m_vRefComboBox;
        private global::System.Windows.Forms.Label label1;
    }
}
