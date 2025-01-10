#include "push_swap.h"

void sort_stack(t_stack *a, t_stack *b) {
    if (a->size <= 3) {
        sort_small_stack(a);
    } else if (a->size <= 5) {
        sort_medium_stack(a, b);
    } else {
        radix_sort(a, b);
    }
}

void sort_small_stack(t_stack *a) {
    if (a->size == 2 && a->top->value > a->top->next->value) {
        sa(a);
    } else if (a->size == 3) {
        if (a->top->value > a->top->next->value)
            sa(a);
        if (a->top->next->value > a->top->next->next->value)
            rra(a);
        if (a->top->value > a->top->next->value)
            sa(a);
    }
}

void sort_medium_stack(t_stack *a, t_stack *b) {
    while (a->size > 3) {
        bring_to_top(a, find_min(a)); // Apporte le plus petit élément en haut
        pb(a, b); // Déplace le plus petit élément dans b
    }
    sort_small_stack(a); // Trie les 3 éléments restants
    while (b->size > 0) {
        pa(a, b); // Récupère les éléments triés depuis b
    }
}

void radix_sort(t_stack *a, t_stack *b) {
    int max_bits = get_max_bits(a);
    for (int i = 0; i < max_bits; i++) {
        int size = a->size;
        for (int j = 0; j < size; j++) {
            if (((a->top->value >> i) & 1) == 0)
                pb(a, b);
            else
                ra(a);
        }
        while (b->size > 0)
            pa(a, b);
    }
}
