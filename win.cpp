#include <windows.h>
#include <gl\glew.h>
#include "win.h"
#include "msg.h"
#include "engine.h"

WinEngine::WinEngine( void ) {
    LARGE_INTEGER tmp;

    init();
    QueryPerformanceFrequency(&tmp);
    freq = tmp.QuadPart;
    //Log("High performance counter frequency: %lluHz\n", freq);
}

WinEngine::~WinEngine( void ) {
}

int WinEngine::msgBox(char *msg) {
    MessageBox(NULL, msg, "Alert", MB_OK);
    return 0;
}

void WinEngine::UpdateTimer() {
    LARGE_INTEGER tmp;
    UINT64 temp_time;

    QueryPerformanceCounter(&tmp);
    temp_time = tmp.QuadPart;
    time = (double)(temp_time - timer) / freq;
    timer = temp_time;
}

void WinEngine::KeyDown(WPARAM wParam, LPARAM lParam) {
    if (wParam == 0x71)
        ToggleFrame();
    else
        Log("Button 0x%02X (%c) pressed.\n", wParam, wParam);
}

void InitPixelFormat(HDC hDC);

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_KEYDOWN:
        Engine->KeyDown(wParam, lParam);
        break;
    case WM_KEYUP:
        break;
    case WM_CREATE:
        Engine = new WinEngine;

        mainDC = GetDC(hwnd);
        InitPixelFormat(mainDC);

        mainGLRC = wglCreateContext(mainDC);
        if (!mainGLRC) {
            DestroyWindow(hwnd);
            break;
        }

        if (!wglMakeCurrent(mainDC, mainGLRC)) {
            DestroyWindow(hwnd);
            break;
        }

        if (glewInit()) {
            Log("FATAL - glewInit: Failed.\n");
            Engine->msgBox("A fatal error occured, check your log file.");
            DestroyWindow(hwnd);
            return 0;
        }

        Engine->initRender();
        Engine->SetViewport(((CREATESTRUCT*)lParam)->cx,((CREATESTRUCT*)lParam)->cy);
        break;

    case WM_SIZE:
        Engine->SetViewport(lParam & 0x0000FFFF, lParam >> 16);
        SwapBuffers(mainDC);
        break;

    case WM_PAINT:
        if (Engine) {
            Engine->DrawFrame();
        }
        SwapBuffers(mainDC);
        //ValidateRect(mainWindow, NULL);
        break;

    case WM_DESTROY:
        delete Engine;
        wglMakeCurrent(mainDC, NULL);
        wglDeleteContext(mainGLRC);
        ReleaseDC(hwnd, mainDC);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
    WNDCLASS mainClass =
    {
        CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
        MainWndProc,
        0, 0,
        hInst,
        LoadIcon(NULL, IDI_APPLICATION),
        LoadCursor(NULL, IDC_ARROW),
        (HBRUSH)(COLOR_BACKGROUND+1),
        NULL, MAINCLASSNAME
    };

    if (!RegisterClass(&mainClass)) {
        MessageBox(NULL, "Failed to register mainClass.", "Error", MB_OK);
        return 0;
    }

    mainWindow = CreateWindow(MAINCLASSNAME, "Legendary Alpha", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInst, NULL);
    ShowWindow(mainWindow, iCmdShow);
    UpdateWindow(mainWindow);
    mainDC = GetDC(mainWindow);

    while (GetMessage(&mainMsg, NULL, 0, 0)) {
        TranslateMessage(&mainMsg);
        DispatchMessage(&mainMsg);
    }

    return 0;
}

void InitPixelFormat(HDC hDC)
{
    static PIXELFORMATDESCRIPTOR pfd =
        {	sizeof(PIXELFORMATDESCRIPTOR),
          1,
          PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
          PFD_TYPE_RGBA,
          32,															//Colour depth
          0, 0, 0, 0, 0, 0,
          0, 0, 0,
          0, 0, 0, 0,
          24, 8, 0,													//Bits of depth- and stencil buffers, 0 AUX buffers
          PFD_MAIN_PLANE,												//Deprecated, but doesn't hurt
          0, 0, 0, 0
        };

    int PixelFormat = ChoosePixelFormat(hDC, &pfd);
    if (!SetPixelFormat(hDC, PixelFormat, &pfd))
        Log("SetPixelFormat failed. Last error code: %X\n", GetLastError());
    //Log("ChoosePixelFormat() chosen pixel format: %X\n", PixelFormat);
    return;
}
