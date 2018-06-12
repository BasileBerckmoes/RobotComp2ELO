namespace CSD_Comp_P4_v1_0.Tabs
{
    partial class CyConfigTab
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyConfigTab));
            this.gbVrefSource = new System.Windows.Forms.GroupBox();
            this.numVinref = new System.Windows.Forms.NumericUpDown();
            this.m_lblBandgap = new System.Windows.Forms.Label();
            this.rbExternalReference = new System.Windows.Forms.RadioButton();
            this.rbInternalBandgap = new System.Windows.Forms.RadioButton();
            this.gbVRefType = new System.Windows.Forms.GroupBox();
            this.panelAdjustableVref = new System.Windows.Forms.Panel();
            this.m_cmbxAdjustableVref = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.numVrange = new System.Windows.Forms.NumericUpDown();
            this.m_lblVrangeActual = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.rbAdjustable = new System.Windows.Forms.RadioButton();
            this.rbFixed = new System.Windows.Forms.RadioButton();
            this.pbGraph = new System.Windows.Forms.PictureBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.m_lblVdda = new System.Windows.Forms.Label();
            this.gbVrefSource.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numVinref)).BeginInit();
            this.gbVRefType.SuspendLayout();
            this.panelAdjustableVref.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numVrange)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbGraph)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // gbVrefSource
            // 
            this.gbVrefSource.Controls.Add(this.numVinref);
            this.gbVrefSource.Controls.Add(this.m_lblBandgap);
            this.gbVrefSource.Controls.Add(this.rbExternalReference);
            this.gbVrefSource.Controls.Add(this.rbInternalBandgap);
            resources.ApplyResources(this.gbVrefSource, "gbVrefSource");
            this.gbVrefSource.Name = "gbVrefSource";
            this.gbVrefSource.TabStop = false;
            // 
            // numVinref
            // 
            this.numVinref.DecimalPlaces = 2;
            this.numVinref.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            resources.ApplyResources(this.numVinref, "numVinref");
            this.numVinref.Name = "numVinref";
            this.numVinref.ValueChanged += new System.EventHandler(this.numeric_ValueChanged);
            // 
            // m_lblBandgap
            // 
            resources.ApplyResources(this.m_lblBandgap, "m_lblBandgap");
            this.m_lblBandgap.Name = "m_lblBandgap";
            // 
            // rbExternalReference
            // 
            resources.ApplyResources(this.rbExternalReference, "rbExternalReference");
            this.rbExternalReference.Name = "rbExternalReference";
            this.rbExternalReference.TabStop = true;
            this.rbExternalReference.UseVisualStyleBackColor = true;
            this.rbExternalReference.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // rbInternalBandgap
            // 
            resources.ApplyResources(this.rbInternalBandgap, "rbInternalBandgap");
            this.rbInternalBandgap.Name = "rbInternalBandgap";
            this.rbInternalBandgap.TabStop = true;
            this.rbInternalBandgap.UseVisualStyleBackColor = true;
            this.rbInternalBandgap.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // gbVRefType
            // 
            this.gbVRefType.Controls.Add(this.panelAdjustableVref);
            this.gbVRefType.Controls.Add(this.rbAdjustable);
            this.gbVRefType.Controls.Add(this.rbFixed);
            resources.ApplyResources(this.gbVRefType, "gbVRefType");
            this.gbVRefType.Name = "gbVRefType";
            this.gbVRefType.TabStop = false;
            // 
            // panelAdjustableVref
            // 
            this.panelAdjustableVref.Controls.Add(this.m_cmbxAdjustableVref);
            this.panelAdjustableVref.Controls.Add(this.label1);
            this.panelAdjustableVref.Controls.Add(this.label5);
            this.panelAdjustableVref.Controls.Add(this.numVrange);
            this.panelAdjustableVref.Controls.Add(this.m_lblVrangeActual);
            this.panelAdjustableVref.Controls.Add(this.label4);
            resources.ApplyResources(this.panelAdjustableVref, "panelAdjustableVref");
            this.panelAdjustableVref.Name = "panelAdjustableVref";
            // 
            // m_cmbxAdjustableVref
            // 
            this.m_cmbxAdjustableVref.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmbxAdjustableVref.FormattingEnabled = true;
            this.m_cmbxAdjustableVref.Items.AddRange(new object[] {
            resources.GetString("m_cmbxAdjustableVref.Items"),
            resources.GetString("m_cmbxAdjustableVref.Items1"),
            resources.GetString("m_cmbxAdjustableVref.Items2"),
            resources.GetString("m_cmbxAdjustableVref.Items3"),
            resources.GetString("m_cmbxAdjustableVref.Items4"),
            resources.GetString("m_cmbxAdjustableVref.Items5"),
            resources.GetString("m_cmbxAdjustableVref.Items6"),
            resources.GetString("m_cmbxAdjustableVref.Items7"),
            resources.GetString("m_cmbxAdjustableVref.Items8"),
            resources.GetString("m_cmbxAdjustableVref.Items9"),
            resources.GetString("m_cmbxAdjustableVref.Items10"),
            resources.GetString("m_cmbxAdjustableVref.Items11"),
            resources.GetString("m_cmbxAdjustableVref.Items12"),
            resources.GetString("m_cmbxAdjustableVref.Items13"),
            resources.GetString("m_cmbxAdjustableVref.Items14"),
            resources.GetString("m_cmbxAdjustableVref.Items15"),
            resources.GetString("m_cmbxAdjustableVref.Items16"),
            resources.GetString("m_cmbxAdjustableVref.Items17"),
            resources.GetString("m_cmbxAdjustableVref.Items18"),
            resources.GetString("m_cmbxAdjustableVref.Items19"),
            resources.GetString("m_cmbxAdjustableVref.Items20"),
            resources.GetString("m_cmbxAdjustableVref.Items21"),
            resources.GetString("m_cmbxAdjustableVref.Items22"),
            resources.GetString("m_cmbxAdjustableVref.Items23"),
            resources.GetString("m_cmbxAdjustableVref.Items24"),
            resources.GetString("m_cmbxAdjustableVref.Items25"),
            resources.GetString("m_cmbxAdjustableVref.Items26"),
            resources.GetString("m_cmbxAdjustableVref.Items27"),
            resources.GetString("m_cmbxAdjustableVref.Items28"),
            resources.GetString("m_cmbxAdjustableVref.Items29"),
            resources.GetString("m_cmbxAdjustableVref.Items30"),
            resources.GetString("m_cmbxAdjustableVref.Items31")});
            resources.ApplyResources(this.m_cmbxAdjustableVref, "m_cmbxAdjustableVref");
            this.m_cmbxAdjustableVref.Name = "m_cmbxAdjustableVref";
            this.m_cmbxAdjustableVref.SelectedIndexChanged += new System.EventHandler(this.cmbxAdjustableVref_SelectedIndexChanged);
            // 
            // label1
            // 
            resources.ApplyResources(this.label1, "label1");
            this.label1.Name = "label1";
            // 
            // label5
            // 
            resources.ApplyResources(this.label5, "label5");
            this.label5.Name = "label5";
            // 
            // numVrange
            // 
            this.numVrange.DecimalPlaces = 2;
            this.numVrange.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            resources.ApplyResources(this.numVrange, "numVrange");
            this.numVrange.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.numVrange.Name = "numVrange";
            this.numVrange.Value = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.numVrange.ValueChanged += new System.EventHandler(this.numeric_ValueChanged);
            // 
            // m_lblVrangeActual
            // 
            resources.ApplyResources(this.m_lblVrangeActual, "m_lblVrangeActual");
            this.m_lblVrangeActual.Name = "m_lblVrangeActual";
            // 
            // label4
            // 
            resources.ApplyResources(this.label4, "label4");
            this.label4.Name = "label4";
            // 
            // rbAdjustable
            // 
            resources.ApplyResources(this.rbAdjustable, "rbAdjustable");
            this.rbAdjustable.Name = "rbAdjustable";
            this.rbAdjustable.TabStop = true;
            this.rbAdjustable.UseVisualStyleBackColor = true;
            this.rbAdjustable.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // rbFixed
            // 
            resources.ApplyResources(this.rbFixed, "rbFixed");
            this.rbFixed.Name = "rbFixed";
            this.rbFixed.TabStop = true;
            this.rbFixed.UseVisualStyleBackColor = true;
            this.rbFixed.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // pbGraph
            // 
            this.pbGraph.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            resources.ApplyResources(this.pbGraph, "pbGraph");
            this.pbGraph.Name = "pbGraph";
            this.pbGraph.TabStop = false;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::CSD_Comp_P4_v1_0.Properties.Resources.csdCompImg;
            resources.ApplyResources(this.pictureBox1, "pictureBox1");
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.TabStop = false;
            // 
            // m_lblVdda
            // 
            resources.ApplyResources(this.m_lblVdda, "m_lblVdda");
            this.m_lblVdda.Name = "m_lblVdda";
            // 
            // CyConfigTab
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_lblVdda);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.pbGraph);
            this.Controls.Add(this.gbVRefType);
            this.Controls.Add(this.gbVrefSource);
            this.Name = "CyConfigTab";
            this.gbVrefSource.ResumeLayout(false);
            this.gbVrefSource.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numVinref)).EndInit();
            this.gbVRefType.ResumeLayout(false);
            this.gbVRefType.PerformLayout();
            this.panelAdjustableVref.ResumeLayout(false);
            this.panelAdjustableVref.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numVrange)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbGraph)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox gbVrefSource;
        private System.Windows.Forms.NumericUpDown numVinref;
        private System.Windows.Forms.Label m_lblBandgap;
        private System.Windows.Forms.RadioButton rbExternalReference;
        private System.Windows.Forms.RadioButton rbInternalBandgap;
        private System.Windows.Forms.GroupBox gbVRefType;
        private System.Windows.Forms.NumericUpDown numVrange;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.RadioButton rbAdjustable;
        private System.Windows.Forms.RadioButton rbFixed;
        private System.Windows.Forms.Label m_lblVrangeActual;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox m_cmbxAdjustableVref;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.PictureBox pbGraph;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label m_lblVdda;
        private System.Windows.Forms.Panel panelAdjustableVref;
    }
}
