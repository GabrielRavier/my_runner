/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** Defines game_is_jumping
*/

#include "is_jumping.h"
#include <SFML/Window/Keyboard.h>

bool game_is_jumping(void)
{
    return sfKeyboard_isKeyPressed(sfKeyX) || sfKeyboard_isKeyPressed(sfKeyC);
}
