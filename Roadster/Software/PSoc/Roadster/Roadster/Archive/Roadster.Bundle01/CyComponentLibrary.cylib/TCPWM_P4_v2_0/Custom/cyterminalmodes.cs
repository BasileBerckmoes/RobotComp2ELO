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

namespace TCPWM_P4_v2_0
{
    [Serializable]
    public class CyTerminalsModes
    {
        private CyETCPWMConfig m_tcpwmMode;
        private CyETerminalMode m_termMode_clock;
        private CyETerminalMode m_termMode_reload;
        private CyETerminalMode m_termMode_count;
        private CyETerminalMode m_termMode_start;
        private CyETerminalMode m_termMode_stop;
        private CyETerminalMode m_termMode_capture;
        private CyETerminalMode m_termMode_ov;
        private CyETerminalMode m_termMode_un;
        private CyETerminalMode m_termMode_cc;
        private CyETerminalMode m_termMode_line;
        private CyETerminalMode m_termMode_line_n;
        private CyETerminalMode m_termMode_interrupt;

        #region Properties
        [XmlElement("TCPWM_mode")]
        public CyETCPWMConfig TCPWM_Mode
        {
            get { return m_tcpwmMode; }
            set { m_tcpwmMode = value; }
        }

        [XmlElement("TermMode_clock")]
        public CyETerminalMode TermMode_clock
        {
            get { return m_termMode_clock; }
            set { m_termMode_clock = value; }
        }

        [XmlElement("TermMode_reload")]
        public CyETerminalMode TermMode_reload
        {
            get { return m_termMode_reload; }
            set { m_termMode_reload = value; }
        }

        [XmlElement("TermMode_count")]
        public CyETerminalMode TermMode_count
        {
            get { return m_termMode_count; }
            set { m_termMode_count = value; }
        }

        [XmlElement("TermMode_start")]
        public CyETerminalMode TermMode_start
        {
            get { return m_termMode_start; }
            set { m_termMode_start = value; }
        }

        [XmlElement("TermMode_stop")]
        public CyETerminalMode TermMode_stop
        {
            get { return m_termMode_stop; }
            set { m_termMode_stop = value; }
        }

        [XmlElement("TermMode_capture")]
        public CyETerminalMode TermMode_capture
        {
            get { return m_termMode_capture; }
            set { m_termMode_capture = value; }
        }

        [XmlElement("TermMode_ov")]
        public CyETerminalMode TermMode_ov
        {
            get { return m_termMode_ov; }
            set { m_termMode_ov = value; }
        }

        [XmlElement("TermMode_un")]
        public CyETerminalMode TermMode_un
        {
            get { return m_termMode_un; }
            set { m_termMode_un = value; }
        }

        [XmlElement("TermMode_cc")]
        public CyETerminalMode TermMode_cc
        {
            get { return m_termMode_cc; }
            set { m_termMode_cc = value; }
        }

        [XmlElement("TermMode_line")]
        public CyETerminalMode TermMode_line
        {
            get { return m_termMode_line; }
            set { m_termMode_line = value; }
        }

        [XmlElement("TermMode_line_n")]
        public CyETerminalMode TermMode_line_n
        {
            get { return m_termMode_line_n; }
            set { m_termMode_line_n = value; }
        }

        [XmlElement("TermMode_interrupt")]
        public CyETerminalMode TermMode_interrupt
        {
            get { return m_termMode_interrupt; }
            set { m_termMode_interrupt = value; }
        }
        #endregion

        #region Constructor(s)
        public CyTerminalsModes() { }
        public CyTerminalsModes(CyETCPWMConfig tcpwm_mode, CyETerminalMode termMode_clock, 
            CyETerminalMode termMode_reload, CyETerminalMode termMode_count, CyETerminalMode termMode_start,
            CyETerminalMode termMode_stop, CyETerminalMode termMode_capture, CyETerminalMode termMode_ov, 
            CyETerminalMode termMode_un, CyETerminalMode termMode_cc, CyETerminalMode termMode_line, 
            CyETerminalMode termMode_line_n, CyETerminalMode termMode_interrupt)
        {
            this.m_tcpwmMode = tcpwm_mode;
            this.m_termMode_clock = termMode_clock;
            this.m_termMode_reload = termMode_reload;
            this.m_termMode_count = termMode_count;
            this.m_termMode_start = termMode_start;
            this.m_termMode_stop = termMode_stop;
            this.m_termMode_capture = termMode_capture;
            this.m_termMode_ov = termMode_ov;
            this.m_termMode_un = termMode_un;
            this.m_termMode_cc = termMode_cc;
            this.m_termMode_line = termMode_line;
            this.m_termMode_line_n = termMode_line_n;
            this.m_termMode_interrupt = termMode_interrupt;
        }
        #endregion
    }
}
