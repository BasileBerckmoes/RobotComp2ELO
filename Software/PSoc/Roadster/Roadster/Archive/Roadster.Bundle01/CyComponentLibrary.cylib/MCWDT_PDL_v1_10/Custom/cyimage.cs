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
using CyDesigner.Toolkit;

namespace MCWDT_PDL_v1_10
{
    public abstract class CyImage : IDisposable
    {       
        public const int IMAGE_SIZE_WIDTH = 600;
        public const int IMAGE_SIZE_HEIGHT = 140;

        protected Bitmap m_bmp;

        protected Size ImageSize { get; set; }
        public Bitmap Image { get { return m_bmp; } }
        public bool CascadeC0C1 { get; set; }
        public bool CascadeC1C2 { get; set; }
        public CyEModeType ModeC0 { get; set; }
        public CyEModeType ModeC1 { get; set; }
        public CyEC2ModeType ModeC2 { get; set; }
        public UInt16 MatchC0 { get; set; }
        public UInt16 MatchC1 { get; set; }
        public CyEClearOnMatchType C0ClearOnMatch { get; set; }
        public CyEClearOnMatchType C1ClearOnMatch { get; set; }

        public CyEPeriodType PeriodC2 { get; set; }

        public CyImage(Size size)
        {
            ImageSize = size;
        }

        public abstract void Update();

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

    public class CyMCWDTImage : CyImage
    {
        public CyMCWDTImage(Size size) : base(size)
        {
        }

        public override void Update()
        {
            Bitmap updatedBitmap = new Bitmap(ImageSize.Width, ImageSize.Height);

            double divider, dividerTemp;           

            // Set general coordinates.
            float rectangleWidth = IMAGE_SIZE_WIDTH / 5;
            float rectangleHeight = IMAGE_SIZE_HEIGHT / 5;
            float startX = 15;
            float rectangleXoffset = IMAGE_SIZE_WIDTH / 3;
            float rectangleY = IMAGE_SIZE_HEIGHT / 4;
            float arrowsY = rectangleY + rectangleHeight / 2;
            float frequencyY = rectangleY + rectangleHeight + 10;
            float periodY = frequencyY + 15;

            float rectangleC0X = startX;
            float rectangleC1X = startX + rectangleXoffset;
            float rectangleC2X = rectangleC1X + rectangleXoffset;

            RectangleF[] rects =
                {
                    new RectangleF(rectangleC2X, rectangleY, rectangleWidth, rectangleHeight),
                    new RectangleF(rectangleC1X, rectangleY, rectangleWidth, rectangleHeight),
                    new RectangleF(rectangleC0X, rectangleY, rectangleWidth, rectangleHeight)
                };

            using (StringFormat drawFormat = new StringFormat())
            using (Graphics g = Graphics.FromImage(updatedBitmap))
            using (Pen rectPen = new Pen(Color.Black, 3))
            using (Pen arrowPen = new Pen(Color.Black, 2))
            using (SolidBrush rectBrush = new SolidBrush(Color.FromArgb(198, 208, 221))) // Creator color for Category
            using (Font perfont = new Font("Arial", 12, FontStyle.Regular, GraphicsUnit.Pixel))
            using (Font perfontBold = new Font("Arial", 12, FontStyle.Bold, GraphicsUnit.Pixel))
            {
                CyGraphicsUtils.MakeHighQualityForDrawing(g);
                g.Clear(SystemColors.Control);

                // Set format of string.            
                drawFormat.Alignment = StringAlignment.Center;
                drawFormat.LineAlignment = StringAlignment.Center;

                // Draw general strings.
                g.DrawString(Resources.CountersClockNote, perfont, Brushes.Black, new PointF(startX, 10));                
                g.DrawString(Resources.InterruptsStructureNote, perfont, Brushes.Black,
                             new PointF(startX, IMAGE_SIZE_HEIGHT - 20));                

                // Draw and fill rectangles.
                g.DrawRectangles(rectPen, rects);
                g.FillRectangles(rectBrush, rects);
                g.DrawString("C0 (16-bit)", perfontBold, Brushes.Black, rects[0], drawFormat);
                g.DrawString("C1 (16-bit)", perfontBold, Brushes.Black, rects[1], drawFormat);
                g.DrawString("C2 (32-bit)", perfontBold, Brushes.Black, rects[2], drawFormat);

                // Draw arrows between rectangles.
                AdjustableArrowCap bigArrow = new AdjustableArrowCap(4, 5);
                arrowPen.CustomEndCap = bigArrow;
                if (CascadeC0C1)
                {
                    g.DrawLine(arrowPen, rectangleC2X, arrowsY, (rectangleC1X + rectangleWidth), arrowsY);
                }
                if (CascadeC1C2)
                {
                    g.DrawLine(arrowPen, rectangleC1X, arrowsY, (rectangleC0X + rectangleWidth), arrowsY);
                }

                // Draw strings with calculated Frequency and Period.
                // Counter 0
                divider = (C0ClearOnMatch == CyEClearOnMatchType.CLEAR_ON_MATCH) ? (MatchC0 + 1) : 65535;                
                g.DrawString(CyClockUtils.FormatFrequency(divider), perfont, Brushes.Black, 
                             new PointF(rectangleC2X, frequencyY));
                g.DrawString(CyClockUtils.FormatPeriod(divider), perfont, Brushes.Black,
                             new PointF(rectangleC2X, periodY));

                // Counter 1
                dividerTemp = (C1ClearOnMatch == CyEClearOnMatchType.CLEAR_ON_MATCH) ? (MatchC1 + 1) : 65535;
                divider = CascadeC0C1 ? (dividerTemp * divider) : dividerTemp;
                g.DrawString(CyClockUtils.FormatFrequency(divider), perfont, Brushes.Black,
                             new PointF(rectangleC1X, frequencyY));
                g.DrawString(CyClockUtils.FormatPeriod(divider), perfont, Brushes.Black, 
                             new PointF(rectangleC1X, periodY));

                // Counter 2
                if (ModeC2 == CyEC2ModeType.INTERRUPT)
                {
                    dividerTemp = Math.Pow(2, (double)PeriodC2);
                }
                else
                {
                    dividerTemp = UInt32.MaxValue;
                }
                divider =  CascadeC1C2 ? (dividerTemp * divider) : dividerTemp;
                g.DrawString(CyClockUtils.FormatFrequency(divider), perfont, Brushes.Black, 
                             new PointF(rectangleC0X, frequencyY));
                g.DrawString(CyClockUtils.FormatPeriod(divider), perfont, Brushes.Black, 
                             new PointF(rectangleC0X, periodY));

                g.ResetTransform();

                Bitmap old = m_bmp;
                m_bmp = updatedBitmap;
                if (old != null)
                {
                    old.Dispose();
                }
            }
        }
    }
}
