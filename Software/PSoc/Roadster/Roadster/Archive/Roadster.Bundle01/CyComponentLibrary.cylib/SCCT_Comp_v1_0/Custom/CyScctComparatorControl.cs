/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using SCCT_Comp_v1_0; 


namespace SCCT_Comp_v1_0   
{
    public partial class CyScctComparatorControl : CyScctCompTabWrapper
    {
        private const int X_START_POINT = 40;
        private const int X_FONT_START_POINT_1 = 7;
        private const int X_FONT_START_POINT_2 = 17;
        private const int X_OFFSET_1 = 90;
        private const int Y_START_POINT_1 = 100;
        private const int Y_START_POINT_2 = 140;


        public CyScctComparatorControl(CyScctCompParameters parameters, string sTabName)
            : base(parameters,sTabName)
        {
            InitializeComponent();

            Load += delegate(object sender, EventArgs e)
            {
                UpdateSchematic();
                UpdateDrawing();
            };
        }

        /// <summary>
        /// Update controls on tab
        /// </summary>
        public void UpdateFormFromParams()
        {            
            //Set the Polarity Radio Button
            switch (m_params.Polarity)
            {
                case CyEPolarity.Inverting: m_rbPolarity_Inve.Checked = true;
                                      break;
                default: m_rbPolarity_NonInve.Checked = true; //Non-Inverting is default
                                      break;
            }
            
            //Set the Sync Radio Button
            switch (m_params.Sync)
            {
                case CyESync.Bypass : m_rbSync_Bypass.Checked = true;
                                  break;
                default: m_rbSync_Norm.Checked = true; //Normal is default
                                  break;
            }
            UpdateSchematic();
            UpdateDrawing();

        }

        #region Event Handlers
        //Check if Polarity Radio Button is checked and set the image and waveform accordingly 
        private void m_rbPolarity_CheckedChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (m_rbPolarity_NonInve.Checked)
                {
                    m_params.Polarity = CyEPolarity.Non_Inverting;
                    UpdateSchematic();
                    UpdateDrawing();
                }
                if (m_rbPolarity_Inve.Checked)
                {
                    m_params.Polarity = CyEPolarity.Inverting;
                    UpdateSchematic();
                    UpdateDrawing();
                }
            }
        }

        //Check if Sync Radio Button is checked and set the image accordingly 
        private void m_rbSync_CheckedChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (m_rbSync_Norm.Checked)
                {
                    m_params.Sync = CyESync.Normal;
                    UpdateSchematic();
                }
                if (m_rbSync_Bypass.Checked)
                {
                    m_params.Sync = CyESync.Bypass;
                    UpdateSchematic();
                }
            }
        }
        #endregion

        #region Drawing
        /// <summary>
        /// Update schematic
        /// </summary>
        private void UpdateSchematic()
        {
            if (m_params.Polarity == CyEPolarity.Non_Inverting)
            {
                if (m_params.Sync == CyESync.Normal)
                    pictureBox2.Image = Resources.sync;
                else//Sync is bypass
                    pictureBox2.Image = Resources.comp;
            }
            else//polarity is Inverting
            {
                if (m_params.Sync == CyESync.Normal)
                    pictureBox2.Image = Resources.inv_sync;
                else//Sync is bypass
                    pictureBox2.Image = Resources.inverting;
            }
        }
        /// <summary>
        /// Draw waveform
        /// </summary>
        private void UpdateDrawing()
        {
            CancelEventArgs ce = new CancelEventArgs();
            int iWidth = pbox_waveform.Width;
            Image imageWaveform = new Bitmap(iWidth, pbox_waveform.Height);
            Graphics wfg;
            wfg = Graphics.FromImage(imageWaveform);
            wfg.Clear(Color.White);
            SolidBrush blkbrush = new SolidBrush(Color.Black);
            SolidBrush greenbrush = new SolidBrush(Color.Green);
            SolidBrush bluebrush = new SolidBrush(Color.Blue);
            SolidBrush orangebrush = new SolidBrush(Color.Orange);
            Pen extentspen = new Pen(blkbrush);
            Pen greenpen = new Pen(greenbrush);
            Pen bluepen = new Pen(bluebrush);
            Pen orangepen = new Pen(orangebrush);
            extentspen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;
            // Setup the input wave 
            wfg.DrawLine(extentspen, X_START_POINT, 20, iWidth, 20);
            wfg.DrawLine(greenpen, X_START_POINT, 50, iWidth, 50);
            wfg.DrawLine(extentspen, X_START_POINT, 75, iWidth, 75);
            extentspen.DashStyle = System.Drawing.Drawing2D.DashStyle.Solid;
            wfg.DrawLine(extentspen, X_START_POINT, 10, X_START_POINT, 150);
            int x = X_START_POINT; //initialize start point
            while (x < iWidth)
            {
                wfg.DrawLine(bluepen, x, 70, x + X_OFFSET_1, 20);
                x += X_OFFSET_1;
                wfg.DrawLine(bluepen, x, 20, x + X_OFFSET_1, 70);
                x += X_OFFSET_1;
            }
            extentspen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;
            x = 76;//initialize start point
            while (x < iWidth)
           {
                wfg.DrawLine(extentspen, x, 96, x, 35);
                wfg.DrawLine(extentspen, x+107, 96, x+107, 35);
                x += 181;
            }
            if (m_params.Polarity == CyEPolarity.Non_Inverting)
            {
                wfg.DrawLine(orangepen, X_START_POINT, Y_START_POINT_2, 70, Y_START_POINT_2);
                wfg.DrawLine(orangepen, 70, Y_START_POINT_2, 84, Y_START_POINT_1);
                wfg.DrawLine(orangepen, 84, Y_START_POINT_1, 173, Y_START_POINT_1);
                wfg.DrawLine(orangepen, 173, Y_START_POINT_1, 191, Y_START_POINT_2);
                x = 191;//initialize start point
                while (x < iWidth)
                {
                    wfg.DrawLine(orangepen, x, Y_START_POINT_2, x + 60, Y_START_POINT_2);
                    x += 60;
                    wfg.DrawLine(orangepen, x, Y_START_POINT_2, x + 15, Y_START_POINT_1);
                    x += 15;
                    wfg.DrawLine(orangepen, x, Y_START_POINT_1, x + 88, Y_START_POINT_1);
                    x += 88;
                    wfg.DrawLine(orangepen, x, Y_START_POINT_1, x + 18, Y_START_POINT_2);
                    x += 18;
                }
            }
            else //Polarity is Inverting
            {
                wfg.DrawLine(orangepen, X_START_POINT, Y_START_POINT_1, 67, Y_START_POINT_1);
                wfg.DrawLine(orangepen, 67, Y_START_POINT_1, 83, Y_START_POINT_2);
                wfg.DrawLine(orangepen, 83, Y_START_POINT_2, 176, Y_START_POINT_2);
                wfg.DrawLine(orangepen, 176, Y_START_POINT_2, 192, Y_START_POINT_1);
                x = 192;//initialize start point
                while (x < iWidth)
                {
                    wfg.DrawLine(orangepen, x, Y_START_POINT_1, x + 57, Y_START_POINT_1);
                    x += 57;
                    wfg.DrawLine(orangepen, x, Y_START_POINT_1, x + 15, Y_START_POINT_2);
                    x += 15;
                    wfg.DrawLine(orangepen, x, Y_START_POINT_2, x + 94, Y_START_POINT_2);
                    x += 94;
                    wfg.DrawLine(orangepen, x, Y_START_POINT_2, x + 13, Y_START_POINT_1);
                    x += 13;
                }
            }

            //Put labels
            Font perfont = new Font("Arial", 10, FontStyle.Regular, GraphicsUnit.Pixel);
            wfg.DrawString("Vdda", perfont, blkbrush, new PointF(X_FONT_START_POINT_1, 10));
            wfg.DrawString("0V", perfont, blkbrush, new PointF(X_FONT_START_POINT_2, 70));
            wfg.DrawString("Vddd", perfont, blkbrush, new PointF(X_FONT_START_POINT_1, 95));
            wfg.DrawString("Vssd", perfont, blkbrush, new PointF(X_FONT_START_POINT_1, 135));
            wfg.DrawString("V+", perfont, bluebrush, new PointF(X_FONT_START_POINT_2, 60));
            wfg.DrawString("V-", perfont, greenbrush, new PointF(X_FONT_START_POINT_2, 40));
            wfg.DrawString("out", perfont, greenbrush, new PointF(X_FONT_START_POINT_2, 115));
            pbox_waveform.Image = imageWaveform;

            //Dispose objects
            blkbrush.Dispose();
            greenbrush.Dispose();
            bluebrush.Dispose();
            orangebrush.Dispose();
            extentspen.Dispose();
            greenpen.Dispose();
            bluepen.Dispose();
            orangepen.Dispose();
            perfont.Dispose();
        }
        #endregion

    }
}

