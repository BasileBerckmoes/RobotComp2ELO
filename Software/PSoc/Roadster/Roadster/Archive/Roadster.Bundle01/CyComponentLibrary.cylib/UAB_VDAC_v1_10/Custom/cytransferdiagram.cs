/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

// The namespace is required to have the same name as the component for a customizer.
namespace UAB_VDAC_v1_10
{
    public class CyTransferDiagram
    {

        private delegate string CalcTransferGraphLabel();

        private CyParameters m_parameters;
        private Dictionary<string, CalcTransferGraphLabel> m_dict;
        private bool m_dacInputSigned;

        public float m_leftX, m_leftIndentX, m_rightX, m_rightIndentX,
                     m_bottomY, m_bottomIndentY, m_topY, m_topIndentY,
                     m_centerX, m_centerY, m_transBottomY, m_transTopY;

        public PointF[] m_leftGuidePoly;
        public PointF[] m_rightGuidePoly;
        public PointF[] m_hAxisPoly;
        public PointF[] m_vAxisPoly;
        public PointF[] m_defaultOutPoly;
        public PointF[] m_transferGraphPoly;

        public CyTransferDiagram(CyParameters parameters)
        {
            this.m_parameters = parameters;
            this.m_leftGuidePoly = new PointF[] { new PointF(0, 0), new PointF(0, 0) };
            this.m_rightGuidePoly = new PointF[] { new PointF(0, 0), new PointF(0, 0) };
            this.m_hAxisPoly = new PointF[] { new PointF(0, 0), new PointF(0, 0) };
            this.m_vAxisPoly = new PointF[] { new PointF(0, 0), new PointF(0, 0) };
            this.m_defaultOutPoly = new PointF[] { new PointF(0, 0), new PointF(0, 0) };
            this.m_transferGraphPoly = new PointF[] { new PointF(0, 0), new PointF(0, 0) };
            this.CreateDacTextDict();
        }

        public bool IsDacInputSigned { get { return this.m_dacInputSigned; } }

        public string RangeLsbLabel { get { return this.m_dict["range lsb"](); } }
        public string RangeDLowLabel { get { return this.m_dict["range D low"](); } }
        public string RangeDMidLabel { get { return this.m_dict["range D middle"](); } }
        public string RangeDHighLabel { get { return this.m_dict["range D high"](); } }
        public string HeaderLeftLabel { get { return this.m_dict["header left"](); } }
        public string HeaderMidLabel { get { return this.m_dict["header middle"](); } }
        public string FooterLowValueLabel { get { return this.m_dict["footer low value"](); } }
        public string FooterMidValueLabel { get { return this.m_dict["footer middle value"](); } }
        public string FooterHighValueLabel { get { return this.m_dict["footer high value"](); } }
        public string FooterLowCodeLabel { get { return this.m_dict["footer low code"](); } }
        public string FooterMidCodeLabel { get { return this.m_dict["footer middle code"](); } }
        public string FooterHighCodeLabel { get { return this.m_dict["footer high code"](); } }
        public string VoutMinLabel { get { return this.m_dict["vout min"](); } }
        public string VoutMaxLabel { get { return this.m_dict["vout max"](); } }
        public string VoutCenterLabel { get { return this.m_dict["vout center"](); } }
        public string VoutDeltaLabel { get { return this.m_dict["vout delta"](); } }

        public string DefaultOutLabel
        {
            get
            {
                return String.Format("{0}\n{1}", m_parameters.DefaultOutVolt.ToString("F3") + " V", (Int16)m_parameters.DefaultOutCode);
            }
        }
        public void Resize(RectangleF rect, Font diagramFont)
        {
            float sideMargin = 3 * diagramFont.Height;
            float topMargin = diagramFont.Height / 2;
            float bottomGapMargin = (rect.Height - topMargin) / 7;

            m_centerX = (this.IsDacInputSigned) ? (rect.Left + rect.Right) / 2 : rect.Left + sideMargin;
            m_bottomY = rect.Bottom;
            m_topY = rect.Top;
            m_topIndentY = rect.Top + topMargin;
            
            m_leftIndentX = rect.Left + sideMargin;
            m_leftX = rect.Left;
            m_rightIndentX = rect.Right - sideMargin;
            m_rightX = rect.Right;
            m_transBottomY = (this.IsDacInputSigned) ? rect.Bottom - bottomGapMargin : rect.Bottom;
            m_transTopY = rect.Top + topMargin + bottomGapMargin;

            m_leftGuidePoly = new PointF[] { new PointF(m_leftIndentX, m_bottomY), 
                                            new PointF(m_leftIndentX, m_transBottomY), 
                                            new PointF(m_centerX, m_transBottomY) };

            m_rightGuidePoly = new PointF[] { new PointF(m_centerX, m_transTopY), 
                                             new PointF(m_rightIndentX, m_transTopY), 
                                             new PointF(m_rightIndentX, m_bottomY) };

            m_hAxisPoly = new PointF[] { new PointF(m_leftX, m_bottomY), 
                                         new PointF(m_rightX, m_bottomY) };

            m_vAxisPoly = new PointF[] { new PointF(m_centerX, m_bottomY), 
                                         new PointF(m_centerX, m_topIndentY)};

            m_transferGraphPoly = CreateTransferGraph();

            int tmpIndx;
            if (this.IsDacInputSigned)
            {
                tmpIndx = (((Int16)m_parameters.DefaultOutCode)+4096) * m_transferGraphPoly.Length / 8192;
            }
            else
            {
                tmpIndx = ((Int16)m_parameters.DefaultOutCode) * m_transferGraphPoly.Length / 4096;
            }

            /* Saturate to xfer graph bounds.  Should be unnecessary. */
            tmpIndx = Math.Max(0, Math.Min(m_transferGraphPoly.Length - 1, tmpIndx));

            m_defaultOutPoly = new PointF[] { new PointF(m_centerX, m_transferGraphPoly[tmpIndx].Y),
                                              new PointF(m_transferGraphPoly[tmpIndx].X, m_transferGraphPoly[tmpIndx].Y),
                                              new PointF(m_transferGraphPoly[tmpIndx].X, m_bottomY)};
        }

        public PointF SnapToTransferGraph(PointF point)
        {
            // Clip dot to transfer graph domain.
            float tmpX = Math.Max(m_transferGraphPoly[0].X,
                         Math.Min(m_transferGraphPoly[m_transferGraphPoly.Length - 1].X, point.X)) - m_transferGraphPoly[0].X;
            // Snap dot to transfer graph line.
            //int tmpIndex = Math.Max(0, Math.Min(m_transferGraphPoly.Length - 1, (int)(tmpX - m_transferGraphPoly[0].X)));
            point = m_transferGraphPoly[(int) tmpX /*tmpIndex*/];
            return point;
        }

        public PointF graphPointToCVPair(PointF graphedPoint)
        {
            PointF scaledPoint = new PointF (0f, 0f);
            double y_low_v = m_parameters.MinimumOutputVoltage;
            double y_high_v = m_parameters.MaximumOutputVoltage;
            double y_grphP_dist = graphedPoint.Y - this.m_transferGraphPoly[0].Y;
            double y_total_dist = this.m_transferGraphPoly[m_transferGraphPoly.Length - 1].Y - this.m_transferGraphPoly[0].Y;

            double y_v = y_low_v + (y_high_v - y_low_v) * (y_grphP_dist) / (y_total_dist);

            scaledPoint.Y = (float)Math.Max(y_low_v, Math.Min(y_high_v, y_v));
            scaledPoint.X = Voltage2Code(scaledPoint.Y);
            return scaledPoint;
        }
        
        void CreateDacTextDict()
        {
            this.m_dict = new Dictionary<string, CalcTransferGraphLabel>();

            if (m_parameters.m_dacMode.Display == m_parameters.m_dacMode.ValueToDisplay(DacFormatType.MODE_2CMP))
            {
                this.m_dacInputSigned = true;
                this.m_dict.Add("range lsb", this.CalcVrefRangeLsb);
                this.m_dict.Add("range D low", this.TwosCompRangeDLow);
                this.m_dict.Add("range D middle", this.TwosCompRangeDMiddle);
                this.m_dict.Add("range D high", this.TwosCompRangeDHigh);
                this.m_dict.Add("header left", this.TwosCompHeaderLeft);
                this.m_dict.Add("header middle", this.TwosCompHeaderMiddle);
                this.m_dict.Add("footer low value", this.TwosCompFooterLowValue);
                this.m_dict.Add("footer middle value", this.TwosCompFooterMiddleValue);
                this.m_dict.Add("footer high value", this.TwosCompFooterHighValue);
                this.m_dict.Add("footer low code", this.TwosCompFooterLowCode);
                this.m_dict.Add("footer middle code", this.TwosCompFooterMiddleCode);
                this.m_dict.Add("footer high code", this.TwosCompFooterHighCode);
                this.m_dict.Add("vout min", this.TwosCompVoutMin);
                this.m_dict.Add("vout max", this.TwosCompVoutMax);
                this.m_dict.Add("vout center", this.TwosCompVoutCenter);
            }
            else //Not 2's comp, must be sign mag.
            {
                this.m_dacInputSigned = true;
                this.m_dict.Add("range lsb", this.CalcVrefRangeLsb);
                this.m_dict.Add("range D low", this.SignMagRangeDLow);
                this.m_dict.Add("range D middle", this.SignMagRangeDMiddle);
                this.m_dict.Add("range D high", this.SignMagRangeDHigh);
                this.m_dict.Add("header left", this.SignMagHeaderLeft);
                this.m_dict.Add("header middle", this.SignMagHeaderMiddle);
                this.m_dict.Add("footer low value", this.SignMagFooterLowValue);
                this.m_dict.Add("footer middle value", this.SignMagFooterMiddleValue);
                this.m_dict.Add("footer high value", this.SignMagFooterHighValue);
                this.m_dict.Add("footer low code", this.SignMagFooterLowCode);
                this.m_dict.Add("footer middle code", this.SignMagFooterMiddleCode);
                this.m_dict.Add("footer high code", this.SignMagFooterHighCode);
                this.m_dict.Add("vout min", this.SignMagVoutMin);
                this.m_dict.Add("vout max", this.SignMagVoutMax);
                this.m_dict.Add("vout center", this.SignMagVoutCenter);
            }
        }

        private string CalcVrefRangeLsb()
        {
            // "LSB = VRef*Gain*(1/4096)";
            double value = this.m_parameters.VrefVolts * this.m_parameters.DacGain / 4.096;
            string text = "LSB = " + value.ToString("F2") + " mV";
            return text;
        }
        
        #region Dictionaries and Worse
        /* m_params.UnsignedMaximumVoltage and SignedMaximumVoltage are useful here. */

        private string SignMagRangeDLow() { return "D = -4095: Vout = Vagnd-Vref*Gain*(4095/4096)"; }
        private string SignMagRangeDMiddle() { return "D = 0: Vout = Vagnd"; }
        private string SignMagRangeDHigh() { return "D = +4095: Vout = Vagnd+Vref*Gain*(4095/4096)"; }
        private string SignMagHeaderLeft() { return ""; }
        private string SignMagHeaderMiddle() { return "Vout"; }
        private string SignMagFooterLowValue() { return "-4095"; }
        private string SignMagFooterMiddleValue() { return "0"; }
        private string SignMagFooterHighValue() { return "4095"; }
        private string SignMagFooterLowCode() { return "0x1FFF"; }
        private string SignMagFooterMiddleCode() { return ""; }
        private string SignMagFooterHighCode() { return "0x0FFF"; }

        private string SignMagVoutMin()
        {
            // "Vagnd-Vref"
            double value = m_parameters.TwosCompMinimumOutVoltage;
            string text = value.ToString("F3") + " V";
            return text;
        }

        private string SignMagVoutMax()
        {
            // "Vagnd+(4096/4096)*Vref"
            double value = m_parameters.TwosCompMaximumOutVoltage;
            string text = value.ToString("F3") + " V";
            return text;
        }

        private string SignMagVoutCenter()
        {
            // "Vagnd"
            double value = Math.Min(m_parameters.TwosCompMaximumOutVoltage, Math.Max(m_parameters.TwosCompMinimumOutVoltage, this.m_parameters.VagndVolts));
            string text = value.ToString("F3") + " V";
            return text;
        }
        
        private string TwosCompRangeDLow() { return "D = -4096: Vout = Vagnd - Vref*Gain"; }
        private string TwosCompRangeDMiddle() { return "D = 0: Vout = Vagnd"; }
        private string TwosCompRangeDHigh() { return "D = +4095: Vout = Vagnd + Vref*Gain*(4095/4096)"; }
        private string TwosCompHeaderLeft() { return ""; }
        private string TwosCompHeaderMiddle() { return "Vout"; }
        private string TwosCompFooterLowValue() { return "-4096"; }
        private string TwosCompFooterMiddleValue() { return "0"; }
        private string TwosCompFooterHighValue() { return "4095"; }
        private string TwosCompFooterLowCode() { return "0x1000"; }
        private string TwosCompFooterMiddleCode() { return ""; }
        private string TwosCompFooterHighCode() { return "0x0FFF"; }

        private string TwosCompVoutMin()
        {
            // "Vagnd-Vref"
            double value = m_parameters.TwosCompMinimumOutVoltage;
            string text = value.ToString("F3") + " V";
            return text;
        }

        private string TwosCompVoutMax()
        {
            // "Vagnd+(4095/4096)*Vref"
            double value = m_parameters.TwosCompMaximumOutVoltage;
            string text = value.ToString("F3") + " V";
            return text;
        }

        private string TwosCompVoutCenter()
        {
            // "Vagnd"
            double value = Math.Min(m_parameters.TwosCompMaximumOutVoltage, Math.Max(m_parameters.TwosCompMinimumOutVoltage, this.m_parameters.VagndVolts));
            string text = value.ToString("F3") + " V";
            return text;
        }
        
#endregion Dictionaries and Worse

        private PointF[] CreateTransferGraph()
        {
            Int16 numPoints = Convert.ToInt16(m_rightIndentX - m_leftIndentX);
            Int16 height = Convert.ToInt16(m_transTopY - m_transBottomY);

            PointF[] transferGraph = new PointF[numPoints];

            float botClip_v, topClip_v,
                  agnd_v, ref_v, xferGain,
                  xMax_code, xMin_code;

            int xTmp_code;
            float yTmp_v;

            agnd_v   = (float)(m_parameters.VagndVolts);
            ref_v    = (float)(m_parameters.VrefVolts);
            xferGain = (float)(m_parameters.DacGain);

            /*Set up mode-specific variables*/
            if (m_parameters.m_dacMode.Display == m_parameters.m_dacMode.ValueToDisplay(DacFormatType.MODE_SGNMAG))
            {
                xMax_code = 4095;
                xMin_code = -4095;
                botClip_v = (float)m_parameters.SignMagMinimumOutVoltage;
                topClip_v = (float)m_parameters.SignMagMaximumOutVoltage;
            } /* else, must be 2's comp mode*/
            else
            {
                xMax_code = 4095;
                xMin_code = -4096;
                botClip_v = (float)m_parameters.TwosCompMinimumOutVoltage;
                topClip_v = (float)m_parameters.TwosCompMaximumOutVoltage;
            }

            /* For every plottable point*/
            for (int xPlot = 0; xPlot < numPoints; xPlot++)
            {
                xTmp_code = (int)(xPlot*(xMax_code - xMin_code)/numPoints + xMin_code); /* Convert pixel X to encoded X*/
                yTmp_v = Code2Voltage(xTmp_code); /* Convert code to clipped voltage*/
                yTmp_v = height * (yTmp_v - botClip_v) / (topClip_v - botClip_v); /* Convert voltage to pixel*/
                transferGraph[xPlot] = new PointF(xPlot + m_leftIndentX, yTmp_v + m_transBottomY); /* Add pixel to poly, with offset */
            }

            return transferGraph;
        }

        public float Code2Voltage(int code)
        {
            float yTmp_v; ;
            
            float xferGain   = (float) m_parameters.DacGain;
            float range_code = (float) 4096;
            float agnd_v     = (float) m_parameters.VagndVolts;
            float ref_v      = (float) m_parameters.VrefVolts;
            float topClip_v  = (float) m_parameters.MaximumOutputVoltage;
            float botClip_v  = (float) m_parameters.MinimumOutputVoltage;
            
            yTmp_v = agnd_v + ref_v * xferGain * code / range_code;
            yTmp_v = Math.Min(topClip_v, Math.Max(botClip_v, yTmp_v)); /*Saturate output voltage*/
            return (float)yTmp_v;
        }

        public int Voltage2Code(float voltage)
        {
            int tmp_code;
            float ref_v     = (float) m_parameters.VrefVolts;
            float agnd_v    = (float) m_parameters.VagndVolts;
            float xferGain  = (float) m_parameters.DacGain;
            
            tmp_code = (int)(((voltage - agnd_v) * 4096) / (ref_v * xferGain));

            return tmp_code;
        }
    }
}
