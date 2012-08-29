#include <stdio.h>
#include <GL/glew.h>
#include "engine.h"
#include "msg.h"
#include "cube.h"
#include "sound.h"
#include "scene.h"


void Engine::init()
{
    m_engine = this;
}

void Engine::initRender()
{
    m_render = new GLRender;
    m_scene = new Scene();
}

void Engine::drawFrame()
{
    if (m_render) {
        updateTimer();
        m_render->drawFrame();
        m_scene->drawFrame(0);
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

