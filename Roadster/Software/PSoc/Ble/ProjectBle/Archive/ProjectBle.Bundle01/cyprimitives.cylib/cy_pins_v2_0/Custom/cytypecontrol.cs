/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing.Imaging;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

using CyDesigner.Common.Base;

namespace Cypress.Comps.PinsAndPorts.cy_pins_v2_0
{
    public partial class CyTypeControl : UserControl
    {
        public delegate void PinTypeChanged(CyPinType pinType, IList<CyPinData.PerPin> pins);

        public static readonly CyPinData.Key[] OwnedSettings = new CyPinData.Key[]
        {
            CyPinData.Key.TYPE_IS_ANALOG,
            CyPinData.Key.TYPE_IS_DIGITAL_IN,
            CyPinData.Key.TYPE_IS_DIGITAL_IN_HW,
            CyPinData.Key.TYPE_IS_DIGITAL_OUT,
            CyPinData.Key.TYPE_IS_DIGITAL_OUT_HW,
            CyPinData.Key.TYPE_IS_DIGITAL_OUT_OE,
            CyPinData.Key.TYPE_IS_BIDIRECTIONAL,
            CyPinData.Key.TYPE_SHOW_EXTERNAL_TERM,
        };

        private IList<CyPinData.PerPin> m_pins;
        private readonly PinTypeChanged m_pinTypeChanged;

        public CyTypeControl(
            CyDeviceSupport deviceSupport, CyErrorManager errMgr, CyPinData pins, PinTypeChanged pinTypeChanged)
        {
            InitializeComponent();

            m_pinTypeChanged = pinTypeChanged;
            bool showAnalog = !deviceSupport.IsTSG4;
            foreach (CyPinData.PerPin pin in pins.Pins)
                showAnalog |= ((pin.Type & CyPinType.ANALOG) == CyPinType.ANALOG);

            EnableEvents();

            m_errorProvider.SetIconAlignment(m_previewLabel, ErrorIconAlignment.MiddleRight);
            m_errorProvider.SetIconPadding(m_previewLabel, 3);

            m_analogCheckBox.Enabled = showAnalog;

            errMgr.RegisterSettingOwner(CyPinData.Key.TYPE_IS_ANALOG, m_errorProvider, m_analogCheckBox);
            errMgr.RegisterSettingOwner(CyPinData.Key.TYPE_IS_DIGITAL_IN, m_errorProvider, m_digInputCheckBox);
            errMgr.RegisterSettingOwner(CyPinData.Key.TYPE_IS_DIGITAL_IN_HW, m_errorProvider, m_displayDigitalInputCheckBox);
            errMgr.RegisterSettingOwner(CyPinData.Key.TYPE_IS_DIGITAL_OUT, m_errorProvider, m_digOutputCheckBox);
            errMgr.RegisterSettingOwner(CyPinData.Key.TYPE_IS_DIGITAL_OUT_HW, m_errorProvider, m_displayDigitalOutputCheckBox);
            errMgr.RegisterSettingOwner(CyPinData.Key.TYPE_IS_DIGITAL_OUT_OE, m_errorProvider, m_oeCheckBox);
            errMgr.RegisterSettingOwner(CyPinData.Key.TYPE_IS_BIDIRECTIONAL, m_errorProvider, m_bidirCheckBox);
            errMgr.RegisterSettingOwner(CyPinData.Key.TYPE_SHOW_EXTERNAL_TERM, m_errorProvider, m_annotCheckBox);
        }

        private void EnableEvents()
        {
            m_analogCheckBox.CheckedChanged += m_analogCheckBox_CheckedChanged;
            m_digInputCheckBox.CheckedChanged += m_digInputCheckBox_CheckedChanged;
            m_displayDigitalInputCheckBox.CheckedChanged += m_displayDigitalInputCheckBox_CheckedChanged;
            m_digOutputCheckBox.CheckedChanged += m_digOutputCheckBox_CheckedChanged;
            m_displayDigitalOutputCheckBox.CheckedChanged += m_displayDigitalOutputCheckBox_CheckedChanged;
            m_oeCheckBox.CheckedChanged += m_oeCheckBox_CheckedChanged;
            m_bidirCheckBox.CheckedChanged += m_bidirCheckBox_CheckedChanged;
            m_annotCheckBox.CheckedChanged += m_annotCheckBox_CheckedChanged;
        }
        private void DisableEvents()
        {
            m_analogCheckBox.CheckedChanged -= m_analogCheckBox_CheckedChanged;
            m_digInputCheckBox.CheckedChanged -= m_digInputCheckBox_CheckedChanged;
            m_displayDigitalInputCheckBox.CheckedChanged -= m_displayDigitalInputCheckBox_CheckedChanged;
            m_digOutputCheckBox.CheckedChanged -= m_digOutputCheckBox_CheckedChanged;
            m_displayDigitalOutputCheckBox.CheckedChanged -= m_displayDigitalOutputCheckBox_CheckedChanged;
            m_oeCheckBox.CheckedChanged -= m_oeCheckBox_CheckedChanged;
            m_bidirCheckBox.CheckedChanged -= m_bidirCheckBox_CheckedChanged;
            m_annotCheckBox.CheckedChanged -= m_annotCheckBox_CheckedChanged;
        }

        internal void UpdateData(IList<CyPinData.PerPin> pins)
        {
            m_pins = pins;

            CheckState analog = ((pins[0].Type & CyPinType.ANALOG) > 0) ? CheckState.Checked : CheckState.Unchecked;
            CheckState digIn = ((pins[0].Type & CyPinType.DIGITAL_IN) > 0) ? CheckState.Checked : CheckState.Unchecked;
            CheckState digInHw = pins[0].TypeIsDigitalInputHw ? CheckState.Checked : CheckState.Unchecked;
            CheckState digOut = ((pins[0].Type & CyPinType.DIGITAL_OUT) > 0) ? CheckState.Checked : CheckState.Unchecked;
            CheckState digOutHw = pins[0].TypeIsDigitalOutputHw ? CheckState.Checked : CheckState.Unchecked;
            CheckState digOE = ((pins[0].Type & CyPinType.OE) > 0) ? CheckState.Checked : CheckState.Unchecked;
            CheckState biDir = ((pins[0].Type & CyPinType.BIDIRECTIONAL) > 0) ? CheckState.Checked : CheckState.Unchecked;
            CheckState annot = pins[0].TypeShowExternalTerm ? CheckState.Checked : CheckState.Unchecked;

            for (int i = 1; i < pins.Count; i++)
            {
                if (analog != (((pins[i].Type & CyPinType.ANALOG) > 0) ? CheckState.Checked : CheckState.Unchecked))
                    analog = CheckState.Indeterminate;
                if (digIn != (((pins[i].Type & CyPinType.DIGITAL_IN) > 0) ? CheckState.Checked : CheckState.Unchecked))
                    digIn = CheckState.Indeterminate;
                if (digInHw != (pins[i].TypeIsDigitalInputHw ? CheckState.Checked : CheckState.Unchecked))
                    digInHw = CheckState.Indeterminate;
                if (digOut != (((pins[i].Type & CyPinType.DIGITAL_OUT) > 0) ? CheckState.Checked : CheckState.Unchecked))
                    digOut = CheckState.Indeterminate;
                if (digOutHw != (pins[i].TypeIsDigitalOutputHw ? CheckState.Checked : CheckState.Unchecked))
                    digOutHw = CheckState.Indeterminate;
                if (digOE != (((pins[i].Type & CyPinType.OE) > 0) ? CheckState.Checked : CheckState.Unchecked))
                    digOE = CheckState.Indeterminate;
                if (biDir != (((pins[i].Type & CyPinType.BIDIRECTIONAL) > 0) ? CheckState.Checked : CheckState.Unchecked))
                    biDir = CheckState.Indeterminate;
                if (annot != (pins[i].TypeShowExternalTerm ? CheckState.Checked : CheckState.Unchecked))
                    annot = CheckState.Indeterminate;
            }

            DisableEvents();

            m_analogCheckBox.CheckState = analog;
            m_digInputCheckBox.CheckState = digIn;
            m_displayDigitalInputCheckBox.CheckState = digInHw;
            m_digOutputCheckBox.CheckState = digOut;
            m_displayDigitalOutputCheckBox.CheckState = digOutHw;
            m_oeCheckBox.CheckState = digOE;
            m_bidirCheckBox.CheckState = biDir;
            m_annotCheckBox.CheckState = annot;

            UpdateDigInSubCheckBoxEnabledState();
            UpdateDigOutSubCheckBoxEnabledState();

            EnableEvents();
            UpdatePreviewPic();
        }

        private void UpdateHwPinConfig(CheckBox chkBox, CyPinType pinType)
        {
            if (!m_digOutputCheckBox.Checked && !m_digInputCheckBox.Checked &&
                !m_analogCheckBox.Checked && !m_bidirCheckBox.Checked)
            {
                MessageBox.Show("Cannot uncheck all Pin Type options.", "Operation Not Allowed",
                     MessageBoxButtons.OK, MessageBoxIcon.Information, MessageBoxDefaultButton.Button1);
                chkBox.Checked = true;
            }
            else
            {
                CyPinType newTypeOpts = 0;
                foreach (CyPinData.PerPin pin in m_pins)
                {
                    if (chkBox.Checked)
                        pin.Type |= pinType;
                    else
                        pin.Type &= ~pinType;

                    newTypeOpts |= pin.Type;
                }
                UpdatePreviewPic();
                m_pinTypeChanged(newTypeOpts, m_pins);
            }
        }

        void m_analogCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            UpdateHwPinConfig(m_analogCheckBox, CyPinType.ANALOG);
        }

        void m_digInputCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (m_digInputCheckBox.Checked)
                m_bidirCheckBox.Checked = false;
            UpdateHwPinConfig(m_digInputCheckBox, CyPinType.DIGITAL_IN);
            UpdateDigInSubCheckBoxEnabledState();
        }

        void m_displayDigitalInputCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.TypeIsDigitalInputHw = m_displayDigitalInputCheckBox.Checked;
            UpdatePreviewPic();
        }

        void m_digOutputCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (m_digOutputCheckBox.Checked)
                m_bidirCheckBox.Checked = false;
            UpdateHwPinConfig(m_digOutputCheckBox, CyPinType.DIGITAL_OUT);
            UpdateDigOutSubCheckBoxEnabledState();
        }

        void m_displayDigitalOutputCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.TypeIsDigitalOutputHw = m_displayDigitalOutputCheckBox.Checked;
            UpdatePreviewPic();
        }

        void m_oeCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            UpdateHwPinConfig(m_oeCheckBox, CyPinType.OE);
        }

        void m_bidirCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (m_bidirCheckBox.Checked)
            {
                m_digInputCheckBox.Checked = false;
                m_digOutputCheckBox.Checked = false;
            }
            UpdateHwPinConfig(m_bidirCheckBox, CyPinType.BIDIRECTIONAL);
        }

        private void m_annotCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.TypeShowExternalTerm = m_annotCheckBox.Checked;
            UpdatePreviewPic();
        }

        void UpdateDigOutSubCheckBoxEnabledState()
        {
            m_oeCheckBox.Enabled = m_digOutputCheckBox.Checked;
            m_displayDigitalOutputCheckBox.Enabled = m_digOutputCheckBox.Checked;
        }

        void UpdateDigInSubCheckBoxEnabledState()
        {
            m_displayDigitalInputCheckBox.Enabled = m_digInputCheckBox.Checked;
        }

        void UpdatePreviewPic()
        {
            m_pinPicture.ShowAnalog = m_analogCheckBox.Checked;
            m_pinPicture.ShowDigitalInput = m_digInputCheckBox.Checked;
            m_pinPicture.ShowDigitalOutput = m_digOutputCheckBox.Checked;
            m_pinPicture.ShowBidirectional = m_bidirCheckBox.Checked;
            m_pinPicture.ShowOutputEnable = m_oeCheckBox.Checked;
            m_pinPicture.ShowDigitalInputConnection = m_displayDigitalInputCheckBox.Checked;
            m_pinPicture.ShowDigitalOutputConnection = m_displayDigitalOutputCheckBox.Checked;
            m_pinPicture.ShowAnnotation = m_annotCheckBox.Checked;
            m_pinPicture.Invalidate();
        }
    }

    public class CyPinPicture : PictureBox
    {
        Dictionary<string, Metafile> m_pics;

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
            Rectangle border = new Rectangle(0, 0, this.Width, this.Height);
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
