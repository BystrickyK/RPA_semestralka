/*******************************************/
/*     FILE GENERATED BY iec2c             */
/* Editing this file is not recommended... */
/*******************************************/

#include "iec_std_lib.h"

#include "accessor.h"

#include "POUS.h"

// CONFIGURATION CONFIG0
__DECLARE_GLOBAL(DWORD,CONFIG0,CONTROLLER_OUTPUT)
__DECLARE_GLOBAL(UINT,CONFIG0,WDT)
__DECLARE_GLOBAL(INT,CONFIG0,CURRENT_SUPERSTATE)
__DECLARE_GLOBAL(INT,CONFIG0,CURRENT_STATE)
__DECLARE_GLOBAL(DWORD,CONFIG0,SENSOR_OUTPUT)
__DECLARE_GLOBAL(DWORD,CONFIG0,SSM_TRANSITIONS)
__DECLARE_GLOBAL(BOOL,CONFIG0,OUT_AP)
__DECLARE_GLOBAL(BOOL,CONFIG0,OUT_AM)
__DECLARE_GLOBAL(BOOL,CONFIG0,OUT_B)
__DECLARE_GLOBAL(BOOL,CONFIG0,OUT_C)
__DECLARE_GLOBAL(BOOL,CONFIG0,OUT_DP)
__DECLARE_GLOBAL(BOOL,CONFIG0,OUT_DM)
__DECLARE_GLOBAL(BOOL,CONFIG0,OUT_PREASURE_OFF)

void RES0_init__(void);

void config_init__(void) {
  BOOL retain;
  retain = 0;
  __INIT_GLOBAL(DWORD,CONTROLLER_OUTPUT,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(UINT,WDT,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,CURRENT_SUPERSTATE,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(INT,CURRENT_STATE,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(DWORD,SENSOR_OUTPUT,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(DWORD,SSM_TRANSITIONS,__INITIAL_VALUE(0),retain)
  __INIT_GLOBAL(BOOL,OUT_AP,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  __INIT_GLOBAL(BOOL,OUT_AM,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  __INIT_GLOBAL(BOOL,OUT_B,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  __INIT_GLOBAL(BOOL,OUT_C,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  __INIT_GLOBAL(BOOL,OUT_DP,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  __INIT_GLOBAL(BOOL,OUT_DM,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  __INIT_GLOBAL(BOOL,OUT_PREASURE_OFF,__INITIAL_VALUE(__BOOL_LITERAL(FALSE)),retain)
  RES0_init__();
}

void RES0_run__(unsigned long tick);

void config_run__(unsigned long tick) {
  RES0_run__(tick);
}
unsigned long long common_ticktime__ = 10000000ULL; /*ns*/
unsigned long greatest_tick_count__ = (unsigned long)4294967291UL; /*tick*/
