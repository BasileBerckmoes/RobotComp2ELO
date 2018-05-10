/*******************************************************************************
* File Name: EdgeDetect_v1_0.v
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
* The Edge Detector component samples the connected signal and produces a
* pulse when the selected edge occurs. This file describes the component
* functionality in Verilog.
*
********************************************************************************
* I*O Signals:
********************************************************************************
*   Name        Direction       Description
*   det         output          Detected edge
*   clock       input           Sampling clock
*   d           input           Signal to sample for edge
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

`include "cypress.v"

`ifdef EdgeDetect_v1_0_V_ALREADY_INCLUDED
`else
`define EdgeDetect_v1_0_V_ALREADY_INCLUDED

module EdgeDetect_v1_0 (
    det,    /* Detected edge */
    clock,  /* Sampling clock */
    d       /* Signal to sample for edge */
);

    /***************************************************************************
    *             Parameters                                                
    ***************************************************************************/
    parameter [1:0] EdgeType = 0;
    
    /***************************************************************************
    *            Interface Definition                                                
    ***************************************************************************/
    output wire det;
    input wire clock;
    input wire d;
    
    /* Edge Types */
    localparam [1:0] EDGE_DETECT_EDGETYPE_RISING = 2'd0;
    localparam [1:0] EDGE_DETECT_EDGETYPE_FALLING  = 2'd1;
    localparam [1:0] EDGE_DETECT_EDGETYPE_EITHER = 2'd2;
    
    reg last;
    
    always @(posedge clock)
    begin
        last <= d;
    end
    
    generate
    if (EdgeType == EDGE_DETECT_EDGETYPE_RISING)
    begin
        assign det = (~last & d);
    end
    else if (EdgeType == EDGE_DETECT_EDGETYPE_FALLING)
    begin
        assign det = (last & ~d);
    end
    else if (EdgeType == EDGE_DETECT_EDGETYPE_EITHER)
    begin
        assign det = (last ^ d);
    end
    endgenerate
    
endmodule

`endif /* EdgeDetect_v1_0_V_ALREADY_INCLUDED */
