/******************************************************************************
文 件 名：CAN_Communication_Matrix.c
功能描述：BZ3组合仪表CAN通信矩阵变量声明
作    者：张暄
版    本：V1.0
日    期：2016.11.8
******************************************************************************/

#include "CAN_Communication_Matrix.h"

volatile CANMsgUnion_280            CANMsg280; 
volatile uint8_t                CANMsg280Status;

volatile CANMsgUnion_2C0    CANMsg2c0; 
volatile uint8_t           CANMsg2c0Status;


volatile CANMsgUnion_392         CANMsg392;    //  
volatile uint8_t                CANMsg392Status;

volatile CANMsgUnion_320            CANMsg320;    //  
volatile uint8_t                CANMsg320Status;


volatile CANMsgUnion_51B         CANMsg51b;    //  
volatile uint8_t                CANMsg51bStatus;


volatile CANMsgUnion_301         CANMsg301;    //  
volatile uint8_t                CANMsg301Status;

volatile CANMsgUnion_380         CANMsg380;    //  
volatile uint8_t                CANMsg380Status;


volatile CANMsgUnion_4F6         CANMsg4f6;    //  
volatile uint8_t                CANMsg4f6Status;

//volatile CANMsgUnion_4D4         CANMsg4D4;    //  
//volatile uint8_t                CANMsg4d4Status;

volatile CANMsgUnion_440         CANMsg440;    //  
volatile uint8_t                CANMsg440Status;

volatile CANMsgUnion_5F0         CANMsg5f0;    //  
volatile uint8_t                CANMsg5f0Status;

volatile CANMsgUnion_5E1         CANMsg5e1;    //  
volatile uint8_t                CANMsg5e1Status;

volatile CANMsgUnion_5EA         CANMsg5ea;    //  
volatile uint8_t                CANMsg5eaStatus;

volatile CANMsgUnion_401         CANMsg401;    //  
volatile uint8_t                CANMsg401Status;

volatile CANMsgUnion_3E6         CANMsg3e6;    //  
volatile uint8_t                CANMsg3e6Status;

volatile CANMsgUnion_421         CANMsg421;    //  
volatile uint8_t                CANMsg421Status;

volatile CANMsgStruct    CanMessageID51A;
volatile CANMsgStruct    CanMessageID47A;
volatile CANMsgStruct    CanMessageID436;
volatile CANMsgStruct    CanMessageID307;
volatile CANMsgStruct    CanMessageID305;
volatile CANMsgStruct    CanMessageID5A3;
volatile CANMsgStruct    CanMessageID508;
volatile CANMsgStruct    CanMessageID517;


