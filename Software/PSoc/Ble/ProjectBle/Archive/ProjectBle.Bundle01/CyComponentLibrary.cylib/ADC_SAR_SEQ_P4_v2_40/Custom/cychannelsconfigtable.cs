/*******************************************************************************
* Copyright 2011-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.Xml.Serialization;

namespace ADC_SAR_SEQ_P4_v2_40
{
    public interface ICyTable
    {
        void InitializeTable(int count);
    }

    [Serializable]
    public class CyChannelsConfigTableRow
    {
        public const bool DEFAULT_ENABLED = true;
        public const bool DEFAULT_INJ_ENABLED = false;
        public const CyEMode DEFAULT_MODE = CyEMode.Diff;
        public const CyEResolution DEFAULT_RESOLUTION = CyEResolution.Twelve;
        public const bool DEFAULT_AVERAGED = false;
        public const CyEAcquisionTime DEFAULT_ACQTIME = CyEAcquisionTime.AClocks;

        public bool m_enabled;
        public CyEResolution m_resolution;
        public CyEMode m_mode;
        public bool m_averaged;
        public CyEAcquisionTime m_acqTime;
        public bool m_limitsDetectIntrEnabled;
        public bool m_saturationIntrEnabled;

        public CyChannelsConfigTableRow()
        {
        }

        public static CyChannelsConfigTableRow CreateDefaultRow(int rowIndex)
        {
            CyChannelsConfigTableRow row = new CyChannelsConfigTableRow();

            row.m_enabled = (rowIndex == CyChannelsConfigTable.INJ_CHANNEL_INDEX) ?
                DEFAULT_INJ_ENABLED :
                DEFAULT_ENABLED;
            row.m_resolution = DEFAULT_RESOLUTION;
            row.m_mode = DEFAULT_MODE;
            row.m_averaged = DEFAULT_AVERAGED;
            row.m_acqTime = DEFAULT_ACQTIME;
            row.m_limitsDetectIntrEnabled = false;
            row.m_saturationIntrEnabled = false;

            return row;
        }
    }

    [Serializable]
    public class CyChannelsConfigTable : ICyTable
    {
        public const int INJ_CHANNEL_INDEX = 0;
        public List<CyChannelsConfigTableRow> m_channelsConfigTable = new List<CyChannelsConfigTableRow>();

        public CyChannelsConfigTable() { }

        public CyChannelsConfigTable(List<CyChannelsConfigTableRow> rows)
        {
            m_channelsConfigTable = rows;
        }

        public void InitializeTable(int count)
        {
            for (int i = 0; i < count; i++)
            {
                m_channelsConfigTable.Add(CyChannelsConfigTableRow.CreateDefaultRow(i));
            }
        }

        [XmlIgnore]
        public CyChannelsConfigTableRow this[int i]
        {
            get
            {
                return (i < this.m_channelsConfigTable.Count) ?
                    this.m_channelsConfigTable[i] :
                    CyChannelsConfigTableRow.CreateDefaultRow(i);
            }
        }

        [XmlIgnore]
        public int Count
        {
            get { return m_channelsConfigTable.Count; }
        }

        public CyChannelsConfigTableRow[] ToArray()
        {
            return m_channelsConfigTable.ToArray();
        }

        public void Add(CyChannelsConfigTableRow row)
        {
            m_channelsConfigTable.Add(row);
        }
    }
}
