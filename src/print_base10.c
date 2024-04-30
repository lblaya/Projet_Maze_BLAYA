#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "maze.h"

static void tc_putchar(char c)
{
    write(1, &c, 1);
}

static int get_digit(int nb, int index)
{
    int res;

    res = nb;
    while (index != 0) {
        res = res / 10;
        index = index - 1;
    }
    res = res % 10;
    return res;
}

static int nb_len(int nb)
{
    int res;

    res = 0;
    while (nb >= 1) {
        nb = nb / 10;
        res = res + 1;
    }
    return res;
}

int print_base10(int nb)
{
    int conteur;

    conteur = nb_len(nb) - 1;
    if (nb < 0) {
        tc_putchar('-');
    }
    if (nb == 0) {
        tc_putchar('0');
    }
    while (conteur >= 0) {
        tc_putchar(get_digit(nb, conteur) + 48);
        conteur = conteur - 1;
    }
    if (nb < 0) {
        tc_putchar(nb_len(nb) + 1);
    } else {
        tc_putchar(nb_len(nb));
    }
    return 0;
}
