/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Xml.Serialization;

namespace ScanComp_v1_10
{
    public interface ICyTable
    {
        void InitializeTable(int count);
    }

    [Serializable]
    public class CyChannelsTableRow
    {
        private CyEChannelIntMode m_interruptMode;
        private UInt16 m_vdacVoltage;

        public CyChannelsTableRow() { }

        public CyEChannelIntMode InterruptMode
        {
            get { return m_interruptMode; }
            set { m_interruptMode = value; }
        }

        public UInt16 DacVoltage
        {
            get { return m_vdacVoltage; }
            set { m_vdacVoltage = value; }
        }

        public static CyChannelsTableRow CreateDefaultRow()
        {
            CyChannelsTableRow row = new CyChannelsTableRow();
            row.m_interruptMode = CyEChannelIntMode.INTR_LEVEL;
            row.m_vdacVoltage = 2000; // default is 2000 since default range is 4 V
            return row;
        }
    }

    [Serializable]
    public class CyChannelsTable : ICyTable
    {
        private List<CyChannelsTableRow> m_channelsList = new List<CyChannelsTableRow>();

        #region Constructor(s)
        public CyChannelsTable() { }
        public CyChannelsTable(List<CyChannelsTableRow> rows)
            : base()
        {
            m_channelsList = rows;
        }
        #endregion

        #region Properties
        public List<CyChannelsTableRow> ChannelsList
        {
            get { return m_channelsList; }
            set { m_channelsList = value; }
        }

        [XmlIgnore]
        public CyChannelsTableRow this[int i]
        {
            get
            {
                return (i < m_channelsList.Count) ? this.m_channelsList[i] : CyChannelsTableRow.CreateDefaultRow();
            }
        }

        [XmlIgnore]
        public int Count
        {
            get { return m_channelsList.Count; }
        }
        #endregion

        #region Methods
        /// <summary>
        /// Create DataGridView with default rows
        /// </summary>
        /// <param name="count">Number of rows</param>
        public void InitializeTable(int count)
        {
            for (int i = 0; i < count; i++)
            {
                m_channelsList.Add(CyChannelsTableRow.CreateDefaultRow());
            }
        }

        public void Add(CyChannelsTableRow row)
        {
            m_channelsList.Add(row);
        }

        /// <summary>
        /// Converts list of rows to array of rows
        /// </summary>
        public CyChannelsTableRow[] ToArray()
        {
            return m_channelsList.ToArray();
        }
        #endregion
    }
}
