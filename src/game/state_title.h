/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Declares game_state_title
*/

#pragma once

#include <SFML/Graphics/Types.h>

struct game_state_title {
    sfSprite *title_background;
    sfSprite *title_text_sprite;
    sfText *proud_to_present_text;
    sfText *press_to_start_text;
};
