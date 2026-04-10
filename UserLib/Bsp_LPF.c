/**
*   @file BSP_LPF.c
*   @brief 一阶低通滤波算法
*   @author Kena Zhong
*   @date 26-04-07
*   @version 1.0
*   @note
*/

#include "Bsp_LPF.h"

#include <string.h>

/**
 * @brief AS5600一阶低通滤波函数（带角度跳变保护）
 * @param
 * @return 滤波后的平滑角度值（单位：rad）
 * @note
 */

float AS5600_SetLPF(float new_value, float alpha) {
    static float output = 0.0f;

    float delta = ((new_value - output) > 0) ? (new_value - output) : -(new_value - output);

    if (delta > PI) {
        output = new_value;
    } else {
        output = alpha * new_value + (1.0f - alpha) * output;
    }

    return output;
};

/**
 * @brief AS5600中值滤波函数
 * @param
 * @return 滤波后的平滑角度值（单位：rad）
 * @note 5点中值滤波
 */
float AS5600_SetMedian(float new_value){
    static float buffer[MEDIAN_WINDOW_SIZE] = {0};
    static int index = 0;

    //更新缓冲区
    buffer[index] = new_value;
    index = (index + 1) % MEDIAN_WINDOW_SIZE;

    //复制并排序（冒泡排序）
    float sorted[MEDIAN_WINDOW_SIZE];
    memcpy(sorted, buffer, sizeof(buffer));
    for (int i = 0; i < MEDIAN_WINDOW_SIZE-1; i++) {
        for (int j = 0; j < MEDIAN_WINDOW_SIZE-i-1; j++) {
            if (sorted[j] > sorted[j+1]) {
                float temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
        }
    }


    // 返回中值
    return sorted[MEDIAN_WINDOW_SIZE/2];
}