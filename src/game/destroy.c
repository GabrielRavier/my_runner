/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines game_destroy
*/

#include "destroy.h"
#include <SFML/Audio/Music.h>
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/View.h>

void game_destroy(struct game *self)
{
    sfMusic_destroy(self->state.music);
    game_object_vector_destroy(&self->state.play.objects);
    sfSprite_destroy(self->state.menu.title_background);
    sfSprite_destroy(self->state.menu.title_text_sprite);
    sfText_destroy(self->state.menu.press_to_start_text);
    sfText_destroy(self->state.menu.proud_to_present_text);
    sfView_destroy(self->state.camera);
    sfFont_destroy(self->resources.nokia_font);
    sfTexture_destroy(self->resources.player);
    sfTexture_destroy(self->resources.title_text);
    sfTexture_destroy(self->resources.title_background);
    sfRenderWindow_destroy(self->window);
}
