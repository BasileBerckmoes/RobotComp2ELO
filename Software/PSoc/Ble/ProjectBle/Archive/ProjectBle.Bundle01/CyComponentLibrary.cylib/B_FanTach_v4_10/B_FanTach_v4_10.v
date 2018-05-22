/*******************************************************************************
*
* FILENAME:         B_FanTach_v4_10.v
* Component Name:   B_FanTach_v4_10
*
* DESCRIPTION:
*   The FanTach component is responsible for measuring the actual rotational
*   speeds of all fans in the system (up to 16) by measuring the period of the
*   fan's tachometer signal. In the event that the tachometer signal is not
*   present, stuck low or high or toggling too slowly, this component generates
*   a stall alert for the affected fan.
*
*   In closed loop control mode, the FanTach block has the additional
*   responsibility of comparing the measured speeds to system desired speeds
*   and sending control signals to the Closed Loop fan driver PWM components in
*   order to regulate fan speeds.
*
*   In order to minimize the loading on the CPU, DMA is used to transfer actual
*   fan speeds to an SRAM buffer, and fetch desired fan speeds from another SRAM
*   buffer. This autonomy allows the block to function properly without placing
*   any real-time response requirements on the CPU.
*
*   Note that the tachometer speed measurement is hard-coded to support 4-pole
*   brushless DC (BLDC) fans that output two complete pulse trains per
*   revolution of the fan. That is, two high periods plus two low period on the
*   tachometer signal equals one rotation of the fan.
*
*******************************************************************************
*                 Datapath Register Definitions 
*******************************************************************************
*
*  INSTANCE NAME:  FanTachCounter (16-bit)
*
*  DESCRIPTION:
*    This data path measures actual fan rotational speeds, compares them to
*    desired speeds and generates control signals to the ClosedLoopPWMs.
*
*  REGISTER USAGE:
*    F0 => not used
*    F1 => not used
*    D0 => Desired fan tachometer period (inversely related to desired speed)
*    D1 => Desired fan tachometer period hysteresis
*    A0 => Actual fan tachometer period
*    A1 => Fan period delta (Actual-Desired)
*
*  DATA PATH STATES:
*    0 0 0   0   IDLE: Reset tach period counter (A0<-0)
*    0 0 1   1   TACH_SYNC: Increment tach period counter, but check for Stall
*                           (A0<-A0+1)
*    0 1 0   2   TACH_CLR: Found tach edge, reset tach period counter (A0<-0)
*    0 1 1   3   TACH_CNT1: Count 1st half of tach period (A0<-A0+1)
*    1 0 0   4   TACH_CNT2: Count 2nd half of tach period (A0<-A0+1)
*    1 0 1   5   COMPARE: Calculate speed delta  (A1<-A0-D0)
*    1 1 0   6   ACTION: Reset tach period counter (A0<-0)
*    1 1 1   7   STALL: Reset tach period counter (A0<-0)
*
*
*  INSTANCE NAME:  GlitchFilterTimer (8-bit)
*
*  DESCRIPTION:
*    The primary purpose of this datapath is to perform glitch filtering of
*    tach input from currently addressed fan. Also it is used to generate 
*    divided by 20 clock for damping factor counter. This datapath uses 
*    tachometer clock divided by 2 so damping factor divider register is set to 
*    10. This datapath is not used in Manual Control mode.
*
*  REGISTER USAGE:
*    F0 => not used
*    F1 => not used
*    D0 => Glitch filter period
*    D1 => Clock divider period for damping factor counter
*    A0 => Actual glitch filter counter 
*    A1 => Actual damping factor clock divider counter
*
*  DATA PATH STATES:
*    0 0 0   0   DEC_A0: Decrement A0 and save A1
*    0 0 1   1   RELOAD_A0: Reload A0 and save A1
*    0 1 0   2   DEC_A0: Decrement A0 and reload A1
*    0 1 1   3   RELOAD_A0: Reload A0 and reload A1
*    1 0 0   4   DEC_A1: Decrement A1 and save A0
*    1 0 1   5   DEC_A1: Decrement A1, decrement A0
*    1 1 0   6   RELOAD_A1: Reload A1 and save A0
*    1 1 1   7   RELOAD_A1: Reload A1 and reload A0
*
*
*  INSTANCE NAME:  DmpgTimeCntr (8-bit)
*
*  DESCRIPTION:
*    This data path operates as a 16-bit down counter to implement Damping
*    factor functionality. This datapath uses 25kHz clock (500 kHz tachometer 
*    clock divided by 20). This datapath is not used in Manual control mode 
*    and in other modes it is only used when the control loop period selected 
*    in the customizer is not zero.
*
*  REGISTER USAGE:
*    F0 => not used
*    F1 => not used
*    D0 => Low 8-bit Damping Factor period of 16 bit counter
*    D1 => High 8-bit Damping Factor period of 16 bit counter
*    A0 => Low 8-bit of accumulator of 16 bit counter
*    A1 => High 8-bit of accumulator of 16 bit counter
*
*  DATA PATH STATES:
*    0 0 0   0   IDLE: Reset Counter (A0<-D0, A1<-D1)
*    0 0 1   1   IDLE: Reset Counter (A0<-D0, A1<-D1)
*    0 1 0   2   IDLE: Reset Counter (A0<-D0, A1<-D1)
*    0 1 1   3   IDLE: Reset Counter (A0<-D0, A1<-D1)
*    1 0 0   4   DEC_A0: Decrement A0
*    1 0 1   5   DEC_A1: Decrement A1 and reload A0
*    1 1 0   6   DEC_A0: Decrement A0
*    1 1 1   7   IDLE: Reset Counter (A0<-D0, A1<-D1)
*
********************************************************************************
*                 I*O Signals:
********************************************************************************
*    Name              Direction       Description
*    tach_clock        input           500 kHz. Support fan speeds from 1,000
*                                      -> 30,000 RPM
*    en                input           FanTach component enable
*    override          input           Signal that enabled CPU to override
*                                      Automatic fan control
*    tch[15:0]         input           Bussed tachometer inputs from fans
*    stl_mask[15:0]    input           Mask to enable/disable stall alert
*                                      monitoring for each fan
*    damping_clock     input           1 kHz clock to control damping factor of
*                                      hardware control loop
*    addr[3:0]         output          Address bus to the input tachometer mux
*                                      and ClosedLoopPWMs
*    speed_dn          output          Decrease PWM control signal to the
*                                      ClosedLoopPWMs
*    speed_up          output          Increase PWM control signal to the
*                                      ClosedLoopPWMs
*    stall[15:0]       output          Fan stall alert bit for each enabled fan
*    drq               output          DMA controller transfer request
*	 pid_int           output          Signal that triggers PID Control 
*                                      interrupt
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

`include "cypress.v"

`ifdef B_FanTach_v4_10_ALREADY_INCLUDED
`else
`define B_FanTach_v4_10_ALREADY_INCLUDED

module B_FanTach_v4_10
(
    input   wire            tach_clock,     /* 500 kHz. Support fan speeds from 1,000->30,000 RPM */
    input   wire            en,             /* FanTach component enable */
    input   wire            override,       /* Signal that enabled CPU to override hardware fan control */
    input   wire    [15:0]  tch,            /* Tachometer input */
    input   wire    [15:0]  stl_mask,       /* Mask to enable/disable stall alert monitoring for each fan */
    output  wire    [3:0]   addr,           /* Address bus to the input tachometer mux and ClosedLoopPWMs */
    output  reg             speed_dn,       /* Decrease PWM control signal to the ClosedLoopPWMs */
    output  reg             speed_up,       /* Increase PWM control signal to the ClosedLoopPWMs */
    output  wire    [15:0]  stall,          /* Fan stall alert bit for each enabled fan */
    output  wire            pid_int,        /* Signal that triggers the PID ISR */
    output  reg             drq             /* DMA controller transfer request */
);

    /**************************************************************************
    * Parameters
    **************************************************************************/
    /* Customizer Parameters */
    parameter   NumberOfFans  = 5'h0;       /* 1 through 16 supported */
    parameter   ClosedLoop    = 1'b0;       /* Closed or open loop control mode */
    parameter   DampingFactor = 7'h0;       /* Closed loop damping factor (1..127) */
    parameter   MotorType     = 1'b0;       /* Specifies the type of motor either 4-pole or six pole */
    parameter   FanModeManual = 1'b0;       /* Defines if the Controlling mode used is manual */

    localparam  FanCountPeriod = NumberOfFans - 1;

    /* FanTach Speed Counter State Machine - the state bits directly map to the
    * datapath cs_addr.
    */
    localparam IDLE             = 3'b000;     /* Reset tach period counter (A0->0) */
    localparam TACH_SYNC        = 3'b001;     /* Increment tach period counter, but check for Stall (A0->A0+1) */
    localparam TACH_CLR         = 3'b010;     /* Found tach edge, reset tach period counter (A0->0) */
    localparam TACH_CNT1        = 3'b011;     /* Count 1st half of tach period (A0->A0+1) */
    localparam TACH_CNT2        = 3'b100;     /* Count 2nd half of tach period (A0->A0+1) */
    localparam COMPARE          = 3'b101;     /* Calculate speed delta (A1=A0-D0)*/
    localparam ACTION           = 3'b110;     /* Reset tach period counter (A0->0) */
    localparam STALL            = 3'b111;     /* Reset tach period counter (A0->0) */

    /* PWM indexes */
    localparam PWM0             = 4'h0;     /* PWM #0 index */
    localparam PWM1             = 4'h1;     /* PWM #1 index */
    localparam PWM2             = 4'h2;     /* PWM #2 index */
    localparam PWM3             = 4'h3;     /* PWM #3 index */
    localparam PWM4             = 4'h4;     /* PWM #4 index */
    localparam PWM5             = 4'h5;     /* PWM #5 index */
    localparam PWM6             = 4'h6;     /* PWM #6 index */
    localparam PWM7             = 4'h7;     /* PWM #7 index */
    localparam PWM8             = 4'h8;     /* PWM #8 index */
    localparam PWM9             = 4'h9;     /* PWM #9 index */
    localparam PWM10            = 4'hA;     /* PWM #10 index */
    localparam PWM11            = 4'hB;     /* PWM #11 index */
    localparam PWM12            = 4'hC;     /* PWM #12 index */
    localparam PWM13            = 4'hD;     /* PWM #13 index */
    localparam PWM14            = 4'hE;     /* PWM #14 index */
    localparam PWM15            = 4'hF;     /* PWM #15 index */

    localparam FOUR_POLE        = 1'b0;     /* Defines four pole motors */
    localparam SIX_POLE         = 1'b1;     /* Defines six pole motors */

    localparam ACC0             = 1'b0;     /* A0 is active */
    localparam ACC1             = 1'b1;     /* A1 is active */

    localparam FILT_LOAD        = 1'b1;     /* Load state for glitch filter */
    localparam FILT_ENABLE      = 1'b0;     /* Enable state for glitch filter */

    /* PSoC 4 device family */
    localparam CY_PSOC4_FAMILY  = (`CYDEV_CHIP_FAMILY_USED == `CYDEV_CHIP_FAMILY_PSOC4);
    
    /* Parameters for Fan controlling mode identification */
    localparam IS_AUTO_HARDWARE  = (ClosedLoop == 1'b1);
    localparam IS_AUTO_FIRMWARE  = ((FanModeManual == 1'b0) && (!IS_AUTO_HARDWARE));
    localparam IS_MANUAL         = ((FanModeManual == 1'b1) && (!IS_AUTO_HARDWARE));
    
    /* Parameter for high range limit of fan addr bus */
    localparam ADDR_HI_RANGE  = (NumberOfFans < 4'd5) ? 1 : (NumberOfFans < 4'd8) ? 2 : 3;

    /**************************************************************************
    * Internal Signals
    **************************************************************************/
    genvar          i;                      /* Variable used by generate statements to instantiate arrays of logic */
    reg             rising_tach;            /* True when rising tachometer edge found */
    reg             rising_tach_d;          /* True when rising tachometer edge found (delayed by 1 clock cycle) */
    reg     [2:0]   tach_state;             /* State machine that drives the tachometer datapath */
    reg             next_fan;               /* Control signal to advance the count7 block to address the next fan */
    reg             fifo_load;              /* Loads the measured period of the specific fan to FIFO */
    reg             pulse_tc;               /* Indicates the end of speed measurement for specific fan fan */
    reg             stall_det;              /* Fan stall condition detected (tachometer counter overflow) */
    reg             reg_enable;             /* Internal signal used in damping factor logic */
    reg             glitch_filter_ld;       /* Load signal for the 7 bit glitch filter */
    reg [FanCountPeriod:0]  reg_stall;      /* Fan stall alert bit for each enabled fan */
    reg             filtered_rising_tach;   /* True when glitch filtered rising tachometer edge found */
    reg             end_of_measurement;     /* Indicates that speed measurement complete for a set of fans */
    reg             damping_factor_tc;      /* Final TC signal for DampingFactor counter */
    reg             glitch_filter_state;    /* Holds state of a simple Glitch Filer state machine used to generate 
                                            * glitch filter load signal.
                                            */
    reg             gf_dmp_state;           /* Multiplex signal that sequentially activates glitch filter or
                                            * damping factor divider counter. 
                                            */
    wire            glitch_filter_tc;       /* 7 bit glitch filter terminal count output */
    wire            synced_tach_clock;      /* Internal clock net synchronized to bus_clk */
    wire    [1:0]   co;                     /* Dp flag: co  = tach counter overflow = stall condition */
    wire    [1:0]   cl0;                    /* Dp flag: cl0 = actual tach period < desired tach period */
    wire    [1:0]   ce0;                    /* Dp flag: ce0 = actual tach period = desired tach period */
    wire    [1:0]   cl1;                    /* Dp flag: cl1 = delta(actual tach period - desired tach period)
                                            * < tolerance.
                                            */
    wire    [6:0]   fan_count;              /* Fan address generator */
    wire            fan_count_tc;           /* Fan address counter terminal count signal */
    wire            damping_cntr_tc;        /* Terminal count output from the DampingFactor counter */
    wire            damping_cntr_reload_a0; /* Terminal count for 100 ms period of damping factor counter */
    wire            enable;                 /* Enable signal for Fan Tach state machine */
    wire            div10_tc;               /* Tachometer clock divided by 10. Used as enable for damping factor
                                            * counter.
                                            */
    wire    [2:0]   damping_cntr_cs;        /* Enable signal for Fan Tach state machine */
    wire    [2:0]   glitch_filter_cntr_cs;  /* Enable signal for Fan Tach state machine */
    wire            dma_control;            /* Control Register used by DMA to generate eoc pulse */
    wire            f0_data_ready;           /* Control Register used by DMA to generate eoc pulse */
    wire            tach_data_ready;        /* Indicates that the new FAN's speed measurement data is ready in the 
                                            * FIFO.
                                            */
    reg             tach;                   /* Currently active input from tachometer mux */
    reg             sync2_tach_cnt3;        /* Signal used to replace TACH_CNT3 and SYNC2 states of tachometer SM.
                                            * The signal is used to save macrocells resources. 
                                            */
    wire    [3:0]   addrCtrl;               /* PSoC 4 only: Output lines from control register used to generate the
                                            * address for tachometer input mux.
                                            */
    wire            eom;                    /* End-Of_Measurement pulse from tachometer control register */
    
    /* Not connected */
    wire            nc1;
    wire            nc2;
    wire            nc3;
    wire            nc4;
    wire            nc5;


    /**************************************************************************
    * Clock Synchronization
    **************************************************************************/
    cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`TRUE)) ClkSync
    (
        /* input  */    .clock_in(tach_clock),
        /* input  */    .enable(en),
        /* output */    .clock_out(synced_tach_clock)
    );

    /**************************************************************************
    * Input tach signals multiplexing
    **************************************************************************/
    generate
    if(CY_PSOC4_FAMILY)
    begin: P4

        /**************************************************************************
        * Tachometer Address Control Register
        **************************************************************************/
        cy_psoc3_control #(.cy_force_order(1), .cy_ctrl_mode_1(8'h80), .cy_ctrl_mode_0(8'hfF))
        TachAddrControl(
            /* input             */     .clock(synced_tach_clock),
            /* output    [07:00] */     .control({eom,nc5,nc4,nc3,addrCtrl})
        );

        assign addr[3:0] = addrCtrl[3:0];

        if(NumberOfFans < 4'd5)
        begin
            always @(posedge synced_tach_clock)
            begin
                case(addr[ADDR_HI_RANGE:0])         /* To save resources only 2 addr bits are used */
                    PWM0: tach <= tch[PWM0];        /* Select tach signal from Fan#0 */
                    PWM1: tach <= tch[PWM1];        /* Select tach signal from Fan#1 */
                    PWM2: tach <= tch[PWM2];        /* Select tach signal from Fan#2 */
                    PWM3: tach <= tch[PWM3];        /* Select tach signal from Fan#3 */
                default:
                    tach <= tch[PWM0];
                endcase
            end
        end
        else if(NumberOfFans < 4'd9)
        begin
            always @(posedge synced_tach_clock)
            begin
                case(addr[ADDR_HI_RANGE:0])
                    PWM0: tach <= tch[PWM0];        /* Select tach signal from Fan#0 */
                    PWM1: tach <= tch[PWM1];        /* Select tach signal from Fan#1 */
                    PWM2: tach <= tch[PWM2];        /* Select tach signal from Fan#2 */
                    PWM3: tach <= tch[PWM3];        /* Select tach signal from Fan#3 */
                    PWM4: tach <= tch[PWM4];        /* Select tach signal from Fan#4 */
                    PWM5: tach <= tch[PWM5];        /* Select tach signal from Fan#5 */
                    PWM6: tach <= tch[PWM6];        /* Select tach signal from Fan#6 */
                    PWM7: tach <= tch[PWM7];        /* Select tach signal from Fan#7 */
                default:
                    tach <= tch[PWM0];
                endcase
            end
        end
        else
        begin
            always @(posedge synced_tach_clock)
            begin
                case(addr)
                    PWM0: tach <= tch[PWM0];        /* Select tach signal from Fan#0 */
                    PWM1: tach <= tch[PWM1];        /* Select tach signal from Fan#1 */
                    PWM2: tach <= tch[PWM2];        /* Select tach signal from Fan#2 */
                    PWM3: tach <= tch[PWM3];        /* Select tach signal from Fan#3 */
                    PWM4: tach <= tch[PWM4];        /* Select tach signal from Fan#4 */
                    PWM5: tach <= tch[PWM5];        /* Select tach signal from Fan#5 */
                    PWM6: tach <= tch[PWM6];        /* Select tach signal from Fan#6 */
                    PWM7: tach <= tch[PWM7];        /* Select tach signal from Fan#7 */
                    PWM8: tach <= tch[PWM8];        /* Select tach signal from Fan#8 */
                    PWM9: tach <= tch[PWM9];        /* Select tach signal from Fan#9 */
                    PWM10: tach <= tch[PWM10];      /* Select tach signal from Fan#10 */
                    PWM11: tach <= tch[PWM11];      /* Select tach signal from Fan#11 */
                    PWM12: tach <= tch[PWM12];      /* Select tach signal from Fan#12 */
                    PWM13: tach <= tch[PWM13];      /* Select tach signal from Fan#13 */
                    PWM14: tach <= tch[PWM14];      /* Select tach signal from Fan#14 */
                    PWM15: tach <= tch[PWM15];      /* Select tach signal from Fan#15 */
                default:
                    tach <= tch[PWM0];
                endcase
            end
        end
    end
    else
    begin: P3_P5
        /* PSoC 3/5LP can have up to 16 inputs */
        always @(posedge synced_tach_clock)
        begin
            case(addr)
                PWM0: tach <= tch[PWM0];        /* Select tach signal from Fan#0 */
                PWM1: tach <= tch[PWM1];        /* Select tach signal from Fan#1 */
                PWM2: tach <= tch[PWM2];        /* Select tach signal from Fan#2 */
                PWM3: tach <= tch[PWM3];        /* Select tach signal from Fan#3 */
                PWM4: tach <= tch[PWM4];        /* Select tach signal from Fan#4 */
                PWM5: tach <= tch[PWM5];        /* Select tach signal from Fan#5 */
                PWM6: tach <= tch[PWM6];        /* Select tach signal from Fan#6 */
                PWM7: tach <= tch[PWM7];        /* Select tach signal from Fan#7 */
                PWM8: tach <= tch[PWM8];        /* Select tach signal from Fan#8 */
                PWM9: tach <= tch[PWM9];        /* Select tach signal from Fan#9 */
                PWM10: tach <= tch[PWM10];      /* Select tach signal from Fan#10 */
                PWM11: tach <= tch[PWM11];      /* Select tach signal from Fan#11 */
                PWM12: tach <= tch[PWM12];      /* Select tach signal from Fan#12 */
                PWM13: tach <= tch[PWM13];      /* Select tach signal from Fan#13 */
                PWM14: tach <= tch[PWM14];      /* Select tach signal from Fan#14 */
                PWM15: tach <= tch[PWM15];      /* Select tach signal from Fan#15 */
            default:
                tach <= tch[PWM0];
            endcase
        end
        
        /**************************************************************************
        * Fan/PWM Address Bus Generation
        **************************************************************************/
        cy_psoc3_count7 #(.cy_period(FanCountPeriod), .cy_route_ld(`FALSE), .cy_route_en(`TRUE), .cy_alt_mode(`FALSE))
        FanCounter
        (
            /*  input          */  .clock(synced_tach_clock),
            /*  input          */  .reset(1'b0),
            /*  input          */  .load(1'b0),
            /*  input          */  .enable(next_fan),        /* Enabled by speed regulation control logic */
            /*  output [06:00] */  .count(fan_count),
            /*  output         */  .tc(fan_count_tc)
        );

        assign addr[3:0] = fan_count[3:0];

    end
    endgenerate
    
    /**************************************************************************
    * Damping Factor (Control Loop) Block
    *
    * Designers can control the dynamic response time of the hardware control
    * loop using the DampingFactor customizer parameter. Increasing this
    * parameter will just add delay to the fan control state machine in order
    * to prevent oscillations in the fan through over-aggressive duty cycle
    * adjustments. The fans need time to stabilize after duty cycle changes.
    **************************************************************************/
    generate
    if((!IS_MANUAL) && (DampingFactor > 0))
    begin: DmpgFactor

        /* Controls store signals for damping factor counter datapath */
        assign damping_cntr_cs[0] = damping_cntr_reload_a0;
        assign damping_cntr_cs[1] = damping_factor_tc;
        assign damping_cntr_cs[2] = div10_tc;

        cy_psoc3_dp8 #(.cy_dpconfig_a(
        {
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM0:           IDLE: Retain register values*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM1:           IDLE: Retain register values*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM2:           IDLE: Retain register values*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC___D1,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM3:           IDLE: Reset Counter (A0<-D0, A1<-D1)*/
            `CS_ALU_OP__DEC, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM4:           DEC_A0: Decrement A0*/
            `CS_ALU_OP__DEC, `CS_SRCA_A1, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC__ALU,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM5:           DEC_A1: Decrement A1 and reload A0*/
            `CS_ALU_OP__DEC, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC___D1,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM6:           DEC_A0: Decrement A0*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_A0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC___D1,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM7:           IDLE: Reset Counter (A0<-D0, A1<-D1)*/
            8'hFF, 8'h00, /*CFG9:       */
            8'hFF, 8'hFF, /*CFG11-10:       */
            `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_REGIS,
            `SC_CI_A_ARITH, `SC_C1_MASK_ENBL, `SC_C0_MASK_ENBL,
            `SC_A_MASK_ENBL, `SC_DEF_SI_0, `SC_SI_B_ROUTE,
            `SC_SI_A_ROUTE, /*CFG13-12:       */
            `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
            1'h0, `SC_FIFO1__A0, `SC_FIFO0_BUS,
            `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
            `SC_FB_NOCHN, `SC_CMP1_NOCHN,
            `SC_CMP0_NOCHN, /*CFG15-14:       */
            10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
            `SC_FIFO__EDGE,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
            `SC_WRK16CAT_DSBL  /*CFG17-16:       */
        }))
        DmpgTimeCntr
        (
            /* input */         .clk(synced_tach_clock),
            /* input [02:00] */ .cs_addr(damping_cntr_cs),
            /* input */         .route_si(1'b0),
            /* input */         .route_ci(1'b0),
            /* input */         .f0_load(1'b0),
            /* input */         .f1_load(1'b0),
            /* input */         .d0_load(1'b0),
            /* input */         .d1_load(1'b0),
            /* output */        .ce0(),
            /* output */        .cl0(),
            /* output */        .z0(damping_cntr_reload_a0),
            /* output */        .ff0(),
            /* output */        .ce1(),
            /* output */        .cl1(),
            /* output */        .z1(damping_cntr_tc),
            /* output */        .ff1(),
            /* output */        .ov_msb(),
            /* output */        .co_msb(),
            /* output */        .cmsb(),
            /* output */        .so(),
            /* output */        .f0_bus_stat(),
            /* output */        .f0_blk_stat(),
            /* output */        .f1_bus_stat(),
            /* output */        .f1_blk_stat()
        );

        always @ (posedge synced_tach_clock)
        begin
            if(CY_PSOC4_FAMILY)
            begin
                /* Condition when all fans were scanned */
                end_of_measurement <= eom;

            end
            else
            begin
                /* Condition when all fans were scanned */
                end_of_measurement <= pulse_tc & !(fan_count[3] | fan_count[2] | fan_count[1] | fan_count[0]);
            end

            /* TC signal of damping factor counter */
            damping_factor_tc <= damping_cntr_tc & damping_cntr_reload_a0 & gf_dmp_state;
        end

        /* Generate a pulse that triggers PID ISR */
        assign pid_int = damping_factor_tc;

        always@ (posedge synced_tach_clock)
        begin
            if(damping_factor_tc)
            begin            /* Starts new measurement sequence */
                reg_enable <= en;
            end
            else if(end_of_measurement)
            begin      /* Indicates that measurement sequence is complete */
                reg_enable <= 1'b0;
            end
            else begin
                /* reg_enable holds its previous state */
            end
        end

        /* Enable signal for Fan Tach state machine logic */
        assign enable = reg_enable;
    end
    else
    begin
    
        /* Enable signal for Fan Tach state machine logic */
        assign enable = en;

        /* No PID interrupt for "Manual" or "HW" mode */
        assign pid_int = 1'b0;
    end
    endgenerate

    /**************************************************************************
    * Glitch Filtering of Tach inputs
    **************************************************************************/
    /* State Machine Transitions */
    always @ (posedge synced_tach_clock)
    begin
        case (gf_dmp_state)

            ACC0:                       /* A0 of GlitchFilterTimer is active */
                if (en)
                begin
                    gf_dmp_state <= ACC1;
                end

            ACC1:                       /* A1 of GlitchFilterTimer is active */
                gf_dmp_state <= ACC0;

            default:
                gf_dmp_state <=ACC0;

        endcase
    end
    
    /* Glitch Filter control State Machine */
    /* This SM is used to generate load signal for Glitch Filter(down counter).
    * The glitch_filter_state is ORed with ~tach to get desirable load signal.
    */
    always @ (posedge synced_tach_clock)
    begin
        case (glitch_filter_state)

            FILT_ENABLE:                           /* Glitch filter is enabled so wait for terminal count */
                begin
                    if (glitch_filter_tc)
                    begin
                        glitch_filter_state <= FILT_LOAD;    /* TC occurred so change the state */
                    end
                end
                
            FILT_LOAD:
                begin
                    if (~tach)
                    begin
                        glitch_filter_state <= FILT_ENABLE;
                    end
                end

            default:
                begin
                    glitch_filter_state <= FILT_ENABLE;
                end
        endcase
    end
    
    always @ (posedge synced_tach_clock)
    begin
        /* Load signal for Glitch Filter */
        glitch_filter_ld <= glitch_filter_state | ~tach;
        /* glitch_filter_tc has duration of 2 tach clock cycles because it 
        * is multiplexed with damping factor(control loop period), so need to cut 
        * one extra cycle.
        */
        filtered_rising_tach <= glitch_filter_tc & glitch_filter_state;
        
    end

    /* Performs glitch filtering on rising edge of tachometer input using a
    * counter implemented in datapath. Also implements a divided for 10
    * for damping factor counter.
    */
    assign glitch_filter_cntr_cs[0] = glitch_filter_ld;
    assign glitch_filter_cntr_cs[1] = div10_tc;
    assign glitch_filter_cntr_cs[2] = gf_dmp_state;

    cy_psoc3_dp8 #(.cy_dpconfig_a(
    {
        `CS_ALU_OP__DEC, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM0:         DEC_A0: Decrement A0 and save A1*/
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM1:         RELOAD_A0: Reload A0 and save A1*/
        `CS_ALU_OP__DEC, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC___D1,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM2:         DEC_A0: Decrement A0 and reload A1*/
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC___D1,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM3:         RELOAD_A0: Reload A0 and reload A1*/
        `CS_ALU_OP__DEC, `CS_SRCA_A1, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM4:         DEC_A1: Decrement A1 and save A0*/
        `CS_ALU_OP__DEC, `CS_SRCA_A1, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC__ALU,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM5:         DEC_A1: Decrement A1, decrement A0*/
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC___D1,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM6:         RELOAD_A1: Reload A1 and save A0*/
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_A0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC___D1,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM7:         RELOAD_A1: Reload A1 and reload A0*/
        8'hFF, 8'h00, /*CFG9:     */
        8'hFF, 8'hFF, /*CFG11-10:     */
        `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_REGIS,
        `SC_CI_A_ARITH, `SC_C1_MASK_ENBL, `SC_C0_MASK_ENBL,
        `SC_A_MASK_ENBL, `SC_DEF_SI_0, `SC_SI_B_ROUTE,
        `SC_SI_A_ROUTE, /*CFG13-12:     */
        `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
        1'h0, `SC_FIFO1__A0, `SC_FIFO0_BUS,
        `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
        `SC_FB_NOCHN, `SC_CMP1_NOCHN,
        `SC_CMP0_NOCHN, /*CFG15-14:     */
        10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
        `SC_FIFO__EDGE,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
        `SC_WRK16CAT_DSBL  /*CFG17-16:     */
    }))
    GlitchFilterTimer
    (
        /* input */         .clk(synced_tach_clock),
        /* input [02:00] */ .cs_addr(glitch_filter_cntr_cs),
        /* input */         .route_si(1'b0),
        /* input */         .route_ci(1'b0),
        /* input */         .f0_load(1'b0),
        /* input */         .f1_load(1'b0),
        /* input */         .d0_load(1'b0),
        /* input */         .d1_load(1'b0),
        /* output */        .ce0(),
        /* output */        .cl0(),
        /* output */        .z0(glitch_filter_tc),
        /* output */        .ff0(),
        /* output */        .ce1(),
        /* output */        .cl1(),
        /* output */        .z1(div10_tc),
        /* output */        .ff1(),
        /* output */        .ov_msb(),
        /* output */        .co_msb(),
        /* output */        .cmsb(),
        /* output */        .so(),
        /* output */        .f0_bus_stat(),
        /* output */        .f0_blk_stat(),
        /* output */        .f1_bus_stat(),
        /* output */        .f1_blk_stat()
    );

    /**************************************************************************
    * Tachometer State Machine
    **************************************************************************/
    generate
    if(MotorType == FOUR_POLE)
    begin
        /* State Machine Transitions */
        always @ (posedge synced_tach_clock)
        begin
            case (tach_state)
                IDLE:                       /* Reset entry. Clear tach counter */
                    begin
                        if (enable & ~tach_data_ready)
                        begin
                            tach_state <= TACH_SYNC;
                            sync2_tach_cnt3 <= 1'b0;      /* Clear sync2_tach_cnt3 prior to next measurement cycle */
                        end
                    end 
                TACH_SYNC:                  /* Ignore 1st rising edge as tach input switches. Stall if we timeout */
					if (filtered_rising_tach)
                    begin
                        if (sync2_tach_cnt3)
                        begin
                            tach_state <= TACH_CLR;
                        end
                        else
                        begin
                            sync2_tach_cnt3 <= 1'b1;  /* sync2_tach_cnt3 is used to emulate TACH_SYNC2 state. The 
                                                      * separate state was not used for synchronization to 
                                                      * save UDB resources.
                                                      */
                        end
                    end
                    else if (co[1])
                    begin
                        tach_state <= STALL;
                    end

                TACH_CLR:                       /* Got 1st rising edge. Reset counter to start actual measurement */
                    begin
                        tach_state <= TACH_CNT1;
                    end
                TACH_CNT1:                      /* Measure first tach pulse. Stall if we timeout */
                    if (filtered_rising_tach)
                    begin
                        tach_state <= TACH_CNT2;
                    end
                    else if (co[1])
                    begin
                        tach_state <= STALL;
                    end

                TACH_CNT2:                      /* Measure 2nd tach pulse. Stall if we timeout */
                    if (filtered_rising_tach)
                    begin
                        tach_state <= COMPARE;
                    end
                    else if (co[1])
                    begin
                        tach_state <= STALL;
                    end

                COMPARE:                        /* Compare desired period to actual period using the datapath */
                    begin
                        tach_state <= ACTION;
                    end

                ACTION:                         /* Take action depending on compare result */
                    begin
                        tach_state <= IDLE;
                    end

                STALL:                          /* Stall condition detected */
                    if(CY_PSOC4_FAMILY)
                    begin
                        tach_state <= ACTION;
                    end
                    else
                    begin
                        tach_state <= IDLE;
                    end

                default:
                    tach_state <= IDLE;
            endcase
        end
    end
    else begin
         /* State Machine Transitions */
        always @ (posedge synced_tach_clock)
        begin
            case (tach_state)

                IDLE:                       /* Reset entry. Clear tach counter */
                    begin
                        if (enable & ~tach_data_ready)
                        begin
                            tach_state <= TACH_SYNC;
                            sync2_tach_cnt3 <= 1'b0;      /* Clear sync2_tach_cnt3 prior to next measurement cycle */
                        end
                    end

                TACH_SYNC:                  /* Ignore 1st rising edge as tach input switches. Stall if we timeout */
                    if (filtered_rising_tach)
                    begin
                        if (sync2_tach_cnt3)
                        begin
                            tach_state <= TACH_CLR;
                        end
                        else
                        begin
                            sync2_tach_cnt3 <= 1'b1;  /* sync2_tach_cnt3 is used to emulate TACH_SYNC2 state. The 
                                                      * separate state was not used for synchronization to 
                                                      * save UDB resources.
                                                      */
                        end
                    end
                    else if (co[1])
                    begin
                        tach_state <= STALL;
                    end

                TACH_CLR:                       /* Got 1st rising edge. Reset counter to start actual measurement */
                    begin
                        tach_state <= TACH_CNT1;
                        sync2_tach_cnt3 <= 1'b0;      /* Clear sync2_tach_cnt3 prior to next measurement cycle */
                    end

                TACH_CNT1:                      /* Measure first tach pulse. Stall if we timeout */
                    if (filtered_rising_tach)
                    begin
                        tach_state <= TACH_CNT2;
                    end
                    else if (co[1])
                    begin
                        tach_state <= STALL;
                    end

                TACH_CNT2:                      /* Measure 2nd and 3rd tach pulses. Stall if we timeout */
                    if (filtered_rising_tach)
                    begin
                        if (sync2_tach_cnt3)
                        begin
                            tach_state <= COMPARE;
                        end
                        else
                        begin
                            sync2_tach_cnt3 <= 1'b1;  /* sync2_tach_cnt3 is used to emulate TACH_CNT3 state. The 
                                                * separate state was not used for counting third tachometer pulse to 
                                                * save UDB resources.
                                                */
                        end
                    end
                    else if (co[1])
                    begin
                        tach_state <= STALL;
                    end

                COMPARE:                        /* Compare desired period to actual period using the datapath */
                    begin
                        tach_state <= ACTION;
                    end

                ACTION:                         /* Take action depending on compare result */
                    begin
                        tach_state <= IDLE;
                    end

                STALL:                          /* Stall condition detected */
                    if(CY_PSOC4_FAMILY)
                    begin
                        tach_state <= ACTION;
                    end
                    else
                    begin
                        tach_state <= IDLE;
                    end

                default:
                    begin
                        tach_state <= IDLE;
                    end
            endcase
        end

    end
    endgenerate

    /**************************************************************************
    * Speed Regulation Control Logic
    **************************************************************************/
    generate
    if (CY_PSOC4_FAMILY)
    begin
        always @ (posedge synced_tach_clock)
        begin
            stall_det <= (tach_state == STALL);
            fifo_load <= (tach_state == STALL) | (tach_state == COMPARE);
            drq       <= tach_data_ready;
        end
        
        assign tach_data_ready = f0_data_ready;
    end

    else
    begin
        always @ (posedge synced_tach_clock)
        begin
            drq  <= (tach_state == STALL) | (tach_state == COMPARE);
            fifo_load  <= 1'b0;

            /* Valid tach measurement taken, decide what to do */
            if (tach_state == ACTION)
            begin
                stall_det <= 1'b0;                  /* Valid tach measurement, no stall */
                pulse_tc <= 1'b0;                   /* Set pulse_tc, that was risen on previous state, to low */
                next_fan <= 1'b1;                   /* Change the address to the next fan using the count7 */
                if (IS_AUTO_HARDWARE)
                begin
                    if (cl1[1])                     /* If delta (actual period - desired period) < tolerance */
                    begin                           /* Then regulation achieved -> do nothing */
                    end
                    else if (~(cl0[1] | ce0[1]))    /* Else if actual period >= desired period */
                    begin
                        speed_up <= ~override;      /* Then speed up (to reduce the actual period) */
                    end
                    else if (~cl1[1])               /* Else if delta (actual period - desired period) >= tolerance
                                                    * (includes delta is negative).
                                                    */
                    begin
                        speed_dn <= ~override;      /* Then slow down (to increase the actual period) */
                    end
                end
            end

            /* Tach measurement timed out -> stall condition */
            else if (tach_state == STALL)
            begin
                stall_det <= 1'b1;                  /* Flag the stall condition */
                next_fan  <= 1'b1;                  /* Change the address to the next fan */
                if (IS_AUTO_HARDWARE)
                begin
                    speed_up  <= ~override;         /* Tell PWM to speed up to attempt recovery or re-start */
                end
            end

            /* State != ACTION and != STALL so do nothing */
            else if (tach_state == COMPARE)
            begin
                pulse_tc <= 1'b1;                   /* Indicate the speed measurement completion */
            end
            else
            begin
                stall_det <= 1'b0;                  /* Valid tach measurement, no stall */
                next_fan  <= 1'b0;                  /* next_fan pulse is generated, set it low */
                speed_dn  <= 1'b0;                  /* speed_dn pulse is generated, set it low */
                speed_up  <= 1'b0;                  /* speed_up pulse is generated, set it low */
                pulse_tc  <= 1'b0;                  /* pulse_tc pulse is generated, set it low */
            end
        end
        
        assign tach_data_ready = 1'b0;
    end
    endgenerate

    /* Generate stall alert if enabled */
    generate
    if (CY_PSOC4_FAMILY)
    begin
        /* For PSoC 4 stall alert are generated in SW so set the tachometer stall 
        * outputs to all zeroes.
        */        
        assign stall[PWM15:0] = 16'h00;
    end
    else
    begin 
        for(i = 0; i < NumberOfFans; i = i + 1)
        begin
            always @ (posedge synced_tach_clock)
            begin
                if (i == addr[ADDR_HI_RANGE:0]) /* To optimize PLD inputs only 2 addr signals are used */
                begin
                    /* Sticky event latching done in external status registers */
                    reg_stall[i] <= (stall_det & stl_mask[i]);
                end
            end
        end

        /**************************************************************************
        * Handle stall[15..0] output assignment
        **************************************************************************/
        if(NumberOfFans < 4'd1)
        begin
            assign stall[PWM0] = 1'b0;
        end
        else
        begin
            assign stall[PWM0] = reg_stall[PWM0];
        end

        if(NumberOfFans < 4'd2)
        begin
            assign stall[PWM1] = 1'b0;
        end
        else
        begin
            assign stall[PWM1] = reg_stall[PWM1];
        end

        if(NumberOfFans < 4'd3)
        begin
            assign stall[PWM2] = 1'b0;
        end
        else
        begin
            assign stall[PWM2] = reg_stall[PWM2];
        end

        if(NumberOfFans < 4'd4)
        begin
            assign stall[PWM3] = 1'b0;
        end
        else
        begin
            assign stall[PWM3] = reg_stall[PWM3];
        end

        if(NumberOfFans < 4'd5)
        begin
            assign stall[PWM4] = 1'b0;
        end
        else
        begin
            assign stall[PWM4] = reg_stall[PWM4];
        end

        if(NumberOfFans < 4'd6)
        begin
            assign stall[PWM5] = 1'b0;
        end
        else
        begin
            assign stall[PWM5] = reg_stall[PWM5];
        end

        if(NumberOfFans < 4'd7)
        begin
            assign stall[PWM6] = 1'b0;
        end
        else
        begin
            assign stall[PWM6] = reg_stall[PWM6];
        end

        if(NumberOfFans < 4'd8)
        begin
            assign stall[PWM7] = 1'b0;
        end
        else
        begin
            assign stall[PWM7] = reg_stall[PWM7];
        end

        if(NumberOfFans < 4'd9)
        begin
            assign stall[PWM8] = 1'b0;
        end
        else
        begin
            assign stall[PWM8] = reg_stall[PWM8];
        end

        if(NumberOfFans < 4'd10)
        begin
            assign stall[PWM9] = 1'b0;
        end
        else
        begin
            assign stall[PWM9] = reg_stall[PWM9];
        end

        if(NumberOfFans < 4'd11)
        begin
            assign stall[PWM10] = 1'b0;
        end
        else
        begin
            assign stall[PWM10] = reg_stall[PWM10];
        end

        if(NumberOfFans < 4'd12)
        begin
            assign stall[PWM11] = 1'b0;
        end
        else
        begin
            assign stall[PWM11] = reg_stall[PWM11];
        end

        if(NumberOfFans < 4'd13)
        begin
            assign stall[PWM12] = 1'b0;
        end
        else
        begin
            assign stall[PWM12] = reg_stall[PWM12];
        end

        if(NumberOfFans < 4'd14)
        begin
            assign stall[PWM13] = 1'b0;
        end
        else
        begin
            assign stall[PWM13] = reg_stall[PWM13];
        end

        if(NumberOfFans < 4'd15)
        begin
            assign stall[PWM14] = 1'b0;
        end
        else
        begin
            assign stall[PWM14] = reg_stall[PWM14];
        end

        if(NumberOfFans < 5'd16)
        begin
            assign stall[PWM15] = 1'b0;
        end
        else
        begin
            assign stall[PWM15] = reg_stall[PWM15];
        end
    end
    endgenerate

    /**************************************************************************
    * Tachometer Speed Measurement Datapath
    **************************************************************************/
    cy_psoc3_dp16 #(.cy_dpconfig_a(
    {
        `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM0:           IDLE: Reset Counter*/
        `CS_ALU_OP__INC, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM1:           TACH_SYNC: Check for Stall*/
        `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM2:           TACH_CLR: Reset Counter*/
        `CS_ALU_OP__INC, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM3:           TACH_CNT1: Count 1st Half of Tach Period*/
        `CS_ALU_OP__INC, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM4:           TACH_CNT2: Count 2nd Half of Tach Period*/
        `CS_ALU_OP__SUB, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM5:           COMPARE: A1=A0-D0*/
        `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM6:           ACTION: Reset Counter*/
        `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM7:           STALL: Reset Counter*/
        8'hFF, 8'h00,  /*CFG9:          */
        8'hFF, 8'hFF,  /*CFG11-10:          */
        `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
        `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
        `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
        `SC_SI_A_DEFSI, /*CFG13-12:          */
        `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
        1'h0, `SC_FIFO1_BUS, `SC_FIFO0__A0,
        `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
        `SC_FB_NOCHN, `SC_CMP1_NOCHN,
        `SC_CMP0_NOCHN, /*CFG15-14:          */
        10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
        `SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
        `SC_WRK16CAT_DSBL /*CFG17-16:          */
    }
    ), .cy_dpconfig_b(
    {
        `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM0:           IDLE: Reset Counter*/
        `CS_ALU_OP__INC, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM1:           TACH_SYNC: Check for Stall*/
        `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM2:           TACH_CLR: Reset Counter*/
        `CS_ALU_OP__INC, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM3:           TACH_CNT1: Count 1st Half of Tach Period*/
        `CS_ALU_OP__INC, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM4:           TACH_CNT2: Count 2nd Half of Tach Period*/
        `CS_ALU_OP__SUB, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM5:           COMPARE: A1=A0-D0*/
        `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM6:           ACTION: Reset Counter*/
        `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM7:           STALL: Reset Counter*/
        8'hFF, 8'h00,  /*CFG9:          */
        8'hFF, 8'hFF,  /*CFG11-10:          */
        `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_CHAIN,
        `SC_CI_A_CHAIN, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
        `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_CHAIN,
        `SC_SI_A_CHAIN, /*CFG13-12:          */
        `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
        1'h0, `SC_FIFO1_BUS, `SC_FIFO0__A0,
        `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_CHNED,
        `SC_FB_CHNED, `SC_CMP1_CHNED,
        `SC_CMP0_CHNED, /*CFG15-14:          */
        10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
        `SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
        `SC_WRK16CAT_DSBL /*CFG17-16:          */
    }
    )) FanTachCounter
    (
            /*  input                   */  .reset(1'b0),
            /*  input                   */  .clk(synced_tach_clock),
            /*  input   [02:00]         */  .cs_addr(tach_state[2:0]),
            /*  input                   */  .route_si(1'b0),
            /*  input                   */  .route_ci(1'b0),
            /*  input                   */  .f0_load(fifo_load),
            /*  input                   */  .f1_load(1'b0),
            /*  input                   */  .d0_load(1'b0),
            /*  input                   */  .d1_load(1'b0),
            /*  output  [01:00]         */  .ce0(ce0),          /* Actual Period == Desired Period */
            /*  output  [01:00]         */  .cl0(cl0),          /* Actual Period  < Desired Period */
            /*  output  [01:00]         */  .z0(),
            /*  output  [01:00]         */  .ff0(),
            /*  output  [01:00]         */  .ce1(),
            /*  output  [01:00]         */  .cl1(cl1),          /* Delta (Actual Period - Desired Period) < Tolerance */
            /*  output  [01:00]         */  .z1(),
            /*  output  [01:00]         */  .ff1(),
            /*  output  [01:00]         */  .ov_msb(),
            /*  output  [01:00]         */  .co_msb(co),        /* Period measurement timed out */
            /*  output  [01:00]         */  .cmsb(),
            /*  output  [01:00]         */  .so(),
            /*  output  [01:00]         */  .f0_bus_stat(f0_data_ready),
            /*  output  [01:00]         */  .f0_blk_stat(),
            /*  output  [01:00]         */  .f1_bus_stat(),
            /*  output  [01:00]         */  .f1_blk_stat()
    );
endmodule
`endif /* B_FanTach_v4_10_ALREADY_INCLUDED */

