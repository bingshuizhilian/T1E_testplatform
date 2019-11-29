/*
 * GUI_Display.h
 *
 *  Created on: 2012-3-27
 *      Author: arno.qi
 */
#ifdef        GLOBALS_GUI_DISP
    #define   EXTERN_GUI_DISP


#else
    #define   EXTERN_GUI_DISP     extern
#endif
#ifndef GUI_DISP_H_
#define GUI_DISP_H_


    EXTERN_GUI_DISP     void       Gui_ButoonProc(void);     

//硬线检测类型
typedef struct
{
    uint8_t maxTimer;
    uint8_t curTimer; 
    uint16_t PushTimer;
    uint8_t timer;  //次数  
    uint8_t valid; 
    uint8_t enable; 
}HardWireCheck;

void HardWireCheckInit(void);
#endif /* GUI_DISP_H_ */