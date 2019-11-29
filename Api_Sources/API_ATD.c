#define  GLOBALS_API_ATD
#include "../App_Headers/includes.h"


/*-------------------------------------------------------------------------
* Function Name  : ATD_INIT
* Description    : ADת����ʼ��
* Input          : 
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
void API_ATD_init(void)
{
    ///*
    ATDCTL0 = null;
    ATDCTL1_ETRIGSEL = Disable;
    ATDCTL1_SRES     = True;     //10λ����
    ATDCTL1_SMP_DIS  = Disable;  //
    ATDCTL1_ETRIGCH  = 0;        //ת��ͨ����ʼ��
                                
    ATDCTL2_AFFC     = Disable;  //�ֱ����ÿһ�� CCFX��־λ��д1�ķ�ʽ
    ATDCTL2_ICLKSTP  = Enable;   //ʹ��ֹͣģʽ
    ATDCTL2_ETRIGE   = Disable;  //�ⲿ������ֹ
    ATDCTL2_ASCIE    = Disable;  //��ֹת���ж�
    ATDCTL2_ACMPIE   = Disable;  //��ֹ�Ƚ��ж�
    
    ATDCTL3_DJM      = Enable;   //�Ҷ���
    ATDCTL3_S1C      = 1;        //ת������1
    ATDCTL3_S2C      = 0;
    ATDCTL3_S4C      = 0;
    ATDCTL3_S8C      = 0;
    ATDCTL3_FIFO     = Disable;  //����FIFOģʽ ���Ҹ��ԵĽ�����ڸ��ԵļĴ��� ATDDRx
    ATDCTL3_FRZ      = Disable;  //��ֹ����ģʽ
    
    ATDCTL4_SMP      = SMP_TIME;  //����ʱ�� 4 CYCLE
    ATDCTL4_PRS      = SMP_PRE;   //
    
    ATDCTL5_SC       = Disable;
    ATDCTL5_CA       = 0;
    ATDCTL5_CB       = 0;
    ATDCTL5_CC       = 0;
    ATDCTL5_CD       = 0;
    
    ATDDIEN=0xfe;
    ATDCTL5_SCAN     = Enable;   //����ת��
    ATDCTL5_MULT     = 0;        //ֻ��һ��ͨ��
    //*/

}
/*-------------------------------------------------------------------------
* Function Name  : API_GetSensorAD
* Description    : ��ȡADֵ
* Input          : 
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
void API_GetSensorAD(void)
{
    static INT16U  ad_data[10];
    static INT8U   p = null;
           INT8U   AD_STATUS;
    AD_STATUS = ATDSTAT0;
    if((AD_STATUS & 0x80) == 0x80)
    {
        ad_data[p] = ATDDR0;
        p++;
        if(p >2)
        {
           p = null;
        }
        APP_SortNByte(ad_data,3);
        if(ad_data[1] > 200)  //2V = 7.7V
        {
            Curkeyinput = KeyON;
        }
        else
        {
            Curkeyinput = KeyOFF;
            
        }
        ATDSTAT0_SCF = ClearFlag;
    }    
}