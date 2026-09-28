#ifndef __FONT_H__
#define __FONT_H__

#include "CH552.H"

#define FONT_WIDTH 16
#define FONT_HEIGHT 16
#define FONT_BYTES 32

#define FONT_ID_LAO 0
#define FONT_ID_BEI 1
#define FONT_ID_JING 2

#define FONT_GROUP_COUNT 3

extern const UINT8 code font_lao[32];
extern const UINT8 code font_bei[32];
extern const UINT8 code font_jing[32];

UINT16 Font_GetColumn(const UINT8 code *font, UINT8 column);
UINT16 Font_GetColumnById(UINT8 glyph_id, UINT8 column);
UINT8 Font_GetGroupGlyph(UINT8 group, UINT8 position);

#endif
