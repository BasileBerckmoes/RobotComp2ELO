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
using VDAC12_PDL_v1_0.Utils;

namespace VDAC12_PDL_v1_0.TransferGraph
{
    internal class CyTransferGraph : IDisposable
    {
        protected const int HEIGHT_MARGIN = 20;
        protected const int AXIS_X_HEIGHT = 5;
        protected const int MAX_COUNT = 4096;
        protected const int FONT_SIZE = 13;

        protected Graphics m_graphics;

        /// <summary>
        /// Transfer graph image size.
        /// </summary>
        public Size Size { get; set; }

        public CyTransferGraph(Graphics g, Size size)
        {
            m_graphics = g;
            Size = size;
            CyGraphicsUtils.MakeHighQualityForDrawing(m_graphics);
        }

        public void DrawErrorMessage()
        {
            string errorMessage = "Vref is above the output range of the Vref buffer, transfer function is unknown.";

            using (Font perfont = new Font("Arial", FONT_SIZE, FontStyle.Regular, GraphicsUnit.Pixel))
            {
                SizeF textSize = m_graphics.MeasureString("-2048", perfont); // align with the longest text
                int textPositionY = Size.Height/2;
                m_graphics.TextRenderingHint = System.Drawing.Text.TextRenderingHint.SingleBitPerPixelGridFit;
                m_graphics.DrawString(errorMessage, perfont, Brushes.Black, (int)(textSize.Width - 30), textPositionY);                
            }
        }
        public void Draw()
        {
            DrawAxes(HEIGHT_MARGIN);
        }

        public void DrawAxes(int height)
        {
            int midPoint = Size.Width / 2;
            using (Pen solidPen = new Pen(Color.Black))
            {
                m_graphics.DrawLine(solidPen, 0, Size.Height - height, Size.Width, Size.Height - height);
                m_graphics.DrawLine(solidPen, midPoint, Size.Height - height, midPoint, height);

                //tick marks
                m_graphics.DrawLine(solidPen, midPoint -5, height, midPoint +5, height);
                m_graphics.DrawLine(solidPen, 0, Size.Height - height -5, 0, Size.Height - height +5);
                m_graphics.DrawLine(solidPen, Size.Width -1, Size.Height - height - 5, Size.Width -1, Size.Height - height +5);
            }

            using (Pen bluePen = new Pen(Color.Blue))
            {
                m_graphics.DrawLine(bluePen, 0, Size.Height - height, Size.Width, height);
            }
        }

        public void DrawLabels(CyEnums.CyESignMode mode, double vrefVoltage)
        {
            int midPoint = Size.Width / 2 -5;
            string minValue = "-2048";
            string midValue = "0";
            string maxValue = "2047";
            string vref = "Vref = " + vrefVoltage.ToString("0.0000") + " V";

            if(mode == CyEnums.CyESignMode.FormatUnsigned)
            {
                minValue = "0";
                midValue = "2048";
                maxValue = "4095";
                midPoint -= 10;
            }
            using (Font perfont = new Font("Arial", FONT_SIZE, FontStyle.Regular, GraphicsUnit.Pixel))
            {
                SizeF textSize = m_graphics.MeasureString("-2048", perfont); // align with the longest text
                int textPositionY = Size.Height - (int) textSize.Height;
                m_graphics.TextRenderingHint = System.Drawing.Text.TextRenderingHint.SingleBitPerPixelGridFit;
                m_graphics.DrawString(minValue, perfont, Brushes.Black, (int)(textSize.Width - 30), textPositionY);
                m_graphics.DrawString(midValue, perfont, Brushes.Black, midPoint, textPositionY);
                m_graphics.DrawString(vref, perfont, Brushes.Black, midPoint, textSize.Height - 15);
                m_graphics.DrawString(maxValue, perfont, Brushes.Black, Size.Width - textSize.Width, textPositionY);
            }
        }

        public void DrawBufferWarning()
        {
            int midPoint = Size.Width / 2 - 5;
            string bufferWarning = "Yellow bands indicate Output Buffer limits,";
            string seeDatasheet = "see datasheet.";
            
            using (Font perfont = new Font("Arial", FONT_SIZE, FontStyle.Regular, GraphicsUnit.Pixel))
            {
                SizeF textSize = m_graphics.MeasureString(bufferWarning, perfont); // align with the longest text
                int textPositionY = Size.Height - HEIGHT_MARGIN*3;
                m_graphics.TextRenderingHint = System.Drawing.Text.TextRenderingHint.SingleBitPerPixelGridFit;
                m_graphics.DrawString(bufferWarning, perfont, Brushes.Black, midPoint + 20, textPositionY);
                m_graphics.DrawString(seeDatasheet, perfont, Brushes.Black, midPoint + 20, textPositionY + textSize.Height);
            }
        }

        public void DrawWarningBands(double vrefVoltage, double maxOutput)
        {
            // Output degrades within 200-500 mV of the rails when using a buffer. 
            // Set the warning bands to ~200 mV.
            if (vrefVoltage > 0)
            {
                double graphHeight = Size.Height - (HEIGHT_MARGIN * 2);

                //Draw upper warning band if Vref is greater than the max output voltage
                if(vrefVoltage > maxOutput)
                {
                    double ratio = (vrefVoltage - maxOutput) / vrefVoltage;
                    int upperBandHeight = Convert.ToInt32(ratio * graphHeight);
                    using (Brush yellowBrush = new System.Drawing.SolidBrush(Color.Yellow))
                    {
                        m_graphics.FillRectangle(yellowBrush, new Rectangle(0, HEIGHT_MARGIN, Size.Width, upperBandHeight));
                    }
                }
                
                double bandRatio = 0.200 / vrefVoltage;
                int lowerBandHeight = Convert.ToInt32(bandRatio * graphHeight);

                using (Brush yellowBrush = new System.Drawing.SolidBrush(Color.Yellow))
                {                    
                    m_graphics.FillRectangle(yellowBrush, new Rectangle(0, Size.Height - HEIGHT_MARGIN - lowerBandHeight, Size.Width, lowerBandHeight));
                }
            }
        }

        public void DrawInitialVoltage(CyEnums.CyESignMode mode, double vrefVoltage, double initialVoltage)
        {
            int height = Size.Height - (2 * HEIGHT_MARGIN);
            int width = Size.Width;
            if (vrefVoltage > 0)
            {
                double initialRatio = initialVoltage / vrefVoltage;
                double hScaled = Math.Round(height * initialRatio);
                double wScaled = Math.Round(width * initialRatio);

                height = (int)hScaled;
                width = (int)wScaled;
                //Keep the vertical line on the drawing
                if(width == Size.Width)
                {
                    width--;
                }
                using (Pen redPen = new Pen(Color.Red))
                {
                    m_graphics.DrawLine(redPen, 0, Size.Height - height - HEIGHT_MARGIN, width, Size.Height - height - HEIGHT_MARGIN);
                    m_graphics.DrawLine(redPen, width, Size.Height - HEIGHT_MARGIN, width, Size.Height - height - HEIGHT_MARGIN);
                }

                DrawInitialVoltageLabel(mode, initialVoltage, vrefVoltage, height);
            }
        }

        private void DrawInitialVoltageLabel(CyEnums.CyESignMode mode, double initialVoltage, double vrefVoltage, int height)
        {
            string voltage = "Vout = " + initialVoltage.ToString("0.0000") + " V";
            double lsb = vrefVoltage / (double) MAX_COUNT;
            int initCode = 0;
            
            if (mode == CyEnums.CyESignMode.FormatSigned)
            {
                double midVoltage = vrefVoltage / 2;
                if(initialVoltage >= midVoltage)
                {
                    initCode = Convert.ToInt32(Math.Round((initialVoltage - midVoltage) / lsb));
                }
                else
                {
                    initCode = Convert.ToInt32(Math.Round((midVoltage - initialVoltage) / lsb));
                    initCode = initCode * -1;
                }
            }
            else
            {
                initCode = Convert.ToInt32(Math.Round(initialVoltage / lsb));
            }

            string code = "Initial Code = " + initCode.ToString();
            string finalString = code + ", " + voltage;

            using (Font perfont = new Font("Arial", FONT_SIZE, FontStyle.Regular, GraphicsUnit.Pixel))
            {
                SizeF textSize = m_graphics.MeasureString(finalString, perfont); // align with the longest text
                int textPositionY = Size.Height - height;
                m_graphics.TextRenderingHint = System.Drawing.Text.TextRenderingHint.SingleBitPerPixelGridFit;
                m_graphics.DrawString(finalString, perfont, Brushes.Black, 0, Size.Height - height - HEIGHT_MARGIN - textSize.Height);
            }
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                // dispose of managed disposable members
                m_graphics.Dispose();
            }
            // release unmanaged resources
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        ~CyTransferGraph()
        {
            Dispose(false);
        }
    }
}
