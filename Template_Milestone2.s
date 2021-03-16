;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


; Name: Abdelmoniem Hassan
; Student Number: 400248003
; Lab Section: L06
; Description of Code: Turns on User LED D4 with the push of an external button

 
; Original: Copyright 2014 by Jonathan W. Valvano, valvano@mail.utexas.edu



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;ADDRESS DEFINTIONS

;The EQU directive gives a symbolic name to a numeric constant, a register-relative value or a program-relative value

;;;;;;;;;;;;;; FILL this;;;;;;;;;;;;;;;;0x40025000
SYSCTL_RCGCGPIO_R            EQU 0x400FE608  ;General-Purpose Input/Output Run Mode Clock Gating Control Register (RCGCGPIO Register)
GPIO_PORTF_DIR_R             EQU 0x4005D400  ;Fill in the address for your assigned LED
GPIO_PORTF_DEN_R             EQU 0x4005D51C  ;Fill in the address for your assigned LED
GPIO_PORTF_DATA_R            EQU 0x4005D3FC  ;Fill in the address for your assigned LED
	
GPIO_PORTM_DIR_R             EQU  0x40063400 ;GPIO Port M Direction Register Address (Fill in these addresses)
GPIO_PORTM_DEN_R             EQU  0x4006351C ;GPIO Port M Direction Register Address (Fill in these addresses)
GPIO_PORTM_DATA_R            EQU  0x400633FC ;GPIO Port M Data Register Address      (Fill in these addresses) 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;clear amsel offset 0x528 
;clear 0x420afsel offset 
;clear ptcl offset 0x52C

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;Do not alter this section

        AREA    |.text|, CODE, READONLY, ALIGN=2 ;code in flash ROM
        THUMB                                    ;specifies using Thumb instructions
        EXPORT Start

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;Function PortF_Init 100000
;;;;;;;;;;;;;;;;;;;; Fill this;;;;;;;;;;;;;;
PortF_Init 
	;STEP 1
	LDR R1, =SYSCTL_RCGCGPIO_R          
    LDR R0, [R1]                        
    ORR R0,R0, #0x20                     
    STR R0, [R1]
	NOP
	NOP
   
    ;STEP 5
	LDR R1, =GPIO_PORTF_DIR_R          
    LDR R0, [R1]                        
    ORR R0,R0, #0x10                     
    STR R0, [R1]
	
    ;STEP 7
	LDR R1, =GPIO_PORTF_DEN_R         
    LDR R0, [R1]                        
    ORR R0,R0, #0x10                     
    STR R0, [R1]
    BX  LR                           
 
PortM_Init 
    LDR R1, =SYSCTL_RCGCGPIO_R          
    LDR R0, [R1]                        
    ORR R0,R0, #0x800                 
    STR R0, [R1]
	NOP
	NOP
   
    ;STEP 5
	LDR R1, =GPIO_PORTM_DIR_R          
    LDR R0, [R1]                        
    AND R0,R0, #0x0                     
    STR R0, [R1]
	
    ;STEP 7
	LDR R1, =GPIO_PORTM_DEN_R         
    LDR R0, [R1]                        
    ORR R0,R0, #0x01                     
    STR R0, [R1] 
	BX  LR                
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;     
 
Start                             ; Your assembly code starts executing here
	BL  PortM_Init                ;The BL instruction is like a function call to initalize Port M
	BL  PortF_Init                ;The BL instruction is like a function call to initalize Port F  
 
Loop LDR R0, =GPIO_PORTM_DATA_R  ;Save the address of Input Port M to R0   
     LDR R1, [R0]                ;Save the contents at Input Port M to R1
;;;;;;;;;;;;;;;;;;;;;;;;;;; Fill this;;;;;;;;;;;;;;;
	 EOR R1, R1, #0x1             ;Flips the input bit value at R1 bit 0: 0-> 1 or 1 -> 0 (remember push button is active low, so when we push we get 0 and we need 1 to turn on LED)
	 LSL R1, R1, #0x4             ;Left shift R1 x bits to the left depends on student number, just use shift of zero here if not
	 LDR R3, =GPIO_PORTF_DATA_R  
		STR R1, [R3]
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
     
	 B Loop 
 
     ALIGN   
     END   