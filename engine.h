#ifndef __engine_h_
#define __engine_h_

#include "glrender.h"
class vbo_object;

typedef struct Vertex {
    unsigned char r, g, b, a;
    GLfloat x, y, z;
} Vertex;

class engine {
public:
    virtual				~engine( void ) {
        destroy();
    };
    virtual int			msgBox(char *) {
        return -1;
    };
    virtual void		updateTimer() = 0;

    void 		init();
    void 		destroy();

    void		initRender();
    void		drawFrame();

    void		setViewport(int x, int y);
    void		setFrustum();

    double		getTime();

    void		toggleFrame();

    int			getResX();
    int			getResY();

protected:
    double		m_time;

private:
    GLRender *m_render;
    engine *m_engine;
    vbo_object *m_object;
};

extern engine *p_engine;

#endif
