/* ================================================*/
/* ------------------ ISR UART C ------------------*/
/* ================================================*/

#include "InterruptRoutine_UART.h"
#include "UART.h"
#include "stdio.h"
#include "InterruptRoutine_TIMER.h"

CY_ISR(UART_RX_ISR)
{
    
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {   
        idle = 1; 
        Timer_Start();
        Packet_Read();
        byte ++;
    }
}    


/* [] END OF FILE */
