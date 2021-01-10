/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Declares game_resources
*/

#pragma once

#include "sounds.h"
#include <SFML/Graphics/Types.h>

struct game_resources {
    sfFont *nokia_font;
    sfTexture *title_text;
    sfTexture *title_background;
    sfTexture *player;
    sfTexture *background;
    sfTexture *midground;
    sfTexture *gameover;
    struct game_sounds sounds;
};
