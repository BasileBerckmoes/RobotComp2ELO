/*******************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;

namespace I2C_LCD_v1_20
{
    [Serializable]
    public class CyCommandRow
    {
        private byte? m_cmdSize;
        private byte? m_dataSize;
        private byte? m_cmdByte1;
        private byte? m_cmdByte2;
        private byte? m_cmdByte3;
        private byte? m_cmdByte4;

        #region Properties
        [XmlElement("CommandSize")]
        public byte? CmdSize
        {
            get { return m_cmdSize; }
            set { m_cmdSize = value; }
        }

        [XmlElement("DataSize")]
        public byte? DataSize
        {
            get { return m_dataSize; }
            set { m_dataSize = value; }
        }

        [XmlElement("CmdByte1")]
        public byte? CmdByte1
        {
            get { return m_cmdByte1; }
            set { m_cmdByte1 = value; }
        }

        [XmlElement("CmdByte2")]
        public byte? CmdByte2
        {
            get { return m_cmdByte2; }
            set { m_cmdByte2 = value; }
        }

        [XmlElement("CmdByte3")]
        public byte? CmdByte3
        {
            get { return m_cmdByte3; }
            set { m_cmdByte3 = value; }
        }

        [XmlElement("CmdByte4")]
        public byte? CmdByte4
        {
            get { return m_cmdByte4; }
            set { m_cmdByte4 = value; }
        }
        #endregion

        #region Constructor(s)
        public CyCommandRow() { }
        public CyCommandRow(byte? cmdSize, byte? dataSize, byte? cmdByte1, byte? cmdByte2, byte? cmdByte3,
            byte? cmdByte4)
        {
            this.m_cmdSize = cmdSize;
            this.m_dataSize = dataSize;
            this.m_cmdByte1 = cmdByte1;
            this.m_cmdByte2 = cmdByte2;
            this.m_cmdByte3 = cmdByte3;
            this.m_cmdByte4 = cmdByte4;
        }
        #endregion
    }

    [Serializable]
    public class CyRequiredCommandRow : CyCommandRow
    {
        private string m_cmdDescription;
        private bool m_isDataSizeReadOnly = true;
        private string m_cmdName;

        #region Properties
        [XmlIgnore]
        public string CmdDescription
        {
            get { return m_cmdDescription; }
            set { m_cmdDescription = value; }
        }

        [XmlIgnore]
        public bool IsDataSizeReadOnly
        {
            get { return m_isDataSizeReadOnly; }
            set { m_isDataSizeReadOnly = value; }
        }

        [XmlIgnore]
        public string CmdName
        {
            get { return m_cmdName; }
            set { m_cmdName = value; }
        }
        #endregion

        #region Constructor(s)
        public CyRequiredCommandRow() { }
        public CyRequiredCommandRow(byte? cmdSize, byte? dataSize, bool isDataSizeReadOnly,
            byte? cmdByte1, byte? cmdByte2, byte? cmdByte3, byte? cmdByte4, string cmdName, string cmdDescription)
            : base(cmdSize, dataSize, cmdByte1, cmdByte2, cmdByte3, cmdByte4)
        {
            this.m_isDataSizeReadOnly = isDataSizeReadOnly;
            this.m_cmdDescription = cmdDescription;
            this.m_cmdName = cmdName;
        }
        #endregion
    }

    [Serializable]
    public class CyCustomCommandRow : CyCommandRow
    {
        private bool m_enable;
        private string m_apiName;

        #region Properties
        [XmlElement("Enable")]
        public bool Enable
        {
            get { return m_enable; }
            set { m_enable = value; }
        }

        [XmlElement("APIName")]
        public string ApiName
        {
            get { return m_apiName; }
            set { m_apiName = value; }
        }
        #endregion

        #region Constructor(s)
        public CyCustomCommandRow() { }
        public CyCustomCommandRow(bool enable, byte? cmdSize, byte? dataSize, byte? cmdByte1, byte? cmdByte2, byte?
            cmdByte3, byte? cmdByte4, string apiName)
            : base(cmdSize, dataSize, cmdByte1, cmdByte2, cmdByte3, cmdByte4)
        {
            this.m_enable = enable;
            this.m_apiName = apiName;
        }
        #endregion
    }
}
