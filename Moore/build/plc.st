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


PROGRAM failure
  VAR_EXTERNAL
    current_superstate : INT;
    ssm_transitions : WORD;
  END_VAR

  (* permission *)
  IF current_superstate = 5 THEN
    
        (* set failure symptome WDOx as false *)
        ssm_transitions := ssm_transitions XOR 256;
        
        
        
  END_IF;
END_PROGRAM

PROGRAM superstate_machine
  VAR_EXTERNAL
    ssm_transitions : WORD;
    current_superstate : INT;
    WDT : UINT;
  END_VAR
  VAR
    col : INT := 0;
    tmp1 : WORD := 0;
    tmp2 : WORD := 0;
    tmp3 : INT := 123;
  END_VAR
  VAR_EXTERNAL
    sensor_output : WORD;
  END_VAR

  VAR
  transition_matrix: ARRAY[0..5,0..10] OF INT := [
  (*  1     2     4     8     16    32      64      128   256     512      1024
  (*  EM    SAP   APF   SMP   MPF   SSVC    SVCF    EMF   WDOx    RESx     BAD *)
      4,    1,    -1,   2,    -1,   3,      -1,     -1,   -1,     -1,       -1, (* IDLE *)
      4,    -1,   0,    -1,   -1,   -1,     -1,     -1,   5,      -1,       -1, (* AP *)
      4,    -1,   -1,   -1,   0,    -1,     -1,     -1,   -1,     -1,       -1, (* MP *)
      4,    -1,   -1,   -1,   -1,   -1,     0,      -1,   -1,     -1,       -1, (* SVC *)
      -1,   -1,   -1,   -1,   -1,   -1,     -1,     0,    -1,     -1,       -1, (* EMG *)
      4,    -1,   -1,   -1,   -1,   -1,     -1,     -1,   -1,      1,       3   (* FAIL *)    
    ];
  END_VAR

  VAR
  transition_masks: ARRAY[0..10] OF WORD := [
  (*  BAD RESx WDOx  EMF  SVCF SSVC  MPF SMP APF SAP EM   *)
  2#00000_00000000001,
  2#00000_00000000010,
  2#00000_00000000100,
  2#00000_00000001000,
  2#00000_00000010000,
  2#00000_00000100000,
  2#00000_00001000000,
  2#00000_00010000000,
  2#00000_00100000000,
  2#00000_01000000000,
  2#00000_10000000000
  ];
  END_VAR

  (* superstate transitions *)
  FOR col := 0 TO 10 DO
    IF (transition_matrix[current_superstate,col] <> -1) THEN
      IF (ssm_transitions AND transition_masks[col]) = transition_masks[col] THEN
        current_superstate :=  transition_matrix[current_superstate,col];
        WDT := 0; (*RESET WDT*)
      END_IF;
    END_IF;
  END_FOR;

END_PROGRAM

PROGRAM watchdogtimer
  VAR_EXTERNAL
    WDT : UINT;
  END_VAR

  WDT := WDT + 1;
END_PROGRAM

PROGRAM autoproduction
  VAR_EXTERNAL
    controller_output : BYTE;
    current_superstate : INT;
    sensor_output : WORD;
    WDT : UINT;
    ssm_transitions : WORD;
  END_VAR
  VAR
    current_state : INT;
    col : INT;
  END_VAR

  VAR
  transition_matrix: ARRAY[0..9,0..9] OF INT := [
  (*     prox  a1      b1      c1      c0d0    d1      c0d1      b0      d0      a0 *)
          1,    -1,     -1,     -1,      -1,     -1,     -1,      -1,     -1,     -1, (* START - 100 *)
         -1,     2,     -1,     -1,      -1,     -1,     -1,      -1,     -1,     -1, (* 101 *)
         -1,    -1,      3,     -1,      -1,     -1,     -1,      -1,     -1,     -1, (* 102 *)
         -1,    -1,     -1,      4,      -1,     -1,     -1,      -1,     -1,     -1, (* 103 *)
         -1,    -1,     -1,     -1,       5,     -1,      6,      -1,     -1,     -1, (* 104 *)
         -1,    -1,     -1,     -1,      -1,      3,     -1,      -1,     -1,     -1, (* 105 *)
         -1,    -1,     -1,     -1,      -1,     -1,     -1,       7,     -1,     -1, (* 106 *)
         -1,    -1,     -1,     -1,      -1,     -1,     -1,      -1,      8,     -1, (* 107 *)
         -1,    -1,     -1,     -1,      -1,     -1,     -1,      -1,     -1,      9, (* 108 *)
         -1,    -1,     -1,     -1,      -1,     -1,     -1,      -1,     -1,     -1 (* 109 *)
    ];
  END_VAR

  VAR
  mask: ARRAY[0..10] OF WORD  := [ (* 0 0 0 0 0 0 emg a0 a1 b0 b1 c0 c1 d0 d1 prox *)
    2#0000000_000000001, (*       prox 1*)
    2#0000000_010000000, (*       a1 2*)
    2#0000000_000100000, (*       b1 3*)
    2#0000000_000001000, (*       c1 4*)
    2#0000000_000010100, (*       c0d0 5*)
    2#0000000_000000010, (*       d1 6*)
    2#0000000_000010010, (*       c0d1 7*)
    2#0000000_001000000, (*       b0 8*)
    2#0000000_000000100, (*       d0 9*)
    2#0000000_100000000 (*        a0 10*)
    (* back to init state *)
    ];
  END_VAR

  VAR
  state_output: ARRAY[0..11] OF BYTE  := [ 
  (* A+ A- B C D+ D- 0 0 /// State transitions *)
    2#00000000, (* init - wait                                       0 0 *)
    2#10000000, (* prox -> 1 - set A+                                128 1*)
    2#00100000, (* a0 -> 0, a1 -> 1 - set B, reset A+ (bistable)     32 2*)
    2#00110000, (* b0 -> 0, b1 -> 1 - set C                          48 3*)
    2#00100000, (* c0 -> 0, c1 -> 1 - reset C                        32 4*)
    2#00101000, (* c0 -> 1, c1 -> 0 - set D+                         40 5*)
    2#00000000, (* c0 -> 1, c1 -> 0 - reset B                        0 6*)
    2#00000100, (* b0 -> 1, b1 -> 0 - set D-                         8 7*)
    2#01000000, (* d0 -> 1, d1 -> 0 - reset D-, set A-               64 8*)
    2#00000000 (*  a0 -> 1, a1 -> 0 - reset A-                       0 9*)
    (* back to init state *)
    ];
  END_VAR

  (* permission *)
  IF current_superstate = 1 THEN
        
        (* watchdog timer *)
  (* TODO : make watchdogtimer "overflow" value state dependent instead of fixed 1000
          add an array with overflow values for each state *)                                                  
        IF WDT > 6000 THEN
          (* set failure symptome WDOx as true *)
          ssm_transitions := ssm_transitions OR 256;
        END_IF;
        
        (* interstate transitions *)
        FOR col := 0 TO 10 DO
          IF (transition_matrix[current_state,col] <> -1) THEN
            IF (sensor_output AND mask[col]) = mask[col] THEN
              current_state :=  transition_matrix[current_state,col];
              WDT := 0; (*RESET watchdogtimer*)
            END_IF;
          END_IF;
        END_FOR;
        
        (* actuator signal *)
        controller_output := state_output[current_state];
        
  END_IF;
END_PROGRAM


CONFIGURATION Config0
  VAR_GLOBAL
    controller_output : BYTE;
    WDT : UINT;
    current_superstate : INT;
    sensor_output : WORD;
    ssm_transitions : WORD;
  END_VAR

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#100ms,PRIORITY := 0);
    TASK WDT_clock(INTERVAL := T#10ms,PRIORITY := 0);
    PROGRAM SSM WITH task0 : superstate_machine;
    PROGRAM AP WITH task0 : autoproduction;
    PROGRAM WDTimer WITH WDT_clock : watchdogtimer;
  END_RESOURCE
END_CONFIGURATION
