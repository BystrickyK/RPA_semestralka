<<<<<<< HEAD
/*******************************************/
/*     FILE GENERATED BY iec2c             */
/* Editing this file is not recommended... */
/*******************************************/

#include "iec_std_lib.h"

// RESOURCE RES0

extern unsigned long long common_ticktime__;

#include "accessor.h"
#include "POUS.h"

#include "Config0.h"

#include "POUS.c"

BOOL TASK0;
BOOL WDT_CLOCK;
SUPERSTATE_MACHINE RES0__SSM;
#define SSM RES0__SSM
SERVICE RES0__SVC;
#define SVC RES0__SVC
EMERIGENCY RES0__EM;
#define EM RES0__EM
AUTOPRODUCTION RES0__AP;
#define AP RES0__AP
MANUALPRODUCTION RES0__MP;
#define MP RES0__MP
FAILURE RES0__FAIL;
#define FAIL RES0__FAIL
WATCHDOGTIMER RES0__WDTIMER;
#define WDTIMER RES0__WDTIMER

void RES0_init__(void) {
  BOOL retain;
  retain = 0;
  
  TASK0 = __BOOL_LITERAL(FALSE);
  WDT_CLOCK = __BOOL_LITERAL(FALSE);
  SUPERSTATE_MACHINE_init__(&SSM,retain);
  SERVICE_init__(&SVC,retain);
  EMERIGENCY_init__(&EM,retain);
  AUTOPRODUCTION_init__(&AP,retain);
  MANUALPRODUCTION_init__(&MP,retain);
  FAILURE_init__(&FAIL,retain);
  WATCHDOGTIMER_init__(&WDTIMER,retain);
}

void RES0_run__(unsigned long tick) {
  TASK0 = !(tick % 10);
  WDT_CLOCK = !(tick % 1);
  if (TASK0) {
    SUPERSTATE_MACHINE_body__(&SSM);
  }
  if (TASK0) {
    SERVICE_body__(&SVC);
  }
  if (TASK0) {
    EMERIGENCY_body__(&EM);
  }
  if (TASK0) {
    AUTOPRODUCTION_body__(&AP);
  }
  if (TASK0) {
    MANUALPRODUCTION_body__(&MP);
  }
  if (TASK0) {
    FAILURE_body__(&FAIL);
  }
  if (WDT_CLOCK) {
    WATCHDOGTIMER_body__(&WDTIMER);
  }
}

=======
/*******************************************/
/*     FILE GENERATED BY iec2c             */
/* Editing this file is not recommended... */
/*******************************************/

#include "iec_std_lib.h"

// RESOURCE RES0

extern unsigned long long common_ticktime__;

#include "accessor.h"
#include "POUS.h"

#include "Config0.h"

#include "POUS.c"

BOOL TASK0;
MOOREAUTOMATON RES0__INSTANCE0;
#define INSTANCE0 RES0__INSTANCE0

void RES0_init__(void) {
  BOOL retain;
  retain = 0;
  
  TASK0 = __BOOL_LITERAL(FALSE);
  MOOREAUTOMATON_init__(&INSTANCE0,retain);
}

void RES0_run__(unsigned long tick) {
  TASK0 = !(tick % 1);
  if (TASK0) {
    MOOREAUTOMATON_body__(&INSTANCE0);
  }
}

>>>>>>> 553e0b3e32c973bc8a997dc9b25d87bddf8ad5ea
