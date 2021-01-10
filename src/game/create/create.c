/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_create
*/

#include "../create.h"
#include "internal.h"
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Texture.h>

static bool game_create_resources(struct game_resources *self)
{
    if (!game_create_font(&self->nokia_font, "assets/nokia.ttf") ||
        !game_create_texture(&self->title_background,
            "assets/title_background.png") ||
        !game_create_texture(&self->title_text, "assets/title_text.png") ||
        !game_create_texture(&self->background, "assets/background.png") ||
        !game_create_texture(&self->midground, "assets/midground.png") ||
        !game_create_texture(&self->gameover, "assets/gameover.png") ||
        !game_create_texture(&self->player, "assets/player.png") ||
        !game_create_sound(&self->sounds.jump1, "assets/jump1.wav") ||
        !game_create_sound(&self->sounds.jump2, "assets/jump2.wav") ||
        !game_create_sound(&self->sounds.jump3, "assets/jump3.wav") ||
        !game_create_sound(&self->sounds.foot1, "assets/foot1.wav") ||
        !game_create_sound(&self->sounds.foot2, "assets/foot2.wav") ||
        !game_create_sound(&self->sounds.foot3, "assets/foot3.wav") ||
        !game_create_sound(&self->sounds.foot4, "assets/foot4.wav") ||
        !game_create_sound(&self->sounds.wall, "assets/wall.wav"))
        return (false);
    sfTexture_setRepeated(self->background, sfTrue);
    sfTexture_setRepeated(self->midground, sfTrue);
    return (true);
}

static bool game_create_state_title(struct game_state_title *self,
    const struct game *game)
{
    if (!game_create_text(&self->proud_to_present_text, game) ||
        !game_create_text(&self->press_to_start_text, game) ||
        !game_create_sprite(&self->title_text_sprite,
            game->resources.title_text) ||
        !game_create_sprite(&self->title_background,
            game->resources.title_background))
        return (false);
    sfText_setString(self->proud_to_present_text,
        "Gabriel Ravier is pround to present a CSFML port of");
    sfText_setPosition(self->proud_to_present_text, (sfVector2f){80, 10});
    sfText_setFillColor(self->proud_to_present_text,
        sfColor_fromRGB(134, 134, 150));
    sfText_setString(self->press_to_start_text,
        "Press X or C to start your daring escape.");
    sfText_setPosition(self->press_to_start_text, (sfVector2f){230, 305});
    sfSprite_setPosition(self->title_text_sprite, (sfVector2f){40, 30});
    return (true);
}

static bool game_create_state(struct game_state *self, const struct game *game)
{
    if (!game_create_view(&self->camera, game->window) ||
        !game_create_state_title(&self->title, game) ||
        !game_create_state_play(&self->play, game))
        return (false);
    self->music = NULL;
    return (true);
}

bool game_create(struct game *self, const struct arguments *args)
{
    return (game_create_window(&self->window, args) &&
        game_create_resources(&self->resources) &&
        game_create_state(&self->state, self) &&
        game_create_map(&self->map, args->map_filename));
}
