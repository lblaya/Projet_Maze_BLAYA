#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "maze.h"

static char *map(char *filename)
{
    int total_bytes;
    char *buffer;
    int bytes_read;
    char *second_buffer;
    int file;

    total_bytes = 0;
    buffer = malloc(sizeof(char) * 100);
    file = open(filename, O_RDONLY);
    bytes_read = read(file, buffer, 100);
    total_bytes = bytes_read;
    while (bytes_read > 0) {
        bytes_read = read(file, buffer, 100);
        total_bytes = total_bytes + bytes_read;
    }
    second_buffer = malloc(sizeof(char) * (total_bytes + 1));
    close(file);
    file = open(filename, O_RDONLY);
    second_buffer[total_bytes] = '\0';
    read(file, second_buffer, total_bytes);
    close(file);
    free(buffer);
    return second_buffer;
}

static int height(char *filename)
{
    char *buffer_height;
    int cnt;
    int height_value;

    cnt = 0;
    height_value = 0;
    buffer_height = map(filename);
    while (buffer_height[cnt] != '\0') {
        if (buffer_height[cnt] == '\n') {
            height_value = height_value + 1;
        }
        cnt = cnt + 1;
    }
    free(buffer_height);
    return height_value;
}

static int width(char *filename)
{
    char *buffer_width;
    int width_value;
    int cnt;

    cnt = 0;
    width_value = 0;
    buffer_width = map(filename);
    while (buffer_width[cnt] != '\0') {
        if (buffer_width[cnt] != '\n') {
            width_value = width_value + 1;
        }
        cnt = cnt + 1;
    }
    width_value = width_value / height(filename);
    free(buffer_width);
    return width_value;
}

static int start_index(char *filename)
{
    unsigned int cnt;
    char *buffer_index;

    cnt = 0;
    buffer_index = map(filename);
    while (buffer_index[cnt] != '\0' && buffer_index[cnt] != 'S') {
        cnt = cnt + 1;
    }
    free(buffer_index);
    return cnt;
}

struct map_info *map_infos(char *filename)
{
    struct map_info *map_info;

    map_info = malloc(sizeof(struct map_info));
    map_info->map = map(filename);
    map_info->height = height(filename);
    map_info->width = width(filename);
    map_info->start_index = start_index(filename);
    if ((map_info->height * map_info->width) !=
        (int)stu_strlen(map_info->map) - map_info->height) {
        write(1, "Map ", 4);
        write(1, filename, stu_strlen(filename));
        write(1, " is invalid.\n", 13);
        free(map_info->map);
        free(map_info);
        map_info = NULL;
    }
    return map_info;
}
