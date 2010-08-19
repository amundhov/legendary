#include <X11/keysymdef.h>
#include "linux.h"
#include "sound.h"
#include "msg.h"

Display                 *display;
Window                  root;
GLint                   att[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
XVisualInfo             *vi;
Colormap                cmap;
XSetWindowAttributes    swa;
Window                  win;
GLXContext              glc;
XWindowAttributes       gwa;
XEvent                  xev;

LinuxEngine				*engine;

LinuxEngine::LinuxEngine() :
        m_elapsed(0),
        m_sound(new Sound("default"))
{
    init();
    Log("LINUX ENGINE INITIALIZED!\n");
}

LinuxEngine::~LinuxEngine() {
    delete m_sound;
}

int LinuxEngine::msgBox(char *msg) {
    printf("ATTENTION: %s\n", msg);
    //Forward to Log
    Log(msg);
    return 0;
}

void LinuxEngine::updateTimer() {
    struct timeval now;
    gettimeofday(&now, NULL);
    suseconds_t cur = (now.tv_sec * 1000000) + now.tv_usec;
    m_elapsed = cur - m_lastTick;
    m_lastTick = cur;
}

int main() {
    engine = new LinuxEngine;
    glewInit();
    if (!glewIsSupported("GL_VERSION_2_0")) {
        printf("FATAL! Needs OpenGL 2.0 or later!\n");
//        return 255; glew be broken
    }
    display = XOpenDisplay(NULL);
    if (!display) {
        Log("Couldn't open display, terminating.\n");
        delete engine;
        return 1;
    }

    root = DefaultRootWindow(display);
    vi = glXChooseVisual(display, 0, att);
    if (!vi) {
        delete engine;
        return 1;
    }

    cmap = XCreateColormap(display, root, vi->visual, AllocNone);
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask | ResizeRedirectMask;
    win = XCreateWindow(display, root, 0, 0, 1024, 600, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);

    XMapWindow(display, win);
    XStoreName(display, win, "Legendary Alpha");
    glc = glXCreateContext(display, vi, NULL, GL_TRUE);
    glXMakeCurrent(display, win, glc);


    if (glewInit()) {
        Log("FATAL - glewInit failed.\n");
        return 0;
    }

    engine->initRender();
    engine->SetViewport(1024,600);

    while (1) {
        engine->DrawFrame();
        glXSwapBuffers(display, win);

        if (!XPending(display))
            continue;

        XNextEvent(display, &xev);

            XResizeRequestEvent *rev = reinterpret_cast<XResizeRequestEvent*>(&xev);
        switch (xev.type) {
        case Expose:
            XGetWindowAttributes(display, win, &gwa);
            engine->DrawFrame();
            glXSwapBuffers(display, win);
            break;

        case KeyPress:
            switch (XLookupKeysym(&xev.xkey, 0)) {
            case XK_space:
                glXMakeCurrent(display, None, NULL);
                glXDestroyContext(display, glc);
                XDestroyWindow(display, win);
                XCloseDisplay(display);
                delete engine;
                return(1);
            case XK_F2:
                engine->ToggleFrame();
                break;
            default:
                break;
            }
        case ResizeRequest:
            engine->SetViewport(rev->width, rev->height);
            break;
        default:
            break;
        }
    }
}

