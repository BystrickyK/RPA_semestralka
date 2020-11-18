void LOGGER_init__(LOGGER *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MSG,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->LEVEL,LOGLEVEL__INFO,retain)
  __INIT_VAR(data__->TRIG0,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void LOGGER_body__(LOGGER *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if ((__GET_VAR(data__->TRIG,) && !(__GET_VAR(data__->TRIG0,)))) {
    #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
    #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)

   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  
    #undef GetFbVar
    #undef SetFbVar
;
  };
  __SET_VAR(data__->,TRIG0,,__GET_VAR(data__->TRIG,));

  goto __end;

__end:
  return;
} // LOGGER_body__() 





void PYTHON_EVAL_init__(PYTHON_EVAL *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CODE,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->ACK,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->RESULT,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->STATE,0,retain)
  __INIT_VAR(data__->BUFFER,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->PREBUFFER,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->TRIGM1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TRIGGED,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void PYTHON_EVAL_body__(PYTHON_EVAL *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __IL_DEFVAR_T __IL_DEFVAR;
  __IL_DEFVAR_T __IL_DEFVAR_BACK;
  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void __PythonEvalFB(int, PYTHON_EVAL*);__PythonEvalFB(0, data__);
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // PYTHON_EVAL_body__() 





void PYTHON_POLL_init__(PYTHON_POLL *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CODE,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->ACK,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->RESULT,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->STATE,0,retain)
  __INIT_VAR(data__->BUFFER,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->PREBUFFER,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->TRIGM1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TRIGGED,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void PYTHON_POLL_body__(PYTHON_POLL *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __IL_DEFVAR_T __IL_DEFVAR;
  __IL_DEFVAR_T __IL_DEFVAR_BACK;
  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void __PythonEvalFB(int, PYTHON_EVAL*);__PythonEvalFB(1,(PYTHON_EVAL*)(void*)data__);
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // PYTHON_POLL_body__() 





void PYTHON_GEAR_init__(PYTHON_GEAR *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->N,0,retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CODE,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->ACK,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->RESULT,__STRING_LITERAL(0,""),retain)
  PYTHON_EVAL_init__(&data__->PY_EVAL,retain);
  __INIT_VAR(data__->COUNTER,0,retain)
  __INIT_VAR(data__->ADD10_OUT,0,retain)
  __INIT_VAR(data__->EQ13_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->SEL15_OUT,0,retain)
  __INIT_VAR(data__->AND7_OUT,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void PYTHON_GEAR_body__(PYTHON_GEAR *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,ADD10_OUT,,ADD__UINT__UINT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (UINT)__GET_VAR(data__->COUNTER,),
    (UINT)1));
  __SET_VAR(data__->,EQ13_OUT,,EQ__BOOL__UINT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (UINT)__GET_VAR(data__->N,),
    (UINT)__GET_VAR(data__->ADD10_OUT,)));
  __SET_VAR(data__->,SEL15_OUT,,SEL__UINT__BOOL__UINT__UINT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (BOOL)__GET_VAR(data__->EQ13_OUT,),
    (UINT)__GET_VAR(data__->ADD10_OUT,),
    (UINT)0));
  __SET_VAR(data__->,COUNTER,,__GET_VAR(data__->SEL15_OUT,));
  __SET_VAR(data__->,AND7_OUT,,AND__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->EQ13_OUT,),
    (BOOL)__GET_VAR(data__->TRIG,)));
  __SET_VAR(data__->PY_EVAL.,TRIG,,__GET_VAR(data__->AND7_OUT,));
  __SET_VAR(data__->PY_EVAL.,CODE,,__GET_VAR(data__->CODE,));
  PYTHON_EVAL_body__(&data__->PY_EVAL);
  __SET_VAR(data__->,ACK,,__GET_VAR(data__->PY_EVAL.ACK,));
  __SET_VAR(data__->,RESULT,,__GET_VAR(data__->PY_EVAL.RESULT,));

  goto __end;

__end:
  return;
} // PYTHON_GEAR_body__() 





void SUPERSTATE_MACHINE_init__(SUPERSTATE_MACHINE *data__, BOOL retain) {
  __INIT_EXTERNAL(WORD,SSM_TRANSITIONS,data__->SSM_TRANSITIONS,retain)
  __INIT_EXTERNAL(INT,CURRENT_SUPERSTATE,data__->CURRENT_SUPERSTATE,retain)
  __INIT_EXTERNAL(UINT,WDT,data__->WDT,retain)
  __INIT_VAR(data__->COL,0,retain)
  __INIT_EXTERNAL(WORD,SENSOR_OUTPUT,data__->SENSOR_OUTPUT,retain)
  __INIT_VAR(data__->EM,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->SAP,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->APF,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->SMP,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MPF,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->SSVC,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->SVCF,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->EMF,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->WDOX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->RESX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->BAD,__BOOL_LITERAL(FALSE),retain)
  {
    static const __ARRAY_OF_INT_6_11 temp = {{4,1,-1,2,-1,3,-1,-1,-1,-1,-1,4,-1,0,-1,-1,-1,-1,-1,5,-1,-1,4,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,4,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,4,-1,-1,-1,-1,-1,-1,-1,-1,1,3}};
    __SET_VAR(data__->,TRANSITION_MATRIX,,temp);
  }
  {
    static const __ARRAY_OF_WORD_11 temp = {{0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,0x0100,0x0200,0x0400}};
    __SET_VAR(data__->,TRANSITION_MASKS,,temp);
  }
}

// Code part
void SUPERSTATE_MACHINE_body__(SUPERSTATE_MACHINE *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,EM,,WORD_TO_BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (WORD)(__GET_EXTERNAL(data__->SSM_TRANSITIONS,) & 0x0001)));
  __SET_VAR(data__->,SAP,,WORD_TO_BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (WORD)(__GET_EXTERNAL(data__->SSM_TRANSITIONS,) & 0x0002)));
  __SET_VAR(data__->,APF,,WORD_TO_BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (WORD)(__GET_EXTERNAL(data__->SSM_TRANSITIONS,) & 0x0004)));
  __SET_VAR(data__->,SMP,,WORD_TO_BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (WORD)(__GET_EXTERNAL(data__->SSM_TRANSITIONS,) & 0x0008)));
  __SET_VAR(data__->,MPF,,WORD_TO_BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (WORD)(__GET_EXTERNAL(data__->SSM_TRANSITIONS,) & 0x0010)));
  __SET_VAR(data__->,SSVC,,WORD_TO_BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (WORD)(__GET_EXTERNAL(data__->SSM_TRANSITIONS,) & 0x0020)));
  __SET_VAR(data__->,SVCF,,WORD_TO_BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (WORD)(__GET_EXTERNAL(data__->SSM_TRANSITIONS,) & 0x0040)));
  __SET_VAR(data__->,EMF,,WORD_TO_BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (WORD)(__GET_EXTERNAL(data__->SSM_TRANSITIONS,) & 0x0080)));
  __SET_VAR(data__->,WDOX,,WORD_TO_BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (WORD)(__GET_EXTERNAL(data__->SSM_TRANSITIONS,) & 0x0100)));
  __SET_VAR(data__->,RESX,,WORD_TO_BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (WORD)(__GET_EXTERNAL(data__->SSM_TRANSITIONS,) & 0x0200)));
  __SET_VAR(data__->,BAD,,WORD_TO_BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (WORD)(__GET_EXTERNAL(data__->SSM_TRANSITIONS,) & 0x0400)));
  for(__GET_VAR(data__->COL,) = 0; __GET_VAR(data__->COL,) <= 10; __GET_VAR(data__->COL,)++) {
    if ((__GET_VAR(data__->TRANSITION_MATRIX,.table[(__GET_EXTERNAL(data__->CURRENT_SUPERSTATE,)) - (0)][(__GET_VAR(data__->COL,)) - (0)]) != -1)) {
      if (((__GET_EXTERNAL(data__->SSM_TRANSITIONS,) & __GET_VAR(data__->TRANSITION_MASKS,.table[(__GET_VAR(data__->COL,)) - (0)])) == __GET_VAR(data__->TRANSITION_MASKS,.table[(__GET_VAR(data__->COL,)) - (0)]))) {
        __SET_EXTERNAL(data__->,CURRENT_SUPERSTATE,,__GET_VAR(data__->TRANSITION_MATRIX,.table[(__GET_EXTERNAL(data__->CURRENT_SUPERSTATE,)) - (0)][(__GET_VAR(data__->COL,)) - (0)]));
        __SET_EXTERNAL(data__->,WDT,,0);
      };
    };
  };
  __SET_EXTERNAL(data__->,SSM_TRANSITIONS,,(__GET_EXTERNAL(data__->SSM_TRANSITIONS,) & ~(4)));

  goto __end;

__end:
  return;
} // SUPERSTATE_MACHINE_body__() 





void SERVICE_init__(SERVICE *data__, BOOL retain) {
  __INIT_EXTERNAL(INT,CURRENT_SUPERSTATE,data__->CURRENT_SUPERSTATE,retain)
  __INIT_EXTERNAL(WORD,SENSOR_OUTPUT,data__->SENSOR_OUTPUT,retain)
  __INIT_EXTERNAL(WORD,SSM_TRANSITIONS,data__->SSM_TRANSITIONS,retain)
  __INIT_VAR(data__->IN_AP,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->IN_AM,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->IN_B,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->IN_C,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->IN_DP,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->IN_DM,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->IN_PREASURE_OFF,__BOOL_LITERAL(FALSE),retain)
  __INIT_EXTERNAL(BOOL,OUT_AP,data__->OUT_AP,retain)
  __INIT_EXTERNAL(BOOL,OUT_AM,data__->OUT_AM,retain)
  __INIT_EXTERNAL(BOOL,OUT_B,data__->OUT_B,retain)
  __INIT_EXTERNAL(BOOL,OUT_C,data__->OUT_C,retain)
  __INIT_EXTERNAL(BOOL,OUT_DP,data__->OUT_DP,retain)
  __INIT_EXTERNAL(BOOL,OUT_DM,data__->OUT_DM,retain)
  __INIT_EXTERNAL(BOOL,OUT_PREASURE_OFF,data__->OUT_PREASURE_OFF,retain)
}

// Code part
void SERVICE_body__(SERVICE *data__) {
  // Initialise TEMP variables

  if ((__GET_EXTERNAL(data__->CURRENT_SUPERSTATE,) == 3)) {
    __SET_VAR(data__->,IN_AP,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->SENSOR_OUTPUT,) & 0x8000)));
    __SET_VAR(data__->,IN_AM,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->SENSOR_OUTPUT,) & 0x4000)));
    __SET_VAR(data__->,IN_B,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->SENSOR_OUTPUT,) & 0x2000)));
    __SET_VAR(data__->,IN_C,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->SENSOR_OUTPUT,) & 0x1000)));
    __SET_VAR(data__->,IN_DP,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->SENSOR_OUTPUT,) & 0x0800)));
    __SET_VAR(data__->,IN_DM,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->SENSOR_OUTPUT,) & 0x0400)));
    __SET_VAR(data__->,IN_PREASURE_OFF,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->SENSOR_OUTPUT,) & 0x0100)));
    __SET_EXTERNAL(data__->,OUT_AP,,__GET_VAR(data__->IN_AP,));
    __SET_EXTERNAL(data__->,OUT_AM,,__GET_VAR(data__->IN_AM,));
    __SET_EXTERNAL(data__->,OUT_B,,__GET_VAR(data__->IN_B,));
    __SET_EXTERNAL(data__->,OUT_C,,__GET_VAR(data__->IN_C,));
    __SET_EXTERNAL(data__->,OUT_DP,,__GET_VAR(data__->IN_DP,));
    __SET_EXTERNAL(data__->,OUT_DM,,__GET_VAR(data__->IN_DM,));
  };

  goto __end;

__end:
  return;
} // SERVICE_body__() 





void FAILURE_init__(FAILURE *data__, BOOL retain) {
  __INIT_EXTERNAL(INT,CURRENT_SUPERSTATE,data__->CURRENT_SUPERSTATE,retain)
  __INIT_EXTERNAL(WORD,SSM_TRANSITIONS,data__->SSM_TRANSITIONS,retain)
}

// Code part
void FAILURE_body__(FAILURE *data__) {
  // Initialise TEMP variables

  if ((__GET_EXTERNAL(data__->CURRENT_SUPERSTATE,) == 5)) {
    __SET_EXTERNAL(data__->,SSM_TRANSITIONS,,(__GET_EXTERNAL(data__->SSM_TRANSITIONS,) & ~(256)));
  };

  goto __end;

__end:
  return;
} // FAILURE_body__() 





void WATCHDOGTIMER_init__(WATCHDOGTIMER *data__, BOOL retain) {
  __INIT_EXTERNAL(UINT,WDT,data__->WDT,retain)
}

// Code part
void WATCHDOGTIMER_body__(WATCHDOGTIMER *data__) {
  // Initialise TEMP variables

  __SET_EXTERNAL(data__->,WDT,,(__GET_EXTERNAL(data__->WDT,) + 1));

  goto __end;

__end:
  return;
} // WATCHDOGTIMER_body__() 





void AUTOPRODUCTION_init__(AUTOPRODUCTION *data__, BOOL retain) {
  
  {
    static const __ARRAY_OF_WORD_12 temp = {{0,0,0,0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,VALUEMATRIX,,temp);
  }
  {
    static const __ARRAY_OF_WORD_12 temp = {{0,0,0,0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,MASKMATRIX,,temp);
  }
  {
    static const __ARRAY_OF_WORD_11 temp = {{0,0,0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,OUTPUTMATRIX,,temp);
  }__INIT_EXTERNAL(WORD,CONTROLLER_OUTPUT,data__->CONTROLLER_OUTPUT,retain)
  __INIT_EXTERNAL(INT,CURRENT_SUPERSTATE,data__->CURRENT_SUPERSTATE,retain)
  __INIT_EXTERNAL(WORD,SENSOR_OUTPUT,data__->SENSOR_OUTPUT,retain)
  __INIT_EXTERNAL(UINT,WDT,data__->WDT,retain)
  __INIT_EXTERNAL(WORD,SSM_TRANSITIONS,data__->SSM_TRANSITIONS,retain)
  __INIT_EXTERNAL(INT,CURRENT_STATE,data__->CURRENT_STATE,retain)
  __INIT_VAR(data__->COLUMN,0,retain)
  __INIT_EXTERNAL(BOOL,OUT_AP,data__->OUT_AP,retain)
  __INIT_EXTERNAL(BOOL,OUT_AM,data__->OUT_AM,retain)
  __INIT_EXTERNAL(BOOL,OUT_B,data__->OUT_B,retain)
  __INIT_EXTERNAL(BOOL,OUT_C,data__->OUT_C,retain)
  __INIT_EXTERNAL(BOOL,OUT_DP,data__->OUT_DP,retain)
  __INIT_EXTERNAL(BOOL,OUT_DM,data__->OUT_DM,retain)
  __INIT_VAR(data__->IN_PROX,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->IN_A0,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->IN_A1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->IN_B,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->IN_C0,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->IN_C1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->IN_D0,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->IN_D1,__BOOL_LITERAL(FALSE),retain)
  {
    static const __ARRAY_OF_INT_11_11 temp = {{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,5,-1,6,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,9,-1,10,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}};
    __SET_VAR(data__->,TRANSITIONMATRIX,,temp);
  }
}

// Code part
void AUTOPRODUCTION_body__(AUTOPRODUCTION *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,MASKMATRIX,.table[(0) - (0)],0x0080);
  __SET_VAR(data__->,MASKMATRIX,.table[(1) - (0)],0x0080);
  __SET_VAR(data__->,MASKMATRIX,.table[(2) - (0)],0x0020);
  __SET_VAR(data__->,MASKMATRIX,.table[(3) - (0)],0x0010);
  __SET_VAR(data__->,MASKMATRIX,.table[(4) - (0)],0x0004);
  __SET_VAR(data__->,MASKMATRIX,.table[(5) - (0)],0x000A);
  __SET_VAR(data__->,MASKMATRIX,.table[(6) - (0)],0x0001);
  __SET_VAR(data__->,MASKMATRIX,.table[(7) - (0)],0x0009);
  __SET_VAR(data__->,MASKMATRIX,.table[(8) - (0)],0x0010);
  __SET_VAR(data__->,MASKMATRIX,.table[(9) - (0)],0x0002);
  __SET_VAR(data__->,MASKMATRIX,.table[(10) - (0)],0x0040);
  __SET_VAR(data__->,VALUEMATRIX,.table[(0) - (0)],0x0080);
  __SET_VAR(data__->,VALUEMATRIX,.table[(1) - (0)],0x0000);
  __SET_VAR(data__->,VALUEMATRIX,.table[(2) - (0)],0x0020);
  __SET_VAR(data__->,VALUEMATRIX,.table[(3) - (0)],0x0010);
  __SET_VAR(data__->,VALUEMATRIX,.table[(4) - (0)],0x0004);
  __SET_VAR(data__->,VALUEMATRIX,.table[(5) - (0)],0x000A);
  __SET_VAR(data__->,VALUEMATRIX,.table[(6) - (0)],0x0001);
  __SET_VAR(data__->,VALUEMATRIX,.table[(7) - (0)],0x0009);
  __SET_VAR(data__->,VALUEMATRIX,.table[(8) - (0)],0x0000);
  __SET_VAR(data__->,VALUEMATRIX,.table[(9) - (0)],0x0002);
  __SET_VAR(data__->,VALUEMATRIX,.table[(10) - (0)],0x0040);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(0) - (0)],0x0044);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(1) - (0)],0x0080);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(2) - (0)],0x0020);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(3) - (0)],0x0030);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(4) - (0)],0x0020);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(5) - (0)],0x0028);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(6) - (0)],0x0000);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(7) - (0)],0x0004);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(8) - (0)],0x0040);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(9) - (0)],0x0000);
  if ((__GET_EXTERNAL(data__->CURRENT_SUPERSTATE,) == 1)) {
    __SET_VAR(data__->,IN_PROX,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->SENSOR_OUTPUT,) & 0x00000080)));
    __SET_VAR(data__->,IN_A0,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->SENSOR_OUTPUT,) & 0x00000040)));
    __SET_VAR(data__->,IN_A1,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->SENSOR_OUTPUT,) & 0x00000020)));
    __SET_VAR(data__->,IN_B,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->SENSOR_OUTPUT,) & 0x00000010)));
    __SET_VAR(data__->,IN_C0,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->SENSOR_OUTPUT,) & 0x00000008)));
    __SET_VAR(data__->,IN_C1,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->SENSOR_OUTPUT,) & 0x00000004)));
    __SET_VAR(data__->,IN_D0,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->SENSOR_OUTPUT,) & 0x00000002)));
    __SET_VAR(data__->,IN_D1,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->SENSOR_OUTPUT,) & 0x00000001)));
    for(__GET_VAR(data__->COLUMN,) = 0; __GET_VAR(data__->COLUMN,) <= 10; __GET_VAR(data__->COLUMN,)++) {
      if ((__GET_VAR(data__->TRANSITIONMATRIX,.table[(__GET_EXTERNAL(data__->CURRENT_STATE,)) - (0)][(__GET_VAR(data__->COLUMN,)) - (0)]) != -1)) {
        if (((__GET_EXTERNAL(data__->SENSOR_OUTPUT,) & __GET_VAR(data__->MASKMATRIX,.table[(__GET_VAR(data__->COLUMN,)) - (0)])) == __GET_VAR(data__->VALUEMATRIX,.table[(__GET_VAR(data__->COLUMN,)) - (0)]))) {
          __SET_EXTERNAL(data__->,CURRENT_STATE,,__GET_VAR(data__->TRANSITIONMATRIX,.table[(__GET_EXTERNAL(data__->CURRENT_STATE,)) - (0)][(__GET_VAR(data__->COLUMN,)) - (0)]));
          __SET_EXTERNAL(data__->,WDT,,0);
        };
      };
    };
    __SET_EXTERNAL(data__->,CONTROLLER_OUTPUT,,__GET_VAR(data__->OUTPUTMATRIX,.table[(__GET_EXTERNAL(data__->CURRENT_STATE,)) - (0)]));
    __SET_EXTERNAL(data__->,OUT_AP,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->CONTROLLER_OUTPUT,) & 0x00000080)));
    __SET_EXTERNAL(data__->,OUT_AM,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->CONTROLLER_OUTPUT,) & 0x00000040)));
    __SET_EXTERNAL(data__->,OUT_B,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->CONTROLLER_OUTPUT,) & 0x00000020)));
    __SET_EXTERNAL(data__->,OUT_C,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->CONTROLLER_OUTPUT,) & 0x00000010)));
    __SET_EXTERNAL(data__->,OUT_DP,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->CONTROLLER_OUTPUT,) & 0x00000008)));
    __SET_EXTERNAL(data__->,OUT_DM,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->CONTROLLER_OUTPUT,) & 0x00000004)));
    if ((__GET_EXTERNAL(data__->WDT,) > 3000)) {
      __SET_EXTERNAL(data__->,SSM_TRANSITIONS,,256);
    };
    if ((__GET_EXTERNAL(data__->CURRENT_STATE,) == 10)) {
      __SET_EXTERNAL(data__->,SSM_TRANSITIONS,,4);
      __SET_EXTERNAL(data__->,CURRENT_STATE,,0);
    };
  };

  goto __end;

__end:
  return;
} // AUTOPRODUCTION_body__() 





void MANUALPRODUCTION_init__(MANUALPRODUCTION *data__, BOOL retain) {
  
  {
    static const __ARRAY_OF_WORD_12 temp = {{0,0,0,0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,VALUEMATRIX,,temp);
  }
  {
    static const __ARRAY_OF_WORD_12 temp = {{0,0,0,0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,MASKMATRIX,,temp);
  }
  {
    static const __ARRAY_OF_WORD_11 temp = {{0,0,0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,OUTPUTMATRIX,,temp);
  }__INIT_EXTERNAL(WORD,CONTROLLER_OUTPUT,data__->CONTROLLER_OUTPUT,retain)
  __INIT_EXTERNAL(INT,CURRENT_SUPERSTATE,data__->CURRENT_SUPERSTATE,retain)
  __INIT_EXTERNAL(WORD,SENSOR_OUTPUT,data__->SENSOR_OUTPUT,retain)
  __INIT_EXTERNAL(UINT,WDT,data__->WDT,retain)
  __INIT_EXTERNAL(WORD,SSM_TRANSITIONS,data__->SSM_TRANSITIONS,retain)
  __INIT_EXTERNAL(INT,CURRENT_STATE,data__->CURRENT_STATE,retain)
  __INIT_VAR(data__->COLUMN,0,retain)
  {
    static const __ARRAY_OF_INT_11_11 temp = {{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,5,-1,6,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,9,-1,10,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}};
    __SET_VAR(data__->,TRANSITIONMATRIXMP,,temp);
  }
}

// Code part
void MANUALPRODUCTION_body__(MANUALPRODUCTION *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,MASKMATRIX,.table[(0) - (0)],0x0080);
  __SET_VAR(data__->,MASKMATRIX,.table[(1) - (0)],0x0080);
  __SET_VAR(data__->,MASKMATRIX,.table[(2) - (0)],0x0020);
  __SET_VAR(data__->,MASKMATRIX,.table[(3) - (0)],0x0010);
  __SET_VAR(data__->,MASKMATRIX,.table[(4) - (0)],0x0004);
  __SET_VAR(data__->,MASKMATRIX,.table[(5) - (0)],0x000A);
  __SET_VAR(data__->,MASKMATRIX,.table[(6) - (0)],0x0001);
  __SET_VAR(data__->,MASKMATRIX,.table[(7) - (0)],0x0009);
  __SET_VAR(data__->,MASKMATRIX,.table[(8) - (0)],0x0010);
  __SET_VAR(data__->,MASKMATRIX,.table[(9) - (0)],0x0002);
  __SET_VAR(data__->,MASKMATRIX,.table[(10) - (0)],0x0040);
  __SET_VAR(data__->,VALUEMATRIX,.table[(0) - (0)],0x0080);
  __SET_VAR(data__->,VALUEMATRIX,.table[(1) - (0)],0x0000);
  __SET_VAR(data__->,VALUEMATRIX,.table[(2) - (0)],0x0020);
  __SET_VAR(data__->,VALUEMATRIX,.table[(3) - (0)],0x0010);
  __SET_VAR(data__->,VALUEMATRIX,.table[(4) - (0)],0x0004);
  __SET_VAR(data__->,VALUEMATRIX,.table[(5) - (0)],0x000A);
  __SET_VAR(data__->,VALUEMATRIX,.table[(6) - (0)],0x0001);
  __SET_VAR(data__->,VALUEMATRIX,.table[(7) - (0)],0x0009);
  __SET_VAR(data__->,VALUEMATRIX,.table[(8) - (0)],0x0000);
  __SET_VAR(data__->,VALUEMATRIX,.table[(9) - (0)],0x0002);
  __SET_VAR(data__->,VALUEMATRIX,.table[(10) - (0)],0x0040);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(0) - (0)],0x0000);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(1) - (0)],0x0080);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(2) - (0)],0x0020);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(3) - (0)],0x0030);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(4) - (0)],0x0020);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(5) - (0)],0x0028);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(6) - (0)],0x0000);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(7) - (0)],0x0004);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(8) - (0)],0x0040);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(9) - (0)],0x0000);
  if ((__GET_EXTERNAL(data__->CURRENT_SUPERSTATE,) == 2)) {
    for(__GET_VAR(data__->COLUMN,) = 0; __GET_VAR(data__->COLUMN,) <= 10; __GET_VAR(data__->COLUMN,)++) {
      if ((__GET_VAR(data__->TRANSITIONMATRIXMP,.table[(__GET_EXTERNAL(data__->CURRENT_STATE,)) - (0)][(__GET_VAR(data__->COLUMN,)) - (0)]) != -1)) {
        if (((__GET_EXTERNAL(data__->SENSOR_OUTPUT,) & __GET_VAR(data__->MASKMATRIX,.table[(__GET_VAR(data__->COLUMN,)) - (0)])) == __GET_VAR(data__->VALUEMATRIX,.table[(__GET_VAR(data__->COLUMN,)) - (0)]))) {
          __SET_EXTERNAL(data__->,CURRENT_STATE,,__GET_VAR(data__->TRANSITIONMATRIXMP,.table[(__GET_EXTERNAL(data__->CURRENT_STATE,)) - (0)][(__GET_VAR(data__->COLUMN,)) - (0)]));
          __SET_EXTERNAL(data__->,WDT,,0);
        };
      };
    };
    __SET_EXTERNAL(data__->,CONTROLLER_OUTPUT,,__GET_VAR(data__->OUTPUTMATRIX,.table[(__GET_EXTERNAL(data__->CURRENT_STATE,)) - (0)]));
    if ((__GET_EXTERNAL(data__->CURRENT_STATE,) == 10)) {
      __SET_EXTERNAL(data__->,SSM_TRANSITIONS,,4);
      __SET_EXTERNAL(data__->,CURRENT_STATE,,0);
    };
  };

  goto __end;

__end:
  return;
} // MANUALPRODUCTION_body__() 





void EMERIGENCY_init__(EMERIGENCY *data__, BOOL retain) {
  
  {
    static const __ARRAY_OF_WORD_11 temp = {{0,0,0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,OUTPUTMATRIX,,temp);
  }__INIT_EXTERNAL(WORD,CONTROLLER_OUTPUT,data__->CONTROLLER_OUTPUT,retain)
  __INIT_EXTERNAL(INT,CURRENT_SUPERSTATE,data__->CURRENT_SUPERSTATE,retain)
  __INIT_EXTERNAL(WORD,SENSOR_OUTPUT,data__->SENSOR_OUTPUT,retain)
  __INIT_EXTERNAL(WORD,SSM_TRANSITIONS,data__->SSM_TRANSITIONS,retain)
  __INIT_EXTERNAL(INT,CURRENT_STATE,data__->CURRENT_STATE,retain)
  __INIT_EXTERNAL(BOOL,OUT_AP,data__->OUT_AP,retain)
  __INIT_EXTERNAL(BOOL,OUT_AM,data__->OUT_AM,retain)
  __INIT_EXTERNAL(BOOL,OUT_B,data__->OUT_B,retain)
  __INIT_EXTERNAL(BOOL,OUT_C,data__->OUT_C,retain)
  __INIT_EXTERNAL(BOOL,OUT_DP,data__->OUT_DP,retain)
  __INIT_EXTERNAL(BOOL,OUT_DM,data__->OUT_DM,retain)
  __INIT_VAR(data__->OUT_PREASURE_OFF,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void EMERIGENCY_body__(EMERIGENCY *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,OUTPUTMATRIX,.table[(0) - (0)],0x0001);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(1) - (0)],0x0040);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(2) - (0)],0x0000);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(3) - (0)],0x0000);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(4) - (0)],0x0001);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(5) - (0)],0x0004);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(6) - (0)],0x0001);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(7) - (0)],0x0008);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(8) - (0)],0x0080);
  __SET_VAR(data__->,OUTPUTMATRIX,.table[(9) - (0)],0x0001);
  if ((__GET_EXTERNAL(data__->CURRENT_SUPERSTATE,) == 4)) {
    __SET_EXTERNAL(data__->,CONTROLLER_OUTPUT,,__GET_VAR(data__->OUTPUTMATRIX,.table[(__GET_EXTERNAL(data__->CURRENT_STATE,)) - (0)]));
    __SET_EXTERNAL(data__->,OUT_AP,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->CONTROLLER_OUTPUT,) & 0x0080)));
    __SET_EXTERNAL(data__->,OUT_AM,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->CONTROLLER_OUTPUT,) & 0x0040)));
    __SET_EXTERNAL(data__->,OUT_B,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->CONTROLLER_OUTPUT,) & 0x0020)));
    __SET_EXTERNAL(data__->,OUT_C,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->CONTROLLER_OUTPUT,) & 0x0010)));
    __SET_EXTERNAL(data__->,OUT_DP,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->CONTROLLER_OUTPUT,) & 0x0008)));
    __SET_EXTERNAL(data__->,OUT_DM,,WORD_TO_BOOL(
      (BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (WORD)(__GET_EXTERNAL(data__->CONTROLLER_OUTPUT,) & 0x0004)));
  };

  goto __end;

__end:
  return;
} // EMERIGENCY_body__() 





