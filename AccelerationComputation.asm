;MP2 (XX22)
;John Rovere Iral
;Daniella Limbag
;Ma. Julianna Reyes

section .data
    kmToM dd 1000.0
    hoursToSec dd 3600.0
    
section .text
bits 64
default rel
global x64CompAcceleration   
x64CompAcceleration:
    PUSH rbx
    PUSH r12
    XOR r12, r12;counter for the loop

process_cars_loop:
    CMP r12d, ecx ;compare counter with number of rows
    JGE end_processing

    ;load matric vals
    MOV rbx, r12
    IMUL rbx, 12

    MOVSS xmm0, [rdx + rbx];V0
    MOVSS xmm1, [rdx + rbx + 4];V1
    MOVSS xmm2, [rdx + rbx + 8];T
    
    ;compute
    SUBSS xmm1, xmm0
    MULSS xmm1, [rel kmToM]
    DIVSS xmm1, [rel hoursToSec]
    DIVSS xmm1, xmm2

    ;convert acceleration to integer
    CVTSS2SI eax, xmm1
    MOV [r8 + r12 * 4], eax

    INC r12
    JMP process_cars_loop

end_processing:
    XOR r12, r12

end_program:
    POP r12
    POP rbx
    RET
