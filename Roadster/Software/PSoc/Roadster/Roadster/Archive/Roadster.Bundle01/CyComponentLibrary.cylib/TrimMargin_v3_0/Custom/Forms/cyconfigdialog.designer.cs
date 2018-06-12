namespace TrimMargin_v3_0.Forms
{
    partial class CyConfigDialog
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyConfigDialog));
            this.pictureBoxCircuit = new System.Windows.Forms.PictureBox();
            this.buttonOk = new System.Windows.Forms.Button();
            this.buttonApply = new System.Windows.Forms.Button();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.panelCalculatedIdealValues = new System.Windows.Forms.Panel();
            this.buttHideCalculatedIdealValues = new System.Windows.Forms.PictureBox();
            this.label5 = new System.Windows.Forms.Label();
            this.txbLabelR2Calc = new System.Windows.Forms.TextBox();
            this.txbLabelR3plusR4Calc = new System.Windows.Forms.TextBox();
            this.panelActualValues = new System.Windows.Forms.Panel();
            this.buttHideActualValues = new System.Windows.Forms.PictureBox();
            this.label6 = new System.Windows.Forms.Label();
            this.panelError = new System.Windows.Forms.Panel();
            this.labelError = new System.Windows.Forms.Label();
            this.txbLabelCalcMinVoltageActual = new System.Windows.Forms.TextBox();
            this.txbLabelCalcMaxVoltageActual = new System.Windows.Forms.TextBox();
            this.txbLabelCalcVoutRippleActual = new System.Windows.Forms.TextBox();
            this.txbLabelR3plusR4Actual = new System.Windows.Forms.TextBox();
            this.m_errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.tableTrimMergCircParam = new System.Windows.Forms.TableLayoutPanel();
            this.panelErrorC1 = new System.Windows.Forms.Panel();
            this.numC1 = new System.Windows.Forms.NumericUpDown();
            this.panel16 = new System.Windows.Forms.Panel();
            this.checkBoxEnableC1 = new System.Windows.Forms.CheckBox();
            this.txbLabelC1 = new System.Windows.Forms.TextBox();
            this.panelErrorR4 = new System.Windows.Forms.Panel();
            this.numR4 = new System.Windows.Forms.NumericUpDown();
            this.panelErrorR1 = new System.Windows.Forms.Panel();
            this.numR1 = new System.Windows.Forms.NumericUpDown();
            this.panelErrorR3 = new System.Windows.Forms.Panel();
            this.numR3 = new System.Windows.Forms.NumericUpDown();
            this.panel6 = new System.Windows.Forms.Panel();
            this.comboBoxResistorsESeries = new System.Windows.Forms.ComboBox();
            this.panelErrorR2 = new System.Windows.Forms.Panel();
            this.numR2 = new System.Windows.Forms.NumericUpDown();
            this.txbLabelResistorsESeries = new System.Windows.Forms.TextBox();
            this.panel5 = new System.Windows.Forms.Panel();
            this.comboBoxCapacitorESeries = new System.Windows.Forms.ComboBox();
            this.panel4 = new System.Windows.Forms.Panel();
            this.checkBoxEnableR2 = new System.Windows.Forms.CheckBox();
            this.txbLabelR2 = new System.Windows.Forms.TextBox();
            this.panel3 = new System.Windows.Forms.Panel();
            this.checkBoxEnableR3 = new System.Windows.Forms.CheckBox();
            this.txbLabelR3 = new System.Windows.Forms.TextBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.checkBoxEnableR4 = new System.Windows.Forms.CheckBox();
            this.txbLabelR4 = new System.Windows.Forms.TextBox();
            this.txbLabelCapacitorESeries = new System.Windows.Forms.TextBox();
            this.txbLabelR1 = new System.Windows.Forms.TextBox();
            this.tableHardParam = new System.Windows.Forms.TableLayoutPanel();
            this.txbLabelVadjVref = new System.Windows.Forms.TextBox();
            this.txbLabelBoxVohOfPwmOutput = new System.Windows.Forms.TextBox();
            this.panelErrorVohOfPwmOutput = new System.Windows.Forms.Panel();
            this.numVohOfPwmOutput = new System.Windows.Forms.NumericUpDown();
            this.panelErrorNominalVadjOutput = new System.Windows.Forms.Panel();
            this.numNominalVadjOutput = new System.Windows.Forms.NumericUpDown();
            this.txbLabelDesiredVoutRipple = new System.Windows.Forms.TextBox();
            this.panelErrorDesiredVoutRipple = new System.Windows.Forms.Panel();
            this.numDesiredVoutRipple = new System.Windows.Forms.NumericUpDown();
            this.tableBasic = new System.Windows.Forms.TableLayoutPanel();
            this.panel8 = new System.Windows.Forms.Panel();
            this.comboBoxFeedback = new System.Windows.Forms.ComboBox();
            this.panelErrorControlSampleTime = new System.Windows.Forms.Panel();
            this.numControlSampleTime = new System.Windows.Forms.NumericUpDown();
            this.txbLabelFeedback = new System.Windows.Forms.TextBox();
            this.textBoxConverterName = new System.Windows.Forms.TextBox();
            this.txbLabelConverterName = new System.Windows.Forms.TextBox();
            this.txbLabelControlSampleTime = new System.Windows.Forms.TextBox();
            this.tableVoltParam = new System.Windows.Forms.TableLayoutPanel();
            this.panelErrorMarginLowV = new System.Windows.Forms.Panel();
            this.numMarginLowV = new System.Windows.Forms.NumericUpDown();
            this.panelErrorMarginHighV = new System.Windows.Forms.Panel();
            this.numMarginHighV = new System.Windows.Forms.NumericUpDown();
            this.txbLabelMarginHighV = new System.Windows.Forms.TextBox();
            this.txbLabelStartupVoltage = new System.Windows.Forms.TextBox();
            this.panelErrorStartupVoltage = new System.Windows.Forms.Panel();
            this.numStartupVoltage = new System.Windows.Forms.NumericUpDown();
            this.txbLabelMinVoltage = new System.Windows.Forms.TextBox();
            this.txbLabelMaxVoltage = new System.Windows.Forms.TextBox();
            this.panelErrorMinVoltage = new System.Windows.Forms.Panel();
            this.numMinVoltage = new System.Windows.Forms.NumericUpDown();
            this.txbLabelMarginLowPercent = new System.Windows.Forms.TextBox();
            this.txbLabelMarginHighPercent = new System.Windows.Forms.TextBox();
            this.panelErrorMaxVoltage = new System.Windows.Forms.Panel();
            this.numMaxVoltage = new System.Windows.Forms.NumericUpDown();
            this.txbLabelNominalVoltage = new System.Windows.Forms.TextBox();
            this.panelErrorNominalVoltage = new System.Windows.Forms.Panel();
            this.numNominalVoltage = new System.Windows.Forms.NumericUpDown();
            this.panelErrorMarginLowPercent = new System.Windows.Forms.Panel();
            this.numMarginLowPercent = new System.Windows.Forms.NumericUpDown();
            this.panelErrorMarginHighPercent = new System.Windows.Forms.Panel();
            this.numMarginHighPercent = new System.Windows.Forms.NumericUpDown();
            this.txbLabelMarginLowV = new System.Windows.Forms.TextBox();
            this.panel1TrimMergCircuitParams = new System.Windows.Forms.Panel();
            this.buttHideTrimMergCircParam = new System.Windows.Forms.PictureBox();
            this.s = new System.Windows.Forms.Label();
            this.panel1HardwareParams = new System.Windows.Forms.Panel();
            this.buttHideHardParam = new System.Windows.Forms.PictureBox();
            this.ss = new System.Windows.Forms.Label();
            this.panel1VoltageParams = new System.Windows.Forms.Panel();
            this.buttHideVoltParam = new System.Windows.Forms.PictureBox();
            this.label9 = new System.Windows.Forms.Label();
            this.panel1Basic = new System.Windows.Forms.Panel();
            this.label8 = new System.Windows.Forms.Label();
            this.buttHideBasic = new System.Windows.Forms.PictureBox();
            this.tlpCalculated = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel4 = new System.Windows.Forms.TableLayoutPanel();
            this.tableActualValues = new System.Windows.Forms.TableLayoutPanel();
            this.textBoxMinVoltageError = new System.Windows.Forms.TextBox();
            this.textBoxMaxVoltageError = new System.Windows.Forms.TextBox();
            this.textBoxVoutRippleError = new System.Windows.Forms.TextBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.labelErrorCalcMinVoltageActual = new System.Windows.Forms.Label();
            this.numCalcMinVoltageActual = new System.Windows.Forms.NumericUpDown();
            this.panelVoutMaxActual = new System.Windows.Forms.Panel();
            this.numCalcMaxVoltageActual = new System.Windows.Forms.NumericUpDown();
            this.panelVoutRippleActual = new System.Windows.Forms.Panel();
            this.numCalcVoutRippleActual = new System.Windows.Forms.NumericUpDown();
            this.panelR3plusR4Actual = new System.Windows.Forms.Panel();
            this.numR3plusR4Actual = new System.Windows.Forms.NumericUpDown();
            this.textBoxR3plusR4Error = new System.Windows.Forms.TextBox();
            this.tableCalculatedIdealValues = new System.Windows.Forms.TableLayoutPanel();
            this.panelR3plusR4Calc = new System.Windows.Forms.Panel();
            this.numR3plusR4Calc = new System.Windows.Forms.NumericUpDown();
            this.panelR2Calc = new System.Windows.Forms.Panel();
            this.numR2Calc = new System.Windows.Forms.NumericUpDown();
            this.tlpBasic = new System.Windows.Forms.TableLayoutPanel();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.panel7 = new System.Windows.Forms.Panel();
            this.toolTip = new System.Windows.Forms.ToolTip(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxCircuit)).BeginInit();
            this.panelCalculatedIdealValues.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.buttHideCalculatedIdealValues)).BeginInit();
            this.panelActualValues.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.buttHideActualValues)).BeginInit();
            this.panelError.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_errorProvider)).BeginInit();
            this.tableTrimMergCircParam.SuspendLayout();
            this.panelErrorC1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numC1)).BeginInit();
            this.panel16.SuspendLayout();
            this.panelErrorR4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numR4)).BeginInit();
            this.panelErrorR1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numR1)).BeginInit();
            this.panelErrorR3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numR3)).BeginInit();
            this.panel6.SuspendLayout();
            this.panelErrorR2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numR2)).BeginInit();
            this.panel5.SuspendLayout();
            this.panel4.SuspendLayout();
            this.panel3.SuspendLayout();
            this.panel2.SuspendLayout();
            this.tableHardParam.SuspendLayout();
            this.panelErrorVohOfPwmOutput.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numVohOfPwmOutput)).BeginInit();
            this.panelErrorNominalVadjOutput.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numNominalVadjOutput)).BeginInit();
            this.panelErrorDesiredVoutRipple.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numDesiredVoutRipple)).BeginInit();
            this.tableBasic.SuspendLayout();
            this.panel8.SuspendLayout();
            this.panelErrorControlSampleTime.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numControlSampleTime)).BeginInit();
            this.tableVoltParam.SuspendLayout();
            this.panelErrorMarginLowV.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numMarginLowV)).BeginInit();
            this.panelErrorMarginHighV.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numMarginHighV)).BeginInit();
            this.panelErrorStartupVoltage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numStartupVoltage)).BeginInit();
            this.panelErrorMinVoltage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numMinVoltage)).BeginInit();
            this.panelErrorMaxVoltage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numMaxVoltage)).BeginInit();
            this.panelErrorNominalVoltage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numNominalVoltage)).BeginInit();
            this.panelErrorMarginLowPercent.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numMarginLowPercent)).BeginInit();
            this.panelErrorMarginHighPercent.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numMarginHighPercent)).BeginInit();
            this.panel1TrimMergCircuitParams.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.buttHideTrimMergCircParam)).BeginInit();
            this.panel1HardwareParams.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.buttHideHardParam)).BeginInit();
            this.panel1VoltageParams.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.buttHideVoltParam)).BeginInit();
            this.panel1Basic.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.buttHideBasic)).BeginInit();
            this.tlpCalculated.SuspendLayout();
            this.tableLayoutPanel4.SuspendLayout();
            this.tableActualValues.SuspendLayout();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numCalcMinVoltageActual)).BeginInit();
            this.panelVoutMaxActual.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numCalcMaxVoltageActual)).BeginInit();
            this.panelVoutRippleActual.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numCalcVoutRippleActual)).BeginInit();
            this.panelR3plusR4Actual.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numR3plusR4Actual)).BeginInit();
            this.tableCalculatedIdealValues.SuspendLayout();
            this.panelR3plusR4Calc.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numR3plusR4Calc)).BeginInit();
            this.panelR2Calc.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numR2Calc)).BeginInit();
            this.tlpBasic.SuspendLayout();
            this.panel7.SuspendLayout();
            this.SuspendLayout();
            // 
            // pictureBoxCircuit
            // 
            this.pictureBoxCircuit.BackColor = System.Drawing.SystemColors.Control;
            resources.ApplyResources(this.pictureBoxCircuit, "pictureBoxCircuit");
            this.pictureBoxCircuit.Name = "pictureBoxCircuit";
            this.pictureBoxCircuit.TabStop = false;
            // 
            // buttonOk
            // 
            resources.ApplyResources(this.buttonOk, "buttonOk");
            this.buttonOk.Name = "buttonOk";
            this.buttonOk.UseVisualStyleBackColor = true;
            // 
            // buttonApply
            // 
            resources.ApplyResources(this.buttonApply, "buttonApply");
            this.buttonApply.Name = "buttonApply";
            this.buttonApply.UseVisualStyleBackColor = true;
            // 
            // buttonCancel
            // 
            resources.ApplyResources(this.buttonCancel, "buttonCancel");
            this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.UseVisualStyleBackColor = true;
            // 
            // panelCalculatedIdealValues
            // 
            this.panelCalculatedIdealValues.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.panelCalculatedIdealValues.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelCalculatedIdealValues.Controls.Add(this.buttHideCalculatedIdealValues);
            this.panelCalculatedIdealValues.Controls.Add(this.label5);
            resources.ApplyResources(this.panelCalculatedIdealValues, "panelCalculatedIdealValues");
            this.panelCalculatedIdealValues.Name = "panelCalculatedIdealValues";
            // 
            // buttHideCalculatedIdealValues
            // 
            this.buttHideCalculatedIdealValues.Cursor = System.Windows.Forms.Cursors.Hand;
            this.buttHideCalculatedIdealValues.Image = global::TrimMargin_v3_0.Resources.minus;
            resources.ApplyResources(this.buttHideCalculatedIdealValues, "buttHideCalculatedIdealValues");
            this.buttHideCalculatedIdealValues.Name = "buttHideCalculatedIdealValues";
            this.buttHideCalculatedIdealValues.TabStop = false;
            // 
            // label5
            // 
            resources.ApplyResources(this.label5, "label5");
            this.label5.Name = "label5";
            // 
            // txbLabelR2Calc
            // 
            this.txbLabelR2Calc.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelR2Calc.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelR2Calc.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelR2Calc, "txbLabelR2Calc");
            this.txbLabelR2Calc.Name = "txbLabelR2Calc";
            this.txbLabelR2Calc.ReadOnly = true;
            this.txbLabelR2Calc.TabStop = false;
            // 
            // txbLabelR3plusR4Calc
            // 
            this.txbLabelR3plusR4Calc.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelR3plusR4Calc.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelR3plusR4Calc.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelR3plusR4Calc, "txbLabelR3plusR4Calc");
            this.txbLabelR3plusR4Calc.Name = "txbLabelR3plusR4Calc";
            this.txbLabelR3plusR4Calc.ReadOnly = true;
            this.txbLabelR3plusR4Calc.TabStop = false;
            // 
            // panelActualValues
            // 
            this.panelActualValues.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.panelActualValues.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelActualValues.Controls.Add(this.buttHideActualValues);
            this.panelActualValues.Controls.Add(this.label6);
            resources.ApplyResources(this.panelActualValues, "panelActualValues");
            this.panelActualValues.Name = "panelActualValues";
            // 
            // buttHideActualValues
            // 
            this.buttHideActualValues.Cursor = System.Windows.Forms.Cursors.Hand;
            this.buttHideActualValues.Image = global::TrimMargin_v3_0.Resources.minus;
            resources.ApplyResources(this.buttHideActualValues, "buttHideActualValues");
            this.buttHideActualValues.Name = "buttHideActualValues";
            this.buttHideActualValues.TabStop = false;
            // 
            // label6
            // 
            resources.ApplyResources(this.label6, "label6");
            this.label6.Name = "label6";
            // 
            // panelError
            // 
            this.panelError.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.panelError.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelError.Controls.Add(this.labelError);
            resources.ApplyResources(this.panelError, "panelError");
            this.panelError.Name = "panelError";
            // 
            // labelError
            // 
            resources.ApplyResources(this.labelError, "labelError");
            this.labelError.Name = "labelError";
            // 
            // txbLabelCalcMinVoltageActual
            // 
            this.txbLabelCalcMinVoltageActual.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelCalcMinVoltageActual.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelCalcMinVoltageActual.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelCalcMinVoltageActual, "txbLabelCalcMinVoltageActual");
            this.txbLabelCalcMinVoltageActual.Name = "txbLabelCalcMinVoltageActual";
            this.txbLabelCalcMinVoltageActual.ReadOnly = true;
            this.txbLabelCalcMinVoltageActual.TabStop = false;
            // 
            // txbLabelCalcMaxVoltageActual
            // 
            this.txbLabelCalcMaxVoltageActual.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelCalcMaxVoltageActual.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelCalcMaxVoltageActual.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelCalcMaxVoltageActual, "txbLabelCalcMaxVoltageActual");
            this.txbLabelCalcMaxVoltageActual.Name = "txbLabelCalcMaxVoltageActual";
            this.txbLabelCalcMaxVoltageActual.ReadOnly = true;
            this.txbLabelCalcMaxVoltageActual.TabStop = false;
            // 
            // txbLabelCalcVoutRippleActual
            // 
            this.txbLabelCalcVoutRippleActual.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelCalcVoutRippleActual.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelCalcVoutRippleActual.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelCalcVoutRippleActual, "txbLabelCalcVoutRippleActual");
            this.txbLabelCalcVoutRippleActual.Name = "txbLabelCalcVoutRippleActual";
            this.txbLabelCalcVoutRippleActual.ReadOnly = true;
            this.txbLabelCalcVoutRippleActual.TabStop = false;
            // 
            // txbLabelR3plusR4Actual
            // 
            this.txbLabelR3plusR4Actual.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelR3plusR4Actual.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelR3plusR4Actual.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelR3plusR4Actual, "txbLabelR3plusR4Actual");
            this.txbLabelR3plusR4Actual.Name = "txbLabelR3plusR4Actual";
            this.txbLabelR3plusR4Actual.ReadOnly = true;
            this.txbLabelR3plusR4Actual.TabStop = false;
            // 
            // m_errorProvider
            // 
            this.m_errorProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.m_errorProvider.ContainerControl = this;
            // 
            // tableTrimMergCircParam
            // 
            resources.ApplyResources(this.tableTrimMergCircParam, "tableTrimMergCircParam");
            this.tableTrimMergCircParam.Controls.Add(this.panelErrorC1, 1, 6);
            this.tableTrimMergCircParam.Controls.Add(this.panel16, 0, 6);
            this.tableTrimMergCircParam.Controls.Add(this.panelErrorR4, 1, 5);
            this.tableTrimMergCircParam.Controls.Add(this.panelErrorR1, 1, 2);
            this.tableTrimMergCircParam.Controls.Add(this.panelErrorR3, 1, 4);
            this.tableTrimMergCircParam.Controls.Add(this.panel6, 1, 0);
            this.tableTrimMergCircParam.Controls.Add(this.panelErrorR2, 1, 3);
            this.tableTrimMergCircParam.Controls.Add(this.txbLabelResistorsESeries, 0, 0);
            this.tableTrimMergCircParam.Controls.Add(this.panel5, 1, 1);
            this.tableTrimMergCircParam.Controls.Add(this.panel4, 0, 3);
            this.tableTrimMergCircParam.Controls.Add(this.panel3, 0, 4);
            this.tableTrimMergCircParam.Controls.Add(this.panel2, 0, 5);
            this.tableTrimMergCircParam.Controls.Add(this.txbLabelCapacitorESeries, 0, 1);
            this.tableTrimMergCircParam.Controls.Add(this.txbLabelR1, 0, 2);
            this.tableTrimMergCircParam.Name = "tableTrimMergCircParam";
            // 
            // panelErrorC1
            // 
            this.panelErrorC1.BackColor = System.Drawing.SystemColors.Window;
            this.panelErrorC1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelErrorC1.Controls.Add(this.numC1);
            resources.ApplyResources(this.panelErrorC1, "panelErrorC1");
            this.panelErrorC1.Name = "panelErrorC1";
            // 
            // numC1
            // 
            this.numC1.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.numC1.DecimalPlaces = 3;
            this.numC1.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            resources.ApplyResources(this.numC1, "numC1");
            this.numC1.Maximum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            0});
            this.numC1.Minimum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            -2147483648});
            this.numC1.Name = "numC1";
            this.numC1.Value = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            // 
            // panel16
            // 
            resources.ApplyResources(this.panel16, "panel16");
            this.panel16.Controls.Add(this.checkBoxEnableC1);
            this.panel16.Controls.Add(this.txbLabelC1);
            this.panel16.Name = "panel16";
            // 
            // checkBoxEnableC1
            // 
            resources.ApplyResources(this.checkBoxEnableC1, "checkBoxEnableC1");
            this.checkBoxEnableC1.Name = "checkBoxEnableC1";
            this.checkBoxEnableC1.UseVisualStyleBackColor = true;
            // 
            // txbLabelC1
            // 
            this.txbLabelC1.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelC1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelC1.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelC1, "txbLabelC1");
            this.txbLabelC1.Name = "txbLabelC1";
            this.txbLabelC1.ReadOnly = true;
            this.txbLabelC1.TabStop = false;
            // 
            // panelErrorR4
            // 
            this.panelErrorR4.BackColor = System.Drawing.SystemColors.Window;
            this.panelErrorR4.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelErrorR4.Controls.Add(this.numR4);
            resources.ApplyResources(this.panelErrorR4, "panelErrorR4");
            this.panelErrorR4.Name = "panelErrorR4";
            // 
            // numR4
            // 
            this.numR4.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.numR4.DecimalPlaces = 3;
            this.numR4.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            resources.ApplyResources(this.numR4, "numR4");
            this.numR4.Maximum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            0});
            this.numR4.Minimum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            -2147483648});
            this.numR4.Name = "numR4";
            this.numR4.Value = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            // 
            // panelErrorR1
            // 
            this.panelErrorR1.BackColor = System.Drawing.SystemColors.Window;
            this.panelErrorR1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelErrorR1.Controls.Add(this.numR1);
            resources.ApplyResources(this.panelErrorR1, "panelErrorR1");
            this.panelErrorR1.Name = "panelErrorR1";
            // 
            // numR1
            // 
            this.numR1.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.numR1.DecimalPlaces = 3;
            this.numR1.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            resources.ApplyResources(this.numR1, "numR1");
            this.numR1.Maximum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            0});
            this.numR1.Minimum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            -2147483648});
            this.numR1.Name = "numR1";
            this.numR1.Value = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            // 
            // panelErrorR3
            // 
            this.panelErrorR3.BackColor = System.Drawing.SystemColors.Window;
            this.panelErrorR3.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelErrorR3.Controls.Add(this.numR3);
            resources.ApplyResources(this.panelErrorR3, "panelErrorR3");
            this.panelErrorR3.Name = "panelErrorR3";
            // 
            // numR3
            // 
            this.numR3.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.numR3.DecimalPlaces = 3;
            this.numR3.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            resources.ApplyResources(this.numR3, "numR3");
            this.numR3.Maximum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            0});
            this.numR3.Minimum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            -2147483648});
            this.numR3.Name = "numR3";
            this.numR3.Value = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            // 
            // panel6
            // 
            this.panel6.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel6.Controls.Add(this.comboBoxResistorsESeries);
            resources.ApplyResources(this.panel6, "panel6");
            this.panel6.Name = "panel6";
            // 
            // comboBoxResistorsESeries
            // 
            this.comboBoxResistorsESeries.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxResistorsESeries.FormattingEnabled = true;
            this.comboBoxResistorsESeries.Items.AddRange(new object[] {
            resources.GetString("comboBoxResistorsESeries.Items"),
            resources.GetString("comboBoxResistorsESeries.Items1"),
            resources.GetString("comboBoxResistorsESeries.Items2"),
            resources.GetString("comboBoxResistorsESeries.Items3")});
            resources.ApplyResources(this.comboBoxResistorsESeries, "comboBoxResistorsESeries");
            this.comboBoxResistorsESeries.Name = "comboBoxResistorsESeries";
            // 
            // panelErrorR2
            // 
            this.panelErrorR2.BackColor = System.Drawing.SystemColors.Window;
            this.panelErrorR2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelErrorR2.Controls.Add(this.numR2);
            resources.ApplyResources(this.panelErrorR2, "panelErrorR2");
            this.panelErrorR2.Name = "panelErrorR2";
            // 
            // numR2
            // 
            this.numR2.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.numR2.DecimalPlaces = 3;
            this.numR2.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            resources.ApplyResources(this.numR2, "numR2");
            this.numR2.Maximum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            0});
            this.numR2.Minimum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            -2147483648});
            this.numR2.Name = "numR2";
            this.numR2.Value = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            // 
            // txbLabelResistorsESeries
            // 
            this.txbLabelResistorsESeries.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelResistorsESeries.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelResistorsESeries.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelResistorsESeries, "txbLabelResistorsESeries");
            this.txbLabelResistorsESeries.Name = "txbLabelResistorsESeries";
            this.txbLabelResistorsESeries.ReadOnly = true;
            this.txbLabelResistorsESeries.TabStop = false;
            // 
            // panel5
            // 
            this.panel5.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel5.Controls.Add(this.comboBoxCapacitorESeries);
            resources.ApplyResources(this.panel5, "panel5");
            this.panel5.Name = "panel5";
            // 
            // comboBoxCapacitorESeries
            // 
            this.comboBoxCapacitorESeries.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxCapacitorESeries.FormattingEnabled = true;
            this.comboBoxCapacitorESeries.Items.AddRange(new object[] {
            resources.GetString("comboBoxCapacitorESeries.Items"),
            resources.GetString("comboBoxCapacitorESeries.Items1"),
            resources.GetString("comboBoxCapacitorESeries.Items2"),
            resources.GetString("comboBoxCapacitorESeries.Items3")});
            resources.ApplyResources(this.comboBoxCapacitorESeries, "comboBoxCapacitorESeries");
            this.comboBoxCapacitorESeries.Name = "comboBoxCapacitorESeries";
            // 
            // panel4
            // 
            resources.ApplyResources(this.panel4, "panel4");
            this.panel4.Controls.Add(this.checkBoxEnableR2);
            this.panel4.Controls.Add(this.txbLabelR2);
            this.panel4.Name = "panel4";
            // 
            // checkBoxEnableR2
            // 
            resources.ApplyResources(this.checkBoxEnableR2, "checkBoxEnableR2");
            this.checkBoxEnableR2.Name = "checkBoxEnableR2";
            this.checkBoxEnableR2.UseVisualStyleBackColor = true;
            // 
            // txbLabelR2
            // 
            this.txbLabelR2.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelR2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelR2.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelR2, "txbLabelR2");
            this.txbLabelR2.Name = "txbLabelR2";
            this.txbLabelR2.ReadOnly = true;
            this.txbLabelR2.TabStop = false;
            // 
            // panel3
            // 
            resources.ApplyResources(this.panel3, "panel3");
            this.panel3.Controls.Add(this.checkBoxEnableR3);
            this.panel3.Controls.Add(this.txbLabelR3);
            this.panel3.Name = "panel3";
            // 
            // checkBoxEnableR3
            // 
            resources.ApplyResources(this.checkBoxEnableR3, "checkBoxEnableR3");
            this.checkBoxEnableR3.Name = "checkBoxEnableR3";
            this.checkBoxEnableR3.UseVisualStyleBackColor = true;
            // 
            // txbLabelR3
            // 
            this.txbLabelR3.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelR3.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelR3.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelR3, "txbLabelR3");
            this.txbLabelR3.Name = "txbLabelR3";
            this.txbLabelR3.ReadOnly = true;
            this.txbLabelR3.TabStop = false;
            // 
            // panel2
            // 
            resources.ApplyResources(this.panel2, "panel2");
            this.panel2.Controls.Add(this.checkBoxEnableR4);
            this.panel2.Controls.Add(this.txbLabelR4);
            this.panel2.Name = "panel2";
            // 
            // checkBoxEnableR4
            // 
            resources.ApplyResources(this.checkBoxEnableR4, "checkBoxEnableR4");
            this.checkBoxEnableR4.Name = "checkBoxEnableR4";
            this.checkBoxEnableR4.UseVisualStyleBackColor = true;
            // 
            // txbLabelR4
            // 
            this.txbLabelR4.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelR4.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelR4.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelR4, "txbLabelR4");
            this.txbLabelR4.Name = "txbLabelR4";
            this.txbLabelR4.ReadOnly = true;
            this.txbLabelR4.TabStop = false;
            // 
            // txbLabelCapacitorESeries
            // 
            this.txbLabelCapacitorESeries.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelCapacitorESeries.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelCapacitorESeries.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelCapacitorESeries, "txbLabelCapacitorESeries");
            this.txbLabelCapacitorESeries.Name = "txbLabelCapacitorESeries";
            this.txbLabelCapacitorESeries.ReadOnly = true;
            this.txbLabelCapacitorESeries.TabStop = false;
            // 
            // txbLabelR1
            // 
            this.txbLabelR1.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelR1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelR1.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelR1, "txbLabelR1");
            this.txbLabelR1.Name = "txbLabelR1";
            this.txbLabelR1.ReadOnly = true;
            this.txbLabelR1.TabStop = false;
            // 
            // tableHardParam
            // 
            resources.ApplyResources(this.tableHardParam, "tableHardParam");
            this.tableHardParam.Controls.Add(this.txbLabelVadjVref, 0, 1);
            this.tableHardParam.Controls.Add(this.txbLabelBoxVohOfPwmOutput, 0, 0);
            this.tableHardParam.Controls.Add(this.panelErrorVohOfPwmOutput, 1, 0);
            this.tableHardParam.Controls.Add(this.panelErrorNominalVadjOutput, 1, 1);
            this.tableHardParam.Controls.Add(this.txbLabelDesiredVoutRipple, 0, 2);
            this.tableHardParam.Controls.Add(this.panelErrorDesiredVoutRipple, 1, 2);
            this.tableHardParam.Name = "tableHardParam";
            // 
            // txbLabelNominalVadjOutput
            // 
            this.txbLabelVadjVref.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelVadjVref.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelVadjVref.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelVadjVref, "txbLabelNominalVadjOutput");
            this.txbLabelVadjVref.Name = "txbLabelNominalVadjOutput";
            this.txbLabelVadjVref.ReadOnly = true;
            this.txbLabelVadjVref.TabStop = false;
            // 
            // txbLabelBoxVohOfPwmOutput
            // 
            this.txbLabelBoxVohOfPwmOutput.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelBoxVohOfPwmOutput.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelBoxVohOfPwmOutput.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelBoxVohOfPwmOutput, "txbLabelBoxVohOfPwmOutput");
            this.txbLabelBoxVohOfPwmOutput.Name = "txbLabelBoxVohOfPwmOutput";
            this.txbLabelBoxVohOfPwmOutput.ReadOnly = true;
            this.txbLabelBoxVohOfPwmOutput.TabStop = false;
            // 
            // panelErrorVohOfPwmOutput
            // 
            this.panelErrorVohOfPwmOutput.BackColor = System.Drawing.SystemColors.Window;
            this.panelErrorVohOfPwmOutput.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelErrorVohOfPwmOutput.Controls.Add(this.numVohOfPwmOutput);
            resources.ApplyResources(this.panelErrorVohOfPwmOutput, "panelErrorVohOfPwmOutput");
            this.panelErrorVohOfPwmOutput.Name = "panelErrorVohOfPwmOutput";
            // 
            // numVohOfPwmOutput
            // 
            this.numVohOfPwmOutput.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.numVohOfPwmOutput.DecimalPlaces = 3;
            this.numVohOfPwmOutput.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            resources.ApplyResources(this.numVohOfPwmOutput, "numVohOfPwmOutput");
            this.numVohOfPwmOutput.Maximum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            0});
            this.numVohOfPwmOutput.Minimum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            -2147483648});
            this.numVohOfPwmOutput.Name = "numVohOfPwmOutput";
            this.numVohOfPwmOutput.Value = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            // 
            // panelErrorNominalVadjOutput
            // 
            this.panelErrorNominalVadjOutput.BackColor = System.Drawing.SystemColors.Window;
            this.panelErrorNominalVadjOutput.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelErrorNominalVadjOutput.Controls.Add(this.numNominalVadjOutput);
            resources.ApplyResources(this.panelErrorNominalVadjOutput, "panelErrorNominalVadjOutput");
            this.panelErrorNominalVadjOutput.Name = "panelErrorNominalVadjOutput";
            // 
            // numNominalVadjOutput
            // 
            this.numNominalVadjOutput.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.numNominalVadjOutput.DecimalPlaces = 3;
            this.numNominalVadjOutput.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            resources.ApplyResources(this.numNominalVadjOutput, "numNominalVadjOutput");
            this.numNominalVadjOutput.Maximum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            0});
            this.numNominalVadjOutput.Minimum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            -2147483648});
            this.numNominalVadjOutput.Name = "numNominalVadjOutput";
            this.numNominalVadjOutput.Value = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            // 
            // txbLabelDesiredVoutRipple
            // 
            this.txbLabelDesiredVoutRipple.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelDesiredVoutRipple.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelDesiredVoutRipple.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelDesiredVoutRipple, "txbLabelDesiredVoutRipple");
            this.txbLabelDesiredVoutRipple.Name = "txbLabelDesiredVoutRipple";
            this.txbLabelDesiredVoutRipple.ReadOnly = true;
            this.txbLabelDesiredVoutRipple.TabStop = false;
            // 
            // panelErrorDesiredVoutRipple
            // 
            this.panelErrorDesiredVoutRipple.BackColor = System.Drawing.SystemColors.Window;
            this.panelErrorDesiredVoutRipple.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelErrorDesiredVoutRipple.Controls.Add(this.numDesiredVoutRipple);
            resources.ApplyResources(this.panelErrorDesiredVoutRipple, "panelErrorDesiredVoutRipple");
            this.panelErrorDesiredVoutRipple.Name = "panelErrorDesiredVoutRipple";
            // 
            // numDesiredVoutRipple
            // 
            this.numDesiredVoutRipple.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.numDesiredVoutRipple.DecimalPlaces = 3;
            this.numDesiredVoutRipple.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            resources.ApplyResources(this.numDesiredVoutRipple, "numDesiredVoutRipple");
            this.numDesiredVoutRipple.Maximum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            0});
            this.numDesiredVoutRipple.Minimum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            -2147483648});
            this.numDesiredVoutRipple.Name = "numDesiredVoutRipple";
            this.numDesiredVoutRipple.Value = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            // 
            // tableBasic
            // 
            resources.ApplyResources(this.tableBasic, "tableBasic");
            this.tableBasic.Controls.Add(this.panel8, 1, 1);
            this.tableBasic.Controls.Add(this.panelErrorControlSampleTime, 1, 2);
            this.tableBasic.Controls.Add(this.txbLabelFeedback, 0, 1);
            this.tableBasic.Controls.Add(this.textBoxConverterName, 1, 0);
            this.tableBasic.Controls.Add(this.txbLabelConverterName, 0, 0);
            this.tableBasic.Controls.Add(this.txbLabelControlSampleTime, 0, 2);
            this.tableBasic.Name = "tableBasic";
            // 
            // panel8
            // 
            this.panel8.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel8.Controls.Add(this.comboBoxFeedback);
            resources.ApplyResources(this.panel8, "panel8");
            this.panel8.Name = "panel8";
            // 
            // comboBoxFeedback
            // 
            this.comboBoxFeedback.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxFeedback.FormattingEnabled = true;
            this.comboBoxFeedback.Items.AddRange(new object[] {
            resources.GetString("comboBoxFeedback.Items"),
            resources.GetString("comboBoxFeedback.Items1")});
            resources.ApplyResources(this.comboBoxFeedback, "comboBoxFeedback");
            this.comboBoxFeedback.Name = "comboBoxFeedback";
            // 
            // panelErrorControlSampleTime
            // 
            this.panelErrorControlSampleTime.BackColor = System.Drawing.SystemColors.Window;
            this.panelErrorControlSampleTime.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelErrorControlSampleTime.Controls.Add(this.numControlSampleTime);
            resources.ApplyResources(this.panelErrorControlSampleTime, "panelErrorControlSampleTime");
            this.panelErrorControlSampleTime.Name = "panelErrorControlSampleTime";
            // 
            // numControlSampleTime
            // 
            this.numControlSampleTime.BorderStyle = System.Windows.Forms.BorderStyle.None;
            resources.ApplyResources(this.numControlSampleTime, "numControlSampleTime");
            this.numControlSampleTime.Maximum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            0});
            this.numControlSampleTime.Minimum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            -2147483648});
            this.numControlSampleTime.Name = "numControlSampleTime";
            this.numControlSampleTime.Value = new decimal(new int[] {
            50,
            0,
            0,
            0});
            // 
            // txbLabelFeedback
            // 
            this.txbLabelFeedback.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelFeedback.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelFeedback.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelFeedback, "txbLabelFeedback");
            this.txbLabelFeedback.Name = "txbLabelFeedback";
            this.txbLabelFeedback.ReadOnly = true;
            this.txbLabelFeedback.TabStop = false;
            // 
            // textBoxConverterName
            // 
            this.textBoxConverterName.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            resources.ApplyResources(this.textBoxConverterName, "textBoxConverterName");
            this.textBoxConverterName.Name = "textBoxConverterName";
            // 
            // txbLabelConverterName
            // 
            this.txbLabelConverterName.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelConverterName.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelConverterName.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelConverterName, "txbLabelConverterName");
            this.txbLabelConverterName.Name = "txbLabelConverterName";
            this.txbLabelConverterName.ReadOnly = true;
            this.txbLabelConverterName.TabStop = false;
            // 
            // txbLabelControlSampleTime
            // 
            this.txbLabelControlSampleTime.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelControlSampleTime.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelControlSampleTime.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelControlSampleTime, "txbLabelControlSampleTime");
            this.txbLabelControlSampleTime.Name = "txbLabelControlSampleTime";
            this.txbLabelControlSampleTime.ReadOnly = true;
            this.txbLabelControlSampleTime.TabStop = false;
            // 
            // tableVoltParam
            // 
            resources.ApplyResources(this.tableVoltParam, "tableVoltParam");
            this.tableVoltParam.Controls.Add(this.panelErrorMarginLowV, 1, 4);
            this.tableVoltParam.Controls.Add(this.panelErrorMarginHighV, 1, 2);
            this.tableVoltParam.Controls.Add(this.txbLabelMarginHighV, 0, 2);
            this.tableVoltParam.Controls.Add(this.txbLabelStartupVoltage, 0, 7);
            this.tableVoltParam.Controls.Add(this.panelErrorStartupVoltage, 1, 7);
            this.tableVoltParam.Controls.Add(this.txbLabelMinVoltage, 0, 6);
            this.tableVoltParam.Controls.Add(this.txbLabelMaxVoltage, 0, 5);
            this.tableVoltParam.Controls.Add(this.panelErrorMinVoltage, 1, 6);
            this.tableVoltParam.Controls.Add(this.txbLabelMarginLowPercent, 0, 3);
            this.tableVoltParam.Controls.Add(this.txbLabelMarginHighPercent, 0, 1);
            this.tableVoltParam.Controls.Add(this.panelErrorMaxVoltage, 1, 5);
            this.tableVoltParam.Controls.Add(this.txbLabelNominalVoltage, 0, 0);
            this.tableVoltParam.Controls.Add(this.panelErrorNominalVoltage, 1, 0);
            this.tableVoltParam.Controls.Add(this.panelErrorMarginLowPercent, 1, 3);
            this.tableVoltParam.Controls.Add(this.panelErrorMarginHighPercent, 1, 1);
            this.tableVoltParam.Controls.Add(this.txbLabelMarginLowV, 0, 4);
            this.tableVoltParam.Name = "tableVoltParam";
            // 
            // panelErrorMarginLowV
            // 
            this.panelErrorMarginLowV.BackColor = System.Drawing.SystemColors.ControlLight;
            this.panelErrorMarginLowV.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelErrorMarginLowV.Controls.Add(this.numMarginLowV);
            resources.ApplyResources(this.panelErrorMarginLowV, "panelErrorMarginLowV");
            this.panelErrorMarginLowV.Name = "panelErrorMarginLowV";
            // 
            // numMarginLowV
            // 
            this.numMarginLowV.BackColor = System.Drawing.SystemColors.ControlLight;
            this.numMarginLowV.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.numMarginLowV.DecimalPlaces = 3;
            this.numMarginLowV.Increment = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            this.numMarginLowV.InterceptArrowKeys = false;
            resources.ApplyResources(this.numMarginLowV, "numMarginLowV");
            this.numMarginLowV.Maximum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            0});
            this.numMarginLowV.Minimum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            -2147483648});
            this.numMarginLowV.Name = "numMarginLowV";
            this.numMarginLowV.ReadOnly = true;
            this.numMarginLowV.Value = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            // 
            // panelErrorMarginHighV
            // 
            this.panelErrorMarginHighV.BackColor = System.Drawing.SystemColors.ControlLight;
            this.panelErrorMarginHighV.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelErrorMarginHighV.Controls.Add(this.numMarginHighV);
            resources.ApplyResources(this.panelErrorMarginHighV, "panelErrorMarginHighV");
            this.panelErrorMarginHighV.Name = "panelErrorMarginHighV";
            // 
            // numMarginHighV
            // 
            this.numMarginHighV.BackColor = System.Drawing.SystemColors.ControlLight;
            this.numMarginHighV.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.numMarginHighV.DecimalPlaces = 3;
            this.numMarginHighV.Increment = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            this.numMarginHighV.InterceptArrowKeys = false;
            resources.ApplyResources(this.numMarginHighV, "numMarginHighV");
            this.numMarginHighV.Maximum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            0});
            this.numMarginHighV.Minimum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            -2147483648});
            this.numMarginHighV.Name = "numMarginHighV";
            this.numMarginHighV.ReadOnly = true;
            this.numMarginHighV.Value = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            // 
            // txbLabelMarginHighV
            // 
            this.txbLabelMarginHighV.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelMarginHighV.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelMarginHighV.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelMarginHighV, "txbLabelMarginHighV");
            this.txbLabelMarginHighV.Name = "txbLabelMarginHighV";
            this.txbLabelMarginHighV.ReadOnly = true;
            this.txbLabelMarginHighV.TabStop = false;
            // 
            // txbLabelStartupVoltage
            // 
            this.txbLabelStartupVoltage.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelStartupVoltage.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelStartupVoltage.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelStartupVoltage, "txbLabelStartupVoltage");
            this.txbLabelStartupVoltage.Name = "txbLabelStartupVoltage";
            this.txbLabelStartupVoltage.ReadOnly = true;
            this.txbLabelStartupVoltage.TabStop = false;
            // 
            // panelErrorStartupVoltage
            // 
            this.panelErrorStartupVoltage.BackColor = System.Drawing.SystemColors.Window;
            this.panelErrorStartupVoltage.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelErrorStartupVoltage.Controls.Add(this.numStartupVoltage);
            resources.ApplyResources(this.panelErrorStartupVoltage, "panelErrorStartupVoltage");
            this.panelErrorStartupVoltage.Name = "panelErrorStartupVoltage";
            // 
            // numStartupVoltage
            // 
            this.numStartupVoltage.BackColor = System.Drawing.SystemColors.Window;
            this.numStartupVoltage.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.numStartupVoltage.DecimalPlaces = 3;
            this.numStartupVoltage.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            resources.ApplyResources(this.numStartupVoltage, "numStartupVoltage");
            this.numStartupVoltage.Maximum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            0});
            this.numStartupVoltage.Minimum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            -2147483648});
            this.numStartupVoltage.Name = "numStartupVoltage";
            this.numStartupVoltage.Value = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            // 
            // txbLabelMinVoltage
            // 
            this.txbLabelMinVoltage.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelMinVoltage.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelMinVoltage.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelMinVoltage, "txbLabelMinVoltage");
            this.txbLabelMinVoltage.Name = "txbLabelMinVoltage";
            this.txbLabelMinVoltage.ReadOnly = true;
            this.txbLabelMinVoltage.TabStop = false;
            // 
            // txbLabelMaxVoltage
            // 
            this.txbLabelMaxVoltage.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelMaxVoltage.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelMaxVoltage.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelMaxVoltage, "txbLabelMaxVoltage");
            this.txbLabelMaxVoltage.Name = "txbLabelMaxVoltage";
            this.txbLabelMaxVoltage.ReadOnly = true;
            this.txbLabelMaxVoltage.TabStop = false;
            // 
            // panelErrorMinVoltage
            // 
            this.panelErrorMinVoltage.BackColor = System.Drawing.SystemColors.Window;
            this.panelErrorMinVoltage.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelErrorMinVoltage.Controls.Add(this.numMinVoltage);
            resources.ApplyResources(this.panelErrorMinVoltage, "panelErrorMinVoltage");
            this.panelErrorMinVoltage.Name = "panelErrorMinVoltage";
            // 
            // numMinVoltage
            // 
            this.numMinVoltage.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.numMinVoltage.DecimalPlaces = 3;
            this.numMinVoltage.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            resources.ApplyResources(this.numMinVoltage, "numMinVoltage");
            this.numMinVoltage.Maximum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            0});
            this.numMinVoltage.Minimum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            -2147483648});
            this.numMinVoltage.Name = "numMinVoltage";
            this.numMinVoltage.Value = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            // 
            // txbLabelMarginLowPercent
            // 
            this.txbLabelMarginLowPercent.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelMarginLowPercent.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelMarginLowPercent.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelMarginLowPercent, "txbLabelMarginLowPercent");
            this.txbLabelMarginLowPercent.Name = "txbLabelMarginLowPercent";
            this.txbLabelMarginLowPercent.ReadOnly = true;
            this.txbLabelMarginLowPercent.TabStop = false;
            // 
            // txbLabelMarginHighPercent
            // 
            this.txbLabelMarginHighPercent.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelMarginHighPercent.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelMarginHighPercent.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelMarginHighPercent, "txbLabelMarginHighPercent");
            this.txbLabelMarginHighPercent.Name = "txbLabelMarginHighPercent";
            this.txbLabelMarginHighPercent.ReadOnly = true;
            this.txbLabelMarginHighPercent.TabStop = false;
            // 
            // panelErrorMaxVoltage
            // 
            this.panelErrorMaxVoltage.BackColor = System.Drawing.SystemColors.Window;
            this.panelErrorMaxVoltage.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelErrorMaxVoltage.Controls.Add(this.numMaxVoltage);
            resources.ApplyResources(this.panelErrorMaxVoltage, "panelErrorMaxVoltage");
            this.panelErrorMaxVoltage.Name = "panelErrorMaxVoltage";
            // 
            // numMaxVoltage
            // 
            this.numMaxVoltage.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.numMaxVoltage.DecimalPlaces = 3;
            this.numMaxVoltage.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            resources.ApplyResources(this.numMaxVoltage, "numMaxVoltage");
            this.numMaxVoltage.Maximum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            0});
            this.numMaxVoltage.Minimum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            -2147483648});
            this.numMaxVoltage.Name = "numMaxVoltage";
            this.numMaxVoltage.Value = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            // 
            // txbLabelNominalVoltage
            // 
            this.txbLabelNominalVoltage.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelNominalVoltage.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelNominalVoltage.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelNominalVoltage, "txbLabelNominalVoltage");
            this.txbLabelNominalVoltage.Name = "txbLabelNominalVoltage";
            this.txbLabelNominalVoltage.ReadOnly = true;
            this.txbLabelNominalVoltage.TabStop = false;
            // 
            // panelErrorNominalVoltage
            // 
            this.panelErrorNominalVoltage.BackColor = System.Drawing.SystemColors.Window;
            this.panelErrorNominalVoltage.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelErrorNominalVoltage.Controls.Add(this.numNominalVoltage);
            resources.ApplyResources(this.panelErrorNominalVoltage, "panelErrorNominalVoltage");
            this.panelErrorNominalVoltage.Name = "panelErrorNominalVoltage";
            // 
            // numNominalVoltage
            // 
            this.numNominalVoltage.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.numNominalVoltage.DecimalPlaces = 3;
            this.numNominalVoltage.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            resources.ApplyResources(this.numNominalVoltage, "numNominalVoltage");
            this.numNominalVoltage.Maximum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            0});
            this.numNominalVoltage.Minimum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            -2147483648});
            this.numNominalVoltage.Name = "numNominalVoltage";
            this.numNominalVoltage.Value = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            // 
            // panelErrorMarginLowPercent
            // 
            this.panelErrorMarginLowPercent.BackColor = System.Drawing.SystemColors.Window;
            this.panelErrorMarginLowPercent.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelErrorMarginLowPercent.Controls.Add(this.numMarginLowPercent);
            resources.ApplyResources(this.panelErrorMarginLowPercent, "panelErrorMarginLowPercent");
            this.panelErrorMarginLowPercent.Name = "panelErrorMarginLowPercent";
            // 
            // numMarginLowPercent
            // 
            this.numMarginLowPercent.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.numMarginLowPercent.DecimalPlaces = 2;
            this.numMarginLowPercent.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            resources.ApplyResources(this.numMarginLowPercent, "numMarginLowPercent");
            this.numMarginLowPercent.Maximum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            0});
            this.numMarginLowPercent.Minimum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            -2147483648});
            this.numMarginLowPercent.Name = "numMarginLowPercent";
            // 
            // panelErrorMarginHighPercent
            // 
            this.panelErrorMarginHighPercent.BackColor = System.Drawing.SystemColors.Window;
            this.panelErrorMarginHighPercent.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelErrorMarginHighPercent.Controls.Add(this.numMarginHighPercent);
            resources.ApplyResources(this.panelErrorMarginHighPercent, "panelErrorMarginHighPercent");
            this.panelErrorMarginHighPercent.Name = "panelErrorMarginHighPercent";
            // 
            // numMarginHighPercent
            // 
            this.numMarginHighPercent.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.numMarginHighPercent.DecimalPlaces = 2;
            this.numMarginHighPercent.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            resources.ApplyResources(this.numMarginHighPercent, "numMarginHighPercent");
            this.numMarginHighPercent.Maximum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            0});
            this.numMarginHighPercent.Minimum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            -2147483648});
            this.numMarginHighPercent.Name = "numMarginHighPercent";
            // 
            // txbLabelMarginLowV
            // 
            this.txbLabelMarginLowV.BackColor = System.Drawing.SystemColors.Window;
            this.txbLabelMarginLowV.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txbLabelMarginLowV.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.txbLabelMarginLowV, "txbLabelMarginLowV");
            this.txbLabelMarginLowV.Name = "txbLabelMarginLowV";
            this.txbLabelMarginLowV.ReadOnly = true;
            this.txbLabelMarginLowV.TabStop = false;
            // 
            // panel1TrimMergCircuitParams
            // 
            this.panel1TrimMergCircuitParams.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.panel1TrimMergCircuitParams.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1TrimMergCircuitParams.Controls.Add(this.buttHideTrimMergCircParam);
            this.panel1TrimMergCircuitParams.Controls.Add(this.s);
            resources.ApplyResources(this.panel1TrimMergCircuitParams, "panel1TrimMergCircuitParams");
            this.panel1TrimMergCircuitParams.Name = "panel1TrimMergCircuitParams";
            // 
            // buttHideTrimMergCircParam
            // 
            this.buttHideTrimMergCircParam.Cursor = System.Windows.Forms.Cursors.Hand;
            this.buttHideTrimMergCircParam.Image = global::TrimMargin_v3_0.Resources.minus;
            resources.ApplyResources(this.buttHideTrimMergCircParam, "buttHideTrimMergCircParam");
            this.buttHideTrimMergCircParam.Name = "buttHideTrimMergCircParam";
            this.buttHideTrimMergCircParam.TabStop = false;
            // 
            // s
            // 
            resources.ApplyResources(this.s, "s");
            this.s.Name = "s";
            // 
            // panel1HardwareParams
            // 
            this.panel1HardwareParams.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.panel1HardwareParams.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1HardwareParams.Controls.Add(this.buttHideHardParam);
            this.panel1HardwareParams.Controls.Add(this.ss);
            resources.ApplyResources(this.panel1HardwareParams, "panel1HardwareParams");
            this.panel1HardwareParams.Name = "panel1HardwareParams";
            // 
            // buttHideHardParam
            // 
            this.buttHideHardParam.Cursor = System.Windows.Forms.Cursors.Hand;
            this.buttHideHardParam.Image = global::TrimMargin_v3_0.Resources.minus;
            resources.ApplyResources(this.buttHideHardParam, "buttHideHardParam");
            this.buttHideHardParam.Name = "buttHideHardParam";
            this.buttHideHardParam.TabStop = false;
            // 
            // ss
            // 
            resources.ApplyResources(this.ss, "ss");
            this.ss.Name = "ss";
            // 
            // panel1VoltageParams
            // 
            this.panel1VoltageParams.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.panel1VoltageParams.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1VoltageParams.Controls.Add(this.buttHideVoltParam);
            this.panel1VoltageParams.Controls.Add(this.label9);
            resources.ApplyResources(this.panel1VoltageParams, "panel1VoltageParams");
            this.panel1VoltageParams.Name = "panel1VoltageParams";
            // 
            // buttHideVoltParam
            // 
            this.buttHideVoltParam.Cursor = System.Windows.Forms.Cursors.Hand;
            this.buttHideVoltParam.Image = global::TrimMargin_v3_0.Resources.minus;
            resources.ApplyResources(this.buttHideVoltParam, "buttHideVoltParam");
            this.buttHideVoltParam.Name = "buttHideVoltParam";
            this.buttHideVoltParam.TabStop = false;
            // 
            // label9
            // 
            resources.ApplyResources(this.label9, "label9");
            this.label9.Name = "label9";
            // 
            // panel1Basic
            // 
            this.panel1Basic.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.panel1Basic.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1Basic.Controls.Add(this.label8);
            this.panel1Basic.Controls.Add(this.buttHideBasic);
            resources.ApplyResources(this.panel1Basic, "panel1Basic");
            this.panel1Basic.Name = "panel1Basic";
            // 
            // label8
            // 
            resources.ApplyResources(this.label8, "label8");
            this.label8.Name = "label8";
            // 
            // buttHideBasic
            // 
            this.buttHideBasic.Cursor = System.Windows.Forms.Cursors.Hand;
            this.buttHideBasic.Image = global::TrimMargin_v3_0.Resources.minus;
            resources.ApplyResources(this.buttHideBasic, "buttHideBasic");
            this.buttHideBasic.Name = "buttHideBasic";
            this.buttHideBasic.TabStop = false;
            // 
            // tlpCalculated
            // 
            resources.ApplyResources(this.tlpCalculated, "tlpCalculated");
            this.tlpCalculated.Controls.Add(this.tableLayoutPanel4, 0, 2);
            this.tlpCalculated.Controls.Add(this.tableActualValues, 0, 3);
            this.tlpCalculated.Controls.Add(this.panelCalculatedIdealValues, 0, 0);
            this.tlpCalculated.Controls.Add(this.tableCalculatedIdealValues, 0, 1);
            this.tlpCalculated.Name = "tlpCalculated";
            // 
            // tableLayoutPanel4
            // 
            resources.ApplyResources(this.tableLayoutPanel4, "tableLayoutPanel4");
            this.tableLayoutPanel4.Controls.Add(this.panelActualValues, 0, 0);
            this.tableLayoutPanel4.Controls.Add(this.panelError, 1, 0);
            this.tableLayoutPanel4.Name = "tableLayoutPanel4";
            // 
            // tableActualValues
            // 
            resources.ApplyResources(this.tableActualValues, "tableActualValues");
            this.tableActualValues.Controls.Add(this.textBoxMinVoltageError, 2, 3);
            this.tableActualValues.Controls.Add(this.textBoxMaxVoltageError, 2, 2);
            this.tableActualValues.Controls.Add(this.textBoxVoutRippleError, 2, 1);
            this.tableActualValues.Controls.Add(this.panel1, 1, 3);
            this.tableActualValues.Controls.Add(this.panelVoutMaxActual, 1, 2);
            this.tableActualValues.Controls.Add(this.panelVoutRippleActual, 1, 1);
            this.tableActualValues.Controls.Add(this.panelR3plusR4Actual, 1, 0);
            this.tableActualValues.Controls.Add(this.txbLabelR3plusR4Actual, 0, 0);
            this.tableActualValues.Controls.Add(this.txbLabelCalcVoutRippleActual, 0, 1);
            this.tableActualValues.Controls.Add(this.txbLabelCalcMinVoltageActual, 0, 3);
            this.tableActualValues.Controls.Add(this.txbLabelCalcMaxVoltageActual, 0, 2);
            this.tableActualValues.Controls.Add(this.textBoxR3plusR4Error, 2, 0);
            this.tableActualValues.Name = "tableActualValues";
            // 
            // textBoxMinVoltageError
            // 
            this.textBoxMinVoltageError.BackColor = System.Drawing.SystemColors.ControlLight;
            this.textBoxMinVoltageError.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            resources.ApplyResources(this.textBoxMinVoltageError, "textBoxMinVoltageError");
            this.textBoxMinVoltageError.Name = "textBoxMinVoltageError";
            this.textBoxMinVoltageError.ReadOnly = true;
            this.textBoxMinVoltageError.TabStop = false;
            // 
            // textBoxMaxVoltageError
            // 
            this.textBoxMaxVoltageError.BackColor = System.Drawing.SystemColors.ControlLight;
            this.textBoxMaxVoltageError.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            resources.ApplyResources(this.textBoxMaxVoltageError, "textBoxMaxVoltageError");
            this.textBoxMaxVoltageError.Name = "textBoxMaxVoltageError";
            this.textBoxMaxVoltageError.ReadOnly = true;
            this.textBoxMaxVoltageError.TabStop = false;
            // 
            // textBoxVoutRippleError
            // 
            this.textBoxVoutRippleError.BackColor = System.Drawing.SystemColors.ControlLight;
            this.textBoxVoutRippleError.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            resources.ApplyResources(this.textBoxVoutRippleError, "textBoxVoutRippleError");
            this.textBoxVoutRippleError.Name = "textBoxVoutRippleError";
            this.textBoxVoutRippleError.ReadOnly = true;
            this.textBoxVoutRippleError.TabStop = false;
            // 
            // panel1
            // 
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Controls.Add(this.labelErrorCalcMinVoltageActual);
            this.panel1.Controls.Add(this.numCalcMinVoltageActual);
            resources.ApplyResources(this.panel1, "panel1");
            this.panel1.Name = "panel1";
            // 
            // labelErrorCalcMinVoltageActual
            // 
            resources.ApplyResources(this.labelErrorCalcMinVoltageActual, "labelErrorCalcMinVoltageActual");
            this.labelErrorCalcMinVoltageActual.BackColor = System.Drawing.SystemColors.ControlLight;
            this.labelErrorCalcMinVoltageActual.Name = "labelErrorCalcMinVoltageActual";
            // 
            // numCalcMinVoltageActual
            // 
            this.numCalcMinVoltageActual.BackColor = System.Drawing.SystemColors.ControlLight;
            this.numCalcMinVoltageActual.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.numCalcMinVoltageActual.DecimalPlaces = 3;
            this.numCalcMinVoltageActual.Increment = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            this.numCalcMinVoltageActual.InterceptArrowKeys = false;
            resources.ApplyResources(this.numCalcMinVoltageActual, "numCalcMinVoltageActual");
            this.numCalcMinVoltageActual.Maximum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            0});
            this.numCalcMinVoltageActual.Minimum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            -2147483648});
            this.numCalcMinVoltageActual.Name = "numCalcMinVoltageActual";
            this.numCalcMinVoltageActual.ReadOnly = true;
            this.numCalcMinVoltageActual.TabStop = false;
            this.numCalcMinVoltageActual.Value = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            // 
            // panelVoutMaxActual
            // 
            this.panelVoutMaxActual.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelVoutMaxActual.Controls.Add(this.numCalcMaxVoltageActual);
            resources.ApplyResources(this.panelVoutMaxActual, "panelVoutMaxActual");
            this.panelVoutMaxActual.Name = "panelVoutMaxActual";
            // 
            // numCalcMaxVoltageActual
            // 
            this.numCalcMaxVoltageActual.BackColor = System.Drawing.SystemColors.ControlLight;
            this.numCalcMaxVoltageActual.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.numCalcMaxVoltageActual.DecimalPlaces = 3;
            this.numCalcMaxVoltageActual.Increment = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            this.numCalcMaxVoltageActual.InterceptArrowKeys = false;
            resources.ApplyResources(this.numCalcMaxVoltageActual, "numCalcMaxVoltageActual");
            this.numCalcMaxVoltageActual.Maximum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            0});
            this.numCalcMaxVoltageActual.Minimum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            -2147483648});
            this.numCalcMaxVoltageActual.Name = "numCalcMaxVoltageActual";
            this.numCalcMaxVoltageActual.ReadOnly = true;
            this.numCalcMaxVoltageActual.TabStop = false;
            this.numCalcMaxVoltageActual.Value = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            // 
            // panelVoutRippleActual
            // 
            this.panelVoutRippleActual.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelVoutRippleActual.Controls.Add(this.numCalcVoutRippleActual);
            resources.ApplyResources(this.panelVoutRippleActual, "panelVoutRippleActual");
            this.panelVoutRippleActual.Name = "panelVoutRippleActual";
            // 
            // numCalcVoutRippleActual
            // 
            this.numCalcVoutRippleActual.BackColor = System.Drawing.SystemColors.ControlLight;
            this.numCalcVoutRippleActual.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.numCalcVoutRippleActual.DecimalPlaces = 3;
            this.numCalcVoutRippleActual.Increment = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            this.numCalcVoutRippleActual.InterceptArrowKeys = false;
            resources.ApplyResources(this.numCalcVoutRippleActual, "numCalcVoutRippleActual");
            this.numCalcVoutRippleActual.Maximum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            0});
            this.numCalcVoutRippleActual.Minimum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            -2147483648});
            this.numCalcVoutRippleActual.Name = "numCalcVoutRippleActual";
            this.numCalcVoutRippleActual.ReadOnly = true;
            this.numCalcVoutRippleActual.TabStop = false;
            this.numCalcVoutRippleActual.Value = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            // 
            // panelR3plusR4Actual
            // 
            this.panelR3plusR4Actual.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelR3plusR4Actual.Controls.Add(this.numR3plusR4Actual);
            resources.ApplyResources(this.panelR3plusR4Actual, "panelR3plusR4Actual");
            this.panelR3plusR4Actual.Name = "panelR3plusR4Actual";
            // 
            // numR3plusR4Actual
            // 
            this.numR3plusR4Actual.BackColor = System.Drawing.SystemColors.ControlLight;
            this.numR3plusR4Actual.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.numR3plusR4Actual.DecimalPlaces = 3;
            this.numR3plusR4Actual.Increment = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            this.numR3plusR4Actual.InterceptArrowKeys = false;
            resources.ApplyResources(this.numR3plusR4Actual, "numR3plusR4Actual");
            this.numR3plusR4Actual.Maximum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            0});
            this.numR3plusR4Actual.Minimum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            -2147483648});
            this.numR3plusR4Actual.Name = "numR3plusR4Actual";
            this.numR3plusR4Actual.ReadOnly = true;
            this.numR3plusR4Actual.TabStop = false;
            this.numR3plusR4Actual.Value = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            // 
            // textBoxR3plusR4Error
            // 
            this.textBoxR3plusR4Error.BackColor = System.Drawing.SystemColors.ControlLight;
            this.textBoxR3plusR4Error.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            resources.ApplyResources(this.textBoxR3plusR4Error, "textBoxR3plusR4Error");
            this.textBoxR3plusR4Error.Name = "textBoxR3plusR4Error";
            this.textBoxR3plusR4Error.ReadOnly = true;
            this.textBoxR3plusR4Error.TabStop = false;
            // 
            // tableCalculatedIdealValues
            // 
            resources.ApplyResources(this.tableCalculatedIdealValues, "tableCalculatedIdealValues");
            this.tableCalculatedIdealValues.Controls.Add(this.panelR3plusR4Calc, 1, 1);
            this.tableCalculatedIdealValues.Controls.Add(this.panelR2Calc, 1, 0);
            this.tableCalculatedIdealValues.Controls.Add(this.txbLabelR2Calc, 0, 0);
            this.tableCalculatedIdealValues.Controls.Add(this.txbLabelR3plusR4Calc, 0, 1);
            this.tableCalculatedIdealValues.Name = "tableCalculatedIdealValues";
            // 
            // panelR3plusR4Calc
            // 
            this.panelR3plusR4Calc.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelR3plusR4Calc.Controls.Add(this.numR3plusR4Calc);
            resources.ApplyResources(this.panelR3plusR4Calc, "panelR3plusR4Calc");
            this.panelR3plusR4Calc.Name = "panelR3plusR4Calc";
            // 
            // numR3plusR4Calc
            // 
            this.numR3plusR4Calc.BackColor = System.Drawing.SystemColors.ControlLight;
            this.numR3plusR4Calc.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.numR3plusR4Calc.DecimalPlaces = 3;
            this.numR3plusR4Calc.Increment = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            this.numR3plusR4Calc.InterceptArrowKeys = false;
            resources.ApplyResources(this.numR3plusR4Calc, "numR3plusR4Calc");
            this.numR3plusR4Calc.Maximum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            0});
            this.numR3plusR4Calc.Minimum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            -2147483648});
            this.numR3plusR4Calc.Name = "numR3plusR4Calc";
            this.numR3plusR4Calc.ReadOnly = true;
            this.numR3plusR4Calc.TabStop = false;
            this.numR3plusR4Calc.Value = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            // 
            // panelR2Calc
            // 
            this.panelR2Calc.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelR2Calc.Controls.Add(this.numR2Calc);
            resources.ApplyResources(this.panelR2Calc, "panelR2Calc");
            this.panelR2Calc.Name = "panelR2Calc";
            // 
            // numR2Calc
            // 
            this.numR2Calc.BackColor = System.Drawing.SystemColors.ControlLight;
            this.numR2Calc.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.numR2Calc.DecimalPlaces = 3;
            this.numR2Calc.Increment = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            this.numR2Calc.InterceptArrowKeys = false;
            resources.ApplyResources(this.numR2Calc, "numR2Calc");
            this.numR2Calc.Maximum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            0});
            this.numR2Calc.Minimum = new decimal(new int[] {
            1316134911,
            2328,
            0,
            -2147483648});
            this.numR2Calc.Name = "numR2Calc";
            this.numR2Calc.ReadOnly = true;
            this.numR2Calc.TabStop = false;
            this.numR2Calc.Value = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            // 
            // tlpBasic
            // 
            resources.ApplyResources(this.tlpBasic, "tlpBasic");
            this.tlpBasic.Controls.Add(this.tableBasic, 0, 1);
            this.tlpBasic.Controls.Add(this.tableTrimMergCircParam, 0, 7);
            this.tlpBasic.Controls.Add(this.panel1Basic, 0, 0);
            this.tlpBasic.Controls.Add(this.panel1TrimMergCircuitParams, 0, 6);
            this.tlpBasic.Controls.Add(this.tableVoltParam, 0, 3);
            this.tlpBasic.Controls.Add(this.tableHardParam, 0, 5);
            this.tlpBasic.Controls.Add(this.panel1HardwareParams, 0, 4);
            this.tlpBasic.Controls.Add(this.panel1VoltageParams, 0, 2);
            this.tlpBasic.Name = "tlpBasic";
            // 
            // groupBox1
            // 
            resources.ApplyResources(this.groupBox1, "groupBox1");
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.TabStop = false;
            // 
            // panel7
            // 
            resources.ApplyResources(this.panel7, "panel7");
            this.panel7.Controls.Add(this.tlpBasic);
            this.panel7.Controls.Add(this.tlpCalculated);
            this.panel7.Controls.Add(this.pictureBoxCircuit);
            this.panel7.Name = "panel7";
            // 
            // toolTip
            // 
            this.toolTip.AutoPopDelay = 15000;
            this.toolTip.InitialDelay = 500;
            this.toolTip.IsBalloon = true;
            this.toolTip.ReshowDelay = 100;
            // 
            // CyConfigDialog
            // 
            this.AcceptButton = this.buttonOk;
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.buttonCancel;
            this.Controls.Add(this.panel7);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.buttonOk);
            this.Controls.Add(this.buttonApply);
            this.Controls.Add(this.buttonCancel);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "CyConfigDialog";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxCircuit)).EndInit();
            this.panelCalculatedIdealValues.ResumeLayout(false);
            this.panelCalculatedIdealValues.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.buttHideCalculatedIdealValues)).EndInit();
            this.panelActualValues.ResumeLayout(false);
            this.panelActualValues.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.buttHideActualValues)).EndInit();
            this.panelError.ResumeLayout(false);
            this.panelError.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_errorProvider)).EndInit();
            this.tableTrimMergCircParam.ResumeLayout(false);
            this.tableTrimMergCircParam.PerformLayout();
            this.panelErrorC1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numC1)).EndInit();
            this.panel16.ResumeLayout(false);
            this.panel16.PerformLayout();
            this.panelErrorR4.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numR4)).EndInit();
            this.panelErrorR1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numR1)).EndInit();
            this.panelErrorR3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numR3)).EndInit();
            this.panel6.ResumeLayout(false);
            this.panelErrorR2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numR2)).EndInit();
            this.panel5.ResumeLayout(false);
            this.panel4.ResumeLayout(false);
            this.panel4.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.tableHardParam.ResumeLayout(false);
            this.tableHardParam.PerformLayout();
            this.panelErrorVohOfPwmOutput.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numVohOfPwmOutput)).EndInit();
            this.panelErrorNominalVadjOutput.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numNominalVadjOutput)).EndInit();
            this.panelErrorDesiredVoutRipple.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numDesiredVoutRipple)).EndInit();
            this.tableBasic.ResumeLayout(false);
            this.tableBasic.PerformLayout();
            this.panel8.ResumeLayout(false);
            this.panelErrorControlSampleTime.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numControlSampleTime)).EndInit();
            this.tableVoltParam.ResumeLayout(false);
            this.tableVoltParam.PerformLayout();
            this.panelErrorMarginLowV.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numMarginLowV)).EndInit();
            this.panelErrorMarginHighV.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numMarginHighV)).EndInit();
            this.panelErrorStartupVoltage.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numStartupVoltage)).EndInit();
            this.panelErrorMinVoltage.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numMinVoltage)).EndInit();
            this.panelErrorMaxVoltage.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numMaxVoltage)).EndInit();
            this.panelErrorNominalVoltage.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numNominalVoltage)).EndInit();
            this.panelErrorMarginLowPercent.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numMarginLowPercent)).EndInit();
            this.panelErrorMarginHighPercent.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numMarginHighPercent)).EndInit();
            this.panel1TrimMergCircuitParams.ResumeLayout(false);
            this.panel1TrimMergCircuitParams.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.buttHideTrimMergCircParam)).EndInit();
            this.panel1HardwareParams.ResumeLayout(false);
            this.panel1HardwareParams.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.buttHideHardParam)).EndInit();
            this.panel1VoltageParams.ResumeLayout(false);
            this.panel1VoltageParams.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.buttHideVoltParam)).EndInit();
            this.panel1Basic.ResumeLayout(false);
            this.panel1Basic.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.buttHideBasic)).EndInit();
            this.tlpCalculated.ResumeLayout(false);
            this.tlpCalculated.PerformLayout();
            this.tableLayoutPanel4.ResumeLayout(false);
            this.tableActualValues.ResumeLayout(false);
            this.tableActualValues.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numCalcMinVoltageActual)).EndInit();
            this.panelVoutMaxActual.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numCalcMaxVoltageActual)).EndInit();
            this.panelVoutRippleActual.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numCalcVoutRippleActual)).EndInit();
            this.panelR3plusR4Actual.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numR3plusR4Actual)).EndInit();
            this.tableCalculatedIdealValues.ResumeLayout(false);
            this.tableCalculatedIdealValues.PerformLayout();
            this.panelR3plusR4Calc.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numR3plusR4Calc)).EndInit();
            this.panelR2Calc.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numR2Calc)).EndInit();
            this.tlpBasic.ResumeLayout(false);
            this.tlpBasic.PerformLayout();
            this.panel7.ResumeLayout(false);
            this.panel7.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBoxCircuit;
        private System.Windows.Forms.Button buttonOk;
        private System.Windows.Forms.Button buttonApply;
        private System.Windows.Forms.Button buttonCancel;
        private System.Windows.Forms.Panel panelCalculatedIdealValues;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txbLabelR2Calc;
        private System.Windows.Forms.TextBox txbLabelR3plusR4Calc;
        private System.Windows.Forms.Panel panelActualValues;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Panel panelError;
        private System.Windows.Forms.Label labelError;
        private System.Windows.Forms.TextBox txbLabelCalcMinVoltageActual;
        private System.Windows.Forms.TextBox txbLabelCalcMaxVoltageActual;
        private System.Windows.Forms.TextBox txbLabelCalcVoutRippleActual;
        private System.Windows.Forms.TextBox txbLabelR3plusR4Actual;
        private System.Windows.Forms.PictureBox buttHideCalculatedIdealValues;
        private System.Windows.Forms.PictureBox buttHideActualValues;
        private System.Windows.Forms.ErrorProvider m_errorProvider;
        private System.Windows.Forms.TableLayoutPanel tableHardParam;
        private System.Windows.Forms.TextBox txbLabelDesiredVoutRipple;
        private System.Windows.Forms.TextBox txbLabelVadjVref;
        private System.Windows.Forms.TextBox txbLabelBoxVohOfPwmOutput;
        private System.Windows.Forms.TableLayoutPanel tableBasic;
        private System.Windows.Forms.TextBox textBoxConverterName;
        private System.Windows.Forms.TextBox txbLabelConverterName;
        private System.Windows.Forms.TableLayoutPanel tableVoltParam;
        private System.Windows.Forms.TextBox txbLabelStartupVoltage;
        private System.Windows.Forms.TextBox txbLabelMinVoltage;
        private System.Windows.Forms.TextBox txbLabelMaxVoltage;
        private System.Windows.Forms.TextBox txbLabelMarginLowPercent;
        private System.Windows.Forms.TextBox txbLabelMarginHighPercent;
        private System.Windows.Forms.TextBox txbLabelNominalVoltage;
        private System.Windows.Forms.Panel panel1TrimMergCircuitParams;
        private System.Windows.Forms.PictureBox buttHideTrimMergCircParam;
        private System.Windows.Forms.Label s;
        private System.Windows.Forms.Panel panel1HardwareParams;
        private System.Windows.Forms.PictureBox buttHideHardParam;
        private System.Windows.Forms.Label ss;
        private System.Windows.Forms.Panel panel1VoltageParams;
        private System.Windows.Forms.PictureBox buttHideVoltParam;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Panel panel1Basic;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.PictureBox buttHideBasic;
        private System.Windows.Forms.TextBox txbLabelR4;
        private System.Windows.Forms.TextBox txbLabelR3;
        private System.Windows.Forms.TextBox txbLabelR2;
        private System.Windows.Forms.TextBox txbLabelR1;
        private System.Windows.Forms.TextBox txbLabelCapacitorESeries;
        private System.Windows.Forms.TextBox txbLabelResistorsESeries;
        private System.Windows.Forms.TableLayoutPanel tlpCalculated;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel4;
        private System.Windows.Forms.TableLayoutPanel tableActualValues;
        private System.Windows.Forms.TableLayoutPanel tableCalculatedIdealValues;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.CheckBox checkBoxEnableR4;
        private System.Windows.Forms.Panel panel4;
        private System.Windows.Forms.CheckBox checkBoxEnableR2;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.CheckBox checkBoxEnableR3;
        private System.Windows.Forms.ComboBox comboBoxResistorsESeries;
        private System.Windows.Forms.ComboBox comboBoxCapacitorESeries;
        private System.Windows.Forms.Panel panel6;
        private System.Windows.Forms.Panel panel5;
        private System.Windows.Forms.TableLayoutPanel tableTrimMergCircParam;
        private System.Windows.Forms.Panel panel16;
        private System.Windows.Forms.TableLayoutPanel tlpBasic;
        private System.Windows.Forms.TextBox txbLabelC1;
        private System.Windows.Forms.CheckBox checkBoxEnableC1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Panel panelErrorC1;
        private System.Windows.Forms.NumericUpDown numC1;
        private System.Windows.Forms.Panel panelErrorR4;
        private System.Windows.Forms.NumericUpDown numR4;
        private System.Windows.Forms.Panel panelErrorR1;
        private System.Windows.Forms.NumericUpDown numR1;
        private System.Windows.Forms.Panel panelErrorR3;
        private System.Windows.Forms.NumericUpDown numR3;
        private System.Windows.Forms.Panel panelErrorR2;
        private System.Windows.Forms.NumericUpDown numR2;
        private System.Windows.Forms.Panel panelErrorVohOfPwmOutput;
        private System.Windows.Forms.NumericUpDown numVohOfPwmOutput;
        private System.Windows.Forms.Panel panelErrorNominalVadjOutput;
        private System.Windows.Forms.NumericUpDown numNominalVadjOutput;
        private System.Windows.Forms.Panel panelErrorDesiredVoutRipple;
        private System.Windows.Forms.NumericUpDown numDesiredVoutRipple;
        private System.Windows.Forms.Panel panelErrorStartupVoltage;
        private System.Windows.Forms.NumericUpDown numStartupVoltage;
        private System.Windows.Forms.Panel panelErrorMinVoltage;
        private System.Windows.Forms.NumericUpDown numMinVoltage;
        private System.Windows.Forms.Panel panelErrorMaxVoltage;
        private System.Windows.Forms.NumericUpDown numMaxVoltage;
        private System.Windows.Forms.Panel panelErrorNominalVoltage;
        private System.Windows.Forms.NumericUpDown numNominalVoltage;
        private System.Windows.Forms.Panel panelErrorMarginLowPercent;
        private System.Windows.Forms.NumericUpDown numMarginLowPercent;
        private System.Windows.Forms.Panel panelErrorMarginHighPercent;
        private System.Windows.Forms.NumericUpDown numMarginHighPercent;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.NumericUpDown numCalcMinVoltageActual;
        private System.Windows.Forms.Panel panelVoutMaxActual;
        private System.Windows.Forms.NumericUpDown numCalcMaxVoltageActual;
        private System.Windows.Forms.Panel panelVoutRippleActual;
        private System.Windows.Forms.NumericUpDown numCalcVoutRippleActual;
        private System.Windows.Forms.Panel panelR3plusR4Actual;
        private System.Windows.Forms.NumericUpDown numR3plusR4Actual;
        private System.Windows.Forms.Panel panelR3plusR4Calc;
        private System.Windows.Forms.NumericUpDown numR3plusR4Calc;
        private System.Windows.Forms.Panel panelR2Calc;
        private System.Windows.Forms.NumericUpDown numR2Calc;
        private System.Windows.Forms.TextBox textBoxMinVoltageError;
        private System.Windows.Forms.TextBox textBoxMaxVoltageError;
        private System.Windows.Forms.TextBox textBoxVoutRippleError;
        private System.Windows.Forms.TextBox textBoxR3plusR4Error;
        private System.Windows.Forms.Panel panel7;
        private System.Windows.Forms.Panel panelErrorMarginLowV;
        private System.Windows.Forms.NumericUpDown numMarginLowV;
        private System.Windows.Forms.Panel panelErrorMarginHighV;
        private System.Windows.Forms.NumericUpDown numMarginHighV;
        private System.Windows.Forms.TextBox txbLabelMarginHighV;
        private System.Windows.Forms.TextBox txbLabelMarginLowV;
        private System.Windows.Forms.Label labelErrorCalcMinVoltageActual;
        private System.Windows.Forms.ToolTip toolTip;
        private System.Windows.Forms.NumericUpDown numControlSampleTime;
        private System.Windows.Forms.TextBox txbLabelControlSampleTime;
        private System.Windows.Forms.Panel panel8;
        private System.Windows.Forms.ComboBox comboBoxFeedback;
        private System.Windows.Forms.Panel panelErrorControlSampleTime;
        private System.Windows.Forms.TextBox txbLabelFeedback;
    }
}
