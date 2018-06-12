/*******************************************************************************
* Copyright 2012-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace SCB_P4_v4_0
{
    public partial class CyCustomizer : ICyAPICustomize_v1
    {
        #region API Customizer File Constants and Variables

        private const string ACTUAL_SAMPLE_RATE_PARAM_NAME = "ActualDataRate";

        const string I2C_FILE_PATTERN = "SCB_I2C";
        const string EZI2C_FILE_PATTERN = "SCB_EZI2C";
        const string UART_PATTERN = "SCB_UART";
        const string SPI_PATTERN = "SCB_SPI";
        const string SPI_UART_PATTERN = "SCB_SPI_UART";

        const string I2C_SLAVE_NAME = "SCB_I2C_SLAVE.c";
        const string I2C_MASTER_NAME = "SCB_I2C_MASTER.c";
        const string SPI_INTERRUPTS_FILE_PATTERN = "SCB_SPI_UART_INT";

        const string FF_DATA_NR_LOG2_PLUS1_MASK_PRMNAME = "FFDataNRLog2Plus1Mask";
        const string FF_DATA_NR_LOG2_MASK_PRMNAME = "FFDataNRLog2Mask";
        const string FIFO_SIZE_PRMNAME = "FifoSize";
        const string EZDATANR_PRMNAME = "EZDataNR";
        const string HSIOMSELINIT_PRMNAME = "HsiomSelInit";

        const string SPI_BYTE_TO_BYTE_PRMNAME = "SpiByteToByte";
        const string UART_BYTE_TO_BYTE_PRMNAME = "UartByteToByte";

        CyAPICustomizer m_i2cSlaveName = null;
        CyAPICustomizer m_i2cMasterName = null;
        CyAPICustomizer m_spiUartInterruptName = null;

        List<CyAPICustomizer> m_i2cFiles = new List<CyAPICustomizer>();
        List<CyAPICustomizer> m_spiFiles = new List<CyAPICustomizer>();
        List<CyAPICustomizer> m_uartFiles = new List<CyAPICustomizer>();
        List<CyAPICustomizer> m_ezi2cFiles = new List<CyAPICustomizer>();
        #endregion

        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery,
            IEnumerable<CyAPICustomizer> apis)
        {
            CyParameters parameters = new CyParameters(query, termQuery);

            List<CyAPICustomizer> inputCustomizers = new List<CyAPICustomizer>(apis);
            List<CyAPICustomizer> outputCustomizers = FilterAPI(inputCustomizers, parameters);

            Dictionary<string, string> paramDict = inputCustomizers[0].MacroDictionary;

            GenerateInclude(query, paramDict, parameters, inputCustomizers);
            GenerateActualSampleRate(paramDict, parameters);
            GenerateAutoLowHighOversampling(paramDict, parameters);
            GenerateBootloaderByteToByte(paramDict, parameters);
            GenerateHsiomSelInit(paramDict, parameters);

            // Replace macro dictionaries with paramDict
            foreach (CyAPICustomizer file in outputCustomizers)
            {
                file.MacroDictionary = paramDict;
            }

            return outputCustomizers;
        }

        /// <summary>
        /// Filter API files depending on the SCB mode.
        /// </summary>
        private List<CyAPICustomizer> FilterAPI(List<CyAPICustomizer> inputCustomizers, CyParameters parameters)
        {
            List<CyAPICustomizer> outputCustomizers = new List<CyAPICustomizer>();

            foreach (CyAPICustomizer file in inputCustomizers)
            {
                if (file.OriginalName.Contains(EZI2C_FILE_PATTERN))
                    m_ezi2cFiles.Add(file);

                if (file.OriginalName.Contains(I2C_FILE_PATTERN))
                    m_i2cFiles.Add(file);
                if (file.OriginalName.Contains(SPI_PATTERN))
                    m_spiFiles.Add(file);
                if (file.OriginalName.Contains(UART_PATTERN) || file.OriginalName.Contains(SPI_UART_PATTERN))
                    m_uartFiles.Add(file);

                if (file.OriginalName.EndsWith(I2C_SLAVE_NAME))
                    m_i2cSlaveName = file;

                if (file.OriginalName.EndsWith(I2C_MASTER_NAME))
                    m_i2cMasterName = file;

                if (file.OriginalName.Contains(SPI_INTERRUPTS_FILE_PATTERN))
                    m_spiUartInterruptName = file;
            }

            outputCustomizers.AddRange(inputCustomizers);

            switch (parameters.SCBMode)
            {
                case CyESCBMode.EZI2C:

                    foreach (CyAPICustomizer item in m_i2cFiles)
                    {
                        outputCustomizers.Remove(item);
                    }

                    foreach (CyAPICustomizer item in m_spiFiles)
                    {
                        outputCustomizers.Remove(item);
                    }

                    foreach (CyAPICustomizer item in m_uartFiles)
                    {
                        outputCustomizers.Remove(item);
                    }

                    break;

                case CyESCBMode.I2C:

                    foreach (CyAPICustomizer item in m_ezi2cFiles)
                    {
                        outputCustomizers.Remove(item);
                    }

                    foreach (CyAPICustomizer item in m_spiFiles)
                    {
                        outputCustomizers.Remove(item);
                    }

                    foreach (CyAPICustomizer item in m_uartFiles)
                    {
                        outputCustomizers.Remove(item);
                    }

                    //Remove SCB_I2C_SLAVE.c 
                    if (parameters.I2cMode.Value != CyEI2CModeType.I2C_SLAVE && parameters.I2cMode.Value !=
                        CyEI2CModeType.I2C_MULTI_MASTER_SLAVE)
                        outputCustomizers.Remove(m_i2cSlaveName);

                    //Remove SCB_I2C_MASTER.c
                    if (parameters.I2cMode.Value == CyEI2CModeType.I2C_SLAVE)
                        outputCustomizers.Remove(m_i2cMasterName);

                    break;
                case CyESCBMode.UART:
                case CyESCBMode.SPI:

                    foreach (CyAPICustomizer item in m_ezi2cFiles)
                    {
                        outputCustomizers.Remove(item);
                    }

                    foreach (CyAPICustomizer item in m_i2cFiles)
                    {
                        outputCustomizers.Remove(item);
                    }

                    if (parameters.SCBMode == CyESCBMode.SPI &&
                        parameters.SPI_InterruptMode != CyEInterruptModeType.INTERNAL)
                    {
                        outputCustomizers.Remove(m_spiUartInterruptName);
                    }

                    if (parameters.SCBMode == CyESCBMode.UART)
                    {
                        foreach (CyAPICustomizer item in m_spiFiles)
                        {
                            if (m_uartFiles.Contains(item) == false)
                            {
                                outputCustomizers.Remove(item);
                            }
                        }
                    }
                    else
                    {
                        foreach (CyAPICustomizer item in m_uartFiles)
                        {
                            if (m_spiFiles.Contains(item) == false)
                            {
                                outputCustomizers.Remove(item);
                            }
                        }
                    }
                    break;
                case CyESCBMode.UNCONFIG:
                    // Remove UART and SPI files for SCB IP V1 devices
                    if (parameters.IsScbIPV1)
                    {
                        foreach (CyAPICustomizer item in m_spiFiles)
                        {
                            outputCustomizers.Remove(item);
                        }

                        foreach (CyAPICustomizer item in m_uartFiles)
                        {
                            outputCustomizers.Remove(item);
                        }
                    }
                    break;
            }
            return outputCustomizers;
        }

        /// <summary>
        /// Generate #include for all .h files which presence is conditional (depends on the SCB mode).
        /// </summary>
        private void GenerateInclude(ICyInstQuery_v1 query, Dictionary<string, string> paramDict,
                                     CyParameters parameters, List<CyAPICustomizer> inputCustomizers)
        {
            StringBuilder builderInclude = new StringBuilder();
            string instName = query.GetCommittedParam("INSTANCE_NAME").Value;
            switch (parameters.SCBMode)
            {
                case CyESCBMode.I2C:
                    for (int i = 0; i < m_i2cFiles.Count; i++)
                    {
                        if (m_i2cFiles[i].OutputName.EndsWith(".h"))
                        {
                            builderInclude.AppendLine(AddIncludeStr(m_i2cFiles[i].OutputName));
                        }
                    }
                    break;
                case CyESCBMode.UART:
                    for (int i = 0; i < m_uartFiles.Count; i++)
                    {
                        if (m_uartFiles[i].OutputName.EndsWith(".h"))
                        {
                            builderInclude.AppendLine(AddIncludeStr(m_uartFiles[i].OutputName));
                        }
                    }
                    break;
                case CyESCBMode.SPI:
                    for (int i = 0; i < m_spiFiles.Count; i++)
                    {
                        if (m_spiFiles[i].OutputName.EndsWith(".h"))
                        {
                            builderInclude.AppendLine(AddIncludeStr(m_spiFiles[i].OutputName));
                        }
                    }
                    break;
                case CyESCBMode.UNCONFIG:
                    for (int i = 0; i < inputCustomizers.Count; i++)
                    {
                        if (inputCustomizers[i].OutputName.EndsWith(".h") &&
                            inputCustomizers[i].OutputName != instName + ".h")
                        {
                            builderInclude.AppendLine(AddIncludeStr(inputCustomizers[i].OutputName));
                        }
                    }
                    break;
                default:
                    Debug.Assert(false);
                    break;
            }
            paramDict.Add("IncludeDefines", builderInclude.ToString());
        }

        private static string AddIncludeStr(string name)
        {
            return String.Format("#include \"{0}\"", name);
        }

        private void GenerateActualSampleRate(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            switch (parameters.SCBMode)
            {
                case CyESCBMode.I2C:
                case CyESCBMode.EZI2C:
                    double actualSampleRate;
                    if (parameters.I2C_ManualOversampleControl)
                    {
                        actualSampleRate = parameters.GetActualDataRate(parameters.SCBMode);
                    }
                    else
                    {
                        byte ovsLow;
                        byte ovsHigh;
                        parameters.GetAutoOversamplingLowHigh(out actualSampleRate, out ovsLow, out ovsHigh);
                    }
                    paramDict.Add(ACTUAL_SAMPLE_RATE_PARAM_NAME, Math.Round(actualSampleRate).ToString());
                    break;
                default:
                    // Do nothing
                    break;
            }
        }

        private void GenerateAutoLowHighOversampling(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            byte ovsLow;
            byte ovsHigh;

            if (parameters.I2C_ManualOversampleControl)
            {
                ovsLow = parameters.I2C_OvsFactorLow;
                ovsHigh = parameters.I2C_OvsFactorHigh;
            }
            else
            {
                parameters.GetAutoOversamplingLowHigh(out ovsLow, out ovsHigh);
            }

            paramDict.Add("AutoI2cOvsFactorLow", ovsLow.ToString());
            paramDict.Add("AutoI2cOvsFactorHigh", ovsHigh.ToString());
        }

        private void GenerateBootloaderByteToByte(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            int[] byteToByte = new int[2];
            int numberOfBits = 0;
            double bitTime = 0;
            double dataRate = 0;

            // Index 0 for SPI and 1 for UART.
            for (int i = 0; i < byteToByte.Length; i++)
            {
                if (0 == i)
                {
                    if (parameters.SCBMode == CyESCBMode.SPI)
                    {
                        // Get data rate in kbps. Select smaller data rate from actaul and desired (internal clock).
                        dataRate = (parameters.SPI_ClockFromTerminal == false) &&
                            (parameters.GetActualDataRate(CyESCBMode.SPI) > parameters.SPI_BitsRateInKHz)
                                ? (double)parameters.SPI_BitsRateInKHz
                                : parameters.GetActualDataRate(CyESCBMode.SPI);

                        // Number of bits to transmit / receive
                        numberOfBits = (byte)parameters.SPI_NumberOfTXDataBits;
                    }
                    else
                    {
                        // Get arbitrary numbers for Unconfigured mode
                        numberOfBits = CyParamRanges.SPI_BTLDR_DEFAULT_NUMBER_OF_BITS;
                        dataRate = CyParamRanges.SPI_BTLDR_DEFAULT_BIT_RATE_KBPS;
                    }
                }
                else
                {
                    if (parameters.SCBMode == CyESCBMode.UART)
                    {
                        // Get data rate in kbps. Select smaller data rate from actaul and desired (internal clock).
                        dataRate = (parameters.UART_ClockFromTerminal == false) &&
                            (parameters.GetActualDataRate(CyESCBMode.UART) > parameters.UART_DataRate)
                                ? (double)parameters.UART_DataRate
                                : parameters.GetActualDataRate(CyESCBMode.UART);

                        // Number of bits to transmit / receive: Start bit, data bits, Parity bit, Stop bits.
                        // There is no parity when it set to None.
                        // Stop bits enum (1 bit = 2, 1.5 bits = 3, 2 bits = 4. The value is divided by 2 to get 
                        // number of Stop bits).
                        numberOfBits = 1 + (int)parameters.UartNumberDataBits.Value +
                            Convert.ToInt32(parameters.UartParityType.Value != CyEUARTParityType.PARITY_NONE) +
                            ((int)parameters.UartNumberStopBits.Value / 2);
                    }
                    else
                    {
                        // Get arbitrary numbers for Unconfigured mode
                        numberOfBits = CyParamRanges.UART_BTLDR_DEFAULT_NUMBER_OF_BITS;
                        dataRate = CyParamRanges.UART_BTLDR_DEFAULT_BIT_RATE_KBPS;
                    }
                }

                // Actual data rate is in kbps
                bitTime = (1000 / dataRate);

                // Byte to byte equal to (data element bus time * 2)
                byteToByte[i] = (int)Math.Ceiling(2 * bitTime * numberOfBits);
            }

            paramDict.Add(SPI_BYTE_TO_BYTE_PRMNAME, byteToByte[0].ToString());
            paramDict.Add(UART_BYTE_TO_BYTE_PRMNAME, byteToByte[1].ToString());

            paramDict.Add(FF_DATA_NR_LOG2_PLUS1_MASK_PRMNAME, String.Format("0x{0}",
                parameters.FfDataNrLog2Plus1Mask.ToString("X2")));
            paramDict.Add(FF_DATA_NR_LOG2_MASK_PRMNAME, String.Format("0x{0}", 
                parameters.FfDataNrLog2Mask.ToString("X2")));

            paramDict.Add(FIFO_SIZE_PRMNAME, parameters.GetBufferMinSize().ToString());
            paramDict.Add(EZDATANR_PRMNAME, parameters.EzDataNr.ToString());
        }

        private void GenerateHsiomSelInit(Dictionary<string, string> paramDict, CyParameters parameters)
        {
            StringBuilder strBuilder = new StringBuilder();

            if (parameters.SCB_MosiSclRxEnabled)
            {
                string wake = parameters.SCB_RxWake ? "_WAKE" : String.Empty;

                if (parameters.IsScbIPV1)
                    strBuilder.AppendLine(String.Format("{0}_SCL_HSIOM_SEL_GPIO,", parameters.InstName));
                else if (parameters.IsScbIPV2 && parameters.IsBleCapable)
                    strBuilder.AppendLine(String.Format("{0}_RX{1}_SDA_MOSI_HSIOM_SEL_GPIO,", 
                        parameters.InstName, wake));
                else
                    strBuilder.AppendLine(String.Format("{0}_RX{1}_SCL_MOSI_HSIOM_SEL_GPIO,", 
                        parameters.InstName, wake));
            }
            else
                strBuilder.AppendLine("0u,");

            if (parameters.SCB_MisoSdaTxEnabled)
            {
                if (parameters.IsScbIPV1)
                    strBuilder.AppendLine(String.Format("            {0}_SDA_HSIOM_SEL_GPIO,", parameters.InstName));
                else if (parameters.IsScbIPV2 && parameters.IsBleCapable)
                    strBuilder.AppendLine(String.Format("            {0}_TX_SCL_MISO_HSIOM_SEL_GPIO,", 
                        parameters.InstName));
                else
                    strBuilder.AppendLine(String.Format("            {0}_TX_SDA_MISO_HSIOM_SEL_GPIO,", 
                        parameters.InstName));
            }
            else
                strBuilder.AppendLine("            0u,");

            if (!parameters.IsScbIPV1)
            {
                if (parameters.SCB_SclkEnabled)
                {
                    if (parameters.IsScbIPV2)
                        strBuilder.AppendLine(String.Format("            {0}_CTS_SCLK_HSIOM_SEL_GPIO,",
                            parameters.InstName));
                    else
                        strBuilder.AppendLine(String.Format("            {0}_SCLK_HSIOM_SEL_GPIO,", parameters.
                            InstName));
                }
                else
                    strBuilder.AppendLine("            0u,");

                if (parameters.SCB_Ss0Enabled)
                {
                    if (parameters.IsScbIPV2)
                        strBuilder.AppendLine(String.Format("            {0}_RTS_SS0_HSIOM_SEL_GPIO,",
                            parameters.InstName));
                    else
                        strBuilder.AppendLine(String.Format("            {0}_SS0_HSIOM_SEL_GPIO,", parameters.
                            InstName));
                }
                else
                    strBuilder.AppendLine("            0u,");

                if (parameters.SCB_Ss1Enabled)
                    strBuilder.AppendLine(String.Format("            {0}_SS1_HSIOM_SEL_GPIO,", parameters.InstName));
                else
                    strBuilder.AppendLine("            0u,");

                if (parameters.SCB_Ss2Enabled)
                    strBuilder.AppendLine(String.Format("            {0}_SS2_HSIOM_SEL_GPIO,", parameters.InstName));
                else
                    strBuilder.AppendLine("            0u,");

                if (parameters.SCB_Ss3Enabled)
                    strBuilder.Append(String.Format("            {0}_SS3_HSIOM_SEL_GPIO,", parameters.InstName));
                else
                    strBuilder.Append("            0u,");
            }

            paramDict.Add(HSIOMSELINIT_PRMNAME, strBuilder.ToString());
        }
    }
}
