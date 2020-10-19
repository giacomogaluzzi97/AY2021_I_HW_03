/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "project.h"
#include "RGBLedDriver.h"
#include "InterruptRoutine_UART.h"
#include "InterruptRoutine_TIMER.h"


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    /* initialization */
    
    isr_timer_StartEx(TIMER_ISR);
    isr_UART_StartEx(UART_RX_ISR);
    UART_Start();
    PWM_RG_Start();
    PWM_B_Start();
    RGBLed_InitializeColor();
    Micro_Init();
    
    for(;;)
    {
        Micro_Manager(); 
    }
}


/* [] END OF FILE */
