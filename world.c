#include "world.h"

#include <stdlib.h>
#include "pico/types.h"
#include "pico/malloc.h"
#include "GUI_Paint.h"
#include "LCD_1in3.h"

#include "color_palette.h"
#include "drawing.h"
#include "debug.h"
#include "settings.h"
/*
cell representation:

    x x x x x x x x
    0 1 2 3 4 5 6 7
y 0|- - - - - - - -
y 1|- - - - - - - -
y 2|- - - P - - - -
y 3|- - - - - - - -
y 4|- - - - - - - -

P = cell[2, 3]

*/

int generate_random_int (int min_value, int max_value)
{
    // int random_value = (int)((1.0 + max_value) * rand() / ( RAND_MAX + 1.0 ) );// 0 to max_value
    int random_value = (rand() % (max_value - min_value + 1)) + min_value;
    return random_value;
}

struct vector2 get_cell_pixels(struct cell * cell)
{
    uint8_t start_pixel_x = cell->position.x * CELL_SIZE;
    uint8_t start_pixel_y = cell->position.y * CELL_SIZE;
    struct vector2 start_pixels = {start_pixel_x, start_pixel_y};
    return start_pixels;
}

struct cell * get_cell(int x, int y)
{
    return &cells[y][x];
}

//determine_neighbour_cell(reference_cell, direction)

//init_cell
void world_initialize()//world type: closed or open
{
    for(int j = 0; j < CELLS_AMOUNT; j++)// |y
    {
        for(int i = 0; i < CELLS_AMOUNT; i++)// --->x
        {
            cells[j][i].position.x = i;
            cells[j][i].position.y = j;
            cells[j][i].cell_type = CELL_EMPTY;
            set_cell_color(&cells[j][i], BACKGROUND_COLOR);
            if(settings.has_border)
            {
                if(j == 0 || j == CELLS_AMOUNT - 1 || i == 0 || i == CELLS_AMOUNT - 1)
                {
                    cells[j][i].cell_type = CELL_OBSTACLE;
                    set_cell_color(&cells[j][i], BORDER_COLOR);//draw map border
                    // log("setting pixel\n");
                }
            }
        }
    }
    LCD_1IN3_Display(BlackImage);
}
