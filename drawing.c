#include "GUI_Paint.h"
#include "LCD_1in3.h"
#include "snake.h"
#include "world.h"
#include "drawing.h"
#include <stdint.h>
#include "debug.h"

void set_cell_color(struct cell * cell, int color)
{
    struct vector2 start_pixel_position = get_cell_pixels(cell);
    // log("set_cell_color: after get_cell_pixels");
    Paint_DrawPoint(start_pixel_position.x, start_pixel_position.y, color, CELL_SIZE,  DOT_FILL_RIGHTUP);
    // for(uint8_t j = 0; j < CELL_SIZE; j++)//rows
    // {
    //     for(uint8_t i = 0; i < CELL_SIZE; i++)//next column pixels
    //     {
    //         uint8_t x_pixel = start_pixel_position.x + i;
    //         uint8_t y_pixel = start_pixel_position.y + j; 
    //         Paint_DrawPoint(x_pixel, y_pixel, color, DOT_PIXEL_1X1,  DOT_FILL_RIGHTUP);
    //         // log("set_cell_color: iteration %d", i + j*CELL_SIZE);
    //     }
    // }
    
}

void initial_draw_snake(struct snake_body * body)
{
    struct snake_segment * it = body->tip;
    while(it != NULL)
    {
        set_cell_color(it->cell, BLACK);
        it = it->next;
    }
}

void redraw_snake(
            struct snake_segment * old_tip,
            struct snake_segment * new_head)
{
    //only draw new head cell and clear old tip cell
    set_cell_color(new_head->cell, 1);
    set_cell_color(old_tip->cell, 0);
}
