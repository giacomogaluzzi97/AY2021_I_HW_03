/* ================================================*/
/* ------------------ ISR UART H ------------------*/
/* ================================================*/

#ifndef __INTERRUPT_ROUTINE_UART_H__
    #define  __INTERRUPT_ROUTINE_UART_H__
    
    #include "UART.h"
    #include "global.h"
    #include "RGBLedDriver.h"
    
    CY_ISR_PROTO(UART_RX_ISR);
    
#endif
/* [] END OF FILE */
