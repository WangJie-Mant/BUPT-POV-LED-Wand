#ifndef POV_WAND_SDCC_COMPAT_H
#define POV_WAND_SDCC_COMPAT_H

/*
 * Compatibility layer for compiling the original Keil C51 sources with
 * SDCC.  The device definitions are from the CH554 SDCC port in
 * .sdcc-sdk/include, retained locally for reproducible SDCC builds.
 */
#define bit   __bit
#define data  __data
#define idata __idata
#define pdata __pdata
#define xdata __xdata
#define code  __code

#include ".sdcc-sdk/include/ch554_datatypes.h"
#include ".sdcc-sdk/include/ch554.h"

#ifndef INT16
typedef signed short INT16;
#endif

/* The upstream SDCC header exposes the peripheral pin aliases used by its
 * examples.  The original project also addresses the raw P1 pin bits. */
SBIT(P1_0, 0x90, 0);
SBIT(P1_1, 0x90, 1);
SBIT(P1_2, 0x90, 2);
SBIT(P1_3, 0x90, 3);
SBIT(P1_4, 0x90, 4);
SBIT(P1_5, 0x90, 5);
SBIT(P1_6, 0x90, 6);
SBIT(P1_7, 0x90, 7);
SBIT(P3_0, 0xB0, 0);
SBIT(P3_1, 0xB0, 1);
SBIT(P3_2, 0xB0, 2);
SBIT(P3_3, 0xB0, 3);
SBIT(P3_4, 0xB0, 4);
SBIT(P3_5, 0xB0, 5);
SBIT(P3_6, 0xB0, 6);
SBIT(P3_7, 0xB0, 7);

/* The project headers include Keil device headers by their original names.
 * Their definitions have already been supplied above for SDCC. */
#define __CH552_H__

#ifndef BOOL
typedef __bit BOOL;
#endif

#endif
