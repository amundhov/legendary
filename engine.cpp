#include <stdio.h>
#include <GL/glew.h>
#include "engine.h"
#include "msg.h"
#include "cube.h"
#include "vbo_object.h"
#include "c3ds_object.h"


void engine::init() {
    initLog("debug.log");
    m_engine = this;
}

void engine::initRender()
{
    m_render = new GLRender;
    m_object = new c3ds_object("cube.3ds");
    m_object->locate(-100, 100, -200);

    m_cube = new cube();
    m_cube->locate(-100, 100, -200);
}

void engine::drawFrame()
{
    if (m_render) {
        updateTimer();
        m_render->drawFrame();
        m_object->draw();
        m_cube->draw();
    }
}

void engine::setViewport(int x, int y) {
    if (m_render) {
        m_render->setViewport(x, y);
    }
}

void engine::toggleFrame() {
    if (m_render)
        m_render->toggleFrame();
}

void engine::destroy() {
    delete m_render;
    delete m_object;
    closeLog();
}

double engine::getTime() {
    return m_time;
}

int engine::getResX() {
    return m_render->getResX();
}

int engine::getResY() {
    return m_render->getResY();
}

