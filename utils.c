#include "push_swap.h"
#include <stdlib.h>

void init_stack(t_stack *stack) {
    stack->top = NULL;
    stack->size = 0;
}

void push(t_stack *stack, int value) {
    t_node *new_node = malloc(sizeof(t_node));
    if (!new_node)
        return;
    new_node->value = value;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
}

int pop(t_stack *stack) {
    if (stack->size == 0)
        return 0;
    t_node *temp = stack->top;
    int value = temp->value;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    return value;
}

int pop_bottom(t_stack *stack) {
    if (stack->size == 0)
        return 0;
    t_node *current = stack->top;
    if (!current->next) {
        int value = current->value;
        free(current);
        stack->top = NULL;
        stack->size--;
        return value;
    }
    while (current->next->next)
        current = current->next;
    int value = current->next->value;
    free(current->next);
    current->next = NULL;
    stack->size--;
    return value;
}

void push_bottom(t_stack *stack, int value) {
    t_node *new_node = malloc(sizeof(t_node));
    if (!new_node)
        return;
    new_node->value = value;
    new_node->next = NULL;
    if (!stack->top) {
        stack->top = new_node;
    } else {
        t_node *current = stack->top;
        while (current->next)
            current = current->next;
        current->next = new_node;
    }
    stack->size++;
}

void bring_to_top(t_stack *stack, int value) {
    int index = 0;
    t_node *current = stack->top;

    while (current && current->value != value) {
        current = current->next;
        index++;
    }
    if (index <= stack->size / 2) {
        while (index-- > 0)
            ra(stack);
    } else {
        index = stack->size - index;
        while (index-- > 0)
            rra(stack);
    }
}

void free_stack(t_stack *stack) {
    while (stack->size > 0)
        pop(stack);
}

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
    t_node *current = stack->top;
    int min = current->value;
    while (current) {
        if (current->value < min)
            min = current->value;
        current = current->next;
    }
    return min;
}

int get_max_bits(t_stack *stack) {
    t_node *current = stack->top;
    int max = 0;
    while (current) {
        if (current->value > max)
            max = current->value;
        current = current->next;
    }
    int bits = 0;
    while ((max >> bits) != 0)
        bits++;
    return bits;
}
