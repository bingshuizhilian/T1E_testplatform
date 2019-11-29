#ifndef  __MAIN__H
#define  __MAIN__H

typedef struct 
{
   void (* ptr)(INT8U state); 
   INT8U type;
}RunModeStruct;

static void Init_CanMsg(void);
static void Switch_timer(INT16U timerId);
static void Run(); 
static void EngineSpeed_Run(); 
static void VehicleSpeed_Run();
static void WaterTemp_Run();
static void LED_Run();

static void  Led_all(void);
static void  UnLed_all(void);
static void Led_Right(INT8U state);
static void Led_Left(INT8U state);

static void Led_1(INT8U state);
static void Led_2(INT8U state);
static void Led_3(INT8U state);
static void Led_4(INT8U state);
static void Led_5(INT8U state);
static void Led_6(INT8U state);
static void Led_11(INT8U state);
static void Led_12(INT8U state);
static void Led_13(INT8U state);
static void Led_14(INT8U state);
static void Led_15(INT8U state);
static void Led_16(INT8U state);
static void Led_17(INT8U state);
static void Led_18(INT8U state);
static void Led_19(INT8U state);
static void Led_20(INT8U state);
static void Led_21(INT8U state);
static void Clear_CanMsg();

static void Warning_1(INT8U state);
static void Warning_2(INT8U state);
static void Warning_3(INT8U state);
static void Warning_4(INT8U state);
static void Warning_5(INT8U state);
static void Warning_6(INT8U state);


static  RunModeStruct runStruct[] = 
{  
   {null,       0}, 
   {Led_Right,  0},
   {Led_12,     0},
   {Led_11,     0},
   {Led_13,     0},
   {Led_Left,   0},  
   {Led_6,      0},
   {Led_20,     0},
   {Led_5,      0},
   {Led_1,      0},
   {Led_2,      0},
   {Led_3,      0},
   {Led_19,     0}, //×ó±íÅÌ   
   {Led_14,     0},
   {Led_15,     0},
   {Led_16,     0},
   {Led_17,     0},
   {Led_18,     0},
   {Led_21,     0},   
   {Warning_1,  1},
   {Warning_2,  1},
   {Warning_3,  1},
   {Warning_4,  1},
   {Warning_5,  1},
   {Warning_6,  1} 
};

#define MAX_LED (sizeof(runStruct) / sizeof(RunModeStruct))
#define LED_COUNT  19

#endif