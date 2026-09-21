#ifndef __BOOT_H__
#define __BOOT_H__

#include "CH552.H"

/* CH551G 内置 ISP Bootloader 入口 */
#define CH551_BOOT_ADDR 0x3800

/* 你的启动按钮 */
#define BOOT_KEY P1_4

/*
 * 检查上电时是否按住 Boot 按钮。
 *
 * 返回：
 *   1 = 进入 ISP
 *   0 = 正常启动 APP
 */
UINT8 Boot_CheckKey(void);

/*
 * 跳转到 CH551 内置 ISP Bootloader
 */
void Boot_JumpToISP(void);

#endif