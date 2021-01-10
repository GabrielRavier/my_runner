/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Defines game_create_map
*/

#include "internal.h"
#include "my/my_string.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/fcntl.h>
#include <sys/types.h>

bool game_create_map(struct my_string **read_map, const char *map_filename)
{
    int map_fd = open(map_filename, O_RDONLY);
    static const size_t READ_SIZE = 2000;
    ssize_t read_retval;

    if (map_fd < 0)
        return (false);
    *read_map = my_string_new();
    do {
        my_string_resize(*read_map, (*read_map)->length + READ_SIZE);
        read_retval = read(map_fd, (*read_map)->string + (*read_map)->length -
            READ_SIZE, READ_SIZE);
        if (read_retval < 0)
            return (false);
    } while ((size_t)read_retval == READ_SIZE);
    my_string_resize(*read_map, (*read_map)->length - READ_SIZE + read_retval);
    return (true);
}
