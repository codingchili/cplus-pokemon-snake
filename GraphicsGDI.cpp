#include "Graphics.h"
#include <Windows.h>
#include <vector>

using namespace std;

namespace {
    HWND window;
    int windowWidth;
    int windowHeight;

    HDC backbufferDC;
    HBITMAP backbufferBitmap;

    HDC bitmapDC;

    struct GDIBitmap {
        HBITMAP handle;
        int width;
        int height;

        GDIBitmap()
                : handle(0) {
        }
    };

    vector<GDIBitmap> bitmaps;
}

void InitializeGraphics(void *window) {
    ::window = (HWND) window;

    HDC hdc = GetDC(::window);
    backbufferDC = CreateCompatibleDC(hdc);

    RECT windowSize = {0};
    GetClientRect(::window, &windowSize);

    windowWidth = windowSize.right - windowSize.left;
    windowHeight = windowSize.bottom - windowSize.top;

    backbufferBitmap = CreateCompatibleBitmap(hdc, windowWidth, windowHeight);
    SelectObject(backbufferDC, backbufferBitmap);

    SetBkMode(backbufferDC, TRANSPARENT);

    bitmapDC = CreateCompatibleDC(hdc);
}

bool LoadBitmapFromFile(const char *filename, Bitmap &bitmap) {
    GDIBitmap gdi;
    gdi.handle = (HBITMAP) LoadImage(0, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (gdi.handle == 0) {
        return false;
    }

    BITMAP header;
    GetObject(gdi.handle, sizeof(header), &header);
    gdi.width = header.bmWidth;
    gdi.height = header.bmHeight;

    bitmaps.push_back(gdi);

    bitmap.index = bitmaps.size() - 1;
    return true;
}

void BeginGraphics() {
    RECT rectangle = {0, 0, windowWidth, windowHeight};
    FillRect(backbufferDC, &rectangle, (HBRUSH) COLOR_BACKGROUND);
}

void DrawBitmap(Bitmap bitmap, int x, int y) {
    GDIBitmap &gdi = bitmaps[bitmap.index];
    SelectObject(bitmapDC, gdi.handle);
    BitBlt(backbufferDC, x, y, gdi.width, gdi.height, bitmapDC, 0, 0, SRCCOPY);
}

void DrawingTextColor(int r, int g, int b) {
    SetTextColor(backbufferDC, RGB(r, g, b));
}

void DrawString(const char *text, int x, int y) {
    TextOut(backbufferDC, x, y, text, strlen(text));
}

void EndGraphics() {
    HDC windowDC = GetDC(::window);
    BitBlt(windowDC, 0, 0, windowWidth, windowHeight, backbufferDC, 0, 0, SRCCOPY);
    ReleaseDC(::window, windowDC);
}

void FreeBitmap(Bitmap bitmap) {
    if (bitmaps[bitmap.index].handle != 0) {
        DeleteObject(bitmaps[bitmap.index].handle);
        bitmaps[bitmap.index].handle = 0;
    }
}

void ShutdownGraphics() {
    DeleteDC(bitmapDC);

    DeleteObject(backbufferBitmap);
    DeleteDC(backbufferDC);
}
