/* ================================================*/
/* ----------------- ISR TIMER C ------------------*/
/* ================================================*/

#include "InterruptRoutine_TIMER.h"

CY_ISR(TIMER_ISR)
{   
    Timer_ReadStatusRegister();
    timeout = 1;
}


/* [] END OF FILE */
