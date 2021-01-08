/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Defines game_object_building_rect
*/

#include "building_rect.h"
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <stdlib.h>

struct building_rect_data {
    sfRectangleShape *rect;
};

static void do_draw(struct game_object *self, sfRenderWindow *window)
{
    struct building_rect_data *data = self->private_data;

    sfRenderWindow_drawRectangleShape(window, data->rect, NULL);
}

static void do_destroy(struct game_object *self)
{
    struct building_rect_data *data = self->private_data;

    sfRectangleShape_destroy(data->rect);
}

struct game_object game_object_create_building_rect(
    struct game_state_play_sequence *sequence)
{
    struct game_object result;
    struct building_rect_data *data = malloc(sizeof(data));

    result.draw = do_draw;
    result.destroy = do_destroy;
    result.update = NULL;
    data->rect = sfRectangleShape_create();
    sfRectangleShape_setPosition(data->rect, sequence->position);
    sfRectangleShape_setSize(data->rect,
        (sfVector2f){sequence->width, sequence->height});
    sfRectangleShape_setFillColor(data->rect, sfColor_fromRGB(134, 134, 150));
    result.rect = sfRectangleShape_getGlobalBounds(data->rect);
    result.private_data = data;
    return (result);
}
