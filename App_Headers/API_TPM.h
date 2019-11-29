
#ifdef        GLOBALS_API_TPM
    #define   EXTERN_API_TPM
   
#else
    #define   EXTERN_API_TPM     extern
#endif

#ifndef API_TPM_H_
#define API_TPM_H_
  
        #define           TPM_DIV4              2
        #define           TPM_DIV2              1
        #define           TPM_DIV1              0
        #define           TPM_DIV128            7

  
        #define           TT_10ms                 5
        #define           TT_15ms                 7
        #define           TT_30ms                 TT_15ms *2
        #define           TT_100ms                49
        #define           TT_200ms                96 
        #define           TT_120ms                58 
        #define           TT_180ms                87 
        #define           TT_240ms                117 
        #define           TT_250ms                122 
        #define           TT_340ms                165
        #define           TT_500ms                TT_100ms *5
        #define           TT_750ms                367
        #define           TT_1s                   490
        #define           TT_1_5s                 735
        #define           TT_2s                   980
        #define           TT_2_5s                 1225
        #define           TT_3s                   1465
        #define           TT_6s                   2930
        #define           TT_8s                   3186
  
        EXTERN_API_TPM              void        API_Timer0_Init(INT8U TPM_DIV);
        EXTERN_API_TPM              void        API_Timer1_Init(INT8U TPM_DIV);
        EXTERN_API_TPM    interrupt void        API_Timer0_isr(void);
        EXTERN_API_TPM    interrupt void        API_Timer1_isr(void);


  
#endif /* API_TPM_H_ */
