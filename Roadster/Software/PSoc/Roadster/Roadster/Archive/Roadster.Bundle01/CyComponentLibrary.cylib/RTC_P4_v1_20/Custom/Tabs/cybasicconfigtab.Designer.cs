namespace RTC_P4_v1_20.Tabs
{
    partial class CyBasicConfigTab
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyBasicConfigTab));
            this.m_dtpDate = new System.Windows.Forms.DateTimePicker();
            this.m_lblInitialDate = new System.Windows.Forms.Label();
            this.m_chbUpdateManualy = new System.Windows.Forms.CheckBox();
            this.m_chbAlarm = new System.Windows.Forms.CheckBox();
            this.m_chbDaylingSavings = new System.Windows.Forms.CheckBox();
            this.m_gbTimeFormat = new System.Windows.Forms.GroupBox();
            this.m_rb24Hour = new System.Windows.Forms.RadioButton();
            this.m_rb12Hour = new System.Windows.Forms.RadioButton();
            this.m_gbDateFormat = new System.Windows.Forms.GroupBox();
            this.m_rbYYYYMMDD = new System.Windows.Forms.RadioButton();
            this.m_rbDDMMYYYY = new System.Windows.Forms.RadioButton();
            this.m_rbMMDDYYYY = new System.Windows.Forms.RadioButton();
            this.m_lblNote = new System.Windows.Forms.Label();
            this.m_gbDSTSettings = new System.Windows.Forms.GroupBox();
            this.tableLayoutPanel5 = new System.Windows.Forms.TableLayoutPanel();
            this.flowLayoutPanel2 = new System.Windows.Forms.FlowLayoutPanel();
            this.m_cmbHoursStop = new System.Windows.Forms.ComboBox();
            this.m_lblHrsStop = new System.Windows.Forms.Label();
            this.m_numDayOfMonthStop = new System.Windows.Forms.NumericUpDown();
            this.m_cmbWeekOfMonthStop = new System.Windows.Forms.ComboBox();
            this.m_cmdDayOfWeekStop = new System.Windows.Forms.ComboBox();
            this.m_lblOfStop = new System.Windows.Forms.Label();
            this.m_lblOfStopRelative = new System.Windows.Forms.Label();
            this.m_cmbMonthStop = new System.Windows.Forms.ComboBox();
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.m_cmbHoursStart = new System.Windows.Forms.ComboBox();
            this.m_lblHrsStart = new System.Windows.Forms.Label();
            this.m_numDayOfMonthStart = new System.Windows.Forms.NumericUpDown();
            this.m_cmbWeekOfMonthStart = new System.Windows.Forms.ComboBox();
            this.m_cmdDayOfWeekStart = new System.Windows.Forms.ComboBox();
            this.m_lblOfStart = new System.Windows.Forms.Label();
            this.m_lblOfStartRelative = new System.Windows.Forms.Label();
            this.m_cmbMonthStart = new System.Windows.Forms.ComboBox();
            this.m_lblDSTStop = new System.Windows.Forms.Label();
            this.m_lblDSTStart = new System.Windows.Forms.Label();
            this.m_rbFixedDate = new System.Windows.Forms.RadioButton();
            this.m_rbRelativeDate = new System.Windows.Forms.RadioButton();
            this.m_lblInitialTime = new System.Windows.Forms.Label();
            this.m_dtpTime = new System.Windows.Forms.DateTimePicker();
            this.m_btUpdateToSysTime = new System.Windows.Forms.Button();
            this.m_btUpdateToSysDate = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel4 = new System.Windows.Forms.TableLayoutPanel();
            this.m_gbTimeFormat.SuspendLayout();
            this.m_gbDateFormat.SuspendLayout();
            this.m_gbDSTSettings.SuspendLayout();
            this.tableLayoutPanel5.SuspendLayout();
            this.flowLayoutPanel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numDayOfMonthStop)).BeginInit();
            this.flowLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numDayOfMonthStart)).BeginInit();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.tableLayoutPanel3.SuspendLayout();
            this.tableLayoutPanel4.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_dtpDate
            // 
            resources.ApplyResources(this.m_dtpDate, "m_dtpDate");
            this.m_dtpDate.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
            this.m_dtpDate.Name = "m_dtpDate";
            // 
            // m_lblInitialDate
            // 
            resources.ApplyResources(this.m_lblInitialDate, "m_lblInitialDate");
            this.m_lblInitialDate.Name = "m_lblInitialDate";
            // 
            // m_chbUpdateManualy
            // 
            resources.ApplyResources(this.m_chbUpdateManualy, "m_chbUpdateManualy");
            this.m_chbUpdateManualy.Name = "m_chbUpdateManualy";
            this.m_chbUpdateManualy.UseVisualStyleBackColor = true;
            // 
            // m_chbAlarm
            // 
            resources.ApplyResources(this.m_chbAlarm, "m_chbAlarm");
            this.m_chbAlarm.Name = "m_chbAlarm";
            this.m_chbAlarm.UseVisualStyleBackColor = true;
            // 
            // m_chbDaylingSavings
            // 
            resources.ApplyResources(this.m_chbDaylingSavings, "m_chbDaylingSavings");
            this.m_chbDaylingSavings.Name = "m_chbDaylingSavings";
            this.m_chbDaylingSavings.UseVisualStyleBackColor = true;
            // 
            // m_gbTimeFormat
            // 
            this.m_gbTimeFormat.Controls.Add(this.m_rb24Hour);
            this.m_gbTimeFormat.Controls.Add(this.m_rb12Hour);
            resources.ApplyResources(this.m_gbTimeFormat, "m_gbTimeFormat");
            this.m_gbTimeFormat.Name = "m_gbTimeFormat";
            this.m_gbTimeFormat.TabStop = false;
            // 
            // m_rb24Hour
            // 
            resources.ApplyResources(this.m_rb24Hour, "m_rb24Hour");
            this.m_rb24Hour.Name = "m_rb24Hour";
            this.m_rb24Hour.TabStop = true;
            this.m_rb24Hour.UseVisualStyleBackColor = true;
            // 
            // m_rb12Hour
            // 
            resources.ApplyResources(this.m_rb12Hour, "m_rb12Hour");
            this.m_rb12Hour.Name = "m_rb12Hour";
            this.m_rb12Hour.TabStop = true;
            this.m_rb12Hour.UseVisualStyleBackColor = true;
            // 
            // m_gbDateFormat
            // 
            this.m_gbDateFormat.Controls.Add(this.m_rbYYYYMMDD);
            this.m_gbDateFormat.Controls.Add(this.m_rbDDMMYYYY);
            this.m_gbDateFormat.Controls.Add(this.m_rbMMDDYYYY);
            resources.ApplyResources(this.m_gbDateFormat, "m_gbDateFormat");
            this.m_gbDateFormat.Name = "m_gbDateFormat";
            this.m_gbDateFormat.TabStop = false;
            // 
            // m_rbYYYYMMDD
            // 
            resources.ApplyResources(this.m_rbYYYYMMDD, "m_rbYYYYMMDD");
            this.m_rbYYYYMMDD.Name = "m_rbYYYYMMDD";
            this.m_rbYYYYMMDD.TabStop = true;
            this.m_rbYYYYMMDD.UseVisualStyleBackColor = true;
            // 
            // m_rbDDMMYYYY
            // 
            resources.ApplyResources(this.m_rbDDMMYYYY, "m_rbDDMMYYYY");
            this.m_rbDDMMYYYY.Name = "m_rbDDMMYYYY";
            this.m_rbDDMMYYYY.TabStop = true;
            this.m_rbDDMMYYYY.UseVisualStyleBackColor = true;
            // 
            // m_rbMMDDYYYY
            // 
            resources.ApplyResources(this.m_rbMMDDYYYY, "m_rbMMDDYYYY");
            this.m_rbMMDDYYYY.Name = "m_rbMMDDYYYY";
            this.m_rbMMDDYYYY.TabStop = true;
            this.m_rbMMDDYYYY.UseVisualStyleBackColor = true;
            // 
            // m_lblNote
            // 
            resources.ApplyResources(this.m_lblNote, "m_lblNote");
            this.m_lblNote.Name = "m_lblNote";
            // 
            // m_gbDSTSettings
            // 
            resources.ApplyResources(this.m_gbDSTSettings, "m_gbDSTSettings");
            this.m_gbDSTSettings.Controls.Add(this.tableLayoutPanel5);
            this.m_gbDSTSettings.Controls.Add(this.m_rbFixedDate);
            this.m_gbDSTSettings.Controls.Add(this.m_rbRelativeDate);
            this.m_gbDSTSettings.Name = "m_gbDSTSettings";
            this.m_gbDSTSettings.TabStop = false;
            // 
            // tableLayoutPanel5
            // 
            resources.ApplyResources(this.tableLayoutPanel5, "tableLayoutPanel5");
            this.tableLayoutPanel5.Controls.Add(this.flowLayoutPanel2, 1, 1);
            this.tableLayoutPanel5.Controls.Add(this.flowLayoutPanel1, 1, 0);
            this.tableLayoutPanel5.Controls.Add(this.m_lblDSTStop, 0, 1);
            this.tableLayoutPanel5.Controls.Add(this.m_lblDSTStart, 0, 0);
            this.tableLayoutPanel5.Name = "tableLayoutPanel5";
            // 
            // flowLayoutPanel2
            // 
            this.flowLayoutPanel2.Controls.Add(this.m_cmbHoursStop);
            this.flowLayoutPanel2.Controls.Add(this.m_lblHrsStop);
            this.flowLayoutPanel2.Controls.Add(this.m_numDayOfMonthStop);
            this.flowLayoutPanel2.Controls.Add(this.m_cmbWeekOfMonthStop);
            this.flowLayoutPanel2.Controls.Add(this.m_cmdDayOfWeekStop);
            this.flowLayoutPanel2.Controls.Add(this.m_lblOfStop);
            this.flowLayoutPanel2.Controls.Add(this.m_lblOfStopRelative);
            this.flowLayoutPanel2.Controls.Add(this.m_cmbMonthStop);
            resources.ApplyResources(this.flowLayoutPanel2, "flowLayoutPanel2");
            this.flowLayoutPanel2.Name = "flowLayoutPanel2";
            // 
            // m_cmbHoursStop
            // 
            this.m_cmbHoursStop.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmbHoursStop.FormattingEnabled = true;
            resources.ApplyResources(this.m_cmbHoursStop, "m_cmbHoursStop");
            this.m_cmbHoursStop.Name = "m_cmbHoursStop";
            // 
            // m_lblHrsStop
            // 
            resources.ApplyResources(this.m_lblHrsStop, "m_lblHrsStop");
            this.m_lblHrsStop.Name = "m_lblHrsStop";
            // 
            // m_numDayOfMonthStop
            // 
            resources.ApplyResources(this.m_numDayOfMonthStop, "m_numDayOfMonthStop");
            this.m_numDayOfMonthStop.Maximum = new decimal(new int[] {
            999999,
            0,
            0,
            0});
            this.m_numDayOfMonthStop.Name = "m_numDayOfMonthStop";
            // 
            // m_cmbWeekOfMonthStop
            // 
            this.m_cmbWeekOfMonthStop.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmbWeekOfMonthStop.FormattingEnabled = true;
            resources.ApplyResources(this.m_cmbWeekOfMonthStop, "m_cmbWeekOfMonthStop");
            this.m_cmbWeekOfMonthStop.Name = "m_cmbWeekOfMonthStop";
            // 
            // m_cmdDayOfWeekStop
            // 
            this.m_cmdDayOfWeekStop.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmdDayOfWeekStop.FormattingEnabled = true;
            resources.ApplyResources(this.m_cmdDayOfWeekStop, "m_cmdDayOfWeekStop");
            this.m_cmdDayOfWeekStop.Name = "m_cmdDayOfWeekStop";
            // 
            // m_lblOfStop
            // 
            resources.ApplyResources(this.m_lblOfStop, "m_lblOfStop");
            this.m_lblOfStop.Name = "m_lblOfStop";
            // 
            // m_lblOfStopRelative
            // 
            resources.ApplyResources(this.m_lblOfStopRelative, "m_lblOfStopRelative");
            this.m_lblOfStopRelative.Name = "m_lblOfStopRelative";
            // 
            // m_cmbMonthStop
            // 
            this.m_cmbMonthStop.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmbMonthStop.FormattingEnabled = true;
            resources.ApplyResources(this.m_cmbMonthStop, "m_cmbMonthStop");
            this.m_cmbMonthStop.Name = "m_cmbMonthStop";
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.Controls.Add(this.m_cmbHoursStart);
            this.flowLayoutPanel1.Controls.Add(this.m_lblHrsStart);
            this.flowLayoutPanel1.Controls.Add(this.m_numDayOfMonthStart);
            this.flowLayoutPanel1.Controls.Add(this.m_cmbWeekOfMonthStart);
            this.flowLayoutPanel1.Controls.Add(this.m_cmdDayOfWeekStart);
            this.flowLayoutPanel1.Controls.Add(this.m_lblOfStart);
            this.flowLayoutPanel1.Controls.Add(this.m_lblOfStartRelative);
            this.flowLayoutPanel1.Controls.Add(this.m_cmbMonthStart);
            resources.ApplyResources(this.flowLayoutPanel1, "flowLayoutPanel1");
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            // 
            // m_cmbHoursStart
            // 
            this.m_cmbHoursStart.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmbHoursStart.FormattingEnabled = true;
            resources.ApplyResources(this.m_cmbHoursStart, "m_cmbHoursStart");
            this.m_cmbHoursStart.Name = "m_cmbHoursStart";
            // 
            // m_lblHrsStart
            // 
            resources.ApplyResources(this.m_lblHrsStart, "m_lblHrsStart");
            this.m_lblHrsStart.Name = "m_lblHrsStart";
            // 
            // m_numDayOfMonthStart
            // 
            resources.ApplyResources(this.m_numDayOfMonthStart, "m_numDayOfMonthStart");
            this.m_numDayOfMonthStart.Maximum = new decimal(new int[] {
            999999,
            0,
            0,
            0});
            this.m_numDayOfMonthStart.Name = "m_numDayOfMonthStart";
            // 
            // m_cmbWeekOfMonthStart
            // 
            this.m_cmbWeekOfMonthStart.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmbWeekOfMonthStart.FormattingEnabled = true;
            resources.ApplyResources(this.m_cmbWeekOfMonthStart, "m_cmbWeekOfMonthStart");
            this.m_cmbWeekOfMonthStart.Name = "m_cmbWeekOfMonthStart";
            // 
            // m_cmdDayOfWeekStart
            // 
            this.m_cmdDayOfWeekStart.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmdDayOfWeekStart.FormattingEnabled = true;
            resources.ApplyResources(this.m_cmdDayOfWeekStart, "m_cmdDayOfWeekStart");
            this.m_cmdDayOfWeekStart.Name = "m_cmdDayOfWeekStart";
            // 
            // m_lblOfStart
            // 
            resources.ApplyResources(this.m_lblOfStart, "m_lblOfStart");
            this.m_lblOfStart.Name = "m_lblOfStart";
            // 
            // m_lblOfStartRelative
            // 
            resources.ApplyResources(this.m_lblOfStartRelative, "m_lblOfStartRelative");
            this.m_lblOfStartRelative.Name = "m_lblOfStartRelative";
            // 
            // m_cmbMonthStart
            // 
            this.m_cmbMonthStart.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmbMonthStart.FormattingEnabled = true;
            resources.ApplyResources(this.m_cmbMonthStart, "m_cmbMonthStart");
            this.m_cmbMonthStart.Name = "m_cmbMonthStart";
            // 
            // m_lblDSTStop
            // 
            resources.ApplyResources(this.m_lblDSTStop, "m_lblDSTStop");
            this.m_lblDSTStop.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.m_lblDSTStop.Name = "m_lblDSTStop";
            // 
            // m_lblDSTStart
            // 
            resources.ApplyResources(this.m_lblDSTStart, "m_lblDSTStart");
            this.m_lblDSTStart.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.m_lblDSTStart.Name = "m_lblDSTStart";
            // 
            // m_rbFixedDate
            // 
            resources.ApplyResources(this.m_rbFixedDate, "m_rbFixedDate");
            this.m_rbFixedDate.Name = "m_rbFixedDate";
            this.m_rbFixedDate.TabStop = true;
            this.m_rbFixedDate.UseVisualStyleBackColor = true;
            // 
            // m_rbRelativeDate
            // 
            resources.ApplyResources(this.m_rbRelativeDate, "m_rbRelativeDate");
            this.m_rbRelativeDate.Name = "m_rbRelativeDate";
            this.m_rbRelativeDate.TabStop = true;
            this.m_rbRelativeDate.UseVisualStyleBackColor = true;
            // 
            // m_lblInitialTime
            // 
            resources.ApplyResources(this.m_lblInitialTime, "m_lblInitialTime");
            this.m_lblInitialTime.Name = "m_lblInitialTime";
            // 
            // m_dtpTime
            // 
            resources.ApplyResources(this.m_dtpTime, "m_dtpTime");
            this.m_dtpTime.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
            this.m_dtpTime.Name = "m_dtpTime";
            this.m_dtpTime.ShowUpDown = true;
            // 
            // m_btUpdateToSysTime
            // 
            resources.ApplyResources(this.m_btUpdateToSysTime, "m_btUpdateToSysTime");
            this.m_btUpdateToSysTime.BackgroundImage = global::RTC_P4_v1_20.Resource.imgUpdate;
            this.m_btUpdateToSysTime.Name = "m_btUpdateToSysTime";
            this.m_btUpdateToSysTime.UseVisualStyleBackColor = true;
            // 
            // m_btUpdateToSysDate
            // 
            resources.ApplyResources(this.m_btUpdateToSysDate, "m_btUpdateToSysDate");
            this.m_btUpdateToSysDate.BackgroundImage = global::RTC_P4_v1_20.Resource.imgUpdate;
            this.m_btUpdateToSysDate.Name = "m_btUpdateToSysDate";
            this.m_btUpdateToSysDate.UseVisualStyleBackColor = true;
            // 
            // panel1
            // 
            resources.ApplyResources(this.panel1, "panel1");
            this.panel1.Controls.Add(this.m_chbUpdateManualy);
            this.panel1.Controls.Add(this.m_chbAlarm);
            this.panel1.Name = "panel1";
            // 
            // panel2
            // 
            resources.ApplyResources(this.panel2, "panel2");
            this.panel2.Controls.Add(this.m_chbDaylingSavings);
            this.panel2.Controls.Add(this.m_gbDSTSettings);
            this.panel2.Name = "panel2";
            // 
            // tableLayoutPanel1
            // 
            resources.ApplyResources(this.tableLayoutPanel1, "tableLayoutPanel1");
            this.tableLayoutPanel1.Controls.Add(this.m_btUpdateToSysDate, 2, 1);
            this.tableLayoutPanel1.Controls.Add(this.m_dtpDate, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.m_lblInitialDate, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.m_btUpdateToSysTime, 2, 0);
            this.tableLayoutPanel1.Controls.Add(this.m_dtpTime, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.m_lblInitialTime, 0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            // 
            // tableLayoutPanel2
            // 
            resources.ApplyResources(this.tableLayoutPanel2, "tableLayoutPanel2");
            this.tableLayoutPanel2.Controls.Add(this.tableLayoutPanel3, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.panel2, 0, 1);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            // 
            // tableLayoutPanel3
            // 
            resources.ApplyResources(this.tableLayoutPanel3, "tableLayoutPanel3");
            this.tableLayoutPanel3.Controls.Add(this.tableLayoutPanel4, 0, 0);
            this.tableLayoutPanel3.Controls.Add(this.m_gbTimeFormat, 1, 0);
            this.tableLayoutPanel3.Controls.Add(this.m_gbDateFormat, 2, 0);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            // 
            // tableLayoutPanel4
            // 
            resources.ApplyResources(this.tableLayoutPanel4, "tableLayoutPanel4");
            this.tableLayoutPanel4.Controls.Add(this.tableLayoutPanel1, 0, 0);
            this.tableLayoutPanel4.Controls.Add(this.panel1, 0, 1);
            this.tableLayoutPanel4.Name = "tableLayoutPanel4";
            // 
            // CyBasicConfigTab
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tableLayoutPanel2);
            this.Controls.Add(this.m_lblNote);
            this.Name = "CyBasicConfigTab";
            this.m_gbTimeFormat.ResumeLayout(false);
            this.m_gbTimeFormat.PerformLayout();
            this.m_gbDateFormat.ResumeLayout(false);
            this.m_gbDateFormat.PerformLayout();
            this.m_gbDSTSettings.ResumeLayout(false);
            this.m_gbDSTSettings.PerformLayout();
            this.tableLayoutPanel5.ResumeLayout(false);
            this.tableLayoutPanel5.PerformLayout();
            this.flowLayoutPanel2.ResumeLayout(false);
            this.flowLayoutPanel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numDayOfMonthStop)).EndInit();
            this.flowLayoutPanel1.ResumeLayout(false);
            this.flowLayoutPanel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numDayOfMonthStart)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel2.PerformLayout();
            this.tableLayoutPanel3.ResumeLayout(false);
            this.tableLayoutPanel3.PerformLayout();
            this.tableLayoutPanel4.ResumeLayout(false);
            this.tableLayoutPanel4.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DateTimePicker m_dtpDate;
        private System.Windows.Forms.Label m_lblInitialDate;
        private System.Windows.Forms.CheckBox m_chbUpdateManualy;
        private System.Windows.Forms.CheckBox m_chbAlarm;
        private System.Windows.Forms.CheckBox m_chbDaylingSavings;
        private System.Windows.Forms.GroupBox m_gbTimeFormat;
        private System.Windows.Forms.RadioButton m_rb24Hour;
        private System.Windows.Forms.RadioButton m_rb12Hour;
        private System.Windows.Forms.GroupBox m_gbDateFormat;
        private System.Windows.Forms.RadioButton m_rbYYYYMMDD;
        private System.Windows.Forms.RadioButton m_rbDDMMYYYY;
        private System.Windows.Forms.RadioButton m_rbMMDDYYYY;
        private System.Windows.Forms.Label m_lblNote;
        private System.Windows.Forms.GroupBox m_gbDSTSettings;
        private System.Windows.Forms.RadioButton m_rbFixedDate;
        private System.Windows.Forms.RadioButton m_rbRelativeDate;
        private System.Windows.Forms.Label m_lblDSTStart;
        private System.Windows.Forms.Label m_lblDSTStop;
        private System.Windows.Forms.Label m_lblInitialTime;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
        private System.Windows.Forms.ComboBox m_cmbHoursStart;
        private System.Windows.Forms.Label m_lblHrsStart;
        private System.Windows.Forms.NumericUpDown m_numDayOfMonthStart;
        private System.Windows.Forms.ComboBox m_cmbWeekOfMonthStart;
        private System.Windows.Forms.ComboBox m_cmdDayOfWeekStart;
        private System.Windows.Forms.Label m_lblOfStart;
        private System.Windows.Forms.ComboBox m_cmbMonthStart;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel2;
        private System.Windows.Forms.ComboBox m_cmbHoursStop;
        private System.Windows.Forms.Label m_lblHrsStop;
        private System.Windows.Forms.NumericUpDown m_numDayOfMonthStop;
        private System.Windows.Forms.ComboBox m_cmbWeekOfMonthStop;
        private System.Windows.Forms.ComboBox m_cmdDayOfWeekStop;
        private System.Windows.Forms.Label m_lblOfStop;
        private System.Windows.Forms.ComboBox m_cmbMonthStop;
        private System.Windows.Forms.Label m_lblOfStartRelative;
        private System.Windows.Forms.Label m_lblOfStopRelative;
        private System.Windows.Forms.DateTimePicker m_dtpTime;
        private System.Windows.Forms.Button m_btUpdateToSysTime;
        private System.Windows.Forms.Button m_btUpdateToSysDate;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel4;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel5;
    }
}
