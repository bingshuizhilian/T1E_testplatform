

#ifdef        GLOBALS_API_DFLASH
    #define   EXTERN_API_DFLASH
    
#else
    #define   EXTERN_API_DFLASH     extern
#endif

#ifndef API_DFLASH_H_
#define API_DFLASH_H_

    #define   MaxDFlashCommandCounter           0x06
    #define   MaxDelayTime                      BusClock 
    #define   RunComplete                       0
    #define   RunErr                            1
    #define   RunParameterErr                   2
    #define   RunOverTimeErr                    3
    #define   RunErrACCERR                      4
    #define   RunErrFPVIOL                      5
    #define   RunErrMGSTAT1                     6
    #define   RunErrMGSTAT0                     7
    #define   RunErr                            1
    #define   WordSize                          0x02
                                                 //�ִ�С
    #define   GLOBAL_ADDRESS_DFLASH             0x0000
                                                 //D Flashȫ�ֵ�ַ[17:16]
    #define   DFLASH_BLOCK_START_ADDR           0x004400
                                                 // D Flash ��ʼ��ַ
                                                 
    #define   DFLASH_VOLT_ADDR                  DFLASH_BLOCK_START_ADDR
                                                 // ��ѹ��ʼ��ַ 
    #define   DFLASH_OIL_ADDR                   DFLASH_VOLT_ADDR + 64
                                                 // ������ʼ��ַ
    #define   DFLASH_TMP_ADDR                   DFLASH_OIL_ADDR + 64
                                                 // ˮ����ʼ��ַ
    #define   DFLASH_FUEL_ADDR                  DFLASH_TMP_ADDR + 64
                                                 // ȼ����ʼ��ַ
    #define   DFLASH_VEH_ADDR                   DFLASH_FUEL_ADDR + 64
                                                 // ������ʼ��ַ
    #define   DFLASH_REV_ADDR                   DFLASH_VEH_ADDR + 64
                                                 // ת����ʼ��ַ
    #define   DFLASH_UNION_ADDR                 DFLASH_REV_ADDR + 64
                                                 // 
                                                                                                                                                                                                                                                                                                                                                                                                      
    #define   DFLASH_BLOCK_END_ADDR             0x0053FF
                                                 // D Flash ������ַ
    #define   DFLASH_SECTOR_SIZE                0x0100  
                                                 // 256 �ֽ���
    #define   DFLASH_ACC_START_ADD              0x004C00
                                                 //D-Falsh����ۼ���ʼ��ַ
    #define   DFLASH_ACC_END_ADD                0x004FFF
                                                 //D-Flash����ۼƽ�����ַ
    #define   DFLASH_MAXIMUM_SIZE               0x00001000  
                                                 //D Flash ���ߴ� 4 KB
    #define   DFLASH_ERASE_VERIFY               0x10 
                                                 //D Flash ������֤����
    #define   DFLASH_PROGRAM                    0x11  
                                                 //D Falsh �������
    #define   DFLASH_ERASE_SECTOR               0x12  
                                                 //D Flash ��������
    #define   DFLASH_ERASE_COM_LENGTH           0x01
                                                 //D Flash ���������
    #define   DFLASH_ERASE_VERIFY_COM_LENGTH    0x02
                                                 //D Flash ������������� 
    #define   DFLASH_PROGRAM_COM_LENGTH         0x04
                                                 //D Flash ������ֽڳ���  
    #define   MaxProgramByteNumber              0x08
                                                 //������ֽ��� 
    #define   DFlashAccSectorEndAdd             0x004F00 
    #define   DflashAccSectorStartAdd           0x004C00 
    #define   DFLASH_PROGRAM_OFFSET             0x4000 
    
    #define   DFlashAccReadStartAdd             (DFLASH_ACC_START_ADD - DFLASH_PROGRAM_OFFSET)
    #define   DFlashAccReadEndAdd               (DFLASH_ACC_END_ADD - DFLASH_PROGRAM_OFFSET)
    #define   DFlashAccBlockNumber              ((DFLASH_ACC_END_ADD - DFLASH_ACC_START_ADD + 1) / DFlashAccBlockLength)
                                               
                                              
    EXTERN_API_DFLASH     void    API_Flash_Init(void);
    EXTERN_API_DFLASH     INT8U   API_Flash_byte_read(INT16U _addr);                                                                                                                                      
    EXTERN_API_DFLASH     INT8U   API_DFlashCommSequence(INT8U bCommandCounter);
    EXTERN_API_DFLASH     INT8U   API_DFlashEraseSector(INT16U wDestination);
    EXTERN_API_DFLASH     INT8U   API_DFalshProgram(INT16U wDest,INT16U wByteNub,INT16U *wSource);
    EXTERN_API_DFLASH     INT8U   API_DFlashEraseVerify(INT16U wDestination, INT16U wSize);  



                             
#endif /* API_DFLASH_H_ */
