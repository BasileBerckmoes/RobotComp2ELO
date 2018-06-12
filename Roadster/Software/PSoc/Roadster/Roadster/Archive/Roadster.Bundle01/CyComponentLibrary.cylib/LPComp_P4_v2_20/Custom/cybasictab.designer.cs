namespace LPComp_P4_v2_20
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

                if (m_symbol != null)
                {
                    m_symbol.Dispose();
                }
                if (m_graph != null)
                {
                    m_graph.Dispose();
                }
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
            this.groupBoxHysteresis = new System.Windows.Forms.GroupBox();
            this.rbHysteresisDisable = new System.Windows.Forms.RadioButton();
            this.rbHysteresisEnable = new System.Windows.Forms.RadioButton();
            this.groupBoxSpeedPower = new System.Windows.Forms.GroupBox();
            this.rbSpeedHigh = new System.Windows.Forms.RadioButton();
            this.rbSpeedMedium = new System.Windows.Forms.RadioButton();
            this.rbSpeedSlow = new System.Windows.Forms.RadioButton();
            this.groupBoxOuputConfig = new System.Windows.Forms.GroupBox();
            this.rbPulse = new System.Windows.Forms.RadioButton();
            this.rbSynchronized = new System.Windows.Forms.RadioButton();
            this.rbDirect = new System.Windows.Forms.RadioButton();
            this.groupBoxPulseInterrConfig = new System.Windows.Forms.GroupBox();
            this.labelNote2SuperscriptFalling = new System.Windows.Forms.Label();
            this.labelNote2SuperscriptRising = new System.Windows.Forms.Label();
            this.rbInterruptBoth = new System.Windows.Forms.RadioButton();
            this.rbInterruptFalling = new System.Windows.Forms.RadioButton();
            this.rbInterruptRising = new System.Windows.Forms.RadioButton();
            this.rbInterruptDisabled = new System.Windows.Forms.RadioButton();
            this.pbSymbol = new System.Windows.Forms.PictureBox();
            this.pbGraph = new System.Windows.Forms.PictureBox();
            this.chB_IntEnabled = new System.Windows.Forms.CheckBox();
            this.label_Note1 = new System.Windows.Forms.Label();
            this.label_Note2 = new System.Windows.Forms.Label();
            this.labelNote1SuperscriptInt = new System.Windows.Forms.Label();
            this.labelNote1SuperscriptPulse = new System.Windows.Forms.Label();
            this.groupBoxHysteresis.SuspendLayout();
            this.groupBoxSpeedPower.SuspendLayout();
            this.groupBoxOuputConfig.SuspendLayout();
            this.groupBoxPulseInterrConfig.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbSymbol)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbGraph)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBoxHysteresis
            // 
            this.groupBoxHysteresis.Controls.Add(this.rbHysteresisDisable);
            this.groupBoxHysteresis.Controls.Add(this.rbHysteresisEnable);
            this.groupBoxHysteresis.Location = new System.Drawing.Point(167, 3);
            this.groupBoxHysteresis.Name = "groupBoxHysteresis";
            this.groupBoxHysteresis.Size = new System.Drawing.Size(158, 86);
            this.groupBoxHysteresis.TabIndex = 1;
            this.groupBoxHysteresis.TabStop = false;
            this.groupBoxHysteresis.Text = "Hysteresis";
            // 
            // rbHysteresisDisable
            // 
            this.rbHysteresisDisable.AutoSize = true;
            this.rbHysteresisDisable.Location = new System.Drawing.Point(6, 42);
            this.rbHysteresisDisable.Name = "rbHysteresisDisable";
            this.rbHysteresisDisable.Size = new System.Drawing.Size(60, 17);
            this.rbHysteresisDisable.TabIndex = 2;
            this.rbHysteresisDisable.Text = "Disable";
            this.rbHysteresisDisable.UseVisualStyleBackColor = true;
            // 
            // rbHysteresisEnable
            // 
            this.rbHysteresisEnable.AutoSize = true;
            this.rbHysteresisEnable.Checked = true;
            this.rbHysteresisEnable.Location = new System.Drawing.Point(6, 19);
            this.rbHysteresisEnable.Name = "rbHysteresisEnable";
            this.rbHysteresisEnable.Size = new System.Drawing.Size(58, 17);
            this.rbHysteresisEnable.TabIndex = 0;
            this.rbHysteresisEnable.TabStop = true;
            this.rbHysteresisEnable.Text = "Enable";
            this.rbHysteresisEnable.UseVisualStyleBackColor = true;
            // 
            // groupBoxSpeedPower
            // 
            this.groupBoxSpeedPower.Controls.Add(this.rbSpeedHigh);
            this.groupBoxSpeedPower.Controls.Add(this.rbSpeedMedium);
            this.groupBoxSpeedPower.Controls.Add(this.rbSpeedSlow);
            this.groupBoxSpeedPower.Location = new System.Drawing.Point(167, 95);
            this.groupBoxSpeedPower.Name = "groupBoxSpeedPower";
            this.groupBoxSpeedPower.Size = new System.Drawing.Size(158, 86);
            this.groupBoxSpeedPower.TabIndex = 3;
            this.groupBoxSpeedPower.TabStop = false;
            this.groupBoxSpeedPower.Text = "Speed/Power";
            // 
            // rbSpeedHigh
            // 
            this.rbSpeedHigh.AutoSize = true;
            this.rbSpeedHigh.Location = new System.Drawing.Point(6, 65);
            this.rbSpeedHigh.Name = "rbSpeedHigh";
            this.rbSpeedHigh.Size = new System.Drawing.Size(83, 17);
            this.rbSpeedHigh.TabIndex = 2;
            this.rbSpeedHigh.Text = "Fast/Normal";
            this.rbSpeedHigh.UseVisualStyleBackColor = true;
            // 
            // rbSpeedMedium
            // 
            this.rbSpeedMedium.AutoSize = true;
            this.rbSpeedMedium.Location = new System.Drawing.Point(6, 42);
            this.rbSpeedMedium.Name = "rbSpeedMedium";
            this.rbSpeedMedium.Size = new System.Drawing.Size(87, 17);
            this.rbSpeedMedium.TabIndex = 1;
            this.rbSpeedMedium.Text = "Medium/Low";
            this.rbSpeedMedium.UseVisualStyleBackColor = true;
            // 
            // rbSpeedSlow
            // 
            this.rbSpeedSlow.AutoSize = true;
            this.rbSpeedSlow.Checked = true;
            this.rbSpeedSlow.Location = new System.Drawing.Point(6, 19);
            this.rbSpeedSlow.Name = "rbSpeedSlow";
            this.rbSpeedSlow.Size = new System.Drawing.Size(94, 17);
            this.rbSpeedSlow.TabIndex = 0;
            this.rbSpeedSlow.TabStop = true;
            this.rbSpeedSlow.Text = "Slow/Ultra low";
            this.rbSpeedSlow.UseVisualStyleBackColor = true;
            // 
            // groupBoxOuputConfig
            // 
            this.groupBoxOuputConfig.Controls.Add(this.rbPulse);
            this.groupBoxOuputConfig.Controls.Add(this.rbSynchronized);
            this.groupBoxOuputConfig.Controls.Add(this.rbDirect);
            this.groupBoxOuputConfig.Location = new System.Drawing.Point(3, 3);
            this.groupBoxOuputConfig.Name = "groupBoxOuputConfig";
            this.groupBoxOuputConfig.Size = new System.Drawing.Size(158, 86);
            this.groupBoxOuputConfig.TabIndex = 0;
            this.groupBoxOuputConfig.TabStop = false;
            this.groupBoxOuputConfig.Text = "Output configuration";
            // 
            // rbPulse
            // 
            this.rbPulse.AutoSize = true;
            this.rbPulse.Location = new System.Drawing.Point(6, 65);
            this.rbPulse.Name = "rbPulse";
            this.rbPulse.Size = new System.Drawing.Size(51, 17);
            this.rbPulse.TabIndex = 2;
            this.rbPulse.Text = "Pulse";
            this.rbPulse.UseVisualStyleBackColor = true;
            // 
            // rbSynchronized
            // 
            this.rbSynchronized.AutoSize = true;
            this.rbSynchronized.Location = new System.Drawing.Point(6, 42);
            this.rbSynchronized.Name = "rbSynchronized";
            this.rbSynchronized.Size = new System.Drawing.Size(89, 17);
            this.rbSynchronized.TabIndex = 1;
            this.rbSynchronized.Text = "Synchronized";
            this.rbSynchronized.UseVisualStyleBackColor = true;
            // 
            // rbDirect
            // 
            this.rbDirect.AutoSize = true;
            this.rbDirect.Checked = true;
            this.rbDirect.Location = new System.Drawing.Point(6, 19);
            this.rbDirect.Name = "rbDirect";
            this.rbDirect.Size = new System.Drawing.Size(53, 17);
            this.rbDirect.TabIndex = 0;
            this.rbDirect.TabStop = true;
            this.rbDirect.Text = "Direct";
            this.rbDirect.UseVisualStyleBackColor = true;
            // 
            // groupBoxPulseInterrConfig
            // 
            this.groupBoxPulseInterrConfig.Controls.Add(this.labelNote2SuperscriptFalling);
            this.groupBoxPulseInterrConfig.Controls.Add(this.labelNote2SuperscriptRising);
            this.groupBoxPulseInterrConfig.Controls.Add(this.rbInterruptBoth);
            this.groupBoxPulseInterrConfig.Controls.Add(this.rbInterruptFalling);
            this.groupBoxPulseInterrConfig.Controls.Add(this.rbInterruptRising);
            this.groupBoxPulseInterrConfig.Controls.Add(this.rbInterruptDisabled);
            this.groupBoxPulseInterrConfig.Location = new System.Drawing.Point(3, 95);
            this.groupBoxPulseInterrConfig.Name = "groupBoxPulseInterrConfig";
            this.groupBoxPulseInterrConfig.Size = new System.Drawing.Size(158, 109);
            this.groupBoxPulseInterrConfig.TabIndex = 2;
            this.groupBoxPulseInterrConfig.TabStop = false;
            this.groupBoxPulseInterrConfig.Text = "Pulse/Interrupt configuration";
            // 
            // labelNote2SuperscriptFalling
            // 
            this.labelNote2SuperscriptFalling.AutoSize = true;
            this.labelNote2SuperscriptFalling.Font = new System.Drawing.Font("Microsoft Sans Serif", 6F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelNote2SuperscriptFalling.Location = new System.Drawing.Point(81, 62);
            this.labelNote2SuperscriptFalling.Margin = new System.Windows.Forms.Padding(0);
            this.labelNote2SuperscriptFalling.Name = "labelNote2SuperscriptFalling";
            this.labelNote2SuperscriptFalling.Size = new System.Drawing.Size(9, 9);
            this.labelNote2SuperscriptFalling.TabIndex = 10;
            this.labelNote2SuperscriptFalling.Text = "2";
            // 
            // labelNote2SuperscriptRising
            // 
            this.labelNote2SuperscriptRising.AutoSize = true;
            this.labelNote2SuperscriptRising.Font = new System.Drawing.Font("Microsoft Sans Serif", 6F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelNote2SuperscriptRising.Location = new System.Drawing.Point(81, 42);
            this.labelNote2SuperscriptRising.Margin = new System.Windows.Forms.Padding(0);
            this.labelNote2SuperscriptRising.Name = "labelNote2SuperscriptRising";
            this.labelNote2SuperscriptRising.Size = new System.Drawing.Size(9, 9);
            this.labelNote2SuperscriptRising.TabIndex = 9;
            this.labelNote2SuperscriptRising.Text = "2";
            // 
            // rbInterruptBoth
            // 
            this.rbInterruptBoth.AutoSize = true;
            this.rbInterruptBoth.Location = new System.Drawing.Point(6, 88);
            this.rbInterruptBoth.Name = "rbInterruptBoth";
            this.rbInterruptBoth.Size = new System.Drawing.Size(79, 17);
            this.rbInterruptBoth.TabIndex = 3;
            this.rbInterruptBoth.Text = "Both edges";
            this.rbInterruptBoth.UseVisualStyleBackColor = true;
            // 
            // rbInterruptFalling
            // 
            this.rbInterruptFalling.AutoSize = true;
            this.rbInterruptFalling.Location = new System.Drawing.Point(6, 65);
            this.rbInterruptFalling.Name = "rbInterruptFalling";
            this.rbInterruptFalling.Size = new System.Drawing.Size(82, 17);
            this.rbInterruptFalling.TabIndex = 2;
            this.rbInterruptFalling.Text = "Falling edge";
            this.rbInterruptFalling.UseVisualStyleBackColor = true;
            // 
            // rbInterruptRising
            // 
            this.rbInterruptRising.AutoSize = true;
            this.rbInterruptRising.Location = new System.Drawing.Point(6, 42);
            this.rbInterruptRising.Name = "rbInterruptRising";
            this.rbInterruptRising.Size = new System.Drawing.Size(81, 17);
            this.rbInterruptRising.TabIndex = 1;
            this.rbInterruptRising.Text = "Rising edge";
            this.rbInterruptRising.UseVisualStyleBackColor = true;
            // 
            // rbInterruptDisabled
            // 
            this.rbInterruptDisabled.AutoSize = true;
            this.rbInterruptDisabled.Checked = true;
            this.rbInterruptDisabled.Location = new System.Drawing.Point(6, 19);
            this.rbInterruptDisabled.Name = "rbInterruptDisabled";
            this.rbInterruptDisabled.Size = new System.Drawing.Size(66, 17);
            this.rbInterruptDisabled.TabIndex = 0;
            this.rbInterruptDisabled.TabStop = true;
            this.rbInterruptDisabled.Text = "Disabled";
            this.rbInterruptDisabled.UseVisualStyleBackColor = true;
            // 
            // pbSymbol
            // 
            this.pbSymbol.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pbSymbol.Location = new System.Drawing.Point(331, 10);
            this.pbSymbol.Name = "pbSymbol";
            this.pbSymbol.Size = new System.Drawing.Size(100, 100);
            this.pbSymbol.TabIndex = 4;
            this.pbSymbol.TabStop = false;
            // 
            // pbGraph
            // 
            this.pbGraph.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pbGraph.Location = new System.Drawing.Point(3, 236);
            this.pbGraph.Name = "pbGraph";
            this.pbGraph.Size = new System.Drawing.Size(428, 210);
            this.pbGraph.TabIndex = 5;
            this.pbGraph.TabStop = false;
            // 
            // chB_IntEnabled
            // 
            this.chB_IntEnabled.AutoSize = true;
            this.chB_IntEnabled.Location = new System.Drawing.Point(173, 184);
            this.chB_IntEnabled.Name = "chB_IntEnabled";
            this.chB_IntEnabled.Size = new System.Drawing.Size(107, 17);
            this.chB_IntEnabled.TabIndex = 4;
            this.chB_IntEnabled.Text = "Interrupt Enabled";
            this.chB_IntEnabled.UseVisualStyleBackColor = true;
            // 
            // label_Note1
            // 
            this.label_Note1.AutoSize = true;
            this.label_Note1.Location = new System.Drawing.Point(6, 207);
            this.label_Note1.Name = "label_Note1";
            this.label_Note1.Size = new System.Drawing.Size(368, 13);
            this.label_Note1.TabIndex = 7;
            this.label_Note1.Text = "1. To use the interrupt place a global signal reference and select LPCompInt.";
            // 
            // label_Note2
            // 
            this.label_Note2.AutoSize = true;
            this.label_Note2.Location = new System.Drawing.Point(6, 220);
            this.label_Note2.Name = "label_Note2";
            this.label_Note2.Size = new System.Drawing.Size(227, 13);
            this.label_Note2.TabIndex = 8;
            this.label_Note2.Text = "2. These modes are not available in Hibernate.";
            // 
            // labelNote1SuperscriptInt
            // 
            this.labelNote1SuperscriptInt.AutoSize = true;
            this.labelNote1SuperscriptInt.Font = new System.Drawing.Font("Microsoft Sans Serif", 6F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelNote1SuperscriptInt.Location = new System.Drawing.Point(272, 183);
            this.labelNote1SuperscriptInt.Margin = new System.Windows.Forms.Padding(0);
            this.labelNote1SuperscriptInt.Name = "labelNote1SuperscriptInt";
            this.labelNote1SuperscriptInt.Size = new System.Drawing.Size(9, 9);
            this.labelNote1SuperscriptInt.TabIndex = 11;
            this.labelNote1SuperscriptInt.Text = "1";
            // 
            // labelNote1SuperscriptPulse
            // 
            this.labelNote1SuperscriptPulse.AutoSize = true;
            this.labelNote1SuperscriptPulse.Font = new System.Drawing.Font("Microsoft Sans Serif", 6F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelNote1SuperscriptPulse.Location = new System.Drawing.Point(145, 92);
            this.labelNote1SuperscriptPulse.Margin = new System.Windows.Forms.Padding(0);
            this.labelNote1SuperscriptPulse.Name = "labelNote1SuperscriptPulse";
            this.labelNote1SuperscriptPulse.Size = new System.Drawing.Size(9, 9);
            this.labelNote1SuperscriptPulse.TabIndex = 12;
            this.labelNote1SuperscriptPulse.Text = "1";
            // 
            // CyBasicTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.labelNote1SuperscriptPulse);
            this.Controls.Add(this.labelNote1SuperscriptInt);
            this.Controls.Add(this.label_Note2);
            this.Controls.Add(this.label_Note1);
            this.Controls.Add(this.chB_IntEnabled);
            this.Controls.Add(this.pbGraph);
            this.Controls.Add(this.pbSymbol);
            this.Controls.Add(this.groupBoxSpeedPower);
            this.Controls.Add(this.groupBoxPulseInterrConfig);
            this.Controls.Add(this.groupBoxOuputConfig);
            this.Controls.Add(this.groupBoxHysteresis);
            this.Name = "CyBasicTab";
            this.Size = new System.Drawing.Size(447, 457);
            this.groupBoxHysteresis.ResumeLayout(false);
            this.groupBoxHysteresis.PerformLayout();
            this.groupBoxSpeedPower.ResumeLayout(false);
            this.groupBoxSpeedPower.PerformLayout();
            this.groupBoxOuputConfig.ResumeLayout(false);
            this.groupBoxOuputConfig.PerformLayout();
            this.groupBoxPulseInterrConfig.ResumeLayout(false);
            this.groupBoxPulseInterrConfig.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbSymbol)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbGraph)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxHysteresis;
        private System.Windows.Forms.RadioButton rbHysteresisDisable;
        private System.Windows.Forms.RadioButton rbHysteresisEnable;
        private System.Windows.Forms.GroupBox groupBoxSpeedPower;
        private System.Windows.Forms.RadioButton rbSpeedMedium;
        private System.Windows.Forms.RadioButton rbSpeedSlow;
        private System.Windows.Forms.GroupBox groupBoxOuputConfig;
        private System.Windows.Forms.RadioButton rbSynchronized;
        private System.Windows.Forms.RadioButton rbDirect;
        private System.Windows.Forms.GroupBox groupBoxPulseInterrConfig;
        private System.Windows.Forms.RadioButton rbInterruptRising;
        private System.Windows.Forms.RadioButton rbInterruptDisabled;
        private System.Windows.Forms.RadioButton rbSpeedHigh;
        private System.Windows.Forms.PictureBox pbSymbol;
        private System.Windows.Forms.PictureBox pbGraph;
        private System.Windows.Forms.RadioButton rbInterruptBoth;
        private System.Windows.Forms.RadioButton rbInterruptFalling;
        private System.Windows.Forms.RadioButton rbPulse;
        private System.Windows.Forms.CheckBox chB_IntEnabled;
        private System.Windows.Forms.Label label_Note1;
        private System.Windows.Forms.Label label_Note2;
        private System.Windows.Forms.Label labelNote2SuperscriptFalling;
        private System.Windows.Forms.Label labelNote2SuperscriptRising;
        private System.Windows.Forms.Label labelNote1SuperscriptInt;
        private System.Windows.Forms.Label labelNote1SuperscriptPulse;

    }
}
