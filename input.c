#include "input.h"
#include "pico/types.h"
#include "snake.h"
#include "stdio.h"

void on_joystick_up(uint gpio, uint32_t event_mask)
{
    if(gpio == JOYSTICK_UP_PIN)
        snake->current_direction = DIRECTION_TOP;
}

void on_joystick_down(uint gpio, uint32_t event_mask)
{
    if(gpio == JOYSTICK_DOWN_PIN)
        snake->current_direction = DIRECTION_DOWN;
}

void on_joystick_right(uint gpio, uint32_t event_mask)
{
    if(gpio == JOYSTICK_RIGHT_PIN)
        snake->current_direction = DIRECTION_RIGHT;
}

void on_joystick_left(uint gpio, uint32_t event_mask)
{
    if(gpio == JOYSTICK_LEFT_PIN)
        snake->current_direction = DIRECTION_LEFT;
}