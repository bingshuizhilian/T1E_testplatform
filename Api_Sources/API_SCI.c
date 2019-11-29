#include "../App_Headers/includes.h"
#define  GLOBALS_API_SCI
/*-------------------------------------------------------------------------
* Function Name  : Api_SCI_Init
* Description    : SCI模块初始化
* Input          : 
* Output         : None
* Return         : None
* onther         : 

When IREN = 0 then,
SCI baud rate = SCI bus clock / (16 x SBR[12:0])
When IREN = 1 then,
SCI baud rate = SCI bus clock / (32 x SBR[12:1])

--------------------------------------------------------------------------*/
void Api_SCI_Init(void)
{
    SCISR2_AMAP = Disable;
    SCICR1_LOOPS   = Disable;   //串口正常模式
    SCICR1_SCISWAI = Disable;    //使能等待模式
    SCICR1_M       = Disable;   //8 byte 模式
    SCICR1_WAKE    = Enable;    //Adrress Wake
    SCICR1_PE      = Disable;   //禁止校验
    SCISR1_RDRF    = Disable;
    
    SCISR2_BRK13 = Enable; //14bit break    
    SCISR2_AMAP = Disable;
                
    SCIBDH_TNP     = div4;
    SCIBDH_IREN    = Disable;   //禁止红外线
    SCIBD_SBR      = baud_9600;
    
    SCICR2_TIE  = Disable;
    SCICR2_TCIE = Disable;
    SCICR2_ILIE = Disable;
    SCICR2_RE  = Enable;    //使能接收
    SCICR2_TE  = Enable;    //使能发送
    SCICR2_RWU = Enable;
    SCICR2_SBK = Disable;   //
  
    SCICR2_RIE = Enable;    //使能接收中断
    
    SCISR2_AMAP = Enable;
    SCIACR2_BKDFE   = Enable;   //使能断点检测电路
    SCIACR2_BERRM   = 0;    
    SCIACR1_BERRIE  = Disable;  //位错误
    SCIACR1_RXEDGIE = Disable;  //
    SCIACR1_BKDIE   = Enable;   //断点检测使能
    SCIASR1_BKDIF = ClearFlag; 
}
/*-------------------------------------------------------------------------
* Function Name  : Api_SCI_Trans_Bytes
* Description    : 串口发送
* Input          : INT8U *str,INT16U len
* Output         : None
* Return         : None
* onther         : str:发送字符串   len:发送数据长度
--------------------------------------------------------------------------*/
void Api_SCI_Trans_Bytes(INT8U *str,INT8U len)
{
    INT8U i;    
    for(i=0;i<len;i++)
    {
       Api_SCI_Trans_Byte((*str));
       str++;
    }
}
/*-------------------------------------------------------------------------
* Function Name  : Api_SCI_Trans_Byte
* Description    : 串口发送
* Input          : INT8U data
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
void  Api_SCI_Trans_Byte(INT8U data)
{
    while(SCISR1_TDRE == null);
    SCIDRL = data;
    while(!SCISR1_TC);    
}

/*-------------------------------------------------------------------------
* Function Name  : Api_SCI_Rev_isr
* Description    : 串口接收中断
* Input          : 
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
interrupt void Api_SCI_Rev_isr(void)
{        
    //断点检测中断
    if(SCIASR1_BKDIF)
    {  
        rvcnt = null;            
    }     

          if(SCISR1_RDRF)
          {                    
              SCIRV[rvcnt] = SCIDRL;
              rvcnt ++;    
          }

          if(SCIRV[0] == 0x55)
          {                  
              if(SCIRV[1] == 0x32)
              {
                  Linsend = Enable;
              }             
          }
          else
          {
              rvcnt = null;
              SCIRV[0] = 0;
              SCIRV[1] = 0;
              SCIRV[2] = 0;
              SCIRV[3] = 0;              
          }

    SCIASR1_BKDIF = ClearFlag;      
    SCISR1_RDRF = ClearFlag;          
}

////////////////////////////
INT8U LINCheckState(void)
{
    return(LinRevMsg.state);
}

Bool LINSendChar(Bool brk, INT8U ch)
{
    while(!(SCISR1 &0x80))
      ;
    if(brk)
    {
        SCICR2 |= 0x01;
        SCICR2 &= ~0x01;
        LinRevMsg.tout = 50;
    }
    else
        SCIDRL = ch;
    return(True);
}
//////////////////////////////////////////////////////////////////////////////
// Checksum Calculation Routine
//////////////////////////////////////////////////////////////////////////////

INT8U LINCalcChecksum(INT8U *data)
{
    INT16U sum = 0;
    INT8U i;

    for(i = 0; i < 7; i++)
    {
        sum += data[i];
        if(sum&0xFF00)
            sum = (sum&0x00FF) + 1;
    }
    sum ^= 0x00FF;
    return((INT8U)sum);
}
Bool LINSendMsg(Lin_Send_Msg msg,INT8U len)
{
    INT8U check_sum,i;
    if(LinRevMsg.state != LIN_STATE_IDLE)
        return(false);
    LinRevMsg.error_code = 0;
    
        if(!LINSendChar(True, 0x00))
            return(false);
        //if(!LINCheckSend(lin_num, LIN_STATE_BREAK, 0x00))
        //    return(FALSE);
        if(!LINSendChar(false, 0x55))
            return(false);
        //if(!LINCheckSend(lin_num, LIN_STATE_SYNCH, 0x55))
        //    return(FALSE);
        if(!LINSendChar(false, msg.id))
            return(false);
        //if(!LINCheckSend(lin_num, LIN_STATE_ID, id_index))
        //    return(FALSE);

        /////////////
        check_sum = LINCalcChecksum(msg.data);
        for(i = 0; i < len; i++)
        {
            if(!LINSendChar(false, msg.data[i]))
                return(false);
            //if(!LINCheckSend(lin_num, LIN_STATE_DATA_0+i, msg.data[i]))
            //    return(false);
        }
        if(!LINSendChar(false, check_sum))
            return(false);
        //if(!LINCheckSend(lin_num, LIN_STATE_CHECKSUM, check_sum))
        //    return(FALSE);
        LinRevMsg.state = LIN_STATE_IDLE;

    return(True);
}
