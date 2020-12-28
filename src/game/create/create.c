/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_create
*/

#include "../create.h"
#include "internal.h"
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/View.h>

static bool game_create_font(sfFont **font, const char *filename)
{
    *font = sfFont_createFromFile(filename);
    return (*font != NULL);
}

static bool game_create_view(sfView **view, sfRenderWindow *window)
{
    *view = sfView_copy(sfRenderWindow_getDefaultView(window));
    return (*view != NULL);
}

static bool game_create_text(sfText **text, struct game *self)
{
    *text = sfText_create();
    if (*text == NULL)
        return (false);
    sfText_setFont(*text, self->resources.nokia_font);
    return (true);
}

static bool game_create_texture(sfTexture **texture, const char *filename)
{
    *texture = sfTexture_createFromFile(filename, NULL);
    return (*texture != NULL);
}

static bool game_create_sprite(sfSprite **sprite, sfTexture *texture)
{
    *sprite = sfSprite_create();
    if (*sprite == NULL)
        return (false);
    sfSprite_setTexture(*sprite, texture, sfTrue);
    return (true);
}

bool game_create(struct game *self, const struct arguments *args)
{
    if (!game_create_window(&self->window, args) ||
        !game_create_font(&self->resources.nokia_font, "assets/nokia.ttf") ||
        !game_create_texture(&self->resources.title_background,
            "assets/title_background.png") ||
        !game_create_texture(&self->resources.title_text,
            "assets/title_text.png") ||
        !game_create_view(&self->state.camera, self->window) ||
        !game_create_text(&self->state.menu.proud_to_present_text, self) ||
        !game_create_text(&self->state.menu.press_to_start_text, self) ||
        !game_create_sprite(&self->state.menu.title_text_sprite,
            self->resources.title_text) ||
        !game_create_sprite(&self->state.menu.title_background,
            self->resources.title_background))
        return (false);
    sfText_setString(self->state.menu.proud_to_present_text,
        "Gabriel Ravier is pround to present a CSFML port of");
    sfText_setCharacterSize(self->state.menu.proud_to_present_text, 10);
    sfText_setPosition(self->state.menu.proud_to_present_text,
        (sfVector2f){80, 10});
    sfText_setFillColor(self->state.menu.proud_to_present_text,
        sfColor_fromRGB(134, 134, 150));
    sfText_setString(self->state.menu.press_to_start_text,
        "Press X or C to start your daring escape.");
    sfText_setCharacterSize(self->state.menu.press_to_start_text, 10);
    sfText_setPosition(self->state.menu.press_to_start_text,
        (sfVector2f){230, 305});
    sfSprite_setPosition(self->state.menu.title_text_sprite,
        (sfVector2f){40, 30});
    return (true);
}
