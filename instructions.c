#include "push_swap.h"

void sa(t_stack *a) {
    if (a->size < 2)
        return;
    int first = pop(a);
    int second = pop(a);
    push(a, first);
    push(a, second);
    printf("sa\n");
}

void sb(t_stack *b) {
    if (b->size < 2)
        return;
    int first = pop(b);
    int second = pop(b);
    push(b, first);
    push(b, second);
    printf("sb\n");
}

void ss(t_stack *a, t_stack *b) {
    sa(a);
    sb(b);
    printf("ss\n");
}

void pa(t_stack *a, t_stack *b) {
    if (b->size > 0) {
        push(a, pop(b));
        printf("pa\n");
    }
}

void pb(t_stack *a, t_stack *b) {
    if (a->size > 0) {
        push(b, pop(a));
        printf("pb\n");
    }
}

void ra(t_stack *a) {
    if (a->size > 1) {
        int value = pop(a);
        t_node *current = a->top;
        while (current && current->next) {
            current = current->next;
        }
        t_node *new_node = malloc(sizeof(t_node));
        if (!new_node)
            exit(EXIT_FAILURE);
        new_node->value = value;
        new_node->next = NULL;
        if (current)
            current->next = new_node;
        else
            a->top = new_node;
        a->size++;
    }
    printf("ra\n");
}

void rb(t_stack *b) {
    if (b->size > 1) {
        int value = pop(b);
        t_node *current = b->top;
        while (current && current->next) {
            current = current->next;
        }
        t_node *new_node = malloc(sizeof(t_node));
        if (!new_node)
            exit(EXIT_FAILURE);
        new_node->value = value;
        new_node->next = NULL;
        if (current)
            current->next = new_node;
        else
            b->top = new_node;
        b->size++;
    }
    printf("rb\n");
}

void rr(t_stack *a, t_stack *b) {
    ra(a);
    rb(b);
    printf("rr\n");
}

void rra(t_stack *a) {
    if (a->size > 1) {
        t_node *prev = NULL;
        t_node *current = a->top;
        while (current && current->next) {
            prev = current;
            current = current->next;
        }
        if (prev)
            prev->next = NULL;
        if (current) {
            current->next = a->top;
            a->top = current;
        }
        a->size++;
    }
    printf("rra\n");
}

void rrb(t_stack *b) {
    if (b->size > 1) {
        t_node *prev = NULL;
        t_node *current = b->top;
        while (current && current->next) {
            prev = current;
            current = current->next;
        }
        if (prev)
            prev->next = NULL;
        if (current) {
            current->next = b->top;
            b->top = current;
        }
        b->size++;
    }
    printf("rrb\n");
}

void rrr(t_stack *a, t_stack *b) {
    rra(a);
    rrb(b);
    printf("rrr\n");
}
