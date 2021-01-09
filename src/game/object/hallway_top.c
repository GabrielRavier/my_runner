/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Defines game_object_hallway_top
*/

#include "hallway_top.h"
#include "my/assert.h"
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <stdlib.h>

struct hallway_top_data {
    sfRectangleShape *hallway_top;
    sfRectangleShape *line_left;
    sfRectangleShape *line_right;
    sfRectangleShape *black_hallway_part;
    sfRectangleShape *gray_hallway_part;
    sfRectangleShape *light_gray_hallway_part;
    sfRectangleShape *line_bottom;
    sfRectangleShape *line_bottom2;
};

static void do_draw(struct game_object *self, sfRenderWindow *window)
{
    struct hallway_top_data *data = self->private_data;

    sfRenderWindow_drawRectangleShape(window, data->hallway_top, NULL);
    sfRenderWindow_drawRectangleShape(window, data->black_hallway_part, NULL);
    sfRenderWindow_drawRectangleShape(window, data->gray_hallway_part, NULL);
    sfRenderWindow_drawRectangleShape(window, data->light_gray_hallway_part, NULL);
    sfRenderWindow_drawRectangleShape(window, data->line_bottom, NULL);
    sfRenderWindow_drawRectangleShape(window, data->line_bottom2, NULL);
    sfRenderWindow_drawRectangleShape(window, data->line_left, NULL);
    sfRenderWindow_drawRectangleShape(window, data->line_right, NULL);
}

static void do_destroy(struct game_object *self)
{
    struct hallway_top_data *data = self->private_data;

    sfRectangleShape_destroy(data->line_bottom2);
    sfRectangleShape_destroy(data->line_bottom);
    sfRectangleShape_destroy(data->light_gray_hallway_part);
    sfRectangleShape_destroy(data->gray_hallway_part);
    sfRectangleShape_destroy(data->black_hallway_part);
    sfRectangleShape_destroy(data->line_right);
    sfRectangleShape_destroy(data->line_left);
    sfRectangleShape_destroy(data->hallway_top);
}

struct game_object game_object_create_hallway_top(
    struct game_state_play_sequence *sequence, int hallway_height)
{
    struct game_object result;
    struct hallway_top_data *data = malloc(sizeof(*data));

    MY_ASSERT(data != NULL);
    result.private_data = data;
    result.draw = do_draw;
    result.destroy = do_destroy;
    result.update = NULL;
    data->hallway_top = sfRectangleShape_create();
    sfRectangleShape_setFillColor(data->hallway_top,
        sfColor_fromRGB(176, 176, 191));
    sfRectangleShape_setPosition(data->hallway_top, (sfVector2f){
        sequence->position.x, -1000});
    sfRectangleShape_setSize(data->hallway_top, (sfVector2f){sequence->width,
        1000 + sequence->position.y - hallway_height});
    data->line_left = sfRectangleShape_copy(data->hallway_top);
    sfRectangleShape_setSize(data->line_left, (sfVector2f){2,
        sfRectangleShape_getSize(data->line_left).y});
    sfRectangleShape_setFillColor(data->line_left,
        sfColor_fromRGB(100, 106, 125));
    data->line_right = sfRectangleShape_copy(data->line_left);
    sfRectangleShape_setPosition(data->line_right, (sfVector2f){
        sfRectangleShape_getPosition(data->line_right).x +
        sfRectangleShape_getSize(data->hallway_top).x - 2,
        sfRectangleShape_getPosition(data->line_right).y});
    data->black_hallway_part = sfRectangleShape_create();
    sfRectangleShape_setPosition(data->black_hallway_part,
        (sfVector2f){sequence->position.x,
        sequence->position.y - hallway_height});
    sfRectangleShape_setSize(data->black_hallway_part, (sfVector2f){
        sequence->width, hallway_height / 2});
    sfRectangleShape_setFillColor(data->black_hallway_part,
        sfColor_fromRGB(53, 53, 61));
    data->gray_hallway_part = sfRectangleShape_create();
    sfRectangleShape_setPosition(data->gray_hallway_part,
        (sfVector2f){sequence->position.x,
        sequence->position.y - hallway_height / 2});
    sfRectangleShape_setSize(data->gray_hallway_part, (sfVector2f){
        sequence->width, hallway_height / 4});
    sfRectangleShape_setFillColor(data->gray_hallway_part,
        sfColor_fromRGB(77, 77, 89));
    data->light_gray_hallway_part = sfRectangleShape_create();
    sfRectangleShape_setPosition(data->light_gray_hallway_part,
        (sfVector2f){sequence->position.x,
        sequence->position.y - hallway_height / 4});
    sfRectangleShape_setSize(data->light_gray_hallway_part, (sfVector2f){
        sequence->width, hallway_height / 4});
    sfRectangleShape_setFillColor(data->light_gray_hallway_part,
        sfColor_fromRGB(100, 106, 125));
    data->line_bottom = sfRectangleShape_create();
    sfRectangleShape_setPosition(data->line_bottom, (sfVector2f){
        sequence->position.x, sequence->position.y - hallway_height - 1});
    sfRectangleShape_setSize(data->line_bottom, (sfVector2f){
        sequence->width, 1});
    sfRectangleShape_setFillColor(data->line_bottom,
        sfColor_fromRGB(77, 77, 89));
    data->line_bottom2 = sfRectangleShape_create();
    sfRectangleShape_setPosition(data->line_bottom, (sfVector2f){
        sequence->position.x, sequence->position.y - hallway_height - 2});
    sfRectangleShape_setSize(data->line_bottom, (sfVector2f){
        sequence->width, 1});
    sfRectangleShape_setFillColor(data->line_bottom,
        sfColor_fromRGB(255, 255, 255));
    result.rect = sfRectangleShape_getGlobalBounds(data->hallway_top);
    return (result);
}
