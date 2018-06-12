/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Windows.Forms;

namespace Cypress.Comps.PinsAndPorts.cy_pins_v2_10
{
    public class CyPinPicture : PictureBox
    {
        readonly Dictionary<string, Metafile> m_pics;

        const string BidirImageKey = "Bidir";
        const string AnalogImageKey = "Analog";
        const string DigInImageKey = "DigIn";
        const string DigOutImageKey = "DigOut";
        const string DigInNCImageKey = "DigInNC";
        const string DigOutNCImageKey = "DigOutNC";
        const string DigInAnalogImageKey = "DigInAnalog";
        const string DigOutOEImageKey = "DigOutOE";
        const string DigInNCAnalogImageKey = "DigInNCAnalog";
        const string DigOutNCOEImageKey = "DigOutNCOE";
        const string AnnLeftImageKey = "AnnLeft";
        const string AnnRightImageKey = "AnnRight";
        const string Ann1DownLeftImageKey = "Ann1DownLeft";
        const string Ann1DownRightImageKey = "Ann1DownRight";
        const string Ann2DownLeftImageKey = "Ann2DownLeft";

        private bool m_showAnalog;
        public bool ShowAnalog
        {
            get { return m_showAnalog; }
            set { m_showAnalog = value; }
        }

        private bool m_showDigitalInput;
        public bool ShowDigitalInput
        {
            get { return m_showDigitalInput; }
            set { m_showDigitalInput = value; }
        }

        private bool m_showDigitalOutput;
        public bool ShowDigitalOutput
        {
            get { return m_showDigitalOutput; }
            set { m_showDigitalOutput = value; }
        }

        private bool m_showOutputEnable;
        public bool ShowOutputEnable
        {
            get { return m_showOutputEnable; }
            set { m_showOutputEnable = value; }
        }

        private bool m_showBidirectional;
        public bool ShowBidirectional
        {
            get { return m_showBidirectional; }
            set { m_showBidirectional = value; }
        }

        private bool m_showDigitalInputConnection;
        public bool ShowDigitalInputConnection
        {
            get { return m_showDigitalInputConnection; }
            set { m_showDigitalInputConnection = value; }
        }

        private bool m_showDigitalOutputConnection;
        public bool ShowDigitalOutputConnection
        {
            get { return m_showDigitalOutputConnection; }
            set { m_showDigitalOutputConnection = value; }
        }

        private bool m_showAnnotation;
        public bool ShowAnnotation
        {
            get { return m_showAnnotation; }
            set { m_showAnnotation = value; }
        }

        public CyPinPicture()
        {
            DoubleBuffered = true;
            BackColor = Color.White;

            SetStyle(
                ControlStyles.AllPaintingInWmPaint |
                ControlStyles.OptimizedDoubleBuffer |
                ControlStyles.ResizeRedraw |
                ControlStyles.UserPaint, true);

            m_pics = new Dictionary<string, Metafile>();

            using (MemoryStream ms = new MemoryStream(Resource1.BidirEMF))
            {
                m_pics.Add(BidirImageKey, new Metafile(ms));
            }
            using (MemoryStream ms = new MemoryStream(Resource1.AnalogEMF))
            {
                m_pics.Add(AnalogImageKey, new Metafile(ms));
            }
            using (MemoryStream ms = new MemoryStream(Resource1.DigInEMF))
            {
                m_pics.Add(DigInImageKey, new Metafile(ms));
            }
            using (MemoryStream ms = new MemoryStream(Resource1.DigOutEMF))
            {
                m_pics.Add(DigOutImageKey, new Metafile(ms));
            }
            using (MemoryStream ms = new MemoryStream(Resource1.DigInNCEMF))
            {
                m_pics.Add(DigInNCImageKey, new Metafile(ms));
            }
            using (MemoryStream ms = new MemoryStream(Resource1.DigOutNCEMF))
            {
                m_pics.Add(DigOutNCImageKey, new Metafile(ms));
            }
            using (MemoryStream ms = new MemoryStream(Resource1.DigInAnalogEMF))
            {
                m_pics.Add(DigInAnalogImageKey, new Metafile(ms));
            }
            using (MemoryStream ms = new MemoryStream(Resource1.DigOutOEEMF))
            {
                m_pics.Add(DigOutOEImageKey, new Metafile(ms));
            }
            using (MemoryStream ms = new MemoryStream(Resource1.DigInNCAnalogEMF))
            {
                m_pics.Add(DigInNCAnalogImageKey, new Metafile(ms));
            }
            using (MemoryStream ms = new MemoryStream(Resource1.DigOutNCOEEMF))
            {
                m_pics.Add(DigOutNCOEImageKey, new Metafile(ms));
            }
            using (MemoryStream ms = new MemoryStream(Resource1.AnnLeftEMF))
            {
                m_pics.Add(AnnLeftImageKey, new Metafile(ms));
            }
            using (MemoryStream ms = new MemoryStream(Resource1.AnnRightEMF))
            {
                m_pics.Add(AnnRightImageKey, new Metafile(ms));
            }
            using (MemoryStream ms = new MemoryStream(Resource1.Ann1DownLeftEMF))
            {
                m_pics.Add(Ann1DownLeftImageKey, new Metafile(ms));
            }
            using (MemoryStream ms = new MemoryStream(Resource1.Ann1DownRightEMF))
            {
                m_pics.Add(Ann1DownRightImageKey, new Metafile(ms));
            }
            using (MemoryStream ms = new MemoryStream(Resource1.Ann2DownLeftEMF))
            {
                m_pics.Add(Ann2DownLeftImageKey, new Metafile(ms));
            }
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            Rectangle border = new Rectangle(0, 0, Width, Height);
            e.Graphics.Clear(BackColor);

            //Deal with left side (dig out, oe, bidir).
            if (ShowBidirectional)
            {
                if (ShowAnnotation)
                {
                    if (ShowAnalog)
                    {
                        e.Graphics.DrawImage(m_pics[Ann1DownLeftImageKey], border);
                    }
                    else
                    {
                        e.Graphics.DrawImage(m_pics[AnnRightImageKey], border);
                    }
                }
                e.Graphics.DrawImage(m_pics[BidirImageKey], border);
            }
            else if (ShowDigitalOutput)
            {
                if (ShowOutputEnable)
                {
                    if (ShowAnnotation)
                    {
                        if (ShowAnalog || ShowDigitalInput)
                        {
                            if (ShowAnalog && ShowDigitalInput)
                            {
                                e.Graphics.DrawImage(m_pics[Ann2DownLeftImageKey], border);
                            }
                            else
                            {
                                e.Graphics.DrawImage(m_pics[Ann1DownRightImageKey], border);
                            }
                        }
                        else
                        {
                            e.Graphics.DrawImage(m_pics[AnnRightImageKey], border);
                        }
                    }
                    if (ShowDigitalOutputConnection)
                    {
                        e.Graphics.DrawImage(m_pics[DigOutOEImageKey], border);
                    }
                    else
                    {
                        e.Graphics.DrawImage(m_pics[DigOutNCOEImageKey], border);
                    }
                }
                else
                {
                    if (ShowAnnotation)
                    {
                        if (ShowAnalog || ShowDigitalInput)
                        {
                            e.Graphics.DrawImage(m_pics[Ann1DownLeftImageKey], border);
                        }
                        else
                        {
                            e.Graphics.DrawImage(m_pics[AnnRightImageKey], border);
                        }
                    }
                    if (ShowDigitalOutputConnection)
                    {
                        e.Graphics.DrawImage(m_pics[DigOutImageKey], border);
                    }
                    else
                    {
                        e.Graphics.DrawImage(m_pics[DigOutNCImageKey], border);
                    }
                }
            }

            //Deal with right side (dig in, analog).
            if (ShowDigitalInput)
            {
                if (ShowAnnotation && !ShowBidirectional && !ShowDigitalOutput)
                {
                    e.Graphics.DrawImage(m_pics[AnnLeftImageKey], border);
                }
                if (ShowAnalog)
                {
                    if (ShowDigitalInputConnection)
                    {
                        e.Graphics.DrawImage(m_pics[DigInAnalogImageKey], border);
                    }
                    else
                    {
                        e.Graphics.DrawImage(m_pics[DigInNCAnalogImageKey], border);
                    }
                }
                else
                {
                    if (ShowDigitalInputConnection)
                    {
                        e.Graphics.DrawImage(m_pics[DigInImageKey], border);
                    }
                    else
                    {
                        e.Graphics.DrawImage(m_pics[DigInNCImageKey], border);
                    }
                }
            }
            else if (ShowAnalog)
            {
                if (ShowAnnotation && !ShowBidirectional && !ShowDigitalOutput)
                {
                    e.Graphics.DrawImage(m_pics[AnnLeftImageKey], border);
                }
                e.Graphics.DrawImage(m_pics[AnalogImageKey], border);
            }

            base.OnPaint(e);
        }
    }
}
