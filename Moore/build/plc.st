TYPE
  LOGLEVEL : (CRITICAL, WARNING, INFO, DEBUG) := INFO;
END_TYPE

FUNCTION_BLOCK LOGGER
  VAR_INPUT
    TRIG : BOOL;
    MSG : STRING;
    LEVEL : LOGLEVEL := INFO;
  END_VAR
  VAR
    TRIG0 : BOOL;
  END_VAR

  IF TRIG AND NOT TRIG0 THEN
  {{
   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  }}
  END_IF;
  TRIG0:=TRIG;
END_FUNCTION_BLOCK



FUNCTION_BLOCK python_eval
  VAR_INPUT
    TRIG : BOOL;
    CODE : STRING;
  END_VAR
  VAR_OUTPUT
    ACK : BOOL;
    RESULT : STRING;
  END_VAR
  VAR
    STATE : DWORD;
    BUFFER : STRING;
    PREBUFFER : STRING;
    TRIGM1 : BOOL;
    TRIGGED : BOOL;
  END_VAR

  {extern void __PythonEvalFB(int, PYTHON_EVAL*);__PythonEvalFB(0, data__);}
END_FUNCTION_BLOCK

FUNCTION_BLOCK python_poll
  VAR_INPUT
    TRIG : BOOL;
    CODE : STRING;
  END_VAR
  VAR_OUTPUT
    ACK : BOOL;
    RESULT : STRING;
  END_VAR
  VAR
    STATE : DWORD;
    BUFFER : STRING;
    PREBUFFER : STRING;
    TRIGM1 : BOOL;
    TRIGGED : BOOL;
  END_VAR

  {extern void __PythonEvalFB(int, PYTHON_EVAL*);__PythonEvalFB(1,(PYTHON_EVAL*)(void*)data__);}
END_FUNCTION_BLOCK

FUNCTION_BLOCK python_gear
  VAR_INPUT
    N : UINT;
    TRIG : BOOL;
    CODE : STRING;
  END_VAR
  VAR_OUTPUT
    ACK : BOOL;
    RESULT : STRING;
  END_VAR
  VAR
    py_eval : python_eval;
    COUNTER : UINT;
    ADD10_OUT : UINT;
    EQ13_OUT : BOOL;
    SEL15_OUT : UINT;
    AND7_OUT : BOOL;
  END_VAR

  ADD10_OUT := ADD(COUNTER, 1);
  EQ13_OUT := EQ(N, ADD10_OUT);
  SEL15_OUT := SEL(EQ13_OUT, ADD10_OUT, 0);
  COUNTER := SEL15_OUT;
  AND7_OUT := AND(EQ13_OUT, TRIG);
  py_eval(TRIG := AND7_OUT, CODE := CODE);
  ACK := py_eval.ACK;
  RESULT := py_eval.RESULT;
END_FUNCTION_BLOCK


PROGRAM MooreAutomaton
  VAR
    a0 : BOOL := 1;
    a1 : BOOL := 0;
    b0 : BOOL := 1;
    b1 : BOOL := 0;
    c0 : BOOL := 1;
    c1 : BOOL := 0;
    d0 : BOOL := 1;
    d1 : BOOL := 0;
    prox : WORD := 0;
    currentState : UINT := 0;
    sensorOutput : WORD := 2#0000000000000000;
    controllerOutput : BYTE;
  END_VAR

  VAR
  state: ARRAY[0..11] OF WORD  := [ (* a0 a1 b0 b1 c0 c1 d0 d1 prox 0 0 0 0 0 0 0 *)
    2#1010101000000000, (* init *)
    2#1010101010000000, (* prox -> 1 *)
    2#0110101010000000, (* a0 -> 0, a1 -> 1 *)
    2#0101101010000000, (* b0 -> 0, b1 -> 1 *)
    2#0101011010000000, (* c0 -> 0, c1 -> 1 *)
    2#0101101010000000, (* c0 -> 1, c1 -> 0 *)
    2#0101100110000000, (* d0 -> 0, d1 -> 1 *)
    2#0101010110000000, (* c0 -> 0, c1 -> 1 *)
    2#0101100110000000, (* c0 -> 1, c1 -> 0 *)
    2#0110100110000000, (* b0 -> 1, b1 -> 0 *)
    2#0110101010000000, (* d0 -> 1, d1 -> 0 *)
    2#1010101010000000 (* a0 -> 1, a1 -> 0 *)
    (* back to init state *)
    ];
  END_VAR

  VAR
  stateOutput: ARRAY[0..11] OF BYTE  := [ (* A+ A- B C D+ D- 0 0 /// State transitions *)
    2#00000000, (* init - wait*)
    2#10000000, (* prox -> 1 - set A+ *)
    2#00100000, (* a0 -> 0, a1 -> 1 - set B, reset A+ (bistable)*)
    2#00110000, (* b0 -> 0, b1 -> 1 - set C*)
    2#00100000, (* c0 -> 0, c1 -> 1 - reset C*)
    2#00101000, (* c0 -> 1, c1 -> 0 - set D+*)
    2#00110000, (* d0 -> 0, d1 -> 1 -  set C, reset D+*)
    2#00100000, (* c0 -> 0, c1 -> 1 - reset C*)
    2#00000000, (* c0 -> 1, c1 -> 0 - reset B*)
    2#00000100, (* b0 -> 1, b1 -> 0 - set D-*)
    2#01000000, (* d0 -> 1, d1 -> 0 - reset D-, set A-*)
    2#00000000 (*  a0 -> 1, a1 -> 0 - reset A-*)
    (* back to init state *)
    ];
  END_VAR

  (*
  sensorOutput.0 := a0;
  sensorOutput.1 := a1;
  sensorOutput.2 := b0;
  sensorOutput.3 := b1;
  sensorOutput.4 := c0;
  sensorOutput.5 := c1;
  sensorOutput.6 := d0;
  sensorOutput.7 := d1;
  sensorOutput.8 := prox;
  *)

  IF sensorOutput = state(currentState) THEN
    currentState := currentState+1;
  END_IF;

  controllerOutput := stateOutput(currentState);
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : MooreAutomaton;
  END_RESOURCE
END_CONFIGURATION
