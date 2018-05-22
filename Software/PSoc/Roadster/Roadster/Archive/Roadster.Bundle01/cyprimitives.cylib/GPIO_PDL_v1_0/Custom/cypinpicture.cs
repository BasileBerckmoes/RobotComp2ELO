/*******************************************************************************
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Windows.Forms;

namespace Cypress.Comps.PinsAndPorts.GPIO_PDL_v1_0
{
    [ExcludeFromCodeCoverage]
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

        public bool ShowAnalog { get; set; }
        public bool ShowDigitalInput { get; set; }
        public bool ShowDigitalOutput { get; set; }
        public bool ShowOutputEnable { get; set; }
        public bool ShowBidirectional { get; set; }
        public bool ShowDigitalInputConnection { get; set; }
        public bool ShowDigitalOutputConnection { get; set; }
        public bool ShowAnnotation { get; set; }

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

            string pic;

            //Deal with left side (dig out, oe, bidir).
            if (ShowBidirectional)
            {
                if (ShowAnnotation)
                    e.Graphics.DrawImage(m_pics[ShowAnalog ? Ann1DownLeftImageKey : AnnRightImageKey], border);

                e.Graphics.DrawImage(m_pics[BidirImageKey], border);
            }
            else if (ShowDigitalOutput)
            {
                if (ShowOutputEnable)
                {
                    if (ShowAnnotation)
                    {
                        if (ShowAnalog && ShowDigitalInput)
                            pic = Ann2DownLeftImageKey;
                        else if (ShowAnalog || ShowDigitalInput)
                            pic = Ann1DownRightImageKey;
                        else
                            pic = AnnRightImageKey;
                        e.Graphics.DrawImage(m_pics[pic], border);
                    }
                    pic = ShowDigitalOutputConnection ? DigOutOEImageKey : DigOutNCOEImageKey;
                }
                else
                {
                    if (ShowAnnotation)
                    {
                        pic = (ShowAnalog || ShowDigitalInput) ? Ann1DownLeftImageKey : AnnRightImageKey;
                        e.Graphics.DrawImage(m_pics[pic], border);
                    }
                    pic = ShowDigitalOutputConnection ? DigOutImageKey : DigOutNCImageKey;
                }
                e.Graphics.DrawImage(m_pics[pic], border);
            }

            //Deal with right side (dig in, analog).
            if (ShowDigitalInput)
            {
                if (ShowAnnotation && !ShowBidirectional && !ShowDigitalOutput)
                    e.Graphics.DrawImage(m_pics[AnnLeftImageKey], border);

                if (ShowAnalog)
                    pic = ShowDigitalInputConnection ? DigInAnalogImageKey : DigInNCAnalogImageKey;
                else
                    pic = ShowDigitalInputConnection ? DigInImageKey : DigInNCImageKey;
                e.Graphics.DrawImage(m_pics[pic], border);
            }
            else if (ShowAnalog)
            {
                if (ShowAnnotation && !ShowBidirectional && !ShowDigitalOutput)
                    e.Graphics.DrawImage(m_pics[AnnLeftImageKey], border);

                e.Graphics.DrawImage(m_pics[AnalogImageKey], border);
            }

            base.OnPaint(e);
        }
    }
}
