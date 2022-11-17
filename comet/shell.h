#ifndef COMET_SHELL_H_INCLUDED
#define COMET_SHELL_H_INCLUDED

#include <stdint.h>
#include <stdio.h>

/** \fn comet_execute_file
 * This execute binary comet file in new instance and return comet instance
 * exit code.
 * @*file_name Name of file to execute
 */
int comet_execute_file(char *file_name);

#endif

