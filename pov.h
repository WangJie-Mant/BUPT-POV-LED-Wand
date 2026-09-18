#ifndef __POV_H__
#define __POV_H__

#include "CH552.H"

void POV_ShowColumn(UINT16 column, UINT8 r, UINT8 g, UINT8 b);

void POV_ShowGlyph(const UINT8 code *font, UINT8 r, UINT8 g, UINT8 b);

void POV_ShowText(const UINT8 code * code text[], UINT8 length, UINT8 r, UINT8 g, UINT8 b);

#endif
