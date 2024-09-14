default: run

S ?= .

test_sse: main.cpp model.cpp $(S)/sse.cpp sse.h Makefile
	g++ -g -march=haswell -std=c++17 -O2 -o test_sse main.cpp model.cpp $(S)/sse.cpp -I.

run: test_sse
	./checktime.py
