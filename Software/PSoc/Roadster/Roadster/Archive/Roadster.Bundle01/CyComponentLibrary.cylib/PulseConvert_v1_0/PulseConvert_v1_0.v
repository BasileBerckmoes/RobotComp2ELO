/*******************************************************************************
* File Name: PulseConvert_v1_0.v
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
* The Basic Counter component provides an up-counter with routable count value. 
* This file describes the component functionality in Verilog.
*
********************************************************************************
* I*O Signals:
********************************************************************************
*   Name        Direction       Description
*   p_out       output          Pulse output
*   out_clock   input           Clock to generate output
*   p_in        input           Sampled input
*   sample_clk  input           Clock to sample input
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

`include "cypress.v"

`ifdef PulseConvert_v1_0_V_ALREADY_INCLUDED
`else
`define PulseConvert_v1_0_V_ALREADY_INCLUDED

module PulseConvert_v1_0 (
    p_out,      /* Pulse output */
    out_clk,    /* Clock to generate output */
    p_in,       /* Sampled input */
    sample_clk  /* Clock to sample input */
);

    /***************************************************************************
    *            Interface Definition                                                
    ***************************************************************************/
    output wire p_out;
    input wire out_clk;
    input wire p_in;
    input wire sample_clk;

    reg in_sample;
    reg out_sample;
    reg out_pulse;

    assign p_out = out_pulse;

    always @(posedge sample_clk)
    begin
        /* in_sample needs to store a pulse until out_sample has seen it */
        in_sample <= (p_in | (in_sample & ~out_sample));
    end

    always @(posedge out_clk)
    begin
        /* out_sample must store the pulse until out_pulse sees it */
        out_sample <= (p_in | (in_sample & ~out_sample & ~out_pulse));
        
        /* out_pulse effectively edge detects out_sample */
        out_pulse <= ((p_in | in_sample) & ~out_sample);
    end

endmodule

`endif /* PulseConvert_v1_0_V_ALREADY_INCLUDED */
