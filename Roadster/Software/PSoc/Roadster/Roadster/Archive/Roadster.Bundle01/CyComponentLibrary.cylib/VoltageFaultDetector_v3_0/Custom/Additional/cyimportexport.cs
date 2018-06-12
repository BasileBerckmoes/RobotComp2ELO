/*******************************************************************************
* Copyright 2012 - 2015, Cypress Semiconductor Corporation.  All rights reserved.
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

namespace VoltageFaultDetector_v3_0
{
    public class CyImportExport
    {
        private static char Separator = ',';

        #region Export functions
        public static string Export(List<CyVoltagesTableRow> voltagesTable, List<string> colHeaders, bool clipBoard)
        {
            StringBuilder sb = new StringBuilder();

            string header = "";
            for (int i = 0; i < colHeaders.Count; i++)
            {
                if (!clipBoard &&
                    ((i == CyVoltagesTableRow.UV_FAULT_ACTUAL_THRESHOLD_TABLE_INDEX) ||
                     (i == CyVoltagesTableRow.OV_FAULT_ACTUAL_THRESHOLD_TABLE_INDEX)))
                {
                    continue;
                }
                header += colHeaders[i] + Separator;                
            }
            header = header.TrimEnd(Separator);
            sb.AppendLine(header);

            string line;
            for (int i = 0; i < voltagesTable.Count; i++)
            {
                CyVoltagesTableRow item = voltagesTable[i];
                if (clipBoard)
                {
                   line =
                        CyVoltagesTableRow.GetVoltageIndexStr(i + 1) + Separator +
                        item.VoltageName.ToString() + Separator +
                        CyParameters.NullableDoubleToString(item.NominalVoltage, "f3") + Separator +
                        CyParameters.NullableDoubleToString(item.UvFaultThreshold, "f3") + Separator +
                        CyParameters.NullableDoubleToString(item.UvFaultActualThreshold, "f3") + Separator +
                        CyParameters.NullableDoubleToString(item.OvFaultThreshold, "f3") + Separator +
                        CyParameters.NullableDoubleToString(item.OvFaultActualThreshold, "f3") + Separator +
                        CyParameters.NullableDoubleToString(item.InputScalingFactor, "f3");
                }
                else
                {
                    line =
                       CyVoltagesTableRow.GetVoltageIndexStr(i + 1) + Separator +
                       item.VoltageName.ToString() + Separator +
                       CyParameters.NullableDoubleToString(item.NominalVoltage, "f3") + Separator +
                       CyParameters.NullableDoubleToString(item.UvFaultThreshold, "f3") + Separator +
                       CyParameters.NullableDoubleToString(item.OvFaultThreshold, "f3") + Separator +
                       CyParameters.NullableDoubleToString(item.InputScalingFactor, "f3");
                }
                sb.AppendLine(line);
            }
            return sb.ToString();
        }
        #endregion

        #region Import functions
        public static List<CyVoltagesTableRow> ImportVoltagesTable(int numberOfVoltages, int columnCount,
            string fileContent, bool pasteMode)
        {
            List<CyVoltagesTableRow> importTable = new List<CyVoltagesTableRow>();

            string result = CyImportExport.ValidateTextData(columnCount, fileContent, CyParamRanges.NUM_VOLTAGES_MIN,
                CyParamRanges.NUM_VOLTAGES_MAX, pasteMode);

            if (string.IsNullOrEmpty(result))
            {
                importTable = null;
            }
            else
            {
                string[] rows = result.Split(new char[] { '\n' }, StringSplitOptions.None);
                string[] cells;
                for (int i = 1; i <= numberOfVoltages; i++)
                {
                    CyVoltagesTableRow row = new CyVoltagesTableRow();
                    if (i < rows.Length - 1)
                    {
                        try
                        {
                            if (pasteMode)
                            {
                                cells = rows[i].Split(new char[] { Separator }, StringSplitOptions.None);
                                row.VoltageName = cells[1].Trim().ToString();
                                row.NominalVoltage = CyParameters.ParseNullableDouble(cells[2].Trim());
                                row.UvFaultThreshold = CyParameters.ParseNullableDouble(cells[3].Trim());
                                row.UvFaultActualThreshold = CyParameters.ParseNullableDouble(cells[4].Trim());
                                row.OvFaultThreshold = CyParameters.ParseNullableDouble(cells[5].Trim());
                                row.OvFaultActualThreshold = CyParameters.ParseNullableDouble(cells[6].Trim());
                                row.InputScalingFactor = CyParameters.ParseNullableDouble(cells[7].Trim());
                            }
                            else
                            {
                                cells = rows[i].Split(new char[] { Separator }, StringSplitOptions.None);
                                row.VoltageName = cells[1].Trim().ToString();
                                row.NominalVoltage = CyParameters.ParseNullableDouble(cells[2].Trim());
                                row.UvFaultThreshold = CyParameters.ParseNullableDouble(cells[3].Trim());
                                row.OvFaultThreshold = CyParameters.ParseNullableDouble(cells[4].Trim());
                                row.InputScalingFactor = CyParameters.ParseNullableDouble(cells[5].Trim());
                            }
                        }
                        catch (Exception)
                        {
                            importTable = null;
                            break;
                        }
                    }
                    else
                    {
                        if (pasteMode == false)
                            row = CyVoltagesTableRow.CreateDefaultRow(i);
                        else
                            break;
                    }
                    importTable.Add(row);
                }
            }

            return importTable;
        }
        #endregion

        private static string ValidateTextData(int numberOfColumns, string content, byte rowCountMin, 
            byte rowCountMax, bool pasteMode)
        {
            try
            {
                string[] rows = content.Split(new char[] { '\n' }, StringSplitOptions.None);
                if (rows.Length < rowCountMin || rows.Length > rowCountMax)
                    throw new Exception(Resources.InvalidDataFormat);

                string[] cells;
                for (int i = 0; i < rows.Length - 1; i++)
                {
                    cells = rows[i].Split(new char[] { Separator }, StringSplitOptions.None);

                    if (pasteMode)
                    {
                        if (cells.Length != numberOfColumns)                        
                            throw new Exception(Resources.InvalidDataFormat);
                    }
                    else
                    {
                        if (cells.Length != (numberOfColumns - 2))
                            throw new Exception(Resources.InvalidDataFormat);
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, Resources.MsgWarningTitle, MessageBoxButtons.OK, MessageBoxIcon.Warning);
                content = null;
            }
            return content;
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
            catch
            {
                MessageBox.Show(Resources.FileWriteError, Resources.MsgErrorTitle, MessageBoxButtons.OK,
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
            catch
            {
                MessageBox.Show(Resources.FileReadError, Resources.MsgErrorTitle, MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
            return result;
        }
    }
}
