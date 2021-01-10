/*
** EPITECH PROJECT, 2020
** myrunner
** File description:
** Defines object_vector methods
*/

#include "object_vector.h"
#include "object.h"
#include "my/macros.h"
#include "my/stdlib.h"
#include "my/assert.h"
#include <SFML/Graphics/Sprite.h>
#include <stddef.h>

// We allocate some extra bytes to reduce the amount of calls to realloc when
// frequently increasing the size of self
static const size_t EXTRA_ALLOCATED_SPACE = 16;

static void game_object_vector_guarantee_can_expand(
    struct game_object_vector *self, size_t size)
{
    size_t current_allocated_size = self->allocated_size;

    if (self->size + size >= current_allocated_size) {
        self->allocated_size = MY_MAX(self->size + size + 1 +
            EXTRA_ALLOCATED_SPACE, self->size * 2);
        self->array = (struct game_object *)my_realloc_size(self->array,
            self->allocated_size * sizeof(*self->array),
            current_allocated_size * sizeof(*self->array));
        MY_ASSERT(self->array != NULL);
    }
}

void game_object_vector_construct(struct game_object_vector *self)
{
    self->size = 0;
    self->allocated_size = 0;
    self->array = NULL;
    game_object_vector_guarantee_can_expand(self, 1);
}

void game_object_vector_destroy(struct game_object_vector *self)
{
    game_object_vector_clear(self);
    free(self->array);
}

void game_object_vector_clear(struct game_object_vector *self)
{
    struct game_object *i;

    GAME_OBJECT_VECTOR_FOR_EACH(self, i) {
        if (i->destroy != NULL)
            i->destroy(i);
        free(i->private_data);
    }
    self->size = 0;
}

size_t game_object_vector_push_back(struct game_object_vector *self,
    const struct game_object *object)
{
    game_object_vector_guarantee_can_expand(self, 1);
    self->array[self->size] = *object;
    ++self->size;
    return (self->size - 1);
}
