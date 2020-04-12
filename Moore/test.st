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
    controllerOutput : BYTE := 0;
  END_VAR

  VAR
  state: ARRAY[0..11] OF WORD  := [ (* 0 0 0 0 0 0 0 a0 a1 b0 b1 c0 c1 d0 d1 prox *)
    2#0000000101010100, (* init                  340 *)
    2#0000000101010101, (* prox -> 1             341 *)
    2#0000000011010101, (* a0 -> 0, a1 -> 1      213 *)
    2#0000000010110101, (* b0 -> 0, b1 -> 1      181 *)
    2#0000000010101101, (* c0 -> 0, c1 -> 1      173 *)
    2#0000000010110101, (* c0 -> 1, c1 -> 0      181 *)
    2#0000000010110011, (* d0 -> 0, d1 -> 1      179 *)
    2#0000000010101011, (* c0 -> 0, c1 -> 1      171 *)
    2#0000000010110011, (* c0 -> 1, c1 -> 0      179 *)
    2#0000000011010011, (* b0 -> 1, b1 -> 0      211 *)
    2#0000000011010101, (* d0 -> 1, d1 -> 0      213 *)
    2#0000000101010101 (* a0 -> 1, a1 -> 0       341 *)
    (* back to init state *)
    ];
  END_VAR

  VAR
  stateOutput: ARRAY[0..11] OF BYTE  := [ (* A+ A- B C D+ D- 0 0 /// State transitions *)
    2#00000000, (* init - wait                                       0 *)
    2#10000000, (* prox -> 1 - set A+                                128 *)
    2#00100000, (* a0 -> 0, a1 -> 1 - set B, reset A+ (bistable)     32 *)
    2#00110000, (* b0 -> 0, b1 -> 1 - set C                          48 *)
    2#00100000, (* c0 -> 0, c1 -> 1 - reset C                        32 *)
    2#00101000, (* c0 -> 1, c1 -> 0 - set D+                         40 *)
    2#00110000, (* d0 -> 0, d1 -> 1 -  set C, reset D+               48 *)
    2#00100000, (* c0 -> 0, c1 -> 1 - reset C                        32 *)
    2#00000000, (* c0 -> 1, c1 -> 0 - reset B                        0 *)
    2#00000100, (* b0 -> 1, b1 -> 0 - set D-                         8 *)
    2#01000000, (* d0 -> 1, d1 -> 0 - reset D-, set A-               64 *)
    2#00000000 (*  a0 -> 1, a1 -> 0 - reset A-                       0 *)
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


  IF sensorOutput = state[currentState+1] THEN
    currentState := currentState+1;
  END_IF;

  controllerOutput := stateOutput[currentState];
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : MooreAutomaton;
  END_RESOURCE
END_CONFIGURATION
