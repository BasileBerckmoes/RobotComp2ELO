/*******************************************************************************
* File Name:  bTMP05Intf_v1_10.v
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides a top level model of the TMP05Intf component
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
*  +=====+-----------+-----+-----+-----+-----+-----------+-----------+-----------+
*  | Bit |  7        |  6  |  5  |  4  |  3  |     2     |     1     |     0     |
*  +=====+-----------+-----+-----+-----+-----+-----------+-----------+-----------+
*  | Name|ctrl_enable|        UNUSED         |ctrl_count1|ctrl_count0|ctrl_start |
*  +=====+-----------+-----+-----+-----+-----+-----------+-----------+-----------+
*
*  ctrl_start       => edge = start measure
*
*  ctrl_count[1:0]  => Number of sensors selection.
*
*  ctrl_enable      => Enables the component
*
*
*******************************************************************************
*                 Datapath Register Definitions (16-bit)
*******************************************************************************
*
*  DESCRIPTION:
*    This data path captures the high and low times of up to 4 independent
*    sensor output PWMs
*
*  REGISTER USAGE:
*    F0 => Captures up to 4 sensor pwm input low times
*    F1 => Captures up to 4 sensor pwm input high times
*    D0 => Not used
*    D1 => Not used
*    A0 => Counter to measure sensor pwm input low time
*    A1 => Counter to measure sensor pwm input high time
*
*  DATA PATH STATES:
*    0 0 0   0   IDLE:   Reset pwm counters (A0<-0, A1<-0)
*    0 0 1   1   CNT_HI: Increment pwm high period counter (A1<-A1+1)
*    0 1 0   2   CNT_LO: Increment pwm low period counter (A0<-A0+1)
*    0 1 1   3   NEXT:   Prepare for next sensor reading (A0<-0, A1<-0)
*    1 0 0   4   Not used
*    1 0 1   5   Not used
*    1 1 0   6   Not used
*    1 1 1   7   Not used
*
*
********************************************************************************
*                 I*O Signals:
********************************************************************************
*    Name              Direction       Description
*    clk               input           Timing reference for pwm measurements
*    en                input           Block enable (active high)
*    sensor            input           Outputs from TMP05-06 daisy chain
*    eoc               output          Internal End-of-Conversion output pulse
*    eoc_out           output          End-of-Conversion output pulse
*    error             output          Error flag (sensor measurement timeout)
*    conv_start        output          Conversion start pulse to sensors
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*********************************************************************************/

`include "cypress.v"
`ifdef bTMP05Intf_v1_10_V_ALREADY_INCLUDED
`else
`define bTMP05Intf_v1_10_V_ALREADY_INCLUDED

module bTMP05Intf_v1_10
(
    input    wire    clk,
    input    wire    en,
    input    wire    sensor,
    output   wire    eoc,
    output   wire    eoc_out,
    output   wire    error,
    output   wire    conv_start
);

    /**************************************************************************/
    /* Parameters                                                             */
    /**************************************************************************/

    /* Control Register Bits (Bits 6-3 are unused )*/
    localparam [2:0] TMP05_CTRL_START    = 3'h0;   /* Start measure */
    localparam [2:0] TMP05_CTRL_COUNT0   = 3'h1;   /* Sensor num 0 */
    localparam [2:0] TMP05_CTRL_COUNT1   = 3'h2;   /* Sensor num 1 */
    localparam [2:0] TMP05_CTRL_EOC      = 3'h3;   /* EOC generation */
    localparam [2:0] TMP05_CTRL_ENABLE   = 3'h7;   /* Enable */

    /* PWM Capture Timer State Machine States */
    localparam [1:0] PWM_IDLE   = 2'b00;
    localparam [1:0] PWM_CNT_HI = 2'b01;
    localparam [1:0] PWM_CNT_LO = 2'b10;
    localparam [1:0] PWM_NEXT   = 2'b11;

    /* UDB Revision definitions */
    localparam CY_UDB_V0 = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_5A);
    localparam CY_UDB_V1 = (!CY_UDB_V0);


    /**************************************************************************/
    /* Internal Signals                                                       */
    /**************************************************************************/
    reg  [1:0]  pwm_state;          /* PWM Capture Timer state machine bits */

    wire [7:0]  control;            /* Control Register Output */
    wire        ctrl_start;         /* Conversion start pulse generated by F/W */
    wire        ctrl_count0;        /* Bit to select number of TMP05-06 sensors */
    wire        ctrl_count1;        /* Bit to select number of TMP05-06 sensors */
    wire        ctrl_enable;        /* Bit to enable component */
    wire        ctrl_eoc;           /* Bit to generate EOC signal */

    reg  [1:0]  capture_count;      /* Number of sensors in daisy chain */
    reg         sensor_reg;         /* Triggered version of sensor input */
    reg         stop_reg;           /* Triggered version of stop output */

    reg         start_pulse_1;      /* Triggered version of start input */
    reg         start_pulse_2;      /* Triggered version of triggered start */
    reg         start_pulse_reg;    /* Triggered start signal */    
    reg         eoc_pulse_1;        /* Triggered version of eoc */
    reg         eoc_pulse_2;        /* Triggered version of triggered eoc */
    reg         eoc_pulse_reg;      /* Triggered eoc output */
    
    wire        overflow;           /* Error condition */
    wire        load_fifos;         /* Signal to load A0->F0, A1->F1 */
    wire        synced_clock;       /* Internal clock net synchronized to clk */
    wire        internal_reset;     /* Block reset signal */
    wire        pos_edge_sensor;    /* Positive edge signal */
    wire        neg_edge_sensor;    /* Negative edge  signal */
    wire [1:0]  ff0;                /* Datapath overflow flags */
    wire [1:0]  ff1;                /* Datapath overflow flags */


    /**************************************************************************/
    /* Clock Synchronization                                                  */
    /**************************************************************************/
    cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`TRUE)) ClkSync
    (
        /* input  */    .clock_in(clk),
        /* input  */    .enable(en),
        /* output */    .clock_out(synced_clock)
    );

    generate
        if (CY_UDB_V0)
        begin: AsyncCtrl
            cy_psoc3_control #(.cy_force_order(`TRUE))
            CtrlReg (
                /* input [07:00] */.control(control)
            );
        end
        else
        begin: SyncCtrl
            cy_psoc3_control #(.cy_force_order(`TRUE), .cy_ctrl_mode_1(8'h0), .cy_ctrl_mode_0(8'h8F))
            CtrlReg (
                /* input         */ .clock(synced_clock),
                /* input [07:00] */ .control(control)
            );
        end
    endgenerate

    /* PWM Capture Timer Datapath  */
    cy_psoc3_dp16 #(.cy_dpconfig_a
    (
        {
            `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC__ALU,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM0:      IDLE: Clear A0, A1*/
            `CS_ALU_OP__INC, `CS_SRCA_A1, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM1:      CNT_HI: INC A1*/
            `CS_ALU_OP__INC, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM2:      CNT_LO: INC A0*/
            `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC__ALU,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM3:      NEXT: Clear A0, A1*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM4:          */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM5:          */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM6:          */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM7:          */
            8'hFF, 8'h00,  /*CFG9:      */
            8'hFF, 8'hFF,  /*CFG11-10:      */
            `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
            `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
            `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
            `SC_SI_A_DEFSI, /*CFG13-12:      */
            `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
            1'h0, `SC_FIFO1__A1, `SC_FIFO0__A0,
            `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
            `SC_FB_NOCHN, `SC_CMP1_NOCHN,
            `SC_CMP0_NOCHN, /*CFG15-14:      */
            10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
            `SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
            `SC_WRK16CAT_DSBL /*CFG17-16:      */
        }
    ), .cy_dpconfig_b
    (
        {
            `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC__ALU,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM0:      IDLE: Clear A0, A1*/
            `CS_ALU_OP__INC, `CS_SRCA_A1, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM1:      CNT_HI: INC A1*/
            `CS_ALU_OP__INC, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM2:      CNT_LO: INC A0*/
            `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC__ALU,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM3:      NEXT: Clear A0, A1*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM4:          */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM5:          */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM6:          */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM7:          */
            8'hFF, 8'h00,  /*CFG9:      */
            8'hFF, 8'hFF,  /*CFG11-10:      */
            `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_CHAIN,
            `SC_CI_A_CHAIN, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
            `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
            `SC_SI_A_DEFSI, /*CFG13-12:      */
            `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
            1'h0, `SC_FIFO1__A1, `SC_FIFO0__A0,
            `SC_MSB_DSBL, `SC_MSB_BIT7, `SC_MSB_NOCHN,
            `SC_FB_NOCHN, `SC_CMP1_CHNED,
            `SC_CMP0_CHNED, /*CFG15-14:      */
            10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
            `SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
            `SC_WRK16CAT_DSBL /*CFG17-16:      */
        }
    ))
    Tmp05Timer
    (
        /*  input                   */  .reset(1'b0),
        /*  input                   */  .clk(synced_clock),
        /*  input   [02:00]         */  .cs_addr({1'b0, pwm_state}),
        /*  input                   */  .route_si(1'b0),
        /*  input                   */  .route_ci(1'b0),
        /*  input                   */  .f0_load(load_fifos),
        /*  input                   */  .f1_load(load_fifos),
        /*  input                   */  .d0_load(1'b0),
        /*  input                   */  .d1_load(1'b0),
        /*  output  [01:00]         */  .ce0(),
        /*  output  [01:00]         */  .cl0(),
        /*  output  [01:00]         */  .z0(),
        /*  output  [01:00]         */  .ff0(ff0),
        /*  output  [01:00]         */  .ce1(),
        /*  output  [01:00]         */  .cl1(),
        /*  output  [01:00]         */  .z1(),
        /*  output  [01:00]         */  .ff1(ff1),
        /*  output  [01:00]         */  .ov_msb(),
        /*  output  [01:00]         */  .co_msb(),
        /*  output  [01:00]         */  .cmsb(),
        /*  output  [01:00]         */  .so(),
        /*  output  [01:00]         */  .f0_bus_stat(),
        /*  output  [01:00]         */  .f0_blk_stat(),
        /*  output  [01:00]         */  .f1_bus_stat(),
        /*  output  [01:00]         */  .f1_blk_stat()
    );


    /**************************************************************************/
    /* Synchronous logic                                                      */
    /**************************************************************************/

    
    always @(posedge synced_clock)
    begin
       /* Sensor signal triggered */
       sensor_reg <= sensor;

       /* Start signal pulse generator */
       start_pulse_1 <= ctrl_start;
       start_pulse_2 <= start_pulse_1;   
       start_pulse_reg <= start_pulse_1 ^ start_pulse_2;  
       
       /* EOC signal pulse generator */
       eoc_pulse_1 <= ctrl_eoc;
       eoc_pulse_2 <= eoc_pulse_1;   
       eoc_pulse_reg <= eoc_pulse_1 ^ eoc_pulse_2;  
    end

    /* PWM Capture Timer State Machine Generation */
    always @(posedge synced_clock)
    begin
        /* Reset to IDLE state when block is disabled or sensor times out */
        if (internal_reset)
        begin
            pwm_state <= PWM_IDLE;
        end
        else
        begin
            case (pwm_state)
                PWM_IDLE:           if (ctrl_enable)
                                    begin
                                        capture_count <= {ctrl_count1, ctrl_count0};
                                        stop_reg = 1'b0;
                                        if (start_pulse_reg)
                                        begin
                                            pwm_state <= PWM_CNT_HI;
                                        end
                                        else
                                        begin
                                            pwm_state <= PWM_IDLE;
                                        end
                                    end
                                    else
                                    begin
                                        pwm_state <= PWM_IDLE;
                                    end
                PWM_CNT_HI:         if (neg_edge_sensor)
                                    begin
                                        pwm_state <= PWM_CNT_LO;
                                    end
                                    else
                                    begin
                                        pwm_state <= PWM_CNT_HI;
                                    end
                PWM_CNT_LO:         if (pos_edge_sensor)
                                    begin
                                        pwm_state <= PWM_NEXT;
                                    end
                                    else
                                    begin
                                        pwm_state <= PWM_CNT_LO;
                                    end
                PWM_NEXT:           if (capture_count == 2'b00)
                                    begin
                                        stop_reg = 1'b1;
                                        pwm_state <= PWM_IDLE;
                                    end
                                    else
                                    begin
                                        capture_count <= capture_count - 1;
                                        pwm_state <= PWM_CNT_HI;
                                    end
                default:            pwm_state <= PWM_IDLE;
            endcase
        end
    end


    /**************************************************************************/
    /* Combinatorial signals                                                  */
    /**************************************************************************/

    /* Load FIFOs co-incident with timer_state == NEXT */
    assign load_fifos = (pwm_state == PWM_CNT_LO) & pos_edge_sensor;

    assign internal_reset = ~en | ff0[1];

    assign pos_edge_sensor = sensor & ~sensor_reg;

    assign neg_edge_sensor = ~sensor & sensor_reg;

    assign conv_start = start_pulse_reg;

    assign overflow = ff1[1] | ff0[1];

    assign eoc = stop_reg | overflow;
    
    assign eoc_out = eoc_pulse_reg;
    
    assign error = overflow;
    
    /* Control Signals */
    assign ctrl_start  = control[TMP05_CTRL_START];
    assign ctrl_count0 = control[TMP05_CTRL_COUNT0];
    assign ctrl_count1 = control[TMP05_CTRL_COUNT1];
    assign ctrl_eoc    = control[TMP05_CTRL_EOC];
    assign ctrl_enable = control[TMP05_CTRL_ENABLE];

endmodule


`endif /* bTMP05Intf_v1_10_V_ALREADY_INCLUDED */
