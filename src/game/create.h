/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Declares game_create
*/

#pragma once

#include "../game.h"
#include "../parse_argv.h"
#include <stdbool.h>

bool game_create(struct game *self, const struct arguments *args);
