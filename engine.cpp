#include <stdio.h>
#include <GL/glew.h>
#include "engine.h"
#include "msg.h"
#include "cube.h"
#include "vbo_object.h"
#include "c3ds_object.h"

engine *p_engine;
vbo_object **object;

void engine::init() {
    initLog("debug.log");
    p_engine = this;
}

void engine::initRender()
{
    Render = new GLRender;
    object = new vbo_object*[4];
    object[0] = new c3ds_object("cube.3ds");


    object[0]->locate(-100, 100, -200);
}

void engine::DrawFrame()
{
    if (Render) {
        updateTimer();
        Render->drawFrame();
            object[0]->draw();
    }
}

void engine::SetViewport(int x, int y) {
    if (Render) {
        Render->setViewport(x, y);
    }
}

void engine::ToggleFrame() {
    if (Render)
        Render->toggleFrame();
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
