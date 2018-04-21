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

namespace LPComp_PDL_v1_0
{
    public abstract class CyImage : IDisposable
    {
        protected const int START_X = 40;
        protected const int END_X = 400;

        protected Bitmap m_bmp;

        protected Size ImageSize { get; set; }
        public Bitmap Image { get { return m_bmp; } }
        public CyEHysteresisType Hysteresis { get; set; }
        public CyEOutputModeType OutputMode { get; set; }
        public CyEInterruptType Interrupt { get; set; }
        public CyESpeedType Power { get; set; }
        public bool LocalVrefInput { get; set; }
        
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
        public CyWaveformImage(Size size) : base(size)
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

            const int BLUE_W = (END_X - START_X) / 4;
            const int BLUE_CROSS_X = (int)(BLUE_W * ((float)(VPLUS_Y - VMIN_Y) / (VPLUS_Y - VDDA_Y)));
            const int BLUE_CROSS_HYST_X = (int)(BLUE_W * ((float)(VPLUS_Y - HYST_Y) / (VPLUS_Y - VDDA_Y)));
            const int HYST_TEXT_X = 45;
            const int HYST_ARR_H = 15;
            const int WAVE_Y1 = 100;
            const int WAVE_Y2 = 140;
            const int WAVE_Y3 = 160;
            const int WAVE_Y4 = 200;
            const int TWO_CLOCK_OFFSET = 24;

            using (Graphics g = Graphics.FromImage(updatedBitmap))
            using (Pen extentspen = new Pen(Brushes.Black))
            {
                extentspen.DashStyle = DashStyle.Dash;
                MakeHighQualityForDrawing(g);
                g.Clear(Color.White);

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
                if (Hysteresis == CyEHysteresisType.LPCOMP_ENABLE_HYST)
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
                    int shift = (Hysteresis == CyEHysteresisType.LPCOMP_ENABLE_HYST) ? BLUE_CROSS_HYST_X : BLUE_CROSS_X;
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

                if (Power == CyESpeedType.LPCOMP_MODE_ULP)
                {
                    waveShift += 3;
                    interruptShift += 3;
                }
                else if (Power == CyESpeedType.LPCOMP_MODE_NORMAL)
                {
                    waveShift = 0;
                }

                // Draw HW out
                switch (OutputMode)
                {
                    case CyEOutputModeType.LPCOMP_OUT_SYNC:
                        UpdateHwOut(wavePts, ptsLineX, WAVE_Y1, WAVE_Y2, waveShift, TWO_CLOCK_OFFSET, out wavePtsOut);
                        g.DrawLines(Pens.Orange, wavePtsOut.ToArray());
                        break;
                    case CyEOutputModeType.LPCOMP_OUT_PULSE:
                        UpdateHwOutIntOut(wave1Pts, ptsWave1X, WAVE_Y2, WAVE_Y1, waveShift, interruptShift, Interrupt,
                        out wavePtsOut);
                        g.DrawLines(Pens.Orange, wavePtsOut.ToArray());
                        break;
                    case CyEOutputModeType.LPCOMP_OUT_DIRECT:
                        UpdateHwOut(wavePts, ptsLineX, WAVE_Y1, WAVE_Y2, waveShift, 0, out wavePtsOut);
                        g.DrawLines(Pens.Orange, wavePtsOut.ToArray());
                        break;
                    default:
                        Debug.Fail("unhandled enum item.");
                        break;
                }

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
                    ((interr == CyEInterruptType.LPCOMP_INTR_RISING) ||
                     (interr == CyEInterruptType.LPCOMP_INTR_BOTH)))
                {
                    y = YHight;
                    wavePts.Add(new Point(x, y));
                    x += intShift;
                    wavePts.Add(new Point(x - waveShift, y));
                    wavePts.Add(new Point(x + waveShift, YLow));
                }
                else if ((i % 4 == 2) &&
                        ((interr == CyEInterruptType.LPCOMP_INTR_FALLING) ||
                         (interr == CyEInterruptType.LPCOMP_INTR_BOTH)))
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

    public class CySymbolImage : CyImage
    {
        public CySymbolImage(Size size) : base(size)
        {
        }

        public override void Update()
        {
            Bitmap updatedBitmap = new Bitmap(ImageSize.Width, ImageSize.Height);
            int triangleLeft = ImageSize.Width / 5;
            int triangleRight = ImageSize.Width - triangleLeft;
            int triangleSide = (int)((triangleRight - triangleLeft) / Math.Cos(Math.PI / 6));
            int triangleTop = ImageSize.Height / 2 - triangleSide / 2;
            int triangleBottom = triangleTop + triangleSide;
            int plusY = triangleTop + triangleSide / 3;
            int minusY = triangleTop + triangleSide * 2 / 3;
            int minusVertY = triangleTop + 10 * triangleSide / 9;
            int plusCenterX = triangleLeft + triangleSide / 6;
            int plusW = (plusCenterX - triangleLeft) * 4 / 3;
            int hystLeft = triangleLeft + (plusCenterX - triangleLeft) * 2;
            int hystW = plusW / 3;
            int vrefRectW = ImageSize.Width / 6;
            int vrefRectH = ImageSize.Width / 11;
            int vrefRectX = triangleLeft * 3 / 2;
            int vrefRectY = minusVertY - vrefRectH / 2;
            int vrefLine1X1 = triangleLeft / 2;
            int vrefLine1X2 = triangleLeft;
            int vrefLine1Y = minusY;
            int vrefLine2X = triangleLeft / 2;
            int vrefLine2Y1 = minusY;
            int vrefLine2Y2 = minusVertY;
            int vrefLine3X1 = triangleLeft / 2;
            int vrefLine3X2 = vrefRectX;
            int vrefLine3Y = minusVertY;
            
            Rectangle rect = new Rectangle(vrefRectX, vrefRectY, vrefRectW, vrefRectH);
            String vrefText = "Vref";
            
            using(Graphics g = Graphics.FromImage(updatedBitmap))
            using(Pen pen = new Pen(Color.Black, 1))
            using(Pen penPlus = new Pen(Color.Black, 2))
            using(Pen penWire = new Pen(Color.FromArgb(0, 0, 128), 1))
            using(Pen rectPen = new Pen(Color.Black, 2))
            using(SolidBrush rectBrush = new SolidBrush(Color.FromArgb(255, 255, 128)))   
            using(Font vrefTextFont = new Font("Arial", 8))
            using(SolidBrush vrefBrush = new SolidBrush(Color.Black))
            using(StringFormat vrefFormat = new StringFormat())
            {
                MakeHighQualityForDrawing(g);

                // input lines
                g.DrawLine(penWire, new Point(0, plusY), new Point(triangleLeft, plusY));
                if (LocalVrefInput)
                {
                    g.DrawLine(penWire, new Point(vrefLine1X1, vrefLine1Y), new Point(vrefLine1X2, vrefLine1Y));
                    g.DrawLine(penWire, new Point(vrefLine2X, vrefLine2Y1), new Point(vrefLine2X, vrefLine2Y2));
                    g.DrawLine(penWire, new Point(vrefLine3X1, vrefLine3Y), new Point(vrefLine3X2, vrefLine3Y)); 
                    
                    // internal reference
                    SizeF stringSizeVref = new SizeF(); 
                    stringSizeVref = g.MeasureString(vrefText, vrefTextFont);
                    g.DrawRectangle(rectPen, rect);
                    g.FillRectangle(rectBrush, rect);
                    PointF vrefPoint = new PointF(vrefRectX + vrefRectW/2 - stringSizeVref.Width/2, vrefRectY + vrefRectH/2 - stringSizeVref.Height/2);
                    g.DrawString(vrefText, vrefTextFont, vrefBrush, vrefPoint, vrefFormat);
                }
                else
                {
                    g.DrawLine(penWire, new Point(0, minusY), new Point(triangleLeft, minusY));  					
                }

                // triangle
                Point[] pts = new Point[3];
                pts[0] = new Point(triangleLeft, triangleTop);
                pts[1] = new Point(triangleLeft, triangleBottom);
                pts[2] = new Point(triangleRight, triangleTop + triangleSide / 2);
                g.FillPolygon(Brushes.Aqua, pts);
                g.DrawPolygon(pen, pts);

                // plus, minus
                g.DrawLine(penPlus, new Point(plusCenterX - plusW / 2, plusY),
                                    new Point(plusCenterX + plusW / 2, plusY));
                g.DrawLine(penPlus, new Point(plusCenterX, plusY - plusW / 2),
                                    new Point(plusCenterX, plusY + plusW / 2));
                g.DrawLine(penPlus, new Point(plusCenterX - plusW / 2, minusY),
                                    new Point(plusCenterX + plusW / 2, minusY));

                // hysteresis
                if (Hysteresis == CyEHysteresisType.LPCOMP_ENABLE_HYST)
                {
                    g.DrawLine(pen, new Point(hystLeft, plusY), new Point(hystLeft + hystW * 2, plusY));
                    g.DrawLine(pen, new Point(hystLeft + hystW, minusY), new Point(hystLeft + hystW * 3, minusY));
                    g.DrawLine(pen, new Point(hystLeft + hystW, plusY), new Point(hystLeft + hystW, minusY));
                    g.DrawLine(pen, new Point(hystLeft + 2 * hystW, plusY), new Point(hystLeft + 2 * hystW, minusY));
                }

                // pulse
                if (OutputMode == CyEOutputModeType.LPCOMP_OUT_PULSE)
                {
                    Point[] pts1 = new Point[6];
                    pts1[0] = new Point(triangleRight + 4, triangleTop + triangleSide / 2 - 4);
                    pts1[1] = new Point(pts1[0].X + 4, pts1[0].Y);
                    pts1[2] = new Point(pts1[0].X + 4, pts1[0].Y - 4);
                    pts1[3] = new Point(pts1[2].X + 4, pts1[0].Y - 4);
                    pts1[4] = new Point(pts1[2].X + 4, pts1[0].Y);
                    pts1[5] = new Point(pts1[4].X + 4, pts1[0].Y);
                    g.DrawLine(pen, pts1[0], pts1[1]);
                    g.DrawLine(pen, pts1[1], pts1[2]);
                    g.DrawLine(pen, pts1[2], pts1[3]);
                    g.DrawLine(pen, pts1[3], pts1[4]);
                    g.DrawLine(pen, pts1[4], pts1[5]);
                }

                g.DrawLine(penWire, new Point(triangleRight, triangleTop + triangleSide / 2),
                                    new Point(ImageSize.Width, triangleTop + triangleSide / 2));
            }

            Bitmap old = m_bmp;
            m_bmp = updatedBitmap;
            if (old != null)
            {
                old.Dispose();
            }
        }
    }
}
