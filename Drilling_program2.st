PROGRAM superstate_machine
  VAR_EXTERNAL
    ssm_transitions : WORD;
    current_superstate : INT;
    WDT : UINT;
  END_VAR
  VAR
    col : INT := 0;
  END_VAR
  VAR_EXTERNAL
    sensor_output : WORD;
  END_VAR
  VAR
    EM : BOOL;
    SAP : BOOL;
    APF : BOOL;
    SMP : BOOL;
    MPF : BOOL;
    SSVC : BOOL;
    SVCF : BOOL;
    EMF : BOOL;
    WDOx : BOOL;
    RESx : BOOL;
    BAD : BOOL;
  END_VAR

  (*NAPLNENI MATICE PRECHODU*)
  VAR
  transition_matrix: ARRAY[0..5,0..10] OF INT := [
  (*  1     2     4     8     16    32      64      128   256     512      1024
  (*  EM    SAP   APF   SMP   MPF   SSVC    SVCF    EMF   WDOx    RESx     BAD *)
      4,    1,    -1,   2,    -1,   3,      -1,     -1,   -1,     -1,       -1, (* IDLE *)
      4,    -1,   0,    -1,   -1,   -1,     -1,     -1,   5,      -1,       -1, (* AP *)
      4,    -1,   -1,   -1,   0,    -1,     -1,     -1,   -1,     -1,       -1, (* MP *)
      4,    -1,   -1,   -1,   -1,   -1,      0,      -1,   -1,     -1,       -1, (* SVC *)
      -1,   -1,   -1,   -1,   -1,   -1,     -1,      0,    -1,     -1,       -1, (* EMG *)
      4,    -1,   -1,   -1,   -1,   -1,     -1,     -1,   -1,      1,        3   (* FAIL *)    
    ];
  END_VAR

  (*NAPLNENI MATICE MASEK, V TOMTO PRIPADE STACI POUZE TA, NEB NEPOTREBUJEME POROVNAVAT NULOVE HODNOTY*)
  VAR
  transition_masks: ARRAY[0..10] OF WORD := [
  (*  BAD RESx WDOx  _ EMF  SVCF SSVC  MPF SMP APF SAP EM   *)
  2#00000000_00000001,
  2#00000000_00000010,
  2#00000000_00000100,
  2#00000000_00001000,
  2#00000000_00010000,
  2#00000000_00100000,
  2#00000000_01000000,
  2#00000000_10000000,
  2#00000001_00000000,
  2#00000010_00000000,
  2#00000100_00000000
  ];
  END_VAR

  (* NAČTENÍ VSTUPŮ *)
        EM :=   WORD_TO_BOOL(ssm_transitions AND 2#00000000_00000001);
        SAP :=  WORD_TO_BOOL(ssm_transitions AND 2#00000000_00000010);
        APF :=  WORD_TO_BOOL(ssm_transitions AND 2#00000000_00000100);
        SMP :=  WORD_TO_BOOL(ssm_transitions AND 2#00000000_00001000);
        MPF :=  WORD_TO_BOOL(ssm_transitions AND 2#00000000_00010000);
        SSVC := WORD_TO_BOOL(ssm_transitions AND 2#00000000_00100000);
        SVCF := WORD_TO_BOOL(ssm_transitions AND 2#00000000_01000000);
        EMF :=  WORD_TO_BOOL(ssm_transitions AND 2#00000000_10000000);
        WDOx := WORD_TO_BOOL(ssm_transitions AND 2#00000001_00000000);
        RESx := WORD_TO_BOOL(ssm_transitions AND 2#00000010_00000000);
        BAD :=  WORD_TO_BOOL(ssm_transitions AND 2#00000100_00000000);
        

        


  (* superstate transitions *)
  FOR col := 0 TO 10 DO
    IF (transition_matrix[current_superstate,col] <> -1) THEN
      IF (ssm_transitions AND transition_masks[col]) = transition_masks[col] THEN
        current_superstate :=  transition_matrix[current_superstate,col];
        WDT := 0; (*RESET WDT*)
      END_IF;
    END_IF;
  END_FOR;

  ssm_transitions := ssm_transitions AND NOT 4;
END_PROGRAM

PROGRAM service
  VAR_EXTERNAL
    current_superstate : INT;
    sensor_output : WORD;
    ssm_transitions : WORD;
  END_VAR
  VAR
    in_Ap : BOOL;
    in_Am : BOOL;
    in_B : BOOL;
    in_C : BOOL;
    in_Dp : BOOL;
    in_Dm : BOOL;
    in_preasure_off : BOOL;
  END_VAR
  VAR_EXTERNAL
    out_Ap : BOOL;
    out_Am : BOOL;
    out_B : BOOL;
    out_C : BOOL;
    out_Dp : BOOL;
    out_Dm : BOOL;
    out_preasure_off : BOOL;
  END_VAR

  (* ZDE JE KONTROLOVÁNO ZDA JSME V DANÉM SUPERSTAVU *)
  IF current_superstate = 3 THEN
    
        (* NAČTENÍ VSTUPŮ *)
        in_Ap :=            WORD_TO_BOOL(sensor_output AND 2#10000000_00000000);
        in_Am :=            WORD_TO_BOOL(sensor_output AND 2#01000000_00000000);
        in_B :=             WORD_TO_BOOL(sensor_output AND 2#00100000_00000000);
        in_C :=             WORD_TO_BOOL(sensor_output AND 2#00010000_00000000);
        in_Dp :=            WORD_TO_BOOL(sensor_output AND 2#00001000_00000000);
        in_Dm :=            WORD_TO_BOOL(sensor_output AND 2#00000100_00000000);
        (* empty bit in_Dp :=              WORD_TO_BOOL(sensor_output AND 2#00000010_00000000);*)
        in_preasure_off :=  WORD_TO_BOOL(sensor_output AND 2#00000001_00000000);
        
       

        
        (* ZÁPIS VÝSTUPU DO JEDNOTLIVÝCH PROMĚNNÝCH (RUCNI POHYB MOTORU A VRETENE) *)
        out_Ap := in_Ap;
        out_Am := in_Am;
        out_B := in_B;
        out_C := in_C;
        out_Dp := in_Dp;
        out_Dm := in_Dm;
        
  END_IF;
END_PROGRAM

PROGRAM failure
  VAR_EXTERNAL
    current_superstate : INT;
    ssm_transitions : WORD;
  END_VAR

  (* SEPNUTI SUPERSTAVU *)
  IF current_superstate = 5 THEN
    
        (* VYNULUJE PRIZNAK PRETECENI TIMERU *)
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
  VAR
    valueMatrix : ARRAY [0..11] OF WORD;
    maskMatrix : ARRAY [0..11] OF WORD;
    outputMatrix : ARRAY [0..10] OF WORD;
  END_VAR
  VAR_EXTERNAL
    controller_output : WORD;
    current_superstate : INT;
    sensor_output : WORD;
    WDT : UINT;
    ssm_transitions : WORD;
    current_state : INT;
  END_VAR
  VAR
    column : INT;
  END_VAR
  VAR_EXTERNAL
    out_Ap : BOOL;
    out_Am : BOOL;
    out_B : BOOL;
    out_C : BOOL;
    out_Dp : BOOL;
    out_Dm : BOOL;
  END_VAR
  VAR
    in_prox : BOOL;
    in_a0 : BOOL;
    in_a1 : BOOL;
    in_b : BOOL;
    in_c0 : BOOL;
    in_c1 : BOOL;
    in_d0 : BOOL;
    in_d1 : BOOL;
  END_VAR

  (*TESTOVACÍ SEKVENCE - VÝSTUP ZE SENZORŮ*)
  (*
  PRVNÍ NACTENÍ SENZORŮ --74
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
  maskMatrix[0]  := 2#00000000_10000000; (*PROXIMITY SENZOR SEPNUTO -- 128*) 
  maskMatrix[1]  := 2#00000000_10000000; (*PROXIMITY SENZOR NESEPNUTO -- 128*)
  maskMatrix[2]  := 2#00000000_00100000; (*KONCOVÝ SENZOR MOTORU A V POLOZE VYSUNUTO --32*)
  maskMatrix[3]  := 2#00000000_00010000; (*SENZOR SEPNUTÍ VŘETENE B V POLOZE ZAPNUTO --16*)
  maskMatrix[4]  := 2#00000000_00000100; (*KONCOVÝ SENZOR MOTORU C V POLOZE VYSUNUTO --4*)
  maskMatrix[5]  := 2#00000000_00001010; (*KONCOVÝ SENZOR MOTORU C A D V POLOZE ZASUNUTO --10*)
  maskMatrix[6]  := 2#00000000_00000001; (*KONCOVÝ SENZOR MOTORU D V POLOZE VYSUNUTO --1*)
  maskMatrix[7]  := 2#00000000_00001001; (*KONCOVÝ SENZOR MOTORU D V POLOZE VYSUNUTO A KONCOVÝ SENZOR MOTORU C V POLOZE ZASUNUTO --9*)
  maskMatrix[8]  := 2#00000000_00010000; (*SENZOR SEPNUTÍ VŘETENE B V POLOZE VYPNUTO --16*)
  maskMatrix[9]  := 2#00000000_00000010; (*KONCOVÝ SENZOR MOTORU D V POLOZE ZASUNUTO --2*)
  maskMatrix[10] := 2#00000000_01000000; (*KONCOVÝ SENZOR MOTORU A V POLOZE ZASUNUTO --64*)

  (*NAPLNĚNÍ MATICE POŽADOVANÝCH HODNOT*)
  (* ... emg a0 _ a1 b0 b1 c0 c1 d0 d1 prox  - JEDNOTLIVÉ BITY PŘEDSTAVUJÍCÍ VSTUPY PLC V TOMTO POŘADÍ*)
  valueMatrix[0]  := 2#00000000_10000000; (*PROXIMITY SENZOR SEPNUTO*)
  valueMatrix[1]  := 2#00000000_00000000; (*PROXIMITY SENZOR NESEPNUTO*)
  valueMatrix[2]  := 2#00000000_00100000; (*KONCOVÝ SENZOR MOTORU A V POLOZE VYSUNUTO*)
  valueMatrix[3]  := 2#00000000_00010000; (*SENZOR SEPNUTÍ VŘETENE B V POLOZE ZAPNUTO*)
  valueMatrix[4]  := 2#00000000_00000100; (*KONCOVÝ SENZOR MOTORU C V POLOZE VYSUNUTO*)
  valueMatrix[5]  := 2#00000000_00001010; (*KONCOVÝ SENZOR MOTORU C A D V POLOZE ZASUNUTO*)
  valueMatrix[6]  := 2#00000000_00000001; (*KONCOVÝ SENZOR MOTORU D V POLOZE VYSUNUTO*)
  valueMatrix[7]  := 2#00000000_00001001; (*KONCOVÝ SENZOR MOTORU D V POLOZE VYSUNUTO A KONCOVÝ SENZOR MOTORU C V POLOZE ZASUNUTO*)
  valueMatrix[8]  := 2#00000000_00000000; (*SENZOR SEPNUTÍ VŘETENE B V POLOZE VYPNUTO*)
  valueMatrix[9]  := 2#00000000_00000010; (*KONCOVÝ SENZOR MOTORU D V POLOZE ZASUNUTO*)
  valueMatrix[10] := 2#00000000_01000000; (*KONCOVÝ SENZOR MOTORU A V POLOZE ZASUNUTO*)

  (*NAPLNĚNÍ MATICE VÝSTUPŮ*)
  (* ... A+ A- B C D+ D- 0 0   - JEDNOTLIVÉ BITY PŘEDSTAVUJÍCÍ AKTORY V TOMTO POŘADÍ*)
  outputMatrix[0]  := 2#00000000_01000100; (*INICIÁLNÍ STAV, ŽÁDNÝ VÝSTUP NA AKTORY*)
  outputMatrix[1]  := 2#00000000_10000000; (*UPNUTÍ OBROBKU*)
  outputMatrix[2]  := 2#00000000_00100000; (*SEPNUTÍ VŘETENE*)
  outputMatrix[3]  := 2#00000000_00110000; (*POSUV VŘETENE K OBROBKU*)
  outputMatrix[4]  := 2#00000000_00100000; (*POSUV VŘETENE OD OBROBKU*)
  outputMatrix[5]  := 2#00000000_00101000; (*PŘESUNUTÍ OBROBKU DO DRUHÉ POLOHY*)
  outputMatrix[6]  := 2#00000000_00000000; (*VYPNUTÍ VŘETENE*)
  outputMatrix[7]  := 2#00000000_00000100; (*NÁVRAT OBROBKU DO PŮVODNÍ POLOHY*)
  outputMatrix[8]  := 2#00000000_01000000; (*UVOLNĚNÍ OBROBKU*)
  outputMatrix[9]  := 2#00000000_00000000; (*ČEKÁNÍ NA ODEBRÁNÍ OBROBKU*)










  (* ZDE JE KONTROLOVÁNO ZDA JSME V DANÉM SUPERSTAVU *)
  IF current_superstate = 1 THEN
    
        (* NAČTENÍ VSTUPŮ *)
        in_prox := WORD_TO_BOOL(sensor_output AND 2#00000000_00000000_00000000_10000000);
        in_a0 := WORD_TO_BOOL(sensor_output AND 2#00000000_00000000_00000000_01000000);
        in_a1 := WORD_TO_BOOL(sensor_output AND 2#00000000_00000000_00000000_00100000);
        in_b := WORD_TO_BOOL(sensor_output AND 2#00000000_00000000_00000000_00010000);
        in_c0 := WORD_TO_BOOL(sensor_output AND 2#00000000_00000000_00000000_00001000);
        in_c1 := WORD_TO_BOOL(sensor_output AND 2#00000000_00000000_00000000_00000100);
        in_d0 := WORD_TO_BOOL(sensor_output AND 2#00000000_00000000_00000000_00000010);
        in_d1 := WORD_TO_BOOL(sensor_output AND 2#00000000_00000000_00000000_00000001);
        
       
        
        (* PROCHÁZENÍ MATICE PŘECHODŮ *)
        FOR column := 0 TO 10 DO
          IF (transitionMatrix[current_state,column] <> -1) THEN
            IF (sensor_output AND maskMatrix[column]) = valueMatrix[column] THEN
              current_state :=  transitionMatrix[current_state,column];
              WDT := 0; (*RESET watchdogtimer*)
            END_IF;
          END_IF;
        END_FOR;
        
        (* ZÁPIS SIGNÁLU NA VÝSTUP *)
        controller_output := outputMatrix[current_state];
        
        (* ZÁPIS VÝSTUPU DO JEDNOTLIVÝCH PROMĚNNÝCH *)
        out_Ap := WORD_TO_BOOL(controller_output AND 2#00000000_00000000_00000000_10000000);
        out_Am := WORD_TO_BOOL(controller_output AND 2#00000000_00000000_00000000_01000000);
        out_B := WORD_TO_BOOL(controller_output AND 2#00000000_00000000_00000000_00100000);
        out_C := WORD_TO_BOOL(controller_output AND 2#00000000_00000000_00000000_00010000);
        out_Dp := WORD_TO_BOOL(controller_output AND 2#00000000_00000000_00000000_00001000);
        out_Dm := WORD_TO_BOOL(controller_output AND 2#00000000_00000000_00000000_00000100);
        
        (* watchdog timer  - KONTROLUJE ZDA NEDOŠLO K ZASEKNUTÍ*)                                                 
        IF WDT > 3000 THEN
          (* set failure symptome WDOx as true *)
          ssm_transitions := 256;
        END_IF;
        
       (* BYLO DOSAŽENO KONEČNÉHO STAVU SKOK DO IDDLE *)                                              
        IF current_state = 10 THEN
          ssm_transitions := 4;
          current_state := 0;
        END_IF;
        
  END_IF;
END_PROGRAM

PROGRAM manualproduction
  VAR
    valueMatrix : ARRAY [0..11] OF WORD;
    maskMatrix : ARRAY [0..11] OF WORD;
    outputMatrix : ARRAY [0..10] OF WORD;
  END_VAR
  VAR_EXTERNAL
    controller_output : WORD;
    current_superstate : INT;
    sensor_output : WORD;
    WDT : UINT;
    ssm_transitions : WORD;
    current_state : INT;
  END_VAR
  VAR
    column : INT;
  END_VAR

  (*TESTOVACÍ SEKVENCE - VÝSTUP ZE SENZORŮ*)
  (*
  VLOŽENÍ OBROBKU -- x202 ->16777418
  UPNUTÍ OBROBKU --x170 -> 16777386
  SPUŠTĚNÍ VŘETENE --x186 -> 16777402
  VYSUNUTÍ MOTORU C (VRTÁNÍ) --x182 -> 16777398
  ZASUNUTÍ MOTORU C (VRTÁNÍ) --x186 -> 16777402
  PRESUN OBROBKU DO DRUHÉ POLOHY --x185 ->16777401
  VYSUNUTÍ MOTORU C (VRTÁNÍ) --x181 ->16777397
  ZASUNUTÍ MOTORU C (VRTÁNÍ) --x185 -> 16777401
  VYPNUTÍ VŘETENE --x169 -> 16777385
  NÁVRAT DO PŮVODNÍ POLOHY --x170 ->16777386
  UVOLNĚNÍ OBROBKU --16777418
  ODEBRÁNÍ OBROBKU --16777290
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
  maskMatrix[0]  := 2#00000000_10000000; (*PROXIMITY SENZOR SEPNUTO*) 
  maskMatrix[1]  := 2#00000000_10000000; (*PROXIMITY SENZOR NESEPNUTO*)
  maskMatrix[2]  := 2#00000000_00100000; (*KONCOVÝ SENZOR MOTORU A V POLOZE VYSUNUTO*)
  maskMatrix[3]  := 2#00000000_00010000; (*SENZOR SEPNUTÍ VŘETENE B V POLOZE ZAPNUTO*)
  maskMatrix[4]  := 2#00000000_00000100; (*KONCOVÝ SENZOR MOTORU C V POLOZE VYSUNUTO*)
  maskMatrix[5]  := 2#00000000_00001010; (*KONCOVÝ SENZOR MOTORU C A D V POLOZE ZASUNUTO*)
  maskMatrix[6]  := 2#00000000_00000001; (*KONCOVÝ SENZOR MOTORU D V POLOZE VYSUNUTO*)
  maskMatrix[7]  := 2#00000000_00001001; (*KONCOVÝ SENZOR MOTORU D V POLOZE VYSUNUTO A KONCOVÝ SENZOR MOTORU C V POLOZE ZASUNUTO*)
  maskMatrix[8]  := 2#00000000_00010000; (*SENZOR SEPNUTÍ VŘETENE B V POLOZE VYPNUTO*)
  maskMatrix[9]  := 2#00000000_00000010; (*KONCOVÝ SENZOR MOTORU D V POLOZE ZASUNUTO*)
  maskMatrix[10] := 2#00000000_01000000; (*KONCOVÝ SENZOR MOTORU A V POLOZE ZASUNUTO*)

  (*NAPLNĚNÍ MATICE POŽADOVANÝCH HODNOT*)
  (* ... emg a0 _ a1 b0 b1 c0 c1 d0 d1 prox  - JEDNOTLIVÉ BITY PŘEDSTAVUJÍCÍ VSTUPY PLC V TOMTO POŘADÍ*)
  valueMatrix[0]  := 2#00000000_10000000; (*PROXIMITY SENZOR SEPNUTO*)
  valueMatrix[1]  := 2#00000000_00000000; (*PROXIMITY SENZOR NESEPNUTO*)
  valueMatrix[2]  := 2#00000000_00100000; (*KONCOVÝ SENZOR MOTORU A V POLOZE VYSUNUTO*)
  valueMatrix[3]  := 2#00000000_00010000; (*SENZOR SEPNUTÍ VŘETENE B V POLOZE ZAPNUTO*)
  valueMatrix[4]  := 2#00000000_00000100; (*KONCOVÝ SENZOR MOTORU C V POLOZE VYSUNUTO*)
  valueMatrix[5]  := 2#00000000_00001010; (*KONCOVÝ SENZOR MOTORU C A D V POLOZE ZASUNUTO*)
  valueMatrix[6]  := 2#00000000_00000001; (*KONCOVÝ SENZOR MOTORU D V POLOZE VYSUNUTO*)
  valueMatrix[7]  := 2#00000000_00001001; (*KONCOVÝ SENZOR MOTORU D V POLOZE VYSUNUTO A KONCOVÝ SENZOR MOTORU C V POLOZE ZASUNUTO*)
  valueMatrix[8]  := 2#00000000_00000000; (*SENZOR SEPNUTÍ VŘETENE B V POLOZE VYPNUTO*)
  valueMatrix[9]  := 2#00000000_00000010; (*KONCOVÝ SENZOR MOTORU D V POLOZE ZASUNUTO*)
  valueMatrix[10] := 2#00000000_01000000; (*KONCOVÝ SENZOR MOTORU A V POLOZE ZASUNUTO*)

  (*NAPLNĚNÍ MATICE VÝSTUPŮ*)
  (* ... A+ A- B C D+ D- 0 0   - JEDNOTLIVÉ BITY PŘEDSTAVUJÍCÍ AKTORY V TOMTO POŘADÍ*)
  outputMatrix[0]  := 2#00000000_00000000; (*INICIÁLNÍ STAV, ŽÁDNÝ VÝSTUP NA AKTORY*)
  outputMatrix[1]  := 2#00000000_10000000; (*UPNUTÍ OBROBKU*)
  outputMatrix[2]  := 2#00000000_00100000; (*SEPNUTÍ VŘETENE*)
  outputMatrix[3]  := 2#00000000_00110000; (*POSUV VŘETENE K OBROBKU*)
  outputMatrix[4]  := 2#00000000_00100000; (*POSUV VŘETENE OD OBROBKU*)
  outputMatrix[5]  := 2#00000000_00101000; (*PŘESUNUTÍ OBROBKU DO DRUHÉ POLOHY*)
  outputMatrix[6]  := 2#00000000_00000000; (*VYPNUTÍ VŘETENE*)
  outputMatrix[7]  := 2#00000000_00000100; (*NÁVRAT OBROBKU DO PŮVODNÍ POLOHY*)
  outputMatrix[8]  := 2#00000000_01000000; (*UVOLNĚNÍ OBROBKU*)
  outputMatrix[9]  := 2#00000000_00000000; (*ČEKÁNÍ NA ODEBRÁNÍ OBROBKU*)










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
        
        
        
       (* BYLO DOSAŽENO KONEČNÉHO STAVU SKOK DO IDDLE *)                                              
        IF current_state = 10 THEN
          ssm_transitions := 4;
          current_state := 0;
        END_IF;
        
  END_IF;
END_PROGRAM

PROGRAM emerigency
  VAR
    outputMatrix : ARRAY [0..10] OF WORD;
  END_VAR
  VAR_EXTERNAL
    controller_output : WORD;
    current_superstate : INT;
    sensor_output : WORD;
    ssm_transitions : WORD;
    current_state : INT;
    out_Ap : BOOL;
    out_Am : BOOL;
    out_B : BOOL;
    out_C : BOOL;
    out_Dp : BOOL;
    out_Dm : BOOL;
  END_VAR
  VAR
    out_preasure_off : BOOL;
  END_VAR



  (*NAPLNĚNÍ MATICE VÝSTUPŮ*)
  (* ... A+ A- B C D+ D- 0 preasure_off   - JEDNOTLIVÉ BITY PŘEDSTAVUJÍCÍ AKTORY V TOMTO POŘADÍ*)
  outputMatrix[0]  := 2#00000000_00000001; (*INICIÁLNÍ STAV - vypne tlak*)
  outputMatrix[1]  := 2#00000000_01000000; (*UPNUTÍ OBROBKU - ZASUNU MOTOR A ZPET*)
  outputMatrix[2]  := 2#00000000_00000000; (*SEPNUTÍ VŘETENE - VYPNU VRETENO*)
  outputMatrix[3]  := 2#00000000_00000000; (*POSUV VŘETENE K OBROBKU - VRATIM POSUV A VYPNU VRETENO*)
  outputMatrix[4]  := 2#00000000_00000001; (*POSUV VŘETENE OD OBROBKU - VYPNU TLAK*)
  outputMatrix[5]  := 2#00000000_00000100; (*PŘESUNUTÍ OBROBKU DO DRUHÉ POLOHY - PRESUNU ZPET,VYPNU VRETENO*)
  outputMatrix[6]  := 2#00000000_00000001; (*VYPNUTÍ VŘETENE - VYPNU TLAK, NEMUZE NASTAT DALSI KROK*)
  outputMatrix[7]  := 2#00000000_00001000; (*NÁVRAT OBROBKU DO PŮVODNÍ POLOHY - OBRATIM CHOD MOTORU*)
  outputMatrix[8]  := 2#00000000_10000000; (*UVOLNĚNÍ OBROBKU - OBRATIM CHOD MOTORU*)
  outputMatrix[9]  := 2#00000000_00000001; (*ČEKÁNÍ NA ODEBRÁNÍ OBROBKU - VYPNU TLAK*)



  (* ZDE JE KONTROLOVÁNO ZDA JSME V DANÉM SUPERSTAVU *)
  IF current_superstate = 4 THEN
        
        
        (* ZÁPIS SIGNÁLU NA VÝSTUP *)
        controller_output := outputMatrix[current_state];
        
        (* ZÁPIS VÝSTUPU DO JEDNOTLIVÝCH PROMĚNNÝCH *)
        out_Ap := WORD_TO_BOOL(controller_output AND 2#00000000_10000000);
        out_Am := WORD_TO_BOOL(controller_output AND 2#00000000_01000000);
        out_B := WORD_TO_BOOL(controller_output AND 2#00000000_00100000);
        out_C := WORD_TO_BOOL(controller_output AND 2#00000000_00010000);
        out_Dp := WORD_TO_BOOL(controller_output AND 2#00000000_00001000);
        out_Dm := WORD_TO_BOOL(controller_output AND 2#00000000_00000100);
        
  END_IF;
END_PROGRAM


CONFIGURATION Config0
  VAR_GLOBAL
    controller_output : WORD;
    WDT AT %MW2 : UINT;
    current_superstate AT %MW0 : INT;
    current_state AT %MW1 : INT;
    sensor_output AT %MW4: WORD;
    ssm_transitions AT %MW3 : WORD;
    out_Ap : BOOL;
    out_Am : BOOL;
    out_B : BOOL;
    out_C : BOOL;
    out_Dp : BOOL;
    out_Dm : BOOL;
    out_preasure_off : BOOL;
  END_VAR

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#100ms,PRIORITY := 0);
    TASK WDT_clock(INTERVAL := T#10ms,PRIORITY := 0);
    PROGRAM SSM WITH task0 : superstate_machine;
    PROGRAM svc WITH task0 : service;
    PROGRAM EM WITH task0 : emerigency;
    PROGRAM AP WITH task0 : autoproduction;
    PROGRAM MP WITH task0 : manualproduction;
    PROGRAM FAIL WITH task0 : failure;
    PROGRAM WDTimer WITH WDT_clock : watchdogtimer;
  END_RESOURCE
END_CONFIGURATION
