;MP2 (XX22)
;Manila Gang
;John Rovere Iral
;Daniella Limbag
;Ma. Julianna Reyes

%include 'io64.inc'
section .data
    ;input matrix w the dataaa (V0, V1, Time)
    matrix dq 0.0, 62.5, 10.1
           dq 60.0, 122.3, 5.5
           dq 30.0, 160.7, 7.8

    matrixRows dq 3 ;num of rows of matrix
    kmToM dq 1000.0
    hoursToSec dq 3600.0
    
section .text
global main   
main:
    XOR r12, r12;counter for the loop
    SUB rsp, 12;3 spaces for results

process_cars_loop:
    MOV rax, r12
    CMP rax, qword [matrixRows]
    JGE end_processing

    ;load matric vals
    MOV rax, matrix
    MOV rbx, r12
    IMUL rbx, rbx, 24
    ADD rax, rbx

    MOVSD xmm0, qword [rax];V0
    MOVSD xmm1, qword [rax + 8];V1
    MOVSD xmm2, qword [rax + 16];T

    ;conversion
    MOVSD xmm3, qword [kmToM]
    MOVSD xmm4, qword [hoursToSec]

    ;V0 to m/s
    MULSD xmm0, xmm3 ; xmm0 *= 1000.0
    DIVSD xmm0, xmm4 ; xmm0 /= 3600.0

    ;V1 to m/s
    MULSD xmm1, xmm3 ; xmm1 *= 1000.0
    DIVSD xmm1, xmm4 ; xmm1 /= 3600.0

    ;(V1-V0)/T
    SUBSD xmm1, xmm0
    DIVSD xmm1, xmm2 ; xmm1 = (V1 - V0) / T

    ;convert acceleration to integer
    CVTSD2SI eax, xmm1
    MOV [rsp + r12 * 4], eax

    INC r12
    JMP process_cars_loop

end_processing:
    XOR r12, r12

print_results_loop:
    MOV rax, r12
    CMP rax, qword [matrixRows]
    JGE end_program
    MOV eax, [rsp + r12 * 4]
    PRINT_DEC 4, eax
    PRINT_CHAR 10
    INC r12
    JMP print_results_loop

end_program:
    ADD rsp, 12
    MOV rax, 0
    RET