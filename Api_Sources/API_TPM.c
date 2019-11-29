#define GLOBALS_API_TPM
#include "../App_Headers/includes.h"


/*-------------------------------------------------------------------------
* Function Name  : API_Timer0_Init
* Description    : 定时器0初始化
* Input          : 
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
void API_Timer0_Init(INT8U TPM_DIV)
{
    
    TIM0_TSCR1_TSWAI = Enable;   //timer 0 在MCU等待模式下不能运行
    TIM0_TSCR1_TSWAI = WaitRun;
    TIM0_TSCR1_TSFRZ = Enable;   //timer 0 计数器在冻结模式下禁止运行
    TIM0_TSCR1_TFFCA = Disable;  //正常清除标志位
    TIM0_TSCR1_PRNT  = Disable;  // 
    TIM0_TSCR2_PR    = TPM_DIV;  //Bus Clock / 4
    TIM0_TSCR2_TCRE  = Disable;
    TIM0_TTOV        = Disable;

    TIM0_TCTL1 = Disable;        //禁止输出比较功能
    TIM0_TCTL2 = Disable;
    TIM0_TCTL3 = Disable;        //禁止输出比较功能
    TIM0_TCTL4 = Disable; 
        
    TIM0_TFLG2_TOF   = Enable;
    TIM0_TSCR1_TEN   = Enable;   //使能timer 0 正常功能
    TIM0_TSCR2_TOI   = Enable;   //溢出中断使能
    
}
/*-------------------------------------------------------------------------
* Function Name  : API_Timer1_Init
* Description    : 定时器1初始化
* Input          : 
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
void API_Timer1_Init(INT8U TPM_DIV)
{

    TIM1_TSCR1_TSWAI = Enable;   //timer 0 在MCU等待模式下不能运行
    TIM1_TSCR1_TSFRZ = Enable;   //timer 0 计数器在冻结模式下禁止运行
    TIM1_TSCR1_TFFCA = Disable;  //正常清除标志位
    TIM1_TSCR1_PRNT  = Disable;  // 
    TIM1_TSCR2_PR    = TPM_DIV; //Bus Clock / 4
    TIM1_TSCR2_TCRE  = Disable;
    TIM1_TTOV        = Disable;

    TIM1_TCTL1 = Disable;        //禁止输出比较功能
    TIM1_TCTL2 = Disable;
    TIM1_TCTL3 = Disable;        //禁止输出比较功能
    TIM1_TCTL4 = Disable; 
    
    TIM1_TFLG2_TOF   = Enable;
    TIM1_TSCR1_TEN   = Enable;   //使能timer 0 正常功能
    TIM1_TSCR2_TOI   = Enable;   //溢出中断使能
    

}

/*-------------------------------------------------------------------------
* Function Name  : API_Timer0_isr
* Description    : 定时器中断
* Input          : None
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
interrupt void API_Timer0_isr(void)
{
    if((CANRFLG_RSTAT == 0x03)||(CANRFLG_TSTAT == 0x03))
    {
        if(BusOffTime == null) 
        {                       
            BusOffTime = TT_200ms;
            CANMISC_BOHOLD = ClearFlag;                                                 
        }  
        if(BusOffTime > null)
        {
             BusOffTime--;                 
        }         
    }    
    TIM0_TFLG2_TOF = ClearFlag;  //清除中断标志位
}
/*-------------------------------------------------------------------------
* Function Name  : API_Timer1_isr
* Description    : 定时器中断
* Input          : None
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
interrupt void API_Timer1_isr(void)
{
  
    TIM1_TFLG2_TOF = ClearFlag;  //清除中断标志位
}

/*-------------------------------------------------------------------------
* Function Name  : VehCap_isr
* Description    : 输入捕捉
* Input          : 
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
interrupt void VehCap_isr(void)
{

    TIM1_TFLG1_C7F = ClearFlag;
}

/*-------------------------------------------------------------------------
* Function Name  : RevCap_isr
* Description    : 输入捕捉
* Input          : 
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
interrupt void RevCap_isr(void)
{

    TIM0_TFLG1_C7F = ClearFlag;
}