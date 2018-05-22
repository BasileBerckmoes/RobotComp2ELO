/*******************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;

namespace CSD_Comp_v1_0
{
    public partial class CyConfigureTab : CyTabWrapper
    {
        public override string TabName
        {
            get { return "Configure"; }
        }

        #region Constructor(s)

        public CyConfigureTab(CyParameters parameters)
            : base(parameters)
        {
            InitializeComponent();

            DrawSymbol();
            UpdateDiagram();

            m_rbSlow.CheckedChanged += m_rbSpeed_CheckedChanged;
            m_rbFast.CheckedChanged += m_rbSpeed_CheckedChanged;
        }

        #endregion

        #region GUI update

        public void UpdateUI()
        {
            // Update Speed/Power groupbox controls
            m_rbSlow.Checked = (m_params.Speed == CyECompSpeedType.SLOW_SPEED);
            m_rbFast.Checked = (m_params.Speed == CyECompSpeedType.FAST_SPEED);
        }

        #endregion

        #region Event handlers

        void m_rbSpeed_CheckedChanged(object sender, EventArgs e)
        {
            if ((sender as RadioButton).Checked == false) return;
            m_params.Speed = (sender == m_rbSlow) ? CyECompSpeedType.SLOW_SPEED : CyECompSpeedType.FAST_SPEED;
            UpdateDiagram();
        }

        #endregion

        #region Drawing

        private void DrawSymbol()
        {
            Bitmap bmp = new Bitmap(m_pbSymbol.Width, m_pbSymbol.Height);

            int triangleLeft = m_pbSymbol.Width / 5;
            int triangleRight = m_pbSymbol.Width - triangleLeft;
            int triangleSide = (int)((triangleRight - triangleLeft) / Math.Cos(Math.PI / 6));
            int triangleTop = m_pbSymbol.Height / 2 - (triangleSide / 2) - 10;
            int triangleBottom = triangleTop + triangleSide;

            int plusY = triangleTop + triangleSide / 3;
            int minusY = triangleTop + 2 * triangleSide / 3;
            int plusCenterX = triangleLeft + triangleSide / 6;
            int plusW = (plusCenterX - triangleLeft) * 4 / 3;

            Pen penOutline = new Pen(Color.Black, 1);
            Pen penPolarity = new Pen(Color.Black, 1.5f);
            Pen penWire = new Pen(Color.FromArgb(0, 0, 128), 1);
            Font vrefFont = new Font("Microsoft Sans Serif", 11, FontStyle.Bold, GraphicsUnit.Pixel);

            using (Graphics g = Graphics.FromImage(bmp))
            {
                g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
                g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.AntiAlias;

                // Draw triangle
                Point[] trianglePts = new Point[3];
                trianglePts[0] = new Point(triangleLeft, triangleTop);                     // left top corner
                trianglePts[1] = new Point(triangleLeft, triangleBottom);                  // left bottom corner
                trianglePts[2] = new Point(triangleRight, triangleTop + triangleSide / 2); // right corner
                g.FillPolygon(Brushes.Aqua, trianglePts);
                g.DrawPolygon(penOutline, trianglePts);

                // Draw lines
                g.DrawLine(penWire, new Point(0, plusY), new Point(triangleLeft, plusY));         // plus input line
                g.DrawLine(penWire, new Point(triangleLeft, minusY),
                                    new Point(triangleLeft / 2, minusY));                         // minus input line
                int vrefWireY = (int)(triangleBottom + (m_pbSymbol.Height - triangleBottom) / 2); // vref left center
                g.DrawLine(penWire, new Point(triangleLeft / 2, minusY),
                                    new Point(triangleLeft / 2, vrefWireY));                      // down line
                g.DrawLine(penWire, new Point(triangleLeft, vrefWireY),
                                    new Point(triangleLeft / 2, vrefWireY));                      // vref line
                g.DrawLine(penWire, new Point(triangleRight, triangleTop + triangleSide / 2),
                                    new Point(m_pbSymbol.Width, triangleTop + triangleSide / 2)); // out line

                // Vref box
                int vrefBoxHeight = 12;
                Rectangle rectanglePts = new Rectangle(new Point(triangleLeft, vrefWireY - vrefBoxHeight / 2),
                                         new Size(26, vrefBoxHeight));
                g.FillRectangle(Brushes.Yellow, rectanglePts);
                g.DrawString("Vref", vrefFont, Brushes.Black,
                              new RectangleF(rectanglePts.X, rectanglePts.Y, rectanglePts.Width, rectanglePts.Height));
                g.DrawRectangle(penOutline, rectanglePts);

                // 1.2V caption
                g.DrawString("1.2V", vrefFont, Brushes.Black,
                              new PointF(rectanglePts.X + rectanglePts.Width, rectanglePts.Y));

                // Plus, minus
                g.DrawLine(penPolarity, new Point(plusCenterX - plusW / 2, plusY),
                                        new Point(plusCenterX + plusW / 2, plusY));
                g.DrawLine(penPolarity, new Point(plusCenterX, plusY - plusW / 2),
                                        new Point(plusCenterX, plusY + plusW / 2));
                g.DrawLine(penPolarity, new Point(plusCenterX - plusW / 2, minusY),
                                        new Point(plusCenterX + plusW / 2, minusY));
            }
            penOutline.Dispose();
            penPolarity.Dispose();
            penWire.Dispose();
            vrefFont.Dispose();
            m_pbSymbol.Image = bmp;
        }

        private void UpdateDiagram()
        {
            if ((m_pbDiagram.Width == 0) || (m_pbDiagram.Height == 0))
                return;

            using (Pen extentsPen = new Pen(Brushes.Black))
            {
                Image waveform = new Bitmap(m_pbDiagram.Width, m_pbDiagram.Height);
                Size defSize = new Size(444, 152);

                float scaleX = m_pbDiagram.Width / (float)defSize.Width;
                float scaleY = m_pbDiagram.Height / (float)defSize.Height;

                const int SHIFT = -5;
                using (Graphics wfg = Graphics.FromImage(waveform))
                {
                    wfg.ScaleTransform(scaleX, scaleY);
                    wfg.Clear(Color.White);

                    // Draw 0V and Vdda marking lines (Y axis).
                    extentsPen.DashStyle = DashStyle.Dash;
                    wfg.DrawLine(extentsPen, 40 + SHIFT, 20, 442 + SHIFT, 20);
                    wfg.DrawLine(Pens.Green, 40 + SHIFT, 50, 441 + SHIFT, 50);
                    wfg.DrawLine(extentsPen, 40 + SHIFT, 75, 442 + SHIFT, 75);

                    // Draw X axis.
                    extentsPen.DashStyle = DashStyle.Solid;
                    wfg.DrawLine(extentsPen, 40 + SHIFT, 10, 40 + SHIFT, 150);

                    // Draw V+ to Vdda signal (blue line). One line represents one segment of the signal.
                    wfg.DrawLine(Pens.Blue, 40 + SHIFT, 70, 139 + SHIFT, 20);
                    wfg.DrawLine(Pens.Blue, 139 + SHIFT, 20, 238 + SHIFT, 70);
                    wfg.DrawLine(Pens.Blue, 238 + SHIFT, 70, 337 + SHIFT, 20);
                    wfg.DrawLine(Pens.Blue, 337 + SHIFT, 20, 436 + SHIFT, 70);

                    // Four vertical marking lines which show intersection of blue (V+ to Vdda) and green lines (1.2V).
                    extentsPen.DashStyle = DashStyle.Dash;
                    wfg.DrawLine(extentsPen, 79 + SHIFT, 96, 79 + SHIFT, 35);
                    wfg.DrawLine(extentsPen, 198 + SHIFT, 96, 198 + SHIFT, 35);
                    wfg.DrawLine(extentsPen, 277 + SHIFT, 96, 277 + SHIFT, 35);
                    wfg.DrawLine(extentsPen, 396 + SHIFT, 96, 396 + SHIFT, 35);

                    if (m_rbFast.Checked)
                    {
                        // Rectangular signal (output). One line represents one segment of the signal.
                        wfg.DrawLine(Pens.Orange, 40 + SHIFT, 140, 79 + SHIFT, 140);
                        wfg.DrawLine(Pens.Orange, 79 + SHIFT, 140, 79 + SHIFT, 100);
                        wfg.DrawLine(Pens.Orange, 79 + SHIFT, 100, 198 + SHIFT, 100);
                        wfg.DrawLine(Pens.Orange, 198 + SHIFT, 100, 198 + SHIFT, 140);
                        wfg.DrawLine(Pens.Orange, 198 + SHIFT, 140, 277 + SHIFT, 140);
                        wfg.DrawLine(Pens.Orange, 277 + SHIFT, 140, 277 + SHIFT, 100);
                        wfg.DrawLine(Pens.Orange, 277 + SHIFT, 100, 396 + SHIFT, 100);
                        wfg.DrawLine(Pens.Orange, 396 + SHIFT, 100, 396 + SHIFT, 140);
                        wfg.DrawLine(Pens.Orange, 396 + SHIFT, 140, 436 + SHIFT, 140);
                    }
                    else // Slow speed
                    {
                        // Trapezoidal signal (output). One line represents one segment of the signal.
                        wfg.DrawLine(Pens.Orange, 40 + SHIFT, 140, 72 + SHIFT, 140);
                        wfg.DrawLine(Pens.Orange, 72 + SHIFT, 140, 86 + SHIFT, 100);
                        wfg.DrawLine(Pens.Orange, 86 + SHIFT, 100, 191 + SHIFT, 100);
                        wfg.DrawLine(Pens.Orange, 191 + SHIFT, 100, 205 + SHIFT, 140);
                        wfg.DrawLine(Pens.Orange, 205 + SHIFT, 140, 270 + SHIFT, 140);
                        wfg.DrawLine(Pens.Orange, 270 + SHIFT, 140, 284 + SHIFT, 100);
                        wfg.DrawLine(Pens.Orange, 284 + SHIFT, 100, 389 + SHIFT, 100);
                        wfg.DrawLine(Pens.Orange, 389 + SHIFT, 100, 403 + SHIFT, 140);
                        wfg.DrawLine(Pens.Orange, 403 + SHIFT, 140, 436 + SHIFT, 140);
                    }

                    Font perfont = new Font("Arial", 10, FontStyle.Regular, GraphicsUnit.Pixel);
                    wfg.DrawString("Vdda", perfont, Brushes.Black, new PointF(7 + SHIFT, 10));
                    wfg.DrawString("1.2V", perfont, Brushes.Green, new PointF(9 + SHIFT, 40));
                    wfg.DrawString("V+", perfont, Brushes.Blue, new PointF(18 + SHIFT, 60));
                    wfg.DrawString("0V", perfont, Brushes.Black, new PointF(18 + SHIFT, 70));
                    wfg.DrawString("Vddd", perfont, Brushes.Black, new PointF(7 + SHIFT, 95));
                    wfg.DrawString("Vssd", perfont, Brushes.Black, new PointF(9 + SHIFT, 135));
                    wfg.DrawString("out", perfont, Brushes.Orange, new PointF(17 + SHIFT, 115));
                }

                m_pbDiagram.Image = waveform;
            }
        }

        #endregion
    }
}
