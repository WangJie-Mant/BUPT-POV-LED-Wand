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

#define SYSTEM_STANDBY 0
#define SYSTEM_READY 1

static UINT8 data system_state = SYSTEM_STANDBY;
static UINT8 data selected_group;

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

  system_state = SYSTEM_READY;
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
  selected_group = 0;
  LED_Clear();
  LED_Update();

  while (1) {
    switch (system_state) {
    case SYSTEM_STANDBY:
      if (Key_GetPress()) {
        System_Start();
      }
      break;
    case SYSTEM_READY:
      POV_Update();
      if (Key_GetPress()) {
        selected_group++;
        if (selected_group >= FONT_GROUP_COUNT) {
          selected_group = 0;
        }
      }
      motion_trigger = Motion_Update();
      if (motion_trigger) {
        POV_SetColumnInterval(Motion_GetColumnInterval());
        if (!POV_IsActive()) {
          POV_Start(selected_group);
        }
      }
      break;

    default:
      system_state = SYSTEM_STANDBY;
      break;
    }
  }
}
