/*
 * APP_Data_Process.h
 *
 *  Created on: 2012-3-27
 *      Author: qitiancun
 */
 

    
#ifdef        GLOBALS_APP_PROCESS
    #define   EXTERN_APP_PROCESS
   
#else
    #define   EXTERN_APP_PROCESS     extern
#endif

#ifndef APP_DATA_PROCESS_H_
#define APP_DATA_PROCESS_H_

    
               

   
    #define                  CheckFlag            0x55
    

    EXTERN_APP_PROCESS        void      APP_Clear_Data(INT8U *data);
    EXTERN_APP_PROCESS        void      APP_State_Init(void);

#endif /* APP_DATA_PROCESS_H_ */
