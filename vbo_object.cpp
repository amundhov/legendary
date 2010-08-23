#include <cstdlib>
#include <fstream>
#include <GL/glew.h>
#include "msg.h"
#include "vbo_object.h"

vbo_object::vbo_object()
{
    loc.x = 0.0;
    loc.y = 0.0;
    loc.z = 0.0;

    count = 0;
    VBO = 0;
    IBO = 0;
    VBO_size_vertices = 0;
    VBO_size_colours = 0;
    VBO_size_coords = 0;
    VBO_size_indices = 0;
    VBO_indices = 0;
    INDEX_SIZE = GL_UNSIGNED_INT;

    count++;
}

vbo_object::~vbo_object() {
    if (!--count)
        freeBO();
}

void vbo_object::locate(float x, float y, float z) {
    loc.x = x;
    loc.y = y;
    loc.z = z;
}

void vbo_object::genBO() {
    float *vertices = getVertices();
    int *indices = getIndices();
    unsigned char *colours = getColours();
    float *coords = getCoords();

    printf("Vertsize %i, Colsize %i, coordsize %i, indices %i\n",
        VBO_size_vertices,VBO_size_colours,VBO_size_coords,VBO_indices);

    glGenBuffersARB(1, &VBO);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, VBO);
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, VBO_size_vertices + VBO_size_colours + VBO_size_coords, NULL, GL_STATIC_DRAW);
    glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, VBO_size_vertices, vertices);
    glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, VBO_size_vertices, VBO_size_colours, colours);
    glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, VBO_size_vertices + VBO_size_colours, VBO_size_coords, coords);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

    glGenBuffersARB(1, &IBO);
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, IBO);
    glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, VBO_size_indices, indices, GL_STATIC_DRAW);
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    if ( vertices != NULL ) delete[] vertices;
    if ( indices != NULL ) delete[] indices;
    if ( colours != NULL ) delete[] colours;
    if ( coords != NULL ) delete[] coords;
    printf("Generated the Buffer Objects. VBO: %i IBO: %i\n", VBO, IBO);
}

void vbo_object::freeBO() {
    if (VBO) glDeleteBuffersARB(1, &VBO);
    if (IBO) glDeleteBuffersARB(1, &IBO);
}

void vbo_object::draw() {
    static float i=0;
    i+=0.01;

    GLfloat transform[16] = {
        1,			0,		0,		0,
        0,			1,		0,		0,
        0,			0,		1,		0,
        loc.x,		loc.y,	loc.z,	1
    };
    glLoadMatrixf(transform);

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, VBO);
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, IBO);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glRotatef(i, 1, 1, 1);

    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColorPointer(3, GL_UNSIGNED_BYTE, 0, (GLvoid *)VBO_size_vertices);
    glTexCoordPointer(2, GL_FLOAT, 0, (GLvoid *)(VBO_size_vertices+VBO_size_colours));
    glDrawElements(GL_TRIANGLES, VBO_indices, INDEX_SIZE, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
}
unsigned int vbo_object::count = 0;
