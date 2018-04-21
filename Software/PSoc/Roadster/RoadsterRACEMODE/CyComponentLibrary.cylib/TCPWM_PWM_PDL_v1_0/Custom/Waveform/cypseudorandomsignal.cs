/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System.Drawing;
using System.Collections.Generic;
using TCPWM_PWM_PDL_v1_0.Utils;

namespace TCPWM_PWM_PDL_v1_0.Waveform
{
    internal class CyPseudoRandomSignal : CyWaveform
    {
        private uint m_period0;
        private uint m_period1;
        private bool m_periodSwap;
        private uint m_compare0;
        private uint m_compare1;
        private bool m_compareSwap;
        private CyEnums.CyResolution m_resolution;

        private CyPseudoRandomSignal(Graphics g, Size size) : base(g, size)
        {
        }

        public CyPseudoRandomSignal(Graphics g, Size size,
            uint period0, uint period1, bool periodSwap, uint compare0, uint compare1, bool compareSwap, CyEnums.CyResolution resolution)
            : this(g, size)
        {
            m_period0 = period0;
            m_period1 = period1;
            m_periodSwap = periodSwap;
            m_compare0 = compare0;
            m_compare1 = compare1;
            m_compareSwap = compareSwap;
            m_resolution = resolution;
        }

        public override void Draw()
        {
            //
            // Pseudo-random mode. Left waveform
            //
            // pwm
            int x1 = SignalX;
            int x2 = (RightEdgeLineX - x1) / 2 + x1;
            byte[] signal = GetPseudoRandomSignal(m_period0, m_compare0, m_resolution);
            DrawSignal(signal, x1, x2, CySignalDock.Top);
            // pwm_n
            byte[] invertedSignal = InvertSignal(signal);
            DrawSignal(invertedSignal, x1, x2, CySignalDock.Bottom);

            //
            // Pseudo-random mode. Right waveform
            //
            uint period;
            uint compare;
            SelectActualPeriodAndCompare(m_period0, m_period1, m_compare0, m_compare1, m_periodSwap, m_compareSwap,
                out period, out compare);
            signal = GetPseudoRandomSignal(period, compare, m_resolution);
            // pwm
            x1 = x2;
            x2 = RightEdgeLineX;
            DrawSignal(signal, x1, x2, CySignalDock.Top);
            // pwm_n
            invertedSignal = InvertSignal(signal);
            DrawSignal(invertedSignal, x1, x2, CySignalDock.Bottom);
        }

        /// <summary>
        /// Gets array of bits sequence, which represent signal in pseudo-random mode.
        /// </summary>
        private static byte[] GetPseudoRandomSignal(uint period, uint compare, CyEnums.CyResolution resolution)
        {
            const byte MAX_STAGE_COUNT = 45;
            uint counter = 1;

            // 002-10927 Rev. *A. Section 4.5.2.8.6.1 PWM_PR mode functionality overview
            List<byte> signal = new List<byte>() { (byte)counter };
            for (int i = 0; i < MAX_STAGE_COUNT; i++)
            {
                if (resolution == CyEnums.CyResolution.WIDTH_16_BITS)
                {
                    uint temp = ((counter >> 5) & 1) ^ ((counter >> 3) & 1) ^ ((counter >> 2) & 1) ^ ((counter >> 0) & 1);
                    counter = ((temp << 15) | (counter >> 1));
                    signal.Add((byte)(((counter & 0x7FFF) < compare) ? 1 : 0));
                }
                else
                {
                    uint temp = ((counter >> 7) & 1) ^ ((counter >> 6) & 1) ^ ((counter >> 2) & 1) ^ ((counter >> 0) & 1);
                    counter = ((temp << 31) | (counter >> 1));
                    signal.Add((byte)(((counter & 0x7FFFFFFF) < compare) ? 1 : 0));
                }
            }
            return signal.ToArray();
        }

        /// <summary>
        /// Inverts array of bits.
        /// </summary>
        private static byte[] InvertSignal(byte[] signal)
        {
            byte[] invertedSignal = new byte[signal.Length];
            for (int i = 0; i < signal.Length; i++)
            {
                invertedSignal[i] = (byte)(signal[i] == 1 ? 0 : 1);
            }

            return invertedSignal;
        }
    }
}
