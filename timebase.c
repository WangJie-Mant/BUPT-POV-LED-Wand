#include "timebase.h"

void Timebase_Init(void) {
  TMOD = (TMOD & 0xF0) | 0x01;
  TH0 = 0;
  TL0 = 0;
  TF0 = 0;
  TR0 = 1;
}

UINT16 Timebase_NowUs(void) {
  UINT8 high_first;
  UINT8 high_second;
  UINT8 low;

  do {
    high_first = TH0;
    low = TL0;
    high_second = TH0;
  } while (high_first != high_second);

  return ((UINT16)high_first << 8) | low;
}
