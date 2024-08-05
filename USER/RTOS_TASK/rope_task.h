#ifndef ROPE_TASK_H
#define ROPE_TASK_H
#include "pid.h"
#include "dm4310_drv.h"
#define ARM_MOTOR_KP 10.0f
#define ARM_MOTOR_KI 0.0f
#define ARM_MOTOR_KD 0.0f
typedef struct
{
    float  x_angel[3];
	float  y_angle[3];
	float  rope_length[3][2];
} arm_param;

void rope_cal_process(void);
void motor_enable_init(void);
void dm4310_data(motor_fbpara_t *motor, uint8_t *rx_data,uint32_t data_len);
#endif
