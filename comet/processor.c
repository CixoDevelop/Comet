#include <stdint.h>
#include <stdbool.h>
#include "machine.h"
#include "processor.h"
#include "debug.h"

static inline uint16_t word_from_byte(uint8_t high, uint8_t low) {
    return (uint16_t) ((high * 0x0100) + low);
}

static inline uint8_t low_byte_from_word(uint16_t word) {
    return (uint8_t) (word & 0xFF);
}

static inline uint8_t high_byte_from_word(uint16_t word) {
    return (uint8_t) (word / 0x0100);
}

static inline void load(comet_instance_t *instance) {
    comet_push_stack(
        &instance->data_stack, 
        comet_program_pop(&instance->program)
    );
}

static inline void push_a_register(comet_instance_t *instance) {
    comet_push_stack(
        &instance->data_stack,
        instance->register_a
    );
}

static inline void push_b_register(comet_instance_t *instance) {
    comet_push_stack(
        &instance->data_stack,
        instance->register_b
    );
}

static inline void pop_a_register(comet_instance_t *instance) {
    instance->register_a = comet_pop_stack(&instance->data_stack);
}

static inline void pop_b_register(comet_instance_t *instance) {
    instance->register_b = comet_pop_stack(&instance->data_stack);
}

static inline size_t load_address(comet_instance_t *instance) {
    comet_word_t high = comet_program_pop(&instance->program);
    comet_word_t low = comet_program_pop(&instance->program);

    return word_from_byte(high, low);
}

static inline void push_address(comet_instance_t *instance, size_t address) {
    comet_push_stack(&instance->call_stack, low_byte_from_word(address));
    comet_push_stack(&instance->call_stack, high_byte_from_word(address));
}

static inline size_t pop_address(comet_instance_t *instance) {
    comet_word_t high = comet_pop_stack(&instance->call_stack);
    comet_word_t low = comet_pop_stack(&instance->call_stack);

    return word_from_byte(high, low);
}

static inline void relative_jump(comet_instance_t *instance) {
    comet_program_relative_jump(&instance->program, load_address(instance));
}

static inline void absolute_jump(comet_instance_t *instance) {
    comet_program_absolute_jump(&instance->program, load_address(instance));
}

static inline void call(comet_instance_t *instance) {
    size_t calling = load_address(instance);
    size_t currently = comet_program_get_position(&instance->program);

    push_address(instance, currently);
    comet_program_absolute_jump(&instance->program, calling);
    
}

static inline void ret(comet_instance_t *instance) {
    comet_program_absolute_jump(&instance->program, pop_address(instance));
}

static inline int exit_instance(comet_instance_t *instance) {
    return (int) (comet_pop_stack(&instance->data_stack));
}

int comet_execute_instance_operation(comet_instance_t *instance) {
    comet_word_t instruction = comet_program_pop(&instance->program);

    switch (instruction) {
        case NOP:
        break;

        case LOAD:
            load(instance);
        break;

        case PUSA:
            push_a_register(instance);
        break;

        case PUSB:
            push_b_register(instance);
        break;

        case POPA:
            pop_a_register(instance);
        break;

        case POPB:
            pop_b_register(instance);
        break;
        
        case RJMP:
            relative_jump(instance);
        break;

        case AJMP:
            absolute_jump(instance);
        break;

        case CALL:
            call(instance);
        break;

        case RET:
            ret(instance);
        break;
    
        case EXIT:
            return exit_instance(instance);
        break;

        case DSTP:
            debug(instance);
        break;
    
    }
    
    return 0xFFFF;
}

int comet_execute_instance(comet_instance_t *instance) {
    int current_result = 0xFFFF;

    while (current_result == 0xFFFF) {
        current_result = comet_execute_instance_operation(instance);
    }

    return current_result;
}
