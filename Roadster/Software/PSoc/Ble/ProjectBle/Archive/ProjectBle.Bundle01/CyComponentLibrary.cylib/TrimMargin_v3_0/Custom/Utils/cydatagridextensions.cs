/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System.Windows.Forms;
using System.Collections.Generic;

namespace TrimMargin_v3_0
{
    internal static class CyDataGridExtensions
    {
        /// <summary>
        /// Updates control height according to number of its rows.
        /// </summary>
        public static void UpdateHeight(DataGridView dgv)
        {
            if (dgv.Rows.Count > 0)
            {
                int height = 2 + dgv.ColumnHeadersHeight + dgv.Rows[0].Height * dgv.Rows.Count;
                dgv.Height = height;
            }
        }

        /// <summary>
        /// Changes specified cell read-only state.
        /// </summary>
        public static void SetCellReadOnlyState(DataGridView dgv, int row, int col, bool readOnly)
        {
            dgv[col, row].Style = readOnly ? CyParameters.DGDisabledStyle : CyParameters.DGEnabledStyle;
            dgv[col, row].ReadOnly = readOnly;
        }

        /// <summary>
        /// Gets control columns names.
        /// </summary>
        public static List<string> GetColumnNames(DataGridView dgv)
        {
            List<string> colNames = new List<string>();
            for (int i = 0; i < dgv.ColumnCount; i++)
            {
                colNames.Add(dgv.Columns[i].HeaderText);
            }

            colNames.Add("R2_EN");
            colNames.Add("R3_EN");
            colNames.Add("R4_EN");
            colNames.Add("C1_EN");

            colNames.Add("R_Series");
            colNames.Add("C_Series");

            return colNames;
        }

        /// <summary>
        /// Sets sort mode for all columns.
        /// </summary>
        public static void SetColumnSortMode(DataGridView dgv, DataGridViewColumnSortMode mode)
        {
            foreach (DataGridViewColumn item in dgv.Columns)
            {
                item.SortMode = mode;
            }
        }

        /// <summary>
        /// Selects rows with the specified indexes.
        /// </summary>
        /// <param name="selectedRows">List of rows indexes</param>
        public static void SelectRows(DataGridView dgv, List<int> selectedRows)
        {
            if (selectedRows.Count > 0)
            {
                for (int i = 0; i < dgv.SelectedRows.Count; i++)
                {
                    dgv.SelectedRows[i].Selected = false;
                }

                for (int i = 0; i < selectedRows.Count; i++)
                {
                    dgv.Rows[selectedRows[i]].Selected = true;
                }
            }
        }

        /// <summary>
        /// Selects rows between specified indexes.
        /// </summary>
        public static void SelectRows(DataGridView dataGridView, int fromRow, int toRow)
        {
            if (fromRow >= 0 && toRow >= 0)
            {
                dataGridView.CurrentCell = dataGridView.Rows[toRow].Cells[0];
                for (int i = 0; i < dataGridView.Rows.Count; i++)
                {
                    dataGridView.Rows[i].Selected = (i >= fromRow && i <= toRow);
                }
            }
        }

        /// <summary>
        /// Gets enumerator with the selected rows indexes.
        /// </summary>
        public static IEnumerable<int> GetSelectedRowsIndexes(DataGridView dgv)
        {
            for (int i = 0; i < dgv.SelectedRows.Count; i++)
            {
                yield return dgv.SelectedRows[i].Index;
            }
        }
    }
}