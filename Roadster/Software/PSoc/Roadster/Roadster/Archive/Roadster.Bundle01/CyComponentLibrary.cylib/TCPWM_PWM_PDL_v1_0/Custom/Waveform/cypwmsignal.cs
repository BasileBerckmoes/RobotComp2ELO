/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Drawing;
using System.Diagnostics;
using System.Collections.Generic;
using System.Windows.Forms;
using TCPWM_PWM_PDL_v1_0.Utils;

namespace TCPWM_PWM_PDL_v1_0.Waveform
{
    internal class CyPwmSignal : CyWaveform
    {
        private uint m_period0;
        private uint m_period1;
        private bool m_periodSwap;
        private uint m_compare0;
        private uint m_compare1;
        private bool m_compareSwap;
        private byte m_deadTime;
        private CyEnums.CyAlignment m_alignment;

        /// <summary>
        /// This period may have either period0 or period1 value depending on mode
        /// </summary>
        uint m_period;

        /// <summary>
        /// This compare may have either compare0 or compare1 value depending on mode.
        /// </summary>
        uint m_compare;

        /// <summary>
        /// Deadtime percent from period0.
        /// </summary>
        double m_deadtimePercentPeriod0;

        /// <summary>
        /// Deadtime percent from period1;
        /// </summary>
        double m_deadtimePercentPeriod;

        /// <summary>
        /// PWM signal segments.
        /// </summary>
        List<CySegment> pwmSegments;

        /// <summary>
        /// PWM_n signal segments
        /// </summary>
        List<CySegment> pwmNSegments;

        private CyPwmSignal(Graphics g, Size size) : base(g, size)
        {
            pwmSegments = new List<CySegment>();
            pwmNSegments = new List<CySegment>();
        }

        public CyPwmSignal(Graphics g, Size size,
            uint period0,
            uint period1,
            bool periodSwap,
            uint compare0,
            uint compare1,
            bool compareSwap,
            byte deadTime,
            CyEnums.CyAlignment alignment)
            : this(g, size)
        {
            m_period0 = period0;
            m_period1 = period1;
            m_periodSwap = periodSwap;
            m_compare0 = compare0;
            m_compare1 = compare1;
            m_compareSwap = compareSwap;
            m_deadTime = deadTime;
            m_alignment = alignment;
        }

        public override void Draw()
        {
            SelectActualPeriodAndCompare(m_period0, m_period1, m_compare0, m_compare1, m_periodSwap, m_compareSwap,
                out m_period, out m_compare);

            if (m_alignment == CyEnums.CyAlignment.LEFT)
            {
                // Increment period according to 002-10927 Rev *A. Figure 38: Left align PWM.
                m_period0++;
                m_period++;
            }
            else if (m_alignment == CyEnums.CyAlignment.RIGHT)
            {
                // Increment period according to 002-10927 Rev *A. Figure 39: Right align PWM.
                m_period0++;
                m_period++;
                m_compare0++;
                m_compare++;
            }

            if (m_period0 > 0)
            {
                m_deadtimePercentPeriod0 = m_deadTime / (double)m_period0 * 100;
            }
            if (m_period > 0)
            {
                m_deadtimePercentPeriod = m_deadTime / (double)m_period * 100;
            }

            switch (m_alignment)
            {
                case CyEnums.CyAlignment.LEFT:
                    DrawLeftAlignmentSignal();
                    break;
                case CyEnums.CyAlignment.RIGHT:
                    DrawRightAlignmentSignal();
                    break;
                case CyEnums.CyAlignment.CENTER:
                case CyEnums.CyAlignment.ASYMMETRIC:
                    DrawCenterAsymmetricAlignmentSignal();
                    break;
                default:
                    Debug.Fail("unhandled enum item.");
                    break;
            }

            // Draw PWM line segments
            DrawSegments(pwmSegments, 20, 60);

            // Draw PWM_n line segments
            DrawSegments(pwmNSegments, 80, 120);
        }

        private void DrawLeftAlignmentSignal()
        {
            // Find compare percent
            double compare0Percent = m_compare0 / (double)m_period0 * 100;
            double comparePercent = m_compare / (double)m_period * 100;

            // Find compare coordinates
            // X coordinate of compare0 on the left part of the waveform
            int compare0Left = GetPercentPosition(compare0Percent, Start, Center); 
            // X coordinate of compare 0/1 on the right part of the waveform
            int compareRight = GetPercentPosition(comparePercent, Center, End); 

            // Find dead time coordinates
            // X coordinate of deadtime based on period0 on the left part of the waveform
            int deadtimeLeft = GetPercentPosition(m_deadtimePercentPeriod0, Start, Center);
            // X coordinate of deadtime based on period 0/1 on the right part of the waveform
            int deadtimeRight = GetPercentPosition(m_deadtimePercentPeriod, Center, End);

            // Find compare+deadtime percent
            double dtp1Percent = (m_compare0 + m_deadTime) / (double)m_period0 * 100;
            double dtp2Percent = (m_compare + m_deadTime) / (double)m_period * 100;

            // Find compare+deatime coordinates
            int dtp1Pwm = GetPercentPosition(dtp1Percent, Start, Center);
            if (dtp1Pwm > Center)
                dtp1Pwm = Center;
            int dtp2Pwm =  GetPercentPosition(dtp2Percent, Center, End);
            if (dtp2Pwm > End)
                dtp2Pwm = End;

            // Left part
            if ((m_deadTime > 0) && IgnoreDeadTime(compare0Percent) == false)
            {
                if (deadtimeLeft >= compare0Left)
                {
                    // pwm
                    pwmSegments.Add(new CySegment(0, Start, Center));
                    // pwm_n
                    pwmNSegments.Add(new CySegment(0, Start, dtp1Pwm));
                    pwmNSegments.Add(new CySegment(1, dtp1Pwm, Center));
                }
                else
                {
                    // pwm
                    pwmSegments.Add(new CySegment(0, Start, deadtimeLeft));
                    pwmSegments.Add(new CySegment(1, deadtimeLeft, compare0Left));
                    pwmSegments.Add(new CySegment(0, compare0Left, Center));
                    // pwm_n
                    pwmNSegments.Add(new CySegment(0, Start, dtp1Pwm));
                    pwmNSegments.Add(new CySegment(1, dtp1Pwm, Center));
                }
            }
            else // m_deadTime == 0
            {
                if (m_compare0 >= m_period0)
                {
                    pwmSegments.Add(new CySegment(1, Start, Center));  // pwm
                    pwmNSegments.Add(new CySegment(0, Start, Center)); // pwm_n
                }
                else
                {
                    // pwm
                    pwmSegments.Add(new CySegment(1, Start, compare0Left));
                    pwmSegments.Add(new CySegment(0, compare0Left, Center));
                    // pwm_n
                    pwmNSegments.Add(new CySegment(0, Start, compare0Left));
                    pwmNSegments.Add(new CySegment(1, compare0Left, Center));
                }
            }
            // Right part
            if ((m_deadTime > 0) && IgnoreDeadTime(comparePercent) == false)
            {
                if (deadtimeRight >= compareRight)
                {
                    // pwm
                    pwmSegments.Add(new CySegment(0, Center, End));
                    // pwm_n
                    pwmNSegments.Add(new CySegment(0, Center, dtp2Pwm));
                    pwmNSegments.Add(new CySegment(1, dtp2Pwm, End));
                }
                else
                {
                    // pwm
                    pwmSegments.Add(new CySegment(0, Center, deadtimeRight));
                    pwmSegments.Add(new CySegment(1, deadtimeRight, compareRight));
                    pwmSegments.Add(new CySegment(0, compareRight, End));
                    // pwm_n
                    pwmNSegments.Add(new CySegment(0, Center, dtp2Pwm));
                    pwmNSegments.Add(new CySegment(1, dtp2Pwm, End));
                }
            }
            else // m_deadTime == 0
            {
                if (m_compare >= m_period)
                {
                    pwmSegments.Add(new CySegment(1, Center, End));  // pwm
                    pwmNSegments.Add(new CySegment(0, Center, End)); // pwm_n
                }
                else
                {
                    // pwm
                    pwmSegments.Add(new CySegment(1, Center, compareRight));
                    pwmSegments.Add(new CySegment(0, compareRight, End));
                    // pwm_n
                    pwmNSegments.Add(new CySegment(0, Center, compareRight));
                    pwmNSegments.Add(new CySegment(1, compareRight, End));
                }
            }
        }

        private void DrawRightAlignmentSignal()
        {
            // Find compare percent
            double compare0Percent = 100 - m_compare0 / (double)m_period0 * 100;
            double comparePercent = 100 - m_compare / (double)m_period * 100;

            // Find deadtime percent
            double dtP1PercentPwm = (100 - (m_compare0 / (double)m_period0 * 100)) + (m_deadTime / (double)m_period0 * 100);
            if (dtP1PercentPwm > 100)
                dtP1PercentPwm = 100;
            double dtP2PercentPwm = (100 - (m_compare / (double)m_period * 100)) + (m_deadTime / (double)m_period * 100);
            if (dtP2PercentPwm > 100)
                dtP2PercentPwm = 100;
            double dtP1PercentPwmN = (m_deadTime / (double)m_period0 * 100);
            if (dtP1PercentPwmN > 100)
                dtP1PercentPwmN = 100;
            double dtP2PercentPwmN = (m_deadTime / (double)m_period * 100);
            if (dtP2PercentPwmN > 100)
                dtP2PercentPwmN = 100;
            // If duty cycle = 0% or 100% then Dead time has no impact on PWM
            if (IgnoreDeadTime(compare0Percent))
            {
                dtP1PercentPwm = compare0Percent;
                dtP1PercentPwmN = 0;
            }
            if (IgnoreDeadTime(comparePercent))
            {
                dtP2PercentPwm = comparePercent;
                dtP2PercentPwmN = 0;
            }

            // Find compare coordinates
            // X coordinate of compare 0 on the left part of the waveform
            int compare0Left = GetPercentPosition(compare0Percent, Start, Center); 
            // X coordinate of compare 0/1 on the right part of the waveform
            int compareRight = GetPercentPosition(comparePercent, Center, End);

            // Find compare+deadtime coordinates
            int dtp1Pwm = GetPercentPosition(dtP1PercentPwm, Start, Center);
            if (dtp1Pwm > Center)
                dtp1Pwm = Center;
            int dtp1PwmN = GetPercentPosition(dtP1PercentPwmN, Start, Center);
            if (dtp1PwmN > compare0Left)
                dtp1PwmN = Center;
            int dtp2Pwm = GetPercentPosition(dtP2PercentPwm, Center, End);
            if (dtp2Pwm > End)
                dtp2Pwm = End;
            int dtp2PwmN = GetPercentPosition(dtP2PercentPwmN, Center, End);
            if (dtp2PwmN > compareRight)
                dtp2PwmN = End;

            // Left part
            if ((m_deadTime > 0) && IgnoreDeadTime(compare0Percent) == false)
            {
                // pwm
                pwmSegments.Add(new CySegment(0, Start, dtp1Pwm));
                pwmSegments.Add(new CySegment(1, dtp1Pwm, Center));
                // pwm_n
                if (dtp1PwmN > compare0Left)
                {
                    pwmNSegments.Add(new CySegment(0, Start, Center));
                }
                else
                {
                    pwmNSegments.Add(new CySegment(0, Start, dtp1PwmN));
                    pwmNSegments.Add(new CySegment(1, dtp1PwmN, compare0Left));
                    pwmNSegments.Add(new CySegment(0, compare0Left, Center));
                }
            }
            else // m_deadTime == 0
            {
                if (m_compare0 > m_period0) // Special case
                {
                    pwmSegments.Add(new CySegment(0, Start, Center));  // pwm
                    pwmNSegments.Add(new CySegment(1, Start, Center)); // pwm_n
                }
                else
                {
                    // pwm
                    pwmSegments.Add(new CySegment(0, Start, compare0Left));
                    pwmSegments.Add(new CySegment(1, compare0Left, Center));
                    // pwm_n
                    pwmNSegments.Add(new CySegment(1, Start, compare0Left));
                    pwmNSegments.Add(new CySegment(0, compare0Left, Center));
                }
            }
            // Right part
            if ((m_deadTime > 0) && IgnoreDeadTime(comparePercent) == false)
            {
                // pwm
                pwmSegments.Add(new CySegment(0, Center, dtp2Pwm));
                pwmSegments.Add(new CySegment(1, dtp2Pwm, End));
                // pwm_n
                if (dtp2PwmN > compareRight)
                {
                    pwmNSegments.Add(new CySegment(0, Center, End));
                }
                else
                {
                    pwmNSegments.Add(new CySegment(0, Center, dtp2PwmN));
                    pwmNSegments.Add(new CySegment(1, dtp2PwmN, compareRight));
                    pwmNSegments.Add(new CySegment(0, compareRight, End));
                }
            }
            else // m_deadTime == 0
            {
                if (m_compare > m_period) // Special case
                {
                    pwmSegments.Add(new CySegment(0, Center, End));  // pwm
                    pwmNSegments.Add(new CySegment(1, Center, End)); // pwm_n
                }
                else
                {
                    // pwm
                    pwmSegments.Add(new CySegment(0, Center, compareRight));
                    pwmSegments.Add(new CySegment(1, compareRight, End));
                    // pwm_n
                    pwmNSegments.Add(new CySegment(1, Center, compareRight));
                    pwmNSegments.Add(new CySegment(0, compareRight, End));
                }
            }
        }

        private void DrawCenterAsymmetricAlignmentSignal()
        {
            int compareQ1; // X coordinate of compare0 on the 1st quarter of the waveform
            int compareQ2; // X coordinate of compare0 on the 2nd quarter of the waveform
            int compareQ3; // X coordinate of compare0 on the 3rd quarter of the waveform
            int compareQ4; // X coordinate of compare0 on the 4th quarter of the waveform

            double dtQ1PercentPwm = 0;  // deadtime % from period on the Q1
            double dtQ2PercentPwm = 0;  // deadtime % from period on the Q2
            double dtQ3PercentPwm = 0;  // deadtime % from period on the Q3
            double dtQ4PercentPwm = 0;  // deadtime % from period on the Q4
            double dtQ1PercentPwmN = 0; // deadtime % from period on the Q1
            double dtQ2PercentPwmN = 0; // deadtime % from period on the Q2
            double dtQ3PercentPwmN = 0; // deadtime % from period on the Q3
            double dtQ4PercentPwmN = 0; // deadtime % from period on the Q4

            // Find compare percent
            double compareQ1Percent = 0;
            double compareQ2Percent = 0;
            double compareQ3Percent = 0;
            double compareQ4Percent = 0;

            bool ignoreQ1Q2deadTime = false;
            bool ignoreQ3Q4deadTime = false;

            if (m_alignment == CyEnums.CyAlignment.CENTER)
            {
                if (m_period0 > 0)
                {
                    compareQ1Percent = m_compare0 / (double)m_period0 * 100;
                    compareQ2Percent = compareQ1Percent;
                }
                if (m_period > 0)
                {
                    compareQ3Percent = m_compare / (double)m_period * 100;
                    compareQ4Percent = compareQ3Percent;
                }

                // Don't draw anything if non-valid initial values
                if (IsMoreThan100Percent(compareQ1Percent) || IsMoreThan100Percent(compareQ2Percent) ||
                    IsMoreThan100Percent(compareQ3Percent) || IsMoreThan100Percent(compareQ4Percent))
                {
                    return;
                }

                compareQ1 = GetPercentPosition(compareQ1Percent, Start, Quarter1);
                compareQ2 = GetPercentPosition(100 - compareQ2Percent, Quarter1, Center); 
                compareQ3 = GetPercentPosition(compareQ3Percent, Center, Quarter3);
                compareQ4 = GetPercentPosition(100 - compareQ4Percent, Quarter3, End);

                if (m_deadTime > 0)
                {
                    //
                    // PWM calculations
                    //
                    byte quarterDt = 0;
                    // Q1 deadtime percent
                    dtQ1PercentPwm = compareQ1Percent + m_deadtimePercentPeriod0;
                    if (dtQ1PercentPwm > 100)
                        dtQ1PercentPwm = 100;
    
                    // Q2 deadtime percent
                    // Do not take into account 1st quarter deadtime
                    if (m_period0 > 0)
                    {
                        quarterDt = (m_deadTime >= m_period0 - m_compare0) ? (byte)(m_deadTime - (m_period0 - m_compare0)) : (byte)0;
                        dtQ2PercentPwm = (quarterDt > 0) ? (quarterDt) / (double)m_period0 * 100 : 1;
                        if (dtQ2PercentPwm > 100)
                            dtQ2PercentPwm = 100;
                    }

                    // Q3 deadtime percent
                    if (m_period > 0)
                    {
                        dtQ3PercentPwm = (m_deadTime + m_compare) / (double)m_period * 100;
                        if (dtQ3PercentPwm > 100)
                            dtQ3PercentPwm = 100;
                    }

                    // Q4 deadtime percent
                    // Do not take into account Q1-Q3 quarter deadtimes
                    if (m_period > 0)
                    {
                        quarterDt = (m_deadTime >= (m_period - m_compare)) ? (byte)(m_deadTime - ((m_period - m_compare))) : (byte)0;
                        dtQ4PercentPwm = (quarterDt > 0) ? (quarterDt) / (double)m_period * 100 : 1;
                        if (dtQ4PercentPwm > 100)
                            dtQ4PercentPwm = 100;
                    }
                    
                    //
                    // PWM_n calculations
                    //
                    // Q1 deadtime percent
                    dtQ1PercentPwmN = m_deadtimePercentPeriod0;
                    if (dtQ1PercentPwmN > 100)
                        dtQ1PercentPwmN = 100;

                    // Q2 deadtime percent
                    if (m_period0 > 0)
                    {
                        dtQ2PercentPwmN = 100 - (m_compare0 / (double)m_period0 * 100) + (m_deadTime / (double)m_period0 * 100);
                        if (dtQ2PercentPwmN > 100)
                            dtQ2PercentPwmN = 100;
                    }

                    // Q3 deadtime percent
                    // Do not take into account Q1-Q2 quarter deadtimes
                    if (m_period > 0)
                    {
                        quarterDt = (m_deadTime >= m_compare0) ? (byte)(m_deadTime - (m_compare0)) : (byte)0;
                        dtQ3PercentPwmN = quarterDt / (double)m_period * 100;
                        if (dtQ3PercentPwmN > 100)
                            dtQ3PercentPwmN = 100;
                    }

                    // Q4 deadtime percent
                    if (m_period > 0)
                    {
                        dtQ4PercentPwmN = 100 - (m_compare / (double)m_period * 100) + (m_deadTime / (double)m_period * 100);
                        if (dtQ4PercentPwmN > 100)
                            dtQ4PercentPwmN = 100;
                    }

                    // If duty cycle = 0% or 100% then Dead time has no impact on PWM
                    if (IgnoreDeadTime(compareQ1Percent))
                    {
                        ignoreQ1Q2deadTime = true;
                    }
                    if (IgnoreDeadTime(compareQ3Percent))
                    {
                        ignoreQ3Q4deadTime = true;
                    }
                }
            }
            else // ASSYMETRIC
            {
                if (m_period0 > 0)
                {
                    compareQ1Percent = m_compare0 / (double)m_period0 * 100;
                    compareQ2Percent = m_compare / (double)m_period0 * 100;
                }
                if (m_period > 0)
                {
                    compareQ3Percent = m_compare0 / (double)m_period * 100;
                    compareQ4Percent = m_compare / (double)m_period * 100;
                }

                // Don't draw anything if non-valid initial values
                if (IsMoreThan100Percent(compareQ1Percent) || IsMoreThan100Percent(compareQ2Percent) ||
                    IsMoreThan100Percent(compareQ3Percent) || IsMoreThan100Percent(compareQ4Percent))
                {
                    return;
                }

                compareQ1 = GetPercentPosition(compareQ1Percent, Start, Quarter1);
                compareQ2 = GetPercentPosition(100 - compareQ2Percent, Quarter1, Center);
                compareQ3 = GetPercentPosition(compareQ3Percent, Center, Quarter3);
                compareQ4 = GetPercentPosition(100 - compareQ4Percent, Quarter3, End);

                if (m_deadTime > 0)
                {
                    //
                    // PWM calculations
                    //
                    byte quarterDt = 0;
                    // Q1 deadtime percent
                    dtQ1PercentPwm = compareQ1Percent + m_deadtimePercentPeriod0;
                    if (dtQ1PercentPwm > 100)
                        dtQ1PercentPwm = 100;

                    // Q2 deadtime percent
                    // Do not take into account 1st quarter deadtime
                    if (m_period0 > 0)
                    {
                        quarterDt = (m_deadTime >= m_period0 - m_compare0) ? (byte)(m_deadTime - (m_period0 - m_compare0)) : (byte)0;
                        dtQ2PercentPwm = (quarterDt > 0) ? (quarterDt) / (double)m_period0 * 100 : 1;
                        if (dtQ2PercentPwm > 100)
                            dtQ2PercentPwm = 100;
                    }

                    // Q3 deadtime percent
                    if (m_period > 0)
                    {
                        dtQ3PercentPwm = (m_deadTime + m_compare0) / (double)m_period * 100;
                        if (dtQ3PercentPwm > 100)
                            dtQ3PercentPwm = 100;
                    }

                    // Q4 deadtime percent
                    // Do not take into account Q1-Q3 quarter deadtimes
                    if (m_period > 0)
                    {
                        quarterDt = (m_deadTime >= (m_period - m_compare0)) ? (byte)(m_deadTime - ((m_period - m_compare0))) : (byte)0;
                        dtQ4PercentPwm = (quarterDt > 0) ? (quarterDt) / (double)m_period * 100 : 1;
                        if (dtQ4PercentPwm > 100)
                            dtQ4PercentPwm = 100;
                    }

                    //
                    // PWM_n calculations
                    //
                    // Q1 deadtime percent
                    dtQ1PercentPwmN = m_deadtimePercentPeriod0;
                    if (dtQ1PercentPwmN > 100)
                        dtQ1PercentPwmN = 100;

                    // Q2 deadtime percent
                    if (m_period0 > 0)
                    {
                        dtQ2PercentPwmN = 100 - (m_compare / (double)m_period0 * 100) + (m_deadTime / (double)m_period0 * 100);
                        if (dtQ2PercentPwmN > 100)
                            dtQ2PercentPwmN = 100;
                    }

                    // Q3 deadtime percent
                    if (m_period > 0)
                    {
                        quarterDt = (m_deadTime >= m_compare) ? (byte)(m_deadTime - (m_compare)) : (byte)0;
                        dtQ3PercentPwmN = quarterDt / (double)m_period * 100;
                        if (dtQ3PercentPwmN > 100)
                            dtQ3PercentPwmN = 100;
                    }

                    // Q4 deadtime percent
                    if (m_period > 0)
                    {
                        dtQ4PercentPwmN = 100 - (m_compare / (double)m_period * 100) + (m_deadTime / (double)m_period * 100);
                        if (dtQ4PercentPwmN > 100)
                            dtQ4PercentPwmN = 100;
                    }

                    // If duty cycle = 0% or 100% then Dead time has no impact on PWM
                    if (IgnoreDeadTime(compareQ1Percent) && IgnoreDeadTime(compareQ2Percent))
                    {
                        ignoreQ1Q2deadTime = true;
                    }
                    if (IgnoreDeadTime(compareQ3Percent) && IgnoreDeadTime(compareQ4Percent))
                    {
                        ignoreQ3Q4deadTime = true;
                    }
                }
            }

            if (m_deadTime > 0) // Common for Central and Assymetric
            {
                //
                // PWM (deadtime > 0)
                //

                // X coordinate of deadtime on the 1st quarter
                int q1dt = GetPercentPosition(dtQ1PercentPwm, Start, Quarter1);
                if (q1dt > Quarter1)
                    q1dt = Quarter1;
                // X coordinate of deadtime on the 2nd quarter
                int q2dt = GetPercentPosition(dtQ2PercentPwm, Quarter1, Center);
                if (q2dt > Center)
                    q2dt = Center;
                // X coordinate of deadtime on the 3rd quarter
                int q3dt = GetPercentPosition(dtQ3PercentPwm, Center, Quarter3);
                if (q3dt > Quarter3)
                    q3dt = Quarter3;
                // X coordinate of deadtime on the 4th quarter
                int q4dt = GetPercentPosition(dtQ4PercentPwm, Quarter3, End);
                if (q4dt > End)
                    q4dt = End;

                // Q1-Q2
                if (ignoreQ1Q2deadTime)
                {
                    pwmSegments.Add(new CySegment(0, Start, compareQ1));
                    pwmSegments.Add(new CySegment(1, compareQ1, Quarter1));
                    pwmSegments.Add(new CySegment(1, Quarter1, compareQ2));
                    pwmSegments.Add(new CySegment(0, compareQ2, Center));
                }
                else if (q1dt < Quarter1)
                {
                    // Q1
                    pwmSegments.Add(new CySegment(0, Start, q1dt));
                    pwmSegments.Add(new CySegment(1, q1dt, Quarter1));
                    // Q2
                    pwmSegments.Add(new CySegment(1, Quarter1, compareQ2));
                    pwmSegments.Add(new CySegment(0, compareQ2, Center));
                }
                else if (q2dt < compareQ2)
                {
                    // Q1
                    pwmSegments.Add(new CySegment(0, Start, Quarter1));
                    pwmSegments.Add(new CySegment(0, Quarter1, q2dt));
                    // Q2
                    pwmSegments.Add(new CySegment(1, q2dt, compareQ2));
                    pwmSegments.Add(new CySegment(0, compareQ2, Center));
                }
                else
                {
                   // Q1-Q2
                    pwmSegments.Add(new CySegment(0, Start, Center)); 
                }

                // Q3-Q4
                if (ignoreQ3Q4deadTime)
                {
                    pwmSegments.Add(new CySegment(0, Center, compareQ3));
                    pwmSegments.Add(new CySegment(1, compareQ3, Quarter3));
                    pwmSegments.Add(new CySegment(1, Quarter3, compareQ4));
                    pwmSegments.Add(new CySegment(0, compareQ4, End));
                }
                else if (q3dt < Quarter3)
                {
                    // Q3
                    pwmSegments.Add(new CySegment(0, Center, q3dt));
                    pwmSegments.Add(new CySegment(1, q3dt, Quarter3));
                    // Q4
                    pwmSegments.Add(new CySegment(1, Quarter3, compareQ4));
                    pwmSegments.Add(new CySegment(0, compareQ4, End));
                }
                else if (q4dt <= compareQ4)
                {
                    // Q3
                    pwmSegments.Add(new CySegment(0, Center, Quarter3));
                    // Q4    
                    pwmSegments.Add(new CySegment(0, Quarter3, q4dt));
                    pwmSegments.Add(new CySegment(1, q4dt, compareQ4));
                    pwmSegments.Add(new CySegment(0, compareQ4, End));

                }
                else
                {
                    pwmSegments.Add(new CySegment(0, Center, End));
                }

                //
                // PWM_n (deadtime > 0)
                //

                // X coordinate of deadtime on the 1st quarter
                q1dt = GetPercentPosition(dtQ1PercentPwmN, Start, Quarter1);
                if (q1dt > Quarter1)
                    q1dt = Quarter1;
                // X coordinate of deadtime on the 2nd quarter
                q2dt = GetPercentPosition(dtQ2PercentPwmN, Quarter1, Center);
                if (q2dt > Center)
                    q2dt = Center;
                // X coordinate of deadtime on the 3rd quarter
                q3dt = GetPercentPosition(dtQ3PercentPwmN, Center, Quarter3);
                if (q3dt > Quarter3)
                    q3dt = Quarter3;
                // X coordinate of deadtime on the 4th quarter
                q4dt = GetPercentPosition(dtQ4PercentPwmN, Quarter3, End);
                if (q4dt > End)
                    q4dt = End;

                // Q1-Q2
                if (ignoreQ1Q2deadTime)
                {
                    pwmNSegments.Add(new CySegment(1, Start, compareQ1));
                    pwmNSegments.Add(new CySegment(0, compareQ1, Quarter1));
                    pwmNSegments.Add(new CySegment(0, Quarter1, compareQ2));
                    pwmNSegments.Add(new CySegment(1, compareQ2, Center));
                }
                else if (q1dt < compareQ1)
                {
                    // Q1
                    pwmNSegments.Add(new CySegment(0, Start, q1dt));
                    pwmNSegments.Add(new CySegment(1, q1dt, compareQ1));
                    pwmNSegments.Add(new CySegment(0, compareQ1, Quarter1));
                    // Q2
                    pwmNSegments.Add(new CySegment(0, Quarter1, q2dt));
                    pwmNSegments.Add(new CySegment(1, q2dt, Center));
                }
                else if (q2dt < Center)
                {
                    // Q1
                    pwmNSegments.Add(new CySegment(0, Start, Quarter1));
                    // Q2
                    pwmNSegments.Add(new CySegment(0, Quarter1, q2dt));
                    pwmNSegments.Add(new CySegment(1, q2dt, Center));
                }
                else
                {
                    // Q1-Q2
                    pwmNSegments.Add(new CySegment(0, Start, Center));
                }

                // Q3-Q4
                if (ignoreQ3Q4deadTime)
                {
                    pwmNSegments.Add(new CySegment(1, Center, compareQ3));
                    pwmNSegments.Add(new CySegment(0, compareQ3, Quarter3));
                    pwmNSegments.Add(new CySegment(0, Quarter3, compareQ4));
                    pwmNSegments.Add(new CySegment(1, compareQ4, End));
                }
                else if (q3dt < compareQ3)
                {
                    // Q3
                    pwmNSegments.Add(new CySegment(0, Center, q3dt));
                    pwmNSegments.Add(new CySegment(1, q3dt, compareQ3));
                    pwmNSegments.Add(new CySegment(0, compareQ3, Quarter3));
                    // Q4
                    pwmNSegments.Add(new CySegment(0, Quarter3, q4dt));
                    pwmNSegments.Add(new CySegment(1, q4dt, End));
                }
                else if (q4dt < End)
                {
                    // Q3
                    pwmNSegments.Add(new CySegment(0, Center, Quarter3));
                    // Q4
                    pwmNSegments.Add(new CySegment(0, Quarter3, q4dt));
                    pwmNSegments.Add(new CySegment(1, q4dt, End));
                }
                else
                {
                    // Q3-Q4
                    pwmNSegments.Add(new CySegment(0, Center, End));
                }
            }
            else // m_deadTime == 0
            {
                //
                // PWM (deadtime = 0)
                //
                // Left part
                pwmSegments.Add(new CySegment(0, Start, compareQ1));
                pwmSegments.Add(new CySegment(1, compareQ1, Quarter1));
                pwmSegments.Add(new CySegment(1, Quarter1, compareQ2));
                pwmSegments.Add(new CySegment(0, compareQ2, Center));
        
                // Right part
                pwmSegments.Add(new CySegment(0, Center, compareQ3));
                pwmSegments.Add(new CySegment(1, compareQ3, Quarter3));
                pwmSegments.Add(new CySegment(1, Quarter3, compareQ4));
                pwmSegments.Add(new CySegment(0, compareQ4, End));

                //
                // PWM_n (deadtime = 0)
                //
                // Left part
                pwmNSegments.Add(new CySegment(1, Start, compareQ1));
                pwmNSegments.Add(new CySegment(0, compareQ1, Quarter1));
                pwmNSegments.Add(new CySegment(0, Quarter1, compareQ2));
                pwmNSegments.Add(new CySegment(1, compareQ2, Center));
                
                // Right part
                pwmNSegments.Add(new CySegment(1, Center, compareQ3));
                pwmNSegments.Add(new CySegment(0, compareQ3, Quarter3));
                pwmNSegments.Add(new CySegment(0, Quarter3, compareQ4));
                pwmNSegments.Add(new CySegment(1, compareQ4, End));
            }
        }

        private int GetPercentPosition(double percent, int start, int end)
        {
            if (percent < 0) percent = 0;
            if (percent > 100) percent = 100;
            int pixelMargin = (IsPercent0(percent) || IsPercent100(percent)) ? 0 : 1;
            return (int)Math.Round(start + pixelMargin + (end - start - 2 * pixelMargin) * (percent / 100));
        }

        private bool IsPercent100(double value)
        {
            return Math.Abs(value - 100) < CyMath.EPS;
        }

        private bool IsPercent0(double value)
        {
            return Math.Abs(value) < CyMath.EPS;
        }

        private bool IsMoreThan100Percent(double value)
        {
            return value > 100 + CyMath.EPS;
        }

        private bool IgnoreDeadTime(double comparePercent)
        {
            return IsPercent0(comparePercent) || IsPercent100(comparePercent) ||
                   (comparePercent < 0) || (comparePercent > 100);
        }
    }
}
