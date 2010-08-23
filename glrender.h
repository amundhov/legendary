#ifndef GLRENDER_H
#define GLRENDER_H

#include <GL/glew.h>

class GLRender
{
public:
    GLRender();
    ~GLRender();

    void drawFrame();

    void setViewport(int x, int y);
    void setFrustum();

    void toggleFrame();

    int getResX()		{
        return m_xRes;
    };
    int getResY()		{
        return m_yRes;
    };


    GLuint shaderProgram() { return m_shaderProgram; }

private:
    void loadShaders();

    bool m_fill;				//Filled triangles? (For wireframe mode feature)

    int m_xRes, m_yRes;
    float m_xPos, m_yPos, m_zPos;

    float m_zNear, m_zFar;
    float m_fov;

    GLuint m_shaderProgram;
};

#endif//GLRENDER_H

