        .global main
        .data

s_test_sum:
        .ascii "error in test_sum\0"
s_test_sum_struct:
        .ascii "error in test_sum_struct\0"
s_test_sum_array:
        .ascii "error in test_sum_array\0"
s_test_sum_va_arg:
        .ascii "error in test_sum_va_arg\0"

test_struct0:
        .quad 2
        .quad 1
        .quad 0
test_struct1:
        .quad 10
        .quad 20
        .quad 0

test_array:
        .quad 1
        .quad 2
        .quad 3
        .quad 4
        .quad 5
        .quad 6


////////////////////////////////////////////////////////////////////////////////
        .text

test_sum:
        mov $1, %rdi
        mov $2, %rsi
        call sum
        cmp $3, %rax
        jne panic_test_sum

        mov $10, %rdi
        mov $20, %rsi
        call sum
        cmp $30, %rax
        jne panic_test_sum

        ret

test_sum_struct:
        mov $test_struct0, %rdi
        call sum_struct
        mov $test_struct0, %rdi
        cmp $3, 0x10(%rdi)
        jne panic_test_sum_struct

        mov $test_struct1, %rdi
        call sum_struct
        mov $test_struct1, %rdi
        cmp $30, 0x10(%rdi)
        jne panic_test_sum_struct

        ret

test_sum_array:
        mov $test_array, %rdi
        mov $0, %rsi
        call sum_array
        cmp $0, %rax
        jne panic_test_sum_array

        mov $test_array, %rdi
        mov $1, %rsi
        call sum_array
        cmp $1, %rax
        jne panic_test_sum_array

        mov $test_array, %rdi
        mov $2, %rsi
        call sum_array
        cmp $3, %rax
        jne panic_test_sum_array

        mov $test_array, %rdi
        add $0x10, %rdi
        mov $4, %rsi
        call sum_array
        cmp $18, %rax
        jne panic_test_sum_array

        ret

test_sum_va_arg:
        sub $0x80, %rsp

        mov $0, %rdi
        call sum_va_arg
        cmp $0, %rax
        jne panic_test_sum_va_arg

        movq $1, (%rsp)
        movq $2, 0x8(%rsp)
        movq $100, 0x10(%rsp)
        mov $3, %rdi
        call sum_va_arg
        cmp $103, %rax
        jne panic_test_sum_va_arg

        add $0x80, %rsp
        ret

////////////////////////////////////////////////////////////////////////////////

panic_test_sum:
        mov $s_test_sum, %rdi
        call panic

panic_test_sum_struct:
        mov $s_test_sum_struct, %rdi
        call panic

panic_test_sum_array:
        mov $s_test_sum_array, %rdi
        call panic

panic_test_sum_va_arg:
        mov $s_test_sum_va_arg, %rdi
        call panic

panic:
        call puts
        int $3
        nop

////////////////////////////////////////////////////////////////////////////////

main:
        call test_sum
        call test_sum_struct
        call test_sum_array
        call test_sum_va_arg
        xor %rax, %rax
        ret
