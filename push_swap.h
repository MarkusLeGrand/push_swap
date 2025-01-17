#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <stdlib.h>
#include <stdio.h>

#define INT_MIN (-2147483648)
#define INT_MAX 2147483647

typedef struct s_node {
    int value;
    struct s_node *next;
} t_node;

typedef struct s_stack {
    t_node *top;
    int size;
} t_stack;

// Parsing
int parse_arguments(int argc, char **argv, t_stack *a);
int is_valid_number(const char *str);

// Instructions
void sa(t_stack *a);
void sb(t_stack *b);
void ss(t_stack *a, t_stack *b);
void pa(t_stack *a, t_stack *b);
void pb(t_stack *a, t_stack *b);
void ra(t_stack *a);
void rb(t_stack *b);
void rr(t_stack *a, t_stack *b);
void rra(t_stack *a);
void rrb(t_stack *b);
void rrr(t_stack *a, t_stack *b);

// Utils
void print_stack(const char *name, t_stack *stack);
void init_stack(t_stack *stack);
void push(t_stack *stack, int value);
int pop(t_stack *stack);
void free_stack(t_stack *stack);
int contains(t_stack *stack, int value);
int find_min(t_stack *stack);
void bring_to_top(t_stack *stack, int index);
int get_max_bits(t_stack *stack);


// Tri
void sort_stack(t_stack *a, t_stack *b);
void sort_three(t_stack *stack);
void push_to_b(t_stack *a, t_stack *b);
void push_to_a(t_stack *a, t_stack *b);
int find_position_in_b(t_stack *b, int value);

#endif
