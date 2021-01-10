/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Defines game_object_hallway_top_make_next_hallway_part
*/

#include "internal.h"
#include "my/assert.h"
#include <SFML/Graphics/RectangleShape.h>

sfRectangleShape *game_object_hallway_top_make_next_hallway_part(
    sfRectangleShape *current_part, int offset_y, int size_y, sfColor color)
{
    sfRectangleShape *result = sfRectangleShape_copy(current_part);

    MY_ASSERT(result != NULL);
    sfRectangleShape_setPosition(result, (sfVector2f){
        sfRectangleShape_getPosition(result).x, sfRectangleShape_getPosition(
        result).y + offset_y});
    sfRectangleShape_setSize(result, (sfVector2f){sfRectangleShape_getSize(
        result).x, size_y});
    sfRectangleShape_setFillColor(result, color);
    return (result);
}
