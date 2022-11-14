#include "../comet/machine.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

/** \fn main
 * This test comet_stact_t for pushing, poping and relocating stack in memory.
 * You would run this as script on your computer.
 */
int main() {
    printf("This make tests on stack object!\n");

    printf("Creating object...\n");
    comet_stack_t test_stack = comet_create_stack();

    printf("Pushing 10 items into stack...\n");

    for (int count = 0; count < 10; ++count) {
        printf("Push %i\n", count);
        comet_push_stack(&test_stack, count);
    }

    printf("Size ");
    printf((test_stack.size == 10) ? "work\n" : "not work\n");

    printf("Checking 10 after pop...\n");

    for (int count = 9; count >= 0; --count) {
        printf("%i ", count);
        printf(
            (comet_pop_stack(&test_stack) == count) ? "work\n" : "not work\n"
        );
    }

    printf("Size after pop ");
    printf((test_stack.size == 0) ? "work\n" : "not work\n");

    return 0;
}
