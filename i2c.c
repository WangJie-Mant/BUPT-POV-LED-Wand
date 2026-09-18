#include "CH552.H"
#include "i2c.h"


static void I2C_Delay(void) {
  UINT8 i;

  for (i = 0; i < 5; i++) {
    ;
  }
}

static void I2C_SDA_Low(void) { I2C_SDA_PIN = 0; }

static void I2C_SDA_High(void) { I2C_SDA_PIN = 1; }

static void I2C_SCL_Low(void) { I2C_SCL_PIN = 0; }

static void I2C_SCL_High(void) { I2C_SCL_PIN = 1; }

void I2C_Init(void) {
  Port1Cfg(3, 0);
  Port1Cfg(3, 1);

  I2C_SDA_High();
  I2C_SCL_High();

  I2C_Delay();
}

void I2C_Start(void) {
  I2C_SDA_High();

  I2C_SCL_High();

  I2C_Delay();

  // start

  I2C_SDA_Low();
  I2C_Delay();

  I2C_SCL_Low();
  I2C_Delay();
}

void I2C_Stop(void) {
  I2C_SDA_Low();

  I2C_SCL_High();

  I2C_Delay();

  // stop

  I2C_SDA_High();
  I2C_Delay();
}

UINT8 I2C_WriteByte(UINT8 dat) {
  UINT8 i;
  UINT8 ack;

  for (i = 0; i < 8; i++) {
    if (dat & 0x80) {
      I2C_SDA_High();
    } else {
      I2C_SDA_Low();
    }

    I2C_Delay();

    I2C_SCL_High();

    I2C_Delay();

    I2C_SCL_Low();

    I2C_Delay();

    dat <<= 1;
  }

  I2C_SDA_High();
  I2C_Delay();
  I2C_SCL_High();
  I2C_Delay();

  ack = I2C_SDA_PIN; // 0 expected

  I2C_SCL_Low();
  I2C_Delay();

  return ack;
}

UINT8 I2C_ReadByte(UINT8 ack) {
  UINT8 i;
  UINT8 dat = 0;

  I2C_SDA_High();

  for (i = 0; i < 8; i++) {
    dat <<= 1;

    I2C_SCL_High();
    I2C_Delay();

    if (I2C_SDA_PIN) {
      dat |= 0x01;
    }

    I2C_SCL_Low();
    I2C_Delay();
  }

  if (ack) {
    I2C_SDA_Low();
  } else {
    I2C_SDA_High();
  }

  I2C_Delay();

  I2C_SCL_High();
  I2C_Delay();

  I2C_SCL_Low();
  I2C_Delay();

  I2C_SDA_High();
  I2C_Delay();

  return dat;
}

void I2C_ReadBytes(UINT8 *buf, UINT8 len) {
  UINT8 i;

  for (i = 0; i < len; i++) {
    if (i == (len - 1)) {
      buf[i] = I2C_ReadByte(0);
    } else {
      buf[i] = I2C_ReadByte(1);
    }
  }
}