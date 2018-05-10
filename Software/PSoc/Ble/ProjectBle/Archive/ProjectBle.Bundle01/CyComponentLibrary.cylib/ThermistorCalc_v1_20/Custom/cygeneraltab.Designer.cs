namespace ThermistorCalc_v1_20
{
    partial class CyGeneralTab
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
            this.m_lblRefResistor = new System.Windows.Forms.Label();
            this.m_numRefResistor = new System.Windows.Forms.NumericUpDown();
            this.m_grpImpl = new System.Windows.Forms.GroupBox();
            this.m_rbEquation = new System.Windows.Forms.RadioButton();
            this.m_rbLut = new System.Windows.Forms.RadioButton();
            this.m_cbCalcResolution = new System.Windows.Forms.ComboBox();
            this.m_lblCalcResolution = new System.Windows.Forms.Label();
            this.m_grpTemperatures = new System.Windows.Forms.GroupBox();
            this.m_numMinTemp = new System.Windows.Forms.NumericUpDown();
            this.m_numMidTemp = new System.Windows.Forms.NumericUpDown();
            this.m_numMaxTemp = new System.Windows.Forms.NumericUpDown();
            this.m_lblMinTemp = new System.Windows.Forms.Label();
            this.m_lblMidTemp = new System.Windows.Forms.Label();
            this.m_lblMaxTemp = new System.Windows.Forms.Label();
            this.m_numMinResist = new System.Windows.Forms.NumericUpDown();
            this.m_numMidResist = new System.Windows.Forms.NumericUpDown();
            this.m_numMaxResist = new System.Windows.Forms.NumericUpDown();
            this.m_rtbInfo = new System.Windows.Forms.RichTextBox();
            this.m_grpResistances = new System.Windows.Forms.GroupBox();
            this.m_lblMinRes = new System.Windows.Forms.Label();
            this.m_lblMaxRes = new System.Windows.Forms.Label();
            this.m_lblMidRes = new System.Windows.Forms.Label();
            this.m_lblLutError = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.m_numRefResistor)).BeginInit();
            this.m_grpImpl.SuspendLayout();
            this.m_grpTemperatures.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numMinTemp)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numMidTemp)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numMaxTemp)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numMinResist)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numMidResist)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numMaxResist)).BeginInit();
            this.m_grpResistances.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_lblRefResistor
            // 
            this.m_lblRefResistor.AutoSize = true;
            this.m_lblRefResistor.Location = new System.Drawing.Point(3, 5);
            this.m_lblRefResistor.Name = "m_lblRefResistor";
            this.m_lblRefResistor.Size = new System.Drawing.Size(114, 13);
            this.m_lblRefResistor.TabIndex = 0;
            this.m_lblRefResistor.Text = "Reference resistor (Ω):";
            // 
            // m_numRefResistor
            // 
            this.m_numRefResistor.Location = new System.Drawing.Point(124, 3);
            this.m_numRefResistor.Name = "m_numRefResistor";
            this.m_numRefResistor.Size = new System.Drawing.Size(79, 20);
            this.m_numRefResistor.TabIndex = 1;
            // 
            // m_grpImpl
            // 
            this.m_grpImpl.Controls.Add(this.m_rbEquation);
            this.m_grpImpl.Controls.Add(this.m_rbLut);
            this.m_grpImpl.Controls.Add(this.m_cbCalcResolution);
            this.m_grpImpl.Controls.Add(this.m_lblCalcResolution);
            this.m_grpImpl.Location = new System.Drawing.Point(3, 28);
            this.m_grpImpl.Name = "m_grpImpl";
            this.m_grpImpl.Size = new System.Drawing.Size(208, 97);
            this.m_grpImpl.TabIndex = 4;
            this.m_grpImpl.TabStop = false;
            this.m_grpImpl.Text = "Implementation";
            // 
            // m_rbEquation
            // 
            this.m_rbEquation.AutoSize = true;
            this.m_rbEquation.Location = new System.Drawing.Point(6, 19);
            this.m_rbEquation.Name = "m_rbEquation";
            this.m_rbEquation.Size = new System.Drawing.Size(67, 17);
            this.m_rbEquation.TabIndex = 1;
            this.m_rbEquation.TabStop = true;
            this.m_rbEquation.Text = "Equation";
            this.m_rbEquation.UseVisualStyleBackColor = true;
            // 
            // m_rbLut
            // 
            this.m_rbLut.AutoSize = true;
            this.m_rbLut.Location = new System.Drawing.Point(6, 42);
            this.m_rbLut.Name = "m_rbLut";
            this.m_rbLut.Size = new System.Drawing.Size(46, 17);
            this.m_rbLut.TabIndex = 0;
            this.m_rbLut.TabStop = true;
            this.m_rbLut.Text = "LUT";
            this.m_rbLut.UseVisualStyleBackColor = true;
            // 
            // m_cbCalcResolution
            // 
            this.m_cbCalcResolution.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbCalcResolution.FormattingEnabled = true;
            this.m_cbCalcResolution.Location = new System.Drawing.Point(144, 65);
            this.m_cbCalcResolution.Name = "m_cbCalcResolution";
            this.m_cbCalcResolution.Size = new System.Drawing.Size(45, 21);
            this.m_cbCalcResolution.TabIndex = 3;
            // 
            // m_lblCalcResolution
            // 
            this.m_lblCalcResolution.AutoSize = true;
            this.m_lblCalcResolution.Location = new System.Drawing.Point(6, 68);
            this.m_lblCalcResolution.Name = "m_lblCalcResolution";
            this.m_lblCalcResolution.Size = new System.Drawing.Size(130, 13);
            this.m_lblCalcResolution.TabIndex = 2;
            this.m_lblCalcResolution.Text = "Calculation resolution (°C):";
            // 
            // m_grpTemperatures
            // 
            this.m_grpTemperatures.Controls.Add(this.m_numMinTemp);
            this.m_grpTemperatures.Controls.Add(this.m_numMidTemp);
            this.m_grpTemperatures.Controls.Add(this.m_numMaxTemp);
            this.m_grpTemperatures.Controls.Add(this.m_lblMinTemp);
            this.m_grpTemperatures.Controls.Add(this.m_lblMidTemp);
            this.m_grpTemperatures.Controls.Add(this.m_lblMaxTemp);
            this.m_grpTemperatures.Location = new System.Drawing.Point(217, 28);
            this.m_grpTemperatures.Name = "m_grpTemperatures";
            this.m_grpTemperatures.Size = new System.Drawing.Size(113, 97);
            this.m_grpTemperatures.TabIndex = 5;
            this.m_grpTemperatures.TabStop = false;
            this.m_grpTemperatures.Text = "Temperature (°C)";
            // 
            // m_numMinTemp
            // 
            this.m_numMinTemp.Location = new System.Drawing.Point(39, 71);
            this.m_numMinTemp.Name = "m_numMinTemp";
            this.m_numMinTemp.Size = new System.Drawing.Size(46, 20);
            this.m_numMinTemp.TabIndex = 9;
            // 
            // m_numMidTemp
            // 
            this.m_numMidTemp.Location = new System.Drawing.Point(39, 45);
            this.m_numMidTemp.Name = "m_numMidTemp";
            this.m_numMidTemp.Size = new System.Drawing.Size(46, 20);
            this.m_numMidTemp.TabIndex = 5;
            // 
            // m_numMaxTemp
            // 
            this.m_numMaxTemp.Location = new System.Drawing.Point(39, 19);
            this.m_numMaxTemp.Name = "m_numMaxTemp";
            this.m_numMaxTemp.Size = new System.Drawing.Size(46, 20);
            this.m_numMaxTemp.TabIndex = 1;
            // 
            // m_lblMinTemp
            // 
            this.m_lblMinTemp.AutoSize = true;
            this.m_lblMinTemp.Location = new System.Drawing.Point(6, 73);
            this.m_lblMinTemp.Name = "m_lblMinTemp";
            this.m_lblMinTemp.Size = new System.Drawing.Size(24, 13);
            this.m_lblMinTemp.TabIndex = 8;
            this.m_lblMinTemp.Text = "Min";
            // 
            // m_lblMidTemp
            // 
            this.m_lblMidTemp.AutoSize = true;
            this.m_lblMidTemp.Location = new System.Drawing.Point(6, 47);
            this.m_lblMidTemp.Name = "m_lblMidTemp";
            this.m_lblMidTemp.Size = new System.Drawing.Size(24, 13);
            this.m_lblMidTemp.TabIndex = 4;
            this.m_lblMidTemp.Text = "Mid";
            // 
            // m_lblMaxTemp
            // 
            this.m_lblMaxTemp.AutoSize = true;
            this.m_lblMaxTemp.Location = new System.Drawing.Point(6, 21);
            this.m_lblMaxTemp.Name = "m_lblMaxTemp";
            this.m_lblMaxTemp.Size = new System.Drawing.Size(27, 13);
            this.m_lblMaxTemp.TabIndex = 0;
            this.m_lblMaxTemp.Text = "Max";
            // 
            // m_numMinResist
            // 
            this.m_numMinResist.Location = new System.Drawing.Point(38, 71);
            this.m_numMinResist.Name = "m_numMinResist";
            this.m_numMinResist.Size = new System.Drawing.Size(68, 20);
            this.m_numMinResist.TabIndex = 11;
            // 
            // m_numMidResist
            // 
            this.m_numMidResist.Location = new System.Drawing.Point(38, 45);
            this.m_numMidResist.Name = "m_numMidResist";
            this.m_numMidResist.Size = new System.Drawing.Size(68, 20);
            this.m_numMidResist.TabIndex = 7;
            // 
            // m_numMaxResist
            // 
            this.m_numMaxResist.Location = new System.Drawing.Point(38, 19);
            this.m_numMaxResist.Name = "m_numMaxResist";
            this.m_numMaxResist.Size = new System.Drawing.Size(68, 20);
            this.m_numMaxResist.TabIndex = 3;
            // 
            // m_rtbInfo
            // 
            this.m_rtbInfo.Location = new System.Drawing.Point(3, 131);
            this.m_rtbInfo.Name = "m_rtbInfo";
            this.m_rtbInfo.Size = new System.Drawing.Size(454, 46);
            this.m_rtbInfo.TabIndex = 6;
            this.m_rtbInfo.Text = "";
            // 
            // m_grpResistances
            // 
            this.m_grpResistances.Controls.Add(this.m_lblMinRes);
            this.m_grpResistances.Controls.Add(this.m_numMinResist);
            this.m_grpResistances.Controls.Add(this.m_lblMaxRes);
            this.m_grpResistances.Controls.Add(this.m_numMidResist);
            this.m_grpResistances.Controls.Add(this.m_lblMidRes);
            this.m_grpResistances.Controls.Add(this.m_numMaxResist);
            this.m_grpResistances.Location = new System.Drawing.Point(335, 28);
            this.m_grpResistances.Margin = new System.Windows.Forms.Padding(2);
            this.m_grpResistances.Name = "m_grpResistances";
            this.m_grpResistances.Padding = new System.Windows.Forms.Padding(2);
            this.m_grpResistances.Size = new System.Drawing.Size(122, 97);
            this.m_grpResistances.TabIndex = 7;
            this.m_grpResistances.TabStop = false;
            this.m_grpResistances.Text = "Resistance (Ω)";
            // 
            // m_lblMinRes
            // 
            this.m_lblMinRes.AutoSize = true;
            this.m_lblMinRes.Location = new System.Drawing.Point(5, 73);
            this.m_lblMinRes.Name = "m_lblMinRes";
            this.m_lblMinRes.Size = new System.Drawing.Size(24, 13);
            this.m_lblMinRes.TabIndex = 11;
            this.m_lblMinRes.Text = "Min";
            // 
            // m_lblMaxRes
            // 
            this.m_lblMaxRes.AutoSize = true;
            this.m_lblMaxRes.Location = new System.Drawing.Point(5, 21);
            this.m_lblMaxRes.Name = "m_lblMaxRes";
            this.m_lblMaxRes.Size = new System.Drawing.Size(27, 13);
            this.m_lblMaxRes.TabIndex = 9;
            this.m_lblMaxRes.Text = "Max";
            // 
            // m_lblMidRes
            // 
            this.m_lblMidRes.AutoSize = true;
            this.m_lblMidRes.Location = new System.Drawing.Point(5, 47);
            this.m_lblMidRes.Name = "m_lblMidRes";
            this.m_lblMidRes.Size = new System.Drawing.Size(24, 13);
            this.m_lblMidRes.TabIndex = 10;
            this.m_lblMidRes.Text = "Mid";
            // 
            // m_lblLutError
            // 
            this.m_lblLutError.AutoSize = true;
            this.m_lblLutError.Location = new System.Drawing.Point(19, 185);
            this.m_lblLutError.Name = "m_lblLutError";
            this.m_lblLutError.Size = new System.Drawing.Size(443, 13);
            this.m_lblLutError.TabIndex = 9;
            this.m_lblLutError.Text = "The selected combinations of temperatures and resistances do not produce a valid " +
                "equation.";
            this.m_lblLutError.VisibleChanged += new System.EventHandler(this.labelLutError_VisibleChanged);
            // 
            // CyGeneralTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_lblLutError);
            this.Controls.Add(this.m_grpResistances);
            this.Controls.Add(this.m_rtbInfo);
            this.Controls.Add(this.m_grpTemperatures);
            this.Controls.Add(this.m_grpImpl);
            this.Controls.Add(this.m_numRefResistor);
            this.Controls.Add(this.m_lblRefResistor);
            this.Name = "CyGeneralTab";
            this.Size = new System.Drawing.Size(460, 219);
            ((System.ComponentModel.ISupportInitialize)(this.m_numRefResistor)).EndInit();
            this.m_grpImpl.ResumeLayout(false);
            this.m_grpImpl.PerformLayout();
            this.m_grpTemperatures.ResumeLayout(false);
            this.m_grpTemperatures.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numMinTemp)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numMidTemp)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numMaxTemp)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numMinResist)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numMidResist)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numMaxResist)).EndInit();
            this.m_grpResistances.ResumeLayout(false);
            this.m_grpResistances.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label m_lblRefResistor;
        private System.Windows.Forms.NumericUpDown m_numRefResistor;
        private System.Windows.Forms.GroupBox m_grpImpl;
        private System.Windows.Forms.RadioButton m_rbEquation;
        private System.Windows.Forms.RadioButton m_rbLut;
        private System.Windows.Forms.Label m_lblCalcResolution;
        private System.Windows.Forms.ComboBox m_cbCalcResolution;
        private System.Windows.Forms.GroupBox m_grpTemperatures;
        private System.Windows.Forms.NumericUpDown m_numMinTemp;
        private System.Windows.Forms.NumericUpDown m_numMidTemp;
        private System.Windows.Forms.NumericUpDown m_numMaxTemp;
        private System.Windows.Forms.Label m_lblMinTemp;
        private System.Windows.Forms.Label m_lblMidTemp;
        private System.Windows.Forms.Label m_lblMaxTemp;
        private System.Windows.Forms.NumericUpDown m_numMinResist;
        private System.Windows.Forms.NumericUpDown m_numMidResist;
        private System.Windows.Forms.NumericUpDown m_numMaxResist;
        private System.Windows.Forms.RichTextBox m_rtbInfo;
        private System.Windows.Forms.GroupBox m_grpResistances;
        private System.Windows.Forms.Label m_lblMinRes;
        private System.Windows.Forms.Label m_lblMaxRes;
        private System.Windows.Forms.Label m_lblMidRes;
        private System.Windows.Forms.Label m_lblLutError;
    }
}
