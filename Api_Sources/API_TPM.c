#define GLOBALS_API_TPM
#include "../App_Headers/includes.h"


/*-------------------------------------------------------------------------
* Function Name  : API_Timer0_Init
* Description    : ��ʱ��0��ʼ��
* Input          : 
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
void API_Timer0_Init(INT8U TPM_DIV)
{
    
    TIM0_TSCR1_TSWAI = Enable;   //timer 0 ��MCU�ȴ�ģʽ�²�������
    TIM0_TSCR1_TSWAI = WaitRun;
    TIM0_TSCR1_TSFRZ = Enable;   //timer 0 �������ڶ���ģʽ�½�ֹ����
    TIM0_TSCR1_TFFCA = Disable;  //���������־λ
    TIM0_TSCR1_PRNT  = Disable;  // 
    TIM0_TSCR2_PR    = TPM_DIV;  //Bus Clock / 4
    TIM0_TSCR2_TCRE  = Disable;
    TIM0_TTOV        = Disable;

    TIM0_TCTL1 = Disable;        //��ֹ����ȽϹ���
    TIM0_TCTL2 = Disable;
    TIM0_TCTL3 = Disable;        //��ֹ����ȽϹ���
    TIM0_TCTL4 = Disable; 
        
    TIM0_TFLG2_TOF   = Enable;
    TIM0_TSCR1_TEN   = Enable;   //ʹ��timer 0 ��������
    TIM0_TSCR2_TOI   = Enable;   //����ж�ʹ��
    
}
/*-------------------------------------------------------------------------
* Function Name  : API_Timer1_Init
* Description    : ��ʱ��1��ʼ��
* Input          : 
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
void API_Timer1_Init(INT8U TPM_DIV)
{

    TIM1_TSCR1_TSWAI = Enable;   //timer 0 ��MCU�ȴ�ģʽ�²�������
    TIM1_TSCR1_TSFRZ = Enable;   //timer 0 �������ڶ���ģʽ�½�ֹ����
    TIM1_TSCR1_TFFCA = Disable;  //���������־λ
    TIM1_TSCR1_PRNT  = Disable;  // 
    TIM1_TSCR2_PR    = TPM_DIV; //Bus Clock / 4
    TIM1_TSCR2_TCRE  = Disable;
    TIM1_TTOV        = Disable;

    TIM1_TCTL1 = Disable;        //��ֹ����ȽϹ���
    TIM1_TCTL2 = Disable;
    TIM1_TCTL3 = Disable;        //��ֹ����ȽϹ���
    TIM1_TCTL4 = Disable; 
    
    TIM1_TFLG2_TOF   = Enable;
    TIM1_TSCR1_TEN   = Enable;   //ʹ��timer 0 ��������
    TIM1_TSCR2_TOI   = Enable;   //����ж�ʹ��
    

}

/*-------------------------------------------------------------------------
* Function Name  : API_Timer0_isr
* Description    : ��ʱ���ж�
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
    TIM0_TFLG2_TOF = ClearFlag;  //����жϱ�־λ
}
/*-------------------------------------------------------------------------
* Function Name  : API_Timer1_isr
* Description    : ��ʱ���ж�
* Input          : None
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
interrupt void API_Timer1_isr(void)
{
  
    TIM1_TFLG2_TOF = ClearFlag;  //����жϱ�־λ
}

/*-------------------------------------------------------------------------
* Function Name  : VehCap_isr
* Description    : ���벶׽
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
* Description    : ���벶׽
* Input          : 
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
interrupt void RevCap_isr(void)
{

    TIM0_TFLG1_C7F = ClearFlag;
}