/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Declares game_handle_key
*/

#pragma once

#include <SFML/Window/Keyboard.h>

struct game;

void game_handle_key(struct game *self, sfKeyCode key_code);
