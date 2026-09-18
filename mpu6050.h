#ifndef __MPU6050_H__
#define __MPU6050_H__

#include "CH552.H"

//typedef int16_t INT16

#define MPU6050_ADDR 0x68

#define MPU6050_WHO_AM_I 0x75
#define MPU6050_PWR_MGMT1 0x6B

#define MPU6050_ACCEL_XOUT_H 0x3B
#define MPU6050_ACCEL_XOUT_L 0x3C

#define MPU6050_ACCEL_YOUT_H 0x3D
#define MPU6050_ACCEL_YOUT_L 0x3E

#define MPU6050_ACCEL_ZOUT_H 0x3F
#define MPU6050_ACCEL_ZOUT_L 0x40

    void MPU6050_Init(void);
UINT8 MPU6050_ReadReg(UINT8 reg);
void MPU6050_WriteReg(UINT8 reg, UINT8 dat);

void MPU6050_ReadAccel(INT16 *ax, INT16 *ay, INT16 *az);

#endif
