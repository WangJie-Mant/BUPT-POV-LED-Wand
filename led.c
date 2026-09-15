#include "led.h"
#include "./Public/Debug.H"
#include "CH552.H"
#include "Public/CH554.H"
#include "SPI.H"
#include "stdio.h"

static LED_Color led_buffer[LED_COUNT];

void LED_Init(void) {

  UINT8 i;

  CfgFsys();

  mDelaymS(5);

  mInitSTDIO();

  printf("start ...\n");

  // 配置寄存器对应位为0对应推挽输出，那应该是P1.5对应0，也就是0x11011111
  // bpwm1是0x20，也就是掩码为0x00100000，设置方法就是
  P1_MOD_OC &= ~bPWM1;

  P1_DIR_PU |= bPWM1;

  // 使用SPI输出
  // SPI初始化
  P1_5 = 0;

  SPIMasterModeSet(3);

  SPI_CK_SET(4);

  // 清空当前的ledbuffer
  for (i = 0; i < LED_COUNT; i++) {
    led_buffer[i].r = 0;
    led_buffer[i].g = 0;
    led_buffer[i].b = 0;
  }
  //   SetPWMClk(4); // 时钟配置，Fsys/256/4分频
  //   //   ForceClearPWMFIFO(); // 强制清除PWM FIFO和COUNT
  //   //   CancleClearPWMFIFO(); // 取消清除PWM FIFO和COUNT

  //   PWM1OutEnable();

  //   PWM1OutPolarHighAct(); // PWM1输出默认低，高有效

  //   PWM_DATA1 = 0x00;
}

static void WS2812_SendByte(unsigned char dat) {
  UINT8 i;
  UINT8 encoded;

  encoded = 0;

  for (i = 0; i < 8; i++) {
    encoded <<= 3;

    if (dat & 0x80) {
      // 这一位是1
      encoded |= 0x06; // 110
    } else {
      // 这一位是0
      encoded |= 0x04; // 100
    }
    dat <<= 1;
  }

  CH554SPIMasterWrite((UINT8)(encoded >> 16));
  CH554SPIMasterWrite((UINT8)(encoded >> 8));
  CH554SPIMasterWrite((UINT8)(encoded & 0xFF));
}

void LED_SetPixel(unsigned char index, unsigned char r, unsigned char g,
                  unsigned char b) {
  if (index >= LED_COUNT) {
    return;
  }

  led_buffer[index].r = r;
  led_buffer[index].g = g;
  led_buffer[index].b = b;
}

void LED_Update() {
  UINT8 i;

  for (i = 0; i < LED_COUNT; i++) {
    // 注意WS2812的颜色顺序
    WS2812_SendByte(led_buffer[i].g);
    WS2812_SendByte(led_buffer[i].r);
    WS2812_SendByte(led_buffer[i].b);
  }

  P1_5 = 0;
  mDelayuS(50);
}

void LED_SetAll(unsigned char r, unsigned char g, unsigned char b) {
  UINT8 i;

  for (i = 0; i < LED_COUNT; i++) {
    LED_SetPixel(i, r, g, b);
  }
}

void LED_Clear() { LED_SetAll(0, 0, 0); }
