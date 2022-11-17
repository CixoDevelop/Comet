#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <alloca.h>
#include "comet/machine.h"
#include "comet/shell.h"

#define EXECUTE_FLAG "execute"
#define HELP_FLAG "help"
#define FILE_PARAMETER 1
#define HELP_TEXT "UwU this will be create...lateeeee!\n"

char get_letter_from_parameter(char *parameter) {
    return *parameter;
}

bool check_parameter(char *parameter, char *command_line) {
    int parameter_len = strlen(parameter);
    char letter_option[3] = {'-', get_letter_from_parameter(parameter), 0x00};
    char *parameter_option = alloca(parameter_len + 3);

    strcpy(parameter_option, "--");
    strcpy(parameter_option + 2, parameter);

    if (!strcmp(parameter_option, command_line)) return true;
    if (!strcmp(letter_option, command_line)) return true;

    return false;
}

bool is_positional_parameter(char *parameter) {
    return *parameter != '-';
}

int main(int argc, char *argv[]) {
    char *file_to_open = NULL;
    bool executable = false;
    bool help = false;

    if (argc == 1) help = true;

    int positional_parameter_count = 0;

    for (int count = 1; count < argc; ++count) {
        executable += check_parameter(EXECUTE_FLAG, argv[count]);
        help += check_parameter(HELP_FLAG, argv[count]);
        
        bool is_positional = is_positional_parameter(argv[count]);
        positional_parameter_count += is_positional;
        
        if (positional_parameter_count == FILE_PARAMETER && is_positional) {
            file_to_open = argv[count];
        }
    }

    if (help) {
        printf(HELP_TEXT);
        exit(0);
    }

    if (executable) exit(comet_execute_file(file_to_open));

    return 0;
}
