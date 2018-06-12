/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Drawing;
using System.Diagnostics;
using System.Windows.Forms;
using System.Collections.Generic;
using CyDesigner.Toolkit;
using CyDesigner.Extensions.Common;

namespace SCB_SPI_PDL_v2_0.Controls
{
    public class CyImagePageControl : CyImageDefaultPageControl, IDisposable
    {
        CyParameters m_params;

        public CyImagePageControl(Image image, PictureBoxSizeMode sizeMode, bool onTop, SizeType sizeType, int height,
            CyParameters parameters)
            : base(image, sizeMode, onTop, sizeType, height)
        {
            m_params = parameters;
            TypeSpecificControl.BackColor = Color.White;
        }

        public override void Refresh(CyQueryArgs args)
        {
            TypeSpecificControl.Size = Image.Size;
            UpdateDrawing();
            base.Refresh(args);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                // dispose of managed disposable members
                Image.Dispose();
            }
            // release unmanaged resources
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        ~CyImagePageControl()
        {
            Dispose(false);
        }

        private void UpdateDrawing()
        {
            // Image constants
            const int PB_SPIMTEXT_WIDTH = 40;
            const int PB_EXTENTS_BORDER = 5;
            const int PB_POLYGON_WIDTH = 4;
            const int NUM_WAVEFORMS = 5;

            if ((Image.Width == 0) || (Image.Height == 0))
                return;

            const int SS_LINE_INDEX = 0;
            const int SCLK_LINE_INDEX = 1;
            const int MOSI_LINE_INDEX = 2;
            const int MISO_LINE_INDEX = 3;
            const int SAMPLE_LINE_INDEX = 4;

            bool normal_mode = ((m_params.SclkMode == CyESCLKModeType.MODE_00) ||
                  (m_params.SclkMode == CyESCLKModeType.MODE_01));
            bool starthigh = (m_params.SclkMode == CyESCLKModeType.MODE_01) ||
                (m_params.SclkMode == CyESCLKModeType.MODE_11);
            bool shiftDir = (m_params.BitsOrder != CyEBitOrderType.MSB_FIRST);

            bool nsMode = m_params.SubMode == CyESubModeType.NS;
            int numberOfBits = nsMode ? 7 : m_params.TxWordWidth;
            int numberOfTXBits = m_params.TxWordWidth;
            int numberOfRXBits = m_params.RxWordWidth;

            int misoStart = nsMode ? 6 : 0;
            int mosiEnd = nsMode ? 6 : numberOfBits * 2;

            int misoSt = 2 + Convert.ToInt32(normal_mode == false) +
               Convert.ToInt32(m_params.EnableLateMisoSample);

            bool hideMiso = m_params.RemoveMiso;
            bool hideMosi = m_params.RemoveMosi;
            bool hideSclk = m_params.RemoveSclk;
            bool hideSample = (hideMiso && m_params.Mode == CyEModeType.SPI_MASTER) ||
                              (hideMosi && m_params.Mode == CyEModeType.SPI_SLAVE);
            bool hideSS = m_params.NumberOfSSLines == 0;

            Image waveform = new Bitmap(Image.Width, Image.Height);

            using (Graphics wfg = Graphics.FromImage(waveform))
            using (SolidBrush blkbrush = new SolidBrush(Color.Black))
            using (Pen extentspen = new Pen(blkbrush))
            using (Font perfont = new Font("Arial", 10, FontStyle.Regular, GraphicsUnit.Pixel))
            {
                wfg.Clear(Color.White);

                // Display No Signal label when no signals were selected
                if (hideMiso && hideMosi && hideSclk && hideSample && hideSS)
                {
                    using (Font labelFnt = new Font("Microsoft Sans Serif", 16, FontStyle.Regular, GraphicsUnit.Pixel))
                    using (Font descFnt = new Font("Microsoft Sans Serif", 12, FontStyle.Regular, GraphicsUnit.Pixel))
                    {
                        SizeF labelSize = wfg.MeasureString(Resources.NoSignalLabel, labelFnt);
                        SizeF descSize = wfg.MeasureString(Resources.NoSignalDescription, descFnt);
                        wfg.DrawString(Resources.NoSignalLabel, labelFnt, Brushes.Black,
                            Image.Width / 2 - labelSize.Width / 2,
                            Image.Height / 2 - labelSize.Height / 2);
                        wfg.DrawString(Resources.NoSignalDescription, descFnt, Brushes.Black,
                            Image.Width / 2 - descSize.Width / 2,
                            Image.Height / 2 - descSize.Height / 2 + labelSize.Height);
                    }
                }
                else
                {
                    float extentsleft = PB_EXTENTS_BORDER + PB_SPIMTEXT_WIDTH;
                    float extentsright = Image.Width - PB_EXTENTS_BORDER;

                    // Setup the right, left and center indicators
                    extentspen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;
                    // Draw the Left Extents Line
                    wfg.DrawLine(extentspen, extentsleft, PB_EXTENTS_BORDER,
                        extentsleft, Image.Height - PB_EXTENTS_BORDER);

                    // Setup and draw all of the waveforms
                    string[] wfnames = new string[NUM_WAVEFORMS];

                    wfnames[SS_LINE_INDEX] = "SS";
                    wfnames[SCLK_LINE_INDEX] = "SCLK";
                    wfnames[MOSI_LINE_INDEX] = "MOSI";
                    wfnames[MISO_LINE_INDEX] = "MISO";
                    wfnames[SAMPLE_LINE_INDEX] = "Sample";

                    // Each waveform's height is dependent upon the drawing size minus a top and bottom border 
                    // and the top period waveform which is the size of two polygon widths, and an bottom 
                    // ticker tape of 2 polygon widths
                    float wfheight = (Image.Height - (2 * PB_EXTENTS_BORDER) - (4 * PB_POLYGON_WIDTH)) /
                        (float)NUM_WAVEFORMS;
                    // Fill in All Waveform Names
                    for (int i = 0; i < NUM_WAVEFORMS; i++)
                    {
                        if ((hideMiso && i == MISO_LINE_INDEX) ||
                            (hideMosi && i == MOSI_LINE_INDEX) ||
                            (hideSclk && i == SCLK_LINE_INDEX) ||
                            (hideSample && i == SAMPLE_LINE_INDEX) ||
                            (hideSS && i == SS_LINE_INDEX))
                            continue;

                        PointF pt = new PointF(extentsleft - wfg.MeasureString(wfnames[i], perfont).Width -
                            PB_EXTENTS_BORDER, PB_EXTENTS_BORDER + (2 * PB_POLYGON_WIDTH) + (wfheight * i) +
                            (wfheight / 2) - (wfg.MeasureString(wfnames[i], perfont).Height / 2));
                        wfg.DrawString(wfnames[i], perfont, blkbrush, pt);
                    }

                    // Draw Waveforms
                    float lastXPoint = extentsright; // point that indicates the end of timeline
                    int numsegments = 2 + (Convert.ToInt16(numberOfBits) * 2) + 3;
                    for (int i = 0; i < NUM_WAVEFORMS; i++)
                    {
                        float highY = PB_EXTENTS_BORDER + (2 * PB_POLYGON_WIDTH) + (wfheight * i) + (wfheight / 8);
                        float lowY = PB_EXTENTS_BORDER + (2 * PB_POLYGON_WIDTH) + (wfheight * (i + 1));
                        float middle = (lowY + highY) / 2;
                        float segwidth = (extentsright - extentsleft) / numsegments;

                        List<float> segs = new List<float>();
                        for (int x = 0; x < numsegments; x++)
                        {
                            segs.Add(extentsleft + (x * segwidth));
                        }
                        using (SolidBrush wfbrush = new SolidBrush(Color.Blue))
                        using (Pen pen = new Pen(wfbrush))
                        {
                            string val = null;
                            int j = 0;

                            switch (wfnames[i])
                            {
                                case "SS":
                                    if (hideSS)
                                        break;

                                    float lineHighY = highY;
                                    float lineLowY = lowY;
                                    if (m_params.Ss0Polarity == CyEActivePolarityType.ACTIVE_HIGH)
                                    {
                                        // Inverse diagram
                                        lineHighY = lowY;
                                        lineLowY = highY;
                                    }

                                    switch (m_params.SubMode)
                                    {
                                        case CyESubModeType.MOTOROLA:
                                            wfg.DrawLine(pen, segs[0], lineHighY, segs[2], lineHighY);
                                            wfg.DrawLine(pen, segs[2], lineHighY, segs[2], lineLowY);
                                            wfg.DrawLine(pen, segs[2], lineLowY, segs[numsegments - 2], lineLowY);
                                            wfg.DrawLine(pen, segs[numsegments - 2], lineLowY, segs[numsegments - 2], lineHighY);
                                            wfg.DrawLine(pen, segs[numsegments - 2], lineHighY, segs[numsegments - 1], lineHighY);
                                            break;
                                        case CyESubModeType.TI_COINCIDES:
                                            wfg.DrawLine(pen, segs[0], lineLowY, segs[3], lineLowY);
                                            wfg.DrawLine(pen, segs[3], lineHighY, segs[3], lineLowY);

                                            wfg.DrawLine(pen, segs[3], lineHighY, segs[5], lineHighY);
                                            wfg.DrawLine(pen, segs[5], lineHighY, segs[5], lineLowY);
                                            wfg.DrawLine(pen, segs[5], lineLowY, segs[numsegments - 1], lineLowY);
                                            break;
                                        case CyESubModeType.TI_PRECEDES:
                                            wfg.DrawLine(pen, segs[0], lineLowY, segs[1], lineLowY);
                                            wfg.DrawLine(pen, segs[1], lineHighY, segs[1], lineLowY);

                                            wfg.DrawLine(pen, segs[1], lineHighY, segs[3], lineHighY);
                                            wfg.DrawLine(pen, segs[3], lineHighY, segs[3], lineLowY);
                                            wfg.DrawLine(pen, segs[3], lineLowY, segs[numsegments - 1], lineLowY);
                                            break;
                                        case CyESubModeType.NS:
                                            wfg.DrawLine(pen, segs[0], lineHighY, segs[1], lineHighY);
                                            wfg.DrawLine(pen, segs[1], lineHighY, segs[1], lineLowY);
                                            wfg.DrawLine(pen, segs[1], lineLowY, segs[numsegments - 2], lineLowY);
                                            wfg.DrawLine(pen, segs[numsegments - 2], lineLowY, segs[numsegments - 2], lineHighY);
                                            wfg.DrawLine(pen, segs[numsegments - 2], lineHighY, segs[numsegments - 1], lineHighY);
                                            break;
                                        default:
                                            Debug.Fail("Unhandled enum value " + m_params.SubMode);
                                            break;
                                    }
                                    break;

                                case "MOSI":
                                    if (hideMosi)
                                        break;

                                    bool no_shift = normal_mode;
                                    int mosiSt = no_shift ? 2 : 3;

                                    // Draw Bus to First Transition Point
                                    wfg.DrawLine(pen, segs[0], highY, segs[mosiSt] - 2, highY);
                                    wfg.DrawLine(pen, segs[0], lowY, segs[mosiSt] - 2, lowY);
                                    // Draw Transition
                                    wfg.DrawLine(pen, segs[mosiSt] - 2, highY, segs[mosiSt] + 2, lowY);
                                    wfg.DrawLine(pen, segs[mosiSt] - 2, lowY, segs[mosiSt] + 2, highY);

                                    for (j = 0; j < (mosiEnd);)
                                    {
                                        bool nsEndNode = (j + 2 >= mosiEnd) && nsMode;
                                        // Draw Bus to Transition Point
                                        wfg.DrawLine(pen, segs[mosiSt + j] + 2, highY, segs[mosiSt + (j + 2)] - 2, highY);
                                        wfg.DrawLine(pen, segs[mosiSt + j] + 2, lowY, segs[mosiSt + (j + 2)] - 2, lowY);

                                        if (nsEndNode == false)
                                        {
                                            // Draw Transition line
                                            wfg.DrawLine(pen, segs[mosiSt + (j + 2)] - 2, highY,
                                                segs[mosiSt + (j + 2)] + 2, lowY);
                                            wfg.DrawLine(pen, segs[mosiSt + (j + 2)] - 2, lowY, segs[mosiSt + (j + 2)] + 2,
                                                highY);
                                        }

                                        #region label text
                                        val = String.Format("D{0}", shiftDir ? j / 2 : numberOfBits - (j / 2) - 1);
                                        if (nsMode)
                                        {
                                            int numBits = (m_params.Mode == CyEModeType.SPI_MASTER) ? numberOfTXBits : numberOfRXBits;
                                            if (j == 0)
                                                val = String.Format("D{0}", shiftDir ? 0 : numBits - 1);
                                            else if (nsEndNode)
                                                val = String.Format("D{0}", shiftDir ? numBits - 1 : 0);
                                            else
                                                val = "...";
                                        }
                                        #endregion

                                        SizeF strsize = wfg.MeasureString(val, perfont);
                                        float centerx = segs[mosiSt + j] + segwidth;
                                        using (SolidBrush strBrush = new SolidBrush(Color.Black))
                                        {
                                            wfg.DrawString(val, perfont, strBrush,
                                                new RectangleF(centerx - (strsize.Width / 2f), highY + ((wfheight) / 2f) -
                                                    (strsize.Height / 2f), strsize.Width, strsize.Height));
                                        }

                                        j += 2;
                                    }

                                    if (nsMode)
                                    {
                                        // Draw Transition line
                                        wfg.DrawLine(pen, segs[mosiSt + j] - 2, highY, segs[mosiSt + j] + 1, middle);
                                        wfg.DrawLine(pen, segs[mosiSt + j] - 2, lowY, segs[mosiSt + j] + 1, middle);

                                        //Draw end line
                                        wfg.DrawLine(pen, segs[mosiSt + j] + 1, middle, segs[segs.Count - 1], middle);
                                    }
                                    else
                                    {
                                        // Draw Bus to Transition Point
                                        wfg.DrawLine(pen, segs[mosiSt + j] + 2, lowY, segs[mosiSt + (j + 1 +
                                            Convert.ToInt32(no_shift))], lowY);
                                        wfg.DrawLine(pen, segs[mosiSt + j] + 2, highY, segs[mosiSt + (j + 1 +
                                            Convert.ToInt32(no_shift))], highY);
                                    }
                                    break;

                                case "MISO":
                                    if (hideMiso)
                                        break;

                                    if (nsMode)
                                    {
                                        // Draw Bus to First Transition Point
                                        wfg.DrawLine(pen, segs[0], middle, segs[misoSt + (misoStart)], middle);
                                        // Draw Transition for idle
                                        wfg.DrawLine(pen, segs[misoSt + (misoStart)], middle, segs[misoSt + misoStart] + 2,
                                            lowY);
                                    }
                                    else
                                    {
                                        // Draw Bus to First Transition Point
                                        wfg.DrawLine(pen, segs[0], highY, segs[misoSt] - 2, highY);
                                        wfg.DrawLine(pen, segs[0], lowY, segs[misoSt] - 2, lowY);
                                        // Draw Transition
                                        wfg.DrawLine(pen, segs[misoSt] - 2, highY, segs[misoSt] + 2, lowY);
                                        wfg.DrawLine(pen, segs[misoSt] - 2, lowY, segs[misoSt] + 2, highY);
                                    }
                                    for (j = misoStart; j < (numberOfBits * 2);)
                                    {
                                        bool idle = (j == misoStart) && nsMode;

                                        // Draw Bus to Transition Point. For idle node oly bottom line
                                        if (idle == false)
                                            wfg.DrawLine(pen, segs[misoSt + j] + 2, highY, segs[misoSt + (j + 2)] - 2,
                                                highY);
                                        wfg.DrawLine(pen, segs[misoSt + j] + 2, lowY, segs[misoSt + (j + 2)] - 2, lowY);

                                        // Draw Transition. For idle node oly bottom line
                                        if (idle)
                                            wfg.DrawLine(pen, segs[misoSt + (j + 2)], middle, segs[misoSt + (j + 2)] + 2,
                                                lowY);
                                        else
                                            wfg.DrawLine(pen, segs[misoSt + (j + 2)] - 2, highY, segs[misoSt + (j + 2)] + 2,
                                                lowY);
                                        wfg.DrawLine(pen, segs[misoSt + (j + 2)] - 2, lowY, segs[misoSt + (j + 2)] + 2,
                                            highY);

                                        #region label text
                                        val = String.Format("D{0}", shiftDir ? j / 2 : numberOfBits - (j / 2) - 1);
                                        if (nsMode)
                                        {
                                            int numBits = (m_params.Mode == CyEModeType.SPI_MASTER) ? numberOfRXBits : numberOfTXBits;
                                            if (idle)
                                                val = "idle";
                                            else if (j == misoStart + 2)
                                                val = String.Format("D{0}", shiftDir ? 0 : numBits - 1);
                                            else if (j + 2 >= (numberOfBits * 2))
                                                val = String.Format("D{0}", shiftDir ? numBits - 1 : 0);
                                            else
                                                val = "...";
                                        }
                                        #endregion

                                        SizeF strsize = wfg.MeasureString(val, perfont);
                                        float centerx = segs[misoSt + j] + segwidth;
                                        using (SolidBrush strBrush = new SolidBrush(Color.Black))
                                        {
                                            wfg.DrawString(val, perfont, strBrush,
                                                            new RectangleF(centerx - (strsize.Width / 2f), highY +
                                                                ((wfheight) / 2f) - (strsize.Height / 2f), strsize.Width,
                                                                strsize.Height));
                                        }
                                        j += 2;
                                    }

                                    // Draw Bus to Transition Point
                                    wfg.DrawLine(pen, segs[misoSt + j] + 2, lowY, segs[segs.Count - 1], lowY);
                                    wfg.DrawLine(pen, segs[misoSt + j] + 2, highY, segs[segs.Count - 1], highY);
                                    break;

                                case "SCLK":
                                    if (hideSclk)
                                        break;

                                    int goHighSeg;
                                    int addSegments;

                                    if (m_params.EnableSclkFreeRunning)
                                    {
                                        goHighSeg = 1;
                                        addSegments = 2;
                                    }
                                    else
                                    {
                                        goHighSeg = m_params.SubMode == CyESubModeType.TI_PRECEDES ? 1 : 3;
                                        addSegments = m_params.SubMode == CyESubModeType.TI_PRECEDES ? 1 : 0;
                                    }

                                    wfg.DrawLine(pen, segs[0], starthigh ? highY : lowY, segs[goHighSeg], starthigh ?
                                        highY : lowY);
                                    wfg.DrawLine(pen, segs[goHighSeg], starthigh ? highY : lowY, segs[goHighSeg],
                                        starthigh ? highY : lowY);

                                    for (j = 0; j < (numberOfBits * 2) + addSegments;)
                                    {
                                        wfg.DrawLine(pen, segs[goHighSeg + j], starthigh ? highY : lowY,
                                            segs[goHighSeg + j], starthigh ? lowY : highY);
                                        wfg.DrawLine(pen, segs[goHighSeg + j++], starthigh ? lowY : highY,
                                            segs[goHighSeg + j], starthigh ? lowY : highY);
                                        wfg.DrawLine(pen, segs[goHighSeg + j], starthigh ? lowY : highY,
                                            segs[goHighSeg + j], starthigh ? highY : lowY);
                                        wfg.DrawLine(pen, segs[goHighSeg + j++], starthigh ? highY : lowY,
                                            segs[goHighSeg + j], starthigh ? highY : lowY);
                                    }

                                    if (m_params.EnableSclkFreeRunning)
                                    {
                                        wfg.DrawLine(pen, segs[goHighSeg + j], starthigh ? lowY : highY,
                                                segs[goHighSeg + j], starthigh ? highY : lowY);
                                        wfg.DrawLine(pen, segs[goHighSeg + j++], starthigh ? lowY : highY,
                                            segs[goHighSeg + j], starthigh ? lowY : highY);
                                    }
                                    else
                                    {
                                        wfg.DrawLine(pen, segs[goHighSeg + j++], starthigh ? highY : lowY,
                                        segs[goHighSeg + j], starthigh ? highY : lowY);
                                    }
                                    break;

                                case "Sample":
                                    if (hideSample)
                                        break;

                                    wfg.DrawLine(pen, segs[0], lowY, segs[misoSt + 1] - 2, lowY); // go to first edge
                                    for (j = 0; j < (numberOfBits * 2);)
                                    {
                                        wfg.DrawLine(pen, segs[misoSt + 1 + j] - 2, lowY, segs[misoSt + 1 + j] - 2, highY);
                                        wfg.DrawLine(pen, segs[misoSt + 1 + j] - 2, highY, segs[misoSt + 1 + j] + 2, highY);
                                        wfg.DrawLine(pen, segs[misoSt + 1 + j] + 2, highY, segs[misoSt + 1 + j] + 2, lowY);

                                        if (j + 2 < numberOfBits * 2)
                                            wfg.DrawLine(pen, segs[misoSt + 1 + j] + 2, lowY,
                                                segs[misoSt + 1 + (j + 2)] - 2, lowY);
                                        else
                                            wfg.DrawLine(pen, segs[misoSt + 1 + j] + 2, lowY, segs[segs.Count - 1], lowY);

                                        j += 2;
                                    }
                                    break;

                                case "Interrupt":
                                    break;

                                default:
                                    Debug.Fail("Unhandled waveform name.");
                                    break;
                            }
                        }
                        lastXPoint = segs[segs.Count - 1];
                    }
                    // Draw the Right Extents Line
                    wfg.DrawLine(extentspen, lastXPoint, PB_EXTENTS_BORDER,
                        lastXPoint, Image.Height - PB_EXTENTS_BORDER);
                }
            }

            //
            // Assign the image and dispose resources
            //
            Bitmap old = Image as Bitmap;
            Image = waveform;
            if (old != null)
            {
                old.Dispose();
            }
        }
    }
}
