/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_destroy
*/

#include "destroy.h"
#include "sound_with_buffer.h"
#include <SFML/Audio/Music.h>
#include <SFML/Audio/Sound.h>
#include <SFML/Audio/SoundBuffer.h>
#include <SFML/Graphics/Font.h>
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

void game_destroy(struct game *self)
{
    sfMusic_destroy(self->state.music);
    game_object_vector_destroy(&self->state.play.objects);
    free(self->state.play.player.private_data);
    sfSprite_destroy(self->state.play.player.sprite);
    sfSprite_destroy(self->state.play.midground);
    sfSprite_destroy(self->state.play.background);
    sfView_destroy(self->state.play.midground_view);
    sfView_destroy(self->state.play.background_view);
    sfSprite_destroy(self->state.title.title_background);
    sfSprite_destroy(self->state.title.title_text_sprite);
    sfText_destroy(self->state.title.press_to_start_text);
    sfText_destroy(self->state.title.proud_to_present_text);
    sfView_destroy(self->state.camera);
    destroy_sound_with_buffer(&self->resources.sounds.wall);
    destroy_sound_with_buffer(&self->resources.sounds.footc4);
    destroy_sound_with_buffer(&self->resources.sounds.footc3);
    destroy_sound_with_buffer(&self->resources.sounds.footc2);
    destroy_sound_with_buffer(&self->resources.sounds.footc1);
    destroy_sound_with_buffer(&self->resources.sounds.foot4);
    destroy_sound_with_buffer(&self->resources.sounds.foot3);
    destroy_sound_with_buffer(&self->resources.sounds.foot2);
    destroy_sound_with_buffer(&self->resources.sounds.foot1);
    destroy_sound_with_buffer(&self->resources.sounds.jump3);
    destroy_sound_with_buffer(&self->resources.sounds.jump2);
    destroy_sound_with_buffer(&self->resources.sounds.jump1);
    sfTexture_destroy(self->resources.midground);
    sfTexture_destroy(self->resources.background);
    sfTexture_destroy(self->resources.player);
    sfTexture_destroy(self->resources.title_text);
    sfTexture_destroy(self->resources.title_background);
    sfFont_destroy(self->resources.nokia_font);
    sfRenderWindow_destroy(self->window);
}
