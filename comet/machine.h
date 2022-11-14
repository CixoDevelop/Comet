#ifndef COMET_MACHINE_H_INCLUDED
#define COMET_MACHINE_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/** \typedef comet_word_t
 * This is base item in comet instance.
 */
typedef char comet_word_t;

/** \struct comet_stack_t
 * This struct store stack for comet instance.
 */
typedef struct {
    
    /* Store current stack size */
    size_t size;

    /* Store current position in stack */
    comet_word_t *pointer;
    
    /* Store pointer to stack space */
    comet_word_t *space;

} comet_stack_t;

/** \struct comet_program_t 
 * This struct store program for comet instance.
 */
typedef struct {

    /* Store program size */
    size_t size;

    /* Store current position in program */
    comet_word_t *pointer;

    /* Store pointer to program space */
    comet_word_t *space;

} comet_program_t;

/** \struct comet_instance_t
 * This struct store comet instance.
 */
typedef struct {

    /* Program executed in instance */
    comet_program_t program;

    /* Stack for functions return address */
    comet_stack_t call_stack;

    /* Stack for data */
    comet_stack_t data_stack;

    /* Registers for working on */
    comet_word_t flags;
    comet_word_t register_a;
    comet_word_t register_b;

} comet_instance_t;

/** \fn comet_create_program
 * This create and return object for storing comet program.
 */
comet_program_t comet_create_program();

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
);

/** \fn comet_program_absolute_jump
 * This function make absolute jump in program space. If position is over
 * program size, return false. If all gone well, return true.
 * @*program Program to make jump on
 * @position Position in program spece to jump in
 */
bool comet_program_absolute_jump(comet_program_t *program, size_t position);

/** \fn comet_program_relative_jump
 * This make relative jump in program space by position given in parameter.
 * If that position is over program space size, return false, if all gone 
 * well, return true.
 * @*program Program to work on
 * position Position to jump by them
 */
bool comet_program_relative_jump(comet_program_t *program, size_t position);

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
);

/** \fn comet_program_pop
 * This get one item from program space and return it.
 * @*program Program container to load from
 */
comet_word_t comet_program_pop(comet_program_t *program);

/** \fn comet_create_stack
 * This create and return new clean stack.
 */
comet_stack_t comet_create_stack();

/** \fn comet_pop_stack
 * This pop one item from stack.
 * @*stack Stack object to get from
 */
comet_word_t comet_pop_stack(comet_stack_t *stack);

/** \fn comet_push_stack
 * This insert one item into stack.
 * @*stack Stack to insert into stack
 * @data Data to insert 
 */
bool comet_push_stack(comet_stack_t *stack, comet_word_t data);

/** \fn comet_create_instance 
 * This create instance of comet virtual machine.
 * @program Program to run in instance
 */
comet_instance_t comet_create_instance(comet_program_t program);

/** \fn comet_execute_instance
 * This run comet instance.
 * @*instance Comet instance to run
 */
int comet_execute_instance(comet_instance_t *instance);

#endif
