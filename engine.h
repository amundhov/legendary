#ifndef __engine_h_
#define __engine_h_

#include "glrender.h"

typedef struct Vertex {
	unsigned char r, g, b, a;
	GLfloat x, y, z;
} Vertex;

class engine {
	public:
virtual				~engine( void ) {destroy();};
virtual int			msgBox(char *msg) {return -1;};
virtual void		UpdateTimer() = 0;
		
		void 		init();
		void 		destroy();
		
		void		initRender();
		void		DrawFrame();
		
		void		SetViewport(int x, int y);
		void		SetFrustum();
		
		double		GetTime();
		
		void		ToggleFrame();
		
		int			getResX();
		int			getResY();
		
	protected:
		double		time;

	private:
		glRender	*Render;
};

extern engine *p_engine;

#endif
