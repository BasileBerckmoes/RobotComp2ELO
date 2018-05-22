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

namespace Scan_ADC_v2_10
{
    public class CyLineChart
    {
        protected string m_title;
        protected List<DataSeries> m_series = new List<DataSeries>();
        protected Hull m_initialHull = null;
        protected List<GridLine> m_xGrid = new List<GridLine>();
        protected List<GridLine> m_yGrid = new List<GridLine>();
        public List<Tick> m_xTicks = new List<Tick>();
        protected List<Tick> m_yTicks = new List<Tick>();

        protected Font m_font;

        protected RectangleF m_chartRect;
        protected RectangleF m_titleRect;
        protected RectangleF m_yLabelRect;
        protected RectangleF m_yTickRect;
        protected RectangleF m_graphRect;
        protected RectangleF m_keyRect;
        protected RectangleF m_xTickRect;
        protected RectangleF m_xLabelRect;

        public Color BackgroundColor { get; set; }
        public Color LabelColor { get; set; }
        public Color AxisColor { get; set; }
        public Color TickMinorColor { get; set; }
        public Color TickMajorColor { get; set; }
        public Color GridMinorColor { get; set; }
        public Color GridMajorColor { get; set; }

        public float AxisWidth { get; set; }
        public float TickMinorWidth { get; set; }
        public float TickMajorWidth { get; set; }

        public Matrix m_dataToScreen { get; private set; }

        public bool m_isDebug;

        public CyLineChart(string title, Font font, List<DataSeries> series,
            Hull initialHull, bool isDebug)
        {
            this.m_title = title;
            this.m_font = font;
            this.m_series = series;
            this.m_initialHull = initialHull;
            this.m_isDebug = isDebug;

            this.BackgroundColor = Color.White;
            this.LabelColor = Color.Black;
            this.AxisColor = Color.Black;
            this.TickMinorColor = Color.Black;
            this.TickMajorColor = Color.Black;
            this.GridMinorColor = Color.Gray;
            this.GridMajorColor = Color.Gray;

            this.AxisWidth = 2.0f;
            this.TickMinorWidth = 1.0f;
            this.TickMajorWidth = 1.0f;
        }

        public void Draw(Graphics g)
        {
            DrawStub(g, this.m_chartRect, this.BackgroundColor);
            DrawTitle(g);

            if (this.m_dataToScreen.IsInvertible)
            {
                DrawXLabels(g, this.m_xLabelRect);
                DrawYLabels(g, this.m_yLabelRect);
                if (this.m_series.Count > 1)
                {
                    DrawKey(g, this.m_keyRect);
                }
                DrawGrid(g, this.m_graphRect);
                DrawAxes(g, this.m_graphRect);
                DrawXTicks(g, this.m_xTickRect);
                DrawYTicks(g, this.m_yTickRect);
                DrawGraph(g);
            }
        }

        protected void DrawStub(Graphics g, RectangleF rect, Color color)
        {
            float margin = this.m_font.Height / 4;
            rect.Inflate(-margin, -margin);
            SolidBrush brush = new SolidBrush(color);
            g.FillRectangle(brush, rect);
        }

        protected void DrawTitle(Graphics g)
        {
            var format = new StringFormat();
            format.Alignment = StringAlignment.Center;
            format.LineAlignment = StringAlignment.Center;
            SolidBrush brush = new SolidBrush(this.LabelColor);
            g.DrawString(this.m_title, this.m_font, brush, this.m_titleRect, format);
        }

        protected void DrawXLabels(Graphics g, RectangleF rect)
        {
            var format = new StringFormat();
            format.Alignment = StringAlignment.Center;
            format.LineAlignment = StringAlignment.Center;
            SolidBrush brush = new SolidBrush(this.LabelColor);

            var y = rect.Top;

            foreach (var tick in this.m_xTicks)
            {
                var pTicks = new PointF[] { new PointF(tick.m_coord, 0) };
                this.m_dataToScreen.TransformPoints(pTicks);

                SizeF labelSize = g.MeasureString(tick.m_label, this.m_font);
                var point = new PointF(pTicks[0].X - labelSize.Width / 2, y);
                g.DrawString(tick.m_label, this.m_font, brush, point);
            }
        }

        protected void DrawKey(Graphics g, RectangleF rect)
        {
            var point = new PointF(
                rect.Left + this.m_font.Height / 2,
                rect.Top + (3 * this.m_font.Height) / 4);
            float nameWidthMax = 0;
            foreach (var dataSeries in this.m_series)
            {
                SizeF size = g.MeasureString(dataSeries.m_name, this.m_font);
                nameWidthMax = Math.Max(nameWidthMax, size.Width);
            }

            foreach (var dataSeries in this.m_series)
            {
                var brush = new SolidBrush(this.LabelColor);
                g.DrawString(dataSeries.m_name, this.m_font, brush, point);
                var p0 = new PointF(
                    rect.Left + nameWidthMax + this.m_font.Height / 2,
                    point.Y + this.m_font.Height / 2);
                var p1 = new PointF(rect.Right, point.Y + this.m_font.Height / 2);
                var pen = new Pen(dataSeries.m_color, dataSeries.m_width);
                g.DrawLine(pen, p0, p1);
                point = new PointF(point.X, point.Y + this.m_font.Height);
            }
        }

        protected void DrawYLabels(Graphics g, RectangleF rect)
        {
            var format = new StringFormat();
            format.Alignment = StringAlignment.Center;
            format.LineAlignment = StringAlignment.Center;
            SolidBrush brush = new SolidBrush(this.LabelColor);

            var x = rect.Right;

            foreach (var tick in this.m_yTicks)
            {
                var pTicks = new PointF[] { new PointF(0, tick.m_coord) };
                this.m_dataToScreen.TransformPoints(pTicks);

                SizeF labelSize = g.MeasureString(tick.m_label, this.m_font);
                var point = new PointF(
                    x - labelSize.Width - this.m_font.Height / 2, 
                    pTicks[0].Y - this.m_font.Height / 2);
                g.DrawString(tick.m_label, this.m_font, brush, point);
            }
        }

        protected void DrawGraph(Graphics g)
        {
            foreach (var dataSeries in this.m_series)
            {
                var points = TransformPoints(this.m_dataToScreen, dataSeries.m_series);
                var pen = new Pen(dataSeries.m_color, dataSeries.m_width);
                pen.LineJoin = LineJoin.Round;
                g.DrawLines(pen, points.ToArray());
            }
        }

        protected void DrawGrid(Graphics g, RectangleF rect)
        {
            var pen = new Pen(this.GridMinorColor, this.TickMinorWidth);

            var x0 = rect.Left;
            var x1 = rect.Right;

            var y0 = rect.Bottom;
            var y1 = rect.Top;

            foreach (var tick in this.m_xTicks)
            {
                var pTicks = new PointF[] { new PointF(tick.m_coord, 0) };
                this.m_dataToScreen.TransformPoints(pTicks);
                var p0 = new PointF(pTicks[0].X, y0);
                var p1 = new PointF(pTicks[0].X, y1);
                g.DrawLine(pen, p0, p1);
            }

            foreach (var tick in this.m_yTicks)
            {
                var pTicks = new PointF[] { new PointF(0, tick.m_coord) };
                this.m_dataToScreen.TransformPoints(pTicks);
                var p0 = new PointF(x0, pTicks[0].Y);
                var p1 = new PointF(x1, pTicks[0].Y);
                g.DrawLine(pen, p0, p1);
            }
        }

        protected void DrawAxes(Graphics g, RectangleF rect)
        {
            var pen = new Pen(this.AxisColor, this.AxisWidth);

            var px0 = new PointF(rect.Left, rect.Bottom);
            var px1 = new PointF(rect.Right, rect.Bottom);
            g.DrawLine(pen, px0, px1);

            var py0 = new PointF(rect.Left, rect.Top);
            var py1 = new PointF(rect.Left, rect.Bottom);
            g.DrawLine(pen, py0, py1);
        }

        protected void DrawXTicks(Graphics g, RectangleF rect)
        {
            var majorPen = new Pen(this.TickMajorColor, this.TickMajorWidth);
            var minorPen = new Pen(this.TickMinorColor, this.TickMinorWidth);

            var majorY0 = rect.Bottom;
            var minorY0 = (rect.Top + rect.Bottom) / 2;
            var y1 = rect.Top;

            foreach (var tick in this.m_xTicks)
            {
                var pTicks = new PointF[] { new PointF(tick.m_coord, 0) };
                this.m_dataToScreen.TransformPoints(pTicks);

                float y0 = (tick.m_emphasis == CyLineChart.Emphasis.MAJOR) ? majorY0 : minorY0;
                var pen = (tick.m_emphasis == CyLineChart.Emphasis.MAJOR) ? majorPen : minorPen;
                var p0 = new PointF(pTicks[0].X, y0);
                var p1 = new PointF(pTicks[0].X, y1);
                g.DrawLine(pen, p0, p1);
            }
        }

        protected void DrawYTicks(Graphics g, RectangleF rect)
        {
            Pen majorPen = new Pen(this.TickMajorColor, this.TickMajorWidth);
            Pen minorPen = new Pen(this.TickMinorColor, this.TickMinorWidth);

            var majorX0 = rect.Left;
            var minorX0 = (rect.Left + rect.Right) / 2;
            var x1 = rect.Right;

            foreach (var tick in this.m_yTicks)
            {
                var pTicks = new PointF[] { new PointF(0, tick.m_coord) };
                this.m_dataToScreen.TransformPoints(pTicks);

                float x0 = (tick.m_emphasis == CyLineChart.Emphasis.MAJOR) ? majorX0 : minorX0;
                var pen = (tick.m_emphasis == CyLineChart.Emphasis.MAJOR) ? majorPen : minorPen;
                var p0 = new PointF(x0, pTicks[0].Y);
                var p1 = new PointF(x1, pTicks[0].Y);
                g.DrawLine(pen, p0, p1);
            }
        }

        public virtual void Resize(RectangleF chartRect)
        {
            SizeRectangles(chartRect);
            this.m_dataToScreen = CalcGraphTransform(this.m_series, this.m_graphRect);
        }

        protected void SizeRectangles(RectangleF chartRect)
        {
            float titleHeight = 2 * this.m_font.Height;
            float yLabelWidth = 4 * this.m_font.Height;
            float yTickWidth = this.m_font.Height;
            float xTickHeight = this.m_font.Height;
            float xLabelHeight = 2 * this.m_font.Height;
            float keyHeight = this.m_xTickRect.Height + this.m_xLabelRect.Height;
            float yLabelHeight = chartRect.Height - titleHeight - xTickHeight - xLabelHeight;
            float xLabelWidth = chartRect.Width - yLabelWidth - yTickWidth;
            float graphMargin = 2 * this.m_font.Height;
            float graphWidth = chartRect.Width - yLabelWidth - yTickWidth - graphMargin;

            this.m_chartRect = chartRect;
            this.m_titleRect = new RectangleF(
                chartRect.X, chartRect.Y,
                chartRect.Width, titleHeight);
            this.m_yLabelRect = new RectangleF(
                chartRect.X, chartRect.Y + titleHeight,
                yLabelWidth, yLabelHeight);
            this.m_yTickRect = new RectangleF(
                chartRect.X + yLabelWidth, chartRect.Y + titleHeight,
                yTickWidth, yLabelHeight);
            this.m_graphRect = new RectangleF(
                chartRect.X + yLabelWidth + yTickWidth + graphMargin, chartRect.Y + titleHeight,
                chartRect.Width - yLabelWidth - yTickWidth - 2 * graphMargin, yLabelHeight);
            this.m_keyRect = new RectangleF(
                chartRect.X, chartRect.Y + titleHeight + yLabelHeight,
                yLabelWidth + yTickWidth, xTickHeight + xLabelHeight);
            this.m_xTickRect = new RectangleF(
                chartRect.X + yLabelWidth + yTickWidth,
                chartRect.Y + titleHeight + yLabelHeight,
                chartRect.Width - yLabelWidth - yTickWidth, xTickHeight);
            this.m_xLabelRect = new RectangleF(
                chartRect.X + yLabelWidth + yTickWidth,
                chartRect.Y + titleHeight + yLabelHeight + xTickHeight,
                chartRect.Width - yLabelWidth - yTickWidth, xLabelHeight);
        }

        protected Matrix CalcGraphTransform(List<DataSeries> series, RectangleF rect)
        {
            if (series.Count == 0)
            {
                return new Matrix();
            }

            Hull dataHull = this.m_initialHull;
            if (dataHull == null)
            {
                dataHull = new Hull(series[0].m_series);
            }
            foreach (DataSeries dataSeries in series)
            {
                dataHull.Grow(dataSeries.m_series);
            }

            RectangleF dataRect = new RectangleF(
                dataHull.MinX, dataHull.MinY,
                dataHull.MaxX - dataHull.MinX, dataHull.MaxY - dataHull.MinY);

            var dataToScreen = new Matrix(dataRect, new PointF[] {
                new PointF(rect.Left, rect.Bottom),     // Upper left of target rectangle.
                new PointF(rect.Right, rect.Bottom),    // Upper right of target rectangle.
                new PointF(rect.Left, rect.Top)         // Lower left of target rectangle.
            });

            return dataToScreen;
        }

        protected static List<PointF> TransformPoints(Matrix matrix, List<PointF> pointList)
        {
            var points = pointList.ToArray();
            matrix.TransformPoints(points);
            return new List<PointF>(points);
        }


        public enum Emphasis
        {
            MINOR = 0,
            MAJOR,
        }

        public struct DataSeries
        {
            public string m_name;
            public List<PointF> m_series;
            public Color m_color;
            public float m_width;

            public DataSeries(string name, List<PointF> series, Color color, float width)
            {
                this.m_name = name;
                this.m_series = series;
                this.m_color = color;
                this.m_width = width;
            }
        }

        public struct GridLine
        {
            public float m_coord;
            public Emphasis m_emphasis;

            public GridLine(float coord, Emphasis emphasis)
            {
                this.m_coord = coord;
                this.m_emphasis = emphasis;
            }
        }

        public struct Tick
        {
            public float m_coord;
            public string m_label;
            public Emphasis m_emphasis;

            public Tick(float coord, string label, Emphasis emphasis)
            {
                this.m_coord = coord;
                this.m_label = label;
                this.m_emphasis = emphasis;
            }
        }

        public class Hull
        {
            public float MinX { get; set; }
            public float MaxX { get; set; }
            public float MinY { get; set; }
            public float MaxY { get; set; }

            public Hull(float minX, float maxX, float minY, float maxY)
            {
                this.MinX = minX;
                this.MaxX = maxX;
                this.MinY = minY;
                this.MaxY = maxY;
            }

            public Hull(List<PointF> points)
            {
                if (points.Count > 0)
                {
                    this.MinX = points[0].X;
                    this.MaxX = points[0].X;
                    this.MinY = points[0].Y;
                    this.MaxY = points[0].Y;
                    this.Grow(points);
                }
            }

            public void Grow(List<PointF> points)
            {
                foreach (var point in points)
                {
                    this.MinX = Math.Min(this.MinX, point.X);
                    this.MaxX = Math.Max(this.MaxX, point.X);
                    this.MinY = Math.Min(this.MinY, point.Y);
                    this.MaxY = Math.Max(this.MaxY, point.Y);
                }
            }
        }
    }
}