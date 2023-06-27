	AREA    |.text|, CODE, READONLY
		
	EXPORT int_to_float
	GET stm32f0.inc
	
	
int_to_float      PROC
	
	;LDR r1, =-5;
    MOV R2, R1
    CMP R1, #0
    BGE positive

    MOV R2, R1
    NEGS R2, R2         
    LDR R3, =0x1         
    B continue

positive
    LDR R3, =0         

continue
    LDR R4, =0         
    CMP R2, #0
    BEQ endd

while_loop
    ADDS R4, #1
    LSRS R2, R2, #1     
    CMP R2, #0
    BNE while_loop

endd
    CMP R1, #0
    BGE positive2
    NEGS R1, R1         

positive2
    LDR R5, =24
	MOV R2, R1
    SUBS R5, R5, R4    
    LSLS R2, R2, R5     
    LDR R7, =0x7FFFFF
    ANDS R2, R7         

    LDR r0, =0
	LSLS R3, R3, #31
    ADDS r4, r4, #126
	LSLS R4, R4, #23
    ORRS R0, R3
	ORRS R0, R4
	ORRS R0, R2
	
	BX LR
	
	ENDP
	
 END
	 
	 