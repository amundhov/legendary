#ifndef __CUBE_H
#define __CUBE_H

#include "material.h"
#include "rtt.h"
#include "vboobject.h"

class Cube : public VboObject {
public:
    Cube();
    ~Cube();
    float* getVertices();
    int* getIndices();
    unsigned char* getColours();
    float* getCoords();
    void draw();

private:
    Material *m_material;
};

#endif
