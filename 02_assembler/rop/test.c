#include "rop.h"

#include <assert.h>
#include <stdio.h>
#include <strings.h>

int main() {
    void* ropchain[1024];
    bzero(ropchain, sizeof(ropchain));
    size_t len = make_ropchain(ropchain);
    for (int i = 0; i < 1024; i++) {
        if (ropchain[i] != 0 && ropchain[i] != gadgets[0] && ropchain[i] != gadgets[1] &&
            ropchain[i] != gadgets[2] && ropchain[i] != gadgets[3] && ropchain[i] != gadgets[4]) {
            fprintf(stderr, "error: ropchain verification failed: %p\n", ropchain[i]);
            return 1;
        }
    }

    int ret = run_ropchain(ropchain, len);
    int expected = 0xdeadbeef;
    if (ret != expected) {
        fprintf(stderr, "error: 0x%x != 0x%x\n", ret, expected);
        return 1;
    }
    return 0;
}
