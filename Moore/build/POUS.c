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
  __INIT_VAR(data__->TMP1,0,retain)
  __INIT_VAR(data__->TMP2,0,retain)
  __INIT_VAR(data__->TMP3,123,retain)
  __INIT_EXTERNAL(WORD,SENSOR_OUTPUT,data__->SENSOR_OUTPUT,retain)
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

  for(__GET_VAR(data__->COL,) = 0; __GET_VAR(data__->COL,) <= 10; __GET_VAR(data__->COL,)++) {
    if ((__GET_VAR(data__->TRANSITION_MATRIX,.table[(__GET_EXTERNAL(data__->CURRENT_SUPERSTATE,)) - (0)][(__GET_VAR(data__->COL,)) - (0)]) != -1)) {
      if (((__GET_EXTERNAL(data__->SSM_TRANSITIONS,) & __GET_VAR(data__->TRANSITION_MASKS,.table[(__GET_VAR(data__->COL,)) - (0)])) == __GET_VAR(data__->TRANSITION_MASKS,.table[(__GET_VAR(data__->COL,)) - (0)]))) {
        __SET_EXTERNAL(data__->,CURRENT_SUPERSTATE,,__GET_VAR(data__->TRANSITION_MATRIX,.table[(__GET_EXTERNAL(data__->CURRENT_SUPERSTATE,)) - (0)][(__GET_VAR(data__->COL,)) - (0)]));
        __SET_EXTERNAL(data__->,WDT,,0);
      };
    };
  };

  goto __end;

__end:
  return;
} // SUPERSTATE_MACHINE_body__() 





void ARRAY_ALL_1_init__(ARRAY_ALL_1 *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->SIZE,8,retain)
  {
    static const __ARRAY_OF_INT_9 temp = {{0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,ARRAY1,,temp);
  }
  __INIT_VAR(data__->OUTPUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->HELP,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->INDEX,0,retain)
}

// Code part
void ARRAY_ALL_1_body__(ARRAY_ALL_1 *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  for(__GET_VAR(data__->INDEX,) = 0; __GET_VAR(data__->INDEX,) <= __GET_VAR(data__->SIZE,); __GET_VAR(data__->INDEX,)++) {
    if ((__GET_VAR(data__->ARRAY1,.table[(__GET_VAR(data__->INDEX,)) - (0)]) != 1)) {
      __SET_VAR(data__->,HELP,,__BOOL_LITERAL(FALSE));
      break;
    };
  };
  __SET_VAR(data__->,OUTPUT,,__GET_VAR(data__->HELP,));

  goto __end;

__end:
  return;
} // ARRAY_ALL_1_body__() 





void ARRAY_EQUAL_init__(ARRAY_EQUAL *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->SIZE,0,retain)
  {
    static const __ARRAY_OF_INT_4 temp = {{0,0,0,0}};
    __SET_VAR(data__->,ARRAY1,,temp);
  }
  {
    static const __ARRAY_OF_INT_4 temp = {{0,0,0,0}};
    __SET_VAR(data__->,ARRAY2,,temp);
  }
  __INIT_VAR(data__->OUTPUT,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->INDEX,0,retain)
}

// Code part
void ARRAY_EQUAL_body__(ARRAY_EQUAL *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  for(__GET_VAR(data__->INDEX,) = 0; __GET_VAR(data__->INDEX,) <= __GET_VAR(data__->SIZE,); __GET_VAR(data__->INDEX,)++) {
    if ((__GET_VAR(data__->ARRAY1,.table[(__GET_VAR(data__->INDEX,)) - (0)]) != __GET_VAR(data__->ARRAY2,.table[(__GET_VAR(data__->INDEX,)) - (0)]))) {
      __SET_VAR(data__->,OUTPUT,,__BOOL_LITERAL(FALSE));
      break;
    };
  };

  goto __end;

__end:
  return;
} // ARRAY_EQUAL_body__() 





void GET_MASK_init__(GET_MASK *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->SIZE,8,retain)
  {
    static const __ARRAY_OF_INT_10_9 temp = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,MASKS,,temp);
  }
  __INIT_VAR(data__->MASKINDEX,0,retain)
  {
    static const __ARRAY_OF_INT_9 temp = {{0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,MASK,,temp);
  }
  __INIT_VAR(data__->INDEX,0,retain)
}

// Code part
void GET_MASK_body__(GET_MASK *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  for(__GET_VAR(data__->INDEX,) = 0; __GET_VAR(data__->INDEX,) <= __GET_VAR(data__->SIZE,); __GET_VAR(data__->INDEX,)++) {
    __SET_VAR(data__->,MASK,.table[(__GET_VAR(data__->INDEX,)) - (0)],__GET_VAR(data__->MASKS,.table[(__GET_VAR(data__->MASKINDEX,)) - (0)][(__GET_VAR(data__->INDEX,)) - (0)]));
  };

  goto __end;

__end:
  return;
} // GET_MASK_body__() 





void ARRAY_MASK1_init__(ARRAY_MASK1 *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->SIZE,8,retain)
  {
    static const __ARRAY_OF_INT_9 temp = {{0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,ARRAY1,,temp);
  }
  {
    static const __ARRAY_OF_INT_9 temp = {{0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,OUTPUT,,temp);
  }
  __INIT_VAR(data__->INDEX,0,retain)
  __INIT_VAR(data__->HELP,0,retain)
}

// Code part
void ARRAY_MASK1_body__(ARRAY_MASK1 *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  for(__GET_VAR(data__->INDEX,) = 0; __GET_VAR(data__->INDEX,) <= __GET_VAR(data__->SIZE,); __GET_VAR(data__->INDEX,)++) {
    __SET_VAR(data__->,HELP,,__GET_VAR(data__->ARRAY1,.table[(__GET_VAR(data__->INDEX,)) - (0)]));
    if ((__GET_VAR(data__->HELP,) == -1)) {
      __SET_VAR(data__->,OUTPUT,.table[(__GET_VAR(data__->INDEX,)) - (0)],0);
    } else {
      __SET_VAR(data__->,OUTPUT,.table[(__GET_VAR(data__->INDEX,)) - (0)],1);
    };
  };

  goto __end;

__end:
  return;
} // ARRAY_MASK1_body__() 





void ARRAY_MASK2_init__(ARRAY_MASK2 *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->SIZE,8,retain)
  {
    static const __ARRAY_OF_INT_9 temp = {{0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,ARRAY1,,temp);
  }
  {
    static const __ARRAY_OF_INT_9 temp = {{0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,OUTPUT,,temp);
  }
  __INIT_VAR(data__->INDEX,0,retain)
  __INIT_VAR(data__->HELP,0,retain)
}

// Code part
void ARRAY_MASK2_body__(ARRAY_MASK2 *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  for(__GET_VAR(data__->INDEX,) = 0; __GET_VAR(data__->INDEX,) <= __GET_VAR(data__->SIZE,); __GET_VAR(data__->INDEX,)++) {
    __SET_VAR(data__->,HELP,,__GET_VAR(data__->ARRAY1,.table[(__GET_VAR(data__->INDEX,)) - (0)]));
    if ((__GET_VAR(data__->HELP,) == 1)) {
      __SET_VAR(data__->,OUTPUT,.table[(__GET_VAR(data__->INDEX,)) - (0)],0);
    } else if ((__GET_VAR(data__->HELP,) == 0)) {
      __SET_VAR(data__->,OUTPUT,.table[(__GET_VAR(data__->INDEX,)) - (0)],1);
    } else if ((__GET_VAR(data__->HELP,) == -1)) {
      __SET_VAR(data__->,OUTPUT,.table[(__GET_VAR(data__->INDEX,)) - (0)],1);
    } else {
      __SET_VAR(data__->,OUTPUT,.table[(__GET_VAR(data__->INDEX,)) - (0)],99);
    };
  };

  goto __end;

__end:
  return;
} // ARRAY_MASK2_body__() 





void ARRAY_AND_init__(ARRAY_AND *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->SIZE,8,retain)
  {
    static const __ARRAY_OF_INT_9 temp = {{0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,ARRAY1,,temp);
  }
  {
    static const __ARRAY_OF_INT_9 temp = {{0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,ARRAY2,,temp);
  }
  {
    static const __ARRAY_OF_INT_9 temp = {{0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,OUTPUT,,temp);
  }
  __INIT_VAR(data__->INDEX,0,retain)
  __INIT_VAR(data__->HELP,0,retain)
}

// Code part
void ARRAY_AND_body__(ARRAY_AND *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  for(__GET_VAR(data__->INDEX,) = 0; __GET_VAR(data__->INDEX,) <= __GET_VAR(data__->SIZE,); __GET_VAR(data__->INDEX,)++) {
    __SET_VAR(data__->,HELP,,(__GET_VAR(data__->ARRAY1,.table[(__GET_VAR(data__->INDEX,)) - (0)]) + __GET_VAR(data__->ARRAY2,.table[(__GET_VAR(data__->INDEX,)) - (0)])));
    if ((__GET_VAR(data__->HELP,) == 0)) {
      __SET_VAR(data__->,OUTPUT,.table[(__GET_VAR(data__->INDEX,)) - (0)],0);
    } else if ((__GET_VAR(data__->HELP,) == 1)) {
      __SET_VAR(data__->,OUTPUT,.table[(__GET_VAR(data__->INDEX,)) - (0)],0);
    } else if ((__GET_VAR(data__->HELP,) == 2)) {
      __SET_VAR(data__->,OUTPUT,.table[(__GET_VAR(data__->INDEX,)) - (0)],1);
    } else {
      __SET_VAR(data__->,OUTPUT,.table[(__GET_VAR(data__->INDEX,)) - (0)],99);
    };
  };

  goto __end;

__end:
  return;
} // ARRAY_AND_body__() 





void ARRAY_XOR_init__(ARRAY_XOR *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->SIZE,8,retain)
  {
    static const __ARRAY_OF_INT_9 temp = {{0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,ARRAY1,,temp);
  }
  {
    static const __ARRAY_OF_INT_9 temp = {{0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,ARRAY2,,temp);
  }
  {
    static const __ARRAY_OF_INT_9 temp = {{0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,OUTPUT,,temp);
  }
  __INIT_VAR(data__->INDEX,0,retain)
  __INIT_VAR(data__->HELP,0,retain)
}

// Code part
void ARRAY_XOR_body__(ARRAY_XOR *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  for(__GET_VAR(data__->INDEX,) = 0; __GET_VAR(data__->INDEX,) <= __GET_VAR(data__->SIZE,); __GET_VAR(data__->INDEX,)++) {
    __SET_VAR(data__->,HELP,,(__GET_VAR(data__->ARRAY1,.table[(__GET_VAR(data__->INDEX,)) - (0)]) + __GET_VAR(data__->ARRAY2,.table[(__GET_VAR(data__->INDEX,)) - (0)])));
    if ((__GET_VAR(data__->HELP,) == 0)) {
      __SET_VAR(data__->,OUTPUT,.table[(__GET_VAR(data__->INDEX,)) - (0)],0);
    } else if ((__GET_VAR(data__->HELP,) == 1)) {
      __SET_VAR(data__->,OUTPUT,.table[(__GET_VAR(data__->INDEX,)) - (0)],1);
    } else {
      __SET_VAR(data__->,OUTPUT,.table[(__GET_VAR(data__->INDEX,)) - (0)],0);
    };
  };

  goto __end;

__end:
  return;
} // ARRAY_XOR_body__() 





void ARRAY_MASK_init__(ARRAY_MASK *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  {
    static const __ARRAY_OF_INT_9 temp = {{0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,MASK,,temp);
  }
  {
    static const __ARRAY_OF_INT_9 temp = {{0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,INPUT,,temp);
  }
  {
    static const __ARRAY_OF_INT_9 temp = {{0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,HELP,,temp);
  }
  {
    static const __ARRAY_OF_INT_9 temp = {{0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,MASK1,,temp);
  }
  {
    static const __ARRAY_OF_INT_9 temp = {{0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,MASK2,,temp);
  }
  __INIT_VAR(data__->OUTPUT,__BOOL_LITERAL(FALSE),retain)
  ARRAY_MASK1_init__(&data__->ARRAY_MASK1_INSTANCE,retain);
  ARRAY_MASK2_init__(&data__->ARRAY_MASK2_INSTANCE,retain);
  ARRAY_AND_init__(&data__->ARRAY_AND_INSTANCE,retain);
  ARRAY_XOR_init__(&data__->ARRAY_XOR_INSTANCE,retain);
  ARRAY_ALL_1_init__(&data__->ARRAY_ALL_1_INSTANCE,retain);
}

// Code part
void ARRAY_MASK_body__(ARRAY_MASK *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->ARRAY_XOR_INSTANCE.,ARRAY1,,__GET_VAR(data__->MASK,));
  ARRAY_XOR_body__(&data__->ARRAY_XOR_INSTANCE);
  __SET_VAR(data__->,MASK1,,__GET_VAR(data__->ARRAY_XOR_INSTANCE.OUTPUT));
  __SET_VAR(data__->ARRAY_MASK2_INSTANCE.,ARRAY1,,__GET_VAR(data__->MASK,));
  ARRAY_MASK2_body__(&data__->ARRAY_MASK2_INSTANCE);
  __SET_VAR(data__->,MASK2,,__GET_VAR(data__->ARRAY_MASK2_INSTANCE.OUTPUT));
  __SET_VAR(data__->ARRAY_AND_INSTANCE.,ARRAY1,,__GET_VAR(data__->INPUT,));
  __SET_VAR(data__->ARRAY_AND_INSTANCE.,ARRAY2,,__GET_VAR(data__->MASK1,));
  ARRAY_AND_body__(&data__->ARRAY_AND_INSTANCE);
  __SET_VAR(data__->,HELP,,__GET_VAR(data__->ARRAY_AND_INSTANCE.OUTPUT));
  __SET_VAR(data__->ARRAY_XOR_INSTANCE.,ARRAY1,,__GET_VAR(data__->HELP,));
  __SET_VAR(data__->ARRAY_XOR_INSTANCE.,ARRAY2,,__GET_VAR(data__->MASK2,));
  ARRAY_XOR_body__(&data__->ARRAY_XOR_INSTANCE);
  __SET_VAR(data__->,HELP,,__GET_VAR(data__->ARRAY_XOR_INSTANCE.OUTPUT));
  __SET_VAR(data__->ARRAY_ALL_1_INSTANCE.,ARRAY1,,__GET_VAR(data__->HELP,));
  ARRAY_ALL_1_body__(&data__->ARRAY_ALL_1_INSTANCE);
  __SET_VAR(data__->,OUTPUT,,__GET_VAR(data__->ARRAY_ALL_1_INSTANCE.OUTPUT));

  goto __end;

__end:
  return;
} // ARRAY_MASK_body__() 





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
  __INIT_EXTERNAL(BYTE,CONTROLLER_OUTPUT,data__->CONTROLLER_OUTPUT,retain)
  __INIT_EXTERNAL(INT,CURRENT_SUPERSTATE,data__->CURRENT_SUPERSTATE,retain)
  __INIT_EXTERNAL(WORD,SENSOR_OUTPUT,data__->SENSOR_OUTPUT,retain)
  __INIT_EXTERNAL(UINT,WDT,data__->WDT,retain)
  __INIT_EXTERNAL(WORD,SSM_TRANSITIONS,data__->SSM_TRANSITIONS,retain)
  __INIT_VAR(data__->CURRENT_STATE,0,retain)
  __INIT_VAR(data__->COL,0,retain)
  GET_MASK_init__(&data__->GET_MASK_INSTANCE,retain);
  ARRAY_MASK_init__(&data__->MASK_INSTANCE,retain);
  {
    static const __ARRAY_OF_INT_9 temp = {{0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,MASK,,temp);
  }
  __INIT_VAR(data__->ISSAMEASMASK,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->A0,0,retain)
  __INIT_VAR(data__->A1,0,retain)
  __INIT_VAR(data__->B0,0,retain)
  __INIT_VAR(data__->B1,0,retain)
  __INIT_VAR(data__->C0,0,retain)
  __INIT_VAR(data__->C1,0,retain)
  __INIT_VAR(data__->D0,0,retain)
  __INIT_VAR(data__->D1,0,retain)
  __INIT_VAR(data__->PROX,0,retain)
  {
    static const __ARRAY_OF_INT_9 temp = {{0,0,0,0,0,0,0,0,0}};
    __SET_VAR(data__->,INPUT,,temp);
  }
  {
    static const __ARRAY_OF_INT_10_10 temp = {{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,5,-1,6,-1,-1,-1,-1,-1,-1,-1,-1,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}};
    __SET_VAR(data__->,TRANSITION_MATRIX,,temp);
  }
  {
    static const __ARRAY_OF_INT_10_9 temp = {{-1,-1,-1,-1,-1,-1,-1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,-1,-1,-1,1,-1,-1,1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1}};
    __SET_VAR(data__->,MASKARRAY,,temp);
  }
  {
    static const __ARRAY_OF_WORD_11 temp = {{0x0001,0x0080,0x0020,0x0008,0x0014,0x0002,0x0012,0x0040,0x0004,0x0100,0}};
    __SET_VAR(data__->,MASKORIGINAL,,temp);
  }
  {
    static const __ARRAY_OF_BYTE_12 temp = {{0x00,0x80,0x20,0x30,0x20,0x28,0x00,0x04,0x40,0x00,0,0}};
    __SET_VAR(data__->,STATE_OUTPUT,,temp);
  }
}

// Code part
void AUTOPRODUCTION_body__(AUTOPRODUCTION *data__) {
  // Initialise TEMP variables

  if ((__GET_EXTERNAL(data__->CURRENT_SUPERSTATE,) == 1)) {
    for(__GET_VAR(data__->COL,) = 0; __GET_VAR(data__->COL,) <= 10; __GET_VAR(data__->COL,)++) {
      __SET_VAR(data__->,INPUT,.table[(0) - (0)],__GET_VAR(data__->A0,));
      __SET_VAR(data__->,INPUT,.table[(1) - (0)],__GET_VAR(data__->A1,));
      __SET_VAR(data__->,INPUT,.table[(2) - (0)],__GET_VAR(data__->B0,));
      __SET_VAR(data__->,INPUT,.table[(3) - (0)],__GET_VAR(data__->B1,));
      __SET_VAR(data__->,INPUT,.table[(4) - (0)],__GET_VAR(data__->C0,));
      __SET_VAR(data__->,INPUT,.table[(5) - (0)],__GET_VAR(data__->C1,));
      __SET_VAR(data__->,INPUT,.table[(6) - (0)],__GET_VAR(data__->D0,));
      __SET_VAR(data__->,INPUT,.table[(7) - (0)],__GET_VAR(data__->D1,));
      __SET_VAR(data__->,INPUT,.table[(8) - (0)],__GET_VAR(data__->PROX,));
      if ((__GET_VAR(data__->TRANSITION_MATRIX,.table[(__GET_VAR(data__->CURRENT_STATE,)) - (0)][(__GET_VAR(data__->COL,)) - (0)]) != -1)) {
        __SET_VAR(data__->GET_MASK_INSTANCE.,MASKS,,__GET_VAR(data__->MASKARRAY,));
        __SET_VAR(data__->GET_MASK_INSTANCE.,MASKINDEX,,__GET_VAR(data__->COL,));
        GET_MASK_body__(&data__->GET_MASK_INSTANCE);
        __SET_VAR(data__->,MASK,,__GET_VAR(data__->GET_MASK_INSTANCE.MASK));
        __SET_VAR(data__->MASK_INSTANCE.,MASK,,__GET_VAR(data__->MASK,));
        __SET_VAR(data__->MASK_INSTANCE.,INPUT,,__GET_VAR(data__->INPUT,));
        ARRAY_MASK_body__(&data__->MASK_INSTANCE);
        __SET_VAR(data__->,ISSAMEASMASK,,__GET_VAR(data__->MASK_INSTANCE.OUTPUT));
        if (__GET_VAR(data__->ISSAMEASMASK,)) {
          __SET_VAR(data__->,CURRENT_STATE,,__GET_VAR(data__->TRANSITION_MATRIX,.table[(__GET_VAR(data__->CURRENT_STATE,)) - (0)][(__GET_VAR(data__->COL,)) - (0)]));
          __SET_EXTERNAL(data__->,WDT,,0);
        };
      };
    };
    __SET_EXTERNAL(data__->,CONTROLLER_OUTPUT,,__GET_VAR(data__->STATE_OUTPUT,.table[(__GET_VAR(data__->CURRENT_STATE,)) - (0)]));
    if ((__GET_EXTERNAL(data__->WDT,) > 6000)) {
      __SET_EXTERNAL(data__->,SSM_TRANSITIONS,,(__GET_EXTERNAL(data__->SSM_TRANSITIONS,) | 256));
    };
    if ((__GET_VAR(data__->CURRENT_STATE,) == 9)) {
      __SET_EXTERNAL(data__->,SSM_TRANSITIONS,,(__GET_EXTERNAL(data__->SSM_TRANSITIONS,) | 4));
      __SET_VAR(data__->,CURRENT_STATE,,0);
    };
  };

  goto __end;

__end:
  return;
} // AUTOPRODUCTION_body__() 





// FUNCTION
INT TEST_FUNCTION(
  BOOL EN, 
  BOOL *__ENO, 
  INT MYCONSTANT)
{
  BOOL ENO = __BOOL_LITERAL(TRUE);
  INT TEST_FUNCTION = 0;

  // Control execution
  if (!EN) {
    if (__ENO != NULL) {
      *__ENO = __BOOL_LITERAL(FALSE);
    }
    return TEST_FUNCTION;
  }
  TEST_FUNCTION = MYCONSTANT;

  goto __end;

__end:
  if (__ENO != NULL) {
    *__ENO = ENO;
  }
  return TEST_FUNCTION;
}


// FUNCTION
BOOL ARRAY_EQUAL_FUNCTION(
  BOOL EN, 
  BOOL *__ENO, 
  __ARRAY_OF_INT_4 ARRAY1, 
  __ARRAY_OF_INT_4 ARRAY2)
{
  BOOL ENO = __BOOL_LITERAL(TRUE);
  INT SIZE = 0;
  BOOL HELP = __BOOL_LITERAL(TRUE);
  INT INDEX = 0;
  BOOL ARRAY_EQUAL_FUNCTION = __BOOL_LITERAL(FALSE);

  // Control execution
  if (!EN) {
    if (__ENO != NULL) {
      *__ENO = __BOOL_LITERAL(FALSE);
    }
    return ARRAY_EQUAL_FUNCTION;
  }
  for(INDEX = 0; INDEX <= SIZE; INDEX++) {
    if ((ARRAY1.table[(INDEX) - (0)] == ARRAY2.table[(INDEX) - (0)])) {
      HELP = __BOOL_LITERAL(TRUE);
    } else {
      HELP = __BOOL_LITERAL(FALSE);
    };
  };
  ARRAY_EQUAL_FUNCTION = __BOOL_LITERAL(TRUE);

  goto __end;

__end:
  if (__ENO != NULL) {
    *__ENO = ENO;
  }
  return ARRAY_EQUAL_FUNCTION;
}


void ARRAY_NOT_init__(ARRAY_NOT *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->SIZE,3,retain)
  {
    static const __ARRAY_OF_INT_4 temp = {{0,0,0,0}};
    __SET_VAR(data__->,ARRAY1,,temp);
  }
  {
    static const __ARRAY_OF_INT_4 temp = {{0,0,0,0}};
    __SET_VAR(data__->,OUTPUT,,temp);
  }
  __INIT_VAR(data__->INDEX,0,retain)
  __INIT_VAR(data__->HELP,0,retain)
}

// Code part
void ARRAY_NOT_body__(ARRAY_NOT *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  for(__GET_VAR(data__->INDEX,) = 0; __GET_VAR(data__->INDEX,) <= __GET_VAR(data__->SIZE,); __GET_VAR(data__->INDEX,)++) {
    __SET_VAR(data__->,HELP,,__GET_VAR(data__->ARRAY1,.table[(__GET_VAR(data__->INDEX,)) - (0)]));
    if ((__GET_VAR(data__->HELP,) == 0)) {
      __SET_VAR(data__->,OUTPUT,.table[(__GET_VAR(data__->INDEX,)) - (0)],1);
    } else if ((__GET_VAR(data__->HELP,) == 1)) {
      __SET_VAR(data__->,OUTPUT,.table[(__GET_VAR(data__->INDEX,)) - (0)],0);
    } else {
      __SET_VAR(data__->,OUTPUT,.table[(__GET_VAR(data__->INDEX,)) - (0)],99);
    };
  };

  goto __end;

__end:
  return;
} // ARRAY_NOT_body__() 





