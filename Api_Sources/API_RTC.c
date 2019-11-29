#define  GLOBALS_API_RTC
#include "../App_Headers/includes.h"


/*-------------------------------------------------------------------------
* Function Name  : API_Set100msTimer
* Description    : 设置定时器
* Input          : 
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
void API_Set30msTimer(INT16U Second,ClockType *T)
{
    T->T30msEnable = Enable;
    T->Over30msTime = Second;
    Clock.T30msTime = null;
}
/*-------------------------------------------------------------------------
* Function Name  : API_TimerOver
* Description    : 设置定时器
* Input          : 
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
INT8U API_30msTimerOver(ClockType *T)
{
    if((T->T30msTime >= T->Over30msTime)&&(T->T30msEnable))
    {        
        T->T30msEnable = Disable;
        T->T30msTime = null;
        return 1;
    }
    else
    {
        return 0;
    }    
}
/*-------------------------------------------------------------------------
* Function Name  : API_Set100msTimer
* Description    : 设置定时器
* Input          : 
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
void API_Set100msTimer(INT16U Second,ClockType *T)
{    
    T->Over100msTime = Second;
    Clock.T100msTime = null;
    T->T100msTEnable = Enable;
}
/*-------------------------------------------------------------------------
* Function Name  : API_TimerOver
* Description    : 设置定时器
* Input          : 
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
INT8U API_100msTimerOver(ClockType *T)
{
    if((T->T100msTime >= T->Over100msTime)&&(T->T100msTEnable == Enable))
    {        
        T->T100msTEnable = Disable;
        T->T100msTime = null;
        return 1;
    }
    else
    {
        return 0;
    }    
}
/*-------------------------------------------------------------------------
* Function Name  : API_Set100msTimer
* Description    : 设置定时器
* Input          : 
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
void API_Set10msTimer(INT16U Second,ClockType *T)
{
    T->T10msEnable = Enable;
    T->Over10msTime = Second;
    Clock.T10msTime = null;
}
/*-------------------------------------------------------------------------
* Function Name  : API_TimerOver
* Description    : 设置定时器
* Input          : 
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
INT8U API_10msTimerOver(ClockType *T)
{
    if((T->T10msTime >= T->Over10msTime)&&(T->T10msEnable))
    {        
        T->T10msEnable = Disable;
        T->T10msTime = null;
        return 1;
    }
    else
    {
        return 0;
    }    
}


/*-------------------------------------------------------------------------
* Function Name  : API_Set500msTimer
* Description    : 设置定时器
* Input          : 
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
void API_Set500msTimer(INT16U Second,ClockType *T)
{
    T->T500msEnable = Enable;
    T->Over500msTime = Second;
    Clock.T500msTime = null;
}
/*-------------------------------------------------------------------------
* Function Name  : API_500msTimerOver
* Description    : 设置定时器
* Input          : 
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
INT8U API_500msTimerOver(ClockType *T)
{
    if((T->T500msTime >= T->Over500msTime)&&(T->T500msEnable))
    {        
        T->T500msEnable = Disable;
        T->T500msTime = null;
        return 1;
    }
    else
    {
        return 0;
    }    
}
/*-------------------------------------------------------------------------
* Function Name  : API_Set100msTimer
* Description    : 设置定时器
* Input          : 
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
void API_Set1000msTimer(INT16U Second,ClockType *T)
{    
    T->Over1000msTime = Second;
    Clock.T1000msTime = null;
    T->T1000msEnable = Enable;
}
/*-------------------------------------------------------------------------
* Function Name  : API_TimerOver
* Description    : 设置定时器
* Input          : 
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
INT8U API_1000msTimerOver(ClockType *T)
{
    if((T->T1000msTime >= T->Over1000msTime)&&(T->T1000msEnable == Enable))
    {        
        T->T1000msEnable = Disable;
        T->T1000msTime = null;
        return 1;
    }
    else
    {
        return 0;
    }    
}
/*-------------------------------------------------------------------------
* Function Name  : API_RTC_isr
* Description    : 
* Input          : 
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
interrupt void API_RTC_isr(void)
{        
    if(pSBLInput == PushDown)
    {
        if(Key.PushTime1 < 5000)
        {
            Key.PushTime1 ++;  
        }          
    }
    if(pSBRInput == PushDown)
    {
        if(Key.PushTime2 < 5000)
        {
            Key.PushTime2 ++;  
        }          
    } 
    if(Key.MainMenu == Auto)
    {
        if(Key.AutoTime1 < 5000)
        {
           Key.AutoTime1 ++;
        } 
        if(Key.AutoTime2 < 1000)
        {
           Key.AutoTime2 ++;
        }                     
    }

    if(Clock.T30msEnable)
    {
        if(Clock.T30msTime < Clock.Over30msTime)
        {
            Clock.T30msTime++;
        }
    }
    if(Clock.T100msTEnable)
    {
        if(Clock.T100msTime < Clock.Over100msTime)
        {
            Clock.T100msTime++;
        }
    }
    if(Clock.T10msEnable)
    {
        if(Clock.T10msTime < Clock.Over10msTime)
        {
            Clock.T10msTime++;
        }
    }

    if(Clock.T500msEnable)
    {
        if(Clock.T500msTime < Clock.Over500msTime)
        {
            Clock.T500msTime++;
        }
    }
    
    if(Clock.T1000msEnable)
    {
        if(Clock.T1000msTime < Clock.Over1000msTime)
        {
            Clock.T1000msTime++;
        }
    }
    
    Clock.millisecond++;
    if(Clock.millisecond == 1000)
    {                              
        Clock.isFlash = !Clock.isFlash;

        Clock.millisecond = null;           
    }
        
    CPMUFLG_RTIF = ClearFlag;
}
