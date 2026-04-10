// #include "main.h"
// #include <i2c.h>
//
// #define AS5600_ADDRESS		0x36		//AS5600的I2C从机地址
//
// HAL_StatusTypeDef AS5600_WaitEvent(I2C_HandleTypeDef *hi2c, uint32_t timeout)
// {
//     return HAL_I2C_GetState(hi2c);
// }
//
// /**
//   * 函    数：AS5600写寄存器
//   * 参    数：RegAddress 寄存器地址
//   * 参    数：Data 要写入寄存器的数据，范围：0x00~0xFF
//   * 返 回 值：HAL状态，HAL_OK表示成功，其他表示失败
//   */
// HAL_StatusTypeDef AS5600_WriteReg(uint8_t RegAddress, uint8_t Data)
// {
//     uint8_t buffer[2];
//     HAL_StatusTypeDef status;
//
//     buffer[0] = RegAddress;  // 寄存器地址
//     buffer[1] = Data;        // 要写入的数据
//
//     // 使用HAL_I2C_Master_Transmit发送数据
//     status = HAL_I2C_Master_Transmit(&hi2c2, AS5600_ADDRESS << 1, buffer, 2, 100);
//
//     return status;
// }
//
// /**
//   * 函    数：AS5600读寄存器
//   * 参    数：RegAddress 寄存器地址
//   * 返 回 值：读取寄存器的数据
//   */
// uint8_t AS5600_ReadReg(uint8_t RegAddress)
// {
//     uint8_t Data = 0;
//
//     // 步骤1：发送寄存器地址
//     HAL_I2C_Master_Transmit(&hi2c2, AS5600_ADDRESS << 1, &RegAddress, 1, 100);
//
//     // 步骤2：读取数据
//     HAL_I2C_Master_Receive(&hi2c2, AS5600_ADDRESS << 1, &Data, 1, 100);
//
//     return Data;
// }
//
//
// /**
//   * 函    数：AS5600获取ID号
//   * 参    数：无
//   * 返 回 值：AS5600的ID号
//   */
// uint8_t AS5600_GetID(void)
// {
//     return AS5600_ReadReg(0x00);		//返回AS5600 ID寄存器的值
// }
//
// /**
//   * 函    数：AS5600获取角度数据
//   * 参    数：RawAngle 原始角度值(0~4095)
//   * 参    数：Angle 实际角度值(0~360.0°)
//   * 返 回 值：无
//   */
// void AS5600_GetData(uint16_t *RawAngle, float *Angle)
// {
//     uint8_t DataH, DataL;								//定义数据高8位和低8位的变量
//
//     DataH = AS5600_ReadReg(0x0C);		//读取角度高8位
//     DataL = AS5600_ReadReg(0x0D);		//读取角度低8位
//     *RawAngle = ((uint16_t)DataH << 8) | DataL;						//数据拼接
//     *Angle = (float)*RawAngle * 360.0f / 4096.0f;
// }