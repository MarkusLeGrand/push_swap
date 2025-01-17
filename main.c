#include "push_swap.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    t_stack a;
    t_stack b;

    if (argc < 2)
        return 0;

    init_stack(&a);
    init_stack(&b);

    if (!parse_arguments(argc, argv, &a)) {
        fprintf(stderr, "Error\n");
        return 1;
    }

    sort_stack(&a, &b);
    free_stack(&a);
    free_stack(&b);

    return 0;
}
