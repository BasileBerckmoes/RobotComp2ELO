/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  Contains the function prototypes, constants and register definition of the 
*  Voltage Fault Detector Component.
*
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_VFD_UV_`$INSTANCE_NAME`_H)
#define CY_VFD_UV_`$INSTANCE_NAME`_H
  
#include "`$INSTANCE_NAME`_PVT.h"
#include "`$INSTANCE_NAME`_Comp_UV.h"

#if (`$INSTANCE_NAME`_INT_VREF)
#include "`$INSTANCE_NAME`_VDAC_UV.h"
#include "`$INSTANCE_NAME`_UvDMA_dma.h"


/***************************************
*   Variable with external linkage
***************************************/

extern          uint8           `$INSTANCE_NAME`_UVFaultThreshold[`$INSTANCE_NAME`_NUMBER_OF_VOLTAGES];
extern  const   uint16  CYCODE  `$INSTANCE_NAME`_initUVFaultThreshold[`$INSTANCE_NAME`_NUMBER_OF_VOLTAGES];


/***************************************
*        Function Prototypes
***************************************/

cystatus `$INSTANCE_NAME`_SetUVFaultThreshold(uint8 voltageNum, uint16 uvFaultThreshold) `=ReentrantKeil($INSTANCE_NAME . "_SetUVFaultThreshold")`;
uint16   `$INSTANCE_NAME`_GetUVFaultThreshold(uint8 voltageNum) `=ReentrantKeil($INSTANCE_NAME . "_GetUVFaultThreshold")`;


/***************************************
*   Internal Function Prototypes
***************************************/

void   `$INSTANCE_NAME`_UVRefInit(void) `=ReentrantKeil($INSTANCE_NAME . "_UVRefInit")`;
void   `$INSTANCE_NAME`_UVRefEnable(void) `=ReentrantKeil($INSTANCE_NAME . "_UVRefEnable")`;
void   `$INSTANCE_NAME`_UVRefStop(void) `=ReentrantKeil($INSTANCE_NAME . "_UVRefStop")`;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetUVDac
********************************************************************************
*
* Summary:
*  Calling this API does not change the UV VDAC setting immediately. It writes
*  a specified value to the SRAM buffer to be used by the DMA controller that
*  drives updates to the UV DAC for the specified voltage input.
*  This API does not apply when ExternalRef=true.
*
* Parameters:
*  uint8 voltageNum: Specifies the voltage input number. Valid range: 1..32.
*  uint8 dacValue  : Specifies the value to be written to the UV VDAC.
*                    Valid range: 1..255.
*
* Return:
*  None.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_SetUVDac(voltageNum, dacValue)     \
    (`$INSTANCE_NAME`_UVFaultThreshold[`$INSTANCE_NAME`_NUMBER_OF_VOLTAGES - (voltageNum)] = (dacValue))


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetUVDac
********************************************************************************
*
* Summary:
*  Returns the DAC value currently being used by the DMA controller that drives
*  updates to UV DAC for the specified voltage input. The value is extracted
*  from the SRAM buffer, not from VDAC directly.
*  This API does not apply when ExternalRef=true.
*
* Parameters:
*  uint8 voltageNum: Specifies the voltage input number. Valid range: 1..32.
*
* Return:
*  UV DAC value for the specified voltage input. Valid range: 1..255.
*
*
*******************************************************************************/
#define `$INSTANCE_NAME`_GetUVDac(voltageNum)   (`$INSTANCE_NAME`_UVFaultThreshold[`$INSTANCE_NAME`_NUMBER_OF_VOLTAGES - (voltageNum)])


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetUVDacDirect
********************************************************************************
*
* Summary:
*  Allows manual control of the UV VDAC. The dacValue is written directly to
*  the VDAC component. Useful for UV VDAC calibration. Note that if the VFD
*  component is running when this API is called, the state machine controller
*  will override the UV VDAC value set by this API call. Call the Pause API to
*  stop the state machine controller if manual UV VDAC control is desired.
*  This API does not apply when ExternalRef=true.
*
* Parameters:
*  uint8 dacValue: Specifies the value to be written to the UV VDAC directly.
*                  Valid range: 1..255
*
* Return:
*  None.
*
* Side Effects:
*  Calling this API may cause the comparator to trigger a fault condition. To 
*  prevent this, call the VFD_Pause() API prior to calling this API.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_SetUVDacDirect(dacValue)   (`$INSTANCE_NAME`_VDAC_UV_Data_REG = (dacValue))


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetUVDacDirect
********************************************************************************
*
* Summary:
*  Returns the current UV VDAC. The returned dacValue is read directly from the
*  VDAC component. Useful for UV VDAC calibration. Note: If this API is called
*  while the component is running, it is not possible to know which voltage input
*  the UV VDAC value is associated with. Call the Pause API to stop the state
*  machine controller if manual UV VDAC control is desired.
*  This API does not apply when ExternalRef=true.
*
* Parameters:
*  None.
*
* Return:
*  A current UV DAC value.
*
*******************************************************************************/   
#define `$INSTANCE_NAME`_GetUVDacDirect()   `$INSTANCE_NAME`_VDAC_UV_Data_REG

#endif /* `$INSTANCE_NAME`_INT_VREF */


/*******************************************************************************
*   Encapsulate function calls into macro helpers to simplify coding
*******************************************************************************/

#define `$INSTANCE_NAME`_Comp_UV_LOWSPEED   `$INSTANCE_NAME`_Comp_UV_SLOWSPEED

#if (`$INSTANCE_NAME`_INT_VREF)
    
/* Initializes UV comparator and threshold generation */
#define `$INSTANCE_NAME`_UVInit()       do { \
                                            `$INSTANCE_NAME`_UVRefInit();    \
                                            `$INSTANCE_NAME`_Comp_UV_Init(); \
                                        } while(0)

/* Enables UV comparator and threshold generation */
#define `$INSTANCE_NAME`_UVEnable()     do { \
                                            `$INSTANCE_NAME`_UVRefEnable();    \
                                            `$INSTANCE_NAME`_Comp_UV_Enable(); \
                                        } while(0)

/* Disables UV comparator and threshold generation */
#define `$INSTANCE_NAME`_UVStop()       do { \
                                            `$INSTANCE_NAME`_UVRefStop();    \
                                            `$INSTANCE_NAME`_Comp_UV_Stop(); \
                                        } while(0)

/* Sets speed mode for UV DAC and comparator. Valid values are LOWSPEED and HIGHSPEED. */
#define `$INSTANCE_NAME`_SetUVSpeed(speed)  do { \
                                                `$INSTANCE_NAME`_Comp_UV_SetSpeed(`$INSTANCE_NAME`_Comp_UV_##speed); \
                                                `$INSTANCE_NAME`_VDAC_UV_SetSpeed(`$INSTANCE_NAME`_VDAC_UV_##speed); \
                                            } while(0)
#else
 
/* Initializes OV comparator */
#define `$INSTANCE_NAME`_UVInit()       `$INSTANCE_NAME`_Comp_UV_Init()

/* Enables OV comparator */
#define `$INSTANCE_NAME`_UVEnable()     `$INSTANCE_NAME`_Comp_UV_Enable()

/* Disables OV comparator */
#define `$INSTANCE_NAME`_UVStop()       `$INSTANCE_NAME`_Comp_UV_Stop()

/* Sets speed mode for UV comparator. Valid values are LOWSPEED and HIGHSPEED. */
#define `$INSTANCE_NAME`_SetUVSpeed(speed)  `$INSTANCE_NAME`_Comp_UV_SetSpeed(`$INSTANCE_NAME`_Comp_UV_##speed)

#endif /* `$INSTANCE_NAME`_INT_VREF */

#endif /* CY_VFD_UV_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
