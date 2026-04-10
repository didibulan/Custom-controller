/**
*   @file BSP_AS5600.h
*   @brief AS5600磁编码器BSP驱动
*   @author Kena Zhong
*   @date 26-04-07
*   @version 1.0
*   @note
*/
#ifndef BSP_LPF_H
#define BSP_LPF_H

#include "stm32f4xx_hal.h"

#define FILTER_MODE_NONE        0                // 不滤波
#define FILTER_MODE_LPF         1                // 一阶低通滤波
#define FILTER_MODE_MEDIAN      2                // 中值滤波

#define MEDIAN_WINDOW_SIZE      5               // 中值滤波窗口大小

#define PI                      3.1415926535f    // 圆周率

//滤波算法
float AS5600_SetLPF(float new_value, float alpha) ;
float AS5600_SetMedian(float new_value);

#endif //BSP_LPF_H