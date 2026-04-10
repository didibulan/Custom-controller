/**
*   @file BSP_AS5600.h
*   @brief AS5600磁编码器BSP驱动
*   @author Kena Zhong
*   @date 26-04-07
*   @version 1.0
*   @note
*/
#ifndef BSP_AS5600_H
#define BSP_AS5600_H

#include "Bsp_LPF.h"
#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

#define AS5600_ADDRESS		0x36		//AS5600的I2C从机地址

#define AS5600_REG_RAW_ANGLE_H         0x0C    // 原始角度高位
#define AS5600_REG_RAW_ANGLE_L         0x0D    // 原始角度低位

    /* 功能常量宏定义 */
#define AS5600_ANGLE_MAX_VAL           4096.0f // 12位ADC最大值
#define AS5600_ANGLE_TO_DEGREE         360.0f  // 角度转换系数
#define PI                             3.1415926535f  // 圆周率


    void AS5600_WriteReg(uint8_t RegAddress, uint8_t Data);
    uint8_t AS5600_ReadReg(uint8_t RegAddress);
    uint8_t AS5600_GetID(void);
    //对外函数
    void AS5600_Init(I2C_HandleTypeDef *hi2c);
    void AS5600_GetData(uint16_t *RawAngle, float *Angle_deg, float *Angle_rad,float *FinalOutput,uint8_t filter_mode);

#ifdef __cplusplus
}
#endif

#endif //BSP_AS5600_H