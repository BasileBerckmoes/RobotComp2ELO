/*******************************************************************************
* Copyright 2011-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace ADC_SAR_SEQ_P4_v2_40
{
    public class CyShapesBuilder
    {
        #region Shape names constants
        private const string BODY_SHAPE_NAME = "body";
        private const string CONN_LINES_NAME = "connLine";
        private const string INPUT_BUFFER_SHAPE_NAME = "inputBuffer";
        private const string MUX_SHAPE_NAME = "muxShape";
        private const string SAR_SHAPE_NAME = "sarShape";
        private const string STATE_LABEL = "CY_STATE_LABEL";
        private const string SINGLE_ENDED_REF_SHAPE_NAME = "singleEndedRef";
        private const string ANNOTATIONS_NAME = "text";
        private const string SINGLE_ENDED_REF_TEXT_NAME = "singleEndedRefText";
        private const string SAR_SIGNS_SHAPE_NAME = "sarSigns";
        private const string SINGLE_ENDED_LINE_SHAPE_NAME = "singleEndRefLine";
        #endregion

        #region Text constants
        private const string VSS_TEXT = "Vss";
        private const string VREF_TEXT = "Vref";
        private const string VNEG_TEXT = "Vneg";
        #endregion

        #region Shape unit constants
        private const int MUX_OFFSET_X = 3;
        private const int MUX_OFFSET_Y = 7;
        private const int MUX_WIDTH = 3;
        private const int MUX_CHANNEL_OFFSET = 3;
        private const int MUX_DIFF = 2;
        private const int BUFFER_OFFSET = MUX_OFFSET_X + MUX_WIDTH + 1;
        private const int BUFFER_WIDTH = 2;
        private const int BUFFER_HEIGHT = 4;
        private const int SAR_OFFSET = BUFFER_OFFSET + BUFFER_WIDTH + 1;
        private const int SAR_HEIGHT = 4;
        private const int BODY_MIN_UNITS_HEIGHT = 6;

        private readonly float BASE_UNIT;
        #endregion

        #region Terminals constants
        private const string INPUT_VOLTAGE_TERMINAL_NAME_BASE = "vin";
        private const string POSITIVE_INPUT_VOLTAGE_TERMINAL_NAME_BASE = INPUT_VOLTAGE_TERMINAL_NAME_BASE + "Plus";
        private const string NEGATIVE_INPUT_VOLTAGE_TERMINAL_NAME_BASE = INPUT_VOLTAGE_TERMINAL_NAME_BASE + "Minus";
        private const string VNEG_TERMINAL_NAME = INPUT_VOLTAGE_TERMINAL_NAME_BASE + "Neg";
        private const string INJECTION_CHANNEL_NAME = "INJ";
        #endregion

        #region Shapes common constants
        private const float INNER_BLOCK_LINE_WIDTH = 0.5f;
        private const float CONNECTION_LINE_WIDTH = 0.5f;
        private const float CLOCK_SHAPE_LINE_WIDTH = 1f;
        private const float VREF_SHAPE_LINE_WIDTH = 1.5f;
        private const float SAR_SIGNS_LINE_WIDTH = 1f;
        private const float BODY_SHAPE_LINE_WIDTH = 1f;
        private readonly Color BODY_FILL_COLOR = Color.Gainsboro;
        private readonly Color ANNOTATION_COLOR = Color.Black;
        private readonly Color VSS_FILL_COLOR = Color.White;
        private readonly Color CONNECTION_COLOR = Color.Navy;
        private readonly Color INTERNAL_FUNCTIONAL_BLOCK_FILL_COLOR = Color.FromArgb(0, 255, 255);
        private readonly Font ANNOTATIONS_FONT = new Font(FontFamily.GenericSansSerif, 10f, FontStyle.Regular,
            GraphicsUnit.Point, 1, false);

        private readonly string [] SHAPES_TO_REMOVE = new string []
        {
            BODY_SHAPE_NAME,
            MUX_SHAPE_NAME,
            INPUT_BUFFER_SHAPE_NAME,
            CONN_LINES_NAME,
            SINGLE_ENDED_REF_SHAPE_NAME,
            SINGLE_ENDED_REF_TEXT_NAME,
            ANNOTATIONS_NAME,
            SINGLE_ENDED_LINE_SHAPE_NAME
        };
        #endregion

        #region Internally used data
        private PointF m_bodyLocation;
        private SizeF m_bodySize;
        private PointF m_inputBufferLoc;
        private PointF m_sarLoc;
        private bool m_symbolHasSingleEndedInputChannel = false;
        #endregion

        private CyParameters m_params;
        private ICySymbolShapeEdit_v1 m_shapeEdit;
        private ICyTerminalEdit_v1 m_termEdit;

        #region Constructor(s)
        public CyShapesBuilder(CyParameters parameters, ICySymbolShapeEdit_v1 shapeEd, ICyTerminalEdit_v1 termEd)
        {
            m_params = parameters;
            m_shapeEdit = shapeEd;
            m_termEdit = termEd;

            BASE_UNIT = m_shapeEdit.UserBaseUnit;

            RectangleF bodyRect = m_shapeEdit.GetShapeBounds(BODY_SHAPE_NAME);
            m_inputBufferLoc = new PointF(bodyRect.Location.X + BUFFER_OFFSET * BASE_UNIT,
                bodyRect.Location.Y + MUX_OFFSET_Y * BASE_UNIT);
            m_sarLoc = new PointF(bodyRect.Location.X + SAR_OFFSET * BASE_UNIT,
                m_inputBufferLoc.Y);

            m_bodyLocation = bodyRect.Location;
            m_bodySize = bodyRect.Size;
            m_bodySize.Height = BODY_MIN_UNITS_HEIGHT * BASE_UNIT;
        }
        #endregion

        #region Auxiliary properties
        bool SymbolHasMux
        {
            get
            {
                return m_params.InjectionChannelEnabled || m_params.SequencedChannels > 1;
            }
        }
        #endregion

        public void DrawSymbol()
        {
            // Remove all terminals and shapes
            RemoveShapes();

            //Draw mux
            if (SymbolHasMux)
            {
                CreateMux();
            }
            else
            {
                m_bodySize.Height += (SAR_HEIGHT + 3) * BASE_UNIT;
            }

            // Draw connection lines
            CreateVoltageInputs();

            // Draw symbol body
            CreateBody();

            //Correct SAR
            CorrectSARLocation();
            //move cy_state label to front
            m_shapeEdit.BringToFront(STATE_LABEL);

        }

        #region Create shapes
        private CyCustErr CreateMux()
        {
            byte numChannels = m_params.SequencedChannels;

            int actualNumChannels = numChannels + (m_params.InjectionChannelEnabled ? 1 : 0);
            int muxUnitsHeight = (actualNumChannels + 1) * MUX_CHANNEL_OFFSET;

            PointF leftTop = new PointF(m_bodyLocation.X + MUX_OFFSET_X * BASE_UNIT,
                m_bodyLocation.Y + MUX_OFFSET_Y * BASE_UNIT);
            PointF leftBottom = new PointF(leftTop.X, leftTop.Y + muxUnitsHeight * BASE_UNIT);
            PointF rightTop = new PointF(leftTop.X + MUX_WIDTH * BASE_UNIT, leftTop.Y + MUX_DIFF *
                BASE_UNIT);
            PointF rightBottom = new PointF(rightTop.X, leftBottom.Y - MUX_DIFF * BASE_UNIT);

            // Create polygon
            m_shapeEdit.CreatePolyline(new string[] { MUX_SHAPE_NAME }, leftTop, leftBottom, rightBottom, rightTop,
                leftTop, leftBottom);
            m_shapeEdit.SetFillColor(MUX_SHAPE_NAME, BODY_FILL_COLOR);
            m_shapeEdit.SetOutlineWidth(MUX_SHAPE_NAME, INNER_BLOCK_LINE_WIDTH);

            // Create annotations for channels
            PointF textLoc = new PointF(rightTop.X - 3 * BASE_UNIT, rightTop.Y);
            for (int i = 0; i < actualNumChannels; i++)
            {
                string text = (m_params.InjectionChannelEnabled && i == actualNumChannels - 1) ?
                    INJECTION_CHANNEL_NAME : i.ToString();
                CreateAnnotation(text, textLoc);
                textLoc = new PointF(textLoc.X, textLoc.Y + MUX_CHANNEL_OFFSET * BASE_UNIT);
            }

            m_shapeEdit.ClearOutline(ANNOTATIONS_NAME);

            // Set new location for buffer and SAR
            m_inputBufferLoc = new PointF(m_bodyLocation.X + BUFFER_OFFSET * BASE_UNIT,
                rightTop.Y + (rightBottom.Y - rightTop.Y) / 2 - BUFFER_HEIGHT / 2 * BASE_UNIT);
            m_sarLoc = new PointF(m_bodyLocation.X + SAR_OFFSET * BASE_UNIT,
                m_inputBufferLoc.Y);
            m_bodySize.Height += (muxUnitsHeight + 3) * BASE_UNIT;


            return CyCustErr.OK;
        }

        private CyCustErr CreateInputBuffer()
        {
            PointF second = new PointF(m_inputBufferLoc.X, m_inputBufferLoc.Y + BUFFER_HEIGHT *
                BASE_UNIT);
            PointF third = new PointF(m_inputBufferLoc.X + BUFFER_WIDTH * BASE_UNIT,
                m_inputBufferLoc.Y + BUFFER_HEIGHT / 2 * BASE_UNIT);
            m_shapeEdit.CreatePolyline(new string[] { INPUT_BUFFER_SHAPE_NAME }, m_inputBufferLoc, second, third,
                m_inputBufferLoc, second);
            m_shapeEdit.SetFillColor(INPUT_BUFFER_SHAPE_NAME, INTERNAL_FUNCTIONAL_BLOCK_FILL_COLOR);
            m_shapeEdit.SetOutlineWidth(INPUT_BUFFER_SHAPE_NAME, INNER_BLOCK_LINE_WIDTH);

            return CyCustErr.OK;
        }

        private CyCustErr CorrectSARLocation()
        {
            PointF sarLocation = m_shapeEdit.GetShapeBounds(SAR_SHAPE_NAME).Location;
            PointF sarNewLocation = m_sarLoc;

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

        private CyCustErr CreateBody()
        {
            byte numChannels = m_params.SequencedChannels;

            float bodyWidth = m_bodySize.Width;

            PointF bodyLocation = m_bodyLocation;
            CyCustErr err = m_shapeEdit.CreateRectangle(new string[] { BODY_SHAPE_NAME }, bodyLocation, bodyWidth,
                m_bodySize.Height);
            if (err.IsNotOk)
            {
                return err;
            }

            // Set the color and outline width of symbol body
            err = m_shapeEdit.SetFillColor(BODY_SHAPE_NAME, Color.Gainsboro);
            if (err.IsNotOk)
            {
                return err;
            }
            err = m_shapeEdit.SetOutlineWidth(BODY_SHAPE_NAME, BODY_SHAPE_LINE_WIDTH);
            if (err.IsNotOk)
            {
                return err;
            }

            err = m_shapeEdit.SendToBack(BODY_SHAPE_NAME);
            if (err.IsNotOk)
            {
                return err;
            }

            return CyCustErr.OK;
        }

        private CyCustErr CreateVoltageInputs()
        {
            byte numChannels = m_params.SequencedChannels;
            PointF singleEndedPoint1 = new PointF();
            PointF singleEndedPoint2 = new PointF();
            PointF singleEndedPoint3 = new PointF();

            List<string> connLinesTags = new List<string>();
            connLinesTags.Add(CONN_LINES_NAME);

            // Create mux connections
            float x0 = m_bodyLocation.X;
            float x0_se = m_bodyLocation.X + 2 * BASE_UNIT;
            string termName;
            if (SymbolHasMux)
            {
                float x1 = m_bodyLocation.X + 3 * BASE_UNIT;
                float y0 = m_bodyLocation.Y + 9 * BASE_UNIT;

                int numMuxInputs = numChannels + (m_params.InjectionChannelEnabled ? 1 : 0);
                if (numMuxInputs > 1)
                {
                    for (int i = 0; i < numMuxInputs; i++)
                    {
                        CyChannelsConfigTableRow currentRow =
                            m_params.m_channelsConfTable.m_channelsConfigTable[m_params.TableRowIndex(i)];

                        // Create Vin+
                        PointF beg = new PointF(x0, y0 + i * 3 * BASE_UNIT);
                        PointF end = new PointF(x1, beg.Y);
                        m_shapeEdit.CreateLine(connLinesTags, beg, end);
                        PointF termLoc = new PointF(beg.X - BASE_UNIT, beg.Y);
                        string channelName = m_params.InjectionChannelEnabled && i == numMuxInputs - 1 ?
                            INJECTION_CHANNEL_NAME :
                            i.ToString();
                        termName = POSITIVE_INPUT_VOLTAGE_TERMINAL_NAME_BASE + channelName;
                        m_termEdit.TerminalAdd(termName, CyCompDevTermDir.INOUT, CyCompDevTermType.ANALOG, termLoc,
                            string.Empty, 0f, false);
                        m_termEdit.SetMustConnectIfVisible(termName, true);
                        m_termEdit.SetIsBurriedPin(termName, false);

                        // Check if Vin- has single ended mode
                        bool singleEnded = false;
                        if (i < m_params.m_channelsConfTable.m_channelsConfigTable.Count)
                        {
                            singleEnded = currentRow.m_mode == CyEMode.Single;
                        }
                        // Create Vin-
                        beg = new PointF(singleEnded ? x0_se : x0, beg.Y + BASE_UNIT);
                        end = new PointF(x1, beg.Y);
                        // If connector is first single ended remember its begin point,
                        // otherwise create wire
                        if (singleEnded)
                        {
                            if (!m_symbolHasSingleEndedInputChannel)
                            {
                                singleEndedPoint1 = end;
                                singleEndedPoint2 = beg;
                                m_symbolHasSingleEndedInputChannel = true;
                            }
                            else
                            {
                                m_shapeEdit.CreateLine(connLinesTags, beg, end);
                                m_shapeEdit.CreateEllipse(connLinesTags, beg, 1f, 1f);
                            }
                        }
                        else
                        {
                            m_shapeEdit.CreateLine(connLinesTags, beg, end);
                            termLoc = new PointF(termLoc.X, termLoc.Y + BASE_UNIT);
                            termName = NEGATIVE_INPUT_VOLTAGE_TERMINAL_NAME_BASE + channelName;
                            m_termEdit.TerminalAdd(termName, CyCompDevTermDir.INOUT, CyCompDevTermType.ANALOG, termLoc,
                                string.Empty, 0f, false);
                            m_termEdit.SetMustConnectIfVisible(termName, true);
                            m_termEdit.SetIsBurriedPin(termName, false);
                        }
                    }

                    if (m_symbolHasSingleEndedInputChannel)
                    {
                        singleEndedPoint3 = new PointF(x0_se, y0 + (numMuxInputs * 3 + 2) * BASE_UNIT);
                    }
                }
            }

            // Create two connections to SAR
            if (SymbolHasMux)
            {
                PointF connEnd = new PointF(m_sarLoc.X + BASE_UNIT, m_sarLoc.Y +
                    BASE_UNIT);
                PointF connBeg = new PointF(m_inputBufferLoc.X - BASE_UNIT, connEnd.Y);
                m_shapeEdit.CreateLine(connLinesTags, connBeg, connEnd);
                connBeg = new PointF(connBeg.X, connEnd.Y + 2 * BASE_UNIT);
                connEnd = new PointF(connEnd.X, connBeg.Y);
                m_shapeEdit.CreateLine(connLinesTags, connBeg, connEnd);
            }
            else
            {
                PointF connEnd = new PointF(m_sarLoc.X + BASE_UNIT, m_sarLoc.Y +
                    BASE_UNIT);
                PointF connBeg = new PointF(x0, connEnd.Y);
                m_shapeEdit.CreateLine(connLinesTags, connBeg, connEnd);
                PointF termLoc = new PointF(connBeg.X - BASE_UNIT, connBeg.Y);
                termName = POSITIVE_INPUT_VOLTAGE_TERMINAL_NAME_BASE + "0";
                m_termEdit.TerminalAdd(termName, CyCompDevTermDir.INOUT, CyCompDevTermType.ANALOG, termLoc,
                    string.Empty, 0f, false);
                m_termEdit.SetMustConnectIfVisible(termName, true);
                m_termEdit.SetIsBurriedPin(termName, false);
                if (m_params.m_channelsConfTable.m_channelsConfigTable.Count > 1)
                {
                    m_symbolHasSingleEndedInputChannel =
                        m_params.m_channelsConfTable.m_channelsConfigTable[1].m_mode == CyEMode.Single;
                }
                connBeg = new PointF(m_symbolHasSingleEndedInputChannel ? x0_se : x0, connBeg.Y + 2 *
                    BASE_UNIT);
                connEnd = new PointF(connEnd.X, connBeg.Y);
                if (m_symbolHasSingleEndedInputChannel)
                {
                    singleEndedPoint1 = connEnd;
                    singleEndedPoint2 = connBeg;
                    singleEndedPoint3 = new PointF(singleEndedPoint2.X, singleEndedPoint2.Y + 3 *
                        BASE_UNIT);
                }
                else
                {
                    termLoc = new PointF(connBeg.X - BASE_UNIT, connBeg.Y);
                    termName = NEGATIVE_INPUT_VOLTAGE_TERMINAL_NAME_BASE + "0";
                    m_termEdit.TerminalAdd(termName, CyCompDevTermDir.INOUT, CyCompDevTermType.ANALOG, termLoc,
                        string.Empty, 0f, false);
                    m_termEdit.SetMustConnectIfVisible(termName, true);
                    m_termEdit.SetIsBurriedPin(termName, false);
                }
                m_shapeEdit.CreateLine(connLinesTags, connBeg, connEnd);

                m_bodySize.Height += BASE_UNIT;
            }

            // Create single ended negative input
            if (m_symbolHasSingleEndedInputChannel)
            {
                List<PointF> points = new List<PointF>(
                    new PointF[] { singleEndedPoint1, singleEndedPoint2, singleEndedPoint3 });
                if (m_params.SingleEndedNegativeInput == CyESingleEndedNegativeInput.Other)
                {
                    points.Add(new PointF(singleEndedPoint3.X - 2 * BASE_UNIT, singleEndedPoint3.Y));
                }
                m_shapeEdit.CreatePolyline(new string[] { SINGLE_ENDED_LINE_SHAPE_NAME }, points);
                CreateSingleEndedNegativeInput(singleEndedPoint3);
                m_shapeEdit.SetOutlineColor(SINGLE_ENDED_LINE_SHAPE_NAME, CONNECTION_COLOR);
                m_shapeEdit.SetOutlineWidth(SINGLE_ENDED_LINE_SHAPE_NAME, CONNECTION_LINE_WIDTH);
                m_shapeEdit.SendToBack(SINGLE_ENDED_LINE_SHAPE_NAME);
            }

            m_shapeEdit.SetFillColor(CONN_LINES_NAME, CONNECTION_COLOR);
            m_shapeEdit.SetOutlineColor(CONN_LINES_NAME, CONNECTION_COLOR);
            m_shapeEdit.SetOutlineWidth(CONN_LINES_NAME, CONNECTION_LINE_WIDTH);

            m_shapeEdit.SendToBack(CONN_LINES_NAME);

            return CyCustErr.OK;
        }

        private CyCustErr CreateSingleEndedNegativeInput(PointF location)
        {
            StringFormat fmt = new StringFormat();
            fmt.Alignment = StringAlignment.Near;
            fmt.LineAlignment = StringAlignment.Near;

            if (m_params.SingleEndedNegativeInput == CyESingleEndedNegativeInput.Vss ||
                m_params.SingleEndedNegativeInput == CyESingleEndedNegativeInput.Vref)
            {
                PointF left = new PointF(location.X - BASE_UNIT, location.Y);
                PointF right = new PointF(location.X + BASE_UNIT, location.Y);

                PointF loc = new PointF();
                string text = string.Empty;

                if (m_params.SingleEndedNegativeInput == CyESingleEndedNegativeInput.Vss)
                {
                    PointF bottom = new PointF(location.X, location.Y + BASE_UNIT);
                    m_shapeEdit.CreatePolyline(new string[] { SINGLE_ENDED_REF_SHAPE_NAME }, left, right, bottom, left,
                        right);
                    m_shapeEdit.SetOutlineWidth(SINGLE_ENDED_REF_SHAPE_NAME, INNER_BLOCK_LINE_WIDTH);
                    m_shapeEdit.SetFillColor(SINGLE_ENDED_REF_SHAPE_NAME, VSS_FILL_COLOR);
                    m_shapeEdit.SetOutlineWidth(SINGLE_ENDED_REF_SHAPE_NAME, CONNECTION_LINE_WIDTH);

                    loc = new PointF(m_bodyLocation.X, bottom.Y);
                    text = VSS_TEXT;
                }
                else if (m_params.SingleEndedNegativeInput == CyESingleEndedNegativeInput.Vref)
                {
                    m_shapeEdit.CreateLine(new string[] { SINGLE_ENDED_REF_SHAPE_NAME }, left, right);
                    m_shapeEdit.SetOutlineWidth(SINGLE_ENDED_REF_SHAPE_NAME, VREF_SHAPE_LINE_WIDTH);

                    loc = new PointF(m_bodyLocation.X, left.Y);
                    text = VREF_TEXT;
                }

                // Create text
                m_shapeEdit.CreateAnnotation(new string[] { SINGLE_ENDED_REF_TEXT_NAME }, text, loc, ANNOTATIONS_FONT,
                    fmt);
                m_shapeEdit.SetFillColor(SINGLE_ENDED_REF_TEXT_NAME, CONNECTION_COLOR);
                m_shapeEdit.SetOutlineColor(SINGLE_ENDED_REF_TEXT_NAME, CONNECTION_COLOR);
                m_shapeEdit.ClearOutline(SINGLE_ENDED_REF_TEXT_NAME);
            }
            else
            {
                PointF to = new PointF(location.X - 2 * BASE_UNIT, location.Y);
                m_shapeEdit.CreateAnnotation(new string[] { ANNOTATIONS_NAME }, VNEG_TEXT, to, ANNOTATIONS_FONT, fmt);
                m_shapeEdit.SetFillColor(ANNOTATIONS_NAME, ANNOTATION_COLOR);
                m_shapeEdit.ClearOutline(ANNOTATIONS_NAME);
                PointF termLoc = new PointF(to.X - BASE_UNIT, to.Y);
                m_termEdit.TerminalAdd(VNEG_TERMINAL_NAME, CyCompDevTermDir.INOUT, CyCompDevTermType.ANALOG, termLoc,
                    string.Empty, 0f, false);
                m_termEdit.SetMustConnectIfVisible(VNEG_TERMINAL_NAME, true);
                m_termEdit.SetIsBurriedPin(VNEG_TERMINAL_NAME, false);
            }

            m_shapeEdit.SetOutlineColor(SINGLE_ENDED_REF_SHAPE_NAME, CONNECTION_COLOR);

            m_bodySize.Height += (m_params.SingleEndedNegativeInput == CyESingleEndedNegativeInput.Vss ? 2 : 1) *
                BASE_UNIT;

            return CyCustErr.OK;
        }
        #endregion

        #region Remove shapes
        private void RemoveShapes()
        {
            // Remove all inputVoltage terminals
            List<string> termNames = new List<string>(m_termEdit.GetTerminalNames());
            foreach (string termName in termNames)
            {
                if (termName.StartsWith(INPUT_VOLTAGE_TERMINAL_NAME_BASE))
                {
                    m_termEdit.TerminalDelete(termName);
                }
            }

            // Remove shapes
            foreach (string shapeTag in SHAPES_TO_REMOVE)
            {
                m_shapeEdit.ShapesRemove(shapeTag);
            }
        }
        #endregion

        #region Auxiliary methods
        private void CreateAnnotation(string text, PointF loc)
        {
            StringFormat fmt = new StringFormat();
            fmt.Alignment = StringAlignment.Near;
            fmt.LineAlignment = StringAlignment.Near;
            m_shapeEdit.CreateAnnotation(new string[] { ANNOTATIONS_NAME }, text, loc, ANNOTATIONS_FONT, fmt);
            m_shapeEdit.SetFillColor(ANNOTATIONS_NAME, ANNOTATION_COLOR);
        }
        #endregion
    }
}
