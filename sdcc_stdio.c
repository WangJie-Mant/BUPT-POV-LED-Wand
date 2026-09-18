#include <stdio.h>
#include "CH552.H"
#include "Public/Debug.H"

/* SDCC's printf calls this hook.  The Keil library supplied its own PUTCHAR
 * module, so the original firmware did not need to define it. */
int putchar(int character) {
  CH554UART0SendByte((UINT8)character);
  return character;
}
