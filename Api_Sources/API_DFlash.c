#define  GLOBALS_API_DFLASH
#include "../App_Headers/includes.h"

/*-------------------------------------------------------------------------
* Function Name  : Api_Flash_Init
* Description    : FLASH��ʼ��
* Input          : None
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
void API_Flash_Init(void)
{
     FCNFG          = Disable;                   //��ֹ����ж�
     FERCNFG        = Disable;                   //��ֹ�����ж�
     if(false != FERSTAT)
     {
          FERSTAT = 0x03;
     }
     if(false == FCLKDIV_FDIVLD)
     {
          if(True == FCLKDIV_FDIVLCK)
          {
               FCLKDIV_FDIVLCK = Disable;         //������дʱ��Flashʱ�ӷ�Ƶ
          }
          FCLKDIV_FDIV    = 32;                 //10
          FCLKDIV_FDIVLCK = Enable;               //��ֹ��дʱ��Flashʱ�ӷ�Ƶ
     }
}
/*-------------------------------------------------------------------------
* Function Name  : API_Flash_byte_read
* Description    : ��ȡ�ֽ�
* Input          : None
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
INT8U API_Flash_byte_read(INT16U _addr)
{
    return *(INT8U *)_addr;  
}
/*-------------------------------------------------------------------------
* Function Name  : API_DFlashCommSequence
* Description    : DFlash��������
* Input          : bCommandCounter
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
INT8U  API_DFlashCommSequence(INT8U bCommandCounter)
{
    INT8U     bCounter;
    INT32U    dwDelay;
    
    if(MaxDFlashCommandCounter <= bCommandCounter)
    {
         return RunParameterErr;
    }
    //����������
    dwDelay = null;
    while(!FSTAT_CCIF)
    {
         dwDelay++;
         if(dwDelay > MaxDelayTime)
         {
              bReturn = RunOverTimeErr;
              break;
         }
    }
    //�����������
    if(dwDelay < MaxDelayTime)
    {
         //����ACCERR��FPVIOL��־
         if((True == FSTAT_FPVIOL) ||
            (True == FSTAT_ACCERR))
         {
              FSTAT = (FSTAT_FPVIOL_MASK | FSTAT_ACCERR_MASK);
         }
         //װ������
         for(bCounter = 0; bCounter <= bCommandCounter; bCounter++)
         {
              FCCOBIX = bCounter;
              FCCOB   = FlashCommandArray[bCounter];
         }
         FSTAT_CCIF = True;                     //��������
         //����������
         dwDelay = 0;
         while(!FSTAT_CCIF)
         {
              dwDelay++;
              if(dwDelay > MaxDelayTime)
              {
                   bReturn = RunOverTimeErr;
                   break;
              }
         }
         if(dwDelay < MaxDelayTime)
         {
              if(false != FSTAT_ACCERR)
              {
                   bReturn = RunErrACCERR;
              }
              else
              {
                   if(false != FSTAT_FPVIOL) 
                   {
                        bReturn = RunErrFPVIOL;  
                   }
                   else
                   {
                        if(false != FSTAT_MGSTAT1)
                        {
                             bReturn = RunErrMGSTAT1;
                        }
                        else
                        {
                             if(false != FSTAT_MGSTAT0)
                             {
                                  bReturn = RunErrMGSTAT0;
                             }
                        }
                   }
              }
         }
    }
    return(bReturn);
}

/*-------------------------------------------------------------------------
* Function Name  : API_DFlashEraseSector
* Description    : DFlash��������
* Input          : wDestination
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
INT8U   API_DFlashEraseSector(INT16U wDestination)
{
    INT16U    wCommand;
    
    if((wDestination & (INT16U)(DFLASH_SECTOR_SIZE -1)) != 0)
    {
         bReturn = RunParameterErr;
    }
    else
    {
    	   bReturn = RunComplete;
         if((wDestination < DFLASH_BLOCK_START_ADDR) || \
            (wDestination >= DFLASH_BLOCK_END_ADDR)  || \
            ((wDestination + DFLASH_SECTOR_SIZE) > DFLASH_BLOCK_END_ADDR))
         {
              bReturn = RunParameterErr;
         }
         else
         {    
              wDestination = wDestination & (INT16U)~(DFLASH_SECTOR_SIZE -1); 
              //����׼��
              wCommand = ((INT16U)(DFLASH_ERASE_SECTOR) << 8);
              FlashCommandArray[0] = (wCommand|GLOBAL_ADDRESS_DFLASH);
              FlashCommandArray[1] = wDestination;
              bReturn = API_DFlashCommSequence(DFLASH_ERASE_COM_LENGTH);
         }
    }
    return(bReturn);
}
/*-------------------------------------------------------------------------
* Function Name  : API_DFlashEraseVerify
* Description    : DFlash��������
* Input          : wDestination
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
INT8U   API_DFlashEraseVerify(INT16U wDestination, INT16U wSize)
{
    INT16U    wWordCounter;
    INT16U    wCommand;
    
    bReturn = RunComplete;
    if((0 != (wSize % WordSize)) ||
       (wSize > DFLASH_SECTOR_SIZE))
    {
         bReturn = RunParameterErr;
    }
    else
    {
         if(0 != wSize)
         {
              wWordCounter             = (INT16U)(wSize / WordSize);
              wCommand                 = (((INT16U)(DFLASH_ERASE_VERIFY)) << 8);
              FlashCommandArray[0]    = (wCommand | GLOBAL_ADDRESS_DFLASH);
              FlashCommandArray[1]    = wDestination;
              FlashCommandArray[2]    = wWordCounter;
              bReturn = API_DFlashCommSequence(DFLASH_ERASE_VERIFY_COM_LENGTH);
         }
    }
    return(bReturn);
}
/*-------------------------------------------------------------------------
* Function Name  : API_DFlashEraseVerify
* Description    : DFlash��������
* Input          : wDestination
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
INT8U   API_DFalshProgram(INT16U wDest,INT16U wByteNub,INT16U *wSource)
{
    INT8U     bLoopIndex;
    INT8U     bCounter;
    INT8U     bIndex;
    INT16U    wEndAdd;
    INT16U    wCommand;
    

    //else
    {
    	   bReturn = RunComplete;
         wEndAdd = wDest + wByteNub;
         //��������ȷ��
         if((0 != (wByteNub % WordSize)) || 
            (DFLASH_BLOCK_END_ADDR < wEndAdd))
         {
              bReturn = RunParameterErr;
         }
         else
         {
              wCommand = (((INT16U)(DFLASH_PROGRAM)) << 8);
              while(wDest < wEndAdd)
              {
                   FlashCommandArray[0] = (wCommand | GLOBAL_ADDRESS_DFLASH);
                   FlashCommandArray[1] = wDest;
                   if(MaxProgramByteNumber < wByteNub) 
                   {
                        bLoopIndex = DFLASH_PROGRAM_COM_LENGTH;
                   }
                   else
                   {
                        bLoopIndex = (INT8U)(wByteNub / WordSize);
                   }
                   for(bCounter = 0;bCounter < bLoopIndex;bCounter++)
                   {
                        FlashCommandArray[bCounter + 2] = *wSource;
                        wDest += WordSize;
                        wSource++;
                        wByteNub -= WordSize;   
                   }
                   bIndex = bLoopIndex + 1; 
                   
                   if(RunComplete != API_DFlashCommSequence(bIndex))
                   {
                        break;
                   }
              }
         }
    }
    return(bReturn);
}