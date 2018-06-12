/*******************************************************************************
* File Name: bVoltageSequencer_v3_40.v
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* DESCRIPTION:
*   The VoltageSequencer is primarily a firmware driven component. The verilog
*   file serves 3 purposes:
*
*      1) Instantiates control registers to drive the converter enable pins
*         and status registers to read the converter pgood outputs.
*
*      2) To implement Rapid Fault Response Hardware Block. The intention of
*         this block is turning off a power converter in response to a fault
*         condition in the shortest time possible.
*
*      3) To drive the interrupt terminal on the symbol (buried) for Fault
*         ISR processing.
*
********************************************************************************
*                 I*O Signals:
********************************************************************************
*    Name           Direction       Description
*    clock          input           Input component clock
*    enable         input           Global enable input 
*    ctl[6:1]       input           General purpose control signals    
*    pgood1..16     input           Converter pgood status
*    sys_stable     output          System power stability status
*    sys_up         output          System power ON status
*    sys_dn         output          System power OFF status
*    warn           output          System power warning status
*    fault          output          System power fault status
*    sts[6:1]       output          General purpose outputs
*    en1..16        output          Converter enable control
*    interrupt      output          Interrupt terminal
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*********************************************************************************/
 
`include "cypress.v"
`ifdef bVoltageSequencer_v3_40_V_ALREADY_INCLUDED
`else
`define bVoltageSequencer_v3_40_V_ALREADY_INCLUDED

module bVoltageSequencer_v3_40 (
	input   wire        clock,          /* Input clock */
    input   wire        systick,        /* Timing source for tick time */
	input   wire [6:1]  ctl,            /* General purpose control inputs */
	input   wire        enable,         /* Global enable input */
	input   wire        pgood1,         /* Converter  1 pgood status */
	input   wire        pgood2,         /* Converter  2 pgood status */
	input   wire        pgood3,         /* Converter  3 pgood status */
	input   wire        pgood4,         /* Converter  4 pgood status */
	input   wire        pgood5,         /* Converter  5 pgood status */
	input   wire        pgood6,         /* Converter  6 pgood status */
	input   wire        pgood7,         /* Converter  7 pgood status */
	input   wire        pgood8,         /* Converter  8 pgood status */
	input   wire        pgood9,         /* Converter  9 pgood status */
	input   wire        pgood10,        /* Converter 10 pgood status */
	input   wire        pgood11,        /* Converter 11 pgood status */
	input   wire        pgood12,        /* Converter 12 pgood status */
	input   wire        pgood13,        /* Converter 13 pgood status */
	input   wire        pgood14,        /* Converter 14 pgood status */
	input   wire        pgood15,        /* Converter 15 pgood status */
	input   wire        pgood16,        /* Converter 16 pgood status */
	input   wire        pgood17,        /* Converter 17 pgood status */
	input   wire        pgood18,        /* Converter 18 pgood status */
	input   wire        pgood19,        /* Converter 19 pgood status */
	input   wire        pgood20,        /* Converter 20 pgood status */
	input   wire        pgood21,        /* Converter 21 pgood status */
	input   wire        pgood22,        /* Converter 22 pgood status */
	input   wire        pgood23,        /* Converter 23 pgood status */
	input   wire        pgood24,        /* Converter 24 pgood status */
	input   wire        pgood25,        /* Converter 25 pgood status */
	input   wire        pgood26,        /* Converter 26 pgood status */
	input   wire        pgood27,        /* Converter 27 pgood status */
	input   wire        pgood28,        /* Converter 28 pgood status */
	input   wire        pgood29,        /* Converter 29 pgood status */
	input   wire        pgood30,        /* Converter 30 pgood status */
	input   wire        pgood31,        /* Converter 31 pgood status */
	input   wire        pgood32,        /* Converter 32 pgood status */
	output  wire        fault,          /* System power fault status */
    output  wire        warn,           /* System power warning status */
	output  wire [6:1]  sts,            /* General purpose status signals */
	output  wire        sys_dn,         /* System power OFF status */
	output  wire        sys_stable,     /* System power stability status */
	output  wire        sys_up,         /* System power OFF status */
    output  wire        en1,            /* Converter  1  enable control */
	output  wire        en2,            /* Converter  2  enable control */
	output  wire        en3,            /* Converter  3  enable control */
	output  wire        en4,            /* Converter  4  enable control */
	output  wire        en5,            /* Converter  5  enable control */
	output  wire        en6,            /* Converter  6  enable control */
	output  wire        en7,            /* Converter  7  enable control */
	output  wire        en8,            /* Converter  8  enable control */
	output  wire        en9,            /* Converter  9  enable control */
	output  wire        en10,           /* Converter 10  enable control */
	output  wire        en11,           /* Converter 11  enable control */
	output  wire        en12,           /* Converter 12  enable control */
	output  wire        en13,           /* Converter 13  enable control */
	output  wire        en14,           /* Converter 14  enable control */
	output  wire        en15,           /* Converter 15  enable control */
	output  wire        en16,           /* Converter 16  enable control */
	output  wire        en17,           /* Converter 17  enable control */
	output  wire        en18,           /* Converter 18  enable control */
	output  wire        en19,           /* Converter 19  enable control */
	output  wire        en20,           /* Converter 20  enable control */
	output  wire        en21,           /* Converter 21  enable control */
	output  wire        en22,           /* Converter 22  enable control */
	output  wire        en23,           /* Converter 23  enable control */
	output  wire        en24,           /* Converter 24  enable control */
	output  wire        en25,           /* Converter 25  enable control */
	output  wire        en26,           /* Converter 26  enable control */
	output  wire        en27,           /* Converter 27  enable control */
	output  wire        en28,           /* Converter 28  enable control */
	output  wire        en29,           /* Converter 29  enable control */
	output  wire        en30,           /* Converter 30  enable control */
	output  wire        en31,           /* Converter 31  enable control */
	output  wire        en32,           /* Converter 32  enable control */
    output  wire        seq_tick,       /* 250 us tick timer */
    output  wire        stable_tick,    /* 8 ms tick timer */
    output  reg         fault_interrupt /* Fault detection interrupt */
);

    /***************************************************************************
    *                       Parameters
    ***************************************************************************/
    parameter [5:0] NumConverters = 6'd8;  /* Number of converters      */
    parameter [2:0] NumCtlInputs  = 3'd1;  /* Number of control inputs  */
    parameter [2:0] NumStsOutputs = 3'd1;  /* Number of status outputs  */
    parameter [7:0] CtlPolarity   = 8'h1;  /* Polarity of ctl[x] inputs */
    
    /* The fault interrupt generation logic is pipelined to optimize usage of
    * PLD resources. Converters are divided into fault groups (four converters
    * in one fault group).
    */
    localparam FaultGroupNum = (NumConverters - 1) / 4;
    
    /***************************************************************************
    *                  Internal Signals
    ***************************************************************************/
    /* Combine pgood[x] into bus */
    wire [32:1] pgood_bus = {pgood32, pgood31, pgood30, pgood29, pgood28, pgood27, pgood26, pgood25,
                             pgood24, pgood23, pgood22, pgood21, pgood20, pgood19, pgood18, pgood17,
                             pgood16, pgood15, pgood14, pgood13, pgood12, pgood11, pgood10, pgood9,
                             pgood8,  pgood7,  pgood6,  pgood5,  pgood4,  pgood3,  pgood2,  pgood1};

    wire fault_detect_clk;              /* Fault detection logic clock source */
    wire fault_response_clk;            /* Rapid fault response clock source  */
    wire op_systick;                    /* Systick timing reference           */ 
    wire en_fault_hw;                   /* Rapid fault response clock enable  */

    /***************************************************************************
    *               Instantiation of udb_clock_enable primitive 
    ****************************************************************************
    * The udb_clock_enable primitive component allows to support clock enable 
    * mechanism and specify the intended synchronization behavior for the clock 
    * result (operational clock).
    */

    /* Fault detection logic clock source. Free-running. */
    cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`TRUE)) ClkSync
    (
        /* input  */    .clock_in(clock),
        /* input  */    .enable(1'b1),
        /* output */    .clock_out(fault_detect_clk)
    );

    /* System tick timer clock source. Free-running. */
    cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`TRUE)) TickSync
    (
        /* input  */    .clock_in(systick),
        /* input  */    .enable(1'b1),
        /* output */    .clock_out(op_systick)
    );

    /* Rapid fault response block clock source. Stopped while Sequencer is in
    * calibartion state.
    */
    cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`TRUE)) ClkEn
    (
        /* input  */    .clock_in(clock),
        /* input  */    .enable(en_fault_hw),
        /* output */    .clock_out(fault_response_clk)
    );

    /***************************************************************************
    *   Sequencer State Machine and System Stable Timer Tick 
    ****************************************************************************
    * State machine transitions for every power converter are always handled in 
    * the Sequencer State Machine ISR that is invoked every 250 us (when the 
    * number of converters is 16 or less) or 500 us (when the number of 
    * converters is greater than 16).
    * To implement the 250/500 us tick timer interrupt used to drive state 
    * machine transitions and the 8 ms tick timer used to count System Stable
    * Time a single count7 is used.
    * The count7 divides the input 8kHz clock frequency by 2 to generate 
    * 250 us tick (count0) or by 4 to generate 500 us tick (count1) and by 64
    * to generate 8 ms tick (tc).
    ***************************************************************************/
    localparam [6:0] TickTimerPeriod = 7'd63;

    wire [6:0]  count; 
    cy_psoc3_count7 #(.cy_period(TickTimerPeriod)) TickTimer
    (
        /*  input             */  .clock(op_systick),
        /*  input             */  .reset(1'b0),
        /*  input             */  .load(1'b0),
        /*  input             */  .enable(1'b1),
        /*  output  [06:00]   */  .count(count),
        /*  output            */  .tc(stable_tick)
    );
    assign seq_tick = (NumConverters <= 6'd16) ? count[0] : count[1];

    /***************************************************************************
    *           Status Register to monitor enable and ctl[6:0] inputs                    
    ****************************************************************************
    * Hardware monitoring of fault condition due to a de-assertion of ctl[x]
    * inputs. The signal can be active high or active low based on the parameter
    * settings in the customizer. If the signals are active high than they are 
    * inverted before feeding them to the statusi register, else the direct 
    * version of signals is used. This needs to be done to generate Fault ISR if
    * the ctl[x] inputs are used as shutdown source for power converter(s). 
    ***************************************************************************/
    wire cflt_int;
    reg [6:1] ctl_in;
    always @(posedge fault_detect_clk)
    begin
        ctl_in <= ctl[6:1] ^ CtlPolarity[5:0];
    end

    cy_psoc3_statusi #(.cy_force_order(`TRUE), .cy_md_select(7'h3F), .cy_int_mask(7'h0)) CtlMon
    (
        /* input         */ .clock(fault_detect_clk),
        /* input [06:00] */ .status({enable, ctl_in}),
        /* output        */ .interrupt(cflt_int)
    );    

    /***************************************************************************
    * Generation of ctl[6:1] fault condition. If ctl[x] not used, ctlf is
    * assigned to zero for logic optimization.
    ***************************************************************************/
    wire ctlfault = (NumCtlInputs > 3'd0) ? cflt_int : 1'b0;
    
    /***************************************************************************
    *                   System Control Register                    
    ****************************************************************************
    * Serves two purposes:
    *  - enables/disables rapid fault detection block
    *  - drives fault, warn, sys_stable, sys_up and sys_dn outputs
    ***************************************************************************/
    wire [7:0] ctrl;

    /* Control register bit locations. Bits 5-7 not used. */
    localparam [2:0] SEQUENCER_FAULT      = 3'd0;
    localparam [2:0] SEQUENCER_WARN       = 3'd1;
    localparam [2:0] SEQUENCER_SYS_STABLE = 3'd2;
    localparam [2:0] SEQUENCER_SYS_UP     = 3'd3;
    localparam [2:0] SEQUENCER_SYS_DN     = 3'd4;
    localparam [2:0] SEQUENCER_FAULT_EN   = 3'd7;
    
    cy_psoc3_control #(.cy_force_order(1)) SystemCtlReg
    (
        /* output [07:00] */  .control(ctrl)
    );    

    assign fault       = ctrl[SEQUENCER_FAULT];
    assign warn        = ctrl[SEQUENCER_WARN];
    assign sys_stable  = ctrl[SEQUENCER_SYS_STABLE];
    assign sys_up      = ctrl[SEQUENCER_SYS_UP];
    assign sys_dn      = ctrl[SEQUENCER_SYS_DN];
    assign en_fault_hw = ctrl[SEQUENCER_FAULT_EN];
    
    /***************************************************************************
    *  Control Register to drive sts[6:1] outputs                    
    ***************************************************************************/
    generate 
    if(NumStsOutputs > 0)
    begin: STS
        wire [1:0] nc;
        cy_psoc3_control #(.cy_force_order(1)) GeneralStsReg
        (
            /* output [07:00] */  .control({nc, sts[6:1]})
        );     
    end
    endgenerate
    
    /***************************************************************************
    *           Status Registers for Converter Pgood Monitoring                    
    ***************************************************************************/
    /* Converter power good (pgood1 through pgood8) Status Register */
    generate
    if(NumConverters > 0)
    begin: PG1
        cy_psoc3_status #(.cy_force_order(`TRUE), .cy_md_select(8'h00)) PgoodReg
        (
            /* input         */ .clock(1'b1),
            /* input [07:00] */ .status(pgood_bus[8:1])
        ); 
    end
    endgenerate
    
    /* Converter power good (pgood9 through pgood16) Status Register */
    generate
    if(NumConverters > 8)
    begin: PG2
        cy_psoc3_status #(.cy_force_order(`TRUE), .cy_md_select(8'h00)) PgoodReg
        (
            /* input         */ .clock(1'b1),
            /* input [07:00] */ .status(pgood_bus[16:9])
        ); 
    end
    endgenerate
    
    /* Converter power good (pgood17 through pgood24) Status Register */
    generate
    if(NumConverters > 16)
    begin: PG3
        cy_psoc3_status #(.cy_force_order(`TRUE), .cy_md_select(8'h00)) PgoodReg
        (
            /* input         */ .clock(1'b1),
            /* input [07:00] */ .status(pgood_bus[24:17])
        ); 
    end
    endgenerate
    
    /* Converter power good (pgood25 through pgood32) Status Register */
    generate
    if(NumConverters > 24)
    begin: PG4
        cy_psoc3_status #(.cy_force_order(`TRUE), .cy_md_select(8'h00)) PgoodReg
        (
            /* input         */ .clock(1'b1),
            /* input [07:00] */ .status(pgood_bus[32:25])
        ); 
    end
    endgenerate
    
    /***************************************************************************
    *           Control Registers for Converter Enable Driving                    
    ***************************************************************************/
    wire [32:1] fwen; /* firmware driven enable */  
    /* Converter enable (en1 through en8) Control Register */
    generate
    if(NumConverters > 0)
    begin: EN1
        cy_psoc3_control #(.cy_force_order(1)) EnReg
        (
            /* output [07:00] */  .control(fwen[8:1])
        ); 
    end
    endgenerate
    
    /* Converter enable (en9 through en16) Control Register */
    generate
    if(NumConverters > 8)
    begin: EN2
        cy_psoc3_control #(.cy_force_order(1)) EnReg
        (
            /* output [07:00] */  .control(fwen[16:9])
        ); 
    end
    endgenerate
    
    /* Converter enable (en17 through en25) Control Register */
    generate
    if(NumConverters > 16)
    begin: EN3
        cy_psoc3_control #(.cy_force_order(1)) EnReg
        (
            /* output [07:00] */  .control(fwen[24:17])
        );
    end
    endgenerate
    
    /* Converter enable (en9 through en16) Control Register */
    generate
    if(NumConverters > 24)
    begin: EN4
        cy_psoc3_control #(.cy_force_order(1)) EnReg
        (
            /* output [07:00] */  .control(fwen[32:25])
        ); 
    end
    endgenerate
    
    /***************************************************************************
    *               Fault interrupt generation logic
    ****************************************************************************
    * Fault interrupt generation logic requires 2 macrocells and one control 
    * register per 8 power converters. Control register is required to provide
    * knowledge for HW that converter's SW state machine is in the ON state.
    */
    /* Each bit represents a pgood fault condition in the corresponding group */
    reg [FaultGroupNum:0] pgfault; 
    /* Indicates that associated FW state machine is in ON state */
    wire [32:1] on;
    
    generate
    if(NumConverters > 0)
    begin: ON1
        cy_psoc3_control #(.cy_force_order(1)) OnReg
        (
            /* output [07:00] */  .control(on[8:1])
        ); 
    end
    endgenerate
    generate
    if(NumConverters > 8)
    begin: ON2
        cy_psoc3_control #(.cy_force_order(1)) OnReg
        (
            /* output [07:00] */  .control(on[16:9])
        ); 
    end
    endgenerate
    generate
    if(NumConverters > 16)
    begin: ON3
        cy_psoc3_control #(.cy_force_order(1)) OnReg
        (
            /* output [07:00] */  .control(on[24:17])
        ); 
    end
    endgenerate
    generate
    if(NumConverters > 24)
    begin: ON4
        cy_psoc3_control #(.cy_force_order(1)) OnReg
        (
            /* output [07:00] */  .control(on[32:25])
        ); 
    end
    endgenerate
    
    genvar i;
    
    generate
    for(i = 0; i <= FaultGroupNum; i = i + 1)
    begin: PGF
        always @(posedge fault_detect_clk)
        begin
            pgfault[i] <= ((~pgood_bus[4*(i+1):4*i+1] & on[4*(i+1):4*i+1]) != 4'h0);
        end
    end
    endgenerate

    always @(posedge fault_detect_clk)
    begin
        fault_interrupt <= |{pgfault, ctlfault} & en_fault_hw;
    end
    
    /***************************************************************************
    *                    Rapid Fault Response Implementation
    ****************************************************************************
    * A simple macrocell based design allows hardware to bypass firmware control
    * of the en[x] outputs and take immediate action. The intention is to let 
    * firmware control the en[x] terminals during power up sequencing and during
    * intended power down sequencing. Hardware will control the en[x] terminals
    * when a pgood[x] fault occurs and the associated power converter is ON.
    */
    localparam SEQUENCER_FAULTRESP_STATE_IDLE     = 2'b00;
    localparam SEQUENCER_FAULTRESP_STATE_PWR_UP   = 2'b01;
    localparam SEQUENCER_FAULTRESP_STATE_ON       = 2'b11;
    localparam SEQUENCER_FAULTRESP_STATE_SHUTDOWN = 2'b10;
    
    wire [32:1] en_bus;
    generate 
    for (i = 1; i <= NumConverters; i = i + 1)
    begin: FAULTRESP
        reg [1:0] state;
        always @(posedge fault_response_clk)
        begin
            case (state)
                SEQUENCER_FAULTRESP_STATE_IDLE: 
                if(fwen[i])
                begin
                    state <= SEQUENCER_FAULTRESP_STATE_PWR_UP;
                end
                SEQUENCER_FAULTRESP_STATE_PWR_UP:
                if(~fwen[i])
                begin
                    state <= SEQUENCER_FAULTRESP_STATE_IDLE;
                end
                else
                begin
                    if(on[i])
                    begin
                        state <= SEQUENCER_FAULTRESP_STATE_ON;
                    end
                    else
                    begin
                        state <= SEQUENCER_FAULTRESP_STATE_PWR_UP;
                    end
                end    
                SEQUENCER_FAULTRESP_STATE_ON:
                if(~pgood_bus[i] | ~fwen[i])
                begin
                    state <= SEQUENCER_FAULTRESP_STATE_SHUTDOWN;
                end
                SEQUENCER_FAULTRESP_STATE_SHUTDOWN:
                if(~fwen[i] & ~pgood_bus[i])
                begin
                    state <= SEQUENCER_FAULTRESP_STATE_IDLE;
                end    
                default:
                    state <= SEQUENCER_FAULTRESP_STATE_IDLE;
            endcase
        end
        assign en_bus[i] = state[0];
    end
    endgenerate
    
    /* Output assignment */
    assign en1  = en_bus[1];         
    assign en2  = en_bus[2];         
    assign en3  = en_bus[3];
    assign en4  = en_bus[4];
    assign en5  = en_bus[5];
    assign en6  = en_bus[6];
    assign en7  = en_bus[7];
    assign en8  = en_bus[8];
    assign en9  = en_bus[9];
    assign en10 = en_bus[10];
    assign en11 = en_bus[11];
    assign en12 = en_bus[12];
    assign en13 = en_bus[13];
    assign en14 = en_bus[14];
    assign en15 = en_bus[15];
    assign en16 = en_bus[16];
    assign en17 = en_bus[17];
    assign en18 = en_bus[18];
    assign en19 = en_bus[19];
    assign en20 = en_bus[20];
    assign en21 = en_bus[21];
    assign en22 = en_bus[22];
    assign en23 = en_bus[23];
    assign en24 = en_bus[24];
    assign en25 = en_bus[25];
    assign en26 = en_bus[26];
    assign en27 = en_bus[27];
    assign en28 = en_bus[28];
    assign en29 = en_bus[29];
    assign en30 = en_bus[30];
    assign en31 = en_bus[31];
    assign en32 = en_bus[32];
    
endmodule

`endif /* bVoltageSequencer_v3_40_V_ALREADY_INCLUDED */
