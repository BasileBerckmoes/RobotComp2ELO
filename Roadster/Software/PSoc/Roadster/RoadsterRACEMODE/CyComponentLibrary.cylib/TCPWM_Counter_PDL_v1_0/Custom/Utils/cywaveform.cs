/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Drawing;
using System.Diagnostics;
using System.Drawing.Drawing2D;
using System.Collections.Generic;

namespace TCPWM_Counter_PDL_v1_0.Utils
{
    internal class CyWaveform : IDisposable
    {
        public const int STAIR_HEIGHT = 20;
        public const int ARROW_HEIGHT = 15;
        public const int LINES_X = 110;
        public const int MAX_STAIR_COUNT = 6;
        private const int TEXT_X = LINES_X - 4;
        private const int fontIncrease96Dpi = 3;

        private Graphics m_g;
        private uint m_period;
        private int m_waveformWidth;
        private CyEnums.CyCountDirection m_direction;

        private Font m_normalFont = new Font("Arial", 7, FontStyle.Regular);
        private Font m_smallFont = new Font("Arial", 6, FontStyle.Regular);
        private Font m_largeFont = new Font("Arial", 10, FontStyle.Regular);

        public CyWaveform(Graphics g, int waveformWidth, CyEnums.CyCountDirection direction, uint period)
        {
            m_g = g;
            m_waveformWidth = waveformWidth;
            m_direction = direction;
            m_period = period;
            m_g.Clear(Color.White);
            
            // Increase font size for 96Dpi
            if (g!= null && g.DpiX == 96 && g.DpiY == 96)
            {
                m_normalFont = new Font(m_normalFont.FontFamily, m_normalFont.Size + fontIncrease96Dpi, FontStyle.Regular);
                m_smallFont = new Font(m_smallFont.FontFamily, m_smallFont.Size + fontIncrease96Dpi, FontStyle.Regular);
                m_largeFont = new Font(m_largeFont.FontFamily, m_largeFont.Size + fontIncrease96Dpi, FontStyle.Regular);

            }
        }

        public void DrawLine(int lineY, int[] arrowPositions, CyEStairPart stairPart = CyEStairPart.Beginning, string text = "")
        {
            using (Pen pen = new Pen(Color.Black))
            {
                // Draw line
                m_g.DrawLine(pen, LINES_X, lineY, m_waveformWidth, lineY);
                DrawText(text, TEXT_X, lineY, StringAlignment.Far, CyEFontSize.Normal, CyETextDockStyle.Top);

                // Draw arrows
                AdjustableArrowCap adjCap = new AdjustableArrowCap(4, 4, true);
                pen.EndCap = System.Drawing.Drawing2D.LineCap.Custom;
                pen.CustomEndCap = adjCap;
                int stairX;
                for (int i = 0; i < arrowPositions.Length; i++)
                {
                    switch (stairPart)
                    {
                        case CyEStairPart.Beginning:
                            stairX = arrowPositions[i];
                            break;
                        case CyEStairPart.Middle:
                            stairX = arrowPositions[i] + STAIR_HEIGHT / 2;
                            break;
                        case CyEStairPart.End:
                            stairX = arrowPositions[i] + STAIR_HEIGHT;
                            break;
                        default:
                            Debug.Fail("unhandled enum item.");
                            stairX = arrowPositions[i];
                            break;
                    }
                    m_g.DrawLine(pen, stairX, lineY, stairX, lineY - ARROW_HEIGHT);
                }
            }
        }

        public int[] DrawStairs(int y)
        {
            int stairCount = GetStairCount();
            int xx = LINES_X;
            int yy = y;
            int periodMaxY = yy - 5;
            int periodMinY = yy + STAIR_HEIGHT * stairCount - STAIR_HEIGHT;

            switch (m_direction)
            {
                case CyEnums.CyCountDirection.COUNT_UP:
                    yy += STAIR_HEIGHT * stairCount - STAIR_HEIGHT;
                    while (xx <= m_waveformWidth)
                    {
                        DrawStairs(stairCount, m_direction, ref xx, ref yy);
                        int yy2 = yy + STAIR_HEIGHT * (stairCount - 1);
                        m_g.DrawLine(Pens.Black, xx, yy, xx, yy2);
                        yy = yy2;
                    }
                    break;
                case CyEnums.CyCountDirection.COUNT_DOWN:
                    while (xx <= m_waveformWidth)
                    {
                        DrawStairs(stairCount, m_direction, ref xx, ref yy);
                        int yy2 = yy - STAIR_HEIGHT * (stairCount - 1);
                        m_g.DrawLine(Pens.Black, xx, yy, xx, yy2);
                        yy = yy2;
                    }
                    break;
                case CyEnums.CyCountDirection.COUNT_UPDOWN0:
                case CyEnums.CyCountDirection.COUNT_UPDOWN1:
                    yy += STAIR_HEIGHT * stairCount - STAIR_HEIGHT;
                    while (xx <= m_waveformWidth)
                    {
                        if (xx != LINES_X)
                            xx -= STAIR_HEIGHT;
                        DrawStairs(stairCount, CyEnums.CyCountDirection.COUNT_UP, ref xx, ref yy);
                        if (m_period > 0)
                        {
                            xx -= STAIR_HEIGHT;
                        }
                        DrawStairs(stairCount, CyEnums.CyCountDirection.COUNT_DOWN, ref xx, ref yy);
                    }
                    break;
                default:
                    Debug.Fail("unhandled enum item.");
                    break;
            }

            if (m_period > 0)
            {
                DrawText(m_period.ToString(), TEXT_X, periodMaxY, StringAlignment.Far, CyEFontSize.Normal);
            }
            DrawText("0", TEXT_X, periodMinY, StringAlignment.Far, CyEFontSize.Normal, CyETextDockStyle.Top);
            DrawText("counter", TEXT_X - 8, periodMaxY + stairCount * STAIR_HEIGHT / 2 - 4, // offset to show the label exactly in the center 
                StringAlignment.Far, CyEFontSize.Normal, CyETextDockStyle.Top);

            return GetStairsPositions(null);
        }

        public int GetStairCount()
        {
            return (m_period < MAX_STAIR_COUNT ? (int)m_period : MAX_STAIR_COUNT) + 1;
        }

        private List<int> DrawStairs(int count, CyEnums.CyCountDirection direction, ref int x, ref int y)
        {
            int x1 = x;
            int y1 = y;
            int x2 = x;
            int y2 = y;
            List<int> stairsXCoordinates = new List<int>();

            int lineCount = count - 1; // minus 1 because first line is a stair
            lineCount *= 2;            // multiply by 2 because one stair has two lines
            if (lineCount % 2 == 0)
                lineCount++;           // add one line if the line count is odd to finish last stair

            for (int i = 0; i < lineCount; i++)
            {
                if (i % 2 == 0)
                {
                    x2 += STAIR_HEIGHT;
                }
                else
                {
                    switch (direction)
                    {
                        case CyEnums.CyCountDirection.COUNT_UP:
                            y2 -= STAIR_HEIGHT;
                            break;
                        case CyEnums.CyCountDirection.COUNT_DOWN:
                            y2 += STAIR_HEIGHT;
                            break;
                        default:
                            Debug.Fail("unhandled enum type. use UP or DOWN only in the private method.");
                            break;
                    }
                }

                m_g.DrawLine(Pens.Black, x1, y1, x2, y2);
                if (x1 != x2)
                    stairsXCoordinates.Add(x1);

                x1 = x2;
                y1 = y2;
            }

            x = x2;
            y = y2;
            return stairsXCoordinates;
        }

        public void DrawRectangle(int width, int height, int rectY, string text, string title, int rectX = LINES_X)
        {
            SizeF titleSize = m_g.MeasureString(title, m_normalFont);
            SizeF textSize = m_g.MeasureString(text, m_smallFont);
            PointF textPos = new PointF(rectX + width / 2 - textSize.Width / 2, rectY + height / 2 - textSize.Height / 2);

            DrawText(title, TEXT_X, (int)(rectY + titleSize.Height / 2), StringAlignment.Far, CyEFontSize.Normal, CyETextDockStyle.None);

            m_g.DrawRectangle(Pens.Black, rectX, rectY, width, height);
            m_g.DrawString(text, m_smallFont, Brushes.Black, textPos);
        }

        public void DrawRectanglesByStairs(int[] stairs, int height, int rectY, string[] text, string title,
            CyEStairPart stairPart = CyEStairPart.Beginning)
        {
            int rectWidth;
            int rectX = LINES_X;
            SizeF titleSize = m_g.MeasureString(title, m_normalFont);
            DrawText(title, TEXT_X, (int)(rectY + titleSize.Height / 2), StringAlignment.Far, CyEFontSize.Normal, CyETextDockStyle.None);

            for (int i = 0; i < stairs.Length; i++)
            {
                rectWidth = (i > 0) ? stairs[i] - stairs[i - 1] - STAIR_HEIGHT : stairs[i] - LINES_X;

                switch (stairPart)
                {
                    case CyEStairPart.Beginning:
                        break;
                    case CyEStairPart.Middle:
                        rectWidth += STAIR_HEIGHT / 2;
                        break;
                    case CyEStairPart.End:
                        rectWidth += STAIR_HEIGHT;
                        break;
                    default:
                        Debug.Fail("unhandled enum item.");
                        break;
                }
                DrawRectangle(rectWidth, height, rectY, text[i], "", rectX);
                rectX += rectWidth;
            }
        }

        public void DrawText(string text, int x, int y, StringAlignment alignment = StringAlignment.Near,
            CyEFontSize fontSize = CyEFontSize.Normal, CyETextDockStyle dockStyle = CyETextDockStyle.None)
        {
            using (StringFormat sf = new StringFormat())
            {
                sf.Alignment = alignment;
                Font font = m_normalFont;
                switch (fontSize)
                {
                    case CyEFontSize.Small:
                        font = m_smallFont;
                        break;
                    case CyEFontSize.Normal:
                        font = m_normalFont;
                        break;
                    case CyEFontSize.Large:
                        font = m_largeFont;
                        break;
                    default:
                        Debug.Fail("unhandled enum item.");
                        break;
                }

                SizeF textSize = m_g.MeasureString(text, font);
                switch (dockStyle)
                {
                    case CyETextDockStyle.None:
                        break;
                    case CyETextDockStyle.Top:
                        y -= (int)textSize.Height;
                        break;
                    case CyETextDockStyle.Bottom:
                        y += (int)textSize.Height;
                        break;
                    case CyETextDockStyle.HalfTop:
                        y -= (int)textSize.Height / 2;
                        break;
                    case CyETextDockStyle.HalfBottom:
                        y += (int)textSize.Height / 2;
                        break;
                    default:
                        Debug.Fail("unhandled enum item.");
                        break;
                }
                m_g.DrawString(text, font, Brushes.Black, x, y, sf);
            }
        }

        private int PeriodToStair(uint foundPeriod)
        {
            if (foundPeriod > m_period)
                return -1;

            int result;
            if (m_period <= MAX_STAIR_COUNT)
            {
                result = (int)foundPeriod;
            }
            else
            {
                if (foundPeriod < MAX_STAIR_COUNT / 2)
                    result = (int)foundPeriod;
                else if (foundPeriod >= m_period - MAX_STAIR_COUNT / 2)
                    result = (int)(MAX_STAIR_COUNT - (m_period - foundPeriod));
                else
                    result = (int)(MAX_STAIR_COUNT / 2);
            }
            if (m_direction == CyEnums.CyCountDirection.COUNT_DOWN)
            {
                if (m_period <= MAX_STAIR_COUNT)
                {
                    result = (int)m_period - (int)foundPeriod;
                }
                else
                {
                    if (foundPeriod < MAX_STAIR_COUNT / 2)
                        result = MAX_STAIR_COUNT - (int)foundPeriod;
                    else if (foundPeriod >= m_period - MAX_STAIR_COUNT / 2)
                        result = (int)(m_period - foundPeriod);
                    else
                        result = MAX_STAIR_COUNT - (int)(MAX_STAIR_COUNT / 2);
                }
            }
            return result;
        }

        public int[] GetStairsPositions(uint[] periodToReturn, bool skipDownPeriod = false)
        {
            List<int> arrowsPos = new List<int>();

            if (m_period == 0)
                return arrowsPos.ToArray();

            int[] stairsToReturn;
            int stairCount = GetStairCount();
            if (periodToReturn == null)
            {
                stairsToReturn = new int[stairCount];
                for (int i = 0; i < stairCount; i++)
                {
                    stairsToReturn[i] = i + 1;
                }
            }
            else
            {
                stairsToReturn = new int[periodToReturn.Length];
                for (int i = 0; i < stairsToReturn.Length; i++)
                {
                    stairsToReturn[i] = PeriodToStair(periodToReturn[i]);
                }
            }
            
            int stairsX = 0;
            int step = 0;
            int periodNumber = 1;
            int periodWidth = (stairCount-1) * STAIR_HEIGHT;
            while (stairsX <= m_waveformWidth)
            {
                for (int j = 0; j < stairsToReturn.Length; j++)
                {
                    if (stairsX > 0)
                    {
                        stairsX = (periodNumber % 2 == 0)
                            ? LINES_X + step + (periodWidth) - ((stairsToReturn[j] + 1) * STAIR_HEIGHT) + STAIR_HEIGHT
                            : LINES_X + step + ((stairsToReturn[j] - 1) * STAIR_HEIGHT) + STAIR_HEIGHT;
                    }
                    else
                    {
                        stairsX = LINES_X + step + (stairsToReturn[j]) * STAIR_HEIGHT;
                    }
                    arrowsPos.Add(stairsX);
                }
                switch (m_direction)
                {
                    case CyEnums.CyCountDirection.COUNT_UP:
                    case CyEnums.CyCountDirection.COUNT_DOWN:
                        step += STAIR_HEIGHT * stairCount;       // go to the next period
                        break;
                    case CyEnums.CyCountDirection.COUNT_UPDOWN0:
                    case CyEnums.CyCountDirection.COUNT_UPDOWN1:
                        if (skipDownPeriod)
                        {
                            step += ((stairCount - 1) * STAIR_HEIGHT * 2);
                        }
                        else
                        {
                            step = periodWidth * periodNumber++;
                        }
                        break;
                    default:
                        Debug.Fail("unhandled enum item.");
                        break;
                }
            }
            int[] array = arrowsPos.ToArray();
            Array.Sort(array);
            return array;
        }

        public void DrawBreakLine(int x, int y1, int y2, CyEStairPart stairPart)
        {
            const byte BREAK_LINE_WIDTH = 5;

            switch (stairPart)
            {
                case CyEStairPart.Beginning:
                    break;
                case CyEStairPart.Middle:
                    x += (STAIR_HEIGHT - BREAK_LINE_WIDTH) / 2;
                    break;
                case CyEStairPart.End:
                    x += STAIR_HEIGHT;
                    break;
                default:
                    Debug.Fail("unhandled enum item.");
                    break;
            }

            m_g.FillRectangle(Brushes.White, x - 1, y1, BREAK_LINE_WIDTH + 2, y2 - y1);

            int xAmplitude = 1;
            int yAmplitude = 3;
            int xx = x;
            int yy = y1;

            for (int i = 0; i < 2; i++)
            {
                while (yy < y2)
                {
                    Point point1 = new Point(xx, yy);
                    Point point2 = new Point(xx - xAmplitude, yy += yAmplitude);
                    Point point3 = new Point(xx + xAmplitude, yy += yAmplitude);
                    Point point4 = new Point(xx, yy += yAmplitude);
                    m_g.DrawCurve(Pens.Black, new Point[] { point1, point2, point3, point4 });
                    yy += 2;
                }

                xx = x + BREAK_LINE_WIDTH;
                yy = y1;
            }
        }

        public void DrawBreakLines(int x, int y1, int y2, CyEStairPart stairPart)
        {
            int stairCount = GetStairCount();
            while (x <= m_waveformWidth)
            {
                DrawBreakLine(x, y1, y2, stairPart);

                switch (m_direction)
                {
                    case CyEnums.CyCountDirection.COUNT_UP:
                    case CyEnums.CyCountDirection.COUNT_DOWN:
                        x += STAIR_HEIGHT * stairCount;
                        break;
                    case CyEnums.CyCountDirection.COUNT_UPDOWN0:
                    case CyEnums.CyCountDirection.COUNT_UPDOWN1:
                        x += STAIR_HEIGHT * (stairCount - 1);
                        break;
                    default:
                        Debug.Fail("unhandled enum item.");
                        break;
                }
            }
        }

        public void Dispose()
        {
            m_smallFont.Dispose();
            m_normalFont.Dispose();
            m_largeFont.Dispose();
        }
    }

    public enum CyEStairPart
    {
        Beginning,
        Middle,
        End,
    }

    public enum CyEFontSize
    {
        Small,
        Normal,
        Large
    }

    enum CyETextDockStyle
    {
        None,
        Top,
        Bottom,
        HalfTop,
        HalfBottom
    }
}