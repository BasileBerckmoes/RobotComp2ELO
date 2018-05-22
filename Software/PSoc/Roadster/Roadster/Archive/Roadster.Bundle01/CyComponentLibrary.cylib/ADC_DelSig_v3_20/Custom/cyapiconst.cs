/******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


using System;
using System.Collections.Generic;
using System.Text;

namespace ADC_DelSig_v3_20
{
    /// <summary>
    ///  ADC Decimator and Modulator constants
    /// </summary>
    public static class Cyrc
    {
        public const uint MAX_CONFIGS = 4;
        public const uint IDEAL_GAIN_CONST = 32768;
        public const uint MIN_RESOLUTION = 8;
        public const uint MAX_RESOLUTION = 20;
        public const uint HIGH_FREQ = 3600000;
        public const uint HIGH_FREQ_16BIT = 3072000;
        public const uint HIGH_FREQ_12BIT = 6144000;
        public const uint MAXCHARGEPUMPCLOCK = 12000000;
        public const uint MINCHARGEPUMPCLOCK = 1000000;

        public static uint[] MAX_FREQ_8_15_BITS =
        // vss/vref  *2     vs/vd    *6Sin      diff   *2di(New) *6Dif    /2dif    /4dif    /8dif    /16dif
        { 6144000, 6144000, 2200000, 1900000, 6144000, 6144000, 1900000, 4800000, 3000000, 2800000, 1500000 };

        public static uint[] MAX_FREQ_16_20_BITS =
        // vss/vref  *2     vs/vd    *6Sin      diff   *2di   *6Dif     /2dif     /4dif    /8dif    /16dif
        {3072000, 3072000, 3072000, 3072000, 3072000, 3072000, 3072000, 2800000, 1000000, 1000000, 1000000};

        public const uint MIN_FREQ_15_20_BITS = 128000;
        public const uint MIN_FREQ_8_14_BITS = 128000;

        public const uint MAX_FREQ_GAIN_8 = 192000;
        public const uint MIN_FREQ_GAIN_8 = 128000;

        /// <summary>
        /// ADC_Clock Constants
        /// </summary>
        public const uint ADC_CLOCK_INTERNAL = 0;
        public const uint ADC_CLOCK_EXTERNAL = 1;

        /// <summary>
        /// INPUT_MODE Constants
        /// </summary>
        public const uint INPUT_MODE_DIFFERENTIAL = 0;
        public const uint INPUT_MODE_SINGLE = 1;

        /// <summary>
        /// ADC_Input_Range Constants
        /// </summary>
        public const uint ADC_IR_VSSA_TO_VREF = 0x00;
        public const uint ADC_IR_VSSA_TO_2VREF = 0x01;
        public const uint ADC_IR_VSSA_TO_VDDA = 0x02;
        public const uint ADC_IR_VSSA_TO_6VREF = 0x03;
        public const uint ADC_IR_VNEG_VREF_DIFF = 0x04;
        public const uint ADC_IR_VNEG_2VREF_DIFF = 0x05;
        public const uint ADC_IR_VNEG_6VREF_DIFF = 0x06;
        public const uint ADC_IR_VNEG_VREF_2_DIFF = 0x07;
        public const uint ADC_IR_VNEG_VREF_4_DIFF = 0x08;
        public const uint ADC_IR_VNEG_VREF_8_DIFF = 0x09;
        public const uint ADC_IR_VNEG_VREF_16_DIFF = 0x0A;


        public static uint[] SumCapin8_15 = {
                            DSM_SUMCAPIN_50_FF,    // VSSA to VREF (New)
                            DSM_SUMCAPIN_50_FF,    // VSSA to 2*VREF (New)
                            DSM_SUMCAPIN_50_FF,    // VSSA to VDDA
                            DSM_SUMCAPIN_0_FF,     // VSSA to 6*VREF (Fixed)
                            DSM_SUMCAPIN_50_FF,    // VNEG +/- VREF (New)
                            DSM_SUMCAPIN_50_FF,    // VNEG +/- 2*VREF (New)
                            DSM_SUMCAPIN_0_FF,     // VNEG +/- 6*VREF (Fixed)
                            DSM_SUMCAPIN_200_FF,   // VNEG +/- VREF/2 (New)
                            DSM_SUMCAPIN_300_FF,   // VNEG +/- VREF/4 (New)
                            DSM_SUMCAPIN_800_FF,   // VNEG +/- VREF/8
                            DSM_SUMCAPIN_1200_FF };// VNEG +/- VREF/16 (New)

        public static uint[] SumCapin16_20 = {
                            DSM_SUMCAPIN_250_FF,   // VSSA to VREF
                            DSM_SUMCAPIN_250_FF,   // VSSA to 2*VREF
                            DSM_SUMCAPIN_50_FF,    // VSSA to VDDA
                            DSM_SUMCAPIN_0_FF,     // VSSA to 6*VREF (Fixed)
                            DSM_SUMCAPIN_250_FF,   // VNEG +/- VREF
                            DSM_SUMCAPIN_100_FF,   // VNEG +/- 2*VREF
                            DSM_SUMCAPIN_0_FF,     // VNEG +/- 6*VREF (Fixed)
                            DSM_SUMCAPIN_300_FF,   // VNEG +/- VREF/2 (New)
                            DSM_SUMCAPIN_600_FF,   // VNEG +/- VREF/4 (New)
                            DSM_SUMCAPIN_900_FF,   // VNEG +/- VREF/8 (New)
                            DSM_SUMCAPIN_900_FF }; // VNEG +/- VREF/16 (New)



        public static uint[] IpCap1_8_15 = { 
                            (DSM_IPCAP1_800FF | DSM_IPCAP1_96FF ),                     //  896 fF VSSA to VREF
                            (DSM_IPCAP1_800FF | DSM_IPCAP1_96FF ),                     //  896 fF VSSA to 2*VREF
                            (DSM_IPCAP1_400FF | DSM_IPCAP1_96FF ),                     //  496 fF VSSA to VDDA (New)
                            (DSM_IPCAP1_400FF),                                        //  400 fF VSSA to 6*VREF
                            (DSM_IPCAP1_800FF | DSM_IPCAP1_96FF ),                     //  896 fF VNEG +/- VREF
                            (DSM_IPCAP1_400FF),                                        //  400 fF VNEG +/- 2*VREF (New)
                            (DSM_IPCAP1_400FF),                                        //  400 fF VNEG +/- 6*VREF
                            (DSM_IPCAP1_1600FF ),                                      // 1600 fF VNEG +/- VREF/2
                            (DSM_IPCAP1_1600FF | DSM_IPCAP1_800FF | DSM_IPCAP1_400FF ),// 2800 fF VNEG +/- VREF/4
                            (DSM_IPCAP1_3200FF | DSM_IPCAP1_192FF | DSM_IPCAP1_96FF),  // 3488 fF VNEG +/- VREF/8
                            (DSM_IPCAP1_3200FF | DSM_IPCAP1_1600FF |DSM_IPCAP1_800FF | DSM_IPCAP1_96FF) // 5696 fF VNEG +/- VREF/16
                            };

        // IpCap1 values for Vssa to Vdda range with reference option Vdda/3. 
        public static uint IpCap1_8_15_Vdda_3 = (DSM_IPCAP1_400FF | DSM_IPCAP1_192FF); // 592 (New)
        public static uint IpCap1_16_20_Vdda_3 = (DSM_IPCAP1_800FF | DSM_IPCAP1_400FF | DSM_IPCAP1_96FF); // 1296 (New) 

        public static uint[] DacCap_8_15 = { 
                            //  992 fF VSSA to VREF
                            (DSM_DACCAP_800FF | DSM_DACCAP_192FF ),                                              
                            //  992 fF VSSA to 2*VREF
                            (DSM_DACCAP_800FF | DSM_DACCAP_192FF ),
                             // 2192 fF VSSA to VDDA (New)
                            (DSM_DACCAP_1600FF | DSM_DACCAP_400FF | DSM_DACCAP_192FF),    
                            // 2400 fF VSSA to 6*VREF
                            (DSM_DACCAP_1600FF | DSM_DACCAP_800FF),
                            //  992 fF VNEG +/- VREF
                            (DSM_DACCAP_800FF | DSM_DACCAP_192FF ),  
                            // 896 fF VNEG +/- 2*VREF (New)
                            (DSM_DACCAP_800FF | DSM_DACCAP_96FF), 
                            // 2400 fF VNEG +/- 6*VREF
                            (DSM_DACCAP_1600FF | DSM_DACCAP_800FF), 
                            //  896 fF VNEG +/- VREF/2
                            (DSM_DACCAP_800FF | DSM_DACCAP_96FF ), 
                            //  800 fF VNEG +/- VREF/4
                            (DSM_DACCAP_800FF ), 
                            //  496 fF VNEG +/- VREF/8
                            (DSM_DACCAP_400FF | DSM_DACCAP_96FF), 
                            //  400 fF VNEG +/- VREF/16
                            (DSM_DACCAP_400FF )                             
                            };

        // DacCap values for Vssa to Vdda range with reference option Vdda/3. 
        public static uint DacCap_8_15_Vdda_3 = (DSM_DACCAP_1600FF | DSM_DACCAP_400FF); //2000 (New)

        public static uint DacCap_16_20_Vdda_3 = (DSM_DACCAP_3200FF | DSM_DACCAP_800FF 
                                                | DSM_DACCAP_192FF | DSM_DACCAP_96FF);  //4288 (New)

        public static uint[] IpCap1_16_20 = { 
                            // 3888 fF VSSA to VREF
                            (DSM_IPCAP1_3200FF | DSM_IPCAP1_400FF | DSM_IPCAP1_192FF | DSM_IPCAP1_96FF), 
                            // 3888 fF VSSA to 2*VREF
                            (DSM_IPCAP1_3200FF | DSM_IPCAP1_400FF | DSM_IPCAP1_192FF | DSM_IPCAP1_96FF), 
                            // 992 fF VSSA to VDDA (New)
                            (DSM_IPCAP1_800FF | DSM_IPCAP1_192FF), 
                            // 688 fF VSSA to 6*VREF (New)
                            (DSM_IPCAP1_400FF | DSM_IPCAP1_192FF | DSM_IPCAP1_96FF), 
                            // 3888 fF VNEG +/- VREF
                            (DSM_IPCAP1_3200FF | DSM_IPCAP1_400FF | DSM_IPCAP1_192FF | DSM_IPCAP1_96FF), 
                            // 1888 fF VNEG +/- 2*VREF (New)
                            (DSM_IPCAP1_1600FF | DSM_IPCAP1_192FF | DSM_IPCAP1_96FF), 
                            // 688 fF VNEG +/- 6*VREF (New)
                            (DSM_IPCAP1_400FF | DSM_IPCAP1_192FF | DSM_IPCAP1_96FF), 
                            // 6000 fF VNEG +/- VREF/2
                            (DSM_IPCAP1_3200FF | DSM_IPCAP1_1600FF | DSM_IPCAP1_800FF | DSM_IPCAP1_400FF), 
                            // 12000 fF VNEG +/- VREF/4
                            (DSM_IPCAP1_6400FF | DSM_IPCAP1_3200FF | DSM_IPCAP1_1600FF | DSM_IPCAP1_800FF), 
                            // 17588 fF = 12800 fF + 4800 fF offset VNEG +/- VREF/8
                            (DSM_IPCAP1_12700FF | DSM_IPCAP1_96FFpath), 
                            //17200 fF = 12400 fF + 4800 fF offset VNEG +/- VREF/16
                            (DSM_IPCAP1_6400FF | DSM_IPCAP1_3200FF | DSM_IPCAP1_1600FF | DSM_IPCAP1_800FF | 
                             DSM_IPCAP1_400FF) 
                            };

        public static uint[] DacCap_16_20 = { 
                            // 4400 fF VSSA to VREF
                            (DSM_DACCAP_3200FF | DSM_DACCAP_800FF | DSM_DACCAP_400FF), 
                            // 4400 fF VSSA to 2*VREF
                            (DSM_DACCAP_3200FF | DSM_DACCAP_800FF | DSM_DACCAP_400FF), 
                            // 4400 fF VSSA to VDDA (New)
                            (DSM_DACCAP_3200FF | DSM_DACCAP_800FF | DSM_DACCAP_400FF), 
                            // 4096 fF VSSA to 6*VREF (New)
                            (DSM_DACCAP_3200FF | DSM_DACCAP_800FF | DSM_DACCAP_96FF), 
                            // 4400 fF VNEG +/- VREF
                            (DSM_DACCAP_3200FF | DSM_DACCAP_800FF | DSM_DACCAP_400FF), 
                            // 4288 fF VNEG +/- 2*VREF (New)
                            (DSM_DACCAP_3200FF | DSM_DACCAP_800FF | DSM_DACCAP_192FF | DSM_DACCAP_96FF), 
                            // 4096 fF VNEG +/- 6*VREF (New)
                            (DSM_DACCAP_3200FF | DSM_DACCAP_800FF | DSM_DACCAP_96FF), 
                            // 3392 fF VNEG +/- VREF/2
                            (DSM_DACCAP_3200FF | DSM_DACCAP_192FF ), 
                            // 3392 fF VNEG +/- VREF/4
                            (DSM_DACCAP_3200FF | DSM_DACCAP_192FF ), 
                            // 2496 fF VNEG +/- VREF/8
                            (DSM_DACCAP_1600FF | DSM_DACCAP_800FF |DSM_DACCAP_96FF), 
                            // 1200 fF VNEG +/- VREF/16
                            (DSM_DACCAP_800FF | DSM_DACCAP_400FF )                             
                            };
        //                                          vss/vref  *2   vs/vd *6Sin dif   *2di  *6Dif /2dif /4dif  /8dif  /16dif
        public static uint[] IPCap1_Res8to15_Real =  {  896,  896,  496,  400,  896,  400,  400, 1600,  2800,  3488,  5696 };
        public static uint[] IPCap1_Res16to20_Real = { 3888, 3888,  992,  688, 3888, 1888,  688, 6000, 12000, 17588, 17200 };
        
        public static uint[] DACCap_Res8to15_Real =  {  992,  992, 2192, 2400,  992,  896, 2400,  896,   800,   496,   400 };
        public static uint[] DACCap_Res16to20_Real = { 4400, 4400, 4400, 4096, 4400, 4288, 4096, 3392,  3392,  2496,  1200 };
        
        public static uint IPCap1_Res8to15_Vdda_3_Real = 592;
        public static uint IPCap1_Res16to20_Vdda_3_Real = 1296;
        
        public static uint DACCap_Res8to15_Vdda_3_Real = 2000;
        public static uint DACCap_Res16to20_Vdda_3_Real = 4288;

        public static uint FCap1_8_15 = DSM_FCAP1_1600FF | DSM_FCAP1_400FF; // 2000
        public static uint FCap1_16_20 = DSM_FCAP1_1600FF | DSM_FCAP1_6400FF; // 8000 (New)

        public static uint IPCap2_FCap2_8_15 = Cyrc.DSM_IPCAP2_50_FF | Cyrc.DSM_FCAP2_100_FF;
        public static uint IPCap2_FCap2_16_20 = Cyrc.DSM_IPCAP2_250_FF | Cyrc.DSM_FCAP2_550_FF; // (New)

        public static uint IPCap3_FCap3_8_15 = Cyrc.DSM_IPCAP3_50_FF | Cyrc.DSM_FCAP3_300_FF;
        public static uint IPCap3_FCap3_16_20 = Cyrc.DSM_IPCAP3_250_FF | Cyrc.DSM_FCAP3_1400_FF; // (New)


        public static uint[] CapOffset_16_20 = { 
                            0x00,                           // VSSA to VREF
                            0x00,                           // VSSA to 2*VREF
                            0x00,                           // VSSA to VDDA
                            0x00,                           // VSSA to 6*VREF
                            0x00,                           // VNEG +/- VREF
                            0x00,                           // VNEG +/- 2*VREF
                            0x00,                           // VNEG +/- 6*VREF
                            0x00,                           // VNEG +/- VREF/2
                            0x00,                           // VNEG +/- VREF/4
                            DSM_IPCAP1OFFSET,               // Add 4800 fF to ipcap VNEG +/- VREF/8
                            DSM_IPCAP1OFFSET                // Add 4800 fF to ipcap VNEG +/- VREF/16
                            };


        public static uint[] SumCap3Fb_8_15 = {
                            (DSM_SUMCAP3_50_FF  | DSM_SUMCAPFB_100_FF),   // VSSA to VREF (New)
                            (DSM_SUMCAP3_50_FF  | DSM_SUMCAPFB_100_FF),   // VSSA to 2*VREF (New)
                            (DSM_SUMCAP3_200_FF | DSM_SUMCAPFB_400_FF),   // VSSA to VDDA
                            (DSM_SUMCAP3_50_FF  | DSM_SUMCAPFB_100_FF),   // VSSA to 6*VREF
                            (DSM_SUMCAP3_50_FF  | DSM_SUMCAPFB_100_FF),   // VNEG +/- VREF (New)
                            (DSM_SUMCAP3_100_FF | DSM_SUMCAPFB_200_FF),   // VNEG +/- 2*VREF (New)
                            (DSM_SUMCAP3_50_FF  | DSM_SUMCAPFB_100_FF),   // VNEG +/- 6*VREF
                            (DSM_SUMCAP3_100_FF | DSM_SUMCAPFB_200_FF),   // VNEG +/- VREF/2 (New)
                            (DSM_SUMCAP3_100_FF | DSM_SUMCAPFB_150_FF),   // VNEG +/- VREF/4 (New)
                            (DSM_SUMCAP3_200_FF | DSM_SUMCAPFB_200_FF),   // VNEG +/- VREF/8
                            (DSM_SUMCAP3_200_FF | DSM_SUMCAPFB_150_FF)    // VNEG +/- VREF/16 (New)
                            };

        public static uint[] SumCap3Fb_16_20 = {
                            (DSM_SUMCAP3_250_FF | DSM_SUMCAPFB_500_FF),   // VSSA to VREF
                            (DSM_SUMCAP3_250_FF | DSM_SUMCAPFB_500_FF),   // VSSA to 2*VREF
                            (DSM_SUMCAP3_200_FF | DSM_SUMCAPFB_400_FF),   // VSSA to VDDA
                            (DSM_SUMCAP3_250_FF | DSM_SUMCAPFB_500_FF),   // VSSA to 6*VREF (New)
                            (DSM_SUMCAP3_250_FF | DSM_SUMCAPFB_500_FF),   // VNEG +/- VREF
                            (DSM_SUMCAP3_200_FF | DSM_SUMCAPFB_400_FF),   // VNEG +/- 2*VREF
                            (DSM_SUMCAP3_250_FF | DSM_SUMCAPFB_500_FF),   // VNEG +/- 6*VREF (New)
                            (DSM_SUMCAP3_200_FF | DSM_SUMCAPFB_300_FF),   // VNEG +/- VREF/2 (New)
                            (DSM_SUMCAP3_200_FF | DSM_SUMCAPFB_300_FF),   // VNEG +/- VREF/4 (New)
                            (DSM_SUMCAP3_200_FF | DSM_SUMCAPFB_200_FF),   // VNEG +/- VREF/8
                            (DSM_SUMCAP3_200_FF | DSM_SUMCAPFB_100_FF)    // VNEG +/- VREF/16
                            };


        public static uint[] SumCap12_8_15 = {
                            (DSM_SUMCAP1_50_FF  | DSM_SUMCAP2_50_FF),    // VSSA to VREF (New)
                            (DSM_SUMCAP1_50_FF  | DSM_SUMCAP2_50_FF),    // VSSA to 2*VREF (New)
                            (DSM_SUMCAP1_200_FF | DSM_SUMCAP2_200_FF),   // VSSA to VDDA
                            (DSM_SUMCAP1_50_FF  | DSM_SUMCAP2_50_FF),    // VSSA to 6*VREF
                            (DSM_SUMCAP1_50_FF  | DSM_SUMCAP2_50_FF),    // VNEG +/- VREF (New)
                            (DSM_SUMCAP1_100_FF | DSM_SUMCAP2_100_FF),   // VNEG +/- 2*VREF (New)
                            (DSM_SUMCAP1_50_FF  | DSM_SUMCAP2_50_FF),    // VNEG +/- 6*VREF
                            (DSM_SUMCAP1_100_FF | DSM_SUMCAP2_100_FF),   // VNEG +/- VREF/2 (New)
                            (DSM_SUMCAP1_100_FF | DSM_SUMCAP2_100_FF),   // VNEG +/- VREF/4 (New)
                            (DSM_SUMCAP1_200_FF | DSM_SUMCAP2_200_FF),   // VNEG +/- VREF/8
                            (DSM_SUMCAP1_200_FF | DSM_SUMCAP2_200_FF)    // VNEG +/- VREF/16
                            };

        public static uint[] SumCap12_16_20 = {
                            (DSM_SUMCAP1_250_FF | DSM_SUMCAP2_250_FF),   // VSSA to VREF
                            (DSM_SUMCAP1_250_FF | DSM_SUMCAP2_250_FF),   // VSSA to 2*VREF
                            (DSM_SUMCAP1_200_FF | DSM_SUMCAP2_200_FF),   // VSSA to VDDA
                            (DSM_SUMCAP1_250_FF | DSM_SUMCAP2_250_FF),   // VSSA to 6*VREF (New)
                            (DSM_SUMCAP1_250_FF | DSM_SUMCAP2_250_FF),   // VNEG +/- VREF
                            (DSM_SUMCAP1_200_FF | DSM_SUMCAP2_200_FF),   // VNEG +/- 2*VREF
                            (DSM_SUMCAP1_250_FF | DSM_SUMCAP2_250_FF),   // VNEG +/- 6*VREF (New)
                            (DSM_SUMCAP1_200_FF | DSM_SUMCAP2_200_FF),   // VNEG +/- VREF/2
                            (DSM_SUMCAP1_200_FF | DSM_SUMCAP2_200_FF),   // VNEG +/- VREF/4
                            (DSM_SUMCAP1_200_FF | DSM_SUMCAP2_200_FF),   // VNEG +/- VREF/8
                            (DSM_SUMCAP1_200_FF | DSM_SUMCAP2_200_FF)    // VNEG +/- VREF/16
                            };


        /// <summary>
        /// ADC_Power Constants
        /// </summary>
        public const uint ADC_LOWPOWER = 0;
        public const uint ADC_MEDPOWER = 1;
        public const uint ADC_HIGHPOWER = 2;


        /// <summary>
        /// ADC_Reference Constants
        /// </summary>
        public const uint ADC_INT_REF_NOT_BYPASSED = 0;
        public const uint ADC_INT_REF_BYPASSED_ON_P03 = 1;
        public const uint ADC_INT_REF_BYPASSED_ON_P32 = 2;
        public const uint ADC_EXT_REF_ON_P03 = 3;
        public const uint ADC_EXT_REF_ON_P32 = 4;
        public const uint ADC_INT_REF_VDDA_4 = 5;
        public const uint ADC_INT_REF_VDDA_4_BYPASSED_ON_P03 = 6;
        public const uint ADC_INT_REF_VDDA_4_BYPASSED_ON_P32 = 7;
        public const uint ADC_INT_REF_VDDA_3 = 8;
        public const uint ADC_INT_REF_VDDA_3_BYPASSED_ON_P03 = 9;
        public const uint ADC_INT_REF_VDDA_3_BYPASSED_ON_P32 = 0xA;

        /// <summary>
        /// Input_Buffer_Gain Constants
        /// </summary>
        public const uint ADC_IBG_1X = 0;
        public const uint ADC_IBG_2X = 1;
        public const uint ADC_IBG_4X = 2;
        public const uint ADC_IBG_8X = 3;

        /// <summary>
        /// Constants for SetInputRange() bufmode parameter
        /// </summary>
        public const uint BUF_DIFF_MODE = 0x00;  // Differential mode 
        public const uint BUF_BYPASS_POS = 0x04;  // Bypass and power down positive channel 
        public const uint BUF_BYPASS_NEG = 0x08;  // Bypass and power down negative channel 
        public const uint BUF_RAIL_TO_RAIL = 0x10;  // Enables Rail-to-rail mode 
        public const uint BUF_FILTER_EN = 0x20;  // Output filter enable 
        public const uint BUF_LOW_PWR = 0x40;  // Enable  Low power mode 

        /// <summary>
        /// Constants for Buffermode parameter
        /// </summary>
        public const uint BUF_MODE_BYPASS_BUFFER = 0x00;  // Bypass buffer mode 
        public const uint BUF_MODE_RAIL_TO_RAIL = 0x01;  // Rail to Rail buffer mode 
        public const uint BUF_MODE_LEVEL_SHIFT = 0x02;  // Level Shift buffer mode 

        //      Register Constants        

        /// <summary>
        /// DSM.CR0 Control Register 0 definitions 
        /// </summary>
        /// 
        // Bit Field  DSM_NONOV                   
        public const uint DSM_NONOV_MASK = 0x0C;
        public const uint DSM_NONOV_LOW = 0x00;
        public const uint DSM_NONOV_MED = 0x04;
        public const uint DSM_NONOV_HIGH = 0x08;
        public const uint DSM_NONOV_VHIGH = 0x0C;

        // Bit Field  DSM_QLEV                    
        public const uint DSM_QLEV_MASK = 0x03;
        public const uint DSM_QLEV_2 = 0x00;
        public const uint DSM_QLEV_3 = 0x01;
        public const uint DSM_QLEV_9 = 0x02;
        public const uint DSM_QLEV_9x = 0x03;


        /// <summary>
        /// DSM.CR1 Control Register 1 definitions  
        /// </summary>
        public const uint DSM_ODET_TH_MASK = 0x1F;
        public const uint DSM_ODEN = 0x20;
        public const uint DSM_DPMODE = 0x40;

        /// <summary>
        /// DSM.CR2 Control Register 2 definitions  
        /// </summary>

        // Bit Field  DSM_FCHOP                    
        public const uint DSM_FCHOP_MASK = 0x07;
        public const uint DSM_FCHOP_DIV2 = 0x00;
        public const uint DSM_FCHOP_DIV4 = 0x01;
        public const uint DSM_FCHOP_DIV8 = 0x02;
        public const uint DSM_FCHOP_DIV16 = 0x03;
        public const uint DSM_FCHOP_DIV32 = 0x04;
        public const uint DSM_FCHOP_DIV64 = 0x05;
        public const uint DSM_FCHOP_DIV128 = 0x06;
        public const uint DSM_FCHOP_DIV256 = 0x07;

        // Bit Field  DSM_MOD_CHOP_EN                 
        public const uint DSM_MOD_CHOP_EN = 0x08;

        // Bit Field  DSM_MX_RESET                    
        public const uint DSM_MX_RESET = 0x80;

        // Bit Field  DSM_RESET1_EN                   
        public const uint DSM_RESET1_EN = 0x10;

        // Bit Field  DSM_RESET2_EN                   
        public const uint DSM_RESET2_EN = 0x20;

        // Bit Field  DSM_RESET3_EN                   
        public const uint DSM_RESET3_EN = 0x40;

        /// <summary>
        /// DSM.CR3 Control Register 3 definitions
        /// </summary>

        // Bit Field  DSM_SELECT_MOD_BIT           
        public const uint DSM_MODBITIN_MASK = 0x0F;
        public const uint DSM_MODBITIN_LUT0 = 0x00;
        public const uint DSM_MODBITIN_LUT1 = 0x01;
        public const uint DSM_MODBITIN_LUT2 = 0x02;
        public const uint DSM_MODBITIN_LUT3 = 0x03;
        public const uint DSM_MODBITIN_LUT4 = 0x04;
        public const uint DSM_MODBITIN_LUT5 = 0x05;
        public const uint DSM_MODBITIN_LUT6 = 0x06;
        public const uint DSM_MODBITIN_LUT7 = 0x07;
        public const uint DSM_MODBITIN_UDB = 0x08;

        // Bit Field  DSM_MODBIT_EN                  
        public const uint DSM_MODBIT_EN = 0x10;

        // Bit Field  DSM_MX_DOUT                    
        public const uint DSM_MX_DOUT_8BIT = 0x00;
        public const uint DSM_MX_DOUT_2SCOMP = 0x20;

        // Bit Field  DSM_MODBIT  TBD                
        public const uint DSM_MODBIT = 0x40;

        // Bit Field  DSM_SIGN                       
        public const uint DSM_SIGN_NINV = 0x00;
        public const uint DSM_SIGN_INV = 0x80;


        /// <summary>
        /// DSM.CR4 Control Register 4 definitions 
        /// </summary>

        // Bit Field  DSM_SELECT_FCAP_EN             
        public const uint DSM_FCAP1_EN = 0x80;
        public const uint DSM_FCAP1_DIS = 0x00;

        // Bit Field  DSM_SELECT_FCAP1              
        public const uint DSM_FCAP1_MASK = 0x7F;
        public const uint DSM_FCAP1_MIN = 0x00;
        public const uint DSM_FCAP1_MAX = 0x7F;
        public const uint DSM_FCAP1_100FF = 0x01;
        public const uint DSM_FCAP1_200FF = 0x02;
        public const uint DSM_FCAP1_400FF = 0x04;
        public const uint DSM_FCAP1_800FF = 0x08;
        public const uint DSM_FCAP1_1600FF = 0x10;
        public const uint DSM_FCAP1_3200FF = 0x20;
        public const uint DSM_FCAP1_6400FF = 0x40;

        /// <summary>
        /// DSM.CR5 Control Register 5 definitions  
        /// </summary>

        // Bit Field  DSM_SELECT_IPCAP_EN             
        public const uint DSM_IPCAP1_EN = 0x80;
        public const uint DSM_IPCAP1_DIS = 0x00;
        public const uint DSM_IPCAP1_96FFpath = 0x80;

        // Bit Field  DSM_SELECT_IPCAP1              
        public const uint DSM_IPCAP1_MASK = 0x7F;
        public const uint DSM_IPCAP1_MIN = 0x00;
        public const uint DSM_IPCAP1_MAX = 0x7F;
        public const uint DSM_IPCAP1_96FF = 0x01;
        public const uint DSM_IPCAP1_192FF = 0x02;
        public const uint DSM_IPCAP1_400FF = 0x04;
        public const uint DSM_IPCAP1_800FF = 0x08;
        public const uint DSM_IPCAP1_1600FF = 0x10;
        public const uint DSM_IPCAP1_3200FF = 0x20;
        public const uint DSM_IPCAP1_6400FF = 0x40;
        public const uint DSM_IPCAP1_12700FF = 0x7F;


        /// <summary>
        /// DSM.CR6 Control Register 6 definitions  
        /// </summary>

        // Bit Field  DSM_SELECT_DACCAP_EN             
        public const uint DSM_DACCAP_EN = 0x40;
        public const uint DSM_DACCAP_DIS = 0x00;

        // Bit Field  DSM_SELECT_DACCAP              
        public const uint DSM_DACCAP_MASK = 0x3F;
        public const uint DSM_DACCAP_MIN = 0x00;
        public const uint DSM_DACCAP_MAX = 0x3F;
        public const uint DSM_DACCAP_96FF = 0x01;
        public const uint DSM_DACCAP_192FF = 0x02;
        public const uint DSM_DACCAP_400FF = 0x04;
        public const uint DSM_DACCAP_800FF = 0x08;
        public const uint DSM_DACCAP_1600FF = 0x10;
        public const uint DSM_DACCAP_3200FF = 0x20;


        /// <summary>
        /// DSM.CR7 Control Register 7 definitions  
        /// </summary>

        // Bit Field  DSM_SELECT_RESCAP_EN             
        public const uint DSM_RESCAP_EN = 0x08;
        public const uint DSM_RESCAP_DIS = 0x00;

        // Bit Field  DSM_SELECT_RESCAP              
        public const uint DSM_RESCAP_MASK = 0x07;
        public const uint DSM_RESCAP_MIN = 0x00;
        public const uint DSM_RESCAP_MAX = 0x07;
        public const uint DSM_RESCAP_12FF = 0x00;
        public const uint DSM_RESCAP_24FF = 0x01;
        public const uint DSM_RESCAP_36FF = 0x02;
        public const uint DSM_RESCAP_48FF = 0x03;
        public const uint DSM_RESCAP_60FF = 0x04;
        public const uint DSM_RESCAP_72FF = 0x05;
        public const uint DSM_RESCAP_84FF = 0x06;
        public const uint DSM_RESCAP_96FF = 0x07;

        public const uint DSM_FCAP2_DIS = 0x00;
        public const uint DSM_FCAP2_EN = 0x80;

        public const uint DSM_FCAP3_DIS = 0x00;
        public const uint DSM_FCAP3_EN = 0x40;

        public const uint DSM_IPCAP1OFFSET = 0x20;
        public const uint DSM_FPCAP1OFFSET = 0x10;


        /// <summary>
        /// DSM.CR8 Control Register 8 definitions  
        /// </summary>

        public const uint DSM_IPCAP2_EN = 0x80;

        public const uint DSM_IPCAP2_MASK = 0x70;
        public const uint DSM_IPCAP2_0_FF = 0x00;
        public const uint DSM_IPCAP2_50_FF = 0x10;
        public const uint DSM_IPCAP2_100_FF = 0x20;
        public const uint DSM_IPCAP2_150_FF = 0x30;
        public const uint DSM_IPCAP2_200_FF = 0x40;
        public const uint DSM_IPCAP2_250_FF = 0x50;
        public const uint DSM_IPCAP2_300_FF = 0x60;
        public const uint DSM_IPCAP2_350_FF = 0x70;

        public const uint DSM_FCAP2_MASK = 0x0F;
        public const uint DSM_FCAP2_0_FF = 0x00;
        public const uint DSM_FCAP2_50_FF = 0x01;
        public const uint DSM_FCAP2_100_FF = 0x02;
        public const uint DSM_FCAP2_150_FF = 0x03;
        public const uint DSM_FCAP2_200_FF = 0x04;
        public const uint DSM_FCAP2_250_FF = 0x05;
        public const uint DSM_FCAP2_300_FF = 0x06;
        public const uint DSM_FCAP2_350_FF = 0x07;
        public const uint DSM_FCAP2_400_FF = 0x08;
        public const uint DSM_FCAP2_450_FF = 0x09;
        public const uint DSM_FCAP2_500_FF = 0x0A;
        public const uint DSM_FCAP2_550_FF = 0x0B;
        public const uint DSM_FCAP2_600_FF = 0x0C;
        public const uint DSM_FCAP2_650_FF = 0x0D;
        public const uint DSM_FCAP2_700_FF = 0x0E;
        public const uint DSM_FCAP2_750_FF = 0x0F;

        /// <summary>
        /// DSM.CR9 Control Register 9 definitions  
        /// </summary>

        public const uint DSM_IPCAP3_EN = 0x80;

        public const uint DSM_IPCAP3_MASK = 0x70;
        public const uint DSM_IPCAP3_0_FF = 0x00;
        public const uint DSM_IPCAP3_50_FF = 0x10;
        public const uint DSM_IPCAP3_100_FF = 0x20;
        public const uint DSM_IPCAP3_150_FF = 0x30;
        public const uint DSM_IPCAP3_200_FF = 0x40;
        public const uint DSM_IPCAP3_250_FF = 0x50;
        public const uint DSM_IPCAP3_300_FF = 0x60;
        public const uint DSM_IPCAP3_350_FF = 0x70;

        public const uint DSM_FCAP3_MASK = 0x0F;
        public const uint DSM_FCAP3_0_FF = 0x00;
        public const uint DSM_FCAP3_100_FF = 0x01;
        public const uint DSM_FCAP3_200_FF = 0x02;
        public const uint DSM_FCAP3_300_FF = 0x03;
        public const uint DSM_FCAP3_400_FF = 0x04;
        public const uint DSM_FCAP3_500_FF = 0x05;
        public const uint DSM_FCAP3_600_FF = 0x06;
        public const uint DSM_FCAP3_700_FF = 0x07;
        public const uint DSM_FCAP3_800_FF = 0x08;
        public const uint DSM_FCAP3_900_FF = 0x09;
        public const uint DSM_FCAP3_1000_FF = 0x0A;
        public const uint DSM_FCAP3_1100_FF = 0x0B;
        public const uint DSM_FCAP3_1200_FF = 0x0C;
        public const uint DSM_FCAP3_1300_FF = 0x0D;
        public const uint DSM_FCAP3_1400_FF = 0x0E;
        public const uint DSM_FCAP3_1500_FF = 0x0F;

        /// <summary>
        /// DSM.CR10 Control Register 10 definitions  
        /// </summary>

        public const uint DSM_SUMCAP1_EN = 0x80;
        public const uint DSM_SUMCAP2_EN = 0x08;

        public const uint DSM_SUMCAP1_MASK = 0x70;
        public const uint DSM_SUMCAP1_0_FF = 0x00;
        public const uint DSM_SUMCAP1_50_FF = 0x10;
        public const uint DSM_SUMCAP1_100_FF = 0x20;
        public const uint DSM_SUMCAP1_150_FF = 0x30;
        public const uint DSM_SUMCAP1_200_FF = 0x40;
        public const uint DSM_SUMCAP1_250_FF = 0x50;
        public const uint DSM_SUMCAP1_300_FF = 0x60;
        public const uint DSM_SUMCAP1_350_FF = 0x70;

        public const uint DSM_SUMCAP2_MASK = 0x07;
        public const uint DSM_SUMCAP2_0_FF = 0x00;
        public const uint DSM_SUMCAP2_50_FF = 0x01;
        public const uint DSM_SUMCAP2_100_FF = 0x02;
        public const uint DSM_SUMCAP2_150_FF = 0x03;
        public const uint DSM_SUMCAP2_200_FF = 0x04;
        public const uint DSM_SUMCAP2_250_FF = 0x05;
        public const uint DSM_SUMCAP2_300_FF = 0x06;
        public const uint DSM_SUMCAP2_350_FF = 0x07;

        /// <summary>
        /// DSM.CR11 Control Register 11 definitions  
        /// </summary>

        public const uint DSM_SUMCAP3_EN = 0x08;

        public const uint DSM_SUMCAP3_MASK = 0x70;
        public const uint DSM_SUMCAP3_0_FF = 0x00;
        public const uint DSM_SUMCAP3_50_FF = 0x10;
        public const uint DSM_SUMCAP3_100_FF = 0x20;
        public const uint DSM_SUMCAP3_150_FF = 0x30;
        public const uint DSM_SUMCAP3_200_FF = 0x40;
        public const uint DSM_SUMCAP3_250_FF = 0x50;
        public const uint DSM_SUMCAP3_300_FF = 0x60;
        public const uint DSM_SUMCAP3_350_FF = 0x70;

        public const uint DSM_SUMCAPFB_MASK = 0x07;
        public const uint DSM_SUMCAPFB_0_FF = 0x00;
        public const uint DSM_SUMCAPFB_50_FF = 0x01;
        public const uint DSM_SUMCAPFB_100_FF = 0x02;
        public const uint DSM_SUMCAPFB_150_FF = 0x03;
        public const uint DSM_SUMCAPFB_200_FF = 0x04;
        public const uint DSM_SUMCAPFB_250_FF = 0x05;
        public const uint DSM_SUMCAPFB_300_FF = 0x06;
        public const uint DSM_SUMCAPFB_350_FF = 0x07;
        public const uint DSM_SUMCAPFB_400_FF = 0x08;
        public const uint DSM_SUMCAPFB_450_FF = 0x09;
        public const uint DSM_SUMCAPFB_500_FF = 0x0A;
        public const uint DSM_SUMCAPFB_550_FF = 0x0B;
        public const uint DSM_SUMCAPFB_600_FF = 0x0C;
        public const uint DSM_SUMCAPFB_650_FF = 0x0D;
        public const uint DSM_SUMCAPFB_700_FF = 0x0E;
        public const uint DSM_SUMCAPFB_750_FF = 0x0F;

        /// <summary>
        /// DSM.CR12 Control Register 12 definitions  
        /// </summary>

        public const uint DSM_SUMCAPFB_EN = 0x40;
        public const uint DSM_SUMCAPIN_EN = 0x20;

        public const uint DSM_SUMCAPIN_MASK = 0x1F;
        public const uint DSM_SUMCAPIN_0_FF = 0x00;
        public const uint DSM_SUMCAPIN_50_FF = 0x01;
        public const uint DSM_SUMCAPIN_100_FF = 0x02;
        public const uint DSM_SUMCAPIN_150_FF = 0x03;
        public const uint DSM_SUMCAPIN_200_FF = 0x04;
        public const uint DSM_SUMCAPIN_250_FF = 0x05;
        public const uint DSM_SUMCAPIN_300_FF = 0x06;
        public const uint DSM_SUMCAPIN_350_FF = 0x07;
        public const uint DSM_SUMCAPIN_400_FF = 0x08;
        public const uint DSM_SUMCAPIN_450_FF = 0x09;
        public const uint DSM_SUMCAPIN_500_FF = 0x0A;
        public const uint DSM_SUMCAPIN_550_FF = 0x0B;
        public const uint DSM_SUMCAPIN_600_FF = 0x0C;
        public const uint DSM_SUMCAPIN_650_FF = 0x0D;
        public const uint DSM_SUMCAPIN_700_FF = 0x0E;
        public const uint DSM_SUMCAPIN_750_FF = 0x0F;
        public const uint DSM_SUMCAPIN_800_FF = 0x10;
        public const uint DSM_SUMCAPIN_850_FF = 0x11;
        public const uint DSM_SUMCAPIN_900_FF = 0x12;
        public const uint DSM_SUMCAPIN_950_FF = 0x13;
        public const uint DSM_SUMCAPIN_1000_FF = 0x14;
        public const uint DSM_SUMCAPIN_1050_FF = 0x15;
        public const uint DSM_SUMCAPIN_1100_FF = 0x16;
        public const uint DSM_SUMCAPIN_1150_FF = 0x17;
        public const uint DSM_SUMCAPIN_1200_FF = 0x18;
        public const uint DSM_SUMCAPIN_1250_FF = 0x19;
        public const uint DSM_SUMCAPIN_1300_FF = 0x1A;
        public const uint DSM_SUMCAPIN_1350_FF = 0x1B;
        public const uint DSM_SUMCAPIN_1400_FF = 0x1C;
        public const uint DSM_SUMCAPIN_1450_FF = 0x1D;
        public const uint DSM_SUMCAPIN_1500_FF = 0x1E;
        public const uint DSM_SUMCAPIN_1550_FF = 0x15;


        /// <summary>
        /// DSM.CR13 Control Register 13 definitions 
        /// </summary>

        public const uint DSM_CR13_RSVD = 0xFF;

        /// <summary>
        /// DSM.CR14 Control Register 14 definitions 
        /// </summary>

        // Bit Field  DSM_POWER1                     
        public const uint DSM_POWER1_MASK = 0x07;

        public const uint DSM_POWER1_0 = 0x00;
        public const uint DSM_POWER1_1 = 0x01;
        public const uint DSM_POWER1_2 = 0x02;
        public const uint DSM_POWER1_3 = 0x03;
        public const uint DSM_POWER1_4 = 0x04;
        public const uint DSM_POWER1_5 = 0x05;
        public const uint DSM_POWER1_6 = 0x06;
        public const uint DSM_POWER1_7 = 0x07;

        public const uint DSM_POWER1_44UA = 0x00;
        public const uint DSM_POWER1_123UA = 0x01;
        public const uint DSM_POWER1_492UA = 0x02;
        public const uint DSM_POWER1_750UA = 0x03;
        public const uint DSM_POWER1_1MA = 0x04;

        // Bit Field  DSM_OPAMP1_BW                  
        public const uint DSM_OPAMP1_BW_MASK = 0xF0;
        public const uint DSM_OPAMP1_BW_0 = 0x00;
        public const uint DSM_OPAMP1_BW_1 = 0x10;
        public const uint DSM_OPAMP1_BW_2 = 0x20;
        public const uint DSM_OPAMP1_BW_3 = 0x30;
        public const uint DSM_OPAMP1_BW_4 = 0x40;
        public const uint DSM_OPAMP1_BW_5 = 0x50;
        public const uint DSM_OPAMP1_BW_6 = 0x60;
        public const uint DSM_OPAMP1_BW_7 = 0x70;
        public const uint DSM_OPAMP1_BW_8 = 0x80;
        public const uint DSM_OPAMP1_BW_9 = 0x90;
        public const uint DSM_OPAMP1_BW_A = 0xA0;
        public const uint DSM_OPAMP1_BW_B = 0xB0;
        public const uint DSM_OPAMP1_BW_C = 0xC0;
        public const uint DSM_OPAMP1_BW_D = 0xD0;
        public const uint DSM_OPAMP1_BW_E = 0xE0;
        public const uint DSM_OPAMP1_BW_F = 0xF0;

        /// <summary>
        /// DSM.CR15 Control Register 15 definitions  
        /// </summary>

        // Bit Field  DSM_POWER2_3                   
        public const uint DSM_POWER2_3_MASK = 0x07;

        public const uint DSM_POWER2_3_LOW = 0x00;
        public const uint DSM_POWER2_3_MED = 0x01;
        public const uint DSM_POWER2_3_HIGH = 0x02;
        public const uint DSM_POWER2_3_IP5X = 0x03;
        public const uint DSM_POWER2_3_2X = 0x04;
        public const uint DSM_POWER2_3_HIGH_5 = 0x05;
        public const uint DSM_POWER2_3_HIGH_6 = 0x06;
        public const uint DSM_POWER2_3_HIGH_7 = 0x07;

        // Bit Field  DSM_POWER_COMP                 
        public const uint DSM_POWER_COMP_MASK = 0x30;

        public const uint DSM_POWER_VERYLOW = 0x00;
        public const uint DSM_POWER_NORMAL = 0x10;
        public const uint DSM_POWER_6MHZ = 0x20;
        public const uint DSM_POWER_12MHZ = 0x30;

        /// <summary>
        /// DSM.CR16 Control Register 16 definitions 
        /// </summary>

        // Bit Field  DSM_POWER_SUM                  
        public const uint DSM_POWER_SUM_MASK = 0x70;

        public const uint DSM_POWER_SUM_LOW = 0x00;
        public const uint DSM_POWER_SUM_MED = 0x10;
        public const uint DSM_POWER_SUM_HIGH = 0x20;
        public const uint DSM_POWER_SUM_IP5X = 0x30;
        public const uint DSM_POWER_SUM_2X = 0x40;
        public const uint DSM_POWER_SUM_HIGH_5 = 0x50;
        public const uint DSM_POWER_SUM_HIGH_6 = 0x60;
        public const uint DSM_POWER_SUM_HIGH_7 = 0x70;

        public const uint DSM_CP_ENABLE = 0x08;
        public const uint DSM_CP_PWRCTL_MASK = 0x07;
        public const uint DSM_CP_PWRCTL_DEFAULT = 0x0A;
        public const uint DSM_CP_PWRCTL_2X = 0x09;
        public const uint DSM_CP_PWRCTL_TURBO = 0x08;
        public const uint DSM_CP_PWRCTL_HIGH = 0x0A;
        public const uint DSM_CP_PWRCTL_MEDIUM = 0x0B;

        /// <summary>
        /// DSM.CR17 Control Register 17 definitions  
        /// </summary>

        // Bit Field  DSM_EN_BUF                     
        public const uint DSM_EN_BUF_VREF = 0x01;
        public const uint DSM_EN_BUF_VCM = 0x02;

        public const uint DSM_PWR_CTRL_VREF_MASK = 0x0C;
        public const uint DSM_PWR_CTRL_VREF_0 = 0x00;
        public const uint DSM_PWR_CTRL_VREF_1 = 0x04;
        public const uint DSM_PWR_CTRL_VREF_2 = 0x08;
        public const uint DSM_PWR_CTRL_VREF_3 = 0x0C;

        public const uint DSM_PWR_CTRL_VCM_MASK = 0x30;
        public const uint DSM_PWR_CTRL_VCM_0 = 0x00;
        public const uint DSM_PWR_CTRL_VCM_1 = 0x10;
        public const uint DSM_PWR_CTRL_VCM_2 = 0x20;
        public const uint DSM_PWR_CTRL_VCM_3 = 0x30;

        public const uint DSM_PWR_CTRL_VREF_INN_MASK = 0xC0;
        public const uint DSM_PWR_CTRL_VREF_INN_0 = 0x00;
        public const uint DSM_PWR_CTRL_VREF_INN_1 = 0x40;
        public const uint DSM_PWR_CTRL_VREF_INN_2 = 0x80;
        public const uint DSM_PWR_CTRL_VREF_INN_3 = 0xC0;

        /// <summary>
        /// DSM.REF0 Reference Register 0 definitions  
        /// </summary>

        public const uint DSM_REFMUX_MASK = 0x07;
        public const uint DSM_REFMUX_NONE = 0x00;

        public const uint DSM_REFMUX_VDAC0_ES3 = 0x03;  // For PSoC3 and PSoC5LP or later
       
        public const uint DSM_REFMUX_VDA_4 = 0x02;
        public const uint DSM_REFMUX_VDA_3 = 0x03;  // For PSoC3 and PSoC5LP or later        
        public const uint DSM_REFMUX_1_024V = 0x04;
        public const uint DSM_REFMUX_1_20V = 0x05;

        public const uint DSM_EN_BUF_VREF_INN = 0x08;
        public const uint DSM_VREF_RES_DIV_EN = 0x10;
        public const uint DSM_VCM_RES_DIV_EN = 0x20;
        public const uint DSM_VCMSEL_MASK = 0xC0;
        public const uint DSM_VCMSEL_NOSEL = 0x00;
        public const uint DSM_VCMSEL_0_8V = 0x40;
        public const uint DSM_VCMSEL_0_7V = 0x80;
        public const uint DSM_VCMSEL_VPWRA_2 = 0xC0;

        /// <summary>
        /// DSM.REF1 Reference Register 1 definitions 
        /// </summary>
        public const uint DSM_REF1_MASK = 0xFF;

        /// <summary>
        /// DSM.REF2 Reference Register 2 definitions  
        /// </summary>

        public const uint DSM_REF2_MASK = 0xFF;
        public const uint DSM_REF2_NO_SW = 0x00;
        public const uint DSM_REF2_S0_EN = 0x01;
        public const uint DSM_REF2_S1_EN = 0x02;
        public const uint DSM_REF2_S2_EN = 0x04;
        public const uint DSM_REF2_S3_EN = 0x08;
        public const uint DSM_REF2_S4_EN = 0x10;
        public const uint DSM_REF2_S5_EN = 0x20;
        public const uint DSM_REF2_S6_EN = 0x40;
        public const uint DSM_REF2_S7_EN = 0x80;

        /// <summary>
        /// DSM.REF3 Reference Register 3 definitions  
        /// </summary>

        public const uint DSM_REF3_MASK = 0xFF;
        public const uint DSM_REF3_NO_SW = 0x00;
        public const uint DSM_REF3_S8_EN = 0x01;
        public const uint DSM_REF3_S9_EN = 0x02;
        public const uint DSM_REF3_S10_EN = 0x04;
        public const uint DSM_REF3_S11_EN = 0x08;
        public const uint DSM_REF3_S12_EN = 0x10;
        public const uint DSM_REF3_S13_EN = 0x20;


        /// <summary>
        /// DSM.DEM0 Dynamic Element Matching Register 0 
        /// </summary>

        public const uint DSM_EN_SCRAMBLER0 = 0x01;
        public const uint DSM_EN_SCRAMBLER1 = 0x02;
        public const uint DSM_EN_DEM = 0x04;
        public const uint DSM_ADC_TEST_EN = 0x08;
        public const uint DSM_DEMTEST_SRC = 0x10;

        /// <summary>
        /// DSM.DEM1 Dynamic Element Matching Register 1  
        /// </summary>

        public const uint DSM_DEM1_MASK = 0xFF;


        /// <summary>
        /// DSM.BUF0 Buffer Register 0                
        /// </summary>

        public const uint DSM_ENABLE_P = 0x01;
        public const uint DSM_BYPASS_P = 0x02;
        public const uint DSM_RAIL_RAIL_EN = 0x04;

        public const uint DSM_BUFSEL = 0x08;
        public const uint DSM_BUFSEL_A = 0x00;
        public const uint DSM_BUFSEL_B = 0x08;


        /// <summary>
        /// DSM.BUF1 Buffer Register 1          
        /// </summary>

        public const uint DSM_ENABLE_N = 0x01;
        public const uint DSM_BYPASS_N = 0x02;
        public const uint DSM_GAIN_MASK = 0x0C;
        public const uint DSM_GAIN_1X = 0x00;
        public const uint DSM_GAIN_2X = 0x04;
        public const uint DSM_GAIN_4X = 0x08;
        public const uint DSM_GAIN_8X = 0x0C;

        /// <summary>
        /// DSM.BUF2 Buffer Register 2       
        /// </summary>

        public const uint DSM_LOWPOWER_EN = 0x01;
        public const uint DSM_ADD_EXTRA_RC = 0x02;

        /// <summary>
        /// DSM.BUF3 Buffer Register 3       
        /// </summary>

        public const uint DSM_BUF_CHOP_EN = 0x08;

        public const uint DSM_BUF_FCHOP_MASK = 0x07;
        public const uint DSM_BUF_FCHOP_FS2 = 0x00;
        public const uint DSM_BUF_FCHOP_FS4 = 0x01;
        public const uint DSM_BUF_FCHOP_FS8 = 0x02;
        public const uint DSM_BUF_FCHOP_FS16 = 0x03;
        public const uint DSM_BUF_FCHOP_FS32 = 0x04;
        public const uint DSM_BUF_FCHOP_FS64 = 0x05;
        public const uint DSM_BUF_FCHOP_FS128 = 0x06;
        public const uint DSM_BUF_FCHOP_FS256 = 0x07;


        /// <summary>
        /// DSM.MISC Delta Sigma Misc Register     
        /// </summary>

        public const uint DSM_SEL_ICLK_CP = 0x01;
        public const uint DSM_SEL_ECLK_CP = 0x00;

        /// <summary>
        /// DSM.REF1 Delta Sigma Reference register           
        /// </summary>

        public const uint DSM_DAC_GND_SEL_EXT = 0x01;
        public const uint DSM_DAC_GND_SEL_INT = 0x00;

        /// <summary>
        /// DSM.CLK Delta Sigma Clock selection Register 
        /// </summary>

        public const uint DSM_CLK_MX_CLK_MSK = 0x07;
        public const uint DSM_CLK_CLK_EN = 0x08;
        public const uint DSM_CLK_BYPASS_SYNC = 0x10;


        /// <summary>
        /// DSM.OUT0 Output Register 0 
        /// </summary>

        public const uint DSM_DOUT0 = 0xFF;


        /// <summary>
        /// DSM.OUT1 Output Register 1  
        /// </summary>

        public const uint DSM_DOUT2SCOMP_MASK = 0x0F;
        public const uint DSM_OVDFLAG = 0x10;
        public const uint DSM_OVDCAUSE = 0x20;


        /// <summary>
        /// DECIMATOR
        /// </summary>


        /// <summary>
        /// DEC.CR Control Register 0 
        /// </summary>

        public const uint DEC_SAT_EN = 0x80; // Enable post process offset correction  
        public const uint DEC_FIR_EN = 0x40; // Post process FIR enable   
        public const uint DEC_OCOR_EN = 0x20; // Offest correction enable  
        public const uint DEC_GCOR_EN = 0x10; // Enable gain correction feature  

        public const uint MODE_MASK = 0x0C; // Conversion Mode  
        public const uint MODE_SINGLE_SAMPLE = 0x00;
        public const uint MODE_FAST_FILTER = 0x04;
        public const uint MODE_CONTINUOUS = 0x08;
        public const uint MODE_FAST_FIR = 0x0C;

        public const uint DEC_XSTART_EN = 0x02; // Enables external start signal  
        public const uint DEC_START_CONV = 0x01; // A write to this bit starts a conversion  


        /// <summary>
        /// DEC.SR Status and Control Register 0   
        /// </summary>

        public const uint DEC_CORECLK_DISABLE = 0x20; // Controls gating of the Core clock  
        public const uint DEC_INTR_PULSE = 0x10; // Controls interrupt mode   
        public const uint DEC_OUT_ALIGN = 0x08; // Controls 8-bit shift of SAMP registers  
        public const uint DEC_INTR_CLEAR = 0x04; // A write to this bit clears bit0  
        public const uint DEC_INTR_MASK = 0x02; // Controls the generation of the conversion comp. INTR  
        public const uint DEC_CONV_DONE = 0x01; // Bit set if conversion has completed   

        /// <summary>
        /// DEC.SHIFT1 Decimator Input Shift Register 1  
        /// </summary>

        public const uint DEC_SHIFT1_MASK = 0x1F; // Input shift1 control  

        /// <summary>
        /// DEC.SHIFT2 Decimator Input Shift Register 2  
        /// </summary>

        public const uint DEC_SHIFT2_MASK = 0x0F; // Input shift2 control  

        /// <summary>
        /// DEC.DR2 Decimator Decimation Rate of FIR Filter Low Register  
        /// </summary>

        public const uint DEC_DR2_MASK = 0xFF;

        /// <summary>
        /// DEC.DR2H Decimator Decimation Rate of FIR Filter High Register  
        /// </summary>

        public const uint DEC_DR2H_MASK = 0x03;

        /// <summary>
        /// DEC.COHR Decimator Coherency Register    
        /// </summary>

        public const uint DEC_GCOR_KEY_MASK = 0x30;
        public const uint DEC_GCOR_KEY_OFF = 0x00;
        public const uint DEC_GCOR_KEY_LOW = 0x10;
        public const uint DEC_GCOR_KEY_MID = 0x20;
        public const uint DEC_GCOR_KEY_HIGH = 0x30;

        public const uint DEC_OCOR_KEY_MASK = 0x0C;
        public const uint DEC_OCOR_KEY_OFF = 0x00;
        public const uint DEC_OCOR_KEY_LOW = 0x04;
        public const uint DEC_OCOR_KEY_MID = 0x08;
        public const uint DEC_OCOR_KEY_HIGH = 0x0C;

        public const uint DEC_SAMP_KEY_MASK = 0x03;
        public const uint DEC_SAMP_KEY_OFF = 0x00;
        public const uint DEC_SAMP_KEY_LOW = 0x01;
        public const uint DEC_SAMP_KEY_MID = 0x02;
        public const uint DEC_SAMP_KEY_HIGH = 0x03;

        /// <summary>
        /// DSM.SW3 DSM Analog Routing Register 3  
        /// </summary>

        public const uint DSM_VN_AMX = 0x10;
        public const uint DSM_VN_VREF = 0x20;
        public const uint DSM_VN_VSSA = 0x40;
        public const uint DSM_VN_REF_MASK = 0x70;

        /// <summary>
        /// Decimator GVAL
        /// </summary>

        public const uint DEC_GVAL_MIN = 0x0B;
        public const uint DEC_GVAL_MAX = 0x0F;
    }

    
    public static class CyresSettings
    {
        //             Resolution              8   9  10  11  12  13  14  15  16  17  18  19   20   21

        public static uint[] dr1 =          { 15, 19, 22, 26, 31, 38, 45, 53, 63, 63, 63, 127, 127, 127 };
        public static uint[] dr2 =          { 0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  15, 63,  127, 127 };
        public static uint[] dr2h =         { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0   };

        // Default alignment (right)
        public static uint[] shift1_def =   { 4,  4,  5,  5,  6,  6,  5,  4,  4,  4,  4,  0,   0,   0   };
        public static uint[] shift2_def =   { 7,  7,  8,  8,  9,  9,  8,  7,  7,  8,  9,  10,  10,  9   };
        
        // Left overflow protected alignment
        public static uint[] shift1_OVF =   { 4,  4,  5,  5,  6,  6,  5,  4,  4,  4,  4,  0,   0,   0   };
        public static uint[] shift2_OVF =   { 0,  1,  3,  4,  6,  7,  7,  7,  0,  2,  4,  6,   7,   7   };

        // Left not overflow protected alignment
        public static uint[] shift1_nOVF =  { 5,  4,  5,  5,  6,  6,  5,  4,  3,  4,  4,  0,   0,   0   };
        public static uint[] shift2_nOVF =  { 0,  0,  2,  3,  5,  6,  6,  6,  6,  1,  3,  5,   6,   5   };

        public static uint[] gval =         { 9,  10, 11, 12, 13, 14, 15, 15, 15, 15, 15, 15,  15,  15  };
    }
}
