#ifndef __CUBE_H
#define __CUBE_H

#include "types.h"

#include "material.h"
#include "rtt.h"
#include "vboobject.h"

class Cube : public VboObject {
public:
    Cube();
    virtual ~Cube();
    vec3* getVertices();
    vec3* getNormals();
    unsigned short int* getIndices();
    unsigned char* getColours();
    float* getCoords();
    void draw();

private:
    Material *m_material;
};

#endif
