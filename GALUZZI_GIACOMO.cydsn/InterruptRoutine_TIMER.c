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

#include "InterruptRoutine_TIMER.h"

extern uint8_t five_sec;

CY_ISR(TIMER_ISR)
{
    Timer_ReadStatusRegister();
    five_sec = 1; 
}
/* [] END OF FILE */
