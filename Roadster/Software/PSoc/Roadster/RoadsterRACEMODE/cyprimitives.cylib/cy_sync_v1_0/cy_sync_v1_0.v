/*******************************************************************************
* File Name:  cy_sync_v1_0.v
*
* Description:
*  Verilog file for the synchronization mode of the status register. Assigns values to nets.
*
* Note:
*  
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

`include "cypress.v"
`ifdef CY_SYNC_V1_0_ALREADY_INCLUDED
`else
`define CY_SYNC_V1_0_ALREADY_INCLUDED

module cy_sync_v1_0 (
	s_in,
	s_out,
	clock
);
	parameter SignalWidth = 1;

	input   clock;
	input   [SignalWidth-1:00] s_in;
	output  [SignalWidth-1:00] s_out;

	genvar i;
    generate
    	for (i = 0 ; i < SignalWidth ; i = i + 1)
		begin
			cy_psoc3_sync INST (
			.clock	(clock),
			.sc_in	(s_in[i]),
			.sc_out	(s_out[i]));
		end
    endgenerate
endmodule

`endif /* CY_SYNC_V1_0_ALREADY_INCLUDED */
