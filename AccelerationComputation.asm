;MP2 (XX22)
;Manila Gang
;John Rovere Iral
;Daniella Limbag
;Ma. Julianna Reyes

%include 'io64.inc'
section .data
    kmToM dq 1000.0
    hoursToSec dq 3600.0
    
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

    MOVSS xmm0, qword [rdx + rbx];V0
    MOVSS xmm1, qword [rdx + rbx + 4];V1
    MOVSS xmm2, qword [rdx + rbx + 8];T
    
    ;convert to double
    CVTSD2SI xmm0, xmm0
    CVTSD2SI xmm1, xmm1
    CVTSD2SI xmm2, xmm2
    
    SUBSD xmm1, xmm0
    
    ;conversion
    MOVSD xmm3, qword [kmToM]
    MOVSD xmm4, qword [hoursToSec]
    MULSD xmm1, xmm3
    DIVSD xmm1, xmm4
    DIVSD xmm1, xmm2

    ;convert acceleration to integer
    CVTSD2SI eax, xmm1
    MOV [r8 + r12 * 4], eax

    INC r12
    JMP process_cars_loop

end_processing:
    XOR r12, r12

end_program:
    POP r12
    POP rbx
    RET