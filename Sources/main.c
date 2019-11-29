#define GLOBALS_VARIABLE

#include "../App_Headers/includes.h"
#include "main.h"
#define CAN_NUM  23

_SendCanMsg CanMsg[CAN_NUM];

//当前的显示的灯
INT8U Cur_Led = 0;

//转速
int EngineSpeed = 0, jj = 0;
INT8U EngineSpeed_Dir = 0;
INT8U EngineSpeed_En = 0;

//车速
int VehicleSpeed = 0;
INT8U VehicleSpeed_Dir = 0;
INT8U VehicleSpeed_En = 0;

//水温
INT8U EngineCoolantTemperture = 0;
INT8U EngineCoolantTemperture_Dir = 0;

//闪烁
volatile uint8_t flash_1s;
void main(void)
{
    flash_1s = 0;
    RunStep = 0;
    MaxStep = 81 + 34 + 2;//switch 总数
    API_Sys_Init();
    HardWireCheckInit();
    API_Set10msTimer(10, (ClockType*)&Clock);
    API_Set30msTimer(20, (ClockType*)&Clock);
    API_Set100msTimer(100, (ClockType*)&Clock);
    API_Set500msTimer(500, (ClockType*)&Clock);
    API_Set1000msTimer(1000, (ClockType*)&Clock);

    Init_CanMsg();



    for(;;)
    {
        Api_LCD_Display();

//        SN = 1;
//        ASM_ABS_ESP = 0x28;
//        TTCEPI = 0x38;
//        TPMS = 0x01;
//        RAEBT = 0x32;
//        FFPEM = 0x0C;

//        L_OSWF = 0x10;
//        SIMTMA = 0x08;
//        NAVIGATION_INFO = 0x10;
//        SN = 1;

        //CAN CONFIG INIT
        CANMsg5e1.Msg[0] = 0x28;
        CANMsg5e1.Msg[1] = 0x3C;
        CANMsg5e1.Msg[2] = 0x01;
        CANMsg5e1.Msg[3] = 0x92;
        CANMsg5e1.Msg[4] = 0x0F;

        CANMsg5ea.Msg[2] = 0x10;
        CANMsg5ea.Msg[5] = 0x08;
        CANMsg5ea.Msg[7] = 0x10;

        CANMsg5f0.Msg[0] = 0x01;
        CANMsg5f0.Msg[1] = 0x01;
        switch(RunStep)
        {
            case 0:
            {
                Cur_Led = 0;
                EngineCoolantTemperture = 0;
                EngineSpeed = 0;
                VehicleSpeed = 0;
                Clear_CanMsg();
            }
            break;
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            {
                //水温3/8
                if(RunStep == 11)
                    EngineCoolantTemperture  =  154;

                if(RunStep <= 11)
                {
                    //转速调节
                    EngineSpeed = 2000 / 8 * RunStep;
                    if(EngineSpeed > 2000)
                        EngineSpeed = 2000;

                    //车速调节
                    VehicleSpeed = 3520 / 11 * RunStep;
                    if(VehicleSpeed > 3520)
                        VehicleSpeed = 3520;
                }
            }
            break;
            case 12:
            {
                //右转
                BCM_RHTurnlightSts = 1;
            }
            break;
            case 13:
            {
                BCM_RHTurnlightSts = 0;
                //远光
                BCM_HighBeamSts = 1;
            }
            break;
            case 14:
            {
                BCM_HighBeamSts = 0;
                //小灯
                BCM_ParkLightSts = 1;
            }
            break;
            case 15:
            {
                BCM_ParkLightSts = 0;
                //电子转向柱锁严重故障灯亮（红色) 请立即停车并检查电子转向柱锁，扬声器长响.
                ESCLCriticalFailure = 1;
            }
            break;
            case 16:
            {
                ESCLCriticalFailure = 0;
                //电子转向柱锁故障灯亮（黄色） 请立即停车并检查电子转向柱锁，扬声器长响
                ESCLFunctionFailure = 1;
            }
            break;
            case 17:
            {
                ESCLFunctionFailure = 0;
                //电子转向柱锁卡住灯（白色），仪表显示电子转向柱卡住请转动方向盘再启动
                ESCLUnlockJamming = 1;
            }
            break;
            case 18:
            {
                ESCLUnlockJamming = 0;
                //后雾灯亮（黄色）
                BCM_RearFogLightSts = 1;
            }
            break;
            case 19:
            {
                BCM_RearFogLightSts = 0;
                //EPS故障指示亮（黄色）。仪表显示请检查助力转向系统
                BCM_EPSFailSts = 1;
            }
            break;
            case 20:
                BCM_EPSFailSts = 0; //空一步
                break;
            case 21:
            {
                //安全气囊故障灯亮（红色），仪表显示请检查气囊系统
                BCM_AirBagFailSts = 1;
            }
            break;
            case 22:
            {
                BCM_AirBagFailSts = 0;
                //左转向亮（绿色）
                BCM_LHTurnlightSts = 1;

            }
            break;
            case 23:
            {
                BCM_LHTurnlightSts = 0;
                // 陡坡缓降灯亮(绿色) 仪表显示陡坡缓降功能开启
                BCM_HDCCtrlSts = 1;
            }
            break;
            case 24:
            {
                BCM_HDCCtrlSts = 0;
                //仪表显示陡坡缓降失效
                BCM_HDCFailSts = 1;
            }
            break;
            case 25:
            {
                BCM_HDCFailSts = 0;
                //AUTOHOLD亮（绿色），仪表显示ESP动态制动功能失效，后显示自动驻车功能开启
                BCM_CDPFailSts = 1;
                BCM_AVHSts = 2;
            }
            break;
            case 26:
            {
                BCM_CDPFailSts = 0;
                BCM_AVHSts = 0;
                //巡航亮 (绿色)
                BCM_CruiseControlStsForDisplay = 1;
            }
            break;
            case 27:
            {
                BCM_CruiseControlStsForDisplay = 0;
                //巡航限速亮（白色）//***********421********************************************
                LimitSpeedSts = 1;
            }
            break;
            case 28:
            {
                //BCM_RHTurnlightSts = 0;
                //手制动未松灯亮（红色）
                BCM_EBDFailSts = 1;
            }
            break;
            case 29:
            {
                BCM_EBDFailSts = 0;
                //红P闪烁
                BCM_Redwarning = 1;
            }
            break;
            case 30:
            {
                BCM_Redwarning = 0;
                //黄P闪烁
                BCM_Yellowwarning = 1;
            }
            break;
            case 31:
            {
                //ESP亮（黄色）黄P亮（不闪烁）。仪表显示请检查ESP系统
                BCM_Yellowwarning = 2;
                BCM_VDCFailSts = 1;
            }
            break;
            case 32:
            {
                BCM_Yellowwarning = 0;
                BCM_VDCFailSts = 0;
                //ESPOFF亮（黄色）红P亮（不闪烁）
                BCM_ESPSwitchStatus = 1;
                BCM_Redwarning = 2;
            }
            break;
            case 33:
            {
                BCM_ESPSwitchStatus = 0;
                BCM_Redwarning = 0;
                //ABS指示灯亮（黄色）仪表显示请检查ABS系统
                BCM_ABSFailSts = 1;
            }
            break;
            case 34:
            {
                BCM_ABSFailSts = 0;
                //EPC灯亮（黄色）
                BCM_EPCSts = 1;

            }
            break;
            case 35:
            {
                BCM_EPCSts = 0;
                //发动机故障亮（黄色）。
                BCM_MILSts = 2;

            }
            break;
            case 36:
            {
                BCM_MILSts = 0;
                //蓄电池电量低亮（红色）
                BCM_IEMSts = 1;
            }
            break;
            case  37:
            {
                BCM_IEMSts = 0;
                //安全带灯亮（红色） 请系好安全带，副驾安全带未系，请注意安全
                PsngrSeatBeltWarning = 2;
            }
            break;
            case  38:
            {
                PsngrSeatBeltWarning = 0;
                //胎压灯亮（黄色闪烁）。仪表显示请检测胎压故障系统
                BCM_Tire_PressureSystemFailSts = 1;//
            }
            break;

            case  39:
            {
                BCM_Tire_PressureWarningLampSts = 0;
//                SN = 1;
//                ASM_ABS_ESP = 0x28;
//                TTCEPI =  0x3A;
//                FFPEM = 0x04;
//                TPMS = 0x01;
//                RAEBT = 0x32;
//                L_OSWF = 0x10;
//                SIMTMA = 0x08;
//                NAVIGATION_INFO = 0x10;
//                SN = 1;
                //变速箱故障灯亮（黄色）。仪表显示请检查变速箱控制系统
                BCM_AGErrorLamp = 1;//CanMessageID301.Msg[1] = 0x01;
            }
            break;
            case  40:
            {
                BCM_AGErrorLamp = 0;
                //小车左前门开。扬声器长响
                BCM_DriverDoorSts = 1;
            }
            break;
            case  41:
            {
                BCM_DriverDoorSts = 0;
                //小车右前门开，扬声器长响。
                BCM_PsngrDoorSts = 1;
            }
            break;
            case  42:
            {
                BCM_PsngrDoorSts = 0;
                //小车发动机盖开，扬声器长响。
                BCM_HoodSts = 1;
            }
            break;
            case  43:
            {
                BCM_HoodSts = 0;
                //小车右后门开，扬声器长响
                BCM_RHRDoorSts = 1;
            }
            break;
            case  44:
            {
                BCM_RHRDoorSts = 0;
                //小车左后门开，后备箱门开，扬声器长响
                BCM_LHRdoorSts = 1;
            }
            break;
            case  45:
            {
                BCM_LHRdoorSts = 0;
                //小车后备箱门开，扬声器长响。
                BCM_TrunkSts = 1;
            }
            break;
            case  46:
            {
//                SN = 1;
//                ASM_ABS_ESP = 0x28;
//                TTCEPI =  0x3A;
//                FFPEM = 0x04;
//                TPMS = 0x01;
//                RAEBT = 0x32;
//                L_OSWF = 0x10;
//                SIMTMA = 0x08;
//                NAVIGATION_INFO = 0x10;
//                SN = 1;
                BCM_TrunkSts = 0;
                //倒车雷达全亮，档位R档。扬声器长响// *************440*****************
                BCM_GBPositoionDisplay = 2;
                RadarWorkSts = 1;
                RadarDetectSts = 4;

            }
            break;
            case  47:
            {
                RadarWorkSts = 0;
                //BCM_EPBWarningMessage = 0;
                //灯全显。扬声器长响
                Led_all();
                CanMessageID307.Msg[0] = 0x02;
                CanMessageID305.Msg[0] = 0x01;
                CanMessageID305.Msg[4] = 0x04;
                CANMsg320.Msg[1] = 0x01;

                //水温1格。
                EngineCoolantTemperture = 131;
            }
            break;
            case  48:
            {
                //BCM_EPBWarningMessage = 0;
                //水温3格。
                EngineCoolantTemperture = 154;
            }
            break;
            case 49:
                //水温5格。
                EngineCoolantTemperture = 181;
                break;
            case 50:
                //水温8格 发动机水温高，请联系4S点检查，扬声器长响，水温报警灯红色闪烁，水温格变红，仪表显示请检查冷却液位
                EngineCoolantTemperture = 231;
                break;
            case 51:
//                SN = 1;
//                ASM_ABS_ESP = 0x28;
//                TTCEPI =  0x3A;
//                FFPEM = 0x04;
//                TPMS = 0x01;
//                RAEBT = 0x32;
//                L_OSWF = 0x10;
//                SIMTMA = 0x08;
//                NAVIGATION_INFO = 0x10;
//                SN = 1;
                EngineCoolantTemperture = 181;
                //档位1
                BCM_GBPositoionDisplay = 5;
                break;
            case 52:
                //档位2
//                SN = 1;
//                ASM_ABS_ESP = 0x28;
//                TTCEPI =  0x3A;
//                FFPEM = 0x04;
//                TPMS = 0x01;
//                RAEBT = 0x32;
//                L_OSWF = 0x10;
//                SIMTMA = 0x08;
//                NAVIGATION_INFO = 0x10;
//                SN = 1;
                BCM_GBPositoionDisplay = 6;
                break;
            case 53:
//                SN = 1;
//                ASM_ABS_ESP = 0x28;
//                TTCEPI =  0x3A;
//                FFPEM = 0x04;
//                TPMS = 0x01;
//                RAEBT = 0x32;
//                L_OSWF = 0x10;
//                SIMTMA = 0x08;
//                NAVIGATION_INFO = 0x10;
//                SN = 1;
                //档位3
                BCM_GBPositoionDisplay = 7;
                break;
            case 54:
//                SN = 1;
//                ASM_ABS_ESP = 0x28;
//                TTCEPI =  0x3A;
//                FFPEM = 0x04;
//                TPMS = 0x01;
//                RAEBT = 0x32;
//                L_OSWF = 0x10;
//                SIMTMA = 0x08;
//                NAVIGATION_INFO = 0x10;
//                SN = 1;
                //档位4
                BCM_GBPositoionDisplay = 8;
                break;
            case 55:
//                SN = 1;
//                ASM_ABS_ESP = 0x28;
//                TTCEPI =  0x3A;
//                FFPEM = 0x04;
//                TPMS = 0x01;
//                RAEBT = 0x32;
//                L_OSWF = 0x10;
//                SIMTMA = 0x08;
//                NAVIGATION_INFO = 0x10;
//                SN = 1;
                //档位5
                BCM_GBPositoionDisplay = 9;
                break;
            case 56:
                //档位6
//                SN = 1;
//                ASM_ABS_ESP = 0x28;
//                TTCEPI =  0x3A;
//                FFPEM = 0x04;
//                TPMS = 0x01;
//                RAEBT = 0x32;
//                L_OSWF = 0x10;
//                SIMTMA = 0x08;
//                NAVIGATION_INFO = 0x10;
//                SN = 1;
                BCM_GBPositoionDisplay = 10;
                break;
            case 57:
//                SN = 1;
//                ASM_ABS_ESP = 0x28;
//                TTCEPI =  0x3A;
//                FFPEM = 0x04;
//                TPMS = 0x01;
//                RAEBT = 0x32;
//                L_OSWF = 0x10;
//                SIMTMA = 0x08;
//                NAVIGATION_INFO = 0x10;
//                SN = 1;
                //档位7
                BCM_GBPositoionDisplay = 11;
                break;
            case 58:
                BCM_GBPositoionDisplay = 0;
                //空一步
                BCM_Tire_PressureWarningLampSts = 2;
                break;
            case  59:
            {
                //BCM_EPBWarningMessage = 0;
                //仪表显示请挂入P/N档启动  扬声器响6声
                SmtSysWarning_32 = 1;
            }
            break;
            case  60:
            {
                SmtSysWarning_32 = 0;
                //仪表显示请挂入P档  扬声器响6声
                SmtSysWarning_43 = 1;
            }
            break;
            case  61:
            {
                SmtSysWarning_43 = 0;
                //仪表显示请注意车内有智能钥匙  扬声器响6声
                SmtSysWarning_13 = 1;
            }
            break;
            case  62:
            {
                SmtSysWarning_13 = 0;
                //仪表显示智能钥匙电量低，语音提示智能钥匙电量低请及时更换电池  扬声器响6声
                SmtSysWarning_31 = 1;
            }
            break;
            case  63:
            {
                SmtSysWarning_31 = 0;
                //仪表显示请关闭电源   扬声器响6声           ************3e6*BCM_PEPS_G*SmartSystemWarning_1.0************
                SmtSysWarning_10 = 1;
            }
            break;
            case  64:
            {
                SmtSysWarning_10 = 0;
                UnLed_all();
                //仪表显示释放驻车时请踩下制动踏板   扬声器响6声
                BCM_EPBWarningMessage = 1;
            }
            break;
            case  65:
            {
                //BCM_EPBWarningMessage = 0;
                //仪表显示请关闭车门并系好安全带
                BCM_EPBWarningMessage = 2;
            }
            break;
            case  66:
            {
                //BCM_EPBWarningMessage = 0;
                //仪表显示驻车坡度过大请注意安全  扬声器响6声
                BCM_EPBWarningMessage = 3;
            }
            break;
            case  67:
            {
                BCM_EPBWarningMessage = 0;
                //仪表显示未检测到智能钥匙  扬声器响6声
                SmtSysWarning_22 = 1;               //************************************************************
            }
            break;
            case  68:
            {
                //BCM_EPBWarningMessage = 0;                      //************************************************************
                //胎压故障灯亮，左前轮胎红色
                BCM_LFTyre_TirePositionWarning = 2;
            }
            break;
            case  69:
            {
                BCM_LFTyre_TirePositionWarning = 0;
                //胎压故障灯亮，右前轮胎红色
                BCM_RFTyre_TirePositionWarning = 2;                  //************************************************************
            }
            break;
            case  70:
            {
                BCM_RFTyre_TirePositionWarning = 0;                  //************************************************************
                //胎压故障灯亮，左后轮胎红色
                BCM_LRTyre_TirePositionWarning = 2;
            }
            break;
            case  71:
            {
                BCM_LRTyre_TirePositionWarning = 0;
                //胎压故障灯亮，右后轮胎红色
                BCM_RRTyre_TirePositionWarning = 2;
            }
            break;
            case  72:
            {
                BCM_RRTyre_TirePositionWarning = 0;
                //RadarDetectSts = 2;
                RadarWorkSts = 1;
                //倒车雷达左一格亮，并伴随扬声器长响报警   ****440 ****
                LHMRRadarSensorDistance = 30;
                RHRRadarSensorDistance = 30;
                LHRRadarSensorDistance = 25;
                AudibleBeepRate = 4;
            }
            break;
            case  73:
            {
                //BCM_EPBWarningMessage = 0;
                RadarWorkSts = 1;
                //倒车雷达左二格亮，并伴随扬声器长响报警
                LHRRadarSensorDistance = 10;
                LHMRRadarSensorDistance = 30;
                RHRRadarSensorDistance = 30;
                AudibleBeepRate = 4;
            }
            break;
            case  74:
            {
                //BCM_EPBWarningMessage = 0;
                RadarWorkSts = 1;
                //倒车雷达左三格亮，并伴随扬声器长响报警
                LHRRadarSensorDistance = 5;
                LHMRRadarSensorDistance = 30;
                RHRRadarSensorDistance = 30;
                AudibleBeepRate = 4;
            }
            break;
            case  75:
            {
                LHRRadarSensorDistance = 0;
                RadarWorkSts = 1;
                //倒车雷达中一格亮，并伴随扬声器长响报警
                LHMRRadarSensorDistance = 25;
                RHRRadarSensorDistance = 30;
                LHRRadarSensorDistance = 30;
                AudibleBeepRate = 4;
            }
            break;
            case  76:
            {
                //BCM_EPBWarningMessage = 0;
                RadarWorkSts = 1;
                //倒车雷达中二格亮，并伴随扬声器长响报警
                LHMRRadarSensorDistance = 10;
                RHRRadarSensorDistance = 30;
                LHRRadarSensorDistance = 30;
                AudibleBeepRate = 4;
            }
            break;
            case  77:
            {
                //BCM_EPBWarningMessage = 0;
                RadarWorkSts = 1;
                //倒车雷达中三格亮，并伴随扬声器长响报警
                LHMRRadarSensorDistance = 5;
                RHRRadarSensorDistance = 30;
                LHRRadarSensorDistance = 30;
                AudibleBeepRate = 4;
            }
            break;
            case  78:
            {
                LHMRRadarSensorDistance = 0;
                RadarWorkSts = 1;
                //倒车雷达右一格亮，并伴随扬声器长响报警
                RHRRadarSensorDistance = 25;
                LHMRRadarSensorDistance = 30;
                LHRRadarSensorDistance = 30;
                AudibleBeepRate = 4;
            }
            break;
            case  79:
            {
                //BCM_EPBWarningMessage = 0;
                RadarWorkSts = 1;
                //倒车雷达右二格亮，并伴随扬声器长响报警
                RHRRadarSensorDistance = 10;
                LHMRRadarSensorDistance = 30;
                LHRRadarSensorDistance = 30;
                AudibleBeepRate = 4;
            }
            break;
            case  80:
            {
                //BCM_EPBWarningMessage = 0;
                RadarWorkSts = 1;
                //倒车雷达右三格亮，并伴随扬声器长响报警
                RHRRadarSensorDistance = 5;
                LHMRRadarSensorDistance = 30;
                LHRRadarSensorDistance = 30;
                AudibleBeepRate = 4;
            }
            break;
            case  81:
            {
//                SN = 1;
//                ASM_ABS_ESP = 0x28;
//                TTCEPI =  0x3A;
//                FFPEM = 0x04;
//                TPMS = 0x01;
//                RAEBT = 0x32;
//                L_OSWF = 0x10;
//                SIMTMA = 0x08;
//                NAVIGATION_INFO = 0x10;
//                SN = 1;
                RHRRadarSensorDistance = 0;
                AudibleBeepRate = 0;
                RadarWorkSts = 0;
                //仪表显示变速箱过热请停靠的安全处约2分钟
                BCM_AGErrorLamp = 1;
                ClutchTemperature = 2;
            }
            break;
            case 81 + 1:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID305.Msg[2] = 1 << 3;

            }
            break;
            case 81 + 2:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID305.Msg[2] = 2 << 3;

            }
            break;

            case 81 + 3:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID305.Msg[2] = 3 << 3;

            }
            break;
            case 81 + 4:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID305.Msg[2] = 4 << 3;

            }
            break;
            case 81 + 5:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID305.Msg[2] = 5 << 3;

            }
            break;
            case 81 + 6:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID305.Msg[2] = 6 << 3;

            }
            break;
            case 81 + 7:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID305.Msg[2] = 7 << 3;

            }
            break;
            case 81 + 8:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID305.Msg[2] = 8 << 3;

            }
            break;
            case 81 + 9:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID305.Msg[2] = 9 << 3;

            }
            break;
            case 81 + 10:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID305.Msg[2] = 10 << 3;

            }
            break;
            case 81 + 11:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID305.Msg[2] = 11 << 3;
            }
            break;
            case 81 + 12:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID305.Msg[2] = 12 << 3;

            }
            break;
            case 81 + 13:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID305.Msg[2] = 13 << 3;

            }
            break;
            case 81 + 14:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID305.Msg[2] = 14 << 3;
                ;
            }
            break;
            case 81 + 15:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID305.Msg[2] = 15 << 3;

            }
            break;
            case 81 + 16:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID305.Msg[2] = 16 << 3;

            }
            break;
            case 81 + 17:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID305.Msg[2] = 17 << 3;

            }
            break;
            case 81 + 18:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID305.Msg[2] = 18 << 3;

            }
            break;
            case 81 + 19:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID305.Msg[2] = 19 << 3;

            }
            break;
            case 81 + 20:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID305.Msg[2] = 20 << 3;

            }
            break;
            case 81 + 21:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID305.Msg[2] = 21 << 3;

            }
            break;
            case 81 + 22:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID305.Msg[2] = 22 << 3;

            }
            break;
            case 81 + 23:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID436.Msg[0] = 100;

            }
            break;
            case 81 + 24:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CANMsg392.Msg[5] = 3 << 2;

            }
            break;
            case 81 + 25:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID508.Msg[0] = 1 << 3;

            }
            break;
            case 81 + 26:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID508.Msg[0] = 1 << 4;

            }
            break;
            case 81 + 27:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID508.Msg[0] = 1 << 5;

            }
            break;
            case 81 + 28:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID508.Msg[0] = 1 << 6;

            }
            break;
            case 81 + 29:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID508.Msg[0] = 1 << 7;

            }
            break;
            case 81 + 30:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID47A.Msg[0] = 1 << 3;

            }
            break;
            case 81 + 31:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID47A.Msg[0] = 4 << 3;

            }
            break;
            case 81 + 32:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID307.Msg[4] = 1 << 6;
            }
            break;
            case 81 + 33:
            {

                //电子转向柱锁卡住 请转动方向盘再启动//ESCLUnlockJamming 来自ESCL_2
                CanMessageID307.Msg[4] = 2 << 6;

            }
            break;
            case 81 + 34:
            {
                CanMessageID517.Msg[0] = 0x0C;
                CanMessageID517.Msg[1] = 0x22;

                BCM_WiperSensitivitySWSts = 1;
            }
            break;
            case 81 + 35:
            {
                BCM_WiperSensitivitySWSts = 4;
            }
            break;
            case 81 + 36:
            {
                BCM_AGErrorLamp = 0;
                ClutchTemperature = 0;
                //车速220 转速8000  此时按住OK键5S  断长火在给长火仪表大计清零
                EngineSpeed = 2000;
                VehicleSpeed = 3520;
            }
            break;
            case 81 + 37:
            {
                BCM_AGErrorLamp = 0;
                ClutchTemperature = 0;
                //车速220 转速8000  此时按住OK键5S  断长火在给长火仪表大计清零
                EngineSpeed = 2000;
                VehicleSpeed = 3520;
            }
            break;
            case 81 + 38:
            {
                break;
            }

            default:
                break;
        }


        Run();


        if(API_10msTimerOver((ClockType*)&Clock))
        {
            //Switch_timer(10);
            API_Set10msTimer(10, (ClockType*)&Clock);
            Gui_ButoonProc();
        }

        if(API_100msTimerOver((ClockType*)&Clock))
        {
            Switch_timer(100);
            API_Set100msTimer(100, (ClockType*)&Clock);
        }

        if(API_30msTimerOver((ClockType*)&Clock))
        {
            Switch_timer(20);
            API_Set30msTimer(20, (ClockType*)&Clock);
        }

        if(API_500msTimerOver((ClockType*)&Clock))
        {
            flash_1s = flash_1s ? 0 : 1;
            if(pMouseEn)
            {
                pMouseLed = flash_1s;
            }

            Switch_timer(500);
            API_Set500msTimer(500, (ClockType*)&Clock);
        }

        //1S
        if(API_1000msTimerOver((ClockType*)&Clock))
        {
            //Switch_timer(1000);
            API_Set1000msTimer(1000, (ClockType*)&Clock);
        }
        //Clear_CanMsg();
        __RESET_WATCHDOG();

    }
}

//总循环函数
static void Run()
{
    EngineSpeed_Run();
    VehicleSpeed_Run();
    WaterTemp_Run();
    LED_Run();
}


static void EngineSpeed_Run()
{
    BCM_EngineSpeed_h = (EngineSpeed & 0x7F8) >> 3;
    BCM_EngineSpeed_l = (EngineSpeed & 0x007);
}

static void VehicleSpeed_Run()
{
    BCM_VehicleSpeedVSOSig_H = (VehicleSpeed & 0x1F00) >> 8;
    BCM_VehicleSpeedVSOSig_L = (VehicleSpeed & 0xFF);
}

static void WaterTemp_Run()
{
    BCM_EngineCoolantTemperture = EngineCoolantTemperture;
}

static void LED_Run()
{
    INT8U Next_Led;
    if(Cur_Led == 0)
        return;

    //关闭前一个
    if(Cur_Led > 1)
    {
        (runStruct[Cur_Led - 1].ptr)(0);
    }
    //显示当前的
    (runStruct[Cur_Led].ptr)(1);

    //关闭后一个
    if(Cur_Led < MAX_LED - 1)
    {
        (runStruct[Cur_Led + 1].ptr)(0);
    }
}
//亮所有的灯
static void  Led_all(void)
{
    INT8U i;
    for(i = 1; i <= LED_COUNT; i++)
    {
        (runStruct[i].ptr)(1);
    }
}

//灭所有的灯
static void  UnLed_all(void)
{
    INT8U i;
    for(i = 1; i <= LED_COUNT; i++)
    {
        (runStruct[i].ptr)(0);
    }
}
static void Left_Pannel(void)
{
    BCM_ABSFailSts = 1;
    BCM_ESPSwitchStatus = 1;
    BCM_TCSFailSts = 1;
    BCM_EBDFailSts = 1;
    BCM_EPSFailSts = 1;
    BCM_IEMSts = 1;
    BCM_DRLSts = 1;

}

static void Right_Pannel(void)
{

}

static void Top_Pannel(void)
{

}

//初始化报文数据
static void Init_CanMsg()
{
    CanMsg[0].id  = BCM_EMS_1_G;
    CanMsg[0].msg = CANMsg280.Msg;
    CanMsg[0].dlc = 8;
    CanMsg[0].timer = 100;

    CanMsg[1].id  = BCM_ABS_ESP_G;
    CanMsg[1].msg = CANMsg2c0.Msg;
    CanMsg[1].dlc = 7;
    CanMsg[1].timer = 100;

    CanMsg[2].id  = BCM_4;
    CanMsg[2].msg = CANMsg392.Msg;
    CanMsg[2].dlc = 8;
    CanMsg[2].timer = 20;

    CanMsg[3].id  = BCM_ABM_G;
    CanMsg[3].msg = CANMsg320.Msg;
    CanMsg[3].dlc = 8;
    CanMsg[3].timer = 500;

    CanMsg[4].id  = BCM_5;
    CanMsg[4].msg = CANMsg51b.Msg;
    CanMsg[4].dlc = 8;
    CanMsg[4].timer = 500;

    CanMsg[5].id  = BCM_TCU_G;
    CanMsg[5].msg = CANMsg301.Msg;
    CanMsg[5].dlc = 2;
    CanMsg[5].timer = 100;

    CanMsg[6].id  = BCM_EPS_G;
    CanMsg[6].msg = CANMsg380.Msg;
    CanMsg[6].dlc = 3;
    CanMsg[6].timer = 100;

    CanMsg[7].id  = BCM_EPB_G;
    CanMsg[7].msg = CANMsg4f6.Msg;
    CanMsg[7].dlc = 2;
    CanMsg[7].timer = 100;

    CanMsg[8].id  = RADAR_1;
    CanMsg[8].msg = CANMsg440.Msg;
    CanMsg[8].dlc = 8;
    CanMsg[8].timer = 100;

    CanMsg[9].id  = BCM_10;
    CanMsg[9].msg = CANMsg5f0.Msg;
    CanMsg[9].dlc = 8;
    CanMsg[9].timer = 100;

    CanMsg[10].id  = BCM_6;
    CanMsg[10].msg = CANMsg5e1.Msg;
    CanMsg[10].dlc = 8;
    CanMsg[10].timer = 100;

    CanMsg[11].id  = BCM_7;
    CanMsg[11].msg = CANMsg5ea.Msg;
    CanMsg[11].dlc = 8;
    CanMsg[11].timer = 100;

    CanMsg[12].id  = ESCL_2;
    CanMsg[12].msg = CANMsg401.Msg;
    CanMsg[12].dlc = 8;
    CanMsg[12].timer = 100;

    CanMsg[13].id  = BCM_PEPS_G;
    CanMsg[13].msg = CANMsg3e6.Msg;
    CanMsg[13].dlc = 8;
    CanMsg[13].timer = 100;

    CanMsg[14].id  = BCM_EMS_2_G;
    CanMsg[14].msg = CANMsg421.Msg;
    CanMsg[14].dlc = 8;
    CanMsg[14].timer = 100;

    CanMsg[15].id  = 0x51A;
    CanMsg[15].msg = CanMessageID51A.Msg;
    CanMsg[15].dlc = 8;
    CanMsg[15].timer = 100;

    CanMsg[16].id  = 0x47A;
    CanMsg[16].msg = CanMessageID47A.Msg;
    CanMsg[16].dlc = 8;
    CanMsg[16].timer = 100;

    CanMsg[17].id  = 0x436;
    CanMsg[17].msg = CanMessageID436.Msg;
    CanMsg[17].dlc = 8;
    CanMsg[17].timer = 100;

    CanMsg[18].id  = 0x307;
    CanMsg[18].msg = CanMessageID307.Msg;
    CanMsg[18].dlc = 8;
    CanMsg[18].timer = 100;

    CanMsg[19].id  = 0x305;
    CanMsg[19].msg = CanMessageID305.Msg;
    CanMsg[19].dlc = 8;
    CanMsg[19].timer = 100;

    CanMsg[20].id  = 0x5A3;
    CanMsg[20].msg = CanMessageID5A3.Msg;
    CanMsg[20].dlc = 8;
    CanMsg[20].timer = 100;

    CanMsg[21].id  = 0x508;
    CanMsg[21].msg = CanMessageID508.Msg;
    CanMsg[21].dlc = 8;
    CanMsg[21].timer = 100;

    CanMsg[22].id  = 0x517;
    CanMsg[22].msg = CanMessageID517.Msg;
    CanMsg[22].dlc = 8;
    CanMsg[22].timer = 100;
}


static void Switch_timer(INT16U timerId)
{
    INT8U i, j;

    for(i = 0; i < CAN_NUM; i++)
    {
        if(CanMsg[i].timer == timerId)
        {
            j = 0;
            API_CANSendFrame(CanMsg[i].id, 0, CanMsg[i].dlc, CanMsg[i].msg);

            if((CanMsg[i].id != 0x5E1) && (CanMsg[i].id != 0x5EA) && (CanMsg[i].id != 0x5F0) && (CanMsg[i].id != 0x517))
            {
                APP_Clear_Data(CanMsg[i].msg);
            }

            while(j < 10)
            {
                j++;
            }
        }
    }
}


static void Clear_CanMsg()
{
    INT8U i;
    INT8U j = BCM_WiperSensitivitySWSts;
    
    for(i = 0; i < CAN_NUM; i++)
    {
        APP_Clear_Data(CanMsg[i].msg);

        if(CanMsg[i].id == 0x392)
            BCM_WiperSensitivitySWSts = j;
    }
}

/******************************************************跑表程序处理部分********************************************************/

static void Led_Left(INT8U state)
{
    if(state)
    {
        BCM_LHTurnlightSts = 1;
    }
    else
    {
        BCM_LHTurnlightSts = 0;
    }
}

static void Led_Right(INT8U state)
{
    if(state)
    {
        BCM_RHTurnlightSts = 1;
    }
    else
    {
        BCM_RHTurnlightSts = 0;
    }
}

static void Led_1(INT8U state)
{
    if(state)
        BCM_ABSFailSts = 1;
    else
        BCM_ABSFailSts = 0;
}

static void Led_2(INT8U state)
{
    if(state)
        BCM_ESPSwitchStatus = 1;
    else
        BCM_ESPSwitchStatus = 0;
}

static void Led_3(INT8U state)
{
    if(state)
        BCM_VDCFailSts = 1;
    else
        BCM_VDCFailSts = 0;
}

static void Led_4(INT8U state)
{
    if(state)
        BCM_TCSFailSts = 1;
    else
        BCM_TCSFailSts = 0;
}

static void Led_5(INT8U state)
{
    if(state)
        BCM_EBDFailSts = 1;
    else
        BCM_EBDFailSts = 0;
}

static void Led_6(INT8U state)
{
    if(state)
        BCM_EPSFailSts = 1;
    else
        BCM_EPSFailSts = 0;
}

//top
static void Led_11(INT8U state)
{
    if(state)
        BCM_ParkLightSts = 1;
    else
        BCM_ParkLightSts = 0;
}

static void Led_12(INT8U state)
{
    if(state)
        BCM_HighBeamSts = 1;
    else
        BCM_HighBeamSts = 0;
}

static void Led_13(INT8U state)
{
    if(state)
        BCM_RearFogLightSts = 1;
    else
        BCM_RearFogLightSts = 0;
}

//right
static void Led_14(INT8U state)
{
    if(state)
        BCM_EPCSts = 1;
    else
        BCM_EPCSts = 0;
}

static void Led_15(INT8U state)
{
    if(state)
        BCM_MILSts = 2;
    else
        BCM_MILSts = 0;
}

static void Led_16(INT8U state)
{
    if(state)
        BCM_Redwarning = 2;
    else
        BCM_Redwarning = 0;
}

static void Led_17(INT8U state)
{
    if(state)
        BCM_Yellowwarning = 2;
    else
        BCM_Yellowwarning = 0;
}

static void Led_18(INT8U state)
{
    if(state)
        BCM_AVHSts = 2;
    else
        BCM_AVHSts = 0;
}

static void Led_19(INT8U state)
{
    if(state)
        BCM_IEMSts = 1;
    else
        BCM_IEMSts = 0;
}

static void Led_20(INT8U state)
{
    if(state)
        BCM_HDCCtrlSts = 1;
    else
        BCM_HDCCtrlSts = 0;
}

static void Led_21(INT8U state)
{
    if(state)
        BCM_AirBagFailSts = 3;
    else
        BCM_AirBagFailSts = 0;
}

static void Warning_1(INT8U state)
{
    if(state)
        BCM_AGErrorLamp = 1;
    else
        BCM_AGErrorLamp = 0;
}

static void Warning_2(INT8U state)
{
    if(state)
        BCM_AirBagFailSts = 2;
    else
        BCM_AirBagFailSts = 0;
}

static void Warning_3(INT8U state)
{
    if(state)
        BCM_CDPFailSts = 1;
    else
        BCM_CDPFailSts = 0;
}


static void Warning_4(INT8U state)
{
    if(state)
        BCM_AVHFailSts = 1;
    else
        BCM_AVHFailSts = 0;
}

//报警
static void Warning_5(INT8U state)
{
    if(state)
        BCM_EPBWarningMessage = 1;
    else
        BCM_EPBWarningMessage = 0;
}

static void Warning_6(INT8U state)
{
    if(state)
        BCM_DriverDoorSts = 1;
    else
        BCM_DriverDoorSts = 0;
}


/************************************************************************************************************/
