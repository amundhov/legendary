#include <windows.h>
#include "engine.h"

#ifndef __win_h_
#define __win_h_

#define MAINCLASSNAME "Engine"

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class WinEngine : public Engine {
public:
    WinEngine( void );
    virtual ~WinEngine( void );

    virtual int msgBox(char *msg);
    void KeyDown(WPARAM wParam, LPARAM lParam);
    void UpdateTimer();

private:
    UINT64		freq;
    UINT64		timer;
};

WinEngine  *Engine;
HWND		mainWindow;
MSG			mainMsg;
HDC			mainDC;
HGLRC		mainGLRC;

#endif
