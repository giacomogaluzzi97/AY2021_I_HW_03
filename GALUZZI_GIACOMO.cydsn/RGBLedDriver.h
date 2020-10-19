/* ================================================*/
/* ----------------- LED DRIVER H -----------------*/
/* ================================================*/

#ifndef __RGB_LED_DRIVER_H__
    #define __RGB_LED_DRIVER_H__
    
    #include "global.h"
    
    void RGBLed_Start();
    void RGBLed_Stop();
    void RGBLed_InitializeColor();
    void Packet_Read();
    void Micro_Init();
    void Micro_Manager();
    
/* ================================================*/
/* ---------------- COLORS STRUCT -----------------*/
/* ================================================*/    
    
    typedef struct {
        uint8_t red;
        uint8_t green;
        uint8_t blu;
    } Colors;    
    
    Colors color_pack;

    void RGBLed_WriteColor(Colors c);
   
#endif    

/* [] END OF FILE */
