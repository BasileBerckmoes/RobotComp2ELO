/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Windows.Forms;

namespace RTC_P4_v1_10.Tabs
{
    public partial class CyBasicConfigTab : CyTabControlWrapper
    {
        #region Members
        private int m_daysInMonthStart;
        private int m_daysInMonthStop;
        #endregion

        #region Class Properties
        public override string TabName
        {
            get { return "General"; }
        }
        #endregion

        #region Constructor
        public CyBasicConfigTab(CyParameters param)
            : base(param)
        {
            InitializeComponent();

            m_daysInMonthStart = getNumDaysInMonth(m_cmbMonthStart.SelectedIndex);
            m_daysInMonthStop = getNumDaysInMonth(m_cmbMonthStop.SelectedIndex);

            #region Add event handlers
            m_cmbHoursStart.SelectedIndexChanged += cmb_SelectedIndexChanged;
            m_cmbHoursStop.SelectedIndexChanged += cmb_SelectedIndexChanged;
            m_cmbMonthStart.SelectedIndexChanged += cmb_SelectedIndexChanged;
            m_cmbMonthStop.SelectedIndexChanged += cmb_SelectedIndexChanged;
            m_cmbWeekOfMonthStart.SelectedIndexChanged += cmb_SelectedIndexChanged;
            m_cmbWeekOfMonthStop.SelectedIndexChanged += cmb_SelectedIndexChanged;
            m_cmdDayOfWeekStart.SelectedIndexChanged += cmb_SelectedIndexChanged;
            m_cmdDayOfWeekStop.SelectedIndexChanged += cmb_SelectedIndexChanged;

            m_rb12Hour.CheckedChanged += rb_CheckedChanged;
            m_rb24Hour.CheckedChanged += rb_CheckedChanged;
            m_rbDDMMYYYY.CheckedChanged += rb_CheckedChanged;
            m_rbMMDDYYYY.CheckedChanged += rb_CheckedChanged;
            m_rbYYYYMMDD.CheckedChanged += rb_CheckedChanged;
            m_rbFixedDate.CheckedChanged += rb_CheckedChanged;
            m_rbRelativeDate.CheckedChanged += rb_CheckedChanged;

            m_chbAlarm.CheckedChanged += chb_CheckedChanged;
            m_chbDaylingSavings.CheckedChanged += chb_CheckedChanged;
            m_chbUpdateManualy.CheckedChanged += chb_CheckedChanged;

            m_numDayOfMonthStart.ValueChanged += num_ValueChanghed;
            m_numDayOfMonthStart.KeyUp += num_ValueChanghed;
            m_numDayOfMonthStop.ValueChanged += num_ValueChanghed;
            m_numDayOfMonthStop.KeyUp += num_ValueChanghed;
            
            m_dtpDate.ValueChanged += dtp_ValueChanghed;
            m_dtpTime.ValueChanged += dtp_ValueChanghed;

            m_btUpdateToSysDate.Click += bt_Ckicked;
            m_btUpdateToSysTime.Click += bt_Ckicked;
            #endregion
            
            #region Add ranges for comboboxes
            UpdateHoursItemsRange();

            m_cmbWeekOfMonthStart.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.P_WEEK_OF_MONTH_START));
            m_cmdDayOfWeekStart.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.P_DAY_OF_WEEK_START));
            m_cmbMonthStart.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.P_MONTH_START));

            m_cmbWeekOfMonthStop.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.P_WEEK_OF_MONTH_STOP));
            m_cmdDayOfWeekStop.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.P_DAY_OF_WEEK_STOP));
            m_cmbMonthStop.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.P_MONTH_STOP));
            #endregion


            ToolTip tDateTime = new ToolTip();
            tDateTime.SetToolTip(m_btUpdateToSysTime, Resource.btnUpdateTimeText);
            tDateTime.SetToolTip(m_btUpdateToSysDate, Resource.btnUpdateDateText);

        }
        #endregion
        
        #region Update UI
        public void UpdateUI()
        {
            // CheckBoxes
            m_chbAlarm.Checked = m_params.AlarmFunctionality;
            m_chbDaylingSavings.Checked = m_gbDSTSettings.Enabled = m_params.DaylightSavingsTime;
            m_chbUpdateManualy.Checked = m_params.UpdateManually;
            UpdateCheckboxUpdateManualyState();

            // RadioButtons
            m_rb12Hour.Checked = (m_params.TimeFormat == CyETimeFormat.HOUR_12);
            m_rb24Hour.Checked = (m_params.TimeFormat == CyETimeFormat.HOUR_24);

            m_rbDDMMYYYY.Checked = (m_params.DateFormat == CyEDateFormat.DD_MM_YYYY);
            m_rbMMDDYYYY.Checked = (m_params.DateFormat == CyEDateFormat.MM_DD_YYYY);
            m_rbYYYYMMDD.Checked = (m_params.DateFormat == CyEDateFormat.YYYY_MM_DD);

            m_rbRelativeDate.Checked = (m_params.DateType == CyEDateType.RELATIVE);
            m_rbFixedDate.Checked = (m_params.DateType == CyEDateType.FIXED);

            // ComboBoxes
            m_cmbHoursStart.SelectedIndex = (int)m_params.HoursStart;
            m_cmbWeekOfMonthStart.SelectedIndex = (int)m_params.WeekOfMonthStart-1;
            m_cmdDayOfWeekStart.SelectedIndex = (int)m_params.DayOfWeekStart-1;
            m_cmbMonthStart.SelectedIndex = (int)m_params.MonthStart-1;

            m_cmbHoursStop.SelectedIndex = (int)m_params.HoursStop;
            m_cmbWeekOfMonthStop.SelectedIndex = (int)m_params.WeekOfMonthStop-1;
            m_cmdDayOfWeekStop.SelectedIndex = (int)m_params.DayOfWeekStop-1;
            m_cmbMonthStop.SelectedIndex = (int)m_params.MonthStop-1;

            if (m_params.DayOfMonthStart <= m_numDayOfMonthStart.Maximum)
                m_numDayOfMonthStart.Value = m_params.DayOfMonthStart;
            if (m_params.DayOfMonthStop <= m_numDayOfMonthStop.Maximum)
            m_numDayOfMonthStop.Value = m_params.DayOfMonthStop;

            // DateTimePickers
            string dateString = string.Format("{0} {1} {2}", m_params.InitialDay, m_params.InitialMonth,
                m_params.InitialYear);
            string timeString = string.Format("{0} {1} {2}", m_params.InitialSecond, m_params.InitialMinute,
                m_params.InitialHour);
            
            try
            {
                m_dtpDate.Value = DateTime.ParseExact(dateString, "d M yyyy",
                    System.Globalization.CultureInfo.InvariantCulture);

                m_errorProvider.SetError(m_dtpDate, string.Empty);
            }
            catch (FormatException)
            {
                m_errorProvider.SetError(m_dtpDate, Resource.InitialDateError);
            }

            try
            {
                m_dtpTime.Value = DateTime.ParseExact(timeString, "s m H",
                    System.Globalization.CultureInfo.InvariantCulture);
                
                m_errorProvider.SetError(m_dtpTime, string.Empty);
            }
            catch (FormatException)
            {
                m_errorProvider.SetError(m_dtpTime, Resource.InitialTimeError);
            }

            // Update control dependencies
            UpdateVisibility();
            UpdateDateFormat();
            UpdateTime();
        }

        private void UpdateVisibility()
        {
            if (m_params.DateType == CyEDateType.RELATIVE)
            {
                m_numDayOfMonthStart.Visible = false;
                m_numDayOfMonthStop.Visible = false;

                m_cmbWeekOfMonthStart.Visible = true;
                m_cmbWeekOfMonthStop.Visible = true;
                m_cmdDayOfWeekStart.Visible = true;
                m_cmdDayOfWeekStop.Visible = true;

                m_lblOfStart.Visible = true;
                m_lblOfStartRelative.Visible = false;
                m_lblOfStop.Visible = true;
                m_lblOfStopRelative.Visible = false;
            }
            else if (m_params.DateType == CyEDateType.FIXED)
            {
                m_numDayOfMonthStart.Visible = true;
                m_numDayOfMonthStop.Visible = true;

                m_cmbWeekOfMonthStart.Visible = false;
                m_cmbWeekOfMonthStop.Visible = false;
                m_cmdDayOfWeekStart.Visible = false;
                m_cmdDayOfWeekStop.Visible = false;

                m_lblOfStart.Visible = false;
                m_lblOfStartRelative.Visible = true;
                m_lblOfStop.Visible = false;
                m_lblOfStopRelative.Visible = true;
            }        
        }

        private void UpdateDateFormat()
        {
            if (m_params.DateFormat == CyEDateFormat.DD_MM_YYYY)
                m_dtpDate.CustomFormat = "dd/MM/yyyy";
            else if (m_params.DateFormat == CyEDateFormat.MM_DD_YYYY)
                m_dtpDate.CustomFormat = "MM/dd/yyyy";
            else if (m_params.DateFormat == CyEDateFormat.YYYY_MM_DD)
                m_dtpDate.CustomFormat = "yyyy/MM/dd";
        }

        private void UpdateTime()
        {
            if (m_params.TimeFormat == CyETimeFormat.HOUR_12)
                m_dtpTime.CustomFormat = "hh:mm:ss tt";
            else if (m_params.TimeFormat == CyETimeFormat.HOUR_24)
                m_dtpTime.CustomFormat = "HH:mm:ss";
        }

        private void UpdateHoursItemsRange()
        {
            m_cmbHoursStart.Items.Clear();
            m_cmbHoursStop.Items.Clear();
            
            if (m_params.TimeFormat == CyETimeFormat.HOUR_24)
            {
                m_cmbHoursStart.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.P_HOURS_START));
                m_cmbHoursStop.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.P_HOURS_STOP));
            }
            else if (m_params.TimeFormat == CyETimeFormat.HOUR_12)
            {
                string[] s = new string[] { "12:00 AM", "1:00 AM", "2:00 AM", "3:00 AM", "4:00 AM", "5:00 AM", 
                    "6:00 AM", "7:00 AM", "8:00 AM", "9:00 AM", "10:00 AM", "11:00 AM", "12:00 PM", "1:00 PM", 
                    "2:00 PM", "3:00 PM", "4:00 PM", "5:00 PM", "6:00 PM", "7:00 PM", "8:00 PM", "9:00 PM", "10:00 PM", 
                    "11:00 PM" };

                m_cmbHoursStart.Items.AddRange(s);
                m_cmbHoursStop.Items.AddRange(s);
            }

            m_cmbHoursStart.SelectedIndex = (int)m_params.HoursStart;
            m_cmbHoursStop.SelectedIndex = (int)m_params.HoursStop;
        }

        /// <summary>
        /// m_chbUpdateManualy is not applicable when WCO clock doesn't exist.
        /// This method disables m_chbUpdateManualy or shows a warning if checked.
        /// </summary>
        private void UpdateCheckboxUpdateManualyState()
        {
            m_warningProvider.SetError(m_chbUpdateManualy, String.Empty);
            if (m_params.WcoClockExists == false)
            {
                if (m_params.UpdateManually)
                {
                    // Show error
                    m_warningProvider.SetError(m_chbUpdateManualy, Resource.ErrorRtcUpdateManually);
                }
                else
                {
                    // Disable a checkbox
                    m_chbUpdateManualy.Enabled = false;
                }
            }
        }
        #endregion

        #region Event Handlers
        private void bt_Ckicked(object sender, EventArgs e)
        {
            Button bt = (Button)sender;

            if(bt == m_btUpdateToSysDate)
            {
                m_dtpDate.Value = DateTime.Now;
            }
            else if(bt == m_btUpdateToSysTime)
            {
                m_dtpTime.Value = DateTime.Now;
            }

        }

        private void cmb_SelectedIndexChanged(object sender, EventArgs e)
        {
            ComboBox cmb = (ComboBox)sender;
            
            // DST start
            if(cmb == m_cmbHoursStart)
                m_params.HoursStart = (CyEHours)m_cmbHoursStart.SelectedIndex;
            else if(cmb == m_cmbWeekOfMonthStart)
                m_params.WeekOfMonthStart = (CyEWeekOfMonth)m_cmbWeekOfMonthStart.SelectedIndex+1;
            else if(cmb == m_cmdDayOfWeekStart)
                m_params.DayOfWeekStart = (CyEDayOfWeek)m_cmdDayOfWeekStart.SelectedIndex+1;
            else if(cmb == m_cmbMonthStart)
            {
                m_params.MonthStart = (CyEMonth)m_cmbMonthStart.SelectedIndex+1;
                
                m_daysInMonthStart = getNumDaysInMonth(m_cmbMonthStart.SelectedIndex);
                m_errorProvider.SetError(m_numDayOfMonthStart, GetNumDayOfMonthError(m_numDayOfMonthStart));
            }
                
            // DST stop
            else if(cmb == m_cmbHoursStop)
                m_params.HoursStop = (CyEHours)m_cmbHoursStop.SelectedIndex;
            else if(cmb == m_cmbWeekOfMonthStop)
                m_params.WeekOfMonthStop = (CyEWeekOfMonth)m_cmbWeekOfMonthStop.SelectedIndex+1;
            else if(cmb == m_cmdDayOfWeekStop)
                m_params.DayOfWeekStop = (CyEDayOfWeek)m_cmdDayOfWeekStop.SelectedIndex+1;
            else if (cmb == m_cmbMonthStop)
            {
                m_params.MonthStop = (CyEMonth)m_cmbMonthStop.SelectedIndex+1;

                m_daysInMonthStop = getNumDaysInMonth(m_cmbMonthStop.SelectedIndex);
                m_errorProvider.SetError(m_numDayOfMonthStop, GetNumDayOfMonthError(m_numDayOfMonthStop));
            }
        }

        private void rb_CheckedChanged(object sender, EventArgs e)
        { 
            RadioButton rb = (RadioButton)sender;

            if (rb.Checked == false)
            {
                return;
            }

            // Date format
            if (rb == m_rbMMDDYYYY)
            {
                m_params.DateFormat = CyEDateFormat.MM_DD_YYYY;
                UpdateDateFormat();
            }
            else if (rb == m_rbDDMMYYYY)
            {
                m_params.DateFormat = CyEDateFormat.DD_MM_YYYY;
                UpdateDateFormat();
            }
            else if (rb == m_rbYYYYMMDD)
            {
                m_params.DateFormat = CyEDateFormat.YYYY_MM_DD;
                UpdateDateFormat();
            }

            // Time format
            else if (rb == m_rb12Hour)
            {
                m_params.TimeFormat = CyETimeFormat.HOUR_12;
                UpdateTime();
                UpdateHoursItemsRange();
            }
            else if (rb == m_rb24Hour)
            {
                m_params.TimeFormat = CyETimeFormat.HOUR_24;
                UpdateTime();
                UpdateHoursItemsRange();
            }

            // Date type
            else if (rb == m_rbRelativeDate)
            {
                m_params.DateType = CyEDateType.RELATIVE;
                UpdateVisibility();

                m_errorProvider.SetError(m_numDayOfMonthStart, string.Empty);
                m_errorProvider.SetError(m_numDayOfMonthStop, string.Empty);
            }
            else if (rb == m_rbFixedDate)
            {
                m_params.DateType = CyEDateType.FIXED;
                UpdateVisibility();
                    
                m_errorProvider.SetError(m_numDayOfMonthStart, GetNumDayOfMonthError(m_numDayOfMonthStart));
                m_errorProvider.SetError(m_numDayOfMonthStop, GetNumDayOfMonthError(m_numDayOfMonthStop));
            }

        }

        private void chb_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox chb = (CheckBox)sender;

            if (chb == m_chbAlarm)
            {
                m_params.AlarmFunctionality = chb.Checked;
            }
            else if (chb == m_chbUpdateManualy)
            {
                m_params.UpdateManually = chb.Checked;
                UpdateCheckboxUpdateManualyState();
            }
            else if (chb == m_chbDaylingSavings)
            {
                m_gbDSTSettings.Enabled = m_params.DaylightSavingsTime = chb.Checked;
            }
        }

        private void num_ValueChanghed(object sender, EventArgs e)
        { 
            NumericUpDown num = (NumericUpDown)sender;

            if (num.Value < 32)
            {
                if (num == m_numDayOfMonthStart)
                {
                    m_params.DayOfMonthStart = (byte)num.Value;
                }
                else if (num == m_numDayOfMonthStop)
                {
                    m_params.DayOfMonthStop = (byte)num.Value;
                }
            }

            m_errorProvider.SetError(num, GetNumDayOfMonthError(num));

        }

        private void dtp_ValueChanghed(object sender, EventArgs e)
        {
            DateTimePicker dtp = (DateTimePicker)sender;

            if (dtp == m_dtpDate)
            {
                m_params.InitialDay = (UInt16)m_dtpDate.Value.Day;
                m_params.InitialMonth = (UInt16)m_dtpDate.Value.Month;
                m_params.InitialYear = (UInt16)m_dtpDate.Value.Year;
                
                m_errorProvider.SetError(m_dtpDate, string.Empty);
            }
            else if (dtp == m_dtpTime)
            {
                m_params.InitialSecond = (UInt16)m_dtpTime.Value.Second;
                m_params.InitialMinute = (UInt16)m_dtpTime.Value.Minute;
                m_params.InitialHour = (UInt16)m_dtpTime.Value.Hour;

                m_errorProvider.SetError(m_dtpTime, string.Empty);

                UpdateTime();
            }
        }
        #endregion

        #region Class Functions
        private string GetNumDayOfMonthError(NumericUpDown numeric)
        {
            string err = string.Empty;

            int maxDays = numeric == m_numDayOfMonthStart ? m_daysInMonthStart : m_daysInMonthStop;

            if (numeric.Value > maxDays || numeric.Value == 0 || numeric.Text == String.Empty)
            {
                err = string.Format(Resource.NumericUpDownError, maxDays);
            } 
            
            return err;
        }

        private int getNumDaysInMonth(int monthID)
        {
            int num = 31;

            if (monthID == 1)
            {
                num = 29;
            }
            else
            {
                num = monthID > 6 ? 30 + monthID % 2 : 30 + 1 - monthID % 2;
            }

            return num;
        }

        #endregion

    }
}
