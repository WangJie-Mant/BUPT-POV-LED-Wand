#ifndef __BOOT_H__
#define __BOOT_H__

#include "CH552.H"

#define BOOT_KEY P1_4

UINT8 Boot_CheckKey(void);

void Boot_JumpToISP(void);

UINT8 Boot_Check(void);

#endif