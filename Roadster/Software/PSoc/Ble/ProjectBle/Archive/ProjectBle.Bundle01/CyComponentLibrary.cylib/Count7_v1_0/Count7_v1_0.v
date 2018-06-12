/*******************************************************************************
* File Name:  Count7_v1_0.v 
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description: 
*  This file provides a top level model of the 7-bit Down Counter componnent
*  defining and all of the necessary interconnect.
* 
* Note: 
*  None
*
******************************************************************************** 
*               I*O Signals:   
******************************************************************************** 
*  IO SIGNALS: 
*    reset       input           Reset
*    clock       input           Clock
*    en          input           Enable
*    load        input           Load
*    cnt         output          Count output
*    tc          output          Terminal count  
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

`include "cypress.v"
`ifdef Count7_v1_0_V_ALREADY_INCLUDED
`else
`define Count7_v1_0_V_ALREADY_INCLUDED

module Count7_v1_0 
(
    input  wire clock,
    input  wire en,
    input  wire load,
    input  wire reset,
    output wire [6:0] cnt,
    output wire tc
);
    /* Hardware parameters */
    parameter EnableSignal = 1'b0;
    parameter LoadSignal = 1'b0;

    cy_psoc3_count7 #(.cy_period(7'b1111111), .cy_route_ld(LoadSignal), .cy_route_en(EnableSignal))
    Counter7 (
        /* input */         .clock(clock),      /* Clock */
        /* input */         .reset(reset),      /* Reset */
        /* input */         .load(load),        /* Load signal used if cy_route_ld = TRUE */
        /* input */         .enable(en),        /* Enable signal used if cy_route_en = TRUE */
        /* output [6:0] */  .count(cnt),        /* Counter value output */
        /* output */        .tc(tc)             /* Terminal Count output */
    );

endmodule

`endif      /* Count7_v1_0_V_ALREADY_INCLUDED */
