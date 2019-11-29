
#ifdef        GLOBALS_API_RTC
    #define   EXTERN_API_RTC


#else
    #define   EXTERN_API_RTC     extern
#endif
#ifndef API_RTC_H_
#define API_RTC_H_

        #define           T_50ms                50 
        #define           T_100ms               100           
        #define           T_1s                  10  
        #define           T_200ms               2
        #define           T_300ms               3
        #define           T_400ms               4
        #define           T_500ms               5
        #define           T_600ms               6
        #define           T_700ms               7
        #define           T_800ms               8
        #define           T_2s                  T_100ms*20
        #define           T_3s                  30
        #define           T_3_5s                35
        #define           T_4s                  40
        #define           T_5s                  50
        #define           T_6s                  60
        #define           T_2_5s                25
        #define           T_8s                  80
        #define           T_9s                  90
   
        
        EXTERN_API_RTC  interrupt   void        API_RTC_isr(void);
        EXTERN_API_RTC              void        API_Set1000msTimer(INT16U Second,ClockType *T);
        EXTERN_API_RTC              INT8U       API_1000msTimerOver(ClockType *T);
        EXTERN_API_RTC              void        API_Set500msTimer(INT16U Second,ClockType *T);
        EXTERN_API_RTC              INT8U       API_500msTimerOver(ClockType *T);          
        EXTERN_API_RTC              void        API_Set10msTimer(INT16U Second,ClockType *T);
        EXTERN_API_RTC              INT8U       API_10msTimerOver(ClockType *T);
        EXTERN_API_RTC              void        API_Set100msTimer(INT16U Second,ClockType *T);
        EXTERN_API_RTC              INT8U       API_100msTimerOver(ClockType *T);
        EXTERN_API_RTC              void        API_Set30msTimer(INT16U Second,ClockType *T);
        EXTERN_API_RTC              INT8U       API_30msTimerOver(ClockType *T);
        

#endif /* API_RTC_H_ */