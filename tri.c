#include "push_swap.h"


// Trouver la position correcte d'un élément dans STACK_B
int find_position_in_b(t_stack *b, int value) {
    t_node *current = b->top;
    int position = 0;
    int max_value = INT_MIN;
    int min_value = INT_MAX;

    // Trouver le maximum et le minimum dans STACK_B
    while (current) {
        if (current->value > max_value) max_value = current->value;
        if (current->value < min_value) min_value = current->value;
        current = current->next;
    }

    current = b->top;
    while (current) {
        if (value > current->value && value < current->next->value) {
            return position + 1; // Entre current et current->next
        }
        position++;
        current = current->next;
    }

    // Si c'est un nouveau max ou min
    return (value > max_value || value < min_value) ? 0 : position;
}

// Déplacer les éléments de STACK_A vers STACK_B
void push_to_b(t_stack *a, t_stack *b) {
    while (a->size > 0) {
        int value = a->top->value; // Récupérer la valeur en haut de STACK_A
        int position = find_position_in_b(b, value);

        // Effectuer les rotations nécessaires pour positionner correctement
        if (position <= b->size / 2) {
            while (position--) rb(b);
        } else {
            position = b->size - position;
            while (position--) rrb(b);
        }

        pb(a, b); // Pousser dans STACK_B
    }
}

// Rapatrier les éléments de STACK_B vers STACK_A
void push_to_a(t_stack *a, t_stack *b) {
    while (b->size > 0) {
        pa(a, b);
    }
}

// Gérer les cas spéciaux pour une pile de taille 3
void sort_three(t_stack *stack) {
    if (stack->size != 3) return;

    int first = stack->top->value;
    int second = stack->top->next->value;
    int third = stack->top->next->next->value;

    if (first > second && second < third && first < third)
        sa(stack);
    else if (first > second && second > third)
        sa(stack), rra(stack);
    else if (first > second && first > third && second < third)
        ra(stack);
    else if (first < second && second > third && first < third)
        sa(stack), ra(stack);
    else if (first < second && second > third && first > third)
        rra(stack);
}

void sort_stack(t_stack *a, t_stack *b) {
    printf("Initial STACK_A:\n");
    print_stack("A", a);

    if (a->size <= 3) {
        sort_three(a);
        return;
    }

    push_to_b(a, b);
    printf("After pushing to STACK_B:\n");
    print_stack("A", a);
    print_stack("B", b);

    push_to_a(a, b);
    printf("After pushing back to STACK_A:\n");
    print_stack("A", a);
}
