#include <iostream>
#include <Windows.h>
#include "Graphics.h"

using namespace std;

const char *TITLE = "PokeSnake - Gotta eat em' all.";
const int WIDTH = 524;
const int HEIGHT = 524;
char className[] = {"GameWindowClass"};


// todo snake.cpp - game logic, input.cpp - handle player input, render.cpp - render the snake

/**
 * Handles paint messages by redrawing the map, player and info.
 */
void HandlePaintMessage(HWND hwnd) {
    PAINTSTRUCT ps = {0};
    BeginPaint(hwnd, &ps);
    EndPaint(hwnd, &ps);
}

/**
 * Forwards window messages to handlers.
 */
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_PAINT:
            HandlePaintMessage(hwnd);
            break;
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void Render(HWND hwnd) {
    HDC hdc = GetDC(hwnd);

    Rectangle(hdc, 10, 10, 100, 100);

    ReleaseDC(hwnd, hdc);
}

void UpdateGame(HWND hwnd) {
    // todo -- async stuff --
    // todo process input
    // todo modify game fsm
    // todo Render

    Render(hwnd);
}

void InitializeGame(HWND hwnd) {
    InitializeGraphics(hwnd);
    // todo load resource
}

void ShutdownGame() {
    // todo unload resources
    ShutdownGraphics();
}

/**
 * Pops messages from the application event queue.
 */
void HandleMessages(HWND hwnd) {
    InitializeGame(hwnd);

    while(1) {
        MSG msg = {0};

        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                ShutdownGame();
                break;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            UpdateGame(hwnd);
        }
    }
}

/**
 * Centers the application window using form with and screen dimension.
 */
void CenterWindow(HWND hwnd) {
    RECT rect;
    GetWindowRect(hwnd, &rect);
    SetWindowPos(hwnd, 0, (GetSystemMetrics(SM_CXSCREEN) - rect.right) / 2,
                 (GetSystemMetrics(SM_CYSCREEN) - rect.bottom) / 2, WIDTH, HEIGHT, 0);

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    WNDCLASSEX window = {0};

    window.cbSize = sizeof(window);
    window.style = 0;
    window.lpfnWndProc = WinProc;
    window.hInstance = hInstance;
    window.hIcon = (HICON) LoadIcon(0, IDI_APPLICATION);
    window.hIconSm = 0;
    window.hCursor = (HCURSOR) LoadCursor(0, IDC_ARROW);
    window.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    window.lpszMenuName = 0;
    window.lpszClassName = className;

    RegisterClassEx(&window);

    HWND hwnd = CreateWindow(window.lpszClassName,
                             TITLE, WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_VISIBLE, 0, 0,
                             WIDTH,
                             HEIGHT,
                             0, 0, hInstance, 0);

    CenterWindow(hwnd);
    HandleMessages(hwnd);
    return (hwnd == 0) ? -1 : 0;
}