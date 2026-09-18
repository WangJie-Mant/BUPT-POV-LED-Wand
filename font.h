#ifndef __FONT_H__
#define __FONT_H__

#include "CH552.H"

#define FONT_WIDTH 16
#define FONT_HEIGHT 16
#define FONT_BYTES 32

extern const UINT8 code font_lao[32];
extern const UINT8 code font_bei[32];
extern const UINT8 code font_jing[32];

extern const UINT8 code * code text[];

UINT16 Font_GetColumn(const UINT8 code *font, UINT8 column);

#endif
