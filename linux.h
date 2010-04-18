#ifndef __linux_h
#define __linux_h

#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glew.h>
#include <GL/glx.h>
#include "engine.h"

class LinuxEngine : public engine {
	public:
		LinuxEngine(void);
		~LinuxEngine(void);
			
		int msgBox(char *msg);
		void UpdateTimer();
};

#endif
