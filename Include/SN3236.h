#ifndef  __SN3236_H__
#define  __SN3236_H__

#include "app_main.h"

#define REG_00H_TURN_ON        0x00
#define REG_01H_PWM_START      0x01
#define REG_25H_UPDATE         0x25
#define REG_26H_PWM_CONTROL    0x26
#define REG_4AH_GLOBAL_CONTROL 0x4A

extern u8 SN3236_Pwm1_1[36];//一面灯光有两个3236芯片控制
extern u8 SN3236_Pwm1_2[36];
extern u8 SN3236_Pwm2_1[36];
extern u8 SN3236_Pwm2_2[36];
extern u8 SN3236_Pwm3_1[36];
extern u8 SN3236_Pwm3_2[36];
extern u8 SN3236_Pwm4_1[36];
extern u8 SN3236_Pwm4_2[36];
extern u8 SN3236_RegBuffer[0x4B];
void SN3236_Init1(void);
void SN3236_Driver(void);
void SN3236_Clearing(void);

#endif












