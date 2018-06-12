using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace LUT_v1_60
{
    public partial class CyRenameDialog : Form
    {
        public Dictionary<string, string> m_terminalNames = new Dictionary<string, string>();
        private bool m_init = true;

        public CyRenameDialog(Dictionary<string, string> terminalNames)
        {
            InitializeComponent();
            m_terminalNames = terminalNames;
            UpdateDgv();
            m_init = false;
        }

        private void UpdateDgv()
        {
            m_dgv.Rows.Clear();
            foreach (KeyValuePair<string, string> terminal in m_terminalNames)
            {
                m_dgv.Rows.Add(terminal.Key, terminal.Value);
            }
        }

        private void m_dgv_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (m_init || e.RowIndex < 0)
                return;

            if (e.ColumnIndex == m_colNewName.Index)
            {
                object defaultValueObj = m_dgv[m_colDefaultName.Index, e.RowIndex].Value;
                string defaultName = defaultValueObj == null ? "" : defaultValueObj.ToString();
                if (m_terminalNames.ContainsKey(defaultName))
                {
                    object newValueObj = m_dgv[e.ColumnIndex, e.RowIndex].Value;
                    m_terminalNames[defaultName] = newValueObj == null ? String.Empty : newValueObj.ToString();
                }
            }
        }

        #region Overrides
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (keyData == Keys.Escape)
            {
                this.Close();
                return true;
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }
        #endregion
    }
}
