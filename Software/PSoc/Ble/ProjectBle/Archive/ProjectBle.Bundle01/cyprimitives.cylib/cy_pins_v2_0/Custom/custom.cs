/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
using System.Diagnostics;
using System.Text.RegularExpressions;
using System.IO;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace Cypress.Comps.PinsAndPorts.cy_pins_v2_0
{
    public class CyCustomizer : 
        ICyShapeCustomize_v1,
        ICyParamEditHook_v1,
        ICyExprEval_v1,
        ICyVerilogCustomize_v1,
        ICyInstValidateHook_v1,
        ICyPinDataProvider_v3,
        ICyToolTipCustomize_v1,
        ICyAPICustomize_v1,
        ICyDesignClient_v2
    {
        public const string BuiltinTabName = "Built-in";
        public const string ConfigureTabName = "Configure";
        public const string ResetTabName = "Reset";
        public const string MappingTabName = "Mapping";
        public const string ClockingTabName = "Clocking";
        public const string PinsTabName = "Pins";

        #region ICyParamEditHook_v1 Members

        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            CyErrorManager errMgr = new CyErrorManager();
            CyDeviceSupport deviceSupport = new CyDeviceSupport(edit.DeviceQuery);

            CyPinData pins = new CyPinData(edit, errMgr);
            CyPinsControl pinsControl = new CyPinsControl(deviceSupport, errMgr, pins);
            CyPORControl porControl = new CyPORControl(deviceSupport, errMgr, pins);
            CyMappingControl mappingControl = new CyMappingControl(errMgr, pins);
            CyClockingControl clockingControl = new CyClockingControl(deviceSupport, errMgr, pins);

            CyParamExprDelegate UpdateGUIFromExprViewChanging = delegate
                {
                    pinsControl.UpdateData();
                    porControl.UpdateData();
                    mappingControl.UpdateData();
                    clockingControl.UpdateData();
                };

            editor.ParamExprCommittedDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
                {
                    if (param.TabName != ConfigureTabName)
                    {
                        //Update the tree if a param on another tab changed. Examples: inst name needs to regenerate
                        //tree node names, layout mode changing can change errors with the per pin data, ...
                        pinsControl.UpdateData();
                    }

                    /*
                    //Errors may need to be updated.
                    porControl.UpdateData();
                    mappingControl.UpdateData();
                    clockingControl.UpdateData();
                    */
                };

            editor.AddCustomPage(PinsTabName, pinsControl, UpdateGUIFromExprViewChanging, ConfigureTabName);
            editor.AddCustomPage(MappingTabName, mappingControl, UpdateGUIFromExprViewChanging, MappingTabName);

            if (!deviceSupport.HasData || deviceSupport.IsPSoC4 || deviceSupport.IsTSG4 || UsesPaClocking(pins))
                editor.AddCustomPage(ClockingTabName, clockingControl, UpdateGUIFromExprViewChanging, ClockingTabName);
            if (!deviceSupport.HasData || deviceSupport.IsPSoC3 || deviceSupport.IsPSoC5 || UsesPor(pins))
                editor.AddCustomPage(ResetTabName, porControl, UpdateGUIFromExprViewChanging, ResetTabName);

            editor.AddDefaultPage(BuiltinTabName, BuiltinTabName);
            pins.Validate();
            return editor.ShowDialog();
        }

        private static bool UsesPaClocking(CyPinData pins)
        {
            return (pins.ClockInput != CyPinClock.HFCLK) ||
                (pins.ClockInputEnable != CyPinClockEnRst.NONE) ||
                (pins.ClockInputReset != CyPinClockEnRst.NONE) ||
                (pins.ClockOutput != CyPinClock.HFCLK) ||
                (pins.ClockOutputEnable != CyPinClockEnRst.NONE) ||
                (pins.ClockOutputReset != CyPinClockEnRst.NONE) ||
                (pins.ClockOutputResetEnable) ||
                (pins.ClockOutputOeResetEnable);
        }

        private static bool UsesPor(CyPinData pins)
        {
            return (pins.PowerOnReset != CyPowerOnRestMode.HIZ_ANALOG &&
                pins.PowerOnReset != CyPowerOnRestMode.UNSPECIFIED);
        }

        public bool EditParamsOnDrop
        {
            get { return false; }
        }

        public CyCompDevParamEditorMode GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }

        #endregion

        //-----------------------------

        #region ICyShapeCustomize_v1 Members

        private bool IsHomogeneous(CyPinData pins)
        {
            for (int i = 0; i < pins.PinCount; i++)
            {
                if (pins[0].Type != pins[i].Type ||
                    pins[0].TypeIsDigitalInputHw != pins[i].TypeIsDigitalInputHw ||
                    pins[0].TypeIsDigitalOutputHw != pins[i].TypeIsDigitalOutputHw ||
                    pins[0].TypeShowExternalTerm != pins[i].TypeShowExternalTerm ||
                    pins[0].IsSIO() != pins[i].IsSIO())
                    return false;
            }
            return true;
        }
        private bool UsesInterrupts(CyPinData pins)
        {
            for (int i = 0; i < pins.PinCount; i++)
            {
                if (pins[i].InputInterrupt != CyInputInterruptTrigger.NONE)
                    return true;
            }
            return false;
        }

        public CyCustErr CustomizeShapes(ICyInstQuery_v1 query, ICySymbolShapeEdit_v1 shapeEdit,
            ICyTerminalEdit_v1 termEdit)
        {
            //The entire symbol is drawn here. 
            //In the special case where the width is one, no IRQ is used, and only one side has terminals on it 
            //we draw as small as possible and put the instance name on the opposite side as the terminals. 
            CyPinData pins = new CyPinData(query);
            CyCustErr err;

            CyPinsDrawer drawer = new CyPinsDrawer(query, shapeEdit, termEdit);

            byte numPins = (byte)pins.PinCount;
            bool usesInterrupts = UsesInterrupts(pins);
            bool displayAsBus = pins.MappingDisplayAsBus;
            bool isHomogeneous = IsHomogeneous(pins);

            bool[] inputHw = new bool[pins.PinCount];
            bool[] outputHw = new bool[pins.PinCount];
            bool[] annotation = new bool[pins.PinCount];
            for (int i = 0; i < pins.PinCount; i++)
            {
                inputHw[i] = pins[i].TypeIsDigitalInputHw;
                outputHw[i] = pins[i].TypeIsDigitalOutputHw;
                annotation[i] = pins[i].TypeShowExternalTerm;
            }

            bool showInClk, showInClkEn, showInRst, showOutClk, showOutClkEn, showOutRst;
            if (query.DeviceQuery.IsPSoC4 || query.DeviceQuery.IsTSG4)
            {
                showInClk = (pins.ClockInput == CyPinClock.EXTERNAL || pins.ClockInput == CyPinClock.EXTERNAL_INV);
                showInClkEn = (pins.ClockInputEnable == CyPinClockEnRst.EXTERNAL || 
                    pins.ClockInputEnable == CyPinClockEnRst.EXTERNAL_INV);
                showInRst = (pins.ClockInputReset == CyPinClockEnRst.EXTERNAL || 
                    pins.ClockInputReset == CyPinClockEnRst.EXTERNAL_INV);
                showOutClk = (pins.ClockOutput == CyPinClock.EXTERNAL || pins.ClockOutput == CyPinClock.EXTERNAL_INV);
                showOutClkEn = (pins.ClockOutputEnable == CyPinClockEnRst.EXTERNAL || 
                    pins.ClockOutputEnable == CyPinClockEnRst.EXTERNAL_INV);
                showOutRst = (pins.ClockOutputReset == CyPinClockEnRst.EXTERNAL || 
                    pins.ClockOutputReset == CyPinClockEnRst.EXTERNAL_INV);
            }
            else
                showInClk = showInClkEn = showInRst = showOutClk = showOutClkEn = showOutRst = false;

            if (displayAsBus && isHomogeneous)
            {
                err = drawer.DrawAsBus(true, numPins, usesInterrupts, pins, 
                    showInClk, showInClkEn, showInRst, showOutClk, showOutClkEn, showOutRst);
            }
            else
            {
                err = drawer.DrawAsIndividualTerminals(isHomogeneous, usesInterrupts, pins,
                    showInClk, showInClkEn, showInRst, showOutClk, showOutClkEn, showOutRst);
            }
            return err.IsNotOk ? err : CyCustErr.Ok;
        }

        class CyPinsDrawer
        {
            #region Data

            readonly ICyInstQuery_v1 m_query;
            readonly ICySymbolShapeEdit_v1 m_shapeEdit;
            readonly ICyTerminalEdit_v1 m_termEdit;

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
                float quarterUnit = 0.25f * m_shapeEdit.UserBaseUnit;
                float size = 1.5f * m_shapeEdit.UserBaseUnit;

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

            public CyPinsDrawer(ICyInstQuery_v1 query, ICySymbolShapeEdit_v1 shapeEdit, ICyTerminalEdit_v1 termEdit)
            {
                m_query = query;
                m_shapeEdit = shapeEdit;
                m_termEdit = termEdit;
                TopYDelta = m_shapeEdit.UserBaseUnit;
                BottomYDelta = 3 * TopYDelta;
                SingleReservedSize = 2 * m_shapeEdit.UserBaseUnit;
                SIOBorderInflation = m_shapeEdit.UserBaseUnit * 0.15f;

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
            /// Used to center the first pin on (0,0) in the y-direction.
            /// </summary>
            float YOffset
            {
                get { return SingleReservedSize; }
            }

            public CyCustErr DrawAsIndividualTerminals(bool isHomogeneous, bool usesIsr, CyPinData pins,
                bool showInClk, bool showInClkEn, bool showInRst, bool showOutClk, bool showOutClkEn, bool showOutRst)
            {
                CyCustErr err = Clear();
                if (err.IsNotOk) return err;

                bool drawAsSinglePin = GetDrawAsSinglePin(isHomogeneous, false, pins.PinCount, usesIsr, pins[0], 
                    showInClk, showInClkEn, showInRst, showOutClk, showOutClkEn, showOutRst);
                if (err.IsNotOk) return err;

                float y = -YOffset;
                for (int index = 0; index < pins.PinCount; index++)
                {
                    CyPinTypeData pinTypeData = new CyPinTypeData(pins[index]);

                    PointF reservedLoc = new PointF(0, y);
                    y += SingleReservedSize * pinTypeData.NumTerminalsTall;
                    int sioGroupIndex = GetSIOGroupNumber(pins.Pins, index);
                    err = DrawPin(reservedLoc, pinTypeData, index, drawAsSinglePin, 1, 1, true,
                        pins[index].TypeIsDigitalInputHw, pins[index].TypeIsDigitalOutputHw, sioGroupIndex,
                        pins.GetAssignment(index));
                    if (err.IsNotOk) return err;
                }

                UpdateZOrders();

                if (drawAsSinglePin == false)
                {
                    DrawOuterComponentAndIRQ(
                        usesIsr, showInClk, showInClkEn, showInRst, showOutClk, showOutClkEn, showOutRst, y + YOffset);
                }

                return CyCustErr.Ok;
            }

            static int GetSIOGroupNumber(IList<CyPinData.PerPin> pins, int index)
            {
                int sioCnt = 0;
                for (int i = 0; i < index; i++)
                {
                    if (pins[i].IsSIO())
                    {
                        if (pins[i].SIOPairID != 1)
                            sioCnt++;
                    }
                }

                return sioCnt;
            }

            private void UpdateZOrders()
            {
                //Ensures that the analog wires draw below the sio border and the digital inputs (if used).
                m_shapeEdit.SendToBack(SIOTag);
                m_shapeEdit.SendToBack(AnalogTag);
            }

            public CyCustErr DrawAsBus(
                bool isHomogeneous, byte width, bool usesInterrupts, CyPinData pins,
                bool showInClk, bool showInClkEn, bool showInRst, bool showOutClk, bool showOutClkEn, bool showOutRst)
            {
                CyCustErr err = Clear();
                if (err.IsNotOk) return err;

                bool drawAsSinglePin = GetDrawAsSinglePin(isHomogeneous, true, width, usesInterrupts, pins[0], 
                    showInClk, showInClkEn, showInRst, showOutClk, showOutClkEn, showOutRst);
                if (err.IsNotOk) return err;

                CyPinTypeData pinTypeData = new CyPinTypeData(pins[0]);

                PointF reservedLoc = new PointF(0, -YOffset);
                int sioGroupCnt = GetSIOGroupNumber(pins.Pins, pins.PinCount);
                int sioGroupIndex = GetSIOGroupNumber(pins.Pins, 0);
                err = DrawPin(reservedLoc, pinTypeData, width - 1, drawAsSinglePin, width,
                    sioGroupCnt, false, pins[0].TypeIsDigitalInputHw, pins[0].TypeIsDigitalOutputHw, sioGroupIndex,
                    pins.GetAssignment(0));
                if (err.IsNotOk) return err;

                UpdateZOrders();

                if (drawAsSinglePin == false)
                {
                    DrawOuterComponentAndIRQ(usesInterrupts, showInClk, showInClkEn, showInRst, showOutClk, 
                        showOutClkEn, showOutRst, pinTypeData.NumTerminalsTall*SingleReservedSize);
                }

                return CyCustErr.Ok;
            }

            CyCustErr DrawOuterComponentAndIRQ(bool usesInterrupts, bool showInClk, bool showInClkEn, bool showInRst,
                bool showOutClk, bool showOutClkEn, bool showOutRst, float height)
            {
                //This should only be called if not drawAsSinglePin.
                //Draw a box around the component, draw the inst name, and check if the irq terminal needs to be
                //added.

                float compBodyWidth = 3 * SingleReservedSize;
                float compBodyHeight = Math.Abs(height);
                PointF loc = new PointF(-SingleReservedSize, -YOffset);

                int advancedClockingSpaceNeeded = 0;

                if (showOutRst)
                    advancedClockingSpaceNeeded = 6;
                else if (showInRst)
                    advancedClockingSpaceNeeded = 5;
                else if (showOutClkEn)
                    advancedClockingSpaceNeeded = 4;
                else if (showInClkEn)
                    advancedClockingSpaceNeeded = 3;
                else if (showOutClk)
                    advancedClockingSpaceNeeded = 2;
                else if (showInClk)
                    advancedClockingSpaceNeeded = 1;

                float clkBoxHeight = SingleReservedSize * advancedClockingSpaceNeeded;

                // Body box
                const string compBodyTag = "CompBodyTag";
                const int BODY_LINE_WIDTH = 1;
                string[] compBodyTags = new string[] { compBodyTag };
                m_shapeEdit.CreateRectangle(compBodyTags, loc, compBodyWidth, compBodyHeight,
                    Color.FromArgb(220, 220, 220), Color.Black, BODY_LINE_WIDTH, LineJoin.Miter);
                m_shapeEdit.SendToBack(compBodyTag);

                if (advancedClockingSpaceNeeded > 0)
                {
                    // clocking box
                    const string compClkBoxTag = "CompClkBoxTag";
                    string[] compClkBoxTags = new string[] { compClkBoxTag };
                    m_shapeEdit.CreateRectangle(
                        compClkBoxTags, new PointF(loc.X, loc.Y - clkBoxHeight), compBodyWidth, clkBoxHeight,
                        Color.FromArgb(220, 220, 220), Color.Black, BODY_LINE_WIDTH, LineJoin.Miter);
                    m_shapeEdit.SendToBack(compClkBoxTag);
                }

                // Title box
                const string compTitleTag = "CompTitleTag";
                string[] compTitleTags = new string[] { compTitleTag };
                m_shapeEdit.CreateRectangle(compTitleTags, new PointF(loc.X, loc.Y - 2 * BaseUnit - clkBoxHeight),
                    compBodyWidth, 2 * BaseUnit, TitleColor, Color.Black, BODY_LINE_WIDTH, LineJoin.Miter);
                m_shapeEdit.SendToBack(compTitleTag);

                PointF center = new PointF(loc.X + compBodyWidth / 2, loc.Y - BaseUnit - clkBoxHeight); 
                StringFormat titleFmt = new StringFormat();
                titleFmt.LineAlignment = StringAlignment.Center;
                titleFmt.Alignment = StringAlignment.Center;
                m_shapeEdit.CreateAnnotation(TextTags, "Pins", center,
                    new Font(FontFamily.GenericSansSerif, OtherTextSize, FontStyle.Regular), titleFmt, TextFillColor);

                StringFormat fmt = new StringFormat();
                fmt.LineAlignment = StringAlignment.Far;
                fmt.Alignment = StringAlignment.Far;
                DrawInstanceName(new PointF(loc.X + compBodyWidth, loc.Y - clkBoxHeight - SingleReservedSize), fmt);

                if (usesInterrupts)
                {
                    PointF termLoc = 
                        new PointF(loc.X + compBodyWidth/2, loc.Y + compBodyHeight + m_shapeEdit.UserBaseUnit);
                    PointF endTermLoc = new PointF(termLoc.X, loc.Y + compBodyHeight);
                    m_shapeEdit.CreateLine(
                        DigitalTags, termLoc, endTermLoc, DigitalOutlineColor, m_query.Preferences.WireSize);
                    m_termEdit.TerminalAdd(CyTermInfo.RootTermName_Interrupt + "_0",
                        CyCompDevTermDir.OUTPUT, CyCompDevTermType.DIGITAL, termLoc, string.Empty, 90, false);

                    StringFormat irqFmt = new StringFormat();
                    irqFmt.LineAlignment = StringAlignment.Near;
                    irqFmt.Alignment = StringAlignment.Far;
                    m_shapeEdit.CreateAnnotation(TextTags, "irq",
                        new PointF(endTermLoc.X - m_shapeEdit.UserBaseUnit/2.0f, endTermLoc.Y),
                        new Font(FontFamily.GenericSansSerif, ParameterTextSize, FontStyle.Regular), 
                        irqFmt, TextFillColor);
                }

                if (showInClk)
                    DrawClkBoxInTerm(CyTermInfo.RootTermName_InClock, "in_clk", loc, 1);
                if (showInClkEn)
                    DrawClkBoxInTerm(CyTermInfo.RootTermName_InClockEn, "in_en", loc, 5);
                if (showInRst)
                    DrawClkBoxInTerm(CyTermInfo.RootTermName_InReset, "in_rst", loc, 9);
                if (showOutClk)
                    DrawClkBoxInTerm(CyTermInfo.RootTermName_OutClock, "out_clk", loc, 3);
                if (showOutClkEn)
                    DrawClkBoxInTerm(CyTermInfo.RootTermName_OutClockEn, "out_en", loc, 7);
                if (showOutRst)
                    DrawClkBoxInTerm(CyTermInfo.RootTermName_OutReset, "out_rst", loc, 11);

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
            static bool GetDrawAsSinglePin(
                bool isHomogeneous, bool drawAsBus, int width, bool usesInterrupts, CyPinData.PerPin pin,
                bool showInClk, bool showInClkEn, bool showInRst, bool showOutClk, bool showOutClkEn, bool showOutRst)
            {
                bool drawAsSinglePin = false;

                if ((width == 1 || (isHomogeneous && drawAsBus)) && !usesInterrupts && !showInClk && !showInClkEn &&
                    !showInRst && !showOutClk && !showOutClkEn && !showOutRst)
                {
                    CyPinTypeData pinTypeData = new CyPinTypeData(pin);

                    drawAsSinglePin = pinTypeData.OnlyOneSideUsed;
                }

                return drawAsSinglePin;
            }

            private CyCustErr DrawPin(PointF reservedLoc, CyPinTypeData pinTypeData, int indexOfLeftMostBit,
                bool drawAsSinglePin, int width, int sioWidth, bool showIndex,
                bool inputHw, bool outputHw, int sioGroupIndex, CyPinAssignmentInfo_v1 assignment)
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
                    err = DrawAnalog(reservedLoc, pinTypeData.DigitalInputUsed, indexOfLeftMostBit, width);
                    if (err.IsNotOk) return err;
                }
                if (pinTypeData.DigitalInputUsed)
                {
                    err = DrawDigitalInput(reservedLoc, indexOfLeftMostBit, width, inputHw);
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
                    err = DrawDigitalOutput(reservedLoc, indexOfLeftMostBit, width, outputHw);
                    if (err.IsNotOk) return err;
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

                    if (pinTypeData.SIOPairID == 0)
                    {
                        m_sioFirstBounds = sioBounds;
                    }
                    else
                    {
                        if (pinTypeData.SIOPairID == 1)
                        {
                            Debug.Assert(m_sioFirstBounds.IsEmpty == false);
                            sioBounds = RectangleF.Union(sioBounds, m_sioFirstBounds);
                            m_sioFirstBounds = RectangleF.Empty;
                        }

                        m_shapeEdit.CreateRectangle(SIOTags, sioBounds.Location, sioBounds.Width,
                           sioBounds.Height, TitleColor, Color.Black, THIN_LINE_WIDTH, LineJoin.Miter);
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
                PointF end = new PointF(reservedLoc.X + 2.5f * SingleReservedSize - m_shapeEdit.UserBaseUnit, middle.Y);

                CyCustErr err = m_shapeEdit.CreatePolyline(
                    AnalogTags, AnalogOutlineColor, m_query.Preferences.WireSize, LineJoin.Miter, start, middle, end);
                if (err.IsNotOk) return err;

                //Add Terminal
                err = m_termEdit.TerminalAdd(
                    GetTerminalName(CyTermInfo.RootTermName_SIOVRef, index, width), CyCompDevTermDir.INOUT,
                    CyCompDevTermType.ANALOG, new PointF(end.X + m_shapeEdit.UserBaseUnit, end.Y), string.Empty,
                    180, false);
                if (err.IsNotOk) return err;

                if (width > 1)
                {
                    AddTermWidthLabel(end, new PointF(end.X + m_shapeEdit.UserBaseUnit, end.Y), width);
                }

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

                //If the terminal is not drawn, fill in the area with the line so that the term width
                //label has a place to go.
                CyCustErr err = m_shapeEdit.CreateLine(DigitalTags,
                    outputHw
                       ? new PointF(start.X + m_shapeEdit.UserBaseUnit, start.Y)
                       : new PointF(start.X, start.Y),
                    new PointF(end.X + m_shapeEdit.UserBaseUnit*.25f, end.Y),
                    DigitalOutlineColor, m_query.Preferences.WireSize);
                if (err.IsNotOk) return err;

                float leftX = start.X + SingleReservedSize;
                float rightX = leftX + m_shapeEdit.UserBaseUnit / 2;
                float halfArrow = (rightX - leftX) / 2;

                err = m_shapeEdit.CreatePolygon(
                    ArrowLineTags, PinBodyFillColor, PinBodyOutlineColor, THIN_LINE_WIDTH, LineJoin.Miter,
                    new PointF(rightX, end.Y),
                    new PointF(leftX, end.Y + halfArrow),
                    new PointF(leftX, end.Y - halfArrow));
                if (err.IsNotOk) return err;

                if (outputHw)
                {
                    err = m_termEdit.TerminalAdd(GetTerminalName(CyTermInfo.RootTermName_Output, index, width),
                        CyCompDevTermDir.INPUT, CyCompDevTermType.DIGITAL,
                        new PointF(start.X, start.Y), string.Empty, 0, false);
                    if (err.IsNotOk) return err;
                }

                if (width > 1)
                {
                    AddTermWidthLabel(start, new PointF(start.X + m_shapeEdit.UserBaseUnit, start.Y), width);
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

                PointF start = new PointF(reservedLoc.X - 0.25f * SingleReservedSize - 0.25f * m_shapeEdit.UserBaseUnit,
                    reservedLoc.Y + TopYDelta);
                PointF middle = new PointF(start.X, reservedLoc.Y + BottomYDelta);
                PointF end = new PointF(reservedLoc.X - 1.5f * SingleReservedSize + m_shapeEdit.UserBaseUnit, middle.Y);

                CyCustErr err = m_shapeEdit.CreatePolyline(DigitalTags, 
                    DigitalOutlineColor, m_query.Preferences.WireSize, LineJoin.Miter, start, middle, end);
                if (err.IsNotOk) return err;

                err = m_termEdit.TerminalAdd(GetTerminalName(CyTermInfo.RootTermName_OE, index, width),
                    CyCompDevTermDir.INPUT, CyCompDevTermType.DIGITAL,
                    new PointF(end.X - m_shapeEdit.UserBaseUnit, end.Y), string.Empty, 0, false);
                if (err.IsNotOk) return err;

                if (width > 1)
                {
                    AddTermWidthLabel(new PointF(end.X - m_shapeEdit.UserBaseUnit, end.Y), end, width);
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

                //If the terminal is not drawn, fill in the area with the line so that the term width
                //label has a place to go.
                err = m_shapeEdit.CreateLine(
                    DigitalTags, start, new PointF(inputHw ? end.X - m_shapeEdit.UserBaseUnit : end.X, end.Y),
                    DigitalOutlineColor, m_query.Preferences.WireSize);
                if (err.IsNotOk) return err;

                float leftX = end.X - SingleReservedSize;
                float rightX = leftX + m_shapeEdit.UserBaseUnit / 2;
                float halfArrow = (rightX - leftX) / 2;

                err = m_shapeEdit.CreatePolygon(
                    ArrowLineTags, PinBodyFillColor, PinBodyOutlineColor, THIN_LINE_WIDTH, LineJoin.Miter,
                    new PointF(rightX, end.Y),
                    new PointF(leftX, end.Y + halfArrow),
                    new PointF(leftX, end.Y - halfArrow));
                if (err.IsNotOk) return err;

                if (inputHw)
                {
                    err = m_termEdit.TerminalAdd(GetTerminalName(CyTermInfo.RootTermName_Input, index, width),
                        CyCompDevTermDir.OUTPUT, CyCompDevTermType.DIGITAL,
                        new PointF(end.X, end.Y), string.Empty, 0, false);
                    if (err.IsNotOk) return err;
                }

                if (width > 1)
                {
                    AddTermWidthLabel(new PointF(end.X - m_shapeEdit.UserBaseUnit, end.Y), end, width);
                }

                return CyCustErr.Ok;
            }

            private CyCustErr DrawAnalog(PointF reservedLoc, bool digitalInputUsed, int index, int width)
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

                    PointF start = new PointF(pinBodyBounds.Right + m_shapeEdit.UserBaseUnit * 0.5f,
                        reservedLoc.Y + TopYDelta);
                    PointF middle = new PointF(start.X, reservedLoc.Y + BottomYDelta);
                    end = new PointF(reservedLoc.X + 2.5f * SingleReservedSize - m_shapeEdit.UserBaseUnit, middle.Y);

                    err = m_shapeEdit.CreatePolyline(AnalogTags, 
                        AnalogOutlineColor, m_query.Preferences.WireSize, LineJoin.Miter, start, middle, end);
                    if (err.IsNotOk) return err;
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
                    end = new PointF(reservedLoc.X + 2.5f * SingleReservedSize - m_shapeEdit.UserBaseUnit, start.Y);

                    err = m_shapeEdit.CreateLine(
                        AnalogTags, start, end, AnalogOutlineColor, m_query.Preferences.WireSize);
                    if (err.IsNotOk) return err;
                }

                //Add Terminal
                err = m_termEdit.TerminalAdd(
                    GetTerminalName(CyTermInfo.RootTermName_Analog, index, width), CyCompDevTermDir.INOUT,
                    CyCompDevTermType.ANALOG,
                    new PointF(end.X + m_shapeEdit.UserBaseUnit, end.Y), string.Empty, 180, false);
                if (err.IsNotOk) return err;

                if (width > 1)
                {
                    AddTermWidthLabel(end, new PointF(end.X + m_shapeEdit.UserBaseUnit, end.Y), width);
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
                    reservedLoc.X - 1.5f * SingleReservedSize + m_shapeEdit.UserBaseUnit :
                    reservedLoc.X + 2.5f * SingleReservedSize - m_shapeEdit.UserBaseUnit;

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
                    PointF middle = new PointF(start.X, pinBodyBounds.Top + pinBodyBounds.Height / 2 + termRow * 2.0f * m_shapeEdit.UserBaseUnit);
                    end = new PointF(endXVal, middle.Y);

                    err = m_shapeEdit.CreatePolyline(AnnotationTags, 
                        AnnotationOutlineColor, m_query.Preferences.WireSize, LineJoin.Miter, start, middle, end);
                    if (err.IsNotOk) return err;
                }

                //Add Terminal
                err = m_termEdit.TerminalAdd(
                    GetTerminalName(CyTermInfo.RootTermName_Annotation, index, width), CyCompDevTermDir.INOUT,
                    CyCompDevTermType.ANNOTATION,
                    // flip the terminal if (termIsOnLeft == false)
                    new PointF(end.X - m_shapeEdit.UserBaseUnit * (termIsOnLeft ? 1 : -1), end.Y),
                    string.Empty, termIsOnLeft ? 0 : 180, false);
                if (err.IsNotOk) return err;

                if (width > 1)      // pin is a bus
                {
                    bool drawBusWidthNumber = termRow != 0 || (!termIsOnLeft && SIOVrefUsed);
                    if (drawBusWidthNumber)
                        AddTermWidthLabel(end, new PointF(end.X - m_shapeEdit.UserBaseUnit * (termIsOnLeft ? 1 : -1), end.Y), width);
                    else
                        AddTermWidthTick(end, new PointF(end.X - m_shapeEdit.UserBaseUnit * (termIsOnLeft ? 1 : -1), end.Y));
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
                m_shapeEdit.CreateLine(DigitalTags, new PointF(start.X + m_shapeEdit.UserBaseUnit, start.Y), end,
                    DigitalOutlineColor, m_query.Preferences.WireSize);

                //Draw Arrows
                float leftX = start.X + 1.5f * m_shapeEdit.UserBaseUnit;
                float rightX = leftX + m_shapeEdit.UserBaseUnit;
                float middleX = leftX + (rightX - leftX) / 2;
                float arrowHeight = m_shapeEdit.UserBaseUnit * .25f;

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
                string termName = GetTerminalName(CyTermInfo.RootTermName_BiDir, index, width);
                m_termEdit.TerminalAdd(termName,
                    CyCompDevTermDir.INOUT, CyCompDevTermType.DIGITAL,
                    new PointF(start.X, start.Y), string.Empty, 0, false);
                CyCustErr err = m_termEdit.SetIsBurriedPin(termName, true);
                if (err.IsNotOk) return err;

                if (width > 1)
                {
                    AddTermWidthLabel(start, new PointF(start.X + m_shapeEdit.UserBaseUnit, start.Y), width);
                }

                return CyCustErr.Ok;
            }

            private void AddTermWidthLabel(PointF startTerm, PointF endTerm, int width)
            {
                Debug.Assert(width > 1);

                StringFormat fmt = new StringFormat();
                fmt.LineAlignment = StringAlignment.Far;
                fmt.Alignment = StringAlignment.Center;

                PointF centerTerm = new PointF(startTerm.X + (endTerm.X - startTerm.X) / 2, startTerm.Y);
                m_shapeEdit.CreateAnnotation(TextTags, width.ToString(), centerTerm,
                    new Font(FontFamily.GenericSansSerif, DecorativeTextSize, FontStyle.Regular), fmt, TextFillColor);
                AddTermWidthTick(startTerm, endTerm);
            }

            private void AddTermWidthTick(PointF startTerm, PointF endTerm)
            {
                Debug.Assert(startTerm.Y == endTerm.Y);
                PointF centerTerm = new PointF(startTerm.X + (endTerm.X - startTerm.X) / 2, startTerm.Y);

                float quarterUnit = m_shapeEdit.UserBaseUnit / 4;
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
                    Color.White, Color.Black, 0, LineJoin.Miter);
                m_shapeEdit.ClearOutline("background");

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
                    loc.Y -= m_shapeEdit.UserBaseUnit;
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
                    pinBodyBounds.Width, pinBodyBounds.Height,
                    PinBodyFillColor, PinBodyOutlineColor, THIN_LINE_WIDTH, LineJoin.Miter);

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

            class CyPinTypeData
            {
                public readonly CyPinData.PerPin Pin;
                public readonly bool AnalogUsed;
                public readonly bool DigitalInputUsed;
                public readonly bool DigitalOutputUsed;
                public readonly bool BidirectionalUsed;
                public readonly bool OutputEnableUsed;
                public readonly bool SIOVRefUsed;
                public readonly bool ShowAnnotation;

                public readonly bool IsSIO;
                public readonly int SIOPairID;

                public bool RightSideUsed
                {
                    get { return AnalogUsed || DigitalInputUsed || SIOVRefUsed; }
                }

                public bool LeftSideUsed
                {
                    //We don't need to check OE because it cannot be used without using Digital Output.
                    get { return DigitalOutputUsed || BidirectionalUsed; }
                }

                public bool OnlyOneSideUsed
                {
                    get { return RightSideUsed ^ LeftSideUsed; }
                }

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
                    AnalogUsed = ((pin.Type & CyPinType.ANALOG) == CyPinType.ANALOG);
                    DigitalInputUsed = ((pin.Type & CyPinType.DIGITAL_IN) == CyPinType.DIGITAL_IN);
                    DigitalOutputUsed = ((pin.Type & CyPinType.DIGITAL_OUT) == CyPinType.DIGITAL_OUT);
                    BidirectionalUsed = ((pin.Type & CyPinType.BIDIRECTIONAL) == CyPinType.BIDIRECTIONAL);
                    OutputEnableUsed = ((pin.Type & CyPinType.OE) == CyPinType.OE);
                    ShowAnnotation = pin.TypeShowExternalTerm;
                    IsSIO = pin.IsSIO();
                    SIOPairID = pin.SIOPairID;
                    SIOVRefUsed = UsesSIOVRef(pin);
                }

                private bool UsesSIOVRef(CyPinData.PerPin pin)
                {
                    return (pin.SIOPairID == -1 || pin.SIOPairID == 1) && // Second or lone SIO
                           ((pin.OutputDriveLevel == CyOutputDriveLevel.VREF) ||
                           (pin.InputThreshold == CyInputThreshold.PT5_VREF) ||
                           (pin.InputThreshold == CyInputThreshold.VREF));
                }
            }

            #endregion
        }

        #endregion

        //-----------------------------

        #region ICyExprEval_v1 Members

        public virtual CyExprEvalFunc GetFunction(string exprFuncName)
        {
            switch (exprFuncName)
            {
                //`=UsesInterrupts($InterruptModes, $PinTypes, $NumPins)`
                case "UsesInterrupts":
                    return UsesInterrupts;

                //`=IsHomogeneous_v2($PinTypes, $sio_info, $sio_refsel, $DisplayOutputHWConnections, 
                //                   $DisplayInputHWConnections, $NumPins, $sio_group_cnt)`
                case "IsHomogeneous_v2":
                    return IsHomogeneous_v2;

                default:
                    //Return null to indicate that the customizer didn't process the 
                    //function call so CyDesigner should continue trying to process it.
                    return null;
            }
        }

        object UsesInterrupts(string exprFuncName, object[] args, ICyExprTypeConverter typeConverter)
        {
            //Generate an error if the wrong number of arguements have been passed in.
            if (args.Length != 3)
                return new CyCustErr(string.Format(Resource1.ParamCntErr_UsesInterrupts, exprFuncName));

            //Arg 0 used, 1 & 2 are ignorred now
            string interruptModesString = typeConverter.GetAsString(args[0]);
            string[] values = interruptModesString.Split(',');
            for (int i = 0; i < values.Length; i++)
            {
                if (values[i] != CyPinData.InterruptModeValue_NONE)
                    return true;
            }
            return false;
        }

        object IsHomogeneous_v2(string exprFuncName, object[] args, ICyExprTypeConverter typeConverter)
        {
            //Generate an error if the wrong number of arguements have been passed in.
            if (args.Length != 7)
                return new CyCustErr(string.Format(Resource1.ParamCntErr_IsHomogeneous_v2, exprFuncName));

            string pinTypesString = typeConverter.GetAsString(args[0]);
            string sioInfosString = typeConverter.GetAsString(args[1]);
            string sioRefSelsString = typeConverter.GetAsString(args[2]);
            string dspOutputConnString = typeConverter.GetAsString(args[3]);
            string dspInputConnString = typeConverter.GetAsString(args[4]);
            //byte width = typeConverter.GetAsByte(args[5]);
            //byte sioGroupCnt = typeConverter.GetAsByte(args[6]);

            string value;
            string[] values;

            value = null;
            values = pinTypesString.Split(',');
            for (int i = 0; i < values.Length; i++)
            {
                if (value == null) value = values[i];
                else if (value != values[i]) return false;
            }

            value = null;
            values = sioRefSelsString.Split(',');
            for (int i = 0; i < values.Length; i++)
            {
                if (value == null) value = values[i];
                else if (value != values[i]) return false;
            }

            value = null;
            values = dspOutputConnString.Split(',');
            for (int i = 0; i < values.Length; i++)
            {
                if (value == null) value = values[i];
                else if (value != values[i]) return false;
            }

            value = null;
            values = dspInputConnString.Split(',');
            for (int i = 0; i < values.Length; i++)
            {
                if (value == null) value = values[i];
                else if (value != values[i]) return false;
            }

            values = sioInfosString.Split(',');
            if (values.Length > 1)
            {
                for (int i = 0; i < values.Length - 1; i++)
                {
                    string sioInfo1 = values[i];
                    string sioInfo2 = values[i + 1];

                    switch (sioInfo1)
                    {
                        case CyPinData.SIOInfoValue_NOT_SIO:
                        case CyPinData.SIOInfoValue_SINGLE_SIO:
                            if (sioInfo2 != sioInfo1)
                                return false;
                            break;
                        case CyPinData.SIOInfoValue_FIRST_IN_SIO_PAIR:
                            if (sioInfo2 != CyPinData.SIOInfoValue_SECOND_IN_SIO_PAIR)
                                return false;
                            break;
                        case CyPinData.SIOInfoValue_SECOND_IN_SIO_PAIR:
                            if (sioInfo2 == CyPinData.SIOInfoValue_SECOND_IN_SIO_PAIR)
                                return false;
                            break;
                        default:
                            return new CyCustErr(string.Format(Resource1.UnhandledSIOInfo, sioInfo1));
                    }
                }
            }

            return true;
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
            CyVerilogWriter vw = new CyVerilogWriter("cy_psoc3_pins_v1_10", query.InstanceName);

            vw.AddGeneric("id", "\"" + query.InstanceIdPath + "\"");
            CyPinData pins = new CyPinData(query);
            //Add Generics.
            IDictionary<string, string> generics = CyParameters.GenerateVerilogGenerics(pins, query.DeviceQuery);
            foreach (KeyValuePair<string, string> generic in generics)
                vw.AddGeneric(generic.Key, generic.Value);

#if DEBUG
            //Verify we generated everything we intended to.  This is just a sanity check for our 2.0 migration
            //of settings.  It can be removed, as well as all the local parameters once proven to work. Maybe
            //for version 2.1?
            foreach (string paramName in query.GetParamNames())
            {
                CyCompDevParam param = query.GetCommittedParam(paramName);
                if (param.IsHardware)
                    Debug.Assert(generics.ContainsKey(paramName), "Missing verilog local");
            }
#endif

            //Add Ports.
            foreach (string rootTermName in CyTermInfo.TerminalRootNames)
            {
                byte expectedWidth;
                err = CyTermInfo.GetExpectedTerminalWidth(pins, rootTermName, out expectedWidth);
                if (err.IsNotOk) return err;

                Dictionary<int, string> indexToTerminalNameMapping = GetAssociatedTerminals(rootTermName, termQuery);

                //Don't add an entry for analog terminals if no portion is hooked up
                if (indexToTerminalNameMapping.Count != 0 || CyTermInfo.IsAnalog(rootTermName) == false)
                {
                    List<string> bits = new List<string>();
                    for (int i = expectedWidth - 1; i >= 0; )
                    {
                        bool containsMapping = indexToTerminalNameMapping.ContainsKey(i);

                        if (containsMapping)
                        {
                            if (pins.MappingDisplayAsBus && rootTermName == CyTermInfo.RootTermName_OE)
                            {
                                string termName = indexToTerminalNameMapping[i];
                                string value = termQuery.GetTermSigSegName(termName);
                                for (int temp = 0; temp < expectedWidth; temp++)
                                {
                                    bits.Add(value);
                                }
                                int termWidth = termQuery.GetTermWidth(termName) * expectedWidth;
                                i -= termWidth;
                            }
                            else
                            {
                                string termName = indexToTerminalNameMapping[i];
                                string value = termQuery.GetTermSigSegName(termName);
                                bits.Add(value);
                                int termWidth = termQuery.GetTermWidth(termName);
                                i -= termWidth;
                            }
                        }
                        else
                        {
                            int temp = i + 1;
                            while (containsMapping == false && temp >= 0)
                            {
                                temp--;
                                containsMapping = indexToTerminalNameMapping.ContainsKey(temp);
                            }

                            //From i to temp + 1, there is nothing connected.
                            int unhookedWidth = i - temp;

                            if (CyTermInfo.IsInput(rootTermName))
                            {
                                if (CyTermInfo.RootTermName_OE == rootTermName ||
                                    CyTermInfo.RootTermName_InClockEn == rootTermName ||
                                    CyTermInfo.RootTermName_OutClockEn == rootTermName)
                                {
                                    bits.Add(string.Format("{0}'b{1}", unhookedWidth, new string('1', unhookedWidth)));
                                }
                                else
                                {
                                    bits.Add(string.Format("{0}'b0", unhookedWidth));
                                }
                            }
                            else
                            {
                                string wireName =
                                    string.Format("tmp{0}_{1}__{2}_net", rootTermName.ToUpper(), i, query.InstanceName);

                                if (CyTermInfo.IsAnalog(rootTermName))
                                {
                                    vw.AddElectrical(wireName, unhookedWidth - 1, 0);
                                }
                                else
                                {
                                    vw.AddWire(wireName, unhookedWidth - 1, 0);
                                }
                                bits.Add(string.Format("{0}[{1}:0]", wireName, unhookedWidth - 1));
                            }

                            i = temp;
                        }
                    }

                    string assignment = string.Join(", ", bits.ToArray());
                    if (!string.IsNullOrEmpty(assignment))
                    {
                        if (CyTermInfo.RootTermName_OE == rootTermName)
                        {
                            // POST PR4 NOTE:
                            //     Prior to PR4, the OE signals are 'active low', meaning, a 0 will
                            //     enable the output, a 1 would turn it off. CDT 32449 is tracking the
                            //     PR4 change to the device to make it 'active high', as it should have
                            //     been.
                            string netOEName = "tmpOE__" + query.InstanceName + "_net";
                            vw.AddWire(netOEName, expectedWidth - 1, 0);
                            vw.AssignPreES3CondWire(netOEName, "~" + "{" + assignment + "}", "{" + assignment + "}");
                            vw.AddPort(rootTermName, netOEName);
                        }
                        else
                        {
                            string verilogName = (rootTermName == CyTermInfo.RootTermName_Annotation)
                                                     ? "annotation"
                                                     : rootTermName;
                            vw.AddPort(verilogName, "{" + assignment + "}");
                        }
                    }
                }
                else if (CyTermInfo.RootTermName_SIOVRef == rootTermName)
                {
                    string wireName =
                        string.Format("tmp{0}__{1}_net", rootTermName.ToUpper(), query.InstanceName);
                    vw.AddElectrical(wireName, 0, 0);
                    vw.AddPort(rootTermName, wireName);
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

        #region ICyPinDataProvider_v1 Members

        public string BaseTermName_Analog
        {
            get { return CyTermInfo.RootTermName_Analog; }
        }

        public CyCustErr GetWidth(ICyInstQuery_v1 instQuery, out byte width)
        {
            CyPinData pins = new CyPinData(instQuery);
            width = (byte)pins.PinCount;
            return CyCustErr.Ok;
        }

        public CyCustErr GetUsesInterrupts(ICyInstQuery_v1 instQuery, out bool usesInterrupts)
        {
            CyPinData pins = new CyPinData(instQuery);
            usesInterrupts = false;
            for (int i = 0; i < pins.PinCount; i++)
            {
                if (pins[i].InputInterrupt != CyInputInterruptTrigger.NONE)
                    usesInterrupts = true;
            }

            return CyCustErr.Ok;
        }

        public CyCustErr GetContiguousSegments(ICyInstQuery_v1 instQuery,
            out IEnumerable<KeyValuePair<int, int>> contiguousSegments)
        {
            //Segements can be grouped one of 2 ways, either by being contiguous or by being in an SIO pair.
            CyPinData pins = new CyPinData(instQuery);

            contiguousSegments = new KeyValuePair<int, int>[] { };

            List<KeyValuePair<int, int>> contSegments = new List<KeyValuePair<int, int>>();
            if (pins.MappingContigious)
                contSegments.Add(new KeyValuePair<int, int>(pins.PinCount - 1, 0));
            else
            {
                for (int i = pins.PinCount - 1; i >= 0; i--)
                {
                    if (pins[i].SIOPairID == -1)
                        contSegments.Add(new KeyValuePair<int, int>(i, i));
                    else if (pins[i].SIOPairID == 0)
                        contSegments.Add(new KeyValuePair<int, int>(i + 1, i));
                    //else already added as part of pair
                }
            }
            contiguousSegments = contSegments;
            return CyCustErr.Ok;
        }

        public CyCustErr GetAlias(ICyInstQuery_v1 instQuery, int index, out string alias)
        {
            CyPinData pins = new CyPinData(instQuery);
            alias = (pins.PinCount > index)
                ? pins[index].Alias
                : null;
            return CyCustErr.Ok;
        }

        public CyCustErr GetIOVoltage(ICyInstQuery_v1 instQuery, int index, out double ioVoltage)
        {
            CyPinData pins = new CyPinData(instQuery);
            if (pins.PinCount > index)
                double.TryParse(pins[index].GeneralMinimumSupply, out ioVoltage);
            else
                ioVoltage = 0;
            return CyCustErr.Ok;
        }

        public CyCustErr GetPinType(ICyInstQuery_v1 instQuery, int index, out CyPinDataPinType_v1 pinType)
        {
            CyPinData pins = new CyPinData(instQuery);
            pinType = default(CyPinDataPinType_v1);

            if (pins.PinCount > index)
            {
                CyPinData.PerPin pin = pins[index];
                bool isAnalog = ((pin.Type & CyPinType.ANALOG) > 0);
                bool isBiDir = ((pin.Type & CyPinType.BIDIRECTIONAL) > 0);
                bool isDigIn = ((pin.Type & CyPinType.DIGITAL_IN) > 0);
                bool isDigOut = ((pin.Type & CyPinType.DIGITAL_OUT) > 0);
                bool isOe = ((pin.Type & CyPinType.OE) > 0);

                if (isBiDir)
                {
                    pinType = (isAnalog) ? CyPinDataPinType_v1.Bidir_Analog : CyPinDataPinType_v1.Bidir;
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
                    {
                        pinType = isAnalog ? CyPinDataPinType_v1.DigIn_Analog : CyPinDataPinType_v1.DigIn;
                    }
                }
                else if (isDigOut)
                {
                    if (isOe)
                    {
                        pinType = isAnalog ? CyPinDataPinType_v1.DigOut_OE_Analog : CyPinDataPinType_v1.DigOut_OE;
                    }
                    else
                    {
                        pinType = isAnalog ? CyPinDataPinType_v1.DigOut_Analog : CyPinDataPinType_v1.DigOut;
                    }
                }
                else if (isAnalog)
                {
                    pinType = CyPinDataPinType_v1.DigOut_Analog;
                }
                else
                    return new CyCustErr(string.Format(Resource1.UnhandledPinType, "(empty)"));
            }
            else
                return new CyCustErr("Index out of range");

            return CyCustErr.Ok;
        }

        public CyCustErr GetSIOInfo(ICyInstQuery_v1 instQuery, int index, out CyPinDataSIOType_v1 sioInfo)
        {
            CyPinData pins = new CyPinData(instQuery);
            if (pins.PinCount > index)
            {
                if (pins[index].SIOPairID == 1)
                    sioInfo = CyPinDataSIOType_v1.SecondInSIOPair;
                else if (pins[index].SIOPairID == 0)
                    sioInfo = CyPinDataSIOType_v1.FirstInSIOPair;
                else if (pins[index].IsSIO())
                    sioInfo = CyPinDataSIOType_v1.SingleSIO;
                else
                    sioInfo = CyPinDataSIOType_v1.NotSIO;
            }
            else
            {
                sioInfo = default(CyPinDataSIOType_v1);
                return new CyCustErr("Index out of range");
            }

            return CyCustErr.Ok;
        }

        public CyCustErr GetInputThreshold(ICyInstQuery_v1 instQuery, int index, out CyPinDataInputThreshold_v1 threshold)
        {
            CyPinData pins = new CyPinData(instQuery);
            if (pins.PinCount > index)
            {
                switch (pins[index].InputThreshold)
                {
                    case CyInputThreshold.CMOS:
                        threshold = CyPinDataInputThreshold_v1.CMOS;
                        break;
                    case CyInputThreshold.CMOS_LVTTL:
                        threshold = CyPinDataInputThreshold_v1.CMOSorLVTTL;
                        break;
                    case CyInputThreshold.LVTTL:
                        threshold = CyPinDataInputThreshold_v1.LVTTL;
                        break;
                    case CyInputThreshold.PT4_VDDIO:
                        threshold = CyPinDataInputThreshold_v1.Vddio04;
                        break;
                    case CyInputThreshold.PT5_VDDIO:
                        threshold = CyPinDataInputThreshold_v1.Vddio05;
                        break;
                    case CyInputThreshold.PT5_VREF:
                        threshold = CyPinDataInputThreshold_v1.Vref;
                        break;
                    case CyInputThreshold.VREF:
                        threshold = CyPinDataInputThreshold_v1.Vref05;
                        break;
                    default:
                        Debug.Fail("Unhandled input threshold: " + pins[index].InputThreshold);
                        threshold = default(CyPinDataInputThreshold_v1);
                        break;
                }
            }
            else
            {
                threshold = default(CyPinDataInputThreshold_v1);
                return new CyCustErr("Index out of range");
            }

            return CyCustErr.Ok;
        }

        public CyCustErr GetPORMode(ICyInstQuery_v1 instQuery, out CyPinDataPOR_v1 porMode)
        {
            CyPinData pins = new CyPinData(instQuery);
            switch (pins.PowerOnReset)
            {
                case CyPowerOnRestMode.UNSPECIFIED:
                    porMode = CyPinDataPOR_v1.Unspecified;
                    break;
                case CyPowerOnRestMode.HIZ_ANALOG:
                    porMode = CyPinDataPOR_v1.HiZAnalog;
                    break;
                case CyPowerOnRestMode.PULLED_UP:
                    porMode = CyPinDataPOR_v1.PulledUp;
                    break;
                case CyPowerOnRestMode.PULLED_DOWN:
                    porMode = CyPinDataPOR_v1.PulledDown;
                    break;
                default:
                    Debug.Fail("Unhandled POR mode: " + pins.PowerOnReset);
                    porMode = default(CyPinDataPOR_v1);
                    return new CyCustErr(string.Format("Unhandled Power-On Reset Mode '{0}'.", pins.PowerOnReset.ToString()));
            }

            return CyCustErr.Ok;
        }

        public CyCustErr GetAssociatedTerminalName(ICyTerminalQuery_v1 termQuery, string portTermBaseName, int index,
            out string termName, out int offset)
        {
            Dictionary<int, string> indexToTerminalNameMapping = GetAssociatedTerminals(portTermBaseName, termQuery);

            foreach (KeyValuePair<int, string> pair in indexToTerminalNameMapping)
            {
                int termWidth = termQuery.GetTermWidth(pair.Value);
                int leftIndex = pair.Key;
                int rightIndex = leftIndex - (termWidth - 1);

                if (rightIndex <= index && index <= leftIndex)
                {
                    //This is the correct terminal.
                    termName = pair.Value;
                    offset = index - rightIndex;
                    return CyCustErr.Ok;
                }
            }

            termName = null;
            offset = default(int);
            return new CyCustErr(Resource1.TermNotFound);
        }

        public CyCustErr GetDriveMode(ICyInstQuery_v1 instQuery, int index, out CyPinDataDriveMode_v1 driveMode)
        {
            CyPinData pins = new CyPinData(instQuery);
            if (pins.PinCount > index)
            {
                switch (pins[index].GeneralDriveMode)
                {
                    case CyDriveMode.STRONG_DRIVE:
                        driveMode = CyPinDataDriveMode_v1.StrongDrive;
                        break;
                    case CyDriveMode.OPEN_DRAIN_DRIVE_LOW:
                        driveMode = CyPinDataDriveMode_v1.OpenDrainDrivesLow;
                        break;
                    case CyDriveMode.OPEN_DRAIN_DRIVE_HIGH:
                        driveMode = CyPinDataDriveMode_v1.OpenDrainDrivesHigh;
                        break;
                    case CyDriveMode.RESISTIVE_PULL_UP:
                        driveMode = CyPinDataDriveMode_v1.ResistivePullUp;
                        break;
                    case CyDriveMode.RESISTIVE_PULL_DOWN:
                        driveMode = CyPinDataDriveMode_v1.ResistivePullDown;
                        break;
                    case CyDriveMode.RESISTIVE_PULL_UP_DOWN:
                        driveMode = CyPinDataDriveMode_v1.ReistivePullUpDown;
                        break;
                    case CyDriveMode.HIGH_IMPEDANCE_ANALOG:
                        driveMode = CyPinDataDriveMode_v1.HighImpedanceAnalog;
                        break;
                    case CyDriveMode.HIGH_IMPEDANCE_DIGITAL:
                        driveMode = CyPinDataDriveMode_v1.HighImpedanceDigital;
                        break;
                    default:
                        Debug.Fail("Unhandled drive mode: " + pins[index].GeneralDriveMode);
                        driveMode = default(CyPinDataDriveMode_v1);
                        return new CyCustErr(string.Format(Resource1.UnhandledDriveMode, pins[index].GeneralDriveMode));
                }
            }
            else
            {
                driveMode = default(CyPinDataDriveMode_v1);
                return new CyCustErr("Index out of range");
            }
            return CyCustErr.Ok;
        }

        public CyCustErr GetSlewRate(ICyInstQuery_v1 instQuery, int index, out CyPinDataSlewRate_v1 slewRate)
        {
            CyPinData pins = new CyPinData(instQuery);
            if (pins.PinCount > index)
            {
                if (pins[index].OutputSlewRate == CyOutputSlewRate.FAST)
                    slewRate = CyPinDataSlewRate_v1.Fast;
                else
                    slewRate = CyPinDataSlewRate_v1.Slow;
            }
            else
            {
                slewRate = default(CyPinDataSlewRate_v1);
                return new CyCustErr("Index out of range");
            }

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

            string porString;
            switch (pins.PowerOnReset)
            {
                case CyPowerOnRestMode.UNSPECIFIED:
                    porString = "Don't Care";
                    break;
                case CyPowerOnRestMode.HIZ_ANALOG:
                    porString = "High-Z Analog";
                    break;
                case CyPowerOnRestMode.PULLED_UP:
                    porString = "Pulled-Up";
                    break;
                case CyPowerOnRestMode.PULLED_DOWN:
                    porString = "Pulled-Down";
                    break;
                default:
                    Debug.Fail("unhandled");
                    porString = string.Empty;
                    break;
            }

            toolTip.Append("Power-On Reset = " + porString + Environment.NewLine);

            toolTip.Append("Layout Mode = " + ((pins.MappingContigious) ?
                "Contiguous/Non-Spanning" : "Non-Contiguous/Spanning") + Environment.NewLine);

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
                    unlockedAssignmentDisp |= (assigment.IsLocked == false);
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
                toolTip.Append("* Assignment is unlocked and may be moved by the fitter when rebuilt.");
            }

            return toolTip.ToString().Trim();
        }

        static string _getIOVoltageString(string voltage)
        {
            if (string.IsNullOrEmpty(voltage) ||
                CyPinData.DefaultIOVolatageValue.Equals(voltage, StringComparison.OrdinalIgnoreCase))
            {
                return string.Empty;
            }
            return string.Format(", {0}V", voltage);
        }

        static string _getInterruptModeString(CyInputInterruptTrigger interrupt)
        {
            switch (interrupt)
            {
                case CyInputInterruptTrigger.NONE:
                    return string.Empty;
                case CyInputInterruptTrigger.RISING_EDGE:
                    return ", Rising Edge";
                case CyInputInterruptTrigger.FALLING_EDGE:
                    return ", Falling Edge";
                case CyInputInterruptTrigger.BOTH_EDGES:
                    return ", Both Edges";
                default:
                    Debug.Fail("unhandled");
                    return string.Empty;
            }
        }

        static string _getDriveModeString(CyDriveMode driveMode)
        {
            switch (driveMode)
            {
                case CyDriveMode.STRONG_DRIVE:
                    return "Strong Drive";
                case CyDriveMode.OPEN_DRAIN_DRIVE_LOW:
                    return "Open Drain, Drives Low";
                case CyDriveMode.OPEN_DRAIN_DRIVE_HIGH:
                    return "Open Drain, Drives High";
                case CyDriveMode.RESISTIVE_PULL_UP:
                    return "Resistive Pull Up";
                case CyDriveMode.RESISTIVE_PULL_DOWN:
                    return "Resistive Pull Down";
                case CyDriveMode.RESISTIVE_PULL_UP_DOWN:
                    return "Resistive Pull Up/Down";
                case CyDriveMode.HIGH_IMPEDANCE_ANALOG:
                    return "High Impedance Analog";
                case CyDriveMode.HIGH_IMPEDANCE_DIGITAL:
                    return "High Impedance Digital";
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
            {
                return false;
            }
            if (oldInfo == null)
            {
                //Only need to add the new assingment if it is locked.
                return newInfo.IsLocked;
            }
            if (newInfo == null)
            {
                //Only need to remove the previous assignment if it had been locked.
                return oldInfo.IsLocked;
            }
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
            {
                return false;
            }
            if (oldInfo == null || newInfo == null)
            {
                return true;
            }
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

        //-----------------------------

        #region ICyAPICustomize_v1 Members

        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery,
            IEnumerable<CyAPICustomizer> apis)
        {
            //Only generate port level APIs for components that are contiguous and non-spanning.
            //All components get the aliases file with #defines.
            CyPinData pins = new CyPinData(query);
            List<CyAPICustomizer> apiCustomizers = new List<CyAPICustomizer>(apis);

            string instanceName = query.GetCommittedParam(CyPinData.Builtin_ParamName_InstName).Value;

            #region API Gen Specific Params and Param Names

            string driveModeImpl = string.Empty;
            string driveModeImplP4 = string.Empty;
            for (int count = 0; count < pins.PinCount; count++)
            {
                driveModeImpl += string.Format("\tCyPins_SetPinDriveMode({0}_{1}, mode);{2}",
                    instanceName, count, Environment.NewLine);
                driveModeImplP4 += string.Format("\tSetP4PinDriveMode({0}__{1}__SHIFT, mode);{2}",
                    instanceName, count, Environment.NewLine);
            }
            driveModeImpl = driveModeImpl.TrimEnd();
            driveModeImplP4 = driveModeImplP4.TrimEnd();

            StringBuilder poundDefineMappingsSb = new StringBuilder();
            StringBuilder poundDefineMappingsAliasesSb = new StringBuilder();

            //Single underscores were required by TBEN.
            for (byte count = 0; count < pins.PinCount; count++)
            {
                poundDefineMappingsSb.AppendFormat("#define {0}_{1}\t\t{0}__{1}__PC{2}",
                    instanceName, count, Environment.NewLine);

                string alias = pins[count].Alias;
                if (!string.IsNullOrEmpty(alias))
                {
                    poundDefineMappingsAliasesSb.AppendFormat("#define {0}_{1}\t\t{0}__{1}__PC{2}",
                        instanceName, alias, Environment.NewLine);
                }
            }
            poundDefineMappingsSb.AppendLine().Append(poundDefineMappingsAliasesSb.ToString());
            string poundDefineMappings = poundDefineMappingsSb.ToString().TrimEnd();

            #endregion

            foreach (CyAPICustomizer file in apiCustomizers)
            {
                Dictionary<string, string> paramDict = file.MacroDictionary;
                paramDict["SetDriveModeImpl_API_GEN"] = driveModeImpl;
                paramDict["SetDriveModeImplP4_API_GEN"] = driveModeImplP4;
                paramDict["PoundDefineMappings_API_GEN"] = poundDefineMappings;
                file.MacroDictionary = paramDict;
            }

            if (((pins.MappingContigious && !pins.MappingSpanning) || pins.PinCount == 1))
            {
                //Return all the APIs.
                return apiCustomizers;
            }
            else
            {
                //Only return the aliases file
                foreach (CyAPICustomizer cust in apis)
                {
                    string filename = Path.GetFileName(cust.OriginalName);
                    if (filename.Equals("aliases.h"))
                    {
                        return new CyAPICustomizer[] { cust };
                    }
                }

                Debug.Fail("shouldn't get here");
                return new CyAPICustomizer[] { };
            }
        }

        #endregion

        //-----------------------------

        #region Helper Methods

        protected CyCustErr SetTerminalsWidth(ICyTerminalEdit_v1 termEdit, IEnumerable<string> termBaseNames,
                                              byte width)
        {
            CyCustErr err = CyCustErr.Ok;
            foreach (string termBaseName in termBaseNames)
            {
                string termFullName = termEdit.GetTermName(termBaseName);
                err = SetTerminalWidth(termEdit, termFullName, termBaseName, width);
                if (err.IsNotOk) return err;
            }
            return err;
        }

        protected CyCustErr SetTerminalWidth(ICyTerminalEdit_v1 termEdit, string terminalFullName,
                                             string terminalBaseName, int width)
        {
            int leftIndex = width - 1;

            string newName = leftIndex == 0
                                 ? terminalBaseName
                                 : string.Format("{0}[{1}:0]", terminalBaseName, leftIndex);

            CyCustErr err = termEdit.TerminalRename(terminalFullName, newName);
            return err;
        }

        #endregion

        //-----------------------------

        #region Unit Tests

        const int TOTAL_NUM_TEST_PINS = 13;

        /// <summary>
        /// Tests editing parameters and checking that other paramaters get updated as expected.
        /// </summary>
        /// <param name="instEdit"></param>
        public static void RunUnitTest(ICyInstEdit_v1 instEdit)
        {
            CheckDefaultValueSettings(instEdit);
            CheckDirectionRestrictSettings(instEdit);
            CheckSIO(instEdit);
        }

        /// <summary>
        /// Check the default value of certain parameters (InputBufferEnabled, DriveMode, InitDriveState)
        /// are set correctly.
        /// </summary>
        /// <param name="instEdit"></param>
        static void CheckDefaultValueSettings(ICyInstEdit_v1 instEdit)
        {
            SetupDefaultValueTesting(instEdit);
            CheckInputBufferEnabled(instEdit);
            CheckDriveModes(instEdit);
            CheckInitDriveStates(instEdit);
        }

        /// <summary>
        /// Check Input/Output only settings are set to default when pin types are set backwards.
        /// Some parameters only applied to input pins while others only applied to output pins.
        /// This test is to make sure, if the pin type is set to input, all the parameters applied to
        /// output pin only  will be set to default regardless whatever the user set them to and vise versa.
        /// </summary>
        /// <param name="instEdit"></param>
        static void CheckDirectionRestrictSettings(ICyInstEdit_v1 instEdit)
        {
            CheckInputRestrictSettings(instEdit);
            CheckOutputRestrictSettings(instEdit);
        }

        /// <summary>
        /// Check all the rules applied to SIO pins.
        /// </summary>
        /// <param name="instEdit"></param>
        static void CheckSIO(ICyInstEdit_v1 instEdit)
        {
            string defaultSetupValue;

            //======================================================================================================
            //I'am an SIO when
            //Input && HotSwap == true ||
            string hotSwapsValue = string.Format("{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}",
                                                   CyPinData.ParamValue_TRUE,
                                                   CyPinData.ParamValue_FALSE,
                                                   CyPinData.ParamValue_TRUE,
                                                   CyPinData.ParamValue_FALSE,
                                                   CyPinData.ParamValue_FALSE,
                                                   CyPinData.ParamValue_FALSE,
                                                   CyPinData.ParamValue_FALSE,
                                                   CyPinData.ParamValue_FALSE,
                                                   CyPinData.ParamValue_TRUE,
                                                   CyPinData.ParamValue_FALSE,
                                                   CyPinData.ParamValue_FALSE,
                                                   CyPinData.ParamValue_FALSE,
                                                   CyPinData.ParamValue_TRUE);

            string[] IsSIOHotSwapExpectedValues = new string[] {CyPinData.SIOInfoValue_SINGLE_SIO,
                                                         CyPinData.SIOInfoValue_NOT_SIO, 
                                                         CyPinData.SIOInfoValue_SINGLE_SIO, 
                                                         CyPinData.SIOInfoValue_NOT_SIO,
                                                         CyPinData.SIOInfoValue_NOT_SIO,
                                                         CyPinData.SIOInfoValue_NOT_SIO,
                                                         CyPinData.SIOInfoValue_NOT_SIO,
                                                         CyPinData.SIOInfoValue_NOT_SIO,
                                                         CyPinData.SIOInfoValue_NOT_SIO,
                                                         CyPinData.SIOInfoValue_NOT_SIO,
                                                         CyPinData.SIOInfoValue_NOT_SIO,
                                                         CyPinData.SIOInfoValue_NOT_SIO,
                                                         CyPinData.SIOInfoValue_NOT_SIO};

            bool result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_HotSwaps, hotSwapsValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            CheckWarpValuesNonBitVector(instEdit, CyParameters.Local_ParamName_SIOInfo, IsSIOHotSwapExpectedValues);

            //Set HotSwaps back to default value.
            CreateUnitTestParamArrayValue(CyPinData.DefaultHotSwapValue, out defaultSetupValue);
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_HotSwaps, defaultSetupValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            //======================================================================================================
            //Input && Input Threshold == .5 VDDIO, .4 VDDIO,  .5Vref, Vref ||
            string thresholdLevelsValue =
                string.Format("{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}",
                              CyPinData.ThresholdLevelValue_PT5_VDDIO,
                              CyPinData.ThresholdLevelValue_PT4_VDDIO,
                              CyPinData.ThresholdLevelValue_PT5_VREF,
                              CyPinData.ThresholdLevelValue_VREF,
                              CyPinData.ThresholdLevelValue_CMOS,
                              CyPinData.ThresholdLevelValue_CMOS_LVTTL,
                              CyPinData.ThresholdLevelValue_CMOS,
                              CyPinData.ThresholdLevelValue_CMOS,
                              CyPinData.ThresholdLevelValue_PT5_VDDIO,
                              CyPinData.ThresholdLevelValue_PT4_VDDIO,
                              CyPinData.ThresholdLevelValue_CMOS,
                              CyPinData.ThresholdLevelValue_LVTTL,
                              CyPinData.ThresholdLevelValue_PT4_VDDIO);

            string[] IsSIOThresholdLevelsExpectedValue = new string[] {CyPinData.SIOInfoValue_SINGLE_SIO, 
                                                                  CyPinData.SIOInfoValue_SINGLE_SIO,
                                                                  CyPinData.SIOInfoValue_SINGLE_SIO,
                                                                  CyPinData.SIOInfoValue_SINGLE_SIO,
                                                                  CyPinData.SIOInfoValue_NOT_SIO, 
                                                                  CyPinData.SIOInfoValue_NOT_SIO, 
                                                                  CyPinData.SIOInfoValue_NOT_SIO, 
                                                                  CyPinData.SIOInfoValue_NOT_SIO, 
                                                                  CyPinData.SIOInfoValue_NOT_SIO, 
                                                                  CyPinData.SIOInfoValue_NOT_SIO, 
                                                                  CyPinData.SIOInfoValue_NOT_SIO, 
                                                                  CyPinData.SIOInfoValue_NOT_SIO, 
                                                                  CyPinData.SIOInfoValue_NOT_SIO};

            result =
               instEdit.SetParamExpr(CyPinData.Formal_ParamName_ThresholdLevels, thresholdLevelsValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            CheckWarpValuesNonBitVector(instEdit, CyParameters.Local_ParamName_SIOInfo, IsSIOThresholdLevelsExpectedValue);

            //======================================================================================
            //Input Buffer Check.

            //Set up the HotSwaps to match threshold to achieve our test purpose. 
            //Set HotSwap == True so ThresholdLevel == CMOS will make SIO_InputBuffer SingleEnded.
            //Set HotSwap == False so ThresholdLevel == LVTTL will not throw error.
            string hotSwapsForThresholdLevelValue =
                string.Format("{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}",
                              CyPinData.ParamValue_FALSE,
                              CyPinData.ParamValue_FALSE,
                              CyPinData.ParamValue_FALSE,
                              CyPinData.ParamValue_FALSE,
                              CyPinData.ParamValue_TRUE,
                              CyPinData.ParamValue_FALSE,
                              CyPinData.ParamValue_TRUE,
                              CyPinData.ParamValue_FALSE,
                              CyPinData.ParamValue_FALSE,
                              CyPinData.ParamValue_FALSE,
                              CyPinData.ParamValue_FALSE,
                              CyPinData.ParamValue_FALSE,
                              CyPinData.ParamValue_FALSE);

            result =
                instEdit.SetParamExpr(CyPinData.Formal_ParamName_HotSwaps, hotSwapsForThresholdLevelValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            //SIO_InputBuffer
            //if(Threshold == CMOS) then SignleEnded
            //else if(Threshold != LVTTL) then Differential
            //else if (threshold == LVTTL) then not used.
            string[] SIOInputBufferExpectedValues = new string[] {CyPinData.SIOInputBufferValue_DIFFERENTIAL, 
                                                                  CyPinData.SIOInputBufferValue_DIFFERENTIAL, 
                                                                  CyPinData.SIOInputBufferValue_DIFFERENTIAL,
                                                                  CyPinData.SIOInputBufferValue_DIFFERENTIAL,
                                                                  CyPinData.SIOInputBufferValue_SINGLE_ENDED,
                                                                  CyPinData.SIOInputBufferValue_SINGLE_ENDED};

            //Check SIO_InputBuffer
            CheckWarpValuesBitVector(instEdit, "sio_ibuf", SIOInputBufferExpectedValues);

            //Set HotSwap and threshold back to default value.
            CreateUnitTestParamArrayValue(CyPinData.DefaultHotSwapValue, out defaultSetupValue);
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_HotSwaps, defaultSetupValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            CreateUnitTestParamArrayValue(CyPinData.DefaultThresholdLevelValue, out defaultSetupValue);
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_ThresholdLevels, defaultSetupValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            //======================================================================================
            //I'm an SIO when
            //Output && Output Drive Level == Vref || Output && Input Sink Current == 25mA
            string driveLevelsValue =
                string.Format("{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}",
                              CyPinData.OutputDriveLevelValue_VREF,
                              CyPinData.OutputDriveLevelValue_VDDIO,
                              CyPinData.OutputDriveLevelValue_VREF,
                              CyPinData.OutputDriveLevelValue_VDDIO,
                              CyPinData.OutputDriveLevelValue_VDDIO,
                              CyPinData.OutputDriveLevelValue_VDDIO,
                              CyPinData.OutputDriveLevelValue_VREF,
                              CyPinData.OutputDriveLevelValue_VDDIO,
                              CyPinData.OutputDriveLevelValue_VDDIO,
                              CyPinData.OutputDriveLevelValue_VDDIO,
                              CyPinData.OutputDriveLevelValue_VDDIO,
                              CyPinData.OutputDriveLevelValue_VDDIO,
                              CyPinData.OutputDriveLevelValue_VDDIO);

            string outputDriveCurrentValue =
                 string.Format("{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}",
                              CyPinData.DriveCurrentValue_4SOURCE_25SINK,
                              CyPinData.DriveCurrentValue_4SOURCE_8SINK,
                              CyPinData.DriveCurrentValue_4SOURCE_8SINK,
                              CyPinData.DriveCurrentValue_4SOURCE_8SINK,
                              CyPinData.DriveCurrentValue_4SOURCE_25SINK,
                              CyPinData.DriveCurrentValue_4SOURCE_8SINK,
                              CyPinData.DriveCurrentValue_4SOURCE_25SINK,
                              CyPinData.DriveCurrentValue_4SOURCE_8SINK,
                              CyPinData.DriveCurrentValue_4SOURCE_8SINK,
                              CyPinData.DriveCurrentValue_4SOURCE_8SINK,
                              CyPinData.DriveCurrentValue_4SOURCE_25SINK,
                              CyPinData.DriveCurrentValue_4SOURCE_8SINK,
                              CyPinData.DriveCurrentValue_4SOURCE_8SINK);

            string[] IsSIOVrefExpectedValues = new string[] {CyPinData.SIOInfoValue_NOT_SIO, 
                                                             CyPinData.SIOInfoValue_NOT_SIO,
                                                             CyPinData.SIOInfoValue_SINGLE_SIO, 
                                                             CyPinData.SIOInfoValue_NOT_SIO, 
                                                             CyPinData.SIOInfoValue_SINGLE_SIO, 
                                                             CyPinData.SIOInfoValue_NOT_SIO, 
                                                             CyPinData.SIOInfoValue_SINGLE_SIO, 
                                                             CyPinData.SIOInfoValue_NOT_SIO, 
                                                             CyPinData.SIOInfoValue_NOT_SIO, 
                                                             CyPinData.SIOInfoValue_NOT_SIO, 
                                                             CyPinData.SIOInfoValue_SINGLE_SIO, 
                                                             CyPinData.SIOInfoValue_NOT_SIO, 
                                                             CyPinData.SIOInfoValue_NOT_SIO};

            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_OutputDriveLevels, driveLevelsValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_DriveCurrents, outputDriveCurrentValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            CheckWarpValuesNonBitVector(instEdit, CyParameters.Local_ParamName_SIOInfo, IsSIOVrefExpectedValues);

            //=====================================================================================
            //Check SIO_OutputBuffer
            //If(DriveLevel == Vref) Then Regulated
            //If(DriveLevel == VDDIO), then Unregulated]
            string[] SIOOutputBufferExpectedValues = new string[] {CyPinData.SIOOutputBufferValue_REGULATED, 
                                                                   CyPinData.SIOOutputBufferValue_UNREGULATED,
                                                                   CyPinData.SIOOutputBufferValue_REGULATED,
                                                                   CyPinData.SIOOutputBufferValue_UNREGULATED};

            CheckWarpValuesBitVector(instEdit, "sio_obuf", SIOOutputBufferExpectedValues);

            //set Output Driver level back to default
            CreateUnitTestParamArrayValue(CyPinData.DefaultOutputDriveLevelValue, out defaultSetupValue);
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_OutputDriveLevels, defaultSetupValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            //set Output Driver level back to default
            CreateUnitTestParamArrayValue(CyPinData.DefaultDriveCurrentValue, out defaultSetupValue);
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_DriveCurrents, defaultSetupValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();
        }

        /// <summary>
        /// Used to set up a test case with all input pin types and check the set up is complete and correct.
        /// </summary>
        /// <param name="instEdit"></param>
        static void SetupDefaultValueTesting(ICyInstEdit_v1 instEdit)
        {
            //The pin will be set up in the following order:

            //Digital In
            // DIGIN
            // DIGIN_ANALOG

            //Digital In/Out
            //BIDIRECTIONAL
            //BIDIRECTIONAL_ANALOG
            //DIGOUT_DIGIN
            //DIGOUT_DIGIN_ANALOG
            //DIGOUT_DIGIN_OE
            //DIGOUT_OE_DIGIN_ANALOG

            //Digital Out
            //DIGOUT
            //DIGOUT_ANALOG
            //DIGOUT_OE
            //DIGOUT_OE_ANALOG

            //Analog
            //ANALOG

            //We need 13 pins here so the layout mode has to be set to span to achive this
            bool result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_LayoutMode,
                                                CyPinData.LayoutModeValue_CONT_SPANNING);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            string pins = string.Format("{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}",
                CyPinData.PinTypesValue_DIGIN, CyPinData.PinTypesValue_DIGIN_ANALOG,
                CyPinData.PinTypesValue_BIDIRECTIONAL, CyPinData.PinTypesValue_BIDIRECTIONAL_ANALOG,
                CyPinData.PinTypesValue_DIGOUT_DIGIN, CyPinData.PinTypesValue_DIGOUT_DIGIN_ANALOG,
                CyPinData.PinTypesValue_DIGOUT_DIGIN_OE, CyPinData.PinTypesValue_DIGOUT_OE_DIGIN_ANALOG,
                CyPinData.PinTypesValue_DIGOUT, CyPinData.PinTypesValue_DIGOUT_ANALOG,
                CyPinData.PinTypesValue_DIGOUT_OE, CyPinData.PinTypesValue_DIGOUT_OE_ANALOG,
                CyPinData.PinTypesValue_ANALOG);

            //Set number of pins.
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_NumPins, TOTAL_NUM_TEST_PINS.ToString());
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            //Check if it is set up correctly.
            byte numPins;
            CyCustErr err = 
                instEdit.GetCommittedParam(CyPinData.Formal_ParamName_NumPins).TryGetValueAs<byte>(out numPins);
            Trace.Assert(err.IsOk, err.Message);
            Trace.Assert(numPins == TOTAL_NUM_TEST_PINS);

            //Set up all the pin types at once.
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_PinTypes, pins);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            //Check the pin set up is correct.
            //string[] expectedValues = pins.Split(',');
            //CheckWarpValuesNonBitVector(instEdit, "pin_types", expectedValues);
        }

        static void CheckInputBufferEnabled(ICyInstEdit_v1 instEdit)
        {
            //From the test settings, the default value for buffer enabled should be 
            //True for the first 8 pins, false for the rest 5 pins).
            bool[] expectedValues = new bool[] {
                true, true, true, true, true, true, true, true, true, true, true, true, false};

            CheckPinSetting validator = delegate(CyPinData.PerPin pin)
            {
                return (pin.InputBufferEnabled == expectedValues[pin.Index]);
            };
            Check(instEdit, validator);
        }

        static void CheckDriveModes(ICyInstEdit_v1 instEdit)
        {
            string[] expectedValues = new string[] {CyPinData.DriveModeValue_DIGITAL_HI_Z, 
                                                    CyPinData.DriveModeValue_DIGITAL_HI_Z,
                                                    CyPinData.DriveModeValue_OPEN_DRAIN_LO, 
                                                    CyPinData.DriveModeValue_OPEN_DRAIN_LO,
                                                    CyPinData.DriveModeValue_CMOS_OUT, 
                                                    CyPinData.DriveModeValue_CMOS_OUT,
                                                    CyPinData.DriveModeValue_CMOS_OUT,
                                                    CyPinData.DriveModeValue_CMOS_OUT,
                                                    CyPinData.DriveModeValue_CMOS_OUT,
                                                    CyPinData.DriveModeValue_CMOS_OUT,
                                                    CyPinData.DriveModeValue_CMOS_OUT,
                                                    CyPinData.DriveModeValue_CMOS_OUT,
                                                    CyPinData.DriveModeValue_ANALOG_HI_Z};
            CheckWarpValuesNonBitVector(instEdit, CyParameters.Local_ParamName_DriveMode, expectedValues);
        }

        static void CheckInitDriveStates(ICyInstEdit_v1 instEdit)
        {
            string driveModes = string.Format("{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}",
                CyPinData.DriveModeValue_DIGITAL_HI_Z,
                CyPinData.DriveModeValue_DIGITAL_HI_Z,
                CyPinData.DriveModeValue_CMOS_OUT,
                CyPinData.DriveModeValue_DIGITAL_HI_Z,
                CyPinData.DriveModeValue_OPEN_DRAIN_HI,
                CyPinData.DriveModeValue_OPEN_DRAIN_LO,
                CyPinData.DriveModeValue_RES_PULL_DOWN,
                CyPinData.DriveModeValue_RES_PULL_UP,
                CyPinData.DriveModeValue_RES_PULL_UP_DOWN,
                CyPinData.DriveModeValue_OPEN_DRAIN_HI,
                CyPinData.DriveModeValue_OPEN_DRAIN_LO,
                CyPinData.DriveModeValue_RES_PULL_UP,
                CyPinData.DriveModeValue_ANALOG_HI_Z);

            bool result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_DriveMode, driveModes);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            string[] expectedValues = new string[] {CyPinData.InitialDriveStateValue_LOW,
                                                    CyPinData.InitialDriveStateValue_LOW,
                                                    CyPinData.InitialDriveStateValue_LOW,
                                                    CyPinData.InitialDriveStateValue_LOW,
                                                    CyPinData.InitialDriveStateValue_LOW,
                                                    CyPinData.InitialDriveStateValue_LOW,
                                                    CyPinData.InitialDriveStateValue_LOW,
                                                    CyPinData.InitialDriveStateValue_HIGH,
                                                    CyPinData.InitialDriveStateValue_HIGH,
                                                    CyPinData.InitialDriveStateValue_LOW,
                                                    CyPinData.InitialDriveStateValue_LOW,
                                                    CyPinData.InitialDriveStateValue_HIGH,
                                                    CyPinData.InitialDriveStateValue_LOW};

            CheckWarpValuesNonBitVector(instEdit, CyParameters.Local_ParamName_InitialDriveStates, expectedValues);

            string defaultDriveMode = string.Format("{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}",
                                                    CyPinData.DriveModeValue_DIGITAL_HI_Z,
                                                    CyPinData.DriveModeValue_DIGITAL_HI_Z,
                                                    CyPinData.DriveModeValue_OPEN_DRAIN_LO,
                                                    CyPinData.DriveModeValue_OPEN_DRAIN_LO,
                                                    CyPinData.DriveModeValue_CMOS_OUT,
                                                    CyPinData.DriveModeValue_CMOS_OUT,
                                                    CyPinData.DriveModeValue_CMOS_OUT,
                                                    CyPinData.DriveModeValue_CMOS_OUT,
                                                    CyPinData.DriveModeValue_CMOS_OUT,
                                                    CyPinData.DriveModeValue_CMOS_OUT,
                                                    CyPinData.DriveModeValue_CMOS_OUT,
                                                    CyPinData.DriveModeValue_CMOS_OUT,
                                                    CyPinData.DriveModeValue_ANALOG_HI_Z);

            //Set it back to default value in case it messed up the later test.
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_DriveMode, defaultDriveMode);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();
        }

        static void CheckInputRestrictSettings(ICyInstEdit_v1 instEdit)
        {
            string setupValue;

            //Input only parameters:
            //DisplayInputHWConnections(We don't test this parameter because we don't set it in Warp.It's front-end only).
            //HotSwaps
            //InputBuffersEnabled
            //InputSyncs
            //InterruptModes
            //ThresholdLevels

            //For all the above parameters, if pinType is one of the input types, 
            //they should be set to the user's preference. 
            //Otherwise, they should be set to default values.
            //From the test settings, the first 8 pins contains input types, so they should be set to user's preference,
            //the rest 5 pins contains output types only so they should be set to default.

            //HotSwaps=========================================================================================
            string hotswapSetupValue =
                string.Format("{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}",
                CyPinData.ParamValue_TRUE,
                CyPinData.ParamValue_FALSE,
                CyPinData.ParamValue_TRUE,
                CyPinData.ParamValue_FALSE,
                CyPinData.ParamValue_TRUE,
                CyPinData.ParamValue_FALSE,
                CyPinData.ParamValue_TRUE,
                CyPinData.ParamValue_FALSE,
                CyPinData.ParamValue_TRUE,
                CyPinData.ParamValue_FALSE,
                CyPinData.ParamValue_TRUE,
                CyPinData.ParamValue_FALSE,
                CyPinData.ParamValue_FALSE);
            bool result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_HotSwaps, hotswapSetupValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            bool[] hotSwapsExpectedValues = new bool[] { 
                true, false, true, false, true, false, true, false, false, false, false, false, false};
            CheckPinSetting validator = delegate(CyPinData.PerPin pin)
            {
                return (pin.InputHotSwap == hotSwapsExpectedValues[pin.Index]);
            };
            Check(instEdit, validator);

            //Restore back to default
            CreateUnitTestParamArrayValue(CyPinData.DefaultHotSwapValue, out setupValue);
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_HotSwaps, setupValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            //InputBuffersEnabled===================================================================================

            CreateUnitTestParamArrayValue(CyPinData.ParamValue_FALSE, out setupValue);
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_InputBuffersEnabled, setupValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            string[] InputBufferEnabledExpectedValues = new string[] {CyPinData.ParamValue_FALSE, 
                                                                      CyPinData.ParamValue_FALSE,
                                                                      CyPinData.ParamValue_FALSE,
                                                                      CyPinData.ParamValue_FALSE,
                                                                      CyPinData.ParamValue_FALSE,
                                                                      CyPinData.ParamValue_FALSE,
                                                                      CyPinData.ParamValue_FALSE,
                                                                      CyPinData.ParamValue_FALSE,
                                                                      CyPinData.ParamValue_TRUE,
                                                                      CyPinData.ParamValue_TRUE,
                                                                      CyPinData.ParamValue_TRUE,
                                                                      CyPinData.ParamValue_TRUE,
                                                                      CyPinData.ParamValue_FALSE};

            CheckWarpValuesNonBitVector(instEdit, CyParameters.Local_ParamName_InputBuffersEnabled, InputBufferEnabledExpectedValues);

            CreateUnitTestParamArrayValue(CyPinData.ParamValue_TRUE, out setupValue);
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_InputBuffersEnabled, setupValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            //InputSyncs==========================================================================================
            CreateUnitTestParamArrayValue(CyPinData.ParamValue_DISABLED, out setupValue);
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_InputsSynchronized, setupValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            string[] InputSyncsExpectedValues = new string[] {CyPinData.ParamValue_DISABLED,
                                                              CyPinData.ParamValue_DISABLED,
                                                              CyPinData.ParamValue_DISABLED,
                                                              CyPinData.ParamValue_DISABLED,
                                                              CyPinData.ParamValue_DISABLED,
                                                              CyPinData.ParamValue_DISABLED,
                                                              CyPinData.ParamValue_DISABLED,
                                                              CyPinData.ParamValue_DISABLED,
                                                              CyPinData.ParamValue_ENABLED,
                                                              CyPinData.ParamValue_ENABLED,
                                                              CyPinData.ParamValue_ENABLED,
                                                              CyPinData.ParamValue_ENABLED,
                                                              CyPinData.ParamValue_ENABLED};


            CheckWarpValuesNonBitVector(instEdit, CyParameters.Local_ParamName_InputsSynchronized, InputSyncsExpectedValues);

            CreateUnitTestParamArrayValue(CyPinData.ParamValue_ENABLED, out setupValue);
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_InputsSynchronized, setupValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            //InterruptModes===================================================================================
            CreateUnitTestParamArrayValue(CyPinData.InterruptModeValue_RISING_EDGE, out setupValue);
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_InterruptMode, setupValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            string[] InterruptModesExpectedValues = new string[] {CyPinData.InterruptModeValue_RISING_EDGE, 
                                                                  CyPinData.InterruptModeValue_RISING_EDGE,
                                                                  CyPinData.InterruptModeValue_RISING_EDGE,
                                                                  CyPinData.InterruptModeValue_RISING_EDGE,
                                                                  CyPinData.InterruptModeValue_RISING_EDGE,
                                                                  CyPinData.InterruptModeValue_RISING_EDGE,
                                                                  CyPinData.InterruptModeValue_RISING_EDGE,
                                                                  CyPinData.InterruptModeValue_RISING_EDGE,
                                                                  CyPinData.InterruptModeValue_NONE,
                                                                  CyPinData.InterruptModeValue_NONE,
                                                                  CyPinData.InterruptModeValue_NONE,
                                                                  CyPinData.InterruptModeValue_NONE,
                                                                  CyPinData.InterruptModeValue_NONE};

            CheckWarpValuesNonBitVector(instEdit, CyParameters.Local_ParamName_InterruptMode, InterruptModesExpectedValues);

            CreateUnitTestParamArrayValue(CyPinData.DefaultInterruptModeValue, out setupValue);
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_InterruptMode, setupValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();


            //ThresholdLevels===================================================================================
            CreateUnitTestParamArrayValue(CyPinData.ThresholdLevelValue_LVTTL, out setupValue);
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_ThresholdLevels, setupValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            CyInputThreshold[] ThresholdLevelsExpectedValues = new CyInputThreshold[] {
                CyInputThreshold.LVTTL,
                CyInputThreshold.LVTTL,
                CyInputThreshold.LVTTL,
                CyInputThreshold.LVTTL,
                CyInputThreshold.LVTTL,
                CyInputThreshold.LVTTL,
                CyInputThreshold.LVTTL,
                CyInputThreshold.LVTTL,
                CyInputThreshold.CMOS_LVTTL,
                CyInputThreshold.CMOS_LVTTL,
                CyInputThreshold.CMOS_LVTTL,
                CyInputThreshold.CMOS_LVTTL,
                CyInputThreshold.CMOS_LVTTL};

            validator = delegate(CyPinData.PerPin pin)
            {
                return (pin.InputThreshold == ThresholdLevelsExpectedValues[pin.Index]);
            };
            Check(instEdit, validator);

            CreateUnitTestParamArrayValue(CyPinData.DefaultThresholdLevelValue, out setupValue);
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_ThresholdLevels, setupValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();
        }

        static void CheckOutputRestrictSettings(ICyInstEdit_v1 instEdit)
        {
            string setupValue;

            //Output only parameters:
            //DisplayOutputHWConnections(We don't test this parameter because we don't set it in Warp.)
            //DriveCurrents
            //OutputDriveLevels
            //OutputSyncs
            //SlewRates

            //For all the above parameters, if pinType is one of the output types, 
            //they should be set to the user's preference.
            //Otherwise, they should be set to default values.
            //From the test settings, the first 2 pins contains input types only, so they should be set to default,
            //the rest 10 pins contains output types, so they should be set to use's preference. The last one
            //is analog, so should be set to default.

            //DriveCurrents===================================================================================
            string driveCurrentsSetupValue =
                string.Format("{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}",
                CyPinData.DriveCurrentValue_4SOURCE_25SINK,
                CyPinData.DriveCurrentValue_4SOURCE_8SINK,
                CyPinData.DriveCurrentValue_4SOURCE_25SINK,
                CyPinData.DriveCurrentValue_4SOURCE_8SINK,
                CyPinData.DriveCurrentValue_4SOURCE_25SINK,
                CyPinData.DriveCurrentValue_4SOURCE_8SINK,
                CyPinData.DriveCurrentValue_4SOURCE_25SINK,
                CyPinData.DriveCurrentValue_4SOURCE_8SINK,
                CyPinData.DriveCurrentValue_4SOURCE_25SINK,
                CyPinData.DriveCurrentValue_4SOURCE_8SINK,
                CyPinData.DriveCurrentValue_4SOURCE_25SINK,
                CyPinData.DriveCurrentValue_4SOURCE_8SINK,
                CyPinData.DriveCurrentValue_4SOURCE_8SINK);
            bool result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_DriveCurrents, driveCurrentsSetupValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            CyOutputCurrent[] driveCurrentsExpectedValues = new CyOutputCurrent[] {
                CyOutputCurrent.SOURCE_4MA_SINK_8MA, 
                CyOutputCurrent.SOURCE_4MA_SINK_8MA, 
                CyOutputCurrent.SOURCE_4MA_SINK_25MA, 
                CyOutputCurrent.SOURCE_4MA_SINK_8MA, 
                CyOutputCurrent.SOURCE_4MA_SINK_25MA, 
                CyOutputCurrent.SOURCE_4MA_SINK_8MA, 
                CyOutputCurrent.SOURCE_4MA_SINK_25MA, 
                CyOutputCurrent.SOURCE_4MA_SINK_8MA, 
                CyOutputCurrent.SOURCE_4MA_SINK_25MA, 
                CyOutputCurrent.SOURCE_4MA_SINK_8MA, 
                CyOutputCurrent.SOURCE_4MA_SINK_25MA, 
                CyOutputCurrent.SOURCE_4MA_SINK_8MA, 
                CyOutputCurrent.SOURCE_4MA_SINK_8MA};

            CheckPinSetting validator = delegate(CyPinData.PerPin pin)
            {
                return (pin.OutputCurrent == driveCurrentsExpectedValues[pin.Index]);
            };
            Check(instEdit, validator);

            //Set back to default.
            CreateUnitTestParamArrayValue(CyPinData.DefaultDriveCurrentValue, out setupValue);
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_DriveCurrents, setupValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            //OutputDriveLevels==================================================================================
            string driveLevelSetupValue =
               string.Format("{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}",
                              CyPinData.OutputDriveLevelValue_VREF,
                              CyPinData.OutputDriveLevelValue_VDDIO,
                              CyPinData.OutputDriveLevelValue_VREF,
                              CyPinData.OutputDriveLevelValue_VDDIO,
                              CyPinData.OutputDriveLevelValue_VREF,
                              CyPinData.OutputDriveLevelValue_VDDIO,
                              CyPinData.OutputDriveLevelValue_VREF,
                              CyPinData.OutputDriveLevelValue_VDDIO,
                              CyPinData.OutputDriveLevelValue_VREF,
                              CyPinData.OutputDriveLevelValue_VDDIO,
                              CyPinData.OutputDriveLevelValue_VREF,
                              CyPinData.OutputDriveLevelValue_VDDIO,
                              CyPinData.OutputDriveLevelValue_VDDIO);
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_OutputDriveLevels, driveLevelSetupValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            CyOutputDriveLevel[] outputDriveLevelsExpectedValues = new CyOutputDriveLevel[] {
                CyOutputDriveLevel.VDDIO,
                CyOutputDriveLevel.VDDIO,
                CyOutputDriveLevel.VREF,
                CyOutputDriveLevel.VDDIO,
                CyOutputDriveLevel.VREF,
                CyOutputDriveLevel.VDDIO,
                CyOutputDriveLevel.VREF,
                CyOutputDriveLevel.VDDIO,
                CyOutputDriveLevel.VREF,
                CyOutputDriveLevel.VDDIO,
                CyOutputDriveLevel.VREF,
                CyOutputDriveLevel.VDDIO,
                CyOutputDriveLevel.VDDIO};

            validator = delegate(CyPinData.PerPin pin)
            {
                return (pin.OutputDriveLevel == outputDriveLevelsExpectedValues[pin.Index]);
            };
            Check(instEdit, validator);

            CreateUnitTestParamArrayValue(CyPinData.DefaultOutputDriveLevelValue, out setupValue);
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_OutputDriveLevels, setupValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            //OutputSyncs=========================================================================================
            CreateUnitTestParamArrayValue(CyPinData.ParamValue_ENABLED, out setupValue);
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_OutputsSynchronized, setupValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            string[] outputSyncsExpectedValues = new string[] {CyPinData.ParamValue_DISABLED,
                                                               CyPinData.ParamValue_DISABLED,
                                                               CyPinData.ParamValue_ENABLED,
                                                               CyPinData.ParamValue_ENABLED,
                                                               CyPinData.ParamValue_ENABLED,
                                                               CyPinData.ParamValue_ENABLED,
                                                               CyPinData.ParamValue_ENABLED,
                                                               CyPinData.ParamValue_ENABLED,
                                                               CyPinData.ParamValue_ENABLED,
                                                               CyPinData.ParamValue_ENABLED,
                                                               CyPinData.ParamValue_ENABLED,
                                                               CyPinData.ParamValue_ENABLED,
                                                               CyPinData.ParamValue_DISABLED};

            CheckWarpValuesNonBitVector(instEdit, CyParameters.Local_ParamName_OutputsSynchronized, outputSyncsExpectedValues);

            CreateUnitTestParamArrayValue(CyPinData.DefaultOutputsSynchronizedValue, out setupValue);
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_OutputsSynchronized, setupValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            //SlewRates=====================================================================================
            CreateUnitTestParamArrayValue(CyPinData.SlewRateValue_SLOW, out setupValue);
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_SlewRate, setupValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();

            string[] slewRatesExpectedValues = new string[] {CyPinData.SlewRateValue_FAST, 
                                                             CyPinData.SlewRateValue_FAST,
                                                             CyPinData.SlewRateValue_SLOW,
                                                             CyPinData.SlewRateValue_SLOW,
                                                             CyPinData.SlewRateValue_SLOW,
                                                             CyPinData.SlewRateValue_SLOW,
                                                             CyPinData.SlewRateValue_SLOW,
                                                             CyPinData.SlewRateValue_SLOW,
                                                             CyPinData.SlewRateValue_SLOW,
                                                             CyPinData.SlewRateValue_SLOW,
                                                             CyPinData.SlewRateValue_SLOW,
                                                             CyPinData.SlewRateValue_SLOW,
                                                             CyPinData.SlewRateValue_FAST};

            CheckWarpValuesNonBitVector(instEdit, CyParameters.Local_ParamName_SlewRate, slewRatesExpectedValues);

            CreateUnitTestParamArrayValue(CyPinData.DefaultSlewRateValue, out setupValue);
            result = instEdit.SetParamExpr(CyPinData.Formal_ParamName_SlewRate, setupValue);
            Trace.Assert(result, "param was not set");
            instEdit.CommitParamExprs();
        }

        private delegate bool CheckPinSetting(CyPinData.PerPin pin);
        /// <summary>
        /// This function is used to check paramters which never gets send to warp. 
        /// These params (HotSwaps, ThresholdLevels, etc) are usually used to determine other params
        /// which are needed by warp. So verify with this method.
        /// </summary>
        static void Check(ICyInstQuery_v1 query, CheckPinSetting validator)
        {
            CyPinData pins = new CyPinData(query);
            foreach (CyPinData.PerPin pin in pins.Pins)
                Trace.Assert(validator(pin), "Failed to correctly split values");
            /*
            IDictionary<string, string> locals = CyParameters.GenerateVerilogGenerics(pins, false);
            Trace.Assert(locals.ContainsKey(paramName), "Could not find parameter information for: " + paramName);
            string value = locals[paramName];

            string[] values = value.Split(',');
            Trace.Assert(values.Length == expectedVals.Count, "Failed to correctly split values");
            for (int i = 0; i < expectedVals.Count; i++)
                Trace.Assert(values[i].Trim() == expectedVals[i].Trim());
             */
        }

        /// <summary>
        /// This function is used to check paramters which never gets send to warp. 
        /// These params (HotSwaps, ThresholdLevels, etc) are usually used to determine other params
        /// which are needed by warp. So verify with this method.
        /// </summary>
        static void CheckFormal(ICyInstQuery_v1 query, string paramName, IList<string> expectedVals)
        {
            string[] values = query.GetCommittedParam(paramName).Value.Split(',');
            Trace.Assert(values.Length == expectedVals.Count, "Failed to correctly split values");
            for (int i = 0; i < expectedVals.Count; i++)
                Trace.Assert(values[i].Trim() == expectedVals[i].Trim());
        }

        /// <summary>
        /// This method is used to check some params which get send to warp but they are not bit vectors.
        /// </summary>
        static void CheckWarpValuesNonBitVector(ICyInstQuery_v1 query, string paramName, IList<string> expectedValues)
        {
            CyPinData pins = new CyPinData(query);
            IDictionary<string, string> locals = CyParameters.GenerateVerilogGenerics(pins, query.DeviceQuery);
            Trace.Assert(locals.ContainsKey(paramName), "Could not find parameter information for: " + paramName);
            string value = locals[paramName];

            value = value.Substring(value.IndexOf("'b") + 2);
            string[] values = value.Split('_');
            Trace.Assert(values.Length == expectedValues.Count, "Fail to correctly split values");
            for (int i = 0; i < expectedValues.Count; i++)
                Trace.Assert(values[i].Trim() == expectedValues[i].Trim());
        }

        /// <summary>
        /// This method is used to check some params which get send to warp and they are bit vectors.
        /// </summary>
        static void CheckWarpValuesBitVector(ICyInstQuery_v1 query, string paramName, IList<string> expectedValues)
        {
            CyPinData pins = new CyPinData(query);
            IDictionary<string, string> locals = CyParameters.GenerateVerilogGenerics(pins, query.DeviceQuery);
            Trace.Assert(locals.ContainsKey(paramName), "Could not find parameter information for: " + paramName);
            string value = locals[paramName];

            string[] tempValues = value.Split('b');
            Trace.Assert(tempValues.Length > 0);
            string[] values = tempValues[tempValues.Length - 1].Split('_');
            Trace.Assert(values.Length == expectedValues.Count, "Fail to correctly split values");
            for (int i = 0; i < expectedValues.Count; i++)
                Trace.Assert(values[i].Trim() == expectedValues[i].Trim());
        }

        static void CreateUnitTestParamArrayValue(string paramValue, out string paramValues)
        {
            string[] values = new string[TOTAL_NUM_TEST_PINS];
            for (int i = 0; i < TOTAL_NUM_TEST_PINS; i++)
            {
                values[i] = paramValue;
            }
            paramValues = string.Join(",", values);
        }
        #endregion
    }

    class CyTermInfo
    {
        public const string RootTermName_OE = "oe";
        public const string RootTermName_Output = "y";
        public const string RootTermName_Input = "fb";
        public const string RootTermName_Analog = "analog";
        public const string RootTermName_BiDir = "io";
        public const string RootTermName_SIOVRef = "siovref";
        public const string RootTermName_Interrupt = "interrupt";
        public const string RootTermName_Annotation = "external";
        public const string RootTermName_InClock = "in_clock";
        public const string RootTermName_InClockEn = "in_clock_en";
        public const string RootTermName_InReset = "in_reset";
        public const string RootTermName_OutClock = "out_clock";
        public const string RootTermName_OutClockEn = "out_clock_en";
        public const string RootTermName_OutReset = "out_reset";

        public static IEnumerable<string> TerminalRootNames
        {
            get
            {
                yield return RootTermName_OE;
                yield return RootTermName_Output;
                yield return RootTermName_Input;
                yield return RootTermName_Analog;
                yield return RootTermName_BiDir;
                yield return RootTermName_SIOVRef;
                yield return RootTermName_Interrupt;
                yield return RootTermName_Annotation;
                yield return RootTermName_InClock;
                yield return RootTermName_InClockEn;
                yield return RootTermName_InReset;
                yield return RootTermName_OutClock;
                yield return RootTermName_OutClockEn;
                yield return RootTermName_OutReset;
            }
        }

        public static CyCustErr GetExpectedTerminalWidth(CyPinData pins, string rootTermName, out byte numPins)
        {
            CyCustErr err = CyCustErr.Ok;
            if (rootTermName == RootTermName_OE ||
                rootTermName == RootTermName_Output ||
                rootTermName == RootTermName_Input ||
                rootTermName == RootTermName_Analog ||
                rootTermName == RootTermName_BiDir ||
                rootTermName == RootTermName_Annotation)
            {
                numPins = (byte)pins.PinCount;
            }
            else if (rootTermName == RootTermName_SIOVRef)
            {
                numPins = pins.GetSioGroupCnt();
            }
            else if (rootTermName == RootTermName_Interrupt ||
                rootTermName == RootTermName_InClock ||
                rootTermName == RootTermName_InClockEn ||
                rootTermName == RootTermName_InReset ||
                rootTermName == RootTermName_OutClock ||
                rootTermName == RootTermName_OutClockEn ||
                rootTermName == RootTermName_OutReset)
            {
                numPins = 1;
            }
            else
            {
                numPins = default(byte);
                err = new CyCustErr(string.Format(Resource1.UnknownTerm, rootTermName));
            }
            return err;
        }

        internal static bool IsInput(string rootTermName)
        {
            return rootTermName == RootTermName_Output ||
                   rootTermName == RootTermName_OE ||
                   rootTermName == RootTermName_InClock ||
                   rootTermName == RootTermName_InClockEn ||
                   rootTermName == RootTermName_InReset ||
                   rootTermName == RootTermName_OutClock ||
                   rootTermName == RootTermName_OutClockEn ||
                   rootTermName == RootTermName_OutReset;
        }
        internal static bool IsAnalog(string rootTermName)
        {
            return (rootTermName == RootTermName_Analog ||
                    rootTermName == RootTermName_SIOVRef ||
                    rootTermName == RootTermName_Annotation);
        }
    }
}
