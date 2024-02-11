#pragma once

#include "pico/types.h"

enum GPIO_PINS
{
    JOYSTICK_UP_PIN = 2,
    JOYSTICK_DOWN_PIN = 18,
    JOYSTICK_RIGHT_PIN = 20,
    JOYSTICK_LEFT_PIN = 16,
};

void check_input();