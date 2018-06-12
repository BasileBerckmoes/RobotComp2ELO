/*******************************************************************************
* File Name: bI2S_v2_70.v
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
* The I2S module is inter-IC sound interface implementation done with UDBs. It 
* operates as a bus master in both directions, Rx and Tx respectively. The I2S
* module has a setable word select period, data resolution, supports Interrupts
* and DMA operations.
*
*------------------------------------------------------------------------------
*                 Control and Status Register definitions
*------------------------------------------------------------------------------
*
*  Control Register
*  +=====+-------+-------+-------+--------+--------+-------+--------+--------+
*  | Bit |   7   |   6   |   5   |   4    |   3    |   2   |   1    |   0    |
*  +=====+-------+-------+-------+--------+--------+-------+--------+--------+
*  |Desc |        NA:000         | data bits mode  |enable |rxenable|txenable| 
*  +=====+-------+-------+-------+--------+--------+-------+--------+--------+
*
*   Bits   Name             Description
*   4:3    data bits mode   Selects data bits per audio channel
*                            00 - 8-bit data
*                            01 - 16-bit data
*                            10 - 24-bit data
*                            11 - 32-bit data
*   2      enable           ws and sck enable
*                            0 - disable
*                            1 - enable        
*   1      rxenable         Rx direction enable
*                            0 - disable
*                            1 - enable
*   0      txenable         Tx direction enable
*                            0 - disable
*                            1 - enable
*    
*  Tx Interrupt Status Registers
*
*   STS0_1, STS2_3
*  +=======+--------+--------+---------+---------+-------+---------+---------+-------+
*  |  Bit  |   7    |   6    |    5    |    4    |   3   |    2    |    1    |   0   |
*  +=======+--------+--------+---------+---------+-------+---------+---------+-------+
*  | Desc  |  intr  |  NA:0  |f1_n_full|f0_n_full| under |f1_n_full|f0_n_full| under |
*  +=======+--------+--------+---------+---------+-------+---------+---------+-------+
*
*   STS4
*  +=======+--------+--------+---------+---------+-------+---------+---------+-------+
*  |  Bit  |   7    |   6    |    5    |    4    |   3   |    2    |    1    |   0   |
*  +=======+--------+--------+---------+---------+-------+---------+---------+-------+
*  | Desc  |  intr  |               NA:0000              |f1_n_full|f0_n_full| under |
*  +=======+--------+--------+---------+---------+-------+---------+---------+-------+
*
*  The bit fields are the same for STS0_1 and STS2_3 registers but corresponds to
*  different stereo channels, i.e. STS0_1 correspond to channels 0 and 1, STS2_3
*  to channels 2 and 3. STS4 corresponds to stereo channel 4.
*  The description below is for stereo channels 0 and 1.
*
*   Bits   Name             Description
*   7      intr             Interrupt
*   5      f1_n_full        Stereo channel 1 FIFO 1 not full 
*   4      f0_n_full        Stereo channel 1 FIFO 0 not full
*   3      under            Stereo channel 1 FIFOs underflow (common for FIFO 0 and FIFO 1)
*   2      f1_n_full        Stereo channel 0 FIFO 1 not full
*   1      f0_n_full        Stereo channel 0 FIFO 0 not full
*   0      under            Stereo channel 0 FIFOs underflow (common for FIFO 0 and FIFO 1)
*
*  Rx Interrupt Status Register Definition
*
*   STS0_1, STS2_3
*  +=======+--------+--------+---------+---------+-------+---------+---------+-------+
*  |  Bit  |   7    |   6    |    5    |    4    |   3   |    2    |    1    |   0   |
*  +=======+--------+--------+---------+---------+-------+---------+---------+-------+
*  | Desc  |  intr  |  NA:0  |f1_n_empt|f0_n_empt|  over |f1_n_empt|f0_n_empt| over  |
*  +=======+--------+--------+---------+---------+-------+---------+---------+-------+
*
*   STS4
*  +=======+--------+--------+---------+---------+-------+---------+---------+-------+
*  |  Bit  |   7    |   6    |    5    |    4    |   3   |    2    |    1    |   0   |
*  +=======+--------+--------+---------+---------+-------+---------+---------+-------+
*  | Desc  |  intr  |               NA:0000              |f1_n_empt|f0_n_empt| over  |
*  +=======+--------+--------+---------+---------+-------+---------+---------+-------+
*
*  The bit fields are the same for STS0_1 and STS2_3 registers but corresponds to
*  different stereo channels, i.e. STS0_1 correspond to channels 0 and 1, STS2_3
*  to channels 2 and 3. STS4 corresponds to stereo channel 4.
*  The description below is for stereo channels 0 and 1.
*  
*   Bits   Name             Description
*   7      intr             Interrupt
*   5      f1_n_empt        Stereo channel 1 FIFO 1 not empty
*   4      f0_n_empt        Stereo channel 1 FIFO 0 not empty
*   3      over             Stereo channel 1 FIFOs overflow (common for FIFO 0 and FIFO 1)
*   2      f1_n_empt        Stereo channel 0 FIFO 1 not empty
*   1      f0_n_empt        Stereo channel 0 FIFO 0 not empty
*   0      over             Stereo channel 0 FIFOs overflow (common for FIFO 0 and FIFO 1)
*
********************************************************************************
* Data Path register definitions
********************************************************************************
* I2S: dpTx
* DESCRIPTION: dpTx is used to implement the Tx direction of the I2S component
* REGISTER USAGE:
* F0 => Left channel FIFO
* F1 => Right channel FIFO for separate data stream
* D0 => Intermediate register for byte swapping
* D1 => Not used
* A0 => Shift register for data transition
* A1 => Intermediate register for data load from F1 and byte swapping
*
********************************************************************************
* I2S: dpRx
* DESCRIPTION:
* REGISTER USAGE: dpRx is used to implement the Rx direction of the I2S component 
* F0 => Left channel FIFO
* F1 => Right channel FIFO for separate data stream. 
*       Intermediate register for byte swapping.
* D0 => Positive clipping threshold
* D1 => Negative clipping threshold
* A0 => Shift register for data receiving
* A1 => Intermediate register for byte swapping
*
********************************************************************************
* I*O Signals:
********************************************************************************
*    name              direction       Description
*    sck               output          I2S clock line                      
*    sdo               output          I2S output data line                
*    ws                output          I2S word select line                
*    sdi               input           I2S input data line                 
*    clock             input           System clock                        
*    rx_dma0           output          Rx direction DMA request for FIFO 0 
*    rx_dma1           output          Rx direction DMA request for FIFO 1 
*    rx_interrupt      output          Rx direction interrupt              
*    tx_dma0           output          Tx direction DMA request for FIFO 0 
*    tx_dma1           output          Tx direction DMA request for FIFO 1 
*    tx_interrupt      output          Tx direction interrupt  
*    clip              output          Rx clip detection 
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

`include "cypress.v"
`ifdef bI2S_v2_70_V_ALREADY_INCLUDED
`else
`define bI2S_v2_70_V_ALREADY_INCLUDED

module bI2S_v2_70 (
    output  wire       sck,           /* I2S clock line                      */
    output  reg  [4:0] sdo,           /* I2S output data line                */
    output  wire       ws,            /* I2S word select line                */
    input   wire [4:0] sdi,           /* I2S input data line                 */
    input   wire       clock,         /* System clock                        */
    output  wire [4:0] rx_dma0,       /* Rx direction DMA request for FIFO 0 */
    output  wire [4:0] rx_dma1,       /* Rx direction DMA request for FIFO 1 */
    output  wire       rx_interrupt,  /* Rx direction interrupt              */
    output  wire [4:0] tx_dma0,       /* Tx direction DMA request for FIFO 0 */
    output  wire [4:0] tx_dma1,       /* Tx direction DMA request for FIFO 1 */
    output  wire       tx_interrupt , /* Tx direction interrupt              */
    output  reg  [4:0] clip           /* Rx clip detection                   */
);

    /***************************************************************************
    *              Parameters                                                
    ***************************************************************************/
    localparam [1:0] RX_PRESENT        = 2'd1;
    localparam [1:0] TX_PRESENT        = 2'd2;
    localparam [1:0] RX_AND_TX_PRESENT = 2'd3;
        
    localparam [6:0] WORD_SEL16     = 7'd16;
    localparam [6:0] WORD_SEL32     = 7'd32;
    localparam [6:0] WORD_SEL48     = 7'd48;
    localparam [6:0] WORD_SEL64     = 7'd64;

    localparam [2:0] MONO_LEFT      = 3'd0;
    localparam [2:0] MONO_RIGHT     = 3'd1;
    localparam [2:0] MAX_I2S_LINES  = 3'd5;

    /* Common settings */
    parameter StaticBitResolution   = 1'b1;
    parameter [6:0] WordSelect      = WORD_SEL64;
    parameter [5:0] DataBits        = 6'd24;
    parameter [1:0] Direction       = RX_AND_TX_PRESENT;

    localparam TxDirectionPresent = (Direction != RX_PRESENT); 
    localparam RxDirectionPresent = (Direction != TX_PRESENT);

    /* Input clock synchronization */
    localparam CLOCK_SYNC           = 1'b1;
    localparam CLOCK_ASYNC          = 1'b0;
    parameter  ClockSyncMode        = CLOCK_SYNC;

    /* Rx settings */
    parameter [3:0] NumRxChannels   = 4'd2;
    parameter RxDataInterleaving    = 1'b1;
    parameter EnableRxByteSwap      = 1'b0;
    parameter EnableClipDetect      = 1'b0;
    
    /* Tx settings */
    parameter [3:0] NumTxChannels   = 4'd2;
    parameter TxDataInterleaving    = 1'b1;
    parameter EnableTxByteSwap      = 1'b0;

    genvar i;

    /***************************************************************************
    * MSB and LSB position definition. MSB and LSB determine unused bits for
    * each direction. Any unused bits will be ignored by Rx and zero on Tx. 
    ***************************************************************************/
    localparam [5:0] ChannelResolution   = WordSelect >> 1;
    localparam [5:0] I2SBitCounterPeriod = WordSelect -  1;

    localparam [5:0] MsbLeft  = I2SBitCounterPeriod - 1;
    localparam [5:0] LsbLeft  = I2SBitCounterPeriod - DataBits;
    localparam [5:0] MsbRight = MsbLeft - ChannelResolution;
    localparam [5:0] LsbRight = LsbLeft - ChannelResolution;

    /***************************************************************************
    *         Instantiation of udb_clock_enable  
    ****************************************************************************
    * The udb_clock_enable primitive component allows supporting the clock enable
    * mechanism and specify the intended synchronization behaviour for the clock 
    * result (operational clock).
    */
    wire op_clk;    /* operational clock */
    
    cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(ClockSyncMode)) ClkSync
    (
        /* input  */    .clock_in(clock),
        /* input  */    .enable(1'b1),
        /* output */    .clock_out(op_clk)
    );     

    /* Depending on how the local component clock is related to the system clock,
    * the FIFO block status is either re-sampled to the local clock (clocks are
    * synchronous) or double synced to the local clock (local clock is async to
    * the system clock).
    */
    localparam FIFO_STS_SYNC = (ClockSyncMode == CLOCK_SYNC) ? `SC_FIFO_SYNC_NONE : `SC_FIFO_SYNC__ADD;

    /***************************************************************************
    *       Control Register Implementation                                      
    ***************************************************************************/   

    /* Control Register bit location */
    localparam [2:0] I2S_CTRL_TX_ENABLE = 3'd0;
    localparam [2:0] I2S_CTRL_RX_ENABLE = 3'd1;
    localparam [2:0] I2S_CTRL_ENABLE    = 3'd2;

    wire [7:0] ctrl_reg_out;
    wire [2:0] ctrl;

    cy_psoc3_control #(.cy_force_order(1), .cy_ctrl_mode_1(8'h00), .cy_ctrl_mode_0(8'h1F)) CtlReg
    (
        /*  input         */  .clock(op_clk),
        /* output [07:00] */  .control(ctrl_reg_out)
    );

    /* Double sync enable signal to the component clock when the I2S is
    * configured for asynchronous operation with respect to the system clock.
    */
    generate
    if(ClockSyncMode == CLOCK_ASYNC)
    begin:EN_ASYNC
        cy_psoc3_sync CtlEnSync
        (
            /* input  */ .clock(op_clk),
            /* input  */ .sc_in(ctrl_reg_out[I2S_CTRL_ENABLE]),
            /* output */ .sc_out(ctrl[I2S_CTRL_ENABLE])
        );
    end
    else
    begin:EN_SYNC
        assign ctrl[I2S_CTRL_ENABLE] = ctrl_reg_out[I2S_CTRL_ENABLE];
    end
    endgenerate

    /* When dynamic bit resolution is enabled, bits [4:3] specify the
    * number of bits in each data sample. The bits can only be changed
    * when the component is stopped. This eliminates the safety issues
    * related to the clock crossings, so no additional synchronizers
    * are used.
    */
    wire [1:0] dyn_data_width = ctrl_reg_out[4:3];

    localparam [1:0] I2S_8BIT_CH   = 2'b00;
    localparam [1:0] I2S_16BIT_CH  = 2'b01;
    localparam [1:0] I2S_24BIT_CH  = 2'b10;
    localparam [1:0] I2S_32BIT_CH  = 2'b11;

    /* Reset and enable control signals. Reset is one clock delayed from
    * the enable to suppress one cycle logic high pulse on ws signal after
    * counter start.
    */
    wire enable = ctrl[I2S_CTRL_ENABLE];
    reg reset;
    always @(posedge op_clk)
    begin
        reset <= ~ctrl[I2S_CTRL_ENABLE];
    end

    /***************************************************************************
    *       7-bit down counter is used for bit counting                                     
    ***************************************************************************/
    wire [6:0]  count;
    cy_psoc3_count7 #(.cy_period({I2SBitCounterPeriod,1'b1}), .cy_route_en(1)) BitCounter
    (
        /*  input             */  .clock(op_clk),
        /*  input             */  .reset(1'b0),
        /*  input             */  .load(1'b0),
        /*  input             */  .enable(enable),
        /*  output  [06:00]   */  .count(count),
        /*  output            */  .tc()
    );

    /***************************************************************************
    * The channel bit is used to distinguish the LEFT or RIGHT channel will be
    * loaded. Then in conjunction with TxDataInterleaving parameter value it
    * defines which FIFO is the source for each channel. 
    ***************************************************************************/
    reg channel;
    always @(posedge op_clk)
        if(reset)
        begin
            channel <= 1'b0;
        end
        else
        begin
            case(WordSelect)
                WORD_SEL16: channel <= ~count[4];
                WORD_SEL32: channel <= ~count[5];
                WORD_SEL48: channel <= ~(count[6] | count[5] & count[4]);
                WORD_SEL64: channel <= ~count[6];
            default: channel <= ~count[6]; /* WS = 64 bits by default */
            endcase
        end

    assign sck = count[0]; /* Output data clock */
    assign ws = channel;   /* Word Select Output Generation */

    /***************************************************************************
    * Each I2S data line can support one stereo channel data (i.e. two audio
    * outputs, left and right) or one mono channel data (i.e. one audio output,
    * left or right.
    ***************************************************************************/
    localparam [2:0] NumRxLines = (NumRxChannels <= 4'd1) ? 3'd1 : NumRxChannels >> 1; 
    localparam [2:0] NumTxLines = (NumTxChannels <= 4'd1) ? 3'd1 : NumTxChannels >> 1;

    wire tx_lch_active = (NumTxChannels != MONO_RIGHT);
    wire tx_rch_active = (NumTxChannels != MONO_LEFT);
    wire tx_stereo_data = tx_lch_active & tx_rch_active;
    wire rx_lch_active = (NumRxChannels != MONO_RIGHT);
    wire rx_rch_active = (NumRxChannels != MONO_LEFT);
    wire rx_stereo_data = rx_lch_active & rx_rch_active;

    /***************************************************************************
    * The channel data bit resolution can be static or dynamic.
    * Depending on that, the Tx and Rx FSMs have a fixed (compile time) state
    * transition, or configured from the firmware.
    *
    * Static bit resolution:
    *   If a channel resolution is less than half of the word select period and
    *   is not multiple of 8, all unused bits on Rx and Tx directions must be
    *   truncated by zero.
    *   If a channel resolution is multiple of 8, all unused bits are truncated
    *   by Tx and Rx FSMs.
    *
    * Dynamic bit resolution:
    *   A channel resolution must be multiple of 8. Thus all unused bits are
    *   truncated by Tx and Rx FSMs.
    *
    * Note: When the byte swap is enabled, the word select period must be 64
    *       bits and the max channel resolution supported is 24 bits to provide
    *       additional counts for the Tx and Rx FSMs for the byte swapping.
    *       Thus the 8 least significant bits must be truncated if the byte
    *       swap is enabled.
    *       The data bits parameter value can be set to 16 and 24 only when
    *       the byte swap is enabled. This allows checking only one bit of
    *       dyn_data_width signal to determine the data width set. 
    ***************************************************************************/
    wire data_width_8  = 1'b1; /* There is always at least one byte to transfer */
    wire data_width_16 = (StaticBitResolution) ? (DataBits > 8) :
                         (EnableTxByteSwap || EnableRxByteSwap) ? 1'b1 : (dyn_data_width > I2S_8BIT_CH);
    wire data_width_24 = (StaticBitResolution) ? (DataBits > 16) :
                         (EnableTxByteSwap || EnableRxByteSwap) ? dyn_data_width[1] : (dyn_data_width > I2S_16BIT_CH);
    wire data_width_32 = (StaticBitResolution) ? (DataBits > 24) :
                         (EnableTxByteSwap || EnableRxByteSwap) ? 1'b0 : (dyn_data_width > I2S_24BIT_CH);
    
    wire [3:0] tx_lch_load = {data_width_32 & tx_lch_active, data_width_24 & tx_lch_active,
                              data_width_16 & tx_lch_active, data_width_8  & tx_lch_active
                             };
    wire [3:0] tx_rch_load = {data_width_32 & tx_rch_active, data_width_24 & tx_rch_active,
                              data_width_16 & tx_rch_active, data_width_8  & tx_rch_active
                             };
    wire [3:0] rx_lch_load = {data_width_32 & rx_lch_active, data_width_24 & rx_lch_active,
                              data_width_16 & rx_lch_active, data_width_8  & rx_lch_active
                             };
    wire [3:0] rx_rch_load = {data_width_32 & rx_rch_active, data_width_24 & rx_rch_active,
                              data_width_16 & rx_rch_active, data_width_8  & rx_rch_active
                             };

    localparam TruncCondition = (DataBits[2:0] == 3'h0) ? EnableTxByteSwap : StaticBitResolution;
    
    /* For a 16-bit word select period, a channel resolution is always equal to half
    * of the word select period. Thus the truncation is never needed in this case.
    */
    wire data_trunc = (TruncCondition == 1'b0) ? 1'b0 : /* truncation is not needed */
        (WordSelect == WORD_SEL32) ? ((count[4:1] <= MsbRight) & (count[4:1] >= LsbRight)) :
        (WordSelect == WORD_SEL64) ? ((count[5:1] <= MsbRight) & (count[5:1] >= LsbRight)) :
        /* 48-bits WS length */     (((count[6:1] <= MsbLeft)  & (count[6:1] >= LsbLeft)) |
                                     ((count[6:1] <= MsbRight) & (count[6:1] >= LsbRight)));

    /***************************************************************************
    *                      TX direction implementation                         
    ***************************************************************************/
    generate
    if(TxDirectionPresent)
    begin: Tx
        wire [NumTxLines-1:0] tx_f0_n_full;  /* Tx FIFO 0 not full status */
        wire [NumTxLines-1:0] tx_f1_n_full;  /* Tx FIFO 1 not full status */
        wire [NumTxLines-1:0] tx_f0_empty;   /* Tx FIFO 0 empty status    */
        wire [NumTxLines-1:0] tx_f1_empty;   /* Tx FIFO 1 empty status    */
        wire [NumTxLines-1:0] tx_underflow;  /* Tx underflow status       */
        wire [NumTxLines-1:0] tx_data_out;   /* Tx datapath so output     */

        /* Double sync Tx enable signal to the component clock when the I2S is
        * configured for asynchronous operation with respect to the system clock.
        */
        if(ClockSyncMode == CLOCK_ASYNC)
        begin:TX_EN_ASYNC
            cy_psoc3_sync CtlTxEnSync
            (
                /* input  */ .clock(op_clk),
                /* input  */ .sc_in(ctrl_reg_out[I2S_CTRL_TX_ENABLE]),
                /* output */ .sc_out(ctrl[I2S_CTRL_TX_ENABLE])
            );
        end
        else
        begin:TX_EN_SYNC
            assign ctrl[I2S_CTRL_TX_ENABLE] = ctrl_reg_out[I2S_CTRL_TX_ENABLE];
        end       

        /*********************************************************************** 
        * State machine state definitions. To simplify the code, the state
        * machine logical states are mapped onto different hardware states
        * depending on the configuration. Therefore the state machine always
        * transits through the fixed logical states that represent the relevant
        * hardware states.
        ***********************************************************************/

        /* Tx datapath state definitions */
        localparam PASS_A0   = 3'd0;
        localparam MOV_A0_F0 = 3'd1;
        localparam SL_A0     = 3'd2;
        localparam MOV_A0_D0 = 3'd3;
        localparam MOV_A1_F1 = 3'd4;
        localparam MOV_A0_A1 = 3'd5;
        localparam MOV_A1_A0 = 3'd6;
        localparam A0_XOR_A0 = 3'd7;

        /* Tx state machine logical states and state register */
        localparam TX_STATE_HOLD      = PASS_A0;
        localparam TX_STATE_SHIFT     = SL_A0;
        localparam TX_STATE_LOAD0_L   = MOV_A0_F0;
        localparam TX_STATE_LOAD1_L   = EnableTxByteSwap ? MOV_A0_D0 : MOV_A0_F0;
        localparam TX_STATE_LOAD2_L   = EnableTxByteSwap ? MOV_A0_A1 : MOV_A0_F0;
        localparam TX_STATE_LOAD3_L   = MOV_A0_F0;
        localparam TX_STATE_LOAD0_R   = TxDataInterleaving ? MOV_A0_F0 : MOV_A1_F1;
        localparam TX_STATE_LOAD1_R   = EnableTxByteSwap   ? MOV_A0_D0 : (TxDataInterleaving ? MOV_A0_F0 : MOV_A1_F1);
        localparam TX_STATE_LOAD2_R   = EnableTxByteSwap   ? MOV_A0_A1 : (TxDataInterleaving ? MOV_A0_F0 : MOV_A1_F1);
        localparam TX_STATE_LOAD3_R   = TxDataInterleaving ? MOV_A0_F0 : MOV_A1_F1;
        localparam TX_STATE_MOV_ALU_R = MOV_A0_A1;
        localparam TX_STATE_SWAP1     = MOV_A0_F0;
        localparam TX_STATE_SWAP2     = MOV_A1_A0;
        localparam TX_STATE_ZERO      = A0_XOR_A0;

        reg [2:0] tx_state;

        /* Capture the underflow signal and clear it when the transmit is disabled */
        reg tx_underflow_sticky;
        always @(posedge op_clk)
        begin
            tx_underflow_sticky <= (tx_underflow_sticky | |tx_underflow) & ctrl[I2S_CTRL_TX_ENABLE];
        end

        /***********************************************************************
        * The transition into and out of the enabled state will occur at a word
        * select boundary such that a left / right sample pair is always
        * transmitted.
        ***********************************************************************/
        reg txenable; 
        always @(posedge op_clk)
        begin
            if(tx_underflow_sticky)
            begin
                /* Stop state machine from fetching any further data */
                txenable <= 1'b0;
            end
            else
            begin
                if(count[6:0] == 7'd0)
                /* Enable/Disable at word select boundary */
                begin
                    txenable <= ctrl[I2S_CTRL_TX_ENABLE];
                end
                else
                /* Disable any time component is stopped */
                begin
                    txenable <= txenable & ctrl[I2S_CTRL_ENABLE];
                end
            end
        end

        /***********************************************************************
        * Byte swapping allows data transfer between a source and destination
        * that have different endianess.
        * tx_swap_done indicates that the byte swap operation is complete
        * and the audio sample can be sent onto sdo output. The Tx sends all zero
        * samples if the byte swap has not been performed.
        * The byte swap is supported only when a 64-bit word select period is
        * selected and the audio stream is interleaved.
        * Constant 1'b0 is assigned to tx_swap_done_reg and d0_load to optimize
        * the signals out when the byte swapping operation is disabled.
        * The byte swap operation is performed as follows:
        *   1. F0 (MSB) -> A0;
        *   2. A0 (MSB) -> A1; F0 (MID) -> D0;
        *   3. F0 (LSB) -> A0;
        *   4. Shift out A0 (LSB);
        *   5. D0 (MID) -> A0;
        *   6. Shift out A0 (MID);
        *   7. A1 (MSB) -> A0;
        *   8. Shift out A0 (MSB).
        ***********************************************************************/
        reg tx_swap_done_reg;
        reg d0_load;
        
        always @(posedge op_clk)
        begin
            if(EnableTxByteSwap)
            begin
                tx_swap_done_reg <= txenable & (tx_swap_done_reg | (tx_state == TX_STATE_SWAP2) & ~count[6]);
                d0_load <= (tx_state == TX_STATE_SWAP2);
            end
            else
            begin
                tx_swap_done_reg <= 1'b0;
                d0_load <= 1'b0;
            end
        end
        wire tx_swap_done = EnableTxByteSwap ? tx_swap_done_reg : 1'b1;
 
        /***********************************************************************
        *                   Tx protocol state machine
        ***********************************************************************/
        always @(posedge op_clk)
        begin
            if(txenable)
            begin
                case(tx_state)
                TX_STATE_ZERO:
                    /***********************************************************
                    * If the byte swap is enabled, the component sends all zeros
                    * while performing the byte swapping operation (first data
                    * sample after txenable).
                    * If the byte swap is disabled, the first byte to transfer
                    * is loaded after txenable is set.
                    ***********************************************************/
                    tx_state <= (EnableTxByteSwap) ? TX_STATE_SHIFT : TX_STATE_LOAD0_L;
                
                TX_STATE_HOLD:
                    case(WordSelect)
                    WORD_SEL64:
                        case(count[6:1])
                        6'd63: tx_state <= (tx_lch_load[0] & tx_swap_done) ? TX_STATE_LOAD0_L : TX_STATE_SHIFT;
                        6'd55: tx_state <= (tx_lch_load[1] & tx_swap_done) ? TX_STATE_LOAD1_L : TX_STATE_SHIFT;
                        6'd47: tx_state <= (tx_lch_load[2] & tx_swap_done) ? TX_STATE_LOAD2_L : TX_STATE_SHIFT;
                        6'd39: tx_state <= (tx_lch_load[3]) ? TX_STATE_LOAD3_L : TX_STATE_SHIFT;
                        6'd33: tx_state <= (EnableTxByteSwap & tx_stereo_data & data_width_24 & tx_swap_done) ?
                                TX_STATE_SWAP1 : TX_STATE_SHIFT;
                        6'd32: tx_state <= (EnableTxByteSwap & tx_stereo_data & tx_swap_done) ?
                                TX_STATE_SWAP2 : TX_STATE_SHIFT;
                        6'd31: tx_state <= (tx_rch_load[0] & tx_swap_done) ? TX_STATE_LOAD0_R : TX_STATE_SHIFT;
                        6'd23: tx_state <= (tx_rch_load[1] & tx_swap_done) ? TX_STATE_LOAD1_R : TX_STATE_SHIFT;
                        6'd15: tx_state <= (tx_rch_load[2] & tx_swap_done) ? TX_STATE_LOAD2_R : TX_STATE_SHIFT;
                        6'd7 : tx_state <= (tx_rch_load[3]) ? TX_STATE_LOAD3_R : TX_STATE_SHIFT;
                        6'd1 : tx_state <= (EnableTxByteSwap & data_width_24) ? TX_STATE_SWAP1 : TX_STATE_SHIFT;
                        6'd0 : tx_state <= (EnableTxByteSwap) ? TX_STATE_SWAP2 : TX_STATE_SHIFT;
                        default: tx_state <= TX_STATE_SHIFT;
                        endcase
                    WORD_SEL48:
                        case(count[6:1])
                        6'd47: tx_state <= (tx_lch_load[0]) ? TX_STATE_LOAD0_L : TX_STATE_SHIFT;
                        6'd39: tx_state <= (tx_lch_load[1]) ? TX_STATE_LOAD1_L : TX_STATE_SHIFT;
                        6'd31: tx_state <= (tx_lch_load[2]) ? TX_STATE_LOAD2_L : TX_STATE_SHIFT;
                        6'd23: tx_state <= (tx_rch_load[0]) ? TX_STATE_LOAD0_R : TX_STATE_SHIFT;
                        6'd15: tx_state <= (tx_rch_load[1]) ? TX_STATE_LOAD1_R : TX_STATE_SHIFT;
                        6'd7 : tx_state <= (tx_rch_load[2]) ? TX_STATE_LOAD2_R : TX_STATE_SHIFT;
                        default: tx_state <= TX_STATE_SHIFT;
                        endcase
                    WORD_SEL32:
                        case(count[5:1])
                        5'd31: tx_state <= (tx_lch_load[0]) ? TX_STATE_LOAD0_L : TX_STATE_SHIFT;
                        5'd23: tx_state <= (tx_lch_load[1]) ? TX_STATE_LOAD1_L : TX_STATE_SHIFT;
                        5'd15: tx_state <= (tx_rch_load[0]) ? TX_STATE_LOAD0_R : TX_STATE_SHIFT;
                        5'd7 : tx_state <= (tx_rch_load[1]) ? TX_STATE_LOAD1_R : TX_STATE_SHIFT;
                        default  : tx_state <= TX_STATE_SHIFT;
                        endcase
                    default: /* WORD_SEL16 */
                        case(count[4:1])
                        4'd15: tx_state <= (tx_lch_load[0]) ? TX_STATE_LOAD0_L : TX_STATE_SHIFT;
                        4'd7 : tx_state <= (tx_rch_load[0]) ? TX_STATE_LOAD1_R : TX_STATE_SHIFT;
                        default: tx_state <= TX_STATE_SHIFT;
                        endcase
                    endcase

                TX_STATE_LOAD0_R:
                    /***********************************************************
                    * In case of separate audio FIFOs, TX_STATE_LOAD0_R,
                    * TX_STATE_LOAD1_R, TX_STATE_LOAD2_R, TX_STATE_LOAD3_R use
                    * the same state value. Therefore the check is performed 
                    * for TX_STATE_LOAD0_R only and the FSM transits to
                    * TX_STATE_MOV_ALU_R. In the case of an interleaved FIFO, the
                    * states have different values, and the FSM transits to
                    * TX_STATE_HOLD that is handled in default case clause.
                    ***********************************************************/
                    tx_state <= TxDataInterleaving ? TX_STATE_HOLD : TX_STATE_MOV_ALU_R;

                TX_STATE_MOV_ALU_R: tx_state <= TxDataInterleaving ? TX_STATE_HOLD : TX_STATE_SHIFT;
                default: tx_state <= TX_STATE_HOLD;
                endcase
            end
            else
            begin
                tx_state <= TX_STATE_ZERO;
            end
        end

        /***********************************************************************
        * Each I2S Tx line has 3 status bits. The bit order is as follows:
        *   Bit 0: TX_UNDERFLOW
        *   Bit 1: TX_F0_NOT_FULL
        *   Bit 2: TX_F1_NOT_FULL
        * The total number of status bits equals to the number of Tx lines
        * multiplied by the number of line status bits. All the status bits are
        * connected to the lower 6 status inputs of 7-bit status registers with
        * the built in interrupt support (statusi). Thus one statusi is utilized
        * by two Tx lines.
        *        
        * The bits are mapped sequentially within the registers, i.e. bits [2:0]
        * of statusi 1 correspond to line 1 and bits [5:3] to line 2. Bits [2:0]
        * of statusi 2 correspond to line 3 etc. Unused bits assigned with '0'.
        ***********************************************************************/
        localparam [2:0] TX_UNDERFLOW_0   = 3'd0;
        localparam [2:0] TX_F0_NOT_FULL_0 = 3'd1;
        localparam [2:0] TX_F1_NOT_FULL_0 = 3'd2;
        localparam [2:0] TX_UNDERFLOW_1   = 3'd3;
        localparam [2:0] TX_F0_NOT_FULL_1 = 3'd4;
        localparam [2:0] TX_F1_NOT_FULL_1 = 3'd5;
        
        localparam NumStsRegs = (NumTxLines + 1) >> 1;
        wire [NumStsRegs-1:0] tx_int_out;

        for(i = 0; i < NumTxLines; i = i + 2)
        begin: STS
            wire [5:0] status;
            assign status[TX_UNDERFLOW_0]   = tx_underflow[i];
            assign status[TX_F0_NOT_FULL_0] = tx_f0_n_full[i];
            assign status[TX_F1_NOT_FULL_0] = (TxDataInterleaving) ? 1'b0 : tx_f1_n_full[i];
            if(i < NumTxLines-1)
            begin
                assign status[TX_UNDERFLOW_1]   = tx_underflow[i+1];
                assign status[TX_F0_NOT_FULL_1] = tx_f0_n_full[i+1];
                assign status[TX_F1_NOT_FULL_1] = (TxDataInterleaving) ? 1'b0 : tx_f1_n_full[i+1];
            end
            else
            begin
                assign status[5:3] = 3'h0;  /* Bits [5:3] unused */
            end

            cy_psoc3_statusi #(.cy_force_order(1), .cy_md_select(7'h01), .cy_int_mask(7'h00)) Sts
            (
                /* input          */  .clock(op_clk),
                /* input  [06:00] */  .status({1'b0, status[5:0]}),
                /* output         */  .interrupt(tx_int_out[i>>1])
            );
        end
        
        /* Interrupt generation */
        reg tx_int_reg;

        /* If more than one statusi register is utilized, their outputs are ORed.
        * The output of the OR term is registered and connected to tx_interrupt
        * terminal. Otherwise the output of the statusi is connected to tx_interrupt
        * terminal directly.
        */
        always @(posedge op_clk)
        begin
            tx_int_reg <= |tx_int_out;
        end

        assign tx_interrupt = (NumStsRegs > 1) ? tx_int_reg : tx_int_out;

        /*********************************************************************** 
        *           Instantiate datapath elements for I2S data lines
        ***********************************************************************/
        for(i = 0; i < NumTxLines; i = i + 1)
        begin: CH
            /* Tx underflow detection */
            assign tx_underflow[i] = (TxDataInterleaving) ? ((tx_state == MOV_A0_F0) & tx_f0_empty[i]) :
                ((tx_state == MOV_A0_F0) & tx_f0_empty[i]) | ((tx_state == MOV_A1_F1) & tx_f1_empty[i]);

            /* DMA requests are connected to FIFO bus status outputs */
            assign tx_dma0[i] = tx_f0_n_full[i];
            assign tx_dma1[i] = tx_f1_n_full[i];

            /* Truncate all unused bits if required */
            always @(posedge op_clk)
            begin
                if(count[0])
                begin
                    sdo[i] <= TruncCondition ? tx_data_out[i] & data_trunc : tx_data_out[i];
                end
            end

            cy_psoc3_dp8 #(.cy_dpconfig_a(
            {
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM0: Hold*/
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC___F0, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM1: Mov A0, F0*/
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP___SL, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM2: Shift data out onto sdo line*/
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM3: Mov D0, A0*/
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC___F1,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM4: Mov A1, F1*/
                `CS_ALU_OP_PASS, `CS_SRCA_A1, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM5: Mov A0, A1*/
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM6: Mov A1, A0*/
                `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM7: Xor A0, A0*/
                  8'hFF, 8'h00,    /*CFG9: */
                  8'hFF, 8'hFF,    /*CFG11-10: */
                `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
                `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
                `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
                `SC_SI_A_DEFSI, /*CFG13-12: */
                `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
                1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
                `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
                `SC_FB_NOCHN, `SC_CMP1_NOCHN,
                `SC_CMP0_NOCHN, /*CFG15-14: */
                3'h00, FIFO_STS_SYNC, 6'h00,
                `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,   
                `SC_FIFO_LEVEL,`SC_FIFO_ASYNC,`SC_EXTCRC_DSBL,
                `SC_WRK16CAT_DSBL /*CFG17-16: */
            })) dpTx(
                /*  input                   */  .clk(op_clk),
                /*  input   [02:00]         */  .cs_addr(tx_state),
                /*  input                   */  .route_si(1'b0),
                /*  input                   */  .route_ci(1'b0),
                /*  input                   */  .f0_load(1'b0),
                /*  input                   */  .f1_load(1'b0),
                /*  input                   */  .d0_load(d0_load),
                /*  input                   */  .d1_load(1'b0),
                /*  output                  */  .ce0(),
                /*  output                  */  .cl0(),
                /*  output                  */  .z0(),
                /*  output                  */  .ff0(),
                /*  output                  */  .ce1(),
                /*  output                  */  .cl1(),
                /*  output                  */  .z1(),
                /*  output                  */  .ff1(),
                /*  output                  */  .ov_msb(),
                /*  output                  */  .co_msb(),
                /*  output                  */  .cmsb(),
                /*  output                  */  .so(tx_data_out[i]),
                /*  output                  */  .f0_bus_stat(tx_f0_n_full[i]), /* FIFO 0 is not FULL */
                /*  output                  */  .f0_blk_stat(tx_f0_empty[i]),  /* FIFO 0 is EMPTY */
                /*  output                  */  .f1_bus_stat(tx_f1_n_full[i]), /* FIFO 1 is not FULL */
                /*  output                  */  .f1_blk_stat(tx_f1_empty[i])   /* FIFO 1 is EMPTY */
            );
        end
    end
    endgenerate    /* Tx */

    /***************************************************************************
    *                 Rx direction implementation                                        
    ***************************************************************************/
    generate
    if(RxDirectionPresent)
    begin: Rx
        wire [NumRxLines-1:0] rx_f0_n_empty;    /* Rx FIFO 0 empty status bit */
        wire [NumRxLines-1:0] rx_f1_n_empty;    /* Rx FIFO 1 empty status bit */
        wire [NumRxLines-1:0] rx_f0_full;       /* Rx FIFO 0 full status bit  */
        wire [NumRxLines-1:0] rx_f1_full;       /* Rx FIFO 1 full status bit  */
        wire [NumRxLines-1:0] rx_overflow;      /* Rx overflow status         */
        reg  [NumRxLines-1:0] rx_data_in;       /* shift_in to rx datapath    */ 

        /* Double sync Rx enable signal to the component clock when the I2S is
        * configured for asynchronous operation with respect to the system clock.
        */
        if(ClockSyncMode == CLOCK_ASYNC)
        begin:RX_EN_ASYNC
            cy_psoc3_sync CtlRxEnSync
            (
                /* input  */ .clock(op_clk),
                /* input  */ .sc_in(ctrl_reg_out[I2S_CTRL_RX_ENABLE]),
                /* output */ .sc_out(ctrl[I2S_CTRL_RX_ENABLE])
            );
        end
        else
        begin:RX_EN_SYNC
            assign ctrl[I2S_CTRL_RX_ENABLE] = ctrl_reg_out[I2S_CTRL_RX_ENABLE];
        end 

        /***********************************************************************
        * State machine state definitions. To simplify the code, the state
        * machine logical states are mapped onto different datapath states
        * depending on the configuration. Therefore the state machine always
        * transits through the fixed logical states that represent the relevant
        * hardware states.
        ***********************************************************************/

        /* RX datapath state definitions */
        localparam PASS_A0   = 3'd0;
        localparam SL_A0     = 3'd1;
        localparam MOV_F0_A0 = 3'd2;
        localparam MOV_A1_A0 = 3'd3;
        localparam MOV_F1_A0 = 3'd4;
        localparam MOV_A1_F1__A0_A1 = 3'd5; /* A1 = F1; A0 = A1 */
        localparam MOV_A0_A1 = 3'd6;
        localparam RX_FIFO1_DYN_MODE = EnableRxByteSwap ? 1'b1 : 1'b0;
        
        /* Rx state machine logical states and state register */
        localparam RX_STATE_HOLD   = PASS_A0;
        localparam RX_STATE_SHIFT  = SL_A0;
        localparam RX_STATE_LOAD0_L = EnableRxByteSwap ? MOV_F1_A0 : MOV_F0_A0;
        localparam RX_STATE_LOAD1_L = EnableRxByteSwap ? MOV_A1_A0 : MOV_F0_A0;
        localparam RX_STATE_LOAD2_L = MOV_F0_A0;
        localparam RX_STATE_LOAD3_L = MOV_F0_A0;
        localparam RX_STATE_LOAD0_R = RxDataInterleaving ? (EnableRxByteSwap ? MOV_F1_A0 : MOV_F0_A0) : MOV_F1_A0;
        localparam RX_STATE_LOAD1_R = RxDataInterleaving ? (EnableRxByteSwap ? MOV_A1_A0 : MOV_F0_A0) : MOV_F1_A0;
        localparam RX_STATE_LOAD2_R = RxDataInterleaving ? MOV_F0_A0 : MOV_F1_A0;
        localparam RX_STATE_LOAD3_R = RxDataInterleaving ? MOV_F0_A0 : MOV_F1_A0;
        localparam RX_STATE_SWAP1   = MOV_A1_F1__A0_A1;
        localparam RX_STATE_SWAP2   = MOV_A0_A1;

        reg [2:0] rx_state;
        reg rx_f0_load;
        reg rx_f1_load;

        /***********************************************************************
        * Byte swapping allows data transfer between a source and destination
        * that have different endianess.
        * The byte swap is supported only when a 64-bit word select period and
        * the audio stream is interleaved.
        * The byte swap operation is performed as follows:
        *   1. Shift into A0 (MSB);
        *   2. A0 (MSB) -> F1;
        *   3. Shift into A0 (MID);
        *   4. A0 (MID) -> A1;
        *   5. Shift into A0 (LSB);
        *   6. A0 (LSB) -> F0;
        *   7. A1 (MID) -> A0, F1 (MSB) -> A1;
        *   8. A0 (MID) -> F0, A1 (MSB) -> A0;
        *   9. A0 (MSB) -> F0.
        ***********************************************************************/
        always @(posedge op_clk)
        begin
            rx_f0_load <= (rx_state == MOV_F0_A0) | (rx_state == MOV_A0_A1) | (rx_state == MOV_A1_F1__A0_A1);
            rx_f1_load <= (EnableRxByteSwap || !RxDataInterleaving) ? (rx_state == MOV_F1_A0) : 1'b0;
        end

        /* Capture overflow signal and clear it when receive is disabled */
        reg rx_overflow_sticky;
        always @(posedge op_clk)
        begin
            rx_overflow_sticky <= (rx_overflow_sticky | |rx_overflow) & ctrl[I2S_CTRL_RX_ENABLE];
        end

        /***********************************************************************
        * The transition into and out of the enabled state occurs at a word 
        * select boundary such that a left/right sample pair is always received.
        * Since the counter period value is used to capture the least
        * significant data byte of right channel, there is one unwanted (false)
        * load, because of rx enabling on the counter period value. To avoid
        * this load, enabling of Rx is delayed by 1.
        ***********************************************************************/
        reg rxenable; 
        always @(posedge op_clk)
        begin
            if(rx_overflow_sticky)
            begin
                /* Stop state machine from capturing any further data */
                rxenable <= 1'b0;
            end
            else
            begin
                /* Enable/Disable at word select boundary delayed by 1 */
                if(count[6:1] == (I2SBitCounterPeriod-1))
                begin
                    /* rxenable signal is synchronized with the falling edge of sck */
                    rxenable <= count[0] ? ctrl[I2S_CTRL_RX_ENABLE] : rxenable;
                end
                else
                /* Disable any time component is stopped */
                begin
                    rxenable <= rxenable & ctrl[I2S_CTRL_ENABLE];
                end
            end
        end

        /***********************************************************************
        *                   Rx protocol state machine
        ***********************************************************************/
        always @(posedge op_clk)
        begin
            if(rxenable)
            begin
                case(rx_state)
                RX_STATE_HOLD:
                    case(WordSelect)
                    WORD_SEL64:
                        case(count[6:1])
                        6'd62: rx_state <= (rx_rch_load[3]) ? RX_STATE_LOAD3_R : RX_STATE_SHIFT;
                        6'd54: rx_state <= (rx_lch_load[0]) ? RX_STATE_LOAD0_L : RX_STATE_SHIFT;
                        6'd46: rx_state <= (rx_lch_load[1]) ? RX_STATE_LOAD1_L : RX_STATE_SHIFT;
                        6'd38: rx_state <= (rx_lch_load[2]) ? RX_STATE_LOAD2_L : RX_STATE_SHIFT;
                        6'd37: rx_state <= (EnableRxByteSwap & rx_lch_active) ? RX_STATE_SWAP1 : RX_STATE_SHIFT;
                        6'd30: rx_state <= (rx_lch_load[3]) ? RX_STATE_LOAD3_L : RX_STATE_SHIFT;
                        6'd22: rx_state <= (rx_rch_load[0]) ? RX_STATE_LOAD0_R : RX_STATE_SHIFT;
                        6'd14: rx_state <= (rx_rch_load[1]) ? RX_STATE_LOAD1_R : RX_STATE_SHIFT;
                        6'd6 : rx_state <= (rx_rch_load[2]) ? RX_STATE_LOAD2_R : RX_STATE_SHIFT;
                        6'd5 : rx_state <= (EnableRxByteSwap & rx_rch_active) ? RX_STATE_SWAP1 : RX_STATE_SHIFT;
                        default: rx_state <= RX_STATE_SHIFT;
                        endcase
                    WORD_SEL48:
                        case(count[6:1])
                        6'd46: rx_state <= (rx_rch_load[2]) ? RX_STATE_LOAD2_R : RX_STATE_SHIFT;
                        6'd38: rx_state <= (rx_lch_load[0]) ? RX_STATE_LOAD0_L : RX_STATE_SHIFT;
                        6'd30: rx_state <= (rx_lch_load[1]) ? RX_STATE_LOAD1_L : RX_STATE_SHIFT;
                        6'd22: rx_state <= (rx_lch_load[2]) ? RX_STATE_LOAD2_L : RX_STATE_SHIFT;
                        6'd14: rx_state <= (rx_rch_load[0]) ? RX_STATE_LOAD0_R : RX_STATE_SHIFT;
                        6'd6 : rx_state <= (rx_rch_load[1]) ? RX_STATE_LOAD1_R : RX_STATE_SHIFT; 
                        default: rx_state <= RX_STATE_SHIFT;
                        endcase
                    WORD_SEL32:
                        case(count[5:1])
                        5'd30: rx_state <= (rx_rch_load[1]) ? RX_STATE_LOAD1_R : RX_STATE_SHIFT;
                        5'd22: rx_state <= (rx_lch_load[0]) ? RX_STATE_LOAD0_L : RX_STATE_SHIFT;
                        5'd14: rx_state <= (rx_lch_load[1]) ? RX_STATE_LOAD1_L : RX_STATE_SHIFT;
                        5'd6 : rx_state <= (rx_rch_load[0]) ? RX_STATE_LOAD0_R : RX_STATE_SHIFT;
                        default: rx_state <= RX_STATE_SHIFT;
                        endcase
                    default: /* WORD_SEL16 */
                        case(count[4:1])
                        4'd14: rx_state <= (rx_rch_load[0] & rx_rch_active) ? RX_STATE_LOAD0_R : RX_STATE_SHIFT;
                        4'd6 : rx_state <= (rx_lch_load[0] & rx_lch_active) ? RX_STATE_LOAD0_L : RX_STATE_SHIFT;
                        default: rx_state <= RX_STATE_SHIFT;
                        endcase
                    endcase
                RX_STATE_SWAP1: rx_state <= RX_STATE_SWAP2;
                RX_STATE_SWAP2: rx_state <= RX_STATE_SHIFT;

                default: rx_state <= RX_STATE_HOLD;
                endcase
            end
            else
            /*******************************************************************
            * Because of the delay for the Rx enabling the first bit should be 
            * captured in preparation for the Rx being enabled. So rx has to 
            * shift input data continuously, even if it isn't enabled 
            *******************************************************************/
            begin
                rx_state <= RX_STATE_SHIFT;
            end
        end
        
        /***********************************************************************
        * Each I2S Rx line has 3 status bits. The bit order is as follows:
        *   Bit 0: RX_OVERFLOW
        *   Bit 1: RX_F0_NOT_EMPTY
        *   Bit 2: RX_F1_NOT_EMPTY
        *
        * Refer to the appropriate section for the Tx status above for details
        * on the status registers mapping.
        ***********************************************************************/
        localparam [2:0] RX_OVERFLOW_0     = 3'd0;
        localparam [2:0] RX_F0_NOT_EMPTY_0 = 3'd1;
        localparam [2:0] RX_F1_NOT_EMPTY_0 = 3'd2;
        localparam [2:0] RX_OVERFLOW_1     = 3'd3;
        localparam [2:0] RX_F0_NOT_EMPTY_1 = 3'd4;
        localparam [2:0] RX_F1_NOT_EMPTY_1 = 3'd5;

        localparam NumStsRegs = (NumRxLines + 1) >> 1;
        wire [NumStsRegs-1:0] rx_int_out;

        for(i = 0; i < NumRxLines; i = i + 2)
        begin: STS
            wire [5:0] status;
            assign status[RX_OVERFLOW_0]     = rx_overflow[i];
            assign status[RX_F0_NOT_EMPTY_0] = rx_f0_n_empty[i];
            assign status[RX_F1_NOT_EMPTY_0] = RxDataInterleaving ? 1'b0 : rx_f1_n_empty[i];
            if(i < NumRxLines-1)
            begin
                assign status[RX_OVERFLOW_1] = rx_overflow[i+1];
                assign status[RX_F0_NOT_EMPTY_1] = rx_f0_n_empty[i+1];
                assign status[RX_F1_NOT_EMPTY_1] = RxDataInterleaving ? 1'b0 : rx_f1_n_empty[i+1];
            end
            else
            begin
                assign status[5:3] = 3'h0;  /* Bits [5:3] unused */
            end

            cy_psoc3_statusi #(.cy_force_order(1), .cy_md_select(7'h01), .cy_int_mask(7'h00)) Sts
            (
                /* input          */  .clock(op_clk),
                /* input  [06:00] */  .status({1'b0, status[5:0]}),
                /* output         */  .interrupt(rx_int_out[i>>1])
            );
        end

        /* Interrupt generation */
        reg rx_int_reg;

        /* If more than one statusi register is utilized, their outputs are ORed.
        * The output of the OR term is registered and connected to tx_interrupt
        * terminal. Otherwise the output of the statusi is connected to tx_interrupt
        * terminal directly.
        */
        always @(posedge op_clk)
        begin
            rx_int_reg <= |rx_int_out;
        end

        assign rx_interrupt = (NumStsRegs > 1) ? rx_int_reg : rx_int_out;

        /***********************************************************************
        * The Rx clip detection logic performs an 8-bit signed comparison of a
        * received audio sample (A0) with a positive (D0) and negative clipping
        * threshold (D1). Only the MSB data byte is used in the comparison. The
        * operation uses "less than" a condition of comparator 0 (cl0) and
        * comparator 1 (cl1).
        * Because of 2's complement data format, the input signal is clipping
        * when its numerical value is less than the negative threshold and
        * greater or equal to its positive threshold, i.e. D0 <= A0 < D1.
        ***********************************************************************/
        wire [NumRxLines-1:0] pos_clip_cmp;
        wire [NumRxLines-1:0] neg_clip_cmp;
        
        if(EnableClipDetect)
        begin: CLIP
            reg is_msb_load;
            always @(posedge op_clk)
            begin
                if(rxenable & ~count[0])
                begin
                    case (WordSelect)
                        WORD_SEL64: is_msb_load <= (count[6:1] == 6'd54) | (count[6:1] == 6'd22);
                        WORD_SEL48: is_msb_load <= (count[6:1] == 6'd38) | (count[6:1] == 6'd14);
                        WORD_SEL32: is_msb_load <= (count[5:1] == 5'd22) | (count[5:1] == 5'd6);
                    default: /* WS = 16 */
                        is_msb_load <=  count[3:1] == 3'd6;
                    endcase
                end
                else
                begin
                    is_msb_load <= 1'b0;
                end
            end

            always @(posedge op_clk)
            begin
                if(is_msb_load)
                begin
                    clip[NumRxLines-1:0] <= ~pos_clip_cmp[NumRxLines-1:0] & neg_clip_cmp[NumRxLines-1:0];
                end
            end
        end

        /*********************************************************************** 
        *           Instantiate datapath elements for I2S data lines
        ***********************************************************************/
        for(i = 0; i < NumRxLines; i = i + 1)
        begin: CH
            /* Rx overflow detection */
            assign rx_overflow[i] = RxDataInterleaving ? (rx_f0_load & rx_f0_full[i]):
                                   ((rx_f0_load & rx_f0_full[i]) | (rx_f1_load & rx_f1_full[i]));

            /* DMA requests are connected to FIFO bus status outputs */
            assign rx_dma0[i] = rx_f0_n_empty[i];
            assign rx_dma1[i] = rx_f1_n_empty[i];
            
            /* Truncate all unused bits if required */
            always @(posedge op_clk)
            begin
                if(~count[0])
                begin
                    rx_data_in[i] <= TruncCondition ? sdi[i] & data_trunc : sdi[i];
                end
            end

            cy_psoc3_dp8 #(.cy_dpconfig_a(
            {
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM0: Idle*/
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP___SL, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM1: Shift in sdi to A0*/
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP___SL, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM2: Move F0, A0 and shift in sdi to A0*/
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP___SL, `CS_A0_SRC__ALU, `CS_A1_SRC__ALU,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM3: Move A1, A0 and shift in sdi to A0*/
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP___SL, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM4: Move F1, A0 and shift in sdi to A0*/
                `CS_ALU_OP_PASS, `CS_SRCA_A1, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC___F1,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM5: Move A0, A1 and move A1, F1*/
                `CS_ALU_OP_PASS, `CS_SRCA_A1, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM6: Move A0, A1*/
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM7: Idle*/
                  8'hFF, 8'h00,    /*CFG9: */
                  8'hFF, 8'hFF,    /*CFG11-10: */
                `SC_CMPB_A1_D1, `SC_CMPA_A0_D1, `SC_CI_B_ARITH,
                `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
                `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
                `SC_SI_A_ROUTE, /*CFG13-12: SI A source is routed from SI input */
                `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
                1'h0, `SC_FIFO1__A0, `SC_FIFO0__A0,
                `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
                `SC_FB_NOCHN, `SC_CMP1_NOCHN,
                `SC_CMP0_NOCHN, /*CFG15-14: FIFO source is A0 */
                3'h00, FIFO_STS_SYNC, 2'h00,    
                RX_FIFO1_DYN_MODE, 3'h00,
                `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,`SC_FIFO_LEVEL,
                `SC_FIFO_ASYNC, `SC_EXTCRC_DSBL,
                `SC_WRK16CAT_DSBL /*CFG17-16: */
            })) dpRx(
                /*  input                   */  .clk(op_clk),
                /*  input   [02:00]         */  .cs_addr(rx_state),
                /*  input                   */  .route_si(rx_data_in[i]),
                /*  input                   */  .route_ci(1'b0),
                /*  input                   */  .f0_load(rx_f0_load),
                /*  input                   */  .f1_load(rx_f1_load),
                /*  input                   */  .d0_load(1'b0),
                /*  input                   */  .d1_load(1'b0),
                /*  output                  */  .ce0(),
                /*  output                  */  .cl0(pos_clip_cmp[i]),
                /*  output                  */  .z0(),
                /*  output                  */  .ff0(),
                /*  output                  */  .ce1(),
                /*  output                  */  .cl1(neg_clip_cmp[i]),
                /*  output                  */  .z1(),
                /*  output                  */  .ff1(),
                /*  output                  */  .ov_msb(),
                /*  output                  */  .co_msb(),
                /*  output                  */  .cmsb(),
                /*  output                  */  .so(),
                /*  output                  */  .f0_bus_stat(rx_f0_n_empty[i]), /* FIFO 0 is not EMPTY */
                /*  output                  */  .f0_blk_stat(rx_f0_full[i]),    /* FIFO 0 is FULL */
                /*  output                  */  .f1_bus_stat(rx_f1_n_empty[i]), /* FIFO 1 is not EMPTY */
                /*  output                  */  .f1_blk_stat(rx_f1_full[i])     /* FIFO 1 is FULL */
            );        
        end        
    end
    endgenerate /* Rx */

endmodule

`endif /* bI2S_v2_70_V_ALREADY_INCLUDED */
