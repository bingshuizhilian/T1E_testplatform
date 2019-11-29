#define  GLOBALS_API_ATD
#include "../App_Headers/includes.h"


/*-------------------------------------------------------------------------
* Function Name  : ATD_INIT
* Description    : AD转化初始化
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
    ATDCTL1_SRES     = True;     //10位精度
    ATDCTL1_SMP_DIS  = Disable;  //
    ATDCTL1_ETRIGCH  = 0;        //转化通道初始化
                                
    ATDCTL2_AFFC     = Disable;  //分别清除每一个 CCFX标志位用写1的方式
    ATDCTL2_ICLKSTP  = Enable;   //使能停止模式
    ATDCTL2_ETRIGE   = Disable;  //外部触发禁止
    ATDCTL2_ASCIE    = Disable;  //禁止转化中断
    ATDCTL2_ACMPIE   = Disable;  //禁止比较中断
    
    ATDCTL3_DJM      = Enable;   //右对齐
    ATDCTL3_S1C      = 1;        //转化长度1
    ATDCTL3_S2C      = 0;
    ATDCTL3_S4C      = 0;
    ATDCTL3_S8C      = 0;
    ATDCTL3_FIFO     = Disable;  //不是FIFO模式 并且各自的结果放在各自的寄存器 ATDDRx
    ATDCTL3_FRZ      = Disable;  //禁止冻结模式
    
    ATDCTL4_SMP      = SMP_TIME;  //采样时间 4 CYCLE
    ATDCTL4_PRS      = SMP_PRE;   //
    
    ATDCTL5_SC       = Disable;
    ATDCTL5_CA       = 0;
    ATDCTL5_CB       = 0;
    ATDCTL5_CC       = 0;
    ATDCTL5_CD       = 0;
    
    ATDDIEN=0xfe;
    ATDCTL5_SCAN     = Enable;   //连续转化
    ATDCTL5_MULT     = 0;        //只有一个通道
    //*/

}
/*-------------------------------------------------------------------------
* Function Name  : API_GetSensorAD
* Description    : 提取AD值
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