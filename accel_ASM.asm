section .data
    conv dq 0.277777777777778

section .text
    bits 64
    default rel
    global accel_ASM
    
accel_ASM:

    ;results@rcx, Y@rdx, matrix@r8
    push rbx                     ; Save rbx

    ; storing the conversion rate to xmm3
    movsd xmm3, qword [conv]

    ; rbx is the loop counter so we clear it to 0
    xor rbx, rbx                 
    
L1:
    ; loop checker (compares rbx to rdx which is Y)
    cmp rbx, rdx                 
    jge done                    

    ; calculate address by multiplying by 24 (8 * 3 because 3 columns 8 bytes each)
    imul r10, rbx, 24
    ; offsetting it by adding r8 to r10 to get to the address of the current row
    add r10, r8

    ; because its float inputs, we store them in xmm registers
    movsd xmm0, qword [r10]     ; INITIAL
    movsd xmm1, qword [r10 + 8] ; FINAL
    movsd xmm2, qword [r10 + 16]; TIME

    ;subtracting the initial and final
    subsd xmm1, xmm0
    ; multiply to convert it to meters
    mulsd xmm1, xmm3
    ; dividing it by time
    divsd xmm1, xmm2  
    
    ; converting to integer and storing it to rax so we can return it (RAX is the return value)
    cvtsd2si rax, xmm1
    mov dword [rcx + rbx * 4], eax

    ; increment loop counter and looping
    inc rbx
    jmp L1
done:
    pop rbx
    ret
