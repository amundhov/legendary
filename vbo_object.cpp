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
    INDEX_SIZE = GL_UNSIGNED_SHORT;

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

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, VBO_size_vertices, vertices, GL_STATIC_DRAW);
    //glBufferSubData(GL_ARRAY_BUFFER, 0, VBO_size_vertices, vertices);
    //glBufferSubData(GL_ARRAY_BUFFER, VBO_size_vertices, VBO_size_colours, colours);
    //glBufferSubData(GL_ARRAY_BUFFER, VBO_size_vertices + VBO_size_colours, VBO_size_coords, coords);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, VBO_size_indices, indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    if ( vertices != NULL ) delete[] vertices;
    if ( indices != NULL ) delete[] indices;
    if ( colours != NULL ) delete[] colours;
    if ( coords != NULL ) delete[] coords;
    printf("Generated the Buffer Objects. VBO: %i IBO: %i\n", VBO, IBO);
}

void vbo_object::freeBO() {
    if (VBO) glDeleteBuffers(1, &VBO);
    if (IBO) glDeleteBuffers(1, &IBO);
}

void vbo_object::draw() {
    static float i=0;
    i+=0.20;

    GLfloat transform[16] = {
        1,			0,		0,		0,
        0,			1,		0,		0,
        0,			0,		1,		0,
        loc.x,		loc.y,	loc.z,	1
    };
    glLoadMatrixf(transform);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glEnableClientState(GL_VERTEX_ARRAY);
    //glEnableClientState(GL_COLOR_ARRAY);
    //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glRotatef(i, 1, 1, 1);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    //glColorPointer(3, GL_UNSIGNED_BYTE, 0, (GLvoid *)VBO_size_vertices);
    //glTexCoordPointer(2, GL_FLOAT, 0, (GLvoid *)(VBO_size_vertices+VBO_size_colours));
    glDrawElements(GL_TRIANGLES, VBO_indices, INDEX_SIZE, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    //glDisableClientState(GL_COLOR_ARRAY);
    //glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
unsigned int vbo_object::count = 0;
