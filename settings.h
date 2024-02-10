#pragma once

#include "world.h"

extern struct settings settings;

struct settings
{
    bool has_border;
    uint speed;
    int snake_initial_length;
    enum DIRECTION snake_initial_direction;
};
