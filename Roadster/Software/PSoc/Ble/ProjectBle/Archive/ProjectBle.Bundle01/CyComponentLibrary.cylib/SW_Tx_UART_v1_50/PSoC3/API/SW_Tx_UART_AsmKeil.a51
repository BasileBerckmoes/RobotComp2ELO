; ================================================================================
;
; File Name: `$INSTANCE_NAME`_AsmKeil.a51
; Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
;
;  Description:
;   Assembly routines for PSoC 3.
;
; ================================================================================
; Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
; You may use this file only in accordance with the license, terms, conditions,
; disclaimers, and limitations in the end user license agreement accompanying
; the software package with which this file was provided.
; ================================================================================

$NOMOD51
$INCLUDE (PSoC3_8051.inc)
$INCLUDE (cydevicekeil_trm.inc)


EXTERN XDATA : DWORD (`$INSTANCE_NAME`_pinNumber)
EXTERN XDATA : DWORD (`$INSTANCE_NAME`_pinPortNumber)
EXTERN XDATA : DWORD (`$INSTANCE_NAME`_pinDrAdress)
EXTERN XDATA : DWORD (cydelay_freq_hz)
EXTERN CODE : WORD (_CyDelayCycles)
EXTERN CODE : WORD (CyEnterCriticalSection)
EXTERN CODE : WORD (_CyExitCriticalSection)
EXTERN CODE : WORD (?C?ULDIV)
EXTERN CODE : WORD (?C?LADD)
EXTERN CODE : WORD (?C?LSTXDATA)
EXTERN CODE : WORD (?C?LLDXDATA)
EXTERN CODE : WORD (?C?LLDXDATA0)
EXTERN CODE : WORD (?C?LLDCODE)
EXTERN CODE : WORD (?C?LLDCODE0)

;-------------------------------------------------------------------------------
; Function Name: `$INSTANCE_NAME`_PutChar
;-------------------------------------------------------------------------------
;
; Summary:
;  Sends one byte via the Tx pin.
;
; Parameters:
;  TxDataByte: Byte to send
;
; Return:
;  None
;
;-------------------------------------------------------------------------------
; void `$INSTANCE_NAME`_PutChar(uint8 txDataByte)
PUBLIC _`$INSTANCE_NAME`_PutChar
?PR?`$INSTANCE_NAME`_PutChar?`$INSTANCE_NAME`ASMKEIL SEGMENT CODE PAGE    ; Align to 256-byte boundary
RSEG ?PR?`$INSTANCE_NAME`_PutChar?`$INSTANCE_NAME`ASMKEIL
_`$INSTANCE_NAME`_PutChar:
DELAY_VAL:    DS 2
                                            ; cycles  bytes
    MOV A, r7                               ;   1       1
    PUSH ACC                                ;   3       2
    MOV DPS,#00h                            ;   2       2
        
    MOV DPL1, #0                            ;   2       2   Calculate CPU cycles to wait between bits:
    MOV DPH1, #0                            ;   2       2   (CPU Frequency + (UARTBaudRate/2)) / UARTBaudRate
    MOV DPTR,#BAUD_RATE                     ;   3       3
    LCALL ?C?LLDCODE                        ;   4       3
    MOV r0, #0                              ;   2       2
    MOV r1, #0                              ;   2       2
    MOV r2, #0                              ;   2       2
    MOV r3, #2                              ;   2       2
    LCALL ?C?ULDIV                          ;   4       3
        
    MOV DPL1, #0                            ;   2       2
    MOV DPH1, #0                            ;   2       2
    MOV DPTR,#FREQ                          ;   3       3
    MOV A, #2                               ;   2       2
    MOVC A, @A+DPTR                         ;   5       1
    MOV r0, A                               ;   1       1
    MOV A, #3                               ;   2       2
    MOVC A, @A+DPTR                         ;   5       1
    MOV r1, A                               ;   1       1
    MOV DPH, r0                             ;   2       2
    MOV DPL, r1                             ;   2       2
    LCALL ?C?LLDXDATA0                      ;   4       3
    LCALL ?C?LADD                           ;   4       3
        
    MOV DPL1, #0                            ;   2       2
    MOV DPH1, #0                            ;   2       2
    MOV DPTR, #BAUD_RATE                    ;   3       3
    LCALL ?C?LLDCODE0                       ;   4       3
    
    LCALL ?C?ULDIV                          ;   4       3
        
    MOV DPTR, #DELAY_VAL                    ;   3       3
    MOV A, r7                               ;   1       1
    SUBB A, #52                             ;   2       2
    MOV r7, A                               ;   1       1
    JNC SaveDelay                           ;   3       2
    CLR C                                   ;   1       1
    MOV A, r6                               ;   1       1
    SUBB A, #1                              ;   2       2
    MOV r6, A                               ;   1       1
    JNC SaveDelay                           ;   3       2
    MOV r6, #0                              ;   2       2
SaveDelay:    
    MOV A, r6                               ;   1       1
    MOVX @DPTR, A                           ;   4       1
    INC DPTR                                ;   1       1
    MOV A, r7                               ;   1       1
    MOVX @DPTR, A                           ;   4       1
        
    MOV r1, #`$INSTANCE_NAME`_pinDrAdress   ;   2       2   Move port Data register address to DPRT1
    INC r1                                  ;   2       1
    INC r1                                  ;   2       1
    MOVX A, @r1                             ;   4       1
    MOV DPH1, A                             ;   2       2
    INC r1                                  ;   2       1
    MOVX A, @r1                             ;   4       1
    MOV DPL1, A                             ;   2       2    
    
    MOV DPS,#00h                            ;   3       3
    MOV r1, #0                              ;   2       2

    LCALL CyEnterCriticalSection            ;   4       3
    POP ACC                                 ;   2       2
    MOV r0, A                               ;   2       2
    MOV A, r7                               ;   1       1
    PUSH ACC                                ;   3       2
    MOV A, r0                               ;   2       2
    RL A                                    ;   1       1
    PUSH ACC                                ;   3       2
                                            ;               Transmitting start bit
    CLR A                                   ;   3       2
    MOV DPS,#01h                            ;   3       3
    MOV A, #0xFE                            ;   2       2
    MOV r0, A                               ;   1       1
    MOVX A, @DPTR                           ;   3       1
    ANL A, r0                               ;   1       1
    MOVX @DPTR, A                           ;   4       1
    MOV DPS,#00h                            ;   3       3
    MOV DPTR, #DELAY_VAL                    ;   3       3
    MOV r4, #0                              ;   2       2
    MOV r5, #0                              ;   2       2
    MOVX A, @DPTR                           ;   4       1
    MOV r6, A                               ;   1       1
    INC DPTR                                ;   1       1
    MOVX A, @DPTR                           ;   4       1
    MOV r7, A                               ;   1       1
    LCALL _CyDelayCycles                    ;   4       3
byteTxLoop:    
                                            ;               Transmit bit loop
    POP ACC                                 ;   2       2
    RR A                                    ;   1       1
    PUSH ACC                                ;   3       2
    MOV DPS,#01h                            ;   3       3
    MOV r2, #0x01                           ;   2       2
    ANL A, r2                               ;   2       1
    MOV r3, A                               ;   1       1
    MOVX A, @DPTR                           ;   3       1
    MOV r2, #0xFE                           ;   2       2
    ANL A, r2                               ;   2       1
    ORL A, r3                               ;   1       1
    MOVX @DPTR, A                           ;   4       1
    MOV DPS,#00h                            ;   3       3
    MOV DPTR, #DELAY_VAL                    ;   3       3
    MOV r4, #0                              ;   2       2
    MOV r5, #0                              ;   2       2
    MOVX A, @DPTR                           ;   3       1
    MOV r6, A                               ;   1       1
    INC DPTR                                ;   1       1
    MOVX A, @DPTR                           ;   3       1
    MOV r7, A                               ;   1       1
    LCALL _CyDelayCycles                    ;   4       3
    INC r1                                  ;   1       1
    CJNE r1, #8, byteTxLoop                 ;
                                            ;               Transmitting STOP bit   
    POP ACC                                 ;   2       2
    MOV A, #1                               ;   2       2
    MOV DPS,#01h                            ;   3       3
    MOV r2, #0x01                           ;   2       2
    ANL A, r2                               ;   1       1
    MOV r3, A                               ;   1       1
    MOVX A, @DPTR                           ;   3       1
    MOV r2, #0xFE                           ;   2       2
    ANL A, r2                               ;   1       1
    ORL A, r3                               ;   1       1
    MOVX @DPTR, A                           ;   4       1
    MOV DPS,#00h                            ;   3       3
    MOV DPTR, #DELAY_VAL                    ;   3       3
    MOV r4, #0                              ;   2       2
    MOV r5, #0                              ;   2       2
    MOVX A, @DPTR                           ;   3       1
    MOV r6, A                               ;   1       1
    INC DPTR                                ;   1       1
    MOVX A, @DPTR                           ;   3       1
    MOV r7, A                               ;   1       1
    LCALL _CyDelayCycles                    ;   4       3
    
    POP ACC                                 ;   2       2
    MOV r7, A                               ;   1       1
    LCALL _CyExitCriticalSection            ;   4       3

    RET                                     ;   4       1
    
PORT_REG_OFFSET: DW 5000H
PORT_REG_SIZE: DB 08H
FREQ: DD cydelay_freq_hz
BAUD_RATE: DD `$BaudRate`

    END


;[] END OF FILE
