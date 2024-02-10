#pragma once

#include <stdbool.h>
#include <stdint.h>

struct vector2
{
    int16_t x;
    int16_t y;
};

struct vector2 vector2_subtract(struct vector2 vec1, struct vector2 vec2);
bool vector2_compare(struct vector2 vec1, struct vector2 vec2);