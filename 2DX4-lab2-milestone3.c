;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


; Name: Abdelmoniem Hassan
; Student Number: 400248003
; Lab Section: L06
; Description of Code: Turns on User LED D2 with the push of an combination

 
; Original: Copyright 2014 by Jonathan W. Valvano, valvano@mail.utexas.edu



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;ADDRESS DEFINTIONS

;The EQU directive gives a symbolic name to a numeric constant, a register-relative value or a program-relative value


SYSCTL_RCGCGPIO_R            EQU 0x400FE608  ;General-Purpose Input/Output Run Mode Clock Gating Control Register (RCGCGPIO Register)
GPIO_PORTN_DIR_R             EQU 0x40064400  ;GPIO Port N Direction Register address 
GPIO_PORTN_DEN_R             EQU 0x4006451C  ;GPIO Port N Digital Enable Register address
GPIO_PORTN_DATA_R            EQU 0x400643FC  ;GPIO Port N Data Register address
	
GPIO_PORTM_DIR_R             EQU 0x40063400  ;GPIO Port M Direction Register Address (Fill in these addresses)
GPIO_PORTM_DEN_R             EQU 0x4006351C  ;GPIO Port M Direction Register Address (Fill in these addresses)
GPIO_PORTM_DATA_R            EQU 0x400633FC  ;GPIO Port M Data Register Address      (Fill in these addresses) 
	
GPIO_PORTF_DIR_R             EQU 0x4005D400  ;Fill in the address for your assigned LED
GPIO_PORTF_DEN_R             EQU 0x4005D51C  ;Fill in the address for your assigned LED
GPIO_PORTF_DATA_R            EQU 0x4005D3FC  ;Fill in the address for your assigned LED
	

COMBINATION EQU 0x09200004; 1
COMBINATION1 EQU 0x09200004; 1
COMBINATION2 EQU 0x09200004; 1
COMBINATION3 EQU 0x20000400; 0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;Do not alter this section

        AREA    |.text|, CODE, READONLY, ALIGN=2 ;code in flash ROM
        THUMB                                    ;specifies using Thumb instructions
        EXPORT Start

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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


;Function PortN_Init 
PortN_Init 
    ;STEP 1
    LDR R1, =SYSCTL_RCGCGPIO_R 
    LDR R0, [R1]   
    ORR R0,R0, #0x1000           				          
    STR R0, [R1]               
    NOP 
    NOP   
   
    ;STEP 5
    LDR R1, =GPIO_PORTN_DIR_R   
    LDR R0, [R1] 
    ORR R0,R0, #0x3         
	STR R0, [R1]   
    
    ;STEP 7
    LDR R1, =GPIO_PORTN_DEN_R   
    LDR R0, [R1] 
    ORR R0, R0, #0x3                                    
    STR R0, [R1]  
    BX  LR                            
 
PortM_Init 
    ;STEP 1 
	LDR R1, =SYSCTL_RCGCGPIO_R       
	LDR R0, [R1]   
    ORR R0,R0, #0x800 
	STR R0, [R1]   
    NOP 
    NOP   
 
    ;STEP 5
    LDR R1, =GPIO_PORTM_DIR_R   
    LDR R0, [R1] 
    ORR R0,R0, #0x00          
	STR R0, [R1]   
    
	;STEP 7
    LDR R1, =GPIO_PORTM_DEN_R   
    LDR R0, [R1] 
    ORR R0, R0, #2_11111111          
	                          
    STR R0, [R1]    
	BX  LR                     


State_Init LDR R5,=GPIO_PORTN_DATA_R  ;Locked is the Initial State
	       MOV R4,#2_00000000
	       STR R4,[R5]
	       BX LR 
		   
;SysTick_Init
;	LDR R1, =NVIC_ST_CTRL_R
;	MOV R0, #0
;	STR R0, [R1]
;	LDR R1, =NVIC_ST_RELOAD_R
;	LDR R0, =0x00FFFFFF; ; 
;	STR R0, [R1]
;	LDR R1, =NVIC_ST_CURRENT_R
;	MOV R0, #0
;	STR R0, [R1]
;	LDR R1, =NVIC_ST_CTRL_R
;	MOV R0, #0x05
;	STR R0, [R1]
;	BX LR

;SysTick_Wait10ms
;	PUSH {R4, LR}
;	MOVS R4,R0
;	BEQ SysTickWait10ms_done
	
;SysTick_Wait10ms_done
;	POP {R4,PC}
delay10ms
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	BX LR
	
Start
	;BL	PLL_Init
	;BL	SysTick_Init
	BL	PortF_Init
	BL  PortN_Init                
	BL  PortM_Init
	BL  State_Init
	LDR R0, =GPIO_PORTM_DATA_R  ; Inputs set pointer to the input 
	LDR R3, =COMBINATION         ;R3 stores our combination
	; value of correct sequential answers


IsZero
	LDR R1, [R0]
	AND R2, R1, #2_00010000
	CMP R2, #2_00000000
	BNE IsZero
	
IsOne
	LDR R1, [R0]
	AND R2, R1, #2_00010000
	CMP R2, #2_00010000
	BNE IsOne

SavePM0Value
	LDR R1,[R0]            
	AND R2,R1,#2_00000001
	AND R7, #0x0
	LDR R7,[R2]
	BL delay10ms



Loop
	CMP R7,R3
	BEQ Locked_State1
	BNE Locked_State0
	
IsZero1
	LDR R1, [R0]
	AND R2, R1, #2_00010000
	CMP R2, #2_00000000
	BNE IsZero1
	
IsOne1
	LDR R1, [R0]
	AND R2, R1, #2_00010000
	CMP R2, #2_00010000
	BNE IsOne1

SavePM0Value1
	LDR R1,[R0]            
	AND R2,R1,#2_00000001
	AND R7, #0x0
	LDR R7,[R2]
	BL delay10ms

Loop1
	CMP R7,R3
	BEQ Locked_State2
	BNE Locked_State0
	
IsZero2
	LDR R1, [R0]
	AND R2, R1, #2_00010000
	CMP R2, #2_00000000
	BNE IsZero2
	
IsOne2
	LDR R1, [R0]
	AND R2, R1, #2_00010000
	CMP R2, #2_00010000
	BNE IsOne2

SavePM0Value2
	LDR R1,[R0]            
	AND R2,R1,#2_00000001
	AND R7, #0x0
	LDR R7,[R2]
	BL delay10ms
	
Loop2
	CMP R7,R3
	BEQ Locked_State3
	BNE Locked_State0
	
	
IsZero3
	LDR R1, [R0]
	AND R2, R1, #2_00010000
	CMP R2, #2_00000000
	BNE IsZero3
	
IsOne3
	LDR R1, [R0]
	AND R2, R1, #2_00010000
	CMP R2, #2_00010000
	BNE IsOne3

SavePM0Value3
	LDR R1,[R0]            
	AND R2,R1,#2_00000001
	AND R7, #0x0
	LDR R7,[R2]
	BL delay10ms
	
Loop3
	CMP R7,R3
	BEQ Unlocked_State
	BNE Locked_State0

Locked_State0
	ORR R8, #0x1
	LDR R3, =COMBINATION
	LDR R5,=GPIO_PORTN_DATA_R
	MOV R4,#2_00000000
	STR R4,[R5]
	LDR R5, =GPIO_PORTF_DATA_R
	MOV R4,#2_00000000
	STR R4, [R5]
	B IsZero
	
Locked_State1
	ORR R8, #0x10
	LDR R3, =COMBINATION1
	LDR R5,=GPIO_PORTN_DATA_R
	MOV R4,#2_00000001
	STR R4,[R5]
	B IsZero1
	
Locked_State2
	ORR R8, #0x100
	LDR R3, =COMBINATION2
	LDR R5,=GPIO_PORTN_DATA_R
	MOV R4,#2_00000010
	STR R4,[R5]
	B IsZero2
	
Locked_State3
	ORR R8, #0x1000
	LDR R3, =COMBINATION3
	LDR R5,=GPIO_PORTN_DATA_R
	MOV R4,#2_00000011
	STR R4,[R5]
	B IsZero3
	
	
Unlocked_State
	LDR R5, =GPIO_PORTN_DATA_R
	MOV R4,#2_00000000
	STR R4, [R5]
	LDR R5, =GPIO_PORTF_DATA_R
	MOV R4,#2_00010000
	STR R4, [R5]
	B IsZero
	
	ALIGN   
	END  
