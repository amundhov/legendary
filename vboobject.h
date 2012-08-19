#ifndef __vbo_object_h_
#define __vbo_object_h_

#include "types.h"
#include <GL/glew.h>

class VboObject {
public:
    VboObject();
    virtual ~VboObject();

    void genBO();
    void freeBO();
    virtual vec3* getVertices()=0;
    virtual unsigned short int* getIndices()=0;
    virtual unsigned char* getColours()=0;
    virtual float* getCoords()=0;
    virtual vec3* getNormals()=0;
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
    virtual void drawElements();

    int VBO_size_vertices;
    int VBO_size_normals;
    int VBO_size_colours;
    int VBO_size_coords;
    int IBO_size_indices;
    int IBO_indices;

    GLenum INDEX_SIZE;

    static unsigned int reference_count;
};

#endif
