/*******************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Diagnostics;

namespace TCPWM_P4_v2_0
{
    abstract class CyImage
    {
        #region Input parameters
        private bool m_reloadPresent = false;
        private bool m_isTcpwmIpV2Ble;
        private uint m_period = 0;
        private uint m_period2 = 1;
        private bool m_swapPeriod = false;
        private uint m_compare1 = 100;
        private uint m_compare2 = 0;
        private bool m_swapCompare = false;
        private CyECounterMode m_counterMode = CyECounterMode.COUNT_UP;
        #endregion Input parameters

        #region String consts
        protected const string STR_RELOAD = "reload";
        protected const string STR_PERIOD = "period";
        protected const string STR_COUNTER = "counter";
        protected const string STR_OV = "OV";
        protected const string STR_UN = "UN";
        protected const string STR_TC = "(interrupt only) TC";
        protected const string STR_CC = "CC";
        protected const string STR_LINE = "line";
        protected const string STR_LINE_N = "line_n";
        #endregion String consts

        #region Image related fields
        private Size m_imageSize;
        private Bitmap m_bmp;        
        #endregion Image related fields

        #region Coordinates
        protected const int X1 = 76 + 80;
        protected const int X2 = 116 + 80; 
        protected const int X2_PERIOD_OFFSET = 3;
        protected const int X3 = 592;
        protected const int Y1_PERIOD = 28;
        protected const int Y2_PERIOD = 49;
        protected const int Y12_PERIOD = Y1_PERIOD + (Y2_PERIOD - Y1_PERIOD) / 2;
        protected const int Y1_RELOAD = 66;
        protected const int Y1_COUNTER = 66;
        protected const int YTC_RELOAD = 20;
        protected const int YPWM_RELOAD = 46;
        protected abstract int Y2_COUNTER { get; }

        protected const int Y_COUNTER_SHIFT = 11;
        protected int COUNTER_H
        {
            get { return Y2_COUNTER - Y1_COUNTER; }
        }
        protected int SECTION_COUNT
        {
            get { return (X3 - X2) / COUNTER_H; }
        }
        protected const int Y_OV = 170;
        protected const int DEL_H = 27;
        protected const int ARROW_H = 15;

        protected const int LINE_W = 1;

        protected int OFFSET_IF_RELOAD = 0;

        protected abstract Size DefaultImageSize { get; }

        protected float XScale
        {
            get { return m_imageSize.Width / (float)DefaultImageSize.Width; }
        }
        protected float YScale
        {
            get { return m_imageSize.Height / (float)DefaultImageSize.Height; }
        }

        protected abstract string TitleText { get; }
        #endregion Coordinates

        #region Properties
        public Bitmap ImageBmp
        {
            get { return m_bmp; }
            set { m_bmp = value; }
        }
        public Size ImageSize
        {
            get { return m_imageSize; }
            set { m_imageSize = value; }
        }
        public bool ImageReloadPresent
        {
            get { return m_reloadPresent; }
            set { m_reloadPresent = value; }
        }
        public bool ImageIsTcpwmIpV2Ble
        {
            get { return m_isTcpwmIpV2Ble; }
            set { m_isTcpwmIpV2Ble = value; }
        }
        public uint ImagePeriod
        {
            get { return m_period; }
            set { m_period = value; }
        }
        public uint ImagePeriod2
        {
            get { return m_period2; }
            set { m_period2 = value; }
        }
        public bool ImageSwapPeriod
        {
            get { return m_swapPeriod; }
            set { m_swapPeriod = value; }
        }
        public uint ImageCompare1
        {
            get { return m_compare1; }
            set { m_compare1 = value; }
        }
        public uint ImageCompare2
        {
            get { return m_compare2; }
            set { m_compare2 = value; }
        }
        public bool ImageSwapCompare
        {
            get { return m_swapCompare; }
            set { m_swapCompare = value; }
        }
        public CyECounterMode ImageCounterMode
        {
            get { return m_counterMode; }
            set { m_counterMode = value; }
        }
        #endregion

        #region Additional protected properties
        protected bool DrawCompare1
        {
            get { return m_compare1 <= m_period; }
        }

        protected bool DrawCompare2
        {
            get { return m_compare2 <= m_period2; }
        }
        #endregion Additional protected properties

        #region Constructor
        public CyImage()
        {
            m_imageSize = new Size(610, 260);
            UpdateBmp();
        }
        #endregion Constructor

        /// <summary>
        /// Draws a diagram
        /// </summary>
        public void UpdateBmp()
        {
            m_bmp = new Bitmap(m_imageSize.Width, m_imageSize.Height);

            Brush brushBlack = Brushes.Black;

            using (Font fnt = new Font("Arial", 10))
            using (Font fntSmall = new Font("Arial", 7.5f))
            using (Pen penBlack = new Pen(Color.Black, LINE_W))
            using (Pen penGray = new Pen(Color.LightGray, LINE_W))
            using (Pen penGrayDash = new Pen(Color.LightGray, LINE_W))
            using (Graphics g = Graphics.FromImage(m_bmp))
            {
                penGrayDash.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;

                g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
                g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.AntiAlias;

                DrawFigures(g, fnt, fntSmall, penBlack, penGray, penGrayDash, brushBlack);
            }
        }
        
        protected virtual void DrawFigures(Graphics g, Font fnt, Font fntSmall, Pen penBlack, Pen penGray,
                                           Pen penDashGray, Brush blackBrush)
        {
            // Title
            DrawText(TitleText, g, new Rectangle(0, 0, DefaultImageSize.Width, DefaultImageSize.Height), fnt,
                StringAlignment.Center, StringAlignment.Near);

            OFFSET_IF_RELOAD = (m_isTcpwmIpV2Ble && m_reloadPresent) ? DEL_H : 0;

            // Counter
            DrawText(STR_COUNTER, g, new Rectangle(0, (Y1_COUNTER + OFFSET_IF_RELOAD), X1, COUNTER_H), fnt, 
                StringAlignment.Far, StringAlignment.Center);

            DrawText("0", g, new RectangleF(X1, (Y2_COUNTER + OFFSET_IF_RELOAD), 0, 0), fntSmall,
                StringAlignment.Near, StringAlignment.Center); 
        }

        protected void DrawArrow(Graphics g, Pen pen, Point endpt, int h)
        {
            g.DrawLine(pen, new Point(endpt.X, endpt.Y - h), endpt);
            Point[] pts = new Point[3];
            pts[0] = new Point(endpt.X - h * 3 / 10, endpt.Y - h / 2);
            pts[1] = new Point(endpt.X + h * 3 / 10, endpt.Y - h / 2);
            pts[2] = endpt;
            g.FillPolygon(Brushes.Black, pts);
        }

        protected void DrawText(string text, Graphics g, RectangleF rect, Font fnt)
        {
            DrawText(text, g, rect, fnt, StringAlignment.Center, StringAlignment.Center);
        }
        protected void DrawText(string text, Graphics g, RectangleF rect, Font fnt,
                                       StringAlignment hAlign, StringAlignment vAlign)
        {
            Brush brushText = Brushes.Black;
            using (StringFormat sf = new StringFormat())
            {
                sf.Alignment = hAlign;
                sf.LineAlignment = vAlign;

                g.ResetTransform();

                rect.X *= XScale;
                rect.Y *= YScale;
                rect.Width *= XScale;
                rect.Height *= YScale;

                g.DrawString(text, fnt, brushText, rect, sf);
                g.ScaleTransform(XScale, YScale);
            }
        }
    }

    class CyImageTC : CyImage
    {
        #region Input parameters
        private CyECompCapMode m_cmpCapMode = CyECompCapMode.Capture;

        public CyECompCapMode ImageTCCmpCapMode
        {
            get { return m_cmpCapMode; }
            set { m_cmpCapMode = value; }
        }
        #endregion Input parameters

        protected override Size DefaultImageSize { get { return new Size(610, 280); } }
        protected override int Y2_COUNTER { get { return 131; } }

        protected override string TitleText
        {
            get 
            {
                string titleText = "Timer, {0} counting mode{1}";
                switch (ImageCounterMode)
                {
                    case CyECounterMode.COUNT_UP:
                        titleText = String.Format(titleText, "up", "");
                        break;
                    case CyECounterMode.COUNT_DOWN:
                        titleText = String.Format(titleText, "down", "");
                        break;
                    case CyECounterMode.COUNT_UPDOWN0:
                        titleText = String.Format(titleText, "up/down", " 0");
                        break;
                    case CyECounterMode.COUNT_UPDOWN1:
                        titleText = String.Format(titleText, "up/down", " 1");
                        break;
                    default:
                        Debug.Assert(false);
                        break;
                }
                return titleText;
            }
        }
        

        protected override void DrawFigures(Graphics g, Font fnt, Font fntSmall, Pen penBlack, Pen penGray,
                                            Pen penGrayDash, Brush brushBlack)
        {
            String text = "";
            g.ScaleTransform(XScale, YScale);

            base.DrawFigures(g, fnt, fntSmall, penBlack, penGray, penGrayDash, brushBlack);

            // reload
            if (ImageIsTcpwmIpV2Ble && ImageReloadPresent)
            {
                g.DrawLine(penBlack, new Point(X1, Y12_PERIOD), new Point(X3, Y12_PERIOD));
                DrawArrow(g, penBlack, new Point(X2, Y12_PERIOD), ARROW_H);
                DrawText(STR_RELOAD, g, new Rectangle(0, YTC_RELOAD, X1, OFFSET_IF_RELOAD), fnt, StringAlignment.Far, 
                    StringAlignment.Far);
            }

            // period
            g.DrawLine(penBlack, new Point(X1, Y12_PERIOD + OFFSET_IF_RELOAD), new Point(X2, Y12_PERIOD + OFFSET_IF_RELOAD));
            g.DrawLine(penBlack, new Point(X2, Y12_PERIOD + OFFSET_IF_RELOAD), new Point(X2 + X2_PERIOD_OFFSET, Y1_PERIOD + OFFSET_IF_RELOAD));
            g.DrawLine(penBlack, new Point(X2, Y12_PERIOD + OFFSET_IF_RELOAD), new Point(X2 + X2_PERIOD_OFFSET, Y2_PERIOD + OFFSET_IF_RELOAD));
            g.DrawLine(penBlack, new Point(X2 + X2_PERIOD_OFFSET, Y1_PERIOD + OFFSET_IF_RELOAD), new Point(X3, Y1_PERIOD + OFFSET_IF_RELOAD));
            g.DrawLine(penBlack, new Point(X2 + X2_PERIOD_OFFSET, Y2_PERIOD + OFFSET_IF_RELOAD), new Point(X3, Y2_PERIOD + OFFSET_IF_RELOAD));

            DrawText(STR_PERIOD, g, new Rectangle(0, Y12_PERIOD + OFFSET_IF_RELOAD, X1, 0), fnt, StringAlignment.Far, StringAlignment.Center);
            DrawText(ImagePeriod.ToString(), g, new Rectangle(0, Y12_PERIOD + OFFSET_IF_RELOAD, DefaultImageSize.Width, 0), fntSmall);

            // counter
            g.DrawLine(penGray, new Point(X2 - Y_COUNTER_SHIFT, Y1_COUNTER + OFFSET_IF_RELOAD), new Point(X3, Y1_COUNTER + OFFSET_IF_RELOAD));
            g.DrawLine(penGray, new Point(X2 - Y_COUNTER_SHIFT, Y2_COUNTER + OFFSET_IF_RELOAD), new Point(X3, Y2_COUNTER + OFFSET_IF_RELOAD));

            for (int i = 1; i <= SECTION_COUNT; i++)
            {
                g.DrawLine(penGrayDash, new Point(X2 + i * COUNTER_H, Y1_COUNTER - Y_COUNTER_SHIFT + OFFSET_IF_RELOAD),
                                        new Point(X2 + i * COUNTER_H, Y2_COUNTER + Y_COUNTER_SHIFT + OFFSET_IF_RELOAD));
            }

            DrawText(ImagePeriod.ToString(), g, new Rectangle(X1, Y1_COUNTER + OFFSET_IF_RELOAD, 0, 0), fntSmall, StringAlignment.Near, 
                StringAlignment.Center);
            
            //OV, UN, TC
            for (int i = 0; i < 3; i++)
            {
                int y = Y_OV + i * DEL_H + OFFSET_IF_RELOAD;
                g.DrawLine(penBlack, new Point(X1, y), new Point(X3, y));
                if (i == 0)
                    text = STR_OV;
                else if (i == 1)
                    text = STR_UN;
                else
                    text = STR_TC;
                DrawText(text, g, new Rectangle(0, 0, X1, y + DEL_H / 3), fnt, StringAlignment.Far, StringAlignment.Far);
            }

            // Counter Mode dependent
            int compare1Shift = (ImagePeriod == 0) ? 0 :
                                (int)((double)ImageCompare1 / ((double)ImagePeriod + 1) * (Y2_COUNTER - Y1_COUNTER));
            int compare2Shift = (ImagePeriod == 0) ? 0 :
                                (int)((double)ImageCompare2 / ((double)ImagePeriod + 1) * (Y2_COUNTER - Y1_COUNTER));
            int compare1X = 0;
            int compare2X = 0;
            switch (ImageCounterMode)
            {
                case CyECounterMode.COUNT_UP:
                    if (ImageIsTcpwmIpV2Ble && ImageReloadPresent)
                    {
                        DrawArrow(g, penBlack, new Point(X2, Y_OV + 0 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                    }
                    for (int i = 0; i < SECTION_COUNT; i++)
                    {
                        g.DrawLine(penBlack, new Point(X2 + i * COUNTER_H, Y2_COUNTER + OFFSET_IF_RELOAD),
                                        new Point(X2 + (i + 1) * COUNTER_H, Y1_COUNTER + OFFSET_IF_RELOAD));
                        DrawArrow(g, penBlack, new Point(X2 + (i + 1) * COUNTER_H, Y_OV + 0 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                        DrawArrow(g, penBlack, new Point(X2 + (i + 1) * COUNTER_H, Y_OV + 2 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                    }
                    compare1X = X2 + compare1Shift;
                    compare2X = X2 + compare2Shift + COUNTER_H;
                    break;
                case CyECounterMode.COUNT_DOWN:
                    if (ImageIsTcpwmIpV2Ble && ImageReloadPresent)
                    {
                        DrawArrow(g, penBlack, new Point(X2, Y_OV + 1 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                    }
                    for (int i = 0; i < SECTION_COUNT; i++)
                    {
                        g.DrawLine(penBlack, new Point(X2 + i * COUNTER_H, Y1_COUNTER + OFFSET_IF_RELOAD),
                                        new Point(X2 + (i + 1) * COUNTER_H, Y2_COUNTER + OFFSET_IF_RELOAD));
                        DrawArrow(g, penBlack, new Point(X2 + (i + 1) * COUNTER_H, Y_OV + 1 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                        DrawArrow(g, penBlack, new Point(X2 + (i + 1) * COUNTER_H, Y_OV + 2 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                    }
                    compare1X = X2 + COUNTER_H - compare1Shift;
                    compare2X = X2 + 2 * COUNTER_H - compare2Shift;
                    break;
                case CyECounterMode.COUNT_UPDOWN0:
                    if (ImageIsTcpwmIpV2Ble && ImageReloadPresent)
                    {
                        DrawArrow(g, penBlack, new Point(X2, Y_OV + 1 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                    }
                    for (int i = 0; i < SECTION_COUNT; i++)
                    {
                        if (i % 2 == 0)
                        {
                            g.DrawLine(penBlack, new Point(X2 + i * COUNTER_H, Y2_COUNTER + OFFSET_IF_RELOAD),
                                            new Point(X2 + (i + 1) * COUNTER_H, Y1_COUNTER + OFFSET_IF_RELOAD));
                            DrawArrow(g, penBlack, new Point(X2 + (i + 1) * COUNTER_H, Y_OV + 0 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                        }
                        else
                        {
                            g.DrawLine(penBlack, new Point(X2 + i * COUNTER_H, Y1_COUNTER + OFFSET_IF_RELOAD),
                                            new Point(X2 + (i + 1) * COUNTER_H, Y2_COUNTER + OFFSET_IF_RELOAD));
                            DrawArrow(g, penBlack, new Point(X2 + (i + 1) * COUNTER_H, Y_OV + 1 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                            DrawArrow(g, penBlack, new Point(X2 + (i + 1) * COUNTER_H, Y_OV + 2 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                        }
                    }
                    compare1X = X2 + compare1Shift;
                    compare2X = X2 + 2 * COUNTER_H - compare2Shift;
                    break;
                case CyECounterMode.COUNT_UPDOWN1:
                    if (ImageIsTcpwmIpV2Ble && ImageReloadPresent)
                    {
                        DrawArrow(g, penBlack, new Point(X2, Y_OV + 1 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                    }
                    for (int i = 0; i < SECTION_COUNT; i++)
                    {
                        if (i % 2 == 0)
                        {
                            g.DrawLine(penBlack, new Point(X2 + i * COUNTER_H, Y2_COUNTER + OFFSET_IF_RELOAD),
                                            new Point(X2 + (i + 1) * COUNTER_H, Y1_COUNTER + OFFSET_IF_RELOAD));
                            DrawArrow(g, penBlack, new Point(X2 + (i + 1) * COUNTER_H, Y_OV + 0 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                            DrawArrow(g, penBlack, new Point(X2 + (i + 1) * COUNTER_H, Y_OV + 2 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                        }
                        else
                        {
                            g.DrawLine(penBlack, new Point(X2 + i * COUNTER_H, Y1_COUNTER + OFFSET_IF_RELOAD),
                                            new Point(X2 + (i + 1) * COUNTER_H, Y2_COUNTER + OFFSET_IF_RELOAD));
                            DrawArrow(g, penBlack, new Point(X2 + (i + 1) * COUNTER_H, Y_OV + 1 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                            DrawArrow(g, penBlack, new Point(X2 + (i + 1) * COUNTER_H, Y_OV + 2 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                        }
                    }
                    compare1X = X2 + compare1Shift;
                    compare2X = X2 + 2 * COUNTER_H - compare2Shift;
                    break;
            }            

            //compare
            if ((ImagePeriod > 0) && (m_cmpCapMode == CyECompCapMode.Compare))
            {
                if (ImageCompare1 < ImagePeriod)
                {
                    g.DrawLine(penGray, new Point(compare1X - Y_COUNTER_SHIFT, Y2_COUNTER - compare1Shift + OFFSET_IF_RELOAD),
                                        new Point(compare1X + Y_COUNTER_SHIFT, Y2_COUNTER - compare1Shift + OFFSET_IF_RELOAD));
                    DrawText(ImageCompare1.ToString(), g,
                        new Rectangle(0, Y2_COUNTER - compare1Shift + OFFSET_IF_RELOAD, compare1X - Y_COUNTER_SHIFT - 5, 0), fntSmall,
                        StringAlignment.Far, StringAlignment.Center);
                }
                if (ImageSwapCompare && (ImageCompare2 < ImagePeriod))
                {
                    g.DrawLine(penGray, new Point(compare2X - Y_COUNTER_SHIFT, Y2_COUNTER - compare2Shift + OFFSET_IF_RELOAD),
                                        new Point(compare2X + Y_COUNTER_SHIFT, Y2_COUNTER - compare2Shift + OFFSET_IF_RELOAD));
                    DrawText(ImageCompare2.ToString(), g,
                       new Rectangle(0, Y2_COUNTER - compare2Shift + OFFSET_IF_RELOAD, compare2X - Y_COUNTER_SHIFT - 5, 0), fntSmall,
                       StringAlignment.Far, StringAlignment.Center);
                }
            }
            g.ResetTransform();
        }
    }

    class CyImagePWM : CyImage
    {
        #region Input parameters
        private CyEPWMAlign m_align = CyEPWMAlign.CENTER;
        private CyEPWMMode m_pwmMode = CyEPWMMode.PWM;
        private CyPWMInvert m_outInvert = CyPWMInvert.DIRECT;
        private CyPWMInvert m_outCCInvert = CyPWMInvert.DIRECT;
        private uint m_deadTime = 0;
        #endregion Input parameters

        #region Properties
        public CyEPWMAlign ImagePWMAlign
        {
            get { return m_align; }
            set { m_align = value; }
        }
        public CyEPWMMode ImagePWMMode
        {
            get { return m_pwmMode; }
            set { m_pwmMode = value; }
        }
        public CyPWMInvert ImagePWMOutInvert
        {
            get { return m_outInvert; }
            set { m_outInvert = value; }
        }
        public CyPWMInvert ImagePWMOutCCInvert
        {
            get { return m_outCCInvert; }
            set { m_outCCInvert = value; }
        }
        public uint ImagePWMDeadTime
        {
            get { return m_deadTime; }
            set { m_deadTime = value; }
        }
        #endregion

        int Counter1H
        {
            get { return (int)((double)ImagePeriod / Math.Max(Math.Max(ImagePeriod, ImagePeriod2), 1) * COUNTER_H); }
        }
        int Counter2H
        {
            get { return (int)((double)ImagePeriod2 / Math.Max(Math.Max(ImagePeriod, ImagePeriod2), 1) * COUNTER_H); }
        }
        int Counter1W
        {
            get { return Math.Max(1, (int)(Counter1H * YScale / XScale)); }
        }
        int Counter2W
        {
            get { return Math.Max(1, (int)(Counter2H * YScale / XScale)); }
        }
        int PERIOD2_START
        {
            get { return X2 + 2 * Counter1W; }
        }
        const int Y_TC = 230;
        const int LINE_Y1 = Y_TC + 4 * DEL_H;
        const int LINE_Y2 = Y_TC + 5 * DEL_H;
        const int LINE_Y12 = Y_TC + 9 * DEL_H / 2;
        const int LINE_INV_Y1 = LINE_Y2 + DEL_H;
        const int LINE_INV_Y2 = LINE_Y2 + 2 * DEL_H;
        const int LINE_INV_Y12 = LINE_Y2 + 3 * DEL_H / 2;
        const int Y_LINE = Y_TC + 8 * DEL_H / 2;
        const int Y_LINE_N = Y_TC + 12 * DEL_H / 2;

        protected override int Y2_COUNTER { get { return 191; } }

        protected override Size DefaultImageSize
        {
            get { return new Size(610, (m_pwmMode == CyEPWMMode.PWM || m_pwmMode == CyEPWMMode.PWM_DT) ? 470 : 380); }
        }

        protected override string TitleText
        {
            get
            {
                string titleText = String.Format("PWM, {0} aligned{1}", "{0}", ImageSwapPeriod ? ", buffered" : "");
                switch (m_align)
                {
                    case CyEPWMAlign.CENTER:
                        titleText = String.Format(titleText, "center");
                        break;
                    case CyEPWMAlign.LEFT:
                        titleText = String.Format(titleText, "left");
                        break;
                    case CyEPWMAlign.RIGHT:
                        titleText = String.Format(titleText, "right");
                        break;
                    case CyEPWMAlign.ASYMMETRIC:
                        titleText = String.Format(titleText, "assymetric");
                        break;
                    default:
                        Debug.Assert(false);
                        break;
                }
                return titleText;
            }
        }

        protected override void DrawFigures(Graphics g, Font fnt, Font fntSmall, Pen penBlack, Pen penGray,
                                            Pen penGrayDash, Brush brushBlack)
        {
            String text = "";

            g.ScaleTransform(XScale, YScale);

            base.DrawFigures(g, fnt, fntSmall, penBlack, penGray, penGrayDash, brushBlack);

            if (ImageSwapPeriod == false)
                ImagePeriod2 = ImagePeriod;
            if (ImageSwapCompare == false)
                ImageCompare2 = ImageCompare1;

            bool isAssymetric = false;
            if (m_align == CyEPWMAlign.ASYMMETRIC)
            {
                m_align = CyEPWMAlign.CENTER;
                isAssymetric = true;
            }

            // reload
            if (ImageIsTcpwmIpV2Ble && ImageReloadPresent)
            {
                g.DrawLine(penBlack, new Point(X1, Y2_COUNTER - Counter1H), new Point(X3, Y2_COUNTER - Counter1H));
                DrawArrow(g, penBlack, new Point(X2, Y2_COUNTER - Counter1H), ARROW_H);
                DrawText(STR_RELOAD, g, new Rectangle(0, YPWM_RELOAD, X1, OFFSET_IF_RELOAD), fnt,
                    StringAlignment.Far, StringAlignment.Center);
            }

            // counter
            g.DrawLine(penGray, new Point(X2 - Y_COUNTER_SHIFT, Y2_COUNTER + OFFSET_IF_RELOAD),
                                new Point(X3, Y2_COUNTER + OFFSET_IF_RELOAD));
            g.DrawLine(penGray, new Point(X2 - Y_COUNTER_SHIFT, Y2_COUNTER - Counter1H + OFFSET_IF_RELOAD),
                                new Point(PERIOD2_START, Y2_COUNTER - Counter1H + OFFSET_IF_RELOAD));
            g.DrawLine(penGray, new Point(PERIOD2_START, Y2_COUNTER - Counter2H + OFFSET_IF_RELOAD),
                                new Point(X3, Y2_COUNTER - Counter2H + OFFSET_IF_RELOAD));
            g.DrawLine(penGrayDash, new Point(PERIOD2_START, Y1_COUNTER - Y_COUNTER_SHIFT + OFFSET_IF_RELOAD),
                                    new Point(PERIOD2_START, Y2_COUNTER + Y_COUNTER_SHIFT + OFFSET_IF_RELOAD));

            DrawText(ImagePeriod.ToString(), g, new RectangleF(X1, Y2_COUNTER - Counter1H + OFFSET_IF_RELOAD, 0, 0),
                fntSmall, StringAlignment.Near, StringAlignment.Center);
            
            if (ImageSwapPeriod)
            {
                DrawText(ImagePeriod2.ToString(), g, new RectangleF(0, Y2_COUNTER - Counter2H + OFFSET_IF_RELOAD,
                    PERIOD2_START - 5, 0),
                         fntSmall, StringAlignment.Far, StringAlignment.Center);
            }
            
            //TC, CC
            for (int i = 0; i < 4; i++)
            {
                int y = Y_TC + i * DEL_H + OFFSET_IF_RELOAD;
                g.DrawLine(penBlack, new Point(X1, y), new Point(X3, y));
                if (i == 0)
                    text = STR_OV;
                else if (i == 1)
                    text = STR_UN;
                else if (i == 2)
                        text = STR_TC;
                else if (i == 3)
                    text = STR_CC;

                DrawText(text, g, new RectangleF(0, 0, X1, y + DEL_H / 2), fnt, StringAlignment.Far, StringAlignment.Far);
            }

            // line
            DrawText(STR_LINE, g, new RectangleF(0, Y_LINE + OFFSET_IF_RELOAD, X1, 0 + OFFSET_IF_RELOAD), fnt, 
                StringAlignment.Far, StringAlignment.Near);

            // Align dependent
            double add1 = (m_align == CyEPWMAlign.CENTER && ImageCompare1 != 0) ? 0.5 : 0;
            double add2 = (m_align == CyEPWMAlign.CENTER && ImageCompare2 != 0) ? 0.5 : 0;
            if (m_align == CyEPWMAlign.RIGHT)
            {
                add1 = 1;
                add2 = 1;
            }
            int compare1Shift = (ImagePeriod == 0) ? 0 : (int)((double)(ImageCompare1 + add1) / ((double)ImagePeriod + 1) * Counter1W);
            int compare2Shift = (ImagePeriod2 == 0) ? 0 : (int)((double)(ImageCompare2 + add2) / ((double)ImagePeriod2 + 1) * Counter2W);
            int compare1YShift = Y2_COUNTER - compare1Shift * Counter1H / Counter1W;
            int compare2YShift = Y2_COUNTER - compare2Shift * Counter2H / Counter2W;
            int compare1X1 = 0;
            int compare1X2 = 0;
            int compare2X1 = 0;
            int compare2X2 = 0;
            List<Point> linePoints = new List<Point>();
            List<Point> lineInvPoints = new List<Point>();

            switch (m_align)
            {
                case CyEPWMAlign.CENTER:
                    g.DrawLine(penBlack, new Point(X2, Y2_COUNTER + OFFSET_IF_RELOAD),
                                    new Point(X2 + Counter1W, Y2_COUNTER - Counter1H + OFFSET_IF_RELOAD));
                    g.DrawLine(penBlack, new Point(X2 + Counter1W, Y2_COUNTER - Counter1H + OFFSET_IF_RELOAD),
                                    new Point(X2 + 2 * Counter1W, Y2_COUNTER + OFFSET_IF_RELOAD));
                    g.DrawLine(penBlack, new Point(PERIOD2_START, Y2_COUNTER + OFFSET_IF_RELOAD),
                                    new Point(PERIOD2_START + Counter2W, Y2_COUNTER - Counter2H + OFFSET_IF_RELOAD));
                    g.DrawLine(penBlack, new Point(PERIOD2_START + Counter2W, Y2_COUNTER - Counter2H + OFFSET_IF_RELOAD),
                                    new Point(PERIOD2_START + 2 * Counter2W, Y2_COUNTER + OFFSET_IF_RELOAD));

                    compare1X1 = X2 + compare1Shift;
                    compare1X2 = PERIOD2_START - compare1Shift;
                    compare2X1 = PERIOD2_START + compare2Shift;
                    compare2X2 = PERIOD2_START + 2 * Counter2W - compare2Shift;

                    // Compare 1
                    if (DrawCompare1)
                    {
                        g.DrawLine(penGrayDash, new Point(compare1X1, Y2_COUNTER + Y_COUNTER_SHIFT + OFFSET_IF_RELOAD),
                                                new Point(compare1X1, compare1YShift - Y_COUNTER_SHIFT + OFFSET_IF_RELOAD));
                        g.DrawLine(penGray, new Point(compare1X1 - Y_COUNTER_SHIFT, compare1YShift + OFFSET_IF_RELOAD),
                                            new Point(compare1X2 + Y_COUNTER_SHIFT, compare1YShift + OFFSET_IF_RELOAD));
                        g.DrawLine(penGrayDash, new Point(compare1X2, Y2_COUNTER + Y_COUNTER_SHIFT + OFFSET_IF_RELOAD),
                                                new Point(compare1X2, compare1YShift - Y_COUNTER_SHIFT + OFFSET_IF_RELOAD));
                    }

                    // Compare2
                    if (DrawCompare2)
                    {
                        g.DrawLine(penGrayDash, new Point(compare2X1, Y2_COUNTER + Y_COUNTER_SHIFT + OFFSET_IF_RELOAD),
                                                new Point(compare2X1, compare2YShift - Y_COUNTER_SHIFT + OFFSET_IF_RELOAD));
                        g.DrawLine(penGray, new Point(compare2X1 - Y_COUNTER_SHIFT, compare2YShift + OFFSET_IF_RELOAD),
                                            new Point(compare2X2 + Y_COUNTER_SHIFT, compare2YShift + OFFSET_IF_RELOAD));
                        g.DrawLine(penGrayDash, new Point(compare2X2, Y2_COUNTER + Y_COUNTER_SHIFT + OFFSET_IF_RELOAD),
                                                new Point(compare2X2, compare2YShift - Y_COUNTER_SHIFT + OFFSET_IF_RELOAD));
                    }
                    // OV, UN arrows
                    if (ImageIsTcpwmIpV2Ble && ImageReloadPresent)
                    {
                        DrawArrow(g, penBlack, new Point(X2, Y_TC + 1 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                    }
                    DrawArrow(g, penBlack, new Point(X2 + Counter1W, Y_TC + OFFSET_IF_RELOAD), ARROW_H);
                    DrawArrow(g, penBlack, new Point(PERIOD2_START + Counter2W, Y_TC + OFFSET_IF_RELOAD), ARROW_H);
                    DrawArrow(g, penBlack, new Point(PERIOD2_START, Y_TC + 1 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                    DrawArrow(g, penBlack, new Point(PERIOD2_START + 2 * Counter2W, Y_TC + 1 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                    break;
                case CyEPWMAlign.LEFT:
                    g.DrawLine(penBlack, new Point(X2, Y2_COUNTER + OFFSET_IF_RELOAD), new Point(X2 + Counter1W,
                        Y2_COUNTER - Counter1H + OFFSET_IF_RELOAD));
                    g.DrawLine(penBlack, new Point(X2 + Counter1W, Y2_COUNTER + OFFSET_IF_RELOAD),
                                    new Point(X2 + 2 * Counter1W, Y2_COUNTER - Counter1H + OFFSET_IF_RELOAD));
                    g.DrawLine(penBlack, new Point(PERIOD2_START, Y2_COUNTER + OFFSET_IF_RELOAD),
                                    new Point(PERIOD2_START + Counter2W, Y2_COUNTER - Counter2H + OFFSET_IF_RELOAD));
                    g.DrawLine(penBlack, new Point(PERIOD2_START + Counter2W, Y2_COUNTER + OFFSET_IF_RELOAD),
                                    new Point(PERIOD2_START + 2 * Counter2W, Y2_COUNTER - Counter2H + OFFSET_IF_RELOAD));

                    compare1X1 = X2 + compare1Shift;
                    compare1X2 = X2 + Counter1W + compare1Shift;
                    compare2X1 = PERIOD2_START + compare2Shift;
                    compare2X2 = PERIOD2_START + Counter2W + compare2Shift;

                    // Compare 1
                    if (DrawCompare1)
                    {
                        g.DrawLine(penGrayDash, new Point(compare1X1, Y2_COUNTER + Y_COUNTER_SHIFT + OFFSET_IF_RELOAD),
                                                new Point(compare1X1, compare1YShift - Y_COUNTER_SHIFT + OFFSET_IF_RELOAD));
                        g.DrawLine(penGray, new Point(compare1X1 - Y_COUNTER_SHIFT, compare1YShift + OFFSET_IF_RELOAD),
                                            new Point(X2 + Counter1W, compare1YShift + OFFSET_IF_RELOAD));
                        g.DrawLine(penGrayDash, new Point(compare1X2, Y2_COUNTER + Y_COUNTER_SHIFT + OFFSET_IF_RELOAD),
                                                new Point(compare1X2, compare1YShift - Y_COUNTER_SHIFT + OFFSET_IF_RELOAD));
                        g.DrawLine(penGray, new Point(compare1X2 - Y_COUNTER_SHIFT, compare1YShift + OFFSET_IF_RELOAD),
                                            new Point(X2 + 2 * Counter1W, compare1YShift + OFFSET_IF_RELOAD));
                    }

                    // Compare2
                    if (DrawCompare2)
                    {
                        g.DrawLine(penGrayDash, new Point(compare2X1, Y2_COUNTER + Y_COUNTER_SHIFT + OFFSET_IF_RELOAD),
                                                new Point(compare2X1, compare2YShift - Y_COUNTER_SHIFT + OFFSET_IF_RELOAD));
                        g.DrawLine(penGray, new Point(compare2X1 - Y_COUNTER_SHIFT, compare2YShift + OFFSET_IF_RELOAD),
                                            new Point(PERIOD2_START + Counter2W, compare2YShift + OFFSET_IF_RELOAD));
                        g.DrawLine(penGrayDash, new Point(compare2X2, Y2_COUNTER + Y_COUNTER_SHIFT + OFFSET_IF_RELOAD),
                                                new Point(compare2X2, compare2YShift - Y_COUNTER_SHIFT + OFFSET_IF_RELOAD));
                        g.DrawLine(penGray, new Point(compare2X2 - Y_COUNTER_SHIFT, compare2YShift + OFFSET_IF_RELOAD),
                                            new Point(PERIOD2_START + 2 * Counter2W, compare2YShift + OFFSET_IF_RELOAD));
                    }
                    // OV arrows
                    if (ImageIsTcpwmIpV2Ble && ImageReloadPresent)
                    {
                        DrawArrow(g, penBlack, new Point(X2, Y_TC + OFFSET_IF_RELOAD), ARROW_H);
                    }
                    DrawArrow(g, penBlack, new Point(PERIOD2_START, Y_TC + OFFSET_IF_RELOAD), ARROW_H);
                    DrawArrow(g, penBlack, new Point(PERIOD2_START + 2 * Counter2W, Y_TC + OFFSET_IF_RELOAD), ARROW_H);
                    DrawArrow(g, penBlack, new Point(X2 + Counter1W, Y_TC + OFFSET_IF_RELOAD), ARROW_H);
                    DrawArrow(g, penBlack, new Point(PERIOD2_START + Counter2W, Y_TC + OFFSET_IF_RELOAD), ARROW_H);
                    break;
                case CyEPWMAlign.RIGHT:
                    g.DrawLine(penBlack, new Point(X2, Y2_COUNTER - Counter1H + OFFSET_IF_RELOAD),
                        new Point(X2 + Counter1W, Y2_COUNTER + OFFSET_IF_RELOAD));
                    g.DrawLine(penBlack, new Point(X2 + Counter1W, Y2_COUNTER - Counter1H + OFFSET_IF_RELOAD),
                                    new Point(X2 + 2 * Counter1W, Y2_COUNTER + OFFSET_IF_RELOAD));
                    g.DrawLine(penBlack, new Point(PERIOD2_START, Y2_COUNTER - Counter2H + OFFSET_IF_RELOAD),
                                    new Point(PERIOD2_START + Counter2W, Y2_COUNTER + OFFSET_IF_RELOAD));
                    g.DrawLine(penBlack, new Point(PERIOD2_START + Counter2W, Y2_COUNTER - Counter2H + OFFSET_IF_RELOAD),
                                    new Point(PERIOD2_START + 2 * Counter2W, Y2_COUNTER + OFFSET_IF_RELOAD));

                    compare1X1 = X2 + Counter1W - compare1Shift;
                    compare1X2 = X2 + 2 * Counter1W - compare1Shift;
                    compare2X1 = PERIOD2_START + Counter2W - compare2Shift;
                    compare2X2 = PERIOD2_START + 2 * Counter2W - compare2Shift;

                    // Compare 1
                    if (DrawCompare1)
                    {
                        g.DrawLine(penGray, new Point(X2, compare1YShift + OFFSET_IF_RELOAD),
                                            new Point(compare1X1 + Y_COUNTER_SHIFT, compare1YShift + OFFSET_IF_RELOAD));
                        g.DrawLine(penGrayDash, new Point(compare1X1, Y2_COUNTER + Y_COUNTER_SHIFT + OFFSET_IF_RELOAD),
                                                new Point(compare1X1, compare1YShift - Y_COUNTER_SHIFT + OFFSET_IF_RELOAD));
                        g.DrawLine(penGray, new Point(X2 + Counter1W, compare1YShift + OFFSET_IF_RELOAD),
                                           new Point(compare1X2 + Y_COUNTER_SHIFT, compare1YShift + OFFSET_IF_RELOAD));
                        g.DrawLine(penGrayDash, new Point(compare1X2, Y2_COUNTER + Y_COUNTER_SHIFT + OFFSET_IF_RELOAD),
                                                new Point(compare1X2, compare1YShift - Y_COUNTER_SHIFT + OFFSET_IF_RELOAD));
                    }

                    // Compare2
                    if (DrawCompare2)
                    {
                        g.DrawLine(penGray, new Point(PERIOD2_START, compare2YShift + OFFSET_IF_RELOAD),
                                            new Point(compare2X1 + Y_COUNTER_SHIFT, compare2YShift + OFFSET_IF_RELOAD));
                        g.DrawLine(penGrayDash, new Point(compare2X1, Y2_COUNTER + Y_COUNTER_SHIFT + OFFSET_IF_RELOAD),
                                                new Point(compare2X1, compare2YShift - Y_COUNTER_SHIFT + OFFSET_IF_RELOAD));
                        g.DrawLine(penGray, new Point(PERIOD2_START + Counter2W, compare2YShift + OFFSET_IF_RELOAD),
                                           new Point(compare2X2 + Y_COUNTER_SHIFT, compare2YShift + OFFSET_IF_RELOAD));
                        g.DrawLine(penGrayDash, new Point(compare2X2, Y2_COUNTER + Y_COUNTER_SHIFT + OFFSET_IF_RELOAD),
                                                new Point(compare2X2, compare2YShift - Y_COUNTER_SHIFT + OFFSET_IF_RELOAD));
                    }
                    // UN arrows
                    if (ImageIsTcpwmIpV2Ble && ImageReloadPresent)
                    {
                        DrawArrow(g, penBlack, new Point(X2, Y_TC + 1 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                    }
                    DrawArrow(g, penBlack, new Point(PERIOD2_START, Y_TC + 1 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                    DrawArrow(g, penBlack, new Point(PERIOD2_START + 2 * Counter2W, Y_TC + 1 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                    DrawArrow(g, penBlack, new Point(X2 + Counter1W, Y_TC + 1 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                    DrawArrow(g, penBlack, new Point(PERIOD2_START + Counter2W, Y_TC + 1 * DEL_H + OFFSET_IF_RELOAD),
                        ARROW_H);
                    break;
            }
            // line
            linePoints = FillLinePoints(isAssymetric, compare1X1, compare1X2, compare2X1, compare2X2);
            // Inverse line (line_n)
            if (m_pwmMode == CyEPWMMode.PWM || m_pwmMode == CyEPWMMode.PWM_DT)
            {
                DrawText(STR_LINE_N, g, new RectangleF(0, Y_LINE_N + OFFSET_IF_RELOAD, X1, 0 + OFFSET_IF_RELOAD), fnt, 
                    StringAlignment.Far, StringAlignment.Near);
                lineInvPoints = FillLineInv(linePoints);
                
                if (m_pwmMode == CyEPWMMode.PWM_DT)
                {
                    CheckLinePointsOrder(linePoints);
                    CheckLinePointsOrder(lineInvPoints);
                    AddDeadTimeShift(linePoints, lineInvPoints);
                }
                if (m_outCCInvert == CyPWMInvert.INVERSE)
                {
                    lineInvPoints = InvertLine(lineInvPoints);
                }
                CheckLinePointsOrder(lineInvPoints);
            }
            // line
            if (m_outInvert == CyPWMInvert.INVERSE)
            {
                linePoints = InvertLine(linePoints);
            }
            CheckLinePointsOrder(linePoints);

            // compare
            if (DrawCompare1)
            {
                DrawText(ImageCompare1.ToString(), g, new RectangleF(0, compare1YShift, compare1X1 - 5, 2 * OFFSET_IF_RELOAD),
                        fntSmall, StringAlignment.Far, StringAlignment.Center);
            }
            if (ImageSwapCompare && DrawCompare2)
            {
                DrawText(ImageCompare2.ToString(), g, new RectangleF(0, compare2YShift, compare2X1 - 5, 2 * OFFSET_IF_RELOAD),
                        fntSmall, StringAlignment.Far, StringAlignment.Center);
            }

            if (m_align != CyEPWMAlign.CENTER)
            {
                g.DrawLine(penGrayDash, new Point(X2 + Counter1W, Y2_COUNTER - Counter1H - Y_COUNTER_SHIFT + OFFSET_IF_RELOAD),
                                        new Point(X2 + Counter1W, Y2_COUNTER + Y_COUNTER_SHIFT + OFFSET_IF_RELOAD));
                g.DrawLine(penGrayDash, new Point(PERIOD2_START + Counter2W, Y2_COUNTER - Counter2H - Y_COUNTER_SHIFT + OFFSET_IF_RELOAD),
                                        new Point(PERIOD2_START + Counter2W, Y2_COUNTER + Y_COUNTER_SHIFT + OFFSET_IF_RELOAD));
                g.DrawLine(penGrayDash,
                                new Point(PERIOD2_START + 2 * Counter2W, Y2_COUNTER - Counter2H - Y_COUNTER_SHIFT + OFFSET_IF_RELOAD),
                                new Point(PERIOD2_START + 2 * Counter2W, Y2_COUNTER + Y_COUNTER_SHIFT + OFFSET_IF_RELOAD));
            }

            DrawArrow(g, penBlack, new Point(PERIOD2_START, Y_TC + 2 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
            DrawArrow(g, penBlack, new Point(PERIOD2_START + 2 * Counter2W, Y_TC + 2 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);

            // CC
            if (m_align == CyEPWMAlign.CENTER && ImageCompare1 == ImagePeriod)
            {
                DrawArrow(g, penBlack, new Point(X2 + Counter1W, Y_TC + 3 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
            }
            else
            {
                if (((m_align == CyEPWMAlign.CENTER || m_align == CyEPWMAlign.LEFT) && ImageIsTcpwmIpV2Ble && ImageCompare1 == 0 && !ImageReloadPresent) ||
                    (m_align == CyEPWMAlign.RIGHT && ImageIsTcpwmIpV2Ble && ImageCompare1 == ImagePeriod && !ImageReloadPresent))
                { 
                }
                else
                    DrawArrow(g, penBlack, new Point(compare1X1, Y_TC + 3 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                DrawArrow(g, penBlack, new Point(compare1X2, Y_TC + 3 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
            }
            if (m_align == CyEPWMAlign.CENTER && ImageCompare2 == ImagePeriod)
            {
                DrawArrow(g, penBlack, new Point(PERIOD2_START + Counter2W, Y_TC + 3 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
            }
            else
            {
                DrawArrow(g, penBlack, new Point(compare2X1, Y_TC + 3 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                DrawArrow(g, penBlack, new Point(compare2X2, Y_TC + 3 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
            }
            if (m_align != CyEPWMAlign.CENTER || isAssymetric)
            {
                DrawArrow(g, penBlack, new Point(X2 + Counter1W, Y_TC + 2 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
                DrawArrow(g, penBlack, new Point(PERIOD2_START + Counter2W, Y_TC + 2 * DEL_H + OFFSET_IF_RELOAD), ARROW_H);
            }

            if (DrawCompare1 && DrawCompare2)
            {
                // Draw line
                g.DrawLines(penBlack, linePoints.ToArray());
                // Draw inverse line 
                if (m_pwmMode == CyEPWMMode.PWM || m_pwmMode == CyEPWMMode.PWM_DT)
                {
                    g.DrawLines(penBlack, lineInvPoints.ToArray());
                }
            }

            g.ResetTransform();
        }


        private List<Point> FillLinePoints(bool isAssymetric, int compare1X1, int compare1X2, int compare2X1,
                                           int compare2X2)
        {
            const int LINE_SHIFT = 3;
            List<Point> linePoints = new List<Point>();
            switch (m_align)
            {
                case CyEPWMAlign.LEFT:
                    if (ImageCompare1 == ImagePeriod)
                    {
                        compare1X1 -= LINE_SHIFT;
                        compare1X2 -= LINE_SHIFT;
                    }
                    if (ImageCompare2 == ImagePeriod2)
                    {
                        compare2X1 -= LINE_SHIFT;
                        compare2X2 -= LINE_SHIFT;
                    }
                    
                    linePoints.Add(new Point(X1, LINE_Y1 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(X2, LINE_Y1 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(X2, LINE_Y1 + OFFSET_IF_RELOAD));

                    if (ImageIsTcpwmIpV2Ble && ImageReloadPresent)
                    {
                        linePoints.Add(new Point(X2, LINE_Y1 + OFFSET_IF_RELOAD));
                        linePoints.Add(new Point(X2, LINE_Y2 + OFFSET_IF_RELOAD));
                        linePoints.Add(new Point(compare1X1, LINE_Y2 + OFFSET_IF_RELOAD));
                        linePoints.Add(new Point(compare1X1, LINE_Y1 + OFFSET_IF_RELOAD));

                        linePoints.Add(new Point(X2 + Counter1W, LINE_Y1 + OFFSET_IF_RELOAD));
                        linePoints.Add(new Point(X2 + Counter1W, LINE_Y2 + OFFSET_IF_RELOAD));
                    }
                    else
                    {
                        linePoints.Add(new Point(X2 + Counter1W, LINE_Y1 + OFFSET_IF_RELOAD));
                        linePoints.Add(new Point(X2 + Counter1W, LINE_Y2 + OFFSET_IF_RELOAD));                    
                    }

                    linePoints.Add(new Point(compare1X2, LINE_Y2 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(compare1X2, LINE_Y1 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(X2 + 2 * Counter1W, LINE_Y1 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(X2 + 2 * Counter1W, LINE_Y2 + OFFSET_IF_RELOAD));
                    
                    linePoints.Add(new Point(compare2X1, LINE_Y2 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(compare2X1, LINE_Y1 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(PERIOD2_START + Counter2W, LINE_Y1 + OFFSET_IF_RELOAD));

                    linePoints.Add(new Point(PERIOD2_START + Counter2W, LINE_Y2 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(compare2X2, LINE_Y2 + OFFSET_IF_RELOAD));

                    linePoints.Add(new Point(compare2X2, LINE_Y1 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(PERIOD2_START + 2 * Counter2W, LINE_Y1 + OFFSET_IF_RELOAD));
                                       
                    linePoints.Add(new Point(PERIOD2_START + 2 * Counter2W, LINE_Y1 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(X3, LINE_Y1 + OFFSET_IF_RELOAD));         

                    linePoints = InvertLine(linePoints);
                    break;
                case CyEPWMAlign.RIGHT:
                    if (ImageCompare1 == 0)
                    {
                        compare1X1 -= LINE_SHIFT;
                        compare1X2 -= LINE_SHIFT;
                    }
                    if (ImageCompare2 == 0)
                    {
                        compare2X1 -= LINE_SHIFT;
                        compare2X2 -= LINE_SHIFT;
                    }
                    
                    linePoints.Add(new Point(X1, LINE_Y1 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(X2, LINE_Y1 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(X2, LINE_Y1 + OFFSET_IF_RELOAD));

                    if (ImageIsTcpwmIpV2Ble && ImageCompare1 == ImagePeriod && !ImageReloadPresent)
                    {
                        linePoints.Add(new Point(compare1X2, LINE_Y1 + OFFSET_IF_RELOAD));
                        linePoints.Add(new Point(compare1X2, LINE_Y2 + OFFSET_IF_RELOAD));
                    }
                    else
                    {
                        linePoints.Add(new Point(compare1X1, LINE_Y1 + OFFSET_IF_RELOAD));
                        linePoints.Add(new Point(compare1X1, LINE_Y2 + OFFSET_IF_RELOAD));
                    }
                    
                    linePoints.Add(new Point(X2 + Counter1W, LINE_Y2 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(X2 + Counter1W, LINE_Y1 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(compare1X2, LINE_Y1 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(compare1X2, LINE_Y2 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(X2 + 2 * Counter1W, LINE_Y2 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(X2 + 2 * Counter1W, LINE_Y1 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(compare2X1, LINE_Y1 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(compare2X1, LINE_Y2 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(PERIOD2_START + Counter2W, LINE_Y2 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(PERIOD2_START + Counter2W, LINE_Y1 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(compare2X2, LINE_Y1 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(compare2X2, LINE_Y2 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(PERIOD2_START + 2 * Counter2W, LINE_Y2 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(PERIOD2_START + 2 * Counter2W, LINE_Y1 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(X3, LINE_Y1 + OFFSET_IF_RELOAD));
                                    
                    linePoints = InvertLine(linePoints);
                    break;
                case CyEPWMAlign.CENTER:
                    bool compare0 = (ImageCompare1 == 0 && ImageCompare2 == 0);
                    if (compare0 && !ImageIsTcpwmIpV2Ble)
                    {
                        compare2X1 += LINE_SHIFT;
                        linePoints.Add(new Point(X1, LINE_Y1 + OFFSET_IF_RELOAD));
                        linePoints.Add(new Point(X2, LINE_Y1 + OFFSET_IF_RELOAD));
                        linePoints.Add(new Point(X2, LINE_Y1 + OFFSET_IF_RELOAD));
                        linePoints.Add(new Point(compare1X2, LINE_Y1 + OFFSET_IF_RELOAD));
                        linePoints.Add(new Point(compare1X2, LINE_Y2 + OFFSET_IF_RELOAD));
                        linePoints.Add(new Point(compare1X2 + LINE_SHIFT, LINE_Y2 + OFFSET_IF_RELOAD));
                        linePoints.Add(new Point(compare1X2 + LINE_SHIFT, LINE_Y1 + OFFSET_IF_RELOAD));
                        linePoints.Add(new Point(compare2X2, LINE_Y1 + OFFSET_IF_RELOAD));
                        linePoints.Add(new Point(compare2X2, LINE_Y2 + OFFSET_IF_RELOAD));
                        linePoints.Add(new Point(compare2X2 + LINE_SHIFT, LINE_Y2 + OFFSET_IF_RELOAD));
                        linePoints.Add(new Point(compare2X2 + LINE_SHIFT, LINE_Y1 + OFFSET_IF_RELOAD));
                        linePoints.Add(new Point(X3, LINE_Y1 + OFFSET_IF_RELOAD));

                        linePoints = InvertLine(linePoints);

                        break;
                    }         

                    linePoints.Add(new Point(X1, LINE_Y2 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(X2, LINE_Y2 + OFFSET_IF_RELOAD));
                        linePoints.Add(new Point(X2, LINE_Y2 + OFFSET_IF_RELOAD));
                    
                    if (ImageCompare1 == ImagePeriod && ImageCompare2 == ImagePeriod2 && !ImageIsTcpwmIpV2Ble)
                    {
                        compare1X2 = PERIOD2_START;
                        compare2X2 = PERIOD2_START + 2 * Counter2W;
                    }


                    if (ImageIsTcpwmIpV2Ble && ImageCompare1 == 0 && !ImageReloadPresent)
                    {
                        linePoints.Add(new Point(compare1X1 + Counter1W, LINE_Y2 + OFFSET_IF_RELOAD));
                        linePoints.Add(new Point(compare1X1 + Counter1W, LINE_Y1 + OFFSET_IF_RELOAD));
                        linePoints.Add(new Point(compare1X2, LINE_Y1 + OFFSET_IF_RELOAD));
                        linePoints.Add(new Point(compare1X2, LINE_Y2 + OFFSET_IF_RELOAD));              
                    }
                    else
                    {
                        linePoints.Add(new Point(compare1X1, LINE_Y2 + OFFSET_IF_RELOAD));

                        if (!(ImageIsTcpwmIpV2Ble && ImageCompare1 == ImagePeriod))
                        {
                            linePoints.Add(new Point(compare1X1, LINE_Y1 + OFFSET_IF_RELOAD));
                            linePoints.Add(new Point(compare1X2, LINE_Y1 + OFFSET_IF_RELOAD));
                        }

                        linePoints.Add(new Point(compare1X2, LINE_Y2 + OFFSET_IF_RELOAD));
                    }

                    linePoints.Add(new Point(compare2X1, LINE_Y2 + OFFSET_IF_RELOAD));
                    
                    
                    if (!(ImageIsTcpwmIpV2Ble && ImageCompare2 == ImagePeriod2))
                    {
                        linePoints.Add(new Point(compare2X1, LINE_Y1 + OFFSET_IF_RELOAD));
                        linePoints.Add(new Point(compare2X2, LINE_Y1 + OFFSET_IF_RELOAD));
                    }   

                    linePoints.Add(new Point(compare2X2, LINE_Y2 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(PERIOD2_START + 2 * Counter2W, LINE_Y2 + OFFSET_IF_RELOAD));

                    linePoints.Add(new Point(PERIOD2_START + 2 * Counter2W, LINE_Y2 + OFFSET_IF_RELOAD));
                    linePoints.Add(new Point(X3, LINE_Y2 + OFFSET_IF_RELOAD));

                    break;
                case CyEPWMAlign.ASYMMETRIC:
                    break;
                default:
                    break;
            }

            return linePoints;
        }

        private List<Point> InvertLine(List<Point> linePoints)
        {
            List<Point> lineInvPoints = new List<Point>();

            if (linePoints.Count == 0)
                return lineInvPoints;

            int minY = linePoints[0].Y, maxY = linePoints[0].Y;
            for (int i = 0; i < linePoints.Count; i++)
            {
                if (linePoints[i].Y < minY)
                    minY = linePoints[i].Y;
                if (linePoints[i].Y > maxY)
                    maxY = linePoints[i].Y;
            }
            if (ImageIsTcpwmIpV2Ble && (minY == maxY))
            {
                lineInvPoints.AddRange(linePoints);
                for (int i = 0; i < lineInvPoints.Count; i++)
                {
                    if (lineInvPoints[i].Y == LINE_Y1 + OFFSET_IF_RELOAD)
                    {
                        lineInvPoints[i] = new Point(lineInvPoints[i].X, LINE_Y2 + OFFSET_IF_RELOAD);
                    }
                    else if (lineInvPoints[i].Y == LINE_Y2 + OFFSET_IF_RELOAD)
                    {
                        lineInvPoints[i] = new Point(lineInvPoints[i].X, LINE_Y1 + OFFSET_IF_RELOAD);
                    }
                    else if (lineInvPoints[i].Y == LINE_INV_Y1 + OFFSET_IF_RELOAD)
                    {
                        lineInvPoints[i] = new Point(lineInvPoints[i].X, LINE_INV_Y2 + OFFSET_IF_RELOAD);
                    }
                    else if (lineInvPoints[i].Y == LINE_INV_Y2 + OFFSET_IF_RELOAD)
                    {
                        lineInvPoints[i] = new Point(lineInvPoints[i].X, LINE_INV_Y1 + OFFSET_IF_RELOAD);
                    }
                }
            }
            else
            {
                for (int i = 0; i < linePoints.Count; i++) 
                {
                    if (linePoints[i].Y == minY)
                        lineInvPoints.Add(new Point(linePoints[i].X, maxY));
                    else if (linePoints[i].Y == maxY)
                        lineInvPoints.Add(new Point(linePoints[i].X, minY));
                    else
                        lineInvPoints.Add(linePoints[i]);
                }
            }
            return lineInvPoints;
        }

        private List<Point> FillLineInv(List<Point> linePoints)
        {
            List<Point> lineInvPoints = new List<Point>();
            lineInvPoints.AddRange(linePoints);

            int temp1;
            int temp2;

            for (int i = 0; i < lineInvPoints.Count; i++)
            {
                if (i < 2 || i >= lineInvPoints.Count - 2)
                {
                    temp1 = LINE_INV_Y1;
                    temp2 = LINE_INV_Y2;
                }
                else
                {
                    temp1 = LINE_INV_Y2;
                    temp2 = LINE_INV_Y1;
                }

                if (lineInvPoints[i].Y == LINE_Y1 + OFFSET_IF_RELOAD)
                {
                    lineInvPoints[i] = new Point(lineInvPoints[i].X, temp1 + OFFSET_IF_RELOAD);
                }
                else if (lineInvPoints[i].Y == LINE_Y2 + OFFSET_IF_RELOAD)
                {
                    lineInvPoints[i] = new Point(lineInvPoints[i].X, temp2 + OFFSET_IF_RELOAD);
                }
                else
                {
                    lineInvPoints[i] = new Point(lineInvPoints[i].X, LINE_INV_Y12 + OFFSET_IF_RELOAD);
                }
            }

            return lineInvPoints;
        }

        private List<Point> AddDeadTimeShift(List<Point> linePoints, List<Point> lineInvPoints)
        {
            List<Point> downPoints = new List<Point>();
            List<Point> upPoints = new List<Point>();
            int deadTimeShift = (int)((m_deadTime * Math.Max(Counter1W, Counter2W)) /
                                       Math.Max(Math.Max(ImagePeriod, ImagePeriod2), 1));

            for (int i = 0; i < lineInvPoints.Count; i++)
            {
                if (lineInvPoints[i].Y == LINE_INV_Y2 + OFFSET_IF_RELOAD)
                {
                    downPoints.Add(lineInvPoints[i]);
                }
            }
            for (int i = 0; i < linePoints.Count; i++)
            {
                if (linePoints[i].Y == LINE_Y1 + OFFSET_IF_RELOAD)
                {
                    upPoints.Add(linePoints[i]);
                }
            }

            // Shift line and line_n X values by Dead Time Cycle value
            for (int i = 0; i < downPoints.Count / 2; i++)
            {
                Point pt = downPoints[i * 2 + 1];
                downPoints[i * 2 + 1] = new Point(pt.X + deadTimeShift, pt.Y);
            }
            for (int i = 0; i < upPoints.Count / 2; i++)
            {
                upPoints[i * 2] = new Point(upPoints[i * 2].X + deadTimeShift, upPoints[i * 2].Y);
            }
            int j1 = 0;
            int j2 = 0;

            for (int i = 0; i < lineInvPoints.Count; i++)
            {
                if (lineInvPoints[i].Y == LINE_INV_Y2 + OFFSET_IF_RELOAD)
                {
                    if (downPoints[j1].X != lineInvPoints[i].X)
                    {
                        if (i < lineInvPoints.Count - 1)
                        {
                            lineInvPoints[i + 1] = new Point(
                            lineInvPoints[i + 1].X + downPoints[j1].X - lineInvPoints[i].X,
                            lineInvPoints[i + 1].Y);
                        }
                        lineInvPoints[i] = new Point(downPoints[j1].X, lineInvPoints[i].Y);
                    }
                    j1++;
                }
            }
            for (int i = 0; i < linePoints.Count; i++)
            {
                if (linePoints[i].Y == LINE_Y1 + OFFSET_IF_RELOAD)
                {
                    if (upPoints[j2].X != linePoints[i].X)
                    {
                        if (i > 0)
                        {
                            linePoints[i - 1] = new Point(
                            linePoints[i - 1].X + upPoints[j2].X - linePoints[i].X,
                            linePoints[i - 1].Y);
                        }                
                        linePoints[i] = new Point(upPoints[j2].X, linePoints[i].Y);
                    }
                    j2++;
                }
            }

            return lineInvPoints;
        }

        private void CheckLinePointsOrder(List<Point> line)
        {
            // If line contains overlayed points or X became wrong after right-shift, remove duplicate points 
            // If X order is wrong, points are shifted back to left and then duplicates are removed. That's why 
            // there is a need to do several cycles
            for (int k = 0; k < 4; k++)
            {
                for (int i = 0; i < line.Count - 1; i++)
                {
                    if (line[i].X > line[i + 1].X)
                    {
                        line[i] = new Point(line[i + 1].X, line[i].Y);
                    }

                    if (line[i] == line[i + 1])
                    {
                        if (i < line.Count - 2)
                            line.RemoveAt(i + 1);
                        line.RemoveAt(i);
                    }
                }
            }

            // Check if X coordinate doesn't exceed right border 
            for (int i = 0; i < line.Count; i++)
            {
                if (line[i].X > X3)
                {
                    line[i] = new Point(X3, line[i].Y);
                }
            }
        }
    }
}
