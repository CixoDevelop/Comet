#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../comet_include/stack.h"

int main() {
    printf("Testing stack!\n");
   
    printf("Creating stack...\n");
    comet_stack_t *stack = comet_stack_create();

    for (int count = 0; count < 1000; ++count) {
        printf("Pushing into stack %i...", count);
        printf(comet_stack_push(stack, count) ? "work\n" : "not work\n");
    }

    for (int count = 999; count >= 0; --count) {
        comet_word_t from_stack = comet_stack_pop(stack);
        printf("Pop from stack %i...", from_stack);
        printf((from_stack == count))
    }

    return 0x00;
}
