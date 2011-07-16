#ifndef __vbo_object_h_
#define __vbo_object_h_

#include "types.h"
#include <GL/glew.h>

class VboObject {
public:
    VboObject();
    ~VboObject();

    void genBO();
    void freeBO();
    virtual float* getVertices()=0;
    virtual int* getIndices()=0;
    virtual unsigned char* getColours()=0;
    virtual float* getCoords()=0;
    void draw();

    void locate(float x, float y, float z);

private:
    vec3 loc;
    float pitch;
    float roll;
    float yaw;

    GLuint VBO;
    GLuint IBO;

protected:
    int VBO_size_vertices;
    int VBO_size_colours;
    int VBO_size_coords;
    int VBO_size_indices;
    int VBO_indices;

    GLenum INDEX_SIZE;

    static unsigned int count;
};

#endif
