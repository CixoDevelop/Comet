#include <stdint.h>
#include <stdbool.h>
#include "machine.h"
#include "processor.h"

int comet_execute_instance(comet_instance_t *instance) {
    comet_word_t instruction = comet_program_pop(&instance->program);

    switch (instruction) {
        case NOP:
        break;

        case LOAD:
            comet_push_stack(
                &instance->data_stack,
                comet_program_pop(&instance->program)
            );
        break;

        case PUSA:
            comet_push_stack(
                &instance->data_stack,
                instance->register_a
            );
        break;

        case PUSB:
            comet_push_stack(
                &instance->data_stack,
                instance->register_b
            );
        break;

        case POPA:
            instance->register_a = comet_pop_stack(
                &instance->data_stack
            );
        break;

        case POPB:
            instance->register_b = comet_pop_stack(
                &instance->data_stack;
            );
        break;
    }
}

