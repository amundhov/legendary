#include <X11/keysymdef.h>
#include "linux.h"
#include "sound.h"
#include "msg.h"

Display                 *display;
Window                  root;
GLint                   att[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
Colormap                cmap;
XSetWindowAttributes    swa;
XWindowAttributes       gwa;

LinuxEngine				*engine;

LinuxEngine::LinuxEngine() :
        m_elapsed(0),
        m_sound(new Sound("default"))
{
    init();
    Log("LINUX ENGINE INITIALIZED!\n");
    printf("\n▛▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▜\n");
    printf(  "▌ DIE LINUX TRIEBWERK INITIALISERT WURDE! ▐\n");
    printf(  "▙▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▂▟\n\n");
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
    //printf("FPS: %i\n", int(1000000.0/ m_elapsed));
    m_lastTick = cur;
}

int main() {
    engine = new LinuxEngine;

    display = XOpenDisplay(NULL);
    if (!display) {
        Log("Couldn't open display, terminating.\n");
        delete engine;
        return 1;
    }

    root = DefaultRootWindow(display);
    XVisualInfo *visualInfo = glXChooseVisual(display, 0, att);
    if (!visualInfo) {
        printf("FATAL: Unable to acquire visual!");
        delete engine;
        return 1;
    }

    cmap = XCreateColormap(display, root, visualInfo->visual, AllocNone);
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask;// | ResizeRedirectMask;
    Window win = XCreateWindow(display, root, 0, 0, 1024, 600, 0, visualInfo->depth, InputOutput, visualInfo->visual, CWColormap | CWEventMask, &swa);


    XMapWindow(display, win);
    XStoreName(display, win, "tenn0");
    GLXContext context = glXCreateContext(display, visualInfo, NULL, GL_TRUE);
    glXMakeCurrent(display, win, context);

    if (glewInit()) {
        Log("FATAL! glewInit failed!\n");
        return 0;
    }

    if (!glewIsSupported("GL_VERSION_2_0")) {
        printf("FATAL! Needs OpenGL 2.0 or later!\n");
        return 255;
    }


    engine->initRender();
    engine->setViewport(1024,768);

    XEvent xev;
    while (1) {
        engine->drawFrame();
        glXSwapBuffers(display, win);

        if (!XPending(display))
            continue;

        XNextEvent(display, &xev);

        //XResizeRequestEvent *rev = reinterpret_cast<XResizeRequestEvent*>(&xev);
        switch (xev.type) {
        case Expose:
            XGetWindowAttributes(display, win, &gwa);
            engine->setViewport(gwa.width, gwa.height);
            engine->drawFrame();
            glXSwapBuffers(display, win);
            break;

        case KeyPress:
            switch (XLookupKeysym(&xev.xkey, 0)) {
            case XK_Escape:
            case XK_space:
                glXMakeCurrent(display, None, NULL);
                glXDestroyContext(display, context);
                XDestroyWindow(display, win);
                XCloseDisplay(display);
                delete engine;
                return(1);
            case XK_F2:
                engine->toggleFrame();
                break;
            default:
                continue;
            }
        default:
            break;
        }
    }
}

