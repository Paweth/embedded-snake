#include "input.h"

#include "hardware/gpio.h"
#include "pico/types.h"
#include "stdio.h"

#include "snake.h"
#include "debug.h"

void check_input(uint gpio, uint32_t event_mask)
{
    switch(gpio)
    {
        case JOYSTICK_UP_PIN:
            snake->input_direction = DIRECTION_UP;
            break;
        case JOYSTICK_RIGHT_PIN:
            snake->input_direction = DIRECTION_RIGHT;
            break;
        case JOYSTICK_DOWN_PIN:
            snake->input_direction = DIRECTION_DOWN;
            break;
        case JOYSTICK_LEFT_PIN:
            snake->input_direction = DIRECTION_LEFT; 
            break;
    }
}