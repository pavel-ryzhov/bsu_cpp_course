#include "context.h"

#include <assert.h>
#include <stdio.h>

void simple() {
    struct context ctx;

    fprintf(stderr, "saving context\n");
    if (savectx(&ctx) == 0) {
        fprintf(stderr, "restoring context\n");
        jumpctx(&ctx);
    }
    fprintf(stderr, "context restored\n");
}

void chain() {
    struct context ctx0, ctx1, ctx2;

    fprintf(stderr, "saving ctx0\n");
    if (savectx(&ctx0)) {
        fprintf(stderr, "restoring ctx1\n");
        jumpctx(&ctx1);
    }

    fprintf(stderr, "saving ctx1\n");
    if (savectx(&ctx1)) {
        fprintf(stderr, "restoring ctx2\n");
        jumpctx(&ctx2);
    }

    fprintf(stderr, "saving ctx2\n");
    if (savectx(&ctx2)) {
        return;
    } else {
        fprintf(stderr, "restoring ctx0\n");
        jumpctx(&ctx0);
    }
}

void loop() {
    int volatile i = 0;
    int j = 0;
    struct context ctx0;

    fprintf(stderr, "saving context\n");
    if (savectx(&ctx0) == 0) {
        fprintf(stderr, "restoring context %d\n", i);
        jumpctx(&ctx0);
    } else if (i == 8) {
        // What's the difference between i and j?
        assert(j == 0);
        return;
    } else {
        i++;
        j++;
        fprintf(stderr, "restoring context %d\n", i);
        jumpctx(&ctx0);
    }
}

__attribute__((noinline)) void restore1(struct context* ctx) {
    __attribute__((unused)) volatile int i = 0;
    fprintf(stderr, "inside restore1\n");
    jumpctx(ctx);
}

__attribute__((noinline)) void restore0(struct context* ctx) {
    __attribute__((unused)) volatile int i = 0;
    fprintf(stderr, "inside restore0\n");
    restore1(ctx);
}

void inside_function() {
    int volatile j = 5;
    struct context ctx;
    fprintf(stderr, "saving context\n");
    if (savectx(&ctx) == 0) {
        restore0(&ctx);
    }
    fprintf(stderr, "restored context\n");
    assert(j == 5);
}

int main() {
    simple();
    chain();
    loop();
    inside_function();
    return 0;
}
