/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Drawing;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

namespace TCPWM_QuadDec_PDL_v1_0.Controls
{
    public class CyWaveform : UserControl
    {
        private Bitmap m_backBuffer;
        private Graphics m_graphics;
        private Pen m_pen;
        private int m_clockWidth;
        private int m_clockHeight;
        private int m_abSignalLen;
        private int m_noiseWidth;
        private int m_baseX;
        private byte m_counterRes;
        private bool m_useIndex;

        public CyWaveform()
        {
            m_backBuffer = new Bitmap(Width, Height);
            m_graphics = Graphics.FromImage(m_backBuffer);

            InitializeComponent();

            DoubleBuffered = true;
            Font = new Font(FontFamily.GenericSansSerif, 13, FontStyle.Regular);
            m_pen = new Pen(Brushes.Black, 2);
            m_clockWidth = 5;
            m_clockHeight = 13;
            m_abSignalLen = 12;
            m_noiseWidth = 5;
            m_baseX = 60;
            m_counterRes = 4;
        }

        #region Properties
        public byte CounterResolution
        {
            get { return m_counterRes; }
            set { m_counterRes = (value == 1 || value == 2 || value == 4) ? value : (byte)0; }
        }

        public bool UseIndexInput
        {
            get { return m_useIndex; }
            set { m_useIndex = value; }
        }
        #endregion

        private void DrawStep(Point basePoint, int ticks, bool inverse, bool noisy)
        {
            GraphicsPath step = new GraphicsPath();
            Point topLeftPoint = new Point(
                noisy ? basePoint.X + m_noiseWidth : basePoint.X,
                inverse ? basePoint.Y + m_clockHeight : basePoint.Y - m_clockHeight);
            Point topRightPoint = new Point(
                topLeftPoint.X + m_clockWidth * ticks,
                topLeftPoint.Y);
            Point bottomPoint = new Point(
                noisy ? basePoint.X + m_clockWidth * ticks + m_noiseWidth * 2 : basePoint.X + m_clockWidth * ticks,
                basePoint.Y);
            Point endPoint = new Point(
                basePoint.X + m_clockWidth * 2 * ticks,
                basePoint.Y);

            step.AddLine(basePoint, topLeftPoint);
            step.AddLine(topLeftPoint, topRightPoint);
            step.AddLine(topRightPoint, bottomPoint);
            step.AddLine(bottomPoint, endPoint);

            m_graphics.DrawPath(m_pen, step);
        }

        private void DrawSignal(Point startPoint, int startTick, int stepLen)
        {
            Point basePoint = new Point(m_clockWidth * 2 * startTick, startPoint.Y);
            int clockStep = stepLen * m_clockWidth * 2;
            int stepCount = Width / clockStep;

            m_graphics.DrawLine(m_pen, startPoint, basePoint);

            for (int i = 0; i < stepCount; i++)
            {
                DrawStep(basePoint, stepLen, false, false);
                basePoint.Offset(clockStep, 0);
            }
        }

        private void DrawCounterSignal(Point startPoint, int startTick)
        {
            Point basePoint = new Point(m_clockWidth * 2 * startTick, startPoint.Y);
            int stepCount = Width / (2 * m_clockWidth * 2);

            Point endStepPoint;
            if (m_counterRes != 2)
            {
                m_graphics.DrawLine(m_pen, startPoint, basePoint);

                for (int i = 0; i < stepCount; i++)
                {
                    DrawStep(basePoint, 2, false, false);
                    endStepPoint = new Point(basePoint.X + 4 * m_clockWidth, basePoint.Y);
                    basePoint.Offset(m_clockWidth * 2 * m_abSignalLen / m_counterRes, 0);
                    m_graphics.DrawLine(m_pen, endStepPoint, basePoint);
                }
            }
            else
            {
                basePoint = new Point(basePoint.X, startPoint.Y);
                int xOffset = m_clockWidth * 12;
                m_graphics.DrawLine(m_pen, startPoint, basePoint);
                for (int i = 0; i < stepCount; i++)
                {
                    DrawStep(basePoint, 2, false, false);
                    endStepPoint = new Point(basePoint.X + 4 * m_clockWidth, basePoint.Y);
                    basePoint.Offset(xOffset, 0);
                    m_graphics.DrawLine(m_pen, endStepPoint, basePoint);

                    DrawStep(basePoint, 2, false, false);
                    endStepPoint = new Point(basePoint.X + 4 * m_clockWidth, basePoint.Y);
                    basePoint.Offset(xOffset, 0);
                    m_graphics.DrawLine(m_pen, endStepPoint, basePoint);
                }
            }
        }

        private void DrawIndex(Point startPoint, int startTick)
        {
            Point basePoint = new Point(m_clockWidth * 2 * startTick, startPoint.Y);
            Point bottomPoint = new Point(basePoint.X + m_clockWidth * 6, basePoint.Y);
            Point endPoint = new Point(Width, bottomPoint.Y);

            m_graphics.DrawLine(m_pen, startPoint, basePoint);
            DrawStep(basePoint, 6, true, false);
            m_graphics.DrawLine(m_pen, bottomPoint, endPoint);

            int resetLen = (m_abSignalLen / 4) * m_clockWidth + (int)m_pen.Width;

            Pen circledPen = new Pen(Color.Red);
            Point circledPoint = new Point(basePoint.X - m_clockWidth * 6, m_clockHeight / 2);
            Rectangle circledRect = new Rectangle(circledPoint,
                new Size(resetLen * 6, circledPoint.Y + bottomPoint.Y + m_clockHeight / 2));
            circledPen.DashStyle = DashStyle.Dash;
            circledPen.Width = 2;
            m_graphics.DrawEllipse(circledPen, circledRect);
        }

        private void DrawString(String text, Point signalBasePoint)
        {
            float baseY = signalBasePoint.Y;
            SizeF textSize = m_graphics.MeasureString(text, Font);
            PointF textPoint = new PointF(signalBasePoint.X - textSize.Width - 5, baseY - textSize.Height);

            m_graphics.FillRectangle(Brushes.White, new RectangleF(textPoint, textSize));
            m_graphics.DrawString(text, Font, Brushes.Black, textPoint);
        }

        private void DrawClock()
        {
            int baseY = m_clockHeight * 2;
            Point basePoint = new Point(m_baseX, baseY);

            DrawString("Clock", basePoint);
            DrawSignal(basePoint, 10, 1);
        }

        private void DrawB()
        {
            int baseY = m_clockHeight * 4;
            Point basePoint = new Point(m_baseX, baseY);

            DrawString("B", basePoint);
            DrawSignal(basePoint, 15, m_abSignalLen);
        }

        private void DrawA()
        {
            int baseY = m_clockHeight * 6;
            Point basePoint = new Point(m_baseX, baseY);

            DrawString("A", basePoint);
            DrawSignal(basePoint, 18, m_abSignalLen);
        }

        private void DrawIndex()
        {
            if (m_useIndex)
            {
                int baseY = m_clockHeight * 7;
                Point basePoint = new Point(m_baseX, baseY);
                Point basePointForString = new Point(basePoint.X, basePoint.Y + m_clockHeight);

                DrawString("Index", basePointForString);
                DrawIndex(basePoint, 36);
            }
        }

        private void DrawCounter()
        {
            const int START_TICK = 16;
            int baseY = CalcCounterBaseY();
            Point basePoint = new Point(m_baseX, baseY);

            DrawString(m_counterRes.ToString() + "x", basePoint);
            DrawCounterSignal(basePoint, START_TICK);
        }

        private int CalcCounterBaseY()
        {
            return m_useIndex ? m_clockHeight * 10 : m_clockHeight * 8;
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            m_clockHeight = m_useIndex ? Height / 11 : Height / 9;
            m_clockWidth = Width >= 92 ? Width / 92 : 1;
            m_backBuffer = new Bitmap(Width, Height);
            m_graphics = Graphics.FromImage(m_backBuffer);

            DrawClock();
            DrawB();
            DrawA();
            DrawIndex();
            if (m_counterRes != 0) { DrawCounter(); }

            e.Graphics.DrawImageUnscaled(m_backBuffer, 0, 0);

            base.OnPaint(e);
        }

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
            float fontSize;
            fontSize = (m_clockHeight > 0 && m_clockHeight < 12) ? m_clockHeight : 11;
            Font = new Font(Font.FontFamily, fontSize * 96 / m_graphics.DpiX, Font.Style);
            Refresh();
        }

        #region Generated code
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                m_backBuffer.Dispose();
                m_graphics.Dispose();
                m_pen.Dispose();

                components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void InitializeComponent()
        {
            this.SuspendLayout();
            // 
            // CyDiagram
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Name = "CyDiagram";
            this.Size = new System.Drawing.Size(458, 171);
            this.ResumeLayout(false);
        }
        #endregion
    }
}
