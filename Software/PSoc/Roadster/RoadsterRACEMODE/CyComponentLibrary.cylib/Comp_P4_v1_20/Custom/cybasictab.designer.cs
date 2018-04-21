namespace Comp_P4_v1_20
{
    partial class CyBasicTab
    {
        /// <summary> 
        /// The required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources are to be disposed; otherwise, false.</param>
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
        /// The required method for Designer support - do not modify. 
        /// The contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyBasicTab));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.rbHysteresisDisable = new System.Windows.Forms.RadioButton();
            this.rbHysteresisEnable = new System.Windows.Forms.RadioButton();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.rbSpeedHigh = new System.Windows.Forms.RadioButton();
            this.rbSpeedMedium = new System.Windows.Forms.RadioButton();
            this.rbSpeedSlow = new System.Windows.Forms.RadioButton();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.rbPolarityInv = new System.Windows.Forms.RadioButton();
            this.rbPolarityNonInv = new System.Windows.Forms.RadioButton();
            this.pbSymbol = new System.Windows.Forms.PictureBox();
            this.pbGraph = new System.Windows.Forms.PictureBox();
            this.grB_DeepSleep = new System.Windows.Forms.GroupBox();
            this.rb_DeepSleepEnabled = new System.Windows.Forms.RadioButton();
            this.rb_DeepSleepDisabled = new System.Windows.Forms.RadioButton();
            this.chB_IntOutEnabled = new System.Windows.Forms.CheckBox();
            this.groupBoxInterrOutMode = new System.Windows.Forms.GroupBox();
            this.rbIgnoreEdges = new System.Windows.Forms.RadioButton();
            this.rbBothEdges = new System.Windows.Forms.RadioButton();
            this.rbFallingEdge = new System.Windows.Forms.RadioButton();
            this.rbRisingEdge = new System.Windows.Forms.RadioButton();
            this.labelNote1SuperscriptInt = new System.Windows.Forms.Label();
            this.label_Note1 = new System.Windows.Forms.Label();
            this.errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbSymbol)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbGraph)).BeginInit();
            this.grB_DeepSleep.SuspendLayout();
            this.groupBoxInterrOutMode.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.rbHysteresisDisable);
            this.groupBox1.Controls.Add(this.rbHysteresisEnable);
            resources.ApplyResources(this.groupBox1, "groupBox1");
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.TabStop = false;
            // 
            // rbHysteresisDisable
            // 
            resources.ApplyResources(this.rbHysteresisDisable, "rbHysteresisDisable");
            this.rbHysteresisDisable.Name = "rbHysteresisDisable";
            this.rbHysteresisDisable.UseVisualStyleBackColor = true;
            // 
            // rbHysteresisEnable
            // 
            resources.ApplyResources(this.rbHysteresisEnable, "rbHysteresisEnable");
            this.rbHysteresisEnable.Checked = true;
            this.rbHysteresisEnable.Name = "rbHysteresisEnable";
            this.rbHysteresisEnable.TabStop = true;
            this.rbHysteresisEnable.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.rbSpeedHigh);
            this.groupBox2.Controls.Add(this.rbSpeedMedium);
            this.groupBox2.Controls.Add(this.rbSpeedSlow);
            resources.ApplyResources(this.groupBox2, "groupBox2");
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.TabStop = false;
            // 
            // rbSpeedHigh
            // 
            resources.ApplyResources(this.rbSpeedHigh, "rbSpeedHigh");
            this.rbSpeedHigh.Name = "rbSpeedHigh";
            this.rbSpeedHigh.UseVisualStyleBackColor = true;
            // 
            // rbSpeedMedium
            // 
            resources.ApplyResources(this.rbSpeedMedium, "rbSpeedMedium");
            this.rbSpeedMedium.Name = "rbSpeedMedium";
            this.rbSpeedMedium.UseVisualStyleBackColor = true;
            // 
            // rbSpeedSlow
            // 
            resources.ApplyResources(this.rbSpeedSlow, "rbSpeedSlow");
            this.rbSpeedSlow.Checked = true;
            this.rbSpeedSlow.Name = "rbSpeedSlow";
            this.rbSpeedSlow.TabStop = true;
            this.rbSpeedSlow.UseVisualStyleBackColor = true;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.rbPolarityInv);
            this.groupBox3.Controls.Add(this.rbPolarityNonInv);
            resources.ApplyResources(this.groupBox3, "groupBox3");
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.TabStop = false;
            // 
            // rbPolarityInv
            // 
            resources.ApplyResources(this.rbPolarityInv, "rbPolarityInv");
            this.rbPolarityInv.Name = "rbPolarityInv";
            this.rbPolarityInv.UseVisualStyleBackColor = true;
            // 
            // rbPolarityNonInv
            // 
            resources.ApplyResources(this.rbPolarityNonInv, "rbPolarityNonInv");
            this.rbPolarityNonInv.Checked = true;
            this.rbPolarityNonInv.Name = "rbPolarityNonInv";
            this.rbPolarityNonInv.TabStop = true;
            this.rbPolarityNonInv.UseVisualStyleBackColor = true;
            // 
            // pbSymbol
            // 
            this.pbSymbol.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            resources.ApplyResources(this.pbSymbol, "pbSymbol");
            this.pbSymbol.Name = "pbSymbol";
            this.pbSymbol.TabStop = false;
            // 
            // pbGraph
            // 
            this.pbGraph.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            resources.ApplyResources(this.pbGraph, "pbGraph");
            this.pbGraph.Name = "pbGraph";
            this.pbGraph.TabStop = false;
            // 
            // grB_DeepSleep
            // 
            this.grB_DeepSleep.Controls.Add(this.rb_DeepSleepEnabled);
            this.grB_DeepSleep.Controls.Add(this.rb_DeepSleepDisabled);
            resources.ApplyResources(this.grB_DeepSleep, "grB_DeepSleep");
            this.grB_DeepSleep.Name = "grB_DeepSleep";
            this.grB_DeepSleep.TabStop = false;
            // 
            // rb_DeepSleepEnabled
            // 
            resources.ApplyResources(this.rb_DeepSleepEnabled, "rb_DeepSleepEnabled");
            this.rb_DeepSleepEnabled.Name = "rb_DeepSleepEnabled";
            this.rb_DeepSleepEnabled.UseVisualStyleBackColor = true;
            // 
            // rb_DeepSleepDisabled
            // 
            resources.ApplyResources(this.rb_DeepSleepDisabled, "rb_DeepSleepDisabled");
            this.rb_DeepSleepDisabled.Checked = true;
            this.rb_DeepSleepDisabled.Name = "rb_DeepSleepDisabled";
            this.rb_DeepSleepDisabled.TabStop = true;
            this.rb_DeepSleepDisabled.UseVisualStyleBackColor = true;
            // 
            // chB_IntOutEnabled
            // 
            resources.ApplyResources(this.chB_IntOutEnabled, "chB_IntOutEnabled");
            this.chB_IntOutEnabled.Name = "chB_IntOutEnabled";
            this.chB_IntOutEnabled.UseVisualStyleBackColor = true;
            // 
            // groupBoxInterrOutMode
            // 
            this.groupBoxInterrOutMode.Controls.Add(this.rbIgnoreEdges);
            this.groupBoxInterrOutMode.Controls.Add(this.rbBothEdges);
            this.groupBoxInterrOutMode.Controls.Add(this.rbFallingEdge);
            this.groupBoxInterrOutMode.Controls.Add(this.rbRisingEdge);
            resources.ApplyResources(this.groupBoxInterrOutMode, "groupBoxInterrOutMode");
            this.groupBoxInterrOutMode.Name = "groupBoxInterrOutMode";
            this.groupBoxInterrOutMode.TabStop = false;
            // 
            // rbIgnoreEdges
            // 
            resources.ApplyResources(this.rbIgnoreEdges, "rbIgnoreEdges");
            this.rbIgnoreEdges.Name = "rbIgnoreEdges";
            this.rbIgnoreEdges.TabStop = true;
            this.rbIgnoreEdges.UseVisualStyleBackColor = true;
            // 
            // rbBothEdges
            // 
            resources.ApplyResources(this.rbBothEdges, "rbBothEdges");
            this.rbBothEdges.Name = "rbBothEdges";
            this.rbBothEdges.TabStop = true;
            this.rbBothEdges.UseVisualStyleBackColor = true;
            // 
            // rbFallingEdge
            // 
            resources.ApplyResources(this.rbFallingEdge, "rbFallingEdge");
            this.rbFallingEdge.Name = "rbFallingEdge";
            this.rbFallingEdge.TabStop = true;
            this.rbFallingEdge.UseVisualStyleBackColor = true;
            // 
            // rbRisingEdge
            // 
            resources.ApplyResources(this.rbRisingEdge, "rbRisingEdge");
            this.rbRisingEdge.Name = "rbRisingEdge";
            this.rbRisingEdge.TabStop = true;
            this.rbRisingEdge.UseVisualStyleBackColor = true;
            // 
            // labelNote1SuperscriptInt
            // 
            resources.ApplyResources(this.labelNote1SuperscriptInt, "labelNote1SuperscriptInt");
            this.labelNote1SuperscriptInt.Name = "labelNote1SuperscriptInt";
            // 
            // label_Note1
            // 
            resources.ApplyResources(this.label_Note1, "label_Note1");
            this.label_Note1.Name = "label_Note1";
            // 
            // errorProvider
            // 
            this.errorProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.errorProvider.ContainerControl = this;
            // 
            // CyBasicTab
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.label_Note1);
            this.Controls.Add(this.labelNote1SuperscriptInt);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBoxInterrOutMode);
            this.Controls.Add(this.chB_IntOutEnabled);
            this.Controls.Add(this.grB_DeepSleep);
            this.Controls.Add(this.pbGraph);
            this.Controls.Add(this.pbSymbol);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox1);
            this.Name = "CyBasicTab";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbSymbol)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbGraph)).EndInit();
            this.grB_DeepSleep.ResumeLayout(false);
            this.grB_DeepSleep.PerformLayout();
            this.groupBoxInterrOutMode.ResumeLayout(false);
            this.groupBoxInterrOutMode.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton rbHysteresisDisable;
        private System.Windows.Forms.RadioButton rbHysteresisEnable;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.RadioButton rbSpeedMedium;
        private System.Windows.Forms.RadioButton rbSpeedSlow;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.RadioButton rbPolarityInv;
        private System.Windows.Forms.RadioButton rbPolarityNonInv;
        private System.Windows.Forms.RadioButton rbSpeedHigh;
        private System.Windows.Forms.PictureBox pbSymbol;
        private System.Windows.Forms.PictureBox pbGraph;
        private System.Windows.Forms.GroupBox grB_DeepSleep;
        private System.Windows.Forms.RadioButton rb_DeepSleepEnabled;
        private System.Windows.Forms.RadioButton rb_DeepSleepDisabled;
        private System.Windows.Forms.GroupBox groupBoxInterrOutMode;
        private System.Windows.Forms.RadioButton rbIgnoreEdges;
        private System.Windows.Forms.RadioButton rbBothEdges;
        private System.Windows.Forms.RadioButton rbFallingEdge;
        private System.Windows.Forms.RadioButton rbRisingEdge;
        private System.Windows.Forms.CheckBox chB_IntOutEnabled;
        private System.Windows.Forms.Label label_Note1;
        private System.Windows.Forms.Label labelNote1SuperscriptInt;
        private System.Windows.Forms.ErrorProvider errorProvider;

    }
}
