#include "main.h"
#include "./Public/Debug.H"
#include "CH552.H"
#include "boot.h"
#include "font.h"
#include "key.h"
#include "led.h"
#include "motion.h"
#include "pov.h"
#include "timebase.h"

typedef enum { STANDBY = 0, READY } SystemState;

static SystemState system_state = STANDBY;

void LED_SelfTest(void) {
  UINT8 i;

  LED_Clear();
  LED_Update();

  for (i = 0; i < LED_COUNT; i++) {
    LED_SetPixel(i, 255, 0, 0);
    LED_Update();

    mDelaymS(50);
  }

  mDelaymS(200);

  LED_Clear();
  LED_Update();
}

void System_Start(void) {
  LED_SelfTest();

  system_state = READY;
}

void main(void) {
  UINT8 motion_trigger;

  CfgFsys();
  mDelaymS(5);

  Key_Init();

  // 检查烧录按键必须在key init之后
  if (Boot_Check()) {
    while (1) {
      ;
      // !unreachable()
    }
  }

  LED_Init();
  Timebase_Init();
  POV_Init();
  Motion_Init();
  LED_Clear();
  LED_Update();

  while (1) {
    switch (system_state) {
    case STANDBY:
      if (Key_IsPressed()) {
        System_Start();
      }
      break;
    case READY:
      POV_Update();
      motion_trigger = Motion_Update();
      if (motion_trigger) {
        POV_SetColumnInterval(Motion_GetColumnInterval());
        if (!POV_IsActive()) {
          POV_Start(0);
        }
      }
      break;

    default:
      system_state = STANDBY;
      break;
    }
  }
}
