/*******************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Text;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

// The namespace is required to have the same name as the component for a customizer.
namespace UAB_VDAC_v1_10
{
    public class CyTransferControl : UserControl
    {
        private enum HAlign { Left, Center, Right }
        private enum VAlign { Top, Center, Bottom }

        private Bitmap m_bitmap;
        private Bitmap m_graphBitmap;
        private CyParameters m_parameters;
        private PointF codeVoltPair;
        private System.Drawing.Color m_colorText = System.Drawing.Color.Black;
        private System.Drawing.Color m_colorAxis = System.Drawing.Color.Black;
        private System.Drawing.Color m_colorGuide = System.Drawing.Color.DarkGray;
        private System.Drawing.Color m_colorGraph = System.Drawing.Color.Green;
        private System.Drawing.Color m_colorDot   = System.Drawing.Color.Red;

        private float mouseLocationX = 0;
        private bool m_moveDynamicElements = false;

        private EventHandler onCodeVoltPairChanged;

        public CyTransferDiagram m_diagram;

        #region Control Properties
        public PointF CodeVoltPair
        {
            get
            {
                return codeVoltPair;
            }
            set
            {
                if (value != codeVoltPair)
                {
                    codeVoltPair = value;
                    OnCodeVoltPairChanged(EventArgs.Empty);
                }
            }
        }
        public System.Drawing.Color TextColor
        {
            get
            {
                return m_colorText;
            }
            set
            {
                m_colorText = value;
            }
        }

        public System.Drawing.Color AxisColor
        {
            get
            {
                return m_colorAxis;
            }
            set
            {
                this.m_colorAxis = value;
            }
        }

        public System.Drawing.Color GuideColor
        {
            get
            {
                return m_colorGuide;
            }
            set
            {
                this.m_colorGuide = value;
            }
        }

        public System.Drawing.Color GraphColor
        {
            get
            {
                return m_colorGraph;
            }
            set
            {
                m_colorGraph = value;
            }
        }
        #endregion

        public event EventHandler CodeVoltPairChanged
        {
            add
            {
                onCodeVoltPairChanged += value;
            }
            remove
            {
                onCodeVoltPairChanged -= value;
            }
        }
        protected virtual void OnCodeVoltPairChanged(EventArgs e)
        {
            if (onCodeVoltPairChanged != null)
            {
                onCodeVoltPairChanged.Invoke(this, e);
            }
        }

        private delegate string CalcTransferGraphLabel();

        public CyTransferControl(CyParameters parameters)
        {
            this.m_parameters = parameters;
            this.m_diagram = new CyTransferDiagram(m_parameters);

            this.TabStop = false;
            this.DoubleBuffered = true;

            this.Load        += CyTransferControl_Load;
            this.SizeChanged += CyTransferControl_SizeChanged;
            this.MouseEnter  += CyTransferControl_MouseEnter;
            this.MouseDown   += CyTransferControl_MouseDown;
            this.MouseMove   += CyTransferControl_MouseMove;
            this.MouseUp     += CyTransferControl_MouseUp;
            this.MouseLeave  += CyTransferControl_MouseLeave;
            
            this.m_parameters.m_sideEffects += CyTransferControl_ParamSideEffects;
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            Graphics g = e.Graphics;
            g.DrawImage(this.m_bitmap, new PointF(0, 0));
        }

        #region Events (especially mouse events)
        void CyTransferControl_Load(object sender, EventArgs e)
        {
            RefreshAll();
        }

        void CyTransferControl_SizeChanged(object sender, EventArgs e)
        {
            RefreshAll();
        }

        void CyTransferControl_MouseEnter(object sender, EventArgs e)
        {
            this.m_moveDynamicElements = false;
        }

        void CyTransferControl_MouseDown(object sender, MouseEventArgs e)
        {
            mouseLocationX = e.X;

            this.m_moveDynamicElements = true;
            CalculateDynamicElements(e);
        }

        void CyTransferControl_MouseMove(object sender, MouseEventArgs e)
        {
            //Only scroll if the move has been 10 mor more pixels.
            if (e.X - mouseLocationX > 10 || mouseLocationX - e.X > 10)
            {
                mouseLocationX = e.X;
                if (this.m_moveDynamicElements)
                {
                    CalculateDynamicElements(e);
                }
            }
        }
        /* Remove dot-related */
        
        private void CalculateDynamicElements(MouseEventArgs e)
        {
            if (0 <= e.X && e.X <= this.m_bitmap.Width &&
                0 <= e.Y && e.Y <= this.m_bitmap.Height)
            {
                PointF clickPoint = new PointF(e.X, e.Y);
                clickPoint = this.m_diagram.SnapToTransferGraph(clickPoint);
                
                // Draw the coordinates.
                CodeVoltPair = this.m_diagram.graphPointToCVPair(clickPoint);
                
                // Trigger a redraw.
                Invalidate();
            }
        }

        void CyTransferControl_MouseUp(object sender, MouseEventArgs e)
        {
            this.m_moveDynamicElements = false;
        }

        void CyTransferControl_MouseLeave(object sender, EventArgs e)
        {
            this.m_moveDynamicElements = false;
        }
        #endregion
        void CyTransferControl_ParamSideEffects()
        {
            RefreshAll();
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

        public void RefreshAll()
        {
            RedrawTransferDiagram();
            Invalidate();
        }

        private void RedrawTransferDiagram()
        {
            this.m_bitmap = new Bitmap(this.Width, this.Height);
            this.m_diagram = new CyTransferDiagram(this.m_parameters);

            using (Graphics g = Graphics.FromImage(this.m_bitmap))
            {
                ToHighQuality(g);

                g.FillRectangle(Brushes.White, 0, 0, m_bitmap.Width, m_bitmap.Height);
                using (Pen penBorder = new Pen(Color.Black, 1))
                {
                    g.DrawRectangle(penBorder, 0, 0, m_bitmap.Width, m_bitmap.Height);
                }


                int margin = this.FontHeight / 2;
                int exprHeight = 3 * this.FontHeight + 2 * margin;
                RectangleF rangeExprRect = new RectangleF(0, 0, this.Width, exprHeight);
                RectangleF diagramRect   = new RectangleF(0, exprHeight, this.Width, this.Height - exprHeight);
                rangeExprRect.Inflate(-margin, -margin);
                diagramRect.Inflate(-margin, -margin);

                DrawRangeExpr(g, rangeExprRect);
                DrawDiagram(g, diagramRect);
            }

            this.m_graphBitmap = new Bitmap(this.m_bitmap);
        }

        private void DrawRangeExpr(Graphics g, RectangleF rect)
        {
            PointF topLeft = new PointF(rect.Left, rect.Top);
            PointF topRight = new PointF(rect.Right, rect.Top);
            Brush textBrush = new SolidBrush(this.m_colorText);

            List<string> d_lines = new List<string>();
            d_lines.Add(this.m_diagram.RangeDLowLabel);
            d_lines.Add(this.m_diagram.RangeDMidLabel);
            d_lines.Add(this.m_diagram.RangeDHighLabel);
 
            List<string> lsb_lines = new List<string>();
            lsb_lines.Add(this.m_diagram.RangeLsbLabel);

            DrawText(g, textBrush, topLeft, d_lines, HAlign.Left, VAlign.Top);
            DrawText(
                g, textBrush, topRight, lsb_lines, HAlign.Right, VAlign.Top);
        }

        private void DrawDiagram(Graphics g, RectangleF rect)
        {
            int headerHeight = this.FontHeight;
            int footerHeight = 2 * this.FontHeight;

            RectangleF headerRect = new RectangleF(
                rect.Left, rect.Top, rect.Width, headerHeight);
            RectangleF bodyRect = new RectangleF(
                rect.Left, headerRect.Bottom,
                rect.Width, rect.Height - headerHeight - footerHeight);
            RectangleF footerRect = new RectangleF(
                rect.Left, bodyRect.Bottom, rect.Width, footerHeight);

            this.m_diagram.Resize(bodyRect, this.Font);

            DrawDiagramHeader(g, headerRect);
            DrawDiagramBody(g, bodyRect);
            DrawDiagramFooter(g, footerRect);
        }

        private void DrawDiagramHeader(Graphics g, RectangleF rect)
        {
            PointF topLeft = new PointF(this.m_diagram.m_vAxisPoly[0].X, rect.Top);
            PointF topMiddle = new PointF((rect.Left + rect.Right) / 2, rect.Top);
            Brush textBrush = new SolidBrush(this.m_colorText);

            List<string> left_lines = new List<string>();
            left_lines.Add(this.m_diagram.HeaderLeftLabel);

            List<string> middle_lines = new List<string>();
            middle_lines.Add(this.m_diagram.HeaderMidLabel);

            DrawText(g, textBrush,
                topLeft, left_lines, HAlign.Center, VAlign.Top);
            DrawText(g, textBrush,
                topMiddle, middle_lines, HAlign.Center, VAlign.Top);
        }

        private void DrawDiagramBody(Graphics g, RectangleF rect)
        {
            /* Draw guide grids */
            using (Pen penGuide = new Pen(this.m_colorGuide, 1))
            {
                g.DrawLines(penGuide, this.m_diagram.m_leftGuidePoly);
                g.DrawLines(penGuide, this.m_diagram.m_rightGuidePoly);
            }
            /* Draw Axis lines */
            using (Pen penAxis = new Pen(this.m_colorAxis, 2))
            {
                g.DrawLines(penAxis, this.m_diagram.m_hAxisPoly);
                g.DrawLines(penAxis, this.m_diagram.m_vAxisPoly);
            }
            /* Draw Transfer Function */
            using (Pen penTransfer = new Pen(this.m_colorGraph, 2))
            {
                g.DrawLines(penTransfer, this.m_diagram.m_transferGraphPoly);
            }

            /* Draw DefaultOut grid */
            using (Pen penTransfer = new Pen(this.m_colorDot, 2))
            {
                g.DrawLines(penTransfer, this.m_diagram.m_defaultOutPoly);
            }

            /* Draw diagram labels.
             * Vmax is same for all modes.
             * Vmin, VoutCenter labels only for the signed modes.*/
            Brush textBrush = new SolidBrush(m_colorText);
            PointF textPoint = this.m_diagram.m_rightGuidePoly[0];
            DrawText(g, textBrush, textPoint, this.m_diagram.VoutMaxLabel, HAlign.Right, VAlign.Center);

            textBrush = new SolidBrush(m_colorDot);
            textPoint = m_diagram.m_defaultOutPoly[1];
            DrawText(g, textBrush, textPoint, this.m_diagram.DefaultOutLabel, HAlign.Left, VAlign.Top);

            if (this.m_diagram.IsDacInputSigned)
            {
                textBrush = new SolidBrush(m_colorText);
                textPoint = this.m_diagram.m_leftGuidePoly[2];
                DrawText(g, textBrush, textPoint, this.m_diagram.VoutMinLabel,
                    HAlign.Left, VAlign.Center);

                textBrush = new SolidBrush(m_colorText);
                textPoint = m_diagram.m_transferGraphPoly[m_diagram.m_transferGraphPoly.Length / 2];
                DrawText(g, textBrush, textPoint, this.m_diagram.VoutCenterLabel, HAlign.Right, VAlign.Bottom);
            }

            /* Draw default lines */
            
        }

        private void DrawDiagramFooter(Graphics g, RectangleF rect)
        {
            /* Define left, middle, and right points. */
            PointF topLeft   = new PointF(this.m_diagram.m_transferGraphPoly[0].X, rect.Top);
            PointF topMiddle = new PointF(this.m_diagram.m_vAxisPoly[0].X, rect.Top);
            PointF topRight = new PointF(this.m_diagram.m_transferGraphPoly[this.m_diagram.m_transferGraphPoly.Length - 1].X, rect.Top);

            /* Get left, middle, and right Strings*/
            List<string> left_lines = new List<string>();
            left_lines.Add(this.m_diagram.FooterLowValueLabel);
            left_lines.Add(this.m_diagram.FooterLowCodeLabel);

            List<string> middle_lines = new List<string>();
            middle_lines.Add(this.m_diagram.FooterMidValueLabel);
            middle_lines.Add(this.m_diagram.FooterMidCodeLabel);

            List<string> right_lines = new List<string>();
            right_lines.Add(this.m_diagram.FooterHighValueLabel);
            right_lines.Add(this.m_diagram.FooterHighCodeLabel);

            /* Draw left, middle, and right */
            Brush textBrush = new SolidBrush(this.m_colorText);
            DrawText(g, textBrush, topLeft,   left_lines,   HAlign.Center, VAlign.Top);
            DrawText(g, textBrush, topMiddle, middle_lines, HAlign.Center, VAlign.Top);
            DrawText(g, textBrush, topRight,  right_lines,  HAlign.Center, VAlign.Top);
        }

        private System.Drawing.SizeF BoundingSizeF(Graphics g, string line)
        {
            System.Drawing.SizeF size = g.MeasureString(line, this.Font);

            return size;
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
            Point snapPoint = new Point((int) textPoint.X, (int) textPoint.Y);
            foreach (string line in lines)
            {
                g.DrawString(line, this.Font, brush, snapPoint);
                snapPoint.Y += this.FontHeight;
            }
        }
    }
}
