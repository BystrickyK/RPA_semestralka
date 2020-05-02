#include "beremiz.h"
#ifndef __POUS_H
#define __POUS_H

#include "accessor.h"
#include "iec_std_lib.h"

__DECLARE_ENUMERATED_TYPE(LOGLEVEL,
  LOGLEVEL__CRITICAL,
  LOGLEVEL__WARNING,
  LOGLEVEL__INFO,
  LOGLEVEL__DEBUG
)
// FUNCTION_BLOCK LOGGER
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,TRIG)
  __DECLARE_VAR(STRING,MSG)
  __DECLARE_VAR(LOGLEVEL,LEVEL)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(BOOL,TRIG0)

} LOGGER;

void LOGGER_init__(LOGGER *data__, BOOL retain);
// Code part
void LOGGER_body__(LOGGER *data__);
// FUNCTION_BLOCK PYTHON_EVAL
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,TRIG)
  __DECLARE_VAR(STRING,CODE)
  __DECLARE_VAR(BOOL,ACK)
  __DECLARE_VAR(STRING,RESULT)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(DWORD,STATE)
  __DECLARE_VAR(STRING,BUFFER)
  __DECLARE_VAR(STRING,PREBUFFER)
  __DECLARE_VAR(BOOL,TRIGM1)
  __DECLARE_VAR(BOOL,TRIGGED)

} PYTHON_EVAL;

void PYTHON_EVAL_init__(PYTHON_EVAL *data__, BOOL retain);
// Code part
void PYTHON_EVAL_body__(PYTHON_EVAL *data__);
// FUNCTION_BLOCK PYTHON_POLL
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,TRIG)
  __DECLARE_VAR(STRING,CODE)
  __DECLARE_VAR(BOOL,ACK)
  __DECLARE_VAR(STRING,RESULT)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(DWORD,STATE)
  __DECLARE_VAR(STRING,BUFFER)
  __DECLARE_VAR(STRING,PREBUFFER)
  __DECLARE_VAR(BOOL,TRIGM1)
  __DECLARE_VAR(BOOL,TRIGGED)

} PYTHON_POLL;

void PYTHON_POLL_init__(PYTHON_POLL *data__, BOOL retain);
// Code part
void PYTHON_POLL_body__(PYTHON_POLL *data__);
// FUNCTION_BLOCK PYTHON_GEAR
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(UINT,N)
  __DECLARE_VAR(BOOL,TRIG)
  __DECLARE_VAR(STRING,CODE)
  __DECLARE_VAR(BOOL,ACK)
  __DECLARE_VAR(STRING,RESULT)

  // FB private variables - TEMP, private and located variables
  PYTHON_EVAL PY_EVAL;
  __DECLARE_VAR(UINT,COUNTER)
  __DECLARE_VAR(UINT,ADD10_OUT)
  __DECLARE_VAR(BOOL,EQ13_OUT)
  __DECLARE_VAR(UINT,SEL15_OUT)
  __DECLARE_VAR(BOOL,AND7_OUT)

} PYTHON_GEAR;

void PYTHON_GEAR_init__(PYTHON_GEAR *data__, BOOL retain);
// Code part
void PYTHON_GEAR_body__(PYTHON_GEAR *data__);
__DECLARE_ARRAY_TYPE(__ARRAY_OF_INT_6_11,INT,[6][11])
__DECLARE_ARRAY_TYPE(__ARRAY_OF_WORD_11,WORD,[11])
// PROGRAM SUPERSTATE_MACHINE
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_EXTERNAL(WORD,SSM_TRANSITIONS)
  __DECLARE_EXTERNAL(INT,CURRENT_SUPERSTATE)
  __DECLARE_EXTERNAL(UINT,WDT)
  __DECLARE_VAR(INT,COL)
  __DECLARE_VAR(WORD,TMP1)
  __DECLARE_VAR(WORD,TMP2)
  __DECLARE_VAR(INT,TMP3)
  __DECLARE_EXTERNAL(WORD,SENSOR_OUTPUT)
  __DECLARE_VAR(__ARRAY_OF_INT_6_11,TRANSITION_MATRIX)
  __DECLARE_VAR(__ARRAY_OF_WORD_11,TRANSITION_MASKS)

} SUPERSTATE_MACHINE;

void SUPERSTATE_MACHINE_init__(SUPERSTATE_MACHINE *data__, BOOL retain);
// Code part
void SUPERSTATE_MACHINE_body__(SUPERSTATE_MACHINE *data__);
__DECLARE_ARRAY_TYPE(__ARRAY_OF_INT_9,INT,[9])
// FUNCTION_BLOCK ARRAY_ALL_1
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(__ARRAY_OF_INT_9,ARRAY1)
  __DECLARE_VAR(BOOL,OUTPUT)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(INT,SIZE)
  __DECLARE_VAR(BOOL,HELP)
  __DECLARE_VAR(INT,INDEX)

} ARRAY_ALL_1;

void ARRAY_ALL_1_init__(ARRAY_ALL_1 *data__, BOOL retain);
// Code part
void ARRAY_ALL_1_body__(ARRAY_ALL_1 *data__);
__DECLARE_ARRAY_TYPE(__ARRAY_OF_INT_4,INT,[4])
// FUNCTION_BLOCK ARRAY_EQUAL
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(__ARRAY_OF_INT_4,ARRAY1)
  __DECLARE_VAR(__ARRAY_OF_INT_4,ARRAY2)
  __DECLARE_VAR(BOOL,OUTPUT)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(INT,SIZE)
  __DECLARE_VAR(INT,INDEX)

} ARRAY_EQUAL;

void ARRAY_EQUAL_init__(ARRAY_EQUAL *data__, BOOL retain);
// Code part
void ARRAY_EQUAL_body__(ARRAY_EQUAL *data__);
__DECLARE_ARRAY_TYPE(__ARRAY_OF_INT_10_9,INT,[10][9])
// FUNCTION_BLOCK GET_MASK
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(__ARRAY_OF_INT_10_9,MASKS)
  __DECLARE_VAR(INT,MASKINDEX)
  __DECLARE_VAR(__ARRAY_OF_INT_9,MASK)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(INT,SIZE)
  __DECLARE_VAR(INT,INDEX)

} GET_MASK;

void GET_MASK_init__(GET_MASK *data__, BOOL retain);
// Code part
void GET_MASK_body__(GET_MASK *data__);
// FUNCTION_BLOCK ARRAY_MASK1
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(__ARRAY_OF_INT_9,ARRAY1)
  __DECLARE_VAR(__ARRAY_OF_INT_9,OUTPUT)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(INT,SIZE)
  __DECLARE_VAR(INT,INDEX)
  __DECLARE_VAR(INT,HELP)

} ARRAY_MASK1;

void ARRAY_MASK1_init__(ARRAY_MASK1 *data__, BOOL retain);
// Code part
void ARRAY_MASK1_body__(ARRAY_MASK1 *data__);
// FUNCTION_BLOCK ARRAY_MASK2
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(__ARRAY_OF_INT_9,ARRAY1)
  __DECLARE_VAR(__ARRAY_OF_INT_9,OUTPUT)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(INT,SIZE)
  __DECLARE_VAR(INT,INDEX)
  __DECLARE_VAR(INT,HELP)

} ARRAY_MASK2;

void ARRAY_MASK2_init__(ARRAY_MASK2 *data__, BOOL retain);
// Code part
void ARRAY_MASK2_body__(ARRAY_MASK2 *data__);
// FUNCTION_BLOCK ARRAY_AND
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(__ARRAY_OF_INT_9,ARRAY1)
  __DECLARE_VAR(__ARRAY_OF_INT_9,ARRAY2)
  __DECLARE_VAR(__ARRAY_OF_INT_9,OUTPUT)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(INT,SIZE)
  __DECLARE_VAR(INT,INDEX)
  __DECLARE_VAR(INT,HELP)

} ARRAY_AND;

void ARRAY_AND_init__(ARRAY_AND *data__, BOOL retain);
// Code part
void ARRAY_AND_body__(ARRAY_AND *data__);
// FUNCTION_BLOCK ARRAY_XOR
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(__ARRAY_OF_INT_9,ARRAY1)
  __DECLARE_VAR(__ARRAY_OF_INT_9,ARRAY2)
  __DECLARE_VAR(__ARRAY_OF_INT_9,OUTPUT)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(INT,SIZE)
  __DECLARE_VAR(INT,INDEX)
  __DECLARE_VAR(INT,HELP)

} ARRAY_XOR;

void ARRAY_XOR_init__(ARRAY_XOR *data__, BOOL retain);
// Code part
void ARRAY_XOR_body__(ARRAY_XOR *data__);
// FUNCTION_BLOCK ARRAY_MASK
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(__ARRAY_OF_INT_9,MASK)
  __DECLARE_VAR(__ARRAY_OF_INT_9,INPUT)
  __DECLARE_VAR(BOOL,OUTPUT)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(__ARRAY_OF_INT_9,HELP)
  __DECLARE_VAR(__ARRAY_OF_INT_9,MASK1)
  __DECLARE_VAR(__ARRAY_OF_INT_9,MASK2)
  ARRAY_MASK1 ARRAY_MASK1_INSTANCE;
  ARRAY_MASK2 ARRAY_MASK2_INSTANCE;
  ARRAY_AND ARRAY_AND_INSTANCE;
  ARRAY_XOR ARRAY_XOR_INSTANCE;
  ARRAY_ALL_1 ARRAY_ALL_1_INSTANCE;

} ARRAY_MASK;

void ARRAY_MASK_init__(ARRAY_MASK *data__, BOOL retain);
// Code part
void ARRAY_MASK_body__(ARRAY_MASK *data__);
// PROGRAM FAILURE
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_EXTERNAL(INT,CURRENT_SUPERSTATE)
  __DECLARE_EXTERNAL(WORD,SSM_TRANSITIONS)

} FAILURE;

void FAILURE_init__(FAILURE *data__, BOOL retain);
// Code part
void FAILURE_body__(FAILURE *data__);
// PROGRAM WATCHDOGTIMER
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_EXTERNAL(UINT,WDT)

} WATCHDOGTIMER;

void WATCHDOGTIMER_init__(WATCHDOGTIMER *data__, BOOL retain);
// Code part
void WATCHDOGTIMER_body__(WATCHDOGTIMER *data__);
__DECLARE_ARRAY_TYPE(__ARRAY_OF_INT_10_10,INT,[10][10])
__DECLARE_ARRAY_TYPE(__ARRAY_OF_BYTE_12,BYTE,[12])
// PROGRAM AUTOPRODUCTION
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_EXTERNAL(BYTE,CONTROLLER_OUTPUT)
  __DECLARE_EXTERNAL(INT,CURRENT_SUPERSTATE)
  __DECLARE_EXTERNAL(WORD,SENSOR_OUTPUT)
  __DECLARE_EXTERNAL(UINT,WDT)
  __DECLARE_EXTERNAL(WORD,SSM_TRANSITIONS)
  __DECLARE_VAR(INT,CURRENT_STATE)
  __DECLARE_VAR(INT,COL)
  GET_MASK GET_MASK_INSTANCE;
  ARRAY_MASK MASK_INSTANCE;
  __DECLARE_VAR(__ARRAY_OF_INT_9,MASK)
  __DECLARE_VAR(BOOL,ISSAMEASMASK)
  __DECLARE_VAR(INT,A0)
  __DECLARE_VAR(INT,A1)
  __DECLARE_VAR(INT,B0)
  __DECLARE_VAR(INT,B1)
  __DECLARE_VAR(INT,C0)
  __DECLARE_VAR(INT,C1)
  __DECLARE_VAR(INT,D0)
  __DECLARE_VAR(INT,D1)
  __DECLARE_VAR(INT,PROX)
  __DECLARE_VAR(__ARRAY_OF_INT_9,INPUT)
  __DECLARE_VAR(__ARRAY_OF_INT_10_10,TRANSITION_MATRIX)
  __DECLARE_VAR(__ARRAY_OF_INT_10_9,MASKARRAY)
  __DECLARE_VAR(__ARRAY_OF_WORD_11,MASKORIGINAL)
  __DECLARE_VAR(__ARRAY_OF_BYTE_12,STATE_OUTPUT)

} AUTOPRODUCTION;

void AUTOPRODUCTION_init__(AUTOPRODUCTION *data__, BOOL retain);
// Code part
void AUTOPRODUCTION_body__(AUTOPRODUCTION *data__);
// FUNCTION
INT TEST_FUNCTION(
  BOOL EN, 
  BOOL *__ENO, 
  INT MYCONSTANT);
// FUNCTION
BOOL ARRAY_EQUAL_FUNCTION(
  BOOL EN, 
  BOOL *__ENO, 
  __ARRAY_OF_INT_4 ARRAY1, 
  __ARRAY_OF_INT_4 ARRAY2);
// FUNCTION_BLOCK ARRAY_NOT
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(__ARRAY_OF_INT_4,ARRAY1)
  __DECLARE_VAR(__ARRAY_OF_INT_4,OUTPUT)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(INT,SIZE)
  __DECLARE_VAR(INT,INDEX)
  __DECLARE_VAR(INT,HELP)

} ARRAY_NOT;

void ARRAY_NOT_init__(ARRAY_NOT *data__, BOOL retain);
// Code part
void ARRAY_NOT_body__(ARRAY_NOT *data__);
#endif //__POUS_H
