#include "./Public/Debug.H"
#include "CH552.H"
#include "key.h"
#include "led.h"


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

  system_state = STANDBY;
}

void main() {
  while (1) {
  }
}

void LED_ShowText(const unsigned char *text, unsigned char length) {}