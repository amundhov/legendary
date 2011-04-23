#ifndef __linux_h
#define __linux_h

#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glew.h>
#include <GL/glx.h>
#include <sys/time.h>
#include <string>
#include "engine.h"

class Sound;

class LinuxEngine : public engine {
public:
    LinuxEngine(void);
    ~LinuxEngine(void);

    int msgBox(std::string msg);
    void updateTimer();

private:
    suseconds_t m_elapsed;
    time_t m_lastTick;
    Sound *m_sound;
};

#endif
