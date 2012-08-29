#ifndef SCENE_H
#define SCENE_H

#include "vboobject.h"

class Scene {
public:
    Scene();
    ~Scene();
    void drawFrame(int tick);

private:
    VboObject *m_object;
};

#endif//SCENE_H

