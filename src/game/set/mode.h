/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Declares game_set_mode
*/

#pragma once

#include "../mode.h"

struct game;

void game_set_mode(struct game *self, enum game_mode mode);
