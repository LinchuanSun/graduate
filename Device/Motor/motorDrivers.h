#ifndef __MOTORDRIVERS_H
#define __MOTORDRIVERS_H

#include "delay.h"

#define STEPMOTOR_SPEED    10       // 定义步进电机速度，值越小，速度越快
#define STEPMOTOR_SPEED_V  5
#define STEPMOTOR_SPEED_H  5

#define STEPMOTOR_DIRECTION    1      // 1:顺时针 0：逆时针
#define STEPMOTOR_DIRECTION_V  1 
#define STEPMOTOR_DIRECTION_H  1

void driver_uln2003_stepmotor(uint8_t dirc,uint16_t step);
void dirver_l298n_vstepmotor(uint8_t dirc,uint16_t step);
void dirver_l298n_hstepmotor(uint8_t dirc,uint16_t step);

#endif

