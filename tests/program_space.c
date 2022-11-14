#include <stdio.h>
#include "../comet/machine.h"

/* Data for testing */
comet_word_t TEST_PROGRAM[] = "UwU test OwO test...";
int TEST_PROGRAM_SIZE = 20;

/** \fn compare_arrays
 * This comapre two arrays, return true if arrays are same, or false if not.
 * @*array_first First array to compare
 * @*array_second Second array to compare
 * @size Size of data to compare
 */
bool compare_arrays(char *array_first, char *array_second, int size) {
    for (int count = 0; count < size; ++count) {
        if (array_first[count] != array_second[count]) return false;
    }

    return true;
}

/** \fn main
 * This test comet_program_t object and function who work on thos object.
 * This report tests state to std out pipe. You would compile it and run
 * as program in your operating system to run all tests.
 */
int main() {
    printf("This make tests on program space object!\n");

    printf("Creating object...");
    comet_program_t test_program = comet_create_program();

    printf("Loading test program...\n");
    comet_program_load(&test_program, TEST_PROGRAM, TEST_PROGRAM_SIZE);

    printf("Loading size ");
    printf((test_program.size == 20) ? "work\n" : "not work\n");

    printf("Poping program data ");
    char poped[3];
    for (int count = 0; count < 3; ++count) {
        poped[count] = comet_program_pop(&test_program);
    }
    printf(
        (compare_arrays(poped, TEST_PROGRAM, 3)) ? "work\n" : "not work\n"
    );

    printf("Serial pop ");
    comet_program_serial_pop(&test_program, poped, 3);
    printf(
        (compare_arrays(poped, TEST_PROGRAM + 3, 3)) ? "work\n" : "not work\n"
    );

    printf("Relative jump ");
    comet_program_relative_jump(&test_program, 5);
    comet_program_serial_pop(&test_program, poped, 3);
    printf(
        (compare_arrays(poped, TEST_PROGRAM + 11, 3)) ? "work\n" : "not work\n"
    );

    printf("Absolute jump ");
    comet_program_absolute_jump(&test_program, 2);
    comet_program_serial_pop(&test_program, poped, 3);
    printf(
        (compare_arrays(poped, TEST_PROGRAM + 2, 3)) ? "work\n" : "not work\n"
    );
}
