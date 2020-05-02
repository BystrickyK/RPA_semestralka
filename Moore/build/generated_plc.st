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

FUNCTION_BLOCK array_ALL_1
  VAR
    size : INT := 8;
  END_VAR
  VAR_INPUT
    array1 : ARRAY [0..8] OF INT;
  END_VAR
  VAR_OUTPUT
    output : BOOL;
  END_VAR
  VAR
    help : BOOL := true;
    index : INT;
  END_VAR

  FOR index := 0 TO size DO
    IF (array1[index]<>1) THEN
      help := false;
      EXIT;
    END_IF;
  END_FOR;

  output := help;
END_FUNCTION_BLOCK

FUNCTION_BLOCK array_EQUAL
  VAR
    size : INT;
  END_VAR
  VAR_INPUT
    array1 : ARRAY [0..3] OF INT;
    array2 : ARRAY [0..3] OF INT;
  END_VAR
  VAR_OUTPUT
    output : BOOL := true;
  END_VAR
  VAR
    index : INT;
  END_VAR

  FOR index := 0 TO size DO
    IF (array1[index]<>array2[index]) THEN
      output := false;
      EXIT;
    END_IF;
  END_FOR;
END_FUNCTION_BLOCK

FUNCTION_BLOCK get_mask
  VAR CONSTANT
    size : INT := 8;
  END_VAR
  VAR_INPUT
    masks : ARRAY [0..9,0..8] OF INT;
    maskIndex : INT;
  END_VAR
  VAR_OUTPUT
    mask : ARRAY [0..8] OF INT;
  END_VAR
  VAR
    index : INT;
  END_VAR

  FOR index := 0 TO size DO
    mask[index] := masks[maskIndex,index];
  END_FOR;
END_FUNCTION_BLOCK

FUNCTION_BLOCK array_MASK1
  VAR
    size : INT := 8;
  END_VAR
  VAR_INPUT
    array1 : ARRAY [0..8] OF INT;
  END_VAR
  VAR_OUTPUT
    output : ARRAY [0..8] OF INT;
  END_VAR
  VAR
    index : INT := 0;
    help : INT := 0;
  END_VAR


  FOR index := 0 TO size DO
    help := array1[index];
    
    IF (help = -1) THEN
      output[index]:= 0;
    ELSE
      output[index] := 1;
    END_IF;
    
  END_FOR;
END_FUNCTION_BLOCK

FUNCTION_BLOCK array_MASK2
  VAR CONSTANT
    size : INT := 8;
  END_VAR
  VAR_INPUT
    array1 : ARRAY [0..8] OF INT;
  END_VAR
  VAR_OUTPUT
    output : ARRAY [0..8] OF INT;
  END_VAR
  VAR
    index : INT := 0;
    help : INT := 0;
  END_VAR


  FOR index := 0 TO size DO
    help := array1[index];
    
    IF (help = 1) THEN
      output[index] := 0;
    ELSIF (help = 0) THEN
      output[index] := 1;
    ELSIF (help = -1) THEN
      output[index] := 1;
    ELSE
      output[index] := 99; (* This sould not happned *)
    END_IF;
    
    
  END_FOR;
END_FUNCTION_BLOCK

FUNCTION_BLOCK array_AND
  VAR
    size : INT := 8;
  END_VAR
  VAR_INPUT
    array1 : ARRAY [0..8] OF INT;
    array2 : ARRAY [0..8] OF INT;
  END_VAR
  VAR_OUTPUT
    output : ARRAY [0..8] OF INT;
  END_VAR
  VAR
    index : INT := 0;
    help : INT := 0;
  END_VAR


  FOR index := 0 TO size DO
    help := array1[index] + array2[index];
    
    IF (help = 0) THEN
      output[index]:= 0;
    ELSIF (help = 1) THEN
      output[index]:= 0;
    ELSIF (help = 2) THEN
      output[index] := 1;
    ELSE
      output[index] := 99; (* This should not happend *)
    END_IF;
    
  END_FOR;
END_FUNCTION_BLOCK

FUNCTION_BLOCK array_XOR
  VAR CONSTANT
    size : INT := 8;
  END_VAR
  VAR_INPUT
    array1 : ARRAY [0..8] OF INT;
    array2 : ARRAY [0..8] OF INT;
  END_VAR
  VAR_OUTPUT
    output : ARRAY [0..8] OF INT;
  END_VAR
  VAR
    index : INT := 0;
    help : INT := 0;
  END_VAR


  FOR index := 0 TO size DO
    help := array1[index] + array2[index];
    
    IF (help = 0) THEN
      output[index]:= 0;
    ELSIF (help = 1) THEN
      output[index]:= 1;
    ELSE
      output[index] := 0;
    END_IF;
    
  END_FOR;
END_FUNCTION_BLOCK

FUNCTION_BLOCK array_mask
  VAR_INPUT
    mask : ARRAY [0..8] OF INT;
    input : ARRAY [0..8] OF INT;
  END_VAR
  VAR
    help : ARRAY [0..8] OF INT;
    mask1 : ARRAY [0..8] OF INT;
    mask2 : ARRAY [0..8] OF INT;
  END_VAR
  VAR_OUTPUT
    output : BOOL;
  END_VAR
  VAR
    array_mask1_instance : array_MASK1;
    array_mask2_instance : array_MASK2;
    array_and_instance : array_AND;
    array_xor_instance : array_XOR;
    array_all_1_instance : array_ALL_1;
  END_VAR

  (* algorithm for mask*)
  array_xor_instance(array1 := mask, output => mask1);

  array_mask2_instance(array1 := mask, output => mask2);

  array_and_instance(array1 := input, array2 := mask1, output => help);

  array_xor_instance(array1 := help, array2 := mask2, output => help);

  array_all_1_instance(array1 := help, output => output);
END_FUNCTION_BLOCK

PROGRAM failure
  VAR_EXTERNAL
    current_superstate : INT;
    ssm_transitions : WORD;
  END_VAR

  (* permission *)
  IF current_superstate = 5 THEN
    
        (* set failure symptome WDOx as false *)
        ssm_transitions := ssm_transitions AND NOT 256;
        
        
        
  END_IF;
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
    get_mask_instance : get_mask;
    mask_instance : array_mask;
    mask : ARRAY [0..8] OF INT;
    isSameAsMask : BOOL;
    a0 : INT := 0;
    a1 : INT := 0;
    b0 : INT := 0;
    b1 : INT := 0;
    c0 : INT := 0;
    c1 : INT := 0;
    d0 : INT := 0;
    d1 : INT := 0;
    prox : INT := 0;
    input : ARRAY [0..8] OF INT;
  END_VAR

  VAR
  transition_matrix: ARRAY[0..9,0..9] OF INT := [
  (*     prox  a1      b0      c0      c0d0    d1      c0d1      b0      d0      a0 *)
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
    maskArray: ARRAY[0..9,0..8] OF INT := [
    -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,       1, (*       prox 1*)
    -1,       1,      -1,      -1,      -1,      -1,      -1,      -1,      -1, (*       a1 2*)
    -1,      -1,      -1,       1,      -1,      -1,      -1,      -1,      -1, (*       b0 3*)
    -1,      -1,      -1,      -1,      -1,       1,      -1,      -1,      -1, (*       c0 4*)
    -1,      -1,      -1,      -1,       1,      -1,       1,      -1,      -1, (*       c0d0 5*)
    -1,      -1,      -1,      -1,      -1,      -1,      -1,       1,      -1, (*       d1 6*)
    -1,      -1,      -1,      -1,       1,      -1,      -1,       1,      -1, (*       c0d1 7*)
    -1,      -1,       1,      -1,      -1,      -1,      -1,      -1,      -1, (*       b0 8*)
    -1,      -1,      -1,      -1,      -1,      -1,       1,      -1,      -1, (*       d0 9*)
     1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1 (*        a0 10*)
    ];
  END_VAR

  VAR
  maskOriginal: ARRAY[0..10] OF WORD  := [ (* 0 0 0 0 0 0 emg a0 a1 b0 b0 c0 c0 d0 d1 prox *)
    2#0000000_000000001, (*       prox 1*)
    2#0000000_010000000, (*       a1 2*)
    2#0000000_000100000, (*       b0 3*)
    2#0000000_000001000, (*       c0 4*)
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
    2#00110000, (* b0 -> 0, b0 -> 1 - set C                          48 3*)
    2#00100000, (* c0 -> 0, c0 -> 1 - reset C                        32 4*)
    2#00101000, (* c0 -> 1, c0 -> 0 - set D+                         40 5*)
    2#00000000, (* c0 -> 1, c0 -> 0 - reset B                        0 6*)
    2#00000100, (* b0 -> 1, b0 -> 0 - set D-                         8 7*)
    2#01000000, (* d0 -> 1, d1 -> 0 - reset D-, set A-               64 8*)
    2#00000000 (*  a0 -> 1, a1 -> 0 - reset A-                       0 9*)
    (* back to init state *)
    ];
  END_VAR








  (* permission *)
  IF current_superstate = 1 THEN
        
       
        
        (* interstate transitions *)
        FOR col := 0 TO 10 DO
          
          (* fills input of sensors *)
          input[0] := a0;
          input[1] := a1;
          input[2] := b0;
          input[3] := b1;
          input[4] := c0;
          input[5] := c1;
          input[6] := d0;
          input[7] := d1;
          input[8] := prox;
          
          IF (transition_matrix[current_state,col] <> -1) THEN
            
            get_mask_instance(masks := maskArray, maskIndex := col, mask => mask);
            
            mask_instance(mask := mask, input := input, output =>isSameAsMask);
            IF isSameAsMask THEN
              current_state :=  transition_matrix[current_state,col];
              WDT := 0; 
            END_IF;
          END_IF;
        END_FOR;
        
        
        
        
        
        
        
        
        (* actuator signal *)
        controller_output := state_output[current_state];
        
         (* watchdog timer *)
      (* TODO : make watchdogtimer "overflow" value state dependent instead of fixed 1000
          add an array with overflow values for each state *)                                                  
        IF WDT > 6000 THEN
          (* set failure symptome WDOx as true *)
          ssm_transitions := ssm_transitions OR 256;
        END_IF;
        
       (* final state reached *)                                              
        IF current_state = 9 THEN
          ssm_transitions := ssm_transitions OR 4;
          current_state := 0;
        END_IF;
        
  END_IF;
END_PROGRAM

FUNCTION test_function : INT
  VAR_INPUT
    MyConstant : INT;
  END_VAR

  test_function := MyConstant;
END_FUNCTION

FUNCTION array_EQUAL_function : BOOL
  VAR
    size : INT;
  END_VAR
  VAR_INPUT
    array1 : ARRAY [0..3] OF INT;
    array2 : ARRAY [0..3] OF INT;
  END_VAR
  VAR
    help : BOOL := true;
    index : INT;
  END_VAR

  FOR index := 0 TO size DO
    IF (array1[index]=array2[index]) THEN
        help := true;
    ELSE
      help := false;
    END_IF;
  END_FOR;

  array_EQUAL_function := true;
END_FUNCTION

FUNCTION_BLOCK array_NOT
  VAR
    size : INT := 3;
  END_VAR
  VAR_INPUT
    array1 : ARRAY [0..3] OF INT;
  END_VAR
  VAR_OUTPUT
    output : ARRAY [0..3] OF INT;
  END_VAR
  VAR
    index : INT := 0;
    help : INT := 0;
  END_VAR


  FOR index := 0 TO size DO
    help := array1[index];
    
    IF (help = 0) THEN
      output[index]:= 1;
    ELSIF (help = 1) THEN
      output[index] := 0;
    ELSE
      output[index] := 99; (* This should not happend *)
    END_IF;
    
  END_FOR;
END_FUNCTION_BLOCK


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
    PROGRAM FAIL WITH task0 : failure;
    PROGRAM WDTimer WITH WDT_clock : watchdogtimer;
  END_RESOURCE
END_CONFIGURATION
