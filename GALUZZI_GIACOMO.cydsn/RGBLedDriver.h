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
#ifndef __RGB_LED_DRIVER_H__
    #define __RGB_LED_DRIVER_H__
    
    #define IDLE 0
    #define HEADER 1
    #define RED 2
    #define GREEN 3
    #define BLU 4
    #define TAIL 5
    #define PERIODTIMER 250
    
    #include "cytypes.h"
    #include "project.h"
    
    uint8_t state = IDLE; //variabile dell stato
    
    typedef struct {
        uint8_t red;
        uint8_t green;
        uint8_t blu;
    } Colors;    
       
    void RGBLed_Start();
    void RGBLed_Stop();
    
    void RGBLed_InitializeColor();
    void RGBLed_WriteColor(Colors c);
    
    void States();
    
    
#endif    
/* [] END OF FILE */
