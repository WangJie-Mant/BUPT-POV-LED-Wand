#ifndef __LED_H__
#define __LED_H__

#define LED_COUNT 16

typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} LED_Color;

void LED_Init(void);

void LED_SetPixel(unsigned char index, unsigned char r, unsigned char g,
                  unsigned char b);

void LED_SetAll(unsigned char r, unsigned char g, unsigned char b);

void LED_Clear(void);
void LED_Update(void);

#endif