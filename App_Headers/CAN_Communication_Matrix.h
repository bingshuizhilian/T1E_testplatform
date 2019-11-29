/*****************************************************************************************************************************************************************************
文 件 名：CAN_Communication_Matrix.h
功能描述：BZ3组合仪表CAN通信矩阵
作    者：张暄
版    本：V1.0
日    期：2016.11.8
*****************************************************************************************************************************************************************************/

#ifndef CAN_COMMUNICATION_MATRIX_H_
#define CAN_COMMUNICATION_MATRIX_H_

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;

#pragma MESSAGE DISABLE C1106

/*****************************************************************************************************************************************************************************/
/*报文及信号定义
*****************************************************************************************************************************************************************************/

/*****************************************************************************************************************************************************************************
ID  :  0x280
报文： ABS_ESC_Status
信号源：BCM_EMS_1_G
信号： |- BCM_EngineCoolantTempertureFailSts
             |- BCM_EngineCoolantTemperture
             |- BCM_EngineSpeed
             |- BCM_EngineSpeedValidData
             |- BCM_EPCSts
             |- BCM_MILSts
             |- BCM_IEMSts
*****************************************************************************************************************************************************************************/
typedef union
{
    uint8_t Msg[8];
    struct
    {
        uint8_t          :  1;
        uint8_t  S0_1    :  1;
        uint8_t          :  6;

        uint8_t  S1_0_1  :  2;
        uint8_t          :  1;
        uint8_t  S1_3    :  1;
        uint8_t  S1_4_5  :  2;
        uint8_t          :  2;

        uint8_t  S2_0_7  :  8;

        uint8_t  S3_0_7  :  8;

        uint8_t  S4_0_7  :  8;


        uint8_t  S5_0_4  :  5;
        uint8_t  S5_5_7  :  3;


        uint8_t          :  5;
        uint8_t  S6_5    :  1;
        uint8_t  S6_6    :  1;
        uint8_t  S6_7    :  1;

        uint8_t  S7_0_7  :  8;
    } Sig;
} CANMsgUnion_280;



extern volatile CANMsgUnion_280            CANMsg280;
extern volatile uint8_t                CANMsg280Status;

#define BCM_EMS_1_G                 0x280
#define BCM_EMS_1_G_STATUS          CANMsg280Status


//-------------------280---------------------
#define BCM_CruiseControlStsForDisplay      CANMsg280.Sig.S1_0_1   //00   巡航指示
#define BCM_EngineCoolantTempertureFailSts  CANMsg280.Sig.S1_3     //(11-1)  0   水温表
#define BCM_EngineCoolantTemperture         CANMsg280.Sig.S2_0_7    //(16-8) (20 度)   水温表
#define BCM_FuelRollingCounter              CANMsg280.Sig.S3_0_7    //(24-8) 发动机喷油量
#define BCM_RollingCounterValidData         CANMsg280.Sig.S6_7    //(55-8) 发动机喷油量有效位
#define BCM_EngineSpeed_h                   CANMsg280.Sig.S4_0_7   //(45-11)  0 转速表 
#define BCM_EngineSpeed_l                   CANMsg280.Sig.S5_5_7  //(45-11)  0 转速表 
#define BCM_EngineSpeedValidData            CANMsg280.Sig.S6_6     //(54-1) 0  转速表 
#define BCM_EPCSts                          CANMsg280.Sig.S6_5     //(53-1) 1  EPC 指示
#define BCM_MILSts                          CANMsg280.Sig.S1_4_5   //(12-2) 10   MIL 灯
#define BCM_IEMSts                          CANMsg280.Sig.S0_1     //(1-1)  1    智能发电机
//---------------------------------------

static const uint8_t  CANMsg280Init[8]    = {0x01, 0x20, 0x58, 0x00, 0x00, 0x00, 0x20, 0x00};


/*****************************************************************************************************************************************************************************/
/*ID  :  0x2C0
报文： BCM_StateUpdate
信号源：BCM_EMS_G
信号： |- BCM_ABSFailSts
             |- BCM_ESPSwitchStatus
             |- BCM_TCSFailSts
             |- BCM_VDCFailSts
             |- BCM_VDCActive
             |- BCM_VehicleSpeedVSOSigValidData
             |- BCM_VehicleSpeedVSOSig
*****************************************************************************************************************************************************************************/
typedef union
{
    uint8_t Msg[8];
    struct
    {
        uint8_t  S0_0    :  1;
        uint8_t  S0_1    :  1;
        uint8_t  S0_2    :  1;
        uint8_t  S0_3    :  1;
        uint8_t  S0_4      :  1;
        uint8_t  S0_5      :  1;
        uint8_t          :  2;

        uint8_t  S1_0_4  :  5;
        uint8_t  S1_5      :  1;
        uint8_t  S1_6    :  1;
        uint8_t  S1_7    :  1;//

        uint8_t  S2_0_7  :  8;

        uint8_t          :  7;
        uint8_t  S3_7    :  1;

        uint8_t  S4_0_7  :  8;

        uint8_t  S5_0_1  :  2;
        uint8_t  S5_2    :  1;
        uint8_t  S5_3_4  :  2;
        uint8_t  S5_5    :  1;
        uint8_t  S5_6    :  1;
        uint8_t          :  1;

        uint8_t  S6_0_7  :  8;

        uint8_t  S7_0_7  :  8;
    } Sig;
} CANMsgUnion_2C0;

extern volatile CANMsgUnion_2C0    CANMsg2c0;
extern volatile uint8_t           CANMsg2c0Status;

#define BCM_ABS_ESP_G          0x2C0
#define BCM_ABS_ESP_G_STATUS    CANMsg2c0Status

//---------------------------2C0----------------------
#define BCM_ABSFailSts             CANMsg2c0.Sig.S0_5   //(5_1)   0   ABS 指示
#define BCM_EBDFailSts             CANMsg2c0.Sig.S0_4   //(5_1)   0   
#define BCM_ESPSwitchStatus        CANMsg2c0.Sig.S1_6   //(14-1)  0   ESP屏蔽指示
#define BCM_TCSFailSts             CANMsg2c0.Sig.S0_3   //(3-1)   0
#define BCM_VDCFailSts             CANMsg2c0.Sig.S0_2   //(2-1)   0
#define BCM_TCSActive              CANMsg2c0.Sig.S0_1   //(1-1)   0   ESP 指示
#define BCM_VDCActive              CANMsg2c0.Sig.S0_0   //(0-1)   0
#define BCM_HDCCtrlSts             CANMsg2c0.Sig.S5_0_1 //(0-1)   0   下坡辅助 灯
#define BCM_HDCFailSts             CANMsg2c0.Sig.S5_2 //(0-1)   0   陡坡缓降功能失效
#define BCM_AVHSts                 CANMsg2c0.Sig.S5_3_4 //(43-2)  0
#define BCM_AVHFailSts             CANMsg2c0.Sig.S5_5   //(0-1)   0
#define BCM_CDPFailSts             CANMsg2c0.Sig.S5_6   //(0-1)  
#define BCM_CDPActive              CANMsg2c0.Sig.S1_5
#define BCM_VehicleSpeedVSOSigValidData   CANMsg2c0.Sig.S3_7              //(31-1)  1  车速表 
#define BCM_VehicleSpeedVSOSig_H            CANMsg2c0.Sig.S1_0_4          //(16-13) 0  车速表 
#define BCM_VehicleSpeedVSOSig_L            CANMsg2c0.Sig.S2_0_7           //(16-13) 0  车速表 
//--------------------------------------------------

//#define BCM_Odometerbackup        (CANMsg2D7.Sig.S08H << 8 | CANMsg2D7.Sig.S08L)
static const uint8_t  CANMsg2c0Init[8]    = {0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00};



/*****************************************************************************************************************************************************************************/
/*ID  :  0x392
报文： BCM_LightChimeReq
信号源：BCM_4
信号： |- BCM_TurnIndicatorLeft
             |- BCM_TurnIndicatorRight
             |- BCM_HoodAjarStatus
             |- BCM_TrunckAjarStatus
             |- BCM_FrontLeftDoorAjarStatus
             |- BCM_FrontRightDoorAjarStatus
             |- BCM_RearLeftDoorAjarStatus
             |- BCM_RearRightDoorAjarStatus
             |- BCM_Warning_door_open
             |- BCM_AnyDoorAjar
             |- BCM_LightLeftOn
             |- BCM_ATWS_St
*****************************************************************************************************************************************************************************/
typedef union
{
    uint8_t Msg[8];
    struct
    {
        //0
        uint8_t          :  2;
        uint8_t  S0_2    :  1;
        uint8_t  S0_3    :  1;
        uint8_t          :  1;
        uint8_t  S0_5_6  :  2;
        uint8_t          :  1;

        uint8_t  S1_0    :  1;
        uint8_t  S1_1    :  1;
        uint8_t          :  1;
        uint8_t  S1_3    :  1;
        uint8_t  S1_4    :  1;
        uint8_t          :  2;
        uint8_t  S1_7     :  1;

        uint8_t          :  4;
        uint8_t  S2_4_7  :  4;

        uint8_t  S3_0    :  1;
        uint8_t  S3_1    :  1;
        uint8_t  S3_2    :  1;
        uint8_t          :  1;
        uint8_t  S3_4    :  1;
        uint8_t  S3_5    :  1;
        uint8_t  S3_6    :  1;
        uint8_t          :  1;

        uint8_t          :  2;
        uint8_t  S4_2    :  1;
        uint8_t  S4_3    :  1;
        uint8_t          :  4;

        uint8_t  S5_0_1  :  2;
        uint8_t  S5_2_4  :  3;
        uint8_t  S5_5_7  :  3;
        uint8_t  S6_0_7  :  8;
        uint8_t  S7_0_7  :  8;
    } Sig;
} CANMsgUnion_392;

extern volatile CANMsgUnion_392         CANMsg392;    //
extern volatile uint8_t                CANMsg392Status;

#define BCM_4              0x392
#define BCM_4_STATUS       CANMsg392Status


//----------------------------------------------------------
#define BCM_KeySts                     CANMsg392.Sig.S0_5_6   //(8-1)    0   钥匙状态
#define BCM_LHTurnlightSts             CANMsg392.Sig.S1_0   //(8-1)    0   左转信号
#define BCM_RHTurnlightSts             CANMsg392.Sig.S1_1   //(9-1)    0   右转信号
#define BCM_ParkLightSts               CANMsg392.Sig.S1_3   //(11-1)    0   小灯信号
#define BCM_HighBeamSts                CANMsg392.Sig.S1_4   //(12-1)    0   远光信号
#define BCM_RearFogLightSts            CANMsg392.Sig.S4_2   //(34-1)    0   后雾灯信号
#define BCM_ReverseGearSts             CANMsg392.Sig.S4_3   //(35-1)    0   倒档信号
#define BCM_FollowMeTimeSts            CANMsg392.Sig.S2_4_7   //(20-4)    0000  FollowMeTime
#define BCM_DriverDoorSts              CANMsg392.Sig.S3_0  //(24-1)  0 驾驶门
#define BCM_PsngrDoorSts               CANMsg392.Sig.S3_1  //(25-1)  0  乘员侧门
#define BCM_HoodSts                    CANMsg392.Sig.S3_2  //(26-1)  0  前舱
#define BCM_RHRDoorSts                 CANMsg392.Sig.S3_4  //(28-1) 0  右后门
#define BCM_LHRdoorSts                 CANMsg392.Sig.S3_5  //(29-1) 0   左后门
#define BCM_TrunkSts                   CANMsg392.Sig.S3_6  //(30-1) 0   行李箱
#define BCM_KeyRemindWarning           CANMsg392.Sig.S0_3       //(3-1) 0  钥匙未拔提示
#define BCM_ParkLightOnWarning         CANMsg392.Sig.S0_2      //(2-1)  0  小灯未关提示
#define BCM_DRLSts                     CANMsg392.Sig.S1_7      //(2-1)  0  小灯未关提
#define BCM_WiperSensitivitySWSts      CANMsg392.Sig.S5_2_4
//----------------------------------------------------------


static const uint8_t  CANMsg392Init[8]    = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};



/*****************************************************************************************************************************************************************************/
/*ID  :  0x320
报文： BCM_LightChimeReq
信号源：BCM_4
信号： |- BCM_TurnIndicatorLeft
             |- BCM_TurnIndicatorRight
             |- BCM_HoodAjarStatus
             |- BCM_TrunckAjarStatus
             |- BCM_FrontLeftDoorAjarStatus
             |- BCM_FrontRightDoorAjarStatus
             |- BCM_RearLeftDoorAjarStatus
             |- BCM_RearRightDoorAjarStatus
             |- BCM_Warning_door_open
             |- BCM_AnyDoorAjar
             |- BCM_LightLeftOn
             |- BCM_ATWS_St
*****************************************************************************************************************************************************************************/

typedef union
{
    uint8_t Msg[8];
    struct
    {
        //0
        uint8_t  S0_0_1  :  2;
        uint8_t                 :  4;
        uint8_t  S0_6_7  :  2;

        uint8_t  S1_0_7  :  8;
        uint8_t  S2_0_7  :  8;
        uint8_t  S3_0_7  :  8;

        uint8_t  S4_0_7  :  8;
        uint8_t  S5_0_7  :  8;
        uint8_t  S6_0_7  :  8;
        uint8_t  S7_0_7  :  8;
    } Sig;
} CANMsgUnion_320;

extern volatile CANMsgUnion_320            CANMsg320;    //
extern volatile uint8_t                CANMsg320Status;

#define BCM_ABM_G              0x320
#define BCM_ABM_G_STATUS       CANMsg320Status

//---------------------320------------------------------------
#define BCM_AirBagFailSts         CANMsg320.Sig.S0_6_7    //(6-2)   11 安全气囊故障指示
#define PsngrSeatBeltWarning   CANMsg320.Sig.S0_0_1    //(0-2)   10 安全气囊故障指示 
//---------------------------------------------------------

static const uint8_t  CANMsg320Init[4]    = {0xc0, 0x00, 0x00, 0x00};


/*****************************************************************************************************************************************************************************/
/*ID  :  0x51B
报文： BCM_LightChimeReq
信号源：BCM_4
信号： |- BCM_TurnIndicatorLeft
             |- BCM_TurnIndicatorRight
             |- BCM_HoodAjarStatus
             |- BCM_TrunckAjarStatus
             |- BCM_FrontLeftDoorAjarStatus
             |- BCM_FrontRightDoorAjarStatus
             |- BCM_RearLeftDoorAjarStatus
             |- BCM_RearRightDoorAjarStatus
             |- BCM_Warning_door_open
             |- BCM_AnyDoorAjar
             |- BCM_LightLeftOn
             |- BCM_ATWS_St
*****************************************************************************************************************************************************************************/
typedef union
{
    uint8_t Msg[8];
    struct
    {
        //0
        uint8_t  S0_0    :  1;
        uint8_t  S0_1_3  :  3;
        uint8_t  S0_4_5  :  2;
        uint8_t          :  1;
        uint8_t  S0_7    :  1;
        //1
        uint8_t  S1_0_2  :  3;
        uint8_t  S1_3_5  :  3;
        uint8_t  S1_6_7  :  2;//
        //2
        uint8_t  S2_0_1  :  2;
        uint8_t          :  6;

        uint8_t  S3_0_7  :  8;
        uint8_t  S4_0_7  :  8;
        uint8_t  S5_0_7  :  8;
        uint8_t  S6_0_7  :  8;
        uint8_t  S7_0_7  :  8;
    } Sig;
} CANMsgUnion_51B;

extern volatile CANMsgUnion_51B         CANMsg51b;    //
extern volatile uint8_t                CANMsg51bStatus;

//extern volatile CANMsgUnion_4D4         CANMsg4D4;    //
//extern volatile uint8_t                CANMsg4d4Status;

#define BCM_5              0x51b
#define BCM_5_STATUS       CANMsg51bStatus

//-----------------------51b----------------------------------
#define BCM_Tire_PressureSystemFailSts                  CANMsg51b.Sig.S0_7          //(7-1)  0  轮胎系统故障
#define BCM_Tire_PressureWarningLampSts            CANMsg51b.Sig.S0_4_5          //(4-2)  00  轮胎压力低报警和轮胎温度高报警
#define BCM_LFTyre_TirePositionWarning                CANMsg51b.Sig.S0_1_3          //(1-3)  000  左前轮胎压力报警
#define BCM_RFTyre_TirePositionWarning               CANMsg51b.Sig.S1_6_7          //(14-3-后2)   000      右前轮胎压力报警
#define BCM_LRTyre_TirePositionWarning               CANMsg51b.Sig.S1_3_5          //(11-3)   000      左后轮胎压力报警
#define BCM_RRTyre_TirePositionWarning              CANMsg51b.Sig.S1_0_2          //(8-3)    000      右后轮胎压力报警
#define BCM_Tyre_Positon                    CANMsg51b.Sig.S2_0_1          //(16-2)   00       轮胎位置
#define BCM_TireTemperature         CANMsg51b.Sig.S3_0_7                  //(24-8)   OX00     轮胎温度
#define BCM_LFTyrePressure          CANMsg51b.Sig.S4_0_7                  //(32-8)   0X00     左前轮胎压力                                              
#define BCM_RFTyrePressure          CANMsg51b.Sig.S5_0_7                  //(40-8)   OX00     右前轮胎压力
#define BCM_LRTyrePressure          CANMsg51b.Sig.S6_0_7                  //(48-8)   0X00     左后轮胎压力
#define BCM_RRTyrePressure          CANMsg51b.Sig.S7_0_7                  //(56-8)   0X00     右后轮胎压力
//---------------------------------------------------------

static const uint8_t  CANMsg51bInit[8]    = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};



/*****************************************************************************************************************************************************************************/
/*ID  :  0x301
报文： BCM_LightChimeReq
信号源：BCM_4
信号： |- BCM_TurnIndicatorLeft
             |- BCM_TurnIndicatorRight
             |- BCM_HoodAjarStatus
             |- BCM_TrunckAjarStatus
             |- BCM_FrontLeftDoorAjarStatus
             |- BCM_FrontRightDoorAjarStatus
             |- BCM_RearLeftDoorAjarStatus
             |- BCM_RearRightDoorAjarStatus
             |- BCM_Warning_door_open
             |- BCM_AnyDoorAjar
             |- BCM_LightLeftOn
             |- BCM_ATWS_St
*****************************************************************************************************************************************************************************/
typedef union
{
    uint8_t Msg[8];
    struct
    {
        //0
        uint8_t  S0_0_1  :  2;
        uint8_t  S0_2_3  :  2;
        uint8_t  S0_4_7  :  4;
        //1
        uint8_t  S1_0_1  :  2;
        uint8_t  S1_2_6  :  5;
        uint8_t                :  1;
        uint8_t  S2_0_7  :  8;
        uint8_t  S3_0_7  :  8;
        uint8_t  S4_0_7  :  8;
        uint8_t  S5_0_7  :  8;
        uint8_t  S6_0_7  :  8;
        uint8_t  S7_0_7  :  8;
    } Sig;
} CANMsgUnion_301;

extern volatile CANMsgUnion_301         CANMsg301;    //
extern volatile uint8_t                CANMsg301Status;

#define BCM_TCU_G              0x301
#define BCM_TCU_G_STATUS       CANMsg301Status

//-----------------------301----------------------------------
#define BCM_AGErrorLamp         CANMsg301.Sig.S1_0_1        //(8-2)  00  变速箱故障及油温高
#define BCM_DriveMode           CANMsg301.Sig.S0_0_1        //(0-2)  00  模式显示 
#define BCM_GBPositoionDisplay  CANMsg301.Sig.S1_2_6           //档位显示
#define ClutchTemperature          CANMsg301.Sig.S0_2_3       //      00   DCT 离合器温度高
//---------------------------------------------------------

static const uint8_t  CANMsg301Init[8]    = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


/*****************************************************************************************************************************************************************************/
/*ID  :  0x380
报文： BCM_LightChimeReq
信号源：BCM_4
信号： |- BCM_TurnIndicatorLeft
             |- BCM_TurnIndicatorRight
             |- BCM_HoodAjarStatus
             |- BCM_TrunckAjarStatus
             |- BCM_FrontLeftDoorAjarStatus
             |- BCM_FrontRightDoorAjarStatus
             |- BCM_RearLeftDoorAjarStatus
             |- BCM_RearRightDoorAjarStatus
             |- BCM_Warning_door_open
             |- BCM_AnyDoorAjar
             |- BCM_LightLeftOn
             |- BCM_ATWS_St
*****************************************************************************************************************************************************************************/
typedef union
{
    uint8_t Msg[8];
    struct
    {
        //0
        uint8_t  S0_0    :  1;
        uint8_t          :  7;
        //1
        uint8_t  S1_0_7  :  8;
        uint8_t  S2_0_7  :  8;
        uint8_t  S3_0_7  :  8;
        uint8_t  S4_0_7  :  8;
        uint8_t  S5_0_7  :  8;
        uint8_t  S6_0_7  :  8;
        uint8_t  S7_0_7  :  8;
    } Sig;
} CANMsgUnion_380;

extern volatile CANMsgUnion_380         CANMsg380;    //
extern volatile uint8_t                CANMsg380Status;

#define BCM_EPS_G              0x380
#define BCM_EPS_G_STATUS       CANMsg380Status

//-----------------------51b----------------------------------
#define BCM_EPSFailSts       CANMsg380.Sig.S0_0                //(7-1)  0  EPS 故障指示

//---------------------------------------------------------

static const uint8_t  CANMsg380Init[8]    = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};



/*****************************************************************************************************************************************************************************/
/*ID  :  0x4f6
报文： BCM_LightChimeReq
信号源：BCM_4
信号： |- BCM_TurnIndicatorLeft
             |- BCM_TurnIndicatorRight
             |- BCM_HoodAjarStatus
             |- BCM_TrunckAjarStatus
             |- BCM_FrontLeftDoorAjarStatus
             |- BCM_FrontRightDoorAjarStatus
             |- BCM_RearLeftDoorAjarStatus
             |- BCM_RearRightDoorAjarStatus
             |- BCM_Warning_door_open
             |- BCM_AnyDoorAjar
             |- BCM_LightLeftOn
             |- BCM_ATWS_St
*****************************************************************************************************************************************************************************/
typedef union
{
    uint8_t Msg[8];
    struct
    {
        //0
        uint8_t  S0_0_2  :  3;
        uint8_t          :  1;
        uint8_t  S0_4    :  1;
        uint8_t  S0_5_7  :  3;
        //1
        uint8_t          :  2;
        uint8_t  S1_2_3  :  2;
        uint8_t  S1_4_5  :  2;
        uint8_t  S1_6        :  1;
        uint8_t          :  1;

        uint8_t  S2_0_7  :  8;

        uint8_t  S3_0_7  :  8;

        uint8_t  S4_0_7 :  8;

        uint8_t  S5_0_7  :  8;

        uint8_t  S6_0_7  :  8;

        uint8_t  S7_0_7  :  8;
    } Sig;
} CANMsgUnion_4F6;

extern volatile CANMsgUnion_4F6         CANMsg4f6;    //
extern volatile uint8_t                CANMsg4f6Status;

#define BCM_EPB_G              0x4f6
#define BCM_EPB_G_STATUS       CANMsg4f6Status

//-----------------------4f6----------------------------------
#define BCM_EPBWarningMessage    CANMsg4f6.Sig.S0_0_2                  //(0-3)  000  EPB 报警信息
#define BCM_EPBStatus            CANMsg4f6.Sig.S0_5_7                  //(5-3)  000  EPB 系统状态
#define BCM_Redwarning           CANMsg4f6.Sig.S1_4_5                  //(12-2) 11   红 P 灯
#define BCM_Yellowwarning        CANMsg4f6.Sig.S1_2_3                      //(10-2) 11   黄 P 灯
#define BCM_EPBErrorStatus       CANMsg4f6.Sig.S0_4
#define BCM_RWUActive            CANMsg4f6.Sig.S1_6
//---------------------------------------------------------

static const uint8_t  CANMsg4f6Init[8]    = {0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


/*****************************************************************************************************************************************************************************/
/*ID  :  0x440
报文： RADAR_1
信号源：
信号：
             |- LHRRadarSensorDistance
             |-     LHMRRadarSensorDistance
             |- RHRRadarSensorDistance
             |- AudibleBeepRate
             |- RadarDetectSts
             |- RadarWorkSts
*****************************************************************************************************************************************************************************/
typedef union
{
    uint8_t Msg[8];
    struct
    {
        uint8_t  S0_0_5  :  6;
        uint8_t                 :  2;
        uint8_t  S1_0_7  :  8;
        uint8_t  S2_0_5  :  6;
        uint8_t  S2_6_7  :  2;
        uint8_t  S3_0_5  :   6;
        uint8_t  S3_6_7  :  2;
        uint8_t  S4_0_7  :   8;
        uint8_t                 :  8;
        uint8_t                 :  5;
        uint8_t  S6_5_7  :  3;
        uint8_t  S7_0_4  :  5;
        uint8_t  S7_5      :  1;
        uint8_t  S7_6_7  :  2;
    } Sig;
} CANMsgUnion_440;

extern volatile CANMsgUnion_440         CANMsg440;    //
extern volatile uint8_t                               CANMsg440Status;

#define RADAR_1                       0x440
#define RADAR_1_STATUS       CANMsg440Status

//-----------------------440----------------------------------
#define LHRRadarSensorDistance                CANMsg440.Sig.S0_0_5      //(0-6)  
#define LHMRRadarSensorDistance            CANMsg440.Sig.S2_0_5       //(16-6)  
#define RHRRadarSensorDistance               CANMsg440.Sig.S3_0_5       //(24-6)    
#define AudibleBeepRate                              CANMsg440.Sig.S6_5_7       //(53-3)    
#define RadarDetectSts                                 CANMsg440.Sig.S7_6_7       //(62-2) 
#define RadarWorkSts                                   CANMsg440.Sig.S7_5          //(61-1) 
//---------------------------------------------------------

static const uint8_t  CANMsg440Init[8]    = {0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 0x20, 0x20};

/*****************************************************************************************************************************************************************************/
/*ID  :  0x5f0
报文： BCM_10
信号源：
信号：
             |- SN
*****************************************************************************************************************************************************************************/
typedef union
{
    uint8_t Msg[8];
    struct
    {
        uint8_t  S0_0_3  :  4;
        uint8_t  S0_4_7  :  4;
        uint8_t  S1_0_7  :   8;
        uint8_t  S2_0_7  :   8;
        uint8_t  S3_0_7  :   8;
        uint8_t  S4_0_7  :   8;
        uint8_t  S5_0_7  :   8;
        uint8_t  S6_0_7  :   8;
        uint8_t  S7_0_7  :   8;
    } Sig;
} CANMsgUnion_5F0;

extern volatile CANMsgUnion_5F0         CANMsg5f0;    //
extern volatile uint8_t                               CANMsg5f0Status;

#define BCM_10                       0x5f0
#define BCM_10_STATUS       CANMsg5f0Status

//-----------------------5f0----------------------------------
#define SN                CANMsg5f0.Sig.S0_0_3      //(0-4)  
//---------------------------------------------------------

static const uint8_t  CANMsg5f0Init[8]    = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


/*****************************************************************************************************************************************************************************/
/*ID  :  0x5e1
报文： BCM_6
信号源：
信号：
             |- ASM_ABS_ESP
             |-     TTCEPI
             |- TPMS
             |- RAEBT
             |- FFPEM
*****************************************************************************************************************************************************************************/
typedef union
{
    uint8_t Msg[8];
    struct
    {
        uint8_t  S0_0_7  :  8;
        uint8_t  S1_0_7  :  8;
        uint8_t  S2_0_7  :  8;
        uint8_t  S3_0_7  :  8;
        uint8_t  S4_0_7  :  8;
        uint8_t  S5_0_7  :  8;
        uint8_t  S6_0_7  :  8;
        uint8_t  S7_0_7  :  8;
    } Sig;
} CANMsgUnion_5E1;

extern volatile CANMsgUnion_5E1         CANMsg5e1;
extern volatile uint8_t                               CANMsg5e1Status;

#define BCM_6                       0x5e1
#define BCM_6_STATUS       CANMsg5e1Status

//-----------------------5e1----------------------------------
#define ASM_ABS_ESP                                   CANMsg5e1.Sig.S0_0_7
#define TTCEPI                                        CANMsg5e1.Sig.S1_0_7
#define TPMS                                          CANMsg5e1.Sig.S2_0_7
#define RAEBT                                         CANMsg5e1.Sig.S3_0_7
#define FFPEM                                         CANMsg5e1.Sig.S4_0_7
//---------------------------------------------------------

static const uint8_t  CANMsg5e1Init[8]    = {0x28, 0x38, 0x01, 0x32, 0x0C, 0x00, 0x00, 0x00};


/*****************************************************************************************************************************************************************************/
/*ID  :  0x5ea
报文： BCM_7
信号源：
信号：
             |- LHRRadarSensorDistance
             |-     LHMRRadarSensorDistance
             |- RHRRadarSensorDistance
             |- AudibleBeepRate
             |- RadarDetectSts
             |- RadarWorkSts
*****************************************************************************************************************************************************************************/
typedef union
{
    uint8_t Msg[8];
    struct
    {
        uint8_t  S0_0_7  :  8;
        uint8_t  S1_0_7  :  8;
        uint8_t  S2_0_7  :  8;
        uint8_t  S3_0_7  :  8;
        uint8_t  S4_0_7  :  8;
        uint8_t  S5_0_7  :  8;
        uint8_t  S6_0_7  :  8;
        uint8_t  S7_0_7  :  8;
    } Sig;
} CANMsgUnion_5EA;

extern volatile CANMsgUnion_5EA         CANMsg5ea;
extern volatile uint8_t                               CANMsg5eaStatus;

#define BCM_7                       0x5ea
#define BCM_7_STATUS       CANMsg5eaStatus

//-----------------------5ea----------------------------------
#define L_OSWF                                             CANMsg5ea.Sig.S2_0_7
#define SIMTMA                                             CANMsg5ea.Sig.S5_0_7
#define NAVIGATION_INFO                         CANMsg5ea.Sig.S7_0_7
//---------------------------------------------------------

static const uint8_t  CANMsg5eaInit[8]    = {0x00, 0x00, 0x10, 0x00, 0x00, 0x08, 0x00, 0x10};


/*****************************************************************************************************************************************************************************/
/*ID  :  0x401
报文： ESCL_2
信号源：
信号：
             |- ESCLCriticalFailure
             |-     ESCLFunctionFailure
             |- ESCLUnlockJamming
             |- ESCLNotLocked
*****************************************************************************************************************************************************************************/
typedef union
{
    uint8_t Msg[8];
    struct
    {
        uint8_t  S0_0_1  :  2;
        uint8_t  S0_2_3  :  2;
        uint8_t  S0_4_5  :  2;
        uint8_t  S0_6_7  :  2;
        uint8_t  S1_0_7  :  8;
        uint8_t  S2_0_7  :  8;
        uint8_t  S3_0_7  :  8;
        uint8_t  S4_0_7  :  8;
        uint8_t  S5_0_7  :  8;
        uint8_t  S6_0_7  :  8;
        uint8_t  S7_0_7  :  8;
    } Sig;
} CANMsgUnion_401;

extern volatile CANMsgUnion_401         CANMsg401;
extern volatile uint8_t                               CANMsg401Status;

#define ESCL_2                       0x401
#define ESCL_2_STATUS       CANMsg401Status

//-----------------------5ea----------------------------------
#define ESCLCriticalFailure                                             CANMsg401.Sig.S0_0_1
#define ESCLFunctionFailure                                          CANMsg401.Sig.S0_2_3
#define ESCLUnlockJamming                                         CANMsg401.Sig.S0_4_5
#define ESCLNotLocked                                                  CANMsg401.Sig.S0_6_7
//---------------------------------------------------------

static const uint8_t  CANMsg401Init[8]    = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/*****************************************************************************************************************************************************************************/
/*ID  :  0x3e6
报文： BCM_PEPS_G
信号源：
信号：
             |- PN_SwitchSts
             |-     SmtSysWarning_30
             |- SmtSysWarning_31
             |- SmtSysWarning_32
             |- SmtSysWarning_42
             |- TrunkbackDoorExternalSwitch
             |- SmtSysWarning_20
             |- SmtSysWarning_22
             |- SmtSysWarning_10
             |- SmtSysWarning_11
             |- SmtSysWarning_13
             |- SmtSysWarning_43
             |- SmtSysWarning_65
             |- CrankingRequestValidData
             |- StarterSwitchFlag
             |- OrderInformation
             |- EasytrunkFlashlight
             |- SSBInputFailure
             |- Infosource
             |- IDinfo
             |- SmtSysWarning_52
             |- RemoteStartSts
             |- Start_StopRequest
             |- CrankingRequest
             |- MessageCounter
             |- RemoteStartFailCode1
             |- Checksum
*****************************************************************************************************************************************************************************/
typedef union
{
    uint8_t Msg[8];
    struct
    {
        uint8_t  S0_0      :  1;
        uint8_t  S0_1      :  1;
        uint8_t  S0_2      :  1;
        uint8_t  S0_3      :  1;
        uint8_t  S0_4      :  1;
        uint8_t                :  3;
        uint8_t  S1_0      :  1;
        uint8_t                :  1;
        uint8_t  S1_2      :  1;
        uint8_t                :  1;
        uint8_t  S1_4      :  1;
        uint8_t  S1_5      :  1;
        uint8_t                :  1;
        uint8_t  S1_7      :  1;
        uint8_t                :  1;
        uint8_t  S2_1      :  1;
        uint8_t  S2_2      :  1;
        uint8_t  S2_3      :  1;
        uint8_t                :  3;
        uint8_t  S2_7      :  1;
        uint8_t  S3_0_3  :  4;
        uint8_t  S3_4      :  1;
        uint8_t  S3_5      :  1;
        uint8_t  S3_6_7  :  2;
        uint8_t  S4_0_2  :  3;
        uint8_t                 :  4;
        uint8_t  S4_7      :  1;
        uint8_t  S5_0      :  1;
        uint8_t  S5_1_2  :  2;
        uint8_t  S5_3_5  :  3;
        uint8_t  S5_6_7  :  2;
        uint8_t  S6_0_3  :  4;
        uint8_t  S6_4_7  :  4;
        uint8_t  S7_0_7  :  8;
    } Sig;
} CANMsgUnion_3E6;

extern volatile CANMsgUnion_3E6         CANMsg3e6;
extern volatile uint8_t                               CANMsg3e6Status;

#define BCM_PEPS_G                       0x480
#define BCM_PEPS_G_STATUS       CANMsg3e6Status

//-----------------------3e6----------------------------------
#define SmtSysWarning_31                                                  CANMsg3e6.Sig.S0_2
#define SmtSysWarning_43                                                  CANMsg3e6.Sig.S2_1
#define SmtSysWarning_13                                                  CANMsg3e6.Sig.S1_7
#define SmtSysWarning_10                                                  CANMsg3e6.Sig.S1_4
#define SmtSysWarning_22                                                  CANMsg3e6.Sig.S1_5
#define SmtSysWarning_32                                                  CANMsg3e6.Sig.S0_3
//---------------------------------------------------------

static const uint8_t  CANMsg3e6Init[8]    = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};



/*****************************************************************************************************************************************************************************/
/*ID  :  0x421
报文： BCM_EMS_2_G
信号源：
信号：
             |- LimitSpeedSts
*****************************************************************************************************************************************************************************/
typedef union
{
    uint8_t Msg[8];
    struct
    {
        uint8_t  S0_0_7  :  8;
        uint8_t  S1_0_2  :  3;
        uint8_t  S1_3_7  :  5;
        uint8_t  S2_0_7  :  8;
        uint8_t  S3_0_7  :  8;
        uint8_t  S4_0_7  :  8;
        uint8_t  S5_0_7  :  8;
        uint8_t  S6_0_7  :  8;
        uint8_t  S7_0_7  :  8;
    } Sig;
} CANMsgUnion_421;

extern volatile CANMsgUnion_421         CANMsg421;
extern volatile uint8_t                               CANMsg421Status;

#define BCM_EMS_2_G                       0x421
#define BCM_EMS_2_G_STATUS       CANMsg421Status

//-----------------------421----------------------------------
#define LimitSpeedSts                                             CANMsg421.Sig.S1_0_2
//---------------------------------------------------------

static const uint8_t  CANMsg421Init[8]    = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/***********高配通用******************/
typedef union
{
    uint8_t Msg[8];
} CANMsgStruct;

extern volatile CANMsgStruct    CanMessageID51A;
extern volatile CANMsgStruct    CanMessageID47A;
extern volatile CANMsgStruct    CanMessageID436;
extern volatile CANMsgStruct    CanMessageID307;
extern volatile CANMsgStruct    CanMessageID305;
extern volatile CANMsgStruct    CanMessageID5A3;
extern volatile CANMsgStruct    CanMessageID508;
extern volatile CANMsgStruct    CanMessageID517;


#endif
