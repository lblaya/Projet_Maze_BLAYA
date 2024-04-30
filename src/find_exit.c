#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "maze.h"

static struct coords *coords_init(int map_width, struct coords *coords)
{
    if (coords->search_state == G_NOT_FOUND) {
        if (coords->view == SOUTH) {
            coords = watching_south(map_width, coords);
        } else if (coords->view == EAST) {
            coords = watching_east(map_width, coords);
        } else if (coords->view == NORTH) {
            coords = watching_north(map_width, coords);
        } else if (coords->view == WEST) {
            coords = watching_west(map_width, coords);
        }
    }
    return coords;
}

static int print_map_infos(int width, int height)
{
    write(1, "width : ", 8);
    print_base10(width);
    write(1, ", height : ", 11);
    print_base10(height);
    write(1, "\n", 1);
    return 0;
}

static void free_maze_info(struct map_info *maze_info)
{
    free(maze_info->map);
    free(maze_info);
}

static void free_struct(struct map_info *maze_info, struct coords *coords)
{
    free_maze_info(maze_info);
    free(coords);
}

int find_exit(char *filename)
{
    struct map_info *maze_info;
    int map_width;
    struct coords *coords;

    maze_info = map_infos(filename);
    if (maze_info != NULL) {
        map_width = maze_info->width;
        coords = start_coords(maze_info);
        print_map_infos(maze_info->width, maze_info->height);
        while (coords != NULL) {
            coords = coords_init(map_width, coords);
            if (coords->search_state == G_FOUND) {
                write(1, coords->dynamic_map, stu_strlen(coords->dynamic_map));
                free_struct(maze_info, coords);
                return 0;
            } else if (coords->search_state == BACK_TO_START) {
                write(1, "No solution to maze.\n", 21);
                free_struct(maze_info, coords);
                return 1;
            }
        }
        write(1, "No S found.\n", 12);
        free_struct(maze_info, coords);
    }
    return -1;
}
