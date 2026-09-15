#include "mpu6050.h"
#include "Public/Debug.H"
#include "i2c.h"

void MPU6050_WriteReg(UINT8 reg, UINT8 dat) {
  I2C_Start();
  I2C_WriteByte(MPU6050_ADDR << 1);

  I2C_WriteByte(reg);
  I2C_WriteByte(dat);
  I2C_Stop();
}

UINT8 MPU6050_ReadReg(UINT8 reg) {
  UINT8 dat;

  I2C_Start();
  I2C_WriteByte(MPU6050_ADDR << 1);
  I2C_WriteByte(reg);

  I2C_Start();

  I2C_WriteByte((MPU6050_ADDR << 1) | 1);

  dat = I2C_ReadByte(0);

  I2C_Stop();

  return dat;
}

void MPU6050_Init() {
  MPU6050_WriteReg(MPU6050_PWR_MGMT1, 0x00);

  mDelaymS(10);
}

void MPU6050_ReadAccel(INT16 *ax, INT16 *ay, INT16 *az) {
  UINT8 buf[6];

  I2C_Start();

  I2C_WriteByte(MPU6050_ADDR << 1);

  I2C_WriteByte(MPU6050_ACCEL_XOUT_H);

  I2C_Start();

  I2C_WriteByte((MPU6050_ADDR << 1) | 1);

  I2C_ReadBytes(buf, 6);

  I2C_Stop();

  *ax = ((INT16)buf[0] << 8) | buf[1];
  *ay = ((INT16)buf[2] << 8) | buf[3];
  *az = ((INT16)buf[4] << 8) | buf[5];
}