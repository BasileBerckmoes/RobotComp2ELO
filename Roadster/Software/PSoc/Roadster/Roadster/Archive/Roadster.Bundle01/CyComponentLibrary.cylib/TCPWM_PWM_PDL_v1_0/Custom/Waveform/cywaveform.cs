/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Drawing;
using System.Diagnostics;
using System.Drawing.Drawing2D;
using System.Collections.Generic;
using CyDesigner.Toolkit;

namespace TCPWM_PWM_PDL_v1_0.Waveform
{
    internal abstract class CyWaveform : IDisposable
    {
        protected const int LEFT_EDGE_LINE_X = 50;
        protected const int EDGE_LINE_WIDTH = 7;
        protected const int SIGNAL_X = LEFT_EDGE_LINE_X + EDGE_LINE_WIDTH;
        protected const int PERIOD_LINE_Y = 2;
        protected const int SIGNALS_DISTANCE = 5;

        protected Graphics m_g;

        /// <summary>
        /// X coordinate of left vertical edge line.
        /// </summary>
        public int LeftEdgeLineX { get { return LEFT_EDGE_LINE_X; } }

        /// <summary>
        ///  X coordinate of right vertical edge line.
        /// </summary>
        public int RightEdgeLineX { get; private set; }

        /// <summary>
        /// X coordinate where the signal line starts.
        /// </summary>
        public int SignalX { get { return SIGNAL_X; } }

        /// <summary>
        /// Waveform image size.
        /// </summary>
        public Size Size { get; set; }

        /// <summary>
        /// Number of points between edges.
        /// </summary>
        public int Diff { get; protected set; }

        /// <summary>
        /// Start point of the waveform.
        /// </summary>
        public int Start { get; protected set; }

        /// <summary>
        /// X coordinate of the end of 1st quarter.
        /// </summary>
        public int Quarter1 { get; protected set; }

        /// <summary>
        /// Center point of the waveform.
        /// </summary>
        public int Center { get; protected set; }

        /// <summary>
        /// X coordinate of the end of 3rd quarter.
        /// </summary>
        public int Quarter3 { get; protected set; }

        /// <summary>
        /// End point of the waveform.
        /// </summary>
        public int End { get; protected set; }

        /// <summary>
        /// Area where the signal is drawing.
        /// </summary>
        private Rectangle SignalArea
        {
            get { return new Rectangle(SIGNAL_X, 22, RightEdgeLineX - SIGNAL_X, Size.Height - 9); }
        }

        public CyWaveform(Graphics g, Size size)
        {
            m_g = g;
            Size = size;
            RightEdgeLineX = size.Width - EDGE_LINE_WIDTH - 5;
            CyGraphicsUtils.MakeHighQualityForDrawing(m_g);

            // Waveform sections coordinates
            Diff = RightEdgeLineX - SignalX;
            Start = SignalX;
            Quarter1 = Start + Diff / 4;
            Center = Start + Diff / 2;
            Quarter3 = Center + Diff / 4;
            End = Start + Diff;
        }

        public abstract void Draw();

        public void DrawDashLine(int x)
        {
            using (Pen dashPen = new Pen(Color.Black))
            {
                dashPen.DashStyle = DashStyle.Dash;
                m_g.DrawLine(dashPen, x, 0, x, Size.Height);
            }
        }

        public void DrawCapLine(int x1, int x2, int y, string text1, string text2)
        {
            const byte TEXT_OFFSET = 10;
            int captionFontSize = m_g.DpiX == 96 && m_g.DpiY == 96 ? 13 : 10;
            using (Font captionFont = new Font("Arial", captionFontSize, FontStyle.Regular, GraphicsUnit.Pixel))
            {
                // Draw line
                SizeF text1Size = m_g.MeasureString(text1, captionFont);
                SizeF text2Size = m_g.MeasureString(text2, captionFont);
                using (Pen pen = new Pen(Color.Black))
                {
                    AdjustableArrowCap adjCap = new AdjustableArrowCap(4, 4, true);
                    pen.StartCap = LineCap.Custom;
                    pen.EndCap = LineCap.Custom;
                    pen.CustomStartCap = adjCap;
                    pen.CustomEndCap = adjCap;
                    int lineY = y + (int)(text1Size.Height / 2);
                    m_g.DrawLine(pen, x1, lineY, x2, lineY);
                }

                // Draw text near the both caps
                int captionX = x1 + TEXT_OFFSET;
                m_g.FillRectangle(Brushes.White, captionX, y, text1Size.Width, y + text1Size.Height);
                m_g.DrawString(text1, captionFont, Brushes.Black, captionX, y);
                captionX = x2 - (int)text2Size.Width - TEXT_OFFSET;
                m_g.FillRectangle(Brushes.White, captionX, y, text2Size.Width, y + text2Size.Height);
                m_g.DrawString(text2, captionFont, Brushes.Black, captionX, y);
            }
        }

        private void GetSignalYCoordinates(CySignalLevel signalLevel, CySignalDock dock, out int y1, out int y2)
        {
            y1 = 0;
            y2 = 0;
            Rectangle signalArea = SignalArea;
            switch (signalLevel)
            {
                case CySignalLevel.High:
                    switch (dock)
                    {
                        case CySignalDock.None:
                            y1 = signalArea.Y;
                            y2 = signalArea.Height;
                            break;
                        case CySignalDock.Top:
                            y1 = signalArea.Y;
                            y2 = (signalArea.Height - signalArea.Y) / 2 - SIGNALS_DISTANCE + signalArea.Y;
                            break;
                        case CySignalDock.Bottom:
                            y1 = (signalArea.Height - signalArea.Y) / 2 + SIGNALS_DISTANCE + signalArea.Y;
                            y2 = signalArea.Height;
                            break;
                        default:
                            Debug.Fail("unhandled enum item.");
                            break;
                    }
                    break;
                case CySignalLevel.Low:
                    switch (dock)
                    {
                        case CySignalDock.None:
                            y1 = signalArea.Height;
                            y2 = signalArea.Y;
                            break;
                        case CySignalDock.Top:
                            y1 = (signalArea.Height - signalArea.Y) / 2 - SIGNALS_DISTANCE + signalArea.Y;
                            y2 = signalArea.Y;
                            break;
                        case CySignalDock.Bottom:
                            y1 = signalArea.Height;
                            y2 = (signalArea.Height - signalArea.Y) / 2 + SIGNALS_DISTANCE + signalArea.Y;
                            break;
                        default:
                            Debug.Fail("unhandled enum item.");
                            break;
                    }
                    break;
                default:
                    Debug.Fail("unhandled enum item.");
                    break;
            }
        }

        public void DrawSignal(byte[] signals, int x1, int x2, CySignalDock dock = CySignalDock.None)
        {
            Rectangle signalArea = SignalArea;
            double signalWidth = signalArea.Width / 2 / (signals.Length);
            List<CySignal> signalGroups = new List<CySignal>();

            // Define the groups that consist from 0 or 1.
            // Using groups accelerates drawing and makes it more accurate 
            // because drawing is done by groups of pulses, not pulse by pulse
            uint signalCount = 1;
            byte currentBit = signals[0];
            for (int i = 1; i < signals.Length; i++)
            {
                if (signals[i] == currentBit)
                {
                    signalCount++;
                }
                else
                {
                    signalGroups.Add(new CySignal(signalCount, currentBit));
                    currentBit = signals[i];
                    signalCount = 1;
                }
            }

            // Add the last group of pulses. Minus one because we start counting from 0
            signalGroups.Add(new CySignal(--signalCount, currentBit));

            // Drawing
            int tmpx1 = x1;
            int tmpx2 = tmpx1;
            for (int i = 0; i < signalGroups.Count; i++)
            {
                CySignal item = signalGroups[i];

                // Define line x2 coordinate
                tmpx2 += (int)Math.Round(signalWidth * item.Count);

                // Define line Y coordinates
                int y1;
                int y2;

                CySignalLevel level = item.Level == 1 ? CySignalLevel.High : CySignalLevel.Low;
                GetSignalYCoordinates(level, dock, out y1, out y2);

                // Complete the last line so it reach center
                if (i == signalGroups.Count - 1)
                    tmpx2 = x2;

                // Draw horizontal line
                m_g.DrawLine(Pens.Blue, new Point(tmpx1, y1), new Point(tmpx2, y1));

                // Draw vertical line if it is not the last one
                if (i < signalGroups.Count - 1)
                    m_g.DrawLine(Pens.Blue, new Point(tmpx2, y1), new Point(tmpx2, y2));

                tmpx1 = tmpx2;
            }
        }

        public void DrawLabels()
        {
            using (Font perfont = new Font("Arial", m_g.DpiX == 96 && m_g.DpiY == 96 ? 13 : 10, FontStyle.Regular, GraphicsUnit.Pixel))
            {
                SizeF textSize = m_g.MeasureString("pwm_n", perfont); // align with the most longest text
                m_g.DrawString("period", perfont, Brushes.Black, (int)(LeftEdgeLineX - textSize.Width - 4), 2);
                m_g.DrawString("pwm", perfont, Brushes.Black, (int)(LeftEdgeLineX - textSize.Width - 4), Size.Height / 4);
                m_g.DrawString("pwm_n", perfont, Brushes.Black, (int)(LeftEdgeLineX - textSize.Width - 4), Size.Height - Size.Height / 4);
            }
        }

        public void DrawSegments(List<CySegment> segments, int highSignalY, int lowSignalY)
        {
            // Remove segments with zero length
            for (int i = 0; i < segments.Count; i++)
            {
                if (segments[i].X1 == segments[i].X2)
                    segments.RemoveAt(i--);
            }
            
            for (int i = 0; i < segments.Count; i++)
            {
                int y = segments[i].Level == 1 ? highSignalY : lowSignalY;
                m_g.DrawLine(Pens.Blue, new Point(segments[i].X1, y), new Point(segments[i].X2, y));

                if (i > 0)
                {
                    int yy = segments[i - 1].Level == 1 ? highSignalY : lowSignalY;
                    m_g.DrawLine(Pens.Blue, new Point(segments[i - 1].X2, yy), new Point(segments[i].X1, y));
                }
            }
        }

        protected static void SelectActualPeriodAndCompare(uint period0, uint period1, uint compare0, uint compare1,
            bool periodSwap, bool compareSwap, out uint period, out uint compare)
        {
            period = periodSwap ? period1 : period0;
            compare = compareSwap ? compare1 : compare0;
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                // dispose of managed disposable members
                m_g.Dispose();
            }
            // release unmanaged resources
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        ~CyWaveform()
        {
            Dispose(false);
        }
    }

    [DebuggerDisplay("Count = {Count}, Level = {Level}")]
    internal class CySignal
    {
        /// <summary>
        /// Represents group of bits.
        /// </summary>
        /// <param name="count">Number of bits.</param>
        /// <param name="level">Bit(s) level: 1 or 0.</param>
        public CySignal(uint count, byte level)
        {
            Count = count;
            Level = level;
        }

        /// <summary>
        /// Number of bits.
        /// </summary>
        public uint Count { get; set; }
        /// <summary>
        /// Bit(s) level: 1 or 0.
        /// </summary>
        public byte Level { get; set; }
    }

    public enum CySignalLevel
    {
        High,
        Low
    }

    public enum CySignalDock
    {
        None,
        Top,
        Bottom
    }

    public class CySignalPart
    {
        public int Percent { get; set; }
        public CySignalLevel Level { get; set; }

        public CySignalPart Clone()
        {
            CySignalPart inverted = new CySignalPart();
            inverted.Percent = this.Percent;
            inverted.Level = this.Level;
            return inverted;
        }
    }

    public class CySegment
    {
        byte m_level;
        int m_x1;
        int m_x2;

        private CySegment()
        {
        }

        public CySegment(byte level, int x1, int x2) : this()
        {
            m_level = level;
            m_x1 = x1;
            m_x2 = x2;
        }

        public byte Level
        {
            get { return m_level; }
            set { m_level = value; }
        }

        public int X1
        {
            get { return m_x1; }
            set { m_x1 = value; }
        }

        public int X2
        {
            get { return m_x2; }
            set { m_x2 = value; }
        }
    }
}
