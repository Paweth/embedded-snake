#pragma once

#include "pico/types.h"

enum GPIO_PINS
{
    JOYSTICK_UP_PIN = 2,
    JOYSTICK_DOWN_PIN = 18,
    JOYSTICK_RIGHT_PIN = 20,
    JOYSTICK_LEFT_PIN = 16,
    USER_KEY_A_PIN = 15,
    USER_KEY_B_PIN = 17,
    USER_KEY_X_PIN = 19,
    USER_KEY_Y_PIN = 21
};

void check_input(uint gpio, uint32_t event_mask);