#define GLOBALS_VARIABLE

#include "../App_Headers/includes.h"
#include "main.h"
#define CAN_NUM  23

_SendCanMsg CanMsg[CAN_NUM];

//��ǰ����ʾ�ĵ�
INT8U Cur_Led = 0;

//ת��
int EngineSpeed = 0, jj = 0;
INT8U EngineSpeed_Dir = 0;
INT8U EngineSpeed_En = 0;

//����
int VehicleSpeed = 0;
INT8U VehicleSpeed_Dir = 0;
INT8U VehicleSpeed_En = 0;

//ˮ��
INT8U EngineCoolantTemperture = 0;
INT8U EngineCoolantTemperture_Dir = 0;

//��˸
volatile uint8_t flash_1s;
void main(void)
{
    flash_1s = 0;
    RunStep = 0;
    MaxStep = 81 + 34 + 2;//switch ����
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
                //ˮ��3/8
                if(RunStep == 11)
                    EngineCoolantTemperture  =  154;

                if(RunStep <= 11)
                {
                    //ת�ٵ���
                    EngineSpeed = 2000 / 8 * RunStep;
                    if(EngineSpeed > 2000)
                        EngineSpeed = 2000;

                    //���ٵ���
                    VehicleSpeed = 3520 / 11 * RunStep;
                    if(VehicleSpeed > 3520)
                        VehicleSpeed = 3520;
                }
            }
            break;
            case 12:
            {
                //��ת
                BCM_RHTurnlightSts = 1;
            }
            break;
            case 13:
            {
                BCM_RHTurnlightSts = 0;
                //Զ��
                BCM_HighBeamSts = 1;
            }
            break;
            case 14:
            {
                BCM_HighBeamSts = 0;
                //С��
                BCM_ParkLightSts = 1;
            }
            break;
            case 15:
            {
                BCM_ParkLightSts = 0;
                //����ת���������ع��ϵ�������ɫ) ������ͣ����������ת������������������.
                ESCLCriticalFailure = 1;
            }
            break;
            case 16:
            {
                ESCLCriticalFailure = 0;
                //����ת���������ϵ�������ɫ�� ������ͣ����������ת������������������
                ESCLFunctionFailure = 1;
            }
            break;
            case 17:
            {
                ESCLFunctionFailure = 0;
                //����ת��������ס�ƣ���ɫ�����Ǳ���ʾ����ת������ס��ת��������������
                ESCLUnlockJamming = 1;
            }
            break;
            case 18:
            {
                ESCLUnlockJamming = 0;
                //�����������ɫ��
                BCM_RearFogLightSts = 1;
            }
            break;
            case 19:
            {
                BCM_RearFogLightSts = 0;
                //EPS����ָʾ������ɫ�����Ǳ���ʾ��������ת��ϵͳ
                BCM_EPSFailSts = 1;
            }
            break;
            case 20:
                BCM_EPSFailSts = 0; //��һ��
                break;
            case 21:
            {
                //��ȫ���ҹ��ϵ�������ɫ�����Ǳ���ʾ��������ϵͳ
                BCM_AirBagFailSts = 1;
            }
            break;
            case 22:
            {
                BCM_AirBagFailSts = 0;
                //��ת��������ɫ��
                BCM_LHTurnlightSts = 1;

            }
            break;
            case 23:
            {
                BCM_LHTurnlightSts = 0;
                // ���»�������(��ɫ) �Ǳ���ʾ���»������ܿ���
                BCM_HDCCtrlSts = 1;
            }
            break;
            case 24:
            {
                BCM_HDCCtrlSts = 0;
                //�Ǳ���ʾ���»���ʧЧ
                BCM_HDCFailSts = 1;
            }
            break;
            case 25:
            {
                BCM_HDCFailSts = 0;
                //AUTOHOLD������ɫ�����Ǳ���ʾESP��̬�ƶ�����ʧЧ������ʾ�Զ�פ�����ܿ���
                BCM_CDPFailSts = 1;
                BCM_AVHSts = 2;
            }
            break;
            case 26:
            {
                BCM_CDPFailSts = 0;
                BCM_AVHSts = 0;
                //Ѳ���� (��ɫ)
                BCM_CruiseControlStsForDisplay = 1;
            }
            break;
            case 27:
            {
                BCM_CruiseControlStsForDisplay = 0;
                //Ѳ������������ɫ��//***********421********************************************
                LimitSpeedSts = 1;
            }
            break;
            case 28:
            {
                //BCM_RHTurnlightSts = 0;
                //���ƶ�δ�ɵ�������ɫ��
                BCM_EBDFailSts = 1;
            }
            break;
            case 29:
            {
                BCM_EBDFailSts = 0;
                //��P��˸
                BCM_Redwarning = 1;
            }
            break;
            case 30:
            {
                BCM_Redwarning = 0;
                //��P��˸
                BCM_Yellowwarning = 1;
            }
            break;
            case 31:
            {
                //ESP������ɫ����P��������˸�����Ǳ���ʾ����ESPϵͳ
                BCM_Yellowwarning = 2;
                BCM_VDCFailSts = 1;
            }
            break;
            case 32:
            {
                BCM_Yellowwarning = 0;
                BCM_VDCFailSts = 0;
                //ESPOFF������ɫ����P��������˸��
                BCM_ESPSwitchStatus = 1;
                BCM_Redwarning = 2;
            }
            break;
            case 33:
            {
                BCM_ESPSwitchStatus = 0;
                BCM_Redwarning = 0;
                //ABSָʾ��������ɫ���Ǳ���ʾ����ABSϵͳ
                BCM_ABSFailSts = 1;
            }
            break;
            case 34:
            {
                BCM_ABSFailSts = 0;
                //EPC��������ɫ��
                BCM_EPCSts = 1;

            }
            break;
            case 35:
            {
                BCM_EPCSts = 0;
                //����������������ɫ����
                BCM_MILSts = 2;

            }
            break;
            case 36:
            {
                BCM_MILSts = 0;
                //���ص�����������ɫ��
                BCM_IEMSts = 1;
            }
            break;
            case  37:
            {
                BCM_IEMSts = 0;
                //��ȫ����������ɫ�� ��ϵ�ð�ȫ�������ݰ�ȫ��δϵ����ע�ⰲȫ
                PsngrSeatBeltWarning = 2;
            }
            break;
            case  38:
            {
                PsngrSeatBeltWarning = 0;
                //̥ѹ��������ɫ��˸�����Ǳ���ʾ����̥ѹ����ϵͳ
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
                //��������ϵ�������ɫ�����Ǳ���ʾ������������ϵͳ
                BCM_AGErrorLamp = 1;//CanMessageID301.Msg[1] = 0x01;
            }
            break;
            case  40:
            {
                BCM_AGErrorLamp = 0;
                //С����ǰ�ſ�������������
                BCM_DriverDoorSts = 1;
            }
            break;
            case  41:
            {
                BCM_DriverDoorSts = 0;
                //С����ǰ�ſ������������졣
                BCM_PsngrDoorSts = 1;
            }
            break;
            case  42:
            {
                BCM_PsngrDoorSts = 0;
                //С���������ǿ������������졣
                BCM_HoodSts = 1;
            }
            break;
            case  43:
            {
                BCM_HoodSts = 0;
                //С���Һ��ſ�������������
                BCM_RHRDoorSts = 1;
            }
            break;
            case  44:
            {
                BCM_RHRDoorSts = 0;
                //С������ſ��������ſ�������������
                BCM_LHRdoorSts = 1;
            }
            break;
            case  45:
            {
                BCM_LHRdoorSts = 0;
                //С�������ſ������������졣
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
                //�����״�ȫ������λR��������������// *************440*****************
                BCM_GBPositoionDisplay = 2;
                RadarWorkSts = 1;
                RadarDetectSts = 4;

            }
            break;
            case  47:
            {
                RadarWorkSts = 0;
                //BCM_EPBWarningMessage = 0;
                //��ȫ�ԡ�����������
                Led_all();
                CanMessageID307.Msg[0] = 0x02;
                CanMessageID305.Msg[0] = 0x01;
                CanMessageID305.Msg[4] = 0x04;
                CANMsg320.Msg[1] = 0x01;

                //ˮ��1��
                EngineCoolantTemperture = 131;
            }
            break;
            case  48:
            {
                //BCM_EPBWarningMessage = 0;
                //ˮ��3��
                EngineCoolantTemperture = 154;
            }
            break;
            case 49:
                //ˮ��5��
                EngineCoolantTemperture = 181;
                break;
            case 50:
                //ˮ��8�� ������ˮ�¸ߣ�����ϵ4S���飬���������죬ˮ�±����ƺ�ɫ��˸��ˮ�¸��죬�Ǳ���ʾ������ȴҺλ
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
                //��λ1
                BCM_GBPositoionDisplay = 5;
                break;
            case 52:
                //��λ2
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
                //��λ3
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
                //��λ4
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
                //��λ5
                BCM_GBPositoionDisplay = 9;
                break;
            case 56:
                //��λ6
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
                //��λ7
                BCM_GBPositoionDisplay = 11;
                break;
            case 58:
                BCM_GBPositoionDisplay = 0;
                //��һ��
                BCM_Tire_PressureWarningLampSts = 2;
                break;
            case  59:
            {
                //BCM_EPBWarningMessage = 0;
                //�Ǳ���ʾ�����P/N������  ��������6��
                SmtSysWarning_32 = 1;
            }
            break;
            case  60:
            {
                SmtSysWarning_32 = 0;
                //�Ǳ���ʾ�����P��  ��������6��
                SmtSysWarning_43 = 1;
            }
            break;
            case  61:
            {
                SmtSysWarning_43 = 0;
                //�Ǳ���ʾ��ע�⳵��������Կ��  ��������6��
                SmtSysWarning_13 = 1;
            }
            break;
            case  62:
            {
                SmtSysWarning_13 = 0;
                //�Ǳ���ʾ����Կ�׵����ͣ�������ʾ����Կ�׵������뼰ʱ�������  ��������6��
                SmtSysWarning_31 = 1;
            }
            break;
            case  63:
            {
                SmtSysWarning_31 = 0;
                //�Ǳ���ʾ��رյ�Դ   ��������6��           ************3e6*BCM_PEPS_G*SmartSystemWarning_1.0************
                SmtSysWarning_10 = 1;
            }
            break;
            case  64:
            {
                SmtSysWarning_10 = 0;
                UnLed_all();
                //�Ǳ���ʾ�ͷ�פ��ʱ������ƶ�̤��   ��������6��
                BCM_EPBWarningMessage = 1;
            }
            break;
            case  65:
            {
                //BCM_EPBWarningMessage = 0;
                //�Ǳ���ʾ��رճ��Ų�ϵ�ð�ȫ��
                BCM_EPBWarningMessage = 2;
            }
            break;
            case  66:
            {
                //BCM_EPBWarningMessage = 0;
                //�Ǳ���ʾפ���¶ȹ�����ע�ⰲȫ  ��������6��
                BCM_EPBWarningMessage = 3;
            }
            break;
            case  67:
            {
                BCM_EPBWarningMessage = 0;
                //�Ǳ���ʾδ��⵽����Կ��  ��������6��
                SmtSysWarning_22 = 1;               //************************************************************
            }
            break;
            case  68:
            {
                //BCM_EPBWarningMessage = 0;                      //************************************************************
                //̥ѹ���ϵ�������ǰ��̥��ɫ
                BCM_LFTyre_TirePositionWarning = 2;
            }
            break;
            case  69:
            {
                BCM_LFTyre_TirePositionWarning = 0;
                //̥ѹ���ϵ�������ǰ��̥��ɫ
                BCM_RFTyre_TirePositionWarning = 2;                  //************************************************************
            }
            break;
            case  70:
            {
                BCM_RFTyre_TirePositionWarning = 0;                  //************************************************************
                //̥ѹ���ϵ����������̥��ɫ
                BCM_LRTyre_TirePositionWarning = 2;
            }
            break;
            case  71:
            {
                BCM_LRTyre_TirePositionWarning = 0;
                //̥ѹ���ϵ������Һ���̥��ɫ
                BCM_RRTyre_TirePositionWarning = 2;
            }
            break;
            case  72:
            {
                BCM_RRTyre_TirePositionWarning = 0;
                //RadarDetectSts = 2;
                RadarWorkSts = 1;
                //�����״���һ���������������������챨��   ****440 ****
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
                //�����״�������������������������챨��
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
                //�����״��������������������������챨��
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
                //�����״���һ���������������������챨��
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
                //�����״��ж����������������������챨��
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
                //�����״��������������������������챨��
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
                //�����״���һ���������������������챨��
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
                //�����״��Ҷ����������������������챨��
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
                //�����״��������������������������챨��
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
                //�Ǳ���ʾ�����������ͣ���İ�ȫ��Լ2����
                BCM_AGErrorLamp = 1;
                ClutchTemperature = 2;
            }
            break;
            case 81 + 1:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID305.Msg[2] = 1 << 3;

            }
            break;
            case 81 + 2:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID305.Msg[2] = 2 << 3;

            }
            break;

            case 81 + 3:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID305.Msg[2] = 3 << 3;

            }
            break;
            case 81 + 4:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID305.Msg[2] = 4 << 3;

            }
            break;
            case 81 + 5:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID305.Msg[2] = 5 << 3;

            }
            break;
            case 81 + 6:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID305.Msg[2] = 6 << 3;

            }
            break;
            case 81 + 7:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID305.Msg[2] = 7 << 3;

            }
            break;
            case 81 + 8:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID305.Msg[2] = 8 << 3;

            }
            break;
            case 81 + 9:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID305.Msg[2] = 9 << 3;

            }
            break;
            case 81 + 10:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID305.Msg[2] = 10 << 3;

            }
            break;
            case 81 + 11:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID305.Msg[2] = 11 << 3;
            }
            break;
            case 81 + 12:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID305.Msg[2] = 12 << 3;

            }
            break;
            case 81 + 13:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID305.Msg[2] = 13 << 3;

            }
            break;
            case 81 + 14:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID305.Msg[2] = 14 << 3;
                ;
            }
            break;
            case 81 + 15:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID305.Msg[2] = 15 << 3;

            }
            break;
            case 81 + 16:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID305.Msg[2] = 16 << 3;

            }
            break;
            case 81 + 17:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID305.Msg[2] = 17 << 3;

            }
            break;
            case 81 + 18:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID305.Msg[2] = 18 << 3;

            }
            break;
            case 81 + 19:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID305.Msg[2] = 19 << 3;

            }
            break;
            case 81 + 20:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID305.Msg[2] = 20 << 3;

            }
            break;
            case 81 + 21:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID305.Msg[2] = 21 << 3;

            }
            break;
            case 81 + 22:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID305.Msg[2] = 22 << 3;

            }
            break;
            case 81 + 23:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID436.Msg[0] = 100;

            }
            break;
            case 81 + 24:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CANMsg392.Msg[5] = 3 << 2;

            }
            break;
            case 81 + 25:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID508.Msg[0] = 1 << 3;

            }
            break;
            case 81 + 26:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID508.Msg[0] = 1 << 4;

            }
            break;
            case 81 + 27:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID508.Msg[0] = 1 << 5;

            }
            break;
            case 81 + 28:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID508.Msg[0] = 1 << 6;

            }
            break;
            case 81 + 29:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID508.Msg[0] = 1 << 7;

            }
            break;
            case 81 + 30:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID47A.Msg[0] = 1 << 3;

            }
            break;
            case 81 + 31:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID47A.Msg[0] = 4 << 3;

            }
            break;
            case 81 + 32:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
                CanMessageID307.Msg[4] = 1 << 6;
            }
            break;
            case 81 + 33:
            {

                //����ת��������ס ��ת��������������//ESCLUnlockJamming ����ESCL_2
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
                //����220 ת��8000  ��ʱ��סOK��5S  �ϳ����ڸ������Ǳ�������
                EngineSpeed = 2000;
                VehicleSpeed = 3520;
            }
            break;
            case 81 + 37:
            {
                BCM_AGErrorLamp = 0;
                ClutchTemperature = 0;
                //����220 ת��8000  ��ʱ��סOK��5S  �ϳ����ڸ������Ǳ�������
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

//��ѭ������
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

    //�ر�ǰһ��
    if(Cur_Led > 1)
    {
        (runStruct[Cur_Led - 1].ptr)(0);
    }
    //��ʾ��ǰ��
    (runStruct[Cur_Led].ptr)(1);

    //�رպ�һ��
    if(Cur_Led < MAX_LED - 1)
    {
        (runStruct[Cur_Led + 1].ptr)(0);
    }
}
//�����еĵ�
static void  Led_all(void)
{
    INT8U i;
    for(i = 1; i <= LED_COUNT; i++)
    {
        (runStruct[i].ptr)(1);
    }
}

//�����еĵ�
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

//��ʼ����������
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

/******************************************************�ܱ��������********************************************************/

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

//����
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
