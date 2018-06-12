namespace FanController_v4_0
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
            this.m_gbFanMethod = new System.Windows.Forms.GroupBox();
            this.m_pnlFanMethodAuto = new System.Windows.Forms.Panel();
            this.m_pnlAutoSettings = new System.Windows.Forms.Panel();
            this.m_nudControlLoopPeriod = new System.Windows.Forms.NumericUpDown();
            this.m_lblPeriod = new System.Windows.Forms.Label();
            this.m_lblTolerance = new System.Windows.Forms.Label();
            this.m_cbFanTolerance = new System.Windows.Forms.ComboBox();
            this.m_chbANR = new System.Windows.Forms.CheckBox();
            this.m_rbFirmware = new System.Windows.Forms.RadioButton();
            this.m_rbHardware = new System.Windows.Forms.RadioButton();
            this.m_rbAutomatic = new System.Windows.Forms.RadioButton();
            this.m_rbManual = new System.Windows.Forms.RadioButton();
            this.m_gbAlerts = new System.Windows.Forms.GroupBox();
            this.m_chbAltSpeedFailure = new System.Windows.Forms.CheckBox();
            this.m_chbAltFanStall = new System.Windows.Forms.CheckBox();
            this.m_chbDisplayBus = new System.Windows.Forms.CheckBox();
            this.m_gbTerminals = new System.Windows.Forms.GroupBox();
            this.m_chbExternalClock = new System.Windows.Forms.CheckBox();
            this.m_gbFanMethod.SuspendLayout();
            this.m_pnlFanMethodAuto.SuspendLayout();
            this.m_pnlAutoSettings.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudControlLoopPeriod)).BeginInit();
            this.m_gbAlerts.SuspendLayout();
            this.m_gbTerminals.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_gbFanMethod
            // 
            this.m_gbFanMethod.Controls.Add(this.m_pnlFanMethodAuto);
            this.m_gbFanMethod.Controls.Add(this.m_rbAutomatic);
            this.m_gbFanMethod.Controls.Add(this.m_rbManual);
            resources.ApplyResources(this.m_gbFanMethod, "m_gbFanMethod");
            this.m_gbFanMethod.Name = "m_gbFanMethod";
            this.m_gbFanMethod.TabStop = false;
            // 
            // m_pnlFanMethodAuto
            // 
            this.m_pnlFanMethodAuto.Controls.Add(this.m_pnlAutoSettings);
            this.m_pnlFanMethodAuto.Controls.Add(this.m_rbFirmware);
            this.m_pnlFanMethodAuto.Controls.Add(this.m_rbHardware);
            resources.ApplyResources(this.m_pnlFanMethodAuto, "m_pnlFanMethodAuto");
            this.m_pnlFanMethodAuto.Name = "m_pnlFanMethodAuto";
            // 
            // m_pnlAutoSettings
            // 
            this.m_pnlAutoSettings.Controls.Add(this.m_nudControlLoopPeriod);
            this.m_pnlAutoSettings.Controls.Add(this.m_lblPeriod);
            this.m_pnlAutoSettings.Controls.Add(this.m_lblTolerance);
            this.m_pnlAutoSettings.Controls.Add(this.m_cbFanTolerance);
            this.m_pnlAutoSettings.Controls.Add(this.m_chbANR);
            resources.ApplyResources(this.m_pnlAutoSettings, "m_pnlAutoSettings");
            this.m_pnlAutoSettings.Name = "m_pnlAutoSettings";
            // 
            // m_nudControlLoopPeriod
            // 
            this.m_nudControlLoopPeriod.DecimalPlaces = 2;
            this.m_nudControlLoopPeriod.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            resources.ApplyResources(this.m_nudControlLoopPeriod, "m_nudControlLoopPeriod");
            this.m_nudControlLoopPeriod.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            131072});
            this.m_nudControlLoopPeriod.Name = "m_nudControlLoopPeriod";
            // 
            // m_lblPeriod
            // 
            resources.ApplyResources(this.m_lblPeriod, "m_lblPeriod");
            this.m_lblPeriod.Name = "m_lblPeriod";
            // 
            // m_lblTolerance
            // 
            resources.ApplyResources(this.m_lblTolerance, "m_lblTolerance");
            this.m_lblTolerance.Name = "m_lblTolerance";
            // 
            // m_cbFanTolerance
            // 
            this.m_cbFanTolerance.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbFanTolerance.FormattingEnabled = true;
            resources.ApplyResources(this.m_cbFanTolerance, "m_cbFanTolerance");
            this.m_cbFanTolerance.Name = "m_cbFanTolerance";
            this.m_cbFanTolerance.SelectedIndexChanged += new System.EventHandler(this.m_cbFanTolerance_SelectedIndexChanged);
            // 
            // m_chbANR
            // 
            resources.ApplyResources(this.m_chbANR, "m_chbANR");
            this.m_chbANR.Name = "m_chbANR";
            this.m_chbANR.UseVisualStyleBackColor = true;
            this.m_chbANR.CheckedChanged += new System.EventHandler(this.m_chbANR_CheckedChanged);
            // 
            // m_rbFirmware
            // 
            resources.ApplyResources(this.m_rbFirmware, "m_rbFirmware");
            this.m_rbFirmware.Name = "m_rbFirmware";
            this.m_rbFirmware.UseVisualStyleBackColor = true;
            this.m_rbFirmware.CheckedChanged += new System.EventHandler(this.rbMode_CheckedChanged);
            // 
            // m_rbHardware
            // 
            resources.ApplyResources(this.m_rbHardware, "m_rbHardware");
            this.m_rbHardware.Checked = true;
            this.m_rbHardware.Name = "m_rbHardware";
            this.m_rbHardware.TabStop = true;
            this.m_rbHardware.UseVisualStyleBackColor = true;
            this.m_rbHardware.CheckedChanged += new System.EventHandler(this.rbMode_CheckedChanged);
            // 
            // m_rbAutomatic
            // 
            resources.ApplyResources(this.m_rbAutomatic, "m_rbAutomatic");
            this.m_rbAutomatic.Name = "m_rbAutomatic";
            this.m_rbAutomatic.TabStop = true;
            this.m_rbAutomatic.UseVisualStyleBackColor = true;
            this.m_rbAutomatic.CheckedChanged += new System.EventHandler(this.rbMode_CheckedChanged);
            // 
            // m_rbManual
            // 
            resources.ApplyResources(this.m_rbManual, "m_rbManual");
            this.m_rbManual.Name = "m_rbManual";
            this.m_rbManual.TabStop = true;
            this.m_rbManual.UseVisualStyleBackColor = true;
            this.m_rbManual.CheckedChanged += new System.EventHandler(this.rbMode_CheckedChanged);
            // 
            // m_gbAlerts
            // 
            this.m_gbAlerts.Controls.Add(this.m_chbAltSpeedFailure);
            this.m_gbAlerts.Controls.Add(this.m_chbAltFanStall);
            resources.ApplyResources(this.m_gbAlerts, "m_gbAlerts");
            this.m_gbAlerts.Name = "m_gbAlerts";
            this.m_gbAlerts.TabStop = false;
            // 
            // m_chbAltSpeedFailure
            // 
            resources.ApplyResources(this.m_chbAltSpeedFailure, "m_chbAltSpeedFailure");
            this.m_chbAltSpeedFailure.Name = "m_chbAltSpeedFailure";
            this.m_chbAltSpeedFailure.UseVisualStyleBackColor = true;
            this.m_chbAltSpeedFailure.CheckedChanged += new System.EventHandler(this.chbAlerts_CheckedChanged);
            // 
            // m_chbAltFanStall
            // 
            resources.ApplyResources(this.m_chbAltFanStall, "m_chbAltFanStall");
            this.m_chbAltFanStall.Name = "m_chbAltFanStall";
            this.m_chbAltFanStall.UseVisualStyleBackColor = true;
            this.m_chbAltFanStall.CheckedChanged += new System.EventHandler(this.chbAlerts_CheckedChanged);
            // 
            // m_chbDisplayBus
            // 
            resources.ApplyResources(this.m_chbDisplayBus, "m_chbDisplayBus");
            this.m_chbDisplayBus.Name = "m_chbDisplayBus";
            this.m_chbDisplayBus.UseVisualStyleBackColor = true;
            this.m_chbDisplayBus.CheckedChanged += new System.EventHandler(this.m_chbDisplayBus_CheckedChanged);
            // 
            // m_gbTerminals
            // 
            this.m_gbTerminals.Controls.Add(this.m_chbExternalClock);
            this.m_gbTerminals.Controls.Add(this.m_chbDisplayBus);
            resources.ApplyResources(this.m_gbTerminals, "m_gbTerminals");
            this.m_gbTerminals.Name = "m_gbTerminals";
            this.m_gbTerminals.TabStop = false;
            // 
            // m_chbExternalClock
            // 
            resources.ApplyResources(this.m_chbExternalClock, "m_chbExternalClock");
            this.m_chbExternalClock.Name = "m_chbExternalClock";
            this.m_chbExternalClock.UseVisualStyleBackColor = true;
            this.m_chbExternalClock.CheckedChanged += new System.EventHandler(this.m_chbExternalClock_CheckedChanged);
            // 
            // CyBasicTab
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_gbTerminals);
            this.Controls.Add(this.m_gbAlerts);
            this.Controls.Add(this.m_gbFanMethod);
            this.Name = "CyBasicTab";
            this.m_gbFanMethod.ResumeLayout(false);
            this.m_gbFanMethod.PerformLayout();
            this.m_pnlFanMethodAuto.ResumeLayout(false);
            this.m_pnlFanMethodAuto.PerformLayout();
            this.m_pnlAutoSettings.ResumeLayout(false);
            this.m_pnlAutoSettings.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudControlLoopPeriod)).EndInit();
            this.m_gbAlerts.ResumeLayout(false);
            this.m_gbAlerts.PerformLayout();
            this.m_gbTerminals.ResumeLayout(false);
            this.m_gbTerminals.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox m_gbFanMethod;
        private System.Windows.Forms.RadioButton m_rbFirmware;
        private System.Windows.Forms.RadioButton m_rbHardware;
        private System.Windows.Forms.GroupBox m_gbAlerts;
        private System.Windows.Forms.CheckBox m_chbAltSpeedFailure;
        private System.Windows.Forms.CheckBox m_chbAltFanStall;
        private System.Windows.Forms.Label m_lblPeriod;
        private System.Windows.Forms.CheckBox m_chbANR;
        private System.Windows.Forms.Label m_lblTolerance;
        private System.Windows.Forms.ComboBox m_cbFanTolerance;
        private System.Windows.Forms.GroupBox m_gbTerminals;
        private System.Windows.Forms.CheckBox m_chbDisplayBus;
        private System.Windows.Forms.CheckBox m_chbExternalClock;
        private System.Windows.Forms.Panel m_pnlFanMethodAuto;
        private System.Windows.Forms.RadioButton m_rbAutomatic;
        private System.Windows.Forms.RadioButton m_rbManual;
        private System.Windows.Forms.Panel m_pnlAutoSettings;
        private System.Windows.Forms.NumericUpDown m_nudControlLoopPeriod;


    }
}
