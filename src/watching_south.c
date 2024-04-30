#include <stddef.h>
#include "maze.h"

static int verif_start_south(int idx, int y, char *dynamic_map)
{
    if ((dynamic_map[idx + y] == '.' ||
         dynamic_map[idx + y] == ' ') &&
        ((dynamic_map[idx + 1] == '.' ||
          dynamic_map[idx + 1] == ' ') ||
         (dynamic_map[idx - 1] == '.' ||
          dynamic_map[idx - 1] == ' '))) {
        return 1;
    } else if ((dynamic_map[idx + y] == '.' ||
                dynamic_map[idx + y] == ' ') &&
               (dynamic_map[idx - 1] == 'S' ||
                dynamic_map[idx + 1] == 'S') &&
               (dynamic_map[idx] == '.')) {
        return 1;
    }
    return 0;
}

static struct coords *verif_watching_south(int idx,
                                           int y,
                                           struct coords *map_info)
{
    if (map_info->dynamic_map[idx + 1] == 'S' ||
        map_info->dynamic_map[idx + y] == 'S') {
        map_info->search_state = BACK_TO_START;
    } else if (map_info->dynamic_map[idx + 1] == 'G' ||
               map_info->dynamic_map[idx + y] == 'G') {
        map_info->dynamic_map[idx] = ' ';
        map_info->search_state = G_FOUND;
    } else if (map_info->dynamic_map[idx + 1] == '.' ||
               map_info->dynamic_map[idx + 1] == ' ') {
        map_info->view = EAST;
    } else if (map_info->dynamic_map[idx + y] == '#') {
        map_info->view = WEST;
    } else {
        map_info = NULL;
    }
    return map_info;
}

struct coords *watching_south(int width, struct coords *map_info)
{
    int idx;
    int y;

    idx = map_info->idx;
    y = width + 1;
    if (verif_start_south(idx, y, map_info->dynamic_map) == 1) {
        map_info->dynamic_map[idx] = ' ';
        idx += y;
    }
    while ((map_info->dynamic_map[idx + y] == '.' ||
            map_info->dynamic_map[idx + y] == ' ') &&
           map_info->dynamic_map[idx + 1] == '#') {
        if (map_info->dynamic_map[idx] != 'S') {
            map_info->dynamic_map[idx] = ' ';
        }
        idx += y;
    }
    map_info->idx = idx;
    map_info = verif_watching_south(idx, y, map_info);
    return map_info;
}
