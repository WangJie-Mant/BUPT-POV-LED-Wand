#include "motion.h"
#include "i2c.h"
#include "mpu6050.h"
#include "Public/Debug.H"
#include "timebase.h"

#define MOTION_CALIBRATION_SAMPLES 16
#define MOTION_SAMPLE_PERIOD_US 5000
#define MOTION_START_RAW 10480
#define MOTION_REARM_RAW 5240
#define MOTION_COLUMN_MAX_US 3500

static INT16 xdata gyro_bias_x;
static INT16 xdata gyro_bias_y;
static INT16 xdata gyro_bias_z;
static UINT16 xdata filtered_speed_raw;
static UINT16 xdata column_interval_us;
static UINT16 xdata last_sample_us;
static UINT8 xdata motion_armed;
static INT32 xdata calibration_sum_x;
static INT32 xdata calibration_sum_y;
static INT32 xdata calibration_sum_z;

static UINT16 Motion_AbsDelta(INT16 sample, INT16 bias) {
  INT32 delta;

  delta = (INT32)sample - bias;
  if (delta < 0) {
    delta = -delta;
  }
  return (UINT16)delta;
}

static UINT16 Motion_Max3(UINT16 x, UINT16 y, UINT16 z) {
  UINT16 maximum = x;

  if (y > maximum) {
    maximum = y;
  }
  if (z > maximum) {
    maximum = z;
  }

  return maximum;
}

static UINT16 Motion_IntervalFromSpeed(UINT16 speed_raw) {
  if (speed_raw >= 60000U) {
    return 1100;
  }
  if (speed_raw >= 50000U) {
    return 1300;
  }
  if (speed_raw >= 40000U) {
    return 1500;
  }
  if (speed_raw >= 30000U) {
    return 1800;
  }
  if (speed_raw >= 22000U) {
    return 2200;
  }
  if (speed_raw >= 16000U) {
    return 2800;
  }

  return MOTION_COLUMN_MAX_US;
}

void Motion_Init(void) {
  UINT8 i;

  I2C_Init();
  MPU6050_Init();

  calibration_sum_x = 0;
  calibration_sum_y = 0;
  calibration_sum_z = 0;

  for (i = 0; i < MOTION_CALIBRATION_SAMPLES; i++) {
    MPU6050_ReadGyro();
    calibration_sum_x += MPU6050_GetGyroX();
    calibration_sum_y += MPU6050_GetGyroY();
    calibration_sum_z += MPU6050_GetGyroZ();
    mDelaymS(2);
  }

  gyro_bias_x = (INT16)(calibration_sum_x / MOTION_CALIBRATION_SAMPLES);
  gyro_bias_y = (INT16)(calibration_sum_y / MOTION_CALIBRATION_SAMPLES);
  gyro_bias_z = (INT16)(calibration_sum_z / MOTION_CALIBRATION_SAMPLES);
  filtered_speed_raw = 0;
  column_interval_us = 1200;
  last_sample_us = Timebase_NowUs();
  motion_armed = 1;
}

UINT8 Motion_Update(void) {
  UINT16 now;
  UINT16 speed_raw;

  now = Timebase_NowUs();
  if ((UINT16)(now - last_sample_us) < MOTION_SAMPLE_PERIOD_US) {
    return 0;
  }
  last_sample_us = now;

  MPU6050_ReadGyro();
  speed_raw = Motion_Max3(Motion_AbsDelta(MPU6050_GetGyroX(), gyro_bias_x),
                         Motion_AbsDelta(MPU6050_GetGyroY(), gyro_bias_y),
                         Motion_AbsDelta(MPU6050_GetGyroZ(), gyro_bias_z));

  filtered_speed_raw = filtered_speed_raw - (filtered_speed_raw >> 2) +
                       (speed_raw >> 2);

  if (filtered_speed_raw > 0) {
    column_interval_us = Motion_IntervalFromSpeed(filtered_speed_raw);
  }

  if (filtered_speed_raw <= MOTION_REARM_RAW) {
    motion_armed = 1;
  }

  if (motion_armed && filtered_speed_raw >= MOTION_START_RAW) {
    motion_armed = 0;
    return 1;
  }

  return 0;
}

UINT16 Motion_GetColumnInterval(void) { return column_interval_us; }
