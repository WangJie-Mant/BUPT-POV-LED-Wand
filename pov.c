#include "CH552.H"
#include "font.h"
#include "led.h"
#include "Public/Debug.H"
#include "pov.h"
#include "timebase.h"

#define POV_DEFAULT_COLUMN_US 1200
#define POV_SPACE_COLUMNS 2
#define POV_GLYPHS_PER_GROUP 3

static UINT8 data pov_active;
static UINT8 data pov_group;
static UINT8 data pov_glyph;
static UINT8 data pov_column;
static UINT16 data pov_interval_us;
static UINT16 data pov_next_column_us;

static void POV_ShowColumn(UINT16 column, UINT8 r, UINT8 g, UINT8 b) {
  UINT8 i;

  for (i = 0; i < LED_COUNT; i++) {
    if (column & ((UINT16)1 << i)) {
      LED_SetPixel(i, r, g, b);
    } else {
      LED_SetPixel(i, 0, 0, 0);
    }
  }

  LED_Update();
}

void POV_Init(void) {
  pov_active = 0;
  pov_interval_us = POV_DEFAULT_COLUMN_US;
}

void POV_Start(UINT8 group) {
  if (pov_active) {
    return;
  }

  pov_group = group;
  pov_glyph = 0;
  pov_column = 0;
  pov_next_column_us = Timebase_NowUs();
  pov_active = 1;
}

void POV_SetColumnInterval(UINT16 interval_us) {
  pov_interval_us = interval_us;
}

UINT8 POV_IsActive(void) { return pov_active; }

void POV_Update(void) {
  UINT16 now;
  UINT16 glyph_data;
  UINT8 glyph_id;

  if (!pov_active) {
    return;
  }

  now = Timebase_NowUs();
  if ((INT16)(now - pov_next_column_us) < 0) {
    return;
  }

  if (pov_column < FONT_WIDTH) {
    glyph_id = Font_GetGroupGlyph(pov_group, pov_glyph);
    glyph_data = Font_GetColumnById(glyph_id, pov_column);
    POV_ShowColumn(glyph_data, 255, 0, 0);
  } else {
    POV_ShowColumn(0, 0, 0, 0);
  }

  pov_column++;
  if (pov_column >= (FONT_WIDTH + POV_SPACE_COLUMNS)) {
    pov_column = 0;
    pov_glyph++;
    if (pov_glyph >= POV_GLYPHS_PER_GROUP) {
      pov_active = 0;
      LED_Clear();
      LED_Update();
      return;
    }
  }

  pov_next_column_us = now + pov_interval_us;
}
