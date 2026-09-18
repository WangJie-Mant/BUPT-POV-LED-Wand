#include "shake.h"
#include "CH552.H"
#include "GPIO.H"
#include "Public/Debug.H"

void Shake_Init() { Port3Cfg(2, 2); }

UINT8 Shake_Detect() {
  static UINT8 shaked = 1;

  if (shaked) {
    if (P3_2 == 0) {
      mDelaymS(10);

      if (P3_2 == 0) {
        shaked = 0;
        return 1;
      }
    }
  } else {
    if (P3_2 == 1) {
      shaked = 1;
    }
  }

  return 0;
}