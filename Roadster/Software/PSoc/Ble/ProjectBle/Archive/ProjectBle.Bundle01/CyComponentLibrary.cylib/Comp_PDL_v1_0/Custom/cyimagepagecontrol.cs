/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Windows.Forms;
using CyDesigner.Toolkit;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;

namespace Comp_PDL_v1_0
{
    public class CyImagePageControl : CyImageDefaultPageControl, IDisposable
    {
        private CyImage m_image;

        public CyImagePageControl(CyImage image, PictureBoxSizeMode sizeMode, bool onTop, SizeType sizeType, int height)
            : base(image.Image, sizeMode, onTop, sizeType, height)
        {
            m_image = image;
        }

        public override void Refresh(CyQueryArgs args)
        {
            ICyInstQuery_v1 instQuery = args.InstQuery;
            CyParameters parameters = new CyParameters(args.InstQuery);
            m_image.Hysteresis = parameters.Hysteresis;
            m_image.Interrupt = parameters.Interrupt;
            m_image.Vdda = parameters.Vdda;
            m_image.DeepSleepEnable = parameters.DeepSleep;
            m_image.Update();
            Image = m_image.Image;
            base.Refresh(args);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                // dispose of managed disposable members
                m_image.Dispose();
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
    }
}