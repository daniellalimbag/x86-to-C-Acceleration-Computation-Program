%include 'io64.inc'
section .text
global main
section .data
    ;input matrix w the dataaa (V0, V1, Time)
    matrix dq 0.0, 62.5, 10.1
           dq 60.0, 122.3, 5.5
           dq 30.0, 160.7, 7.8

    matrixRows dq 3 ;num of rows of matrix
    kmToM dq 1000.0
    hoursToSec dq 3600.0
    
main:
    ;write your code here
    xor rax, rax
    ret