
#ifdef        GLOBALS_API_ATD
    #define   EXTERN_API_ATD
   
#else
    #define   EXTERN_API_ATD     extern
#endif

#ifndef API_ATD_H_
#define API_ATD_H_
    #define             CHNAL1          1
    #define             CHNAL2          2
	  #define             CHNAL3          3
	  
    #define             SMP_TIME        0
    #define             SMP_PRE         16
    
  	EXTERN_API_ATD      INT8U           ADCH_SEL;
  	EXTERN_API_ATD      INT16U          ATD_Time;
    EXTERN_API_ATD      INT16U          ATD_T3s;
    	
    EXTERN_API_ATD      void            API_ATD_init(void);
  	EXTERN_API_ATD      void            API_GetSensorAD(void);
#endif /* API_ATD_H_ */
