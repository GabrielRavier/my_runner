/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Defines game_object_building_rect
*/

#include "building_bottom.h"
#include "my/assert.h"
#include "../state_play_sequence.h"
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/Image.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <stdlib.h>

struct building_bottom_data {
    sfRectangleShape *top_line;
    sfRectangleShape *line2;
    sfRectangleShape *line3;
    sfRectangleShape *line4;
    sfRectangleShape *line5;
    sfRectangleShape *line6;
    sfRectangleShape *line7;
    sfRectangleShape *line89;
    sfRectangleShape *rect_other_lines;
};

static void do_draw(struct game_object *self, sfRenderWindow *window)
{
    __auto_type data = (struct building_bottom_data *)self->private_data;

    sfRenderWindow_drawRectangleShape(window, data->top_line, NULL);
    sfRenderWindow_drawRectangleShape(window, data->line2, NULL);
    sfRenderWindow_drawRectangleShape(window, data->line3, NULL);
    sfRenderWindow_drawRectangleShape(window, data->line4, NULL);
    sfRenderWindow_drawRectangleShape(window, data->line5, NULL);
    sfRenderWindow_drawRectangleShape(window, data->line6, NULL);
    sfRenderWindow_drawRectangleShape(window, data->line7, NULL);
    sfRenderWindow_drawRectangleShape(window, data->line89, NULL);
    sfRenderWindow_drawRectangleShape(window, data->rect_other_lines, NULL);
}

static void do_destroy(struct game_object *self)
{
    __auto_type data = (struct building_bottom_data *)self->private_data;

    sfRectangleShape_destroy(data->rect_other_lines);
    sfRectangleShape_destroy(data->line89);
    sfRectangleShape_destroy(data->line7);
    sfRectangleShape_destroy(data->line6);
    sfRectangleShape_destroy(data->line5);
    sfRectangleShape_destroy(data->line4);
    sfRectangleShape_destroy(data->line3);
    sfRectangleShape_destroy(data->line2);
    sfRectangleShape_destroy(data->top_line);
}

static sfRectangleShape *make_line_below(const sfRectangleShape *line,
    sfUint8 r, sfUint8 g, sfUint8 b)
{
    sfRectangleShape *result = sfRectangleShape_copy(line);
    sfVector2f position = sfRectangleShape_getPosition(line);

    ++position.y;
    sfRectangleShape_setPosition(result, position);
    sfRectangleShape_setFillColor(result, sfColor_fromRGB(r, g, b));
    return (result);
}

static void make_lines(struct building_bottom_data *data,
    struct game_state_play_sequence *sequence)
{
    data->top_line = sfRectangleShape_create();
    sfRectangleShape_setPosition(data->top_line, sequence->position);
    sfRectangleShape_setSize(data->top_line, (sfVector2f){sequence->width, 1});
    sfRectangleShape_setFillColor(data->top_line, sfColor_fromRGB(77, 77, 89));
    data->line2 = make_line_below(data->top_line, 255, 255, 255);
    data->line3 = make_line_below(data->line2, 100, 106, 125);
    data->line4 = make_line_below(data->line3, 134, 134, 150);
    data->line5 = make_line_below(data->line4, 176, 176, 191);
    data->line6 = make_line_below(data->line5, 134, 134, 150);
    data->line7 = make_line_below(data->line6, 176, 176, 191);
    data->line89 = make_line_below(data->line7, 134, 134, 150);
    sfRectangleShape_setSize(data->line89, (sfVector2f){
        sfRectangleShape_getSize(data->line89).x, 2});
    data->rect_other_lines = make_line_below(data->line89, 176, 176, 191);
    sfRectangleShape_setSize(data->rect_other_lines, (sfVector2f){
        sfRectangleShape_getSize(data->rect_other_lines).x, 10000});
}

struct game_object game_object_create_building_bottom(
    struct game_state_play_sequence *sequence)
{
    struct game_object result;
    __auto_type data = (struct building_bottom_data *)malloc(
        sizeof(struct building_bottom_data));

    MY_ASSERT(data != NULL);
    result.draw = do_draw;
    result.destroy = do_destroy;
    result.update = NULL;
    make_lines(data, sequence);
    result.rect = (sfFloatRect){sequence->position.x, sequence->position.y,
        sequence->width, sequence->height};
    result.private_data = data;
    return (result);
}
