        .global gadgets
        .global run_ropchain

        .data
gadgets:        
        .quad gadget0
        .quad gadget1
        .quad gadget2
        .quad gadget3
        .quad gadget4

        .text
gadget0:
        mov %rdi, 0x8(%rsp)
        ret
gadget1:
        pop %rax
        ret
gadget2:
        add $1, %rdi
        ret
gadget3:
        shl $1, %rdi
        ret
gadget4:
        xor %rdi, %rdi
        ret
        
run_ropchain:
        # put return address at the end of ropchain
        # that way run_ropchain returns to caller after executing the chain
        mov (%rsp), %rax
        mov %rax, (%rdi,%rsi)
        # invoke ropchain
        mov %rdi, %rsp
        ret
