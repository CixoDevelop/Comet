#ifndef COMET_STACK_H_INCLUDED
#define COMET_STACK_H_INCLUDED

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "types.h"

/** \def ALLOCATE_STEP
 * This is stepping for memory allocation. Default 0x10.
 */
#ifndef ALLOCATE_STEP
#define ALLOCATE_STEP 0x10
#endif

/** \struct comet_stack_t
 * This struct store stack.
 */
typedef struct {
   
    /* This is currently stack size */
    comet_pointer_t size;

    /* This is currently position on stack */
    comet_pointer_t position;

    /* This is stack area from malloc */
    comet_word_t *space;    

} comet_stack_t;

/** \fn comet_stack_create
 * This function allocate new stack object in heap and return pointer to it.
 * This stack is auto initialized.
 */
comet_stack_t *comet_stack_create();

/** \fn comet_stack_initialize
 * This function initialize new stack. You must give any pointer to no 
 * initialize stack. 
 * @*stack Stack to initialize
 */
bool comet_stack_initialize(comet_stack_t *stack);

/** \fn comet_stack_push
 * This push one item into stack. If memory in stack finished, this auto
 * realloc more memory. If return true, all went fine, else something went
 * wrong.
 * @*stack Stack to put into
 * @data Data to push into stack
 */
bool comet_stack_push(comet_stack_t *stack, comet_word_t data);

/** \fn comet_stack_pop 
 * This pop one item from stack. If memory is no longer needed, this realloc
 * and it give memory back to system. If stack is blank, return 0x00.
 * @*stack Stack to pop from
 */
comet_word_t comet_stack_pop(comet_stack_t *stack);

#endif
