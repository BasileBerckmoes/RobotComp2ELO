/*******************************************************************************
* Copyright 2014-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Drawing;

namespace OpAmp_P4_v1_20
{
    internal class CyImage : IDisposable
    {
        #region Input parameters fields
        public CyEModeType m_modeType;
        public CyEOutputType m_outputType;
        #endregion Input parameters fields

        #region Image related fields
        public Size m_imageSize;
        public Bitmap m_bmp;
        #endregion Image related fields

        #region Private fields
        private bool m_isDisposed = false;
        #endregion Private fields

        #region Defines
        private const int CY_2DIVIDER = 2;
        private const int CY_3DIVIDER = 3;
        private const int CY_OFFSET_Y = 30;
        private const int CY_OFFSET_X = 10;
        private const int CY_SIZE_PIN_BOX = 10;
        private const float CY_PIN_WIDTH = 1;
        #endregion
        #region Constructor(s)
        public CyImage()
        {
            m_imageSize = new Size(130, 100);
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
        /// This function draws the symbol that is displayed on the right side of the window
        /// </summary>
        public void UpdateSymbol()
        {
            int iBitmapWidth = m_imageSize.Width - 30;
            m_bmp = new Bitmap(m_imageSize.Width, m_imageSize.Height);
            int triangleLeft = iBitmapWidth / 5;
            int triangleRight = iBitmapWidth - triangleLeft;
            int triangleSide = (int) ((triangleRight - triangleLeft) / Math.Cos(Math.PI / 6));
            int triangleTop = m_imageSize.Height / CY_2DIVIDER - triangleSide / CY_2DIVIDER;
            int triangleBottom = triangleTop + triangleSide;
            int plusY = triangleTop + triangleSide / CY_3DIVIDER;
            int minusY = triangleTop + 2 * triangleSide / CY_3DIVIDER;
            int plusCenterX = triangleLeft + triangleSide / 6;
            int plusW = (plusCenterX - triangleLeft) * 4 / CY_3DIVIDER;

            Pen pen = new Pen(Color.Black, CY_PIN_WIDTH);
            Pen penPlus = new Pen(Color.Black, 2);
            Pen penWire = new Pen(Color.FromArgb(0, 0, 128), CY_PIN_WIDTH);
            Brush brushAqua = Brushes.Aqua;
            Brush brushWhite = Brushes.White;

            using (Graphics g = Graphics.FromImage(m_bmp))
            {
                g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
                g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.AntiAlias;

                //box
                Point[] pts = new Point[4];
                pts[0] = new Point(0, 0);
                pts[1] = new Point(0, m_imageSize.Height-1);
                pts[2] = new Point(iBitmapWidth, m_imageSize.Height-1);
                pts[3] = new Point(iBitmapWidth, 0);
                g.DrawPolygon(pen, pts);
                // triangle
                pts = new Point[3];
                pts[0] = new Point(triangleLeft, triangleTop);
                pts[1] = new Point(triangleLeft, triangleBottom);
                pts[2] = new Point(triangleRight, triangleTop + triangleSide / CY_2DIVIDER);
                g.FillPolygon(brushAqua, pts);
                g.DrawPolygon(pen, pts);

                // lines
                g.DrawLine(penWire, new Point(0, plusY), new Point(triangleLeft, plusY));
                g.DrawLine(penWire, new Point(triangleRight, triangleTop + triangleSide / CY_2DIVIDER), new Point(iBitmapWidth, triangleTop + triangleSide / CY_2DIVIDER));

                if (m_modeType == CyEModeType.OPAMP)
                {
                    g.DrawLine(penWire, new Point(0, minusY), new Point(triangleLeft, minusY));
                }
                else//Follower
                {
                    g.DrawLine(penWire, new Point(triangleLeft, minusY), new Point(triangleLeft / CY_2DIVIDER, minusY));
                    g.DrawLine(penWire, new Point(triangleLeft / CY_2DIVIDER, minusY), new Point(triangleLeft / CY_2DIVIDER, minusY + CY_OFFSET_Y));
                    g.DrawLine(penWire, new Point(triangleLeft / CY_2DIVIDER, minusY + CY_OFFSET_Y), new Point(triangleRight + CY_OFFSET_X, minusY + CY_OFFSET_Y));
                    g.DrawLine(penWire, new Point(triangleRight + CY_OFFSET_X, minusY + CY_OFFSET_Y), new Point(triangleRight + CY_OFFSET_X, minusY + CY_OFFSET_Y));
                    g.DrawLine(penWire, new Point(triangleRight + CY_OFFSET_X, minusY + CY_OFFSET_Y), new Point(triangleRight + CY_OFFSET_X, triangleTop + triangleSide / CY_2DIVIDER));
                }

                // plus, minus
                g.DrawLine(penPlus, new Point(plusCenterX - plusW / CY_2DIVIDER, plusY), new Point(plusCenterX + plusW / CY_2DIVIDER, plusY));
                g.DrawLine(penPlus, new Point(plusCenterX, plusY - plusW / CY_2DIVIDER), new Point(plusCenterX, plusY + plusW / CY_2DIVIDER));
                g.DrawLine(penPlus, new Point(plusCenterX - plusW / CY_2DIVIDER, minusY), new Point(plusCenterX + plusW / CY_2DIVIDER, minusY));

                //draw external pin
                if (m_outputType == CyEOutputType.OPAMP_HIGH_10MA)
                {
                    g.DrawLine(penWire, new Point(iBitmapWidth, triangleTop + triangleSide / CY_2DIVIDER), new Point(iBitmapWidth + CY_SIZE_PIN_BOX, triangleTop + triangleSide / CY_2DIVIDER));
                    //draw square  
                    pts = new Point[4];
                    pts[0] = new Point(iBitmapWidth + CY_SIZE_PIN_BOX, triangleTop + triangleSide / CY_2DIVIDER - CY_SIZE_PIN_BOX / 2);
                    pts[1] = new Point(iBitmapWidth + CY_SIZE_PIN_BOX, triangleTop + triangleSide / CY_2DIVIDER + CY_SIZE_PIN_BOX / 2);
                    pts[2] = new Point(iBitmapWidth + CY_SIZE_PIN_BOX * 2, triangleTop + triangleSide / CY_2DIVIDER + CY_SIZE_PIN_BOX / 2);
                    pts[3] = new Point(iBitmapWidth + CY_SIZE_PIN_BOX * 2, triangleTop + triangleSide / CY_2DIVIDER - CY_SIZE_PIN_BOX / 2);
                    g.DrawPolygon(pen, pts);

                    g.DrawLine(penWire, new Point(iBitmapWidth + CY_SIZE_PIN_BOX, triangleTop + triangleSide / CY_2DIVIDER - CY_SIZE_PIN_BOX / 2), new Point(iBitmapWidth + CY_SIZE_PIN_BOX * 2, triangleTop + triangleSide / CY_2DIVIDER + CY_SIZE_PIN_BOX/2));
                    g.DrawLine(penWire, new Point(iBitmapWidth + CY_SIZE_PIN_BOX, triangleTop + triangleSide / CY_2DIVIDER + CY_SIZE_PIN_BOX / 2), new Point(iBitmapWidth + CY_SIZE_PIN_BOX * 2, triangleTop + triangleSide / CY_2DIVIDER - CY_SIZE_PIN_BOX/2));

                }
            }
            pen.Dispose();
            penPlus.Dispose();
            penWire.Dispose();
        }

    
        #endregion Update image
    }
}
