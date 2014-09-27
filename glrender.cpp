#include <math.h>
#include "msg.h"
#include "glrender.h"
#include "engine.h"

#define PI 3.14159265358979323846

glRender::glRender()
{
	zNear = 0.1; zFar = 1000;
	fov = 100; fill = true;
	
	glClearColor(0.0,0.0,0.0,0.0f);
	glCullFace(GL_BACK);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
	
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

    // Point stuff
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPointSize(15);

    //GLfloat quadratic[3] = { 0.25, 0.0, 1/60.0 };
    GLfloat quadratic[3] = { 1.0f, 0.0f, 0.0f };
    glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, quadratic);

    // Light
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);
    static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glEnable(GL_LINE_SMOOTH);
    glLineWidth(3);

	
	return;
}

glRender::~glRender()
{
	return;
}

//-----------------------------------------------------------------------------
// Purpose: Sets the OpenGL viewport to the approriate resolution and calls
//			SetFrustum() to correct aspect ratio and perspective
// Input  : x and y size of the viewport in pixels
//-----------------------------------------------------------------------------
void glRender::SetViewport(int x, int y)
{
	xRes = x; yRes = y;
	glViewport(0, 0, (GLsizei)x, (GLsizei)y);
	SetFrustum();
}

//-----------------------------------------------------------------------------
// Purpose: Calculates and uploads Frustum matrix
//-----------------------------------------------------------------------------
void glRender::SetFrustum()
{
	GLfloat top = zNear * tan(0.5 * fov * PI / 180.0);
	GLfloat right = ((float)xRes/(float)yRes) * top;
	GLfloat frustum[16] = {
	(2*zNear)/(right+right), 0,						0,							 0,
	0,						(2*zNear)/(top+top),	0,							 0,
	0,						 0,						-(zFar+zNear)/(zFar-zNear),	-2,
	0,						 0,						-(2*zFar*zNear)/(zFar-zNear),0};	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(frustum);
	glMatrixMode(GL_MODELVIEW);
}

void glRender::DrawFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void glRender::ToggleFrame() {
	glPolygonMode(GL_FRONT, fill == true ? GL_LINE : GL_FILL);
	fill ^= 1;
	if(fill)
		Log("Wireframe off.\n");
	else
		Log("Wireframe on.\n");
}
