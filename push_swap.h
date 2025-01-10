#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>

// Structures
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

// Sorting
void sort_stack(t_stack *a, t_stack *b);
void sort_small_stack(t_stack *a);
void sort_medium_stack(t_stack *a, t_stack *b);
void radix_sort(t_stack *a, t_stack *b);
int find_min(t_stack *stack);
int get_max_bits(t_stack *stack);

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
void init_stack(t_stack *stack);
void push(t_stack *stack, int value);
int pop(t_stack *stack);
int pop_bottom(t_stack *stack);
void push_bottom(t_stack *stack, int value);
void bring_to_top(t_stack *stack, int value);
void free_stack(t_stack *stack);
int contains(t_stack *stack, int value);

#endif
