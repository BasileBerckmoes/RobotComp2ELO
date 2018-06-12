/*******************************************************************************
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics.CodeAnalysis;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
using System.Diagnostics;
using System.Linq;
using System.Text.RegularExpressions;
using System.IO;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using CyDesigner.Toolkit.TerminalControl_v1;
using CyTerminalControl_v1 = CyDesigner.Toolkit.TerminalControl_v1.CyTerminalControl_v1;

// Allow unit tests to run
[assembly: System.Runtime.CompilerServices.InternalsVisibleTo("GPIO_PDL_v1_0_Test")]

namespace Cypress.Comps.PinsAndPorts.GPIO_PDL_v1_0
{
    public class CyCustomizer : 
        ICyShapeCustomize_v2,
        ICyParamEditHook_v1,
        ICyVerilogCustomize_v1,
        ICyInstValidateHook_v1,
        ICyPinDataProvider_v5,
        ICyToolTipCustomize_v1,
        ICyDesignClient_v2
    {
        public readonly string BUILTIN_TAB_NAME = Resource1.BuiltIn;
        public readonly string CONFIGURE_TAB_NAME = Resource1.Configure;
        public readonly string PINS_TAB_NAME = Resource1.Pins;

        const string PIN_COMP_NAME = "cy_mxs40_gpio_v1_0";

        #region ICyParamEditHook_v1 Members

        [ExcludeFromCodeCoverage]
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            editor.UseBigEditor = true;
            CyErrorManager errMgr = new CyErrorManager();
            CyDeviceSupport deviceSupport = new CyDeviceSupport(edit.DeviceQuery);

            CyPinData pinData = new CyPinData(edit, errMgr);
            CyPinsControl pinsControl = new CyPinsControl(deviceSupport, errMgr, pinData);

            CyParamExprDelegate UpdateGUIFromExprViewChanging = (ICyParamEditor custEditor, CyCompDevParam param) =>
                {
                    pinsControl.UpdateData();
                };

            editor.ParamExprCommittedDelegate = (ICyParamEditor custEditor, CyCompDevParam param) =>
                {
                    if (param.TabName != CONFIGURE_TAB_NAME)
                    {
                        //Update the tree if a param on another tab changed. Examples: inst name needs to regenerate
                        //tree node names, layout mode changing can change errors with the per pin data, ...
                        pinsControl.UpdateData();
                    }
                };

            editor.AddCustomPage(PINS_TAB_NAME, pinsControl, UpdateGUIFromExprViewChanging, CONFIGURE_TAB_NAME);
            editor.AddDefaultPage(BUILTIN_TAB_NAME, BUILTIN_TAB_NAME);
            pinData.Validate();
            return editor.ShowDialog();
        }

        [ExcludeFromCodeCoverage]
        public bool EditParamsOnDrop
        {
            get { return false; }
        }

        [ExcludeFromCodeCoverage]
        public CyCompDevParamEditorMode GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }

        #endregion

        //-----------------------------

        #region ICyShapeCustomize_v2 Members

        [ExcludeFromCodeCoverage]
        public CyCustErr CustomizeShapes(ICyShapeCustomizeArgs_v1 args)
        {
            ICyInstQuery_v1 query = args.InstQuery;
            ICySymbolShapeEdit_v2 shapeEdit = args.ShapeEdit;
            ICyTerminalEdit_v2 termEdit = args.TermEdit;

            //The entire symbol is drawn here. 
            //In the special case where the width is one, no IRQ is used, and only one side has terminals on it 
            //we draw as small as possible and put the instance name on the opposite side as the terminals. 
            CyPinData pins = new CyPinData(query);
            CyPinsDrawer drawer = new CyPinsDrawer(query, shapeEdit, termEdit);

            byte numPins = pins.PinCount;
            bool displayAsBus = pins.DisplayAsBus;
            bool hasSameConnections = pins.HasSameConnections;

            CyCustErr err = displayAsBus && hasSameConnections
                ? drawer.DrawAsBus(true, numPins, pins)
                : drawer.DrawAsIndividualTerminals(hasSameConnections, pins);
            return err.IsNotOk ? err : CyCustErr.Ok;
        }

        [ExcludeFromCodeCoverage]
        class CyPinsDrawer
        {
            #region Data

            readonly ICyInstQuery_v1 m_query;
            readonly ICySymbolShapeEdit_v2 m_shapeEdit;
            readonly ICyTerminalEdit_v2 m_termEdit;

            const int ParameterTextSize = 8;
            const int DecorativeTextSize = 6;
            const int IndexTextSize = 4;
            const int OtherTextSize = 10;
            const float THIN_LINE_WIDTH = 0.25f;

            const string PinBodyTag = "PinBodyTag";
            readonly string[] PinBodyTags = new string[] { PinBodyTag };
            readonly Color PinBodyFillColor = Color.White;
            readonly Color PinBodyOutlineColor = Color.Gray;

            const string PinXTag = "PinXTag";
            readonly string[] PinXTags = new string[] { PinXTag };

            const string TextTag = "TextTag";
            readonly string[] TextTags = new string[] { TextTag };
            readonly Color TextFillColor = Color.Black;

            const string IndexTag = "IndexTag";
            readonly string[] IndexTags = new string[] { IndexTag };
            readonly Color IndexFillColor = Color.Black;

            internal const string AssignmentTag = "AssignmentTag";
            readonly string[] AssignmentTags = new string[] { AssignmentTag };

            const string DigitalTag = "DigitalTag";
            readonly string[] DigitalTags = new string[] { DigitalTag };
            readonly Color DigitalOutlineColor;

            const string AnalogTag = "AnalogTag";
            readonly string[] AnalogTags = new string[] { AnalogTag };
            readonly Color AnalogOutlineColor;

            const string AnnotationTag = "AnnotationTag";
            readonly string[] AnnotationTags = new string[] { AnnotationTag };
            readonly Color AnnotationOutlineColor;

            const string ArrowLineTag = "ArrowLinesTag";
            readonly string[] ArrowLineTags = new string[] { ArrowLineTag };

            const string ArrowTag = "ArrowTag";
            readonly string[] ArrowTags = new string[] { ArrowTag };

            const string SIOTag = "SIOTag";
            readonly string[] SIOTags = new string[] { SIOTag };

            static string GetTerminalName(string rootName, int index, int width)
            {
                return width == 1
                           ? string.Format("{0}_{1}", rootName, index)
                           : string.Format("{0}_{1}[{2}:0]", rootName, index, width - 1);
            }

            RectangleF GetPinBodyBounds(PointF reservedLoc)
            {
                float quarterUnit = 0.25f * BaseUnit;
                float size = 1.5f * BaseUnit;

                return new RectangleF(reservedLoc.X + quarterUnit, reservedLoc.Y + quarterUnit, size, size);
            }

            readonly float TopYDelta;
            readonly float BottomYDelta;
            readonly float SingleReservedSize;
            readonly float SIOBorderInflation;
            readonly Color TitleColor = Color.FromArgb(255, 192, 203); //From YFS159

            private float BaseUnit { get { return m_shapeEdit.UserBaseUnit; } }

            #endregion

            #region Constructors/Destructor

            public CyPinsDrawer(ICyInstQuery_v1 query, ICySymbolShapeEdit_v2 shapeEdit, ICyTerminalEdit_v2 termEdit)
            {
                m_query = query;
                m_shapeEdit = shapeEdit;
                m_termEdit = termEdit;
                TopYDelta = BaseUnit;
                BottomYDelta = 3 * TopYDelta;
                SingleReservedSize = 2 * BaseUnit;
                SIOBorderInflation = BaseUnit * 0.15f;

                DigitalOutlineColor = m_query.Preferences.DigitalWireColor;
                AnalogOutlineColor = m_query.Preferences.AnalogWireColor;
                AnnotationOutlineColor = m_query.Preferences.AnnotationWireColor;
            }

            #endregion

            #region Drawing Methods

            /// <summary>
            /// Removes all terminals and shapes from the component.
            /// </summary>
            /// <returns></returns>
            CyCustErr Clear()
            {
                CyCustErr err = m_termEdit.RemoveAllTerminals();
                if (err.IsNotOk) return err;

                err = m_shapeEdit.RemoveAllShapes();
                return err.IsNotOk ? err : CyCustErr.Ok;
            }

            /// <summary>
            /// Used to center the first pin on (0,0).
            /// </summary>
            float XOffset { get { return SingleReservedSize / 2; } }
            float YOffset { get { return SingleReservedSize / 2; } }

            public CyCustErr DrawAsIndividualTerminals(bool hasSameConnections, CyPinData pins)
            {
                CyCustErr err = Clear();
                if (err.IsNotOk) return err;

                bool drawAsSinglePin = GetDrawAsSinglePin(hasSameConnections, false, pins.PinCount, pins[0]);

                float x = -XOffset;
                float y = -YOffset;
                for (int index = 0; index < pins.PinCount; index++)
                {
                    CyPinTypeData pinTypeData = new CyPinTypeData(pins[index]);

                    PointF reservedLoc = new PointF(x, y);
                    y += SingleReservedSize * pinTypeData.NumTerminalsTall;
                    int sioGroupIndex = pins.GetSioGroupIndex(index);
                    err = DrawPin(reservedLoc, pinTypeData, index, drawAsSinglePin, 1, 1, true,
                        sioGroupIndex, pins.GetAssignment(index));
                    if (err.IsNotOk) return err;
                }

                UpdateZOrders();

                if (!drawAsSinglePin)
                    DrawOuterComponent(y + YOffset);

                return CyCustErr.Ok;
            }

            private void UpdateZOrders()
            {
                //Ensures that the analog wires draw below the sio border and the digital inputs (if used).
                m_shapeEdit.SendToBack(SIOTag);
                m_shapeEdit.SendToBack(AnalogTag);
            }

            public CyCustErr DrawAsBus(bool hasSameConnections, byte width, CyPinData pins)
            {
                CyCustErr err = Clear();
                if (err.IsNotOk) return err;

                bool drawAsSinglePin = GetDrawAsSinglePin(hasSameConnections, true, width, pins[0]);

                CyPinTypeData pinTypeData = (pins.PinCount > 1)
                    ? new CyPinTypeData(pins[0], pins[1])
                    : new CyPinTypeData(pins[0]);

                PointF reservedLoc = new PointF(-XOffset, -YOffset);
                int sioGroupCnt = pins.GetSioGroupIndex(pins.PinCount - 1) + 1;
                int sioGroupIndex = pins.GetSioGroupIndex(0);
                err = DrawPin(reservedLoc, pinTypeData, width - 1, drawAsSinglePin, width,
                    sioGroupCnt, false, sioGroupIndex, pins.GetAssignment(0));
                if (err.IsNotOk) return err;

                UpdateZOrders();

                if (!drawAsSinglePin) DrawOuterComponent(pinTypeData.NumTerminalsTall * SingleReservedSize);

                return CyCustErr.Ok;
            }

            CyCustErr DrawOuterComponent(float height)
            {
                //This should only be called if not drawAsSinglePin.
                //Draw a box around the component, draw the inst name, and check if the irq terminal needs to be
                //added.

                float compBodyWidth = 3 * SingleReservedSize;
                float compBodyHeight = Math.Abs(height);
                PointF loc = new PointF(-3 * XOffset, -YOffset);

                // Body box
                const string compBodyTag = "CompBodyTag";
                const int BODY_LINE_WIDTH = 1;
                string[] compBodyTags = new string[] { compBodyTag };
                m_shapeEdit.CreateRectangle(compBodyTags, loc, compBodyWidth, compBodyHeight, LineJoin.Miter,
                    Color.FromArgb(220, 220, 220), Color.Black, BODY_LINE_WIDTH);
                m_shapeEdit.SendToBack(compBodyTag);

                // Title box
                const string compTitleTag = "CompTitleTag";
                string[] compTitleTags = new string[] { compTitleTag };
                m_shapeEdit.CreateRectangle(compTitleTags, new PointF(loc.X, loc.Y - 2 * BaseUnit),
                    compBodyWidth, 2 * BaseUnit, LineJoin.Miter, TitleColor, Color.Black, BODY_LINE_WIDTH);
                m_shapeEdit.SendToBack(compTitleTag);

                PointF center = new PointF(loc.X + compBodyWidth / 2, loc.Y - BaseUnit); 
                StringFormat titleFmt = new StringFormat();
                titleFmt.LineAlignment = StringAlignment.Center;
                titleFmt.Alignment = StringAlignment.Center;
                m_shapeEdit.CreateAnnotation(TextTags, "Pins", center,
                    new Font(FontFamily.GenericSansSerif, OtherTextSize, FontStyle.Regular), titleFmt, TextFillColor);

                StringFormat fmt = new StringFormat();
                fmt.LineAlignment = StringAlignment.Far;
                fmt.Alignment = StringAlignment.Far;
                DrawInstanceName(new PointF(loc.X + compBodyWidth, loc.Y - SingleReservedSize), fmt);

                return CyCustErr.Ok;
            }

            private void DrawClkBoxInTerm(string name, string dispName, PointF baseLoc, int offset)
            {
                PointF termLoc = new PointF(baseLoc.X - BaseUnit, baseLoc.Y - offset*BaseUnit);
                m_termEdit.TerminalAdd(name + "_0", CyCompDevTermDir.INPUT, CyCompDevTermType.DIGITAL, termLoc,
                                       string.Empty, 0, false);

                StringFormat fmt = new StringFormat();
                fmt.LineAlignment = StringAlignment.Center;
                fmt.Alignment = StringAlignment.Near;
                m_shapeEdit.CreateAnnotation(TextTags, dispName, new PointF(baseLoc.X, baseLoc.Y - offset*BaseUnit),
                    new Font(FontFamily.GenericSansSerif, ParameterTextSize, FontStyle.Regular), fmt, TextFillColor);
            }

            /// <summary>
            /// If true there is no component box drawn around the pin and the name is drawn to one side instead
            /// of above the component.
            /// </summary>
            static bool GetDrawAsSinglePin(bool hasSameConnections, bool drawAsBus, int width, CyPinData.PerPin pin)
            {
                bool drawAsSinglePin = false;

                if (width == 1 || hasSameConnections && drawAsBus)
                {
                    CyPinTypeData pinTypeData = new CyPinTypeData(pin);
                    drawAsSinglePin = pinTypeData.OnlyOneSideUsed;
                }

                return drawAsSinglePin;
            }

            private CyCustErr DrawPin(PointF reservedLoc, CyPinTypeData pinTypeData, int indexOfLeftMostBit,
                bool drawAsSinglePin, int width, int sioWidth, bool showIndex, int sioGroupIndex,
                CyPinAssignmentInfo_v1 assignment)
            {
                CyCustErr err;

                bool annotationClobbersName = false;
                if (pinTypeData.ShowAnnotation)
                {
                    err = CalculateAndDrawAnnotation(reservedLoc, pinTypeData, indexOfLeftMostBit, width, out annotationClobbersName);
                    if (err.IsNotOk) return err;
                }

                if (pinTypeData.SIOVRefUsed)
                {
                    err = DrawSIOVRef(reservedLoc, sioGroupIndex, sioWidth);
                    if (err.IsNotOk) return err;
                }
                if (pinTypeData.BidirectionalUsed)
                {
                    err = DrawBidirectional(reservedLoc, indexOfLeftMostBit, width);
                    if (err.IsNotOk) return err;
                }
                if (pinTypeData.AnalogUsed)
                {
                    err = DrawAnalog(reservedLoc, pinTypeData.DigitalInputUsed, pinTypeData.DigitalInputHw, indexOfLeftMostBit, width);
                    if (err.IsNotOk) return err;
                }
                if (pinTypeData.DigitalInputUsed && pinTypeData.DigitalInputHw)
                {
                    err = DrawDigitalInput(reservedLoc, indexOfLeftMostBit, width, pinTypeData.DigitalInputHw);
                    if (err.IsNotOk) return err;
                }
                if (pinTypeData.OutputEnableUsed)
                {
                    //The output enable width is always one. If drawn individually then it should be one.
                    //If drawn as bus then only one is displayed and replicated for all the signals.
                    err = DrawOutputEnable(reservedLoc, indexOfLeftMostBit, 1);
                    if (err.IsNotOk) return err;
                }
                if (pinTypeData.DigitalOutputUsed)
                {
                    // We need to draw the buffer even with a SW output if the OE is used
                    if (pinTypeData.DigitalOutputHw || pinTypeData.OutputEnableUsed)
                    {
                        err = DrawDigitalOutput(reservedLoc, indexOfLeftMostBit, width, pinTypeData.DigitalOutputHw);
                        if (err.IsNotOk) return err;
                    }
                }

                bool showAssignment = (showIndex && assignment != null && assignment.IsLocked);
                RectangleF bodyBounds = DrawPinBody(reservedLoc, !showAssignment);
                if (drawAsSinglePin)
                {
                    DrawInstanceName(pinTypeData.LeftSideUsed, reservedLoc, annotationClobbersName);
                }
                if (showAssignment)
                {
                    DrawAssignmentInPinBody(bodyBounds, assignment);
                }
                else if (showIndex)
                {
                    //This index is displayed for all pins that represent a single pin (i.e. not bus)
                    DrawIndexInPinBody(bodyBounds, indexOfLeftMostBit);
                }

                return DrawSIOBorder(pinTypeData, bodyBounds);
            }

            private CyCustErr CalculateAndDrawAnnotation(PointF reservedLoc, CyPinTypeData pinTypeData, int indexOfLeftMostBit, int width, out bool annotationClobbersName)
            {
                int numTermsOnLeft = 0;
                int numTermsOnRight = 0;

                if (pinTypeData.AnalogUsed)
                    numTermsOnRight++;
                if (pinTypeData.BidirectionalUsed)
                    numTermsOnLeft++;
                if (pinTypeData.DigitalInputUsed)
                {
                    numTermsOnRight++;
                    if (pinTypeData.SIOVRefUsed)
                        numTermsOnRight++;
                }
                if (pinTypeData.DigitalOutputUsed)
                    numTermsOnLeft++;
                if (pinTypeData.OutputEnableUsed)
                    numTermsOnLeft++;

                bool termIsOnLeft = (numTermsOnLeft <= numTermsOnRight);
                int termRow = termIsOnLeft ? numTermsOnLeft : numTermsOnRight;
                annotationClobbersName = (termRow == 0);

                return DrawAnnotation(reservedLoc, indexOfLeftMostBit, width, termRow, termIsOnLeft, pinTypeData.SIOVRefUsed);
            }

            RectangleF m_sioFirstBounds = RectangleF.Empty;
            private CyCustErr DrawSIOBorder(CyPinTypeData pinTypeData, RectangleF bodyBounds)
            {
                if (pinTypeData.IsSIO)
                {
                    RectangleF sioBounds = bodyBounds;
                    sioBounds.Inflate(SIOBorderInflation, SIOBorderInflation);

                    if (pinTypeData.SioPair_1of2)
                    {
                        m_sioFirstBounds = sioBounds;
                    }
                    else
                    {
                        if (pinTypeData.SioPair_2of2)
                        {
                            Debug.Assert(!m_sioFirstBounds.IsEmpty);
                            sioBounds = RectangleF.Union(sioBounds, m_sioFirstBounds);
                            m_sioFirstBounds = RectangleF.Empty;
                        }

                        m_shapeEdit.CreateRectangle(SIOTags, sioBounds.Location, sioBounds.Width,
                           sioBounds.Height, LineJoin.Miter, TitleColor, Color.Black, THIN_LINE_WIDTH);
                    }
                }

                return CyCustErr.Ok;
            }

            private CyCustErr DrawSIOVRef(PointF reservedLoc, int index, int width)
            {
                /*
                 * -------------|
                 * |  --------  |
                 * |  |      |  |
                 * |  |      |  |
                 * |  |      |  |
                 * |  --------  |
                 * --------------
                 *      start
                 *        |
                 *        |
                 *      middle-----------end
                 */

                RectangleF pinBodyBounds = GetPinBodyBounds(reservedLoc);

                PointF start = new PointF(pinBodyBounds.Left + pinBodyBounds.Width / 2,
                    pinBodyBounds.Bottom + SIOBorderInflation);
                PointF middle = new PointF(start.X, reservedLoc.Y + BottomYDelta);
                PointF end = new PointF(reservedLoc.X + 2.5f * SingleReservedSize - BaseUnit, middle.Y);

                CyCustErr err = m_shapeEdit.CreatePolyline(
                    AnalogTags, AnalogOutlineColor, m_query.Preferences.WireSize, LineJoin.Miter, start, middle, end);
                if (err.IsNotOk) return err;

                //Add Terminal
                string termCanName = GetTerminalName(CyRootTerm.Name.SIOVRef, index, width);
                err = m_termEdit.TerminalAdd(
                    termCanName, CyCompDevTermDir.INOUT,
                    CyCompDevTermType.ANALOG, new PointF(end.X + BaseUnit, end.Y), string.Empty,
                    180, false);
                if (err.IsNotOk) return err;

                // Invalid to have an external vref and leave it unconnected
                m_termEdit.SetMustConnectIfVisible(termCanName, true);

                if (width > 1)
                    AddTermWidthLabel(new PointF(end.X + BaseUnit / 2, end.Y), width);

                return CyCustErr.Ok;
            }

            private CyCustErr DrawDigitalOutput(PointF reservedLoc, int index, int width, bool outputHw)
            {
                /*                          _________
                 *                          |       |
                 *   start---------------end|       |
                 *                          |       |
                 *                          ---------
                 */

                RectangleF pinBodyBounds = GetPinBodyBounds(reservedLoc);

                PointF start = new PointF(reservedLoc.X - 1.5f * SingleReservedSize,
                                          reservedLoc.Y + TopYDelta);

                PointF end = new PointF(pinBodyBounds.Left, start.Y);

                float arrowLeftX = start.X + SingleReservedSize;
                float arrowRightX = arrowLeftX + BaseUnit / 2;
                float halfArrow = (arrowRightX - arrowLeftX) / 2;

                // If the terminal is not drawn, only draw the line to the right of the "buffer" arrow,
                // to clearly distinguish from a hardware connection
                CyCustErr err = m_shapeEdit.CreateLine(DigitalTags,
                    outputHw
                       ? new PointF(start.X + BaseUnit, start.Y)
                       : new PointF(arrowRightX, start.Y),
                    new PointF(end.X + BaseUnit * .25f, end.Y),
                    DigitalOutlineColor, m_query.Preferences.WireSize);
                if (err.IsNotOk) return err;


                err = m_shapeEdit.CreatePolygon(
                    ArrowLineTags, PinBodyFillColor, PinBodyOutlineColor, THIN_LINE_WIDTH, LineJoin.Miter,
                    new PointF(arrowRightX, end.Y),
                    new PointF(arrowLeftX, end.Y + halfArrow),
                    new PointF(arrowLeftX, end.Y - halfArrow));
                if (err.IsNotOk) return err;

                PointF labelPos = new PointF(start.X + BaseUnit / 2, start.Y);
                if (outputHw)
                {
                    err = m_termEdit.TerminalAdd(GetTerminalName(CyRootTerm.Name.Output, index, width),
                        CyCompDevTermDir.INPUT, CyCompDevTermType.DIGITAL,
                        new PointF(start.X, start.Y), string.Empty, 0, false);
                    if (err.IsNotOk) return err;
                }

                if (width > 1)
                {
                    AddTermWidthLabel(labelPos, width);
                }

                return CyCustErr.Ok;
            }

            private CyCustErr DrawOutputEnable(PointF reservedLoc, int index, int width)
            {
                /*                 _________
                 *         start   |       | 
                 *         |       |       |
                 *   end--- middle |       |
                 *                 |       |
                 *                 ---------    
                 */

                RectangleF pinBodyBounds = GetPinBodyBounds(reservedLoc);

                PointF start = new PointF(reservedLoc.X - 0.25f * SingleReservedSize - 0.25f * BaseUnit,
                    reservedLoc.Y + TopYDelta);
                PointF middle = new PointF(start.X, reservedLoc.Y + BottomYDelta);
                PointF end = new PointF(reservedLoc.X - 1.5f * SingleReservedSize + BaseUnit, middle.Y);

                CyCustErr err = m_shapeEdit.CreatePolyline(DigitalTags, 
                    DigitalOutlineColor, m_query.Preferences.WireSize, LineJoin.Miter, start, middle, end);
                if (err.IsNotOk) return err;

                err = m_termEdit.TerminalAdd(GetTerminalName(CyRootTerm.Name.OE, index, width),
                    CyCompDevTermDir.INPUT, CyCompDevTermType.DIGITAL,
                    new PointF(end.X - BaseUnit, end.Y), string.Empty, 0, false);
                if (err.IsNotOk) return err;

                if (width > 1)
                {
                    AddTermWidthLabel(new PointF(end.X - BaseUnit / 2, end.Y), width);
                }

                return CyCustErr.Ok;
            }

            private CyCustErr DrawDigitalInput(PointF reservedLoc, int index, int width, bool inputHw)
            {
                /*   _________
                 *   |       |
                 *   |       |start---------------end
                 *   |       |
                 *   ---------
                 */

                CyCustErr err;
                RectangleF pinBodyBounds = GetPinBodyBounds(reservedLoc);
                PointF start = new PointF(pinBodyBounds.Right, reservedLoc.Y + TopYDelta);
                PointF end = new PointF(reservedLoc.X + 2.5f * SingleReservedSize, start.Y);

                float arrowLeftX = end.X - SingleReservedSize;
                float arrowRightX = arrowLeftX + BaseUnit / 2;
                float halfArrow = (arrowRightX - arrowLeftX) / 2;

                err = m_shapeEdit.CreateLine(
                    DigitalTags, start, new PointF(inputHw ? end.X - BaseUnit : arrowLeftX, end.Y),
                    DigitalOutlineColor, m_query.Preferences.WireSize);
                if (err.IsNotOk) return err;

                err = m_shapeEdit.CreatePolygon(
                    ArrowLineTags, PinBodyFillColor, PinBodyOutlineColor, THIN_LINE_WIDTH, LineJoin.Miter,
                    new PointF(arrowRightX, end.Y),
                    new PointF(arrowLeftX, end.Y + halfArrow),
                    new PointF(arrowLeftX, end.Y - halfArrow));
                if (err.IsNotOk) return err;

                PointF labelPos = new PointF(end.X - BaseUnit / 2, end.Y);
                if (inputHw)
                {
                    err = m_termEdit.TerminalAdd(GetTerminalName(CyRootTerm.Name.Input, index, width),
                        CyCompDevTermDir.OUTPUT, CyCompDevTermType.DIGITAL,
                        new PointF(end.X, end.Y), string.Empty, 0, false);
                    if (err.IsNotOk) return err;
                }

                if (width > 1)
                {
                    AddTermWidthLabel(labelPos, width);
                }

                return CyCustErr.Ok;
            }

            private CyCustErr DrawAnalog(PointF reservedLoc, bool digitalInputUsed, bool inputHw, int index, int width)
            {
                PointF end;
                CyCustErr err;
                RectangleF pinBodyBounds = GetPinBodyBounds(reservedLoc);

                if (digitalInputUsed)
                {
                    /*   _________
                     *   |       |
                     *   |       |     start
                     *   |       |         |
                     *   ---------   middle ----------end
                     * 
                     */

                    PointF start = new PointF(pinBodyBounds.Right + BaseUnit * 0.5f,
                        reservedLoc.Y + TopYDelta);
                    PointF middle = new PointF(start.X, reservedLoc.Y + BottomYDelta);
                    end = new PointF(reservedLoc.X + 2.5f * SingleReservedSize - BaseUnit, middle.Y);

                    err = m_shapeEdit.CreatePolyline(AnalogTags, 
                        AnalogOutlineColor, m_query.Preferences.WireSize, LineJoin.Miter, start, middle, end);
                    if (err.IsNotOk) return err;
                    if (!inputHw)
                    {
                        // Also draw a brief analog line segment from the edge of the pin box to where we would have
                        // split off from the digital wire if it existed
                        PointF pinBodyEdge = new PointF(pinBodyBounds.Right, reservedLoc.Y + TopYDelta);
                        err = m_shapeEdit.CreatePolyline(AnalogTags, 
                            AnalogOutlineColor, m_query.Preferences.WireSize, LineJoin.Miter, pinBodyEdge, start);
                        if (err.IsNotOk) return err;
                    }
                }
                else
                {
                    /*   _________
                     *   |       |
                     *   |       |start---------------end
                     *   |       |
                     *   ---------
                     */

                    PointF start = new PointF(pinBodyBounds.Right, reservedLoc.Y + TopYDelta);
                    end = new PointF(reservedLoc.X + 2.5f * SingleReservedSize - BaseUnit, start.Y);

                    err = m_shapeEdit.CreateLine(
                        AnalogTags, start, end, AnalogOutlineColor, m_query.Preferences.WireSize);
                    if (err.IsNotOk) return err;
                }

                //Add Terminal
                err = m_termEdit.TerminalAdd(
                    GetTerminalName(CyRootTerm.Name.Analog, index, width), CyCompDevTermDir.INOUT,
                    CyCompDevTermType.ANALOG,
                    new PointF(end.X + BaseUnit, end.Y), string.Empty, 180, false);
                if (err.IsNotOk) return err;

                if (width > 1)
                {
                    AddTermWidthLabel(new PointF(end.X + BaseUnit / 2, end.Y), width);
                }

                return CyCustErr.Ok;
            }

            private CyCustErr DrawAnnotation(PointF reservedLoc, int index, int width, int termRow, bool termIsOnLeft, bool SIOVrefUsed)
            {
                /*
                 * 
                 *      Annotation terminal can be drawn in several ways, depending on the pin's
                 *      configuration (see CJCU-13).
                 * 
                 *      IN-LINE w/ pin body (termRow == 0)
                 *      -terminal can also be on the right side.
                 *                          _________
                 *                          |       |
                 *   end---------------start|       |
                 *                          |       |
                 *                          ---------
                 *
                 *      DROP-DOWN from pin body (termRow !=0)
                 *      -terminal can also end on right side.
                 *      -terminal can drop down > 1 level if necessary.
                 *      
                 *                          _________
                 *                          |       |
                 *                          |       |
                 *                          |       |
                 *                          ---------
                 *                            start
                 *                              |
                 *                              |
                 *           end-------------middle 
                 * 
                 */

                PointF end;
                CyCustErr err;
                RectangleF pinBodyBounds = GetPinBodyBounds(reservedLoc);

                // determine the location of the end of the terminal
                float endXVal = (termIsOnLeft) ?
                    reservedLoc.X - 1.5f * SingleReservedSize + BaseUnit :
                    reservedLoc.X + 2.5f * SingleReservedSize - BaseUnit;

                if (termRow == 0)   // terminal comes directly off of a side
                {
                    PointF start = new PointF(pinBodyBounds.Left, reservedLoc.Y + TopYDelta);
                    end = new PointF(endXVal, start.Y);
                    err = m_shapeEdit.CreateLine(AnnotationTags, start, end, 
                        AnnotationOutlineColor, m_query.Preferences.WireSize);
                    if (err.IsNotOk) return err;
                }
                else                // terminal comes from bottom of pin, then goes to a side
                {
                    // start y-val depends on whether we have a vref connection
                    float startYVal = (SIOVrefUsed) ?
                        reservedLoc.Y + BottomYDelta :
                        pinBodyBounds.Bottom;
                    PointF start = new PointF(pinBodyBounds.Left + pinBodyBounds.Width / 2, startYVal);
                    PointF middle = new PointF(start.X, pinBodyBounds.Top + pinBodyBounds.Height / 2 + termRow * 2.0f * BaseUnit);
                    end = new PointF(endXVal, middle.Y);

                    err = m_shapeEdit.CreatePolyline(AnnotationTags, 
                        AnnotationOutlineColor, m_query.Preferences.WireSize, LineJoin.Miter, start, middle, end);
                    if (err.IsNotOk) return err;
                }

                //Add Terminal
                err = m_termEdit.TerminalAdd(
                    GetTerminalName(CyRootTerm.Name.Annotation, index, width), CyCompDevTermDir.INOUT,
                    CyCompDevTermType.ANNOTATION,
                    // flip the terminal if (!termIsOnLeft)
                    new PointF(end.X - BaseUnit * (termIsOnLeft ? 1 : -1), end.Y),
                    string.Empty, termIsOnLeft ? 0 : 180, false);
                if (err.IsNotOk) return err;

                if (width > 1)      // pin is a bus
                {
                    bool drawBusWidthNumber = termRow != 0 || (!termIsOnLeft && SIOVrefUsed);
                    if (drawBusWidthNumber)
                        AddTermWidthLabel(new PointF(end.X - BaseUnit * (termIsOnLeft ? 1 : -1) / 2, end.Y), width);
                    else
                        AddTermWidthTick(new PointF(end.X - BaseUnit * (termIsOnLeft ? 1 : -1) / 2, end.Y));
                }

                return CyCustErr.Ok;
            }

            private CyCustErr DrawBidirectional(PointF reservedLoc, int index, int width)
            {
                /*                          _________
                 *                          |       |
                 *   start---------------end|       |
                 *                          |       |
                 *                          ---------
                 */

                RectangleF pinBodyBounds = GetPinBodyBounds(reservedLoc);

                PointF start = new PointF(reservedLoc.X - 1.5f * SingleReservedSize,
                                          reservedLoc.Y + TopYDelta);

                PointF end = new PointF(pinBodyBounds.Left, start.Y);

                //Draw Line to Body
                m_shapeEdit.CreateLine(DigitalTags, new PointF(start.X + BaseUnit, start.Y), end,
                    DigitalOutlineColor, m_query.Preferences.WireSize);

                //Draw Arrows
                float leftX = start.X + 1.5f * BaseUnit;
                float rightX = leftX + BaseUnit;
                float middleX = leftX + (rightX - leftX) / 2;
                float arrowHeight = BaseUnit * .25f;

                m_shapeEdit.CreatePolygon(
                    ArrowLineTags, PinBodyFillColor, PinBodyOutlineColor, THIN_LINE_WIDTH, LineJoin.Miter,
                    new PointF(rightX, start.Y),
                    new PointF(middleX, start.Y + arrowHeight),
                    new PointF(middleX, start.Y - arrowHeight));

                m_shapeEdit.CreatePolygon(
                    ArrowLineTags, PinBodyFillColor, PinBodyOutlineColor, THIN_LINE_WIDTH, LineJoin.Miter,
                    new PointF(leftX, start.Y),
                    new PointF(middleX, start.Y + arrowHeight),
                    new PointF(middleX, start.Y - arrowHeight));

                //Add Terminal
                string termName = GetTerminalName(CyRootTerm.Name.BiDir, index, width);
                m_termEdit.TerminalAdd(termName,
                    CyCompDevTermDir.INOUT, CyCompDevTermType.DIGITAL,
                    new PointF(start.X, start.Y), string.Empty, 0, false);
                CyCustErr err = m_termEdit.SetIsBurriedPin(termName, true);
                if (err.IsNotOk) return err;

                if (width > 1)
                {
                    AddTermWidthLabel(new PointF(start.X + BaseUnit / 2, start.Y), width);
                }

                return CyCustErr.Ok;
            }

            private void AddTermWidthLabel(PointF centerTerm, int width)
            {
                Debug.Assert(width > 1);

                StringFormat fmt = new StringFormat();
                fmt.LineAlignment = StringAlignment.Far;
                fmt.Alignment = StringAlignment.Center;

                string text = width.ToString();
                
                m_shapeEdit.CreateAnnotation(TextTags, text, centerTerm,
                    new Font(FontFamily.GenericSansSerif, DecorativeTextSize, FontStyle.Regular), fmt, TextFillColor);
                AddTermWidthTick(centerTerm);
            }


            private void AddSwLabel(PointF textLoc, int width)
            {
                StringFormat fmt = new StringFormat();
                fmt.LineAlignment = StringAlignment.Far;
                fmt.Alignment = StringAlignment.Far;

                // If width == 1, vertically align the center of the label with the middle of the buffer. Otherwise,
                // align the bottom of the label with the middle of the buffer, so that we can draw the width
                // designation below
                if (width < 2)
                {
                    // .44 chosen by trial and error - due to the way text is padded .5 appears off-center
                    textLoc = new PointF(textLoc.X, textLoc.Y + BaseUnit * .44f); 
                }
                m_shapeEdit.CreateAnnotation(TextTags, "SW", textLoc,
                    new Font(FontFamily.GenericSansSerif, IndexTextSize, FontStyle.Regular), fmt, TextFillColor);
            }

            private void AddTermWidthTick(PointF centerTerm)
            {
                float quarterUnit = BaseUnit / 4;
                m_shapeEdit.CreateLine(new string[] { "WidthLine" },
                    new PointF(centerTerm.X + quarterUnit, centerTerm.Y - quarterUnit),
                    new PointF(centerTerm.X - quarterUnit, centerTerm.Y + quarterUnit));
            }

            private void DrawIndexInPinBody(RectangleF reservedBounds, int index)
            {
                _drawTextInPin(reservedBounds, index.ToString(), IndexTag);
            }

            void _drawTextInPin(RectangleF reservedBounds, string text, string tag)
            {
                StringFormat fmt = new StringFormat();
                fmt.LineAlignment = StringAlignment.Center;
                fmt.Alignment = StringAlignment.Center;

                PointF center = new PointF(
                    reservedBounds.X + reservedBounds.Width / 2,
                    reservedBounds.Y + reservedBounds.Height / 2);

                string uniqueTag = Guid.NewGuid().ToString();
                m_shapeEdit.CreateAnnotation(new string[] { IndexTag, uniqueTag, tag }, text, center,
                    new Font(FontFamily.GenericSansSerif, IndexTextSize, FontStyle.Regular), fmt, IndexFillColor);
                RectangleF bounds = m_shapeEdit.GetShapeBounds(uniqueTag);

                //Adjust the reservedBounds size to ensure we are drawing inside of the box and not on its edges.
                RectangleF backgroundBounds = new RectangleF(
                    Math.Max(bounds.X, reservedBounds.X + .5f),
                    Math.Max(bounds.Y, reservedBounds.Y + .5f),
                    Math.Min(bounds.Width, reservedBounds.Width - 1),
                    Math.Min(bounds.Height, reservedBounds.Height - 1));

                m_shapeEdit.CreateRectangle(new string[] { "background" },
                    backgroundBounds.Location, backgroundBounds.Width, backgroundBounds.Height, 
                    LineJoin.Miter, Color.White);

                m_shapeEdit.BringToFront(uniqueTag);
            }

            private void DrawInstanceName(bool rightSide, PointF reservedLoc, bool isAnnotationWhereNameWas)
            {
                PointF loc;
                StringFormat fmt = new StringFormat();
                fmt.LineAlignment = StringAlignment.Center;

                if (rightSide)
                {
                    loc = new PointF(reservedLoc.X + SingleReservedSize, reservedLoc.Y + TopYDelta);
                    fmt.Alignment = StringAlignment.Near;
                }
                else
                {
                    loc = new PointF(reservedLoc.X, reservedLoc.Y + TopYDelta);
                    fmt.Alignment = StringAlignment.Far;
                }

                if (isAnnotationWhereNameWas)
                {
                    loc.Y -= BaseUnit;
                }

                DrawInstanceName(loc, fmt);
            }

            private void DrawInstanceName(PointF loc, StringFormat fmt)
            {
                m_shapeEdit.CreateAnnotation(TextTags, m_query.InstanceName, loc,
                        new Font(FontFamily.GenericSansSerif, OtherTextSize, FontStyle.Regular), fmt, TextFillColor);
            }

            private RectangleF DrawPinBody(PointF reservedLoc, bool drawX)
            {
                RectangleF pinBodyBounds = GetPinBodyBounds(reservedLoc);

                //Draw Pin Body
                m_shapeEdit.CreateRectangle(PinBodyTags, pinBodyBounds.Location, 
                    pinBodyBounds.Width, pinBodyBounds.Height, LineJoin.Miter,
                    PinBodyFillColor, PinBodyOutlineColor, THIN_LINE_WIDTH);

                //Draw X in Pin Body
                if (drawX)
                {
                    PointF leftTop = new PointF(pinBodyBounds.Left, pinBodyBounds.Top);
                    PointF leftBottom = new PointF(pinBodyBounds.Left, pinBodyBounds.Bottom);
                    PointF rightTop = new PointF(pinBodyBounds.Right, pinBodyBounds.Top);
                    PointF rightBottom = new PointF(pinBodyBounds.Right, pinBodyBounds.Bottom);
                    m_shapeEdit.CreateLine(PinXTags, leftTop, rightBottom, PinBodyOutlineColor, THIN_LINE_WIDTH);
                    m_shapeEdit.CreateLine(PinXTags, rightTop, leftBottom, PinBodyOutlineColor, THIN_LINE_WIDTH);
                }

                return pinBodyBounds;
            }

            private void DrawAssignmentInPinBody(RectangleF reservedBounds, CyPinAssignmentInfo_v1 info)
            {
                Debug.Assert(info != null);
                Debug.Assert(info.IsLocked);
                string assignmentString = string.Format("{0}[{1}]", info.PortNumber, info.PortPinNumber);
                _drawTextInPin(reservedBounds, assignmentString, AssignmentTag);
            }

            #endregion

            #region CyPinTypeData Class

            [ExcludeFromCodeCoverage]
            class CyPinTypeData
            {
                public readonly CyPinData.PerPin Pin;
                public readonly bool AnalogUsed;
                public readonly bool DigitalInputUsed;
                public readonly bool DigitalInputHw;
                public readonly bool DigitalOutputUsed;
                public readonly bool DigitalOutputHw;
                public readonly bool BidirectionalUsed;
                public readonly bool OutputEnableUsed;
                public readonly bool SIOVRefUsed;
                public readonly bool ShowAnnotation;

                public readonly bool IsSIO;
                public readonly bool SioPair_1of2;
                public readonly bool SioPair_2of2;

                public bool RightSideUsed
                {
                    get { return AnalogUsed || DigitalInputUsed || SIOVRefUsed; }
                }

                public bool LeftSideUsed
                {
                    get { return (DigitalOutputUsed || BidirectionalUsed); }
                }

                public bool OnlyOneSideUsed
                {
                    get { return !RightSideUsed || !LeftSideUsed; }
                }

                [ExcludeFromCodeCoverage]
                public int NumTerminalsTall
                {
                    get
                    {
                        int numTermsOnLeft = 0;
                        int numTermsOnRight = 0;

                        if (AnalogUsed)
                            numTermsOnRight++;
                        if (BidirectionalUsed)
                            numTermsOnLeft++;
                        if (DigitalInputUsed)
                        {
                            numTermsOnRight++;
                            if (SIOVRefUsed)
                                numTermsOnRight++;
                        }
                        if (DigitalOutputUsed)
                            numTermsOnLeft++;
                        if (OutputEnableUsed)
                            numTermsOnLeft++;

                        bool annotTermIsOnLeft = (numTermsOnLeft <= numTermsOnRight);

                        if (ShowAnnotation)
                        {
                            if (annotTermIsOnLeft)
                                numTermsOnLeft++;
                            else
                                numTermsOnRight++;
                        }

                        // special case: SIOVRef automatically makes height >=2
                        if (SIOVRefUsed && numTermsOnRight < 2)
                            numTermsOnRight = 2;

                        return Math.Max(numTermsOnLeft, numTermsOnRight);
                    }
                }

                public CyPinTypeData(CyPinData.PerPin pin)
                {
                    Pin = pin;
                    AnalogUsed = pin.Type.Is(CyPinType.Analog);
                    DigitalInputUsed = pin.Type.Is(CyPinType.Digital_In);
                    DigitalInputHw = pin.TypeIsDigitalInputHw;
                    DigitalOutputUsed = pin.Type.Is(CyPinType.Digital_Out);
                    DigitalOutputHw = pin.TypeIsDigitalOutputHw;
                    BidirectionalUsed = pin.Type.Is(CyPinType.Bidirectional);
                    OutputEnableUsed = pin.Type.Is(CyPinType.OE);
                    ShowAnnotation = pin.TypeShowExternalTerm;
                    IsSIO = pin.RequiresSIO;
                    SioPair_1of2 = pin.SioPair_1of2;
                    SioPair_2of2 = pin.SioPair_2of2;
                    SIOVRefUsed = UsesSIOVRef(pin);
                }

                /// <summary>
                /// For SIO, get type data from the second pin of a pair but the digital Hw settings from the first.
                /// </summary>
                /// <param name="pin0">Prefer the Digitial Hw settings of the first of a pair.</param>
                /// <param name="pin1">Prefer the settings of the second of a pair.</param>
                public CyPinTypeData(CyPinData.PerPin pin0, CyPinData.PerPin pin1)
                    // Init from pin[1] if possible, since sio vref displays only for the second sio in the pair
                    : this(pin1)
                {
                    DigitalInputHw = pin0.TypeIsDigitalInputHw;
                    DigitalOutputHw = pin0.TypeIsDigitalOutputHw;
                }

                private bool UsesSIOVRef(CyPinData.PerPin pin)
                {
                    return !pin.SioPair_1of2 && // Second or lone SIO
                           (pin.OutputDriveLevel == CyOutputDriveLevel.Vref ||
                            pin.InputThreshold == CyInputThreshold.Pt5_Vref ||
                            pin.InputThreshold == CyInputThreshold.Vref);
                }
            }

            #endregion
        }

        #endregion

        //-----------------------------

        #region ICyVerilogCustomize_v1 Members

        public CyCustErr CustomizeVerilog(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery, out string codeSnippet)
        {
            //This is needed because it is the only way to get access to query.InstanceIdPath when the value has
            //been correctly calculated and it is the only way to create a valid verilog bit_vector value.
            //It is now also used to combine multiple terminals into a single signal.
            CyCustErr err = CyCustErr.Ok;
            codeSnippet = string.Empty;
            CyVerilogWriter vw = new CyVerilogWriter(PIN_COMP_NAME, query.InstanceName);

            vw.AddGeneric(Warp.Param.Id, "\"" + query.InstanceIdPath + "\"");
            CyPinData pins = new CyPinData(query);
            //Add Generics.
            IDictionary<string, string> generics = Warp.GenerateVerilogGenerics(pins, query.DeviceQuery);
            foreach (KeyValuePair<string, string> generic in generics)
                vw.AddGeneric(generic.Key, generic.Value);

            //Add Ports.
            foreach (string rootTermName in CyRootTerm.TerminalNames)
            {
                byte expectedWidth;
                err = CyRootTerm.GetExpectedTerminalWidth(pins, rootTermName, out expectedWidth);
                if (err.IsNotOk) return err;

                Dictionary<int, string> indexToTerminalNameMapping = GetAssociatedTerminals(rootTermName, termQuery);

                //Don't add an entry for analog terminals if no portion is hooked up
                if (indexToTerminalNameMapping.Count == 0 && CyRootTerm.IsAnalog(rootTermName))
                {
                    if (CyRootTerm.Name.SIOVRef == rootTermName)
                    {
                        string wireName =
                            string.Format("tmp{0}__{1}_net", rootTermName.ToUpper(), query.InstanceName);
                        vw.AddElectrical(wireName, 0, 0);
                        vw.AddPort(rootTermName, wireName);
                    }
                    continue;
                }

                List<string> bits = new List<string>();
                for (int termIndex = expectedWidth - 1; termIndex >= 0; )
                {
                    bool containsMapping = indexToTerminalNameMapping.ContainsKey(termIndex);

                    if (containsMapping)
                    {
                        if (pins.DisplayAsBus && rootTermName == CyRootTerm.Name.OE)
                        {
                            string termName = indexToTerminalNameMapping[termIndex];
                            string value = termQuery.GetTermSigSegName(termName);
                            for (int w = 0; w < expectedWidth; w++)
                                bits.Add(value);
                            int termWidth = termQuery.GetTermWidth(termName) * expectedWidth;
                            termIndex -= termWidth;
                        }
                        else
                        {
                            string termName = indexToTerminalNameMapping[termIndex];
                            string value = termQuery.GetTermSigSegName(termName);
                            bits.Add(value);
                            int termWidth = termQuery.GetTermWidth(termName);
                            termIndex -= termWidth;
                        }

                        continue;
                    }

                    int tempIndex = termIndex + 1;
                    while (!containsMapping && tempIndex >= 0)
                    {
                        tempIndex--;
                        containsMapping = indexToTerminalNameMapping.ContainsKey(tempIndex);
                    }

                    //From i to tempIndex + 1, there is nothing connected.
                    int unhookedWidth = termIndex - tempIndex;

                    if (CyRootTerm.IsOutput(rootTermName))
                    {
                        if (CyRootTerm.Name.OE == rootTermName)
                            bits.Add(string.Format("{0}'b{1}", unhookedWidth, new string('1', unhookedWidth)));
                        else
                            bits.Add(string.Format("{0}'b0", unhookedWidth));
                    }
                    else
                    {
                        string wireName =
                            string.Format("tmp{0}_{1}__{2}_net", rootTermName.ToUpper(), termIndex, query.InstanceName);

                        if (CyRootTerm.IsAnalog(rootTermName))
                            vw.AddElectrical(wireName, unhookedWidth - 1, 0);
                        else
                            vw.AddWire(wireName, unhookedWidth - 1, 0);
                        bits.Add(string.Format("{0}[{1}:0]", wireName, unhookedWidth - 1));
                    }

                    termIndex = tempIndex;
                }

                string assignment = string.Join(", ", bits.ToArray());
                if (!string.IsNullOrEmpty(assignment))
                {
                    string verilogName = (rootTermName == CyRootTerm.Name.Annotation) ? "annotation" : rootTermName;
                    vw.AddPort(verilogName, "{" + assignment + "}");
                }
            }

            codeSnippet = vw.ToString();
            
            return err;
        }

        public static Dictionary<int, string> GetAssociatedTerminals(string portTermBaseName,
            ICyTerminalQuery_v1 termQuery)
        {
            //Key: index of the terminal when combined into a bus, Value: the associated terminal name
            Dictionary<int, string> termsInDescendingOrder = new Dictionary<int, string>();

            //Match portTermBaseName_# and portTermBaseName_#[#:#]
            Regex regex = new Regex("^" + portTermBaseName + @"_(?<Index>\d+)(\[\d+:\d+\])?$");

            foreach (string term in termQuery.GetTerminalNames())
            {
                //Collect all terminals with a name formatted as 'TermName_#'.
                Match m = regex.Match(term);
                if (m.Success)
                {
                    Debug.Assert(m.Value == term);
                    int index = int.Parse(m.Groups["Index"].Value);
                    termsInDescendingOrder.Add(index, term);
                }
            }

            return termsInDescendingOrder;
        }

        #endregion

        //-----------------------------

        #region ICyInstValidateHook_v1 Members

        public void ValidateParams(ICyInstValidate_v1 instVal)
        {
            CyPinData pins = new CyPinData(instVal);
            pins.Validate(instVal);
        }

        #endregion

        //-----------------------------

        #region ICyPinDataProvider_v5 Members

        public CyCustErr GetWidth(ICyInstQuery_v1 instQuery, out byte width)
        {
            CyPinData pins = new CyPinData(instQuery);
            width = (byte)pins.PinCount;
            return CyCustErr.Ok;
        }

        public CyCustErr GetContiguousSegments(ICyInstQuery_v1 instQuery,
            out IEnumerable<KeyValuePair<int, int>> contiguousSegments)
        {
            //Segments can be grouped one of 2 ways, either by being contiguous or by being in an SIO pair.
            CyPinData pins = new CyPinData(instQuery);

            contiguousSegments = new KeyValuePair<int, int>[] { };

            List<KeyValuePair<int, int>> contSegments = new List<KeyValuePair<int, int>>();
            for (int i = pins.PinCount - 1; i >= 0; i--)
            {
                if (!pins[i].IsPairedSio)
                    contSegments.Add(new KeyValuePair<int, int>(i, i));
                else if (pins[i].SioPair_1of2)
                    contSegments.Add(new KeyValuePair<int, int>(i + 1, i));
                //else already added as part of pair
            }
            contiguousSegments = contSegments;
            return CyCustErr.Ok;
        }

        public CyCustErr GetAlias(ICyInstQuery_v1 instQuery, int index, out string alias)
        {
            CyPinData pins = new CyPinData(instQuery);
            alias = (index < pins.PinCount)
                ? pins[index].Alias
                : null;
            return CyCustErr.Ok;
        }

        public CyCustErr GetPinType(ICyInstQuery_v1 instQuery, int index, out CyPinDataPinType_v1 pinType)
        {
            CyPinData pins = new CyPinData(instQuery);
            pinType = default(CyPinDataPinType_v1);

            if (index >= pins.PinCount)
                return new CyCustErr(Resource1.IndexOutOfRange);

            CyPinData.PerPin pin = pins[index];
            bool isAnalog = pin.Type.Is(CyPinType.Analog);
            bool isBiDir = pin.Type.Is(CyPinType.Bidirectional);
            bool isDigIn = pin.Type.Is(CyPinType.Digital_In);
            bool isDigOut = pin.Type.Is(CyPinType.Digital_Out);
            bool isOe = pin.Type.Is(CyPinType.OE);

            if (isBiDir)
            {
                pinType = isAnalog ? CyPinDataPinType_v1.Bidir_Analog : CyPinDataPinType_v1.Bidir;
            }
            else if (isDigIn)
            {
                if (isDigOut)
                {
                    if (isOe)
                    {
                        pinType = isAnalog
                            ? CyPinDataPinType_v1.DigOut_OE_DigIn_Analog
                            : CyPinDataPinType_v1.DigOut_DigIn_OE;
                    }
                    else
                    {
                        pinType = isAnalog
                            ? CyPinDataPinType_v1.DigOut_DigIn_Analog
                            : CyPinDataPinType_v1.DigOut_DigIn;
                    }
                }
                else
                    pinType = isAnalog ? CyPinDataPinType_v1.DigIn_Analog : CyPinDataPinType_v1.DigIn;
            }
            else if (isDigOut)
            {
                if (isOe)
                    pinType = isAnalog ? CyPinDataPinType_v1.DigOut_OE_Analog : CyPinDataPinType_v1.DigOut_OE;
                else
                    pinType = isAnalog ? CyPinDataPinType_v1.DigOut_Analog : CyPinDataPinType_v1.DigOut;
            }
            else if (isAnalog)
                pinType = CyPinDataPinType_v1.Analog;
            else
                return new CyCustErr(string.Format(Resource1.UnhandledPinType, Resource1.Msg_Empty));

            return CyCustErr.Ok;
        }

        #endregion

        //-----------------------------

        #region ICyToolTipCustomize_v1 Members

        public string CustomizeToolTip(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            CyPinData pins = new CyPinData(query);
            StringBuilder toolTip = new StringBuilder();

            toolTip.Append(query.DefaultToolTipText + Environment.NewLine);
            toolTip.Append("Width = " + pins.PinCount.ToString() + Environment.NewLine);
            toolTip.Append(Environment.NewLine);

            bool unlockedAssignmentDisp = false;
            for (int i = 0; i < pins.PinCount; i++)
            {
                string name = pins.GetPinPoundDefineName(i);

                CyPinAssignmentInfo_v1 assigment = pins.GetAssignment(i);
                string assignmentString = string.Empty;
                if (assigment != null)
                {
                    assignmentString = string.Format("P{0}[{1}]{2}, ", assigment.PortNumber, assigment.PortPinNumber,
                        (assigment.IsLocked) ? string.Empty : "*");
                    unlockedAssignmentDisp |= !assigment.IsLocked;
                }

                string driveMode = _getDriveModeString(pins[i].GeneralDriveMode);
                string interruptMode = _getInterruptModeString(pins[i].InputInterrupt);
                string ioVoltage = _getIOVoltageString(pins[i].GeneralMinimumSupply);

                toolTip.Append(string.Format("{0}: {1}{2}{3}{4}{5}",
                    name, assignmentString, driveMode, interruptMode, ioVoltage, Environment.NewLine));
            }

            if (unlockedAssignmentDisp)
            {
                toolTip.Append(Environment.NewLine);
                toolTip.Append(Resource1.AssignmentUnlockedAnd);
            }

            return toolTip.ToString().Trim();
        }

        static string _getIOVoltageString(string voltage)
        {
            if (string.IsNullOrEmpty(voltage) ||
                voltage.Equals(Formal.IOVoltage_Default, StringComparison.OrdinalIgnoreCase))
            {
                return string.Empty;
            }
            return string.Format(", {0}V", voltage);
        }

        static string _getInterruptModeString(CyInputInterruptTrigger interrupt)
        {
            switch (interrupt)
            {
                case CyInputInterruptTrigger.None:
                    return "";
                case CyInputInterruptTrigger.Rising_edge:
                    return ", " + Resource1.RisingEdge;
                case CyInputInterruptTrigger.Falling_edge:
                    return ", " + Resource1.FallingEdge;
                case CyInputInterruptTrigger.Both_edges:
                    return ", " + Resource1.BothEdges;
                default:
                    Debug.Fail("unhandled");
                    return string.Empty;
            }
        }

        static string _getDriveModeString(CyDriveMode driveMode)
        {
            switch (driveMode)
            {
                case CyDriveMode.Strong_Drive:
                    return Resource1.StrongDrive;
                case CyDriveMode.Open_drain_Drive_low:
                    return Resource1.OpenDrainDrivesLow;
                case CyDriveMode.Open_drain_Drive_high:
                    return Resource1.OpenDrainDrivesHigh;
                case CyDriveMode.Resistive_pull_up:
                    return Resource1.ResPullUp;
                case CyDriveMode.Resistive_pull_down:
                    return Resource1.ResPullDown;
                case CyDriveMode.Resistive_pull_up_down:
                    return Resource1.ResPullUpDown;
                case CyDriveMode.High_impedance_analog:
                    return Resource1.HighImpedanceAnalog;
                case CyDriveMode.High_impedance_digital:
                    return Resource1.HighImpedanceDigital;
                default:
                    Debug.Fail("unhandled");
                    return string.Empty;
            }
        }

        #endregion

        //-----------------------------

        #region ICyDesignClient_v2 Members

        static string ToString(IEnumerable<CyPinAssignmentInfo_v1> value)
        {
            StringBuilder sb = new StringBuilder();
            foreach (CyPinAssignmentInfo_v1 info in value)
            {
                if (info != null)
                {
                    sb.Append(info.ToString());
                }
                sb.Append(";");
            }

            //Remove the last ; that was added
            sb.Remove(sb.Length - 1, 1);
            return sb.ToString();
        }

        static List<CyPinAssignmentInfo_v1> FromString(string value)
        {
            string[] parts = value.Split(new char[] { ';' }, StringSplitOptions.None);

            List<CyPinAssignmentInfo_v1> infos = new List<CyPinAssignmentInfo_v1>();
            foreach (string str in parts)
            {
                CyPinAssignmentInfo_v1 info = CyPinAssignmentInfo_v1.FromString(str);
                infos.Add(info);
            }
            return infos;
        }

        string ICyDesignClient_v2.GetDesignClientState(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            List<CyPinAssignmentInfo_v1> info = GetAssignmentInfo(query);
            return ToString(info);
        }

        bool ICyDesignClient_v2.RequiresTooltipUpdate(string designClientState, ICyInstQuery_v1 query,
            ICyTerminalQuery_v1 termQuery)
        {
            List<CyPinAssignmentInfo_v1> oldInfo = FromString(designClientState);
            List<CyPinAssignmentInfo_v1> newInfo = GetAssignmentInfo(query);

            if (oldInfo == null || oldInfo.Count != newInfo.Count) return true;

            for (int i = 0; i < newInfo.Count; i++)
            {
                bool updateNeeded = _tooltipRequiresUpdate(oldInfo[i], newInfo[i]);
                if (updateNeeded) return true;
            }
            return false;
        }

        bool ICyDesignClient_v2.RequiresShapeUpdate(string designClientState, ICyInstQuery_v1 query,
            ICyTerminalQuery_v1 termQuery)
        {
            List<CyPinAssignmentInfo_v1> oldInfo = FromString(designClientState);
            List<CyPinAssignmentInfo_v1> newInfo = GetAssignmentInfo(query);

            if (oldInfo == null || oldInfo.Count != newInfo.Count) return true;

            for (int i = 0; i < newInfo.Count; i++)
            {
                bool updateNeeded = _shapeRequiresUpdate(oldInfo[i], newInfo[i]);
                if (updateNeeded) return true;
            }
            return false;
        }

        private static bool _shapeRequiresUpdate(CyPinAssignmentInfo_v1 oldInfo, CyPinAssignmentInfo_v1 newInfo)
        {
            if (oldInfo == null && newInfo == null)
                return false;

            //Only add the new assignment if it is now locked.
            if (oldInfo == null)
                return newInfo.IsLocked;

            //Only remove the previous assignment if it had been locked.
            if (newInfo == null)
                return oldInfo.IsLocked;

            if (oldInfo.PortNumber != newInfo.PortNumber ||
                oldInfo.PortPinNumber != newInfo.PortPinNumber)
            {
                return newInfo.IsLocked || oldInfo.IsLocked;
            }

            //At this point the assignment must be the same. The only need to update would be if the locked
            //state is different.
            return newInfo.IsLocked != oldInfo.IsLocked;
        }

        private static bool _tooltipRequiresUpdate(CyPinAssignmentInfo_v1 oldInfo, CyPinAssignmentInfo_v1 newInfo)
        {
            if (oldInfo == null && newInfo == null)
                return false;

            if (oldInfo == null || newInfo == null)
                return true;

            return !oldInfo.Equals(newInfo);
        }

        List<CyPinAssignmentInfo_v1> GetAssignmentInfo(ICyInstQuery_v1 query)
        {
            CyPinData pins = new CyPinData(query);

            List<CyPinAssignmentInfo_v1> info = new List<CyPinAssignmentInfo_v1>(pins.PinCount);
            for (int i = 0; i < pins.PinCount; i++)
            {
                CyPinAssignmentInfo_v1 assigment = pins.GetAssignment(i);
                info.Add(assigment);
            }
            return info;
        }

        #endregion

    }

    internal class CyRootTerm
    {
        internal static class Name
        {
            public const string OE = "oe";
            public const string Output = "y";
            public const string Input = "fb";
            public const string Analog = "analog";
            public const string BiDir = "io";
            public const string SIOVRef = "siovref";
            public const string Annotation = "external";
        }

        public static IEnumerable<string> TerminalNames
        {
            get
            {
                yield return Name.OE;
                yield return Name.Output;
                yield return Name.Input;
                yield return Name.Analog;
                yield return Name.BiDir;
                yield return Name.SIOVRef;
                yield return Name.Annotation;
            }
        }

        public static CyCustErr GetExpectedTerminalWidth(CyPinData pins, string rootTermName, out byte numPins)
        {
            CyCustErr err = CyCustErr.Ok;
            if (rootTermName == Name.OE ||
                rootTermName == Name.Output ||
                rootTermName == Name.Input ||
                rootTermName == Name.Analog ||
                rootTermName == Name.BiDir ||
                rootTermName == Name.Annotation)
            {
                numPins = (byte)pins.PinCount;
            }
            else if (rootTermName == Name.SIOVRef)
            {
                numPins = pins.GetSioGroupCnt();
            }
            else
            {
                numPins = default(byte);
                err = new CyCustErr(string.Format(Resource1.UnknownTerm, rootTermName));
            }
            return err;
        }

        internal static bool IsOutput(string rootTermName)
        {
            return rootTermName == Name.Output ||
                   rootTermName == Name.OE;
        }

        internal static bool IsAnalog(string rootTermName)
        {
            return (rootTermName == Name.Analog ||
                    rootTermName == Name.SIOVRef ||
                    rootTermName == Name.Annotation);
        }
    }
}
