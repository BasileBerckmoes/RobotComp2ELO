/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  Contains the function prototypes, constants and register definition
*  of the Voltage Fault Detector Component.
*
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_MuxDMA_dma.h"
#include "`$INSTANCE_NAME`_FiltRdDMA_dma.h"
#include "`$INSTANCE_NAME`_FiltWrDMA_dma.h"

#if (`$INSTANCE_NAME`_ENABLE_OV_DETECT)
#include "`$INSTANCE_NAME`_OV.h"
#endif /* `$INSTANCE_NAME`_ENABLE_OV_DETECT */
#if (`$INSTANCE_NAME`_ENABLE_UV_DETECT)
#include "`$INSTANCE_NAME`_UV.h"
#endif /* `$INSTANCE_NAME`_ENABLE_UV_DETECT */


/***************************************
*   Internal definitions
***************************************/

#define AMUX_DMA_DATA_SIZE      1u
#define AMUX_DMA_DATA_NR        1u

/* Glitch filter DMA data element size depends on the Compare type parameter.
* When the parameter is set to UV, the filtering is only applied to PGOOD.
* Thus the data element size is 1 byte.
* When OV is enabled, a fault type is also distinguished. This requires
* a filtering to be additionally applied to OV fault condition. Both filters
* are combined to use 16-bit interface for DMA access. 
*/
#define FILT_DMA_DATA_SIZE      (`$INSTANCE_NAME`_ENABLE_OV_DETECT ? 2u : 1u)

/* Compiler endiannes compatibility defines */
#if (CY_PSOC3)
    #define STS_B1      3
    #define STS_B2      2
    #define STS_B3      1
    #define STS_B4      0
#else
    #define STS_B1      0
    #define STS_B2      1
    #define STS_B3      2
    #define STS_B4      3
#endif

#define NUM_STS_BYTES   4


/***************************************
*   Internal type definitions
***************************************/

typedef union
{
	uint32	word;
	uint8	bytes[NUM_STS_BYTES];
} FAULT_STS;


/***************************************
*   Internal component variables
***************************************/

static  uint8   amuxDmaCh;
static  uint8   amuxDmaTd;

static  uint8   filtRdDmaCh;
static  uint8   filtWrDmaCh;
static  `$filtCountType`  filtCount[`$INSTANCE_NAME`_NUMBER_OF_VOLTAGES];


/***************************************
*    Internal component functions
***************************************/

static void `$INSTANCE_NAME`_AMuxDmaInit(void) `=ReentrantKeil($INSTANCE_NAME . "_AMuxDmaInit")`;
static void `$INSTANCE_NAME`_GlitchFilterDmaInit(void) `=ReentrantKeil($INSTANCE_NAME . "_GlitchFilterDmaInit")`;


/***************************************
*   External variables
***************************************/

uint8 `$INSTANCE_NAME`_initVar = 0u;
`$VoltageScale`


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the default VFD configuration provided with the
*  customizer. Initializes internal DMA channels. It is not necessary to call
*  VFD_Init() because the VFD_Start() routine calls this function, which is the
*  preferred method to begin the component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  Disables all interrupts for the moment the counter enabling bits are set.
*  Configures DMA transfer the first time this function is called. Does not
*  reinitialize DMA on subsequent calls.
*  Use `$INSTANCE_NAME`_Stop() to reset DMA to the initial state.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    uint8 interruptState;
    static uint8 dmaInitDone = 0u;

    /* DMA initialization is done the first time `$INSTANCE_NAME`_Init() is
    * called. Otherwise it will consume all available TD resources. */
    if(dmaInitDone == 0u)
    {
        `$INSTANCE_NAME`_AMuxDmaInit();
        `$INSTANCE_NAME`_GlitchFilterDmaInit();
        dmaInitDone = 1u;
    }

    #if (`$INSTANCE_NAME`_ENABLE_OV_DETECT)
        `$INSTANCE_NAME`_OVInit();
    #endif /* `$INSTANCE_NAME`_ENABLE_OV_DETECT */

    #if (`$INSTANCE_NAME`_ENABLE_UV_DETECT)
        `$INSTANCE_NAME`_UVInit();
    #endif /* `$INSTANCE_NAME`_ENABLE_UV_DETECT */

    /* Counters are hardware controlled. Set firmware enable bits at init stage */
    interruptState = CyEnterCriticalSection();
    #if (`$INSTANCE_NAME`_VIN_SETTLING_DELAY > `$INSTANCE_NAME`_VIN_SETTLING_DELAY_MIN)
        `$INSTANCE_NAME`_VIN_DELAY_CNT_ACTL_REG |= `$INSTANCE_NAME`_CNT_START;
    #endif /* `$INSTANCE_NAME`_VIN_SETTLING_DELAY > `$INSTANCE_NAME`_VIN_SETTLING_DELAY_MIN */
    `$INSTANCE_NAME`_VIN_INDEX_CNT_ACTL_REG |= `$INSTANCE_NAME`_CNT_START;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Enables hardware blocks, the DMA channels and the control state machine.
*  It is not necessary to call `$INSTANCE_NAME`_Init() because the `$INSTANCE_NAME`_Start()
*  routine calls this function, which is the preferred method to begin the component
*  operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  Sets/restores the initial TD for the AMux DMA channel, resets glitch filter
*  counters and the current voltage index. This function should not be called
*  when the component is started.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
    /* AMux control uses TD chain. Set initial TD in chain. */
    (void)CyDmaChSetInitialTd(amuxDmaCh, amuxDmaTd);
    (void)CyDmaChEnable(amuxDmaCh, 1u);
    (void)CyDmaChEnable(filtRdDmaCh, 1u);
    (void)CyDmaChEnable(filtWrDmaCh, 1u);
       
    #if (`$INSTANCE_NAME`_ENABLE_OV_DETECT)
        `$INSTANCE_NAME`_OVEnable();
    #endif /* `$INSTANCE_NAME`_ENABLE_OV_DETECT */

    #if (`$INSTANCE_NAME`_ENABLE_UV_DETECT)
        `$INSTANCE_NAME`_UVEnable();
    #endif /* `$INSTANCE_NAME`_ENABLE_UV_DETECT */

    /* Reset glitch filter counters */
    (void)memset((void *)filtCount, 0, sizeof(filtCount));

    /* Reset voltage index  */
    `$INSTANCE_NAME`_VIN_INDEX_CNT_COUNT_REG = `$INSTANCE_NAME`_NUMBER_OF_VOLTAGES - 1u;

    /* Enable the control state machine */
    `$INSTANCE_NAME`_CONTROL_REG = `$INSTANCE_NAME`_EN;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Calls the Init() API if the component has not been initialized before.
*  Runs a calibration routine for comparators and then calls Enable() to
*  begin the component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  `$INSTANCE_NAME`_initVar - Used to check the initial configuration, modified
*  on a first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
    if(`$INSTANCE_NAME`_initVar == 0u)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }

    `$INSTANCE_NAME`_ComparatorCal(`$INSTANCE_NAME`_OV);
    `$INSTANCE_NAME`_ComparatorCal(`$INSTANCE_NAME`_UV);
    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Disables the VFD component. Stops DMA controller and resets TDs. Disconnects
*  AMux channels.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  pgood and pgood[x] outputs are de-asserted.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    uint8 indx;
    uint8 interruptState;

    /* Disable control state machine */
    `$INSTANCE_NAME`_CONTROL_REG = 0u;
    
    /* Terminate all transfers and disable DMA channels */
    (void)CyDmaChSetRequest(amuxDmaCh, CY_DMA_CPU_TERM_CHAIN);
    (void)CyDmaChSetRequest(filtRdDmaCh, CY_DMA_CPU_TERM_CHAIN);
    (void)CyDmaChSetRequest(filtWrDmaCh, CY_DMA_CPU_TERM_CHAIN);
        
    /* Clear potential DRQs that may occur during termination period */    
    (void)CyDmaClearPendingDrq(amuxDmaCh);
    (void)CyDmaClearPendingDrq(filtRdDmaCh);
    (void)CyDmaClearPendingDrq(filtWrDmaCh);

    #if (`$INSTANCE_NAME`_ENABLE_OV_DETECT)
        `$INSTANCE_NAME`_OVStop();
    #endif /* `$INSTANCE_NAME`_ENABLE_OV_DETECT */

    #if (`$INSTANCE_NAME`_ENABLE_UV_DETECT)
        `$INSTANCE_NAME`_UVStop();
    #endif /* `$INSTANCE_NAME`_ENABLE_UV_DETECT */

    /* Disconnect AMux channels */
    for(indx = 0u; indx < `$INSTANCE_NAME`_NUMBER_OF_VOLTAGES; ++indx)
    {
        *`$INSTANCE_NAME`_AMux__addrTable[indx] = 0u;
    }
    /* Reset glitch filter FIFOs */
    interruptState = CyEnterCriticalSection();
    `$INSTANCE_NAME`_PG_FILTER_FIFO_ACTL_REG |= `$INSTANCE_NAME`_FIFO_CLR;
    `$INSTANCE_NAME`_PG_FILTER_FIFO_ACTL_REG &= (uint8)~`$INSTANCE_NAME`_FIFO_CLR;
    #if (`$INSTANCE_NAME`_ENABLE_OV_DETECT)
        `$INSTANCE_NAME`_OV_FILTER_FIFO_ACTL_REG |= `$INSTANCE_NAME`_FIFO_CLR;
        `$INSTANCE_NAME`_OV_FILTER_FIFO_ACTL_REG &= (uint8)~`$INSTANCE_NAME`_FIFO_CLR;
    #endif /* `$INSTANCE_NAME`_ENABLE_OV_DETECT */
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetOVUVFaultStatus
********************************************************************************
*
* Summary:
*  Assigns an over/under voltage fault status of each voltage input to its
*  parameters. Bits are sticky and cleared by calling this API. Applicable only
*  if Compare Type is set to "OV/UV".
*
* Parameters:
*  ovStatus: OV status for all voltages.
*  uvStatus: UV status for all voltages.
*
* Return:
*  None.
*
* Side Effects:
*  Calling this API clears the fault condition source sticky bits. If the
*  condition still persists, then the bit will be set again after the next scan.
*
* Reentrant:
*  No.
*
*******************************************************************************/
#if (`$INSTANCE_NAME`_COMP_TYPE == `$INSTANCE_NAME`_OV_UV)
void `$INSTANCE_NAME`_GetOVUVFaultStatus(uint32 * ovStatus, uint32 * uvStatus) `=ReentrantKeil($INSTANCE_NAME . "_GetOVUVFaultStatus")`
{
    FAULT_STS ovLocal;
    FAULT_STS uvLocal;

    #ifdef __CC_ARM
        /* ARMCC compiler issues C4017W warnings about the use of uninitialized
        * variables. The compiler cannot reliably identify faulty code and any
        * C4017W warnings are intended only as an indication of possible problems.
        */
        ovLocal.word = 0u;
        uvLocal.word = 0u;
    #endif /* __CC_ARM */

    #ifdef `$INSTANCE_NAME`_PG_STS8_STATUS_REG
        ovLocal.bytes[STS_B1] = `$INSTANCE_NAME`_OV_STS8_STATUS_REG;
        uvLocal.bytes[STS_B1] = (uint8)~(`$INSTANCE_NAME`_PG_STS8_STATUS_REG | ovLocal.bytes[STS_B1]);
    #endif /* `$INSTANCE_NAME`_PG_STS8_STATUS_REG */
    #ifdef `$INSTANCE_NAME`_PG_STS16_STATUS_REG
        ovLocal.bytes[STS_B2] = `$INSTANCE_NAME`_OV_STS16_STATUS_REG;
        uvLocal.bytes[STS_B2] = (uint8)~(`$INSTANCE_NAME`_PG_STS16_STATUS_REG | ovLocal.bytes[STS_B2]);
    #else
        ovLocal.bytes[STS_B2] = 0u;
        uvLocal.bytes[STS_B2] = 0u;
    #endif /* `$INSTANCE_NAME`_PG_STS16_STATUS_REG */
    #ifdef `$INSTANCE_NAME`_PG_STS24_STATUS_REG
        ovLocal.bytes[STS_B3] = `$INSTANCE_NAME`_OV_STS24_STATUS_REG;
        uvLocal.bytes[STS_B3] = (uint8)~(`$INSTANCE_NAME`_PG_STS24_STATUS_REG | ovLocal.bytes[STS_B3]);
    #else
        ovLocal.bytes[STS_B3] = 0u;
        uvLocal.bytes[STS_B3] = 0u;
    #endif /* `$INSTANCE_NAME`_PG_STS24_STATUS_REG */
    #ifdef `$INSTANCE_NAME`_PG_STS32_STATUS_REG
        ovLocal.bytes[STS_B4] = `$INSTANCE_NAME`_OV_STS32_STATUS_REG;
        uvLocal.bytes[STS_B4] = (uint8)~(`$INSTANCE_NAME`_PG_STS32_STATUS_REG | ovLocal.bytes[STS_B4]);
    #else
        ovLocal.bytes[STS_B4] = 0u;
        uvLocal.bytes[STS_B4] = 0u;
    #endif /* `$INSTANCE_NAME`_PG_STS32_STATUS_REG */

    *ovStatus = ovLocal.word;
    *uvStatus = uvLocal.word;
}

#elif (`$INSTANCE_NAME`_COMP_TYPE == `$INSTANCE_NAME`_OV)

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetOVFaultStatus
********************************************************************************
*
* Summary:
*  Returns the OV status detected for all voltages.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_GetOVFaultStatus(uint32 * status) `=ReentrantKeil($INSTANCE_NAME . "_GetOVFaultStatus")`
{
    FAULT_STS CYDATA stsLocal;

    #ifdef __CC_ARM
        /* ARMCC compiler issues C4017W warnings about the use of uninitialized
        * variables. The compiler cannot reliably identify faulty code and any
        * C4017W warnings are intended only as an indication of possible problems.
        */
        stsLocal.word = 0u;
    #endif /* __CC_ARM */

    #ifdef `$INSTANCE_NAME`_OV_STS8_STATUS_REG
        stsLocal.bytes[STS_B1] = `$INSTANCE_NAME`_OV_STS8_STATUS_REG;
    #endif /* `$INSTANCE_NAME`_OV_STS8_STATUS_REG */
    #ifdef `$INSTANCE_NAME`_OV_STS16_STATUS_REG
        stsLocal.bytes[STS_B2] = `$INSTANCE_NAME`_OV_STS16_STATUS_REG;
    #else
        stsLocal.bytes[STS_B2] = 0u;
    #endif /* `$INSTANCE_NAME`_OV_STS16_STATUS_REG */
    #ifdef `$INSTANCE_NAME`_OV_STS24_STATUS_REG
        stsLocal.bytes[STS_B3] = `$INSTANCE_NAME`_OV_STS24_STATUS_REG;
    #else
        stsLocal.bytes[STS_B3] = 0u;
    #endif /* `$INSTANCE_NAME`_OV_STS24_STATUS_REG */
    #ifdef `$INSTANCE_NAME`_OV_STS32_STATUS_REG
        stsLocal.bytes[STS_B4] = `$INSTANCE_NAME`_OV_STS32_STATUS_REG;
    #else
        stsLocal.bytes[STS_B4] = 0u;
    #endif /* `$INSTANCE_NAME`_OV_STS32_STATUS_REG */

    *status = stsLocal.word;
}

#else 

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetUVFaultStatus
********************************************************************************
*
* Summary:
*  Returns the UV status detected for all voltages.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_GetUVFaultStatus(uint32 * status) `=ReentrantKeil($INSTANCE_NAME . "_GetUVFaultStatus")`
{
    FAULT_STS CYDATA stsLocal;

    #ifdef __CC_ARM
        /* ARMCC compiler issues C4017W warnings about the use of uninitialized
        * variables. The compiler cannot reliably identify faulty code and any
        * C4017W warnings are intended only as an indication of possible problems.
        */
        stsLocal.word = 0u;
    #endif /* __CC_ARM */

    #ifdef `$INSTANCE_NAME`_PG_STS8_STATUS_REG
        stsLocal.bytes[STS_B1] = (uint8)~`$INSTANCE_NAME`_PG_STS8_STATUS_REG;
    #endif /* `$INSTANCE_NAME`_PG_STS8_STATUS_REG */
    #ifdef `$INSTANCE_NAME`_PG_STS16_STATUS_REG
        stsLocal.bytes[STS_B2] = (uint8)~`$INSTANCE_NAME`_PG_STS16_STATUS_REG;
    #else
        stsLocal.bytes[STS_B2] = 0u;
    #endif /* `$INSTANCE_NAME`_PG_STS16_STATUS_REG */
    #ifdef `$INSTANCE_NAME`_PG_STS24_STATUS_REG
        stsLocal.bytes[STS_B3] = (uint8)~`$INSTANCE_NAME`_PG_STS24_STATUS_REG;
    #else
        stsLocal.bytes[STS_B3] = 0u;
    #endif /* `$INSTANCE_NAME`_PG_STS24_STATUS_REG */
    #ifdef `$INSTANCE_NAME`_PG_STS32_STATUS_REG
        stsLocal.bytes[STS_B4] = (uint8)~`$INSTANCE_NAME`_PG_STS32_STATUS_REG;
    #else
        stsLocal.bytes[STS_B4] = 0u;
    #endif /* `$INSTANCE_NAME`_PG_STS32_STATUS_REG */

    *status = stsLocal.word;
}

#endif /* (`$INSTANCE_NAME`_COMP_TYPE == `$INSTANCE_NAME`_OV_UV) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ComparatorCal
********************************************************************************
*
* Summary:
*  Runs a calibration routine that measures the selected comparator's offset 
*  voltage by shorting its inputs together and corrects for it by writing to the
*  CMP block's trim register.
*
* Parameters:
*  enum compType
*    Valid values: `$INSTANCE_NAME`_OV, `$INSTANCE_NAME`_UV.
*
* Return:
*  None.
*
* Side Effects:
*  Calling this API may cause the comparator to trigger a fault condition. To 
*  prevent this, call the VFD_Pause() API prior to calling this API.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ComparatorCal(uint8 compType) `=ReentrantKeil($INSTANCE_NAME . "_ComparatorCal")`
{    
    #if (`$INSTANCE_NAME`_ENABLE_OV_DETECT)
        if(compType == `$INSTANCE_NAME`_OV)
        {
            (void) `$INSTANCE_NAME`_Comp_OV_ZeroCal();
        }
    #endif /*`$INSTANCE_NAME`_ENABLE_OV_DETECT */

    #if (`$INSTANCE_NAME`_ENABLE_UV_DETECT)
        if(compType == `$INSTANCE_NAME`_UV)
        {
            (void) `$INSTANCE_NAME`_Comp_UV_ZeroCal();
        }
    #endif /* `$INSTANCE_NAME`_ENABLE_UV_DETECT */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetSpeed
********************************************************************************
*
* Summary:
*  Sets the speed mode for the Voltage DACs and Comparators.
*
* Parameters:
*  speedMode: specifies the speed mode. Valid values are `$INSTANCE_NAME`_LOW_SPEED
*             and `$INSTANCE_NAME`_HIGH_SPEED.
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetSpeed(uint8 speedMode) `=ReentrantKeil($INSTANCE_NAME . "_SetSpeed")`
{
    if(speedMode == `$INSTANCE_NAME`_LOW_SPEED)
    {
        #if (`$INSTANCE_NAME`_ENABLE_OV_DETECT)
            `$INSTANCE_NAME`_SetOVSpeed(LOWSPEED);
        #endif /* `$INSTANCE_NAME`_ENABLE_OV_DETECT */

        #if (`$INSTANCE_NAME`_ENABLE_UV_DETECT)
            `$INSTANCE_NAME`_SetUVSpeed(LOWSPEED);
        #endif /* `$INSTANCE_NAME`_ENABLE_UV_DETECT */
    }
    else
    {
        #if (`$INSTANCE_NAME`_ENABLE_OV_DETECT)
            `$INSTANCE_NAME`_SetOVSpeed(HIGHSPEED);
        #endif /* `$INSTANCE_NAME`_ENABLE_OV_DETECT */

        #if (`$INSTANCE_NAME`_ENABLE_UV_DETECT)
            `$INSTANCE_NAME`_SetUVSpeed(HIGHSPEED);
        #endif /* `$INSTANCE_NAME`_ENABLE_UV_DETECT */
    }
}

    
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_AMuxDmaInit
********************************************************************************
*
* Summary:
*  Initializes the DMA controlled analog multiplexer. On receiving a trigger,
*  the AMUX DMA channel connects the next analog input voltage to the window
*  comparator. The DMA controller disconnects the previous input before
*  connecting the next input to ensure a break-before-make connection.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_AMuxDmaInit(void) `=ReentrantKeil($INSTANCE_NAME . "_AMuxDmaInit")`
{      
    /* Chained TD pair is used to break previous AMux connection before
    * making new connection, i.e. td0(break)->td1(make).
    */
    uint8 td0;
    uint8 td1;
    uint8 td;

    /* 0x00 is written into AMux port to break connection */
    static uint8 amuxClear = 0u;

    /* Copy AMux mask table to SRAM to improve DMA transfer performance */
    static uint8 amuxMaskTable[`$INSTANCE_NAME`_NUMBER_OF_VOLTAGES];
    (void)memcpy((void *)amuxMaskTable, (const void *)`$INSTANCE_NAME`_AMux__maskTable, `$INSTANCE_NAME`_NUMBER_OF_VOLTAGES);

    amuxDmaCh = `$INSTANCE_NAME`_DMA_CFG(MuxDMA, AMUX_DMA_DATA_SIZE, HI16(CYDEV_SRAM_BASE), HI16(CYDEV_PERIPH_BASE));

    td1 = CY_DMA_INVALID_TD;
    for(td = 0u; td < `$INSTANCE_NAME`_NUMBER_OF_VOLTAGES; ++td)
    {
        /* TD0: Move 0 into channel being disconnected (break) */
        td0 = CyDmaTdAllocate();
        (void)CyDmaTdSetAddress(td0, LO16((uint32)&amuxClear), LO16((uint32)`$INSTANCE_NAME`_AMux__addrTable[td]));
        (void)CyDmaTdSetConfiguration(td0,  AMUX_DMA_DATA_NR, td1, CY_DMA_TD_AUTO_EXEC_NEXT);
        
        /* TD1: Move proper AMux mask into channel being connected (make) */
        td1 = CyDmaTdAllocate();
        (void)CyDmaTdSetAddress(td1, LO16((uint32)&amuxMaskTable[td]), LO16((uint32)`$INSTANCE_NAME`_AMux__addrTable[td]));
        (void)CyDmaTdSetConfiguration(td1, AMUX_DMA_DATA_NR, td0, `$INSTANCE_NAME`_MuxDMA__TD_TERMOUT_EN);
        
        /* Store initial TD in chain */
        if(td == 0u)
        {
            amuxDmaTd = td0;
        }
    }

    /* The initial TD is configured to join this TD chain into a ring.
    * The TD execution order is as follows.
    * break[0]->set[N-1]->break[N-1]->set[N-2]->...->break[1]->set[0]
    * This matches the control logic that uses a down counter to track the
    * voltage number being scanned. 
    */
    (void)CyDmaTdSetConfiguration(amuxDmaTd,  AMUX_DMA_DATA_NR, td1, CY_DMA_TD_AUTO_EXEC_NEXT);
}


/***************************************************************************
* Function Name: `$INSTANCE_NAME`_GlitchFilterDmaInit
****************************************************************************
*
* Summary:
*  Initializes the glitch filter. The glitch filter outputs a 1 only when the 
*  current and previous N samples are 1, and a 0 only when the current and
*  previous N samples are 0. Otherwise the output is unchanged from its
*  current value. The glitch filtering process uses a DMA controller to read
*  the previous filter count for the current voltage from SRAM and write the
*  updated filter count back to SRAM after the voltage is processed.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
***************************************************************************/
static void `$INSTANCE_NAME`_GlitchFilterDmaInit(void) `=ReentrantKeil($INSTANCE_NAME . "_GlitchFilterDmaInit")`
{
    uint8 td;

    /* Reads previous glitch filter count for current input from SRAM */
    filtRdDmaCh = `$INSTANCE_NAME`_DMA_CFG(FiltRdDMA, FILT_DMA_DATA_SIZE, HI16(CYDEV_SRAM_BASE), HI16(CYDEV_PERIPH_BASE));
    td = CyDmaTdAllocate();
    (void)CyDmaTdSetConfiguration(td, sizeof(filtCount), td, CY_DMA_TD_INC_SRC_ADR);
    (void)CyDmaTdSetAddress(td, LO16((uint32)filtCount), LO16((uint32)`$INSTANCE_NAME`_FILTER_IN_FIFO_PTR));
    (void)CyDmaChSetInitialTd(filtRdDmaCh, td);

    /* Moves updated glitch filter result back to SRAM */ 
    filtWrDmaCh = `$INSTANCE_NAME`_DMA_CFG(FiltWrDMA, FILT_DMA_DATA_SIZE, HI16(CYDEV_PERIPH_BASE), HI16(CYDEV_SRAM_BASE));
    td = CyDmaTdAllocate();
    (void)CyDmaTdSetConfiguration(td, sizeof(filtCount), td, CY_DMA_TD_INC_DST_ADR);
    (void)CyDmaTdSetAddress(td, LO16((uint32)`$INSTANCE_NAME`_FILTER_OUT_FIFO_PTR), LO16((uint32)filtCount));
    (void)CyDmaChSetInitialTd(filtWrDmaCh, td);
}

/* [] END OF FILE */
