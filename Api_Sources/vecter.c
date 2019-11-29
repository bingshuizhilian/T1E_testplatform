#include "../App_Headers/includes.h"

extern void _Startup(void);       //Èë¿Úº¯Êý                                                                            
     
#ifndef  VECTF                                                                      
    #define VECTF   ( void ( *const near )( ) )    
#endif
     
static interrupt void DummyISR(void)                          
{                                               
    for(;;);                                       
}                                                                                            
       
#ifndef  VECTF                                                                      
    #define VECTF   ( void ( *const near )( ) )    
#endif
    
   
//INTERRUPT VECTORS TABLE
#pragma CONST_SEG VECTORS_DATA

void near ( * const near _vectab[] )( ) =   
{
    VECTF     DummyISR,      //Spurious interrupt
    VECTF     DummyISR,      //Reserved 
    VECTF     DummyISR,      //ATD Compare Interrupt
    VECTF     DummyISR,      //High Temperature Interrupt
    VECTF     DummyISR,      //Autonomous periodical interrupt (API)
    VECTF     DummyISR,      //Low-voltage interrupt (LVI) 
    VECTF     DummyISR,      //PWM emergency shutdown 
    VECTF     DummyISR,      //Port T 
    VECTF     DummyISR,      //Reserved 
    VECTF     DummyISR,      //Reserved 
    VECTF     DummyISR,      //Reserved 
    VECTF     DummyISR,    //Motor Control Timer Overflow                             
    VECTF     DummyISR,      //Reserved
    VECTF     DummyISR,      //TIM1 Pulse accumulator input edge
    VECTF     DummyISR,      //TIM1 Pulse accumulator A overflow
    VECTF     DummyISR,    //TIM1 timer overflow
    VECTF     DummyISR,    //TIM1 timer channel 7 
    VECTF     DummyISR,      //TIM1 timer channel 6 
    VECTF     DummyISR,      //TIM1 timer channel 5 
    VECTF     DummyISR,      //TIM1 timer channel 4 
    VECTF     DummyISR,      //TIM1 timer channel 3 
    VECTF     DummyISR,      //TIM1 timer channel 2 
    VECTF     DummyISR,      //TIM1 timer channel 1 
    VECTF     DummyISR,      //TIM1 timer channel 0
    VECTF     DummyISR,      //CAN transmit
    VECTF     API_CAN_Rev_isr,    //CAN receive
    VECTF     DummyISR,      //CAN errors 
    VECTF     DummyISR,      //CAN wake-up 
    VECTF     DummyISR,      //FLASH
    VECTF     DummyISR,      //FLASH Fault Detect
    VECTF     DummyISR,      //Reserved
    VECTF     DummyISR,      //Reserved
    VECTF     DummyISR,      //IIC bus
    VECTF     DummyISR,      //Reserved 
    VECTF     DummyISR,      //Reserved
    VECTF     DummyISR,      //CPMU PLL lock 
    VECTF     DummyISR,      //CPMU Oscillator Noise
    VECTF     DummyISR,      //Port S 
    VECTF     DummyISR,      //Port R
    VECTF     DummyISR,      //Port AD
    VECTF     DummyISR,      //Reserved
    VECTF     DummyISR,      //ATD  
    VECTF     DummyISR,      //Reserved
    VECTF     Api_SCI_Rev_isr,//SCI 
    VECTF     DummyISR,      //SPI
    VECTF     DummyISR,      //TIM0 Pulse accumulator input edge 
    VECTF     DummyISR,      //TIM0 Pulse accumulator A overflow
    VECTF     API_Timer0_isr,    //TIM0 timer overflow    API_Timer0_isr
    VECTF     DummyISR,    //TIM0 timer channel 7
    VECTF     DummyISR,      //TIM0 timer channel 6            
    VECTF     DummyISR,      //TIM0 timer channel 5 
    VECTF     DummyISR,      //TIM0 timer channel 4             
    VECTF     DummyISR,      //TIM0 timer channel 3 
    VECTF     DummyISR,      //TIM0 timer channel 2             
    VECTF     DummyISR,      //TIM0 timer channel 1 
    VECTF     DummyISR,      //TIM0 timer channel 0 
    VECTF     API_RTC_isr,      //Real time interrupt 
    VECTF     DummyISR,      //IRQ
    VECTF     DummyISR,      //XIRQ
    VECTF     DummyISR,      //SWI 
    VECTF     DummyISR,      //Unimplemented instruction trap
    VECTF     DummyISR,      //COP watchdog reset
    VECTF     DummyISR,      //Clock monitor reset
    VECTF     _Startup,      // 0xFFFE:  Reset      
};

#pragma CONST_SEG DEFAULT
