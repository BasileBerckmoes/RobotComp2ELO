/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using System.Drawing.Text;

namespace WaveDAC8_v2_10
{
    public partial class CyWaveformChart : UserControl
    {
        #region Const
        private static readonly string[] FREQUENCY_UNITS = { "Hz", "kHz", "MHz" };
        private static readonly string[] PERIOD_UNITS = { "s", "ms", "us", "ns" };
        #endregion Const

        #region Coordinates
        const float L_TEXT_MARGIN = 40.0F;
        const float MARGIN_PERCENT = 0.04F;
        const float TOP_MARGIN_PERCENT = 0.1F;
        const int HALF_ARROW_HEIGHT = 4;
        const int ARROW_WIDTH = HALF_ARROW_HEIGHT * 2;

        float MarginXPercent
        { get { return this.Width * MARGIN_PERCENT; }  }

        float MarginYPercent
        { get { return this.Height * MARGIN_PERCENT; } }

        float MarginTopPercent
        { get { return this.Height * TOP_MARGIN_PERCENT; } }

        int LeftMargin
        { get { return (int)(Math.Round(L_TEXT_MARGIN + MarginXPercent)); } }

        int RightMargin
        { get { return (int)(Math.Round(this.Width - MarginXPercent)); } }

        int TopMargin
        { get { return (int)(Math.Round(MarginTopPercent)); } }

        int HalfTopMargin
        { get { return TopMargin / 2; } }

        int BottomMargin
        { get { return (int)(Math.Round(this.Height - MarginYPercent)); } }

        int MiddleX
        { get { return LeftMargin + (RightMargin - LeftMargin) / 2; } }

        float StepW 
        { get { return (MiddleX - LeftMargin) / (float)m_values.Count; } }

        float StepH 
        { get { return (BottomMargin - TopMargin) / (float)CyParamConst.MAX_DATA_VALUE; } }

        #endregion Coordinates

        #region Fields
        private CyWaveRange m_range = new CyWaveRange();
        private List<byte> m_values = new List<byte>();
        private bool m_mousedown = false;

        public CyParameters m_parameters;
        public int m_waveformNumber;

        private UInt32 m_sps = 0;

        private Bitmap m_bmpBackground;
        private Bitmap m_bmpWaveform;
        #endregion Fields

        #region General Properties
        public List<byte> DataValues
        {
            get { return m_values; }
            set { m_values = value; }
        }

        private bool Arbitrary
        {
            get { return m_parameters.GetWaveType(m_waveformNumber) == CyEWaveFormType.ArbitraryDraw; }
        }

        public UInt32 SPS
        {
            get { return m_sps; } 
            set { m_sps = value; } 
        }

        public void SetWaveRange(CyWaveRange waveRange)
        {
            m_range = waveRange;
        }
        #endregion General Properties

        #region ArbWaveChanged Event
        /// <summary>
        ///  The event ArbWaveChanged occurs when user draws an arbitrary waveform
        /// </summary> 
        public event EventHandler<CyArbWaveChangedEventArgs> ArbWaveChanged;

        private void OnArbWaveChange(List<byte> data)
        {
            EventHandler<CyArbWaveChangedEventArgs> handler = ArbWaveChanged;
            if (handler != null)
            {
                CyArbWaveChangedEventArgs args = new CyArbWaveChangedEventArgs();
                args.Data = data;
                handler(this, args);
            }
        }
        #endregion ArbWaveformChanged Event

        #region Constructor
        public CyWaveformChart(int waveformNumber, CyParameters parameters)
        {
            m_parameters = parameters;
            m_waveformNumber = waveformNumber;

            m_bmpBackground = new Bitmap(this.Width, this.Height);
            m_bmpWaveform = new Bitmap(this.Width, this.Height);

            this.TabStop = false;
            this.DoubleBuffered = true;

            this.Load += CyWaveformChart_Load;
            this.SizeChanged += CyWaveformChart_SizeChanged;

            this.MouseDown += OnMouseDown;
            this.MouseUp += OnMouseUp;
            this.MouseMove += OnMouseMove;
            this.MouseLeave += OnMouseLeave;
        }
        #endregion Constructor
        
        #region Background and graph draw
        private void RedrawBackgroundBitmap()
        {
            m_bmpBackground = new Bitmap(this.Width, this.Height);

            using (Graphics g = Graphics.FromImage(m_bmpBackground))
            {
                g.FillRectangle(Brushes.White, 0, 0, m_bmpBackground.Width, m_bmpBackground.Height);

                int halfWidth = MiddleX - LeftMargin;
                int heightAfterMargins = BottomMargin - TopMargin;
                int middleY = TopMargin + (BottomMargin - TopMargin) / 2;

                // Fill right half with grayish background 
                g.FillRectangle(Brushes.LightGray, MiddleX, TopMargin, halfWidth, heightAfterMargins);

                // Draw left, right, and middle vertical lines 
                using (Pen penBlackWide = new Pen(Color.Black, 2))
                {
                    g.DrawLine(penBlackWide, LeftMargin, HalfTopMargin, LeftMargin, BottomMargin);
                    g.DrawLine(penBlackWide, RightMargin, HalfTopMargin, RightMargin, BottomMargin);
                }
                g.DrawLine(Pens.Black, MiddleX, HalfTopMargin, MiddleX, BottomMargin);
                // Draw top, bottom, and middle horizontal lines 
                g.DrawLine(Pens.Black, LeftMargin, BottomMargin, RightMargin, BottomMargin);
                g.DrawLine(Pens.Black, LeftMargin, TopMargin - 1, RightMargin, TopMargin - 1);
                g.DrawLine(Pens.Gray, LeftMargin, middleY, RightMargin, middleY);

                // Draw Voltage Strings 
                DrawAxisLabel(g, m_range.MaxRange, TopMargin, StringAlignment.Center);
                DrawAxisLabel(g, m_range.MaxRange / 2, middleY, StringAlignment.Center);
                DrawAxisLabel(g, 0, BottomMargin, StringAlignment.Far);

                double period = -1;
                double frequency = -1;
                if (SPS != 0)
                {
                    period = m_values.Count * (1.0 / Convert.ToDouble(SPS));
                    frequency = 1.0 / period;
                }

                String periodStr = String.Format(cywavedacresource.LabelChartPeriod, 
                                                 ConvertToUnitsStr(period, PERIOD_UNITS, false));
                String frequencyStr = String.Format(cywavedacresource.LabelChartFrequency, 
                                                    ConvertToUnitsStr(frequency, FREQUENCY_UNITS, true));
                SizeF pstrsize = g.MeasureString(periodStr, this.Font);
                SizeF fstrsize = g.MeasureString(frequencyStr, this.Font);

                // Draw Arrows
                PointF[] ptsL1 = DrawArrowEnd(g, LeftMargin, true);
                PointF[] ptsL2 = DrawArrowEnd(g, MiddleX, true);
                PointF[] ptsR1 = DrawArrowEnd(g, MiddleX, false);
                PointF[] ptsR2 = DrawArrowEnd(g, RightMargin, false);

                PointF perStrPt = new PointF((float)(LeftMargin + (halfWidth / 2.0) - (pstrsize.Width / 2.0)), 0);
                PointF freqStrPt = new PointF((float)(RightMargin - (halfWidth / 2.0) - (fstrsize.Width / 2.0)), 0);
                Brush textBrush = Brushes.Black;
                g.DrawString(periodStr, this.Font, textBrush, perStrPt);
                g.DrawString(frequencyStr, this.Font, textBrush, freqStrPt);

                // Draw arrows lines
                DrawArrowLine(g, ptsL1[0], new PointF((float)(perStrPt.X - HALF_ARROW_HEIGHT), HalfTopMargin));
                DrawArrowLine(g, new PointF((float)(perStrPt.X + pstrsize.Width + HALF_ARROW_HEIGHT), HalfTopMargin), 
                                 ptsR1[0]);
                DrawArrowLine(g, ptsL2[0], new PointF((float)(freqStrPt.X - HALF_ARROW_HEIGHT), HalfTopMargin));
                DrawArrowLine(g, new PointF((float)(freqStrPt.X + fstrsize.Width + HALF_ARROW_HEIGHT), HalfTopMargin), 
                                 ptsR2[0]);
            }
        }

        private PointF[] DrawArrowEnd(Graphics g, int xBaseCoord, bool isLeft)
        {
            Brush arrowBrush = Brushes.DarkGray;
            PointF[] pts = new PointF[3];
            int xCoord2 = xBaseCoord;
            xCoord2 += isLeft ? (ARROW_WIDTH) : (-ARROW_WIDTH);
            pts[0] = new PointF(xBaseCoord, HalfTopMargin);
            pts[1] = new PointF(xCoord2, HalfTopMargin - HALF_ARROW_HEIGHT);
            pts[2] = new PointF(xCoord2, HalfTopMargin + HALF_ARROW_HEIGHT);
            g.FillPolygon(arrowBrush, pts);
            return pts;
        }

        private void DrawArrowLine(Graphics g, PointF startPt, PointF endPt)
        {
            // Draw line only if first x coord is less than second
            Pen arrowPen = Pens.DarkGray;
            if (startPt.X < endPt.X)
                g.DrawLine(arrowPen, startPt, endPt);
        }

        private void DrawAxisLabel(Graphics g, double value, float yCoord, StringAlignment align)
        {
            string text = m_range.GetFormattedValueStr(value);
            Brush brush = Brushes.Black;

            SizeF textSize = g.MeasureString(text, this.Font);
            float fontSize = textSize.Width < LeftMargin ? this.Font.Size : this.Font.Size - 1.2f;

            using (Font font = new Font(this.Font.FontFamily, fontSize))
            {
                textSize = g.MeasureString(text, font);
                int offset = 2;
                float yShift = (align == StringAlignment.Center) ? (textSize.Height / 2) : textSize.Height;
                PointF point = new PointF(LeftMargin - textSize.Width - offset, yCoord - yShift);

                g.DrawString(text, font, brush, point);
            }
        }

        private void RedrawWaveformBitmap()
        {
            // Calculate the size of drawing region
            float canvasWidth = MiddleX - LeftMargin;
            float canvasHeight = BottomMargin - TopMargin;

            m_bmpWaveform = new Bitmap((int)canvasWidth, (int)canvasHeight);

            using (Graphics g = Graphics.FromImage(m_bmpWaveform))
            {
                ToHighQuality(g);

                if (m_values.Count != 0)
                {
                    List<PointF> points = new List<PointF>();

                    for (int i = 0; i < m_values.Count; i++)
                    {
                        float startx = (i * StepW);
                        float endx = startx + StepW;
                        float y = canvasHeight - (m_values[i] * StepH);
                        points.Add(new PointF(startx, y));
                        points.Add(new PointF(endx, y));
                    }
                    // Add connecting line between two waveforms
                    points.Add(new PointF(points[points.Count - 1].X, points[0].Y));

                    using (Pen wavepen = new Pen(Color.Red, 1.5f))
                    {
                        wavepen.StartCap = LineCap.Round;
                        wavepen.EndCap = LineCap.Round;

                        g.DrawLines(wavepen, points.ToArray());
                    }
                }
            }
        }
        #endregion Background and graph draw

        #region Arbitrary draw
        Point m_lastAddedArbPoint;
        bool m_lastAddedArbPointValid = true;
        /// <summary>
        /// Updates data based on mouse coordinates in arbitrary draw mode
        /// </summary>
        /// <param name="e">Mouse location</param>
        /// <param name="approximate">Defines if points that were left untouched between two MouseMove events 
        /// should be approximated</param>
        private void AddArbitraryStates(MouseEventArgs e, bool approximate)
        {
            if (Arbitrary == false) return;
            
            // If mouse coordinates are inside drawing region
            if ((e.X >= LeftMargin) && (e.X <= MiddleX) && (e.Y >= TopMargin) && (e.Y <= BottomMargin))
            {
                // List of points indexes that are affected by the given pixel
                List<int> ptIndexList = new List<int>();
                int ptIndex = (int)Math.Round((e.X - LeftMargin) / StepW);
                ptIndexList.Add(ptIndex);
                float tempStepW = StepW;
                // Add other points that correspond current x pixel coord
                while (tempStepW < 1)
                {
                    ptIndex = ++ptIndex;
                    ptIndexList.Add(ptIndex);
                    tempStepW += StepW;
                }

                // Y value of point
                byte yval = (byte)Math.Round((BottomMargin - e.Y) / StepH);

                // Approximation of points that were lost between MouseMove events
                if (approximate && m_lastAddedArbPointValid && ptIndexList.Count > 0)
                {
                    // If the difference between last and current point indexes is greater than 1, 
                    // approximate points in between
                    if ((m_lastAddedArbPoint.X < ptIndexList[0] - 1) || 
                        (m_lastAddedArbPoint.X > ptIndexList[ptIndexList.Count - 1] + 1))
                    {
                        // Choose the first and last points for approximation depending on the direction of mouse move 
                        // (left to right or right to left)
                        int first = Math.Min(m_lastAddedArbPoint.X, ptIndexList[0] - 1);
                        int last = Math.Max(m_lastAddedArbPoint.X, ptIndexList[0] - 1);
                        
                        if (m_lastAddedArbPoint.X > ptIndexList[ptIndexList.Count - 1] + 1)
                        {
                            first = Math.Min(m_lastAddedArbPoint.X, ptIndexList[ptIndexList.Count - 1] + 1);
                            last = Math.Max(m_lastAddedArbPoint.X, ptIndexList[ptIndexList.Count - 1] + 1);
                        }
                        // Approximate by linear function
                        double yStep = (yval - m_lastAddedArbPoint.Y) / (double)(last - first);
                        for (int i = 0; i <= last - first; i++)
                        {
                            byte yAppr = (byte)Math.Round(i * yStep + m_lastAddedArbPoint.Y);
                            m_values[first + i] = yAppr;
                        }
                    }
                }

                for (int i = 0; i < ptIndexList.Count; i++)
                {
                    if (ptIndexList[i] >= 0 && ptIndexList[i] < m_values.Count)
                    {
                        m_values[ptIndexList[i]] = yval;
                        m_lastAddedArbPoint = new Point(ptIndexList[i], m_values[ptIndexList[i]]);
                        m_lastAddedArbPointValid = true;
                    }
                }
                RefreshChart();
            }
            else
            {
               m_lastAddedArbPointValid = false;
            }
        }

        void OnMouseDown(object sender, MouseEventArgs e)
        {
            if (Arbitrary && e.Button == MouseButtons.Left)
            {
                m_mousedown = true;
                AddArbitraryStates(e, false);
            }
        }

        void OnMouseMove(object sender, MouseEventArgs e)
        {
            if (Arbitrary && m_mousedown)
            {
                AddArbitraryStates(e, true);
            }
        }

        void OnMouseUp(object sender, MouseEventArgs e)
        {
            if (Arbitrary && m_mousedown)
                OnArbWaveChange(DataValues);
            m_mousedown = false;
            m_lastAddedArbPointValid = false;
        }

        void OnMouseLeave(object sender, EventArgs e)
        {
            if (m_mousedown)
            {
                OnMouseUp(sender, new MouseEventArgs(MouseButtons, 0, MousePosition.X, MousePosition.Y, 0));
            }
        }
        #endregion Arbitrary draw

        #region Event handlers
        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            
            Graphics g = e.Graphics;
            g.DrawImage(m_bmpBackground, new PointF(0, 0));
            g.DrawImage(m_bmpWaveform,new PointF(LeftMargin,TopMargin));
            g.DrawImage(m_bmpWaveform,new PointF(MiddleX,TopMargin));
        }

        void CyWaveformChart_Load(object sender, EventArgs e)
        {
            RefreshAll();
        }

        void CyWaveformChart_SizeChanged(object sender, EventArgs e)
        {
            RefreshAll();
        }
        #endregion Event handlers

        #region Private functions
        /// <summary>
        /// This function converts value to appropriate units for display (for example, 1000000 Hz -> 1 MHz)
        /// </summary>
        /// <param name="value">Input value</param>
        /// <param name="unitsTable">Array of units (strings)</param>
        /// <param name="reduceZero">Defines if the initial value is greater or lower than 1. 
        /// If value is greater than 1, the number of zeros should be reduced.</param>
        /// <returns>Formatted string</returns>
        private static string ConvertToUnitsStr(double value, string[] unitsTable, bool reduceZero)
        {
            if (value < 0)
                return cywavedacresource.UnknownStr;

            int unitsIndex = 0;
            if (reduceZero)
            {
                while ((value >= CyParamConst.THOUSAND) && (unitsIndex < unitsTable.Length - 1))
                {
                    value /= CyParamConst.THOUSAND;
                    unitsIndex++;
                }
            }
            else
            {
                while ((value < 1) && (unitsIndex < unitsTable.Length - 1))
                {
                    value *= CyParamConst.THOUSAND;
                    unitsIndex++;
                }
            }

            return String.Format("{0:f3} {1}", value, unitsTable[unitsIndex]);
        }

        /// <summary>
        /// Apply high quality settings to graphics
        /// </summary>
        public static void ToHighQuality(Graphics graphics)
        {
            graphics.InterpolationMode = InterpolationMode.HighQualityBicubic;
            graphics.CompositingQuality = CompositingQuality.HighQuality;
            graphics.SmoothingMode = SmoothingMode.HighQuality;
            graphics.TextRenderingHint = TextRenderingHint.ClearTypeGridFit;
            graphics.PixelOffsetMode = PixelOffsetMode.HighQuality;
        }

        /// <summary>
        /// Redraw only graph
        /// </summary>
        public void RefreshChart()
        {
            RedrawWaveformBitmap(); 
            Invalidate();
        }

        /// <summary>
        /// Redraw everything
        /// </summary>
        public void RefreshAll()
        {
            RedrawBackgroundBitmap();
            RedrawWaveformBitmap();
            Invalidate();
        }
        #endregion Private functions
    }

    public class CyArbWaveChangedEventArgs : EventArgs
    {
        private List<byte> m_data;
        public List<byte> Data 
        { 
            get { return m_data; } 
            set { m_data = value; } 
        }
    }
}
