#define  GLOBALS_GUI_DISP
#include "../App_Headers/includes.h"


HardWireCheck WarningCheck;
HardWireCheck FuelAddCheck;
HardWireCheck FuelMinCheck;
HardWireCheck CanAddCheck;
HardWireCheck CanMinCheck;
HardWireCheck ChargeCheck;
extern volatile uint8_t flash_1s;

void HardWireCheckInit(void)
{
    WarningCheck.curTimer = 1;
    WarningCheck.PushTimer = 0;
    WarningCheck.maxTimer = 4;
    WarningCheck.valid = Enable;
    WarningCheck.enable = Disable;
    
    FuelAddCheck.curTimer = 0;
    FuelAddCheck.maxTimer = 4;
    FuelAddCheck.valid = Enable;
    FuelAddCheck.enable = Disable;
    
    FuelMinCheck.curTimer = 1;
    FuelMinCheck.maxTimer = 3;
    FuelMinCheck.valid = Enable;
    FuelMinCheck.enable = Disable;
    
    CanAddCheck.curTimer = 0;
    CanAddCheck.maxTimer = MaxStep;
    CanAddCheck.valid = Enable;
    CanAddCheck.enable = Enable;
    
    CanMinCheck.curTimer = 0;
    CanMinCheck.maxTimer = MaxStep;
    CanMinCheck.valid = Enable;
    CanMinCheck.enable = Enable;
    
    ChargeCheck.curTimer = 0;
    ChargeCheck.maxTimer = MaxStep;
    ChargeCheck.valid = Enable;
    ChargeCheck.enable = Enable;
    
}


/*-------------------------------------------------------------------------
* Function Name  : Gui_ButoonProc
* Description    : 加载数据
* Input          : None
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
void Gui_ButoonProc(void)
{     
      //充电灯
      if((pChargeLedInput == PushDown) && (ChargeCheck.enable))
      {         
          ChargeCheck.PushTimer++;
          if((ChargeCheck.PushTimer >= 5) && (ChargeCheck.valid))
          {
              ChargeCheck.valid = Disable;
              WarningCheck.enable = Enable;
              pChargeledLed = 1; 
              pChargeledOut = 1;                                                   
          }                 
      }
      
      if(pChargeLedInput == UpSpring)
      {
          ChargeCheck.PushTimer = 0;
          ChargeCheck.valid = Enable;  
          pChargeledOut = 0;    
      }
      //报警硬线监测
      if((pHardwiredInput == PushDown) && (WarningCheck.enable))
      {         
          WarningCheck.PushTimer++;
          if((WarningCheck.PushTimer >= 5) && (WarningCheck.valid))
          {
              WarningCheck.valid = Disable;              
              if(WarningCheck.curTimer < WarningCheck.maxTimer)
              {    
                   pHardwiredOut = 0; 
                   WarningCheck.curTimer++;                               
                   if(WarningCheck.curTimer == WarningCheck.maxTimer)
                   {                   
                        FuelAddCheck.enable = Enable;
                        pHardwiredLed = 1;                      
                   }                   
              }
              else
              {
                     
              }                                
          }                 
      }
      if(pHardwiredInput == UpSpring)
      {
          WarningCheck.PushTimer = 0;
          WarningCheck.valid = Enable;  
          pHardwiredOut = 1;    
      }
      
      //燃油加监测
      if((pFuelAddInput == PushDown) && (FuelAddCheck.enable) )
      {
          FuelAddCheck.PushTimer++;
          if((FuelAddCheck.PushTimer >= 5) && (FuelAddCheck.valid))
          {
              FuelAddCheck.valid = Disable;
               
              if( FuelAddCheck.curTimer < FuelAddCheck.maxTimer)
              {
                   //FuelMinCheck.enable = Enable;
                   pFuelAddOut = 0; 
                   FuelAddCheck.curTimer++;
                   if(FuelAddCheck.curTimer == FuelAddCheck.maxTimer) 
                   {
                      CanAddCheck.enable = Enable;
                      pFuelAddLed = 1;         
                   }
              }
              else
              {
                   
                   //FuelAddCheck.curTimer = 0;
              }             
          }
      }
      if((pFuelAddInput == UpSpring) && (!FuelAddCheck.valid))
      {
          FuelAddCheck.PushTimer--;
          if(FuelAddCheck.PushTimer == 0)
          {
              pFuelAddOut = 1;
              FuelAddCheck.valid = Enable;  
          }          
                               
      }
      
      //燃油减监测
      if((pFuelMinInput == PushDown) && (FuelMinCheck.enable))
      {
          FuelMinCheck.PushTimer++;
           
          if((FuelMinCheck.PushTimer >= 5) && (FuelMinCheck.valid))
          {
              pFuelMinOut = 0;
              FuelMinCheck.valid = Disable;
              if( FuelAddCheck.curTimer > 0)
              {                 
                   FuelAddCheck.curTimer--; 
                   if(FuelAddCheck.curTimer == 0)
                   {
                        CanAddCheck.enable = Enable;
                        pFuelMinLed = 1;
                   }
              }
              else
              {
                  
              }
                
          }
      }
      if((pFuelMinInput == UpSpring) && (!FuelMinCheck.valid))
      {
          FuelMinCheck.PushTimer--;
          if(FuelMinCheck.PushTimer == 0)
          {
              pFuelAddOut = 1;
              FuelMinCheck.valid = Enable;  
          }     
         
          //FuelMinCheck.valid = Enable;  
          //pFuelMinOut = 1;    
      }
           
      //两个按键 同时按3秒
      if((pSBRInput == PushDown) && (pSBLInput == PushDown))
      {
          if((Key.PushTime2 >= 100)&&(Key.PushTime1 >= 100))
          {              
              if(Key.Valid3 == Enable)
              {                 
                  //Key.MainMenu ++;     //切换到自动
                  if(Key.MainMenu == Manual)
                  {
                     RunStep = 0;
                     Key.MainMenu = Auto;
                     
                  }
                  Key.Valid3 = Disable;
                  Key.Valid2 = Disable;
                  Key.Valid1 = Disable;
              }
          }
      }
      if(CanAddCheck.enable)
      {  
          if((pSBLInput == PushDown) && (pSBRInput == UpSpring))//左键
          {         
              if((Key.PushTime1 >= 5)&&(Key.PushTime2 == null))
              {
                  if(Key.Valid1)
                  {   
                      if(Key.MainMenu == Auto)
                      {
                         Key.MainMenu = Manual;
                      } 
                      else
                      {                                                                                                
                          if(RunStep >= MaxStep)
                          {
                              //RunStep = 0;                            
                          }
                          else 
                          {
                              RunStep ++;
                              if(RunStep == MaxStep)
                              {
                                  //CanMinCheck.enable = Enable;
                                  pCanAddLed = 1;
                                  pMouseEn = 1;
                                  
                              }
                          }
                      }
                      Key.Valid1 = Disable;
                  }
              }          
          }
      }
      
      if(CanMinCheck.enable)
      {  
          if((pSBRInput == PushDown) && (pSBLInput == UpSpring)) //右键
          {          
              if((Key.PushTime2 >= 5)&&(Key.PushTime1 == null))
              {
                  if(Key.Valid2)
                  {   
                      if(Key.MainMenu == Auto)
                      {
                         Key.MainMenu = Manual;
                      } 
                      else
                      {
                          if(RunStep == 0)
                          {
                                FuelAddCheck.enable = Enable;
                                FuelMinCheck.enable = Enable;
                                //RunStep = MaxStep;
                                
                          }
                          else if(RunStep >= 1)
                          {
                                RunStep --;
                                if(RunStep == 0)
                                {
                                    pCanMinLed = 1;
                                    WarningCheck.enable = Enable;
                                }
                          }
                      }
                      Key.Valid2 = Disable;
                  }
              }          
          }         
      }
      //自动
      if(Key.MainMenu == Auto) 
      {                
           if(Key.AutoTime1 >= 400)   //glz--20170215
          {
              Key.AutoTime1 = null;
              
              RunStep ++;                                           
              if(RunStep > MaxStep)
              {
                  RunStep = null;                                           
              }             
          }    
      }
  
      if(pSBLInput == UpSpring)
      {
          Key.PushTime1 = null;
          Key.Valid1 = Enable;         
      }
      if(pSBRInput == UpSpring)
      {
          Key.PushTime2 = null;  
          Key.Valid2 = Enable;        
      }
      if((pSBLInput == UpSpring)&&(pSBRInput == UpSpring))
      {
          Key.Valid3 = Enable; 
      }
}





