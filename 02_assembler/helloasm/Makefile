default: run

S ?= .

test_asm: test.S Makefile $(S)/asm.S
	gcc -no-pie test.S $(S)/asm.S -I. -o $@

run: test_asm
	./test_asm

.PHONY: run
