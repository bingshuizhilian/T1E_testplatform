/*
 * includes.h
 *
 *  Created on: 2012-3-21
 *      Author: qitiancun
 */

#ifndef _INCLUDES_H_
#define _INCLUDES_H_
    #include "hidef.h"      /* common defines and macros */
    #include "derivative.h"      /* derivative-specific definitions */
    #include "mc9s12hy64.h"
    
    #include "../App_Headers/Var_Type.h" 
    //物理层
    #include "../App_Headers/API_Device_Init.h"  
    #include "../App_Headers/API_DFlash.h"
    #include "../App_Headers/API_CAN.h" 
    #include "../App_Headers/API_TPM.h"
    #include "../App_Headers/API_SCI.h" 

    #include "../App_Headers/API_RTC.h"
    #include "../App_Headers/API_LCD.h"  

    //应用层
    #include "../App_Headers/Globals_Var.h"
    #include "../App_Headers/APP_DFlash.h"
    #include "../App_Headers/APP_Data_Process.h"
    #include "../App_Headers/APP_SCI.h" //GUI   
    #include "../App_Headers/CAN_Communication_Matrix.h" 

    //GUI   
    #include "../App_Headers/GUI_Display.h"        
#endif /* _INCLUDES_H_ */
