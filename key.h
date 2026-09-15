#ifndef __KEY_H__
#define __KEY_H__

#include "CH552.H"

#define KEY_PORT P1
#define KEY_PIN P1_4

#define PRESSED 0
#define RELEASED 1

void Key_Init(void);

UINT8 Key_IsPressed(void);

UINT8 Key_GetPress(void);

#endif
