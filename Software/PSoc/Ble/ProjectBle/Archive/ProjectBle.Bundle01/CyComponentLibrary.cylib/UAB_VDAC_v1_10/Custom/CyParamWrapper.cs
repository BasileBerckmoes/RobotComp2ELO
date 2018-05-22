using System;
using System.Collections.Generic;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
namespace UAB_VDAC_v1_10
{
/*
* Example usage:
* 
* //Note: Do not creat CyParamWrapper<float> objects, since Symbol-Paramter
* //floats are actually  doubles internally.  Therefore, use
* //CyParamWrapper<double> to interface with float Symbol-Parameters.
* 
* #region Declare enums
* // enum matches Symbol-type, also called CyEEmployees, also has constants DAND, JAPR, etc
* public enum CyEEmployees {DAND = 0, JAPR = 1, SRR = 2, NWK = 3, SEY = 4}
* #endregion Declare enums
* 
* public partial class CyParamNames
* {
*      public const string NUM_WORKERS = "NumberOfWorkers"; //Name of symbol-parameter containing how many workers on job
*      public const string TEAM_LEAD = "TeamLeader"; //Name of symbol-parameter containing employee who is team lead
* }
* public partial class CyParameters
* {
*      public CyCustomTab m_custTab;
*      public CyParamWrapper<int> m_numWorkers;
*      public CyEnumWrapper<CyEEmployees> m_teamLeader;
*      public CyParameters(ICyInstQuery_v1 instQuery, ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery)
    {
*          m_numWorkers = new CyParamWrapper<int>(instEdit, CyParamNames.NUM_WORKERS);
*          m_teamLeader = new CyEnumWrapper<CyEEmployees>(instEdit, CyParamNames.TEAM_LEAD);
*      }
* }
* public class CyCustomTab
* {
*      CyCustomTab()
*      {
*          SetComboboxStates();
*          UpdateUI;
*      }
*      
*      //Add items to combobox from Symbol parameter
*      public void SetComboboxStates()
*      {
*          m_cmbTeamLeader.Items.Clear();
*          m_cmbTeamLeader.Items.AddRange(m_params.m_TeamLeader.EnumDescriptionList);
*      }
*      
*      //One method that handles all numeric-up-down change events
*      public void nud_ValueChanged(object sender, EventArgs e)
*      {
*          if (sender == m_nudNumberOfEmployees )
*          {
*              //Set the number of workers (int) parameter
*              m_params.m_numWorkers.Value = m_nudNumberOfEmployees.Value;
*          }
*          else{}
*          UpdateUI();
*      }
*      
*      //One method that handles all combobox change events
*      public void cmb_SelectedIndexChanged(object sender, EventArgs e)
*      {
*          if (sender == m_cmbTeamLeader )
*          {
*              //Set the team leader (enum) parameter
*              m_params.m_teamLeader.Display = m_cmbTeamLeader.SelectedItem.ToString();
*          } else {}
*          UpdateUI();
*      }
*      
*      public void UpdateUI()
*      {
*          //Change the states of controls based on parameter values.
*          m_cmbTeamLeader.SelectedItem = m_params.m_TeamLeader.Display;
*          m_nudNumberOfEmployees.Value = m_params.m_numWorkers.Value;
*          
*          //Test the parameter
*          if (m_params.m_numWorkers.Value < 3) {m_cmbTeamLeader.Enabled = false;}
*          if (m_params.m_teamLeader.Value == CyEEmployees.DAND) {m_cbDeservesRaise.Checked = true;}
*      }
* }
* 
*/
    public class CyParamWrapper<T>
    {
        protected ICyInstQuery_v1 m_instQuery;
        protected ICyInstEdit_v1 m_instEdit;
        protected string m_paramName;
        public CyParamWrapper(ICyInstEdit_v1 instEdit, string paramName)
        {
            this.m_instEdit = instEdit;
            this.m_instQuery = instEdit;
            this.m_paramName = paramName;
        }
        /// <summary>
        /// Gets and sets the parameter's value
        /// </summary>
        public T Value
        {
            get
            {
                return GetValue();
            }
            set
            {
                SetValue(value);
            }
        }

        #region Getting Parameters

        protected T GetValue()
        {
            if (m_instQuery == null) return default(T);
            T value;
            
            CyCustErr err = m_instQuery.GetCommittedParam(m_paramName).TryGetValueAs<T>(out value);
            
            if (err != null && err.IsOK)
            {
                return value;
            }
            else
            {
                return default(T);
            }
        }
        #endregion

        #region Setting Parameters
        protected CyCustErr SetValue(T value)
        {
            if (m_instEdit == null)
            {
                return CyCustErr.OK;
            }

            string valueToSet = value.ToString();
            if (value is bool)
                valueToSet = valueToSet.ToLower();
            if (value is byte || value is UInt16 || value is UInt32 || value is UInt64)
                valueToSet += "u";

            if (m_instEdit.SetParamExpr(m_paramName, valueToSet) && m_instEdit.CommitParamExprs())
            {
                return CyCustErr.OK;
            }

            CyCompDevParam param = m_instEdit.GetCommittedParam(m_paramName);
            return param.ErrorCount > 0 ? new CyCustErr(param.ErrorMsgs) : CyCustErr.OK;
        }
        #endregion
    }

    public class CyEnumWrapper<T>:CyParamWrapper<T>
    {
        public CyEnumWrapper(ICyInstEdit_v1 instEdit, string paramName):base(instEdit, paramName)
        {
        }

        /// <summary>
        /// Gets the enum item display literal or sets the parameter's value by enum display.
        /// </summary>
        public string Display
        {
            get
            {
                string res = string.Empty;

                CyCompDevParam param = m_instQuery.GetCommittedParam(m_paramName);
                if (param != null)
                {
                    m_instQuery.ResolveEnumParamToDisplay(param, out res);
                }

                return res;
            }
            set
            {
                string enumItemName = m_instQuery.ResolveEnumDisplayToId(m_paramName, value);
                //enumItemName = m_instQuery.ComponentName
                try
                {
                    Value = (T)Enum.Parse(typeof(T), enumItemName);
                }
                catch { }
            }
        }

        /// <summary>
        /// Gets the array of strings - display literals of the enumeration that is a type of the parameter.
        /// </summary>
        public string[] EnumDisplayList
        {
            get
            {
                return new List<string>(m_instQuery.GetPossibleEnumValues(m_paramName)).ToArray();
            }
        }

        /// <summary>
        /// Get the enum item display from the specified enum value.
        /// </summary>
        /// <param name="value">Enum item value</param>
        /// <returns>Enum item display literal</returns>
        public string ValueToDisplay(T value)
        {
            string res = string.Empty;

            CyCompDevParam prm = m_instQuery.GetCommittedParam(m_paramName);

            if (prm != null)
            {
                CyCompDevParam newParam = new CyCompDevParam(prm.Name, prm.Expr, prm.ExprType, value.ToString(),
                    prm.TypeName, prm.DefaultExpr, prm.TabName, prm.CategoryName, prm.Description, prm.IsVisible,
                    prm.IsReadOnly, prm.IsHardware, prm.IsFormal, prm.IsDisplayEvaluated, prm.ErrorCount, value,
                    prm.Errors);

                if (newParam != null)
                {
                    m_instQuery.ResolveEnumParamToDisplay(newParam, out res);
                }
            }

            return res;
        }

    }
}

