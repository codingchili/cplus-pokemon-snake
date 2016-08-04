#ifndef GRAPHICS_HPP_
#define GRAPHICS_HPP_

#include <afxres.h>

struct Bitmap {
    int index;
};

void InitializeGraphics(void *hwnd);

bool LoadBitmapFromFile(const char *filename, Bitmap &bitmap);

void BeginGraphics();

void DrawBitmap(Bitmap bitmap, int x, int y);

void DrawingTextColor(int r, int g, int b);

void DrawString(const char *text, int x, int y);

void EndGraphics();

void FreeBitmap(Bitmap bitmap);

void ShutdownGraphics();

#endif
