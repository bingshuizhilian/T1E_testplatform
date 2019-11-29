
#ifdef        GLOBALS_API_LCD
    #define   EXTERN_API_LCD
    
   const       INT8U    Matrix1[]=
   { 
      //0     1    2    3    4    5    6    7    8    9  
       0xd7,0x06,0xe3,0xa7,0x36,0xb5,0xf5,0x07,0xf7,0xb7
   }; 
   
   const       INT8U    Matrix2[]=
   { 
      //0     1    2    3    4    5    6    7    8    9  
       0xeb,0x0a,0xc7,0x8f,0x2e,0xad,0xed,0x0b,0xef,0xaf
   };
   
   const       INT8U    Matrix3[]=
   { 
      //0     1    2    3    4    5    6    7    8    9  
       0x5f,0x06,0x6b,0x2f,0x36,0x3d,0x7d,0x07,0x7f,0x3f
   };
           
#else
    #define   EXTERN_API_LCD     extern
#endif
#ifndef API_LCD_H_
#define API_LCD_H_

     #define   Duty4                   0                   // 1/2 Duty
     #define   IRCCLK_1M               1                   // IRCCLK 1M
    
       
     EXTERN_API_LCD       void         API_LCD_Init(void);
     EXTERN_API_LCD       void         Api_LCD_Display(void);


#endif /* API_LCD_H_ */
