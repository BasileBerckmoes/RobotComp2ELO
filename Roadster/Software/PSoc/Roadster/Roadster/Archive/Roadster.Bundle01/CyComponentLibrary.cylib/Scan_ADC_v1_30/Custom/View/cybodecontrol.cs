/*******************************************************************************
* Copyright 2011-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Text;
using System.Windows.Forms;

namespace Scan_ADC_v1_30
{
    public class CyBodeControl : UserControl
    {
        private CyParameters m_params;
        private int ConfigNumber { get; set; }
        private enum HAlign { Left, Center, Right }
        private enum VAlign { Top, Center, Bottom }

        private Bitmap m_bitmap;
        private bool m_enableRedraw = false;

        public Color TextColor { get; set; }
        public Color GraphColor { get; set; }

        public bool EnableRedraw
        {
            get
            {
                return this.m_enableRedraw;
            }
            set
            {
                this.m_enableRedraw = value;
            }
        }

        private EventHandler onFilterChanged;

        public event EventHandler FilterChanged
        {
            add { onFilterChanged += value; }
            remove { onFilterChanged -= value; }
        }

        protected virtual void OnFilterChanged(EventArgs e)
        {
            if (onFilterChanged != null)
            {
                onFilterChanged.Invoke(this, e);
            }
        }

        public CyBodeControl(CyParameters parameters, int configNum)
        {
            this.m_params = parameters;
            this.ConfigNumber = configNum;
            this.Load += CyBodeControl_Load;
            this.SizeChanged += CyBodeControl_SizeChanged;
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            Graphics g = e.Graphics;
            g.DrawImage(this.m_bitmap, new PointF(0, 0));
        }

        #region Events

        private void CyBodeControl_Load(object sender, EventArgs e)
        {
            RefreshAll();
        }

        private void CyBodeControl_SizeChanged(object sender, EventArgs e)
        {
            RefreshAll();
        }

        #endregion Events

        public void RefreshAll()
        {
            if (this.EnableRedraw)
            {
                RedrawTransferDiagram();
                Invalidate();
            }
        }

        private void RedrawTransferDiagram()
        {
            CyConfigModel config = m_params.GetConfig(ConfigNumber);

            this.m_bitmap = new Bitmap(this.Width, this.Height);
            using (Graphics g = Graphics.FromImage(this.m_bitmap))
            {
                ToHighQuality(g);

                g.FillRectangle(Brushes.White, 0, 0, m_bitmap.Width, m_bitmap.Height);
                using (Pen penBorder = new Pen(Color.Black, 1))
                {
                    g.DrawRectangle(penBorder, 0, 0, m_bitmap.Width, m_bitmap.Height);
                }

                int margin = this.FontHeight / 2;
                int amplitudeHeight = this.Height / 2;
                RectangleF amplitudeRect = new RectangleF(
                    0, 0, this.Width, amplitudeHeight);
                RectangleF phaseRect = new RectangleF(
                    0, amplitudeHeight, this.Width, this.Height - amplitudeHeight);

                DrawAmplitudeDiagram(g, amplitudeRect, config);
                DrawPhaseDiagram(g, phaseRect, config);
            }
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

        private void DrawAmplitudeDiagram(Graphics g, RectangleF rect, CyConfigModel config)
        {
            CyAmplitudeChart chart = new CyAmplitudeChart(
                config, "Amplitude Response", this.Font, this.m_params.Debug);
            chart.Resize(rect);
            chart.Draw(g);
        }

        private void DrawPhaseDiagram(Graphics g, RectangleF rect, CyConfigModel config)
        {
            CyPhaseChart chart = new CyPhaseChart(
                config, "Phase Response", this.Font, this.m_params.Debug);
            chart.Resize(rect);
            chart.Draw(g);
        }

        private System.Drawing.SizeF BoundingSizeF(Graphics g, List<string> lines)
        {
            System.Drawing.SizeF totalSize = new System.Drawing.SizeF();

            foreach (string line in lines)
            {
                System.Drawing.SizeF lineSize = g.MeasureString(line, this.Font);
                totalSize.Width = Math.Max(lineSize.Width, totalSize.Width);
                totalSize.Height += lineSize.Height;
            }

            return totalSize;
        }

        private void DrawText(
            Graphics g, Brush brush, PointF textPoint,
            string line, HAlign xalign, VAlign yalign)
        {
            List<string> lines = new List<string>();
            lines.Add(line);
            DrawText(g, brush, textPoint, lines, xalign, yalign);
        }

        private void DrawText(
            Graphics g, Brush brush, PointF textPoint,
            List<string> lines, HAlign xalign, VAlign yalign)
        {
            SizeF textSize = BoundingSizeF(g, lines);
            switch (xalign)
            {
                case HAlign.Right:
                    textPoint.X -= textSize.Width;
                    break;
                case HAlign.Center:
                    textPoint.X -= textSize.Width / 2;
                    break;
            }
            switch (yalign)
            {
                case VAlign.Bottom:
                    textPoint.Y -= textSize.Height;
                    break;
                case VAlign.Center:
                    textPoint.Y -= textSize.Height / 2;
                    break;
            }
            //Font myFont = new Font("Courier New", 12, FontStyle.Regular);
            Point snapPoint = new Point((int)textPoint.X, (int)textPoint.Y);
            foreach (string line in lines)
            {
                g.DrawString(line, this.Font, brush, snapPoint);
                snapPoint.Y += this.FontHeight;
            }
        }
    }
}