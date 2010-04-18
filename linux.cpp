#include <X11/keysymdef.h>
#include "linux.h"
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

LinuxEngine::LinuxEngine() {
	init();
	Log("Testing\n");
}

LinuxEngine::~LinuxEngine() {
	//Stub
}

int LinuxEngine::msgBox(char *msg) {
	//Forward to Log
	Log(msg);
	return 0;
}

void LinuxEngine::UpdateTimer() {
	//Stub. TODO: Actually update a timer
}

int main() {
	engine = new LinuxEngine;
	display = XOpenDisplay(NULL);
	if(!display) {
		Log("Couldn't open display, terminating.\n");
		delete engine;
		return 1;
	}

	root = DefaultRootWindow(display);
	vi = glXChooseVisual(display, 0, att);
	if(!vi) {
		delete engine;
		return 1;
	}
	
	cmap = XCreateColormap(display, root, vi->visual, AllocNone);
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask | ResizeRedirectMask;
	win = XCreateWindow(display, root, 0, 0, 600, 400, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);

	XMapWindow(display, win);
	XStoreName(display, win, "Legendary Alpha");
	glc = glXCreateContext(display, vi, NULL, GL_TRUE);
	glXMakeCurrent(display, win, glc);

	
	if(glewInit()) {
		Log("FATAL - glewInit failed.\n");
		return 0;
	}

	engine->initRender();
	engine->SetViewport(1024,600);

	while(1) {
		XNextEvent(display, &xev);
		
		switch(xev.type) {  
			case Expose:
		 		XGetWindowAttributes(display, win, &gwa);
				engine->DrawFrame();
				glXSwapBuffers(display, win);
				break;

			case KeyPress:
				switch(XLookupKeysym(&xev.xkey, 0)) {
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
				//engine->SetViewport(&xev.width, &xev.height);
				break;
			default:
				break;
		}
		engine->DrawFrame();
		glXSwapBuffers(display, win); }
}	

