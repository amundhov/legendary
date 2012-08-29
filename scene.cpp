#include "scene.h"

#include "c3dsobject.h"

Scene::Scene()
{
    m_object = new C3dsObject("cube.3ds");
    m_object->locate(0, 0,-10);
}

Scene::~Scene()
{
    delete m_object;
}

void Scene::drawFrame(int)
{
    m_object->draw();
}

