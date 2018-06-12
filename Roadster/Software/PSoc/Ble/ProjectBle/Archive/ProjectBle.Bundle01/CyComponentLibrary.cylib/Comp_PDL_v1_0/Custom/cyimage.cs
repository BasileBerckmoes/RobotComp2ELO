/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Drawing;
using System.Drawing.Text;
using System.Drawing.Drawing2D;
using System.Collections.Generic;
using System.Diagnostics;

namespace Comp_PDL_v1_0
{
    public abstract class CyImage : IDisposable
    {
        protected const int START_X = 40;
        protected const int END_X = 400;
        public const double DEEPSLEEP_LESS_VDDA = 1.5;
        protected Bitmap m_bmp;

        protected Size ImageSize { get; set; }
        public Bitmap Image { get { return m_bmp; } }
        public bool Hysteresis { get; set; }        
        public CyEInterruptType Interrupt { get; set; }        
        public bool DeepSleepEnable { get; set; }
        public double Vdda;

        public CyImage(Size size)
        {
            ImageSize = size;
        }

        public abstract void Update();

        protected static void MakeHighQualityForDrawing(Graphics g)
        {
            g.SmoothingMode = SmoothingMode.AntiAlias;
            g.InterpolationMode = InterpolationMode.HighQualityBicubic;
            g.CompositingQuality = CompositingQuality.Default;
            g.TextRenderingHint = TextRenderingHint.SystemDefault;
            g.PixelOffsetMode = PixelOffsetMode.Default;
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                if (m_bmp != null)
                    m_bmp.Dispose();
            }
        }
    }

    public class CyWaveformImage : CyImage
    {
        public CyWaveformImage(Size size)
            : base(size)
        {
        }

        public override void Update()
        {
            Bitmap updatedBitmap = new Bitmap(ImageSize.Width, ImageSize.Height);
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
            const int ERROR_Y = 90;
            const int ERROR_X = 10;

            const int BLUE_W = (END_X - START_X) / 4;
            const int BLUE_CROSS_X = (int)(BLUE_W * ((float)(VPLUS_Y - VMIN_Y) / (VPLUS_Y - VDDA_Y)));
            const int BLUE_CROSS_HYST_X = (int)(BLUE_W * ((float)(VPLUS_Y - HYST_Y) / (VPLUS_Y - VDDA_Y)));
            const int HYST_TEXT_X = 45;
            const int HYST_ARR_H = 15;
            const int WAVE_Y1 = 100;
            const int WAVE_Y2 = 140;
            const int WAVE_Y3 = 160;
            const int WAVE_Y4 = 200;

            using (Graphics g = Graphics.FromImage(updatedBitmap))
            using (Pen extentspen = new Pen(Brushes.Black))
            {
                extentspen.DashStyle = DashStyle.Dash;
                MakeHighQualityForDrawing(g);
                g.Clear(Color.White);

                if (DEEPSLEEP_LESS_VDDA >= Vdda)
                {
                    using (Font perfont = new Font("Arial", 18, FontStyle.Regular, GraphicsUnit.Pixel))
                    {
                        g.DrawString("Vdda voltage is too low for comparator operation with", perfont, Brushes.Black, new PointF(ERROR_X, ERROR_Y));
                        g.DrawString("Deep Sleep enabled.", perfont, Brushes.Black, new PointF(ERROR_X, ERROR_Y + 18));
                    }
                }
                else
                {
                    if(DeepSleepEnable)
                    {
                        // Draw warning band to show operating range with Deep Sleep enabled
                        double warningScale = DEEPSLEEP_LESS_VDDA / Vdda;
                        int warningHeight = (int) ((OV_Y - VDDA_Y) * warningScale);
                        g.FillRectangle(Brushes.Yellow, START_X, VDDA_Y, (END_X - START_X), warningHeight);
                        
                    }
                    // Setup the input wave 
                    g.DrawLine(extentspen, START_X, VDDA_Y, END_X, VDDA_Y);
                    g.DrawLine(Pens.Green, START_X, VMIN_Y, END_X, VMIN_Y);
                    g.DrawLine(extentspen, START_X, OV_Y, END_X, OV_Y);
                    extentspen.DashStyle = DashStyle.Solid;
                    g.DrawLine(extentspen, START_X, START_Y, START_X, ImageSize.Height);

                    // blue line
                    Point[] bluePts = new Point[5];
                    for (int i = 0; i < bluePts.Length; i++)
                    {
                        bluePts[i].Y = (i % 2 == 0) ? VPLUS_Y : VDDA_Y;
                        bluePts[i].X = START_X + i * BLUE_W;
                    }
                    g.DrawLines(Pens.Blue, bluePts);

                    // hysteresis horizontal line
                    if (Hysteresis)
                    {
                        g.DrawLine(Pens.Green, START_X, HYST_Y, END_X, HYST_Y);

                        extentspen.DashStyle = DashStyle.Dash;
                        extentspen.StartCap = LineCap.ArrowAnchor;
                        g.DrawLine(extentspen, HYST_TEXT_X, HYST_Y, HYST_TEXT_X, HYST_Y - HYST_ARR_H);
                        g.DrawLine(extentspen, HYST_TEXT_X, VMIN_Y, HYST_TEXT_X, VMIN_Y + HYST_ARR_H);

                        using (Font arrow = new Font("Arial", 10, FontStyle.Regular, GraphicsUnit.Pixel))
                        {
                            g.DrawString("30mV", arrow, Brushes.Black, HYST_TEXT_X, HYST_Y - HYST_ARR_H);
                        }
                        extentspen.StartCap = LineCap.Flat;
                    }

                    int[] ptsLineX = new int[8];
                    int[] ptsWave1X = new int[8];
                    int[] ptsWave2X = new int[8];

                    // dash vertical
                    extentspen.DashStyle = DashStyle.Dash;
                    for (int i = 0; i < 4; i++)
                    {
                        int shift = Hysteresis ? BLUE_CROSS_HYST_X : BLUE_CROSS_X;
                        int crossX = (i % 2 == 0) ? bluePts[i].X + shift : bluePts[i + 1].X - BLUE_CROSS_X;
                        g.DrawLine(extentspen, crossX, DASH_START_Y, crossX, DASH_END_Y);
                        ptsLineX[i * 2] = crossX;
                        ptsLineX[i * 2 + 1] = crossX;
                        ptsWave1X[i * 2] = crossX;
                        ptsWave1X[i * 2 + 1] = crossX;
                        ptsWave2X[i * 2] = crossX;
                        ptsWave2X[i * 2 + 1] = crossX;
                    }
                    g.DrawLines(Pens.Blue, bluePts);

                    // output square wave
                    List<Point> wavePts = new List<Point>();
                    List<Point> wave1Pts = new List<Point>();
                    List<Point> wave2Pts = new List<Point>();
                    List<Point> wavePtsOut = new List<Point>();

                    waveShift = 0;

                    // Draw HW out                
                    UpdateHwOut(wavePts, ptsLineX, WAVE_Y1, WAVE_Y2, waveShift, 0, out wavePtsOut);
                    g.DrawLines(Pens.Orange, wavePtsOut.ToArray());

                    // Draw Int out
                    UpdateHwOutIntOut(wave2Pts, ptsWave2X, WAVE_Y4, WAVE_Y3, waveShift, interruptShift, Interrupt,
                        out wavePtsOut);
                    g.DrawLines(Pens.Orange, wavePtsOut.ToArray());

                    const int TXT_X = 7;
                    const int TXT_LONG_X = 2;
                    const int TXT_VX = 17;
                    const int TXT_Y_START = 95;
                    const int TXT_STEP_Y = 20;
                    const int TXT_H = 10;

                    using (Font perfont = new Font("Arial", 10, FontStyle.Regular, GraphicsUnit.Pixel))
                    {
                        g.DrawString("Vdda", perfont, Brushes.Black, new PointF(TXT_X, VDDA_Y - TXT_H));
                        g.DrawString("0V", perfont, Brushes.Black, new PointF(TXT_VX, VPLUS_Y));
                        g.DrawString("Vddd", perfont, Brushes.Black, new PointF(TXT_X, TXT_Y_START));
                        g.DrawString("Vssd", perfont, Brushes.Black, new PointF(TXT_X, TXT_Y_START + 2 * TXT_STEP_Y));
                        g.DrawString("Vddd", perfont, Brushes.Black, new PointF(TXT_X, TXT_Y_START + 3 * TXT_STEP_Y));
                        g.DrawString("Vssd", perfont, Brushes.Black, new PointF(TXT_X, TXT_Y_START + 5 * TXT_STEP_Y));
                        g.DrawString("V+", perfont, Brushes.Blue, new PointF(TXT_VX, VPLUS_Y - TXT_H));
                        g.DrawString("V-", perfont, Brushes.Green, new PointF(TXT_VX, VMIN_Y - TXT_H));
                        g.DrawString("HW out", perfont, Brushes.Orange, new PointF(TXT_LONG_X, TXT_Y_START + TXT_STEP_Y));
                        g.DrawString("Int out", perfont, Brushes.Orange, new PointF(TXT_LONG_X, TXT_Y_START + 4 * TXT_STEP_Y));
                    }
                }
                g.ResetTransform();

                Bitmap old = m_bmp;
                m_bmp = updatedBitmap;
                if (old != null)
                {
                    old.Dispose();
                }
            }
        }

        private static void UpdateHwOut(List<Point> wavePts, int[] ptsLineX, int waveY1, int waveY2, int waveShift, int offset,
            out List<Point> wavePtsOut)
        {
            wavePts.Add(new Point(START_X, waveY2));

            for (int i = 0; i < ptsLineX.Length; i++)
            {
                int x = ptsLineX[i] + offset + ((i % 2 == 0) ? -waveShift : waveShift);
                int y = ((i % 4 == 1) || (i % 4 == 2)) ? waveY1 : waveY2;

                wavePts.Add(new Point(x, y));
            }
            wavePts.Add(new Point(END_X, waveY2));
            wavePtsOut = wavePts;
        }

        private static void UpdateHwOutIntOut(List<Point> wavePts, int[] ptsWaveX, int YLow, int YHight,
            int waveShift, int intShift, CyEInterruptType interr, out List<Point> wavePtsOut)
        {
            wavePts.Add(new Point(START_X, YLow));

            for (int i = 0; i < ptsWaveX.Length; i++)
            {
                int y = YLow;
                int x = ptsWaveX[i] + ((i % 2 == 0) ? (-waveShift) : (waveShift));
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

            wavePtsOut = wavePts;
        }
    }
}
