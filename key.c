#include "key.h"
#include "./Public/Debug.H"
#include "CH552.H"
#include "GPIO.H"

void Key_Init() {
  // 配置按键引脚P1.4为输入模式
  Port1Cfg(3, 4);
}

UINT8 Key_IsPressed() { return (KEY_PIN == PRESSED); }

UINT8 Key_GetPress() {
  static UINT8 last_state = RELEASED;

  UINT8 current;

  current = KEY_PIN;

  if ((last_state == RELEASED) && (current == PRESSED)) {
    mDelaymS(10);
    if (KEY_PIN == PRESSED) {
      last_state = PRESSED;
      return 1;
    }
  }

  if (current == RELEASED) {
    last_state = RELEASED;
  }

  return 0;
}