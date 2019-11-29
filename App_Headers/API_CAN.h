

#ifdef        GLOBALS_API_CAN
    #define   EXTERN_API_CAN
    
#else
    #define   EXTERN_API_CAN     extern
#endif

#ifndef API_CAN_H_
#define API_CAN_H_
    #define     SJW_1Tq                  0
    #define     SJW_2Tq                  1
    #define     SJW_3Tq                  2
    #define     SAMP_1                   0
    #define     Seg1_11Tq                10
    #define     Seg1_12Tq                11
    #define     Seg1_8Tq                 7
    #define     Seg2_7Tq                 6
    #define     Seg2_8Tq                 7
    #define     Seg1_4Tq                 3
    #define     Seg1_5Tq                 4
    #define     Seg1_6Tq                 5
    #define     Seg2_1Tq                 0
    #define     Seg2_2Tq                 1
    #define     Seg2_3Tq                 2
    #define     Seg2_4Tq                 3
    #define     IDAM_2_32Bit             0
    #define     IDAM_4_16Bit             1
    #define     IDHIT0                   0
    #define     empoty                   0
    #define     msg_full                 1
    #define     bit0_mask                1
    #define     bit1_mask                2
    #define     bit2_mask                4
    #define     bit3_mask                8
    #define     bit4_mask                16
    #define     bit5_mask                32
    #define     bit6_mask                64
    #define     bit7_mask                128
    //ºê¶¨Òå
    #define     GET_EXTPGN(id)         (((((((INT32U)id&0xFF0000)>>16) >= 0xF0)?((INT32U)id & 0x00FF00):0)|((INT32U)id & 0x2FF0000)) >> 8)
    
    #define     ID0C9    0x0C9
    #define     ID3D1    0x3D1
    #define     ID4C1    0x4C1
    #define     ID4D1    0x4D1
    #define     ID3E9    0x3E9
    #define     ID348    0x348
    #define     ID34A    0x34A
    #define     ID1E9    0x1E9
    #define     ID17D    0x17D
    #define     ID1F1    0x1F1
    #define     ID140    0x140
    #define     ID12A    0x12A
    #define     ID1E5    0x1E5
    #define     ID120    0x120
    #define     ID600    0x600
    #define     ID601    0x601
    #define     ID602    0x602
    #define     ID614    0x614
    #define     ID605    0x605
    #define     ID120    0x120
    #define     success      1
    #define     failt        0
      
    
    EXTERN_API_CAN               void    API_CAN_Init(void);    
    EXTERN_API_CAN               INT32U  API_EXT_ID_TO_PGN(INT8U *IDR0_Add); 
    EXTERN_API_CAN               INT16U  API_GET_STAND_ID(INT8U *IDR0_Add);
    EXTERN_API_CAN               INT8U   API_GET_EXTID_SA(INT8U *IDR3_Add); 
    EXTERN_API_CAN     interrupt void    API_CAN_Rev_isr(void); 
    EXTERN_API_CAN               INT8U   API_CANSendFrame (INT32U id,INT8U priority,INT8U length,INT8U *txdata);
    EXTERN_API_CAN               INT8U   API_CANSendExtFrame (INT32U id,INT8U priority,INT8U length,INT8U *txdata);
#endif /* API_CAN_H_ */
