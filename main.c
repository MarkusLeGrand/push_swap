#include "push_swap.h"
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    t_stack a, b;

    if (argc < 2) {
        return 0; // Aucun argument, rien à afficher
    }

    init_stack(&a);
    init_stack(&b);

    if (!parse_arguments(argc, argv, &a)) {
        write(2, "Error\n", 6);
        return 1;
    }

    sort_stack(&a, &b);

    free_stack(&a);
    free_stack(&b);
    return 0;
}
