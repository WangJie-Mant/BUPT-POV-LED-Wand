#include "CH552.H"
#include "./Public/Debug.H"
#include "key.h"
#include "GPIO.H"
#include "timebase.h"

#define KEY_DEBOUNCE_US 10000

static UINT8 data stable_state = RELEASED;
static UINT8 data candidate_state = RELEASED;
static UINT16 data candidate_since_us;

void Key_Init() {
  // 配置按键引脚P1.4为输入模式
  Port1Cfg(3, 4);
  stable_state = RELEASED;
  candidate_state = RELEASED;
  candidate_since_us = 0;
}

UINT8 Key_IsPressed() { return (KEY_PIN == PRESSED); }

UINT8 Key_GetPress() {
  UINT8 current;
  UINT16 now;

  current = KEY_PIN;
  now = Timebase_NowUs();

  if (current != candidate_state) {
    candidate_state = current;
    candidate_since_us = now;
    return 0;
  }

  if (stable_state != candidate_state &&
      (UINT16)(now - candidate_since_us) >= KEY_DEBOUNCE_US) {
    stable_state = candidate_state;
    if (stable_state == PRESSED) {
      return 1;
    }
  }

  return 0;
}
