#include "Graphics.h"
#include "Resources.h"

Resources::~Resources() {
    for (int i = 0; i < FILE_COUNT; i++) {
        FreeBitmap(*bitmaps[i]);
    }
}

bool Resources::Load() {

    bool loaded = true;

    for (int i = 0; i < FILE_COUNT && loaded; i++) {
        loaded = LoadBitmapFromFile(FILES[i], *bitmaps[i]);
    }

    return loaded;
}
