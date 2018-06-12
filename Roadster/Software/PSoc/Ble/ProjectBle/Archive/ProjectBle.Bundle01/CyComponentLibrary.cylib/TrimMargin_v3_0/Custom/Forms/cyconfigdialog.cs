/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Drawing;
using System.Diagnostics;
using System.Windows.Forms;
using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using TrimMargin_v3_0.Utils;
using TrimMargin_v3_0.DataStructures;

namespace TrimMargin_v3_0.Forms
{
    internal partial class CyConfigDialog : Form
    {
        #region Constants
        private readonly Color COLOR_EDIT = SystemColors.Window;
        private readonly Color COLOR_HIGHLIGHTING = SystemColors.Info;
        private readonly Color COLOR_READONLY = SystemColors.ControlLight;

        private const int FORM_WIDTH_OFFSET = 45;
        private const int FORM_HEIGHT_OFFSET = 92;
        #endregion Constants

        #region Private fields
        private CyParameters m_parameters;

        /// <summary>
        /// Represents actual voltages table row.
        /// </summary>
        private CyVoltagesTableRow m_voltagesTableRow;

        /// <summary>
        /// Represents actual hardware table row.
        /// </summary>
        private CyHardwareTableRow m_hardwareTableRow;

        /// <summary>
        /// List of editable columns passed from the summary tab.
        /// </summary>
        private List<DataGridViewColumn> m_editableColumns;

        /// <summary>
        /// This is a map between picture box that represents expand/collapse button and table layout panel.
        /// </summary>
        private Dictionary<PictureBox, TableLayoutPanel> m_dicControlTables;

        /// <summary>
        /// This is a map between table field and the control that displays error for the field.
        /// </summary>
        private Dictionary<CyEFields, Control> m_errorControlsMap;

        /// <summary>
        /// This is a map between sanity check type and the control that highlights by yellow in case of error.
        /// </summary>
        private Dictionary<CyESanityCheck, CyConfigGridControls> m_sanityCheckControlsMap;

        /// <summary>
        /// Temporary voltages table row used to not modify the real object, but its copy.
        /// </summary>
        private CyVoltagesTableRow m_tempVoltRow;

        /// <summary>
        /// Temporary hardware table row used to not modify the real object, but its copy.
        /// </summary>
        private CyHardwareTableRow m_tempHwRow;

        /// <summary>
        /// Object that contains all math used in the component.
        /// </summary>
        private CyMath m_math;

        /// <summary>
        /// Name of currently edited converter.
        /// </summary>
        private string m_converterName;
        #endregion

        #region Events
        /// <summary>
        /// Event fired when Apply button is pressed.
        /// </summary>
        public event EventHandler<EventArgs> ApplyButtonClick;
        #endregion

        #region Constructor(s)
        public CyConfigDialog(CyParameters parameters, List<DataGridViewColumn> editableColumns, int converterIndex)
        {
            InitializeComponent();
            this.Text = String.Format(CyConstants.FORM_TEXT_STRF, converterIndex + 1);

            m_parameters = parameters;
            m_math = new CyMath(m_parameters);
            m_editableColumns = editableColumns;

            if (m_parameters.NumConverters > converterIndex)
            {
                m_voltagesTableRow = m_parameters.VoltagesTable[(int)converterIndex];
                m_hardwareTableRow = m_parameters.HardwareTable[(int)converterIndex];
                m_converterName = m_voltagesTableRow.m_converterName;
            }
            else
            {
                m_voltagesTableRow = CyVoltagesTableRow.CreateDefaultRow();
                m_hardwareTableRow = CyHardwareTableRow.CreateDefaultRow();
                m_converterName = String.Format(CyConstants.DEFAULT_CONVERTER_NAME_FMT, converterIndex + 1);
            }

            m_tempVoltRow = new CyVoltagesTableRow(m_voltagesTableRow);
            m_tempHwRow = new CyHardwareTableRow(m_hardwareTableRow);

            
            InitializeComboBoxes();
            InitializeMaps();
            InitializeTables();

            this.Size = new System.Drawing.Size(tlpCalculated.Location.X + tlpCalculated.Width +
                FORM_WIDTH_OFFSET, tlpBasic.Size.Height + buttonCancel.Size.Height + FORM_HEIGHT_OFFSET);

            UpdateUI();
            buttonOk.Select();

            #region Event subscription
            buttHideBasic.MouseDown += buttonsHide_MouseDown;
            buttHideVoltParam.MouseDown += buttonsHide_MouseDown;
            buttHideHardParam.MouseDown += buttonsHide_MouseDown;
            buttHideTrimMergCircParam.MouseDown += buttonsHide_MouseDown;
            buttHideActualValues.MouseDown += buttonsHide_MouseDown;
            buttHideCalculatedIdealValues.MouseDown += buttonsHide_MouseDown;

            comboBoxFeedback.Format += comboBoxFeedback_Format;
            comboBoxResistorsESeries.Format += comboBoxResistorsESeries_Format;
            comboBoxCapacitorESeries.Format += comboBoxResistorsESeries_Format;

            checkBoxEnableR2.CheckedChanged += checkBoxes_CheckedChanged;
            checkBoxEnableR3.CheckedChanged += checkBoxes_CheckedChanged;
            checkBoxEnableR4.CheckedChanged += checkBoxes_CheckedChanged;
            checkBoxEnableC1.CheckedChanged += checkBoxes_CheckedChanged;

            buttonOk.Click += buttonsOkApplyCancel_Click;
            buttonApply.Click += buttonsOkApplyCancel_Click;
            buttonCancel.Click += buttonsOkApplyCancel_Click;

            textBoxConverterName.TextChanged += InputValueChanged;
            numControlSampleTime.TextChanged += InputValueChanged;
            numNominalVoltage.ValueChanged += InputValueChanged;
            numMarginHighPercent.ValueChanged += InputValueChanged;
            numMarginLowPercent.ValueChanged += InputValueChanged;
            numMaxVoltage.ValueChanged += InputValueChanged;
            numMinVoltage.ValueChanged += InputValueChanged;
            numStartupVoltage.ValueChanged += InputValueChanged;
            numMarginHighV.ValueChanged += InputValueChanged;
            numMarginHighV.ValueChanged += InputValueChanged;

            comboBoxFeedback.SelectedIndexChanged += FeedbackChanged;
            comboBoxResistorsESeries.SelectedIndexChanged += InputValueChanged;
            comboBoxCapacitorESeries.SelectedIndexChanged += InputValueChanged;

            numVohOfPwmOutput.ValueChanged += InputValueChanged;
            numNominalVadjOutput.ValueChanged += InputValueChanged;
            numDesiredVoutRipple.ValueChanged += InputValueChanged;

            numR1.ValueChanged += InputValueChanged;
            numR2.ValueChanged += InputValueChanged;
            numR3.ValueChanged += InputValueChanged;
            numR4.ValueChanged += InputValueChanged;
            numC1.ValueChanged += InputValueChanged;
            #endregion Add Event Handlers
        }
        #endregion

        #region Overrides
        protected override void OnLoad(EventArgs e)
        {
            // This makes it so the form cannot be opened in designer unless the machine is set to 120 dpi
            if (this.DesignMode)
            {
                using (Graphics g = this.CreateGraphics())
                {
                    if (g.DpiX != 120 || g.DpiY != 120)
                    {
                        throw new Exception("This form must be developed in 120 dpi.");
                    }
                }
            }
            base.OnLoad(e);
        }
        #endregion

        #region Initialization methods
        private void InitializeTables()
        {
            // Set Control Sample Time visibility
            tlpBasic.SuspendLayout();
            SetTableRowVisibility(tableBasic, tableBasic.GetCellPosition(txbLabelControlSampleTime).Row,
                m_parameters.ControllerMethod == CyEControllerMethod.Integral);
            tlpBasic.ResumeLayout();
            // Set Vadj/Vref label text
            ToggleVadjVrefLabel(m_tempVoltRow.Feedback);

            m_dicControlTables = new Dictionary<PictureBox, TableLayoutPanel>();
            m_dicControlTables.Add(buttHideBasic, tableBasic);
            m_dicControlTables.Add(buttHideVoltParam, tableVoltParam);
            m_dicControlTables.Add(buttHideHardParam, tableHardParam);
            m_dicControlTables.Add(buttHideTrimMergCircParam, tableTrimMergCircParam);
            m_dicControlTables.Add(buttHideCalculatedIdealValues, tableCalculatedIdealValues);
            m_dicControlTables.Add(buttHideActualValues, tableActualValues);

            // Set rows size
            panel1Basic.Size = new Size(txbLabelConverterName.Size.Width + textBoxConverterName.Size.Width,
                txbLabelConverterName.Size.Height);
            panel1VoltageParams.Size = new Size(txbLabelConverterName.Size.Width + textBoxConverterName.Size.Width,
                txbLabelConverterName.Size.Height);
            panel1HardwareParams.Size = new Size(txbLabelConverterName.Size.Width + textBoxConverterName.Size.Width,
                txbLabelConverterName.Size.Height);
            panel1TrimMergCircuitParams.Size = new Size(txbLabelConverterName.Size.Width + textBoxConverterName.Size.Width,
                txbLabelConverterName.Size.Height);
            panelCalculatedIdealValues.Size = new Size(txbLabelR2Calc.Size.Width + panelR2Calc.Size.Width,
                txbLabelConverterName.Size.Height);
            panelActualValues.Size = new Size(txbLabelR2Calc.Size.Width + panelR2Calc.Size.Width,
                txbLabelConverterName.Size.Height);
            panelError.Size = new Size(textBoxR3plusR4Error.Size.Width, txbLabelConverterName.Size.Height);

            // Set tables location
            tlpCalculated.Top = tlpBasic.Height - tlpCalculated.Height + tlpCalculated.Margin.Bottom;

            // Delete arrow buttons in numericUpDowns
            numControlSampleTime.Controls.RemoveAt(0);
            numNominalVoltage.Controls.RemoveAt(0);
            numMarginHighPercent.Controls.RemoveAt(0);
            numMarginHighV.Controls.RemoveAt(0);
            numMarginLowPercent.Controls.RemoveAt(0);
            numMarginLowV.Controls.RemoveAt(0);
            numMaxVoltage.Controls.RemoveAt(0);
            numMinVoltage.Controls.RemoveAt(0);
            numStartupVoltage.Controls.RemoveAt(0);
            numVohOfPwmOutput.Controls.RemoveAt(0);
            numNominalVadjOutput.Controls.RemoveAt(0);
            numDesiredVoutRipple.Controls.RemoveAt(0);
            numR1.Controls.RemoveAt(0);
            numR2.Controls.RemoveAt(0);
            numR3.Controls.RemoveAt(0);
            numR4.Controls.RemoveAt(0);
            numC1.Controls.RemoveAt(0);
            numR2Calc.Controls.RemoveAt(0);
            numR3plusR4Calc.Controls.RemoveAt(0);
            numR3plusR4Actual.Controls.RemoveAt(0);
            numCalcVoutRippleActual.Controls.RemoveAt(0);
            numCalcMaxVoltageActual.Controls.RemoveAt(0);
            numCalcMinVoltageActual.Controls.RemoveAt(0);

            // Add ToolTip text
            toolTip.SetToolTip(txbLabelConverterName, Resources.ToolTipConverterName);
            toolTip.SetToolTip(txbLabelNominalVoltage, Resources.ToolTipNominalVoltage);
            toolTip.SetToolTip(txbLabelControlSampleTime, Resources.ToolTipControlSampleTime);
            toolTip.SetToolTip(txbLabelMarginHighPercent, Resources.ToolTipMarginHighPercent);
            toolTip.SetToolTip(txbLabelMarginHighV, Resources.ToolTipMarginHighV);
            toolTip.SetToolTip(txbLabelMarginLowPercent, Resources.ToolTipMarginLowPercent);
            toolTip.SetToolTip(txbLabelMarginLowV, Resources.ToolTipMarginLowV);
            toolTip.SetToolTip(txbLabelMaxVoltage, Resources.ToolTipMaxVoltage);
            toolTip.SetToolTip(txbLabelMinVoltage, Resources.ToolTipMinVoltage);
            toolTip.SetToolTip(txbLabelStartupVoltage, Resources.ToolTipStartupVoltage);
            toolTip.SetToolTip(txbLabelBoxVohOfPwmOutput, Resources.ToolTipVohOfPwmOutput);
            toolTip.SetToolTip(txbLabelVadjVref, Resources.ToolTipNominalVadjOutput);
            toolTip.SetToolTip(txbLabelDesiredVoutRipple, Resources.ToolTipDesiredVoutRipple);
            toolTip.SetToolTip(txbLabelResistorsESeries, Resources.ToolTipResistorsESeries);
            toolTip.SetToolTip(txbLabelCapacitorESeries, Resources.ToolTipCapacitorESeries);
            toolTip.SetToolTip(txbLabelR1, Resources.ToolTipR1);
            toolTip.SetToolTip(txbLabelR2, Resources.ToolTipR2);
            toolTip.SetToolTip(txbLabelR3, Resources.ToolTipR3);
            toolTip.SetToolTip(txbLabelR4, Resources.ToolTipR4);
            toolTip.SetToolTip(txbLabelC1, Resources.ToolTipC1);
            toolTip.SetToolTip(txbLabelR2Calc, Resources.ToolTipR2Calc);
            toolTip.SetToolTip(txbLabelR3plusR4Calc, Resources.ToolTipR3plusR4Calc);
            toolTip.SetToolTip(txbLabelR3plusR4Actual, Resources.ToolTipR3plusR4Actual);
            toolTip.SetToolTip(txbLabelCalcVoutRippleActual, Resources.ToolTipVoutRippleActual);
            toolTip.SetToolTip(txbLabelCalcMaxVoltageActual, Resources.ToolTipCalcMaxVoltageActual);
            toolTip.SetToolTip(txbLabelCalcMinVoltageActual, Resources.ToolTipMinVoltageActual);
            toolTip.SetToolTip(checkBoxEnableC1, Resources.ToolTipCheckBoxRCEn);
            toolTip.SetToolTip(checkBoxEnableR2, Resources.ToolTipCheckBoxRCEn);
            toolTip.SetToolTip(checkBoxEnableR3, Resources.ToolTipCheckBoxRCEn);
            toolTip.SetToolTip(checkBoxEnableR4, Resources.ToolTipCheckBoxRCEn);
        }

        private void ToggleVadjVrefLabel(CyEFeedback feedback)
        {
            const string FMT = "  {0}";
            switch (feedback)
            {
                case CyEFeedback.Positive:
                    txbLabelVadjVref.Text = String.Format(FMT, Resources.VrefLabel);
                    break;
                case CyEFeedback.Negative:
                    txbLabelVadjVref.Text = String.Format(FMT, Resources.VadjLabel);
                    break;
                default:
                    Debug.Fail("Unhandled feedback type.");
                    break;
            }
        }

        private void InitializeMaps()
        {
            m_errorControlsMap = new Dictionary<CyEFields, Control>()
            {
                { CyEFields.NominalVoltage,    panelErrorNominalVoltage    },
                { CyEFields.MinVoltage,        panelErrorMinVoltage        },
                { CyEFields.MaxVoltage,        panelErrorMaxVoltage        },
                { CyEFields.StartupVoltage,    panelErrorStartupVoltage    },
                { CyEFields.MarginLowPercent,  panelErrorMarginLowPercent  },
                { CyEFields.MarginHighPercent, panelErrorMarginHighPercent },
                { CyEFields.MarginLow,         panelErrorMarginLowV        },
                { CyEFields.MarginHigh,        panelErrorMarginHighV       },
                { CyEFields.ControlSampleTime, panelErrorControlSampleTime },
                { CyEFields.VhPwmOutput,       panelErrorVohOfPwmOutput    },
                { CyEFields.Vadj,              panelErrorNominalVadjOutput },
                { CyEFields.R1,                panelErrorR1                },
                { CyEFields.R2,                panelErrorR2                },
                { CyEFields.R3,                panelErrorR3                },
                { CyEFields.R4,                panelErrorR4                },
                { CyEFields.DesiredVoutRipple, panelErrorDesiredVoutRipple },
                { CyEFields.C1,                panelErrorC1                }
            };

            m_sanityCheckControlsMap = new Dictionary<CyESanityCheck, CyConfigGridControls>()
            {
                { CyESanityCheck.MinMaxVoltageSanity,  new CyConfigGridControls(numMaxVoltage,           panelErrorMinVoltage)           },
                { CyESanityCheck.MinVoltageSanity,     new CyConfigGridControls(numMarginLowV ,          labelErrorCalcMinVoltageActual) },
                { CyESanityCheck.MarginLowVoltage,     new CyConfigGridControls(numNominalVoltage,       panelErrorMarginLowV)           },
                { CyESanityCheck.NominalOutputVoltage, new CyConfigGridControls(numMarginHighV,          panelErrorNominalVoltage)       },
                { CyESanityCheck.MarginHighVoltage,    new CyConfigGridControls(numCalcMaxVoltageActual, panelErrorMarginHighV)          },
                { CyESanityCheck.MinVoltageToVStartup, new CyConfigGridControls(numCalcMinVoltageActual, panelErrorStartupVoltage)       },
                { CyESanityCheck.VStartupToMaxVoltage, new CyConfigGridControls(numCalcMaxVoltageActual, panelErrorStartupVoltage)       }
            };
        }

        private void InitializeComboBoxes()
        {
            comboBoxFeedback.DataSource = Enum.GetValues(typeof(CyEFeedback));
            comboBoxResistorsESeries.DataSource = Enum.GetValues(typeof(CyESeriesType));
            comboBoxCapacitorESeries.DataSource = Enum.GetValues(typeof(CyESeriesType));
        }
        #endregion

        #region UI/Parameters interaction methods
        /// <summary>
        /// Updates all controls with the values from parameters.
        /// </summary>
        private void UpdateUI()
        {
            UpdateUIFromTable();
            ToggleNumericControl(checkBoxEnableR2, numR2, m_hardwareTableRow.m_r2);
            ToggleNumericControl(checkBoxEnableR3, numR3, m_hardwareTableRow.m_r3);
            ToggleNumericControl(checkBoxEnableR4, numR4, m_hardwareTableRow.m_r4);
            ToggleNumericControl(checkBoxEnableC1, numC1, m_hardwareTableRow.m_c1);
            RefreshUI();
            UpdateCircuitPicture(m_tempVoltRow.Feedback);
            ToggleVadjVrefLabel(m_tempVoltRow.Feedback);
        }

        /// <summary>
        /// Refreshes all controls states including calculated values, errors etc.
        /// </summary>
        private void RefreshUI()
        {
            UpdateCalculatedControls();
            UpdateDirtyState();
            ValidateUI();
        }

        /// <summary>
        /// Assigns values from table object to the appropriate controls.
        /// </summary>
        private void UpdateUIFromTable()
        {
            // Voltages table
            textBoxConverterName.Text = m_converterName;
            comboBoxFeedback.SelectedItem = m_voltagesTableRow.Feedback;
            numControlSampleTime.Value = Convert.ToDecimal(m_voltagesTableRow.ControlSampleTime);
            numNominalVoltage.Value = Convert.ToDecimal(m_voltagesTableRow.m_nominalVoltage);
            numMarginHighPercent.Value = Convert.ToDecimal(m_voltagesTableRow.MarginHighPercentage);
            numMarginLowPercent.Value = Convert.ToDecimal(m_voltagesTableRow.MarginLowPercentage);
            numMaxVoltage.Value = Convert.ToDecimal(m_voltagesTableRow.m_maxVoltage);
            numMinVoltage.Value = Convert.ToDecimal(m_voltagesTableRow.m_minVoltage);
            numStartupVoltage.Value = Convert.ToDecimal(m_voltagesTableRow.m_startupVoltage);

            // Hardware table
            numVohOfPwmOutput.Value = Convert.ToDecimal(m_hardwareTableRow.m_vOh);
            numNominalVadjOutput.Value = Convert.ToDecimal(m_hardwareTableRow.m_vAdj);
            numDesiredVoutRipple.Value = Convert.ToDecimal(m_hardwareTableRow.m_maxRipple);
            numR1.Value = Convert.ToDecimal(m_hardwareTableRow.m_r1);
            numR2.Value = Convert.ToDecimal(m_hardwareTableRow.m_r2);
            numR3.Value = Convert.ToDecimal(m_hardwareTableRow.m_r3);
            numR4.Value = Convert.ToDecimal(m_hardwareTableRow.m_r4);
            numC1.Value = Convert.ToDecimal(m_hardwareTableRow.m_c1);
            checkBoxEnableR2.Checked = (m_hardwareTableRow.m_r2En == true);
            checkBoxEnableR3.Checked = (m_hardwareTableRow.m_r3En == true);
            checkBoxEnableR4.Checked = (m_hardwareTableRow.m_r4En == true);
            checkBoxEnableC1.Checked = (m_hardwareTableRow.m_c1En == true);
            comboBoxResistorsESeries.SelectedItem = m_hardwareTableRow.m_resistorESeries;
            comboBoxCapacitorESeries.SelectedItem = m_hardwareTableRow.m_capacitorESeries;
        }

        /// <summary>
        /// Assigns values from the controls to the appropriate table objects.
        /// </summary>
        private void UpdateTablesFromUI(ref CyVoltagesTableRow voltagesRow, ref CyHardwareTableRow hardwareRow)
        {
            // Voltages table
            voltagesRow.m_converterName = textBoxConverterName.Text;
            voltagesRow.Feedback = (CyEFeedback)comboBoxFeedback.SelectedItem;
            voltagesRow.ControlSampleTime = Convert.ToUInt16(numControlSampleTime.Value);
            voltagesRow.m_nominalVoltage = Convert.ToDouble(numNominalVoltage.Value);
            voltagesRow.MarginHighPercentage = Convert.ToDouble(numMarginHighPercent.Value);
            voltagesRow.MarginLowPercentage = Convert.ToDouble(numMarginLowPercent.Value);
            voltagesRow.MarginHigh = CyVoltagesTableRow.MarginPercentageToVoltage(voltagesRow.m_nominalVoltage,
                voltagesRow.MarginHighPercentage);
            voltagesRow.MarginLow = CyVoltagesTableRow.MarginPercentageToVoltage(voltagesRow.m_nominalVoltage,
                voltagesRow.MarginLowPercentage);
            voltagesRow.m_maxVoltage = Convert.ToDouble(numMaxVoltage.Value);
            voltagesRow.m_minVoltage = Convert.ToDouble(numMinVoltage.Value);
            voltagesRow.m_startupVoltage = Convert.ToDouble(numStartupVoltage.Value);

            // Hardware table
            hardwareRow.m_vOh = Convert.ToDouble(numVohOfPwmOutput.Value);
            hardwareRow.m_vAdj = Convert.ToDouble(numNominalVadjOutput.Value);
            hardwareRow.m_maxRipple = Convert.ToDouble(numDesiredVoutRipple.Value);
            hardwareRow.m_r1 = Convert.ToDouble(numR1.Value);
            hardwareRow.m_r2 = Convert.ToDouble(numR2.Value);
            hardwareRow.m_r3 = Convert.ToDouble(numR3.Value);
            hardwareRow.m_r4 = Convert.ToDouble(numR4.Value);
            hardwareRow.m_c1 = Convert.ToDouble(numC1.Value);
            hardwareRow.m_r2En = checkBoxEnableR2.Checked;
            hardwareRow.m_r3En = checkBoxEnableR3.Checked;
            hardwareRow.m_r4En = checkBoxEnableR4.Checked;
            hardwareRow.m_c1En = checkBoxEnableC1.Checked;
            hardwareRow.m_resistorESeries = (CyESeriesType)comboBoxResistorsESeries.SelectedItem;
            hardwareRow.m_capacitorESeries = (CyESeriesType)comboBoxCapacitorESeries.SelectedItem;
        }

        /// <summary>
        /// Assigns values from the controls to parameters.
        /// </summary>
        private void UpdateParamsFromUI()
        {
            UpdateTablesFromUI(ref m_voltagesTableRow, ref m_hardwareTableRow);

            if (m_parameters.HardwareTable.Contains(m_hardwareTableRow) == false)
                m_parameters.HardwareTable.Add(m_hardwareTableRow);
            if (m_parameters.VoltagesTable.Contains(m_voltagesTableRow) == false)
                m_parameters.VoltagesTable.Add(m_voltagesTableRow);

            m_parameters.NumConverters = (byte)m_parameters.HardwareTable.Count;

            m_parameters.SetVoltagesTable();
            m_parameters.SetHardwareTable();
        }

        /// <summary>
        /// Changes numeric control state between user input and calculated.
        /// </summary>
        private void ToggleNumericControl(CheckBox checkbox, NumericUpDown numeric, double? value)
        {
            numeric.ReadOnly = !checkbox.Checked;
            numeric.InterceptArrowKeys = checkbox.Checked;
            numeric.BackColor = checkbox.Checked ? COLOR_EDIT : COLOR_READONLY;

            if (checkbox.Checked)
                numeric.Value = Convert.ToDecimal(value);
        }

        /// <summary>
        /// Updates Apply button availability.
        /// </summary>
        private void UpdateDirtyState()
        {
            bool isDatachanged = false;

            if (!m_parameters.HardwareTable.Contains(m_hardwareTableRow) ||
                !m_parameters.VoltagesTable.Contains(m_voltagesTableRow))
            {
                isDatachanged = true;
            }
            else if (textBoxConverterName.Text != m_voltagesTableRow.m_converterName)
            {
                isDatachanged = true;
            }

            else if (
                (((CyEFeedback)comboBoxFeedback.SelectedItem) != m_voltagesTableRow.Feedback) ||
                !CyHelper.AreEqual(numControlSampleTime.Value, m_voltagesTableRow.ControlSampleTime) ||
                !CyHelper.AreEqual(numNominalVoltage.Value, m_voltagesTableRow.m_nominalVoltage) ||
                !CyHelper.AreEqual(numMarginHighPercent.Value, m_voltagesTableRow.MarginHighPercentage) ||
                !CyHelper.AreEqual(numMarginLowPercent.Value, m_voltagesTableRow.MarginLowPercentage) ||
                !CyHelper.AreEqual(numMaxVoltage.Value, m_voltagesTableRow.m_maxVoltage) ||
                !CyHelper.AreEqual(numMinVoltage.Value, m_voltagesTableRow.m_minVoltage) ||
                !CyHelper.AreEqual(numStartupVoltage.Value, m_voltagesTableRow.m_startupVoltage))
            {
                isDatachanged = true;
            }

            else if (!CyHelper.AreEqual(numVohOfPwmOutput.Value, m_hardwareTableRow.m_vOh) ||
                !CyHelper.AreEqual(numNominalVadjOutput.Value, m_hardwareTableRow.m_vAdj) ||
                !CyHelper.AreEqual(numDesiredVoutRipple.Value, m_hardwareTableRow.m_maxRipple))
            {
                isDatachanged = true;
            }

            else if (!CyHelper.AreEqual(numR1.Value, m_hardwareTableRow.m_r1))
            {
                isDatachanged = true;
            }

            else if ((!CyHelper.AreEqual(numR2.Value, m_hardwareTableRow.m_r2) && checkBoxEnableR2.Checked) ||
                (!CyHelper.AreEqual(numR3.Value, m_hardwareTableRow.m_r3) && checkBoxEnableR3.Checked) ||
                (!CyHelper.AreEqual(numR4.Value, m_hardwareTableRow.m_r4) && checkBoxEnableR4.Checked) ||
                (!CyHelper.AreEqual(numC1.Value, m_hardwareTableRow.m_c1) && checkBoxEnableC1.Checked))
            {
                isDatachanged = true;
            }


            else if (m_hardwareTableRow.m_r2En != checkBoxEnableR2.Checked ||
                m_hardwareTableRow.m_r3En != checkBoxEnableR3.Checked ||
                m_hardwareTableRow.m_r4En != checkBoxEnableR4.Checked ||
                m_hardwareTableRow.m_c1En != checkBoxEnableC1.Checked)
            {
                isDatachanged = true;
            }

            else if (comboBoxResistorsESeries.SelectedIndex != (int)m_hardwareTableRow.m_resistorESeries ||
                comboBoxCapacitorESeries.SelectedIndex != (int)m_hardwareTableRow.m_capacitorESeries)
            {
                isDatachanged = true;
            }

            buttonApply.Enabled = isDatachanged;
        }

        /// <summary>
        /// Recalculates values for calculated controls.
        /// </summary>
        private void UpdateCalculatedControls()
        {
            m_math.CalculateTableValues(m_tempVoltRow, m_tempHwRow);

            //
            // Calculated values
            //

            // Vout ripple
            try
            {
                numCalcVoutRippleActual.Value = Convert.ToDecimal(m_tempHwRow.m_calcVRipple);
            }
            catch (OverflowException)
            {
                Debug.Assert(false);
                numCalcVoutRippleActual.Value = 0;
            }

            // Maximum voltage
            try
            {
                numCalcMaxVoltageActual.Value = Convert.ToDecimal(m_math.GetCalculatedVMax(m_tempVoltRow, m_tempHwRow));
            }
            catch (OverflowException)
            {
                Debug.Assert(false);
                numCalcMaxVoltageActual.Value = 0;
            }

            // Minimum voltage
            try
            {
                numCalcMinVoltageActual.Value = Convert.ToDecimal(m_math.GetCalculatedVMin(m_tempVoltRow, m_tempHwRow));
            }
            catch (OverflowException)
            {
                Debug.Assert(false);
                numCalcMinVoltageActual.Value = 0;
            }

            // Margin high voltage
            try
            {
                numMarginHighV.Value = Convert.ToDecimal(m_tempVoltRow.MarginHigh);
            }
            catch (OverflowException)
            {
                Debug.Assert(false);
                numMarginHighV.Value = 0;
            }

            // Margin low voltage
            try
            {
                numMarginLowV.Value = Convert.ToDecimal(m_tempVoltRow.MarginLow);
            }
            catch (OverflowException)
            {
                Debug.Assert(false);
                numMarginLowV.Value = 0;
            }

            // R2 ideal
            try
            {
                numR2Calc.Value = Convert.ToDecimal(m_tempHwRow.m_calcR2);
            }
            catch (OverflowException)
            {
                Debug.Assert(false);
                numR2Calc.Value = 0;
            }

            // R3 + R4 ideal
            try
            {
                numR3plusR4Calc.Value = Convert.ToDecimal(m_tempHwRow.m_calcR3 + m_tempHwRow.m_calcR4);
            }
            catch (OverflowException)
            {
                Debug.Assert(false);
                numR3plusR4Calc.Value = 0;
            }

            // R3 + R4 actual
            try
            {
                numR3plusR4Actual.Value = Convert.ToDecimal(m_tempHwRow.m_r3 + m_tempHwRow.m_r4);
            }
            catch (OverflowException)
            {
                Debug.Assert(false);
                numR3plusR4Actual.Value = 0;
            }

            //
            // Error column calculations
            //

            // R3 + R4 error column
            textBoxR3plusR4Error.Text = (numR3plusR4Actual.Value - numR3plusR4Calc.Value).ToString("0.###") + " kOhm";

            // Vout ripple error column
            try
            {
                textBoxVoutRippleError.Text = (numCalcVoutRippleActual.Value - Convert.ToDecimal(
                    m_tempHwRow.m_maxRipple)).ToString("0.###") + " mV";
            }
            catch (OverflowException)
            {
                Debug.Assert(false);
                decimal value = 0;
                textBoxVoutRippleError.Text = value.ToString("0.###") + " mV";
            }

            // Maximum voltage error column
            textBoxMaxVoltageError.Text = (numCalcMaxVoltageActual.Value - numMaxVoltage.Value).ToString("0.###") + " V";

            // Minimum voltage error column
            textBoxMinVoltageError.Text = (numCalcMinVoltageActual.Value - numMinVoltage.Value).ToString("0.###") + " V";

            //
            // Calculated values for items with checkbox
            //

            // R2
            if (checkBoxEnableR2.Checked == false)
            {
                try
                {
                    numR2.Value = Convert.ToDecimal(m_tempHwRow.m_calcR2);
                }
                catch (OverflowException)
                {
                    Debug.Assert(false);
                    numR2.Value = 0;
                }
            }

            // R3
            if (checkBoxEnableR3.Checked == false)
            {
                try
                {
                    numR3.Value = Convert.ToDecimal(m_tempHwRow.m_calcR3);
                }
                catch (OverflowException)
                {
                    Debug.Assert(false);
                    numR3.Value = 0;
                }
            }

            // R4
            if (checkBoxEnableR4.Checked == false)
            {
                try
                {
                    numR4.Value = Convert.ToDecimal(m_tempHwRow.m_calcR4);
                }
                catch (OverflowException)
                {
                    Debug.Assert(false);
                    numR4.Value = 0;
                }
            }

            // C1
            if (checkBoxEnableC1.Checked == false)
            {
                try
                {
                    numC1.Value = Convert.ToDecimal(m_tempHwRow.m_calcC1);
                }
                catch (OverflowException)
                {
                    Debug.Assert(false);
                    numC1.Value = 0;
                }
            }
        }

        /// <summary>
        /// Sets visibility for table layout panel row.
        /// </summary>
        private static void SetTableRowVisibility(TableLayoutPanel panel, int rowIndex, bool isVisible)
        {
            panel.GetControlFromPosition(0, rowIndex).Visible = isVisible;
            panel.GetControlFromPosition(1, rowIndex).Visible = isVisible;
        }

        /// <summary>
        /// Sets circuit picture according to specified feedback type.
        /// </summary>
        private void UpdateCircuitPicture(CyEFeedback feedback)
        {
            switch (feedback)
            {
                case CyEFeedback.Positive:
                    pictureBoxCircuit.Image = Resources.imgPositive;
                    break;
                case CyEFeedback.Negative:
                    pictureBoxCircuit.Image = Resources.imgNegative;
                    break;
                default:
                    Debug.Fail("Unhandled feedback type.");
                    break;
            }
        }
        #endregion

        #region Event Handlers
        /// <summary>
        /// Called when Apply button is pressed.
        /// </summary>
        private void OnApplyClick(object sender, EventArgs e)
        {
            EventHandler<EventArgs> handler = ApplyButtonClick;
            if (handler != null)
                handler(sender, e);

        }

        private void checkBoxes_CheckedChanged(object sender, EventArgs e)
        {
            if ((CheckBox)sender == checkBoxEnableR2)
            {
                ToggleNumericControl(checkBoxEnableR2, numR2, m_hardwareTableRow.m_r2);
            }
            else if ((CheckBox)sender == checkBoxEnableR3)
            {
                ToggleNumericControl(checkBoxEnableR3, numR3, m_hardwareTableRow.m_r3);
            }
            else if ((CheckBox)sender == checkBoxEnableR4)
            {
                ToggleNumericControl(checkBoxEnableR4, numR4, m_hardwareTableRow.m_r4);
            }
            else if ((CheckBox)sender == checkBoxEnableC1)
            {
                ToggleNumericControl(checkBoxEnableC1, numC1, m_hardwareTableRow.m_c1);
            }

            RefreshUI();
        }

        private void FeedbackChanged(object sender, EventArgs e)
        {
            InputValueChanged(sender, e);
            UpdateCircuitPicture(m_tempVoltRow.Feedback);
            ToggleVadjVrefLabel(m_tempVoltRow.Feedback);
        }

        private void InputValueChanged(object sender, EventArgs e)
        {
            UpdateTablesFromUI(ref m_tempVoltRow, ref m_tempHwRow);
            RefreshUI();
        }

        private void buttonsHide_MouseDown(object sender, MouseEventArgs e)
        {
            PictureBox pButton = (PictureBox)sender;

            if (e.Button != System.Windows.Forms.MouseButtons.Left || !m_dicControlTables.ContainsKey(pButton))
            {
                return;
            }

            if (m_dicControlTables[pButton].Visible)
            {
                pButton.Image = Resources.plus;
                m_dicControlTables[pButton].Visible = false;
            }
            else
            {
                pButton.Image = Resources.minus;
                m_dicControlTables[pButton].Visible = true;
            }
        }

        private void buttonsOkApplyCancel_Click(object sender, EventArgs e)
        {
            Button button = (Button)sender;

            if (button == buttonOk || button == buttonApply)
            {
                List<CyCustErr> errs = CyTabBase.GetControlErrors(m_errorProvider, this.Controls);
                if (errs.Count > 0)
                {
                    MessageBox.Show(Resources.WrongDataMsg, Resources.WrongDataMsgTitle, MessageBoxButtons.OK,
                        MessageBoxIcon.Stop);
                    return;
                }

                UpdateParamsFromUI();
            }

            if (button == buttonOk || button == buttonCancel)
            {
                this.Close();
            }
            else if (button == buttonApply)
            {
                UpdateDirtyState();
                OnApplyClick(this, EventArgs.Empty);
            }
        }

        private void comboBoxFeedback_Format(object sender, ListControlConvertEventArgs e)
        {
            CyEFeedback item = (CyEFeedback)e.ListItem;
            e.Value = CyEnumExtensions.ToDisplayName(item);
        }

        private void comboBoxResistorsESeries_Format(object sender, ListControlConvertEventArgs e)
        {
            CyESeriesType item = (CyESeriesType)e.ListItem;
            e.Value = CyEnumExtensions.ToDisplayName(item);
        }
        #endregion

        #region Validation
        /// <summary>
        /// Checks tables values for range and dependency errors.
        /// </summary>
        private void ValidateUI()
        {
            ClearSanityCheckErrors();
            if (RangeCheck())
            {
                SanityCheck();
            }
        }

        /// <summary>
        /// Checks tables values for range errors.
        /// </summary>
        /// <returns>Number of errors</returns>
        private bool RangeCheck()
        {
            bool isOk = true;
            CyCustErr voltError = CyCustErr.Ok;
            CyCustErr hwError = CyCustErr.Ok;

            foreach (DataGridViewColumn item in m_editableColumns)
            {
                // If tag is not assigned, the column does not need validation
                if (item.Tag == null)
                    continue;

                CyEFields field = (CyEFields)item.Tag;
                Control control = m_errorControlsMap[field];
                if (control.Visible == false)
                    continue;

                voltError = m_tempVoltRow.ValidateRange(field);
                hwError = m_tempHwRow.ValidateRange(field);

                m_errorProvider.SetError(control, String.Empty);

                if (voltError.IsNotOk)
                {
                    m_errorProvider.SetError(control, voltError.Message);
                    isOk = false;
                }
                else if (hwError.IsNotOk)
                {
                    m_errorProvider.SetError(control, hwError.Message);
                    isOk = false;
                }
            }
            return isOk;
        }

        /// <summary>
        /// Removes error providers and back color highlighting that were set by sanity check operation.
        /// </summary>
        private void ClearSanityCheckErrors()
        {
            foreach (KeyValuePair<CyESanityCheck, CyConfigGridControls> item in m_sanityCheckControlsMap)
            {
                m_errorProvider.SetError(item.Value.ErrorControl, String.Empty);
                Control depControl = item.Value.DependentControl;
                if (depControl.Tag != null)
                {
                    KeyValuePair<CyESanityCheck, Color> pair = (KeyValuePair<CyESanityCheck, Color>)depControl.Tag;
                    if (item.Key == pair.Key)
                    {
                        depControl.BackColor = pair.Value;
                    }
                }
            }
        }

        /// <summary>
        /// Checks tables values for dependency errors. In case of error shows error message near 
        /// the issue control and highlights the dependent control with a yellow color.
        /// </summary>
        private void SanityCheck()
        {
            double? calcMinVoltage = m_math.GetCalculatedVMin(m_tempVoltRow, m_tempHwRow);
            double? calcMaxVoltage = m_math.GetCalculatedVMax(m_tempVoltRow, m_tempHwRow);
            Dictionary<CyESanityCheck, CyCustErr> errors = m_tempVoltRow.SanityCheck(calcMinVoltage, calcMaxVoltage);

            foreach (KeyValuePair<CyESanityCheck, CyCustErr> item in errors)
            {
                CyConfigGridControls controls = m_sanityCheckControlsMap[item.Key];
                if (item.Value.IsNotOk)
                {
                    m_errorProvider.SetError(controls.ErrorControl, item.Value.Message);
                    // Save control original color before the change. Since one control can be assigned to 
                    // different sanity check types, save check type to avoid overwriting its color by another check
                    if (controls.DependentControl.BackColor != COLOR_HIGHLIGHTING)
                    {
                        Color controlColor = controls.DependentControl.BackColor;
                        controls.DependentControl.Tag = new KeyValuePair<CyESanityCheck, Color>(item.Key, controlColor);
                    }
                    controls.DependentControl.BackColor = COLOR_HIGHLIGHTING;
                }
                else
                {
                    m_errorProvider.SetError(controls.ErrorControl, String.Empty);
                    Control depControl = controls.DependentControl;
                    if (depControl.Tag != null)
                    {
                        KeyValuePair<CyESanityCheck, Color> pair = (KeyValuePair<CyESanityCheck, Color>)depControl.Tag;
                        if (item.Key == pair.Key)
                        {
                            depControl.BackColor = pair.Value;
                        }
                    }
                }
            }
        }
        #endregion
    }
}
