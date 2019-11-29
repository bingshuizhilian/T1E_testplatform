#define  GLOBALS_API_DEV
#include "../App_Headers/includes.h"

/*-------------------------------------------------------------------------
* Function Name  : Api_Sys_Init
* Description    : 系统初始化
* Input          : None
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
void API_Sys_Init(void)
{
   DisableInterrupts;
   API_Clock_Init();     
   API_Flash_Init();   
   API_IO_init();
   API_CAN_Init();   
   API_Timer0_Init(TPM_DIV1);     
   //Api_SCI_Init();
   API_LCD_Init();   
   EnableInterrupts;
}
/*-------------------------------------------------------------------------
* Function Name  : Api_Clock_Init
* Description    : 系统时钟初始化
* Input          : None
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
void API_Clock_Init(void)
{
    INT32U    dwTime = null;
    MODE      = NormalChip;
    DIRECT    = InitDIRECT;           //初始化直接页寄存器
    IVBR      = InitIVBR;             //初始化中断向量基地址
    CPMUOSC_OSCE   = Enable;                //使能外部振荡器
    while(!CPMUFLG_UPOSC)                   //等待振荡稳定
    {
        dwTime++;
        if(dwTime > 10000)
        {
            dwTime = null;
            break;
        }
    }
    ECLKCTL_NECLK  = Enable;               //禁止ECLK输出
    CPMUPROT       = InitCPMUPROT;         //禁止时钟保护   
    CPMUREFDIV     = InitCPMUREFDIV;       //设置分频系数
    CPMUSYNR       = InitCPMUSYNR;         //设置乘系数
    CPMUPOSTDIV    = InitCPMUPOSTDIV;      //设置分频参数
    CPMUPLL        = InitCPMUPLL;          //PLL频率调节
    CPMUCOP        = InitCPMUCOP;               //开启看门狗
    CPMUCLKS       = InitCPMUCLKS;         //在停止模式下振荡运行 选择PLL时钟
    CPMUCLKS_PLLSEL = Enable;
                
    CPMUOSC_OSCE   = Enable;               //使能外部振荡器
    while(!CPMUFLG_UPOSC)                  //等待振荡稳定
    { 
       dwTime++;
       _FEED_COP();
       if(dwTime > 10000)
       {
           dwTime = null;
           break;
       }
    }
    CPMUCLKS_PSTP  = Enable;               //伪停止模式
    CPMUCLKS_RTIOSCSEL = Enable;           //RTI STOP MODE 继续运行 
    CPMUCLKS_PRE   = Enable;               
    CPMUCLKS_COPOSCSEL = !Enable;           //COP STOP MODE 运行 
    CPMUCLKS_PCE   = !Enable; 
    
    CPMUPROT       = Enable;               //使能时钟保护
    CPMUHTCTL      = Disable;              //温度保护禁止
    //中断
    CPMUINT_OSCIE  = Disable;              //Osc
    CPMUINT_LOCKIE = Disable;              //Lock
    //RTI
    CPMURTI_RTDEC  = True;                 //十进制
    CPMURTI_RTR    = 0x03;                 //400*10^3
    
    CPMUINT_RTIE   = Enable;               //RTI  
    CPMULVCTL_LVIE = Disable;              //LV
    IRQCR          = Disable;              //IRQ  
}

/*-------------------------------------------------------------------------
* Function Name  : API_IO_init
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
void API_IO_init(void)
{    
    PUCR   = 0x40;  //上拉驱动使能 禁止下拉
          
    DDRA   = 0xff;
    
    //PORTB  =                     
    DDRB   = 0xff;    
   
    //PORT U          
    DDRU   = 0x05;    
    PERU   = 0x04;
    PPSU   = 0x05;
    
    //PORT R 
    PTR  = 0x04;     
    DDRR   = 0x0E;        
    PERR   = 0x0F;  
    PPSR   = 0x0E;   
    
    //PORT V  
    DDRV   = 0x40;   
    PERV   = 0x50;
    PPSV   = 0x40;                   

    DDRH   = 0xff;
    PERH   = 0x00;
    PPSH   = 0x00;
    
    //PORT S  
    PTS    = 0x40;
    DDRS   = 0x40;
    PERS   = 0x60;  //使能上拉仅仅 针对输入
    PPSS   = 0x40;  //选择上拉 还是下拉
    RDRS   = 0x00;  //驱动能力选择          
    PTSRR  = 0x10;  //控制IIC OR SPI  
    
    WOMS   = 0x00;
    PIES   = 0x00;
    PIFS   = 0x00;
    SPICR1 = 0x00;
    SPICR2 = 0x01;
 
   //PORT P
    //PTPRR  = 0x01;
    PTP    = 0x00;
    DDRP   = 0x07; 
    PERP   = 0x08; 
    //RDRP   = 0x04;  //驱动能力选择       
    PPSP   = 0x04; 
    
    DDRT   = 0xff;    
    PERT   = 0x00;
    PPST   = 0x00; 
         
    PT1AD  = 0x00;
    DDR1AD = 0xC0;
    PER1AD = 0x06; 
    ATDDIEN = 0xC6; //AD   This bit controls the digital input buffer
}
