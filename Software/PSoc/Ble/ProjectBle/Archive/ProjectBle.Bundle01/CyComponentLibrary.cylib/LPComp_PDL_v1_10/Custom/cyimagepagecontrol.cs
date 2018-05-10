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

namespace LPComp_PDL_v1_10
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
            m_image.Hysteresis = CyParameters.GetValue<CyEHysteresisType>(instQuery, CyParamNames.HYSTERESIS);
            m_image.OutputMode = CyParameters.GetValue<CyEOutputModeType>(instQuery, CyParamNames.OUTPUT_CONFIGURATION);
            m_image.Interrupt = CyParameters.GetValue<CyEInterruptType>(instQuery, CyParamNames.PULSE_INTERRUPT_CONFIGURATION);
            m_image.Power = CyParameters.GetValue<CyESpeedType>(instQuery, CyParamNames.POWER_SPEED);
			m_image.LocalVrefInput = CyParameters.GetValue<bool>(instQuery, CyParamNames.LOCAL_VREF_INPUT);
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
