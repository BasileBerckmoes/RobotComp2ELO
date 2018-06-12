/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using CyTerminalControl_v1 = CyDesigner.Toolkit.TerminalControl_v1.CyTerminalControl_v1;
using System.Diagnostics;
using System.Windows.Forms;

namespace I2S_v2_70
{
    [CyCompDevCustomizer()]
    public partial class CyCustomizer : ICyParamEditHook_v1, ICyShapeCustomize_v1
    {
        private CyI2SParameters m_parameters = null;
        #region ICyParamEditHook_v1 Members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            m_parameters = new CyI2SParameters(edit);
            CyI2SBasicTab basicTab = new CyI2SBasicTab(m_parameters);
            CyI2SAdvancedTab advancedTab = new CyI2SAdvancedTab(m_parameters);
            CyTerminalControl_v1 interconnectTab = null;

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();

            CyParamExprDelegate exprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                m_parameters.GlobalEditMode = false;
                if (param.TabName == basicTab.TabName)
                {
                    basicTab.UpdateUI();
                }
                else if (param.TabName == advancedTab.TabName)
                {
                    advancedTab.UpdateUI();
                }

                if (interconnectTab != null)
                {
                    UpdateInterconnectDisplay(interconnectTab);
                }
                m_parameters.GlobalEditMode = true;
            };

            CyParamExprDelegate sbExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                m_parameters.GlobalEditMode = false;
                if (interconnectTab != null)
                {
                    UpdateInterconnectDisplay(interconnectTab);
                }
                m_parameters.GlobalEditMode = true;
            };

            editor.ParamExprCommittedDelegate = sbExprDelegate; 

            editor.AddCustomPage(Properties.Resources.BasicTabName, basicTab, exprDelegate, 
                basicTab.TabName);
            editor.AddCustomPage(Properties.Resources.AdvancedTabName, advancedTab, exprDelegate,
                advancedTab.TabName);

            // System Builder support
            if (m_parameters.IsPSoC4 && edit.IsInSystemBuilder)
            {
                interconnectTab = new CyTerminalControl_v1(edit);
                UpdateInterconnectDisplay(interconnectTab);

                ICyClockControl_v1 clockControl = edit.DesignQuery.CreateClockCustomizerControl(this, edit);
                CyClockParamEditingControl clockTabControl = new CyClockParamEditingControl(edit,
                    clockControl.DisplayControl);

                editor.AddCustomPage(Properties.Resources.InterconnectTabName, interconnectTab, exprDelegate,
                                 "Interconnect");
                editor.AddCustomPage(Properties.Resources.ClockTabName, clockTabControl, null,
                    clockTabControl.TabName);
            }
            
            editor.AddDefaultPage(Properties.Resources.BuiltInTabName, "Built-in");

            editor.UseBigEditor = true;

            basicTab.UpdateUI();
            advancedTab.UpdateUI();

            m_parameters.GlobalEditMode = true;
            return editor.ShowDialog();
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

        #region ICyShapeCustomize_v1 Members

        public CyCustErr CustomizeShapes(ICyInstQuery_v1 instQuery, ICySymbolShapeEdit_v1 shapeEdit,
            ICyTerminalEdit_v1 termEdit)
        {
            const string SDI_TERM_NAME = "sdi";
            const string SDO_TERM_NAME = "sdo";
            const string RXDMA0_TERM_NAME = "rx_dma0";
            const string TXDMA0_TERM_NAME = "tx_dma0";
            const string RXDMA1_TERM_NAME = "rx_dma1";
            const string TXDMA1_TERM_NAME = "tx_dma1";
            const string CLIP_TERM_NAME = "clip";

            CyI2SParameters parameters = new CyI2SParameters(instQuery);

            CyCustErr err = ChangeBusWidth(termEdit, SDI_TERM_NAME, parameters.RxNumChannels);
            if (err.IsNotOK) return err;

            err = ChangeBusWidth(termEdit, SDO_TERM_NAME, parameters.TxNumChannels);
            if (err.IsNotOK) return err;

            err = ChangeBusWidth(termEdit, RXDMA0_TERM_NAME, parameters.RxNumChannels);
            if (err.IsNotOK) return err;

            err = ChangeBusWidth(termEdit, TXDMA0_TERM_NAME, parameters.TxNumChannels);
            if (err.IsNotOK) return err;

            err = ChangeBusWidth(termEdit, RXDMA1_TERM_NAME, parameters.RxNumChannels);
            if (err.IsNotOK) return err;

            err = ChangeBusWidth(termEdit, TXDMA1_TERM_NAME, parameters.TxNumChannels);
            if (err.IsNotOK) return err;

            err = ChangeBusWidth(termEdit, CLIP_TERM_NAME, parameters.RxNumChannels);
            if (err.IsNotOK) return err;

            return err;
        }

        private CyCustErr ChangeBusWidth(ICyTerminalEdit_v1 termEdit, string termName, CyENumberOfChannels numChannels)
        {
            string busWidthString = GetBusWidthString(numChannels);
            CyCustErr err = termEdit.TerminalRename(termEdit.GetTermName(termName), termName + busWidthString);
            return err;
        }

        /// <summary>
        /// Returns the string that shows the bus width and will be displayed as part of terminal name
        /// </summary>
        private string GetBusWidthString(CyENumberOfChannels numChannels)
        {
            string busWidthString = "";
            switch (numChannels)
            {
                case CyENumberOfChannels.MONO_LEFT:
                case CyENumberOfChannels.MONO_RIGHT:
                case CyENumberOfChannels.STEREO:
                    busWidthString = "[0:0]";
                    break;
                case CyENumberOfChannels.CHANNEL_4:
                    busWidthString = "[1:0]";
                    break;
                case CyENumberOfChannels.CHANNEL_6:
                    busWidthString = "[2:0]";
                    break;
                case CyENumberOfChannels.CHANNEL_8:
                    busWidthString = "[3:0]";
                    break;
                case CyENumberOfChannels.CHANNEL_10:
                    busWidthString = "[4:0]";
                    break;
                default:
                    Debug.Fail(Properties.Resources.DebugUnexpectedCase + typeof(CyENumberOfChannels).Name);
                    break;
            }
            return busWidthString;
        }
        #endregion
    }
}
