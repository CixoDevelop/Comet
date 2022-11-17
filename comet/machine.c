#include <stdlib.h>
#include <stdbool.h>
#include "machine.h"

/** \fn comet_create_program
 * This create and return object for storing comet program.
 */
comet_program_t comet_create_program() {
    comet_word_t *program_space = malloc(0x00 * sizeof(comet_word_t));

    return (comet_program_t) {
        0x00,
        program_space,
        program_space
    };
}

/** \fn comet_program_load
 * This load program about defined size from source to program space.
 * @*program Program container where this save data
 * @*source Source from function load data
 * @size Size of loaded data
 */
bool comet_program_load(
    comet_program_t *program,
    comet_word_t *source,
    size_t size
) {
    if (size == 0x00) return true;

    size_t counter = program->pointer - program->space;
    size_t current_position = program->size;

    program->size += size;
    program->space = realloc(
        program->space, 
        program->size * sizeof(comet_word_t)
    );
    program->pointer = program->space + counter;

    if (program->space == NULL) return false;

    while (current_position < program->size) {
        program->space[current_position] = *source;

        ++current_position;
        ++source;
    }
   
    return true;
}

/** \fn comet_program_absolute_jump
 * This function make absolute jump in program space. If position is over
 * program size, return false. If all gone well, return true.
 * @*program Program to make jump on
 * @position Position in program spece to jump in
 */
bool comet_program_absolute_jump(comet_program_t *program, size_t position) {
    if (program->size <= position) return false;

    program->pointer = program->space + position;

    return true;
}

/** \fn comet_program_relative_jump
 * This make relative jump in program space by position given in parameter.
 * If that position is over program space size, return false, if all gone 
 * well, return true.
 * @*program Program to work on
 * @position Position to jump by them
 */
bool comet_program_relative_jump(comet_program_t *program, size_t position) {
    if (program->pointer + position >= program->space + program->size) {
        return false;
    }

    program->pointer += position;

    return false;
}

/** \fn comet_program_serial_pop
 * This load serial data from program space.
 * @*program Program container to load from
 * @*load_space Space to load into
 * @serial_size Size of serial data
 */
bool comet_program_serial_pop(
    comet_program_t *program, 
    comet_word_t *load_space,
    int serial_size
) {
    if (program->pointer + serial_size >= program->space + program->size) {
        return false;
    }

    comet_word_t *target_counter = program->pointer + serial_size;

    while (program->pointer < target_counter) {
        *load_space = *program->pointer;

        ++load_space;
        ++program->pointer;
    }

    return true;
}

/** \fn comet_program_pop
 * This get one item from program space and return it.
 * @*program Program container to load from
 */
comet_word_t comet_program_pop(comet_program_t *program) {
    if (program->pointer >= program->space + program->size) return 0x00;

    return *program->pointer++;
}

/** \fn comet_program_get_position
 * This return current position in program space.
 * @*program Program container to get from
 */
size_t comet_program_get_position(comet_program_t *program) {
    return (size_t) (program->pointer - program->space);
}

/** \fn comet_create_stack
 * This create and return new clean stack.
 */
comet_stack_t comet_create_stack() {
    return (comet_stack_t) {
        0x00,
        0x00,
        malloc(0x00 * sizeof(comet_word_t))
    };
}

/** \fn comet_pop_stack
 * This pop one item from stack.
 * @*stack Stack object to get from
 */
comet_word_t comet_pop_stack(comet_stack_t *stack) {
    if (stack->size - COMET_ALLOC_STEP == stack->position) {
        stack->size -= COMET_ALLOC_STEP;
        stack->space = realloc(
            stack->space,
            stack->size * sizeof(comet_word_t)
        );
    }


    if (stack->size == 0x00) return 0x00;
    if (stack->position > 0x00) --stack->position;

    return stack->space[stack->position];
}

/** \fn comet_push_stack
 * This insert one item into stack.
 * @*stack Stack to insert into stack
 * @data Data to insert 
 */
bool comet_push_stack(comet_stack_t *stack, comet_word_t data) {
    if (stack->size == stack->position) {
        stack->size += COMET_ALLOC_STEP;
        stack->space = realloc(
            stack->space, 
            stack->size * sizeof(comet_word_t)
        );

        if (stack->space == NULL) return false;
    }

    stack->space[stack->position] = data;
    ++stack->position;

    return true;
}

comet_instance_t comet_create_instance(comet_program_t program) {
    return (comet_instance_t) {
        program, comet_create_stack(), comet_create_stack(), 0x00, 0x00, 0x00 
    };
}

