#pragma once

#include <stdbool.h>
#include <stdint.h>

struct vector2
{
    int8_t x;
    int8_t y;
};

struct vector2 vector2_substract();
bool vector2_compare(struct vector2 vec1, struct vector2 vec2);