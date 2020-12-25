/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Declares internal game_create methods
*/

#pragma once

#include "../../parse_argv.h"
#include <SFML/Graphics/Types.h>
#include <stdbool.h>

bool game_create_window(sfRenderWindow **window, const struct arguments *args);
