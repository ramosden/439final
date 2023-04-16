
    .global context_switch
context_switch:
    mov 4(%esp), %eax
    mov 8(%esp), %ecx

    push %ebx
    push %esi
    push %edi
    push %ebp
    pushf

    mov %esp, (%eax)
    mov (%ecx), %esp

    popf
    pop %ebp
    pop %edi
    pop %esi
    pop %ebx

    ret

