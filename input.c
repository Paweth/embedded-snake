#include "input.h"

#include "hardware/gpio.h"
#include "pico/types.h"
#include "stdio.h"

#include "snake.h"
#include "debug.h"

void check_input()
{
    int joystick_up_state = !gpio_get(JOYSTICK_UP_PIN);
    int joystick_down_state = !gpio_get(JOYSTICK_DOWN_PIN);
    int joystick_right_state = !gpio_get(JOYSTICK_RIGHT_PIN);
    int joystick_left_state = !gpio_get(JOYSTICK_LEFT_PIN);
    //log("%u %u %u %u", joystick_up_state, joystick_down_state, joystick_right_state, joystick_left_state);
    if(joystick_up_state)
        snake->input_direction = DIRECTION_UP;
    if(joystick_down_state) 
        snake->input_direction = DIRECTION_DOWN;
    if(joystick_right_state) 
        snake->input_direction = DIRECTION_RIGHT;
    if(joystick_left_state) 
        snake->input_direction = DIRECTION_LEFT;
    // if (snake->input_direction != DIRECTION_NONE)
    // {
    //     snake->input_direction = direction;
    // }
 
}