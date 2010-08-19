#include <math.h>
#include "msg.h"
#include "glrender.h"
#include "engine.h"
#include "file.h"

#define PI 3.14159265358979323846

GLRender::GLRender():
    m_fill(true),
    m_zNear(0.1),
    m_zFar(1000),
    m_fov(75)
{
    glClearColor(0.0,0.0,0.0,0.0f);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

    loadShaders();

    const int lightPos[] = {100, 100, -200, 0};
    glLightiv(GL_LIGHT0, GL_POSITION, lightPos);

    return;
}

GLRender::~GLRender()
{
    return;
}

//-----------------------------------------------------------------------------
// Purpose: Sets the OpenGL viewport to the approriate resolution and calls
//			SetFrustum() to correct aspect ratio and perspective
// Input  : x and y size of the viewport in pixels
//-----------------------------------------------------------------------------
void GLRender::setViewport(int x, int y)
{
    m_xRes = x;
    m_yRes = y;
    glViewport(0, 0, (GLsizei)x, (GLsizei)y);
    setFrustum();
}

//-----------------------------------------------------------------------------
// Purpose: Calculates and uploads Frustum matrix
//-----------------------------------------------------------------------------
void GLRender::setFrustum()
{
    GLfloat top = m_zNear * tan(0.5 * m_fov * PI / 180.0);
    GLfloat right = ((float)m_xRes/(float)m_yRes) * top;
    GLfloat frustum[16] = {
        (2*m_zNear)/(right+right), 0,						0,							 0,
        0,						(2*m_zNear)/(top+top),	0,							 0,
        0,						 0,						-(m_zFar+m_zNear)/(m_zFar-m_zNear),	-1,
        0,						 0,						-(2*m_zFar*m_zNear)/(m_zFar-m_zNear),0
    };
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(frustum);
    glMatrixMode(GL_MODELVIEW);
}

void GLRender::drawFrame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void GLRender::toggleFrame() {
    glPolygonMode(GL_FRONT, m_fill ? GL_LINE : GL_FILL);
    m_fill ^= 1;
    if (m_fill)
        Log("Wireframe off.\n");
    else
        Log("Wireframe on.\n");
}

void GLRender::loadShaders()
{
    GLuint fragShader, vertShader, program;

    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    vertShader = glCreateShader(GL_VERTEX_SHADER);

    const char *fragCode = File::readFile("shaders/simple.frag");
    glShaderSource(fragShader, 1, &fragCode, NULL);
    delete fragCode;

    const char *vertCode = File::readFile("shaders/simple.vertex");
    glShaderSource(vertShader, 1, &vertCode, NULL);
    delete vertCode;

    glCompileShader(fragShader);
    glCompileShader(vertShader);

    program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
    glUseProgram(program);

    char *log = new char[1000];
    glGetProgramInfoLog(program, 1000, NULL, log);
    printf("\n----------------------------\nShader program log:\n%s\n----------------------------\n", log);
    delete log;
}
