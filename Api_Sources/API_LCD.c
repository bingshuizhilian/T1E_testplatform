#define GLOBALS_API_LCD
#include "../App_Headers/includes.h"


/*-------------------------------------------------------------------------
* Function Name  : API_LCD_Init
* Description    : 
* Input          : 
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
void    API_LCD_Init(void)
{
    INT8U     b;
    INT8U     *bp;

    LCDCR1_LCDSWAI = Disable;               //在停止模式下运行
    LCDCR0_DUTY    = Duty4;                  // 1/4 Duty
    LCDCR0_LCLK    = IRCCLK_1M;            // IRCCLK 1M
    
         
    bp = &LCDRAM0;         
    for(b = 0; b < 20;b++)
    {
         *bp = 0;                           //清零LCDRAM
    }
    
    FPENR0 = 0xf0;                   //初始化各段
    FPENR1 = 0xff;                   //初始化各段
    FPENR2 = 0x7f;                   //初始化各段
    FPENR3 = 0x00;                   //初始化各段
    FPENR4 = 0x00;                   //初始化各段
         
    LCDCR0_LCDEN   = Enable;               //使能LCD
    
}

/*-------------------------------------------------------------------------
* Function Name  : Api_LCD_Display
* Description    : LCD显示
* Input          : None
* Output         : None
* Return         : None
* onther         : 
--------------------------------------------------------------------------*/
void Api_LCD_Display(void) 
{

    LCDFP9BP = Matrix1[RunStep / 100] >> 4;
    LCDFP10BP = Matrix1[RunStep / 100];
    
    LCDFP11BP = Matrix1[(RunStep / 10) % 10]>>4;
    LCDFP12BP = Matrix1[(RunStep / 10) % 10];

    LCDFP13BP = Matrix1[(RunStep % 10)]>>4;
    LCDFP14BP = Matrix1[(RunStep % 10)];

    
    if(RunStep > 23)
    {
        LCDFP19BP = Matrix1[((RunStep -24) / 10) %10]>>4;
        LCDFP20BP = Matrix1[((RunStep -24) / 10) %10];

        LCDFP21BP = Matrix1[((RunStep -24) % 10)]>>4;
        LCDFP22BP = Matrix1[((RunStep -24) % 10)];
    }
    else
    {
        LCDFP19BP = Matrix1[0]>>4;
        LCDFP20BP = Matrix1[0];

        LCDFP21BP = Matrix1[0]>>4;
        LCDFP22BP = Matrix1[0]; 
    }
    //L
    LCDFP18BP |= 0x08;
    LCDFP20BP |= 0x08;
    LCDFP22BP |= 0x08;
    //E
    LCDFP5BP |= 0x0f;
    LCDFP6BP |= 0x01;
    //D
    LCDFP7BP |= 0x0d;
    LCDFP8BP |= 0x07;
    //-
    //LCDFP9BP |= 0x02;
    //Z    
    LCDFP15BP |= Matrix1[2]>>4;
    LCDFP16BP |= Matrix1[2];
    //H
    LCDFP17BP |= 0x07;
    LCDFP18BP |= 0x0e;
                   
    LCDRAM2_FP4BP = LCDFP4BP;
    LCDRAM2_FP5BP = LCDFP5BP;
    LCDRAM3_FP6BP = LCDFP6BP;
    LCDRAM3_FP7BP = LCDFP7BP;
    LCDRAM4_FP8BP = LCDFP8BP;   
    LCDRAM4_FP9BP = LCDFP9BP;            
    LCDRAM5_FP10BP = LCDFP10BP;
    LCDRAM5_FP11BP = LCDFP11BP;
    LCDRAM6_FP12BP = LCDFP12BP;
    LCDRAM6_FP13BP = LCDFP13BP;
    LCDRAM7_FP14BP = LCDFP14BP;
    LCDRAM7_FP15BP = LCDFP15BP;
    LCDRAM8_FP16BP = LCDFP16BP;
    LCDRAM8_FP17BP = LCDFP17BP;
    LCDRAM9_FP18BP = LCDFP18BP;
    LCDRAM9_FP19BP = LCDFP19BP;
    LCDRAM10_FP20BP = LCDFP20BP;
    LCDRAM10_FP21BP = LCDFP21BP;
    LCDRAM11_FP22BP = LCDFP22BP;
}