#include "../comet/processor.h"
#include "../comet/machine.h"
#include <stdlib.h>
#include <stdio.h>

comet_word_t program_content[] = {
    DSTP,
    LOAD, 22,
    POPA,
    LOAD, 25,
    DSTP,
    EXIT
};

int main() {
    comet_program_t program = comet_create_program();
    comet_program_load(&program, program_content, 8);

    comet_instance_t instance = comet_create_instance(program);
    comet_execute_instance(&instance);

    return 0;
}
