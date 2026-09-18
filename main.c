#include "main.h"
#include "CH552.H"
#include "./Public/Debug.H"
#include "font.h"
#include "key.h"
#include "led.h"
#include "pov.h"
#include "shake.h"

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

  CfgFsys();
  mDelaymS(5);

  LED_Init();
  Shake_Init();
  LED_Clear();
  LED_Update();

  Key_Init();

  while (1) {
    switch (system_state) {
    case STANDBY:
      if (Key_IsPressed()) {
        System_Start();
      }
      break;
    case READY:
      if (Shake_Detect()) {
        POV_ShowText(text, 3, 255, 0, 0);
      }
      break;

    default:
      system_state = STANDBY;
      break;
    }
  }
}
