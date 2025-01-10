#include "push_swap.h"
#include <stdlib.h>
#include <limits.h>

int parse_arguments(int argc, char **argv, t_stack *a) {
    int i;
    long num;

    for (i = 1; i < argc; i++) {
        if (!is_valid_number(argv[i]) || (num = strtol(argv[i], NULL, 10)) < INT_MIN || num > INT_MAX || contains(a, (int)num)) {
            free_stack(a);
            return 0;
        }
        push(a, (int)num);
    }
    return 1;
}

int is_valid_number(const char *str) {
    int i = 0;

    if (str[i] == '-' || str[i] == '+')
        i++;
    if (!str[i])
        return 0;
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return 1;
}
