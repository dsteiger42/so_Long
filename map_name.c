#include "so_long.h"

int check_map_name(char *map_name)
{
    int len;

    if (!map_name)
    {
        printf("ERROR: Invalid pointer to file name\n");
        return (1);
    }
    len = strlen(map_name);
    if (len < 4 || strncmp(&map_name[len - 4], ".ber", 4) != 0)
    {
        printf("ERROR: Invalid map name, should end with .ber\n");
        return (1);
    }
    return (0);
}

