#ifndef __CUBE_H
#define __CUBE_H

#include "material.h"
#include "rtt.h"
#include "vboobject.h"

class Cube : public VboObject {
public:
    Cube();
    virtual ~Cube();
    float* getVertices();
    float* getNormals();
    unsigned short int* getIndices();
    unsigned char* getColours();
    float* getCoords();
    void draw();

private:
    Material *m_material;
};

#endif
