#ifndef MAZE_H_
#define MAZE_H_

enum direction {
    SOUTH,
    WEST,
    NORTH,
    EAST
};

enum search_state {
    G_FOUND,
    G_NOT_FOUND,
    BACK_TO_START
};

struct coords {
    int idx;
    char *dynamic_map;
    enum direction view;
    enum search_state search_state;
};

struct map_info {
    char *map;
    int height;
    int width;
    int start_index;
};

unsigned int stu_strlen(const char *str);
int print_base10(int nb);
struct map_info *map_infos(char *filename);
struct coords *start_coords(struct map_info *map_info);
struct coords *watching_west(int width, struct coords *map_info);
struct coords *watching_east(int width, struct coords *map_info);
struct coords *watching_north(int width, struct coords *map_info);
struct coords *watching_south(int width, struct coords *map_info);
int find_exit(char *filename);
int main(int ac, char **av);

#endif
