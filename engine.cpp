#include <stdio.h>
#include <GL/glew.h>
#include "engine.h"
#include "msg.h"
#include "cube.h"
#include "vbo_object.h"

engine *p_engine;
vbo_object **object;

void engine::init() {
	initLog("debug.log");
	p_engine = this;
}

void engine::initRender()
{
	Render = new glRender;
	object = new vbo_object*[4];
	for ( int i=0; i<4; i++ ) {
			object[i] = new cube();
	}

	object[0]->locate(-100, 100, -200);
	object[1]->locate( 100, -100, -200);
	object[2]->locate( 100, 100, -200);
	object[3]->locate( -100, -100, -200);
}

void engine::DrawFrame()
{
	if(Render) {
		UpdateTimer();
		Render->DrawFrame();
		for(int it = 0; it < 4; it++)
			object[it]->draw();
	}
}

void engine::SetViewport(int x, int y) {
	if(Render) {
		Render->SetViewport(x, y);
	}
}

void engine::ToggleFrame() {
	if(Render)
	Render->ToggleFrame();
}

void engine::destroy() {
	delete Render;
	closeLog();
}

double engine::GetTime() {
	return time;
}

int engine::getResX() {
	return Render->getResX();
}

int engine::getResY() {
	return Render->getResY();
}
