#define  GLOBALS_APP_DFLASH
#include "../App_Headers/includes.h"


//-----------------------------------------------------------------------------
// 函数名称   :    App_CopyRam(INT8U *Dp,INT8U *Sp,INT8U Nub)
// 函数功能   :    RAM 复制
// 输入       :    *Dp       -> 目的地址
//                 *Sp       -> 原地址
//                 Nub       -> 复制字节数量
// 输出       :    无
// 返回值     :    无
// 其他       :    无
//-----------------------------------------------------------------------------
void App_CopyRam(INT8U *Dp,INT8U *Sp,INT8U Nub)
{
    INT8U b;
    
    for(b = 0;b < Nub;b++)
    {
         *Dp++ = *Sp++;           
    }
}