#pragma once

#include <stdint.h>
#include <stdlib.h>
#include "pico/types.h"


#define RESOLUTION_X 240
#define RESOLUTION_Y 240

#define CELL_SIZE 4 //how many pixels per cell

#define CELLS_AMOUNT RESOLUTION_X/CELL_SIZE


enum CELL_TYPE
{
    CELL_EMPTY,
    CELL_OBSTACLE,
    CELL_FOOD
};

struct vector2
{
    uint8_t x;
    uint8_t y;
};

struct cell
{
    struct vector2 position;
    enum CELL_TYPE cell_type;
};


struct settings
{
    bool has_border;
    uint speed;
};

extern struct cell cells[CELLS_AMOUNT][CELLS_AMOUNT];
extern struct settings settings;

int generate_random_int (int min_value, int max_value);
struct vector2 get_cell_pixels(struct cell * cell);
struct cell * get_cell(int x, int y);
void world_initialize();