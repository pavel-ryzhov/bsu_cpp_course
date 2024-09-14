#!/usr/bin/python3
import subprocess
import time

def wrap(cmd):
    start = time.time()
    subprocess.check_call(cmd)
    end = time.time()
    return end - start

nosse_elapsed = wrap(["./test_sse"])
print('Time without sse', nosse_elapsed)
sse_elapsed = wrap(["./test_sse", "--sse"])
print('Time with sse', sse_elapsed)
assert sse_elapsed < nosse_elapsed/1.5
print('OK')
