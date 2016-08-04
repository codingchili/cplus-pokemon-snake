//
// Created by chili on 2016-08-04.
//

#include <afxres.h>
#include "Input.h"
#include "Game.h"

const int KEYBOARD_NAVIGATION[] = {VK_UP, VK_LEFT, VK_DOWN, VK_RIGHT};
const int DIRECTION[] = {NORTH, WEST, SOUTH, EAST};
const int DIRECTION_COUNT = 4;

int Input::GetDirection() {
    for (int i = 0; i < DIRECTION_COUNT; i++) {
        if (GetAsyncKeyState(KEYBOARD_NAVIGATION[i]))
            return DIRECTION[i];
    }

    return -1;
}

bool Input::GetSelect() {
    return (GetAsyncKeyState(VK_RETURN) & 0x01 || GetAsyncKeyState(VK_SPACE) & 0x01);
}

