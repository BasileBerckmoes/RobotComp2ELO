/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace ScanComp_v1_10
{
    public partial class CyCustomizer
    {
        public CyCustErr CustomizeShapes(ICyInstQuery_v1 query, ICySymbolShapeEdit_v1 shapeEdit,
            ICyTerminalEdit_v1 termEdit)
        {
            CyParameters parameters = new CyParameters(query, termEdit);
            CyShapeBuilder shapeBuilder = new CyShapeBuilder(parameters, shapeEdit, termEdit);

            shapeBuilder.RemoveShapes();
            shapeBuilder.DrawBody();
            shapeBuilder.DrawInputs();
            shapeBuilder.DrawInputMux();
            if (parameters.OutputsEnable)
            {
                shapeBuilder.DrawOutputs();
                shapeBuilder.DrawOutputMux();
            }
            shapeBuilder.DrawOpamp();
            return CyCustErr.OK;
        }
    }

    public class CyShapeBuilder
    {
        #region Shape names constants
        private const string BODY_SHAPE_NAME = "body";
        private const string CONN_LINES_NAME = "connLine";
        private const string MUX_SHAPE_NAME = "muxShape";
        private const string OPAMP_SHAPE_NAME = "opampShape";
        private const string VDAC_SHAPE = "vdacShape";
        private const string POSITIVE_INPUT_TERMINAL_NAME = "Vplus";
        private const string NEGATIVE_INPUT_TERMINAL_NAME = "Vminus";
        private const string OUTPUT_TERMINAL_NAME = "CmpOut";
        private const string ANNOTATIONS_NAME = "text";
        #endregion

        #region Shapes common constants
        private const float SHAPE_BODY_LINE_WIDTH = 1f;
        private const float CONNECTION_LINE_WIDTH = 0.5f;
        private const float INNER_BLOCK_LINE_WIDTH = 0.5f;

        private readonly Color BODY_FILL_COLOR = Color.Gainsboro;
        private readonly Color CONNECTION_COLOR = Color.Navy;
        private readonly Color ANNOTATION_COLOR = Color.Black;
        private readonly Color VDAC_COLOR = Color.FromArgb(128, 255, 255);
        private readonly Font ANNOTATIONS_FONT = new Font(FontFamily.GenericSansSerif, 10f, FontStyle.Regular,
            GraphicsUnit.Point, 1, false);
        #endregion

        #region Read-only members
        private readonly float BASE_UNIT;
        private readonly float SHAPE_BODY_MIN_HEIGHT;
        private readonly float MUX_CHANNEL_OFFSET;
        private readonly float MUX_WIDTH;
        private readonly float MUX_INPUT_GREATER_HEIGHT;
        private readonly float MUX_OUTPUT_GREATER_HEIGHT;
        private readonly float MUX_SIDES_DIFF;
        private readonly float MUX_OUTPUT_OFFSET_X;
        private readonly float MUX_OUTPUT_OFFSET_Y;
        private readonly float MUX_INPUT_OFFSET_X;
        private readonly float MUX_INPUT_OFFSET_Y;
        private readonly float MUX_INPUT_DIFF_MODE_OFFSET;
        private readonly float DISTANCE_BETWEEN_LINES;
        private readonly float LINES_OFFSET_X;
        private readonly float LINES_OFFSET_Y;

        private readonly string[] SHAPES_TO_REMOVE = new string[]
        {
            BODY_SHAPE_NAME,
            CONN_LINES_NAME,
            MUX_SHAPE_NAME,
            VDAC_SHAPE
        };
        #endregion

        private CyParameters m_params;
        private ICySymbolShapeEdit_v1 m_shapeEdit;
        private ICyTerminalEdit_v1 m_termEdit;
        private PointF m_bodyLocation;
        private SizeF m_bodySize;

        #region Constructor(s)
        public CyShapeBuilder(CyParameters parameters, ICySymbolShapeEdit_v1 shapeEdit, ICyTerminalEdit_v1 termEdit)
        {
            m_shapeEdit = shapeEdit;
            m_termEdit = termEdit;
            m_params = parameters;
            RectangleF bodyRect = m_shapeEdit.GetShapeBounds(BODY_SHAPE_NAME);
            m_bodyLocation = bodyRect.Location;
            m_bodySize = bodyRect.Size;

            BASE_UNIT = m_shapeEdit.UserBaseUnit;
            SHAPE_BODY_MIN_HEIGHT = 18 * BASE_UNIT;

            // Initialize MUX constants
            MUX_CHANNEL_OFFSET = 2 * BASE_UNIT;
            MUX_WIDTH = 3 * BASE_UNIT;
            MUX_INPUT_DIFF_MODE_OFFSET = IsDiffMode() ? (m_params.SequencedChannels * BASE_UNIT) : 0;
            MUX_INPUT_GREATER_HEIGHT = ((m_params.SequencedChannels > 1) ?
                (m_params.SequencedChannels + 1) * MUX_CHANNEL_OFFSET :
                3 * MUX_CHANNEL_OFFSET) + MUX_INPUT_DIFF_MODE_OFFSET;
            MUX_OUTPUT_GREATER_HEIGHT = ((m_params.SequencedChannels > 1) ?
                (m_params.SequencedChannels + 1) * MUX_CHANNEL_OFFSET : 3 * MUX_CHANNEL_OFFSET);
            MUX_SIDES_DIFF = 2 * BASE_UNIT;
            MUX_INPUT_OFFSET_X = BASE_UNIT;
            MUX_INPUT_OFFSET_Y = ((m_params.SequencedChannels == 1) ? 6 : 7) * BASE_UNIT;
            MUX_OUTPUT_OFFSET_X = m_bodySize.Width - BASE_UNIT;
            MUX_OUTPUT_OFFSET_Y = MUX_INPUT_OFFSET_Y;

            // Initialize input/output lines constants
            DISTANCE_BETWEEN_LINES = 2 * BASE_UNIT;
            LINES_OFFSET_X = BASE_UNIT;
            LINES_OFFSET_Y = MUX_INPUT_OFFSET_Y + 2 * BASE_UNIT;
        }
        #endregion

        #region Draw methods
        public CyCustErr DrawBody()
        {
            float distanceBetweenMuxAndBottom = 3;
            if (m_params.NegativeInput == CyENegativeInput.INTERN)
            {
                distanceBetweenMuxAndBottom = 6;
                if (m_params.SequencedChannels == 2) // add one cell to have two cells between VDAC and bottom side                    
                    distanceBetweenMuxAndBottom = SHAPE_BODY_MIN_HEIGHT + BASE_UNIT;
            }

            float bodyHeight = m_params.SequencedChannels < 3 ? SHAPE_BODY_MIN_HEIGHT :
                MUX_INPUT_OFFSET_Y + MUX_INPUT_GREATER_HEIGHT + BASE_UNIT * distanceBetweenMuxAndBottom;

            PointF bodyLocation = m_bodyLocation;
            m_shapeEdit.CreateRectangle(new string[] { BODY_SHAPE_NAME }, bodyLocation, m_bodySize.Width, bodyHeight);

            // Set the color and outline width of symbol body
            m_shapeEdit.SetFillColor(BODY_SHAPE_NAME, BODY_FILL_COLOR);
            m_shapeEdit.SetOutlineWidth(BODY_SHAPE_NAME, SHAPE_BODY_LINE_WIDTH);
            m_shapeEdit.SendToBack(BODY_SHAPE_NAME);
            return CyCustErr.OK;
        }

        public CyCustErr DrawInputs()
        {
            // Mux inputs position depend on input mux position
            float x0;
            float y0;
            float x1;
            float y1;
            PointF startPt;
            PointF endPt;
            float termOffset;

            for (int channelIndex = 0; channelIndex < m_params.SequencedChannels; channelIndex++)
            {
                termOffset = IsDiffMode() && channelIndex > 0 ? BASE_UNIT * channelIndex : 0;
                // Draw connection lines
                x0 = m_bodyLocation.X;
                y0 = (m_bodyLocation.Y + LINES_OFFSET_Y) + (channelIndex * DISTANCE_BETWEEN_LINES) + termOffset;
                x1 = m_bodyLocation.X + LINES_OFFSET_X;
                y1 = y0;

                if (m_params.SequencedChannels == 1)
                {
                    y0 += BASE_UNIT;
                    y1 += BASE_UNIT;
                }

                startPt = new PointF(x0, y0);
                endPt = new PointF(x1, y1);
                m_shapeEdit.CreateLine(new string[] { CONN_LINES_NAME }, startPt, endPt);

                // Diff mode
                if (IsDiffMode())
                {
                    termOffset = BASE_UNIT;
                    // Draw connection lines
                    startPt = new PointF(x0, y0 + termOffset);
                    endPt = new PointF(x1, y1 + termOffset);
                    m_shapeEdit.CreateLine(new string[] { CONN_LINES_NAME }, startPt, endPt);
                }
            }

            m_shapeEdit.SetFillColor(CONN_LINES_NAME, CONNECTION_COLOR);
            m_shapeEdit.SetOutlineColor(CONN_LINES_NAME, CONNECTION_COLOR);
            m_shapeEdit.SetOutlineWidth(CONN_LINES_NAME, CONNECTION_LINE_WIDTH);

            return CyCustErr.OK;
        }

        public CyCustErr DrawOutputs()
        {
            // Mux outputs position depend on output mux position
            float x0;
            float y0;
            float x1;
            float y1;
            PointF startPt;
            PointF endPt;

            for (int channelIndex = 0; channelIndex < m_params.SequencedChannels; channelIndex++)
            {
                // Draw connection lines
                x0 = m_bodyLocation.X + m_bodySize.Width;
                y0 = (m_bodyLocation.Y + LINES_OFFSET_Y) + (channelIndex * DISTANCE_BETWEEN_LINES);
                x1 = x0 - LINES_OFFSET_X;
                y1 = y0;

                if (m_params.SequencedChannels == 1)
                {
                    y0 += BASE_UNIT;
                    y1 += BASE_UNIT;
                }

                startPt = new PointF(x0, y0);
                endPt = new PointF(x1, y1);
                m_shapeEdit.CreateLine(new string[] { CONN_LINES_NAME }, startPt, endPt);
            }

            m_shapeEdit.SetFillColor(CONN_LINES_NAME, CONNECTION_COLOR);
            m_shapeEdit.SetOutlineColor(CONN_LINES_NAME, CONNECTION_COLOR);
            m_shapeEdit.SetOutlineWidth(CONN_LINES_NAME, CONNECTION_LINE_WIDTH);

            return CyCustErr.OK;
        }

        public CyCustErr DrawInputMux()
        {
            float diffModeFirstAnnotationOffset = IsDiffMode() ? BASE_UNIT / 2 : 0;
            float diffModeOtherAnnotationsOffset = IsDiffMode() ? BASE_UNIT : 0;

            PointF leftTop = new PointF(m_bodyLocation.X + MUX_INPUT_OFFSET_X, m_bodyLocation.Y + MUX_INPUT_OFFSET_Y);
            PointF leftBottom = new PointF(leftTop.X, leftTop.Y + MUX_INPUT_GREATER_HEIGHT);
            PointF rightTop = new PointF(leftTop.X + MUX_WIDTH, leftTop.Y + MUX_SIDES_DIFF);
            PointF rightBottom = new PointF(rightTop.X, leftBottom.Y - MUX_SIDES_DIFF);

            // Create polygon
            m_shapeEdit.CreatePolyline(new string[] { MUX_SHAPE_NAME },
                leftTop, leftBottom, rightBottom, rightTop, leftTop, leftBottom);
            m_shapeEdit.SetFillColor(MUX_SHAPE_NAME, BODY_FILL_COLOR);
            m_shapeEdit.SetOutlineWidth(MUX_SHAPE_NAME, INNER_BLOCK_LINE_WIDTH);

            // Create annotations for channels
            PointF textLocation = new PointF(rightTop.X - 3 * BASE_UNIT,
                                             rightTop.Y - 5 + diffModeFirstAnnotationOffset);
            if (m_params.SequencedChannels == 1)
                textLocation.Y += BASE_UNIT;
            for (int i = 0; i < m_params.SequencedChannels; i++)
            {
                CreateAnnotation(i.ToString(), textLocation);
                textLocation = new PointF(textLocation.X,
                                          textLocation.Y + MUX_CHANNEL_OFFSET + diffModeOtherAnnotationsOffset);
            }
            return CyCustErr.OK;
        }

        public CyCustErr DrawOutputMux()
        {
            PointF rightTop = new PointF(m_bodyLocation.X + MUX_OUTPUT_OFFSET_X,
                                         m_bodyLocation.Y + MUX_OUTPUT_OFFSET_Y);
            PointF rightBottom = new PointF(rightTop.X, rightTop.Y + MUX_OUTPUT_GREATER_HEIGHT);
            PointF leftTop = new PointF(rightTop.X - MUX_WIDTH, rightTop.Y + MUX_SIDES_DIFF);
            PointF leftBottom = new PointF(leftTop.X, rightBottom.Y - MUX_SIDES_DIFF);

            // Create polygon
            m_shapeEdit.CreatePolyline(new string[] { MUX_SHAPE_NAME },
                leftTop, leftBottom, rightBottom, rightTop, leftTop, leftBottom);
            m_shapeEdit.SetFillColor(MUX_SHAPE_NAME, BODY_FILL_COLOR);
            m_shapeEdit.SetOutlineWidth(MUX_SHAPE_NAME, INNER_BLOCK_LINE_WIDTH);

            // Create annotations for channels
            PointF textLocation = new PointF(rightTop.X - (m_params.SequencedChannels > 10 ? 2.5f : 1.5f) * BASE_UNIT,
                                             rightTop.Y + 7f);
            if (m_params.SequencedChannels == 1)
                textLocation.Y += BASE_UNIT;
            for (int i = 0; i < m_params.SequencedChannels; i++)
            {
                CreateAnnotation(i.ToString(), textLocation);
                textLocation = new PointF(textLocation.X, textLocation.Y + MUX_CHANNEL_OFFSET);
            }
            return CyCustErr.OK;
        }

        public CyCustErr DrawOpamp()
        {
            SizeF opampSize = m_shapeEdit.GetShapeBounds(OPAMP_SHAPE_NAME).Size;
            PointF opampLocation = m_shapeEdit.GetShapeBounds(OPAMP_SHAPE_NAME).Location;
            PointF opampNewLocation = new PointF();
            PointF startPt;
            PointF endPt;

            opampNewLocation.X = m_bodyLocation.X + MUX_INPUT_OFFSET_X + MUX_WIDTH + BASE_UNIT * 2;

            switch (m_params.NegativeInput)
            {
                case CyENegativeInput.UNIQUE:
                    // Define opamp location and draw minus line parallel to the plus line which is 
                    // the part of the OpAmp shape
                    opampNewLocation.Y = m_bodyLocation.Y + MUX_INPUT_OFFSET_Y +
                                                    MUX_INPUT_GREATER_HEIGHT / 2 - opampSize.Height / 2;
                    // Minus line
                    startPt = new PointF(opampNewLocation.X - BASE_UNIT * 2, opampNewLocation.Y + 4 * BASE_UNIT);
                    endPt = new PointF(opampNewLocation.X + BASE_UNIT * 2, opampNewLocation.Y + 4 * BASE_UNIT);
                    m_shapeEdit.CreateLine(new string[] { CONN_LINES_NAME }, startPt, endPt);
                    // Plus line
                    startPt = new PointF(startPt.X + BASE_UNIT * 2, opampNewLocation.Y + 2 * BASE_UNIT);
                    endPt = new PointF(startPt.X - BASE_UNIT * 2, startPt.Y);
                    m_shapeEdit.CreateLine(new string[] { CONN_LINES_NAME }, startPt, endPt);
                    break;
                case CyENegativeInput.COMMON:
                    // Define opamp location and draw minus line with input terminal at the end
                    opampNewLocation.Y = m_bodyLocation.Y + MUX_INPUT_OFFSET_Y +
                                                    MUX_INPUT_GREATER_HEIGHT / 2 - 3 * BASE_UNIT;
                    // Minus line
                    // Part 1 (near minus)
                    startPt = new PointF(opampNewLocation.X + BASE_UNIT, opampNewLocation.Y + 4 * BASE_UNIT);
                    endPt = new PointF(startPt.X - BASE_UNIT - (BASE_UNIT / 2), opampNewLocation.Y + 4 * BASE_UNIT);
                    m_shapeEdit.CreateLine(new string[] { CONN_LINES_NAME }, startPt, endPt);
                    // Part 2 (line up)
                    startPt = endPt;
                    endPt.Y = m_bodyLocation.Y + 5 * BASE_UNIT;
                    m_shapeEdit.CreateLine(new string[] { CONN_LINES_NAME }, startPt, endPt);
                    // Part 3 (line to the Vminus terminal)
                    startPt = endPt;
                    endPt.X = m_bodyLocation.X;
                    m_shapeEdit.CreateLine(new string[] { CONN_LINES_NAME }, startPt, endPt);

                    // Plus line 
                    // Arc
                    startPt = new PointF(opampNewLocation.X - BASE_UNIT,
                        opampNewLocation.Y + BASE_UNIT * 2 - BASE_UNIT / 4);
                    string arcName = "arcShape";
                    m_shapeEdit.CreateArc(new string[] { arcName },
                        new RectangleF(startPt.X, startPt.Y, BASE_UNIT, BASE_UNIT / 2), 180f, 180f);
                    m_shapeEdit.SetOutlineColor(arcName, CONNECTION_COLOR);
                    m_shapeEdit.SetOutlineWidth(arcName, CONNECTION_LINE_WIDTH);
                    // Line to the input mux
                    startPt = new PointF(startPt.X, startPt.Y + BASE_UNIT / 4);
                    endPt = new PointF(startPt.X - BASE_UNIT, startPt.Y);
                    m_shapeEdit.CreateLine(new string[] { CONN_LINES_NAME }, startPt, endPt);
                    break;
                case CyENegativeInput.INTERN:
                    // Define opamp location and draw minus line with VDAC shape at the end
                    opampNewLocation.Y = m_bodyLocation.Y + MUX_INPUT_OFFSET_Y +
                                                    MUX_INPUT_GREATER_HEIGHT / 2 - 3 * BASE_UNIT;
                    // Plus line
                    startPt = new PointF(opampNewLocation.X, opampNewLocation.Y + BASE_UNIT * 2);
                    endPt = new PointF(startPt.X - BASE_UNIT * 2, startPt.Y);
                    m_shapeEdit.CreateLine(new string[] { CONN_LINES_NAME }, startPt, endPt);
                    // Minus line
                    // Line 1 (near minus)
                    startPt = new PointF(opampNewLocation.X + BASE_UNIT, opampNewLocation.Y + 4 * BASE_UNIT);
                    endPt = new PointF(startPt.X - BASE_UNIT, opampNewLocation.Y + 4 * BASE_UNIT);
                    m_shapeEdit.CreateLine(new string[] { CONN_LINES_NAME }, startPt, endPt);
                    // Line 2 (line down)
                    startPt = endPt;
                    endPt.Y = m_bodyLocation.Y + MUX_INPUT_OFFSET_Y + MUX_INPUT_GREATER_HEIGHT + 2 * BASE_UNIT;
                    m_shapeEdit.CreateLine(new string[] { CONN_LINES_NAME }, startPt, endPt);
                    // Line 3 (line to the VDAC)
                    startPt = endPt;
                    endPt.X += BASE_UNIT;
                    m_shapeEdit.CreateLine(new string[] { CONN_LINES_NAME }, startPt, endPt);
                    // VDAC
                    DrawVdac(new PointF(endPt.X, endPt.Y));
                    break;
                default:
                    Debug.Fail(String.Empty);
                    break;
            }

            // OpAmp is an existing shape. Move it to the new location that depends on mode
            CyCustErr err = m_shapeEdit.ShapesMoveTo(OPAMP_SHAPE_NAME, opampNewLocation);
            m_shapeEdit.BringToFront(OPAMP_SHAPE_NAME);

            // Draw OpAmp output line
            if (m_params.OutputsEnable)
            {
                if (m_params.NegativeInput == CyENegativeInput.UNIQUE)
                {
                    // Line 1 (from the OpAmp)
                    startPt = new PointF(opampNewLocation.X + opampSize.Width, opampNewLocation.Y + BASE_UNIT * 3);
                    endPt = new PointF(startPt.X + BASE_UNIT, startPt.Y);
                    m_shapeEdit.CreateLine(new string[] { CONN_LINES_NAME }, startPt, endPt);
                    // Line 2 (line up)
                    startPt = new PointF(endPt.X, endPt.Y);
                    endPt = new PointF(startPt.X,
                        m_bodyLocation.Y + MUX_OUTPUT_OFFSET_Y + MUX_OUTPUT_GREATER_HEIGHT / 2);
                    err = m_shapeEdit.CreateLine(new string[] { CONN_LINES_NAME }, startPt, endPt);
                    // Line 3 (line to the output mux)
                    startPt = new PointF(endPt.X, endPt.Y);
                    endPt = new PointF(startPt.X + BASE_UNIT, startPt.Y);
                    err = m_shapeEdit.CreateLine(new string[] { CONN_LINES_NAME }, startPt, endPt);
                }
                else
                {
                    startPt = new PointF(opampNewLocation.X + opampSize.Width, opampNewLocation.Y + BASE_UNIT * 3);
                    endPt = new PointF(startPt.X + BASE_UNIT * 2, startPt.Y);
                    m_shapeEdit.CreateLine(new string[] { CONN_LINES_NAME }, startPt, endPt);
                }
            }

            // Set style for the drawn lines
            m_shapeEdit.SetFillColor(CONN_LINES_NAME, CONNECTION_COLOR);
            m_shapeEdit.SetOutlineColor(CONN_LINES_NAME, CONNECTION_COLOR);
            m_shapeEdit.SetOutlineWidth(CONN_LINES_NAME, CONNECTION_LINE_WIDTH);

            return CyCustErr.OK;
        }

        private CyCustErr DrawVdac(PointF vdacInputLocation)
        {
            PointF leftCenter = vdacInputLocation;
            PointF leftTop = new PointF(leftCenter.X + 2 * BASE_UNIT, leftCenter.Y - 2 * BASE_UNIT);
            PointF rightTop = new PointF(leftTop.X + 4 * BASE_UNIT, leftTop.Y);
            PointF rightBottom = new PointF(rightTop.X, rightTop.Y + 4 * BASE_UNIT);
            PointF leftBottom = new PointF(rightBottom.X - 4 * BASE_UNIT, rightBottom.Y);

            m_shapeEdit.CreatePolyline(new string[] { VDAC_SHAPE },
                leftCenter, leftTop, rightTop, rightBottom, rightBottom, leftBottom, leftCenter);
            m_shapeEdit.SetFillColor(VDAC_SHAPE, VDAC_COLOR);
            m_shapeEdit.SetOutlineWidth(VDAC_SHAPE, INNER_BLOCK_LINE_WIDTH);
            m_shapeEdit.BringToFront(VDAC_SHAPE);
            CreateAnnotation("VDAC", new PointF(leftCenter.X + BASE_UNIT - 2, leftCenter.Y - BASE_UNIT + 1));
            return CyCustErr.OK;
        }

        private void CreateAnnotation(string text, PointF location)
        {
            StringFormat fmt = new StringFormat();
            fmt.Alignment = StringAlignment.Near;
            fmt.LineAlignment = StringAlignment.Near;
            m_shapeEdit.CreateAnnotation(new string[] { ANNOTATIONS_NAME }, text, location, ANNOTATIONS_FONT, fmt);
            m_shapeEdit.SetFillColor(ANNOTATIONS_NAME, ANNOTATION_COLOR);
            m_shapeEdit.ClearOutline(ANNOTATIONS_NAME);
        }
        #endregion

        #region Other methods
        public void RemoveShapes()
        {
            foreach (string shapeTag in SHAPES_TO_REMOVE)
            {
                m_shapeEdit.ShapesRemove(shapeTag);
            }
        }

        private bool IsDiffMode()
        {
            return m_params.NegativeInput == CyENegativeInput.UNIQUE;
        }
        #endregion
    }
}
