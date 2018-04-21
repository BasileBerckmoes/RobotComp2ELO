/*******************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Drawing;

namespace Comp_P4_v1_20
{
    internal class CyImage : IDisposable
    {
        public const int START_X = 40;
        public const int END_X = 400;

        #region Input parameters fields
        public CyEHysteresisType m_hysteresis = CyEHysteresisType.CMP_ENABLE_HYST;
        public CyEPolarityType m_polarity;
        public CyEInterruptType m_interrupt = CyEInterruptType.INTR_BOTH;
        public CyEPowerType m_power;
        #endregion Input parameters fields

        #region Image related fields
        public Size m_imageSize;
        public Bitmap m_bmp;
        #endregion Image related fields

        #region Private fields
        private bool m_isDisposed = false;
        #endregion Private fields

        #region Constructor(s)
        public CyImage()
        {
            m_imageSize = new Size(100, 100);
        }
        #endregion Constructor(s)

        #region Dispose
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!m_isDisposed)
            {
                if (disposing)
                {
                    if (m_bmp != null)
                        m_bmp.Dispose();
                }
            }
            m_isDisposed = true;
        }
        #endregion Dispose

        #region Update image
        /// <summary>
        /// This function draws the symbol that is displayed on the right side of the window.
        /// </summary>
        public void UpdateSymbol()
        {
            m_bmp = new Bitmap(m_imageSize.Width, m_imageSize.Height);
            int triangleLeft = m_imageSize.Width / 5;
            int triangleRight = m_imageSize.Width - triangleLeft;
            int triangleSide = (int) ((triangleRight - triangleLeft) / Math.Cos(Math.PI / 6));
            int triangleTop = m_imageSize.Height / 2 - triangleSide / 2;
            int triangleBottom = triangleTop + triangleSide;
            int plusY = triangleTop + triangleSide / 3;
            int minusY = triangleTop + 2 * triangleSide / 3;
            int plusCenterX = triangleLeft + triangleSide / 6;
            int plusW = (plusCenterX - triangleLeft) * 4 / 3;
            int hystLeft = triangleLeft + (plusCenterX - triangleLeft) * 2;
            int hystW = plusW / 3;

            Pen pen = new Pen(Color.Black, 1);
            Pen penPlus = new Pen(Color.Black, 2);
            Pen penWire = new Pen(Color.FromArgb(0, 0, 128), 1);
            Brush brushAqua = Brushes.Aqua;
            Brush brushWhite = Brushes.White;

            using (Graphics g = Graphics.FromImage(m_bmp))
            {
                g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
                g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.AntiAlias;

                // triangle
                Point[] pts = new Point[3];
                pts[0] = new Point(triangleLeft, triangleTop);
                pts[1] = new Point(triangleLeft, triangleBottom);
                pts[2] = new Point(triangleRight, triangleTop + triangleSide / 2);
                g.FillPolygon(brushAqua, pts);
                g.DrawPolygon(pen, pts);

                // lines
                g.DrawLine(penWire, new Point(0, plusY), new Point(triangleLeft, plusY));
                g.DrawLine(penWire, new Point(0, minusY), new Point(triangleLeft, minusY));
                g.DrawLine(penWire, new Point(triangleRight, triangleTop + triangleSide / 2),
                    new Point(m_imageSize.Width, triangleTop + triangleSide / 2));

                // plus, minus
                g.DrawLine(penPlus, new Point(plusCenterX - plusW / 2, plusY),
                    new Point(plusCenterX + plusW / 2, plusY));
                g.DrawLine(penPlus, new Point(plusCenterX, plusY - plusW / 2),
                    new Point(plusCenterX, plusY + plusW / 2));
                g.DrawLine(penPlus, new Point(plusCenterX - plusW / 2, minusY),
                    new Point(plusCenterX + plusW / 2, minusY));

                // invert
                if (m_polarity == CyEPolarityType.CMP_INVERTING)
                {
                    g.FillEllipse(brushWhite, pts[2].X, pts[2].Y - triangleLeft / 4, triangleLeft / 2,
                        triangleLeft / 2);
                    g.DrawEllipse(pen, pts[2].X, pts[2].Y - triangleLeft / 4, triangleLeft / 2, triangleLeft / 2);
                }

                // hysteresis
                if (m_hysteresis == CyEHysteresisType.CMP_ENABLE_HYST)
                {
                    g.DrawLine(pen, new Point(hystLeft, plusY), new Point(hystLeft + hystW * 2, plusY));
                    g.DrawLine(pen, new Point(hystLeft + hystW, minusY), new Point(hystLeft + hystW * 3, minusY));
                    g.DrawLine(pen, new Point(hystLeft + hystW, plusY), new Point(hystLeft + hystW, minusY));
                    g.DrawLine(pen, new Point(hystLeft + 2 * hystW, plusY), new Point(hystLeft + 2 * hystW, minusY));
                }
            }
            pen.Dispose();
            penPlus.Dispose();
            penWire.Dispose();
        }

        /// <summary>
        /// This function draws a graph that is displayed at the bottom of the window.
        /// </summary>
        public void UpdateGraph()
        {
            m_bmp = new Bitmap(m_imageSize.Width, m_imageSize.Height);
            Size defSize = new Size(410, 210);
            float scaleX = m_imageSize.Width / (float)defSize.Width;
            float scaleY = m_imageSize.Height / (float)defSize.Height;
            int waveShift = 9;
            int interruptShift = 15;

            const int START_Y = 10;
            const int VDDA_Y = 20;
            const int HYST_Y = 45;
            const int VMIN_Y = 50;
            const int VPLUS_Y = 70;
            const int OV_Y = 75;
            const int DASH_START_Y = 35;
            const int DASH_END_Y = 96;

            const int BLUE_W = (END_X - START_X) / 4;
            const int BLUE_CROSS_X = (int)(BLUE_W * ((float)(VPLUS_Y - VMIN_Y) / (VPLUS_Y - VDDA_Y)));
            const int BLUE_CROSS_HYST_X = (int)(BLUE_W * ((float)(VPLUS_Y - HYST_Y) / (VPLUS_Y - VDDA_Y)));
            const int HYST_TEXT_X = 45;
            const int HYST_ARR_H = 15;
            const int WAVE_Y1 = 100;
            const int WAVE_Y2 = 140;
            const int WAVE_Y3 = 160;
            const int WAVE_Y4 = 200;

            using (Graphics g = Graphics.FromImage(m_bmp))
            {
                g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
                g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.AntiAlias;

                g.ScaleTransform(scaleX, scaleY);

                g.Clear(Color.White);
                Brush blkbrush = Brushes.Black;
                Brush greenbrush = Brushes.Green;
                Brush bluebrush = Brushes.Blue;
                Brush orangebrush = Brushes.Orange;
                Pen extentspen = new Pen(blkbrush);
                Pen greenpen = new Pen(greenbrush);
                Pen bluepen = new Pen(bluebrush);
                Pen orangepen = new Pen(orangebrush);
                extentspen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;
                // Setup the input wave 
                g.DrawLine(extentspen, START_X, VDDA_Y, END_X, VDDA_Y);
                g.DrawLine(greenpen, START_X, VMIN_Y, END_X, VMIN_Y);
                g.DrawLine(extentspen, START_X, OV_Y, END_X, OV_Y);
                extentspen.DashStyle = System.Drawing.Drawing2D.DashStyle.Solid;
                g.DrawLine(extentspen, START_X, START_Y, START_X, m_imageSize.Height);

                // blue line
                Point[] bluePts = new Point[5];
                for (int i = 0; i < bluePts.Length; i++)
                {
                    bluePts[i].Y = (i % 2 == 0) ? VPLUS_Y : VDDA_Y;
                    bluePts[i].X = START_X + i * BLUE_W;
                }
                g.DrawLines(bluepen, bluePts);

                // hysteresis horizontal line
                if (m_hysteresis == CyEHysteresisType.CMP_ENABLE_HYST)
                {
                    g.DrawLine(greenpen, START_X, HYST_Y, END_X, HYST_Y);

                    extentspen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;
                    extentspen.StartCap = System.Drawing.Drawing2D.LineCap.ArrowAnchor;
                    g.DrawLine(extentspen, HYST_TEXT_X, HYST_Y, HYST_TEXT_X, HYST_Y - HYST_ARR_H);
                    g.DrawLine(extentspen, HYST_TEXT_X, VMIN_Y, HYST_TEXT_X, VMIN_Y + HYST_ARR_H);

                    using (Font arrow = new Font("Arial", 10, FontStyle.Regular, GraphicsUnit.Pixel))
                    {
                        g.DrawString("10mV", arrow, blkbrush, HYST_TEXT_X, HYST_Y - HYST_ARR_H);
                    }
                    extentspen.StartCap = System.Drawing.Drawing2D.LineCap.Flat;
                }

                int[] ptsLineX = new int[8];
                int[] ptsWave1X = new int[8];
                int[] ptsWave2X = new int[8];

                // dash vertical
                extentspen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;
                for (int i = 0; i < 4; i++)
                {
                    int shift = (m_hysteresis == CyEHysteresisType.CMP_ENABLE_HYST) ? BLUE_CROSS_HYST_X : BLUE_CROSS_X;
                    int crossX = (i % 2 == 0) ? bluePts[i].X + shift : bluePts[i + 1].X - BLUE_CROSS_X;
                    g.DrawLine(extentspen, crossX, DASH_START_Y, crossX, DASH_END_Y);
                    ptsLineX[i * 2] = crossX;
                    ptsLineX[i * 2 + 1] = crossX;
                    ptsWave1X[i * 2] = crossX;
                    ptsWave1X[i * 2 + 1] = crossX;
                    ptsWave2X[i * 2] = crossX;
                    ptsWave2X[i * 2 + 1] = crossX;
                }
                g.DrawLines(bluepen, bluePts);

                // output square wave
                List<Point> wavePts = new List<Point>();
                List<Point> wavePtsOut = new List<Point>();
                List<Point> wavePtsIntOut = new List<Point>();

                if (m_power == CyEPowerType.CMP_LOW_POWER)
                {
                    waveShift += 3;
                    interruptShift += 3;
                }
                else if (m_power == CyEPowerType.CMP_HIGH_POWER)
                {
                    waveShift = 0;
                }


                if (m_polarity == CyEPolarityType.CMP_INVERTING)
                    wavePtsOut = UpdateHWOut(ptsLineX, WAVE_Y2, WAVE_Y1, waveShift, 0);
                else
                    wavePtsOut = UpdateHWOut(ptsLineX, WAVE_Y1, WAVE_Y2, waveShift, 0);

                g.DrawLines(orangepen, wavePtsOut.ToArray());

                // Draw Int out
                wavePtsIntOut = UpdateHWOutIntOut(ptsWave2X, WAVE_Y4, WAVE_Y3, waveShift, interruptShift, m_interrupt);

                g.DrawLines(orangepen, wavePtsIntOut.ToArray());

                const int TXT_X = 7;
                const int TXT_LONG_X = 2;
                const int TXT_VX = 17;
                const int TXT_Y_START = 95;
                const int TXT_STEP_Y = 20;
                const int TXT_H = 10;

                Font perfont = new Font("Arial", 10, FontStyle.Regular, GraphicsUnit.Pixel);
                g.DrawString("Vdda", perfont, blkbrush, new PointF(TXT_X, VDDA_Y - TXT_H));
                g.DrawString("0V", perfont, blkbrush, new PointF(TXT_VX, VPLUS_Y));
                g.DrawString("Vddd", perfont, blkbrush, new PointF(TXT_X, TXT_Y_START));
                g.DrawString("Vssd", perfont, blkbrush, new PointF(TXT_X, TXT_Y_START + 2 * TXT_STEP_Y));
                g.DrawString("Vddd", perfont, blkbrush, new PointF(TXT_X, TXT_Y_START + 3 * TXT_STEP_Y));
                g.DrawString("Vssd", perfont, blkbrush, new PointF(TXT_X, TXT_Y_START + 5 * TXT_STEP_Y));
                g.DrawString("V+", perfont, bluebrush, new PointF(TXT_VX, VPLUS_Y - TXT_H));
                g.DrawString("V-", perfont, greenbrush, new PointF(TXT_VX, VMIN_Y - TXT_H));
                g.DrawString("HW out", perfont, orangebrush, new PointF(TXT_LONG_X, TXT_Y_START + TXT_STEP_Y));
                g.DrawString("Int out", perfont, orangebrush, new PointF(TXT_LONG_X, TXT_Y_START + 4 * TXT_STEP_Y));

                perfont.Dispose();
                extentspen.Dispose();
                greenpen.Dispose();
                bluepen.Dispose();
                orangepen.Dispose();

                g.ResetTransform();
            }
        }

        private static List<Point> UpdateHWOut(int[] ptsLineX, int waveY1, int waveY2, int waveShift, int offset)
        {
            List<Point> wavePts = new List<Point>();
            wavePts.Add(new Point(START_X, waveY2));

            for (int i = 0; i < ptsLineX.Length; i++)
            {
                int y = waveY2;
                int x = ptsLineX[i] + offset;
                if ((i % 4 == 1) || (i % 4 == 2))
                {
                    y = waveY1;
                }
                x += (i % 2 == 0) ? -waveShift : waveShift;

                wavePts.Add(new Point(x, y));
            }
            wavePts.Add(new Point(END_X, waveY2));
            return wavePts;
        }

        private static List<Point> UpdateHWOutIntOut(int[] ptsWaveX, int YLow, int YHight, int waveShift, int intShift, 
            CyEInterruptType interr)
        {
            List<Point> wavePts = new List<Point>();
            wavePts.Add(new Point(START_X, YLow));

            for (int i = 0; i < ptsWaveX.Length; i++)
            {
                int y = YLow;
                int x = ptsWaveX[i];
                x += (i % 2 == 0) ? (-waveShift) : (waveShift);
                if ((i % 4 == 1) &&
                    ((interr == CyEInterruptType.INTR_RISING) ||
                     (interr == CyEInterruptType.INTR_BOTH)))
                {
                    y = YHight;
                    wavePts.Add(new Point(x, y));
                    x += intShift;
                    wavePts.Add(new Point(x - waveShift, y));
                    wavePts.Add(new Point(x + waveShift, YLow));
                }
                else if ((i % 4 == 2) &&
                        ((interr == CyEInterruptType.INTR_FALLING) ||
                         (interr == CyEInterruptType.INTR_BOTH)))
                {
                    y = YLow;
                    wavePts.Add(new Point(x, y));
                    x += 2 * waveShift;
                    wavePts.Add(new Point(x, YHight));
                    x += intShift - waveShift;
                    wavePts.Add(new Point(x, YHight));
                }
                else if (i % 4 == 3)
                {
                    x += intShift + waveShift;
                    y = YLow;
                    wavePts.Add(new Point(x, y));
                }
                else
                {
                    wavePts.Add(new Point(x, y));
                }
            }
            wavePts.Add(new Point(Math.Max(END_X, wavePts[wavePts.Count - 1].X), YLow));

            return wavePts;
        }
        #endregion Update image
    }
}
