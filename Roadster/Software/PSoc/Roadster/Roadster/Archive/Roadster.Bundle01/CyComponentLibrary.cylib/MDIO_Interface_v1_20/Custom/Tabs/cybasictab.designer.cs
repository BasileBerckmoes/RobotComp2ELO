namespace MDIO_Interface_v1_20.Tabs
{
    partial class CyBasicTab
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyBasicTab));
            this.gbConfiguration = new System.Windows.Forms.GroupBox();
            this.rbAdvancedConfig = new System.Windows.Forms.RadioButton();
            this.rbBasicConfig = new System.Windows.Forms.RadioButton();
            this.gbPhysicalAddress = new System.Windows.Forms.GroupBox();
            this.m_flpAddress = new System.Windows.Forms.FlowLayoutPanel();
            this.labelPhysicalAddress = new System.Windows.Forms.Label();
            this.lbl0x = new System.Windows.Forms.Label();
            this.tbPhysicalAddress = new System.Windows.Forms.TextBox();
            this.pnlPhyAddressWidth = new System.Windows.Forms.Panel();
            this.lblPhyAddressWidth = new System.Windows.Forms.Label();
            this.rbAddressWidth5 = new System.Windows.Forms.RadioButton();
            this.rbAddressWidth3 = new System.Windows.Forms.RadioButton();
            this.rbFirmware = new System.Windows.Forms.RadioButton();
            this.rbHardware = new System.Windows.Forms.RadioButton();
            this.cbDeviceAddress = new System.Windows.Forms.ComboBox();
            this.lblDeviceAddress = new System.Windows.Forms.Label();
            this.chbEnableExternalOE = new System.Windows.Forms.CheckBox();
            this.gbConfiguration.SuspendLayout();
            this.gbPhysicalAddress.SuspendLayout();
            this.m_flpAddress.SuspendLayout();
            this.pnlPhyAddressWidth.SuspendLayout();
            this.SuspendLayout();
            // 
            // gbConfiguration
            // 
            this.gbConfiguration.Controls.Add(this.rbAdvancedConfig);
            this.gbConfiguration.Controls.Add(this.rbBasicConfig);
            this.gbConfiguration.ForeColor = System.Drawing.SystemColors.ControlText;
            resources.ApplyResources(this.gbConfiguration, "gbConfiguration");
            this.gbConfiguration.Name = "gbConfiguration";
            this.gbConfiguration.TabStop = false;
            // 
            // rbAdvancedConfig
            // 
            resources.ApplyResources(this.rbAdvancedConfig, "rbAdvancedConfig");
            this.rbAdvancedConfig.Checked = true;
            this.rbAdvancedConfig.Name = "rbAdvancedConfig";
            this.rbAdvancedConfig.TabStop = true;
            this.rbAdvancedConfig.UseVisualStyleBackColor = true;
            this.rbAdvancedConfig.CheckedChanged += new System.EventHandler(this.rbConfig_CheckedChanged);
            // 
            // rbBasicConfig
            // 
            resources.ApplyResources(this.rbBasicConfig, "rbBasicConfig");
            this.rbBasicConfig.Name = "rbBasicConfig";
            this.rbBasicConfig.UseVisualStyleBackColor = true;
            this.rbBasicConfig.CheckedChanged += new System.EventHandler(this.rbConfig_CheckedChanged);
            // 
            // gbPhysicalAddress
            // 
            this.gbPhysicalAddress.Controls.Add(this.m_flpAddress);
            this.gbPhysicalAddress.Controls.Add(this.pnlPhyAddressWidth);
            this.gbPhysicalAddress.Controls.Add(this.rbFirmware);
            this.gbPhysicalAddress.Controls.Add(this.rbHardware);
            this.gbPhysicalAddress.ForeColor = System.Drawing.SystemColors.ControlText;
            resources.ApplyResources(this.gbPhysicalAddress, "gbPhysicalAddress");
            this.gbPhysicalAddress.Name = "gbPhysicalAddress";
            this.gbPhysicalAddress.TabStop = false;
            // 
            // m_flpAddress
            // 
            resources.ApplyResources(this.m_flpAddress, "m_flpAddress");
            this.m_flpAddress.Controls.Add(this.labelPhysicalAddress);
            this.m_flpAddress.Controls.Add(this.lbl0x);
            this.m_flpAddress.Controls.Add(this.tbPhysicalAddress);
            this.m_flpAddress.Name = "m_flpAddress";
            // 
            // labelPhysicalAddress
            // 
            resources.ApplyResources(this.labelPhysicalAddress, "labelPhysicalAddress");
            this.labelPhysicalAddress.Name = "labelPhysicalAddress";
            // 
            // lbl0x
            // 
            resources.ApplyResources(this.lbl0x, "lbl0x");
            this.lbl0x.Name = "lbl0x";
            // 
            // tbPhysicalAddress
            // 
            resources.ApplyResources(this.tbPhysicalAddress, "tbPhysicalAddress");
            this.tbPhysicalAddress.Name = "tbPhysicalAddress";
            this.tbPhysicalAddress.TextChanged += new System.EventHandler(this.tbPhysicalAddress_TextChanged);
            // 
            // pnlPhyAddressWidth
            // 
            this.pnlPhyAddressWidth.Controls.Add(this.lblPhyAddressWidth);
            this.pnlPhyAddressWidth.Controls.Add(this.rbAddressWidth5);
            this.pnlPhyAddressWidth.Controls.Add(this.rbAddressWidth3);
            resources.ApplyResources(this.pnlPhyAddressWidth, "pnlPhyAddressWidth");
            this.pnlPhyAddressWidth.Name = "pnlPhyAddressWidth";
            // 
            // lblPhyAddressWidth
            // 
            resources.ApplyResources(this.lblPhyAddressWidth, "lblPhyAddressWidth");
            this.lblPhyAddressWidth.Name = "lblPhyAddressWidth";
            // 
            // rbAddressWidth5
            // 
            resources.ApplyResources(this.rbAddressWidth5, "rbAddressWidth5");
            this.rbAddressWidth5.Checked = true;
            this.rbAddressWidth5.Name = "rbAddressWidth5";
            this.rbAddressWidth5.TabStop = true;
            this.rbAddressWidth5.UseVisualStyleBackColor = true;
            this.rbAddressWidth5.CheckedChanged += new System.EventHandler(this.rbAddressWidth_CheckedChanged);
            // 
            // rbAddressWidth3
            // 
            resources.ApplyResources(this.rbAddressWidth3, "rbAddressWidth3");
            this.rbAddressWidth3.Name = "rbAddressWidth3";
            this.rbAddressWidth3.TabStop = true;
            this.rbAddressWidth3.UseVisualStyleBackColor = true;
            this.rbAddressWidth3.CheckedChanged += new System.EventHandler(this.rbAddressWidth_CheckedChanged);
            // 
            // rbFirmware
            // 
            resources.ApplyResources(this.rbFirmware, "rbFirmware");
            this.rbFirmware.Checked = true;
            this.rbFirmware.Name = "rbFirmware";
            this.rbFirmware.TabStop = true;
            this.rbFirmware.UseVisualStyleBackColor = true;
            this.rbFirmware.CheckedChanged += new System.EventHandler(this.rbPhAddress_CheckedChanged);
            // 
            // rbHardware
            // 
            resources.ApplyResources(this.rbHardware, "rbHardware");
            this.rbHardware.Name = "rbHardware";
            this.rbHardware.UseVisualStyleBackColor = true;
            this.rbHardware.CheckedChanged += new System.EventHandler(this.rbPhAddress_CheckedChanged);
            // 
            // cbDeviceAddress
            // 
            this.cbDeviceAddress.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbDeviceAddress.FormattingEnabled = true;
            resources.ApplyResources(this.cbDeviceAddress, "cbDeviceAddress");
            this.cbDeviceAddress.Name = "cbDeviceAddress";
            this.cbDeviceAddress.SelectedIndexChanged += new System.EventHandler(this.cbDeviceAddress_SelectedIndexChanged);
            this.cbDeviceAddress.Format += new System.Windows.Forms.ListControlConvertEventHandler(this.cbDeviceAddress_Format);
            // 
            // lblDeviceAddress
            // 
            resources.ApplyResources(this.lblDeviceAddress, "lblDeviceAddress");
            this.lblDeviceAddress.Name = "lblDeviceAddress";
            // 
            // chbEnableExternalOE
            // 
            resources.ApplyResources(this.chbEnableExternalOE, "chbEnableExternalOE");
            this.chbEnableExternalOE.Name = "chbEnableExternalOE";
            this.chbEnableExternalOE.UseVisualStyleBackColor = true;
            this.chbEnableExternalOE.CheckedChanged += new System.EventHandler(this.chbEnableExternalOE_CheckedChanged);
            // 
            // CyBasicTab
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.chbEnableExternalOE);
            this.Controls.Add(this.lblDeviceAddress);
            this.Controls.Add(this.cbDeviceAddress);
            this.Controls.Add(this.gbPhysicalAddress);
            this.Controls.Add(this.gbConfiguration);
            this.Name = "CyBasicTab";
            this.gbConfiguration.ResumeLayout(false);
            this.gbConfiguration.PerformLayout();
            this.gbPhysicalAddress.ResumeLayout(false);
            this.gbPhysicalAddress.PerformLayout();
            this.m_flpAddress.ResumeLayout(false);
            this.m_flpAddress.PerformLayout();
            this.pnlPhyAddressWidth.ResumeLayout(false);
            this.pnlPhyAddressWidth.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox gbPhysicalAddress;
        private System.Windows.Forms.Label labelPhysicalAddress;
        private System.Windows.Forms.TextBox tbPhysicalAddress;
        private System.Windows.Forms.RadioButton rbFirmware;
        private System.Windows.Forms.RadioButton rbHardware;
        private System.Windows.Forms.GroupBox gbConfiguration;
        private System.Windows.Forms.RadioButton rbAdvancedConfig;
        private System.Windows.Forms.RadioButton rbBasicConfig;
        private System.Windows.Forms.ComboBox cbDeviceAddress;
        private System.Windows.Forms.Label lblDeviceAddress;
        private System.Windows.Forms.CheckBox chbEnableExternalOE;
        private System.Windows.Forms.Label lbl0x;
        private System.Windows.Forms.RadioButton rbAddressWidth3;
        private System.Windows.Forms.RadioButton rbAddressWidth5;
        private System.Windows.Forms.Label lblPhyAddressWidth;
        private System.Windows.Forms.Panel pnlPhyAddressWidth;
        private System.Windows.Forms.FlowLayoutPanel m_flpAddress;
    }
}
