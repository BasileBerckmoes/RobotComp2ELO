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
using VDAC12_PDL_v1_0.Utils;
using VDAC12_PDL_v1_0.TransferGraph;

namespace VDAC12_PDL_v1_0
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
            CyEnums.CyESignMode signMode = CyParameters.GetCodeMode(instQuery);
            CyEnums.CyEOutputType outputType = CyParameters.GetOutputBuffer(instQuery);
            double initialCode = CyParameters.GetInitialCode(instQuery);
            double vrefVoltage = CyParameters.GetVrefVoltage(instQuery);
            bool signed = CyParameters.GetCodeMode(instQuery) == CyEnums.CyESignMode.FormatSigned;
            bool deepSleep = CyParameters.GetDeepSleep(instQuery);
            double vdda = CyParameters.GetVddaVoltage(instQuery);
            double initialVoltage;

            double upperOutputMax = vdda;
            double upperInputMax = vdda;
            if(CyParameters.GetVrefSource(instQuery) != CyEnums.CyEVrefSource.VrefVdda)
            {
                upperInputMax = deepSleep ? (vdda - 1.5) : vdda - 0.200;
            }
            if ((CyParameters.GetOutputBuffer(instQuery) == CyEnums.CyEOutputType.BufferedPin) || (CyParameters.GetOutputBuffer(instQuery) == CyEnums.CyEOutputType.BufferedInternal))
            {
                upperOutputMax = deepSleep ? (vdda - 1.5) : vdda - 0.200;
            }            

            if(signed)
            {
                initialVoltage = (initialCode + 2048) / 4096 * vrefVoltage;
            }
            else
            {
                initialVoltage = initialCode / 4096 * vrefVoltage;
            }

            TypeSpecificControl.Size = Image.Size;
            UpdateDrawing(signMode, initialVoltage, vrefVoltage, outputType, upperInputMax, upperOutputMax);
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
        private void UpdateDrawing(CyEnums.CyESignMode signMode, double initialVoltage, double vrefVoltage, CyEnums.CyEOutputType outputType, double maxInput, double maxOutput)        
        {
            Bitmap updatedBitmap = new Bitmap(Image.Width, Image.Height);

            using (Graphics graph = Graphics.FromImage(updatedBitmap))
            using (CyTransferGraph transfer = new CyTransferGraph(graph, updatedBitmap.Size ))
            {
                if(vrefVoltage > maxInput)
                {
                    transfer.DrawErrorMessage();
                }
                else
                {
                    if ((outputType == CyEnums.CyEOutputType.BufferedPin) || (outputType == CyEnums.CyEOutputType.BufferedInternal))
                    {
                        transfer.DrawWarningBands(vrefVoltage, maxOutput);
                        transfer.DrawBufferWarning();
                    }
                    transfer.Draw();
                    transfer.DrawLabels(signMode, vrefVoltage);
                    transfer.DrawInitialVoltage(signMode, vrefVoltage, initialVoltage);
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
