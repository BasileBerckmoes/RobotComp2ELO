/*******************************************************************************
*
* FILENAME:         bVoltageFaultDetector.v
* Component Name:   bVoltageFaultDetector
*
* DESCRIPTION:
*  The Voltage Fault Detector component provides a simple way to monitor
*  up to 32 voltage inputs against user-defined over and under voltage limits
*  without the need to use ADC and to write firmware. The
*  component simply outputs a good/bad status result (power good or
*  pg[x]) for each voltage being monitored.
* 
*******************************************************************************
*                Control and Status Register Definitions
*******************************************************************************
*
*  Control Register
*  +=====+-------+-------+-------+--------+--------+-------+-------+-------+
*  | Bit |   7   |   6   |   5   |   4    |   3    |   2   |   1   |   0   |
*  +=====+-------+-------+-------+--------+--------+-------+-------+-------+
*  |Desc |                  NA:000000                      | pause | reset | 
*  +=====+-------+-------+-------+--------+--------+-------+-------+-------+
*
*   Bits   Name         Description
*   1      pause         When asserted, holds the fault detection logic and
*                        control state machine. pd[x] outputs keep their 
*                        current state.
*                            0 - de-asserted
*                            1 - asserted
*   0      reset         Active low reset signal
*    
*  PGOOD Status Registers
*
*   PG_STS_8, PG_STS_16, PG_STS_24, PG_STS_32
*  +=====+-------+-------+-------+--------+--------+-------+-------+-------+
*  | Bit |   7   |   6   |   5   |   4    |   3    |   2   |   1   |   0   |
*  +=====+-------+-------+-------+--------+--------+-------+-------+-------+
*  |Desc |                          PGOOD status                           |
*  +=====+-------+-------+-------+--------+--------+-------+-------+-------+
*
*  The status registers retain the PGOOD status of the corresponding input
*  voltage. That is, PG_STS_8 corresponds to input voltage 1 through 8,
*  PG_STS_16 - to inputs from 9 to 16, and so on.
*
*
*  OV Status Registers
*
*   OV_STS_8, OV_STS_16, OV_STS_24, OV_STS_32
*  +=====+-------+-------+-------+--------+--------+-------+-------+-------+
*  | Bit |   7   |   6   |   5   |   4    |   3    |   2   |   1   |   0   |
*  +=====+-------+-------+-------+--------+--------+-------+-------+-------+
*  |Desc |                          OV status                           |
*  +=====+-------+-------+-------+--------+--------+-------+-------+-------+
*
*  The status registers retain the OV status of the corresponding input
*  voltage. That is, OV_STS_8 corresponds to input voltage 1 through 8,
*  OV_STS_16 - to inputs from 9 to 16, and so on.
*
*******************************************************************************
*                 Datapath Register Definitions
*******************************************************************************
*
*  INSTANCE NAME:  PgFilt/OvFilt 
*
*  DESCRIPTION:
*    These data paths implement glitch filtering of the current voltage input.
*    PgFilt starts to increment anytime the current pgood sample differs from 
*    the pgood state for the associated input. OvFilt increments when OV fault
*    is asserted (OV Comp output is 1'b0) for the input being monitored. 
*    When the counter hits the glitch filter length, it gets reset to zero and
*    the current pgood value propagates to the output.
*    The PgFilt gets reset to zero anytime the current pgood sample matches
*    the current pgood state for the associated voltage input.
*	 OvFilt is gets reset when OV status is good, i.e. the OV Comp output
*    is 1'b1.
*
*  REGISTER USAGE:
*    F0 => Keeps the previous count value for the voltage being monitored
*    F1 => Keeps the current count value for the voltage being monitored
*    D0 => Glitch filter length
*    D1 => Not used
*    A0 => Glitch filter count register
*    A1 => Not used
*
*  DATA PATH STATES:
*    0 0 0   0   Idle:
*    0 0 1   1   Load the previous glitch filter count
*    0 1 0   2   Increment the glitch filter counter
*    0 1 1   3   Reset the glitch filter counter to zero
*    1 0 0   4   Reload the glitch filter counter
*    1 0 1   5   Not used
*    1 1 0   6   Not used
*    1 1 1   7   Not used
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

`include "cypress.v"
`ifdef bVoltageFaultDetector_v3_0_V_ALREADY_INCLUDED
`else
`define bVoltageFaultDetector_v3_0_V_ALREADY_INCLUDED

module bVoltageFaultDetector_v3_0(
    input  wire en,       /* Sync active high global enable */
    input  wire ov,       /* Over voltage comparator output */
    input  wire uv,       /* Under voltage comparator output */
    input  wire clock,    /* Component clock source */
    input  wire bus_clk,  /* Bus clock. Used to sample DMA nrq signals */
    input  wire mux_done, /* MUX control DMA completion status */
    output reg  pgood,    /* Global pgood signal */
    output wire pg1,      /* Active high signal indicating v1 is within range */
    output wire pg2,      /* Active high signal indicating v2 is within range */
    output wire pg3,      /* Active high signal indicating v3 is within range */
    output wire pg4,      /* Active high signal indicating v4 is within range */
    output wire pg5,      /* Active high signal indicating v5 is within range */
    output wire pg6,      /* Active high signal indicating v6 is within range */
    output wire pg7,      /* Active high signal indicating v7 is within range */
    output wire pg8,      /* Active high signal indicating v8 is within range */
    output wire pg9,      /* Active high signal indicating v9 is within range */
    output wire pg10,     /* Active high signal indicating v10 is within range */
    output wire pg11,     /* Active high signal indicating v11 is within range */
    output wire pg12,     /* Active high signal indicating v12 is within range */
    output wire pg13,     /* Active high signal indicating v13 is within range */
    output wire pg14,     /* Active high signal indicating v14 is within range */
    output wire pg15,     /* Active high signal indicating v15 is within range */
    output wire pg16,     /* Active high signal indicating v16 is within range */
    output wire pg17,     /* Active high signal indicating v17 is within range */
    output wire pg18,     /* Active high signal indicating v18 is within range */
    output wire pg19,     /* Active high signal indicating v19 is within range */
    output wire pg20,     /* Active high signal indicating v20 is within range */
    output wire pg21,     /* Active high signal indicating v21 is within range */
    output wire pg22,     /* Active high signal indicating v22 is within range */
    output wire pg23,     /* Active high signal indicating v23 is within range */
    output wire pg24,     /* Active high signal indicating v24 is within range */
    output wire pg25,     /* Active high signal indicating v25 is within range */
    output wire pg26,     /* Active high signal indicating v26 is within range */
    output wire pg27,     /* Active high signal indicating v27 is within range */
    output wire pg28,     /* Active high signal indicating v28 is within range */
    output wire pg29,     /* Active high signal indicating v29 is within range */
    output wire pg30,     /* Active high signal indicating v30 is within range */
    output wire pg31,     /* Active high signal indicating v31 is within range */
    output wire pg32,     /* Active high signal indicating v32 is within range */
    output reg  eoc,      /* Active high pulse at the end of scanning cycle */
    output wire dac_wr,   /* Triggers DMA to move VDACs to new OV/UV thresholds */
    output wire mux_next, /* Triggers DMA to switch AMux to next v[x] input */
    output wire filt_wr,  /* Triggers DMA to write glitch filter count */
    output reg  filt_rd   /* Triggers DMA to read glitch filter count */
);

    /***************************************************************************
    *       Parameters
    ***************************************************************************/
    localparam MAX_VOLTAGES = 32;
    parameter NumVoltages = 7'd8;

    /* Compare type */
    localparam OV_UV   = 2'd0;
    localparam OV_ONLY = 2'd1;
    localparam UV_ONLY = 2'd2;
    parameter  [1:0] CompareType = OV_UV;
    localparam OV_ENABLED = (CompareType != UV_ONLY);
    localparam UV_ENABLED = (CompareType != OV_ONLY);

    /* Input voltage settling time */
    parameter [6:0] SettlingDelay = 7'd64;
    localparam SETTLING_TIMER_PRESENT = (SettlingDelay != 7'd0);

    /* Glitch filter length */
    parameter [7:0] GfLength = 8'd8;

    genvar i;

    /***************************************************************************
    * Internal block interfaces
    ***************************************************************************/

    /* Glitch filter */
    reg  pg_filt_in_current;
    wire pg_filt_in_new;
    wire pg_filt_f0_empty;
    wire pg_filt_done;
    wire ov_filt_done;   

    /* This is used to connect a converter pgood status to pg[x] outputs */
    wire [MAX_VOLTAGES-1:0] pg_bus;

    /* This is used to connect a converter OV status to teh status registers */
    wire [MAX_VOLTAGES-1:0] ov_bus;

    /* Signals coming from comparators */
    reg  ov_sample;   /* Keeps most recent ov comparator output */
    reg  uv_sample;   /* Keeps most recent uv comparator output */
    reg  sample_comp; /* Active high pulse to trigger comparator sampling */

    /* pg[x] digital mux to connect current pg[x] to glitch filter */
    wire pg_mux_out;
    wire [NumVoltages-1:0] pg_mux_in;

    /* Active high pulse that enables internal voltage counter to switch to
    * next voltage.
    */
    reg next_voltage;

    /* Set when processing pipeline has been filled. Cleared when reset
    * is asserted.
    */
    reg busy;

    /* Stores settling delay expiration status until VFD state machine
    * has seen it.
    */
    wire settling_time_expired;

    /* OV status is sticky. This is connected to control register output and
    * generates pulse when status is read by SW.
    */
    wire is_ov_read;

    /***************************************************************************
    *         Instantiation of udb_clock_enable  
    ****************************************************************************
    * The udb_clock_enable primitive component allows supporting the clock
    * enable mechanism and specifying the intended synchronization behaviour for
    * the clock result (operational clock).
    */
    wire op_clk;    /* operational clock */

    cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`TRUE)) ClkSync
    (
        /* input  */    .clock_in(clock),
        /* input  */    .enable(1'b1),
        /* output */    .clock_out(op_clk)
    );

    /***************************************************************************
    *       Control register implementation
    ***************************************************************************/
    wire [7:0] ctrl;

    /* Control Register bit location (bits 7-3 are unused) */
    localparam [2:0] VFD_CTRL_RESET = 3'd0;
    localparam [2:0] VFD_CTRL_PAUSE = 3'd1;

    cy_psoc3_control #(.cy_force_order(1), .cy_ctrl_mode_1(8'h04), .cy_ctrl_mode_0(8'h07)) CtlReg
    (
        /*  input         */  .clock(op_clk),
        /* output [07:00] */  .control(ctrl)
    );

    /* Active low reset. Asserted when component is stopped. PGOOD outputs
    * are reset to '0' if the reset signal is asserted.
    */
    wire reset = ~ctrl[VFD_CTRL_RESET];

    /* The enable signal pauses the state machine controller. When the component
    * is paused, the PGOOD outputs are kept at their current state.
    * This is equivalent to the Pause() API functionality.
    */
    reg enable;
    always @(posedge op_clk)
    begin
        enable <= en & ~ctrl[VFD_CTRL_PAUSE] & ~reset;
    end

    /*************************************************************************** 
    * VFD control block state machine. Each voltage is being monitored using
    * the following control states. The state machine sequentially transits
    * through all the states.
    ***************************************************************************/
    localparam [2:0] VFD_IDLE         = 3'b000;
    localparam [2:0] VFD_TR_DAC_DMA   = 3'b001;
    localparam [2:0] VFD_TR_AMUX_DMA  = 3'b011;
    localparam [2:0] VFD_SAMPLE_PG    = 3'b010;
    localparam [2:0] VFD_FILTER_PG    = 3'b110;
    localparam [2:0] VFD_UPDATE_PG    = 3'b111;
    localparam [2:0] VFD_SETTLE_DELAY = 3'b101;
    localparam [2:0] VFD_SAMPLE_COMP  = 3'b100;
    reg [2:0] state;

    always @(posedge op_clk)
    begin
        if(reset)
        begin
            state <= VFD_IDLE;
        end
        else
        begin
            case(state)
                VFD_IDLE:         state <= (enable) ? VFD_TR_DAC_DMA : VFD_IDLE;
                VFD_TR_DAC_DMA:   state <= ~(pg_filt_f0_empty & busy) ? VFD_TR_AMUX_DMA : VFD_TR_DAC_DMA;
                VFD_TR_AMUX_DMA:  state <= VFD_SAMPLE_PG;
                VFD_SAMPLE_PG:    state <= VFD_FILTER_PG;
                VFD_FILTER_PG:    state <= VFD_UPDATE_PG;
                VFD_UPDATE_PG:    state <= VFD_SETTLE_DELAY;
                VFD_SETTLE_DELAY: state <= (settling_time_expired) ? VFD_SAMPLE_COMP : VFD_SETTLE_DELAY;
                VFD_SAMPLE_COMP:  state <= VFD_IDLE;
                default: state <= VFD_IDLE;
            endcase
        end
    end

    /***************************************************************************
    * The FSM state is exposed to the firmware using status register. This
    * allows the firmware to let the component run to a completion before an
    * attempt to access the VDACs directly for calibration purposes.
    ***************************************************************************/
    cy_psoc3_status #(.cy_force_order(1), .cy_md_select(8'h0)) StsReg
    (
        /* input          */  .clock(op_clk),
        /* input  [07:00] */  .status({5'b0, state})
    );

    /***************************************************************************
    *       Trigger DMAs to update DACs, AMux and glitch filter count
    ***************************************************************************/
    assign dac_wr   = (state == VFD_TR_DAC_DMA);
    assign mux_next = (state == VFD_TR_AMUX_DMA);
    always @(posedge op_clk)
    begin
        filt_rd <= (state == VFD_FILTER_PG);
    end

    /***************************************************************************
    *       AMux control and voltage settling delay
    ****************************************************************************
    * The nrq signal from the AMux control DMA triggers the settling delay timer 
    * to enable the input voltage being processed to settle before it is
    * sampled to the comparators.
    * To respond to the fast DMA nrq events without the possibility of
    * missing the events, the nrq signals must be converted to the component
    * slow clock domain.
    ***************************************************************************/
    reg  mux_done_fast;
    reg  mux_done_slow;
    wire settling_timer_ld;
    wire settling_timer_tc;
    reg  settling_timer_done;

    /* mux_done_fast needs to store pulse until mux_done_slow has seen it. */
    always @(posedge bus_clk)
    begin
        mux_done_fast <= (mux_done | (mux_done_fast & ~mux_done_slow));
    end

    always @(posedge op_clk)
    begin
        /* Samples and stores pulse until comparators are sampled. */
        mux_done_slow <= (mux_done_slow | mux_done_fast) & ~sample_comp;
    end

    /* Indicates to state machine that settling delay has
    * been expired. Logic depends on settling timer presence in design.
    * Synthesized as virtual mux. 
    */
    assign settling_time_expired = (SETTLING_TIMER_PRESENT) ? settling_timer_tc : mux_done_slow | mux_done_fast;

    /* Settling timer load. Optimized out from design if timer is not present. */
    assign settling_timer_ld = ~((mux_done_slow | mux_done_fast) & (state == VFD_SETTLE_DELAY));

    generate
    if(SETTLING_TIMER_PRESENT)    
    begin: Settling
        cy_psoc3_count7 #(.cy_period(SettlingDelay), .cy_route_ld(`TRUE), .cy_alt_mode(`TRUE)) Timer
        (
            /*  input             */  .clock(op_clk),
            /*  input             */  .reset(1'b0),
            /*  input             */  .load(settling_timer_ld),
            /*  input             */  .enable(1'b1),
            /*  output  [06:00]   */  .count(),
            /*  output            */  .tc(settling_timer_tc)
        );
    end
    endgenerate

    /***************************************************************************
    * Over (ov) and under (uv) voltage comparator outputs are considered
    * asynchronous because their timing is not guaranteed, however the
    * sync cells are not required by design. The output are sampled after they
    * settle down to a stable state.
    ***************************************************************************/    
    always @(posedge op_clk)
    begin
        sample_comp <= (state == VFD_SAMPLE_COMP);
        ov_sample   <= (reset) ? 1'b0 : (sample_comp) ? ov : ov_sample;
        uv_sample   <= (reset) ? 1'b0 : (sample_comp) ? uv : uv_sample;
    end

    /* Busy signal indicates when processing is active.
    * Processing is pipelined, therefore one sampling cycle delay is
    * required to fill pipeline.
    */
    always @(posedge op_clk)
    begin
        if(reset)
        begin
            busy <= 1'b0;
        end
        else
        begin
            busy <= busy | sample_comp;
        end
    end

    /***************************************************************************
    *                   Voltage multiplexing
    ****************************************************************************
    * The input to the glitch filter is multiplexed. The multiplexer select
    * signal (address) is derived from a down counter block, so signals
    * are multiplexed in the reverse order. The counter keeps track on which
    * voltage is currently being processed.
    */
    localparam [6:0] CNT_PERIOD = NumVoltages-1;
    
    /* Number of counter bits needed to control mux. To simplify code,
    * mux width granularity is 8.
    */
    localparam SEL_WIDTH = (NumVoltages <=  8) ? 3 :
                           (NumVoltages <= 16) ? 4 :
                       /* (NumVoltages <= 32) */ 5 ;
    
    wire [6:0] count;
    wire [SEL_WIDTH-1:0] sel = count[SEL_WIDTH-1:0];

    /* next_voltage generates a pulse that initiates:
    *  1. Capturing the current glitch filter count to FIFO (F1). This generates
    *     FIFO not empty status that triggers FiltWrDma to move the value to SRAM.
    *  2. Enabling the internal voltage counter to point to the next voltage.
    */
    always @(posedge op_clk)
    begin
        next_voltage <= (state == VFD_UPDATE_PG) & busy;
    end

    /* Generate eoc at the end of one complete comparison cycle. */
    always @(posedge op_clk)
    begin
        eoc <= (sel == 0) & next_voltage;
    end

    cy_psoc3_count7 #(.cy_period(CNT_PERIOD), .cy_route_en(`TRUE)) VoltCounter
    (
        /*  input             */  .clock(op_clk),
        /*  input             */  .reset(1'b0),
        /*  input             */  .load(1'b0),
        /*  input             */  .enable(next_voltage),
        /*  output  [06:00]   */  .count(count),
        /*  output            */  .tc()
    );

    /* The PLD capacity is limited by 12 inputs. Thus wide buses must be
    * divided to allow a design to fit better. 
    * N-channel multiplexers can be constructed by using smaller multiplexers
    * by chaining them together. For example, a 32-to-1 multiplexer can be made
    * with four 8-to-1 and one 4-to-1 multiplexers. The four 8-to-1 multiplexer
    * outputs are fed into the 4-to-1 with the three selector pins on the 8-to-1's
    * put in parallel and the two selector pins connected to 4-to-1 yielding the
    * total number of selector inputs of 5.
    */
    localparam M8_TO_1_IN_NUM = 8;
    localparam M8_TO_1_SEL_WIDTH = 3;
    localparam M8_TO_1_MUXES = (NumVoltages - 1) / M8_TO_1_IN_NUM + 1;

    /* This signal is forced to be made into a factoring point for logic
    * equations, which keeps the signal from being substituted out during
    * optimization. This allows the design to fit better.
    */
    reg  [M8_TO_1_MUXES-1:0] mux_8_to_1;
    wire [M8_TO_1_SEL_WIDTH-1:0] sel1 = sel[M8_TO_1_SEL_WIDTH-1:0];

    generate
    for(i = 0; i < M8_TO_1_MUXES; i = i + 1)
    begin:PG_MUX_STAGE1
        /* Connect pg_bus[] to corresponding 8-to-1 mux */
        always @(sel1 or pg_bus)
        begin
            case(sel1)
                3'd0: mux_8_to_1[i] = pg_bus[i * M8_TO_1_IN_NUM];
                3'd1: mux_8_to_1[i] = pg_bus[i * M8_TO_1_IN_NUM + 1];
                3'd2: mux_8_to_1[i] = pg_bus[i * M8_TO_1_IN_NUM + 2];
                3'd3: mux_8_to_1[i] = pg_bus[i * M8_TO_1_IN_NUM + 3];
                3'd4: mux_8_to_1[i] = pg_bus[i * M8_TO_1_IN_NUM + 4];
                3'd5: mux_8_to_1[i] = pg_bus[i * M8_TO_1_IN_NUM + 5];
                3'd6: mux_8_to_1[i] = pg_bus[i * M8_TO_1_IN_NUM + 6];
                3'd7: mux_8_to_1[i] = pg_bus[i * M8_TO_1_IN_NUM + 7];
            default:  mux_8_to_1[i] = 'bx;
            endcase
        end
    end
    endgenerate

    /* The second level mux is only used if the number of 8-to-1 muxes
    * is greater than 1. The width of sel signal for the second level 
    * mux is calculated as the difference between the total number of 
    * sel bits needed to address the given number of inputs and the
    * width of the 8-to-1 mux select signal.
    */
    if(M8_TO_1_MUXES > 1)
    begin: PG_MUX_STAGE2
        wire [SEL_WIDTH-1:M8_TO_1_SEL_WIDTH] sel2 = sel[SEL_WIDTH-1:M8_TO_1_SEL_WIDTH];
        assign pg_mux_out = mux_8_to_1[sel2];
    end
    else
    begin: PG_MUX_STAGE2_BYPASS
        assign pg_mux_out = mux_8_to_1[0];
    end

    /***************************************************************************
    *   pg[x] assignments
    ***************************************************************************/

    /* Global pgood generation. A single, active high signal indicating all
    * voltages are within the range. This output is registered, therefore it is
    * asserted/de-asserted one cycle clock after individual pgoods. The logic
    * must account for the PLD architecture to allow a design to fit better.
    * Unused logic will be optimized out.
    */
    wire and_pg_bus_07_00 = &pg_bus[07:00];
    wire and_pg_bus_15_08 = &pg_bus[15:08];
    wire and_pg_bus_23_16 = &pg_bus[23:16];
    wire and_pg_bus_31_24 = &pg_bus[31:24];

    always @(posedge op_clk)
    begin
        pgood <= and_pg_bus_07_00 & and_pg_bus_15_08 & and_pg_bus_23_16 & and_pg_bus_31_24;
    end

    /* Individual pgood logic generation. */
    generate
    for(i = 0; i < MAX_VOLTAGES; i = i + 1)
    begin: PG_REG
        if(i < NumVoltages)
        begin: STATE
            reg pg;
            always @(posedge op_clk)
            begin
                if(reset)
                begin
                    pg <= 1'b0;
                end
                else
                begin
                    /* If this input is active and glitch filter is done,
                    * invert pgood state. */
                    pg <= ((sel == i) & pg_filt_done) ? ~pg : pg;
                end
            end
            /* Connect pg[i] register to the output pg bus. */
            assign pg_bus[i] = pg;
        end
        else
        begin: ONE
            /* Populate unused pg_bus[] signals with ones. */
            assign pg_bus[i] = 1'b1;
        end
    end

    /* OV fault logic detection. */
    for(i = 0; (i < MAX_VOLTAGES) && (OV_ENABLED); i = i + 1)
    begin: OV_REG
        if(i < NumVoltages)
        begin: STATE
            reg ov;
            always @(posedge op_clk)
            begin
                if(reset | ov)
                begin
                    ov <= 1'b0;
                end
                else
                begin
                    /* If this input is active, glitch filter is done, and OV
                    * comparator output is low, assert OV fault bit. */
                    ov <= ((sel == i) & ov_filt_done) ? ~ov_sample : ov;
                end
            end
            /* Connect ov[i] register to output ov bus. */
            assign ov_bus[i] = ov;
        end
        else
        begin: ZERO
            /* Populate unused ov_bus[] signals with zeros. */
            assign ov_bus[i] = 1'b0;
        end
    end

    /* Assign pg_bus to status registers for CPU access. The number of status
    * registers needed in a design depends on the number of voltages to be 
    * monitored. A status register is an 8-bit width.
    */
    localparam NUM_STS_INPUTS = 8;
    localparam NUM_STS_REGS = (NumVoltages - 1) / NUM_STS_INPUTS + 1;

    /* Instantiate and connect PGOOD status registers */
    for(i = NUM_STS_INPUTS; (i <= NUM_STS_INPUTS * NUM_STS_REGS) && UV_ENABLED; i = i + NUM_STS_INPUTS)
    begin:PG_STS
        cy_psoc3_status #(.cy_force_order(1), .cy_md_select(8'h0)) Sts
        (
            /* input          */  .clock(op_clk),
            /* input  [07:00] */  .status(pg_bus[i-1:i-NUM_STS_INPUTS])
        );
    end

    /* Instantiate and connect OV status registers. OV fault event must be acknowledged.
    * Otherwise, event will persist. */
    for(i = NUM_STS_INPUTS; (i <= NUM_STS_INPUTS * NUM_STS_REGS) && OV_ENABLED; i = i + NUM_STS_INPUTS)
    begin: OV_STS
        cy_psoc3_status #(.cy_force_order(1), .cy_md_select(8'hFF)) Sts
        (
            /* input          */  .clock(op_clk),
            /* input  [07:00] */  .status(ov_bus[i-1:i-NUM_STS_INPUTS])
        );
    end
    endgenerate

    /* Map the internal pg_bus to pg[x] outputs. pg[x] that are not exposed on 
    * the VFD symbol are left floating and removed during the optimization phase.
    * (they are not connected to anything).
    * Mapping takes into account that the range of internal signals is
    * zero-based.  
    */
    assign { pg8,  pg7,  pg6,  pg5,  pg4,  pg3,  pg2, pg1 } = pg_bus[7 :0];
    assign {pg16, pg15, pg14, pg13, pg12, pg11, pg10, pg9 } = pg_bus[15:8];
    assign {pg24, pg23, pg22, pg21, pg20, pg19, pg18, pg17} = pg_bus[23:16];
    assign {pg32, pg31, pg30, pg29, pg28, pg27, pg26, pg25} = pg_bus[31:24];

    /***************************************************************************
    *                   Glitch Filtering
    ****************************************************************************
    * The glitch filter is a counter with a programmable period. It propagates
    * the input value to the output only after the user-specified glitch filter
    * delay expires.
    * The glitch filter gets reset to zero anytime its input matches its output.
    * Any time the input is changed, the counter inside the glitch filter starts
    * to increment. When it hits the user-specified delay value, the glitch
    * filter output reflects the input state.
    ***************************************************************************/

    localparam  GLITCH_FILT_COUNT_CFG = {
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM0: Idle*/
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC___F0, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM1: Load previous glitch filter count*/
        `CS_ALU_OP__INC, `CS_SRCA_A0, `CS_SRCB_A0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM2: Increment glitch filter count*/
        `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM3: Reset glitch filter count*/
        `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM4: Reload on counter done event*/
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM5: Idle*/
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM6: Idle*/
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM7: Idle*/
        8'hFF, 8'h00,  /*CFG9: */
        8'hFF, 8'hFF,  /*CFG11-10: */
        `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
        `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
        `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
        `SC_SI_A_DEFSI, /*CFG13-12: */
        `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
        1'h0, `SC_FIFO1__A0, `SC_FIFO0_BUS,
        `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
        `SC_FB_NOCHN, `SC_CMP1_NOCHN,
        `SC_CMP0_NOCHN, /*CFG15-14: */
        10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
        `SC_FIFO_LEVEL,`SC_FIFO_ASYNC,`SC_EXTCRC_DSBL,
        `SC_WRK16CAT_DSBL /*CFG17-16: */
    };

    /* Glitch filter FSM state definitions */
    localparam GLITCH_FILT_IDLE  = 2'd0;
    localparam GLITCH_FILT_LOAD  = 2'd1;
    localparam GLITCH_FILT_INCR  = 2'd2;
    localparam GLITCH_FILT_RESET = 2'd3;
    
    /***************************************************************************
    *                PGOOD glitch filter
    ***************************************************************************/
    reg [1:0] pg_filt_state;

    /* Feed current pg[x] value for voltage being monitored to glitch filter. */
    always @(posedge op_clk)
    begin     
        pg_filt_in_current <= pg_mux_out;
    end
    assign pg_filt_in_new = ov_sample & uv_sample;

    always @(posedge op_clk)
    begin
        if(busy)
        begin
            case(pg_filt_state)
                /* Transit to LOAD state in preparation for filtering when commanded
                * by main control state machine.
                */
                GLITCH_FILT_IDLE:
                    pg_filt_state <= (state == VFD_TR_AMUX_DMA) ? GLITCH_FILT_LOAD : GLITCH_FILT_IDLE;

                /* Load glitch filter count for voltage being monitored and
                * transit to either INCR or RESET state depending on the previous
                * and current pg[] state.
                */    
                GLITCH_FILT_LOAD:
                    pg_filt_state <= (pg_filt_in_new != pg_filt_in_current) ? GLITCH_FILT_INCR : GLITCH_FILT_RESET;

                default: pg_filt_state <= GLITCH_FILT_IDLE;
            endcase
        end
        else
        begin
            pg_filt_state <= GLITCH_FILT_IDLE;
        end
    end

    wire [14:0] chain;
    
    /* When an OV filter is not used in a design, connect chaining signals from
    * OV counter datapath to 0. */
    wire sil  = OV_ENABLED ? chain[12] : 1'b0;
    wire msbi = OV_ENABLED ? chain[11] : 1'b0;

    cy_psoc3_dp #(.cy_dpconfig(GLITCH_FILT_COUNT_CFG), .d0_init(GfLength)) PgFilt
    (
        /* input */          .clk(op_clk),                     
        /* input [02:00] */  .cs_addr({pg_filt_done, pg_filt_state}),
        /* input */          .route_si(1'b0),
        /* input */          .route_ci(1'b0),
        /* input */          .f0_load(1'b0),
        /* input */          .f1_load(next_voltage),
        /* input */          .d0_load(1'b0),
        /* input */          .d1_load(1'b0),
        /* output */         .ce0(pg_filt_done),
        /* output */         .f0_bus_stat(),
        /* output */         .f0_blk_stat(pg_filt_f0_empty),
        /* output */         .f1_bus_stat(filt_wr),
        /* output */         .f1_blk_stat(),
        /* input */          .ci(1'b0),
        /* output */         .co(chain[14]),
        /* input */          .sir(1'b0),
        /* output */         .sor(),
        /* input */          .sil(sil),
        /* output */         .sol(chain[13]),
        /* input */          .msbi(msbi),
        /* output */         .msbo(),
        /* input [01:00] */  .cei(2'b0),
        /* output [01:00] */ .ceo(chain[10:9]),
        /* input [01:00] */  .cli(2'b0),
        /* output [01:00] */ .clo(chain[8:7]),
        /* input [01:00] */  .zi(2'b0),
        /* output [01:00] */ .zo(chain[6:5]),
        /* input [01:00] */  .fi(2'b0),
        /* output [01:00] */ .fo(chain[4:3]),
        /* input [01:00] */  .capi(2'b0),
        /* output [01:00] */ .capo(chain[2:1]),
        /* input */          .cfbi(1'b0),
        /* output */         .cfbo(chain[0])
    );

    /***************************************************************************
    *                OV glitch filter
    ****************************************************************************
    * If OV/UV fault detection is enabled, the glitch filter is additionaly
    * applied to the OV status. This is required to distinguish a fault type.
    * The OV filter has a dedicated 8-bit counter done in datapath. 
    * The datapaths are chained for 16-bit DMA access. This allows DMA to 
    * read/write both filters at the same time.
    ***************************************************************************/
    generate
    if(OV_ENABLED)
    begin: OV
        reg [1:0] ov_filt_state;
        always @(posedge op_clk)
        begin
            if(busy)
            begin
                case(ov_filt_state)
                    /* Transit to LOAD state in preparation for filtering when commanded
                    * by main control state machine. */
                    GLITCH_FILT_IDLE:
                        ov_filt_state <= (state == VFD_TR_AMUX_DMA) ? GLITCH_FILT_LOAD : GLITCH_FILT_IDLE;

                    /* Load OV count for voltage being monitored. If OV is zero,
                    * increment count. Otherwise - reset. */    
                    GLITCH_FILT_LOAD:
                        ov_filt_state <= (~ov_sample) ? GLITCH_FILT_INCR : GLITCH_FILT_RESET;

                    default: ov_filt_state <= GLITCH_FILT_IDLE;
                endcase
            end
            else
            begin
                ov_filt_state <= GLITCH_FILT_IDLE;
            end
        end
        cy_psoc3_dp #(.cy_dpconfig(GLITCH_FILT_COUNT_CFG), .d0_init(GfLength)) OvFilt
        (
            /* input */          .clk(op_clk),                     
            /* input [02:00] */  .cs_addr({ov_filt_done, ov_filt_state}),    
            /* input */          .route_si(1'b0),
            /* input */          .route_ci(1'b0),
            /* input */          .f0_load(1'b0),
            /* input */          .f1_load(next_voltage),
            /* input */          .d0_load(1'b0),
            /* input */          .d1_load(1'b0),
            /* output */         .ce0(ov_filt_done),
            /* input */          .ci(chain[14]),
            /* output */         .co(),
            /* input */          .sir(chain[13]),
            /* output */         .sor(chain[12]),
            /* input */          .sil(1'b0),
            /* output */         .sol(),
            /* input */          .msbi(1'b0),
            /* output */         .msbo(chain[11]),
            /* input [01:00] */  .cei(chain[10:9]),
            /* output [01:00] */ .ceo(),
            /* input [01:00] */  .cli(chain[8:7]),
            /* output [01:00] */ .clo(),
            /* input [01:00] */  .zi(chain[6:5]),
            /* output [01:00] */ .zo(),
            /* input [01:00] */  .fi(chain[4:3]),
            /* output [01:00] */ .fo(),
            /* input [01:00] */  .capi(chain[2:1]),
            /* output [01:00] */ .capo(),
            /* input */          .cfbi(chain[0]),
            /* output */         .cfbo()                             
        );
    end
    endgenerate

endmodule

`endif /* bVoltageFaultDetector_v3_0_V_ALREADY_INCLUDED */


/* [] END OF FILE */
