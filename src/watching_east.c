#include <stddef.h>
#include "maze.h"

static int verif_start_east(int idx, int y, char *dynamic_map)
{
    if ((dynamic_map[idx + 1] == '.' ||
         dynamic_map[idx + 1] == ' ') &&
        ((dynamic_map[idx + y] == '.' ||
          dynamic_map[idx + y] == ' ') ||
         (dynamic_map[idx - y] == '.' ||
          dynamic_map[idx - y] == ' '))) {
        return 1;
    } else if ((dynamic_map[idx + 1] == '.' ||
                dynamic_map[idx + 1] == ' ') &&
               (dynamic_map[idx - y] == 'S' ||
                dynamic_map[idx + y] == 'S') &&
               (dynamic_map[idx] == '.')) {
        return 1;
    }
    return 0;
}

static struct coords *verif_watching_east(int idx,
                                          int y,
                                          struct coords *map_info)
{
    if (map_info->dynamic_map[idx - y] == 'S' ||
        map_info->dynamic_map[idx + 1] == 'S') {
        map_info->search_state = BACK_TO_START;
    } else if (map_info->dynamic_map[idx - y] == 'G' ||
               map_info->dynamic_map[idx + 1] == 'G') {
        map_info->dynamic_map[idx] = ' ';
        map_info->search_state = G_FOUND;
    } else if (map_info->dynamic_map[idx - y] == '.' ||
               map_info->dynamic_map[idx - y] == ' ') {
        map_info->view = NORTH;
    } else if (map_info->dynamic_map[idx + 1] == '#') {
        map_info->view = SOUTH;
    } else {
        map_info = NULL;
    }
    return map_info;
}

struct coords *watching_east(int width, struct coords *map_info)
{
    int idx;
    int y;

    idx = map_info->idx;
    y = width + 1;
    if (verif_start_east(idx, y, map_info->dynamic_map) == 1) {
        map_info->dynamic_map[idx] = ' ';
        idx += 1;
    }
    while ((map_info->dynamic_map[idx + 1] == '.' ||
            map_info->dynamic_map[idx + 1] == ' ') &&
           map_info->dynamic_map[idx - y] == '#') {
        if (map_info->dynamic_map[idx] != 'S') {
            map_info->dynamic_map[idx] = ' ';
        }
        idx += 1;
    }
    map_info->idx = idx;
    map_info = verif_watching_east(idx, y, map_info);
    return map_info;
}
