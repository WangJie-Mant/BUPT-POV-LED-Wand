#include "boot.h"
#include "./Public/Debug.H"

/*
 * 禁止当前 APP 的外设和中断，
 * 然后直接跳转到 CH551 内部 ISP Bootloader。
 */
void Boot_JumpToISP(void) {
  /*
   * 关闭总中断
   */
  EA = 0;

  /*
   * 关闭 USB 中断
   */
  USB_INT_EN = 0;

  /*
   * 停止 Timer0 / Timer1 / Timer2
   */
  TR0 = 0;
  TR1 = 0;
  TR2 = 0;

  /*
   * 关闭 Timer 中断
   */
  ET0 = 0;
  ET1 = 0;
  ET2 = 0;

  /*
   * 关闭 UART 接收
   */
  REN = 0;

  /*
   * 清除 USB 状态
   *
   * 如果你的 CH551.H 中没有 USB_CTRL，
   * 可以先删除这一行。
   */
  USB_CTRL = 0x06;

  /*
   * 跳转到 WCH 内置 ISP Bootloader
   *
   * 不能写成普通 C 函数调用，
   * 必须生成 LJMP。
   */
  __asm LJMP 0x3800 __endasm;

  /*
   * 理论上不会执行到这里
   */
  while (1)
    ;
}

/*
 * 检查 Boot 按钮。
 *
 * P3.2：
 *
 *        未按 = 1
 *        按下 = 0
 */
UINT8 Boot_CheckKey(void) {
  /*
   * 第一次检测
   */
  if (BOOT_KEY == 0) {
    /*
     * 简单消抖
     */
    mDelaymS(20);

    /*
     * 第二次确认
     */
    if (BOOT_KEY == 0) {
      return 1;
    }
  }

  return 0;
}