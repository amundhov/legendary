#ifndef __engine_h_
#define __engine_h_

#include "glrender.h"
class Scene;

typedef struct Vertex {
    unsigned char r, g, b, a;
    GLfloat x, y, z;
} Vertex;

class Engine {
public:
    virtual				~Engine( void ) {
        destroy();
    };
    virtual int			msgBox(char *) {
        return -1;
    };
    virtual void		updateTimer() = 0;

    void init();
    void destroy();

    void initRender();
    void drawFrame();

    void setViewport(int x, int y);
    void setFrustum();

    double getTime();

    void toggleFrame();

    void reloadShaders();

    int getResX();
    int getResY();

protected:
    double		m_time;

private:
    GLRender *m_render;
    Engine *m_engine;
    Scene *m_scene;
};

extern Engine *p_engine;

#endif
