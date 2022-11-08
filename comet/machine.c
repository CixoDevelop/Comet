#include <stdlib.h>
#include <stdbool.h>
#include "machine.h"

comet_program_t comet_create_program() {
    comet_word_t *program_space = malloc(0x00 * sizeof(comet_word_t));

    return (comet_program_t) {
        0x00,
        program_space,
        program_space
    };
}

bool comet_program_load(
    comet_program_t *program,
    comet_word_t *source,
    size_t size
) {
    if (size == 0x00) return true;

    int counter = program->pointer - program->space;
    int current_position = program->size;

    program->size += size;
    program->space = realloc(program->space, program->size);
    program->pointer = program->space + counter;

    if (program->space == NULL) return false;

    while (current_position < program->size) {
        program->space[current_position] = *source;

        ++current_position;
        ++source;
    }
   
    

    return true;
}

