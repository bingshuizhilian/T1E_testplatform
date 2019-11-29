/*
 * APP_Data_Process.c
 *
 *  Created on: 2012-6-17
 *      Author: qitiancun
 */
#define GLOBALS_APP_PROCESS
#include "../App_Headers/includes.h"




/*-------------------------------------------------------------------------
* Function Name  : APP_State_Init
* Description    : 加载数据
* Input          : None
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
void APP_State_Init(void)
{

   
   Clock.Col = null;
   Clock.isFlash = null; 
   Clock.T30msTime = null; 
   Clock.T100msTime = null;
   Clock.T10msTime = null;
   

   
}
/*-------------------------------------------------------------------------
* Function Name  : APP_Clear_Data
* Description    : 加载数据
* Input          : None
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
void APP_Clear_Data(INT8U *data)
{
    INT8U i;
    for(i = 0;i < 8;i++)
    {
       data[i] = 0;
    }
}

/*-------------------------------------------------------------------------
* Function Name  : APP_Clear_Data
* Description    : 加载数据
* Input          : None
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
INT8U APP_CheckSum(INT8U *data)
{
    INT8U i;    
    INT8U check;
    
    check =0;
    
    for(i = 0;i < 7;i++)
    {
       check += data[i];
    }
    return check;
}

