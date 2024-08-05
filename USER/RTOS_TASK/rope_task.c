#include "rope_task.h"
#include "cmsis_os.h"
#include "fdcan.h"

float pos_test,vel_test;
uint16_t test_id;

void rope_cal_process(void)
{ 	
  motor_enable_init();
  for(;;)
	  {	
		pos_speed_ctrl(&hfdcan1,3, pos_test, vel_test);
		 osDelay(3);
	  }
}
/**
  * @brief          
  * @param[in]      none
  * @retval         none
  */
void angle_trans()
{
	

}
/**
  * @brief          
  * @param[in]      none
  * @retval         none
  */
void motor_enable_init(void)
{
for (uint8_t i = 0; i < 10; i++)
	{
		enable_motor_mode(&hfdcan1,3,POS_MODE);
		osDelay(30);
	}
}
/**
  * @brief          
  * @param[in]      none
  * @retval         none
  */
void dm4310_data(motor_fbpara_t *motor, uint8_t *rx_data,uint32_t data_len)
{ 
	if(data_len==FDCAN_DLC_BYTES_8)
	{//返回的数据有8个字节
	  motor->id = (rx_data[0])&0x0F;
	  motor->state = (rx_data[0])>>4;
	  motor->p_int=(rx_data[1]<<8)|rx_data[2];
	  motor->v_int=(rx_data[3]<<4)|(rx_data[4]>>4);
	  motor->t_int=((rx_data[4]&0xF)<<8)|rx_data[5];
	  motor->pos = uint_to_float(motor->p_int, P_MIN, P_MAX, 16); // (-12.5,12.5)
	  motor->vel = uint_to_float(motor->v_int, V_MIN, V_MAX, 12); // (-30.0,30.0)
	  motor->tor = uint_to_float(motor->t_int, T_MIN, T_MAX, 12);  // (-10.0,10.0)
	  motor->Tmos = (float)(rx_data[6]);
	  motor->Tcoil = (float)(rx_data[7]);
	}
}

