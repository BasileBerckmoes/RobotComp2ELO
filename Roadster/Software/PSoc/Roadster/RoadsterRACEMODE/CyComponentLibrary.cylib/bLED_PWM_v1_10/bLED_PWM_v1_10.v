/*******************************************************************************
* File Name: bLED_PWM_v1_10.v
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  The bLED_PWM is an 8-bit PWM implemented as a down counter. When the counter
*  value is less than the value stored in the Compare register, the pwm output
*  goes high. The pwm output goes low again when the counter wraps around. The
*  tc pin is used to trigger the DMA transfer to the compare register for each
*  of the commons. The tc signal is also used to reset the Com_Driver control
*  register.
*
********************************************************************************
*                 I*O Signals
********************************************************************************
*    Name          Direction       Description
*
*    pwm           output          PWM output
*    tc            output          tc output
*    clock         input           input clock
*
********************************************************************************
*                 Datapath Register Definitions
********************************************************************************
*  INSTANCE NAME: PwmDP
*
*  DESCRIPTION:
*    This 8 bit datapath implements an 8-bit down counter that runs continuosly
*    once enabled. The counter counts down at each rising edge of the clock and
*    compares the current counter value with the value stored in the Compare
*    register. The compare value is loaded from the compare buffer when the
*    counter resets to 0.
*
*  REGISTER USAGE:
*    F0 => Not Used
*    F1 => Not Used
*    D0 => Compare value buffer
*    D1 => Not Used
*    A0 => Compare register
*    A1 => Counter register
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

`include "cypress.v"
`ifdef  bLED_PWM_v1_10_V_ALREADY_INCLUDED
`else
`define bLED_PWM_v1_10_V_ALREADY_INCLUDED

module bLED_PWM_v1_10
(
    output reg       pwm,         /* PWM output signal */
    output reg       tc,          /* Terminal count signal */
    input  wire      clock        /* Clock for the component */
);
    
    /***************************************************************************
    *       Internal signals
    ***************************************************************************/
	reg[1:0] cnt_state;      /* State of the PwmDP.                           */
	wire     cnt_enable;     /* Enable signal from the control register.      */
    wire     drive_pwm;      /* The result of the A1<A0 comparison.           */
    reg      initialization; /* Control for DMA initialization sequence.      */
    reg[1:0] init_cnt;       /* Counter for initialization sequence.          */
    wire     load_compare;   /* Detect A1==0, used to load the compare value. */
                             /* Also used to drive the tc output.             */
                           
    /***************************************************************************
    *         Instantiation of udb_clock_enable primitive 
    ****************************************************************************
    * The udb_clock_enable primitive component allows to support clock enable 
    * mechanism and specify the intended synchronization behavior for the clock 
    * result (operational clock).
    */
    cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`TRUE)) ClkSync
    (
        /* input  */    .clock_in(clock),
        /* input  */    .enable(1'b1),
        /* output */    .clock_out(op_clock)
    );

    /***************************************************************************
    *       Control register implementation                                      
    ***************************************************************************/   
    wire [7:0] ctrl;
    /* Control Register bit location (bits 7-1 are unused) */
    localparam CNT_ENABLE   = 3'd0;

    cy_psoc3_control #(.cy_force_order(1), .cy_ctrl_mode_1(8'h00), .cy_ctrl_mode_0(8'h01)) CtlReg
    (
        /*  input         */  .clock(op_clock),
        /* output [07:00] */  .control(ctrl)
    );
    
    assign cnt_enable = ctrl[CNT_ENABLE];
	
    /***************************************************************************
    *       PWM output drive and dma request logic                                            
    ***************************************************************************/
    always @(posedge op_clock)
    begin
        if(cnt_enable && !initialization)
        begin
            if(load_compare && !drive_pwm)
            begin
                /* let brightness=0 be equivalent to brightness=1 */
                pwm <= 1'b1;
            end
            else
            begin
                pwm <= drive_pwm;
            end
        end
        else
        begin
            pwm <= 1'b0;
        end
    end

    always @(posedge op_clock)
    begin
        if(cnt_enable)
        begin
            tc  <= load_compare;
            if((load_compare) && (init_cnt < 2))
            begin
                /* Need 2 cycles for DMA to transfer initial values */
                init_cnt <= init_cnt + 1;
            end
            else
            begin
                initialization <= 1'b0;
            end
        end
        else
        begin
            tc  <= 1'b0;
            initialization <= 1'b1;
            init_cnt <= 0;
        end
    end
    
	/***************************************************************************
    *       Datapath control logic                                            
    ***************************************************************************/
	localparam [1:0] CNT_STATE_IDLE       = 2'b00;
    localparam [1:0] CNT_STATE_COUNT      = 2'b01;
    localparam [1:0] CNT_STATE_LOAD       = 2'b10;
	
    always @(posedge op_clock)
    begin
        if(cnt_enable)
        begin
            if(load_compare)
            begin
                /* Load the compare value and also count down */
                cnt_state <= CNT_STATE_LOAD;
            end
            else
            begin
                /* Count down */
                cnt_state <= CNT_STATE_COUNT;
            end
        end
        else
        begin
            /* Halt the counter */
            cnt_state <= CNT_STATE_IDLE;
        end
    end

cy_psoc3_dp8 #(.cy_dpconfig_a(
{
    `CS_ALU_OP__XOR, `CS_SRCA_A1, `CS_SRCB_A1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM0:  Idle*/
    `CS_ALU_OP__DEC, `CS_SRCA_A1, `CS_SRCB_A0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM1:  Count*/
    `CS_ALU_OP__DEC, `CS_SRCA_A1, `CS_SRCB_A0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM2:  Load the compare register */
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM3:  Idle*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM4:  Idle*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM5:  Idle*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM6:  Idle*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM7:  Idle*/
    8'hFF, 8'h00,  /*CFG9:     */
    8'hFF, 8'hFF,  /*CFG11-10:     */
    `SC_CMPB_A1_D1, `SC_CMPA_A1_A0, `SC_CI_B_ARITH,
    `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
    `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
    `SC_SI_A_DEFSI, /*CFG13-12:     */
    `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
    1'h0, `SC_FIFO1_ALU, `SC_FIFO0_ALU,
    `SC_MSB_DSBL, `SC_MSB_BIT7, `SC_MSB_NOCHN,
    `SC_FB_NOCHN, `SC_CMP1_NOCHN,
    `SC_CMP0_NOCHN, /*CFG15-14:  */
    10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
    `SC_FIFO__EDGE,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
    `SC_WRK16CAT_DSBL /*CFG17-16:  */
}
)
) PwmDP(
        /*  input                   */  .reset(1'b0),
        /*  input                   */  .clk(op_clock),
        /*  input   [02:00]         */  .cs_addr({1'b0,cnt_state}),
        /*  input                   */  .route_si(1'b0),
        /*  input                   */  .route_ci(1'b0),
        /*  input                   */  .f0_load(1'b0),
        /*  input                   */  .f1_load(1'b0),
        /*  input                   */  .d0_load(1'b0),
        /*  input                   */  .d1_load(1'b0),
        /*  output  [01:00]                  */  .ce0(),
        /*  output  [01:00]                  */  .cl0(),
        /*  output  [01:00]                  */  .z0(),
        /*  output  [01:00]                  */  .ff0(),
        /*  output  [01:00]                  */  .ce1(),
        /*  output  [01:00]                  */  .cl1(drive_pwm),
        /*  output  [01:00]                  */  .z1(load_compare),
        /*  output  [01:00]                  */  .ff1(),
        /*  output  [01:00]                  */  .ov_msb(),
        /*  output  [01:00]                  */  .co_msb(),
        /*  output  [01:00]                  */  .cmsb(),
        /*  output  [01:00]                  */  .so(),
        /*  output  [01:00]                  */  .f0_bus_stat(),
        /*  output  [01:00]                  */  .f0_blk_stat(),
        /*  output  [01:00]                  */  .f1_bus_stat(),
        /*  output  [01:00]                  */  .f1_blk_stat()
);

endmodule

`endif /*  bLED_PWM_v1_10_V */