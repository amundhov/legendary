#include <math.h>
#include "msg.h"
#include "glrender.h"
#include "engine.h"
#include "file.h"
#include "material.h"

#define PI 3.14159265358979323846

GLRender::GLRender():
    m_fill(true),
    m_zNear(0.1),
    m_zFar(1000),
    m_fov(75),
    m_shaderProgram(0)
{
    glClearColor(0.0,0.0,0.0,0.0f);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glEnable(GL_TEXTURE_2D);
    glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

    loadShaders();

    const int lightPos[] = {0, 0, -20, 0};
    const float color[] = { 0.8, 0.8, 0.8, 0.8 };
    glLightiv(GL_LIGHT0, GL_POSITION, lightPos);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

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
    glViewport(0, 0, x, y);
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
    if (m_fill) {
        LOG("Wireframe off.\n");
    }
    else {
        LOG("Wireframe on.\n");
    }
}

void GLRender::loadShaders()
{
    GLuint fragShader, vertShader;

    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    vertShader = glCreateShader(GL_VERTEX_SHADER);

    const char *fragCode = File::readFile("shaders/simple-frag.glsl");
    glShaderSource(fragShader, 1, &fragCode, NULL);
    delete [] fragCode;

    const char *vertCode = File::readFile("shaders/simple-vertex.glsl");
    glShaderSource(vertShader, 1, &vertCode, NULL);
    delete [] vertCode;

    glCompileShader(fragShader);
    glCompileShader(vertShader);

    if (m_shaderProgram) // if we are reloading we need to delete the old one first
        glDeleteProgram(m_shaderProgram);
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertShader);
    glAttachShader(m_shaderProgram, fragShader);
    glLinkProgram(m_shaderProgram);
    glUseProgram(m_shaderProgram);

    char *log = new char[1000];
    GLint success;
    glGetProgramInfoLog(m_shaderProgram, 1000, &success, log);


    if (success != 0) { // Something bad happened
        LOG("\n\033[91m ERROR WHILE COMPILING SHADER:\n" << log << "\033[0m\n" << std::endl);
        delete [] log;
        glDeleteProgram(m_shaderProgram);
        m_shaderProgram = 0;
        return;
    }

    delete [] log;

    // Set up uniform variables for textures
    GLint imageLoc = glGetUniformLocation(m_shaderProgram, "image");
    GLint normalLoc = glGetUniformLocation(m_shaderProgram, "normal");
    GLint shadowLoc = glGetUniformLocation(m_shaderProgram, "shadow");
    glUniform1i(imageLoc, GL_TEXTURE0 + IMAGEOFFSET);
    glUniform1i(normalLoc, GL_TEXTURE0 +  NORMALOFFSET);
    glUniform1i(shadowLoc, GL_TEXTURE0 + SHADOWOFFSET);
}

