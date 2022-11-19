#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "../comet_include/types.h"
#include "../comet_include/stack.h"

/** \fn comet_stack_create
 * This function allocate new stack object in heap and return pointer to it.
 * This stack is auto initialized.
 */
comet_stack_t *comet_stack_create() {
    comet_stack_t *stack = malloc(sizeof(comet_stack_t));
    
    comet_stack_initialize(stack);

    return stack;
}

/** \fn comet_stack_initialize
 * This function initialize new stack. You must give any pointer to no 
 * initialize stack. 
 * @*stack Stack to initialize
 */
bool comet_stack_initialize(comet_stack_t *stack) {
    stack->size = 0x00;
    stack->position = 0x00;
    stack->space = malloc(0x00 * sizeof(comet_word_t));

    return stack->space != NULL;
}

/** \fn comet_stack_push
 * This push one item into stack. If memory in stack finished, this auto
 * realloc more memory. If return true, all went fine, else something went
 * wrong.
 * @*stack Stack to put into
 * @data Data to push into stack
 */
bool comet_stack_push(comet_stack_t *stack, comet_word_t data) {
    if (stack->size == stack->position) {
        stack->size += ALLOCATE_STEP;
        stack->space = realloc(
            stack->space, stack->size * sizeof(comet_word_t)
        );
    
        if (stack->space == NULL) return false;
    }

    stack->space[stack->position] = data;
    ++stack->position;

    return true;
}

/** \fn comet_stack_pop 
 * This pop one item from stack. If memory is no longer needed, this realloc
 * and it give memory back to system. If stack is blank, return 0x00.
 * @*stack Stack to pop from
 */
comet_word_t comet_stack_pop(comet_stack_t *stack) {
    if (stack->size == 0x00) return 0x00;
    if (stack->position > 0x00) --stack->position;

    comet_word_t from_stack = stack->space[stack->position];

    if (stack->size - ALLOCATE_STEP == stack->position) {
        stack->size -= ALLOCATE_STEP;
        stack->space = realloc(
            stack->space, stack->size * sizeof(comet_word_t)
        );
    }

    return from_stack;
}
