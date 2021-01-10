/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Declares internal stuff for game_object_hallway_top
*/

#pragma once

#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Types.h>

struct game_object_hallway_top_data {
    sfRectangleShape *hallway_top;
    sfRectangleShape *line_left;
    sfRectangleShape *line_right;
    sfRectangleShape *black_hallway_part;
    sfRectangleShape *gray_hallway_part;
    sfRectangleShape *light_gray_hallway_part;
    sfRectangleShape *line_bottom;
    sfRectangleShape *line_bottom2;
};

sfRectangleShape *game_object_hallway_top_make_next_hallway_part(
    sfRectangleShape *current_part, int offset_y, int size_y, sfColor color);
