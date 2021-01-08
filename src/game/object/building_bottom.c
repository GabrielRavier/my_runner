/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Defines game_object_building_rect
*/

#include "building_bottom.h"
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <stdlib.h>

struct building_bottom_data {
    sfRectangleShape *top_line;
    sfRectangleShape *line2;
};

static void do_draw(struct game_object *self, sfRenderWindow *window)
{
    struct building_bottom_data *data = self->private_data;

    sfRenderWindow_drawRectangleShape(window, data->top_line, NULL);
    sfRenderWindow_drawRectangleShape(window, data->line2, NULL);
}

static void do_destroy(struct game_object *self)
{
    struct building_bottom_data *data = self->private_data;

    sfRectangleShape_destroy(data->top_line);
    sfRectangleShape_destroy(data->line2);
}

struct game_object game_object_create_building_bottom(
    struct game_state_play_sequence *sequence)
{
    struct game_object result;
    struct building_bottom_data *data = malloc(sizeof(*data));

    result.draw = do_draw;
    result.destroy = do_destroy;
    result.update = NULL;
    data->top_line = sfRectangleShape_create();
    sfRectangleShape_setPosition(data->top_line, sequence->position);
    sfRectangleShape_setSize(data->top_line,
        (sfVector2f){sequence->width, 1});
    sfRectangleShape_setFillColor(data->top_line, sfColor_fromRGB(77, 77, 89));
    data->line2 = sfRectangleShape_copy(data->top_line);
    sfRectangleShape_setPosition(data->line2, (sfVector2f){sequence->position.x,
        sequence->position.y + 1});
    sfRectangleShape_setFillColor(data->line2, sfColor_fromRGB(255, 255, 255));
    result.rect = (sfFloatRect){sequence->position.x, sequence->position.y,
        sequence->width, sequence->height};
    result.private_data = data;
    return (result);
}
