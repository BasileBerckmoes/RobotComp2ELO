/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
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
using System.IO;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace PowerMonitor_P4_v2_0
{
    public class CyImportExport
    {
        private static char separator = ',';

        #region Export functions
        public static string Export(CyParameters prms, List<CyVoltagesTableRow> voltagesTable)
        {
            StringBuilder sb = new StringBuilder();

            string header = "Power Converter Number" + separator + "Converter Name" + separator +
                "Nominal Output Voltage" + separator + "Minimum Acquisition Time" + separator +
                "UV Fault Threshold" + separator + "UV Warning Threshold" + separator +
                "OV Warning Threshold" + separator + "OV Fault Threshold" + separator + "Input Scaling Factor";
            sb.AppendLine(header);

            string line;

            for (int i = 0; i < prms.NumConverters; i++)
            {
                if (i >= voltagesTable.Count) break;

                CyVoltagesTableRow item = voltagesTable[i];
                line =
                    CyVoltagesTableRow.GetConverterNumber(i) + separator +
                    item.m_converterName.ToString() + separator +
                     CyParameters.NullableDoubleToString(item.m_nominalOutputVoltage) + separator +
                     CyParameters.NullableDoubleToString(item.m_minAcqTime_ns) + separator +
                     CyParameters.NullableDoubleToString(item.m_uvFaultTreshold) + separator +
                     CyParameters.NullableDoubleToString(item.m_uvWarningTreshold) + separator +
                     CyParameters.NullableDoubleToString(item.m_ovWarningTreshold) + separator +
                     CyParameters.NullableDoubleToString(item.m_ovFaultTreshold) + separator +
                     CyParameters.NullableDoubleToString(item.m_inputScalingFactor);
                sb.AppendLine(line);
            }
            return sb.ToString();
        }

        #endregion

        #region Import functions
        public static List<CyVoltagesTableRow> ImportVoltagesTable(int numberOfConverters, int columnCount, string fileContent, bool pasteMode)
        {
            List<CyVoltagesTableRow> importTable = new List<CyVoltagesTableRow>();

            string result = CyImportExport.ValidateTextData(columnCount, fileContent, CyParamRanges.NUM_CONVERTERS_MIN,
                CyParamRanges.NUM_CONVERTERS_MAX);

            if (string.IsNullOrEmpty(result)) return null;

            string[] rows = result.Split(new char[] { '\n' }, StringSplitOptions.None);
            int rowLength = (rows[rows.Length - 1].Trim() == string.Empty) ? rows.Length - 1 : rows.Length;

            try
            {
                for (int i = 1; i <= numberOfConverters; i++)
                {
                    CyVoltagesTableRow row = new CyVoltagesTableRow();
                    if (i < rowLength)
                    {
                        string[] cells = rows[i].Split(new char[] { separator }, StringSplitOptions.None);
                        //cells[0] first column with number is ignored
                        row.m_converterName = cells[1].Trim().ToString();
                        row.m_nominalOutputVoltage = CyParameters.ParseNullableDouble(cells[2]);
                        row.m_minAcqTime_ns = CyParameters.ParseNullableDouble(cells[3]);
                        row.m_uvFaultTreshold = CyParameters.ParseNullableDouble(cells[4]);
                        row.m_uvWarningTreshold = CyParameters.ParseNullableDouble(cells[5]);
                        row.m_ovWarningTreshold = CyParameters.ParseNullableDouble(cells[6]);
                        row.m_ovFaultTreshold = CyParameters.ParseNullableDouble(cells[7]);
                        row.m_inputScalingFactor = CyParameters.ParseNullableDouble(cells[8]);

                    }
                    else
                    {
                        if (pasteMode) break;

                        row = new CyVoltagesTableRow();
                    }
                    importTable.Add(row);
                }
            }
            catch (Exception)
            {
                importTable = null;
            }

            return importTable;
        }

       #endregion

        private static string ValidateTextData(int numberOfColumns, string content, byte rowCountMin, byte rowCountMax)
        {
            string[] rows;
            try
            {
                rows = content.Split(new char[] { '\n' }, StringSplitOptions.None);
                int rowsCount = (rows[rows.Length - 1].Trim() == string.Empty) ? rows.Length - 2 : rows.Length - 1;
                if (rowsCount < rowCountMin || rowsCount > rowCountMax)
                    throw new Exception(Resources.InvalidDataFormat);


                string[] cells;
                for (int i = 0; i <= rowsCount; i++)
                {
                    cells = rows[i].Split(new char[] { separator }, StringSplitOptions.None);
                    if (cells.Length != numberOfColumns)
                        throw new Exception(Resources.InvalidDataFormat);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, typeof(CyCustomizer).Namespace, MessageBoxButtons.OK,
                    MessageBoxIcon.Warning);
                content = null;
            }

            return content;
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
                while ((string.IsNullOrEmpty(line) == false) && (line.Trim(separator) != string.Empty))
                {
                    //Remove end separators that may appear after modifying file by Excel
                    line = line.TrimEnd(separator);
                    if (numHeaderColumns < 0)
                    {
                        numHeaderColumns = line.Split(new char[] { separator }, StringSplitOptions.None).Length;
                    }
                    else
                    {
                        int numLineColumns = line.Split(new char[] { separator }, StringSplitOptions.None).Length;
                        if (numLineColumns != numHeaderColumns)
                            line = line.PadRight((line.Length + numHeaderColumns - numLineColumns), separator);
                    }

                    listTables[pos].AppendLine(line);

                    line = data.ReadLine();
                }

                pos++;
                line = data.ReadLine();
            }

            return listTables;
        }

        public static void SaveToFile(string fileName, string fileContent)
        {
            try
            {
                using (StreamWriter writer = new StreamWriter(fileName))
                {
                    writer.Write(fileContent);
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message, typeof(CyCustomizer).Namespace, MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
        }

        public static string GetFileText(string fileName)
        {
            string result = string.Empty;

            try
            {
                using (FileStream fileStream = new FileStream(fileName, FileMode.Open, FileAccess.Read,
                    FileShare.ReadWrite))
                using (StreamReader sr = new StreamReader(fileStream))
                {
                    result = sr.ReadToEnd();
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message, typeof(CyCustomizer).Namespace, MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }

            return result;
        }
    }
}
