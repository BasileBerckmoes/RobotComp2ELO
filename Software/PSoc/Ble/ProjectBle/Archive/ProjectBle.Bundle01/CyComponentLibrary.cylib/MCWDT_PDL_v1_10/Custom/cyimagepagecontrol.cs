/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
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

namespace MCWDT_PDL_v1_10
{
    public class CyImagePageControl : CyTabParamEditorDefaultPageControl<Panel>, IDisposable
    {
        private CyImage m_image;
        PictureBox m_picBox;
        
        public CyImagePageControl(CyImage image)
            : base(new Panel(), false, SizeType.AutoSize, 0)
        {
            m_image = image;
            
            m_picBox = new PictureBox();
            m_picBox.BorderStyle = BorderStyle.None;
            m_picBox.SizeMode = PictureBoxSizeMode.AutoSize;
            m_picBox.Image = image.Image;
            
            TypeSpecificControl.Dock = DockStyle.Fill;
            TypeSpecificControl.AutoScroll = true;
            TypeSpecificControl.BorderStyle = BorderStyle.FixedSingle;
            TypeSpecificControl.Controls.Add(m_picBox);
        }

        public override void Refresh(CyQueryArgs args)
        {
            ICyInstQuery_v1 instQuery = args.InstQuery;
            m_image.CascadeC0C1 = CyParameters.GetValue<bool>(instQuery, CyParamNames.CASCADE_C0C1);
            m_image.CascadeC1C2 = CyParameters.GetValue<bool>(instQuery, CyParamNames.CASCADE_C1C2);
            m_image.ModeC0 = CyParameters.GetValue<CyEModeType>(instQuery, CyParamNames.C0_MODE);
            m_image.ModeC1 = CyParameters.GetValue<CyEModeType>(instQuery, CyParamNames.C1_MODE);
            m_image.ModeC2 = CyParameters.GetValue<CyEC2ModeType>(instQuery, CyParamNames.C2_MODE);
            m_image.MatchC0 = CyParameters.GetValue<UInt16>(instQuery, CyParamNames.C0_MATCH);
            m_image.MatchC1 = CyParameters.GetValue<UInt16>(instQuery, CyParamNames.C1_MATCH);
            m_image.C0ClearOnMatch = 
                CyParameters.GetValue<CyEClearOnMatchType>(instQuery, CyParamNames.C0_CLEAR_ON_MATCH);
            m_image.C1ClearOnMatch = 
                CyParameters.GetValue<CyEClearOnMatchType>(instQuery, CyParamNames.C1_CLEAR_ON_MATCH);
            m_image.PeriodC2 = CyParameters.GetValue<CyEPeriodType>(instQuery, CyParamNames.C2_PERIOD);

            m_image.Update();
            m_picBox.Image = m_image.Image;
            
            Size preferredSize = m_picBox.GetPreferredSize(m_picBox.Size);
            TypeSpecificControl.MinimumSize = new Size(
                0,
                preferredSize.Height + SystemInformation.HorizontalScrollBarHeight + 
                TypeSpecificControl.Margin.Top + TypeSpecificControl.Margin.Bottom);
           
            base.Refresh(args);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                // dispose of managed disposable members
                m_image.Dispose();
                m_picBox.Dispose();
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
