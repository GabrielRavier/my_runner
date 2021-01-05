/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Declares object_vector
*/

#pragma once

#include "object.h"
#include <stddef.h>

struct game_object_vector {
    struct game_object *array;
    size_t size;
    size_t allocated_size;
};

void game_object_vector_construct(struct game_object_vector *self);
void game_object_vector_destroy(struct game_object_vector *self);
void game_object_vector_clear(struct game_object_vector *self);
size_t game_object_vector_push_back(struct game_object_vector *self,
    const struct game_object *object);

#define GAME_OBJECT_VECTOR_FOR_EACH(vector, i) for ((i) = (vector)->array; (i) \
    != (vector)->array + (vector)->size; ++(i))
