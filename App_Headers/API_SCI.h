
#ifdef        GLOBALS_API_SCI
    #define   EXTERN_API_SCI
   
#else
    #define   EXTERN_API_SCI     extern
#endif

#ifndef API_SCI_H_
#define API_SCI_H_

	EXTERN_API_SCI     void            Api_SCI_Init(void);
	EXTERN_API_SCI     void            Api_SCI_Trans_Byte(INT8U data);
	EXTERN_API_SCI     void            Api_SCI_Trans_Bytes(INT8U *pStr, INT8U length);
	EXTERN_API_SCI     interrupt void  Api_SCI_Rev_isr(void);


  EXTERN_API_SCI     INT8U           LINCheckState(void);	
  EXTERN_API_SCI     Bool            LINSendMsg(Lin_Send_Msg msg,INT8U len);
  EXTERN_API_SCI     Bool            LINSendChar(Bool brk, INT8U ch);
  EXTERN_API_SCI     INT8U           LINCalcChecksum(INT8U *data);
  
#endif /* API_SCI_H_ */