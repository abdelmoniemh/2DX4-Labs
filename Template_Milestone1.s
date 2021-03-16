;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


; Name: Abdelmoniem Hassan
; Student Number: 400248003
; Lab Section: L06
; Description of Code: Blinks LED D2
 
; Original: Copyright 2014 by Jonathan W. Valvano, valvano@mail.utexas.edu



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;ADDRESS DEFINTIONS

;The EQU directive gives a symbolic name to a numeric constant, a register-relative value or a program-relative value

;;;;;;;;;;;;;;;;;;;;;;;;;;Fill this;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
SYSCTL_RCGCGPIO_R            EQU 0x400FE608  ;General-Purpose Input/Output Run Mode Clock Gating Control Register (RCGCGPIO Register)
GPIO_PORTN_DIR_R             EQU 0x40064400  ;GPIO Port N Direction Register address 
GPIO_PORTN_DEN_R             EQU 0x4006451C  ;GPIO Port N Digital Enable Register address
GPIO_PORTN_DATA_R            EQU 0x400643FC  ;GPIO Port N Data Register address
COUNTER                      EQU 0xFFFFF
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;Do not alter this section

        AREA    |.text|, CODE, READONLY, ALIGN=2 ;code in flash ROM
        THUMB                                    ;specifies using Thumb instructions
        EXPORT Start

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;Fill this;;;;;;;;;;;;;;;;;;;;;;;;;
;Function PortF_Init
PortN_Init
    ;STEP 1
	 LDR R1, = SYSCTL_RCGCGPIO_R; ENABLING CLOCK
	 LDR R0, [R1]
	 ORR R0, R0, #0x1000 ; turns on register 12 in RCGCGPIO port n
	 STR R0, [R1]
	 NOP
	 NOP
  
     ;STEP 5
	 LDR R1, = GPIO_PORTN_DIR_R
	 LDR R0, [R1]
	 ORR R0, R0, #0x1
	 STR R0, [R1]
    
     ; STEP 7
	 LDR R1, = GPIO_PORTN_DEN_R
	 LDR R0, [R1]
	 ORR R0, R0, #0x1
	 STR R0, [R1]

     BX  LR                            
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
Start
      BL  PortN_Init                ; The BL instruction is like a function call 
	  
      ;STEP 8                              		
      LDR R1, =GPIO_PORTN_DATA_R
      LDR R0,[R1]
      ORR R0,R0, #0x1
loop  STR R0, [R1]
;;;;;;;;;;;; Change this ;;;;;;;;;;;;;;;;;;
      EOR R0, R0, #0x1             ;Note: You are using an OR here you need an XOR to toggle, what should you use?
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;      
	  LDR R4, =COUNTER

loop1 NOP
      NOP                                ;Go into a loop
      SUB R4,R4,#0x1
      CMP R4,#0x00
	  BNE loop1
	  
	  B loop 
	  ALIGN                         ;Make sure the end of this section is aligned
      END