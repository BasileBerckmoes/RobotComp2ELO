/*******************************************************************************
* File Name:  bScanComp_v1_10.v
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides a top level model of the ScanComp component
*  definition and all of the necessary interconnect.
*
* Note:
*  None
*
*
********************************************************************************
*                 Control Register definitions
********************************************************************************
* Control Register Definition:
*  +=====+-----+-----+-----+-----+-----+-----+-----+-----------+
*  | Bit |  7  |  6  |  5  |  4  |  3  |  2  |  1  |     0     |
*  +=====+-----+-----+-----+-----+-----+-----------+-----------+
*  | Name|		         UNUSED            		   |  enable   |
*  +=====+-----+-----+-----+-----+-----+-----+-----+-----------+
*
*  ctrl_enable      => Enables the component clocks
*
*
********************************************************************************
*                 Status Registers definitions
********************************************************************************
* Output Status Registers Definition:
*  status_out0[7:0] => State of output channels from 7 to 0
*  status_out1[7:0] => State of output channels from 15 to 8
*  status_out2[7:0] => State of output channels from 23 to 16
*  status_out3[7:0] => State of output channels from 31 to 24
*  status_out4[7:0] => State of output channels from 39 to 25
*  status_out5[7:0] => State of output channels from 47 to 40
*  status_out6[7:0] => State of output channels from 55 to 48
*  status_out7[7:0] => State of output channels from 63 to 56
*
* Note: All 64 channels grouped by 8 channels and associated with 
*  status registers from 0 to 7.
*
* Interrupt Status Registers Definition:
*  status_int0[6:0] => Output from edge detector for cannels from 6 to 0
*  status_int1[6:0] => Output from edge detector for cannels from 14 to 8
*  status_int2[6:0] => Output from edge detector for cannels from 22 to 16
*  status_int3[6:0] => Output from edge detector for cannels from 30 to 24
*  status_int4[6:0] => Output from edge detector for cannels from 38 to 32
*  status_int5[6:0] => Output from edge detector for cannels from 46 to 40
*  status_int6[6:0] => Output from edge detector for cannels from 54 to 48
*  status_int7[6:0] => Output from edge detector for cannels from 62 to 56
*  status_int8[6:0] => Output from edge detector for cannels: 
                                                       55,47,39,31,24,15,7
*  status_int9[6:0] = Output from edge detector for cannel 63 
*
* Note: All values from Edge Detectors for channels grouped by 8 channels. 
*  Each 8-th MSB channel from 56 channels associated with status register 8. 
*  Channel 64 stored in the status register 9.
*
*
********************************************************************************
*                 I*O Signals:
********************************************************************************
*    Name              Direction       Description
*    clk               input           Clock
*    comp_o            input           Comparator output
*    ch         [63:0] output          Comparator value for each channel
*    ch_addr    [5:0]  output          Address for external muxes
*    eos               output          End-of-Scan output pulse
*    drq               output          The drq signal for DMA
*    interrupt         output          The ored interrupt signal
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

`include "cypress.v"
`ifdef bScanComp_v1_10_V_ALREADY_INCLUDED
`else
`define bScanComp_v1_10_V_ALREADY_INCLUDED

module bScanComp_v1_10
(
    input    wire    		clk,
    input    wire    		comp_o,
    output   wire	[5:0]   ch_addr,
    output   wire			interrupt,
    output   wire	[63:0]  ch,
    output   wire			eos,
    output   wire			drq
);


    /***************************************************************************
    * Parameters                                                             
    ***************************************************************************/
    parameter OutputsEnable = `FALSE;
    parameter [5:0] AvailableChannels = 6'h0;

    localparam Period = AvailableChannels - 1;
    localparam NumInputs = AvailableChannels - 1;

    localparam DEFAULT_CHANNEL_BITVALUE = 1;
    parameter [5:0] ChannelsBitValue = DEFAULT_CHANNEL_BITVALUE;
    
    localparam DEFAULT_INTERRUPT_BITVALUE = 1;
    parameter [3:0] InterruptBitValue = DEFAULT_INTERRUPT_BITVALUE;
    
    /* Edge Types */
    localparam [2:0] SCAN_COMP_EDGETYPE_RISING  = 3'd0;
    localparam [2:0] SCAN_COMP_EDGETYPE_FALLING = 3'd1;
    localparam [2:0] SCAN_COMP_EDGETYPE_EITHER  = 3'd2;
    localparam [2:0] SCAN_COMP_EDGETYPE_DISABLE = 3'd3;
    localparam [2:0] SCAN_COMP_EDGETYPE_LEVEL   = 3'd4;

    /* Control Register Bits (Bits 7-1 are unused )*/
    localparam [2:0] SCAN_COMP_CTRL_ENABLE   = 3'h0;   /* Enable */

    /* Int channels type parameters */
    parameter [2:0] EdgeType0 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType1 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType2 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType3 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType4 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType5 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType6 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType7 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType8 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType9 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType10 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType11 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType12 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType13 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType14 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType15 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType16 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType17 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType18 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType19 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType20 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType21 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType22 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType23 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType24 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType25 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType26 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType27 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType28 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType29 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType30 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType31 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType32 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType33 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType34 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType35 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType36 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType37 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType38 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType39 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType40 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType41 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType42 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType43 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType44 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType45 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType46 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType47 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType48 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType49 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType50 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType51 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType52 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType53 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType54 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType55 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType56 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType57 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType58 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType59 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType60 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType61 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType62 = SCAN_COMP_EDGETYPE_DISABLE;
    parameter [2:0] EdgeType63 = SCAN_COMP_EDGETYPE_DISABLE;


    /***************************************************************************
    * Internal Signals                                                       
    ***************************************************************************/
    /* Reg for ouput signals */
    reg  [NumInputs : 0]  ch_out;
    
    /* Edge detector Reg */
    reg  [NumInputs : 0]  ch_out_reg;
    
    wire [63 : 0]  edge_detect;
    
    /* EOS signal */
    wire tc_o; /* TC from Count7 */
    reg tc0; /* Delay Reg */
    reg tc1; /* Delay Reg */
    reg tc2; /* Delay Reg */
    reg tc3; /* Delay Reg */
    
    /* Internal Enable from Edge Detector forming */
    reg det_reg; /* Edge detector Reg */
    wire enable_int; /* Edge detector Out */
    
    /* Control Register Output */
    wire [7:0]  control;            

    /* Status registers reflect output signals */
    wire [7:0]  status_out0;
    wire [7:0]  status_out1;
    wire [7:0]  status_out2;
    wire [7:0]  status_out3;
    wire [7:0]  status_out4;
    wire [7:0]  status_out5;
    wire [7:0]  status_out6;
    wire [7:0]  status_out7;

    /* Status registers reflect state after edge detectors */
    wire [6:0]  status_int0;
    wire [6:0]  status_int1;
    wire [6:0]  status_int2;
    wire [6:0]  status_int3;
    wire [6:0]  status_int4;
    wire [6:0]  status_int5;
    wire [6:0]  status_int6;
    wire [6:0]  status_int7;
    wire [6:0]  status_int8;
    wire [6:0]  status_int9;
    
    /* Count7 for ch_addr forming */
    wire [6:0]  count;
    wire [ChannelsBitValue : 0]  counter_value;
    reg  [ChannelsBitValue : 0]  count_reg; /* Registered counter value */

    /* Control Register for clock enabling */
    wire        ctrl_enable;    /* Bit to enable clocks of the component */
    
    /* Others */
    reg         delay_form; /* Clock divider for internal enable forming */
    reg         drq_reg; /* Delay for drq signal */
    wire        status_reset; /* Reset for Statusi0 */
    reg         eos_latch; /* Latch for first EOS signal */

    /* Interrupt */
    wire [InterruptBitValue : 0]  irq_out;


    /***************************************************************************
    * Clock Synchronization used for Control register synchronization which  
    * is generate enable signal for component clocking                       
    ***************************************************************************/
    cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`TRUE))
    ClkCtrl
    (
        /* input  */    .clock_in(clk),
        /* input  */    .enable(1'b1),
        /* output */    .clock_out(clk_ctrl)
    );
    
    
    /***************************************************************************
    * Used for Status registers synchronization, edge detection, component   
    * sleep behavior                                                         
    ***************************************************************************/
    cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`TRUE))
    ClkSync(
        /* input  */    .clock_in(clk),
        /* input  */    .enable(ctrl_enable),
        /* output */    .clock_out(clk_int)
    );


    /***************************************************************************
    * Used for enable / disable clock in the component by firmware           
    ***************************************************************************/
    cy_psoc3_control #(.cy_force_order(1), .cy_ctrl_mode_1(8'h00), .cy_ctrl_mode_0(8'h03))
    CtrlCnt(
        /* input          */ .clock(clk_ctrl),
        /* output [07:00] */ .control(control)
    );


    /***************************************************************************
    * One Status register used to store channel output value                 
    * (for GetCompare API) for each 8 channels.                              
    * Another one Status Interrupt register used for each 7 channels.        
    * MSB channel from each 8 channels stores in the Status Register 8 at    
    * the apropriate position.                                               
    * St0_IntReg0 to St9_IntReg9 in the sticky mode used for storing       
    * interrupts after the edge detection. In this case 7-bit Statusi        
    * register components are used. StX_Int_RegX[7] channel is routed to 
    * the additional Statusi register. 
    * St0_OutReg0 to St7_OutReg7 in the transparent mode used for checking 
    * output value be firmware (GetCompare API).                             
    ***************************************************************************/
    /* Status Register 0 */
    cy_psoc3_status #(.cy_force_order(1), .cy_md_select(8'h00))
    St0_OutReg0(
        /* input            */  .clock(clk_int),
        /* input    [07:00] */  .status(status_out0)
    );

    /* Status Int Register 0 */
    cy_psoc3_statusi #(.cy_force_order(1), .cy_md_select(7'h7F),.cy_int_mask(7'h7F))
    St0_IntReg0(
           /* input          */  .clock(clk_int),
           /* input  [06:00] */  .status(status_int0),
           /* output         */  .interrupt(irq_out[0]),
           /* input          */  .reset(status_reset)
    );

    generate
        if (AvailableChannels > 7)
        begin : St8
           /* Status Int Register 8 */
            cy_psoc3_statusi #(.cy_force_order(1), .cy_md_select(7'h7F),.cy_int_mask(7'h7F))
            IntReg8(
                    /* input          */  .clock(clk_int),
                    /* input  [06:00] */  .status(status_int8),
                    /* output         */  .interrupt(irq_out[InterruptBitValue]),
                    /* input          */  .reset(1'b0)
            );
        end
    endgenerate

    generate
        if (AvailableChannels > 8)
        begin : St1
            /* Status Register 1 */
            cy_psoc3_status #(.cy_force_order(1), .cy_md_select(8'h00))
            OutReg1(
                /* input            */  .clock(clk_int),
                /* input    [07:00] */  .status(status_out1)
            );

            /* Status Int Register 1 */
            cy_psoc3_statusi #(.cy_force_order(1), .cy_md_select(7'h7F),.cy_int_mask(7'h7F))
            IntReg1(
                    /* input          */  .clock(clk_int),
                    /* input  [06:00] */  .status(status_int1),
                    /* output         */  .interrupt(irq_out[1]),
                    /* input          */  .reset(1'b0)
            );
        end

        if (AvailableChannels > 16)
        begin : St2
            /* Status Register 2 */
            cy_psoc3_status #(.cy_force_order(1), .cy_md_select(8'h00))
            OutReg2(
                /* input            */  .clock(clk_int),
                /* input    [07:00] */  .status(status_out2)
            );

            /* Status Int Register 2 */
            cy_psoc3_statusi #(.cy_force_order(1), .cy_md_select(7'h7F),.cy_int_mask(7'h7F))
            IntReg2(
                    /* input          */  .clock(clk_int),
                    /* input  [06:00] */  .status(status_int2),
                    /* output         */  .interrupt(irq_out[2]),
                    /* input          */  .reset(1'b0)
            );
        end

        if (AvailableChannels > 24)
        begin : St3
            /* Status Register 3 */
            cy_psoc3_status #(.cy_force_order(1), .cy_md_select(8'h00))
            OutReg3(
                /* input            */  .clock(clk_int),
                /* input    [07:00] */  .status(status_out3)
            );

            /* Status Int Register 3 */
            cy_psoc3_statusi #(.cy_force_order(1), .cy_md_select(7'h7F),.cy_int_mask(7'h7F))
            IntReg3(
                    /* input          */  .clock(clk_int),
                    /* input  [06:00] */  .status(status_int3),
                    /* output         */  .interrupt(irq_out[3]),
                    /* input          */  .reset(1'b0)
            );
        end

        if (AvailableChannels > 32)
        begin : St4
            /* Status Register 4 */
            cy_psoc3_status #(.cy_force_order(1), .cy_md_select(8'h00))
            OutReg4(
                /* input            */  .clock(clk_int),
                /* input    [07:00] */  .status(status_out4)
            );

            /* Status Int Register 4 */
            cy_psoc3_statusi #(.cy_force_order(1), .cy_md_select(7'h7F),.cy_int_mask(7'h7F))
            IntReg4(
                    /* input          */  .clock(clk_int),
                    /* input  [06:00] */  .status(status_int4),
                    /* output         */  .interrupt(irq_out[4]),
                    /* input          */  .reset(1'b0)
            );
        end

        if (AvailableChannels > 40)
        begin : St5
            /* Status Register 5 */
            cy_psoc3_status #(.cy_force_order(1), .cy_md_select(8'h00))
            OutReg5(
                /* input            */  .clock(clk_int),
                /* input    [07:00] */  .status(status_out5)
            );

            /* Status Int Register 5 */
            cy_psoc3_statusi #(.cy_force_order(1), .cy_md_select(7'h7F),.cy_int_mask(7'h7F))
            IntReg5(
                    /* input          */  .clock(clk_int),
                    /* input  [06:00] */  .status(status_int5),
                    /* output         */  .interrupt(irq_out[5]),
                    /* input          */  .reset(1'b0)
            );
        end

        if (AvailableChannels > 48)
        begin : St6
            /* Status Register 6 */
            cy_psoc3_status #(.cy_force_order(1), .cy_md_select(8'h00))
            OutReg6(
                /* input            */  .clock(clk_int),
                /* input    [07:00] */  .status(status_out6)
            );

            /* Status Int Register 6 */
            cy_psoc3_statusi #(.cy_force_order(1), .cy_md_select(7'h7F),.cy_int_mask(7'h7F))
            IntReg6(
                    /* input          */  .clock(clk_int),
                    /* input  [06:00] */  .status(status_int6),
                    /* output         */  .interrupt(irq_out[6]),
                    /* input          */  .reset(1'b0)
            );
        end

        if (AvailableChannels > 56)
        begin : St7
            /* Status Register 7 */
            cy_psoc3_status #(.cy_force_order(1), .cy_md_select(8'h00))
            OutReg7(
                /* input            */  .clock(clk_int),
                /* input    [07:00] */  .status(status_out7)
            );

            /* Status Int Register 7 */
            cy_psoc3_statusi #(.cy_force_order(1), .cy_md_select(7'h7F),.cy_int_mask(7'h7F))
            IntReg7(
                    /* input          */  .clock(clk_int),
                    /* input  [06:00] */  .status(status_int7),
                    /* output         */  .interrupt(irq_out[7]),
                    /* input          */  .reset(1'b0)
            );
        end
    endgenerate

    generate
        if (NumInputs > 63)
        begin : St9
            /* Status Int Register 9 */
            cy_psoc3_statusi #(.cy_force_order(1), .cy_md_select(7'h7F),.cy_int_mask(7'h7F))
            IntReg9(
                    /* input          */  .clock(clk_int),
                    /* input  [06:00] */  .status(status_int9),
                    /* output         */  .interrupt(irq_out[9]),
                    /* input          */  .reset(1'b0)
            );
        end
    endgenerate


    /***************************************************************************
    * Alternative counter mode is used (with separate enable, load           
    * signals and combinatorial tc). Period should be written before enable  
    * for exclude first tc happened. The cnt[5..0] output is used for        
    * changing addresses on comparator channels multiplexers and output      
    * signals forming. The tc output is using for EOS signal generation.     
    * Count7 works as down count counter.                                    
    ***************************************************************************/
    cy_psoc3_count7 #(.cy_period(Period),.cy_route_ld(0),.cy_route_en(1), .cy_alt_mode(1))
    ChannelCounter(
        /* input          */ .clock(clk_int),
        /* input          */ .reset(1'b0),
        /* input          */ .load(1'b0),
        /* input          */ .enable(enable_int),
        /* output [06:00] */ .count(count),
        /* output         */ .tc(tc_o)
    );


    /***************************************************************************
    * Synchronous logic                                                      
    ***************************************************************************/
    
    always @(posedge clk_int)
    begin
        delay_form <= ~ delay_form;
        det_reg <= delay_form;
        
        /* Latch when EOS hapenned */
        if (tc3) 
        begin
            eos_latch <= 1'b1;   
        end

        /* EOS with delay forming */
        tc0 <= tc_o;
        tc1 <= tc0;
        tc2 <= tc1;
        tc3 <= tc2;
    end

    always @(posedge clk_int)
    begin
        if (enable_int)
        begin
            drq_reg <= 1'b1;
            count_reg <= counter_value;
            
            /* Storing the result of comparison on the appropriate output */
            ch_out[count_reg] <= comp_o;
        end
        else
        begin
            drq_reg <= 1'b0;
        end        
    end


    /***************************************************************************
    * Combinatorial signals                                                  
    ***************************************************************************/

    generate
    if (OutputsEnable == `TRUE)
    begin
        if (AvailableChannels < 63)
        begin
            assign ch[63 : AvailableChannels] = 0;
            assign ch[NumInputs : 0] = ch_out[NumInputs : 0];
        end
        else
        begin
            assign ch[63:0] = ch_out[63 : 0];
        end
    end
    else
    begin
        assign ch[63:0] = 64'h0;
    end
    endgenerate

    generate
        if (AvailableChannels < 32)
        begin
            assign ch_addr[5 : (ChannelsBitValue + 1)]	= 1'b0;
            assign ch_addr[ChannelsBitValue : 0]	=  counter_value[ChannelsBitValue : 0];
        end
        else
        begin
            assign ch_addr[5:0]	= counter_value;
        end
    endgenerate

    assign counter_value = count[ChannelsBitValue : 0];
    
    /* EOS output signal */
    assign eos = tc3;
    
    /* DRQ output signal */
    assign drq = drq_reg;

    /* Edge Detecting */
    assign enable_int = (~det_reg & delay_form);

    /* Interrupt */
    assign interrupt = | irq_out[InterruptBitValue : 0];
        
    /* Control Signal */
    assign ctrl_enable	= control[SCAN_COMP_CTRL_ENABLE];

    /* Internal Reset Signal for Statusi0 Reg */
    assign status_reset = ~eos_latch;

    /* Status Int & Status out */
    generate
    if (AvailableChannels >= 8)
        begin
            assign status_out0[7:0] = ch_out[7:0];
            assign status_int0[6:0] = edge_detect[6:0];
        end
        else if (AvailableChannels < 8)
        begin
            assign status_out0[7 : (AvailableChannels)] = 0;
            assign status_out0[(NumInputs) : 0] = ch_out[NumInputs : 0];

            if (AvailableChannels == 7)
            begin
                assign status_int0[(NumInputs) : 0] = edge_detect[NumInputs : 0];
            end
            else
            begin
                assign status_int0[6 : (AvailableChannels)] = 0;
                assign status_int0[(NumInputs) : 0] = edge_detect[NumInputs : 0];
            end
        end
    endgenerate
    generate
        if (AvailableChannels >= 16)
        begin
            assign status_out1[7:0] = ch_out[15:8];
            assign status_int1[6:0] = edge_detect[14:8];
        end
        else if ((AvailableChannels < 16) && (AvailableChannels > 8))
        begin
            assign status_out1[7 : (NumInputs - 7)] = 0;
            assign status_out1[(NumInputs - 8) : 0] = ch_out[NumInputs : 8];

            if (AvailableChannels == 15)
            begin
                assign status_int1[(NumInputs - 8) : 0] = edge_detect[NumInputs : 8];
            end
            else
            begin
                assign status_int1[6 : (NumInputs - 7)] = 0;
                assign status_int1[(NumInputs - 8) : 0] = edge_detect[NumInputs : 8];
            end
        end
    endgenerate
    generate
        if (AvailableChannels >= 24) 
        begin
            assign status_out2[7:0] = ch_out[23:16];
            assign status_int2[6:0] = edge_detect[22:16];
        end
        else if ((AvailableChannels < 24) && (AvailableChannels > 16))
        begin
            assign status_out2[7 : (NumInputs - 15)] = 0;
            assign status_out2[(NumInputs - 16) : 0] = ch_out[NumInputs : 16];

            if (AvailableChannels == 23)
            begin
                assign status_int2[(NumInputs - 16) : 0] = edge_detect[NumInputs : 16];
            end
            else
            begin
                assign status_int2[6 : (NumInputs - 15)] = 0;
                assign status_int2[(NumInputs - 16) : 0] = edge_detect[NumInputs : 16];
            end
        end
    endgenerate
    generate      
        if (AvailableChannels >= 32)
        begin
            assign status_out3[7:0] = ch_out[31:24];
            assign status_int3[6:0] = edge_detect[30:24];
        end
        else if ((AvailableChannels < 32) && (AvailableChannels > 24))
        begin
            assign status_out3[7 : (NumInputs - 23)] = 0;
            assign status_out3[(NumInputs - 24) : 0] = ch_out[NumInputs : 24];

            if (AvailableChannels == 31)
            begin
                assign status_int3[(NumInputs - 24) : 0] = edge_detect[NumInputs : 24];
            end
            else
            begin
                assign status_int3[6 : (NumInputs - 23)] = 0;
                assign status_int3[(NumInputs - 24) : 0] = edge_detect[NumInputs : 24];
            end
        end
    endgenerate
    generate
        if (AvailableChannels >= 40)
        begin
            assign status_out4[7:0] = ch_out[39:32];
            assign status_int4[6:0] = edge_detect[38:32];
        end
        else if ((AvailableChannels < 40)  && (AvailableChannels > 32))
        begin
            assign status_out4[7 : (NumInputs - 31)] = 0;
            assign status_out4[(NumInputs - 32) : 0] = ch_out[NumInputs : 32];

            if (AvailableChannels == 39)
            begin
                assign status_int4[(NumInputs - 32) : 0] = edge_detect[NumInputs : 32];
            end
            else
            begin
                assign status_int4[6 : (NumInputs - 31)] = 0;
                assign status_int4[(NumInputs - 32) : 0] = edge_detect[NumInputs : 32];
            end
        end
    endgenerate
    generate
        if (AvailableChannels >= 48)
        begin
            assign status_out5[7:0] = ch_out[47:40];
            assign status_int5[6:0] = edge_detect[46:40];
       end
        else if ((AvailableChannels < 48) && (AvailableChannels > 40))
        begin
            assign status_out5[7 : (NumInputs - 39)] = 0;
            assign status_out5[(NumInputs - 40) : 0] = ch_out[NumInputs : 40];

            if (AvailableChannels == 47)
            begin
                assign status_int5[(NumInputs - 40) : 0] = edge_detect[NumInputs : 40];
            end
            else
            begin
                assign status_int5[6 : (NumInputs - 39)] = 0;
                assign status_int5[(NumInputs - 40) : 0] = edge_detect[NumInputs : 40];
            end
        end
    endgenerate
    generate
        if (AvailableChannels >= 56)
        begin
            assign status_out6[7:0] = ch_out[55:48];
            assign status_int6[6:0] = edge_detect[54:48];
        end
        else if ((AvailableChannels < 56) && (AvailableChannels > 48))
        begin
            assign status_out6[7 : (NumInputs - 47)] = 0;
            assign status_out6[(NumInputs - 48) : 0] = ch_out[NumInputs : 48];

            if (AvailableChannels == 55)
            begin
                assign status_int6[(NumInputs - 48) : 0] = edge_detect[NumInputs : 48];
            end
            else
            begin
                assign status_int6[6 : (NumInputs - 47)] = 0;
                assign status_int6[(NumInputs - 48) : 0] = edge_detect[NumInputs : 48];
            end
        end
    endgenerate
    generate
        if (AvailableChannels == 64)
        begin
            assign status_out7[7:0] = ch_out[63:56];
            assign status_int7[6:0] = edge_detect[62:56];
            assign status_int9[6:0] = {6'h0, edge_detect[63]};
        end
        else if ((AvailableChannels < 64) && (AvailableChannels > 56))
        begin
            assign status_out7[7 : (NumInputs - 55)] = 0;
            assign status_out7[(NumInputs - 56) : 0] = ch_out[NumInputs : 48];

            assign status_int7[6 : (NumInputs - 55)] = 0;
            assign status_int7[(NumInputs - 56) : 0] = edge_detect[NumInputs : 48];
        end
    endgenerate

    generate
        if (AvailableChannels >= 56)
        begin
            assign status_int8[6:0] = {edge_detect[55], edge_detect[47], edge_detect[39], edge_detect[31],
                                       edge_detect[24], edge_detect[15], edge_detect[7]};
        end
        else if (AvailableChannels >= 48)
        begin
            assign status_int8[6:0] = {1'h0, edge_detect[47], edge_detect[39], edge_detect[31], edge_detect[24],
                                             edge_detect[15], edge_detect[7]};
        end
        else if (AvailableChannels >= 40)
        begin
            assign status_int8[6:0] = {2'h0, edge_detect[39], edge_detect[31], edge_detect[24], edge_detect[15],
                                             edge_detect[7]};
        end
        else if (AvailableChannels >= 32)
        begin
            assign status_int8[6:0] = {3'h0, edge_detect[31], edge_detect[24], edge_detect[15], edge_detect[7]};
        end
        else if (AvailableChannels >= 24)
        begin
            assign status_int8[6:0] = {4'h0, edge_detect[24], edge_detect[15], edge_detect[7]};
        end
        else if (AvailableChannels >= 16)
        begin
            assign status_int8[6:0] = {5'h0, edge_detect[15], edge_detect[7]};
        end
        else if (AvailableChannels >= 8)
        begin
            assign status_int8[6:0] = {6'h0, edge_detect[7]};
        end
    endgenerate


    /**************************************************************************/
    /* EdgeDetect_0 to EdgeDetect_63 used for detects Rising Edge,            */
    /* Falling Edge, or Either Edge. If disabled option will be selected      */
    /* for channel – this component will be removed.                          */
    /**************************************************************************/
    generate
        /* 0 */
        if (EdgeType0 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[0] = ch_out[0];
            end

            if (EdgeType0 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[0] = (~ch_out_reg[0] & ch_out[0]);
            end
            else if (EdgeType0 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[0] = (ch_out_reg[0] & ~ch_out[0]);
            end
            else if (EdgeType0 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[0] = (ch_out_reg[0] ^ ch_out[0]);
            end
            else if (EdgeType0 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[0] = (count_reg == 0) ? ch_out[0] : 1'b0;
            end
            else
            begin
                assign edge_detect[0] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[0] = 1'b0;
        end

        /* 1 */
        if (EdgeType1 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[1] = ch_out[1];
            end

            if (EdgeType1 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[1] = (~ch_out_reg[1] & ch_out[1]);
            end
            else if (EdgeType1 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[1] = (ch_out_reg[1] & ~ch_out[1]);
            end
            else if (EdgeType1 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[1] = (ch_out_reg[1] ^ ch_out[1]);
            end
            else if (EdgeType1 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[1] = (count_reg == 1) ? ch_out[1] : 1'b0;
            end
            else
            begin
                assign edge_detect[1] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[1] = 1'b0;
        end

        /* 2 */
        if (EdgeType2 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[2] = ch_out[2];
            end

            if (EdgeType2 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[2] = (~ch_out_reg[2] & ch_out[2]);
            end
            else if (EdgeType2 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[2] = (ch_out_reg[2] & ~ch_out[2]);
            end
            else if (EdgeType2 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[2] = (ch_out_reg[2] ^ ch_out[2]);
            end
            else if (EdgeType2 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[2] = (count_reg == 2) ? ch_out[2] : 1'b0;
            end
            else
            begin
                assign edge_detect[2] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[2] = 1'b0;
        end

        /* 3 */
        if (EdgeType3 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[3] = ch_out[3];
            end

            if (EdgeType3 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[3] = (~ch_out_reg[3] & ch_out[3]);
            end
            else if (EdgeType3 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[3] = (ch_out_reg[3] & ~ch_out[3]);
            end
            else if (EdgeType3 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[3] = (ch_out_reg[3] ^ ch_out[3]);
            end
            else if (EdgeType3 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[3] = (count_reg == 3) ? ch_out[3] : 1'b0;
            end
            else
            begin
                assign edge_detect[3] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[3] = 1'b0;
        end

        /* 4 */
        if (EdgeType4 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[4] = ch_out[4];
            end

            if (EdgeType4 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[4] = (~ch_out_reg[4] & ch_out[4]);
            end
            else if (EdgeType4 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[4] = (ch_out_reg[4] & ~ch_out[4]);
            end
            else if (EdgeType4 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[4] = (ch_out_reg[4] ^ ch_out[4]);
            end
            else if (EdgeType4 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[4] = (count_reg == 4) ? ch_out[4] : 1'b0;
            end
            else
            begin
                assign edge_detect[4] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[4] = 1'b0;
        end

        /* 5 */
        if (EdgeType5 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[5] = ch_out[5];
            end

            if (EdgeType5 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[5] = (~ch_out_reg[5] & ch_out[5]);
            end
            else if (EdgeType5 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[5] = (ch_out_reg[5] & ~ch_out[5]);
            end
            else if (EdgeType5 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[5] = (ch_out_reg[5] ^ ch_out[5]);
            end
            else if (EdgeType5 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[5] = (count_reg == 5) ? ch_out[5] : 1'b0;
            end
            else
            begin
                assign edge_detect[5] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[5] = 1'b0;
        end

        /* 6 */
        if (EdgeType6 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[6] = ch_out[6];
            end

            if (EdgeType6 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[6] = (~ch_out_reg[6] & ch_out[6]);
            end
            else if (EdgeType6 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[6] = (ch_out_reg[6] & ~ch_out[6]);
            end
            else if (EdgeType6 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[6] = (ch_out_reg[6] ^ ch_out[6]);
            end
            else if (EdgeType6 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[6] = (count_reg == 6) ? ch_out[6] : 1'b0;
            end
            else
            begin
                assign edge_detect[6] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[6] = 1'b0;
        end

        /* 7 */
        if (EdgeType7 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[7] = ch_out[7];
            end

            if (EdgeType7 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[7] = (~ch_out_reg[7] & ch_out[7]);
            end
            else if (EdgeType7 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[7] = (ch_out_reg[7] & ~ch_out[7]);
            end
            else if (EdgeType7 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[7] = (ch_out_reg[7] ^ ch_out[7]);
            end
            else if (EdgeType7 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[7] = (count_reg == 7) ? ch_out[7] : 1'b0;
            end
            else
            begin
                assign edge_detect[7] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[7] = 1'b0;
        end

        /* 8 */
        if (EdgeType8 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[8] = ch_out[8];
            end

            if (EdgeType8 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[8] = (~ch_out_reg[8] & ch_out[8]);
            end
            else if (EdgeType8 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[8] = (ch_out_reg[8] & ~ch_out[8]);
            end
            else if (EdgeType8 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[8] = (ch_out_reg[8] ^ ch_out[8]);
            end
            else if (EdgeType8 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[8] = (count_reg == 8) ? ch_out[8] : 1'b0;
            end
            else
            begin
                assign edge_detect[8] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[8] = 1'b0;
        end

        /* 9 */
        if (EdgeType9 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[9] = ch_out[9];
            end

            if (EdgeType9 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[9] = (~ch_out_reg[9] & ch_out[9]);
            end
            else if (EdgeType9 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[9] = (ch_out_reg[9] & ~ch_out[9]);
            end
            else if (EdgeType9 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[9] = (ch_out_reg[9] ^ ch_out[9]);
            end
            else if (EdgeType9 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[9] = (count_reg == 9) ? ch_out[9] : 1'b0;
            end
            else
            begin
                assign edge_detect[9] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[9] = 1'b0;
        end

        /* 10 */
        if (EdgeType10 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[10] = ch_out[10];
            end

            if (EdgeType10 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[10] = (~ch_out_reg[10] & ch_out[10]);
            end
            else if (EdgeType10 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[10] = (ch_out_reg[10] & ~ch_out[10]);
            end
            else if (EdgeType10 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[10] = (ch_out_reg[10] ^ ch_out[10]);
            end
            else if (EdgeType10 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[10] = (count_reg == 10) ? ch_out[10] : 1'b0;
            end
            else
            begin
                assign edge_detect[10] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[10] = 1'b0;
        end

        /* 11 */
        if (EdgeType11 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[11] = ch_out[11];
            end

            if (EdgeType11 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[11] = (~ch_out_reg[11] & ch_out[11]);
            end
            else if (EdgeType11 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[11] = (ch_out_reg[11] & ~ch_out[11]);
            end
            else if (EdgeType11 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[11] = (ch_out_reg[11] ^ ch_out[11]);
            end
            else if (EdgeType11 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[11] = (count_reg == 11) ? ch_out[11] : 1'b0;
            end
            else
            begin
                assign edge_detect[11] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[11] = 1'b0;
        end

        /* 12 */
        if (EdgeType12 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[12] = ch_out[12];
            end

            if (EdgeType12 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[12] = (~ch_out_reg[12] & ch_out[12]);
            end
            else if (EdgeType12 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[12] = (ch_out_reg[12] & ~ch_out[12]);
            end
            else if (EdgeType12 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[12] = (ch_out_reg[12] ^ ch_out[12]);
            end
            else if (EdgeType12 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[12] = (count_reg == 12) ? ch_out[12] : 1'b0;
            end
            else
            begin
                assign edge_detect[12] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[12] = 1'b0;
        end

        /* 13 */
        if (EdgeType13 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[13] = ch_out[13];
            end

            if (EdgeType13 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[13] = (~ch_out_reg[13] & ch_out[13]);
            end
            else if (EdgeType13 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[13] = (ch_out_reg[13] & ~ch_out[13]);
            end
            else if (EdgeType13 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[13] = (ch_out_reg[13] ^ ch_out[13]);
            end
            else if (EdgeType13 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[13] = (count_reg == 13) ? ch_out[13] : 1'b0;
            end
            else
            begin
                assign edge_detect[13] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[13] = 1'b0;
        end

        /* 14 */
        if (EdgeType14 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[14] = ch_out[14];
            end

            if (EdgeType14 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[14] = (~ch_out_reg[14] & ch_out[14]);
            end
            else if (EdgeType14 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[14] = (ch_out_reg[14] & ~ch_out[14]);
            end
            else if (EdgeType14 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[14] = (ch_out_reg[14] ^ ch_out[14]);
            end
            else if (EdgeType14 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[14] = (count_reg == 14) ? ch_out[14] : 1'b0;
            end
            else
            begin
                assign edge_detect[14] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[14] = 1'b0;
        end

        /* 15 */
        if (EdgeType15 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[15] = ch_out[15];
            end

            if (EdgeType15 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[15] = (~ch_out_reg[15] & ch_out[15]);
            end
            else if (EdgeType15 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[15] = (ch_out_reg[15] & ~ch_out[15]);
            end
            else if (EdgeType15 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[15] = (ch_out_reg[15] ^ ch_out[15]);
            end
            else if (EdgeType15 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[15] = (count_reg == 15) ? ch_out[15] : 1'b0;
            end
            else
            begin
                assign edge_detect[15] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[15] = 1'b0;
        end

        /* 16 */
        if (EdgeType16 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[16] = ch_out[16];
            end

            if (EdgeType16 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[16] = (~ch_out_reg[16] & ch_out[16]);
            end
            else if (EdgeType16 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[16] = (ch_out_reg[16] & ~ch_out[16]);
            end
            else if (EdgeType16 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[16] = (ch_out_reg[16] ^ ch_out[16]);
            end
            else if (EdgeType16 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[16] = (count_reg == 16) ? ch_out[16] : 1'b0;
            end
            else
            begin
                assign edge_detect[16] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[16] = 1'b0;
        end

        /* 17 */
        if (EdgeType17 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[17] = ch_out[17];
            end

            if (EdgeType17 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[17] = (~ch_out_reg[17] & ch_out[17]);
            end
            else if (EdgeType17 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[17] = (ch_out_reg[17] & ~ch_out[17]);
            end
            else if (EdgeType17 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[17] = (ch_out_reg[17] ^ ch_out[17]);
            end
            else if (EdgeType17 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[17] = (count_reg == 17) ? ch_out[17] : 1'b0;
            end
            else
            begin
                assign edge_detect[17] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[17] = 1'b0;
        end

        /* 18 */
        if (EdgeType18 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[18] = ch_out[18];
            end

            if (EdgeType18 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[18] = (~ch_out_reg[18] & ch_out[18]);
            end
            else if (EdgeType18 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[18] = (ch_out_reg[18] & ~ch_out[18]);
            end
            else if (EdgeType18 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[18] = (ch_out_reg[18] ^ ch_out[18]);
            end
            else if (EdgeType18 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[18] = (count_reg == 18) ? ch_out[18] : 1'b0;
            end
            else
            begin
                assign edge_detect[18] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[18] = 1'b0;
        end

        /* 19 */
        if (EdgeType19 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[19] = ch_out[19];
            end

            if (EdgeType19 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[19] = (~ch_out_reg[19] & ch_out[19]);
            end
            else if (EdgeType19 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[19] = (ch_out_reg[19] & ~ch_out[19]);
            end
            else if (EdgeType19 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[19] = (ch_out_reg[19] ^ ch_out[19]);
            end
            else if (EdgeType19 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[19] = (count_reg == 19) ? ch_out[19] : 1'b0;
            end
            else
            begin
                assign edge_detect[19] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[19] = 1'b0;
        end

        /* 20 */
        if (EdgeType20 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[20] = ch_out[20];
            end

            if (EdgeType20 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[20] = (~ch_out_reg[20] & ch_out[20]);
            end
            else if (EdgeType20 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[20] = (ch_out_reg[20] & ~ch_out[20]);
            end
            else if (EdgeType20 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[20] = (ch_out_reg[20] ^ ch_out[20]);
            end
            else if (EdgeType20 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[20] = (count_reg == 20) ? ch_out[20] : 1'b0;
            end
            else
            begin
                assign edge_detect[20] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[20] = 1'b0;
        end

        /* 21 */
        if (EdgeType21 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[21] = ch_out[21];
            end

            if (EdgeType21 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[21] = (~ch_out_reg[21] & ch_out[21]);
            end
            else if (EdgeType21 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[21] = (ch_out_reg[21] & ~ch_out[21]);
            end
            else if (EdgeType21 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[21] = (ch_out_reg[21] ^ ch_out[21]);
            end
            else if (EdgeType21 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[21] = (count_reg == 21) ? ch_out[21] : 1'b0;
            end
            else
            begin
                assign edge_detect[21] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[21] = 1'b0;
        end

        /* 22 */
        if (EdgeType22 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[22] = ch_out[22];
            end

            if (EdgeType22 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[22] = (~ch_out_reg[22] & ch_out[22]);
            end
            else if (EdgeType22 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[22] = (ch_out_reg[22] & ~ch_out[22]);
            end
            else if (EdgeType22 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[22] = (ch_out_reg[22] ^ ch_out[22]);
            end
            else if (EdgeType22 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[22] = (count_reg == 22) ? ch_out[22] : 1'b0;
            end
            else
            begin
                assign edge_detect[22] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[22] = 1'b0;
        end

        /* 23 */
        if (EdgeType23 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[23] = ch_out[23];
            end

            if (EdgeType23 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[23] = (~ch_out_reg[23] & ch_out[23]);
            end
            else if (EdgeType23 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[23] = (ch_out_reg[23] & ~ch_out[23]);
            end
            else if (EdgeType23 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[23] = (ch_out_reg[23] ^ ch_out[23]);
            end
            else if (EdgeType23 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[23] = (count_reg == 23) ? ch_out[23] : 1'b0;
            end
            else
            begin
                assign edge_detect[23] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[23] = 1'b0;
        end

        /* 24 */
        if (EdgeType24 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[24] = ch_out[24];
            end

            if (EdgeType24 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[24] = (~ch_out_reg[24] & ch_out[24]);
            end
            else if (EdgeType24 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[24] = (ch_out_reg[24] & ~ch_out[24]);
            end
            else if (EdgeType24 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[24] = (ch_out_reg[24] ^ ch_out[24]);
            end
            else if (EdgeType24 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[24] = (count_reg == 24) ? ch_out[24] : 1'b0;
            end
            else
            begin
                assign edge_detect[24] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[24] = 1'b0;
        end

        /* 25 */
        if (EdgeType25 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[25] = ch_out[25];
            end

            if (EdgeType25 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[25] = (~ch_out_reg[25] & ch_out[25]);
            end
            else if (EdgeType25 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[25] = (ch_out_reg[25] & ~ch_out[25]);
            end
            else if (EdgeType25 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[25] = (ch_out_reg[25] ^ ch_out[25]);
            end
            else if (EdgeType25 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[25] = (count_reg == 25) ? ch_out[25] : 1'b0;
            end
            else
            begin
                assign edge_detect[25] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[25] = 1'b0;
        end

        /* 26 */
        if (EdgeType26 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[26] = ch_out[26];
            end

            if (EdgeType26 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[26] = (~ch_out_reg[26] & ch_out[26]);
            end
            else if (EdgeType26 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[26] = (ch_out_reg[26] & ~ch_out[26]);
            end
            else if (EdgeType26 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[26] = (ch_out_reg[26] ^ ch_out[26]);
            end
            else if (EdgeType26 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[26] = (count_reg == 26) ? ch_out[26] : 1'b0;
            end
            else
            begin
                assign edge_detect[26] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[26] = 1'b0;
        end

        /* 27 */
        if (EdgeType27 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[27] = ch_out[27];
            end

            if (EdgeType27 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[27] = (~ch_out_reg[27] & ch_out[27]);
            end
            else if (EdgeType27 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[27] = (ch_out_reg[27] & ~ch_out[27]);
            end
            else if (EdgeType27 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[27] = (ch_out_reg[27] ^ ch_out[27]);
            end
            else if (EdgeType27 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[27] = (count_reg == 27) ? ch_out[27] : 1'b0;
            end
            else
            begin
                assign edge_detect[27] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[27] = 1'b0;
        end

        /* 28 */
        if (EdgeType28 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[28] = ch_out[28];
            end

            if (EdgeType28 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[28] = (~ch_out_reg[28] & ch_out[28]);
            end
            else if (EdgeType28 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[28] = (ch_out_reg[28] & ~ch_out[28]);
            end
            else if (EdgeType28 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[28] = (ch_out_reg[28] ^ ch_out[28]);
            end
            else if (EdgeType28 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[28] = (count_reg == 28) ? ch_out[28] : 1'b0;
            end
            else
            begin
                assign edge_detect[28] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[28] = 1'b0;
        end

        /* 29 */
        if (EdgeType29 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[29] = ch_out[29];
            end

            if (EdgeType29 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[29] = (~ch_out_reg[29] & ch_out[29]);
            end
            else if (EdgeType29 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[29] = (ch_out_reg[29] & ~ch_out[29]);
            end
            else if (EdgeType29 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[29] = (ch_out_reg[29] ^ ch_out[29]);
            end
            else if (EdgeType29 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[29] = (count_reg == 29) ? ch_out[29] : 1'b0;
            end
            else
            begin
                assign edge_detect[29] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[29] = 1'b0;
        end

        /* 30 */
        if (EdgeType30 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[30] = ch_out[30];
            end

            if (EdgeType30 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[30] = (~ch_out_reg[30] & ch_out[30]);
            end
            else if (EdgeType30 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[30] = (ch_out_reg[30] & ~ch_out[30]);
            end
            else if (EdgeType30 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[30] = (ch_out_reg[30] ^ ch_out[30]);
            end
            else if (EdgeType30 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[30] = (count_reg == 30) ? ch_out[30] : 1'b0;
            end
            else
            begin
                assign edge_detect[30] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[30] = 1'b0;
        end

        /* 31 */
        if (EdgeType31 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[31] = ch_out[31];
            end

            if (EdgeType31 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[31] = (~ch_out_reg[31] & ch_out[31]);
            end
            else if (EdgeType31 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[31] = (ch_out_reg[31] & ~ch_out[31]);
            end
            else if (EdgeType31 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[31] = (ch_out_reg[31] ^ ch_out[31]);
            end
            else if (EdgeType31 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[31] = (count_reg == 31) ? ch_out[31] : 1'b0;
            end
            else
            begin
                assign edge_detect[31] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[31] = 1'b0;
        end

        /* 32 */
        if (EdgeType32 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[32] = ch_out[32];
            end

            if (EdgeType32 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[32] = (~ch_out_reg[32] & ch_out[32]);
            end
            else if (EdgeType32 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[32] = (ch_out_reg[32] & ~ch_out[32]);
            end
            else if (EdgeType32 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[32] = (ch_out_reg[32] ^ ch_out[32]);
            end
            else if (EdgeType32 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[32] = (count_reg == 32) ? ch_out[32] : 1'b0;
            end
            else
            begin
                assign edge_detect[32] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[32] = 1'b0;
        end

        /* 33 */
        if (EdgeType33 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[33] = ch_out[33];
            end

            if (EdgeType33 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[33] = (~ch_out_reg[33] & ch_out[33]);
            end
            else if (EdgeType33 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[33] = (ch_out_reg[33] & ~ch_out[33]);
            end
            else if (EdgeType33 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[33] = (ch_out_reg[33] ^ ch_out[33]);
            end
            else if (EdgeType33 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[33] = (count_reg == 33) ? ch_out[33] : 1'b0;
            end
            else
            begin
                assign edge_detect[33] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[33] = 1'b0;
        end

        /* 34 */
        if (EdgeType34 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[34] = ch_out[34];
            end

            if (EdgeType34 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[34] = (~ch_out_reg[34] & ch_out[34]);
            end
            else if (EdgeType34 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[34] = (ch_out_reg[34] & ~ch_out[34]);
            end
            else if (EdgeType34 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[34] = (ch_out_reg[34] ^ ch_out[34]);
            end
            else if (EdgeType34 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[34] = (count_reg == 34) ? ch_out[34] : 1'b0;
            end
            else
            begin
                assign edge_detect[34] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[34] = 1'b0;
        end

        /* 35 */
        if (EdgeType35 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[35] = ch_out[35];
            end

            if (EdgeType35 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[35] = (~ch_out_reg[35] & ch_out[35]);
            end
            else if (EdgeType35 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[35] = (ch_out_reg[35] & ~ch_out[35]);
            end
            else if (EdgeType35 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[35] = (ch_out_reg[35] ^ ch_out[35]);
            end
            else if (EdgeType35 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[35] = (count_reg == 35) ? ch_out[35] : 1'b0;
            end
            else
            begin
                assign edge_detect[35] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[35] = 1'b0;
        end

        /* 36 */
        if (EdgeType36 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[36] = ch_out[36];
            end

            if (EdgeType36 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[36] = (~ch_out_reg[36] & ch_out[36]);
            end
            else if (EdgeType36 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[36] = (ch_out_reg[36] & ~ch_out[36]);
            end
            else if (EdgeType36 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[36] = (ch_out_reg[36] ^ ch_out[36]);
            end
            else if (EdgeType36 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[36] = (count_reg == 36) ? ch_out[36] : 1'b0;
            end
            else
            begin
                assign edge_detect[36] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[36] = 1'b0;
        end

        /* 37 */
        if (EdgeType37 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[37] = ch_out[37];
            end

            if (EdgeType37 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[37] = (~ch_out_reg[37] & ch_out[37]);
            end
            else if (EdgeType37 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[37] = (ch_out_reg[37] & ~ch_out[37]);
            end
            else if (EdgeType37 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[37] = (ch_out_reg[37] ^ ch_out[37]);
            end
            else if (EdgeType37 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[37] = (count_reg == 37) ? ch_out[37] : 1'b0;
            end
            else
            begin
                assign edge_detect[37] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[37] = 1'b0;
        end

        /* 38 */
        if (EdgeType38 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[38] = ch_out[38];
            end

            if (EdgeType38 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[38] = (~ch_out_reg[38] & ch_out[38]);
            end
            else if (EdgeType38 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[38] = (ch_out_reg[38] & ~ch_out[38]);
            end
            else if (EdgeType38 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[38] = (ch_out_reg[38] ^ ch_out[38]);
            end
            else if (EdgeType38 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[38] = (count_reg == 38) ? ch_out[38] : 1'b0;
            end
            else
            begin
                assign edge_detect[38] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[38] = 1'b0;
        end

        /* 39 */
        if (EdgeType39 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[39] = ch_out[39];
            end

            if (EdgeType39 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[39] = (~ch_out_reg[39] & ch_out[39]);
            end
            else if (EdgeType39 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[39] = (ch_out_reg[39] & ~ch_out[39]);
            end
            else if (EdgeType39 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[39] = (ch_out_reg[39] ^ ch_out[39]);
            end
            else if (EdgeType39 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[39] = (count_reg == 39) ? ch_out[39] : 1'b0;
            end
            else
            begin
                assign edge_detect[39] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[39] = 1'b0;
        end

        /* 40 */
        if (EdgeType40 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[40] = ch_out[40];
            end

            if (EdgeType40 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[40] = (~ch_out_reg[40] & ch_out[40]);
            end
            else if (EdgeType40 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[40] = (ch_out_reg[40] & ~ch_out[40]);
            end
            else if (EdgeType40 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[40] = (ch_out_reg[40] ^ ch_out[40]);
            end
            else if (EdgeType40 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[40] = (count_reg == 40) ? ch_out[40] : 1'b0;
            end
            else
            begin
                assign edge_detect[40] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[40] = 1'b0;
        end

        /* 41 */
        if (EdgeType41 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[41] = ch_out[41];
            end

            if (EdgeType41 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[41] = (~ch_out_reg[41] & ch_out[41]);
            end
            else if (EdgeType41 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[41] = (ch_out_reg[41] & ~ch_out[41]);
            end
            else if (EdgeType41 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[41] = (ch_out_reg[41] ^ ch_out[41]);
            end
            else if (EdgeType41 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[41] = (count_reg == 41) ? ch_out[41] : 1'b0;
            end
            else
            begin
                assign edge_detect[41] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[41] = 1'b0;
        end

        /* 42 */
        if (EdgeType42 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[42] = ch_out[42];
            end

            if (EdgeType42 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[42] = (~ch_out_reg[42] & ch_out[42]);
            end
            else if (EdgeType42 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[42] = (ch_out_reg[42] & ~ch_out[42]);
            end
            else if (EdgeType42 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[42] = (ch_out_reg[42] ^ ch_out[42]);
            end
            else if (EdgeType42 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[42] = (count_reg == 42) ? ch_out[42] : 1'b0;
            end
            else
            begin
                assign edge_detect[42] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[42] = 1'b0;
        end

        /* 43 */
        if (EdgeType43 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[43] = ch_out[43];
            end

            if (EdgeType43 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[43] = (~ch_out_reg[43] & ch_out[43]);
            end
            else if (EdgeType43 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[43] = (ch_out_reg[43] & ~ch_out[43]);
            end
            else if (EdgeType43 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[43] = (ch_out_reg[43] ^ ch_out[43]);
            end
            else if (EdgeType43 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[43] = (count_reg == 43) ? ch_out[43] : 1'b0;
            end
            else
            begin
                assign edge_detect[43] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[43] = 1'b0;
        end

        /* 44 */
        if (EdgeType44 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[44] = ch_out[44];
            end

            if (EdgeType44 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[44] = (~ch_out_reg[44] & ch_out[44]);
            end
            else if (EdgeType44 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[44] = (ch_out_reg[44] & ~ch_out[44]);
            end
            else if (EdgeType44 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[44] = (ch_out_reg[44] ^ ch_out[44]);
            end
            else if (EdgeType44 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[44] = (count_reg == 44) ? ch_out[44] : 1'b0;
            end
            else
            begin
                assign edge_detect[44] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[44] = 1'b0;
        end

        /* 45 */
        if (EdgeType45 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[45] = ch_out[45];
            end

            if (EdgeType45 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[45] = (~ch_out_reg[45] & ch_out[45]);
            end
            else if (EdgeType45 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[45] = (ch_out_reg[45] & ~ch_out[45]);
            end
            else if (EdgeType45 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[45] = (ch_out_reg[45] ^ ch_out[45]);
            end
            else if (EdgeType45 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[45] = (count_reg == 45) ? ch_out[45] : 1'b0;
            end
            else
            begin
                assign edge_detect[45] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[45] = 1'b0;
        end

        /* 46 */
        if (EdgeType46 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[46] = ch_out[46];
            end

            if (EdgeType46 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[46] = (~ch_out_reg[46] & ch_out[46]);
            end
            else if (EdgeType46 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[46] = (ch_out_reg[46] & ~ch_out[46]);
            end
            else if (EdgeType46 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[46] = (ch_out_reg[46] ^ ch_out[46]);
            end
            else if (EdgeType46 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[46] = (count_reg == 46) ? ch_out[46] : 1'b0;
            end
            else
            begin
                assign edge_detect[46] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[46] = 1'b0;
        end

        /* 47 */
        if (EdgeType47 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[47] = ch_out[47];
            end

            if (EdgeType47 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[47] = (~ch_out_reg[47] & ch_out[47]);
            end
            else if (EdgeType47 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[47] = (ch_out_reg[47] & ~ch_out[47]);
            end
            else if (EdgeType47 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[47] = (ch_out_reg[47] ^ ch_out[47]);
            end
            else if (EdgeType47 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[47] = (count_reg == 47) ? ch_out[47] : 1'b0;
            end
            else
            begin
                assign edge_detect[47] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[47] = 1'b0;
        end

        /* 48 */
        if (EdgeType48 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[48] = ch_out[48];
            end

            if (EdgeType48 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[48] = (~ch_out_reg[48] & ch_out[48]);
            end
            else if (EdgeType48 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[48] = (ch_out_reg[48] & ~ch_out[48]);
            end
            else if (EdgeType48 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[48] = (ch_out_reg[48] ^ ch_out[48]);
            end
            else if (EdgeType48 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[48] = (count_reg == 48) ? ch_out[48] : 1'b0;
            end
            else
            begin
                assign edge_detect[48] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[48] = 1'b0;
        end

        /* 49 */
        if (EdgeType49 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[49] = ch_out[49];
            end

            if (EdgeType49 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[49] = (~ch_out_reg[49] & ch_out[49]);
            end
            else if (EdgeType49 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[49] = (ch_out_reg[49] & ~ch_out[49]);
            end
            else if (EdgeType49 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[49] = (ch_out_reg[49] ^ ch_out[49]);
            end
            else if (EdgeType49 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[49] = (count_reg == 49) ? ch_out[49] : 1'b0;
            end
            else
            begin
                assign edge_detect[49] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[49] = 1'b0;
        end

        /* 50 */
        if (EdgeType50 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[50] = ch_out[50];
            end

            if (EdgeType50 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[50] = (~ch_out_reg[50] & ch_out[50]);
            end
            else if (EdgeType50 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[50] = (ch_out_reg[50] & ~ch_out[50]);
            end
            else if (EdgeType50 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[50] = (ch_out_reg[50] ^ ch_out[50]);
            end
            else if (EdgeType50 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[50] = (count_reg == 50) ? ch_out[50] : 1'b0;
            end
            else
            begin
                assign edge_detect[50] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[50] = 1'b0;
        end

        /* 51 */
        if (EdgeType51 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[51] = ch_out[51];
            end

            if (EdgeType51 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[51] = (~ch_out_reg[51] & ch_out[51]);
            end
            else if (EdgeType51 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[51] = (ch_out_reg[51] & ~ch_out[51]);
            end
            else if (EdgeType51 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[51] = (ch_out_reg[51] ^ ch_out[51]);
            end
            else if (EdgeType51 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[51] = (count_reg == 51) ? ch_out[51] : 1'b0;
            end
            else
            begin
                assign edge_detect[51] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[51] = 1'b0;
        end

        /* 52 */
        if (EdgeType52 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[52] = ch_out[52];
            end

            if (EdgeType52 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[52] = (~ch_out_reg[52] & ch_out[52]);
            end
            else if (EdgeType52 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[52] = (ch_out_reg[52] & ~ch_out[52]);
            end
            else if (EdgeType52 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[52] = (ch_out_reg[52] ^ ch_out[52]);
            end
            else if (EdgeType52 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[52] = (count_reg == 52) ? ch_out[52] : 1'b0;
            end
            else
            begin
                assign edge_detect[52] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[52] = 1'b0;
        end

        /* 53 */
        if (EdgeType53 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[53] = ch_out[53];
            end

            if (EdgeType53 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[53] = (~ch_out_reg[53] & ch_out[53]);
            end
            else if (EdgeType53 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[53] = (ch_out_reg[53] & ~ch_out[53]);
            end
            else if (EdgeType53 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[53] = (ch_out_reg[53] ^ ch_out[53]);
            end
            else if (EdgeType53 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[53] = (count_reg == 53) ? ch_out[53] : 1'b0;
            end
            else
            begin
                assign edge_detect[53] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[53] = 1'b0;
        end

        /* 54 */
        if (EdgeType54 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[54] = ch_out[54];
            end

            if (EdgeType54 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[54] = (~ch_out_reg[54] & ch_out[54]);
            end
            else if (EdgeType54 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[54] = (ch_out_reg[54] & ~ch_out[54]);
            end
            else if (EdgeType54 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[54] = (ch_out_reg[54] ^ ch_out[54]);
            end
            else if (EdgeType54 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[54] = (count_reg == 54) ? ch_out[54] : 1'b0;
            end
            else
            begin
                assign edge_detect[54] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[54] = 1'b0;
        end

        /* 55 */
        if (EdgeType55 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[55] = ch_out[55];
            end

            if (EdgeType55 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[55] = (~ch_out_reg[55] & ch_out[55]);
            end
            else if (EdgeType55 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[55] = (ch_out_reg[55] & ~ch_out[55]);
            end
            else if (EdgeType55 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[55] = (ch_out_reg[55] ^ ch_out[55]);
            end
            else if (EdgeType55 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[55] = (count_reg == 55) ? ch_out[55] : 1'b0;
            end
            else
            begin
                assign edge_detect[55] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[55] = 1'b0;
        end

        /* 56 */
        if (EdgeType56 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[56] = ch_out[56];
            end

            if (EdgeType56 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[56] = (~ch_out_reg[56] & ch_out[56]);
            end
            else if (EdgeType56 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[56] = (ch_out_reg[56] & ~ch_out[56]);
            end
            else if (EdgeType56 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[56] = (ch_out_reg[56] ^ ch_out[56]);
            end
            else if (EdgeType56 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[56] = (count_reg == 56) ? ch_out[56] : 1'b0;
            end
            else
            begin
                assign edge_detect[56] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[56] = 1'b0;
        end

        /* 57 */
        if (EdgeType57 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[57] = ch_out[57];
            end

            if (EdgeType57 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[57] = (~ch_out_reg[57] & ch_out[57]);
            end
            else if (EdgeType57 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[57] = (ch_out_reg[57] & ~ch_out[57]);
            end
            else if (EdgeType57 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[57] = (ch_out_reg[57] ^ ch_out[57]);
            end
            else if (EdgeType57 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[57] = (count_reg == 57) ? ch_out[57] : 1'b0;
            end
            else
            begin
                assign edge_detect[57] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[57] = 1'b0;
        end

        /* 58 */
        if (EdgeType58 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[58] = ch_out[58];
            end

            if (EdgeType58 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[58] = (~ch_out_reg[58] & ch_out[58]);
            end
            else if (EdgeType58 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[58] = (ch_out_reg[58] & ~ch_out[58]);
            end
            else if (EdgeType58 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[58] = (ch_out_reg[58] ^ ch_out[58]);
            end
            else if (EdgeType58 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[58] = (count_reg == 58) ? ch_out[58] : 1'b0;
            end
            else
            begin
                assign edge_detect[58] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[58] = 1'b0;
        end

        /* 59 */
        if (EdgeType59 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[59] = ch_out[59];
            end

            if (EdgeType59 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[59] = (~ch_out_reg[59] & ch_out[59]);
            end
            else if (EdgeType59 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[59] = (ch_out_reg[59] & ~ch_out[59]);
            end
            else if (EdgeType59 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[59] = (ch_out_reg[59] ^ ch_out[59]);
            end
            else if (EdgeType59 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[59] = (count_reg == 59) ? ch_out[59] : 1'b0;
            end
            else
            begin
                assign edge_detect[59] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[59] = 1'b0;
        end

        /* 60 */
        if (EdgeType60 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[60] = ch_out[60];
            end

            if (EdgeType60 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[60] = (~ch_out_reg[60] & ch_out[60]);
            end
            else if (EdgeType60 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[60] = (ch_out_reg[60] & ~ch_out[60]);
            end
            else if (EdgeType60 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[60] = (ch_out_reg[60] ^ ch_out[60]);
            end
            else if (EdgeType60 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[60] = (count_reg == 60) ? ch_out[60] : 1'b0;
            end
            else
            begin
                assign edge_detect[60] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[60] = 1'b0;
        end

        /* 61 */
        if (EdgeType61 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[61] = ch_out[61];
            end

            if (EdgeType61 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[61] = (~ch_out_reg[61] & ch_out[61]);
            end
            else if (EdgeType61 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[61] = (ch_out_reg[61] & ~ch_out[61]);
            end
            else if (EdgeType61 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[61] = (ch_out_reg[61] ^ ch_out[61]);
            end
            else if (EdgeType61 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[61] = (count_reg == 61) ? ch_out[61] : 1'b0;
            end
            else
            begin
                assign edge_detect[61] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[61] = 1'b0;
        end

        /* 62 */
        if (EdgeType62 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[62] = ch_out[62];
            end

            if (EdgeType62 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[62] = (~ch_out_reg[62] & ch_out[62]);
            end
            else if (EdgeType62 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[62] = (ch_out_reg[62] & ~ch_out[62]);
            end
            else if (EdgeType62 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[62] = (ch_out_reg[62] ^ ch_out[62]);
            end
            else if (EdgeType62 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[62] = (count_reg == 62) ? ch_out[62] : 1'b0;
            end
            else
            begin
                assign edge_detect[62] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[62] = 1'b0;
        end

        /* 63 */
        if (EdgeType63 != SCAN_COMP_EDGETYPE_DISABLE)
        begin
            always @(posedge clk_int)
            begin
                ch_out_reg[63] = ch_out[63];
            end

            if (EdgeType63 == SCAN_COMP_EDGETYPE_RISING)
            begin
                assign edge_detect[63] = (~ch_out_reg[63] & ch_out[63]);
            end
            else if (EdgeType63 == SCAN_COMP_EDGETYPE_FALLING)
            begin
                assign edge_detect[63] = (ch_out_reg[63] & ~ch_out[63]);
            end
            else if (EdgeType63 == SCAN_COMP_EDGETYPE_EITHER)
            begin
                assign edge_detect[63] = (ch_out_reg[63] ^ ch_out[63]);
            end
            else if (EdgeType63 == SCAN_COMP_EDGETYPE_LEVEL)
            begin
                assign edge_detect[63] = (count_reg == 63) ? ch_out[63] : 1'b0;
            end
            else
            begin
                assign edge_detect[63] = 1'b0;
            end
        end
        else
        begin
            assign edge_detect[63] = 1'b0;
        end
    endgenerate
    
endmodule


`endif /* bScanComp_v1_10_V_ALREADY_INCLUDED */
