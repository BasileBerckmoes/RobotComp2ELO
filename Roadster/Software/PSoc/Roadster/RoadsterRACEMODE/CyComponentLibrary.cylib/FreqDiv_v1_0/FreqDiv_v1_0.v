/*******************************************************************************
* File Name: FreqDiv_v1_0.v
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
* The Frequency Divider component produces an output that is the clock input
* divided by the specified value. This file describes the component
* functionality in Verilog.
*
********************************************************************************
* I*O Signals:
********************************************************************************
*   Name        Direction       Description
*   div         output          Divided output
*   clock       input           Clock signal to divide
*   en          input           Enable internal counter
*   reset       input           Synchronous reset
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

`include "cypress.v"

`ifdef FreqDiv_v1_0_V_ALREADY_INCLUDED
`else
`define FreqDiv_v1_0_V_ALREADY_INCLUDED

module FreqDiv_v1_0 (
    div,    /* Divided output */
    clock,  /* Clock signal to divide */
    en,     /* Enable internal counter */
    reset   /* Synchronous reset */
);

    /***************************************************************************
    *             Parameters                                                
    ***************************************************************************/
    parameter [7:0] numBits = 1;
    parameter [31:0] Divider = 2;
    parameter [31:0] highPulse = 1;

    /***************************************************************************
    *            Interface Definition                                                
    ***************************************************************************/
    output reg div;
    input wire clock;
    input wire en;
    input wire reset;
    
    reg [(numBits-1):0] count;
    reg not_last_reset;

    always@(posedge clock)
    begin
        if (reset)
        begin
            /* Reset counter and hold output low until reset is released. */
            not_last_reset <= 0;
            div <= 0;
            count <= 0;
        end
        else if (en)
        begin
            not_last_reset <= 1;
            if (!not_last_reset)
            begin
                /* Output goes high first cycle after reset goes low */
                div <= 1;
            end
            else
            begin
                if (count == highPulse - 1)
                begin
                    div <= 0;
                    count <= count + 1;
                end
                else if (count == Divider - 1)
                begin
                    div <= 1;
                    count <= 0;
                end
                else
                begin
                    count <= count + 1;
                end			
            end
        end
    end

endmodule

`endif /* FreqDiv_v1_0_V_ALREADY_INCLUDED */
