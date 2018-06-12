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

#if !defined(CY_VFD_OV_`$INSTANCE_NAME`_H)
#define CY_VFD_OV_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`_PVT.h"
#include "`$INSTANCE_NAME`_Comp_OV.h"

#if (`$INSTANCE_NAME`_INT_VREF)
#include "`$INSTANCE_NAME`_VDAC_OV.h"
#include "`$INSTANCE_NAME`_OvDMA_dma.h"


/***************************************
*   Variable with external linkage
***************************************/

extern          uint8           `$INSTANCE_NAME`_OVFaultThreshold[`$INSTANCE_NAME`_NUMBER_OF_VOLTAGES];
extern  const   uint16  CYCODE  `$INSTANCE_NAME`_initOVFaultThreshold[`$INSTANCE_NAME`_NUMBER_OF_VOLTAGES];


/***************************************
*        Function Prototypes
***************************************/

cystatus `$INSTANCE_NAME`_SetOVFaultThreshold(uint8 voltageNum, uint16 ovFaultThreshold) `=ReentrantKeil($INSTANCE_NAME . "_SetOVFaultThreshold")`;
uint16   `$INSTANCE_NAME`_GetOVFaultThreshold(uint8 voltageNum) `=ReentrantKeil($INSTANCE_NAME . "_GetOVFaultThreshold")`;


/***************************************
*   Internal Function Prototypes
***************************************/

void   `$INSTANCE_NAME`_OVRefInit(void) `=ReentrantKeil($INSTANCE_NAME . "_OVRefInit")`;
void   `$INSTANCE_NAME`_OVRefEnable(void) `=ReentrantKeil($INSTANCE_NAME . "_OVRefEnable")`;
void   `$INSTANCE_NAME`_OVRefStop(void) `=ReentrantKeil($INSTANCE_NAME . "_OVRefStop")`;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOVDac
********************************************************************************
*
* Summary:
*  Calling this API does not change the OV VDAC setting immediately. It writes
*  a specified value to the SRAM buffer to be used by the DMA controller that
*  drives updates to the OV DAC for the specified voltage input.
*  This API does not apply when ExternalRef=true.
*
* Parameters:
*  uint8 voltageNum: Specifies the voltage input number. Valid range: 1..32.
*  uint8 dacValue  : Specifies the value to be written to the OV VDAC.
*                    Valid range: 1..255.
*
* Return:
*  None.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_SetOVDac(voltageNum, dacValue)     \
    (`$INSTANCE_NAME`_OVFaultThreshold[`$INSTANCE_NAME`_NUMBER_OF_VOLTAGES - (voltageNum)] = (dacValue))


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetOVDac
********************************************************************************
*
* Summary:
*  Returns the DAC value currently being used by the DMA controller that drives 
*  updates to the OV DAC for the specified voltage input. The value is extracted
*  from the SRAM buffer, not from the VDAC directly.
*  This API does not apply when ExternalRef=true.
*
* Parameters:
*  uint8 voltageNum: Specifies the voltage input number. Valid range: 1..32.
*
* Return:
*  OV DAC value for the specified voltage input. Valid range: 1..255.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_GetOVDac(voltageNum)   (`$INSTANCE_NAME`_OVFaultThreshold[`$INSTANCE_NAME`_NUMBER_OF_VOLTAGES - (voltageNum)])


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOVDacDirect
********************************************************************************
*
* Summary:
*  Allows manual control of OV VDAC. The dacValue is written directly to
*  the VDAC component. Useful for OV VDAC calibration. Note that if the VFD
*  component is running when this API is called, the state machine controller
*  will override the OV VDAC value set by this API call. Call the Pause API to
*  stop the state machine controller if manual OV VDAC control is desired.
*  This API does not apply when ExternalRef=true.
*  
*
* Parameters:
*  uint8 dacValue: Specifies the value to be written to the OV VDAC directly.
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
#define `$INSTANCE_NAME`_SetOVDacDirect(dacValue)   (`$INSTANCE_NAME`_VDAC_OV_Data_REG = (dacValue))


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetOVDacDirect
********************************************************************************
*
* Summary:
*  Returns the current OV VDAC. The returned dacValue is read directly from the
*  VDAC component. Useful for OV VDAC calibration. Note: If this API is called
*  while  the component is running, it is not possible to know which voltage
*  input the OV VDAC value is associated with. Call the Pause API to stop the
*  state machine controller if manual OV VDAC control is desired.
*  This API does not apply when ExternalRef=true.
*
* Parameters:
*  None.
*
* Return:
*  A current OV DAC value.
*
*******************************************************************************/   
#define `$INSTANCE_NAME`_GetOVDacDirect()   `$INSTANCE_NAME`_VDAC_OV_Data_REG

#endif /* `$INSTANCE_NAME`_INT_VREF */


/*******************************************************************************
*   Encapsulate function calls into macro helpers to simplify coding
*******************************************************************************/

#define `$INSTANCE_NAME`_Comp_OV_LOWSPEED   `$INSTANCE_NAME`_Comp_OV_SLOWSPEED

#if (`$INSTANCE_NAME`_INT_VREF)
    
/* Initializes OV comparator and threshold generation */
#define `$INSTANCE_NAME`_OVInit()       do { \
                                            `$INSTANCE_NAME`_OVRefInit();    \
                                            `$INSTANCE_NAME`_Comp_OV_Init(); \
                                        } while(0)

/* Enables OV comparator and threshold generation */
#define `$INSTANCE_NAME`_OVEnable()     do { \
                                            `$INSTANCE_NAME`_OVRefEnable();    \
                                            `$INSTANCE_NAME`_Comp_OV_Enable(); \
                                        } while(0)

/* Disables OV comparator and threshold generation */
#define `$INSTANCE_NAME`_OVStop()       do { \
                                            `$INSTANCE_NAME`_OVRefStop();    \
                                            `$INSTANCE_NAME`_Comp_OV_Stop(); \
                                        } while(0)

/* Sets speed mode for OV DAC and comparator. Valid values are LOWSPEED and HIGHSPEED. */
#define `$INSTANCE_NAME`_SetOVSpeed(speed)  do { \
                                                `$INSTANCE_NAME`_Comp_OV_SetSpeed(`$INSTANCE_NAME`_Comp_OV_##speed); \
                                                `$INSTANCE_NAME`_VDAC_OV_SetSpeed(`$INSTANCE_NAME`_VDAC_OV_##speed); \
                                            } while(0)
#else

/* Initializes OV comparator */
#define `$INSTANCE_NAME`_OVInit()       `$INSTANCE_NAME`_Comp_OV_Init()

/* Enables OV comparator */
#define `$INSTANCE_NAME`_OVEnable()     `$INSTANCE_NAME`_Comp_OV_Enable()

/* Disables OV comparator */
#define `$INSTANCE_NAME`_OVStop()       `$INSTANCE_NAME`_Comp_OV_Stop()

/* Sets speed mode for OV comparator. Valid values are LOWSPEED and HIGHSPEED. */
#define `$INSTANCE_NAME`_SetOVSpeed(speed)  `$INSTANCE_NAME`_Comp_OV_SetSpeed(`$INSTANCE_NAME`_Comp_OV_##speed)

#endif /* `$INSTANCE_NAME`_INT_VREF */

/* Define power converters OV fault status bits */
#define `$INSTANCE_NAME`_OV_STS8_STATUS_REG         (* (reg8 *)`$INSTANCE_NAME`_bVFD_OV_STS_8__Sts__STATUS_REG)
#define `$INSTANCE_NAME`_OV_STS8_STATUS_PTR         (  (reg8 *)`$INSTANCE_NAME`_bVFD_OV_STS_8__Sts__STATUS_REG)
#if (`$INSTANCE_NAME`_NUMBER_OF_VOLTAGES > 8u)
#define `$INSTANCE_NAME`_OV_STS16_STATUS_REG        (* (reg8 *)`$INSTANCE_NAME`_bVFD_OV_STS_16__Sts__STATUS_REG)
#define `$INSTANCE_NAME`_OV_STS16_STATUS_PTR        (  (reg8 *)`$INSTANCE_NAME`_bVFD_OV_STS_16__Sts__STATUS_REG)
#endif /* `$INSTANCE_NAME`_NUMBER_OF_VOLTAGES > 8u */
#if (`$INSTANCE_NAME`_NUMBER_OF_VOLTAGES > 16u)
#define `$INSTANCE_NAME`_OV_STS24_STATUS_REG        (* (reg8 *)`$INSTANCE_NAME`_bVFD_OV_STS_24__Sts__STATUS_REG)
#define `$INSTANCE_NAME`_OV_STS24_STATUS_PTR        (  (reg8 *)`$INSTANCE_NAME`_bVFD_OV_STS_24__Sts__STATUS_REG)
#endif /* `$INSTANCE_NAME`_NUMBER_OF_VOLTAGES > 16u */
#if (`$INSTANCE_NAME`_NUMBER_OF_VOLTAGES > 24u)
#define `$INSTANCE_NAME`_OV_STS32_STATUS_REG        (* (reg8 *)`$INSTANCE_NAME`_bVFD_OV_STS_32__Sts__STATUS_REG)
#define `$INSTANCE_NAME`_OV_STS32_STATUS_PTR        (  (reg8 *)`$INSTANCE_NAME`_bVFD_OV_STS_32__Sts__STATUS_REG)
#endif /* `$INSTANCE_NAME`_NUMBER_OF_VOLTAGES > 24u */

#endif /* CY_VFD_OV_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
