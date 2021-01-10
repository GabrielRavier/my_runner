/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_create
*/

#include "../create.h"
#include "internal.h"
#include "../object_vector.h"
#include <SFML/Audio/Sound.h>
#include <SFML/Audio/SoundBuffer.h>
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/RectangleShape.h>
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
    sfText_setCharacterSize(*text, 10);
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

static bool game_create_sound(struct sound_with_buffer *sound,
    const char *filename)
{
    sound->buffer = sfSoundBuffer_createFromFile(filename);
    if (sound->buffer == NULL)
        return (false);
    sound->sf_sound = sfSound_create();
    if (sound->sf_sound == NULL)
        return (false);
    sfSound_setBuffer(sound->sf_sound, sound->buffer);
    return (true);
}

static bool game_create_rectangle_shape(sfRectangleShape **rect)
{
    *rect = sfRectangleShape_create();
    return (*rect != NULL);
}

bool game_create(struct game *self, const struct arguments *args)
{
    if (!game_create_window(&self->window, args) ||
        !game_create_font(&self->resources.nokia_font, "assets/nokia.ttf") ||
        !game_create_texture(&self->resources.title_background,
            "assets/title_background.png") ||
        !game_create_texture(&self->resources.title_text,
            "assets/title_text.png") ||
        !game_create_texture(&self->resources.background,
            "assets/background.png") ||
        !game_create_texture(&self->resources.midground,
            "assets/midground.png") ||
        !game_create_texture(&self->resources.gameover,
            "assets/gameover.png") ||
        !game_create_texture(&self->resources.player, "assets/player.png") ||
        !game_create_sound(&self->resources.sounds.jump1,
            "assets/jump1.wav") ||
        !game_create_sound(&self->resources.sounds.jump2,
            "assets/jump2.wav") ||
        !game_create_sound(&self->resources.sounds.jump3,
            "assets/jump3.wav") ||
        !game_create_sound(&self->resources.sounds.foot1, "assets/foot1.wav") ||
        !game_create_sound(&self->resources.sounds.foot2, "assets/foot2.wav") ||
        !game_create_sound(&self->resources.sounds.foot3, "assets/foot3.wav") ||
        !game_create_sound(&self->resources.sounds.foot4, "assets/foot4.wav") ||
        !game_create_sound(&self->resources.sounds.wall, "assets/wall.wav") ||
        !game_create_view(&self->state.camera, self->window) ||
        !game_create_view(&self->state.play.midground_view, self->window) ||
        !game_create_view(&self->state.play.background_view, self->window) ||
        !game_create_view(&self->state.play.distance_text_view, self->window) ||
        !game_create_text(&self->state.title.proud_to_present_text, self) ||
        !game_create_text(&self->state.title.press_to_start_text, self) ||
        !game_create_text(&self->state.play.distance_text, self) ||
        !game_create_sprite(&self->state.title.title_text_sprite,
            self->resources.title_text) ||
        !game_create_sprite(&self->state.title.title_background,
            self->resources.title_background) ||
        !game_create_sprite(&self->state.play.background,
            self->resources.background) ||
        !game_create_sprite(&self->state.play.midground,
            self->resources.midground) ||
        !game_create_sprite(&self->state.play.gameover,
            self->resources.gameover) ||
        !game_create_sprite(&self->state.play.player.sprite,
            self->resources.player) ||
        !game_create_rectangle_shape(&self->state.play.gameover_text_rect) ||
        !game_create_text(&self->state.play.gameover_text, self) ||
        !game_create_text(&self->state.play.jump_to_retry_text, self))
        return (false);
    self->state.music = NULL;
    game_object_vector_construct(&self->state.play.objects);
    sfTexture_setRepeated(self->resources.background, sfTrue);
    sfTexture_setRepeated(self->resources.midground, sfTrue);
    sfView_setSize(self->state.play.background_view, (sfVector2f){1000.f, 1000.f});
    sfView_setSize(self->state.play.midground_view, (sfVector2f){500.f, 500.f});
    sfText_setString(self->state.title.proud_to_present_text,
        "Gabriel Ravier is pround to present a CSFML port of");;
    sfText_setPosition(self->state.title.proud_to_present_text,
        (sfVector2f){80, 10});
    sfText_setFillColor(self->state.title.proud_to_present_text,
        sfColor_fromRGB(134, 134, 150));
    sfText_setString(self->state.title.press_to_start_text,
        "Press X or C to start your daring escape.");
    sfText_setPosition(self->state.title.press_to_start_text,
        (sfVector2f){230, 305});
    sfSprite_setPosition(self->state.title.title_text_sprite,
        (sfVector2f){40, 30});
    sfSprite_setScale(self->state.play.background, (sfVector2f){3, 3});
    sfSprite_setScale(self->state.play.midground, (sfVector2f){3, 3});
    sfSprite_setPosition(self->state.play.gameover, (sfVector2f){50, 110});
    sfRectangleShape_setPosition(self->state.play.gameover_text_rect,
        (sfVector2f){0, 140});
    sfRectangleShape_setSize(self->state.play.gameover_text_rect, (sfVector2f){
        1000, 40});
    sfRectangleShape_setFillColor(self->state.play.gameover_text_rect,
        sfColor_fromRGB(53, 53, 61));
    self->state.play.gameover_bottom_rect =
        sfRectangleShape_copy(self->state.play.gameover_text_rect);
    sfRectangleShape_setPosition(self->state.play.gameover_bottom_rect,
        (sfVector2f){0, 302});
    sfText_setString(self->state.play.jump_to_retry_text,
        "Jump to retry your daring escape.");
    sfText_setPosition(self->state.play.jump_to_retry_text, (sfVector2f){
        275, 305});
    sfText_setFillColor(self->state.play.gameover_text,
        sfColor_fromRGB(255, 255, 255));
    sfText_setFillColor(self->state.play.distance_text,
        sfColor_fromRGB(255, 255, 255));
    return (true);
}
