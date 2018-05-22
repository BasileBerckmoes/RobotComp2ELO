/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Collections.Generic;
using System.Drawing;

namespace ADC_SAR_SEQ_v2_10
{
    public class CyShapeBuilder
    {
        #region Shape names constants
        const string BODY_SHAPE_NAME = "body";
        const string MUX_SHAPE_NAME = "mux";
        const string SAR_SHAPE_NAME = "sar";
        const string ANNOTATION_NAME = "text";
        const string WIRES_NAME = "wire";
        const string VREF_NAME = "vref";
        const string VREF_TEXT_NAME = "vreftext";

        const string VIN_PLUS_0_TERM_NAME = "AIN_10";
        const string VIN_MINUS_0_TERM_NAME = "AIN_11";
        #endregion

        #region Shape constants
        const uint BODY_BASE_HEIGHT = 8;
        const uint MIN_BODY_HEIGHT_SINGLE_ENDED_MODE = 18;
        const float BODY_SHAPE_LINE_WIDTH = 1f;
        readonly Color BODY_SHAPE_COLOR = Color.Gainsboro;
        const uint UNITS_PER_CHANNEL = 3;
        const uint MUX_X_OFFSET_IN_BODY = 3;
        const uint MUX_Y_OFFSET_IN_BODY = 7;
        const uint MUX_WIDTH = 3;
        const uint MUX_VEDGES_DIFFERENCE = 2;
        const float MUX_SHAPE_LINE_WIDTH = 0.5f;
        const float MUX_TEXT_X_OFFSET = 0.1f;
        const float MUX_SINGLE_ENDED_TEXT_Y_OFFSET = 1f;
        const float MUX_DIFFERENTIAL_TEXT_Y_OFFSET = 1.5f;
        const uint DIFFERENTIAL_INPUT_SIZE = 3;
        const uint SINGLE_ENDED_INPUT_SIZE = 2;
        const uint DISTANCE_BETWEEN_CHANNELS = 2;
        const uint DISTANCE_BETWEEN_MUX_AND_SAR = 3;
        const uint SAR_INITIAL_Y_OFFSET = 7;
        const uint SAR_X_OFFSET = MUX_X_OFFSET_IN_BODY + MUX_WIDTH + DISTANCE_BETWEEN_MUX_AND_SAR;
        const uint SAR_HEIGHT = 4;
        const uint SINGLE_ENDED_LOW_OFFSET = 2;
        const uint PIN_START_Y_OFFSET = MUX_Y_OFFSET_IN_BODY + MUX_VEDGES_DIFFERENCE;
        const float WIRES_WIDTH = 0.5f;
        readonly Color WIRES_COLOR = Color.Navy;
        const uint VSS_VLINE_LENGTH = 2;
        const float VSS_LINE_WIDTH = 0.5f;
        readonly Color VSS_LINE_COLOR = Color.Navy;
        readonly Color VSS_FILL_COLOR = Color.White;
        const string VSS_TEXT = "Vss";
        const float VREF_LINE_WIDTH = 1.5f;
        const string VREF_TEXT = "Vref";

        const uint VIN_MINUS_0_TERM_Y_OFFSET = 9;
        #endregion

        private readonly Font ANNOTATIONS_FONT = new Font(FontFamily.GenericSansSerif, 10f, FontStyle.Regular,
            GraphicsUnit.Point, 1, false);
        private readonly Color ANNOTATION_COLOR = Color.Black;


        private CyParameters m_params;
        private ICySymbolShapeEdit_v1 m_shapeEdit;
        private ICyTerminalEdit_v1 m_termEdit;

        private RectangleF m_bodyBounds;

        #region Constructor(s)
        public CyShapeBuilder(CyParameters parameters, ICySymbolShapeEdit_v1 shapeEdit, ICyTerminalEdit_v1 termEdit)
        {
            m_params = parameters;
            m_shapeEdit = shapeEdit;
            m_termEdit = termEdit;

            m_bodyBounds = m_shapeEdit.GetShapeBounds(BODY_SHAPE_NAME);
            m_bodyBounds.Height = BodyHeight * m_shapeEdit.UserBaseUnit;
        }
        #endregion

        #region Auxiliary properties
        uint InputSize
        {
            get { return m_params.IsDifferentialMode ? DIFFERENTIAL_INPUT_SIZE : SINGLE_ENDED_INPUT_SIZE; }
        }

        uint MuxHeight
        {
            get {
                return (m_params.NumChannels > 1) ? m_params.NumChannels * InputSize + 2 : 0;
            }
        }

        uint BodyHeight
        {
            get
            {
                uint height = BODY_BASE_HEIGHT;
                if (MuxHeight > 0)
                {
                    height += MuxHeight + 1;
                }
                else
                {
                    height += SAR_HEIGHT + 2 +
                        (m_params.IsDifferentialMode ? 0u : 1u);
                }
                if ((m_params.IsDifferentialMode == false) && (MuxHeight > 1) &&
                    (height < MIN_BODY_HEIGHT_SINGLE_ENDED_MODE))
                {
                    height = MIN_BODY_HEIGHT_SINGLE_ENDED_MODE;
                }

                return height;
            }
        }

        PointF SarLocation
        {
            get
            {
                if (m_params.NumChannels > 1)
                {
                    float localYOffset = 0;
                    if ((m_params.NumChannels == 2) && (m_params.IsDifferentialMode == false))
                    {
                        localYOffset += m_shapeEdit.UserBaseUnit;
                    }
                    return new PointF(m_bodyBounds.X + SAR_X_OFFSET * m_shapeEdit.UserBaseUnit, m_bodyBounds.Y +
                        (MUX_Y_OFFSET_IN_BODY + (MuxHeight - SAR_HEIGHT) / 2.0f) * m_shapeEdit.UserBaseUnit +
                        localYOffset);
                }
                else
                {
                    return new PointF(m_bodyBounds.X + SAR_X_OFFSET * m_shapeEdit.UserBaseUnit,
                        m_bodyBounds.Y + SAR_INITIAL_Y_OFFSET * m_shapeEdit.UserBaseUnit);
                }
            }
        }
        #endregion

        public CyCustErr DrawSymbol()
        {
            CyCustErr err = DrawBody();
            if (err.IsNotOK)
            {
                return err;
            }

            err = DrawWires();
            if (err.IsNotOK)
            {
                return err;
            }

            if (m_params.NumChannels > 1)
            {
                err = DrawMux();
                if (err.IsNotOK)
                {
                    return err;
                }
            }

            err = CorrectSarLocation();
            if (err.IsNotOK)
            {
                return err;
            }

            err = CorrectTermialLocation();
            if (err.IsNotOK)
            {
                return err;
            }

            return CyCustErr.OK;
        }

        private CyCustErr DrawBody()
        {
            CyCustErr err = m_shapeEdit.ShapesRemove(BODY_SHAPE_NAME);
            if (err.IsNotOK)
            {
                return err;
            }

            err = m_shapeEdit.CreateRectangle(new string[] { BODY_SHAPE_NAME }, m_bodyBounds.Location,
                m_bodyBounds.Width, m_bodyBounds.Height);
            if (err.IsNotOK)
            {
                return err;
            }

            err = m_shapeEdit.SetFillColor(BODY_SHAPE_NAME, BODY_SHAPE_COLOR);
            if (err.IsNotOK)
            {
                return err;
            }
            err = m_shapeEdit.SetOutlineWidth(BODY_SHAPE_NAME, BODY_SHAPE_LINE_WIDTH);
            if (err.IsNotOK)
            {
                return err;
            }

            err = m_shapeEdit.SetOutlineLineJoin(BODY_SHAPE_NAME, System.Drawing.Drawing2D.LineJoin.Round);
            if (err.IsNotOK)
            {
                return err;
            }

            err = m_shapeEdit.SendToBack(BODY_SHAPE_NAME);
            if (err.IsNotOK)
            {
                return err;
            }

            return CyCustErr.OK;
        }

        private CyCustErr DrawMux()
        {
            m_shapeEdit.ShapesRemove(MUX_SHAPE_NAME);
            m_shapeEdit.ShapesRemove(ANNOTATION_NAME);

            // Draw mux trapezoid
            PointF[] muxPoints = new PointF[6];
            muxPoints[0] = new PointF(m_bodyBounds.X + MUX_X_OFFSET_IN_BODY * m_shapeEdit.UserBaseUnit,
                m_bodyBounds.Y + MUX_Y_OFFSET_IN_BODY * m_shapeEdit.UserBaseUnit);
            muxPoints[1] = new PointF(muxPoints[0].X, muxPoints[0].Y + MuxHeight * m_shapeEdit.UserBaseUnit);
            muxPoints[2] = new PointF(muxPoints[1].X + MUX_WIDTH * m_shapeEdit.UserBaseUnit,
                muxPoints[1].Y - MUX_VEDGES_DIFFERENCE * m_shapeEdit.UserBaseUnit);
            muxPoints[3] = new PointF(muxPoints[0].X + MUX_WIDTH * m_shapeEdit.UserBaseUnit,
                muxPoints[0].Y + MUX_VEDGES_DIFFERENCE * m_shapeEdit.UserBaseUnit);
            muxPoints[4] = muxPoints[0];
            muxPoints[5] = muxPoints[1];

            CyCustErr err = m_shapeEdit.CreatePolyline(new string[] { MUX_SHAPE_NAME }, muxPoints);
            if (err.IsNotOK)
            {
                return err;
            }

            err = m_shapeEdit.SetOutlineWidth(MUX_SHAPE_NAME, MUX_SHAPE_LINE_WIDTH);
            if (err.IsNotOK)
            {
                return err;
            }

            // Draw channels numbers
            PointF p = new PointF(muxPoints[0].X + MUX_TEXT_X_OFFSET * m_shapeEdit.UserBaseUnit, muxPoints[0].Y +
                (m_params.IsDifferentialMode ? MUX_DIFFERENTIAL_TEXT_Y_OFFSET : MUX_SINGLE_ENDED_TEXT_Y_OFFSET)
                * m_shapeEdit.UserBaseUnit);
            for (int i = 0; i < m_params.NumChannels; i++)
            {
                err = CreateAnnotation(i.ToString(), p);
                if (err.IsNotOK)
                {
                    return err;
                }
                p = new PointF(p.X, p.Y + InputSize * m_shapeEdit.UserBaseUnit);
            }

            return CyCustErr.OK;
        }

        private CyCustErr DrawWires()
        {
            CyCustErr err;
            PointF p1, p2;

            m_shapeEdit.ShapesRemove(WIRES_NAME);

            if (m_params.NumChannels > 1)
            {
                p1 = new PointF(m_bodyBounds.X, m_bodyBounds.Y + PIN_START_Y_OFFSET * m_shapeEdit.UserBaseUnit);
                for (int i = 0; i < m_params.NumChannels; i++)
                {
                    // Draw a wire between the input and the mux
                    p2 = new PointF(p1.X + MUX_X_OFFSET_IN_BODY * m_shapeEdit.UserBaseUnit, p1.Y);
                    err = m_shapeEdit.CreateLine(new string[] { WIRES_NAME }, p1, p2);
                    if (err.IsNotOK)
                    {
                        return err;
                    }

                    if (m_params.IsDifferentialMode)
                    {
                        // Draw second wire for differential input between the input and the mux
                        p1 = new PointF(p1.X, p1.Y + m_shapeEdit.UserBaseUnit);
                        p2 = new PointF(p2.X, p2.Y + m_shapeEdit.UserBaseUnit);
                        err = m_shapeEdit.CreateLine(new string[] { WIRES_NAME }, p1, p2);
                        if (err.IsNotOK)
                        {
                            return err;
                        }
                    }
                    p1 = new PointF(p1.X, p1.Y + DISTANCE_BETWEEN_CHANNELS * m_shapeEdit.UserBaseUnit);
                }
            }

            // Draw two wires for the SAR
            // line for high
            p1 = new PointF(m_bodyBounds.X + (m_params.NumChannels > 1 ?
                (MUX_X_OFFSET_IN_BODY + MUX_WIDTH) * m_shapeEdit.UserBaseUnit : 0),
                SarLocation.Y + m_shapeEdit.UserBaseUnit);
            p2 = new PointF(SarLocation.X + m_shapeEdit.UserBaseUnit, p1.Y);
            err = m_shapeEdit.CreateLine(new string[] { WIRES_NAME }, p1, p2);
            if (err.IsNotOK)
            {
                return err;
            }
            // line for low
            List<PointF> lowLine = new List<PointF>();
            lowLine.Add(new PointF(p2.X, p1.Y + SAR_HEIGHT / 2f * m_shapeEdit.UserBaseUnit));
            lowLine.Add(new PointF(p1.X + (m_params.IsDifferentialMode ? 0 : SINGLE_ENDED_LOW_OFFSET) *
                m_shapeEdit.UserBaseUnit, lowLine[0].Y));
            if (!m_params.IsDifferentialMode)
            {
                lowLine.Add(new PointF(lowLine[1].X, lowLine[1].Y + VSS_VLINE_LENGTH * m_shapeEdit.UserBaseUnit));
                err = DrawVss(lowLine[2]);
            }
            err = m_shapeEdit.CreatePolyline(new string[] { WIRES_NAME }, lowLine);
            if (err.IsNotOK)
            {
                return err;
            }

            err = m_shapeEdit.SetOutlineWidth(WIRES_NAME, WIRES_WIDTH);
            if (err.IsNotOK)
            {
                return err;
            }

            err = m_shapeEdit.SetOutlineColor(WIRES_NAME, WIRES_COLOR);
            if (err.IsNotOK)
            {
                return err;
            }

            return CyCustErr.OK;
        }

        private CyCustErr DrawVss(PointF from)
        {
            bool drawVss = (m_params.InputRange != CyEInputRange.RANGE_0) &&
                (m_params.InputRange != CyEInputRange.RANGE_3);

            m_shapeEdit.ShapesRemove(VREF_NAME);

            List<PointF> points = new List<PointF>();

            points.Add(new PointF(from.X - m_shapeEdit.UserBaseUnit, from.Y));
            points.Add(new PointF(from.X + m_shapeEdit.UserBaseUnit, from.Y));
            if (drawVss)
            {
                points.Add(new PointF(from.X, from.Y + m_shapeEdit.UserBaseUnit));
                points.Add(points[0]);
                points.Add(points[1]);
            }

            // Draw figure
            CyCustErr err = m_shapeEdit.CreatePolyline(new string[] { VREF_NAME }, points);
            if (err.IsNotOK)
            {
                return err;
            }

            err = m_shapeEdit.SetOutlineWidth(VREF_NAME, drawVss ? VSS_LINE_WIDTH : VREF_LINE_WIDTH);
            if (err.IsNotOK)
            {
                return err;
            }

            err = m_shapeEdit.SetOutlineColor(VREF_NAME, VSS_LINE_COLOR);
            if (err.IsNotOK)
            {
                return err;
            }

            if (drawVss)
            {
                err = m_shapeEdit.SetFillColor(VREF_NAME, VSS_FILL_COLOR);
                if (err.IsNotOK)
                {
                    return err;
                }
            }

            // Add text
            m_shapeEdit.ShapesRemove(VREF_TEXT_NAME);

            StringFormat fmt = new StringFormat();
            fmt.Alignment = StringAlignment.Near;
            fmt.LineAlignment = StringAlignment.Near;
            PointF textLocation = new PointF(points[0].X - m_shapeEdit.UserBaseUnit / 2, points[drawVss ? 2 : 0].Y);
            err = m_shapeEdit.CreateAnnotation(new string[] { VREF_TEXT_NAME }, drawVss ? VSS_TEXT : VREF_TEXT,
                textLocation, ANNOTATIONS_FONT, fmt);
            if (err.IsNotOK)
            {
                return err;
            }

            err = m_shapeEdit.SetFillColor(VREF_TEXT_NAME, VSS_LINE_COLOR);
            if (err.IsNotOK)
            {
                return err;
            }

            err = m_shapeEdit.ClearOutline(VREF_TEXT_NAME);
            if (err.IsNotOK)
            {
                return err;
            }

            return CyCustErr.OK;
        }

        private CyCustErr DrawVref()
        {
            return CyCustErr.OK;
        }

        private CyCustErr CorrectSarLocation()
        {
            PointF sarLocation = m_shapeEdit.GetShapeBounds(SAR_SHAPE_NAME).Location;
            PointF sarNewLocation = SarLocation;

            PointF offset = new PointF(sarNewLocation.X - sarLocation.X, sarNewLocation.Y - sarLocation.Y);

            CyCustErr err = m_shapeEdit.ShapesMoveBy(SAR_SHAPE_NAME, offset);
            if (err.IsNotOK)
            {
                return err;
            }

            err = m_shapeEdit.BringToFront(SAR_SHAPE_NAME);
            if (err.IsNotOK)
            {
                return err;
            }

            return CyCustErr.OK;
        }

        private CyCustErr CreateAnnotation(string text, PointF loc)
        {
            StringFormat fmt = new StringFormat();
            fmt.Alignment = StringAlignment.Near;
            fmt.LineAlignment = StringAlignment.Near;
            CyCustErr err = m_shapeEdit.CreateAnnotation(new string[] { ANNOTATION_NAME }, text, loc, ANNOTATIONS_FONT,
                fmt);
            if (err.IsNotOK)
            {
                return err;
            }

            err = m_shapeEdit.SetFillColor(ANNOTATION_NAME, ANNOTATION_COLOR);
            if (err.IsNotOK)
            {
                return err;
            }

            err = m_shapeEdit.ClearOutline(ANNOTATION_NAME);
            if (err.IsNotOK)
            {
                return err;
            }

            return CyCustErr.OK;
        }

        private CyCustErr CorrectTermialLocation()
        {
            CyCustErr err;

            m_termEdit.TerminalDelete(VIN_MINUS_0_TERM_NAME);

            if (m_params.IsDifferentialMode)
            {
                float x = m_bodyBounds.X - m_shapeEdit.UserBaseUnit;
                float y = m_bodyBounds.Y +
                    (VIN_MINUS_0_TERM_Y_OFFSET + 1) * m_shapeEdit.UserBaseUnit;

                err = m_termEdit.TerminalAdd(VIN_MINUS_0_TERM_NAME, CyCompDevTermDir.INPUT, CyCompDevTermType.ANALOG,
                    new PointF(x, y), string.Empty, 0f, false);

                if (err.IsNotOK)
                {
                    return err;
                }
            }

            if (m_params.NumChannels == 1)
            {
                m_termEdit.TerminalDelete(VIN_PLUS_0_TERM_NAME);

                float x = m_bodyBounds.X - m_shapeEdit.UserBaseUnit;
                float y = m_bodyBounds.Y + (VIN_MINUS_0_TERM_Y_OFFSET - 1) * m_shapeEdit.UserBaseUnit;

                err = m_termEdit.TerminalAdd(VIN_PLUS_0_TERM_NAME, CyCompDevTermDir.INPUT,
                    CyCompDevTermType.ANALOG, new PointF(x, y), string.Empty, 0f, false);

                if (err.IsNotOK)
                {
                    return err;
                }
            }

            return CyCustErr.OK;
        }
    }
}
