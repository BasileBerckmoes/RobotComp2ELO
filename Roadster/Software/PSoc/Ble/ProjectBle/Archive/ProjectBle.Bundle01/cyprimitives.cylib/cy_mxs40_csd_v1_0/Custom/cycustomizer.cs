/*******************************************************************************
* Copyright 2011-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;

namespace cy_mxs40_csd_v1_0
{
    class CyCustomizer : ICyShapeCustomize_v1
    {
        const string SENSE_BASE_TERM_NAME = "sense";
        const string RX_BASE_TERM_NAME = "rx";
        const string TX_BASE_TERM_NAME = "tx";
        const string SHIELD_BASE_TERM_NAME = "shield";
        const string ADC_CHANNEL_BASE_TERM_NAME = "adc_channel";
        const string DEDICATED_IO_BASE_TERM_NAME = "dedicated_io";
		const string TERM_NAME_CHANGE_PATTERN = "{0}[{1}:0]";

        public CyCustErr CustomizeShapes(ICyInstQuery_v1 instQuery, ICySymbolShapeEdit_v1 shapeEdit,
            ICyTerminalEdit_v1 termEdit)
        {
            CyCustErr err;

            // We leave the symbol as it is for symbol preview
            if (instQuery.IsPreviewCanvas)
                return CyCustErr.OK;

            // Read Parameters
            CyCompDevParam sensorsCountParam = instQuery.GetCommittedParam("sensors_count");
            CyCompDevParam rxCountParam = instQuery.GetCommittedParam("rx_count");
            CyCompDevParam txCountParam = instQuery.GetCommittedParam("tx_count");
            CyCompDevParam shieldCountParam = instQuery.GetCommittedParam("shield_count");
            CyCompDevParam adcChannelCountParam = instQuery.GetCommittedParam("adc_channel_count");
            CyCompDevParam dedicatedIOCountParam = instQuery.GetCommittedParam("dedicated_io_count");
            byte sensorsCount = byte.Parse(sensorsCountParam.Value);
            byte shieldCount = byte.Parse(shieldCountParam.Value);
            byte rxCount = byte.Parse(rxCountParam.Value);
            byte txCount = byte.Parse(txCountParam.Value);
            byte adcChannelCount = byte.Parse(adcChannelCountParam.Value);
            byte dedicatedIOCount = byte.Parse(dedicatedIOCountParam.Value);

            string senseTermName = termEdit.GetTermName(SENSE_BASE_TERM_NAME);
            string rxTermName = termEdit.GetTermName(RX_BASE_TERM_NAME);
            string txTermName = termEdit.GetTermName(TX_BASE_TERM_NAME);
            string shieldTermName = termEdit.GetTermName(SHIELD_BASE_TERM_NAME);
            string adcChannelTermName = termEdit.GetTermName(ADC_CHANNEL_BASE_TERM_NAME);
            string dedicatedIOTermName = termEdit.GetTermName(DEDICATED_IO_BASE_TERM_NAME);

            byte senseBusWidth = (byte)(sensorsCount - 1);
            byte rxBusWidth = (byte)(rxCount - 1);
            byte txBusWidth = (byte)(txCount - 1);
            byte shieldBusWidth = (byte)(shieldCount - 1);
            byte adcChannelBusWidth = (byte)(adcChannelCount - 1);
            byte dedicatedIOBusWidth = (byte)(dedicatedIOCount - 1);

            err = termEdit.TerminalRename(senseTermName, senseBusWidth > 0 ? string.Format(TERM_NAME_CHANGE_PATTERN,
                SENSE_BASE_TERM_NAME, senseBusWidth.ToString()) : SENSE_BASE_TERM_NAME);
			if (err.IsNotOK)
                return err;

            err = termEdit.TerminalRename(rxTermName, rxBusWidth > 0 ? string.Format(TERM_NAME_CHANGE_PATTERN,
                RX_BASE_TERM_NAME, rxBusWidth.ToString()) : RX_BASE_TERM_NAME);
			if (err.IsNotOK)
                return err;

            err = termEdit.TerminalRename(txTermName, txBusWidth > 0 ? string.Format(TERM_NAME_CHANGE_PATTERN,
                TX_BASE_TERM_NAME, txBusWidth.ToString()) : TX_BASE_TERM_NAME);
			if (err.IsNotOK)
                return err;

            err = termEdit.TerminalRename(shieldTermName, shieldBusWidth > 0 ? string.Format(TERM_NAME_CHANGE_PATTERN,
                SHIELD_BASE_TERM_NAME, shieldBusWidth.ToString()) : SHIELD_BASE_TERM_NAME);
			if (err.IsNotOK)
                return err;

            err = termEdit.TerminalRename(adcChannelTermName, adcChannelBusWidth > 0 ? string.Format(TERM_NAME_CHANGE_PATTERN,
                ADC_CHANNEL_BASE_TERM_NAME, adcChannelBusWidth.ToString()) : ADC_CHANNEL_BASE_TERM_NAME);
			if (err.IsNotOK)
                return err;

            err = termEdit.TerminalRename(dedicatedIOTermName, dedicatedIOBusWidth > 0 ? string.Format(TERM_NAME_CHANGE_PATTERN,
                DEDICATED_IO_BASE_TERM_NAME, dedicatedIOBusWidth.ToString()) : DEDICATED_IO_BASE_TERM_NAME);
			if (err.IsNotOK)
                return err;

            return CyCustErr.OK;
        }
    }
}
