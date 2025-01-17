#include "push_swap.h"
#include <stdlib.h>

int contains(t_stack *stack, int value) {
    t_node *current = stack->top;
    while (current) {
        if (current->value == value)
            return 1;
        current = current->next;
    }
    return 0;
}

int find_min(t_stack *stack) {
    int min_index = 0;
    int min_value = stack->top->value;
    t_node *current = stack->top;
    int index = 0;
    while (current) {
        if (current->value < min_value) {
            min_value = current->value;
            min_index = index;
        }
        current = current->next;
        index++;
    }
    return min_index;
}

void bring_to_top(t_stack *stack, int index) {
    if (index <= stack->size / 2) {
        while (index--)
            ra(stack);
    } else {
        index = stack->size - index;
        while (index--)
            rra(stack);
    }
}

int get_max_bits(t_stack *stack) {
    int max_value = 0;
    int bits = 0;
    t_node *current = stack->top;
    while (current) {
        if (current->value > max_value)
            max_value = current->value;
        current = current->next;
    }
    while (max_value >> bits)
        bits++;
    return bits;
}

void print_stack(const char *name, t_stack *stack) {
    printf("Stack %s (size: %d): ", name, stack->size);
    t_node *current = stack->top;
    while (current) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

// Initialisation de la pile
void init_stack(t_stack *stack) {
    stack->top = NULL;
    stack->size = 0;
}

// Ajouter un élément au sommet de la pile
void push(t_stack *stack, int value) {
    t_node *new_node = malloc(sizeof(t_node));
    if (!new_node)
        exit(EXIT_FAILURE);
    new_node->value = value;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
}

// Retirer un élément du sommet de la pile
int pop(t_stack *stack) {
    if (!stack->top)
        return 0;
    t_node *temp = stack->top;
    int value = temp->value;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    return value;
}

// Libérer toute la pile
void free_stack(t_stack *stack) {
    while (stack->top)
        pop(stack);
}
