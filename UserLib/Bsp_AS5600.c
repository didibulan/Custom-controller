/**
*   @file BSP_AS5600.c
*   @brief AS5600磁编码器BSP驱动
*   @author Kena Zhong
*   @date 26-04-07
*   @version 1.0
*   @note
*/

#include "Bsp_AS5600.h"

// 静态保存I2C句柄
static I2C_HandleTypeDef *s_AS5600_I2C;

/**
 * @brief  BSP初始化
 * @param  hi2c: I2C句柄
 * @retval None
 */
void AS5600_Init(I2C_HandleTypeDef *hi2c)
{
    s_AS5600_I2C = hi2c;
}

/**
  * 函    数：AS5600写寄存器
  * 参    数：RegAddress 寄存器地址
  * 参    数：Data 要写入寄存器的数据，范围：0x00~0xFF
  * 返 回 值：HAL状态，HAL_OK表示成功，其他表示失败
  */
void AS5600_WriteReg(uint8_t RegAddress, uint8_t Data)
{
    HAL_I2C_Mem_Write(s_AS5600_I2C, AS5600_ADDRESS << 1, RegAddress, I2C_MEMADD_SIZE_8BIT, &Data, 1, 100);
}

/**
  * 函    数：AS5600读寄存器
  * 参    数：RegAddress 寄存器地址
  * 返 回 值：读取寄存器的数据
  */
uint8_t AS5600_ReadReg(uint8_t RegAddress)
{
    uint8_t data=0;
    HAL_I2C_Mem_Read(s_AS5600_I2C, AS5600_ADDRESS << 1, RegAddress, I2C_MEMADD_SIZE_8BIT, &data,1,100);
    return data;
}

/**
  * 函    数：AS5600获取ID号
  * 参    数：无
  * 返 回 值：AS5600的ID号
  */
uint8_t AS5600_GetID(void)
{
    return AS5600_ReadReg(0x00);		//返回AS5600 ID寄存器的值
}

/**
  * 函    数：AS5600获取角度数据
  * 参    数：RawAngle 原始角度值(0~4095)
  * 参    数：Angle 实际角度值(0~360.0°)
  * 返 回 值：无
  */

void AS5600_GetData(uint16_t *RawAngle, float *Angle_deg, float *Angle_rad,float *FinalOutput,uint8_t filter_mode)
{
    uint8_t DataH, DataL;								//定义数据高8位和低8位的变量

    DataH = AS5600_ReadReg(AS5600_REG_RAW_ANGLE_H);		//读取角度高8位
    DataL = AS5600_ReadReg(AS5600_REG_RAW_ANGLE_L);		//读取角度低8位
    *RawAngle = ((uint16_t)DataH << 8) | DataL;			//数据拼接

    //角度制
    *Angle_deg = (float)*RawAngle * AS5600_ANGLE_TO_DEGREE / AS5600_ANGLE_MAX_VAL;//360.0f / 4096.0f
    //弧度制
    *Angle_rad = (float)*RawAngle * 2 * PI / AS5600_ANGLE_MAX_VAL;

    switch(filter_mode)
    {
    case FILTER_MODE_NONE:
        *FinalOutput = AS5600_SetLPF(*Angle_rad, 0.2f);
        break;

    case FILTER_MODE_LPF:
        *FinalOutput = AS5600_SetMedian(*Angle_rad);
        break;

    default:
        *FinalOutput = *Angle_rad;
        break;
    }

    // *FinalOutput = AS5600_SetLPF(*Angle_rad, 0.2f);
}