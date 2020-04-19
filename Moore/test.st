FUNCTION_BLOCK superstateAP
  VAR_INPUT
    row : UINT := 0;
    col : UINT := 0;
  END_VAR
  VAR_OUTPUT
    out : INT := 0;
  END_VAR

  VAR
  transitionMatrix: ARRAY[0..10,0..10] OF INT := [
  (* emg   prox  a1      b1      c1      c0d0    d1      c0d1      b0      d0      a0 *)
      510,    1,    -1,     -1,     -1,      -1,     -1,     -1,      -1,     -1,     -1, (* START - 100 *)
      510,   -1,     2,     -1,     -1,      -1,     -1,     -1,      -1,     -1,     -1, (* 101 *)
      510,   -1,    -1,      3,     -1,      -1,     -1,     -1,      -1,     -1,     -1, (* 102 *)
      510,   -1,    -1,     -1,      4,      -1,     -1,     -1,      -1,     -1,     -1, (* 103 *)
      510,   -1,    -1,     -1,     -1,       5,     -1,      6,      -1,     -1,     -1, (* 104 *)
      510,   -1,    -1,     -1,     -1,      -1,      3,     -1,      -1,     -1,     -1, (* 105 *)
      510,   -1,    -1,     -1,     -1,      -1,     -1,     -1,       7,     -1,     -1, (* 106 *)
      510,   -1,    -1,     -1,     -1,      -1,     -1,     -1,      -1,      8,     -1, (* 107 *)
      510,   -1,    -1,     -1,     -1,      -1,     -1,     -1,      -1,     -1,      9, (* 108 *)
      510,   -1,    -1,     -1,     -1,      -1,     -1,     -1,      -1,     -1,     -1, (* 109 *)
      510,   -1,    -1,     -1,     -1,      -1,     -1,     -1,      -1,     -1,     -1 (* 110 *)
    ];
  END_VAR

  out := transitionMatrix[row,col];
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
    currentState : INT := 0;
    sensorOutput : WORD := 2#0000000000000000;
    controllerOutput : BYTE := 0;
    testVar : INT := 0;
    col : INT := 0;
    tmp : INT := 0;
    tmp0 : DINT := 0;
    superstate : superstateAP;
  END_VAR

  VAR
  state: ARRAY[0..11] OF WORD  := [ (* 0 0 0 0 0 0 0 a0 a1 b0 b1 c0 c1 d0 d1 prox *)
    2#0000000_101010100, (* init                  340 1*)
    2#0000000_101010101, (* prox -> 1             341 2*)
    2#0000000_011010101, (* a0 -> 0, a1 -> 1      213 3*)
    2#0000000_010110101, (* b0 -> 0, b1 -> 1      181 4*)
    2#0000000_010101101, (* c0 -> 0, c1 -> 1      173 5*)
    2#0000000_010110101, (* c0 -> 1, c1 -> 0      181 6*)
    2#0000000_010110011, (* d0 -> 0, d1 -> 1      179 7*)
    2#0000000_010101011, (* c0 -> 0, c1 -> 1      171 8*)
    2#0000000_010110011, (* c0 -> 1, c1 -> 0      179 9*)
    2#0000000_011010011, (* b0 -> 1, b1 -> 0      211 10*)
    2#0000000_011010101, (* d0 -> 1, d1 -> 0      213 11*)
    2#0000000_101010101  (* a0 -> 1, a1 -> 0      341 12*)
    (* back to init state *)
    ];
  END_VAR

  VAR
  transitionMasks: ARRAY[0..11] OF WORD  := [ (* 0 0 0 0 0 0 emg a0 a1 b0 b1 c0 c1 d0 d1 prox *)
    2#0000001_000000000,
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
  transitionMatrix: ARRAY[0..10,0..10] OF INT := [
  (* emg   prox  a1      b1      c1      c0d0    d1      c0d1      b0      d0      a0 *)
      510,    1,    -1,     -1,     -1,      -1,     -1,     -1,      -1,     -1,     -1, (* START - 100 *)
      510,   -1,     2,     -1,     -1,      -1,     -1,     -1,      -1,     -1,     -1, (* 101 *)
      510,   -1,    -1,      3,     -1,      -1,     -1,     -1,      -1,     -1,     -1, (* 102 *)
      510,   -1,    -1,     -1,      4,      -1,     -1,     -1,      -1,     -1,     -1, (* 103 *)
      510,   -1,    -1,     -1,     -1,       5,     -1,      6,      -1,     -1,     -1, (* 104 *)
      510,   -1,    -1,     -1,     -1,      -1,      3,     -1,      -1,     -1,     -1, (* 105 *)
      510,   -1,    -1,     -1,     -1,      -1,     -1,     -1,       7,     -1,     -1, (* 106 *)
      510,   -1,    -1,     -1,     -1,      -1,     -1,     -1,      -1,      8,     -1, (* 107 *)
      510,   -1,    -1,     -1,     -1,      -1,     -1,     -1,      -1,     -1,      9, (* 108 *)
      510,   -1,    -1,     -1,     -1,      -1,     -1,     -1,      -1,     -1,     -1, (* 109 *)
      510,   -1,    -1,     -1,     -1,      -1,     -1,     -1,      -1,     -1,     -1 (* 110 *)
    ];
  END_VAR 

  VAR
  stateOutput: ARRAY[0..11] OF BYTE  := [ (* A+ A- B C D+ D- 0 0 /// State transitions *)
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

  FOR col := 0 TO 10 DO
    IF (transitionMatrix[currentState MOD 100,col] <> -1) THEN
      IF (sensorOutput AND transitionMasks[col]) = transitionMasks[col] THEN
        currentState :=  transitionMatrix[currentState MOD 100,col];
        superstate(
        row:=4,
        col:=5,
        out => tmp);  
      END_IF;
    END_IF;
  END_FOR;

  controllerOutput := stateOutput[currentState];
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : MooreAutomaton;
  END_RESOURCE
END_CONFIGURATION
