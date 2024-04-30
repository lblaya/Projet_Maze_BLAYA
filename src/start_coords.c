#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "maze.h"

static struct coords *set_direction(int i,
                                    int width,
                                    struct coords *start)
{
    if (start->dynamic_map[i] == 'S') {
        if (start->dynamic_map[i - 1] == '#' &&
            start->dynamic_map[i + 1] == '#' &&
            start->dynamic_map[i + width + 1] == '.') {
            start->view = SOUTH;
        } else if (start->dynamic_map[i - width - 1] == '#' &&
                   start->dynamic_map[i + width + 1] == '#' &&
                   start->dynamic_map[i - 1] == '.') {
            start->view = WEST;
        } else if (start->dynamic_map[i - 1] == '#' &&
                   start->dynamic_map[i + 1] == '#' &&
                   start->dynamic_map[i - width - 1] == '.') {
            start->view = NORTH;
        } else if (start->dynamic_map[i - width - 1] == '#' &&
                   start->dynamic_map[i + width + 1] == '#' &&
                   start->dynamic_map[i + 1] == '.') {
            start->view = EAST;
        } else {
            start = NULL;
        }
    } else {
        start = NULL;
    }
    return start;
}

struct coords *start_coords(struct map_info *map_info)
{
    int width;
    int i;
    char *map;
    struct coords *start_coords;

    width = map_info->width;
    i = map_info->start_index;
    map = map_info->map;
    start_coords = (struct coords *)malloc(sizeof(struct coords));
    start_coords->idx = i;
    start_coords->dynamic_map = map;
    start_coords->search_state = G_NOT_FOUND;
    start_coords = set_direction(i, width, start_coords);
    return start_coords;
}
