/*******************************************************************************
*
* File Name: Bus_Connect_v2_40.v
*
* Description:
*  This component is used to connect analog buses with different width together.
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


`include "cypress.v"
`ifdef Bus_Connect_v2_40_V_ALREADY_INCLUDED
`else
`define Bus_Connect_v2_40_V_ALREADY_INCLUDED

module Bus_Connect_v2_40
(
    in_bus,     /* input bus */
    out_bus     /* output bus */
);

    parameter in_width = 1;
    parameter out_width = 1;
    
	inout [in_width - 1 : 0] in_bus;
	inout [out_width - 1 : 0] out_bus;
	
	electrical in_bus;
	electrical out_bus;
	
	cy_connect_v1_0 bus_connect(in_bus[(in_width < out_width ? in_width : out_width) - 1 : 0], 
                               out_bus[(in_width < out_width ? in_width : out_width) - 1 : 0]);
	defparam bus_connect.sig_width = in_width < out_width ? in_width : out_width;

endmodule

`endif /* Bus_Connect_v2_40_V_ALREADY_INCLUDED */

