/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Drawing;

namespace CSD_Comp_P4_v1_0
{
    internal class CyImage : IDisposable
    {
        public const int START_X = 40;
        public const int END_X = 400;

        #region Input parameters fields

        private CyEnumSpeedType m_speed;

        public CyEnumSpeedType Speed
        {
            get { return m_speed; }
            set { m_speed = value; }
        }

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
        /// This function draws a graph that is displayed at the bottom of the window.
        /// </summary>
        public void UpdateGraph()
        {
            m_bmp = new Bitmap(m_imageSize.Width, m_imageSize.Height);
            Size defSize = new Size(410, 160);
            float scaleX = m_imageSize.Width / (float)defSize.Width;
            float scaleY = m_imageSize.Height / (float)defSize.Height;
            int waveShift = 9;

            const int START_Y = 10;
            const int VDDA_Y = 20;
            const int VMIN_Y = 50;
            const int VPLUS_Y = 70;
            const int OV_Y = 75;
            const int DASH_START_Y = 35;
            const int DASH_END_Y = 96;

            const int BLUE_W = (END_X - START_X) / 4;
            const int BLUE_CROSS_X = (int)(BLUE_W * ((float)(VPLUS_Y - VMIN_Y) / (VPLUS_Y - VDDA_Y)));
            const int WAVE_Y1 = 100;
            const int WAVE_Y2 = 140;

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
                g.DrawLine(extentspen, START_X, START_Y, START_X, defSize.Height - START_Y);

                // blue line
                Point[] bluePts = new Point[5];
                for (int i = 0; i < bluePts.Length; i++)
                {
                    bluePts[i].Y = (i % 2 == 0) ? VPLUS_Y : VDDA_Y;
                    bluePts[i].X = START_X + i * BLUE_W;
                }
                g.DrawLines(bluepen, bluePts);

                int[] ptsLineX = new int[8];
                int[] ptsWave1X = new int[8];
                int[] ptsWave2X = new int[8];

                // dash vertical
                extentspen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;
                for (int i = 0; i < 4; i++)
                {
                    int shift = BLUE_CROSS_X;
                    int crossX = (i % 2 == 0) ? bluePts[i].X + shift : 
                        bluePts[i + 1].X - BLUE_CROSS_X;
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

                if (Speed  == CyEnumSpeedType.SLOW_SPEED)
                {
                    waveShift += 3;
                }
                else if (Speed == CyEnumSpeedType.FAST_SPEED)
                {
                    waveShift = 0;
                }

                wavePtsOut = UpdateHWOut(ptsLineX, WAVE_Y1, WAVE_Y2, waveShift, 0);

                g.DrawLines(orangepen, wavePtsOut.ToArray());

                const int TXT_X = 7;
                const int TXT_VX = 17;
                const int TXT_Y_START = 95;
                const int TXT_STEP_Y = 20;
                const int TXT_H = 10;

                Font perfont = new Font("Arial", 10, FontStyle.Regular, GraphicsUnit.Pixel);
                g.DrawString("Vdda", perfont, blkbrush, new PointF(TXT_X, VDDA_Y - TXT_H));
                g.DrawString("0V", perfont, blkbrush, new PointF(TXT_VX, VPLUS_Y));
                g.DrawString("Vddd", perfont, blkbrush, new PointF(TXT_X, TXT_Y_START));
                g.DrawString("Vssd", perfont, blkbrush, new PointF(TXT_X, TXT_Y_START + 2 * TXT_STEP_Y));
                g.DrawString("V+", perfont, bluebrush, new PointF(TXT_VX, VPLUS_Y - TXT_H));
                g.DrawString("Vref", perfont, greenbrush, new PointF(TXT_X + 4 , VMIN_Y - TXT_H));
                g.DrawString("Out", perfont, orangebrush, new PointF(TXT_X + 4, TXT_Y_START + TXT_STEP_Y));

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
                int y = ((i % 4 == 1) || (i % 4 == 2)) ? waveY1 : waveY2;
                int x = ptsLineX[i] + offset;
                x += (i % 2 == 0) ? -waveShift : waveShift;

                wavePts.Add(new Point(x, y));
            }
            wavePts.Add(new Point(END_X, waveY2));
            return wavePts;
        }

        private static List<Point> UpdateHWOutIntOut(int[] ptsWaveX, int YLow, int YHight, int waveShift, int intShift)
        {
            List<Point> wavePts = new List<Point>();
            wavePts.Add(new Point(START_X, YLow));

            for (int i = 0; i < ptsWaveX.Length; i++)
            {
                int y = YLow;
                int x = ptsWaveX[i];
                x += (i % 2 == 0) ? (-waveShift) : (waveShift);
                
                if (i % 4 == 3)
                {
                    x += intShift + waveShift;
                    y = YLow;
                }

                wavePts.Add(new Point(x, y));
            }
            wavePts.Add(new Point(Math.Max(END_X, wavePts[wavePts.Count - 1].X), YLow));

            return wavePts;
        }
        #endregion Update image
    }
}
