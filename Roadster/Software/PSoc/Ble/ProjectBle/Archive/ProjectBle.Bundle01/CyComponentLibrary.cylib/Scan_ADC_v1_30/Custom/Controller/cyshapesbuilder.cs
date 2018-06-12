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
using System.Drawing.Drawing2D;
using System.Text;
using System.Windows.Forms;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

// The namespace is required to have the same name as the component for a customizer.
namespace Scan_ADC_v1_30
{
    public class CyShapesBuilder
    {
        private CyParameters m_params;
        private ICySymbolShapeEdit_v2 m_shapeEdit;
        private ICyTerminalEdit_v2 m_termEdit;
        private CyShapesInfo m_shapeInfo;

        #region Shape tags
        private const string BODY_SHAPE_TAG = "body";
        private const string LAYOUT_SHAPE_TAG = "layout";
        private const string CONFIG_1_SHAPE_TAG = "sarmux1";
        private const string CONFIG_2_SHAPE_TAG = "sarmux2";
        private const string CONFIG_3_SHAPE_TAG = "sarmux3";
        private const string CONFIG_4_SHAPE_TAG = "sarmux4";
        private const string ANALOG_WIRE_TAG = "analog_wire";
        private const string ANALOG_DOT_TAG = "analog_dot";
        private readonly string[] CONFIG_SHAPE_TAGS = null;
        #endregion

        #region Shape Properties
        private static float CREATOR_BODY_STROKE_WEIGHT = 1.0f;
        private static float CREATOR_ANALOGGLYPH_STROKE_WEIGHT = 0.5f;
        private float CREATOR_ANALOGWIRE_STROKE_WEIGHT;
        private float CREATOR_ANALOGDOT_STROKE_WEIGHT;

        #endregion Shape Properties
        #region Shape colors
        private static Color CREATOR_BODY_FILL_COLOR = Color.FromArgb(220, 220, 220);
        private static Color CREATOR_BODY_STROKE_COLOR = Color.FromArgb(0, 0, 0);
        private static Color CREATOR_ANALOGHEADER_FILL_COLOR = Color.FromArgb(255, 255, 128);
        private static Color CREATOR_ANALOGHEADER_STROKE_COLOR = Color.FromArgb(0, 0, 0);
        private static Color CREATOR_ANALOGGLYPH_FILL_COLOR = Color.FromArgb(0, 255, 255);
        private static Color CREATOR_ANALOGGLYPH_STROKE_COLOR = Color.FromArgb(0, 0, 0);

        private Color LAYOUT_FILL_COLOR = CREATOR_ANALOGGLYPH_FILL_COLOR;
        private Color CREATOR_FONT_COLOR; /* Set by design preference. */
        private Color CREATOR_ANALOGWIRE_COLOR; /* Set by design preference. */
        private Color CONFIG_1_COLOR = CREATOR_ANALOGGLYPH_FILL_COLOR;
        // To change shade of configs, use: Color.FromArgb(CREATOR_ANALOGGLYPH_FILL_COLOR.ToArgb() - 0x00002020);
        private Color CONFIG_2_COLOR = CREATOR_ANALOGGLYPH_FILL_COLOR; 
        private Color CONFIG_3_COLOR = CREATOR_ANALOGGLYPH_FILL_COLOR; 
        private Color CONFIG_4_COLOR = CREATOR_ANALOGGLYPH_FILL_COLOR; 
        private Color[] CONFIG_COLORS = null;
        #endregion

        #region Shape fonts
        private readonly Font ANNOTATIONS_FONT = new Font(FontFamily.GenericSansSerif, 10f, FontStyle.Regular, GraphicsUnit.Point, 1, false);
        #endregion

        #region Shape unit constants
        private readonly float BASE_UNIT;
        private readonly float TERM_SOLO_STEP;
        private readonly float TERM_SOLO_PAD;
        private readonly float TERM_PAIR_STEP;
        private readonly float TERM_PAIR_PAD;
        private readonly float SARMUX_FINHEIGHT;
        private readonly float SARMUX_WIDTH;
        private readonly float SAR_HEIGHT_DIV_4;
        private readonly float SAR_WIDTH;
        private readonly float CONFIG_WIDTH;
        private readonly float CONFIG_SPACING;
        private readonly float MUX_YOFFSET;

        private readonly PointF BASE_LOCATION;
        #endregion

        #region Terminal names
        private readonly string SOC_TERM_NAME = "soc";
        private readonly string CLK_TERM_NAME = "aclk";
        private readonly string VREF_TERM_NAME = "vref";
        private readonly string AGND_TERM_NAME = "vagnd";
        private readonly string SDONE_TERM_NAME = "sdone";
        private readonly string EOS_TERM_NAME = "eos";
        private readonly string VIN_PLUS_PREFIX = "vinPlus";
        private readonly string VIN_MINUS_PREFIX = "vinMinus";
        private readonly string VIN_NEG_PREFIX = "vinNeg";
        private readonly string CHIDVAL_TERM_NAME = "t_chidv";
        private readonly string CHID_TERM_NAME = "t_chid";
        private readonly string DATAVAL_TERM_NAME = "t_dav";
        private readonly string DATA_TERM_NAME = "t_da";
        private readonly string FIL_VOUT_TERM_NAME = "t_fvout";
        private readonly string FIL_VALID_TERM_NAME = "t_fvalid";
        private readonly string FIL_VINTERNAL_TERM_NAME = "t_fvinternal[1:0]";
        #endregion

        #region Constructor(s)
        public CyShapesBuilder(CyParameters parameters, ICySymbolShapeEdit_v2 shapeEd, 
            ICyTerminalEdit_v2 termEd, CyShapesInfo shapeInfo)
        {
            m_params = parameters;
            m_shapeEdit = shapeEd;
            m_termEdit = termEd;
            m_shapeInfo = shapeInfo;

            CREATOR_FONT_COLOR = parameters.InstQuery.Preferences.TerminalFontColor;
            CREATOR_ANALOGWIRE_COLOR = parameters.InstQuery.Preferences.AnalogWireColor;
            CREATOR_ANALOGWIRE_STROKE_WEIGHT = parameters.InstQuery.Preferences.WireSize;
            CREATOR_ANALOGDOT_STROKE_WEIGHT = parameters.InstQuery.Preferences.WireDotSize;

            CONFIG_SHAPE_TAGS = new string[] {CONFIG_1_SHAPE_TAG, CONFIG_2_SHAPE_TAG, CONFIG_3_SHAPE_TAG, CONFIG_4_SHAPE_TAG};
            CONFIG_COLORS = new Color[] {CONFIG_1_COLOR, CONFIG_2_COLOR, CONFIG_3_COLOR, CONFIG_4_COLOR };

            BASE_UNIT = m_shapeEdit.UserBaseUnit;
            TERM_SOLO_STEP = 2 * BASE_UNIT;
            TERM_SOLO_PAD = BASE_UNIT;
            TERM_PAIR_STEP = BASE_UNIT;
            TERM_PAIR_PAD = 2 * BASE_UNIT;
            SARMUX_FINHEIGHT = 2 * BASE_UNIT;
            SARMUX_WIDTH = 3 * BASE_UNIT;
            SAR_HEIGHT_DIV_4 = BASE_UNIT;
            SAR_WIDTH = 7 * BASE_UNIT;
            CONFIG_WIDTH = 15 * BASE_UNIT;
            CONFIG_SPACING = shapeInfo.ConfigSpace * BASE_UNIT;
            MUX_YOFFSET = 8 * BASE_UNIT;
            BASE_LOCATION = new PointF(0.0f, 0.0f);
        }
        #endregion


        public void DrawSymbol()
        {
            int configCount = m_shapeInfo.ConfigCount;

            m_termEdit.RemoveAllTerminals();
            m_shapeEdit.RemoveAllShapes();
                        
            DrawCommonTerminals();

            List<float> configHeight = new List<float> { };
            int baseRawChannel = 0;
            for (int configNum = 0; configNum < configCount; configNum++)
            {
                PointF configLocation = new PointF( configNum * (CONFIG_SPACING + CONFIG_WIDTH), BASE_LOCATION.Y);
                RectangleF rect = DrawSarMuxConfig(configNum, baseRawChannel, configLocation);
                configHeight.Add(rect.Height);
                baseRawChannel += m_shapeInfo.ChannelCounts[configNum];
            }

            float bodyWidth = configCount * CONFIG_WIDTH + (configCount - 1) * CONFIG_SPACING;
            float bodyHeight = configHeight[0];
            for( int i=1; i<configCount; i++)
            {
                if(configHeight[i]>bodyHeight)
                {
                    bodyHeight = configHeight[i];
                }
            }

        }

        /* Draws the common terminals, eoc, sdone, ?soc, ?aclk. Draws divider line. */
        private RectangleF DrawCommonTerminals()
        {
            PointF location;

            // Add fixed sdone output terminal.
            SizeF tmpOffset = new SizeF(CONFIG_WIDTH + BASE_UNIT, 3.0f * BASE_UNIT);
            location = BASE_LOCATION + tmpOffset;
            m_termEdit.TerminalAdd(SDONE_TERM_NAME, CyCompDevTermDir.OUTPUT, 
                CyCompDevTermType.DIGITAL, location, string.Empty, 0f, true);

            // Add fixed eoc output terminal.
            tmpOffset.Height += TERM_SOLO_STEP; //Add a step down to the offset.
            location = PointF.Add(BASE_LOCATION, tmpOffset);
            m_termEdit.TerminalAdd(EOS_TERM_NAME, CyCompDevTermDir.OUTPUT, 
                CyCompDevTermType.DIGITAL, location, string.Empty, 0f, true);

            // Add optional test terminals
            var testPoint = location + new SizeF(0f, 2f * BASE_UNIT);
            m_termEdit.TerminalAdd(CHIDVAL_TERM_NAME, CyCompDevTermDir.OUTPUT,
            CyCompDevTermType.DIGITAL, testPoint, string.Empty, 0f, true);
            testPoint += new SizeF(0f, 2f * BASE_UNIT);
            m_termEdit.TerminalAdd(CHID_TERM_NAME, CyCompDevTermDir.OUTPUT,
            CyCompDevTermType.DIGITAL, testPoint, string.Empty, 0f, true);
            testPoint += new SizeF(0f, 2f * BASE_UNIT);
            m_termEdit.TerminalAdd(DATAVAL_TERM_NAME, CyCompDevTermDir.OUTPUT,
            CyCompDevTermType.DIGITAL, testPoint, string.Empty, 0f, true);
            testPoint += new SizeF(0f, 2f * BASE_UNIT);
            m_termEdit.TerminalAdd(DATA_TERM_NAME, CyCompDevTermDir.OUTPUT,
            CyCompDevTermType.DIGITAL, testPoint, string.Empty, 0f, true);
            testPoint += new SizeF(0f, 2f * BASE_UNIT);
            m_termEdit.TerminalAdd(FIL_VOUT_TERM_NAME, CyCompDevTermDir.OUTPUT,
            CyCompDevTermType.ANALOG, testPoint, string.Empty, 0f, true);
            testPoint += new SizeF(0f, 2f * BASE_UNIT);
            m_termEdit.TerminalAdd(FIL_VALID_TERM_NAME, CyCompDevTermDir.OUTPUT,
            CyCompDevTermType.DIGITAL, testPoint, string.Empty, 0f, true);
            testPoint += new SizeF(0f, 2f * BASE_UNIT);
            m_termEdit.TerminalAdd(FIL_VINTERNAL_TERM_NAME, CyCompDevTermDir.OUTPUT,
            CyCompDevTermType.ANALOG, testPoint, string.Empty, 0f, true);

            if (!m_shapeInfo.ExposeTestTerminals)
            {
                m_termEdit.ChangeTerminalVisibilityExpr(CHIDVAL_TERM_NAME, "false");
                m_termEdit.ChangeTerminalVisibilityExpr(CHID_TERM_NAME, "false");
                m_termEdit.ChangeTerminalVisibilityExpr(DATAVAL_TERM_NAME, "false");
                m_termEdit.ChangeTerminalVisibilityExpr(DATA_TERM_NAME, "false");
                m_termEdit.ChangeTerminalVisibilityExpr(FIL_VOUT_TERM_NAME, "false");
                m_termEdit.ChangeTerminalVisibilityExpr(FIL_VALID_TERM_NAME, "false");
                m_termEdit.ChangeTerminalVisibilityExpr(FIL_VINTERNAL_TERM_NAME, "false");
            }

            // Add optional soc input terminal.
            tmpOffset = new SizeF(-1 * BASE_UNIT, 3.0f * BASE_UNIT);
            location = BASE_LOCATION + tmpOffset;
            if (m_shapeInfo.ShowSocTerm)
            {
                m_termEdit.TerminalAdd(SOC_TERM_NAME, CyCompDevTermDir.INPUT,
                    CyCompDevTermType.DIGITAL, location, string.Empty, 0f, true);
                m_termEdit.SetMustConnectIfVisible(SOC_TERM_NAME, true);
            }

            // Add optional clk input terminal.
            tmpOffset.Height += TERM_SOLO_STEP;
            location = BASE_LOCATION + tmpOffset;
            if (m_shapeInfo.ShowClkTerm)
            {
                m_termEdit.TerminalAdd(CLK_TERM_NAME, CyCompDevTermDir.INPUT, 
                    CyCompDevTermType.DIGITAL, location, string.Empty, 0f, true);
                m_termEdit.SetMustConnectIfVisible(CLK_TERM_NAME, true);
                DrawClockTermCarat(new PointF(location.X + BASE_UNIT, location.Y));
            }

            if (m_shapeInfo.ConfigFilterMask != 0)
            {
                // Add filter's agnd input terminal.
                tmpOffset.Height += TERM_SOLO_STEP;
                location = BASE_LOCATION + tmpOffset;
                m_termEdit.TerminalAdd(AGND_TERM_NAME, CyCompDevTermDir.INOUT,
                    CyCompDevTermType.ANALOG, location, string.Empty, 0f, true);
                m_termEdit.SetMustConnectIfVisible(AGND_TERM_NAME, true);
            }
            else
            {
                m_termEdit.TerminalAdd(AGND_TERM_NAME, CyCompDevTermDir.INOUT,
                    CyCompDevTermType.ANALOG, BASE_LOCATION, string.Empty, 0f, false);
                m_termEdit.ChangeTerminalVisibilityExpr(AGND_TERM_NAME, "false");
            }
            tmpOffset.Width = CONFIG_WIDTH;
            tmpOffset.Height += TERM_PAIR_PAD;

            ////Draw divider line
            //string tag = "divider_line";
            //PointF lineRight = BASE_LOCATION + tmpOffset - new SizeF(0, 0.5f * BASE_UNIT);
            //PointF lineLeft = new PointF(BASE_LOCATION.X, lineRight.Y);
            //m_shapeEdit.CreatePolyline(new string[] { tag }, new PointF[] { lineLeft, lineRight },
            //     LineJoin.Miter, CREATOR_BODY_STROKE_COLOR, CREATOR_BODY_STROKE_WEIGHT / 2);

            RectangleF commonTermRect = new RectangleF(BASE_LOCATION, tmpOffset);
            return commonTermRect;
        }

        //clock terminal triangle drawing
        private void DrawClockTermCarat(PointF location)
        {
            PointF top = location;
            top.Y -= BASE_UNIT;
            PointF bottom = location;
            bottom.Y += BASE_UNIT;
            PointF right = location;
            right.X += BASE_UNIT;
            string tag = "clock_triangle";
            m_shapeEdit.CreatePolyline(new string[] { tag }, new PointF[] { top, right, bottom }, 
                 LineJoin.Miter, CREATOR_ANALOGGLYPH_STROKE_COLOR, CREATOR_ANALOGGLYPH_STROKE_WEIGHT);
            m_shapeEdit.BringToFront(tag);
        }

        private RectangleF DrawSarConfig(int configNum, int baseRawChannel, 
            PointF location, float width)
        {
            RectangleF configRect;

            if (m_shapeInfo.ChannelCounts[configNum] > 1)
            {
                configRect = DrawSarMuxConfig(configNum, baseRawChannel, location);
            }
            else
            {
                configRect = DrawSarOnlyConfig(configNum, baseRawChannel, location, width);
            }

            return configRect;
        }

        private RectangleF DrawSarMuxConfig(int configNum, int baseRawChan, PointF location)
        {
            int channelMax = m_shapeInfo.ChannelCounts[configNum];
            uint singleMask = m_shapeInfo.GetConfigSingleMask(configNum);
            uint diffMask = m_shapeInfo.GetConfigDiffMask(configNum);

            List<PointF> vplusLocs;
            List<PointF> vminusLocs;
            PointF vrefLoc;
            PointF vnegLoc;
            float muxHeight;

            /* Region from origin down to MUX_YOFFSET is considered commonCanvas.
               configCanvas is just below it. */
            PointF configCanvasLocation = new PointF(location.X, location.Y + MUX_YOFFSET);

            GetSarMuxTermPositions(configNum, configCanvasLocation, baseRawChan, 
                out vplusLocs, out vminusLocs, out vnegLoc, out vrefLoc, out muxHeight);

            float height = muxHeight + MUX_YOFFSET;

            //Add Vplus Terminals, and if necessary Vminus terminals
            for (int chanOffset = 0; chanOffset < channelMax; chanOffset++)
            {
                int chanNum = chanOffset + baseRawChan;
                string vplusName = BuildVplusName(chanNum);
                m_termEdit.TerminalAdd(vplusName, CyCompDevTermDir.INOUT,
                    CyCompDevTermType.ANALOG, vplusLocs[chanOffset], string.Empty, 0f, false);
                m_termEdit.SetMustConnectIfVisible(vplusName, true);
                if ((diffMask & (1 << chanOffset)) != 0)
                {
                    string vminusName = BuildVminusName(chanNum);
                    m_termEdit.TerminalAdd(vminusName, CyCompDevTermDir.INOUT,
                        CyCompDevTermType.ANALOG, vminusLocs[chanOffset], string.Empty, 0f, false);
                    m_termEdit.SetMustConnectIfVisible(vminusName, true);
                }
            }

            //Add Vneg terminal
            if( m_shapeInfo.ConfigVnegTerms[configNum] )
            {
                string vnegName = BuildVnegName(configNum);
                m_termEdit.TerminalAdd(vnegName, CyCompDevTermDir.INOUT,
                    CyCompDevTermType.ANALOG, vnegLoc, string.Empty, 0f, false);
                m_termEdit.SetMustConnectIfVisible(vnegName, true);
            }

            //Add Vref terminal
            if( m_shapeInfo.ConfigVrefTerms[configNum] )
            {
                string vrefName = VREF_TERM_NAME + "_" + configNum.ToString();
                m_termEdit.TerminalAdd(vrefName, CyCompDevTermDir.INOUT,
                    CyCompDevTermType.ANALOG, vrefLoc, string.Empty, 0f, false);
                m_termEdit.SetMustConnectIfVisible(vrefName, true);
            }
            
            /* Draw the SAR Mux glyph */
            PointF sarMuxLocation = new PointF(vplusLocs[0].X + 4 * BASE_UNIT, 
                vplusLocs[0].Y - SARMUX_FINHEIGHT);
            float sarMuxHeight = (vminusLocs[vminusLocs.Count - 1].Y - vplusLocs[0].Y) + (2 * SARMUX_FINHEIGHT);
            RectangleF sarMuxRect = DrawSarMux(configNum, sarMuxLocation, sarMuxHeight);
            

            /* Draw the ADC glyph */
            PointF sarLocation = new PointF(configCanvasLocation.X + CONFIG_WIDTH - (1 * BASE_UNIT) - SAR_WIDTH, 
                sarMuxRect.Y + sarMuxRect.Height / 2 - 2 * SAR_HEIGHT_DIV_4);
            RectangleF sarRect = DrawSar(configNum, sarLocation);

            /* Draw connecting wires */
            DrawSarMuxVinConnections(configNum, diffMask, configCanvasLocation.X, sarMuxRect.X, vplusLocs, vminusLocs);

            /* If any channel is not differential, draw a Vneg connecting wire. */
            if ((m_shapeInfo.ChannelSingleMasks[configNum] != 0)
                || (m_shapeInfo.ChannelFilterMasks[configNum] != 0))
            {
                DrawVneg2SarMuxVminusConnections(configNum, singleMask, configCanvasLocation.X, 
                    sarMuxRect.X - (1.5f * BASE_UNIT), sarMuxRect.X, vminusLocs, vnegLoc);
            }
            
            DrawVrefGlyph(configNum, m_shapeInfo.ConfigVrefSource[configNum], 
                new PointF(sarRect.Left + (3.0f * BASE_UNIT), sarRect.Bottom), 
                new RectangleF(location.X, location.Y, CONFIG_WIDTH, height));
            
            DrawSarMuxToSarConnections(configNum, sarMuxRect.Right, sarLocation);

            height += BASE_UNIT;

            //Draw component name

            PointF instLabelPoint = new PointF(location.X + CONFIG_WIDTH, -4.0f * BASE_UNIT);
            Font font = new Font(FontFamily.GenericSansSerif, 10);
            StringFormat instLabelFormat = new StringFormat();
            instLabelFormat.Alignment = StringAlignment.Far;
            m_shapeEdit.CreateAnnotation(new string[] { "instLabel" }, "`=$INSTANCE_NAME`", 
                instLabelPoint, font, instLabelFormat, Color.Black);

            StringFormat compLabelFormat = new StringFormat();
            PointF compLabelPoint = new PointF(location.X + (CONFIG_WIDTH / 2), 
                location.Y - (2.0f * BASE_UNIT));
            compLabelFormat.Alignment = StringAlignment.Center;
            m_shapeEdit.CreateAnnotation(new string[] { "compLabel" }, "Scan_ADC", 
                compLabelPoint, font, compLabelFormat, Color.Black);

            if (m_params.NumberOfConfigs > 1)
            {
                //Draw configX labels
                var configLabelPoint = new PointF(location.X + CONFIG_WIDTH / 2, location.Y);
                var configLabelFormat = new StringFormat();
                configLabelFormat.Alignment = StringAlignment.Center;
                m_shapeEdit.CreateAnnotation(
                    new string[] { "configLabel" }, "Config" + configNum.ToString(),
                    configLabelPoint, font, configLabelFormat, Color.Black);
            }

            //Config Rect
            string[] tags = new string[] { "Config" + configNum.ToString(), BODY_SHAPE_TAG };
            m_shapeEdit.CreateRectangle(tags, new PointF(location.X,location.Y - (2.0f * BASE_UNIT)),
                CONFIG_WIDTH, (2.0f * BASE_UNIT), LineJoin.Miter, CREATOR_ANALOGHEADER_FILL_COLOR,
                CREATOR_BODY_STROKE_COLOR, CREATOR_BODY_STROKE_WEIGHT);

            m_shapeEdit.CreateRectangle(tags, location,
                CONFIG_WIDTH, height, LineJoin.Miter, CREATOR_BODY_FILL_COLOR, 
                CREATOR_BODY_STROKE_COLOR, CREATOR_BODY_STROKE_WEIGHT);
            m_shapeEdit.SendToBack(BODY_SHAPE_TAG);

            return new RectangleF(location.X, location.Y, CONFIG_WIDTH, height);
        }

        private void DrawVnegGlyph(int configNum, CyEVnegSource vnegConnection, PointF location)
        {
            PointF t0;
            PointF t1;
            PointF t2;

            string[] shapeTags = { CONFIG_SHAPE_TAGS[configNum], ANALOG_WIRE_TAG };
            switch (vnegConnection)
            {
                case CyEVnegSource.VNEGSOURCE_VSSA_K:
                    t0 = new PointF(location.X - BASE_UNIT, location.Y);
                    t1 = new PointF(location.X + BASE_UNIT, location.Y);
                    t2 = new PointF(location.X, location.Y + BASE_UNIT);

                    m_shapeEdit.CreatePolyline(shapeTags, CREATOR_ANALOGWIRE_COLOR, 
                        CREATOR_ANALOGWIRE_STROKE_WEIGHT, LineJoin.Miter, new PointF[] { t0, t1, t2, t0 });

                    break;
                case CyEVnegSource.VNEGSOURCE_EXTERNAL:
                    t0 = new PointF(location.X - (1.5f * BASE_UNIT), location.Y);
                    t1 = location;

                    m_shapeEdit.CreatePolyline(shapeTags, CREATOR_ANALOGWIRE_COLOR, 
                        CREATOR_ANALOGWIRE_STROKE_WEIGHT, LineJoin.Miter, new PointF[] { t0, t1 });

                    break;
                case CyEVnegSource.VNEGSOURCE_VREFSHORT:
                    t0 = location;
                    t1 = new PointF(location.X + (8.5f * BASE_UNIT), location.Y);

                    m_shapeEdit.CreatePolyline(shapeTags, CREATOR_ANALOGWIRE_COLOR, 
                        CREATOR_ANALOGWIRE_STROKE_WEIGHT, LineJoin.Miter, new PointF[] { t0, t1 });

                    break;
                default:
                    break;
            }

        }

        private void DrawVrefGlyph(int configNum, CyEVrefSource vrefConnection, 
            PointF bottomAdcGlyph, RectangleF configRect)
        {
            PointF topVrefGlyph = bottomAdcGlyph;
            PointF bottomVrefGlyph = new PointF(bottomAdcGlyph.X, configRect.Bottom - (1.0f * BASE_UNIT));
            PointF t1;

            string[] shapeTags = { CONFIG_SHAPE_TAGS[configNum], ANALOG_WIRE_TAG };

            Font font = new Font(FontFamily.GenericSansSerif, 8);
            PointF vrefLabelPoint = new PointF(topVrefGlyph.X - (1.0f * BASE_UNIT), 
                topVrefGlyph.Y - (1.5f * BASE_UNIT));
            StringFormat configLabelFormat = new StringFormat();
            configLabelFormat.Alignment = StringAlignment.Near;
            m_shapeEdit.CreateAnnotation(new string[] { "vrefLabel" }, VREF_TERM_NAME, vrefLabelPoint, 
                font, configLabelFormat, Color.Black);


            m_shapeEdit.CreatePolyline(shapeTags, CREATOR_ANALOGWIRE_COLOR, CREATOR_ANALOGWIRE_STROKE_WEIGHT, 
                LineJoin.Miter, new PointF[] { topVrefGlyph, bottomVrefGlyph });

            switch (vrefConnection)
            {
                case CyEVrefSource.VREFSOURCE_PVREF:
                case CyEVrefSource.VREFSOURCE_VBGR:
                case CyEVrefSource.VREFSOURCE_VDDA:
                case CyEVrefSource.VREFSOURCE_HALFVDDA:
                case CyEVrefSource.VREFSOURCE_DEVPIN:
                    t1 = new PointF(bottomVrefGlyph.X + (3.0f * BASE_UNIT), bottomVrefGlyph.Y);
                    m_shapeEdit.CreatePolyline(shapeTags, CREATOR_ANALOGWIRE_COLOR, 
                        CREATOR_ANALOGWIRE_STROKE_WEIGHT, LineJoin.Miter, new PointF[] { t1, bottomVrefGlyph });
                    
                    m_shapeEdit.CreateEllipse(new string[] {"ellipse"}, t1, CREATOR_ANALOGDOT_STROKE_WEIGHT, 
                        CREATOR_ANALOGDOT_STROKE_WEIGHT);
                    m_shapeEdit.SetFillColor("ellipse", CREATOR_ANALOGWIRE_COLOR);
                    m_shapeEdit.SetOutlineColor("ellipse", CREATOR_ANALOGWIRE_COLOR);

                    vrefLabelPoint = bottomVrefGlyph + new SizeF(0, 0 * BASE_UNIT);
                    String refsourceLabel = GetVrefLabel(vrefConnection);
                    m_shapeEdit.CreateAnnotation(new string[] { "vrefLabel" }, refsourceLabel, 
                        vrefLabelPoint, font, configLabelFormat, Color.Black);
                    break;
                case CyEVrefSource.VREFSOURCE_EXTERNAL:
                    t1 = new PointF(configRect.Left, bottomVrefGlyph.Y);
                    m_shapeEdit.CreatePolyline(shapeTags, CREATOR_ANALOGWIRE_COLOR, 
                        CREATOR_ANALOGWIRE_STROKE_WEIGHT, LineJoin.Miter, new PointF[] { t1, bottomVrefGlyph });
                    
                    break;
                default:
                    break;
            }

        }

        private RectangleF DrawSarOnlyConfig(int configNum, int baseRawChannel, 
            PointF baseLocation, float width)
        {
            PointF vplusLoc;
            PointF vminusLoc;
            PointF vnegLoc;
            float height;
            GetSarOnlyTermPositions(configNum, baseLocation, baseRawChannel, 
                out vplusLoc, out vminusLoc, out vnegLoc, out height);

            PointF sarLocation = new PointF(baseLocation.X + width - TERM_PAIR_STEP - SAR_WIDTH, 
                vplusLoc.Y - SAR_HEIGHT_DIV_4);
            RectangleF sarRect = DrawSar(configNum, sarLocation);

            string vplusName = BuildVplusName(baseRawChannel);
            m_termEdit.TerminalAdd(vplusName, CyCompDevTermDir.INOUT,CyCompDevTermType.ANALOG,
                vplusLoc, string.Empty, 0f, false);
            m_termEdit.SetMustConnectIfVisible(vplusName, true);
            uint singleMask = m_shapeInfo.GetConfigSingleMask(configNum);
            if (singleMask == 0)
            {
                string vminusName = BuildVminusName(baseRawChannel);
                m_termEdit.TerminalAdd(vminusName, CyCompDevTermDir.INOUT,CyCompDevTermType.ANALOG,
                    vminusLoc, string.Empty, 0f, false);
                m_termEdit.SetMustConnectIfVisible(vminusName, true);
            }
            else
            {
                string vnegName = BuildVnegName(baseRawChannel);
                m_termEdit.TerminalAdd(vnegName, CyCompDevTermDir.INOUT,CyCompDevTermType.ANALOG,
                    vnegLoc, string.Empty, 0f, false);
                m_termEdit.SetMustConnectIfVisible(vnegName, true);
            }

            DrawSarConnections(configNum, singleMask,vplusLoc, vminusLoc, vnegLoc, sarLocation);

            SizeF sarOnlySize = new SizeF(width, height);
            return new RectangleF(baseLocation, sarOnlySize);
        }

        private void GetSarMuxTermPositions(int configNum, 
            PointF baseLocation, int baseRawChannel, out List<PointF> vplusLocs,
            out List<PointF> vminusLocs, out PointF vnegLoc, out PointF vrefLoc, out float height)
        {
            int channelMax = m_shapeInfo.ChannelCounts[configNum];
            uint singleMask = m_shapeInfo.GetConfigSingleMask(configNum);

            vplusLocs = new List<PointF>();
            vminusLocs = new List<PointF>();

            PointF location = baseLocation;
            SizeF tmpOffset = new SizeF(-1 * BASE_UNIT, TERM_PAIR_PAD + BASE_UNIT);
            location += tmpOffset;

            for (int chanOffset = 0; chanOffset < channelMax; chanOffset++)
            {
                vplusLocs.Add(location);
                location.Y += TERM_PAIR_STEP;
                vminusLocs.Add(location);
                location.Y += TERM_PAIR_PAD;
            }

            
            location.Y += TERM_SOLO_PAD;
            
            vnegLoc = location;

            if(m_shapeInfo.ConfigVrefTerms[configNum])
            {
                location.Y += TERM_PAIR_PAD;
            }
            vrefLoc = location;

            location.Y += BASE_UNIT;

            height = location.Y - baseLocation.Y;
        }

        private void GetSarOnlyTermPositions(int configNum,
            PointF baseLocation, int baseRawChannel, out PointF vplusLoc,
            out PointF vminusLoc, out PointF vnegLoc, out float height)
        {
            uint singleMask = m_shapeInfo.GetConfigSingleMask(configNum);

            PointF location = baseLocation;
            location.X -= BASE_UNIT;
            location.Y += BASE_UNIT;

            location.Y += SAR_HEIGHT_DIV_4;
            vplusLoc = location;

            location.Y += 2 * SAR_HEIGHT_DIV_4;
            vminusLoc = location;

            location.Y += SAR_HEIGHT_DIV_4;

            if (singleMask != 0)
            {
                location.Y += BASE_UNIT;
                vnegLoc = location;
            }
            else
            {
                vnegLoc = location;
            }

            location.Y += BASE_UNIT;

            height = location.Y - baseLocation.Y;
        }

        /* Draw mux symbol */
        private RectangleF DrawSarMux(int configNum, PointF location, float height)
        {
            
            PointF topLeft = new PointF(location.X, location.Y);
            PointF topRight = new PointF(location.X + SARMUX_WIDTH, location.Y + SARMUX_FINHEIGHT);
            PointF bottomLeft = new PointF(location.X, location.Y + height);
            PointF bottomRight = new PointF(topRight.X, bottomLeft.Y - SARMUX_FINHEIGHT);

            m_shapeEdit.CreatePolygon(new string[] { CONFIG_SHAPE_TAGS[configNum] },  
                new PointF[] { topLeft, bottomLeft, bottomRight, topRight },
                LineJoin.Miter,CONFIG_COLORS[configNum], CREATOR_ANALOGGLYPH_STROKE_COLOR,
                CREATOR_ANALOGGLYPH_STROKE_WEIGHT);

            RectangleF boundingBox = new RectangleF(topLeft.X, topLeft.Y, 
                topRight.X - topLeft.X, bottomLeft.Y - topLeft.Y);

            return boundingBox;
        }

        /* Draw sar adc symbol */
        private RectangleF DrawSar(int configNum, PointF location)
        {
            string shapeTag = CONFIG_SHAPE_TAGS[configNum];
            float sarHalfHeight = 2 * SAR_HEIGHT_DIV_4;
            float sarHeight = 2 * sarHalfHeight;
            float sarWidth = SAR_WIDTH;

            PointF leftCorner = new PointF(location.X, location.Y + sarHalfHeight);
            PointF topLeft = new PointF(location.X + sarHalfHeight, location.Y);
            PointF bottomLeft = new PointF(location.X + sarHalfHeight, location.Y + sarHeight);
            PointF topRight = new PointF(location.X + sarWidth, location.Y);
            PointF bottomRight = new PointF(location.X + sarWidth, location.Y + sarHeight);
            var shapeColor = CONFIG_COLORS[configNum];
            if (m_shapeInfo.ExposeTestTerminals)
            {
                int newRgb = (CREATOR_ANALOGGLYPH_FILL_COLOR.ToArgb() & unchecked((int)~0xFF000000)) + 0x40000000;
                shapeColor = Color.FromArgb(newRgb);//2852126720
            }
            m_shapeEdit.CreatePolygon(new string[] { shapeTag },
                new PointF[] { topLeft, leftCorner, bottomLeft, bottomRight, topRight },
                LineJoin.Miter, shapeColor, CREATOR_ANALOGGLYPH_STROKE_COLOR, 
                CREATOR_ANALOGGLYPH_STROKE_WEIGHT);

            RectangleF boundingBox = new RectangleF(location, new SizeF(sarWidth, sarHeight));

            return boundingBox;
        }

        /* Draw wires from terminals to mux inputs. */
        private void DrawSarMuxVinConnections(int configNum, uint diffMask, float x0, float x1, 
            List<PointF> vplusLocs, List<PointF> vminusLocs)
        {
            int channelMax = vplusLocs.Count;
            string[] shapeTags = {CONFIG_SHAPE_TAGS[configNum], ANALOG_WIRE_TAG};

            for (int channelNum = 0; channelNum < channelMax; channelNum++)
            {
                PointF locPlus = vplusLocs[channelNum];
                PointF p0 = new PointF(x0, locPlus.Y);
                PointF p1 = new PointF(x1, locPlus.Y);
                /* Draw Vplus wires from terminal to mux. */
                m_shapeEdit.CreateLine(shapeTags, p0, p1, CREATOR_ANALOGWIRE_COLOR, 
                    CREATOR_ANALOGWIRE_STROKE_WEIGHT);

                Font font = new Font(FontFamily.GenericSansSerif, 10);
                PointF chanLabellPoint = new PointF(x1 , p1.Y + (-0.5f * BASE_UNIT));
                StringFormat chanLabelFormat = new StringFormat();
                chanLabelFormat.Alignment = StringAlignment.Near;
                m_shapeEdit.CreateAnnotation(new string[] { "chanNumLabel" }, channelNum.ToString(), 
                    chanLabellPoint, font, chanLabelFormat, Color.Black);

                if ((diffMask & (1 << channelNum)) != 0)
                {
                    PointF locMinus = vminusLocs[channelNum];
                    PointF m0 = new PointF(x0, locMinus.Y);
                    PointF m1 = new PointF(x1, locMinus.Y);
                    /* Draw Vminus wires from terminal to mux*/
                    m_shapeEdit.CreateLine(shapeTags, m0, m1, CREATOR_ANALOGWIRE_COLOR, 
                        CREATOR_ANALOGWIRE_STROKE_WEIGHT);
                }
            }
        }

        /* draw lines from Vneg wire to mux Vminus */
        private void DrawVneg2SarMuxVminusConnections(int configNum, uint singleMask, 
            float canvasLeftX, float elbowX, float muxLeftX, List<PointF> vminusLocs, PointF vnegLoc)
        {
            int channelMax = vminusLocs.Count;
            string[] wireTags = { CONFIG_SHAPE_TAGS[configNum], ANALOG_WIRE_TAG };
            string[] dotTags = { CONFIG_SHAPE_TAGS[configNum], ANALOG_DOT_TAG };
            PointF vnegElbow = new PointF(elbowX, vnegLoc.Y);

            bool isFirst = true;
            bool skipFilter = (0 != (m_shapeInfo.ConfigFilterMask & (1 << configNum)));
            for (int channelNum = 0; channelNum < channelMax; channelNum++)
            {
                if ((singleMask & (1 << channelNum)) != 0)
                {
                    PointF locMinus = vminusLocs[channelNum];
                    PointF m0 = new PointF(elbowX, locMinus.Y);
                    PointF m1 = new PointF(muxLeftX, locMinus.Y);
                    m_shapeEdit.CreateLine(wireTags, m0, m1, CREATOR_ANALOGWIRE_COLOR, 
                        CREATOR_ANALOGWIRE_STROKE_WEIGHT);
                    /* Draw a wire from the first Vminus which uses Vneg down to the Vneg spot.
                       Draw a connector dot for subsequent Vminus which use Vneg. */
                    if (isFirst)
                    {
                        if (skipFilter)
                        {
                            skipFilter = false;
                            PointF filterLoc = new PointF(elbowX - BASE_UNIT, locMinus.Y - (1.5f * BASE_UNIT));
                            m_shapeEdit.CreateRectangle(new String[] { CONFIG_SHAPE_TAGS[configNum] }, 
                                filterLoc, 2 * BASE_UNIT, 2 * BASE_UNIT, LineJoin.Miter, CONFIG_COLORS[configNum], 
                                CREATOR_ANALOGGLYPH_STROKE_COLOR, CREATOR_ANALOGGLYPH_STROKE_WEIGHT);
                            
                            Font font = new Font(FontFamily.GenericSansSerif, 8);
                            PointF filterLabLoc = new PointF(filterLoc.X + 1.0f * BASE_UNIT, filterLoc.Y + 2.0f);
                            StringFormat filterLabFmt = new StringFormat();
                            filterLabFmt.Alignment = StringAlignment.Center;
                            m_shapeEdit.CreateAnnotation(new string[] { "chanNumLabel" }, 
                                m_shapeInfo.ConfigFilterAliases[configNum], filterLabLoc, font, 
                                filterLabFmt, Color.Black);

                            }
                        else
                        {
                            isFirst = false;
                            m_shapeEdit.CreateLine(wireTags, m0, vnegElbow, CREATOR_ANALOGWIRE_COLOR, 
                                CREATOR_ANALOGWIRE_STROKE_WEIGHT);
                            DrawVnegGlyph(configNum, m_shapeInfo.ConfigVnegSource[configNum], 
                                new PointF(elbowX, vnegLoc.Y));
                        }
                        
                    }
                    else
                    {
                        m_shapeEdit.CreateEllipse(dotTags, m0, CREATOR_ANALOGDOT_STROKE_WEIGHT, 
                            CREATOR_ANALOGDOT_STROKE_WEIGHT);
                        m_shapeEdit.SetFillColor(ANALOG_DOT_TAG, CREATOR_ANALOGWIRE_COLOR);
                        m_shapeEdit.SetOutlineColor(ANALOG_DOT_TAG, CREATOR_ANALOGWIRE_COLOR);
                    }
                }
            }
        }

        /* draw lines from mux to sar */
        private void DrawSarMuxToSarConnections(int configNum, float sarMuxRight, PointF sarLocation)
        {
            string[] shapeTags = {CONFIG_SHAPE_TAGS[configNum], "analog_wire"};
            float sarHalfHeight = 2 * SAR_HEIGHT_DIV_4;
            float sarHeight = 2 * sarHalfHeight;

            PointF vplusSarLoc = new PointF(sarLocation.X + SAR_HEIGHT_DIV_4 - BASE_UNIT/2, 
                sarLocation.Y + sarHalfHeight - BASE_UNIT/2);
            PointF vminusSarLoc = new PointF(sarLocation.X + SAR_HEIGHT_DIV_4 - BASE_UNIT/2, 
                sarLocation.Y + sarHalfHeight + BASE_UNIT/2);
            PointF vplusSourceLoc = new PointF(sarMuxRight, vplusSarLoc.Y);
            PointF vminusSourceLoc = new PointF(sarMuxRight, vminusSarLoc.Y);

            m_shapeEdit.CreateLine(shapeTags, vplusSourceLoc, vplusSarLoc, CREATOR_ANALOGWIRE_COLOR, 
                CREATOR_ANALOGWIRE_STROKE_WEIGHT);
            m_shapeEdit.CreateLine(shapeTags, vminusSourceLoc, vminusSarLoc, CREATOR_ANALOGWIRE_COLOR, 
                CREATOR_ANALOGWIRE_STROKE_WEIGHT);
        }

        /* Draws direct connections form adc-glyph to terminals. Not used if mux is needed.*/
        private void DrawSarConnections(int configNum, uint singleMask, 
            PointF vplusLoc, PointF vminusLoc, PointF vnegLoc, PointF sarLoc)
        {
            string shapeTag = CONFIG_SHAPE_TAGS[configNum];
            PointF sarVplusLoc = new PointF(sarLoc.X + SAR_HEIGHT_DIV_4, sarLoc.Y + SAR_HEIGHT_DIV_4);
            PointF sarVminusLoc = new PointF(sarLoc.X + SAR_HEIGHT_DIV_4, sarLoc.Y + 3 * SAR_HEIGHT_DIV_4);

            m_shapeEdit.CreateLine(new string[] { shapeTag }, vplusLoc, sarVplusLoc);

            if (singleMask == 0)
            {
                m_shapeEdit.CreateLine(new string[] { shapeTag }, vminusLoc, sarVminusLoc);
            }
            else
            {
                float doglegX = vnegLoc.X + TERM_PAIR_PAD + TERM_PAIR_STEP;
                PointF dogleg0 = new PointF(doglegX, vnegLoc.Y);
                PointF dogleg1 = new PointF(doglegX, sarVminusLoc.Y);
                m_shapeEdit.CreatePolyline(new string[] { shapeTag },
                    CREATOR_ANALOGWIRE_COLOR, CREATOR_ANALOGWIRE_STROKE_WEIGHT, LineJoin.Miter,
                    new PointF[] { vnegLoc, dogleg0, dogleg1, sarVminusLoc });
            }
        }

        private string BuildVplusName(int chanNum)
        {
            return VIN_PLUS_PREFIX + "_" + chanNum.ToString();
        }

        private string BuildVminusName(int chanNum)
        {
            return VIN_MINUS_PREFIX + "_" + chanNum.ToString();
        }

        private string BuildVnegName(int configNum)
        {
            return VIN_NEG_PREFIX + "_" + configNum.ToString();
        }

        private string GetVrefLabel(CyEVrefSource vrefConnection)
        {
            string tmpReturn = "";
            switch (vrefConnection)
            {
                case CyEVrefSource.VREFSOURCE_PVREF:
                    tmpReturn = "dwvref";
                    break;
                case CyEVrefSource.VREFSOURCE_VBGR:
                    tmpReturn = "bg";
                    break;
                case CyEVrefSource.VREFSOURCE_VDDA:
                    tmpReturn = "vdda";
                    break;
                case CyEVrefSource.VREFSOURCE_HALFVDDA:
                    tmpReturn = "vdda/2";
                    break;
                case CyEVrefSource.VREFSOURCE_DEVPIN:
                    tmpReturn = "devpin";
                    break;
                default:
                    break;
            }
            return tmpReturn;
        }
    }
}

//[] END OF FILE
