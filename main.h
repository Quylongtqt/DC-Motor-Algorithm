#ifndef _MAIN_H_
#define _MAIN_H_

#include "stm32f10x.h"
#include <stdio.h> 
#include <stdint.h> 
#include "system_timetick.h"
#include "driver.h"
#include "pid.h"                       /* Model's header file */
#include "rtwtypes.h"                  /* MathWorks types */

void rt_OneStep(void);

#endif
