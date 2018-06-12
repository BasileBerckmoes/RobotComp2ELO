/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System.Drawing;
using System.Diagnostics;
using TCPWM_PWM_PDL_v1_0.Utils;

namespace TCPWM_PWM_PDL_v1_0.Waveform
{
    internal class CyPeriodArrows : CyWaveform
    {
        private CyEnums.CyMode m_mode;
        private CyEnums.CyAlignment m_alignment;
        private uint m_period0;
        private uint m_period1;
        private bool m_periodSwap;

        private CyPeriodArrows(Graphics g, Size size) : base(g, size)
        {
        }

        public CyPeriodArrows(Graphics g, Size size,
            CyEnums.CyMode mode, CyEnums.CyAlignment alignment, uint period0, uint period1, bool periodSwap)
            : this(g, size)
        {
            m_mode = mode;
            m_alignment = alignment;
            m_period0 = period0;
            m_period1 = period1;
            m_periodSwap = periodSwap;
        }

        public override void Draw()
        {
            string text1 = "";
            string text2 = "";
            if (m_mode == CyEnums.CyMode.MODE_PSEUDORANDOM)
            {
                // draw left waveform period arrow
                text1 = "1";
                text2 = m_period0.ToString();
                DrawPeriodLine(Start, Center, text1, text2);
                DrawDashLine(Center);

                // draw right waveform period arrow
                if (m_periodSwap)
                {
                    text2 = m_period1.ToString();
                }
                DrawPeriodLine(Center, End, text1, text2);
            }
            else
            {
                switch (m_alignment)
                {
                    case CyEnums.CyAlignment.LEFT:
                        // draw left waveform period arrow
                        text1 = "0";
                        text2 = m_period0.ToString();
                        DrawPeriodLine(Start, Center, text1, text2);
                        DrawDashLine(Center);

                        // draw right waveform period arrow
                        if (m_periodSwap)
                        {
                            text2 = m_period1.ToString();
                        }
                        DrawPeriodLine(Center, End, text1, text2);
                        break;
                    case CyEnums.CyAlignment.RIGHT:
                        // draw left waveform period arrow
                        text1 = m_period0.ToString();
                        text2 = "0";
                        DrawPeriodLine(Start, Center, text1, text2);
                        DrawDashLine(Center);

                        // draw right waveform period arrow
                        if (m_periodSwap)
                        {
                            text1 = m_period1.ToString();
                        }
                        DrawPeriodLine(Center, End, text1, text2);
                        break;
                    case CyEnums.CyAlignment.CENTER:
                    case CyEnums.CyAlignment.ASYMMETRIC:
                        // draw left waveform period arrow
                        text1 = "0";
                        text2 = m_period0.ToString();
                        DrawPeriodLine(Start, Quarter1, "1", text2);
                        DrawDashLine(Quarter1);
                        //if (m_alignment == CyEnums.CyAlignment.ASYMMETRIC)
                        //{
                        //    text2 = (m_periodSwap ? m_period1 : m_period0).ToString();
                        //}
                        DrawPeriodLine(Quarter1, Center, text2, text1);
                        DrawDashLine(Center);

                        // draw right waveform period arrow
                        text2 = /*(m_alignment == CyEnums.CyAlignment.ASYMMETRIC)
                            ? m_period0.ToString()
                            : */(m_periodSwap ? m_period1 : m_period0).ToString();
                        DrawPeriodLine(Center, Quarter3, "1", text2);
                        DrawDashLine(Quarter3);
                        text2 = (m_periodSwap ? m_period1 : m_period0).ToString();
                        DrawPeriodLine(Quarter3, End, text2, text1);
                        break;
                    default:
                        Debug.Fail("unhandled enum item.");
                        break;
                }
            }
        }

        private void DrawPeriodLine(int x1, int x2, string text1, string text2)
        {
            DrawCapLine(x1, x2, PERIOD_LINE_Y, text1, text2);
        }
    }
}
