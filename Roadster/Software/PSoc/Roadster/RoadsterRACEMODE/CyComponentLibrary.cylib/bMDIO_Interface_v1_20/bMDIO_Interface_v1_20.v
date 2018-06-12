/*******************************************************************************
* File Name: bMDIO_Interface_v1_20.v
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  The bMDIO_Interface module implements the CFP MDIO interface.
*
*  In Basic mode the component receives an MDIO frame, checks PHY and DEV
*  addresses and drives the MDIO line during a data portion of the MDIO read
*  frame. It generates an interrupt signal at the end of each frame if the
*  PHY/DEV address matches the component PHY/DEV address.
*  In Advanced mode the component additionally checks whether the received
*  register address belongs to the one of the allocated register spaces, maps
*  this address to the register memory address and generates all control
*  signals for the DMAs.
*
********************************************************************************
*                 Datapath Register Definitions (16-bit)
********************************************************************************
*
*  INSTANCE NAME: MdioDp
*
*  DESCRIPTION:
*    This datapath checks if the physical address coming from the MDIO matches
*    the configured one in the component customizer. It shifts the received and
*    sent frames.
*
*  REGISTER USAGE:
*    F0 => Loads the register data to be serialized.
*    F1 => Captures the controlling bits from the MDIO master.
*    D0 => Stores the frame pattern + MDIO slave PHY address + DEV address.
*    D1 => Used in Advanced mode only. Contains register writable bitmask.
*    A0 => Shift the bits to/from an MDIO pin.
*    A1 => Used in Advanced mode only for W/R bit masking.
*
********************************************************************************
*  INSTANCE NAME: AddrComp (Advanced Mode Only)
*
*  DESCRIPTION:
*    This datapath determines whether a received address belongs to one of the
*    allocated register spaces and if it does, calculates the register offset
*    within this register space.
*
*  REGISTER USAGE:
*    F0 => Contains the start addresses of all register spaces.
*    F1 => Contains the end addresses of all register spaces.
*    D0 => Loads the start address of each register space for the comparison.
*    D1 => Loads the start address of each register space for the comparison.
*    A0 => Contains the current MDIO address/register offset.
*    A1 => Stores the last accessed MDIO address.
*
********************************************************************************
*  INSTANCE NAME: AddrCalc
*
*  DESCRIPTION:
*    This datapath calculates a physical memory address of the accessed
*    register and the address of its configuration data.
*
*  REGISTER USAGE:
*    F0 => Contains the register space info (register start memory address and
*          the address of configurations array associated with this space.
*    F1 => Not used.
*    D0 => Stores the base memory address of the register space info array.
*    D1 => The size of register space info. Constant = 8.
*    A0 => Used to calculate an address. The meaning depends on the state.!
*    A1 => Used to calculate an address. The meaning depends on the state.!
*
********************************************************************************
*  INSTANCE NAME: FwAlu
*
*  DESCRIPTION:
*    This datapath along with DMA is used by the SetBits API to perform atomic
*    OR write operation.
*
*  REGISTER USAGE:
*    F0 => Not used.
*    F1 => Not used.
*    D0 => Not used.
*    D1 => Not used.
*    A0 => The register value from the memory/result of OR operation.
*    A1 => Bits to set.
*
********************************************************************************
*                 I*O Signals:
********************************************************************************
*    Name           Direction    Description
*    mdio_out       output       An MD IO output pin
*    interrupt      output       An interrupt signal when a frame is finished
*    addr           output       Indicates an address frame
*    cor            output       Indicates clear-on-read register access
*    rs_dma0        output       Triggers StartAddrDMA
*    rs_dma1        output       Triggers EndAddrDMA
*    info_dma       output       Triggers InfoDMA
*    addr_dma       output       Triggers AddrDMA
*    cfg_dma        output       Triggers CfgDMA
*    wr_dma         output       Triggers WrDMA
*    rd_dma         output       Triggers RdDMA
*    fw_dma1        output       Triggers FwDMA1
*    fw_dma2        output       Triggers FwDMA2
*    aux[4:1]       output       Auxiliary bits of a register are being accessed
*    info_nrq       input        Indicates that an InfoDMA transfer is complete
*    addr_nrq       input        Indicates that an AddrDMA transfer is complete
*    wr_nrq         input        Indicates that a WrDMA transfer is complete
*    fw_nrq         input        Indicates that a FwDMA transfer  is complete
*    mdio_in        input        An MD IO input pin
*    mdc            input        An MD clock in
*    enable         input        Synchronous active high enable
*    phy_addr[4:0]  input        A physical port address bus
*    force_cor      input        Forces the register to be cleared on read
*    en_page[7:0]   input        Enables the correspondent page(s)
*    clock          input        An input clock - at least 8 x MDC
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

`include "cypress.v"
`ifdef  bMDIO_Interface_v1_20_V_ALREADY_INCLUDED
`else
`define bMDIO_Interface_v1_20_V_ALREADY_INCLUDED

module bMDIO_Interface_v1_20
(
    output reg        mdio_out,  /* An MD IO output pin (Merged)                 */
    output reg        interrupt, /* An interrupt signal when a frame is finished */
    output reg        address,   /* Indicates that an address frame is received  */
    output reg        cor,       /* Indicates clear-on-read register access      */
    output reg        read,      /* Indicates that a read frame is received      */
    output wire       rs_dma0,   /* Triggers StartAddrDMA                        */
    output wire       rs_dma1,   /* Triggers EndAddrDMA                          */
    output reg        info_dma,  /* Triggers InfoDMA                             */
    output reg        addr_dma,  /* Sets when an AddrDMA transfer is complete    */
    output reg        cfg_dma,   /* Triggers CfgDMA to move register config      */
    output wire       wr_dma,    /* Triggers WrDMA to the write/clear register   */
    output wire       rd_dma,    /* Triggers RdDMA to read the register          */
    output reg        fw_dma1,   /* Triggers FwDMA1 used by APIs                 */
    output reg        fw_dma2,   /* Triggers FwDMA2 used by APIs                 */
    output wire [4:1] aux,       /* Auxiliary bits of an accessed register       */
    input  wire       info_nrq,  /* Sets when an InfoDMA transfer is complete    */
    input  wire       addr_nrq,  /* Sets when an AddrDMA transfer is complete    */
    input  wire       wr_nrq,    /* Sets when a WrDMA transfer is complete       */
    input  wire       fw_nrq1,   /* Sets when an FwDMA1 transfer is complete     */
    input  wire       fw_nrq2,   /* Sets when an FwDMA2 transfer is complete     */
    input  wire       mdio_in,   /* An MD IO input pin                           */
    input  wire       mdc,       /* An MD clock in                               */
    input  wire       enable,    /* Synchronous active high enable               */
    input  wire [4:0] phy_addr,  /* A physical port address bus                  */
    input  wire       force_cor, /* Forces register clearing on the read frame   */
    input  wire [7:0] en_page,   /* Registers space enable signals               */
    input  wire       clock      /* Clock the component operates                 */
);

    /***************************************************************************
    *           Parameters
    ***************************************************************************/
    /* Physical address parameters */
    localparam PHYADDR_FIRMWARE   = 1'b0;
    localparam PHYADDR_HARDWARE   = 1'b1;
    parameter  PhyAddressMode     = PHYADDR_FIRMWARE;
    localparam PHYADDR_3BIT_MASK  = 5'h07;
    localparam PHYADDR_5BIT_MASK  = 5'h1F;
    parameter  PhyAddressMask     = PHYADDR_5BIT_MASK;
    localparam PHYADDR_DP_MASK    = (PhyAddressMask == PHYADDR_5BIT_MASK) ? 8'hF3 : 8'hF0;

    /* Operation mode parameters */
    localparam OPMODE_BASIC       = 1'b0;
    localparam OPMODE_ADVANCED    = 1'b1;
    parameter  OperationMode      = OPMODE_BASIC;

    localparam EXTERN_OE_ENABLED  = 1'b1;
    localparam EXTERN_OE_DISABLED = 1'b0;
    parameter  EnableExternOE     = EXTERN_OE_DISABLED;

    /* Number of register spaces */
    parameter NumRegSpaces = 4;

    /* MDIO frame bit counter period */
    localparam [7:0] BitCountPeriod = 7'd30;

    /* Register page definition */
    localparam [2:0] MDIO_PAGE1 = 3'd0;
    localparam [2:0] MDIO_PAGE2 = 3'd1;
    localparam [2:0] MDIO_PAGE3 = 3'd2;
    localparam [2:0] MDIO_PAGE4 = 3'd3;
    localparam [2:0] MDIO_PAGE5 = 3'd4;
    localparam [2:0] MDIO_PAGE6 = 3'd5;
    localparam [2:0] MDIO_PAGE7 = 3'd6;
    localparam [2:0] MDIO_PAGE8 = 3'd7;

    /***************************************************************************
    *       MDIO FRAME PROCESSING
    ***************************************************************************/
    reg        mdc_dly;       /* A one cycle delay MDC clock                  */
    reg        busy;          /* The busy condition when processing a frame   */
    wire [6:0] count;         /* An MDIO frame bit count                      */
    wire       tc;            /* The terminal count output                    */
    wire       nc1, nc2, nc3; /* nc bits connected to unused datapath outputs */
    reg  [1:0] opcode;        /* MDIO operation bits                          */
    wire       rising_mdc;    /* An MDC rising edge                           */
    wire       ld_count;      /* A bit counter load signal                    */
    wire       so;            /* A shift out                                  */
    wire [1:0] ce0;           /* A0 == D0 condition                           */
    reg        ta_bits;       /* Sets when turning around bits drive the MDIO */
    reg        addr_match;    /* A PHYADDR/DEVADDR detect condition           */
    reg        capture;       /* Forces A0 capture to F1                      */
    reg        mdio_enable;   /* The final MDIO enable signal                 */

    /***************************************************************************
    *         Instantiation of udb_clock_enable primitive
    ****************************************************************************
    * The udb_clock_enable primitive component allows to support the clock enable
    * mechanism and specify the intended synchronization behavior for the clock
    * result (operational clock). Forces the input clock to be synchronous.
    */
    cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`TRUE)) ClkEn
    (
        /* input  */    .clock_in(clock),
        /* input  */    .enable(1'b1),
        /* output */    .clock_out(op_clock)
    );

    /***************************************************************************
    * MDIO and MDC synchronized to input clock
    ***************************************************************************/
    wire mdio_sync;
    wire mdc_sync;

    /***************************************************************************
    * The final MDC signal. Can be either used directly or pass through the sync
    * cell depending on whether the MDIO is captured to the DFF or not.
    ***************************************************************************/
    wire mdc_fin;

    /***************************************************************************
    * The final MDIO signal. Can be either used directly or be captured to the
    * DFF and then pass through the sync cell depending on whether the DFF is
    * used or not.
    ***************************************************************************/
    wire mdio_fin;

    /***************************************************************************
    * To meet the setup and hold times specified in the CFP MSA specification,
    * the D flip-flop, clocked directly by the MDC, is used to capture the MDIO
    * data from the bus. This guaranties that the MDIO is stable for the whole
    * MDC period.
    ***************************************************************************/
    generate
    if(EnableExternOE == EXTERN_OE_DISABLED)
    begin
        /***********************************************************************
        * Instantiate udb_clock_enable primitive configured in Async mode
        * to force the routed clock to be used directly.
        ***********************************************************************/
        cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`FALSE)) MdcClkEn
        (
            /* input  */    .clock_in(mdc),
            /* input  */    .enable(1'b1),
            /* output */    .clock_out(mdc_direct)
        );

        /* The D flip-flop to capture the MDIO from the bus */
        reg mdio_reg;
        always @(posedge mdc_direct)
        begin
            mdio_reg <= mdio_in;
        end

        /* Synchronize mdc to component clock */
        cy_psoc3_sync MdcSync
        (
            /* input  */ .clock(op_clock),
            /* input  */ .sc_in(mdc),
            /* output */ .sc_out(mdc_sync)
        );

        /* Synchronize captured mdio to component clock */
        cy_psoc3_sync MdioSync
        (
            /* input  */ .clock(op_clock),
            /* input  */ .sc_in(mdio_reg),
            /* output */ .sc_out(mdio_sync)
        );
    end
    endgenerate

    assign mdio_fin = (EnableExternOE == EXTERN_OE_DISABLED) ? mdio_sync : mdio_in;
    assign mdc_fin  = (EnableExternOE == EXTERN_OE_DISABLED) ? mdc_sync  : mdc;

    /***************************************************************************
    *       Control register implementation
    ***************************************************************************/
    wire [7:0] ctrl;
    /* Control Register bit location (bits 7-3 are unused) */
    localparam [2:0] MDIO_CTRL_ENABLE      = 3'd0;
    localparam [2:0] MDIO_CTRL_INT_ENABLE  = 3'd1;
    localparam [2:0] MDIO_CTRL_FW_DMA_TRIG = 2'd2;

    cy_psoc3_control #(.cy_force_order(1), .cy_ctrl_mode_1(8'h00), .cy_ctrl_mode_0(8'h07)) CtlReg
    (
        /*  input         */  .clock(op_clock),
        /* output [07:00] */  .control(ctrl)
    );

    always @(posedge op_clock)
    begin
        mdio_enable <= ctrl[MDIO_CTRL_ENABLE] & enable;
    end

    /***************************************************************************
    *       MDIO physical address capture
    ***************************************************************************/
    generate
    if(PhyAddressMode == PHYADDR_HARDWARE)
    begin: Hardware
        cy_psoc3_status #(.cy_force_order(1), .cy_md_select(8'h0)) PhyAddr
        (
            /* input         */  .clock(op_clock),
            /* input [07:00] */  .status({3'b0, phy_addr}) /* Bits 7-5 unused */
        );
    end /* Hardware */
    endgenerate

    /***************************************************************************
    *       MDIO frame detection
    ***************************************************************************/
    reg start_detect;
    always @(posedge op_clock)
    begin
        start_detect <= rising_mdc;
    end

    always @(posedge op_clock)
    begin
        /* If disable or TC is detected, not busy */
        if (~mdio_enable | tc)
        begin
            busy <= 1'b0;
        end
        else
        begin
            /* If start bit detected, busy till the counter TC happens */
            busy <= (~mdio_fin & start_detect) | busy;
        end
    end

    /***************************************************************************
    *       MDC bus clock edge detection
    ***************************************************************************/
    always @(posedge op_clock)
    begin
        mdc_dly <= mdc_fin;                      /* Delay MDC */
    end

    assign rising_mdc  =  mdc_fin & ~mdc_dly;  /* Detect rising edge of MDC  */

    /***************************************************************************
    *       Operation code sampling. Opcode is 2-bit field.
    ***************************************************************************/
    localparam [4:0] OPCODE_BIT1_CNT_VAL = 5'd28;
    localparam [4:0] OPCODE_BIT0_CNT_VAL = 5'd27;

    always @(posedge op_clock)
    begin
        if((count[4:0] == OPCODE_BIT1_CNT_VAL) & start_detect)
        begin
            opcode[1] <= mdio_fin;
        end
    end
    always @(posedge op_clock)
    begin
        if((count[4:0] == OPCODE_BIT0_CNT_VAL) & start_detect)
        begin
            opcode[0] <= mdio_fin;
        end
    end

    /***************************************************************************
    *       Count7 block used to count bits on MDIO frame
    ***************************************************************************/
    cy_psoc3_count7 #(.cy_period(BitCountPeriod),.cy_route_ld(`TRUE),.cy_route_en(`TRUE))
    BitCounter
    (
        /*  input          */  .clock(op_clock),
        /*  input          */  .reset(1'b0),
        /*  input          */  .load(ld_count),     /* Re-load counter */
        /*  input          */  .enable(en_count),   /* Counter enabled on rising edges of MDC */
        /*  output [06:00] */  .count(count),
        /*  output         */  .tc(tc)
     );

    assign ld_count = ~busy;             /* Load counter */
    assign en_count = rising_mdc;        /* Enable counter */

    /***************************************************************************
    *       Datapath control signals
    ***************************************************************************/
    /* The turn around bits should happen when counter is 0x10 */
    always @(posedge op_clock)
    begin
        ta_bits <= (count[4:0] == 5'h10);
    end

    /* Check if PHYADDR/DEVADDR matches when last bit of DEVADDR is sampled */
    localparam [4:0] DEVADDR_LAST_BIT_CNT_VAL = 5'd17;

    always @(posedge op_clock)
    begin
        if(~mdio_enable | tc)
        begin
            /* Clear when disabled or not busy */
            addr_match <= 1'b0;
        end
        else
        begin
            /* Set when PHYADDR/DEVADDR matches (ce0 is high) */
            addr_match <= ce0[1] & (count[4:0] == DEVADDR_LAST_BIT_CNT_VAL) | addr_match;
        end
    end

    /* MDIO Frame processing state machine states */
    localparam [2:0] MDIO_SLAVE_STATE_IDLE      = 3'd0;
    localparam [2:0] MDIO_SLAVE_STATE_SHIFT     = 3'd1;
    localparam [2:0] MDIO_SLAVE_STATE_LOAD_MEM  = 3'd2;
    localparam [2:0] MDIO_SLAVE_STATE_LOAD_MSK  = 3'd3;
    localparam [2:0] MDIO_SLAVE_STATE_A1_XOR_A0 = 3'd4;
    localparam [2:0] MDIO_SLAVE_STATE_A1_AND_D1 = 3'd5;
    localparam [2:0] MDIO_SLAVE_STATE_A0_XOR_A1 = 3'd6;
    localparam [2:0] MDIO_SLAVE_STATE_COR       = 3'd7;

    reg  [2:0] fp_state;
    wire [2:0] mdio_cs_addr;

    generate
    if(OperationMode == OPMODE_BASIC)
    /***************************************************************************
    *                       BASIC MODE OF OPERATION
    ***************************************************************************/
    begin: Basic
        /***********************************************************************
        * Capture the shift register data into the write FIFO (F1) two times per
        * frame:
        *  - 1st time: the device address ended (counter equals 17)
        *  - 2nd time: at the end of the frame (tc from the counter)
        ***********************************************************************/
        always @(posedge op_clock)
        begin
            capture <= (ce0[1] & (count[4:0] == DEVADDR_LAST_BIT_CNT_VAL)) | (tc & addr_match);
        end

        /***********************************************************************
        *       MDIO bus drive logic
        ***********************************************************************/
        always @(posedge op_clock)
        begin
            /*******************************************************************
            * Drive the logic low during turn around bits, drive the MDIO out
            * during 16 lower bits of a read frame. Otherwise drive the logic
            * high.
            *******************************************************************/
            mdio_out <= (so & ~ta_bits) | ~(opcode[1] & addr_match) | (count[4] & ~ta_bits);
        end

        /***********************************************************************
        *       Interrupt generation logic
        ***********************************************************************/
        always @(posedge op_clock)
        begin
            /* Generate a pulse if a frame is received and interrupts are
            * enabled */
            interrupt <= tc & capture & ctrl[MDIO_CTRL_INT_ENABLE];
        end

        /***********************************************************************
        *   State machine for MDIO frame processing datapath (Basic mode)
        ***********************************************************************/
        always @(posedge op_clock)
        begin
            if(mdio_enable & rising_mdc)
            begin
                case(fp_state)
                MDIO_SLAVE_STATE_IDLE:
                    /* PHYADDR/DEVADDR matches and OP is Read */
                    if(ta_bits & opcode[1] & addr_match)
                    begin
                        fp_state <= MDIO_SLAVE_STATE_LOAD_MEM;
                    end
                    else
                    begin
                        fp_state <= MDIO_SLAVE_STATE_SHIFT;
                    end
                default:
                    fp_state <= MDIO_SLAVE_STATE_IDLE;
                endcase
            end
            else
            begin
                fp_state <= MDIO_SLAVE_STATE_IDLE;
            end
        end
        /* Use fp_state[1:0] bits to drive MdioDp datapath control signals */
        assign mdio_cs_addr = {1'b0, fp_state[1:0]};
    end
    else
    /***************************************************************************
    *                    ADVANCED MODE OF OPERATION
    ***************************************************************************/
    begin: Advanced /* Advanced mode */
        /* Register config bitmap
        * Bit 7-4: Auxiliary bits. Mapped to aux[4:1]
        * Bit 3  : the register is clear on read (COR)
        * Bit 2  : the register is write only (WO)
        * Bit 1  : trigger interrupt on write
        * Bit 0  : trigger interrupt on read
        */
        localparam [2:0] MDIO_REG_AUX_BIT4     = 3'd7;
        localparam [2:0] MDIO_REG_AUX_BIT3     = 3'd6;
        localparam [2:0] MDIO_REG_AUX_BIT2     = 3'd5;
        localparam [2:0] MDIO_REG_AUX_BIT1     = 3'd4;
        localparam [2:0] MDIO_REG_IS_COR       = 3'd3;
        localparam [2:0] MDIO_REG_IS_WO        = 3'd2;
        localparam [2:0] MDIO_REG_INT_ON_WRITE = 3'd1;
        localparam [2:0] MDIO_REG_INT_ON_READ  = 3'd0;

        wire [7:0] reg_cfg; /* Register configuration */

        /***************************************************************************
        * Depending on the user settings in the customizer a register space can have
        * a data width of 8 or 16 bits, and be located in Flash or SRAM. Two control
        * registers are used to provide these settings to the hardware.
        ***************************************************************************/
        wire [7:0] data_width;
        wire [7:0] mem_type;
        reg is_16bit;       /* Set when the data has a 16 bit width */
        reg is_sram;        /* Set when the register page is located in SRAM */
        reg is_page_en;     /* Enable a page signal for the current page */
        reg addr_is_valid;  /* Indicates whether the current address is valid */

        /* Register config control register (Sync mode) */
        cy_psoc3_control #(.cy_force_order(1), .cy_ctrl_mode_1(8'h00), .cy_ctrl_mode_0(8'hFF)) CfgReg
        (
            /* input          */  .clock(op_clock),
            /* output [07:00] */  .control(reg_cfg)
        );
        /* Data width register settings (Sync mode) */
        cy_psoc3_control #(.cy_force_order(1), .cy_ctrl_mode_1(8'h00), .cy_ctrl_mode_0(8'hFF)) DataWidthCfg
        (
            /*  input         */  .clock(op_clock),
            /* output [07:00] */  .control(data_width)
        );
        /* Register page memory type settings (Sync mode) */
        cy_psoc3_control #(.cy_force_order(1), .cy_ctrl_mode_1(8'h00), .cy_ctrl_mode_0(8'hFF)) MemTypeCfg
        (
            /*  input         */  .clock(op_clock),
            /* output [07:00] */  .control(mem_type)
        );

        /***********************************************************************
        * Auxiliary bits associated with a register is being accessed
        ***********************************************************************/
        assign aux[4:1] = reg_cfg[MDIO_REG_AUX_BIT4:MDIO_REG_AUX_BIT1];

        /***********************************************************************
        *       Opcode detection based on frame type
        ***********************************************************************/
        localparam MDIO_OP_ADDR       = 2'd0;
        localparam MDIO_OP_WRITE      = 2'd1;
        localparam MDIO_OP_READ       = 2'd3;
        localparam MDIO_OP_POS_READ   = 2'd2;

        reg addr_match_dly; /* A one cycle delayed addr_match signal          */
        reg op_address;     /* A pulse at the end of an address frame         */
        reg op_pos_read;    /* A pulse at the end of a pos read frame         */
        reg op_read;        /* A pulse at the end of a read or pos read frame */
        reg op_write;       /* A pulse at the end of a write frame            */
        reg cor_reg;        /* A pulse if addr_match and a COR reg is read    */


        always @(posedge op_clock)
        begin
            addr_match_dly  <= addr_match;
            op_write        <= addr_match & tc & (opcode == MDIO_OP_WRITE);
            op_address      <= addr_match & tc & (opcode == MDIO_OP_ADDR);
            op_pos_read     <= addr_match & tc & (opcode == MDIO_OP_POS_READ);
            op_read         <= addr_match & tc & opcode[1];
            cor_reg         <= addr_match & ~addr_match_dly & opcode[1] & (reg_cfg[MDIO_REG_IS_COR] | force_cor);
        end

        /***********************************************************************
        * Capture the register data into the write FIFO (F1) after a masking or
        * COR operation and if the register is not configured to be read only,
        * the address is valid and the associated register page is enabled.
        * Check only 2 bits for fp_state due to state encoding.
        ***********************************************************************/
        always @(posedge op_clock)
        begin
            capture <= (fp_state[2:1] == 2'b11) & is_sram & addr_is_valid & is_page_en;
        end

        /***********************************************************************
        * Generate a read interrupt if a read or post read frame is received,
        * the accessed register allows an interrupt on read, the address is
        * valid, and the associated register page is enabled.
        ***********************************************************************/
        always @(posedge op_clock)
        begin
            read <= op_read & reg_cfg[MDIO_REG_INT_ON_READ] & addr_is_valid & is_page_en;
        end

        /***********************************************************************
        * Generate a cor interrupt when WrDMA completes and op_code is
        * read or pos_read.
        ***********************************************************************/
        always @(posedge op_clock)
        begin
            cor <= wr_nrq & opcode[1];
        end

        /***********************************************************************
        *       Interrupt generation logic
        ***********************************************************************/
        always @(posedge op_clock)
        begin
            /* Generate a pulse if a write frame is received, interrupts
            *  enabled and the corresponding register allows an interrupt */
            interrupt <= wr_nrq & ~opcode[1] & ctrl[MDIO_CTRL_INT_ENABLE] &
                         reg_cfg[MDIO_REG_INT_ON_WRITE];
        end

        /***********************************************************************
        * Trigger Read DMA at the beginning of each frame to update the FIFO 0
        * of the Frame processing datapath in preparation for a Read frame.
        ***********************************************************************/
        assign rd_dma = busy;

        /***********************************************************************
        *       MDIO bus drive logic
        ***********************************************************************/
        reg cfp_addr; /* Set if the address is between 0x8000 and 0xFFFF */
        reg keep_high;
        always @(posedge op_clock)
        begin
            /*******************************************************************
            * Drive the logic high if not CFP address or register is WO or a
            * frame is not to this slave or OP is not read or disabled.
            *******************************************************************/
            keep_high <= ~cfp_addr | reg_cfg[MDIO_REG_IS_WO] | (~is_page_en & addr_is_valid) |
                         ~(opcode[1] & addr_match) | ~mdio_enable;
        end

        always @(posedge op_clock)
        begin
            /*******************************************************************
            * Drive the logic low during turn around bits or the accessed
            * address does not belong to the allocated CFP table, drive the MDIO
            * out during 16 lower bits of a read frame. Otherwise drive the
            * logic high.
            *******************************************************************/
            mdio_out <= ((so & addr_is_valid) | count[4] | keep_high) & ~ta_bits;
        end

        /***********************************************************************
        * State machine for the MDIO frame processing datapath (Advanced mode)
        ***********************************************************************/
        always @(posedge op_clock)
        begin
            if(mdio_enable)
            begin
                case(fp_state)
                MDIO_SLAVE_STATE_IDLE:
                if(rising_mdc)
                begin
                    /* PHYADDR/DEVADDR matches and OP is Read (Pos Read) */
                    if(ta_bits & opcode[1] & addr_match)
                    begin
                        fp_state <= MDIO_SLAVE_STATE_LOAD_MEM;
                    end
                    else
                    begin
                        fp_state <= MDIO_SLAVE_STATE_SHIFT;
                    end
                end
                else
                begin
                    if(op_write) /* Generated at the end of a write frame */
                    begin
                        /* If a write frame is received, the state machine goes to
                        *  the LOAD MASK state for masking preparation */
                        fp_state <= MDIO_SLAVE_STATE_LOAD_MSK;
                    end
                    else
                    begin
                        /* If a read frame is received and the associated register
                        *  is configured to be COR. */
                        if(cor_reg)
                        begin
                            fp_state <= MDIO_SLAVE_STATE_COR;
                        end
                        else
                        begin
                            fp_state <= MDIO_SLAVE_STATE_IDLE;
                        end
                    end
                end

                MDIO_SLAVE_STATE_COR:
                    /* Clear A1 and load register data from F0 to A0. */
                    fp_state <= MDIO_SLAVE_STATE_IDLE;

                MDIO_SLAVE_STATE_LOAD_MSK:
                    /* Load register value from F0 to A0 and received data bits
                    *  from A0 to A1 */
                    fp_state <= MDIO_SLAVE_STATE_A1_XOR_A0;

                MDIO_SLAVE_STATE_A1_XOR_A0:
                /* Received bits XOR register value stored in register memory */
                begin
                    fp_state <= MDIO_SLAVE_STATE_A1_AND_D1;
                end

                MDIO_SLAVE_STATE_A1_AND_D1:
                /* Mask read only bits and go to next state, where masking
                * bits are XORed with register memory value */
                begin
                    fp_state <= MDIO_SLAVE_STATE_A0_XOR_A1;
                end
                /* Stay in IDLE otherwise */
                default:
                    fp_state <= MDIO_SLAVE_STATE_IDLE;
                endcase
            end
            else
            begin
                fp_state <= MDIO_SLAVE_STATE_IDLE;
            end
        end
        assign mdio_cs_addr = fp_state;

        /***********************************************************************
        *
        *           ADDRESS ANALYZER MODULE
        *
        ***********************************************************************/

        /* FIFO status signals */
        wire [1:0] ac_f0_not_full;
        wire [1:0] ac_f1_not_full;
        wire [1:0] ac_f0_empty;
        wire [1:0] ac_f1_empty;

        /***********************************************************************
        * DMA request signals to write the register space addresses into FIFOs.
        * The FIFO bus status is used only from the LSB datapath since the DMA
        * accesses a 16-bit UDB address space.
        ***********************************************************************/
        assign rs_dma0 = ac_f0_not_full[0];
        assign rs_dma1 = ac_f1_not_full[0];
        /* Start processing if an address or post read frame is received */
        wire start_analysis = op_address | op_pos_read;

        /***********************************************************************
        * Datapath conditional outputs are used to determine if an address is in
        * the range and which register space is accessed. The A0 is compared to
        * D0 and D1 at the same time. The calculation is based on ce0, cl0, ce1
        * and cl1 datapath outputs.
        ************************************************************************/
        wire [1:0] rsce0; /* high, if an address is equal to the start address */
        wire [1:0] rsce1; /* high, if an address is equal to the end address   */
        wire [1:0] rscl0; /* high, if an address is below the start address    */
        wire [1:0] rscl1; /* high, if an address is below the end address      */

        /***********************************************************************
        * The address is considered in the range if it belongs to one of the
        * register space boundaries.
        * The conditionals are chained, so use the outputs from the MSB
        * datapath only
        ***********************************************************************/
        reg addr_in_range;
        always @(posedge op_clock)
        begin
            addr_in_range <= ((~rscl0[1] & rscl1[1]) | rsce0[1] | rsce1[1]);
        end

        reg [2:0] rs_count;     /* Register space (page) index */
        reg [2:0] current_page; /* Store index of the current page */

        wire rs_tc = (rs_count == (NumRegSpaces-1));

        localparam [3:0] MDIO_AC_STATE_IDLE        = 4'b0000;
        localparam [3:0] MDIO_AC_STATE_SHIFT       = 4'b0001;
        localparam [3:0] MDIO_AC_STATE_INC_ADDR    = 4'b0010;
        localparam [3:0] MDIO_AC_STATE_MULT        = 4'b0011;
        localparam [3:0] MDIO_AC_STATE_STORE_ADDR  = 4'b0100;
        localparam [3:0] MDIO_AC_STATE_COMP        = 4'b0101;
        localparam [3:0] MDIO_AC_STATE_WAIT        = 4'b0110;
        localparam [3:0] MDIO_AC_STATE_CALC_IDX    = 4'b0111;
        localparam [3:0] MDIO_AC_STATE_LOAD_RS     = 4'b1000;

        reg [3:0] rs_state;

        /* Generate a pulse when the last received address is updated with the
        * new one, and the frame is not a post read frame. */
        always @(posedge op_clock)
        begin
            /* Check only 3 bits of rs_state due to state encoding */
            address <= (rs_state[2:0] == 3'b100) & ~opcode[1];
        end

        wire rs_load = rs_state[3];
        /* rs_wait is generated when the address comparison state machine
        * is in the WAIT state. Check only 3 bits due to state encoding. */
        wire rs_wait = (rs_state[2:0] == 3'b110);

        reg rs_update; /* Indicates when the rs_count needs update */
        always @(posedge op_clock)
        begin
            rs_update <= rs_wait;
        end

        /***********************************************************************
        * The rs_addr_ready calculation is based on the register space start
        * address FIFO (F0) and register space end address FIFO (F1). Both FIFOs
        * are updated by individual DMA channels, therefore the data from FIFOs
        * must be loaded only if both FIFOs are not empty.
        ***********************************************************************/
        wire rs_addr_ready = ~ac_f0_empty[0] & ~ac_f1_empty[0];

        /***********************************************************************
        * The next page indicates when the state machine for an address
        * comparison can transit from the STORE_ADDR or COMP state to the next
        * state.
        ***********************************************************************/
        reg next_page;
        always @(posedge op_clock)
        begin
            next_page <= ((rs_state == MDIO_AC_STATE_STORE_ADDR) | (rs_state == MDIO_AC_STATE_COMP)) & rs_addr_ready;
        end

        /***********************************************************************
        * addr_is_valid is used to store whether the last accessed address
        * is valid. Set if the address is in the range and cleared when the
        * address analysis starts.
        ***********************************************************************/
        always @(posedge op_clock)
        begin
            addr_is_valid <= ((addr_in_range & rs_update) | addr_is_valid) & ~start_analysis;
        end

        /***********************************************************************
        * Any access to addresses between 0x0000 and 0x7FFF should be ignored
        * (no activity in the MDIO bus). To determine if the address is in the
        * range between 0x0000 and 0x7FFF the MSB address bit is checked when
        * the state machine is in the STORE_ADDR state.
        ***********************************************************************/
        wire address_msb;       /* so out of AddrComp datapath */
        always @(posedge op_clock)
        begin
            /* Check only 3 bits due to state encoding */
            if(rs_state[2:0] == 3'b100)
            begin
                cfp_addr <= address_msb;
            end
        end

        /***********************************************************************
        *       State machine for address compare (AddrComp) datapath
        ***********************************************************************/
        always @(posedge op_clock)
        begin
            case(rs_state)
            MDIO_AC_STATE_IDLE:
                /* IDLE until enabled */
                if(start_analysis)
                /* Start processing if address or post read frame received */
                begin
                    if(op_address)
                    begin
                        rs_state <= MDIO_AC_STATE_STORE_ADDR;
                    end
                    else
                    begin
                        rs_state <= MDIO_AC_STATE_INC_ADDR;
                    end
                end
                else
                /* If the component is enabled and not processing an address
                * frame, shift the MDIO data on the MDC rising edge. */
                begin
                    if(rising_mdc & busy)
                    begin
                        rs_state <= MDIO_AC_STATE_SHIFT;
                    end
                    else
                    begin
                        rs_state <= MDIO_AC_STATE_IDLE;
                    end
                end

            MDIO_AC_STATE_INC_ADDR:
                /* If a post read frame is received, increment the address
                * previously stored in A1 and start an analysis */
                rs_state <= MDIO_AC_STATE_STORE_ADDR;

            MDIO_AC_STATE_STORE_ADDR:
                /* If an address frame is received, store the address in A1.
                * Move to the next state if the register space address FIFOs
                * are not empty. */
                if(next_page)
                begin
                    rs_state <= MDIO_AC_STATE_LOAD_RS;
                end

            MDIO_AC_STATE_LOAD_RS:
                /* In this state d0_load and d1_load are generated to load
                * the register space boundaries from F0 to D0 (start address)
                * and F1 to D1 (end address). */
                rs_state <= MDIO_AC_STATE_WAIT;

            MDIO_AC_STATE_WAIT:
                /* One cycle delay due to addr_in_range pipelining */
                rs_state <= MDIO_AC_STATE_COMP;

           MDIO_AC_STATE_COMP:
                /* If the address belongs to the current register space,
                *  go to the CALC IDX state and calculate the register
                *  index within given register space. */
                if(next_page)
                begin
                    if(addr_in_range)
                    begin
                        rs_state <= MDIO_AC_STATE_CALC_IDX;
                    end
                    else
                    begin
                        /* Move to IDLE if rs_count done, else load next reg space
                        *  boundary */
                        rs_state <= (rs_count == 3'd0) ? MDIO_AC_STATE_IDLE : MDIO_AC_STATE_LOAD_RS;
                    end
                end
                else
                begin
                    rs_state <= MDIO_AC_STATE_COMP;
                end

            MDIO_AC_STATE_CALC_IDX:
                /* In this state a register index within a register space
                * is calculated, by subtracting the register space start
                * address from the current address. */
                if(is_16bit)
                begin
                    rs_state <= MDIO_AC_STATE_MULT;
                end
                else
                begin
                    rs_state <= (rs_count == 3'd0) ? MDIO_AC_STATE_IDLE : MDIO_AC_STATE_LOAD_RS;
                end

            MDIO_AC_STATE_MULT:
                /* If a 16-bit register is accessed, multiply the index by two.
                * If all register spaces are processed, move to the IDLE
                * state. Else go to the LOAD state. */
                rs_state <= (rs_count == 3'd0) ? MDIO_AC_STATE_IDLE : MDIO_AC_STATE_LOAD_RS;

            default:
                rs_state <= MDIO_AC_STATE_IDLE;
            endcase
        end

        /* Register page width config MUX (8 to 1) */
        always @(posedge op_clock)
        begin
            case(current_page)
                MDIO_PAGE1: is_16bit <= data_width[MDIO_PAGE1];
                MDIO_PAGE2: is_16bit <= data_width[MDIO_PAGE2];
                MDIO_PAGE3: is_16bit <= data_width[MDIO_PAGE3];
                MDIO_PAGE4: is_16bit <= data_width[MDIO_PAGE4];
                MDIO_PAGE5: is_16bit <= data_width[MDIO_PAGE5];
                MDIO_PAGE6: is_16bit <= data_width[MDIO_PAGE6];
                MDIO_PAGE7: is_16bit <= data_width[MDIO_PAGE7];
                MDIO_PAGE8: is_16bit <= data_width[MDIO_PAGE8];
            default:
                is_16bit <= data_width[MDIO_PAGE1];
            endcase
        end

        /* Register page memory type config MUX (8 to 1) */
        always @(posedge op_clock)
        begin
            case(current_page)
                MDIO_PAGE1: is_sram <= mem_type[MDIO_PAGE1];
                MDIO_PAGE2: is_sram <= mem_type[MDIO_PAGE2];
                MDIO_PAGE3: is_sram <= mem_type[MDIO_PAGE3];
                MDIO_PAGE4: is_sram <= mem_type[MDIO_PAGE4];
                MDIO_PAGE5: is_sram <= mem_type[MDIO_PAGE5];
                MDIO_PAGE6: is_sram <= mem_type[MDIO_PAGE6];
                MDIO_PAGE7: is_sram <= mem_type[MDIO_PAGE7];
                MDIO_PAGE8: is_sram <= mem_type[MDIO_PAGE8];
            default:
                is_sram <= mem_type[MDIO_PAGE1];
            endcase
        end

        /* Enable page signal MUX (8 to 1) */
        always @(posedge op_clock)
        begin
            case(current_page)
                MDIO_PAGE1: is_page_en <= en_page[MDIO_PAGE1];
                MDIO_PAGE2: is_page_en <= en_page[MDIO_PAGE2];
                MDIO_PAGE3: is_page_en <= en_page[MDIO_PAGE3];
                MDIO_PAGE4: is_page_en <= en_page[MDIO_PAGE4];
                MDIO_PAGE5: is_page_en <= en_page[MDIO_PAGE5];
                MDIO_PAGE6: is_page_en <= en_page[MDIO_PAGE6];
                MDIO_PAGE7: is_page_en <= en_page[MDIO_PAGE7];
                MDIO_PAGE8: is_page_en <= en_page[MDIO_PAGE8];
            default:
                is_page_en <= en_page[MDIO_PAGE1];
            endcase
        end

        /* Determine index of accessed register page */
        always @(posedge op_clock)
        begin
            if(addr_in_range & rs_update)
            begin
                current_page <= rs_count;
            end
        end

        /***********************************************************************
        * A 3-bit counter is used to count register spaces when the state
        * machine goes over all register spaces to determine which register
        * space is accessed.
        ************************************************************************/
        always @(posedge op_clock)
        begin
            if(~mdio_enable)
            begin
                rs_count <= 3'd0;
            end
            else
            begin
                if(rs_update)
                begin
                    /* Reload counter on period */
                    rs_count <= (rs_tc) ? 3'd0 : rs_count + 1'b1;
                end
                else
                begin
                    rs_count <= rs_count;
                end
            end
        end

        localparam [3:0] MDIO_BA_STATE_RESET            = 4'b0000;
        localparam [3:0] MDIO_BA_STATE_HOLD             = 4'b0001;
        localparam [3:0] MDIO_BA_STATE_INC_OFFSET       = 4'b0011;
        localparam [3:0] MDIO_BA_STATE_UPDATE_INFO      = 4'b1001;
        localparam [3:0] MDIO_BA_STATE_LOAD_LSB         = 4'b0101;
        localparam [3:0] MDIO_BA_STATE_CALC_LSB         = 4'b0100;
        localparam [3:0] MDIO_BA_STATE_UPDATE_LSB       = 4'b0110;
        localparam [3:0] MDIO_BA_STATE_LOAD_MSB         = 4'b1101;
        localparam [3:0] MDIO_BA_STATE_CALC_MSB         = 4'b1111;
        localparam [3:0] MDIO_BA_STATE_UPDATE_MSB       = 4'b1110;
        localparam [3:0] MDIO_BA_STATE_SHIFT_1X         = 4'b1010;
        localparam [3:0] MDIO_BA_STATE_SHIFT_2X         = 4'b0010;

        reg [3:0] ba_state;

        /* Carry is asserted if a register space crosses 64K memory block */
        wire [1:0] co_reg; /* Carry out from AddrCalc datapath */
        reg carry;
        /* Sample carry out from the lower address bits computation one clock
        *  after the state machine transits from CALC_LSB to UPDATE_LSB */
        reg sample_carry;

        always @(posedge op_clock)
        begin
            /* Only 3 bits of the register state need to be checked */
            sample_carry <= (ba_state[2:0] == 3'b100);
        end

        always @(posedge op_clock)
        begin
            if(sample_carry)
            begin
                carry <= co_reg[1];
            end
        end

        /***********************************************************************
        * The procedure to determine the register address into the PSoC memory
        * is the same as determining an address for the register configuration.
        * Therefore the state machine can use the same states and some
        * indication when exit address processing.
        * cfg_done indicates that the register configuration address is being
        * processed. The signal is checked in MSB_UPDATE state to exit from the
        * address calculation procedure.
        ***********************************************************************/
        reg cfg_done;
        always @(posedge op_clock)
        /* Set in SHIFT_1X/SHIFT_2X and clear in RESET. Use only 3 bits of
        *  state register to save logic resources. */
        begin
            cfg_done <= (cfg_done | (ba_state[2:0] == 3'b010)) & ~(ba_state[2:0] == 3'b000);
        end

        /* Trigger a DMA to move physical (PSoC) addresses of the register space
        *  memory and config array for the associated register space to the
        *  address calculation datapath FIFO. */
        always @(posedge op_clock)
        begin
            /* 3'b110 = (MDIO_BA_STATE_UPDATE_LSB | MDIO_BA_STATE_UPDATE_MSB)
            *  3'b111 = MDIO_AC_STATE_CALC_IDX
            *  Check only 3 bits due to state encoding */
            addr_dma <= (ba_state[2:0] == 3'b110) | (rs_state[2:0] == 3'b111);
        end
        always @(posedge op_clock)
        begin
            info_dma <= addr_nrq & (ba_state == MDIO_BA_STATE_UPDATE_INFO);
        end
        /* Trigger DMA to update register configuration */
        always @(posedge op_clock)
        begin
            cfg_dma <= addr_nrq & cfg_done & (ba_state == MDIO_BA_STATE_UPDATE_MSB);
        end

        always @(posedge op_clock)
        begin
            case(ba_state)
            MDIO_BA_STATE_RESET:
                /* Load the start address of the array that contains the physical
                * memory and configuration addresses for all the register spaces
                * from D0 to A0. Clear A1. */
                ba_state <= MDIO_BA_STATE_HOLD;

            MDIO_BA_STATE_HOLD:
                /* Hold state. Move to RESET when address analysis starts */
                if(start_analysis)
                begin
                    ba_state <= MDIO_BA_STATE_RESET;
                end
                else
                begin
                    /* Move to next state if register space boundary is
                    * loaded in address comparison (AddrComp) datapath. */
                    if(rs_wait)
                    begin
                        ba_state <= MDIO_BA_STATE_INC_OFFSET;
                    end
                    else
                    begin
                        ba_state <= MDIO_BA_STATE_HOLD;
                    end
                end

            MDIO_BA_STATE_INC_OFFSET:
                /* Increment A0 by 8 to point to the next register space. */
                if(addr_in_range)
                /* If an address belongs to the current register space, trigger a DMA
                *  to update physical (PSoC) addresses of the register space memory
                *  and config array for the associated register space. */
                begin
                    ba_state <= MDIO_BA_STATE_UPDATE_INFO;
                end
                else
                begin
                    ba_state <= MDIO_BA_STATE_HOLD;
                end

            MDIO_BA_STATE_UPDATE_INFO:
                /***************************************************************
                * In this state AddrDMA is triggered to transfer the register
                * index within the current register space from A0 reg of the
                * AddrComp datapath to A1 reg of the AddrCalc datapath. Then
                * InfoDMA transfers the physical (PSoC) addresses of the register
                * space memory and config array for the associated register
                * space into F0 of the AddrCalc datapath.
                ***************************************************************/
                if(info_nrq)
                begin
                    ba_state <= MDIO_BA_STATE_LOAD_LSB;
                end

            MDIO_BA_STATE_LOAD_LSB:
                /* Load lower 16 bit of physical memory for given
                *  register space (F0 -> A0) */
                ba_state <= MDIO_BA_STATE_CALC_LSB;

            MDIO_BA_STATE_CALC_LSB:
                /* Add register index to lower 16 address bits */
                ba_state <= MDIO_BA_STATE_UPDATE_LSB;

            MDIO_BA_STATE_UPDATE_LSB:
                /* Trigger AddrDMA to update 16 lower address bits of Write
                * and Read DMAs. Wait until the transfer is completed and move to
                * next state. */
                if(addr_nrq)
                begin
                    ba_state <= MDIO_BA_STATE_LOAD_MSB;
                end

            MDIO_BA_STATE_LOAD_MSB:
                /* Load upper 16 bit of physical memory for given
                *  register space (F0 -> A0) */
                if(carry)
                /* Check carry from addition of lower address bits */
                begin
                    ba_state <= MDIO_BA_STATE_CALC_MSB;
                end
                else
                begin
                    ba_state <= MDIO_BA_STATE_UPDATE_MSB;
                end

            MDIO_BA_STATE_CALC_MSB:
                /* Increment upper 16 address bits */
                ba_state <= MDIO_BA_STATE_UPDATE_MSB;

            MDIO_BA_STATE_UPDATE_MSB:
                /* Trigger AddrDMA to update 16 upper address bits of Write
                * and Read DMAs. Wait until transfer is competed and move to
                * next state. */
                if(addr_nrq)
                begin
                    /* Check whether both register memory address and register
                    * configuration address were calculated. If yes, move to
                    * RESET state. Otherwise move to SHIFT states and go through
                    * LOAD_LSB - UPDATE_MSB one more time to calculate
                    * register configuration address. */
                    if(cfg_done)
                    begin
                        ba_state <= MDIO_BA_STATE_RESET;
                    end
                    else
                    begin
                        ba_state <= MDIO_BA_STATE_SHIFT_1X;
                    end
                end
                else
                begin
                    ba_state <= MDIO_BA_STATE_UPDATE_MSB;
                end

            MDIO_BA_STATE_SHIFT_1X:
                /* Each register has 4 bytes of the configuration data. Multiply the
                * index by two to determine the offset within the configuration data
                * array. */
                if(is_16bit)
                begin
                    ba_state <= MDIO_BA_STATE_LOAD_LSB;
                end
                else
                begin
                    ba_state <= MDIO_BA_STATE_SHIFT_2X;
                end

            MDIO_BA_STATE_SHIFT_2X:
                /* Shift index one more time if 8-bit register space
                *  is accessed. */
                ba_state <= MDIO_BA_STATE_LOAD_LSB;

            default:
                ba_state <= MDIO_BA_STATE_RESET;
            endcase
        end

        /***********************************************************************
        * FwAlu datapath control. This datapath along with a DMA is used to
        * implement atomic firmware operations, especially SetBits API.
        ***********************************************************************/

        localparam [1:0] MDIO_FW_STATE_IDLE  = 2'b00;
        localparam [1:0] MDIO_FW_STATE_WAIT1 = 2'b01;
        localparam [1:0] MDIO_FW_STATE_OR    = 2'b11;
        localparam [1:0] MDIO_FW_STATE_WAIT2 = 2'b10;

        reg [1:0] fw_state;

        always @(posedge op_clock)
        begin
            case(fw_state)
            MDIO_FW_STATE_IDLE:
                if(fw_dma1)
                begin
                    fw_state <= MDIO_FW_STATE_WAIT1;
                end

            MDIO_FW_STATE_WAIT1:
                if(fw_nrq1)
                begin
                    fw_state <= MDIO_FW_STATE_OR;
                end

            MDIO_FW_STATE_OR:
                fw_state <= MDIO_FW_STATE_WAIT2;

            MDIO_FW_STATE_WAIT2:
                if(fw_nrq2)
                begin
                    fw_state <= MDIO_FW_STATE_IDLE;
                end
            default
                fw_state <= MDIO_FW_STATE_IDLE;
            endcase
        end

        /* Generate DMA request only when component is not busy */
        reg fw_req;
        reg fw_req_dly;
        always @(posedge op_clock)
        begin
            if(~busy)
            begin
                fw_req <= ctrl[MDIO_CTRL_FW_DMA_TRIG];
            end
            fw_req_dly <= fw_req; /* One cycle delay fw_req */
            fw_dma1 <= fw_req ^ fw_req_dly; /* Pulse when fw_req changes */
            fw_dma2 <= (fw_state == MDIO_FW_STATE_WAIT2); /* Trigger FwDMA2 after FwDMA1 completes */
        end

        /***********************************************************************
        * The FwDMA status register. Used to detect the end of DMA transfers
        * triggered in SetData(), GetData() and SetBits() APIs.
        ***********************************************************************/
        cy_psoc3_status #(.cy_force_order(1), .cy_md_select(8'h3)) FwDmaStatus
        (
            /* input         */  .clock(op_clock),
            /* input [07:00] */  .status({6'h0, fw_nrq2, fw_nrq1}) /* Bits 7-2 unused */
        );

        /***********************************************************************
        * A 16-bit address comparator. Loads the register space boundaries from
        * FIFOs to the D registers. Compares A0 (address) to D registers and
        * generates compare conditions.
        ***********************************************************************/
        cy_psoc3_dp16 #(.cy_dpconfig_a(
        {
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM0:  Idle*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP___SL, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM1:  Shift in MDIO*/
            `CS_ALU_OP__INC, `CS_SRCA_A1, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC__ALU,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM2:  Inc addr if post read*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP___SL, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGB,
            `CS_CMP_SEL_CFGA, /*CFGRAM3:  Multiply by two if 16-bit reg accessed*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM4:  Store current address*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM5:  Idle*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM6:  Idle*/
            `CS_ALU_OP__SUB, `CS_SRCA_A1, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM7:  Calculate reg idx that is accessed*/
            8'hFF, 8'h00,  /*CFG9:  */
            8'hFF, 8'hFF,  /*CFG11-10:  */
            `SC_CMPB_A1_D1, `SC_CMPA_A0_D1, `SC_CI_B_ARITH,
            `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
            `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
            `SC_SI_A_ROUTE, /*CFG13-12:  */
            `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
            1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
            `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
            `SC_FB_NOCHN, `SC_CMP1_NOCHN,
            `SC_CMP0_NOCHN, /*CFG15-14:  */
            10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
            `SC_FIFO_LEVEL,`SC_FIFO_ASYNC,`SC_EXTCRC_DSBL,
            `SC_WRK16CAT_DSBL /*CFG17-16:  */
        }
        ), .cy_dpconfig_b(
        {
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM0:  Idle*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP___SL, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM1:  Shift in MDIO*/
            `CS_ALU_OP__INC, `CS_SRCA_A1, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC__ALU,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM2:  Inc address if post read frame*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP___SL, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM3:  Multiply by two if 16-bit reg accessed*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM4:  Store current address*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM5:  Idle*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM6:  Idle*/
            `CS_ALU_OP__SUB, `CS_SRCA_A1, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM7:  Calculate reg idx that is accessed*/
            8'hFF, 8'h00,  /*CFG9:  */
            8'hFF, 8'hFF,  /*CFG11-10:  */
            `SC_CMPB_A1_D1, `SC_CMPA_A0_D1, `SC_CI_B_ARITH,
            `SC_CI_A_CHAIN, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
            `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
            `SC_SI_A_CHAIN, /*CFG13-12:  */
            `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
            1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
            `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
            `SC_FB_NOCHN, `SC_CMP1_CHNED,
            `SC_CMP0_CHNED, /*CFG15-14:  */
            10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
            `SC_FIFO_LEVEL,`SC_FIFO_ASYNC,`SC_EXTCRC_DSBL,
            `SC_WRK16CAT_DSBL /*CFG17-16:  */
        }
        )) AddrComp
        (
            /*  input                   */  .reset(1'b0),
            /*  input                   */  .clk(op_clock),
            /*  input   [02:00]         */  .cs_addr(rs_state[2:0]),
            /*  input                   */  .route_si(mdio_fin),
            /*  input                   */  .route_ci(1'b0),
            /*  input                   */  .f0_load(1'b0),
            /*  input                   */  .f1_load(1'b0),
            /*  input                   */  .d0_load(rs_load),
            /*  input                   */  .d1_load(rs_load),
            /*  output  [01:00]         */  .ce0(rsce0),
            /*  output  [01:00]         */  .cl0(rscl0),
            /*  output  [01:00]         */  .z0(),
            /*  output  [01:00]         */  .ff0(),
            /*  output  [01:00]         */  .ce1(rsce1),
            /*  output  [01:00]         */  .cl1(rscl1),
            /*  output  [01:00]         */  .z1(),
            /*  output  [01:00]         */  .ff1(),
            /*  output  [01:00]         */  .ov_msb(),
            /*  output  [01:00]         */  .co_msb(),
            /*  output  [01:00]         */  .cmsb(),
            /*  output  [01:00]         */  .so({address_msb, nc3}),
            /*  output  [01:00]         */  .f0_bus_stat(ac_f0_not_full),
            /*  output  [01:00]         */  .f0_blk_stat(ac_f0_empty),
            /*  output  [01:00]         */  .f1_bus_stat(ac_f1_not_full),
            /*  output  [01:00]         */  .f1_blk_stat(ac_f1_empty)
        );

        cy_psoc3_dp16 #(.cy_dpconfig_a(
        {
            `CS_ALU_OP__XOR, `CS_SRCA_A1, `CS_SRCB_A1,
            `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC__ALU,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM0:  Load base addr from D0 to A0; Clear A1;*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM1:  Idle*/
            `CS_ALU_OP_PASS, `CS_SRCA_A1, `CS_SRCB_D0,
            `CS_SHFT_OP___SL, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM2:  Multiple reg index by 2 (A1 << 1)*/
            `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_A1,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC___D1,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM3:  A0 = A0 + A1; A1 = 8;*/
            `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_A1,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM4:  The lower 16 address bits + index*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC___F0, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM5:  Load 16-bit address from F0 to A0*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM6:  Idle (Wait for DMA to complete transfer)*/
            `CS_ALU_OP__INC, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM7:  Incerement the upper address if required*/
            8'hFF, 8'h00,  /*CFG9:   */
            8'hFF, 8'hFF,  /*CFG11-10:   */
            `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
            `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
            `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
            `SC_SI_A_DEFSI, /*CFG13-12:   */
            `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
            1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
            `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
            `SC_FB_NOCHN, `SC_CMP1_NOCHN,
            `SC_CMP0_NOCHN, /*CFG15-14:   */
            10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
            `SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
            `SC_WRK16CAT_DSBL /*CFG17-16:   */
        }
        ), .cy_dpconfig_b(
        {
            `CS_ALU_OP__XOR, `CS_SRCA_A1, `CS_SRCB_A1,
            `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC__ALU,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM0:  Load base address to A0; Clear A1;*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM1:  Idle*/
            `CS_ALU_OP_PASS, `CS_SRCA_A1, `CS_SRCB_D0,
            `CS_SHFT_OP___SL, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM2:  Multiple reg index by 2 (A1 << 1)*/
            `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_A1,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC___D1,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM3:  A0 = A0 + A1; A1 = 8;*/
            `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_A1,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM4:  The lower 16 address bits + index*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC___F0, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM5:  Load 16-bit address from F0 to A0*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM6:  Idle (Wait for DMA to complete transfer)*/
            `CS_ALU_OP__INC, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM7:  Incerement the upper address if required*/
            8'hFF, 8'h00,  /*CFG9:   */
            8'hFF, 8'hFF,  /*CFG11-10:   */
            `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
            `SC_CI_A_CHAIN, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
            `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
            `SC_SI_A_CHAIN, /*CFG13-12:  */
            `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
            1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
            `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
            `SC_FB_NOCHN, `SC_CMP1_NOCHN,
            `SC_CMP0_NOCHN, /*CFG15-14:  */
            10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
            `SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
            `SC_WRK16CAT_DSBL /*CFG17-16:  */
        }
        )) AddrCalc
        (
            /*  input                   */  .reset(1'b0),
            /*  input                   */  .clk(op_clock),
            /*  input   [02:00]         */  .cs_addr(ba_state[2:0]),
            /*  input                   */  .route_si(1'b0),
            /*  input                   */  .route_ci(1'b0),
            /*  input                   */  .f0_load(1'b0),
            /*  input                   */  .f1_load(1'b0),
            /*  input                   */  .d0_load(1'b0),
            /*  input                   */  .d1_load(1'b0),
            /*  output  [01:00]         */  .ce0(),
            /*  output  [01:00]         */  .cl0(),
            /*  output  [01:00]         */  .z0(),
            /*  output  [01:00]         */  .ff0(),
            /*  output  [01:00]         */  .ce1(),
            /*  output  [01:00]         */  .cl1(),
            /*  output  [01:00]         */  .z1(),
            /*  output  [01:00]         */  .ff1(),
            /*  output  [01:00]         */  .ov_msb(),
            /*  output  [01:00]         */  .co_msb_reg(co_reg),
            /*  output  [01:00]         */  .cmsb(),
            /*  output  [01:00]         */  .so(),
            /*  output  [01:00]         */  .f0_bus_stat(),
            /*  output  [01:00]         */  .f0_blk_stat(),
            /*  output  [01:00]         */  .f1_bus_stat(),
            /*  output  [01:00]         */  .f1_blk_stat()
        );

        cy_psoc3_dp16 #(.cy_dpconfig_a(
        {
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM0:  */
            `CS_ALU_OP___OR, `CS_SRCA_A0, `CS_SRCB_A1,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM1:  A0 = A0 OR A1*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM2:  */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM3:  */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM4:  */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM5:  */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM6:  */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM7:  */
            8'hFF, 8'h00,  /*CFG9:  */
            8'hFF, 8'hFF,  /*CFG11-10:  */
            `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
            `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
            `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
            `SC_SI_A_DEFSI, /*CFG13-12:  */
            `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
            1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
            `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
            `SC_FB_NOCHN, `SC_CMP1_NOCHN,
            `SC_CMP0_NOCHN, /*CFG15-14:  */
            10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
            `SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
            `SC_WRK16CAT_DSBL /*CFG17-16:  */
        }
        ), .cy_dpconfig_b(
        {
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM0:  */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM1:  A0 = A0 OR A1*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM2:  */
            `CS_ALU_OP___OR, `CS_SRCA_A0, `CS_SRCB_A1,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM3:  A0 = A0 OR A1*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM4:  */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM5:  */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM6:  */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM7:  */
            8'hFF, 8'h00,  /*CFG9:  */
            8'hFF, 8'hFF,  /*CFG11-10:  */
            `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
            `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
            `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
            `SC_SI_A_DEFSI, /*CFG13-12:  */
            `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
            1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
            `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
            `SC_FB_NOCHN, `SC_CMP1_NOCHN,
            `SC_CMP0_NOCHN, /*CFG15-14:  */
            10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
            `SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
            `SC_WRK16CAT_DSBL /*CFG17-16:  */
        }
        )) FwAlu
        (
            /*  input                   */  .reset(1'b0),
            /*  input                   */  .clk(op_clock),
            /*  input   [02:00]         */  .cs_addr({1'b0, fw_state}),
            /*  input                   */  .route_si(1'b0),
            /*  input                   */  .route_ci(1'b0),
            /*  input                   */  .f0_load(1'b0),
            /*  input                   */  .f1_load(1'b0),
            /*  input                   */  .d0_load(1'b0),
            /*  input                   */  .d1_load(1'b0),
            /*  output  [01:00]         */  .ce0(),
            /*  output  [01:00]         */  .cl0(),
            /*  output  [01:00]         */  .z0(),
            /*  output  [01:00]         */  .ff0(),
            /*  output  [01:00]         */  .ce1(),
            /*  output  [01:00]         */  .cl1(),
            /*  output  [01:00]         */  .z1(),
            /*  output  [01:00]         */  .ff1(),
            /*  output  [01:00]         */  .ov_msb(),
            /*  output  [01:00]         */  .co_msb(),
            /*  output  [01:00]         */  .cmsb(),
            /*  output  [01:00]         */  .so(),
            /*  output  [01:00]         */  .f0_bus_stat(),
            /*  output  [01:00]         */  .f0_blk_stat(),
            /*  output  [01:00]         */  .f1_bus_stat(),
            /*  output  [01:00]         */  .f1_blk_stat()
        );
    end

    endgenerate

    /***************************************************************************
    * 16-bit datapath configured as MDIO shift registers and parallel to
    * serial interface.
    ***************************************************************************/
    cy_psoc3_dp16 #(.cy_dpconfig_a(
    {
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM0:  Idle*/
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP___SL, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM1:  Shift the mdio input in A0*/
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC___F0, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM2:  Load the data to be read from F0*/
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC___F0, `CS_A1_SRC__ALU,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM3:  Load A0 (VAL) to A1; F0 (MEM) to A0*/
        `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A1,
        `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM4:  A1 = A0 (MEM) xor A1 (VAL)*/
        `CS_ALU_OP__AND, `CS_SRCA_A1, `CS_SRCB_D1,
        `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM5:  A1 = A1 AND D1 (MASK)*/
        `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A1,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM6:  A0 = A1 XOR A0 (MEM)*/
        `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM7:  COR operation*/
        8'hFF, 8'h00,  /*CFG9:  */
        8'hFF, 8'hFF,  /*CFG11-10:  Phy Address Match*/
        `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
        `SC_CI_A_ARITH, `SC_C1_MASK_ENBL, `SC_C0_MASK_ENBL,
        `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
        `SC_SI_A_ROUTE, /*CFG13-12:  */
        `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
        1'h0, `SC_FIFO1__A0, `SC_FIFO0_BUS,
        `SC_MSB_DSBL, `SC_MSB_BIT7, `SC_MSB_NOCHN,
        `SC_FB_NOCHN, `SC_CMP1_NOCHN,
        `SC_CMP0_NOCHN, /*CFG15-14:  */
        10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
        `SC_FIFO__EDGE,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
        `SC_WRK16CAT_DSBL /*CFG17-16:  */
    }
    ), .cy_dpconfig_b(
    {
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM0:  Idle*/
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP___SL, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM1:  Shift the mdio data in A0*/
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC___F0, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM2:  Load the data to be read from F0*/
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC___F0, `CS_A1_SRC__ALU,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM3:  Load A0 (VAL) to A1; F0 (MEM) to A0*/
        `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A1,
        `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM4:  A1 = A0 (MEM) xor A1 (VAL)*/
        `CS_ALU_OP__AND, `CS_SRCA_A1, `CS_SRCB_D1,
        `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM5:  A1 = A1 AND D1 (MASK)*/
        `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A1,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM6:  A0 = A1 XOR A0 (MEM)*/
        `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM7: COR operation*/
        8'hFF, 8'h00,  /*CFG9:  */
        8'hFF, PHYADDR_DP_MASK,  /*CFG11-10:  Phy Address Match */
        `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
        `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_ENBL,
        `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
        `SC_SI_A_CHAIN, /*CFG13-12:  */
        `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
        1'h0, `SC_FIFO1__A0, `SC_FIFO0_BUS,
        `SC_MSB_DSBL, `SC_MSB_BIT7, `SC_MSB_NOCHN,
        `SC_FB_NOCHN, `SC_CMP1_CHNED,
        `SC_CMP0_CHNED, /*CFG15-14:  */
        10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
        `SC_FIFO__EDGE,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
        `SC_WRK16CAT_DSBL /*CFG17-16:  */
    }
    )) MdioDp
    (
        /*  input                   */  .reset(1'b0),
        /*  input                   */  .clk(op_clock),
        /*  input   [02:00]         */  .cs_addr(mdio_cs_addr),
        /*  input                   */  .route_si(mdio_fin),
        /*  input                   */  .route_ci(1'b0),
        /*  input                   */  .f0_load(1'b0),
        /*  input                   */  .f1_load(capture),
        /*  input                   */  .d0_load(1'b0),
        /*  input                   */  .d1_load(1'b0),
        /*  output  [01:00]         */  .ce0(ce0), /* PHYADRR/DEVADDR detect */
        /*  output  [01:00]         */  .cl0(),
        /*  output  [01:00]         */  .z0(),
        /*  output  [01:00]         */  .ff0(),
        /*  output  [01:00]         */  .ce1(),
        /*  output  [01:00]         */  .cl1(),
        /*  output  [01:00]         */  .z1(),
        /*  output  [01:00]         */  .ff1(),
        /*  output  [01:00]         */  .ov_msb(),
        /*  output  [01:00]         */  .co_msb(),
        /*  output  [01:00]         */  .cmsb(),
        /*  output  [01:00]         */  .so({so,nc1}),
        /*  output  [01:00]         */  .f0_bus_stat(),
        /*  output  [01:00]         */  .f0_blk_stat(),
        /*  output  [01:00]         */  .f1_bus_stat({wr_dma, nc2}),
        /*  output  [01:00]         */  .f1_blk_stat()
    );

endmodule

`endif /* bMDIO_Interface_v1_20_V_ALREADY_INCLUDED */
