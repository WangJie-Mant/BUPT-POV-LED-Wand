#include "CH552.h"
#include "mpu6050.h"
#include "Public/Debug.H"
#include "i2c.h"

static INT16 xdata gyro_x;
static INT16 xdata gyro_y;
static INT16 xdata gyro_z;
static UINT8 xdata gyro_buffer[6];

void MPU6050_WriteReg(UINT8 reg, UINT8 dat) {
  I2C_Start();
  I2C_WriteByte((UINT8)(MPU6050_ADDR << 1));

  I2C_WriteByte(reg);
  I2C_WriteByte(dat);
  I2C_Stop();
}

UINT8 MPU6050_ReadReg(UINT8 reg) {
  UINT8 dat;

  I2C_Start();
  I2C_WriteByte((UINT8)(MPU6050_ADDR << 1));
  I2C_WriteByte(reg);

  I2C_Start();

  I2C_WriteByte((UINT8)((MPU6050_ADDR << 1) | 1));

  dat = I2C_ReadByte(0);

  I2C_Stop();

  return dat;
}

void MPU6050_Init() {
  MPU6050_WriteReg(MPU6050_PWR_MGMT1, 0x01);

  mDelaymS(30);

  MPU6050_WriteReg(MPU6050_CONFIG, 0x03);
  MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x00);
  MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x04);
}

void MPU6050_ReadGyro(void) {
  I2C_Start();
  I2C_WriteByte((UINT8)(MPU6050_ADDR << 1));
  I2C_WriteByte(MPU6050_GYRO_XOUT_H);
  I2C_Start();
  I2C_WriteByte((UINT8)((MPU6050_ADDR << 1) | 1));
  I2C_ReadBytes(gyro_buffer, 6);
  I2C_Stop();

  gyro_x = ((INT16)gyro_buffer[0] << 8) | gyro_buffer[1];
  gyro_y = ((INT16)gyro_buffer[2] << 8) | gyro_buffer[3];
  gyro_z = ((INT16)gyro_buffer[4] << 8) | gyro_buffer[5];
}

INT16 MPU6050_GetGyroX(void) { return gyro_x; }
INT16 MPU6050_GetGyroY(void) { return gyro_y; }
INT16 MPU6050_GetGyroZ(void) { return gyro_z; }
