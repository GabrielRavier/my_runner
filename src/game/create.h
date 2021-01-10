/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Declares game_create
*/

#pragma once

#include <stdbool.h>

struct game;
struct arguments;

bool game_create(struct game *self, const struct arguments *args);
