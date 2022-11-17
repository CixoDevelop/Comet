#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "machine.h"
#include "shell.h"

/** \fn comet_execute_file
 * This execute binary comet file in new instance and return comet instance
 * exit code.
 * @*file_name Name of file to execute
 */
int comet_execute_file(char *file_name) {
    FILE *file = fopen(file_name, "rb");
    int file_size = 0x00;

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    comet_program_t program = comet_create_program();
    
    fclose(file);

    comet_instance_t machine = comet_create_instance(program);

    return comet_execute_instance(machine);
}
