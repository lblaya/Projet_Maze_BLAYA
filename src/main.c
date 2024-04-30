#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "maze.h"

int main(int ac, char **av)
{
    if (ac == 2) {
        find_exit(av[1]);
    }
    return 0;
}
