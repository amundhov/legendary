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

LinuxEngine				*Engine;

LinuxEngine::LinuxEngine() :
        m_elapsed(0),
        m_sound(new Sound("null"))
{
    init();
    LOG("LINUX ENGINE LOADED");
    m_sound->play();
}

LinuxEngine::~LinuxEngine() {
    delete m_sound;
}

int LinuxEngine::msgBox(std::string msg) {
    //printf("ATTENTION: %s\n", msg);
    system(std::string("zenity --info --text='" + msg + "'").c_str());
    //Forward to Log
    LOG(msg.c_str());
    return 0;
}

void LinuxEngine::updateTimer() {
    struct timeval now;
    gettimeofday(&now, NULL);
    suseconds_t cur = (now.tv_sec * 1000000) + now.tv_usec;
    m_elapsed = cur - m_lastTick;
    //Log("FPS: %i\n", int(1000000.0/ m_elapsed));
    m_lastTick = cur;

    //m_sound->getBass();
}

int main() {
    Engine = new LinuxEngine;

    display = XOpenDisplay(NULL);
    if (!display) {
        LOG("Couldn't open display, terminating.");
        delete Engine;
        return 1;
    }

    root = DefaultRootWindow(display);
    XVisualInfo *visualInfo = glXChooseVisual(display, 0, att);
    if (!visualInfo) {
        LOG("FATAL: Unable to acquire visual!");
        delete Engine;
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
        LOG("FATAL! glewInit failed!\n");
        return 0;
    }

    if (!glewIsSupported("GL_VERSION_2_0")) {
        LOG("FATAL! Needs OpenGL 2.0 or later!");
        return 255;
    }
    //if (!glewIsSupported("GL_EXT_geometry_shader4")) {
    //    LOG("FATAL! Needs geometry shader support!");
    //    return 255;
    //}


    Engine->initRender();
    Engine->setViewport(1024,768);

    XEvent xev;
    while (1) {
        Engine->drawFrame();
        glXSwapBuffers(display, win);

        if (!XPending(display))
            continue;

        XNextEvent(display, &xev);

        //XResizeRequestEvent *rev = reinterpret_cast<XResizeRequestEvent*>(&xev);
        switch (xev.type) {
        case Expose:
            XGetWindowAttributes(display, win, &gwa);
            Engine->setViewport(gwa.width, gwa.height);
            Engine->drawFrame();
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
                delete Engine;
                return(1);
            case XK_F2:
                Engine->toggleFrame();
                break;
            case XK_F3:
                Engine->reloadShaders();
                break;
            default:
                continue;
            }
        default:
            break;
        }
    }
}

