#include "CH552.H"
#include "font.h"
#include "led.h"
#include "Public/Debug.H"
#include "pov.h"

#define POV_COLUMN_DELAY_US 800
#define POV_SPACE_COLUMNS 2

void POV_ShowColumn(UINT16 column, UINT8 r, UINT8 g, UINT8 b) {
  UINT8 i;

  for (i = 0; i < LED_COUNT; i++) {
    if (column & ((UINT16)1 << i)) {
      LED_SetPixel(i, r, g, b);
    } else {
      LED_SetPixel(i, 0, 0, 0);
    }
  }

  LED_Update();

  mDelayuS(POV_COLUMN_DELAY_US);
}

void POV_ShowGlyph(const UINT8 code *font, UINT8 r, UINT8 g, UINT8 b) {
  UINT8 column;
  UINT16 glyph_data;

  for (column = 0; column < FONT_WIDTH; column++) {
    glyph_data = Font_GetColumn(font, column);
    POV_ShowColumn(glyph_data, r, g, b);
  }

  POV_ShowColumn(0, 0, 0, 0);
  POV_ShowColumn(0, 0, 0, 0);
}

void POV_ShowText(const UINT8 code * code text[], UINT8 length, UINT8 r, UINT8 g,
                  UINT8 b) {

  UINT8 i;

  for (i = 0; i < length; i++) {
    POV_ShowGlyph(text[i], r, g, b);
  }
}
