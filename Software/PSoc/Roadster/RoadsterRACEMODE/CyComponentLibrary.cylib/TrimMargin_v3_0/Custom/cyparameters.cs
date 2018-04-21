/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.IO;
using System.Xml;
using System.Text;
using System.Diagnostics;
using System.Globalization;
using System.Windows.Forms;
using System.Xml.Serialization;
using System.Collections.Generic;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using TrimMargin_v3_0.Tabs;
using TrimMargin_v3_0.Utils;
using TrimMargin_v3_0.DataStructures;

namespace TrimMargin_v3_0
{
    internal static class CyParamNames
    {
        internal const string USE_FF_PWM = "UseFF_PWM";
        internal const string INSTANCE_NAME = "INSTANCE_NAME";
        internal const string NUM_CONVERTERS = "NumConverters";
        internal const string PWM_RESOLUTION = "PWMResolution";
        internal const string VOLTAGES_TABLE = "VoltagesTable";
        internal const string HARDWARE_TABLE = "HardwareTable";
        internal const string CONTROLLER_METHOD = "ControllerMethod";
        internal const string PARAMNAME_IS_COLUMNS_VISIBLE = "IsColumnsVisible";
    }

    public class CyParameters
    {
        [XmlIgnore]
        public CySummaryTab m_voltagesTab;

        [XmlIgnore]
        public static DataGridViewCellStyle DGDisabledStyle;

        [XmlIgnore]
        public static DataGridViewCellStyle DGEnabledStyle;

        // There were two tabs Voltages and Hardware before. Now there is 
        // only one tab and hardware table header is not used.
        [XmlIgnore]
        public static List<string> VoltagesHeader_v3_0 = new List<string>();

        [XmlIgnore]
        public static List<string> VoltagesHeader_v1_0 = new List<string>(
            new string[] {
            "Power converter number", "Power converter name", "Nominal voltage (V)",
            "Trim/margin range Min voltage (V)", "Trim/margin range Max voltage (V)", "Margin low (%)",
            "Margin high (%)", "Margin low (V)", "Margin high (V)"
        });

        private readonly ICyInstEdit_v1 m_instEdit;
        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyTerminalQuery_v1 m_termQuery;
        private readonly ICyDeviceQuery_v1 m_deviceQuery;
        private List<CyVoltagesTableRow> m_voltagesTable;
        private List<CyHardwareTableRow> m_hardwareTable;
        private List<CyColumnsVisibility> m_columnsVisibility;
        private Dictionary<string, object> m_restoredParameters = new Dictionary<string, object>();

        // XML serialization parameters
        private XmlSerializer m_serializerVoltages;
        private XmlSerializer m_serializerHardware;
        private XmlSerializer m_serializerParameters;
        private XmlSerializer m_serializerIsColumnsVisible;
        private XmlSerializerNamespaces m_customSerNamespace;

        #region Constructor(s)
        private CyParameters(ICyInstQuery_v1 instQuery, ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery,
            ICyDeviceQuery_v1 deviceQuery)
        {
            m_instQuery = instQuery;
            m_instEdit = instEdit;
            m_termQuery = termQuery;
            m_deviceQuery = deviceQuery;

            // Create XML serializer
            m_serializerVoltages = new XmlSerializer(typeof(CyVoltagesTable));
            m_serializerHardware = new XmlSerializer(typeof(CyHardwareTable));
            m_serializerParameters = new XmlSerializer(typeof(CyParameters));
            m_serializerIsColumnsVisible = new XmlSerializer(typeof(List<CyColumnsVisibility>));
            m_customSerNamespace = new XmlSerializerNamespaces();

            Type classType = typeof(CyParameters);
            string curNamespace = classType.Namespace;
            string version = curNamespace.Substring(curNamespace.LastIndexOf("_v") + 2);
            m_customSerNamespace.Add("Version", version);

            GetVoltagesTable();
            GetHardwareTable();
            GetIsColumnsVisible();
        }

        public CyParameters(ICyInstQuery_v1 instQuery, ICyDeviceQuery_v1 deviceQuery)
            : this(instQuery, null, null, deviceQuery)
        {
        }

        public CyParameters(ICyInstQuery_v1 instQuery, ICyTerminalQuery_v1 termQuery, ICyDeviceQuery_v1 deviceQuery)
            : this(instQuery, null, termQuery, deviceQuery)
        {
        }

        public CyParameters(ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery, ICyDeviceQuery_v1 deviceQuery)
            : this(instEdit, instEdit, termQuery, deviceQuery)
        {
        }

        public CyParameters() { }
        #endregion

        #region Properties
        [XmlIgnore]
        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        }

        [XmlIgnore]
        public ICyTerminalQuery_v1 TermQuery
        {
            get { return m_termQuery; }
        }

        [XmlIgnore]
        public bool GlobalEditMode { get; set; }

        [XmlIgnore]
        public string InstanceName
        {
            get { return GetValue<string>(CyParamNames.INSTANCE_NAME); }
        }

        [XmlIgnore]
        public bool UdbBlockExists
        {
            get
            {
                if (m_deviceQuery == null)
                    return false;

                return (m_deviceQuery.GetFeatureParameter("m0s8udbif", "NUMUDB") > 0) ||
                       (m_deviceQuery.GetFeatureParameter("m0s8udb", "NUMUDB") > 0) ||
                       (m_deviceQuery.GetFeatureCount("S8_UDB") > 0);
            }
        }

        [XmlIgnore]
        public bool TcpwmBlockExists
        {
            get
            {
                return m_deviceQuery != null && m_deviceQuery.GetFeatureCount("m0s8tcpwm") > 0;
            }
        }

        [XmlElement("NumConverters")]
        public byte NumConverters
        {
            get { return GetValue<byte>(CyParamNames.NUM_CONVERTERS); }
            set { SetValue(CyParamNames.NUM_CONVERTERS, value); }
        }

        [XmlElement("PWMResolution")]
        public byte PWMResolution
        {
            get { return GetValue<byte>(CyParamNames.PWM_RESOLUTION); }
            set { SetValue(CyParamNames.PWM_RESOLUTION, value); }
        }

        [XmlElement("PwmImplementation")]
        public CyEImplementation PwmImplementation
        {
            get
            {
                bool useFixedFunctionPwm = GetValue<bool>(CyParamNames.USE_FF_PWM);
                return useFixedFunctionPwm ? CyEImplementation.FixedFunction : CyEImplementation.UDB;
            }
            set
            {
                bool useFixedFunctionPwm = false;
                switch (value)
                {
                    case CyEImplementation.UDB:
                        useFixedFunctionPwm = false;
                        break;
                    case CyEImplementation.FixedFunction:
                        useFixedFunctionPwm = true;
                        break;
                    default:
                        Debug.Fail("Unhandled implementation type.");
                        break;
                }

                SetValue(CyParamNames.USE_FF_PWM, useFixedFunctionPwm);
            }
        }

        [XmlElement("ControllerMethod")]
        public CyEControllerMethod ControllerMethod
        {
            get { return GetValue<CyEControllerMethod>(CyParamNames.CONTROLLER_METHOD); }
            set { SetValue(CyParamNames.CONTROLLER_METHOD, value); }
        }

        [XmlArray("VoltagesTable")]
        public List<CyVoltagesTableRow> VoltagesTable
        {
            get { return m_voltagesTable; }
            set { m_voltagesTable = value; }
        }

        [XmlArray("HardwareTable")]
        public List<CyHardwareTableRow> HardwareTable
        {
            get { return m_hardwareTable; }
            set { m_hardwareTable = value; }
        }

        [XmlArray("IsColumnsVisible")]
        public List<CyColumnsVisibility> ColumnsVisibility
        {
            get { return m_columnsVisibility; }
            set { m_columnsVisibility = value; }
        }

        [XmlIgnore]
        public bool IsVoltagesTableDefault { get; set; }

        [XmlIgnore]
        public bool IsPSoC4 
        {
            get
            {
                if (InstQuery != null)
                    return InstQuery.DeviceQuery.IsPSoC4;
                else
                    return false;
            }
        }
        #endregion

        #region Getting Parameters
        /// <summary>
        /// Gets parameter value from the symbol.
        /// </summary>
        private T GetValue<T>(string paramName)
        {
            T value = default(T);
            if (m_instQuery == null) return default(T);
            CyCompDevParam param = m_instQuery.GetCommittedParam(paramName);
            CyCustErr err = (param != null) ? param.TryGetValueAs<T>(out value) : CyCustErr.OK;
            return (err != null && err.IsOK && value != null) ? value : default(T);
        }

        private void GetIsColumnsVisible()
        {
            string xmlData = GetValue<string>(CyParamNames.PARAMNAME_IS_COLUMNS_VISIBLE);

            if (String.IsNullOrEmpty(xmlData))
                return;

            XmlReader tr = XmlReader.Create(new StringReader(xmlData));
            m_columnsVisibility = (List<CyColumnsVisibility>)m_serializerIsColumnsVisible.Deserialize(tr);
        }

        private void GetVoltagesTable()
        {
            string xmlData = GetValue<string>(CyParamNames.VOLTAGES_TABLE);
            string version = String.Empty;

            CyVoltagesTable package = (CyVoltagesTable)Deserialize(xmlData, typeof(CyVoltagesTable), ref version,
                this.NumConverters);

            // Compatibility with versions older 1_20
            CyComponentVersion ver1_20 = new CyComponentVersion(1, 20);
            CyComponentVersion xmlVersion = new CyComponentVersion(version);
            if (xmlVersion.IsValid && xmlVersion.CompareTo(ver1_20) < 0)
            {
                package.MigrateFrom_v1_20();
            }

            m_voltagesTable = package.m_voltagesTable;
        }

        private void GetHardwareTable()
        {
            string xmlData = GetValue<string>(CyParamNames.HARDWARE_TABLE);
            string version = String.Empty;

            CyHardwareTable package = (CyHardwareTable)Deserialize(xmlData, typeof(CyHardwareTable), ref version,
                this.NumConverters);

            // Compatibility with versions older 1_20
            CyComponentVersion ver1_20 = new CyComponentVersion(1, 20);
            CyComponentVersion xmlVersion = new CyComponentVersion(version);
            if (xmlVersion.IsValid && xmlVersion.CompareTo(ver1_20) < 0)
            {
                package.MigrateFrom_v1_20();
            }

            m_hardwareTable = package.m_hardwareTable;
        }
        #endregion

        #region Setting Parameters
        private void SetValue<T>(string paramName, T value)
        {
            if (GlobalEditMode)
            {
                if (m_instEdit == null) return;

                string valueToSet = (value != null) ? value.ToString() : String.Empty;
                if (value is bool)
                    valueToSet = valueToSet.ToLower();
                if (m_instEdit.SetParamExpr(paramName, valueToSet))
                {
                    m_instEdit.CommitParamExprs();
                }
            }
            // Saving data after deserialization
            if ((GlobalEditMode == false) && (m_instEdit == null))
            {
                if (m_restoredParameters.ContainsKey(paramName))
                {
                    Debug.Assert(false);
                    return;
                }
                m_restoredParameters.Add(paramName, value);
            }
        }

        public void SetIsColumnsVisible()
        {
            StringBuilder sb = new StringBuilder();
            using (XmlWriter tw = XmlWriter.Create(sb))
            {
                m_serializerIsColumnsVisible.Serialize(tw, m_columnsVisibility, m_customSerNamespace);
            }
            SetValue(CyParamNames.PARAMNAME_IS_COLUMNS_VISIBLE, sb.ToString());
        }

        public void SetVoltagesTable()
        {
            CyVoltagesTable package = new CyVoltagesTable();
            package.m_voltagesTable = new List<CyVoltagesTableRow>(m_voltagesTable);
            if ((package.m_voltagesTable.Count - NumConverters) > 0)
            {
                package.m_voltagesTable.RemoveRange(NumConverters, package.m_voltagesTable.Count - NumConverters);
            }
            SetValue(CyParamNames.VOLTAGES_TABLE, Serialize(package));
        }

        public void SetHardwareTable()
        {
            CyHardwareTable package = new CyHardwareTable();
            package.m_hardwareTable = new List<CyHardwareTableRow>(m_hardwareTable);
            if ((package.m_hardwareTable.Count - NumConverters) > 0)
            {
                package.m_hardwareTable.RemoveRange(NumConverters, package.m_hardwareTable.Count - NumConverters);
            }
            SetValue(CyParamNames.HARDWARE_TABLE, Serialize(package));
        }

        private void RestoreParameters(Dictionary<string, object> restoreList)
        {
            foreach (string param_name in restoreList.Keys)
            {
                SetValue<object>(param_name, restoreList[param_name]);
            }
        }
        #endregion

        #region Import or paste rows
        public bool Import(string fileContent)
        {
            List<CyHardwareTableRow> importedTableHardware;
            List<CyVoltagesTableRow> importedTableVoltages;
            CyImportExport.ImportTables(out importedTableVoltages, out importedTableHardware, NumConverters,
                CyParameters.VoltagesHeader_v3_0, fileContent);

            int firstPasteRow = -1;
            int lastPasteRow = -1;
            if (importedTableVoltages != null && importedTableHardware != null)
            {
                firstPasteRow = m_voltagesTab.DataGridFirstSelectedRow;
                lastPasteRow = GetLastPasteRow(importedTableVoltages.Count, firstPasteRow, NumConverters);

                int j = 0;
                for (int i = firstPasteRow; i < lastPasteRow; i++)
                {
                    VoltagesTable[i] = importedTableVoltages[j];
                    HardwareTable[i] = importedTableHardware[j];
                    j++;
                }
                m_voltagesTab.UpdateDataGridFromTable();

                SetVoltagesTable();
                SetHardwareTable();
                m_voltagesTab.ValidateTable();
                m_voltagesTab.SelectDataGridViewRows(firstPasteRow, lastPasteRow - 1);
                m_voltagesTab.ValidateImplementation();
            }
            else
            {
                return false;
            }

            return true;
        }

        private static int GetLastPasteRow(int importRowCount, int datagridActiveRowIndex, int gridRowsCount)
        {
            int lastPasteRow;
            if (importRowCount > (gridRowsCount - datagridActiveRowIndex))
            {
                lastPasteRow = datagridActiveRowIndex + (gridRowsCount - datagridActiveRowIndex);
            }
            else
            {
                lastPasteRow = datagridActiveRowIndex + importRowCount;
            }
            return lastPasteRow;
        }
        #endregion

        #region XML Serialization
        public void LoadAllParametersFromFile(string fileContent)
        {
            string version = "";
            CyParameters imported = (CyParameters)Deserialize(fileContent, typeof(CyParameters), ref version, 0);

            if (imported == null)
            {
                MessageBox.Show(Resources.LoadConfigErrorMsg, Resources.MsgErrorTitle, MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
            }
            else
            {
                Action onError = () =>
                {
                    GlobalEditMode = true;
                    MessageBox.Show(Resources.LoadConfigParamsErrorMsg, Resources.MsgErrorTitle, MessageBoxButtons.OK,
                            MessageBoxIcon.Error);
                };

                try
                {
                    bool prevGlobalEditMode = GlobalEditMode;
                    GlobalEditMode = true;

                    RestoreParameters(imported.m_restoredParameters);

                    this.VoltagesTable = imported.VoltagesTable;
                    this.HardwareTable = imported.HardwareTable;
                    this.ColumnsVisibility = imported.ColumnsVisibility;

                    SetVoltagesTable();
                    SetHardwareTable();
                    SetIsColumnsVisible();

                    GlobalEditMode = false;

                    m_voltagesTab.UpdateUI();

                    GlobalEditMode = prevGlobalEditMode;
                }
                catch (NullReferenceException)
                {
                    onError();
                }
                catch (InvalidOperationException)
                {
                    onError();
                }
            }
        }

        private XmlSerializer GetSerializer(Type type)
        {
            if (type == typeof(CyHardwareTable))
                return m_serializerHardware;
            else if (type == typeof(CyVoltagesTable))
                return m_serializerVoltages;
            else if (type == typeof(CyParameters))
                return m_serializerParameters;
            return null;
        }

        public string Serialize(object obj)
        {
            using (StringWriter sw = new StringWriter(CultureInfo.InvariantCulture))
            {
                using (XmlWriter xw = System.Xml.XmlWriter.Create(sw))
                {
                    XmlSerializer serializer = GetSerializer(obj.GetType());
                    serializer.Serialize(xw, obj, m_customSerNamespace);
                }
                return sw.ToString();
            }
        }

        public object Deserialize(string serializedXml, Type t, ref string version, byte numOfDefaultRows)
        {
            object res = null;
            try
            {
                if (String.IsNullOrEmpty(serializedXml)) throw new ArgumentException();

                using (XmlReader tr = XmlReader.Create(new StringReader(serializedXml)))
                {
                    // Remove header <?xml version="1.0" encoding="utf-16" ?>
                    tr.ReadToFollowing(t.Name);
                    // Go to first node with attributes
                    while (tr.HasAttributes == false)
                    {
                        tr.Skip();
                    }

                    version = tr.GetAttribute(0);
                    res = GetSerializer(t).Deserialize(tr);
                }
                SetTableDefault(t, false);
            }
            catch (Exception ex)
            {
                if (ex is XmlException ||
                    ex is ArgumentException ||
                    ex is InvalidOperationException)
                {
                    res = Activator.CreateInstance(t);

                    if (res is ICyIntTable)
                    {
                        ((ICyIntTable)res).CreateTable(numOfDefaultRows);
                        SetTableDefault(t, true);

                        if (String.IsNullOrEmpty(serializedXml) == false)
                        {
                            MessageBox.Show(Resources.SettingsIncorrectValues, Resources.MsgWarningTitle,
                                MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        }
                    }
                    else
                    {
                        res = null;
                    }
                }
            }
            return res;
        }
        #endregion

        #region DataGridView
        private void SetTableDefault(Type t, bool isDefault)
        {
            if (t == typeof(CyVoltagesTable))
                IsVoltagesTableDefault = isDefault;
        }

        public bool CheckVoltagesTableNullValues()
        {
            for (int i = 0; i < NumConverters; i++)
            {
                if (VoltagesTable[i].ContainsNull)
                {
                    return false;
                }
            }
            return true;
        }

        public bool CheckHardwareTableNullValues()
        {
            for (int i = 0; i < NumConverters; i++)
            {
                if (HardwareTable[i].ContainsNull)
                {
                    return false;
                }
            }
            return true;
        }
        #endregion

        #region Clock
        /// <summary>
        /// Returns internal clock value
        /// </summary>
        public double? GetInternalClock()
        {
            List<CyClockData> clkdata = m_termQuery.GetClockData("clock", 0);

            if (clkdata.Count > 0 && clkdata[0].IsFrequencyKnown)
            {
                return clkdata[0].Frequency * Math.Pow(10, clkdata[0].UnitAsExponent);
            }
            return null;
        }
        #endregion
    }
}
