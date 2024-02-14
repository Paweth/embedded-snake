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

void draw_text_f24(char * text, int position_x, int position_y)
{
    Paint_DrawString_EN(position_x, position_y, text, &Font24, BLACK, WHITE);
}
