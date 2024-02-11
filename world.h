#pragma once

#include <stdint.h>
#include <stdlib.h>
#include "pico/types.h"

#include "snake.h"
#include "vector2.h"

#define RESOLUTION_X 240
#define RESOLUTION_Y 240

#define CELL_SIZE 8 //how many pixels per cell

#define CELLS_AMOUNT RESOLUTION_X/CELL_SIZE

enum CELL_TYPE
{
    CELL_EMPTY = 1,//0b001
    CELL_OBSTACLE = 2,//0b010
    CELL_FOOD = 4//0b100
};

struct cell
{
    struct vector2 position;
    enum CELL_TYPE cell_type;
};

extern struct cell cells[CELLS_AMOUNT][CELLS_AMOUNT];

int generate_random_int (int min_value, int max_value);
struct vector2 get_cell_pixels(struct cell * cell);
struct cell * get_cell(int x, int y);
struct cell * get_random_cell();
void place_food();
void world_initialize();