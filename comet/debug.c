#include "processor.h"
#include "machine.h"
#include "debug.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define DEBUG_MODE_ENABLE

static inline void debug_stack(comet_stack_t *stack) {
    printf("\nCOMET STACK OUTPUT\n");
    printf(
        "Position: %i, Size: %i\n", 
        stack->position, 
        stack->size
    );
    printf("\nEND COMET STACK OUTPUT\n");
}

void debug(comet_instance_t *instance) {
    #ifdef DEBUG_MODE_ENABLE
 
    printf("\nCOMET DEBUG OUTPUT\n");
    printf(
        "Register A: %i, Register B: %i\n", 
        (int) (instance->register_a), 
        (int) (instance->register_b)
    );
    printf("Flag register: %i\n", (int) (instance->flags));
    
    printf("Data stack");
    debug_stack(&instance->data_stack);

    printf("Call stack");
    debug_stack(&instance->call_stack);

    printf("\nEND COMET DEBUG OUTPUT\n\n");

    #endif
}
