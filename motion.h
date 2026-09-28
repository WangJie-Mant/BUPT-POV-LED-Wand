#ifndef __MOTION_H__
#define __MOTION_H__

#include "CH552.H"

void Motion_Init(void);
UINT8 Motion_Update(void);
UINT16 Motion_GetColumnInterval(void);

#endif
