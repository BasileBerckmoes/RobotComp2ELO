/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Drawing;
using System.Windows.Forms;
using CyDesigner.Toolkit;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using TCPWM_PWM_PDL_v1_0.Utils;
using TCPWM_PWM_PDL_v1_0.Waveform;

namespace TCPWM_PWM_PDL_v1_0
{
    public class CyImagePageControl : CyImageDefaultPageControl, IDisposable
    {
        public CyImagePageControl(Image image, PictureBoxSizeMode sizeMode, bool onTop, SizeType sizeType, int height)
            : base(image, sizeMode, onTop, sizeType, height)
        {
            TypeSpecificControl.BackColor = Color.White;
        }

        public override void Refresh(CyQueryArgs args)
        {
            ICyInstQuery_v1 instQuery = args.InstQuery;
            uint period0 = CyParameters.GetPeriod0(instQuery);
            uint period1 = CyParameters.GetPeriod1(instQuery);
            uint compare0 = CyParameters.GetCompare0(instQuery);
            uint compare1 = CyParameters.GetCompare1(instQuery);
            byte deadTime = CyParameters.GetDeadTimeClocks(instQuery);
            bool periodSwap = CyParameters.GetPeriodSwap(instQuery);
            bool compareSwap = CyParameters.GetCompareSwap(instQuery);
            CyEnums.CyMode mode = CyParameters.GetMode(instQuery);
            CyEnums.CyAlignment alignment = CyParameters.GetAlignment(instQuery);
            CyEnums.CyResolution resolution = CyParameters.GetResolution(instQuery);

            TypeSpecificControl.Size = Image.Size;
            UpdateDrawing(period0, period1, periodSwap, compare0, compare1, compareSwap, deadTime, mode, alignment, resolution);
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

        #region Drawing
        private void UpdateDrawing(
            uint period0,
            uint period1,
            bool periodSwap,
            uint compare0,
            uint compare1,
            bool compareSwap,
            byte deadTime,
            CyEnums.CyMode mode,
            CyEnums.CyAlignment alignment,
            CyEnums.CyResolution resolution)
        {
            // Add deadtime in DeadTime mode only
            if (mode != CyEnums.CyMode.MODE_DEADTIME)
            {
                deadTime = 0;
            }

            Bitmap updatedBitmap = new Bitmap(Image.Width, Image.Height);

            using (Graphics g = Graphics.FromImage(updatedBitmap))
            using (CyEgdeLine egdeLines = new CyEgdeLine(g, updatedBitmap.Size))
            using (CyPeriodArrows periodArrows = new CyPeriodArrows(g, updatedBitmap.Size, mode, alignment, period0, period1, periodSwap))
            using (CyPwmSignal pwmSignal = new CyPwmSignal(g, updatedBitmap.Size, period0, period1, periodSwap, compare0, compare1, compareSwap, deadTime, alignment))
            using (CyPseudoRandomSignal pseudoRandomSignal = new CyPseudoRandomSignal(g, updatedBitmap.Size, period0, period1, periodSwap, compare0, compare1, compareSwap, resolution))
            {
                g.Clear(Color.White);
                egdeLines.Draw();
                egdeLines.DrawLabels();
                periodArrows.Draw();
                if (mode == CyEnums.CyMode.MODE_PSEUDORANDOM)
                {
                    pseudoRandomSignal.Draw();
                }
                else
                {
                    pwmSignal.Draw();
                }
            }
            Bitmap old = Image as Bitmap;
            Image = updatedBitmap;
            if (old != null)
            {
                old.Dispose();
            }
        }
        #endregion
    }
}
