#include "push_swap.h"
#include <unistd.h>

void sa(t_stack *a) {
    if (a->size < 2)
        return;
    int temp = a->top->value;
    a->top->value = a->top->next->value;
    a->top->next->value = temp;
    write(1, "sa\n", 3);
}

void pb(t_stack *a, t_stack *b) {
    if (a->size == 0)
        return;
    push(b, pop(a));
    write(1, "pb\n", 3);
}

void pa(t_stack *a, t_stack *b) {
    if (b->size == 0)
        return;
    push(a, pop(b));
    write(1, "pa\n", 3);
}

void ra(t_stack *a) {
    if (a->size < 2)
        return;
    push_bottom(a, pop(a)); // Référence corrigée
    write(1, "ra\n", 3);
}

void rra(t_stack *a) {
    if (a->size < 2)
        return;
    int value = pop_bottom(a);
    push(a, value);
    write(1, "rra\n", 4);
}
