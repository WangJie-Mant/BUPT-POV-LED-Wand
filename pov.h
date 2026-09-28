#ifndef __POV_H__
#define __POV_H__

#include "CH552.H"

void POV_Init(void);
void POV_Start(UINT8 group);
void POV_Update(void);
void POV_SetColumnInterval(UINT16 interval_us);
UINT8 POV_IsActive(void);

#endif
