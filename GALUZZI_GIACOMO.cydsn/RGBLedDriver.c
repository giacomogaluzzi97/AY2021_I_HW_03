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
#include "PWM_RG.h"
#include "PWM_B.h"
#include "InterruptRoutine_UART.h"
#include "InterruptRoutine_TIMER.h"

void RGBLed_Start()
{
    PWM_RG_Start();
    PWM_B_Start();
}
void RGBLed_Stop()
{
    PWM_RG_Stop();
    PWM_B_Stop();
}

void RGBLed_WriteColor(Colors c)
{
    PWM_RG_WriteCompare1(c.red);
    PWM_RG_WriteCompare2(c.green);    
    PWM_B_WriteCompare(c.blu);
}

void RGBLed_InitializeColor()
{
    PWM_RG_WriteCompare1(0);
    PWM_RG_WriteCompare2(0);    
    PWM_B_WriteCompare(0);
}    

uint8_t received = 0;
uint8_t five_sec = 0;

Colors color;

/* ================================================== */

void States()
{
   
    switch(state)
    {
        case IDLE:
                if(received == 1
                   && five_sec != 1
                   && UART_ReadRxData() == 0xA0)
                {
                    received = 0;
                    Timer_WriteCounter(PERIODTIMER);
                    state = RED;
                }
                else if (received == 1
                   && five_sec != 1
                   && UART_ReadRxData() == 'v')
                {
                    received = 0;
                    UART_PutString("RGB LED Program $$$\r\n");
                }
                else if (five_sec == 1)
                {
                    UART_PutString("Time out!\r\n");
                    five_sec = 0;
                    received = 0;
                    Timer_WriteCounter(PERIODTIMER);
                    
                }
                else 
                {
                    UART_PutString("Invalid character\r\n");
                    five_sec = 0;
                    received = 0;
                    Timer_WriteCounter(PERIODTIMER);
                }   
        break;
         
        case RED:
                if(received == 1
                   && five_sec != 1
                   && UART_ReadRxData() <= 0xFF
                   && UART_ReadRxData() >= 0x00)
                {
                    color.red = UART_ReadRxData();
                    received = 0;
                    Timer_WriteCounter(PERIODTIMER);
                    state = GREEN;
                }
                else if (five_sec == 1)
                {
                    UART_PutString("Time out!\r\n");
                    five_sec = 0;
                    received = 0;
                    Timer_WriteCounter(PERIODTIMER);
                    state = IDLE;
                }
                else 
                {
                    UART_PutString("Invalid character\r\n");
                    five_sec = 0;
                    received = 0;
                    Timer_WriteCounter(PERIODTIMER);
                    state = IDLE;
                }   
        break;
        
        case GREEN:
                if(received == 1
                   && five_sec != 1
                   && UART_ReadRxData() <= 0xFF
                   && UART_ReadRxData() >= 0x00)
                {
                    color.green = UART_ReadRxData();
                    received = 0;
                    Timer_WriteCounter(PERIODTIMER);
                    state = BLU;
                }
                else if (five_sec == 1)
                {
                    UART_PutString("Time out!\r\n");
                    five_sec = 0;
                    received = 0;
                    Timer_WriteCounter(PERIODTIMER);
                    state = IDLE;
                }
                else 
                {
                    UART_PutString("Invalid character\r\n");
                    five_sec = 0;
                    received = 0;
                    Timer_WriteCounter(PERIODTIMER);
                    state = IDLE;
                }   
        break;
                
        case BLU:
                if(received == 1
                   && five_sec != 1
                   && UART_ReadRxData() <= 0xFF
                   && UART_ReadRxData() >= 0x00)
                {
                    color.blu = UART_ReadRxData();
                    received = 0;
                    Timer_WriteCounter(PERIODTIMER);
                    state = TAIL;
                }
                else if (five_sec == 1)
                {
                    UART_PutString("Time out!\r\n");
                    five_sec = 0;
                    received = 0;
                    Timer_WriteCounter(PERIODTIMER);
                    state = IDLE;
                }
                else 
                {
                    UART_PutString("Invalid character\r\n");
                    five_sec = 0;
                    received = 0;
                    Timer_WriteCounter(PERIODTIMER);
                    state = IDLE;
                }   
        break; 
                
        case TAIL:
                if(received == 1
                   && five_sec != 1
                   && UART_ReadRxData() == 0xC0)
                {
                    RGBLed_WriteColor(color);
                    received = 0;
                    Timer_WriteCounter(PERIODTIMER);
                    state = IDLE;
                }
                else if (five_sec == 1)
                {
                    UART_PutString("Time out!\r\n");
                    five_sec = 0;
                    received = 0;
                    Timer_WriteCounter(PERIODTIMER);
                    state = IDLE;
                }
                else 
                {
                    UART_PutString("Invalid character\r\n");
                    five_sec = 0;
                    received = 0;
                    Timer_WriteCounter(PERIODTIMER);
                    state = IDLE;
                }  
        break;        
    }   
}
/* [] END OF FILE */
