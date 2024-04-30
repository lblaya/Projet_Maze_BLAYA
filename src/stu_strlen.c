#include "maze.h"

unsigned int stu_strlen(const char *str)
{
    int c;

    c = 0;
    while (str[c] != '\0') {
        c = c + 1;
    }
    return c;
}
