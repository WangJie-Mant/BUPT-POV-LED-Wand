#include "boot.h"
#include "CH552.H"
#include "Public/Debug.H"
#include "key.h"

UINT8 Boot_CheckKey() {
  if (BOOT_KEY == 0) {
    mDelaymS(20);
    if (BOOT_KEY == 0) {
      return 1;
    }
  }

  return 0;
}

void Boot_JumpToISP() {
  typedef void (*pTaskFn)(void);

  pTaskFn tasksArr[1];

  EA = 0;
  TR0 = 0;
  TR1 = 0;
  TR2 = 0;
  ET1 = 0;
  ET2 = 0;
  ET0 = 0;

  tasksArr[0] = (pTaskFn)BOOT_LOAD_ADDR;

  (tasksArr[0])();

  while (1) {
    ;
    // !unreachable()
  }
}

UINT8 Boot_Check() {
  Key_Init();

  if (Boot_CheckKey()) {
    Boot_JumpToISP();

    // !unreachable()
    return 1;
  }

  return 0;
}