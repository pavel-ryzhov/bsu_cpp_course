default: run

S ?= .

test_context: test.c $(S)/context.S context.h Makefile
	gcc -no-pie test.c $(S)/context.S -O2 -fno-omit-frame-pointer -o $@

run: test_context
	./test_context

.PHONY: run
