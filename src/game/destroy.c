/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_destroy
*/

#include "destroy.h"
#include "sound_with_buffer.h"
#include "my/my_string.h"
#include <SFML/Audio/Music.h>
#include <SFML/Audio/Sound.h>
#include <SFML/Audio/SoundBuffer.h>
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/View.h>
#include <stdlib.h>

static void destroy_sound_with_buffer(struct sound_with_buffer *sound)
{
    sfSound_destroy(sound->sf_sound);
    sfSoundBuffer_destroy(sound->buffer);
}

static void game_destroy_state(struct game_state *self)
{
    sfMusic_destroy(self->music);
    game_object_vector_destroy(&self->play.objects);
    sfText_destroy(self->play.jump_to_retry_text);
    sfRectangleShape_destroy(self->play.gameover_bottom_rect);
    sfRectangleShape_destroy(self->play.gameover_text_rect);
    sfText_destroy(self->play.gameover_text);
    sfSprite_destroy(self->play.gameover);
    sfSprite_destroy(self->play.player.sprite);
    sfSprite_destroy(self->play.midground);
    sfSprite_destroy(self->play.background);
    sfView_destroy(self->play.midground_view);
    sfView_destroy(self->play.background_view);
    sfView_destroy(self->play.distance_text_view);
    sfSprite_destroy(self->title.title_background);
    sfSprite_destroy(self->title.title_text_sprite);
    sfText_destroy(self->title.press_to_start_text);
    sfText_destroy(self->title.proud_to_present_text);
    sfText_destroy(self->play.distance_text);
    sfView_destroy(self->camera);
}

static void game_destroy_resources(struct game_resources *self)
{
    destroy_sound_with_buffer(&self->sounds.wall);
    destroy_sound_with_buffer(&self->sounds.foot4);
    destroy_sound_with_buffer(&self->sounds.foot3);
    destroy_sound_with_buffer(&self->sounds.foot2);
    destroy_sound_with_buffer(&self->sounds.foot1);
    destroy_sound_with_buffer(&self->sounds.jump3);
    destroy_sound_with_buffer(&self->sounds.jump2);
    destroy_sound_with_buffer(&self->sounds.jump1);
    sfTexture_destroy(self->gameover);
    sfTexture_destroy(self->midground);
    sfTexture_destroy(self->background);
    sfTexture_destroy(self->player);
    sfTexture_destroy(self->title_text);
    sfTexture_destroy(self->title_background);
    sfFont_destroy(self->nokia_font);
}

void game_destroy(struct game *self)
{
    my_string_free(self->map);
    game_destroy_state(&self->state);
    game_destroy_resources(&self->resources);
    sfRenderWindow_destroy(self->window);
}
