#define GLOBALS_API_CAN
#include "../App_Headers/includes.h"


/*-------------------------------------------------------------------------
* Function Name  : API_CAN_Init
* Description    : CAN��ʼ��
* Input          : None
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
void  API_CAN_Init(void)
{
    INT16U b = null;
    CANCTL0_INITRQ = Enable;                //׼����ʼ�� 
    
    while(!CANCTL1_INITAK);                 //�ȴ������ʼ��ģʽ
    
    CANCTL1        = CANCTL1_CANE_MASK | CANCTL1_BORM_MASK;  
    CANCTL1_WUPM   = Disable;               //�������Ի���
    /*
    SYNC_SEG + (PROP_SEG + PHASE_SEG1) + (PHASE_SEG2)
    1 Tq         4--16  Tq                  2--8  Tq 
    */ 
  
    CANBTR1_TSEG_10 = Seg1_5Tq;    //351page  75%  75<= sp<=83
    CANBTR1_TSEG_20 = Seg2_2Tq;
    CANBTR0_SJW     = SJW_1Tq;     //����ͬ��        
    CANBTR1_SAMP    = SAMP_1;
    CANBTR0_BRP     = 0;             //���Ͳ�����2016.9.13
    
             
    CANIDAC_IDAM   = IDAM_2_32Bit;
    CANIDAC_IDHIT  = IDHIT0;                //�˲��� 0 ��Ч   
         
    CANIDAR0       = null;                  //
    CANIDAR1       = null;
    CANIDAR2       = null;
    CANIDAR3       = null;
    CANIDAR4       = null;
    CANIDAR5       = null;
    CANIDAR6       = null;
    CANIDAR7       = null;   
     
    CANIDMR0       = 0xFF;
    CANIDMR1       = 0xFF;
    CANIDMR2       = 0xFF;
    CANIDMR3       = 0xFF;
    CANIDMR4       = 0xFF;
    CANIDMR5       = 0xFF;
    CANIDMR6       = 0xFF;
    CANIDMR7       = 0xFF;
    //
    CANTIER = null;     
    CANCTL0_INITRQ = Disable;               //��ɳ�ʼ��
    while(CANCTL1_INITAK);                  //�ȴ�ȷ��

    CANRFLG_RXF = ClearFlag;     
    CANRIER_RXFIE = Enable;                 //ʹ�ܽ����ж�
    CANTIER_TXEIE = Disable;                //��ֹ�����ж� 
    
    CANCTL0_TIME   = Enable;                //ʹ��ʱ���  
    CANCTL0_CSWAI  = WaitRun;               //�ȴ�ģʽ�¿�������    
    CANCTL0_WUPE = Enable; 
}

/*-------------------------------------------------------------------------
* Function Name  : EXT_ID_TO_PGN
* Description    : ����չIDת��ΪPGN
* Input          : IDR0_Add          -> ��Ӧ��IDR0�ĵ�ַ
* Output         : None
* Return         : dwPGN
* onther         : 
--------------------------------------------------------------------------*/
INT32U    API_EXT_ID_TO_PGN(INT8U *IDR0_Add)
{
    INT32U    dwPGN;
    INT8U     *bp;
    
    bp = (INT8U*)&dwPGN;
    
    *(bp    ) = *(IDR0_Add    ); 
    *(bp + 1) = *(IDR0_Add + 1); 
    *(bp + 2) = *(IDR0_Add + 2); 
    *(bp + 3) = *(IDR0_Add + 3); 

    dwPGN = ((dwPGN & 0x7FFFF) >> 1) | ((dwPGN & 0xFFE00000) >> 3);

    return(GET_EXTPGN(dwPGN));                 //����PGN
}
/*-------------------------------------------------------------------------
* Function Name  : GET_EXTID_SA
* Description    : ��ȡԴ��ַ
* Input          : IDR3_Add          -> ��Ӧ��IDR3�ĵ�ַ
* Output         : None
* Return         : dwPGN
* onther         : 
--------------------------------------------------------------------------*/
INT8U    API_GET_EXTID_SA(INT8U *IDR3_Add)
{
    INT8U    SA;
    
    SA = *(IDR3_Add -1);
    SA = SA & 0x01;
    SA = SA << 7;
    SA = (*IDR3_Add >> 1) | SA;
    return(SA);
}
/*-------------------------------------------------------------------------
* Function Name  : GET_STAND_ID
* Description    : ��ȡ��׼ID
* Input          : IDR0_Add          -> ��Ӧ��IDR0�ĵ�ַ
* Output         : None
* Return         : dwPGN
* onther         : 
--------------------------------------------------------------------------*/
INT16U    API_GET_STAND_ID(INT8U *IDR0_Add)
{
    INT16U    dwPGN;
    INT8U     *bp;
    
    bp = (INT8U*)&dwPGN;
    
    *(bp    ) = *(IDR0_Add    ); 
    *(bp + 1) = *(IDR0_Add + 1); 


    dwPGN = dwPGN>>5;

    return(dwPGN);                 
}
/*-------------------------------------------------------------------------
* Function Name  : API_CANSendExtFrame
* Description    : 
* Input          : 
* Output         : None
* Return         : dwPGN
* onther         : 
--------------------------------------------------------------------------*/
INT8U API_CANSendExtFrame (INT32U id,INT8U priority,INT8U length,INT8U *txdata)
{
    INT8U txbuffer,index;
    INT16U cn = null;
    if (!CANTFLG) //Is Transmit Buffer full ? Full ( TXEx=0;)
      return   failt;
    if(id == null)
      return   failt;
    CANTBSEL = CANTFLG; /* Select lowest empty buffer */
    txbuffer = CANTBSEL; // Backup selected buffer
    /* Load Id to IDR Register */
    //*((unsigned long *) ((unsigned long)(&CANTXIDR0))) = id; // I appreciate this , easy and good.
    CANTXIDR0 = (INT8U)((id & 0x1fe00000)>>21);
    CANTXIDR1 = (INT8U)((id & 0x001c0000)>>13);
    CANTXIDR1 |= (INT8U)((id & 0x00038000)>>14);
    CANTXIDR1 |= 0x11;
    CANTXIDR2 = (INT8U)((id & 0x00007f80)>>7);
    CANTXIDR3 = (INT8U)((id & 0x0000007f)<<1);  

    if(length>8)
        length=8;
    for ( index=0; index < length; index++) {
        *(&CANTXDSR0 + index) = txdata[index]; //Load data to Tx buffer Data Segment Registers
    }

    CANTXDLR = length; /* Set Data Length Code */
    CANTXTBPR = priority; /* Set Priority */
    CANTFLG = txbuffer; /* Start transmission */
    while ((CANTFLG & txbuffer) != txbuffer)
    {
          //; // Wait for Transmission   completion
          cn++;
          if(cn>WaitOverTime)
              break;
    }
    return success;
}
/*-------------------------------------------------------------------------
* Function Name  : API_CANSendFrame
* Description    : 
* Input          : 
* Output         : None
* Return         : dwPGN
* onther         : 
--------------------------------------------------------------------------*/
INT8U API_CANSendFrame (INT32U id,INT8U priority,INT8U length,INT8U *txdata)
{
    INT8U txbuffer,index;
    INT16U cn = null;
    if (!CANTFLG) //Is Transmit Buffer full ? Full ( TXEx=0;)
      return   failt;

    if(id == null)
      return   failt;
    
    CANTBSEL = CANTFLG; /* Select lowest empty buffer */
    txbuffer = CANTBSEL; // Backup selected buffer
    /* Load Id to IDR Register */
    //*((unsigned long *) ((unsigned long)(&CANTXIDR0))) = id; // I appreciate this , easy and good.
    CANTXIDR0 = (INT8U)(id>>3);
    CANTXIDR1 = id<<5;
    CANTXIDR2 = 0;
    CANTXIDR3 = 0;
    if(length>8)
        length=8;
    for ( index=0; index < length; index++) {
        *(&CANTXDSR0 + index) = txdata[index]; //Load data to Tx buffer Data Segment Registers
    }

    CANTXDLR = length; /* Set Data Length Code */
    CANTXTBPR = priority; /* Set Priority */
    CANTFLG = txbuffer; /* Start transmission */
    while ((CANTFLG & txbuffer) != txbuffer)
    {
          //; // Wait for Transmission   completion
          cn++;
          if(cn>WaitOverTime)
              break;
    }
    return success;
}

/*-------------------------------------------------------------------------
* Function Name  : API_CAN_Rev_isr
* Description    : ��ȡ��׼ID
* Input          : IDR0_Add          -> ��Ӧ��IDR0�ĵ�ַ
* Output         : None
* Return         : dwPGN
* onther         : 
--------------------------------------------------------------------------*/
interrupt void API_CAN_Rev_isr(void)
{
    INT32U    stand_id;
    //INT8U     SA;
    
    stand_id = API_GET_STAND_ID((INT8U*)&CANRXIDR0);
    


 
    //*/              
    CANRFLG_RXF = ClearFlag; 
}