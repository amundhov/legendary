#ifndef __CUBE_H
#define __CUBE_H

#include "base_texture.h"
#include "rtt.h"
#include "vbo_object.h"

class cube : public vbo_object {
public:
    cube();
    ~cube();
    float* getVertices();
    int* getIndices();
    unsigned char* getColours();
    float* getCoords();
    void draw();

private:
    CBaseTexture *mat;
};

#endif
