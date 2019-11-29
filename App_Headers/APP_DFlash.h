#ifdef        GLOBALS_APP_DFLASH
    #define   EXTERN_APP_DFLASH
   
#else
    #define   EXTERN_APP_DFLASH     extern
#endif

#ifndef APP_DFLASH_H_
#define APP_DFLASH_H_

      #define   AccDataFlag                     0x55
      
      #define   PAGE_LEN                        256 
      #define   Register_Len                    16      
      #define   pSCL_Dir                        DDRS_DDRS4
      #define   pSDA_Dir                        DDRS_DDRS7
      #define   pSCL_Pull                       PERS_PERS4
      #define   pSDA_Pull                       PERS_PERS7

      #define   WaitOverTime                   50000

      EXTERN_APP_DFLASH        void App_CopyRam(INT8U *Dp,INT8U *Sp,INT8U Nub);
      
 
      
#endif /* APP_DFLASH_H_ */