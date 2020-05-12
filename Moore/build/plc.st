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
        ssm_transitions := ssm_transitions AND NOT 256;
        
        
        
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
    sensor_output : DWORD;
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
  VAR
    valueMatrix : ARRAY [0..11] OF DWORD;
    maskMatrix : ARRAY [0..11] OF DWORD;
    outputMatrix : ARRAY [0..10] OF DWORD;
  END_VAR
  VAR_EXTERNAL
    controller_output : DWORD;
    current_superstate : INT;
    sensor_output : DWORD;
    WDT : UINT;
    ssm_transitions : WORD;
  END_VAR
  VAR
    current_state : INT;
    column : INT;
  END_VAR

  (*TESTOVACÍ SEKVENCE - VÝSTUP ZE SENZORŮ*)
  (*
  VLOŽENÍ OBROBKU -- 202
  UPNUTÍ OBROBKU --170
  SPUŠTĚNÍ VŘETENE --186
  VYSUNUTÍ MOTORU C (VRTÁNÍ) --182
  ZASUNUTÍ MOTORU C (VRTÁNÍ) --186
  PRESUN OBROBKU DO DRUHÉ POLOHY --185
  VYSUNUTÍ MOTORU C (VRTÁNÍ) --181
  ZASUNUTÍ MOTORU C (VRTÁNÍ) --185
  VYPNUTÍ VŘETENE --169
  NÁVRAT DO PŮVODNÍ POLOHY --170
  UVOLNĚNÍ OBROBKU --202
  ODEBRÁNÍ OBROBKU --74
  *)

  VAR
    transitionMatrix: ARRAY[0..10,0..10] OF INT := [
    (* prox   Nprox   a1      b1      c1      c0d0    d1      c0d1       Nb      d0      a0 *)
       1,    -1,      -1,     -1,     -1,      -1,     -1,     -1,      -1,     -1,     -1, (* (0) ČEKÁ NA VLOŽENÍ OBROBKU  *)
      -1,    -1,       2,     -1,     -1,      -1,     -1,     -1,      -1,     -1,     -1, (* (1) ČEKÁ NA VYSUNUTÍ MOTORU A (UPNUTÍ) *)
      -1,    -1,      -1,      3,     -1,      -1,     -1,     -1,      -1,     -1,     -1, (* (2) ČEKÁ NA SPUŠTĚNÍ VŘETENE *)
      -1,    -1,      -1,     -1,      4,      -1,     -1,     -1,      -1,     -1,     -1, (* (3) ČEKÁ NA VYSUNUTÍ MOTORU C (VRTÁNÍ) *)
      -1,    -1,      -1,     -1,     -1,       5,     -1,      6,      -1,     -1,     -1, (* (4) ČEKÁ NA ZASUNUTÍ MOTORU C (VRTÁNÍ) *)
      -1,    -1,      -1,     -1,     -1,      -1,      3,     -1,      -1,     -1,     -1, (* (5) ČEKÁ NA VYSUNUTÍ MOTORU D (PŘESUN OBROBKU DO DRUHÉ POLOHY) *)
      -1,    -1,      -1,     -1,     -1,      -1,     -1,     -1,       7,     -1,     -1, (* (6) ČEKÁ NA VYPNUTÍ VŘETENE (KONEC VRTÁNÍ) *)
      -1,    -1,      -1,     -1,     -1,      -1,     -1,     -1,      -1,      8,     -1, (* (7) ČEKÁ NA ZASUNUTÍ MOTORU D (NÁVRAT DO PŮVODNÍ POLOHY) *)
      -1,    -1,      -1,     -1,     -1,      -1,     -1,     -1,      -1,     -1,      9, (* (8) ČEKÁ NA ZASUNUTÍ MOTORU A (UVOLNĚNÍ OBROBKU) *)
      -1,    10,      -1,     -1,     -1,      -1,     -1,     -1,      -1,     -1,     -1, (* (9) ČEKÁ NA ODEBRÁNÍ OBROBKU *)
      -1,    -1,      -1,     -1,     -1,      -1,     -1,     -1,      -1,     -1,     -1  (* (10) KONEČNÝ STAV SKOČÍ DO SUPERSTAVU INIT *)
    ];
  END_VAR 

  (*NAPLNĚNÍ MATICE MASEK*)
  (* ...  _ prox a0 a1 b c0 c1 d0 d1  - JEDNOTLIVÉ BITY PŘEDSTAVUJÍCÍ VSTUPY PLC V TOMTO POŘADÍ*)
  (*JEDNOTLIVÉ ŘÁDKY MAJÍ STEJNÉ POŘADÍ JAKO JSOU SLOUPCE MATICE PŘECHODU*)
  maskMatrix[0]  := 2#00000000_00000000_00000000_10000000; (*PROXIMITY SENZOR SEPNUTO -- 128*) 
  maskMatrix[1]  := 2#00000000_00000000_00000000_10000000; (*PROXIMITY SENZOR NESEPNUTO -- 128*)
  maskMatrix[2]  := 2#00000000_00000000_00000000_00100000; (*KONCOVÝ SENZOR MOTORU A V POLOZE VYSUNUTO --32*)
  maskMatrix[3]  := 2#00000000_00000000_00000000_00010000; (*SENZOR SEPNUTÍ VŘETENE B V POLOZE ZAPNUTO --16*)
  maskMatrix[4]  := 2#00000000_00000000_00000000_00000100; (*KONCOVÝ SENZOR MOTORU C V POLOZE VYSUNUTO --4*)
  maskMatrix[5]  := 2#00000000_00000000_00000000_00001010; (*KONCOVÝ SENZOR MOTORU C A D V POLOZE ZASUNUTO --10*)
  maskMatrix[6]  := 2#00000000_00000000_00000000_00000001; (*KONCOVÝ SENZOR MOTORU D V POLOZE VYSUNUTO --1*)
  maskMatrix[7]  := 2#00000000_00000000_00000000_00001001; (*KONCOVÝ SENZOR MOTORU D V POLOZE VYSUNUTO A KONCOVÝ SENZOR MOTORU C V POLOZE ZASUNUTO --9*)
  maskMatrix[8]  := 2#00000000_00000000_00000000_00010000; (*SENZOR SEPNUTÍ VŘETENE B V POLOZE VYPNUTO --16*)
  maskMatrix[9]  := 2#00000000_00000000_00000000_00000010; (*KONCOVÝ SENZOR MOTORU D V POLOZE ZASUNUTO --2*)
  maskMatrix[10] := 2#00000000_00000000_00000000_01000000; (*KONCOVÝ SENZOR MOTORU A V POLOZE ZASUNUTO --64*)

  (*NAPLNĚNÍ MATICE POŽADOVANÝCH HODNOT*)
  (* ... emg a0 _ a1 b0 b1 c0 c1 d0 d1 prox  - JEDNOTLIVÉ BITY PŘEDSTAVUJÍCÍ VSTUPY PLC V TOMTO POŘADÍ*)
  valueMatrix[0]  := 2#00000000_00000000_00000000_10000000; (*PROXIMITY SENZOR SEPNUTO*)
  valueMatrix[1]  := 2#00000000_00000000_00000000_00000000; (*PROXIMITY SENZOR NESEPNUTO*)
  valueMatrix[2]  := 2#00000000_00000000_00000000_00100000; (*KONCOVÝ SENZOR MOTORU A V POLOZE VYSUNUTO*)
  valueMatrix[3]  := 2#00000000_00000000_00000000_00010000; (*SENZOR SEPNUTÍ VŘETENE B V POLOZE ZAPNUTO*)
  valueMatrix[4]  := 2#00000000_00000000_00000000_00000100; (*KONCOVÝ SENZOR MOTORU C V POLOZE VYSUNUTO*)
  valueMatrix[5]  := 2#00000000_00000000_00000000_00001010; (*KONCOVÝ SENZOR MOTORU C A D V POLOZE ZASUNUTO*)
  valueMatrix[6]  := 2#00000000_00000000_00000000_00000001; (*KONCOVÝ SENZOR MOTORU D V POLOZE VYSUNUTO*)
  valueMatrix[7]  := 2#00000000_00000000_00000000_00001001; (*KONCOVÝ SENZOR MOTORU D V POLOZE VYSUNUTO A KONCOVÝ SENZOR MOTORU C V POLOZE ZASUNUTO*)
  valueMatrix[8]  := 2#00000000_00000000_00000000_00000000; (*SENZOR SEPNUTÍ VŘETENE B V POLOZE VYPNUTO*)
  valueMatrix[9]  := 2#00000000_00000000_00000000_00000010; (*KONCOVÝ SENZOR MOTORU D V POLOZE ZASUNUTO*)
  valueMatrix[10] := 2#00000000_00000000_00000000_01000000; (*KONCOVÝ SENZOR MOTORU A V POLOZE ZASUNUTO*)

  (*NAPLNĚNÍ MATICE VÝSTUPŮ*)
  (* ... A+ A- B C D+ D- 0 0   - JEDNOTLIVÉ BITY PŘEDSTAVUJÍCÍ AKTORY V TOMTO POŘADÍ*)
  outputMatrix[0]  := 2#00000000_00000000_00000000_00000000; (*INICIÁLNÍ STAV, ŽÁDNÝ VÝSTUP NA AKTORY*)
  outputMatrix[1]  := 2#00000000_00000000_00000000_10000000; (*UPNUTÍ OBROBKU*)
  outputMatrix[2]  := 2#00000000_00000000_00000000_00100000; (*SEPNUTÍ VŘETENE*)
  outputMatrix[3]  := 2#00000000_00000000_00000000_00110000; (*POSUV VŘETENE K OBROBKU*)
  outputMatrix[4]  := 2#00000000_00000000_00000000_00100000; (*POSUV VŘETENE OD OBROBKU*)
  outputMatrix[5]  := 2#00000000_00000000_00000000_00101000; (*PŘESUNUTÍ OBROBKU DO DRUHÉ POLOHY*)
  outputMatrix[6]  := 2#00000000_00000000_00000000_00000000; (*VYPNUTÍ VŘETENE*)
  outputMatrix[7]  := 2#00000000_00000000_00000000_00000100; (*NÁVRAT OBROBKU DO PŮVODNÍ POLOHY*)
  outputMatrix[8]  := 2#00000000_00000000_00000000_01000000; (*UVOLNĚNÍ OBROBKU*)
  outputMatrix[9]  := 2#00000000_00000000_00000000_00000000; (*ČEKÁNÍ NA ODEBRÁNÍ OBROBKU*)










  (* ZDE JE KONTROLOVÁNO ZDA JSME V DANÉM SUPERSTAVU *)
  IF current_superstate = 1 THEN
        
       
        
        (* PROCHÁZENÍ MATICE PŘECHODŮ *)
        FOR column := 0 TO 10 DO
          IF (transitionMatrix[current_state,column] <> -1) THEN
            IF (sensor_output AND maskMatrix[column]) = valueMatrix[column] THEN
              current_state :=  transitionMatrix[current_state,column];
              WDT := 0; (*RESET watchdogtimer*)
            END_IF;
          END_IF;
        END_FOR;
        
        (* actuator signal *)
        controller_output := outputMatrix[current_state];
        
        (* watchdog timer  - KONTROLUJE ZDA NEDOŠLO K ZASEKNUTÍ*)                                                 
        IF WDT > 3000 THEN
          (* set failure symptome WDOx as true *)
          ssm_transitions := ssm_transitions OR 256;
        END_IF;
        
       (* BYLO DOSAŽENO KONEČNÉHO STAVU SKOK DO IDDLE *)                                              
        IF current_state = 10 THEN
          ssm_transitions := ssm_transitions OR 4;
          current_state := 0;
        END_IF;
        
  END_IF;
END_PROGRAM

PROGRAM manualproduction
  VAR
    valueMatrix : ARRAY [0..11] OF DWORD;
    maskMatrix : ARRAY [0..11] OF DWORD;
    outputMatrix : ARRAY [0..10] OF DWORD;
  END_VAR
  VAR_EXTERNAL
    controller_output : DWORD;
    current_superstate : INT;
    sensor_output : DWORD;
    WDT : UINT;
    ssm_transitions : WORD;
  END_VAR
  VAR
    current_state : INT;
    column : INT;
  END_VAR

  (*TESTOVACÍ SEKVENCE - VÝSTUP ZE SENZORŮ*)
  (*
  VLOŽENÍ OBROBKU -- x202 ->16777290
  UPNUTÍ OBROBKU --x170 -> 16777418
  SPUŠTĚNÍ VŘETENE --x186 -> 16777386
  VYSUNUTÍ MOTORU C (VRTÁNÍ) --182
  ZASUNUTÍ MOTORU C (VRTÁNÍ) --186
  PRESUN OBROBKU DO DRUHÉ POLOHY --185
  VYSUNUTÍ MOTORU C (VRTÁNÍ) --181
  ZASUNUTÍ MOTORU C (VRTÁNÍ) --185
  VYPNUTÍ VŘETENE --169
  NÁVRAT DO PŮVODNÍ POLOHY --170
  UVOLNĚNÍ OBROBKU --202
  ODEBRÁNÍ OBROBKU --74
  *)

  VAR
    transitionMatrixMP: ARRAY[0..10,0..10] OF INT := [
    (* prox   Nprox   a1      b1      c1      c0d0    d1      c0d1       Nb      d0      a0 *)
       1,    -1,      -1,     -1,     -1,      -1,     -1,     -1,      -1,     -1,     -1, (* (0) ČEKÁ NA VLOŽENÍ OBROBKU  *)
      -1,    -1,       2,     -1,     -1,      -1,     -1,     -1,      -1,     -1,     -1, (* (1) ČEKÁ NA VYSUNUTÍ MOTORU A (UPNUTÍ) *)
      -1,    -1,      -1,      3,     -1,      -1,     -1,     -1,      -1,     -1,     -1, (* (2) ČEKÁ NA SPUŠTĚNÍ VŘETENE *)
      -1,    -1,      -1,     -1,      4,      -1,     -1,     -1,      -1,     -1,     -1, (* (3) ČEKÁ NA VYSUNUTÍ MOTORU C (VRTÁNÍ) *)
      -1,    -1,      -1,     -1,     -1,       5,     -1,      6,      -1,     -1,     -1, (* (4) ČEKÁ NA ZASUNUTÍ MOTORU C (VRTÁNÍ) *)
      -1,    -1,      -1,     -1,     -1,      -1,      3,     -1,      -1,     -1,     -1, (* (5) ČEKÁ NA VYSUNUTÍ MOTORU D (PŘESUN OBROBKU DO DRUHÉ POLOHY) *)
      -1,    -1,      -1,     -1,     -1,      -1,     -1,     -1,       7,     -1,     -1, (* (6) ČEKÁ NA VYPNUTÍ VŘETENE (KONEC VRTÁNÍ) *)
      -1,    -1,      -1,     -1,     -1,      -1,     -1,     -1,      -1,      8,     -1, (* (7) ČEKÁ NA ZASUNUTÍ MOTORU D (NÁVRAT DO PŮVODNÍ POLOHY) *)
      -1,    -1,      -1,     -1,     -1,      -1,     -1,     -1,      -1,     -1,      9, (* (8) ČEKÁ NA ZASUNUTÍ MOTORU A (UVOLNĚNÍ OBROBKU) *)
      -1,    10,      -1,     -1,     -1,      -1,     -1,     -1,      -1,     -1,     -1, (* (9) ČEKÁ NA ODEBRÁNÍ OBROBKU *)
      -1,    -1,      -1,     -1,     -1,      -1,     -1,     -1,      -1,     -1,     -1  (* (10) KONEČNÝ STAV SKOČÍ DO SUPERSTAVU INIT *)
    ];
  END_VAR 

  (*NAPLNĚNÍ MATICE MASEK*)
  (* nextStep_..._...  _ prox a0 a1 b c0 c1 d0 d1  - JEDNOTLIVÉ BITY PŘEDSTAVUJÍCÍ VSTUPY PLC V TOMTO POŘADÍ*)
  (*JEDNOTLIVÉ ŘÁDKY MAJÍ STEJNÉ POŘADÍ JAKO JSOU SLOUPCE MATICE PŘECHODU*)
  maskMatrix[0]  := 2#00000001_00000000_00000000_10000000; (*PROXIMITY SENZOR SEPNUTO*) 
  maskMatrix[1]  := 2#00000001_00000000_00000000_10000000; (*PROXIMITY SENZOR NESEPNUTO*)
  maskMatrix[2]  := 2#00000001_00000000_00000000_00100000; (*KONCOVÝ SENZOR MOTORU A V POLOZE VYSUNUTO*)
  maskMatrix[3]  := 2#00000001_00000000_00000000_00010000; (*SENZOR SEPNUTÍ VŘETENE B V POLOZE ZAPNUTO*)
  maskMatrix[4]  := 2#00000001_00000000_00000000_00000100; (*KONCOVÝ SENZOR MOTORU C V POLOZE VYSUNUTO*)
  maskMatrix[5]  := 2#00000001_00000000_00000000_00001010; (*KONCOVÝ SENZOR MOTORU C A D V POLOZE ZASUNUTO*)
  maskMatrix[6]  := 2#00000001_00000000_00000000_00000001; (*KONCOVÝ SENZOR MOTORU D V POLOZE VYSUNUTO*)
  maskMatrix[7]  := 2#00000001_00000000_00000000_00001001; (*KONCOVÝ SENZOR MOTORU D V POLOZE VYSUNUTO A KONCOVÝ SENZOR MOTORU C V POLOZE ZASUNUTO*)
  maskMatrix[8]  := 2#00000001_00000000_00000000_00010000; (*SENZOR SEPNUTÍ VŘETENE B V POLOZE VYPNUTO*)
  maskMatrix[9]  := 2#00000001_00000000_00000000_00000010; (*KONCOVÝ SENZOR MOTORU D V POLOZE ZASUNUTO*)
  maskMatrix[10] := 2#00000001_00000000_00000000_01000000; (*KONCOVÝ SENZOR MOTORU A V POLOZE ZASUNUTO*)

  (*NAPLNĚNÍ MATICE POŽADOVANÝCH HODNOT*)
  (* ... emg a0 _ a1 b0 b1 c0 c1 d0 d1 prox  - JEDNOTLIVÉ BITY PŘEDSTAVUJÍCÍ VSTUPY PLC V TOMTO POŘADÍ*)
  valueMatrix[0]  := 2#00000001_00000000_00000000_10000000; (*PROXIMITY SENZOR SEPNUTO*)
  valueMatrix[1]  := 2#00000001_00000000_00000000_00000000; (*PROXIMITY SENZOR NESEPNUTO*)
  valueMatrix[2]  := 2#00000001_00000000_00000000_00100000; (*KONCOVÝ SENZOR MOTORU A V POLOZE VYSUNUTO*)
  valueMatrix[3]  := 2#00000001_00000000_00000000_00010000; (*SENZOR SEPNUTÍ VŘETENE B V POLOZE ZAPNUTO*)
  valueMatrix[4]  := 2#00000001_00000000_00000000_00000100; (*KONCOVÝ SENZOR MOTORU C V POLOZE VYSUNUTO*)
  valueMatrix[5]  := 2#00000001_00000000_00000000_00001010; (*KONCOVÝ SENZOR MOTORU C A D V POLOZE ZASUNUTO*)
  valueMatrix[6]  := 2#00000001_00000000_00000000_00000001; (*KONCOVÝ SENZOR MOTORU D V POLOZE VYSUNUTO*)
  valueMatrix[7]  := 2#00000001_00000000_00000000_00001001; (*KONCOVÝ SENZOR MOTORU D V POLOZE VYSUNUTO A KONCOVÝ SENZOR MOTORU C V POLOZE ZASUNUTO*)
  valueMatrix[8]  := 2#00000001_00000000_00000000_00000000; (*SENZOR SEPNUTÍ VŘETENE B V POLOZE VYPNUTO*)
  valueMatrix[9]  := 2#00000001_00000000_00000000_00000010; (*KONCOVÝ SENZOR MOTORU D V POLOZE ZASUNUTO*)
  valueMatrix[10] := 2#00000001_00000000_00000000_01000000; (*KONCOVÝ SENZOR MOTORU A V POLOZE ZASUNUTO*)

  (*NAPLNĚNÍ MATICE VÝSTUPŮ*)
  (* ... A+ A- B C D+ D- 0 0   - JEDNOTLIVÉ BITY PŘEDSTAVUJÍCÍ AKTORY V TOMTO POŘADÍ*)
  outputMatrix[0]  := 2#00000000_00000000_00000000_00000000; (*INICIÁLNÍ STAV, ŽÁDNÝ VÝSTUP NA AKTORY*)
  outputMatrix[1]  := 2#00000000_00000000_00000000_10000000; (*UPNUTÍ OBROBKU*)
  outputMatrix[2]  := 2#00000000_00000000_00000000_00100000; (*SEPNUTÍ VŘETENE*)
  outputMatrix[3]  := 2#00000000_00000000_00000000_00110000; (*POSUV VŘETENE K OBROBKU*)
  outputMatrix[4]  := 2#00000000_00000000_00000000_00100000; (*POSUV VŘETENE OD OBROBKU*)
  outputMatrix[5]  := 2#00000000_00000000_00000000_00101000; (*PŘESUNUTÍ OBROBKU DO DRUHÉ POLOHY*)
  outputMatrix[6]  := 2#00000000_00000000_00000000_00000000; (*VYPNUTÍ VŘETENE*)
  outputMatrix[7]  := 2#00000000_00000000_00000000_00000100; (*NÁVRAT OBROBKU DO PŮVODNÍ POLOHY*)
  outputMatrix[8]  := 2#00000000_00000000_00000000_01000000; (*UVOLNĚNÍ OBROBKU*)
  outputMatrix[9]  := 2#00000000_00000000_00000000_00000000; (*ČEKÁNÍ NA ODEBRÁNÍ OBROBKU*)










  (* ZDE JE KONTROLOVÁNO ZDA JSME V DANÉM SUPERSTAVU *)
  IF current_superstate = 2 THEN
        
       
        
        (* PROCHÁZENÍ MATICE PŘECHODŮ *)
        FOR column := 0 TO 10 DO
          IF (transitionMatrixMP[current_state,column] <> -1) THEN
            IF (sensor_output AND maskMatrix[column]) = valueMatrix[column] THEN
              current_state :=  transitionMatrixMP[current_state,column];
              WDT := 0; (*RESET watchdogtimer*)
            END_IF;
          END_IF;
        END_FOR;
        
        (* actuator signal *)
        controller_output := outputMatrix[current_state];
        
        IF WDT > 3000 THEN
          (* set failure symptome WDOx as true *)
          WDT := 0;
        END_IF;
        
        
       (* BYLO DOSAŽENO KONEČNÉHO STAVU SKOK DO IDDLE *)                                              
        IF current_state = 10 THEN
          ssm_transitions := ssm_transitions OR 4;
          current_state := 0;
        END_IF;
        
  END_IF;
END_PROGRAM


CONFIGURATION Config0
  VAR_GLOBAL
    controller_output : DWORD;
    WDT : UINT;
    current_superstate : INT;
    sensor_output : DWORD;
    ssm_transitions : WORD;
  END_VAR

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#100ms,PRIORITY := 0);
    TASK WDT_clock(INTERVAL := T#10ms,PRIORITY := 0);
    PROGRAM SSM WITH task0 : superstate_machine;
    PROGRAM AP WITH task0 : autoproduction;
    PROGRAM MP WITH task0 : manualproduction;
    PROGRAM FAIL WITH task0 : failure;
    PROGRAM WDTimer WITH WDT_clock : watchdogtimer;
  END_RESOURCE
END_CONFIGURATION
