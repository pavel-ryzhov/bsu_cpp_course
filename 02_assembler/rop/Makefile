default: run

S ?= .

test_rop: rop.S test.c $(S)/ropchain.c Makefile rop.h
	gcc -no-pie rop.S test.c $(S)/ropchain.c -I. -o $@

run: test_rop
	./test_rop

.PHONY: run
