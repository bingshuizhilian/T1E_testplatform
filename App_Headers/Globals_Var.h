#ifdef        GLOBALS_VARIABLE
    #define   EXTERN_VAR
    
#else
    #define   EXTERN_VAR     extern
    
#endif

#ifndef GLOBALS_VAR_H_
#define GLOBALS_VAR_H_ 



    

    EXTERN_VAR     volatile  INT8U               SCIRV[130];
    EXTERN_VAR     volatile  INT8U               bReturn;         
    EXTERN_VAR     volatile  INT16U              FlashCommandArray[MaxDFlashCommandCounter];       
    EXTERN_VAR     volatile  ClockType           Clock;
    EXTERN_VAR     volatile  INT8U               rvcnt;     
    EXTERN_VAR     volatile  INT16U              BusOffTime; 
    EXTERN_VAR     volatile  INT8U               FuelStep;
    EXTERN_VAR     volatile  INT8U               TempStep;
    EXTERN_VAR     volatile  INT8U               LedStep;
    EXTERN_VAR     volatile  INT8U               LedStep1;   
    
    EXTERN_VAR     volatile  INT8U               RevOk[6];
    EXTERN_VAR     volatile  INT8U               SnedOk;
    EXTERN_VAR     volatile  INT8U               RunStep;
    EXTERN_VAR     volatile  INT8U               MaxStep;
    EXTERN_VAR     volatile  KeyType             Key;

    
    EXTERN_VAR     volatile  INT8U               LCDFP4BP;
    EXTERN_VAR     volatile  INT8U               LCDFP5BP;
    EXTERN_VAR     volatile  INT8U               LCDFP6BP;
    EXTERN_VAR     volatile  INT8U               LCDFP7BP;
    EXTERN_VAR     volatile  INT8U               LCDFP8BP;
    EXTERN_VAR     volatile  INT8U               LCDFP9BP;
    EXTERN_VAR     volatile  INT8U               LCDFP10BP;
    EXTERN_VAR     volatile  INT8U               LCDFP11BP;
    EXTERN_VAR     volatile  INT8U               LCDFP12BP;
    EXTERN_VAR     volatile  INT8U               LCDFP13BP;
    EXTERN_VAR     volatile  INT8U               LCDFP14BP;
    EXTERN_VAR     volatile  INT8U               LCDFP15BP;
    EXTERN_VAR     volatile  INT8U               LCDFP16BP;
    EXTERN_VAR     volatile  INT8U               LCDFP17BP;
    EXTERN_VAR     volatile  INT8U               LCDFP18BP;
    EXTERN_VAR     volatile  INT8U               LCDFP19BP;
    EXTERN_VAR     volatile  INT8U               LCDFP20BP;
    EXTERN_VAR     volatile  INT8U               LCDFP21BP;
    EXTERN_VAR     volatile  INT8U               LCDFP22BP;

    /*EXTERN_VAR     volatile  _SendCanMsg         Can_120_Msg;
    EXTERN_VAR     volatile  _SendCanMsg         Can_130_Msg;
    EXTERN_VAR     volatile  _SendCanMsg         Can_125_Msg;
    EXTERN_VAR     volatile  _SendCanMsg         Can_320_Msg;
    EXTERN_VAR     volatile  _SendCanMsg         Can_321_Msg;
    EXTERN_VAR     volatile  _SendCanMsg         Can_360_Msg; //glz--20170208
    EXTERN_VAR     volatile  _SendCanMsg         Can_361_Msg;
    EXTERN_VAR     volatile  _SendCanMsg         Can_33A_Msg;
    EXTERN_VAR     volatile  _SendCanMsg         Can_420_Msg;
    EXTERN_VAR     volatile  _SendCanMsg         Can_523_Msg;
    EXTERN_VAR     volatile  _SendCanMsg         Can_326_Msg;
    EXTERN_VAR     volatile  _SendCanMsg         Can_363_Msg;
    EXTERN_VAR     volatile  _SendCanMsg         Can_166_Msg;
    EXTERN_VAR     volatile  _SendCanMsg         Can_530_Msg;
    EXTERN_VAR     volatile  _SendCanMsg         Can_436_Msg;   */

    EXTERN_VAR     volatile  Lin_Send_Msg        LinRadarMsg; 
    EXTERN_VAR     volatile  Lin_Send_Msg        LinTpmsMsg; 
    EXTERN_VAR     volatile  Lin_RevMsg          LinRevMsg; 
    
    EXTERN_VAR     volatile  INT16U              RevValue;
    EXTERN_VAR     volatile  INT16U              VehValue;
    
    EXTERN_VAR     volatile  INT16U              CruiseVehValue;
    
    EXTERN_VAR     volatile  INT16U              TpmsCn;
    
    EXTERN_VAR     volatile  INT16U              Linsend;
    EXTERN_VAR     volatile  INT32U wtemp;
#endif /* GLOBALS_VAR_H_ */
