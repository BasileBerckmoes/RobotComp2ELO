/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.IO;
using System.Text;
using System.Diagnostics;
using System.Windows.Forms;
using System.Collections.Generic;
using TrimMargin_v3_0.Utils;
using TrimMargin_v3_0.DataStructures;

namespace TrimMargin_v3_0
{
    internal class CyImportExport
    {
        private static char Separator = ',';
        public const string VOLTAGES_POSTFIX = "_voltages";
        public const string HARDWARE_POSTFIX = "_hardware";

        #region Export functions
        public static string Export(List<CyVoltagesTableRow> voltagesTable, List<CyHardwareTableRow> hardwareTable, 
            List<string> colHeaders, CyParameters parameters)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine(GetHeaders(colHeaders));
            CyMath math = new CyMath(parameters);

            for (int i = 0; i < voltagesTable.Count; i++)
            {
                CyVoltagesTableRow itemVoltages = voltagesTable[i];
                CyHardwareTableRow itemHardware = hardwareTable[i];

                StringBuilder sbLine = new StringBuilder();

                sbLine.Append(CyVoltagesTableRow.GetVoltageIndexStr(i + 1)).Append(Separator);
                sbLine.Append(itemVoltages.m_converterName).Append(Separator);
                sbLine.Append(CyHelper.NullableDoubleToString(itemVoltages.m_nominalVoltage)).Append(Separator);
                sbLine.Append(CyHelper.NullableDoubleToString(itemVoltages.m_minVoltage)).Append(Separator);
                sbLine.Append(CyHelper.NullableDoubleToString(math.GetCalculatedVMin(i))).Append(Separator);
                sbLine.Append(CyHelper.NullableDoubleToString(itemVoltages.m_maxVoltage)).Append(Separator);
                sbLine.Append(CyHelper.NullableDoubleToString(math.GetCalculatedVMax(i))).Append(Separator);
                sbLine.Append(CyHelper.NullableDoubleToString(itemVoltages.m_startupVoltage)).Append(Separator);
                sbLine.Append(CyHelper.NullableDoubleToString(itemVoltages.MarginLowPercentage, 0)).Append(Separator);
                sbLine.Append(CyHelper.NullableDoubleToString(itemVoltages.MarginLow, 3)).Append(Separator);
                sbLine.Append(CyHelper.NullableDoubleToString(itemVoltages.MarginHighPercentage, 0)).Append(Separator);
                sbLine.Append(CyHelper.NullableDoubleToString(itemVoltages.MarginHigh, 3)).Append(Separator);
                sbLine.Append(CyHelper.NullableDoubleToString(itemHardware.m_vOh)).Append(Separator);
                sbLine.Append(CyHelper.NullableDoubleToString(itemHardware.m_vAdj)).Append(Separator);
                sbLine.Append(CyHelper.NullableDoubleToString(itemHardware.m_r1)).Append(Separator);
                sbLine.Append(CyHelper.NullableDoubleToString(itemHardware.m_r2)).Append(Separator);
                sbLine.Append(CyHelper.NullableDoubleToString(itemHardware.m_calcR2)).Append(Separator);
                sbLine.Append(CyHelper.NullableDoubleToString(itemHardware.m_r3)).Append(Separator);
                sbLine.Append(CyHelper.NullableDoubleToString(itemHardware.m_calcR3)).Append(Separator);
                sbLine.Append(CyHelper.NullableDoubleToString(itemHardware.m_r4)).Append(Separator);
                sbLine.Append(CyHelper.NullableDoubleToString(itemHardware.m_calcR4)).Append(Separator);
                sbLine.Append(CyHelper.NullableDoubleToString(itemHardware.m_maxRipple)).Append(Separator);
                sbLine.Append(CyHelper.NullableDoubleToString(itemHardware.m_calcVRipple)).Append(Separator);
                sbLine.Append(CyHelper.NullableDoubleToString(itemHardware.m_c1)).Append(Separator);
                sbLine.Append(CyHelper.NullableDoubleToString(itemHardware.m_calcC1)).Append(Separator);
                sbLine.Append(Convert.ToUInt16(itemVoltages.ControlSampleTime)).Append(Separator);
                sbLine.Append(itemVoltages.Feedback).Append(Separator);
                sbLine.Append(itemHardware.m_r2En.ToString()).Append(Separator);
                sbLine.Append(itemHardware.m_r3En.ToString()).Append(Separator);
                sbLine.Append(itemHardware.m_r4En.ToString()).Append(Separator);
                sbLine.Append(itemHardware.m_c1En.ToString()).Append(Separator);
                sbLine.Append(Convert.ToInt32(itemHardware.m_resistorESeries).ToString()).Append(Separator);
                sbLine.Append(Convert.ToInt32(itemHardware.m_capacitorESeries).ToString());
                sb.AppendLine(sbLine.ToString());
            }
            return sb.ToString();
        }

        private static string GetHeaders(List<string> colHeaders)
        {
            StringBuilder header = new StringBuilder();
            for (int i = 0; i < colHeaders.Count; i++)
            {
                header.Append(colHeaders[i]).Append(Separator);
            }

            return header.ToString().TrimEnd(Separator);
        }
        #endregion

        #region Import functions
        public static void ImportTables(out List<CyVoltagesTableRow> importTableVoltages, 
            out List<CyHardwareTableRow> importTableHardware, int numberOfRows, List<string> columnNames,  
            string fileContent)
        {
            importTableVoltages = new List<CyVoltagesTableRow>();
            importTableHardware = new List<CyHardwareTableRow>();

            bool tableOldVersion;
            string result = ValidateTextData(columnNames, fileContent, CyConstants.NUM_CONVERTERS_MIN,
                CyConstants.NUM_CONVERTERS_MAX, out tableOldVersion);

            if (string.IsNullOrEmpty(result))
            {
                return;
            }
            else
            {
                string[] rows = result.Split(new char[] { '\n' }, StringSplitOptions.None);
                string[] cells;

                for (int i = 1; i <= numberOfRows; i++)
                {
                    CyVoltagesTableRow rowVoltages = new CyVoltagesTableRow();
                    CyHardwareTableRow rowHardware = new CyHardwareTableRow();
                    if (i < rows.Length - 1)
                    {
                        try
                        {
                            int inc = 1;
                            cells = rows[i].Split(new char[] { Separator }, StringSplitOptions.None);
                            rowVoltages.m_converterName = cells[inc++].Trim().ToString();
                            rowVoltages.m_nominalVoltage = CyHelper.ParseNullableDouble(cells[inc++].Trim());
                            rowVoltages.m_minVoltage = CyHelper.ParseNullableDouble(cells[inc++].Trim());
                            if (tableOldVersion == false)
                            {
                                ++inc; // Skip Calculated Min voltage
                            }
                            rowVoltages.m_maxVoltage = CyHelper.ParseNullableDouble(cells[inc++].Trim());
                            if (tableOldVersion == false)
                            {
                                ++inc; // Skip Calculated Max voltage
                            }
                            if (tableOldVersion == false)
                            {
                                rowVoltages.m_startupVoltage = CyHelper.ParseNullableDouble(cells[inc++].Trim());
                            }
                            else
                            {
                                rowVoltages.m_startupVoltage = rowVoltages.m_nominalVoltage;
                            }
                            rowVoltages.MarginLowPercentage = CyHelper.ParseNullableDouble(cells[inc++].Trim());
                            inc++; // Skip Calculated Margin low voltage 
                            rowVoltages.MarginHighPercentage = CyHelper.ParseNullableDouble(cells[inc++].Trim());
                            inc++; // Skip Calculated Margin high voltage 

                            rowHardware.m_vOh = CyHelper.ParseNullableDouble(cells[inc++].Trim());
                            rowHardware.m_vAdj = CyHelper.ParseNullableDouble(cells[inc++].Trim());
                            rowHardware.m_r1 = CyHelper.ParseNullableDouble(cells[inc++].Trim());
                            rowHardware.m_r2 = CyHelper.ParseNullableDouble(cells[inc++].Trim());
                            inc++; // Skip Calculated R2
                            rowHardware.m_r3 = CyHelper.ParseNullableDouble(cells[inc++].Trim());
                            inc++; // Skip Calculated R3
                            rowHardware.m_r4 = CyHelper.ParseNullableDouble(cells[inc++].Trim());
                            inc++; // Skip Calculated R4
                            rowHardware.m_maxRipple = CyHelper.ParseNullableDouble(cells[inc++].Trim());
                            inc++; // Skip Calculated Vout ripple
                            rowHardware.m_c1 = CyHelper.ParseNullableDouble(cells[inc++].Trim());
                            inc++; // Skip Calculated C4
                            rowVoltages.ControlSampleTime = CyHelper.ParseNullableUInt16(cells[inc++]);
                            rowVoltages.Feedback = (CyEFeedback)Enum.Parse(typeof(CyEFeedback), cells[inc++]);
                            rowHardware.m_r2En = Convert.ToBoolean(cells[inc++]);
                            rowHardware.m_r3En = Convert.ToBoolean(cells[inc++]);
                            rowHardware.m_r4En = Convert.ToBoolean(cells[inc++]);
                            rowHardware.m_c1En = Convert.ToBoolean(cells[inc++]);

                            rowHardware.m_resistorESeries = (CyESeriesType?)Enum.Parse(typeof(CyESeriesType), cells[inc++]);
                            rowHardware.m_capacitorESeries = (CyESeriesType?)Enum.Parse(typeof(CyESeriesType), cells[inc++]);
                        }
                        catch (Exception ex)
                        {
                            importTableVoltages = null;
                            Debug.Fail(ex.Message);
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                    importTableVoltages.Add(rowVoltages);
                    importTableHardware.Add(rowHardware);
                }
            }
        }
        #endregion

        private static string ValidateTextData(List<string> columnsNames, string content, byte rowCountMin,
            byte rowCountMax, out bool tableOldVersion)
        {
            tableOldVersion = false;
            try
            {
                string[] rows = content.Split(new char[] { '\n' }, StringSplitOptions.None);

                int rowLength = (rows[rows.Length - 1].Trim() == string.Empty) ? rows.Length - 2 : rows.Length - 1;

                if (rowLength < rowCountMin || rowLength > rowCountMax)
                    throw new CyInvalidDataException(Resources.InvalidDataFormat);

                string[] cells;
                for (int i = 0; i < rowLength; i++)
                {
                    cells = rows[i].Split(new char[] { Separator }, StringSplitOptions.None);

                    // Stop if empty line occurs
                    if (cells.Length == 1)
                        break;

                    // Validate columns count
                    if (cells.Length != columnsNames.Count)
                    {
                        if (columnsNames == CyParameters.VoltagesHeader_v3_0)
                        {
                            if (cells.Length == CyParameters.VoltagesHeader_v1_0.Count)
                            {
                                tableOldVersion = true;
                            }
                            else
                            {
                                throw new CyInvalidDataException(Resources.InvalidDataFormat);
                            }
                        }
                        else
                        {
                            throw new CyInvalidDataException(Resources.InvalidDataFormat);
                        }
                    }
                }
            }
            catch (CyInvalidDataException ex)
            {
                MessageBox.Show(ex.Message, Resources.MsgErrorTitle, MessageBoxButtons.OK, MessageBoxIcon.Warning);
                content = null;
            }
            return content;
        }

        public static void SaveToFile(string fileName, string fileContent)
        {
            try
            {
                File.WriteAllText(fileName, fileContent);
            }
            catch
            {
                MessageBox.Show(Resources.FileWriteError, fileName, MessageBoxButtons.OK,
                   MessageBoxIcon.Error);
            }
        }

        public static string GetFileText(string fileName)
        {
            string result = String.Empty;
            try
            {
                result = File.ReadAllText(fileName);
            }
            catch
            {
                MessageBox.Show(Resources.FileReadError, fileName, MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
            return result;
        }

        public static List<StringBuilder> GetTables(string fileContent)
        {
            StringReader data = new StringReader(fileContent);
            List<StringBuilder> listTables = new List<StringBuilder>();
            int pos = 0;
            string line = data.ReadLine();

            while (line != null)
            {
                listTables.Add(new StringBuilder());

                //Remove empty lines
                while (line == string.Empty) line = data.ReadLine();

                int numHeaderColumns = -1;

                //Get One table
                while ((string.IsNullOrEmpty(line) == false) && (line.Trim(CyImportExport.Separator) != string.Empty))
                {
                    //Remove end separators that may appear after modifying file by Excel
                    line = line.TrimEnd(Separator);
                    if (numHeaderColumns < 0)
                    {
                        numHeaderColumns = line.Split(new char[] { Separator }, StringSplitOptions.None).Length;
                    }
                    else
                    {
                        int numLineColumns = line.Split(new char[] { Separator }, StringSplitOptions.None).Length;
                        if (numLineColumns != numHeaderColumns)
                            line = line.PadRight((line.Length + numHeaderColumns - numLineColumns), Separator);
                    }

                    listTables[pos].AppendLine(line);

                    line = data.ReadLine();
                }

                pos++;
                line = data.ReadLine();
            }

            return listTables;
        }
    }

    internal class CyInvalidDataException : Exception
    {
        public CyInvalidDataException(string message)
            : base(message)
        {
        }
    }
}
