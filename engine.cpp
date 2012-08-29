#include <stdio.h>
#include <GL/glew.h>
#include "engine.h"
#include "msg.h"
#include "cube.h"
#include "sound.h"
#include "vboobject.h"
#include "c3dsobject.h"


void Engine::init()
{
    m_cube = 0;
    m_engine = this;
}

void Engine::initRender()
{
    m_render = new GLRender;
    m_object = new C3dsScene("cube.3ds");
    //m_object = new Cube;
    m_object->locate(0, 0,-10);

}

void Engine::drawFrame()
{
    if (m_render) {
        updateTimer();
        m_render->drawFrame();
        m_object->draw();
    }
}

void Engine::setViewport(int x, int y) {
    if (m_render) {
        m_render->setViewport(x, y);
    }
}

void Engine::toggleFrame() {
    if (m_render)
        m_render->toggleFrame();
}

void Engine::reloadShaders()
{
    if (m_render)
        m_render->loadShaders();
}

void Engine::destroy() {
    delete m_render;
    delete m_object;
}

double Engine::getTime() {
    return m_time;
}

int Engine::getResX() {
    return m_render->getResX();
}

int Engine::getResY() {
    return m_render->getResY();
}

