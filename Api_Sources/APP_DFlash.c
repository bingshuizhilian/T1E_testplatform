#define  GLOBALS_APP_DFLASH
#include "../App_Headers/includes.h"


//-----------------------------------------------------------------------------
// ��������   :    App_CopyRam(INT8U *Dp,INT8U *Sp,INT8U Nub)
// ��������   :    RAM ����
// ����       :    *Dp       -> Ŀ�ĵ�ַ
//                 *Sp       -> ԭ��ַ
//                 Nub       -> �����ֽ�����
// ���       :    ��
// ����ֵ     :    ��
// ����       :    ��
//-----------------------------------------------------------------------------
void App_CopyRam(INT8U *Dp,INT8U *Sp,INT8U Nub)
{
    INT8U b;
    
    for(b = 0;b < Nub;b++)
    {
         *Dp++ = *Sp++;           
    }
}