//
// Created by chili on 2016-08-03.
//

#ifndef CPLUS_POKESNAKE_RESOURCES_H
#define CPLUS_POKESNAKE_RESOURCES_H

#include "Graphics.h"

class Resources {
public:
    Bitmap background;
    Bitmap head;
    Bitmap wall;

    ~Resources();

    bool load();
};

#endif
