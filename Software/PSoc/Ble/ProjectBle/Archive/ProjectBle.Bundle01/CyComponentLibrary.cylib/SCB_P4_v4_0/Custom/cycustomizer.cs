/*******************************************************************************
* Copyright 2012-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using SCB_P4_v4_0.Tabs.EZI2C;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using CyTerminalControl_v1 = CyDesigner.Toolkit.TerminalControl_v1.CyTerminalControl_v1;

namespace SCB_P4_v4_0
{
    sealed public partial class CyCustomizer : ICyParamEditHook_v1, ICyDRCProvider_v1, ICyBootLoaderSupport,
                                ICyExprEval_v2
    {
        CyParameters m_parameters;
        #region ICyParamEditHook_v1 members
        public System.Windows.Forms.DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery,
            ICyExpressMgr_v1 mgr)
        {
            m_parameters = new CyParameters(edit, termQuery);
            m_parameters.GlobalEditMode = false;

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            editor.UseBigEditor = true;
            m_parameters.m_editor = editor;

            #region Create tab pages
            CyGeneralTab generalTab = new CyGeneralTab(m_parameters, editor);
            CySCBTab scbTab = new CySCBTab(m_parameters, editor);
            CyI2CBasicTab i2cBasicTab = new CyI2CBasicTab(m_parameters, editor);
            CyI2CAdvancedTab i2cAdvancedTab = new CyI2CAdvancedTab(m_parameters, editor);
            CySPIBasicTab spiBasicTab = new CySPIBasicTab(m_parameters, editor);
            CySPIAdvancedTab spiAdvancedTab = new CySPIAdvancedTab(m_parameters, editor);
            CySPIPinsTab spiPinsTab = new CySPIPinsTab(m_parameters, editor);
            CyUARTConfigureTab uartConfigTab = new CyUARTConfigureTab(m_parameters, editor);
            CyUARTAdvancedTab uartAdvancedTab = new CyUARTAdvancedTab(m_parameters, editor);
            CyUARTPinsTab uartPinsTab = new CyUARTPinsTab(m_parameters, editor);
            CyEZI2CTab ezi2cBasicTab = new CyEZI2CTab(m_parameters, editor);
            CyEZI2CAdvancedTab ezi2cAdvancedTab = new CyEZI2CAdvancedTab(m_parameters, editor);
            #endregion

            #region Interaction between expression view and custom view
            CyParamExprDelegate generalChanged =
            delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                m_parameters.GlobalEditMode = false;
                generalTab.UpdateUI();
                scbTab.UpdateUI();
                m_parameters.GlobalEditMode = true;
            };

            CyParamExprDelegate i2CBasicDataChanged = delegate(ICyParamEditor custEditor,
                CyCompDevParam param)
            {
                m_parameters.GlobalEditMode = false;
                i2cBasicTab.UpdateUI();
                m_parameters.GlobalEditMode = true;
            };

            CyParamExprDelegate i2CAdvancedDataChanged = delegate(ICyParamEditor custEditor,
                CyCompDevParam param)
            {
                m_parameters.GlobalEditMode = false;
                i2cAdvancedTab.UpdateUI();
                m_parameters.GlobalEditMode = true;
            };

            CyParamExprDelegate ezI2CBasicDataChanged = delegate(ICyParamEditor custEditor,
                CyCompDevParam param)
            {
                m_parameters.GlobalEditMode = false;
                ezi2cBasicTab.UpdateUI();
                m_parameters.GlobalEditMode = true;
            };

            CyParamExprDelegate ezI2CAdvancedDataChanged = delegate(ICyParamEditor custEditor,
                CyCompDevParam param)
            {
                m_parameters.GlobalEditMode = false;
                ezi2cAdvancedTab.UpdateUI();
                m_parameters.GlobalEditMode = true;
            };

            CyParamExprDelegate spiDataChanged = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                m_parameters.GlobalEditMode = false;
                spiBasicTab.UpdateUI();
                spiAdvancedTab.UpdateUI();
                m_parameters.GlobalEditMode = true;
            };

            CyParamExprDelegate uartDataChanged = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                m_parameters.GlobalEditMode = false;
                uartConfigTab.UpdateUI();
                uartAdvancedTab.UpdateUI();
                m_parameters.GlobalEditMode = true;
            };

            #endregion

            #region Add tabs to the customizer
            editor.AddCustomPage(generalTab.TabDisplayName, generalTab, generalChanged, generalTab.TabName);
            editor.AddCustomPage(scbTab.TabDisplayName, scbTab, generalChanged, scbTab.TabName);
            editor.AddCustomPage(i2cBasicTab.TabDisplayName, i2cBasicTab, i2CBasicDataChanged, i2cBasicTab.TabName);
            editor.AddCustomPage(i2cAdvancedTab.TabDisplayName, i2cAdvancedTab, i2CAdvancedDataChanged,
                i2cAdvancedTab.TabName);
            editor.AddCustomPage(ezi2cBasicTab.TabDisplayName, ezi2cBasicTab, ezI2CBasicDataChanged,
                ezi2cBasicTab.TabName);
            editor.AddCustomPage(ezi2cAdvancedTab.TabDisplayName, ezi2cAdvancedTab, ezI2CAdvancedDataChanged,
                ezi2cAdvancedTab.TabName);
            editor.AddCustomPage(spiBasicTab.TabDisplayName, spiBasicTab, spiDataChanged, spiBasicTab.TabName);
            editor.AddCustomPage(spiAdvancedTab.TabDisplayName, spiAdvancedTab, spiDataChanged,
                spiAdvancedTab.TabName);
            editor.AddCustomPage(spiPinsTab.TabDisplayName, spiPinsTab, spiDataChanged, spiPinsTab.TabName);
            editor.AddCustomPage(uartConfigTab.TabDisplayName, uartConfigTab, uartDataChanged,
                uartConfigTab.TabName);
            editor.AddCustomPage(uartAdvancedTab.TabDisplayName, uartAdvancedTab, uartDataChanged, 
                uartAdvancedTab.TabName);
            editor.AddCustomPage(uartPinsTab.TabDisplayName, uartPinsTab, uartDataChanged, uartPinsTab.TabName);

            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");
            #endregion

            m_parameters.TriggerScbModeChanged();

            // Update all tabs
            generalTab.UpdateUI();
            scbTab.UpdateUI();
            i2cBasicTab.UpdateUI();
            i2cAdvancedTab.UpdateUI();
            spiBasicTab.UpdateUI();
            spiAdvancedTab.UpdateUI();
            spiPinsTab.UpdateUI();
            uartConfigTab.UpdateUI();
            uartAdvancedTab.UpdateUI();
            uartPinsTab.UpdateUI();
            ezi2cBasicTab.UpdateUI();
            ezi2cAdvancedTab.UpdateUI();

            m_parameters.GlobalEditMode = true;

            edit.NotifyWhenDesignUpdates(m_parameters.UpdateDesigns);

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

        #region ICyBootLoaderSupport members
        public CyCustErr IsBootloaderReady(ICyInstQuery_v1 inst)
        {
            CyParameters parameters = new CyParameters(inst);

            if (parameters.SCBMode == CyESCBMode.I2C)
            {
                if (parameters.I2cMode.Value != CyEI2CModeType.I2C_SLAVE &&
                    parameters.I2cMode.Value != CyEI2CModeType.I2C_MULTI_MASTER_SLAVE)
                    return new CyCustErr(String.Concat(Resources.BtldrSupportError, " ", Resources.I2CChangeMode));
            }
            else if (parameters.SCBMode == CyESCBMode.SPI)
            {
                if (parameters.SpiMode.Value != CyESPIModeType.SPI_SLAVE)
                    return new CyCustErr(String.Concat(Resources.BtldrSupportError, " ", Resources.SPIChangeMode));
                if (parameters.SpiSubMode.Value != CyESPISubModeType.MOTOROLA)
                    return new CyCustErr(String.Concat(Resources.BtldrSupportError, " ", Resources.SPIChangeSubMode));
                if (parameters.SPI_RemoveSclk)
                    return new CyCustErr(String.Concat(Resources.BtldrSupportError, " ", Resources.SPIChangeSclkPin));
                if (parameters.SPI_RemoveMiso)
                    return new CyCustErr(String.Concat(Resources.BtldrSupportError, " ", Resources.SPIChangeMisoPin));
                if (parameters.SPI_RemoveMosi)
                    return new CyCustErr(String.Concat(Resources.BtldrSupportError, " ", Resources.SPIChangeMosiPin));
                if (parameters.SPI_NumberOfRXDataBits != CyParameters.SPI_BOOTLOADER_SUPPORTED_DATA_BITS)
                    return new CyCustErr(String.Concat(Resources.BtldrSupportError, " ", String.Format(
                        Resources.SPIChangeRxDataBits, CyParameters.SPI_BOOTLOADER_SUPPORTED_DATA_BITS)));
                if (parameters.SPI_NumberOfTXDataBits != CyParameters.SPI_BOOTLOADER_SUPPORTED_DATA_BITS)
                    return new CyCustErr(String.Concat(Resources.BtldrSupportError, " ", String.Format(
                        Resources.SPIChangeTxDataBits, CyParameters.SPI_BOOTLOADER_SUPPORTED_DATA_BITS)));
            }
            else if (parameters.SCBMode == CyESCBMode.UART)
            {
                if (parameters.UartSubMode.Value != CyEUARTSubModeType.STANDARD)
                    return new CyCustErr(String.Concat(Resources.BtldrSupportError, " ", Resources.UARTChangeMode));
                if (parameters.UartDirection.Value != CyEUARTDirectionType.TX_RX)
                    return new CyCustErr(String.Concat(Resources.BtldrSupportError, " ",
                        Resources.UARTChangeDirection));
            }
            else if (parameters.SCBMode == CyESCBMode.EZI2C)
            {
                return new CyCustErr(String.Concat(Resources.BtldrSupportError, " ", Resources.ChangeMode));
            }
            else
            {
                /* Unconfigured mode supports bootloading */
            }

            return CyCustErr.OK;
        }
        #endregion

        #region ICyExprEval_v2 members
        private const byte DEFAULT_MASK = 254;
        private const byte DEFUALT_SLEW_RATE = 0;


        public CyExprEvalFuncEx GetFunction(string exprFuncName)
        {
            switch (exprFuncName)
            {
                case "Get_ScbClkI2cClock":
                    return new CyExprEvalFuncEx(Get_ScbClkI2cClock);

                case "Get_ScbClkI2cMinusTolerance":
                    return new CyExprEvalFuncEx(Get_ScbClkI2cMinusTolerance);

                case "Get_ScbClkI2cPlusTolerance":
                    return new CyExprEvalFuncEx(Get_ScbClkI2cPlusTolerance);

                case "Get_ScbClkSpiClock":
                    return new CyExprEvalFuncEx(Get_ScbClkSpiClock);

                case "Get_ScbClkSpiMinusTolerance":
                    return new CyExprEvalFuncEx(Get_ScbClkSpiMinusTolerance);

                case "Get_ScbClkSpiPlusTolerance":
                    return new CyExprEvalFuncEx(Get_ScbClkSpiPlusTolerance);

                case "Get_ScbClkUartClock":
                    return new CyExprEvalFuncEx(Get_ScbClkUartClock);

                case "Get_ScbClkUartMinusTolerance":
                    return new CyExprEvalFuncEx(Get_ScbClkUartMinusTolerance);

                case "Get_ScbClkUartPlusTolerance":
                    return new CyExprEvalFuncEx(Get_ScbClkUartPlusTolerance);

                case "EzI2c_GetSlaveAddressMask":
                    return new CyExprEvalFuncEx(EZI2C_SlaveAddressMask);

                default:
                    return null;
            }
        }

        private double Get_I2CMinClock(CyEI2CModeType mode, ushort dataRate)
        {
            double clkScb = 0;

            switch (mode)
            {
                case CyEI2CModeType.I2C_SLAVE:
                    clkScb = (double)((dataRate <= CyParamRanges.I2C_DATA_RATE_100) ? (CyParamRanges.I2C_SLAVE_FSCB_MIN_100KBPS) :
                                      (dataRate <= CyParamRanges.I2C_DATA_RATE_400) ? (CyParamRanges.I2C_SLAVE_FSCB_MIN_400KBPS) :
                                      (dataRate <= CyParamRanges.I2C_DATA_RATE_1000) ? (CyParamRanges.I2C_SLAVE_FSCB_MIN_1000KBPS) :
                                      (CyParamRanges.I2C_SLAVE_FSCB_MIN_100KBPS));
                    break;
                case CyEI2CModeType.I2C_MASTER:
                case CyEI2CModeType.I2C_MULTI_MASTER:
                case CyEI2CModeType.I2C_MULTI_MASTER_SLAVE:
                    clkScb = (double)((dataRate <= CyParamRanges.I2C_DATA_RATE_100) ? (CyParamRanges.I2C_MASTER_FSCB_MIN_100KBPS) :
                            (dataRate <= CyParamRanges.I2C_DATA_RATE_400) ? (CyParamRanges.I2C_MASTER_FSCB_MIN_400KBPS) :
                            (dataRate <= CyParamRanges.I2C_DATA_RATE_1000) ? (CyParamRanges.I2C_MASTER_FSCB_MIN_1000KBPS) :
                            (CyParamRanges.I2C_MASTER_FSCB_MIN_100KBPS));
                    break;
                default:
                    Debug.Fail(String.Format("Unhandled EzI2C mode {0}.", mode));
                    break;
            }

            return clkScb;
        }

        private double Get_I2CMaxClock(CyEI2CModeType mode, ushort dataRate)
        {
            double clkScb = 0;

            switch (mode)
            {
                case CyEI2CModeType.I2C_SLAVE:
                    clkScb = (double)((dataRate <= CyParamRanges.I2C_DATA_RATE_100) ? (CyParamRanges.I2C_SLAVE_FSCB_MAX_100KBPS) :
                                      (dataRate <= CyParamRanges.I2C_DATA_RATE_400) ? (CyParamRanges.I2C_SLAVE_FSCB_MAX_400KBPS) :
                                      (dataRate <= CyParamRanges.I2C_DATA_RATE_1000) ? (CyParamRanges.I2C_SLAVE_FSCB_MAX_1000KBPS) :
                                      (CyParamRanges.I2C_SLAVE_FSCB_MAX_100KBPS));
                    break;
                case CyEI2CModeType.I2C_MASTER:
                case CyEI2CModeType.I2C_MULTI_MASTER:
                case CyEI2CModeType.I2C_MULTI_MASTER_SLAVE:
                    clkScb = (double)((dataRate <= CyParamRanges.I2C_DATA_RATE_100) ? (CyParamRanges.I2C_MASTER_FSCB_MAX_100KBPS) :
                            (dataRate <= CyParamRanges.I2C_DATA_RATE_400) ? (CyParamRanges.I2C_MASTER_FSCB_MAX_400KBPS) :
                            (dataRate <= CyParamRanges.I2C_DATA_RATE_1000) ? (CyParamRanges.I2C_MASTER_FSCB_MAX_1000KBPS) :
                            (CyParamRanges.I2C_MASTER_FSCB_MAX_100KBPS));
                    break;
                default:
                    Debug.Fail(String.Format("Unhandled EzI2C mode {0}.", mode));
                    break;
            }

            return clkScb;
        }

        private double Get_Tolerance(double clkMin, double clkMax, CyEToleranceMode mode)
        {
            double tolerance = (double)(((clkMax - clkMin) / clkMin) * 100);

            if (mode == CyEToleranceMode.MINUS_TOLERANCE)
            {
                tolerance = (tolerance <= (double)CyETolerance.MINUS_MAX) ? tolerance : (double)CyETolerance.MINUS_MAX;
            }
            else
            {
                tolerance = (tolerance <= (double)CyETolerance.PLUS_MAX) ? tolerance : (double)CyETolerance.PLUS_MAX;
            }

            return tolerance;
        }

        object Get_ScbClkI2cClock(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (args.Length == 4)
            {
                try
                {
                    CyEI2CModeType mode = (CyEI2CModeType)typeConverter.GetAsByte(args[0]);
                    ushort dataRate = typeConverter.GetAsUShort(args[1]);
                    byte Ovs = typeConverter.GetAsByte(args[2]);
                    bool manualOvs = typeConverter.GetAsBool(args[3]);

                    double clkScb;

                    if (mode == CyEI2CModeType.I2C_SLAVE)
                    {
                        // I2C slave and EZI2C slave
                        clkScb = Get_I2CMinClock(mode, dataRate);
                    }
                    else
                    {
                        // I2C master modes
                        clkScb = (manualOvs) ? (Ovs * dataRate) : Get_I2CMinClock(mode, dataRate);
                    }

                    return clkScb;
                }
                catch (InvalidCastException ex)
                {
                    Debug.Fail(ex.Message);
                }
            }
            else
            {
                return new CyCustErr("Wrong number of arguments.");
            }

            return (double)CyParamRanges.I2C_SLAVE_FSCB_MIN_100KBPS;
        }

        object Get_ScbClkI2cMinusTolerance(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (args.Length == 2)
            {
                try
                {
                    CyEI2CModeType mode = (CyEI2CModeType)typeConverter.GetAsByte(args[0]);
                    bool manualOvs = typeConverter.GetAsBool(args[1]);

                    if (manualOvs && (mode != CyEI2CModeType.I2C_SLAVE))
                    {
                        return (double)CyETolerance.MINUS_MAX;
                    }
                    else
                    {
                        return (double)CyETolerance.ZERO_ACCURACY;
                    }

                }
                catch (InvalidCastException ex)
                {
                    Debug.Fail(ex.Message);
                }
            }
            else
            {
                return new CyCustErr("Wrong number of arguments.");
            }

            return (double)CyETolerance.IMO_ACCURACY;
        }

        object Get_ScbClkI2cPlusTolerance(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (args.Length == 3)
            {
                try
                {
                    CyEI2CModeType mode = (CyEI2CModeType)typeConverter.GetAsByte(args[0]);
                    ushort dataRate = typeConverter.GetAsUShort(args[1]);
                    bool manualOvs = typeConverter.GetAsBool(args[2]);

                    double minClk = Get_I2CMinClock(mode, dataRate);
                    double maxClock = Get_I2CMaxClock(mode, dataRate);
                    double tolerance = Get_Tolerance(minClk, maxClock, CyEToleranceMode.PLUS_TOLERANCE);

                    if (manualOvs && (mode != CyEI2CModeType.I2C_SLAVE))
                    {
                        tolerance = (double)CyETolerance.IMO_ACCURACY;
                    }

                    return tolerance;
                }
                catch (InvalidCastException ex)
                {
                    Debug.Fail(ex.Message);
                }
            }
            else
            {
                return new CyCustErr("Wrong number of arguments.");
            }

            return (double)CyETolerance.IMO_ACCURACY;
        }

        object Get_ScbClkSpiClock(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
           ICyExprTypeConverter typeConverter)
        {
            if (args.Length == 2)
            {
                try
                {
                    ushort dataRate = typeConverter.GetAsUShort(args[0]);
                    byte Ovs = typeConverter.GetAsByte(args[1]);

                    double clkScb = (double)(Ovs * dataRate);

                    // Cut-off to max IMO frequency
                    if (clkScb > CyParamRanges.MAX_IMO_FREQ)
                    {
                        clkScb = CyParamRanges.MAX_IMO_FREQ;
                    }

                    return clkScb;
                }
                catch (InvalidCastException ex)
                {
                    Debug.Fail(ex.Message);
                }
            }
            else
            {
                return new CyCustErr("Wrong number of arguments.");
            }

            return (double)1000;
        }

        object Get_ScbClkSpiMinusTolerance(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (args.Length == 1)
            {
                try
                {
                    CyESPIModeType mode = (CyESPIModeType)typeConverter.GetAsByte(args[0]);

                    return (mode == CyESPIModeType.SPI_MASTER)
                        ? (double)CyETolerance.MINUS_MAX
                        : (double)CyETolerance.IMO_ACCURACY;
                }
                catch (InvalidCastException ex)
                {
                    Debug.Fail(ex.Message);
                }
            }
            else
            {
                return new CyCustErr("Wrong number of arguments.");
            }

            return (double)CyETolerance.MINUS_MAX;
        }

        object Get_ScbClkSpiPlusTolerance(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (args.Length == 1)
            {
                try
                {
                    CyESPIModeType mode = (CyESPIModeType)typeConverter.GetAsByte(args[0]);

                    return (mode == CyESPIModeType.SPI_MASTER)
                        ? (double)CyETolerance.IMO_ACCURACY
                        : (double)CyETolerance.PLUS_MAX;
                }
                catch (InvalidCastException ex)
                {
                    Debug.Fail(ex.Message);
                }
            }
            else
            {
                return new CyCustErr("Wrong number of arguments.");
            }

            return CyETolerance.IMO_ACCURACY;
        }

        object Get_ScbClkUartClock(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (args.Length == 2)
            {
                try
                {
                    uint dataRate = typeConverter.GetAsUInt(args[0]);
                    ushort Ovs = typeConverter.GetAsUShort(args[1]);

                    return (double)(Ovs * dataRate) / 1000;
                }
                catch (InvalidCastException ex)
                {
                    Debug.Fail(ex.Message);
                }
            }
            else
            {
                return new CyCustErr("Wrong number of arguments.");
            }

            return (double)1000;
        }

        object Get_ScbClkUartMinusTolerance(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            return (double)CyETolerance.DEFAULT;
        }

        object Get_ScbClkUartPlusTolerance(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            return (double)CyETolerance.DEFAULT;
        }

        object EZI2C_SlaveAddressMask(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (args.Length == 2)
            {
                try
                {
                    byte primarySlaveAddress = typeConverter.GetAsByte(args[0]);
                    byte secondarySlaveAddress = typeConverter.GetAsByte(args[1]);

                    return (byte)((~(primarySlaveAddress ^ secondarySlaveAddress)) << 1);
                }
                catch (InvalidCastException ex)
                {
                    Debug.Fail(ex.Message);
                }
            }
            else
            {
                return new CyCustErr("Wrong number of arguments.");
            }

            return DEFAULT_MASK;
        }

        #endregion

        #region ICyDRCProvider_v1 members
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CyParameters parameters = new CyParameters(args.InstQueryV1, args.TermQueryV1);

            List<CyCustErr> errorList = new List<CyCustErr>();

            errorList.AddRange(parameters.GetGeneralDrcErrors());

            switch (parameters.SCBMode)
            {
                case CyESCBMode.I2C:
                    errorList.AddRange(parameters.GetI2cDrcErrors());
                    break;
                case CyESCBMode.SPI:
                    errorList.AddRange(parameters.GetSpiDrcErrors());
                    break;
                case CyESCBMode.UART:
                    errorList.AddRange(parameters.GetUartDrcErrors());
                    break;
                case CyESCBMode.EZI2C:
                    errorList.AddRange(parameters.GetEzI2cDrcErrors());
                    break;
                case CyESCBMode.UNCONFIG:
                    errorList.AddRange(parameters.GetUnconfiguredDrcErrors());
                    break;
                default:
                    break;
            }

            for (int i = 0; i < errorList.Count; i++)
            {
                if (errorList[i] != CyCustErr.OK)
                {
                    CyDRCInfo_v1.CyDRCType_v1 errorType = errorList[i].ErrorId == CyParameters.WARNING_CODE
                        ? CyDRCInfo_v1.CyDRCType_v1.Warning
                        : CyDRCInfo_v1.CyDRCType_v1.Error;
                    yield return new CyDRCInfo_v1(errorType, errorList[i].Message);
                }
            }
        }
        #endregion
    }
}
