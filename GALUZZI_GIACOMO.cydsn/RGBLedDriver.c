/* ================================================*/
/* ----------------- LED DRIVER C -----------------*/
/* ================================================*/

#include "RGBLedDriver.h"
#include "PWM_RG.h"
#include "PWM_B.h"

/* ================================================*/
/* ----------------- FUNZIONI LED -----------------*/
/* ================================================*/
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
void Micro_Init()
{
    Timer_Stop();
    byte = 0;
    idle = 0;
    ok = 0;
}    

/* ================================================*/
/* ----------------- PACKET READ ------------------*/
/* ================================================*/

void Packet_Read()
{
   
    /* header */
    if(byte == 0 && idle == 1)
    {
        packet = UART_ReadRxData();
        if(packet == 'v')
        {
            gui_call = 1;
        }
        else if(packet != 0xA0)
        {
            wrong_header = 1;
        }
        else
        {
            ok = 1;
        }    
    }    
    /* red */
    else if(byte == 1 && idle == 1) 
    {
        packet = UART_ReadRxData();
        if(!(packet >= 0 || packet <= 255))
        {
            wrong_value = 1;
        }   
        else
        {
            color_pack.red = packet;
            ok = 1;
        }    
    }   
    /* green */
    else if(byte == 2 && idle == 1) 
    {
        packet = UART_ReadRxData();
        if(!(packet >= 0 || packet <= 255))
        {
            wrong_value = 1;
        }   
        else
        {
            color_pack.green = packet;
            ok = 1;
        }    
    }  
    /* blu */
    else if(byte == 3 && idle == 1) 
    {
        packet = UART_ReadRxData();
        if(!(packet >= 0 || packet <= 255))
        {
            wrong_value = 1;
        }   
        else
        {
            color_pack.blu = packet;
            ok = 1;
        }    
    }
    /* tail */
    else if(byte == 4 && idle == 1) 
    {
        packet = UART_ReadRxData();
        if(packet != 0xC0)
        {
            wrong_tail = 1;
        }  
        else 
        {
            packet_arrived = 1;
            RGBLed_WriteColor(color_pack);
        }    
    } 
    
}

/* ================================================*/
/* ---------------- MICRO MANAGER -----------------*/
/* ================================================*/

void Micro_Manager()
{
    /* GUI call */
    if(gui_call == 1)
    {
        UART_PutString("RGB LED Program $$$");
        gui_call = 0;
        Micro_Init();
    }
    /* Timeout */
    if(timeout == 1)
    {
        UART_PutString("Timeout!\r\n");
        timeout = 0;
        Micro_Init();
    }
    /* wrong header */
    if(wrong_header == 1)
    {
        UART_PutString("Wrong packet's header\r\n");
        wrong_header = 0;
        Micro_Init();
    }
    /* wrong value */
    if(wrong_value == 1)
    {
        UART_PutString("Wrong packet's color value\r\n");
        wrong_value = 0;
        Micro_Init();
    }
    /* wrong tail */
    if(wrong_tail == 1)
    {
        UART_PutString("Wrong packet's tail\r\n");
        wrong_tail = 0;
        Micro_Init();
    }
    /* packet arrived */
    if(packet_arrived == 1)
    {
        UART_PutString("Packet arrived\r\n");
        packet_arrived = 0;
        Micro_Init();
    }
    if(ok == 1)
    {   
        UART_PutString("Correct byte\r\n");
        Timer_Stop();
        ok = 0;
        idle = 0;
        Timer_Start();
        Timer_WriteCounter(250);
    }    
}   

/* [] END OF FILE */
