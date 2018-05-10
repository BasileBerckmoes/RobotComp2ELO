/*******************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;
using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.IO;

using ActiproSoftware.SyntaxEditor;

using CyDesigner.Common.Base;
using CyDesigner.Common.Base.Controls;
using CyDesigner.Common.Base.Dialogs;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using CyDesigner.PSoC.PSoC3.Fitter.DesignWideResources;

using Cypress.Components.System.Ports.CommonPortCode;

namespace Cypress.Components.System.Ports.cy_sio_port_v1_0
{
    public class CyCustomizer :
        ICyParamEditHook_v1,
        ICyVerilogCustomize_v1,
        ICyShapeCustomize_v1,
        ICyInstValidateHook_v1
    {
        const string m_oeBaseTerminalName = "oe";
        const string m_oBaseTerminalName = "o";
        const string m_ioBaseTerminalName = "io";
        const string m_iBaseTerminalName = "i";
        const string m_irqBaseTerminalName = "irq";
        const string m_vrefBaseTerminalName = "vref";

        const string m_builtinTabName = "Built-in";
        const string m_basicTabName = "Basic";

        //-----------------------------

        #region ICyParamEditHook_v1 Members

        public CyCompDevParamEditorMode GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }

        /// <summary>
        /// Displays a custom parameter editor to the user to allow them to edit the port params.
        /// </summary>
        /// <param name="edit"></param>
        /// <param name="mgr"></param>
        /// <returns></returns>
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CySIOParamInfo info = new CySIOParamInfo();

            CyPortPinEditingControl pinsDGV = new CyPortPinEditingControl(edit);
            pinsDGV.Dock = DockStyle.Fill;
            ICyPortsPinColumnInfo[] columns = new ICyPortsPinColumnInfo[] {
                new CyPinAliasColumnInfo(edit),
                new CyPinModeColumnInfo(edit),
                new cy_digital_port_v1_0.CySlewRateColumnInfo(edit),
                new CyHysteresisEnabledColumnInfo(edit),
                new cy_digital_port_v1_0.CyInterruptModeColumnInfo(edit),
            };
            pinsDGV.SetupColumns(columns, info.GetWidth(edit));

            CyParamExprDelegate paramExprCommitted = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                //only update for valid data
                if (param.ErrorCount == 0)
                {
                    if (param.Name == CySIOParamInfo.ParamNameUseInterrupt ||
                             param.Name == CySIOParamInfo.ParamNameWidth ||
                             param.Name == CySIOParamInfo.ParamNameDirection)
                    {
                        byte width = info.GetWidth(edit);
                        pinsDGV.UpdatePins(width);
                    }
                }
            };

            CyParamExprDelegate expressionViewDataChanged = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                byte width = info.GetWidth(edit);
                pinsDGV.UpdatePins(width);
            };

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            editor.ParamExprCommittedDelegate = paramExprCommitted;
            editor.AddDefaultPage(m_basicTabName, m_basicTabName);
            editor.AddCustomPage("Pins", pinsDGV, expressionViewDataChanged, "Pins");
            editor.AddDefaultPage(m_builtinTabName, m_builtinTabName);
            return editor.ShowDialog();
        }

        /// <summary>
        /// Gets whether or not EditParams should be called when a port is initailly
        /// dropped onto a canvas.
        /// </summary>
        public bool EditParamsOnDrop
        {
            get { return false; }
        }

        #endregion

        //-----------------------------

        #region ICyVerilogCustomize_v1 Members

        public CyCustErr CustomizeVerilog(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery, out string codeSnippet)
        {
            /* Example:
             * 
             * cy_psoc3_port_v1_0
             * #(.width(8),
             *   .id("7fb63523-3721-4e66-848c-192f0924dfc3"),
             *   .pin_aliases("pin0name,pin1name,,,,pin5name,,"),
             *   .access_mode("SW_ONLY"),
             *   .layout_mode("CONTIGUOUS"),
             *   .port_mode("INPUT"),
             *   .intr_mode(16'b00 00 00 00 00 00 00 00),
             *   .drive_mode(16'b00 00 00 00 00 00 00 00))
             * port_1
             *  (.oe(wire_1),
             *   .y(Terminal_1),
             *   .fb(foo),
             *   .analog(8'b0),
             *   .interrupt(wire_2));
             */

            StringBuilder sb = new StringBuilder();
            CySIOParamInfo info = new CySIOParamInfo();

            string termName_OE = termQuery.GetTermName(m_oeBaseTerminalName);
            string termName_I = termQuery.GetTermName(m_iBaseTerminalName);
            string termName_O = termQuery.GetTermName(m_oBaseTerminalName);
            string termName_IO = termQuery.GetTermName(m_ioBaseTerminalName);
            string termName_IRQ = termQuery.GetTermName(m_irqBaseTerminalName);
            string termName_VREF = termQuery.GetTermName(m_vrefBaseTerminalName);

            string sigOEName = (termQuery.GetHasNoDrivers(termName_OE)) ?
               termQuery.GetTermDefaultVlogExpr(termName_OE) :
               termQuery.GetTermSigSegName(termName_OE);

            string sigOName = (termQuery.GetHasNoDrivers(termName_O)) ?
               termQuery.GetTermDefaultVlogExpr(termName_O) :
               termQuery.GetTermSigSegName(termName_O);

            //outputs and inouts don't need to be hooked up (they can be left open)----------
            string sigIName = (termQuery.GetHasNoDrivers(termName_I)) ?
                string.Empty : termQuery.GetTermSigSegName(termName_I);

            string sigIOName = (termQuery.GetHasNoDrivers(termName_IO)) ?
                string.Empty : termQuery.GetTermSigSegName(termName_IO);

            string sigIRQName = (termQuery.GetHasNoDrivers(termName_IRQ)) ?
                string.Empty : termQuery.GetTermSigSegName(termName_IRQ);

            string sigVREFName = (termQuery.GetHasNoDrivers(termName_VREF)) ?
                string.Empty : termQuery.GetTermSigSegName(termName_VREF);
            //--------------------------------------------------------------------------------

            byte width = info.GetWidth(query);

            CyVerilogWriter vw = new CyVerilogWriter("cy_psoc3_port_v1_0", info.GetShortInstanceName(query));
            vw.AddGeneric("width", width.ToString());
            vw.AddGeneric("id", "\"" + query.InstanceIdPath + "\"");
            vw.AddGeneric("pin_aliases", info.GetPinAliasVerilog(query, width));
            vw.AddGeneric("access_mode", string.Format("\"{0}\"", info.GetVerilogAccessMode(query)));
            vw.AddGeneric("layout_mode", string.Format("\"{0}\"", info.GetVerilogLayoutMode(query)));
            vw.AddGeneric("port_mode", string.Format("\"{0}\"", info.GetVerilogDirection(query)));
            vw.AddGeneric("slew_rate", info.GetVerilogSlewRateBitArray(query, width));
            vw.AddGeneric("vtrip", info.GetVerilogStandardLogic(query));
            vw.AddGeneric("intr_mode", info.GetVerilogInterruptModeBitArray(query, width));
            vw.AddGeneric("drive_mode", info.GetVerilogPinModeBitArray(query, width));
            vw.AddGeneric("por_state", info.GetVerilogPORState(query));

            vw.AddGeneric("siorefwidth", ((width + 1) / 2).ToString());
            vw.AddGeneric("sio_obuf", info.GetVerilogOutputBuffer(query));
            vw.AddGeneric("sio_ibuf", info.GetVerilogInputBuffer(query));
            vw.AddGeneric("sio_hyst", info.GetVerilogHysteresisEnabledBitArray(query, width));
            vw.AddGeneric("sio_hifreq", info.GetVerilogHiFreq(query));
            vw.AddGeneric("sio_vtrip", info.GetVerilogVTrip(query));
            vw.AddGeneric("sio_refsel", info.GetVerilogVRefSelection(query));

            // POST PR4 NOTE:
            //     Prior to PR4, the OE signals are 'active low', meaning, a 0 will
            //     enable the output, a 1 would turn it off. CDT 32449 is tracking the
            //     PR4 change to the device to make it 'active high', as it should have
            //     been.
            //vw.AddPort("oe", sigOEName);
            string netOEName = "tmpOE__" + info.GetShortInstanceName(query) + "_net";
            vw.AddWire(netOEName, 0, 0);
            vw.AssignPreES3CondWire(netOEName, "~" + sigOEName, sigOEName);
            vw.AddPort("oe", netOEName); // input
            vw.AddPort("y", sigOName);  //y - INPUT
            if (!string.IsNullOrEmpty(sigIName)) vw.AddPort("fb", sigIName); //fb - OUTPUT
            if (!string.IsNullOrEmpty(sigIOName)) vw.AddPort("io", sigIOName); //io - InOut
            if (!string.IsNullOrEmpty(sigIRQName)) vw.AddPort("interrupt", sigIRQName); // - OUTPUT
            if (!string.IsNullOrEmpty(sigVREFName)) vw.AddPort("siovref", sigVREFName); // analog InOut

            codeSnippet = vw.ToString();
            return CyCustErr.Ok;
        }

        #endregion

        //-----------------------------

        #region ICyShapeCustomize_v1 Members

        public CyCustErr CustomizeShapes(
            ICyInstQuery_v1 query, ICySymbolShapeEdit_v1 shapeEdit, ICyTerminalEdit_v1 termEdit)
        {
            CySIOParamInfo info = new CySIOParamInfo();
            CyCustErr err;

            Debug.Assert(termEdit.TerminalCount > 0);

            string termName_O = termEdit.GetTermName(m_oBaseTerminalName);
            string termName_I = termEdit.GetTermName(m_iBaseTerminalName);
            string termName_IO = termEdit.GetTermName(m_ioBaseTerminalName);
            string termName_OE = termEdit.GetTermName(m_oeBaseTerminalName);
            string termName_IRQ = termEdit.GetTermName(m_irqBaseTerminalName);

            //err = SetTerminalType(termEdit, CyCompDevTermType.DIGITAL,
            //                        termName_O, termName_I, termName_OE, termName_IRQ);
            //if (err.IsNotOK) return err;

            shapeEdit.SetFillColor("body", query.Preferences.SchematicDigitalTerminalColor);

            string iDefV;
            string ioDefV;
            string oDefV;
            string oeDefV;
            CySIOParamInfo.CyPinDirection dir = info.GetDirection(query);
            byte width = info.GetWidth(query);

            iDefV = ioDefV = oDefV = string.Format("{0}'b0", width.ToString());

            if (dir == CySIOParamInfo.CyPinDirection.Input)
                oeDefV = "1'b0";
            else
                oeDefV = "1'b1";

            err = termEdit.ChangeTerminalDefVerilogValue(termName_I, iDefV);
            if (err.IsNotOK) return err;
            err = termEdit.ChangeTerminalDefVerilogValue(termName_O, oDefV);
            if (err.IsNotOK) return err;
            err = termEdit.ChangeTerminalDefVerilogValue(termName_OE, oeDefV);
            if (err.IsNotOK) return err;
            err = termEdit.ChangeTerminalDefVerilogValue(termName_IO, ioDefV);
            if (err.IsNotOK) return err;

            int maxBitIndex = width - 1;
            string newName = (maxBitIndex == 0) ? m_oBaseTerminalName : 
                              string.Format("{0}[{1}:0]", m_oBaseTerminalName, maxBitIndex.ToString());
            err = termEdit.TerminalRename(termName_O, newName);
            if (err.IsNotOK) return err;

            newName = (maxBitIndex == 0) ? m_iBaseTerminalName :
                       string.Format("{0}[{1}:0]", m_iBaseTerminalName, maxBitIndex.ToString());
            err = termEdit.TerminalRename(termName_I, newName);
            if (err.IsNotOK) return err;

            newName = (maxBitIndex == 0) ? m_ioBaseTerminalName :
                       string.Format("{0}[{1}:0]", m_ioBaseTerminalName, maxBitIndex.ToString());
            err = termEdit.TerminalRename(termName_IO, newName);
            if (err.IsNotOK) return err;

            return CyCustErr.OK;
        }

        //static CyCustErr SetTerminalType(ICyTerminalEdit_v1 termEdit, CyCompDevTermType type, 
        //    params string[] terminalNames)
        //{
        //    CyCustErr err;
        //    foreach (string termName in terminalNames)
        //    {
        //        err = termEdit.ChangeTerminalType(termName, type);
        //        if (err.IsNotOK) return err;
        //    }
        //    return CyCustErr.Ok;
        //}

        #endregion

        //-----------------------------

        #region ICyInstValidateHook_v1 Members

        public void ValidateParams(ICyInstValidate_v1 instVal)
        {
            CySIOParamInfo info = new CySIOParamInfo();

            CyPortParamInfoWithPinModeParams.ValidatePinModes(info, instVal);
            CyPortParamInfo.ValidatePinAliases(info, instVal);
            CySIOParamInfo.ValidatePinInterruptModes(info, instVal);
            CySIOParamInfo.ValidateSlewRates(info, instVal);
            CySIOParamInfo.ValidateHysteresisEnabled(info, instVal);
        }

        #endregion
    }

    #region Helper Classes

    internal class CyHysteresisEnabledColumnInfo : CyPinColumnInfo
    {
        readonly CyDGVEnhancedTextBoxColumn m_column;

        public CyHysteresisEnabledColumnInfo(ICyInstEdit_v1 edit)
            : base(edit, CySIOParamInfo.ParamNamePinHysteresisEnabled, 1, CySIOParamInfo.DefaultHysteresisEnabled)
        {
            m_column = new CyDGVEnhancedTextBoxColumn();
            m_column.HeaderText = "Hysteresis Enabled";
            m_column.ReadOnly = false;
            m_column.Name = "HysteresisColumn";
            m_column.AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
            m_column.SortMode = DataGridViewColumnSortMode.Automatic;
            m_column.MemberListDisplaying +=
                new EventHandler<CyMemberListEventArgs>(slewRateCol_MemberListDisplaying);
        }

        void slewRateCol_MemberListDisplaying(object sender, CyMemberListEventArgs e)
        {
            List<IntelliPromptMemberListItem> items = new List<IntelliPromptMemberListItem>();

            items.Add(new IntelliPromptMemberListItem("true",
                (int)ActiproSoftware.Products.SyntaxEditor.IconResource.Keyword));

            items.Add(new IntelliPromptMemberListItem("false",
                (int)ActiproSoftware.Products.SyntaxEditor.IconResource.Keyword));

            e.MemberListData = items.ToArray();
            e.Handled = true;
        }

        public override DataGridViewColumn Column
        {
            get { return m_column; }
        }

        public override string ColumnName
        {
            get { return m_column.Name; }
        }
    }

    internal class CySIOParamInfo : Cypress.Components.System.Ports.cy_digital_port_v1_0.CyDigitalParamInfo
    {
        #region OutputBuffer Param

        //param name
        const string ParamNameOutputBuffer = "OutputBuffer";

        //PortSIOOutput enum values
        const string EnumValuePortSIOOutput_Unregulated = "0";
        const string EnumValuePortSIOOutput_Regulated = "1";

        public string GetVerilogOutputBuffer(ICyInstQuery_v1 query)
        {
            CyCompDevParam param = query.GetCommittedParam(ParamNameOutputBuffer);

            string value = param.Value;

            if (value == EnumValuePortSIOOutput_Unregulated) return "1'b0";
            if (value == EnumValuePortSIOOutput_Regulated) return "1'b1";

            Debug.Fail("unhandled");
            return string.Empty;
        }

        #endregion

        #region InputBuffer Param

        //param name
        const string ParamNameInputBuffer = "InputBuffer";

        //PortSIOInput enum values
        const string EnumValuePortSIOInput_SingleEnded = "0";
        const string EnumValuePortSIOInput_Differential = "1";

        public string GetVerilogInputBuffer(ICyInstQuery_v1 query)
        {
            CyCompDevParam param = query.GetCommittedParam(ParamNameInputBuffer);

            string value = param.Value;

            if (value == EnumValuePortSIOInput_SingleEnded) return "1'b0";
            if (value == EnumValuePortSIOInput_Differential) return "1'b1";

            Debug.Fail("unhandled");
            return string.Empty;
        }

        #endregion

        #region HiFreq Param

        //param name
        const string ParamNameHiFreq = "HiFreq";

        //PortSIOInput enum values
        const string EnumValuePortSIOHiFreq_Low = "0";
        const string EnumValuePortSIOHiFreq_High = "1";

        public string GetVerilogHiFreq(ICyInstQuery_v1 query)
        {
            CyCompDevParam param = query.GetCommittedParam(ParamNameHiFreq);

            string value = param.Value;

            if (value == EnumValuePortSIOHiFreq_Low) return "1'b0";
            if (value == EnumValuePortSIOHiFreq_High) return "1'b1";

            Debug.Fail("unhandled");
            return string.Empty;
        }

        #endregion

        #region VTrip Param

        //param name
        const string ParamNameVTrip = "VTrip";

        //PortSIOInput enum values
        const string EnumValuePortSIOVTrip_Zero = "0";
        const string EnumValuePortSIOVTrip_One = "1";

        public string GetVerilogVTrip(ICyInstQuery_v1 query)
        {
            CyCompDevParam param = query.GetCommittedParam(ParamNameVTrip);

            string value = param.Value;

            if (value == EnumValuePortSIOVTrip_Zero) return "1'b0";
            if (value == EnumValuePortSIOVTrip_One) return "1'b1";

            Debug.Fail("unhandled");
            return string.Empty;
        }

        #endregion

        #region VRefSelection Param

        //param name
        const string ParamNameVRefSelection = "VRefSelection";

        //PortSIOInput enum values
        const string EnumValuePortSIORefSel_VIO = "0";
        const string EnumValuePortSIORefSel_VoHref = "1";

        public string GetVerilogVRefSelection(ICyInstQuery_v1 query)
        {
            CyCompDevParam param = query.GetCommittedParam(ParamNameVRefSelection);

            string value = param.Value;

            if (value == EnumValuePortSIORefSel_VIO) return "1'b0";
            if (value == EnumValuePortSIORefSel_VoHref) return "1'b1";

            Debug.Fail("unhandled");
            return string.Empty;
        }

        #endregion

        #region PinHysteresisEnabled Param

        public const string ParamNamePinHysteresisEnabled = "PinHysteresisEnabled";
        public const string DefaultHysteresisEnabled = "false";

        const string VerilogHysteresisDisabled = "0";
        const string VerilogHysteresisEnabled = "1";

        internal static void ValidateHysteresisEnabled(CySIOParamInfo info, ICyInstValidate_v1 instVal)
        {
            uint width = info.GetWidth(instVal);

            for (int i = 0; i < width; i++)
            {
                string enabled;
                CyCustErr err = info.GetHysteresisEnabledValue(instVal, i, out enabled);
                bool enabledValue;

                if (err.IsNotOk)
                {
                    instVal.AddError(CySIOParamInfo.ParamNamePinHysteresisEnabled,
                            new CyCustErr(string.Format("pin{0}: {1}", i, err.Message)));
                }
                else if (!bool.TryParse(enabled, out enabledValue))
                {
                    //the expression must have been replaced with an error msg
                    instVal.AddError(CySIOParamInfo.ParamNamePinHysteresisEnabled,
                            new CyCustErr(string.Format("pin{0}: {1}", i, enabled)));
                }
            }
        }

        public string GetVerilogHysteresisEnabledBitArray(ICyInstQuery_v1 query, int width)
        {
            string bits = string.Empty;
            for (int i = 0; i < width; i++)
            {
                bits += GetVerilogHysteresisEnabled(query, i);
            }
            bits = bits.Trim();
            string slewRates = string.Format("{0}'b{1}", bits.Length, bits);
            return slewRates;
        }

        string GetVerilogHysteresisEnabled(ICyInstQuery_v1 query, int pinNum)
        {
            string paramValue = GetHysteresisEnabledValue(query, pinNum);

            if (paramValue == "true") return VerilogHysteresisEnabled;
            if (paramValue == "false") return VerilogHysteresisDisabled;

            //unknown value
            return string.Empty;
        }

        public string GetHysteresisEnabledValue(ICyInstQuery_v1 query, int pinNum)
        {
            CyCompDevParam param = query.GetCommittedParam(ParamNamePinHysteresisEnabled);
            CyPinInfo info;
            CyCustErr err = CyPinInfo.LoadInfo(param.Value, ParamNamePinHysteresisEnabled, 1, true, out info);
            return info.GetPinInfo(pinNum);
        }

        public CyCustErr GetHysteresisEnabledValue(ICyInstValidate_v1 query, int pinNum, out string value)
        {
            CyCompDevParam param = query.GetCommittedParam(ParamNamePinHysteresisEnabled);
            CyPinInfo info;
            CyCustErr err = CyPinInfo.LoadInfo(param.Value, ParamNamePinHysteresisEnabled, 1, true, out info);
            value = info.GetPinInfo(pinNum);
            return err;
        }

        #endregion
    }

    #endregion
}
