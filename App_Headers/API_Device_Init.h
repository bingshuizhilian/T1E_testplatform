/*
 * API_Device_Init.h
 *
 *  Created on: 2012-3-27
 *      Author: arno.qi
 */

#ifdef        GLOBALS_API_DEV
    #define   EXTERN_API_DEV   
#else
    #define   EXTERN_API_DEV     extern
#endif

#ifndef API_DEVICE_INIT_H_
#define API_DEVICE_INIT_H_

    #define     NormalChip               0x80
    #define     SpecialChip              0x00
    #define     InitDIRECT               0          
    #define     InitIVBR                 0xFF
    #define     InitCPMUPROT             0x26
    #define     InitCPMUCLKS             0x87
    #define     InitCPMUREFDIV           0x40
    #define     InitCPMUSYNR             0x47 //0X47 4M;  8M 0X43
    #define     InitCPMUPOSTDIV          0x00
    #define     InitCPMUPLL              0
    #define     InitPUCR                 0x40
    #define     InitCPMUCOP              0x07 
    #define     Enable                   1
    #define     Disable                  0
    #define     WaitRun                  0
    #define     null                     0
    #define     one                      1
    #define     ClearFlag                1
    #define     clear                    0
    #define     True                     1
    #define     false                    0
    #define     PushDown                 0
    #define     UpSpring                 1
    #define     BusClock                 32000000 //16777216
    #define     SafetyVeh                10 *64
    #define     Prio1                    1 
    #define     Prio2                    2  
    #define     Prio3                    3  
    #define     Prio4                    4  
    #define     Prio5                    5   
    #define     Prio6                    6 
    #define     Prio7                    7          
    
    #define     PushDown                 0
    #define     UpSpring                 1 
    
    #define     Auto                     1 
    #define     Manual                   0
     
    #define     pSTB                     PTP_PTP1 

    #define     pSBRInput                PT1AD_PT1AD2  // Û±Í-    
    #define     pSBLInput                PT1AD_PT1AD1  // Û±Í+
    
    //≥‰µÁµ∆
    #define     pChargeLedInput          PTP_PTP3      //pp3
    #define     pChargeledOut            PTP_PTP2      //pp2
    #define     pChargeledLed            PORTB_PB2     //pp2
    
    //”≤œﬂºÏ≤‚
    #define     pHardwiredInput          PTV_PTV4       //pv4 
    #define     pHardwiredOut            PTU_PTU2       //pu2
    #define     pHardwiredLed            PTU_PTU0       //pu0
    
    //»º”Õº”ºÏ≤‚
    #define     pFuelAddInput          PTR_PTR0         //pr0
    #define     pFuelAddOut            PTR_PTR2         //pr2
    #define     pFuelAddLed            PTR_PTR3         //pr3
    
    //»º”ÕºıºÏ≤‚
    #define     pFuelMinInput          PTS_PTS5         //ps5
    #define     pFuelMinOut            PTS_PTS6         //ps6
    #define     pFuelMinLed            PTR_PTR1         //pr1
    
    //can÷∏ æµ∆
    #define     pCanMinLed            PTP_PTP0           //pp0
    #define     pCanAddLed            PTV_PTV6           //pv6
    
    // Û±Í
    #define     pMouseEn              PT1AD_PT1AD7        //pv6
    #define     pMouseLed             PT1AD_PT1AD6         //pv6
    
    #define     LIN_STATE_IDLE           0    
    #define     LIN_MSG_ID               0x42
    
  	#define     baud_9600                208
  	#define     div4                     3

    
                     
    EXTERN_API_DEV     void    API_Sys_Init(void);
    EXTERN_API_DEV     void    API_Clock_Init(void);
    EXTERN_API_DEV     void    API_IO_init(void);
    
#endif /* API_DEVICE_INIT_H_ */
