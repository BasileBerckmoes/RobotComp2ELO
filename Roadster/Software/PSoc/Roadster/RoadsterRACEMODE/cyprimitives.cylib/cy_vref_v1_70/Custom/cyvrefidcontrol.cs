/*******************************************************************************
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
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

namespace Cypress.Components.System.cy_vref_v1_70
{
    internal partial class CyVRefIDControl : UserControl, ICyParamEditingControl
    {
        ICyInstEdit_v1 m_edit;

        public CyVRefIDControl(ICyInstEdit_v1 edit, IEnumerable<CyVRef> vRefs, string selectedVRefID)
        {
            InitializeComponent();

            m_edit = edit;
            VRefs = vRefs;
            SelectedVRefId = selectedVRefID;

            m_vRefComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_vRefComboBox.SelectedIndexChanged += new EventHandler(m_vRefComboBox_SelectedIndexChanged);
        }

        private void PerformDispose()
        {
            m_vRefComboBox.SelectedIndexChanged -= m_vRefComboBox_SelectedIndexChanged;
        }

        IEnumerable<CyVRef> VRefs
        {
            get 
            {
                foreach (CyVRef obj in m_vRefComboBox.Items)
                {
                    yield return obj;
                }
            }

            set
            {
                m_vRefComboBox.Items.Clear();
                foreach (CyVRef vRef in value)
                {
                    m_vRefComboBox.Items.Add(vRef);
                }
            }
        }

        string SelectedVRefId
        {
            get 
            { 
                CyVRef vRef = m_vRefComboBox.SelectedItem as CyVRef;
                if (vRef != null)
                {
                    return vRef.ID;
                }
                return string.Empty;
            }

            set 
            {
                bool found = false;
                foreach (CyVRef vRef in VRefs)
                {
                    if (vRef.ID.Equals(value))
                    {
                        m_vRefComboBox.SelectedItem = vRef;
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    m_vRefComboBox.SelectedItem = null;
                }
            }
        }

        CyVRef SelectedVRef
        {
            get
            {
                CyVRef vRef = m_vRefComboBox.SelectedItem as CyVRef;
                return vRef;
            }
        }

        void m_vRefComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            CyVRef vRef = SelectedVRef;
            if(vRef != null)
            {
                CyVRefInfo.SetVRefIDExpr(m_edit, vRef.ID);
                CyVRefInfo.SetVRefNameExpr(m_edit, vRef.Name);
                m_edit.CommitParamExprs();
            }
        }

        public void Update(ICyParamEditor custEditor, CyCompDevParam param)
        {
            string id = CyVRefInfo.GetVRefIDValue(m_edit);
            SelectedVRefId = id;
        }

        #region ICyParamEditingControl Members

        public Control DisplayControl
        {
            get { return this; }
        }

        public IEnumerable<CyCustErr> GetErrors()
        {
            //no errors are displayed in the control. All validation is done by DRCs.
            return new CyCustErr[] { };
        }

        #endregion
    }

    internal class CyVRef
    {
        string m_id;
        string m_name;

        public string ID { get { return m_id; } }
        public string Name { get { return m_name; } }

        public CyVRef(string id, string name)
        {
            m_id = id;
            m_name = name;

            if (m_id == null || m_name == null)
            {
                throw new ArgumentNullException();
            }
        }

        public override string ToString()
        {
            return Name;
        }

        public override bool Equals(object obj)
        {
            CyVRef vRef = obj as CyVRef;
            if (vRef != null)
            {
                return (m_id.Equals(vRef.m_id) && m_name.Equals(vRef.m_name));
            }
            return false;
        }

        public override int GetHashCode()
        {
            return m_id.GetHashCode() ^ m_name.GetHashCode();
        }
    }
}
