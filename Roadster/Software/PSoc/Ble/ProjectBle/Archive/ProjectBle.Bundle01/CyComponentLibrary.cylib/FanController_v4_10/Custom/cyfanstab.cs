/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;


namespace FanController_v4_10
{
    public partial class CyFansTab : CyEditingWrapperControl
    {
        private List<System.Windows.Forms.NumericUpDown> m_nudMinRPMArray;
        private List<System.Windows.Forms.NumericUpDown> m_nudMaxRPMArray;
        private List<System.Windows.Forms.NumericUpDown> m_nudMinDutyArray;
        private List<System.Windows.Forms.NumericUpDown> m_nudMaxDutyArray;
        private List<System.Windows.Forms.Label> m_lblFanRowLabels;
        private List<System.Windows.Forms.NumericUpDown> m_nudInitialRPMArray;
        // Contains all numericUpowns listed above
        private List<List<System.Windows.Forms.NumericUpDown>> m_nudsArray;

        /// <summary>
        /// TabName property of parameters in symbol that are edited on this tab
        /// </summary>
        public override string TabName
        {
            get { return "Fans"; }
        }

        public CyFansTab(CyParameters param)
            : base(param)
        {
            InitializeComponent();

            GenerateNuds(m_pnlMinRPM, ref m_nudMinRPMArray);
            GenerateNuds(m_pnlMaxRPM, ref m_nudMaxRPMArray);
            GenerateNuds(m_pnlMinDuty, ref m_nudMinDutyArray);
            GenerateNuds(m_pnlMaxDuty, ref m_nudMaxDutyArray);
            GenerateNuds(m_pnlInitialRPM, ref m_nudInitialRPMArray);

            m_nudsArray = new List<List<System.Windows.Forms.NumericUpDown>>();

            m_nudsArray.Add(m_nudMinRPMArray);
            m_nudsArray.Add(m_nudMaxRPMArray);
            m_nudsArray.Add(m_nudMinDutyArray);
            m_nudsArray.Add(m_nudMaxDutyArray);
            m_nudsArray.Add(m_nudInitialRPMArray);

            GenerateFanRowLabels();

            CyAuxFunctions.FillComboByEnum(m_cbPWMFreq, typeof(CyPWMFreqType));
            CyAuxFunctions.FillComboByEnum(m_cbPWMRes, typeof(CyPWMResType));

            UpdateFormFromParams();

            m_nudNumFans.TextChanged += new EventHandler(m_nudNumFans_TextChanged);
            m_nudNumFans.Validating += new CancelEventHandler(m_nudNumFans_Validating);
        }

        #region Form Initialization

        /// <summary>
        /// Initializes numericUpDown controls for the table
        /// </summary>
        /// <param name="baseCnt"></param>
        /// <param name="array"></param>
        private void GenerateNuds(Panel baseCnt, ref List<NumericUpDown> array)
        {
            array = new List<System.Windows.Forms.NumericUpDown>();
            int yPos = CyParamConst.YPOS_NUD;
            
            int editColIndex;
            for (int ii = 0; ii < CyParamConst.MAX_FANS; ii++)
            {
                System.Windows.Forms.NumericUpDown nud = new System.Windows.Forms.NumericUpDown();
                array.Add(nud);
                nud.Tag = ii;
                nud.Width = m_pnlNumCol.Width * 2 / 3;
                nud.Minimum = 0;
                nud.Maximum = decimal.MaxValue;
                nud.Left = baseCnt.Left + (baseCnt.Width - nud.Width) / 2;
                nud.Top = baseCnt.Top + yPos;
                nud.TextChanged += new System.EventHandler(m_nud_TextChanged);
                nud.Validating += new CancelEventHandler(m_nud_Validating);
                this.Controls.Add(nud);
                nud.BringToFront();
                yPos += CyParamConst.VSPC_DEF;

                // Set TabIndex
                const int START_TAB_INDEX = 20;
                const int EDITABLE_COL_COUNT = 5;
                if (baseCnt == m_pnlMinDuty)
                    editColIndex = 0;
                else if (baseCnt == m_pnlMinRPM)
                    editColIndex = 1;
                else if (baseCnt == m_pnlMaxDuty)
                    editColIndex = 2;
                else if (baseCnt == m_pnlMaxRPM)
                    editColIndex = 3;
                else 
                    editColIndex = 4;
                nud.TabIndex = START_TAB_INDEX + ii * EDITABLE_COL_COUNT + editColIndex;
            }
        }

        /// <summary>
        /// Initializes label controls for the table
        /// </summary>
        private void GenerateFanRowLabels()
        {
            m_lblFanRowLabels = new List<System.Windows.Forms.Label>();
            int yPos = CyParamConst.YPOS_FAN_NUM_LBL;

            for (int ii = 0; ii < CyParamConst.MAX_FANS; ii++)
            {
                System.Windows.Forms.Label lbl = new System.Windows.Forms.Label();
                m_lblFanRowLabels.Add(lbl);
                lbl.Text = (ii + 1).ToString();
                lbl.Left = 0;
                lbl.AutoSize = false;
                lbl.Width = m_pnlNumCol.Width;
                lbl.TextAlign = ContentAlignment.TopCenter;
                lbl.Top = yPos;
                m_pnlNumCol.Controls.Add(lbl);
                yPos += CyParamConst.VSPC_DEF;
            }
        }
        #endregion

        #region Form Updating Routines
        public void UpdateFormFromParams()
        {
            if (m_prms == null) return;

            for (int ii = 0; ii < CyParamConst.MAX_FANS; ii++)
            {
                m_nudMaxRPMArray[ii].Value = m_prms.GetMaxRPM(ii);
                m_nudMinRPMArray[ii].Value = m_prms.GetMinRPM(ii);
                m_nudMaxDutyArray[ii].Value = m_prms.GetMaxDuty(ii);
                m_nudMinDutyArray[ii].Value = m_prms.GetMinDuty(ii);
                m_nudInitialRPMArray[ii].Value = m_prms.GetInitialRPM(ii);
            }

            m_nudNumFans.Maximum = decimal.MaxValue;
            m_nudNumFans.Value = m_prms.NumberOfFans;

            UpdateBankList();             

            m_cbBankSelect.SelectedItem = m_prms.NumberOfBanks.ToString();

            CyAuxFunctions.SetComboValue(m_cbPWMFreq, m_prms.FanPWMFreq);
            CyAuxFunctions.SetComboValue(m_cbPWMRes, m_prms.FanPWMRes);

            UpdatePWMFrequency();
            ValidateNudNumFans();

            DisplayActiveFans();

            m_rbFourPole.Checked = m_prms.MotorType == CyMotorType.FOUR_POLE;
            m_rbSixPole.Checked = m_prms.MotorType == CyMotorType.SIX_POLE;
        }

        public void UpdateBasicTabRelatedFields()
        {
            // If the switch is automatic mode, we need to disable fan banking
            if (m_prms.BankAvailable == false)
            {
                UpdateBankList();  // This will refresh the list of bank options and select 0 banks
                m_prms.NumberOfBanks = 0;
            }

            // This function will update the fan count limit, which is different for
            // open and closed loop mode
            UpdatePWMFrequency();

            // The refresh function will handle displaying/hiding the bank select box
            DisplayActiveFans();

            ValidateNudNumFans();
        }

        /// <summary>
        /// Updates the number of rows in the table and bank related controls
        /// </summary>
        private void DisplayActiveFans()
        {
            byte fanCount = m_prms.BankMode ? m_prms.NumberOfBanks : m_prms.NumberOfFans;

            m_lblBankDesc.Visible = m_prms.BankMode;
            m_lblColBankNumber.Text = m_prms.BankMode ? Resources.TxtBankNumber : Resources.TxtFanNumber;

            if (m_prms.BankMode)
                m_lblBankDesc.Text = string.Format(Resources.TxtFanBank, m_prms.NumberOfFans / m_prms.NumberOfBanks);
            // In the Bank mode NumberOfBanks always > 0

            m_lblNumBanksCombo.Enabled = m_prms.BankAvailable;
            m_cbBankSelect.Enabled = m_prms.BankAvailable;

            for (int fan_index = 0; fan_index < CyParamConst.MAX_FANS; fan_index++)
            {
                bool c_visible = fan_index < fanCount;
                for (int nud_index = 0; nud_index < m_nudsArray.Count; nud_index++)
                {
                    m_nudsArray[nud_index][fan_index].Visible = c_visible;
                    // Disable the control in order to say GetErrors() function that this control should not
                    // be checked for errors
                    m_nudsArray[nud_index][fan_index].Enabled = c_visible;
                }
                m_lblFanRowLabels[fan_index].Visible = c_visible;
            }

            // Resize the panels to the correct size -- size of each row member plus a
            // little padding at the end
            int pnlHeight = fanCount * CyParamConst.VSPC_DEF + CyParamConst.YPOS_NUD;

            m_pnlNumCol.Height = pnlHeight;
            m_pnlMinRPM.Height = pnlHeight;
            m_pnlMaxRPM.Height = pnlHeight;
            m_pnlMinDuty.Height = pnlHeight;
            m_pnlMaxDuty.Height = pnlHeight;
            m_pnlInitialRPM.Height = pnlHeight;
        }

        /// <summary>
        /// This function figures out which bankcounts are valid based on the number of fans.
        /// A system requirement is that there be an equal number of fans in each bank. This
        /// function populates the cbBankSelect combo box.  Upon exit, the selected index
        /// will be 0, the selection for 0 banks (which is always a member of the list).
        /// </summary>
        private void UpdateBankList()
        {
            m_cbBankSelect.Items.Clear();

            m_cbBankSelect.Items.Add("0");

            // Banking is only valid for 2 or more fans
            if (m_prms.NumberOfFans >= 2)
            {
                for (int counti = 1; counti < m_prms.NumberOfFans; counti++)
                {
                    if ((m_prms.NumberOfFans % counti) == 0)
                    {
                        m_cbBankSelect.Items.Add(counti.ToString());
                    }
                }
            }
            m_cbBankSelect.SelectedIndex = 0;
        }
        #endregion

        #region Event handlers
        private void m_nudNumFans_TextChanged(object sender, EventArgs e)
        {
            CancelEventArgs ce = new CancelEventArgs();
            bool valid = ValidateNudNumFans();
            if (valid)
            {
                m_prms.NumberOfFans = Convert.ToByte(m_nudNumFans.Value);

                // Whenever the user changes the fan count, reset the bank count to
                // zero. Changing the fan count will always change the fan banking options
                // if only temporarily as the user incs/decs the fan count. The only reasonable
                // thing to do is to reset the bank count and have the user re-select it once
                // the fan count has been updated.
                UpdateBankList();  // this will refresh the list of bank options and select 0 banks

                m_prms.NumberOfBanks = 0;

                DisplayActiveFans();
            }
        }
               
        private void m_nudNumFans_Validating(object sender, CancelEventArgs e)
        {
            ValidateNudNumFans();
        }

        /// <summary>
        /// This event handler is assigned to the numericUpDown controls located inside the fans table
        /// </summary>
        private void m_nud_TextChanged(object sender, EventArgs e)
        {
            CancelEventArgs ce = new CancelEventArgs();
            m_nud_Validating(sender, ce);

            NumericUpDown nud = (NumericUpDown)sender;
            ushort value;
            bool valid = UInt16.TryParse(nud.Value.ToString(), out value);
            if (valid)
            {
                int index = Convert.ToInt32(nud.Tag);

                if (m_nudMaxDutyArray.Contains(nud))
                    m_prms.SetMaxDuty(index, value);
                else if (m_nudMinDutyArray.Contains(nud))
                    m_prms.SetMinDuty(index, value);
                else if (m_nudMaxRPMArray.Contains(nud))
                    m_prms.SetMaxRPM(index, value);
                else if (m_nudMinRPMArray.Contains(nud))
                    m_prms.SetMinRPM(index, value);
                else if (m_nudInitialRPMArray.Contains(nud))
                    m_prms.SetInitialRPM(index, value);
            }
        }

        bool m_lockRow = false;
        /// <summary>
        /// This event handler is assigned to the numericUpDown controls located inside the fans table
        /// </summary>
        private void m_nud_Validating(object sender, CancelEventArgs e)
        {
            bool error = false;
            bool invalid = false;
            string message = "";

            NumericUpDown nud = sender as NumericUpDown;

            int min = 0;
            int max = 0;
            if (m_nudMinDutyArray.Contains(nud) || m_nudMaxDutyArray.Contains(nud))
            {
                min = CyParamConst.MIN_DUTY_NUD;
                max = CyParamConst.MAX_DUTY_NUD;
            }
            else if (m_nudMinRPMArray.Contains(nud) || m_nudMaxRPMArray.Contains(nud))
            {
                min = CyParamConst.MIN_RPM_NUD;
                max = CyParamConst.MAX_RPM_NUD;
            }
            else if (m_nudInitialRPMArray.Contains(nud))
            {
                min = CyParamConst.MIN_RPM_NUD;
                max = CyParamConst.MAX_RPM_NUD;
            }

            ushort val = CyAuxFunctions.GetNumUpDownTextValue<ushort>(sender, out error, ref message);
            int fanIndex = (int)nud.Tag;

            // Validate all row because some values are related to each other. Use lock to avoid looping
            if (m_lockRow == false)
            {
                CancelEventArgs ee = new CancelEventArgs();
                m_lockRow = true;

                for (int i = 0; i < m_nudsArray.Count; i++)
                {
                    m_nud_Validating(m_nudsArray[i][fanIndex], ee);
                }

                m_lockRow = false;
            }

            // Check if value is out of range
            if (m_nudMaxDutyArray.Contains(nud))
            {
                if (val <= m_nudMinDutyArray[fanIndex].Value)
                {
                    message = Resources.ErrorDutyMaxLimit;
                    invalid = true;
                }
            }
            else if (m_nudMinRPMArray.Contains(nud))
            {
                if (val >= m_nudMaxRPMArray[fanIndex].Value)
                {
                    message = Resources.ErrorRPMMinLimit;
                    invalid = true;
                }
            }
            else if (m_nudMaxRPMArray.Contains(nud))
            {
                if (val <= m_nudMinRPMArray[fanIndex].Value)
                {
                    message = Resources.ErrorRPMMaxLimit;
                    invalid = true;
                }
            }
            else if (m_nudMinDutyArray.Contains(nud))
            {
                if (val >= m_nudMaxDutyArray[fanIndex].Value)
                {
                    message = Resources.ErrorDutyMinLimit;
                    invalid = true;
                }
            }

            if (val < min || val > max)
            {
                message = string.Format(Resources.ErrorValueLimit, min, max);
                invalid = true;
            }

            if ((error) || (invalid))
            {
                m_errorProvider.SetError(nud, string.Format(message));
            }
            else
            {
                m_errorProvider.SetError(nud, string.Empty);
            }
        }

        private void m_cbPWMFreq_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_prms.FanPWMFreq = CyAuxFunctions.GetEnum<CyPWMFreqType>(m_cbPWMFreq.Text);
        }

        private void m_cbPWMRes_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_prms.FanPWMRes = CyAuxFunctions.GetEnum<CyPWMResType>(m_cbPWMRes.Text);
            UpdatePWMFrequency();
            ValidateNudNumFans();

            if (m_prms.m_pidTab != null)
            {
                m_prms.m_pidTab.ValidateAttenuation();
            }
        }

        private void m_cbBankSelect_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_prms.NumberOfBanks = Convert.ToByte(m_cbBankSelect.Text);
            DisplayActiveFans();
            ValidateNudNumFans();
        }

        private void m_rbFourPole_CheckedChanged(object sender, EventArgs e)
        {
            if (m_rbFourPole.Checked)
                m_prms.MotorType = CyMotorType.FOUR_POLE;
            else if (m_rbSixPole.Checked)
                m_prms.MotorType = CyMotorType.SIX_POLE;
        }
        #endregion

        #region Private functions
        /// <summary>
        /// Validates text entered in the nudNumFans numericUpDown. In case of wrong input format or value 
        /// out of range, an error provider is displayed.
        /// </summary>
        /// <returns>Returns true if value could be committed to symbol.</returns>
        private bool ValidateNudNumFans()
        {
            bool wrongFormat = false;
            string message = "";
            bool outOfRange = false;

            byte val = CyAuxFunctions.GetNumUpDownTextValue<byte>(m_nudNumFans, out wrongFormat, ref message);

            // Check range
            if (wrongFormat == false)
            {
                if (val == 0)
                {
                    message = Resources.MsgMinFanLoop;
                    outOfRange = true;
                }

                if (m_prms.GetFanMode() == CyFanModeDisplayType.AUTO_HARDWARE)
                {                   
                    if ((m_prms.FanPWMRes == CyPWMResType.EIGHT_BIT) && (val > CyParamConst.MAX_FANS_CLOSED_8B))
                    {
                        message = String.Format(Resources.MsgMaxFan8bClosedLoop, CyParamConst.MAX_FANS_CLOSED_8B);
                        outOfRange = true;
                    }
                    else if ((m_prms.FanPWMRes == CyPWMResType.TEN_BIT) && (val > CyParamConst.MAX_FANS_CLOSED_10B))
                    {
                        message = String.Format(Resources.MsgMaxFan10bClosedLoop, CyParamConst.MAX_FANS_CLOSED_10B);
                        outOfRange = true;
                    }
                }
                else
                {
                    if (val > CyParamConst.MAX_FANS)
                    {
                        message = String.Format(Resources.MsgMaxFanLoop, CyParamConst.MAX_FANS);
                        outOfRange = true;
                    }
                }
                if (m_prms.IsPSoC4)
                {
                    // The maximum number of PWM (fans or banks number) for PSoC4 is 4
                    if ((m_prms.BankMode == false) && (val > CyParamConst.MAX_PWM_PSOC4))
                    {
                        message = Resources.ErrorFanBanksPSoC4;
                        outOfRange = true;
                    }
                    // The maximum number of fans for PSoC4 is 8
                    else if (val > CyParamConst.MAX_FAN_PSOC4)
                    {
                        message = Resources.ErrorFanPSoC4;
                        outOfRange = true;
                    }
                }
            }
            if (wrongFormat || outOfRange)
            {
                m_errorProvider.SetError(m_nudNumFans, string.Format(message));
            }
            else
            {
                m_errorProvider.SetError(m_nudNumFans, string.Empty);
            }

            // Value could be committed to symbol if the format is correct and it doesn't exceed the maximum 
            // possible MAX_FANS value
            bool isValid = (wrongFormat == false) && (val <= CyParamConst.MAX_FANS);
            return isValid;
        }

        /// <summary>
        /// Disables some of PWM frequency options depending on other settings
        /// </summary>
        private void UpdatePWMFrequency()
        {
            if (m_prms.ExternalClock)
            {
                m_cbPWMFreq.Enabled = false;
            }
            else if (m_prms.FanPWMRes == CyPWMResType.TEN_BIT)
            {
                m_cbPWMFreq.SelectedIndex = 0;
                m_cbPWMFreq.Enabled = false;
            }
            else if (m_prms.FanPWMRes == CyPWMResType.EIGHT_BIT)
            {
                m_cbPWMFreq.Enabled = true;
            }
        }
        #endregion
    }
}
