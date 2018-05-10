/*******************************************************************************
* File Name:  cy_UDB_clockenable_v1_0.v
*
* Description:
*  Verilog file for the synchronization of an input clock and enable as sepcified.
*  Assigns values to nets.
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
`ifdef CY_UDB_CLOCKENABLE_V1_0_ALREADY_INCLUDED
`else
`define CY_UDB_CLOCKENABLE_V1_0_ALREADY_INCLUDED

module cy_UDB_clockenable_v1_0 (
	clock_out,
	clock_in,
	enable
);
	output  clock_out;
	input   clock_in;
	input   enable;
	parameter ClockOutSync = `TRUE;

	cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(ClockOutSync))
	udbclkenable(
		.clock_in	(clock_in),
		.enable		(enable),
		.clock_out	(clock_out)
	);
endmodule

`endif /* CY_UDB_CLOCKENABLE_V1_0_ALREADY_INCLUDED */
