/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System.Drawing;
using System.Drawing.Drawing2D;

namespace TCPWM_PWM_PDL_v1_0.Waveform
{
    internal class CyEgdeLine : CyWaveform
    {
        public CyEgdeLine(Graphics g, Size size) : base(g, size)
        {
        }

        public override void Draw()
        {
            DrawEdgeLine(LeftEdgeLineX);
            DrawEdgeLine(RightEdgeLineX);
        }

        public void DrawEdgeLine(int x)
        {
            using (Pen dashPen = new Pen(Color.Black))
            using (Brush grayBrush = new SolidBrush(Color.FromArgb(100, Color.LightGray)))
            {
                dashPen.DashStyle = DashStyle.Dash;
                m_g.FillRectangle(grayBrush, x, 0, EDGE_LINE_WIDTH, Size.Height);
                m_g.DrawLine(dashPen, x, 0, x, Size.Height);
                m_g.DrawLine(dashPen, x + EDGE_LINE_WIDTH, 0, x + EDGE_LINE_WIDTH, Size.Height);
            }
        }
    }
}
