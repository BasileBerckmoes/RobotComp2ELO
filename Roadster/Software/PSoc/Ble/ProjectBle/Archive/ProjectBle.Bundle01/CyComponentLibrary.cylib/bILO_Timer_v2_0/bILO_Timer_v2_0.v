/*******************************************************************************
* File Name: bILO_Trim_UDB_Timer.v
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  The bILDO_Timer is an 8-bit down counter that captures the counter
*  value at the rising edge of the capture signal.
*
********************************************************************************
*                 I*O Signals
********************************************************************************
*    Name          Direction       Description
*
*    capture       input           capture signal
*    clock         input           input clock
*
********************************************************************************
*                 Datapath Register Definitions
********************************************************************************
*  INSTANCE NAME: CounterDP
*
*  DESCRIPTION:
*    This 8 bit datapath implements an 8-bit down counter that runs continuosly
*    when enabled. At the rising edge of the compare signal, the counter value
*    is captured into the capture register.
*
*  REGISTER USAGE:
*    F0 => Not Used.
*    F1 => Not Used.
*    D0 => Not Used.
*    D1 => Not Used.
*    A0 => Counter register
*    A1 => Capture register
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

`include "cypress.v"
`ifdef  bILO_Timer_v2_0_V_ALREADY_INCLUDED
`else
`define bILO_Timer_v2_0_V_ALREADY_INCLUDED

module bILO_Timer_v2_0
(
    input  wire       capture,     /* Capture signal */
    input  wire       clock        /* Clock for the component */
);

	/***************************************************************************
    *            UDB array version definitions 
    ***************************************************************************/   
    
    localparam CY_UDB_V0 = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_5A);    
    localparam CY_UDB_V1 = (!CY_UDB_V0);
	
    /***************************************************************************
    *       Internal signals
    ***************************************************************************/
	reg  [1:0] cnt_state;  /* State of the CounterDP                          */
	wire cnt_enable;       /* Enable signal from the control register         */
	reg capture_buf;       /* Buffer used to detect the 'capture' rising edge */
	wire capture_en;       /* Used for transitioning to the capture state     */
	
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
    localparam CNT_ENABLE   = 1'd0;
    
    /* Control register mode */
    cy_psoc3_control #(.cy_force_order(1), .cy_ctrl_mode_1(8'h00), .cy_ctrl_mode_0(8'h01)) CtlReg
    (
        /*  input         */  .clock(op_clock),
        /* output [07:00] */  .control(ctrl)
    );
    
    assign cnt_enable = ctrl[CNT_ENABLE];
	
	/***************************************************************************
    *       Capture edge detect                                            
    ***************************************************************************/
	/* Posedge of capture */
	always @(posedge op_clock)
	begin
	    capture_buf <= capture;
	end
	
	assign capture_en = capture & ~capture_buf;
	
	/***************************************************************************
    *       Counter control logic                                            
    ***************************************************************************/
	localparam CNT_STATE_RST        = 2'b00;
    localparam CNT_STATE_COUNT      = 2'b01;
    localparam CNT_STATE_CAPTURE    = 2'b10;
	
    always @(posedge op_clock)
    begin
		if(cnt_enable)
		begin
			case(cnt_state)
			CNT_STATE_RST:
			begin
				/* Start counting */
				cnt_state <= CNT_STATE_COUNT;
			end
			CNT_STATE_COUNT:
			begin
				if(capture_en)
				begin
					/* Capture the counter value */
					cnt_state <= CNT_STATE_CAPTURE;
				end
				else
				begin
					cnt_state <= CNT_STATE_COUNT;
				end
			end
			CNT_STATE_CAPTURE:
			begin
				cnt_state <= CNT_STATE_RST;
			end
			default:
				cnt_state <= CNT_STATE_RST;
			endcase
		end
		else
		begin
			/* Reset the counter */
			cnt_state <= CNT_STATE_RST;
		end
    end
	
cy_psoc3_dp8 #(.cy_dpconfig_a(
{
    `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM0:   Reset*/
    `CS_ALU_OP__DEC, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM1:   Count*/
    `CS_ALU_OP__DEC, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM2:   Capture + Count*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM3:   Idle*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM4:   Idle*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM5:   Idle*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM6:   Idle*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM7:   Idle*/
    8'hFF, 8'h00,  /*CFG9:   */
    8'hFF, 8'hFF,  /*CFG11-10:   */
    `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
    `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
    `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
    `SC_SI_A_DEFSI, /*CFG13-12:   */
    `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
    1'h0, `SC_FIFO1_ALU, `SC_FIFO0_ALU,
    `SC_MSB_DSBL, `SC_MSB_BIT7, `SC_MSB_NOCHN,
    `SC_FB_NOCHN, `SC_CMP1_NOCHN,
    `SC_CMP0_NOCHN, /*CFG15-14:     F0 in, chained*/
    10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
    `SC_FIFO__EDGE,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
    `SC_WRK16CAT_DSBL /*CFG17-16:     Edge triggered*/
}
)
) CounterDP(
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
        /*  output  [01:00]                  */  .cl1(),
        /*  output  [01:00]                  */  .z1(),
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

`endif
