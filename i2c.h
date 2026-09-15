#ifndef __I2C_H__
#define __I2C_H__

#include "CH552.H"
#include "GPIO.H"

#define I2C_SDA_PIN P1_0
#define I2C_SCL_PIN P1_1

void I2C_Init(void);

void I2C_Start(void);
void I2C_Stop(void);

UINT8 I2C_WriteByte(UINT8 dat);
UINT8 I2C_ReadByte(UINT8 ack);
void I2C_ReadBytes(UINT8 *buf, UINT8 len);

#endif
