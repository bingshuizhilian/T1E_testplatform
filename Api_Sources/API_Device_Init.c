#define  GLOBALS_API_DEV
#include "../App_Headers/includes.h"

/*-------------------------------------------------------------------------
* Function Name  : Api_Sys_Init
* Description    : ϵͳ��ʼ��
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
* Description    : ϵͳʱ�ӳ�ʼ��
* Input          : None
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
void API_Clock_Init(void)
{
    INT32U    dwTime = null;
    MODE      = NormalChip;
    DIRECT    = InitDIRECT;           //��ʼ��ֱ��ҳ�Ĵ���
    IVBR      = InitIVBR;             //��ʼ���ж���������ַ
    CPMUOSC_OSCE   = Enable;                //ʹ���ⲿ����
    while(!CPMUFLG_UPOSC)                   //�ȴ����ȶ�
    {
        dwTime++;
        if(dwTime > 10000)
        {
            dwTime = null;
            break;
        }
    }
    ECLKCTL_NECLK  = Enable;               //��ֹECLK���
    CPMUPROT       = InitCPMUPROT;         //��ֹʱ�ӱ���   
    CPMUREFDIV     = InitCPMUREFDIV;       //���÷�Ƶϵ��
    CPMUSYNR       = InitCPMUSYNR;         //���ó�ϵ��
    CPMUPOSTDIV    = InitCPMUPOSTDIV;      //���÷�Ƶ����
    CPMUPLL        = InitCPMUPLL;          //PLLƵ�ʵ���
    CPMUCOP        = InitCPMUCOP;               //�������Ź�
    CPMUCLKS       = InitCPMUCLKS;         //��ֹͣģʽ�������� ѡ��PLLʱ��
    CPMUCLKS_PLLSEL = Enable;
                
    CPMUOSC_OSCE   = Enable;               //ʹ���ⲿ����
    while(!CPMUFLG_UPOSC)                  //�ȴ����ȶ�
    { 
       dwTime++;
       _FEED_COP();
       if(dwTime > 10000)
       {
           dwTime = null;
           break;
       }
    }
    CPMUCLKS_PSTP  = Enable;               //αֹͣģʽ
    CPMUCLKS_RTIOSCSEL = Enable;           //RTI STOP MODE �������� 
    CPMUCLKS_PRE   = Enable;               
    CPMUCLKS_COPOSCSEL = !Enable;           //COP STOP MODE ���� 
    CPMUCLKS_PCE   = !Enable; 
    
    CPMUPROT       = Enable;               //ʹ��ʱ�ӱ���
    CPMUHTCTL      = Disable;              //�¶ȱ�����ֹ
    //�ж�
    CPMUINT_OSCIE  = Disable;              //Osc
    CPMUINT_LOCKIE = Disable;              //Lock
    //RTI
    CPMURTI_RTDEC  = True;                 //ʮ����
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
    PUCR   = 0x40;  //��������ʹ�� ��ֹ����
          
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
    PERS   = 0x60;  //ʹ���������� �������
    PPSS   = 0x40;  //ѡ������ ��������
    RDRS   = 0x00;  //��������ѡ��          
    PTSRR  = 0x10;  //����IIC OR SPI  
    
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
    //RDRP   = 0x04;  //��������ѡ��       
    PPSP   = 0x04; 
    
    DDRT   = 0xff;    
    PERT   = 0x00;
    PPST   = 0x00; 
         
    PT1AD  = 0x00;
    DDR1AD = 0xC0;
    PER1AD = 0x06; 
    ATDDIEN = 0xC6; //AD   This bit controls the digital input buffer
}
