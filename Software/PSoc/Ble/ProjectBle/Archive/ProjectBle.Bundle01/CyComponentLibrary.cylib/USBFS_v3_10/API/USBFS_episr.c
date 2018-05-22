/***************************************************************************//**
* \file `$INSTANCE_NAME`_episr.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file contains the Data endpoint Interrupt Service Routines.
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_pvt.h"
#include "`$INSTANCE_NAME`_cydmac.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


#if (`$INSTANCE_NAME`_EP1_ISR_ACTIVE)
    /******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EP_1_ISR
    ***************************************************************************//**
    *
    *  Endpoint 1 Interrupt Service Routine
    *
    ******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_EP_1_ISR)
    {

    #ifdef `$INSTANCE_NAME`_EP_1_ISR_ENTRY_CALLBACK
        `$INSTANCE_NAME`_EP_1_ISR_EntryCallback();
    #endif /* (`$INSTANCE_NAME`_EP_1_ISR_ENTRY_CALLBACK) */

        /* `#START EP1_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
        !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */
    
        `$INSTANCE_NAME`_ClearSieEpInterruptSource(`$INSTANCE_NAME`_SIE_INT_EP1_INTR);
            
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to be read from endpoint buffer. 
        */
    #if (CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (`$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP1].addr & `$INSTANCE_NAME`_DIR_IN))
    #endif /* (CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) */
        {
            /* Read CR0 register to clear SIE lock. */
            (void) `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[`$INSTANCE_NAME`_EP1].epCr0;
            
            /* Toggle all endpoint types except ISOC. */
            if (`$INSTANCE_NAME`_GET_EP_TYPE(`$INSTANCE_NAME`_EP1) != `$INSTANCE_NAME`_EP_TYPE_ISOC)
            {
                `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP1].epToggle ^= `$INSTANCE_NAME`_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP1].apiEpState = `$INSTANCE_NAME`_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
            !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
            if (`$INSTANCE_NAME`_midi_out_ep == `$INSTANCE_NAME`_EP1)
            {
                `$INSTANCE_NAME`_MIDI_OUT_Service();
            }
        #endif /* (`$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)) */
    
        /* `#START EP1_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef `$INSTANCE_NAME`_EP_1_ISR_EXIT_CALLBACK
        `$INSTANCE_NAME`_EP_1_ISR_ExitCallback();
    #endif /* (`$INSTANCE_NAME`_EP_1_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
        !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */
    }

#endif /* (`$INSTANCE_NAME`_EP1_ISR_ACTIVE) */


#if (`$INSTANCE_NAME`_EP2_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EP_2_ISR
    ****************************************************************************//**
    *
    *  Endpoint 2 Interrupt Service Routine.
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_EP_2_ISR)
    {
    #ifdef `$INSTANCE_NAME`_EP_2_ISR_ENTRY_CALLBACK
        `$INSTANCE_NAME`_EP_2_ISR_EntryCallback();
    #endif /* (`$INSTANCE_NAME`_EP_2_ISR_ENTRY_CALLBACK) */

        /* `#START EP2_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
        !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */

        `$INSTANCE_NAME`_ClearSieEpInterruptSource(`$INSTANCE_NAME`_SIE_INT_EP2_INTR);

        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to be read from endpoint buffer. 
        */
    #if (CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (`$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP2].addr & `$INSTANCE_NAME`_DIR_IN))
    #endif /* (CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) */
        {            
            /* Read CR0 register to clear SIE lock. */
            (void) `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[`$INSTANCE_NAME`_EP2].epCr0;
            
            /* Toggle all endpoint types except ISOC. */
            if (`$INSTANCE_NAME`_GET_EP_TYPE(`$INSTANCE_NAME`_EP2) != `$INSTANCE_NAME`_EP_TYPE_ISOC)
            {
                `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP2].epToggle ^= `$INSTANCE_NAME`_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP2].apiEpState = `$INSTANCE_NAME`_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
            !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
            if (`$INSTANCE_NAME`_midi_out_ep == `$INSTANCE_NAME`_EP2)
            {
                `$INSTANCE_NAME`_MIDI_OUT_Service();
            }
        #endif /* (`$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)) */        
    
        /* `#START EP2_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef `$INSTANCE_NAME`_EP_2_ISR_EXIT_CALLBACK
        `$INSTANCE_NAME`_EP_2_ISR_ExitCallback();
    #endif /* (`$INSTANCE_NAME`_EP_2_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
        !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (`$INSTANCE_NAME`_EP2_ISR_ACTIVE) */


#if (`$INSTANCE_NAME`_EP3_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EP_3_ISR
    ****************************************************************************//**
    *
    *  Endpoint 3 Interrupt Service Routine.
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_EP_3_ISR)
    {
    #ifdef `$INSTANCE_NAME`_EP_3_ISR_ENTRY_CALLBACK
        `$INSTANCE_NAME`_EP_3_ISR_EntryCallback();
    #endif /* (`$INSTANCE_NAME`_EP_3_ISR_ENTRY_CALLBACK) */

        /* `#START EP3_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
        !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */

        `$INSTANCE_NAME`_ClearSieEpInterruptSource(`$INSTANCE_NAME`_SIE_INT_EP3_INTR);    

        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to be read from endpoint buffer. 
        */
    #if (CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (`$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP3].addr & `$INSTANCE_NAME`_DIR_IN))
    #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) */
        {            
            /* Read CR0 register to clear SIE lock. */
            (void) `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[`$INSTANCE_NAME`_EP3].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (`$INSTANCE_NAME`_GET_EP_TYPE(`$INSTANCE_NAME`_EP3) != `$INSTANCE_NAME`_EP_TYPE_ISOC)
            {
                `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP3].epToggle ^= `$INSTANCE_NAME`_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP3].apiEpState = `$INSTANCE_NAME`_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
            !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
            if (`$INSTANCE_NAME`_midi_out_ep == `$INSTANCE_NAME`_EP3)
            {
                `$INSTANCE_NAME`_MIDI_OUT_Service();
            }
        #endif /* (`$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)) */        

        /* `#START EP3_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef `$INSTANCE_NAME`_EP_3_ISR_EXIT_CALLBACK
        `$INSTANCE_NAME`_EP_3_ISR_ExitCallback();
    #endif /* (`$INSTANCE_NAME`_EP_3_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
        !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (`$INSTANCE_NAME`_EP3_ISR_ACTIVE) */


#if (`$INSTANCE_NAME`_EP4_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EP_4_ISR
    ****************************************************************************//**
    *
    *  Endpoint 4 Interrupt Service Routine.
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_EP_4_ISR)
    {
    #ifdef `$INSTANCE_NAME`_EP_4_ISR_ENTRY_CALLBACK
        `$INSTANCE_NAME`_EP_4_ISR_EntryCallback();
    #endif /* (`$INSTANCE_NAME`_EP_4_ISR_ENTRY_CALLBACK) */

        /* `#START EP4_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
        !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */

        `$INSTANCE_NAME`_ClearSieEpInterruptSource(`$INSTANCE_NAME`_SIE_INT_EP4_INTR);
        
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to read from endpoint buffer. 
        */
    #if (CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (`$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP4].addr & `$INSTANCE_NAME`_DIR_IN))
    #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) */
        {
            /* Read CR0 register to clear SIE lock. */
            (void) `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[`$INSTANCE_NAME`_EP4].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (`$INSTANCE_NAME`_GET_EP_TYPE(`$INSTANCE_NAME`_EP4) != `$INSTANCE_NAME`_EP_TYPE_ISOC)
            {
                `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP4].epToggle ^= `$INSTANCE_NAME`_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP4].apiEpState = `$INSTANCE_NAME`_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
            !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
            if(`$INSTANCE_NAME`_midi_out_ep == `$INSTANCE_NAME`_EP4)
            {
                `$INSTANCE_NAME`_MIDI_OUT_Service();
            }
        #endif /* (`$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)) */        

        /* `#START EP4_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef `$INSTANCE_NAME`_EP_4_ISR_EXIT_CALLBACK
        `$INSTANCE_NAME`_EP_4_ISR_ExitCallback();
    #endif /* (`$INSTANCE_NAME`_EP_4_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
        !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (`$INSTANCE_NAME`_EP4_ISR_ACTIVE) */


#if (`$INSTANCE_NAME`_EP5_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EP_5_ISR
    ****************************************************************************//**
    *
    *  Endpoint 5 Interrupt Service Routine
    *
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_EP_5_ISR)
    {
    #ifdef `$INSTANCE_NAME`_EP_5_ISR_ENTRY_CALLBACK
        `$INSTANCE_NAME`_EP_5_ISR_EntryCallback();
    #endif /* (`$INSTANCE_NAME`_EP_5_ISR_ENTRY_CALLBACK) */

        /* `#START EP5_USER_CODE` Place your code here */

        /* `#END` */

    #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && \
                 `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT && CY_PSOC3)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */

        `$INSTANCE_NAME`_ClearSieEpInterruptSource(`$INSTANCE_NAME`_SIE_INT_EP5_INTR);
    
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to read from endpoint buffer. 
        */
    #if (CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (`$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP5].addr & `$INSTANCE_NAME`_DIR_IN))
    #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) */
        {            
            /* Read CR0 register to clear SIE lock. */
            (void) `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[`$INSTANCE_NAME`_EP5].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (`$INSTANCE_NAME`_GET_EP_TYPE(`$INSTANCE_NAME`_EP5) != `$INSTANCE_NAME`_EP_TYPE_ISOC)
            {
                `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP5].epToggle ^= `$INSTANCE_NAME`_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP5].apiEpState = `$INSTANCE_NAME`_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO))        
        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
            !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
            if (`$INSTANCE_NAME`_midi_out_ep == `$INSTANCE_NAME`_EP5)
            {
                `$INSTANCE_NAME`_MIDI_OUT_Service();
            }
        #endif /* (`$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)) */

        /* `#START EP5_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef `$INSTANCE_NAME`_EP_5_ISR_EXIT_CALLBACK
        `$INSTANCE_NAME`_EP_5_ISR_ExitCallback();
    #endif /* (`$INSTANCE_NAME`_EP_5_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
        !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (`$INSTANCE_NAME`_EP5_ISR_ACTIVE) */


#if (`$INSTANCE_NAME`_EP6_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EP_6_ISR
    ****************************************************************************//**
    *
    *  Endpoint 6 Interrupt Service Routine.
    *
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_EP_6_ISR)
    {
    #ifdef `$INSTANCE_NAME`_EP_6_ISR_ENTRY_CALLBACK
        `$INSTANCE_NAME`_EP_6_ISR_EntryCallback();
    #endif /* (`$INSTANCE_NAME`_EP_6_ISR_ENTRY_CALLBACK) */

        /* `#START EP6_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
        !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */

        `$INSTANCE_NAME`_ClearSieEpInterruptSource(`$INSTANCE_NAME`_SIE_INT_EP6_INTR);
        
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to read from endpoint buffer. 
        */
    #if (CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (`$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP6].addr & `$INSTANCE_NAME`_DIR_IN))
    #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) */
        {
            /* Read CR0 register to clear SIE lock. */
            (void) `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[`$INSTANCE_NAME`_EP6].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (`$INSTANCE_NAME`_GET_EP_TYPE(`$INSTANCE_NAME`_EP6) != `$INSTANCE_NAME`_EP_TYPE_ISOC)
            {
                `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP6].epToggle ^= `$INSTANCE_NAME`_EPX_CNT_DATA_TOGGLE;
            }
            
            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP6].apiEpState = `$INSTANCE_NAME`_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
            !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
            if (`$INSTANCE_NAME`_midi_out_ep == `$INSTANCE_NAME`_EP6)
            {
                `$INSTANCE_NAME`_MIDI_OUT_Service();
            }
        #endif /* (`$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)) */

        /* `#START EP6_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef `$INSTANCE_NAME`_EP_6_ISR_EXIT_CALLBACK
        `$INSTANCE_NAME`_EP_6_ISR_ExitCallback();
    #endif /* (`$INSTANCE_NAME`_EP_6_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
        !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (`$INSTANCE_NAME`_EP6_ISR_ACTIVE) */


#if (`$INSTANCE_NAME`_EP7_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EP_7_ISR
    ****************************************************************************//**
    *
    *  Endpoint 7 Interrupt Service Routine.
    *
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_EP_7_ISR)
    {
    #ifdef `$INSTANCE_NAME`_EP_7_ISR_ENTRY_CALLBACK
        `$INSTANCE_NAME`_EP_7_ISR_EntryCallback();
    #endif /* (`$INSTANCE_NAME`_EP_7_ISR_ENTRY_CALLBACK) */

        /* `#START EP7_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
        !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */
    
        `$INSTANCE_NAME`_ClearSieEpInterruptSource(`$INSTANCE_NAME`_SIE_INT_EP7_INTR);
        
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to read from endpoint buffer. 
        */
    #if (CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (`$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP7].addr & `$INSTANCE_NAME`_DIR_IN))
    #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) */
        {           
            /* Read CR0 register to clear SIE lock. */
            (void) `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[`$INSTANCE_NAME`_EP7].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (`$INSTANCE_NAME`_GET_EP_TYPE(`$INSTANCE_NAME`_EP7) != `$INSTANCE_NAME`_EP_TYPE_ISOC)
            {
                `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP7].epToggle ^= `$INSTANCE_NAME`_EPX_CNT_DATA_TOGGLE;
            }
            
            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP7].apiEpState = `$INSTANCE_NAME`_EVENT_PENDING;
        }


    #if (!(CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
            !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
            if(`$INSTANCE_NAME`_midi_out_ep == `$INSTANCE_NAME`_EP7)
            {
                `$INSTANCE_NAME`_MIDI_OUT_Service();
            }
        #endif /* (`$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)) */

        /* `#START EP7_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef `$INSTANCE_NAME`_EP_7_ISR_EXIT_CALLBACK
        `$INSTANCE_NAME`_EP_7_ISR_ExitCallback();
    #endif /* (`$INSTANCE_NAME`_EP_7_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
        !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (`$INSTANCE_NAME`_EP7_ISR_ACTIVE) */


#if (`$INSTANCE_NAME`_EP8_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EP_8_ISR
    ****************************************************************************//**
    *
    *  Endpoint 8 Interrupt Service Routine
    *
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_EP_8_ISR)
    {
    #ifdef `$INSTANCE_NAME`_EP_8_ISR_ENTRY_CALLBACK
        `$INSTANCE_NAME`_EP_8_ISR_EntryCallback();
    #endif /* (`$INSTANCE_NAME`_EP_8_ISR_ENTRY_CALLBACK) */

        /* `#START EP8_USER_CODE` Place your code here */

        /* `#END` */

    #if (CY_PSOC3 && defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
        !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
        {
            uint8 intEn = EA;
            CyGlobalIntEnable;  /* Enable nested interrupts. */
    #endif /* (CY_PSOC3 && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */

        `$INSTANCE_NAME`_ClearSieEpInterruptSource(`$INSTANCE_NAME`_SIE_INT_EP8_INTR);
        
        /* Notifies user that transfer IN or OUT transfer is completed.
        * IN endpoint: endpoint buffer can be reloaded, Host is read data.
        * OUT endpoint: data is ready to read from endpoint buffer. 
        */
    #if (CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)
        if (0u != (`$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP8].addr & `$INSTANCE_NAME`_DIR_IN))
    #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) */
        {
            /* Read CR0 register to clear SIE lock. */
            (void) `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[`$INSTANCE_NAME`_EP8].epCr0;

            /* Toggle all endpoint types except ISOC. */
            if (`$INSTANCE_NAME`_GET_EP_TYPE(`$INSTANCE_NAME`_EP8) != `$INSTANCE_NAME`_EP_TYPE_ISOC)
            {
                `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP8].epToggle ^= `$INSTANCE_NAME`_EPX_CNT_DATA_TOGGLE;
            }

            /* EP_MANAGEMENT_DMA_AUTO (Ticket ID# 214187): For OUT endpoint this event is used to notify
            * user that DMA has completed copying data from OUT endpoint which is not completely true.
            * Because last chunk of data is being copied.
            * For CY_PSOC 3/5LP: it is acceptable as DMA is really fast.
            * For CY_PSOC4: this event is set in Arbiter interrupt (source is DMA_TERMIN).
            */
            `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_EP8].apiEpState = `$INSTANCE_NAME`_EVENT_PENDING;
        }

    #if (!(CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO))
        #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
            !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
            if (`$INSTANCE_NAME`_midi_out_ep == `$INSTANCE_NAME`_EP8)
            {
                `$INSTANCE_NAME`_MIDI_OUT_Service();
            }
        #endif /* (`$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */
    #endif /* (!(CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)) */

        /* `#START EP8_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef `$INSTANCE_NAME`_EP_8_ISR_EXIT_CALLBACK
        `$INSTANCE_NAME`_EP_8_ISR_ExitCallback();
    #endif /* (`$INSTANCE_NAME`_EP_8_ISR_EXIT_CALLBACK) */

    #if (CY_PSOC3 && defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
        !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
        
            EA = intEn; /* Restore nested interrupt configuration. */
        }
    #endif /* (CY_PSOC3 && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */
    }
#endif /* (`$INSTANCE_NAME`_EP8_ISR_ACTIVE) */


#if (`$INSTANCE_NAME`_SOF_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SOF_ISR
    ****************************************************************************//**
    *
    *  Start of Frame Interrupt Service Routine.
    *
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_SOF_ISR)
    {
    #ifdef `$INSTANCE_NAME`_SOF_ISR_ENTRY_CALLBACK
        `$INSTANCE_NAME`_SOF_ISR_EntryCallback();
    #endif /* (`$INSTANCE_NAME`_SOF_ISR_ENTRY_CALLBACK) */

        /* `#START SOF_USER_CODE` Place your code here */

        /* `#END` */

        `$INSTANCE_NAME`_ClearSieInterruptSource(`$INSTANCE_NAME`_INTR_SIE_SOF_INTR);

    #ifdef `$INSTANCE_NAME`_SOF_ISR_EXIT_CALLBACK
        `$INSTANCE_NAME`_SOF_ISR_ExitCallback();
    #endif /* (`$INSTANCE_NAME`_SOF_ISR_EXIT_CALLBACK) */
    }
#endif /* (`$INSTANCE_NAME`_SOF_ISR_ACTIVE) */


#if (`$INSTANCE_NAME`_BUS_RESET_ISR_ACTIVE)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BUS_RESET_ISR
****************************************************************************//**
*
*  USB Bus Reset Interrupt Service Routine.  Calls _Start with the same
*  parameters as the last USER call to _Start
*
*
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_BUS_RESET_ISR)
{
#ifdef `$INSTANCE_NAME`_BUS_RESET_ISR_ENTRY_CALLBACK
    `$INSTANCE_NAME`_BUS_RESET_ISR_EntryCallback();
#endif /* (`$INSTANCE_NAME`_BUS_RESET_ISR_ENTRY_CALLBACK) */

    /* `#START BUS_RESET_USER_CODE` Place your code here */

    /* `#END` */

    `$INSTANCE_NAME`_ClearSieInterruptSource(`$INSTANCE_NAME`_INTR_SIE_BUS_RESET_INTR);

    `$INSTANCE_NAME`_ReInitComponent();

#ifdef `$INSTANCE_NAME`_BUS_RESET_ISR_EXIT_CALLBACK
    `$INSTANCE_NAME`_BUS_RESET_ISR_ExitCallback();
#endif /* (`$INSTANCE_NAME`_BUS_RESET_ISR_EXIT_CALLBACK) */
}
#endif /* (`$INSTANCE_NAME`_BUS_RESET_ISR_ACTIVE) */


#if (`$INSTANCE_NAME`_LPM_ACTIVE)
/***************************************************************************
* Function Name: `$INSTANCE_NAME`_INTR_LPM_ISR
************************************************************************//**
*
*   Interrupt Service Routine for LPM of the interrupt sources.
*
*
***************************************************************************/
CY_ISR(`$INSTANCE_NAME`_LPM_ISR)
{
#ifdef `$INSTANCE_NAME`_LPM_ISR_ENTRY_CALLBACK
    `$INSTANCE_NAME`_LPM_ISR_EntryCallback();
#endif /* (`$INSTANCE_NAME`_LPM_ISR_ENTRY_CALLBACK) */

    /* `#START LPM_BEGIN_USER_CODE` Place your code here */

    /* `#END` */

    `$INSTANCE_NAME`_ClearSieInterruptSource(`$INSTANCE_NAME`_INTR_SIE_LPM_INTR);

    /* `#START LPM_END_USER_CODE` Place your code here */

    /* `#END` */

#ifdef `$INSTANCE_NAME`_LPM_ISR_EXIT_CALLBACK
    `$INSTANCE_NAME`_LPM_ISR_ExitCallback();
#endif /* (`$INSTANCE_NAME`_LPM_ISR_EXIT_CALLBACK) */
}
#endif /* (`$INSTANCE_NAME`_LPM_ACTIVE) */


#if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA && `$INSTANCE_NAME`_ARB_ISR_ACTIVE)
    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_ARB_ISR
    ************************************************************************//**
    *
    *  Arbiter Interrupt Service Routine.
    *
    *
    ***************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_ARB_ISR)
    {
        `$UINT_TYPE` arbIntrStatus;
        `$UINT_TYPE` epStatus;
        `$UINT_TYPE` ep = `$INSTANCE_NAME`_EP1;

    #ifdef `$INSTANCE_NAME`_ARB_ISR_ENTRY_CALLBACK
        `$INSTANCE_NAME`_ARB_ISR_EntryCallback();
    #endif /* (`$INSTANCE_NAME`_ARB_ISR_ENTRY_CALLBACK) */

        /* `#START ARB_BEGIN_USER_CODE` Place your code here */

        /* `#END` */

        /* Get pending ARB interrupt sources. */
        arbIntrStatus = `$INSTANCE_NAME`_ARB_INT_SR_REG;

        while (0u != arbIntrStatus)
        {
            /* Check which EP is interrupt source. */
            if (0u != (arbIntrStatus & 0x01u))
            {
                /* Get endpoint enable interrupt sources. */
                epStatus = (`$INSTANCE_NAME`_ARB_EP_BASE.arbEp[ep].epSr & `$INSTANCE_NAME`_ARB_EP_BASE.arbEp[ep].epIntEn);

                /* Handle IN endpoint buffer full event: happens only once when endpoint buffer is loaded. */
                if (0u != (epStatus & `$INSTANCE_NAME`_ARB_EPX_INT_IN_BUF_FULL))
                {
                    if (0u != (`$INSTANCE_NAME`_EP[ep].addr & `$INSTANCE_NAME`_DIR_IN))
                    {
                        /* Clear data ready status. */
                        `$INSTANCE_NAME`_ARB_EP_BASE.arbEp[ep].epCfg &= (`$UINT_TYPE`) ~`$INSTANCE_NAME`_ARB_EPX_CFG_IN_DATA_RDY;

                    #if (CY_PSOC3 || CY_PSOC5LP)
                        #if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO && (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u))
                            /* Set up common area DMA with rest of data. */
                            if(`$INSTANCE_NAME`_inLength[ep] > `$INSTANCE_NAME`_DMA_BYTES_PER_BURST)
                            {
                                `$INSTANCE_NAME`_LoadNextInEP(ep, 0u);
                            }
                            else
                            {
                                `$INSTANCE_NAME`_inBufFull[ep] = 1u;
                            }
                        #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO && (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u)) */
                    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

                        /* Arm IN endpoint. */
                        `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[ep].epCr0 = `$INSTANCE_NAME`_EP[ep].epMode;

                    #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_IN)
                        if (ep == `$INSTANCE_NAME`_midi_in_ep)
                        {
                            /* Clear MIDI input pointer. */
                            `$INSTANCE_NAME`_midiInPointer = 0u;
                        }
                    #endif /* (`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) */
                    }
                }

            #if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_MANUAL)
                /* Handle DMA completion event for OUT endpoints. */
                if (0u != (epStatus & `$INSTANCE_NAME`_ARB_EPX_SR_DMA_GNT))
                {
                    if (0u == (`$INSTANCE_NAME`_EP[ep].addr & `$INSTANCE_NAME`_DIR_IN))
                    {
                        /* Notify user that data has been copied from endpoint buffer. */
                        `$INSTANCE_NAME`_EP[ep].apiEpState = `$INSTANCE_NAME`_NO_EVENT_PENDING;

                        /* DMA done coping data: OUT endpoint has to be re-armed by user. */
                    }
                }
            #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_MANUAL) */

            #if (CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)
                /* Handle DMA completion event for OUT endpoints. */
                if (0u != (epStatus & `$INSTANCE_NAME`_ARB_EPX_INT_DMA_TERMIN))
                {
                    uint32 channelNum = `$INSTANCE_NAME`_DmaChan[ep];

                    /* Restore burst counter for endpoint. */
                    `$INSTANCE_NAME`_DmaEpBurstCnt[ep] = `$INSTANCE_NAME`_DMA_GET_BURST_CNT(`$INSTANCE_NAME`_DmaEpBurstCntBackup[ep]);

                    /* Disable DMA channel to restore descriptor configuration. The on-going transfer is aborted. */
                    `$INSTANCE_NAME`_CyDmaChDisable(channelNum);

                    /* Generate DMA tr_out signal to notify USB IP that DMA is done. This signal is not generated
                    * when transfer was aborted (it occurs when host writes less bytes than buffer size).
                    */
                    `$INSTANCE_NAME`_CyDmaTriggerOut(`$INSTANCE_NAME`_DmaBurstEndOut[ep]);

                    /* Restore destination address for output endpoint. */
                    `$INSTANCE_NAME`_CyDmaSetDstAddress(channelNum, `$INSTANCE_NAME`_DMA_DESCR0, (void*) ((uint32) `$INSTANCE_NAME`_DmaEpBufferAddrBackup[ep]));
                    `$INSTANCE_NAME`_CyDmaSetDstAddress(channelNum, `$INSTANCE_NAME`_DMA_DESCR1, (void*) ((uint32) `$INSTANCE_NAME`_DmaEpBufferAddrBackup[ep] +
                                                                                                                   `$INSTANCE_NAME`_DMA_BYTES_PER_BURST));

                    /* Restore number of data elements to transfer which was adjusted for last burst. */
                    if (0u != (`$INSTANCE_NAME`_DmaEpLastBurstEl[ep] & `$INSTANCE_NAME`_DMA_DESCR_REVERT))
                    {
                        `$INSTANCE_NAME`_CyDmaSetNumDataElements(channelNum, (`$INSTANCE_NAME`_DmaEpLastBurstEl[ep] >> `$INSTANCE_NAME`_DMA_DESCR_SHIFT),
                                                                             `$INSTANCE_NAME`_DMA_GET_MAX_ELEM_PER_BURST(`$INSTANCE_NAME`_DmaEpLastBurstEl[ep]));
                    }

                    /* Validate descriptor 0 and 1 (also reset current state). Command to start with descriptor 0. */
                    `$INSTANCE_NAME`_CyDmaValidateDescriptor(channelNum, `$INSTANCE_NAME`_DMA_DESCR0);
                    if (`$INSTANCE_NAME`_DmaEpBurstCntBackup[ep] > 1u)
                    {
                        `$INSTANCE_NAME`_CyDmaValidateDescriptor(channelNum, `$INSTANCE_NAME`_DMA_DESCR1);
                    }
                    `$INSTANCE_NAME`_CyDmaSetDescriptor0Next(channelNum);

                    /* Enable DMA channel: configuration complete. */
                    `$INSTANCE_NAME`_CyDmaChEnable(channelNum);
                    
                    
                    /* Read CR0 register to clear SIE lock. */
                    (void) `$INSTANCE_NAME`_SIE_EP_BASE.sieEp[ep].epCr0;
                    
                    /* Toggle all endpoint types except ISOC. */
                    if (`$INSTANCE_NAME`_GET_EP_TYPE(ep) != `$INSTANCE_NAME`_EP_TYPE_ISOC)
                    {
                        `$INSTANCE_NAME`_EP[ep].epToggle ^= `$INSTANCE_NAME`_EPX_CNT_DATA_TOGGLE;
                    }
            
                    /* Notify user that data has been copied from endpoint buffer. */
                    `$INSTANCE_NAME`_EP[ep].apiEpState = `$INSTANCE_NAME`_EVENT_PENDING;
                    
                #if (defined(`$INSTANCE_NAME`_ENABLE_MIDI_STREAMING) && \
                    !defined(`$INSTANCE_NAME`_MAIN_SERVICE_MIDI_OUT) && `$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT)
                    if (`$INSTANCE_NAME`_midi_out_ep == ep)
                    {
                        `$INSTANCE_NAME`_MIDI_OUT_Service();
                    }
                #endif /* (`$INSTANCE_NAME`_ISR_SERVICE_MIDI_OUT) */
                }
            #endif /* (CY_PSOC4 && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) */


                /* `#START ARB_USER_CODE` Place your code here for handle Buffer Underflow/Overflow */

                /* `#END` */

            #ifdef `$INSTANCE_NAME`_ARB_ISR_CALLBACK
                `$INSTANCE_NAME`_ARB_ISR_Callback(ep, epStatus);
            #endif /* (`$INSTANCE_NAME`_ARB_ISR_CALLBACK) */

                /* Clear serviced endpoint interrupt sources. */
                `$INSTANCE_NAME`_ARB_EP_BASE.arbEp[ep].epSr = epStatus;
            }

            ++ep;
            arbIntrStatus >>= 1u;
        }

        /* `#START ARB_END_USER_CODE` Place your code here */

        /* `#END` */

    #ifdef `$INSTANCE_NAME`_ARB_ISR_EXIT_CALLBACK
        `$INSTANCE_NAME`_ARB_ISR_ExitCallback();
    #endif /* (`$INSTANCE_NAME`_ARB_ISR_EXIT_CALLBACK) */
    }

#endif /*  (`$INSTANCE_NAME`_ARB_ISR_ACTIVE && `$INSTANCE_NAME`_EP_MANAGEMENT_DMA) */


#if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO)
#if (CY_PSOC4)

    /******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EPxDmaDone
    ***************************************************************************//**
    *
    * \internal
    *  Endpoint  DMA Done Interrupt Service Routine basic function .
    *  
    *  \param dmaCh
    *  number of DMA channel
    *  
    *  \param ep
    *  number of USB end point
    *  
    *  \param dmaDone
    *  transfer completion flag
    *  
    *  \return
    *   updated transfer completion flag
    *
    ******************************************************************************/
    CY_INLINE static void `$INSTANCE_NAME`_EPxDmaDone(uint8 dmaCh, uint8 ep)
    {
        uint32 nextAddr;

        /* Manage data elements which remain to transfer. */
        if (0u != `$INSTANCE_NAME`_DmaEpBurstCnt[ep])
        {
            if(`$INSTANCE_NAME`_DmaEpBurstCnt[ep] <= 2u)
            {
                /* Adjust length of last burst. */
                `$INSTANCE_NAME`_CyDmaSetNumDataElements(dmaCh,
                                                    ((uint32) `$INSTANCE_NAME`_DmaEpLastBurstEl[ep] >> `$INSTANCE_NAME`_DMA_DESCR_SHIFT),
                                                    ((uint32) `$INSTANCE_NAME`_DmaEpLastBurstEl[ep] &  `$INSTANCE_NAME`_DMA_BURST_BYTES_MASK));
            }
            

            /* Advance source for input endpoint or destination for output endpoint. */
            if (0u != (`$INSTANCE_NAME`_EP[ep].addr & `$INSTANCE_NAME`_DIR_IN))
            {
                /* Change source for descriptor 0. */
                nextAddr = (uint32) `$INSTANCE_NAME`_CyDmaGetSrcAddress(dmaCh, `$INSTANCE_NAME`_DMA_DESCR0);
                nextAddr += (2u * `$INSTANCE_NAME`_DMA_BYTES_PER_BURST);
                `$INSTANCE_NAME`_CyDmaSetSrcAddress(dmaCh, `$INSTANCE_NAME`_DMA_DESCR0, (void *) nextAddr);

                /* Change source for descriptor 1. */
                nextAddr += `$INSTANCE_NAME`_DMA_BYTES_PER_BURST;
                `$INSTANCE_NAME`_CyDmaSetSrcAddress(dmaCh, `$INSTANCE_NAME`_DMA_DESCR1, (void *) nextAddr);
            }
            else
            {
                /* Change destination for descriptor 0. */
                nextAddr  = (uint32) `$INSTANCE_NAME`_CyDmaGetDstAddress(dmaCh, `$INSTANCE_NAME`_DMA_DESCR0);
                nextAddr += (2u * `$INSTANCE_NAME`_DMA_BYTES_PER_BURST);
                `$INSTANCE_NAME`_CyDmaSetDstAddress(dmaCh, `$INSTANCE_NAME`_DMA_DESCR0, (void *) nextAddr);

                /* Change destination for descriptor 1. */
                nextAddr += `$INSTANCE_NAME`_DMA_BYTES_PER_BURST;
                `$INSTANCE_NAME`_CyDmaSetDstAddress(dmaCh, `$INSTANCE_NAME`_DMA_DESCR1, (void *) nextAddr);
            }

            /* Enable DMA to execute transfer as it was disabled because there were no valid descriptor. */
            `$INSTANCE_NAME`_CyDmaValidateDescriptor(dmaCh, `$INSTANCE_NAME`_DMA_DESCR0);
            
            --`$INSTANCE_NAME`_DmaEpBurstCnt[ep];
            if (0u != `$INSTANCE_NAME`_DmaEpBurstCnt[ep])
            {
                `$INSTANCE_NAME`_CyDmaValidateDescriptor(dmaCh, `$INSTANCE_NAME`_DMA_DESCR1);
                --`$INSTANCE_NAME`_DmaEpBurstCnt[ep];
            }
            
            `$INSTANCE_NAME`_CyDmaChEnable (dmaCh);
            `$INSTANCE_NAME`_CyDmaTriggerIn(`$INSTANCE_NAME`_DmaReqOut[ep]);
        }
        else
        {
            /* No data to transfer. False DMA trig. Ignore.  */
        }

    }

    #if (`$INSTANCE_NAME`_DMA1_ACTIVE)
        /******************************************************************************
        * Function Name: `$INSTANCE_NAME`_EP1_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 1 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void `$INSTANCE_NAME`_EP1_DMA_DONE_ISR(void)
        {

            `$INSTANCE_NAME`_EPxDmaDone((uint8)`$INSTANCE_NAME`_EP1_DMA_CH,
                                                  `$INSTANCE_NAME`_EP1);
                
        }
    #endif /* (`$INSTANCE_NAME`_DMA1_ACTIVE) */


    #if (`$INSTANCE_NAME`_DMA2_ACTIVE)
        /******************************************************************************
        * Function Name: `$INSTANCE_NAME`_EP2_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 2 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void `$INSTANCE_NAME`_EP2_DMA_DONE_ISR(void)
        {

            `$INSTANCE_NAME`_EPxDmaDone((uint8)`$INSTANCE_NAME`_EP2_DMA_CH,
                                                  `$INSTANCE_NAME`_EP2);
        }
    #endif /* (`$INSTANCE_NAME`_DMA2_ACTIVE) */


    #if (`$INSTANCE_NAME`_DMA3_ACTIVE)
        /******************************************************************************
        * Function Name: `$INSTANCE_NAME`_EP3_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 3 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void `$INSTANCE_NAME`_EP3_DMA_DONE_ISR(void)
        {

            `$INSTANCE_NAME`_EPxDmaDone((uint8)`$INSTANCE_NAME`_EP3_DMA_CH,
                                                  `$INSTANCE_NAME`_EP3);
        }
    #endif /* (`$INSTANCE_NAME`_DMA3_ACTIVE) */


    #if (`$INSTANCE_NAME`_DMA4_ACTIVE)
        /******************************************************************************
        * Function Name: `$INSTANCE_NAME`_EP4_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 4 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void `$INSTANCE_NAME`_EP4_DMA_DONE_ISR(void)
        {

            `$INSTANCE_NAME`_EPxDmaDone((uint8)`$INSTANCE_NAME`_EP4_DMA_CH,
                                                  `$INSTANCE_NAME`_EP4);
        }
    #endif /* (`$INSTANCE_NAME`_DMA4_ACTIVE) */


    #if (`$INSTANCE_NAME`_DMA5_ACTIVE)
        /******************************************************************************
        * Function Name: `$INSTANCE_NAME`_EP5_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 5 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void `$INSTANCE_NAME`_EP5_DMA_DONE_ISR(void)
        {

            `$INSTANCE_NAME`_EPxDmaDone((uint8)`$INSTANCE_NAME`_EP5_DMA_CH,
                                                  `$INSTANCE_NAME`_EP5);
        }
    #endif /* (`$INSTANCE_NAME`_DMA5_ACTIVE) */


    #if (`$INSTANCE_NAME`_DMA6_ACTIVE)
        /******************************************************************************
        * Function Name: `$INSTANCE_NAME`_EP6_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 6 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void `$INSTANCE_NAME`_EP6_DMA_DONE_ISR(void)
        {

            `$INSTANCE_NAME`_EPxDmaDone((uint8)`$INSTANCE_NAME`_EP6_DMA_CH,
                                                  `$INSTANCE_NAME`_EP6);
        }
    #endif /* (`$INSTANCE_NAME`_DMA6_ACTIVE) */


    #if (`$INSTANCE_NAME`_DMA7_ACTIVE)
        /******************************************************************************
        * Function Name: `$INSTANCE_NAME`_EP7_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 7 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void `$INSTANCE_NAME`_EP7_DMA_DONE_ISR(void)
        {

            `$INSTANCE_NAME`_EPxDmaDone((uint8)`$INSTANCE_NAME`_EP7_DMA_CH,
                                                  `$INSTANCE_NAME`_EP7);
        }
    #endif /* (`$INSTANCE_NAME`_DMA7_ACTIVE) */


    #if (`$INSTANCE_NAME`_DMA8_ACTIVE)
        /******************************************************************************
        * Function Name: `$INSTANCE_NAME`_EP8_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  Endpoint 8 DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        void `$INSTANCE_NAME`_EP8_DMA_DONE_ISR(void)
        {

            `$INSTANCE_NAME`_EPxDmaDone((uint8)`$INSTANCE_NAME`_EP8_DMA_CH,
                                                  `$INSTANCE_NAME`_EP8);
        }
    #endif /* (`$INSTANCE_NAME`_DMA8_ACTIVE) */


#else
    #if (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u)
        /******************************************************************************
        * Function Name: `$INSTANCE_NAME`_EP_DMA_DONE_ISR
        ***************************************************************************//**
        *
        *  DMA Done Interrupt Service Routine.
        *
        *
        ******************************************************************************/
        CY_ISR(`$INSTANCE_NAME`_EP_DMA_DONE_ISR)
        {
            uint8 int8Status;
            uint8 int17Status;
            uint8 ep_status;
            uint8 ep = `$INSTANCE_NAME`_EP1;

        #ifdef `$INSTANCE_NAME`_EP_DMA_DONE_ISR_ENTRY_CALLBACK
            `$INSTANCE_NAME`_EP_DMA_DONE_ISR_EntryCallback();
        #endif /* (`$INSTANCE_NAME`_EP_DMA_DONE_ISR_ENTRY_CALLBACK) */

            /* `#START EP_DMA_DONE_BEGIN_USER_CODE` Place your code here */

            /* `#END` */

            /* Read clear on read status register with EP source of interrupt. */
            int17Status = `$INSTANCE_NAME`_EP17_DMA_Done_SR_Read() & `$INSTANCE_NAME`_EP17_SR_MASK;
            int8Status  = `$INSTANCE_NAME`_EP8_DMA_Done_SR_Read()  & `$INSTANCE_NAME`_EP8_SR_MASK;

            while (int8Status != 0u)
            {
                while (int17Status != 0u)
                {
                    if ((int17Status & 1u) != 0u)  /* If EpX interrupt present. */
                    {
                        /* Read Endpoint Status Register. */
                        ep_status = `$INSTANCE_NAME`_ARB_EP_BASE.arbEp[ep].epSr;

                        if ((0u == (ep_status & `$INSTANCE_NAME`_ARB_EPX_SR_IN_BUF_FULL)) &&
                            (0u ==`$INSTANCE_NAME`_inBufFull[ep]))
                        {
                            /* `#START EP_DMA_DONE_USER_CODE` Place your code here */

                            /* `#END` */

                        #ifdef `$INSTANCE_NAME`_EP_DMA_DONE_ISR_CALLBACK
                            `$INSTANCE_NAME`_EP_DMA_DONE_ISR_Callback();
                        #endif /* (`$INSTANCE_NAME`_EP_DMA_DONE_ISR_CALLBACK) */

                            /* Transfer again 2 last bytes into pre-fetch endpoint area. */
                            `$INSTANCE_NAME`_ARB_EP_BASE.arbEp[ep].rwWaMsb = 0u;
                            `$INSTANCE_NAME`_ARB_EP_BASE.arbEp[ep].rwWa = (`$INSTANCE_NAME`_DMA_BYTES_PER_BURST * ep) - `$INSTANCE_NAME`_DMA_BYTES_REPEAT;
                            `$INSTANCE_NAME`_LoadNextInEP(ep, 1u);

                            /* Set Data ready status to generate DMA request. */
                            `$INSTANCE_NAME`_ARB_EP_BASE.arbEp[ep].epCfg |= `$INSTANCE_NAME`_ARB_EPX_CFG_IN_DATA_RDY;
                        }
                    }

                    ep++;
                    int17Status >>= 1u;
                }

                int8Status >>= 1u;

                if (int8Status != 0u)
                {
                    /* Prepare pointer for EP8. */
                    ep = `$INSTANCE_NAME`_EP8;
                    int17Status = int8Status & 0x01u;
                }
            }

            /* `#START EP_DMA_DONE_END_USER_CODE` Place your code here */

            /* `#END` */

    #ifdef `$INSTANCE_NAME`_EP_DMA_DONE_ISR_EXIT_CALLBACK
        `$INSTANCE_NAME`_EP_DMA_DONE_ISR_ExitCallback();
    #endif /* (`$INSTANCE_NAME`_EP_DMA_DONE_ISR_EXIT_CALLBACK) */
        }
    #endif /* (`$INSTANCE_NAME`_EP_DMA_AUTO_OPT == 0u) */
#endif /* (CY_PSOC4) */
#endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA_AUTO) */


#if (CY_PSOC4)
    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_IntrHandler
    ************************************************************************//**
    *
    *   Interrupt handler for Hi/Mid/Low ISRs.
    *
    *  regCause - The cause register of interrupt. One of the three variants:
    *       `$INSTANCE_NAME`_INTR_CAUSE_LO_REG - Low interrupts.
    *       `$INSTANCE_NAME`_INTR_CAUSE_MED_REG - Med interrupts.
    *       `$INSTANCE_NAME`_INTR_CAUSE_HI_REG - - High interrupts.
    *
    *
    ***************************************************************************/
    CY_INLINE static void `$INSTANCE_NAME`_IntrHandler(uint32 intrCause)
    {
        /* Array of pointers to component interrupt handlers. */
        static const cyisraddress `$INSTANCE_NAME`_isrCallbacks[] =
        {
`$APIGEN_ISR_CALLBACKS`
        };

        uint32 cbIdx = 0u;

        /* Check arbiter interrupt source first. */
        if (0u != (intrCause & `$INSTANCE_NAME`_INTR_CAUSE_ARB_INTR))
        {
            `$INSTANCE_NAME`_isrCallbacks[`$INSTANCE_NAME`_ARB_EP_INTR_NUM]();
        }

        /* Check all other interrupt sources (except arbiter and resume). */
        intrCause = (intrCause  & `$INSTANCE_NAME`_INTR_CAUSE_CTRL_INTR_MASK) |
                    ((intrCause & `$INSTANCE_NAME`_INTR_CAUSE_EP1_8_INTR_MASK) >>
                                  `$INSTANCE_NAME`_INTR_CAUSE_EP_INTR_SHIFT);

        /* Call interrupt handlers for active interrupt sources. */
        while (0u != intrCause)
        {
            if (0u != (intrCause & 0x1u))
            {
                 `$INSTANCE_NAME`_isrCallbacks[cbIdx]();
            }

            intrCause >>= 1u;
            ++cbIdx;
        }
    }


    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_INTR_HI_ISR
    ************************************************************************//**
    *
    *   Interrupt Service Routine for the high group of the interrupt sources.
    *
    *
    ***************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_INTR_HI_ISR)
    {
        `$INSTANCE_NAME`_IntrHandler(`$INSTANCE_NAME`_INTR_CAUSE_HI_REG);
    }

    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_INTR_MED_ISR
    ************************************************************************//**
    *
    *   Interrupt Service Routine for the medium group of the interrupt sources.
    *
    *
    ***************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_INTR_MED_ISR)
    {
       `$INSTANCE_NAME`_IntrHandler(`$INSTANCE_NAME`_INTR_CAUSE_MED_REG);
    }

    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_INTR_LO_ISR
    ************************************************************************//**
    *
    *   Interrupt Service Routine for the low group of the interrupt sources.
    *
    *
    ***************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_INTR_LO_ISR)
    {
        `$INSTANCE_NAME`_IntrHandler(`$INSTANCE_NAME`_INTR_CAUSE_LO_REG);
    }
#endif /* (CY_PSOC4) */


/* [] END OF FILE */
