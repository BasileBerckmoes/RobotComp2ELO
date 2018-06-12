/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

namespace Bootloadable_v1_50
{
    partial class CyGeneralPage
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyGeneralPage));
            this.errProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.labelAppVersion = new System.Windows.Forms.Label();
            this.labelAppID = new System.Windows.Forms.Label();
            this.labelAppCustomID = new System.Windows.Forms.Label();
            this.textBoxAppVersion = new System.Windows.Forms.TextBox();
            this.textBoxAppID = new System.Windows.Forms.TextBox();
            this.textBoxAppCustomID = new System.Windows.Forms.TextBox();
            this.checkBoxAutoImage = new System.Windows.Forms.CheckBox();
            this.labelPlacementAddress = new System.Windows.Forms.Label();
            this.textBoxPlacementAddress = new System.Windows.Forms.TextBox();
            this.labelChecksumExcludeSize = new System.Windows.Forms.Label();
            this.numUpDownChecksumExcludeSize = new System.Windows.Forms.NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)(this.errProvider)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownChecksumExcludeSize)).BeginInit();
            this.SuspendLayout();
            // 
            // errProvider
            // 
            this.errProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.errProvider.ContainerControl = this;
            // 
            // labelAppVersion
            // 
            resources.ApplyResources(this.labelAppVersion, "labelAppVersion");
            this.labelAppVersion.Name = "labelAppVersion";
            // 
            // labelAppID
            // 
            resources.ApplyResources(this.labelAppID, "labelAppID");
            this.labelAppID.Name = "labelAppID";
            // 
            // labelAppCustomID
            // 
            resources.ApplyResources(this.labelAppCustomID, "labelAppCustomID");
            this.labelAppCustomID.Name = "labelAppCustomID";
            // 
            // textBoxAppVersion
            // 
            resources.ApplyResources(this.textBoxAppVersion, "textBoxAppVersion");
            this.textBoxAppVersion.Name = "textBoxAppVersion";
            this.textBoxAppVersion.TextChanged += new System.EventHandler(this.textBoxHex_TextChanged);
            // 
            // textBoxAppID
            // 
            resources.ApplyResources(this.textBoxAppID, "textBoxAppID");
            this.textBoxAppID.Name = "textBoxAppID";
            this.textBoxAppID.TextChanged += new System.EventHandler(this.textBoxHex_TextChanged);
            // 
            // textBoxAppCustomID
            // 
            resources.ApplyResources(this.textBoxAppCustomID, "textBoxAppCustomID");
            this.textBoxAppCustomID.Name = "textBoxAppCustomID";
            this.textBoxAppCustomID.TextChanged += new System.EventHandler(this.textBoxHex_TextChanged);
            // 
            // checkBoxAutoImage
            // 
            resources.ApplyResources(this.checkBoxAutoImage, "checkBoxAutoImage");
            this.checkBoxAutoImage.Checked = true;
            this.checkBoxAutoImage.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxAutoImage.Name = "checkBoxAutoImage";
            this.checkBoxAutoImage.UseVisualStyleBackColor = true;
            this.checkBoxAutoImage.CheckedChanged += new System.EventHandler(this.checkBoxAutoImage_CheckedChanged);
            // 
            // labelPlacementAddress
            // 
            resources.ApplyResources(this.labelPlacementAddress, "labelPlacementAddress");
            this.labelPlacementAddress.Name = "labelPlacementAddress";
            // 
            // textBoxPlacementAddress
            // 
            resources.ApplyResources(this.textBoxPlacementAddress, "textBoxPlacementAddress");
            this.textBoxPlacementAddress.Name = "textBoxPlacementAddress";
            this.textBoxPlacementAddress.TextChanged += new System.EventHandler(this.textBoxHex_TextChanged);
            // 
            // labelChecksumExcludeSize
            // 
            resources.ApplyResources(this.labelChecksumExcludeSize, "labelChecksumExcludeSize");
            this.labelChecksumExcludeSize.Name = "labelChecksumExcludeSize";
            // 
            // numUpDownChecksumExcludeSize
            // 
            resources.ApplyResources(this.numUpDownChecksumExcludeSize, "numUpDownChecksumExcludeSize");
            this.numUpDownChecksumExcludeSize.Name = "numUpDownChecksumExcludeSize";
            this.numUpDownChecksumExcludeSize.ValueChanged += new System.EventHandler(this.numUpDownChecksumExcludeSize_ValueChanged);
            // 
            // CyGeneralPage
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.numUpDownChecksumExcludeSize);
            this.Controls.Add(this.labelChecksumExcludeSize);
            this.Controls.Add(this.textBoxPlacementAddress);
            this.Controls.Add(this.labelPlacementAddress);
            this.Controls.Add(this.checkBoxAutoImage);
            this.Controls.Add(this.textBoxAppCustomID);
            this.Controls.Add(this.textBoxAppID);
            this.Controls.Add(this.textBoxAppVersion);
            this.Controls.Add(this.labelAppCustomID);
            this.Controls.Add(this.labelAppID);
            this.Controls.Add(this.labelAppVersion);
            this.Name = "CyGeneralPage";
            ((System.ComponentModel.ISupportInitialize)(this.errProvider)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numUpDownChecksumExcludeSize)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ErrorProvider errProvider;
        private System.Windows.Forms.Label labelAppID;
        private System.Windows.Forms.Label labelAppVersion;
        private System.Windows.Forms.TextBox textBoxAppCustomID;
        private System.Windows.Forms.TextBox textBoxAppID;
        private System.Windows.Forms.TextBox textBoxAppVersion;
        private System.Windows.Forms.Label labelAppCustomID;
        private System.Windows.Forms.TextBox textBoxPlacementAddress;
        private System.Windows.Forms.Label labelPlacementAddress;
        private System.Windows.Forms.CheckBox checkBoxAutoImage;
        private System.Windows.Forms.Label labelChecksumExcludeSize;
        private System.Windows.Forms.NumericUpDown numUpDownChecksumExcludeSize;
    }
}
