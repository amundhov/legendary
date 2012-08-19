#include <cstdlib>
#include <fstream>
#include <GL/glew.h>
#include "msg.h"
#include "vboobject.h"

VboObject::VboObject()
{
    loc.x = 0.0;
    loc.y = 0.0;
    loc.z = 0.0;

    reference_count = 0;
    VBO = 0;
    IBO = 0;
    VBO_size_vertices = 0;
    VBO_size_normals = 0;
    VBO_size_colours = 0;
    VBO_size_coords = 0;
    IBO_size_indices = 0;
    indices = 0;
    INDEX_SIZE = GL_UNSIGNED_SHORT;

    reference_count++;
}

VboObject::~VboObject() {
    if (!--reference_count)
        freeBO();
}

void VboObject::locate(float x, float y, float z) {
    loc.x = x;
    loc.y = y;
    loc.z = z;
}

void VboObject::genBO() {
    vec3 *vertices = getVertices();
    unsigned short int *indices = getIndices();
    unsigned char *colours = getColours();
    float *coords = getCoords();
    vec3 *normals = getNormals();

    LOG("Vertsize: " << VBO_size_vertices);
    LOG("colsize:" << VBO_size_colours); 
    LOG("coordsize:" << VBO_size_coords);
    LOG("indices:" << indices);

    const int VBO_total_size = VBO_size_colours + VBO_size_coords + VBO_size_normals + VBO_size_vertices;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, VBO_total_size, vertices, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, VBO_size_vertices, vertices);
    if ( normals != NULL ) glBufferSubData(GL_ARRAY_BUFFER, VBO_size_vertices, VBO_size_normals, normals);
    if ( colours != NULL ) glBufferSubData(GL_ARRAY_BUFFER, VBO_size_vertices+VBO_size_normals, VBO_size_colours, colours);
    if ( coords  != NULL ) glBufferSubData(GL_ARRAY_BUFFER, VBO_size_vertices+VBO_size_normals+VBO_size_colours, VBO_size_coords, coords);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, IBO_size_indices, indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    if ( vertices != NULL ) delete[] vertices;
    if ( indices != NULL ) delete[] indices;
    if ( colours != NULL ) delete[] colours;
    if ( coords != NULL ) delete[] coords;
    if ( normals != NULL ) delete[] normals;
    vertices = NULL;
    indices = NULL;
    colours = NULL;
    coords = NULL;
    normals = NULL;
    LOG("Generated the Buffer Objects.");
    LOG("VBO: " << VBO);
    LOG("IBO: " << IBO);
}

void VboObject::freeBO() {
    if (VBO) glDeleteBuffers(1, &VBO);
    if (IBO) glDeleteBuffers(1, &IBO);
}

void VboObject::draw() {
    static float i=0;
    i+=1.00;


    // Set an identity matrix
    const GLfloat transform[16] = {
        1,			0,		0,		0,
        0,			1,		0,		0,
        0,			0,		1,		0,
        loc.x,		loc.y,	loc.z,	1
    };
    glLoadMatrixf(transform);

    // Bind our buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Enable shit
    glEnableClientState(GL_VERTEX_ARRAY);
    if (VBO_size_normals) glEnableClientState(GL_NORMAL_ARRAY);
    if (VBO_size_colours) glEnableClientState(GL_COLOR_ARRAY);
    if (VBO_size_coords)  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    // Rotate to base
    glRotatef(i, 1, 1, 1);

    drawElements();

    // Return to previous state
    glDisableClientState(GL_VERTEX_ARRAY);
    if (VBO_size_normals) glDisableClientState(GL_NORMAL_ARRAY);
    if (VBO_size_colours) glDisableClientState(GL_COLOR_ARRAY);
    if (VBO_size_coords)  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/* Default implementation draws all vertices in one batch */
void VboObject::drawElements() {
    // Point to our vertices
    glVertexPointer(3, GL_FLOAT, 0, 0);
    if (VBO_size_normals) glNormalPointer(GL_FLOAT,0,(GLvoid*)VBO_size_vertices);
    if (VBO_size_colours) glColorPointer(3, GL_UNSIGNED_BYTE, 0, (GLvoid *)(VBO_size_vertices+VBO_size_normals));
    if (VBO_size_coords)  glTexCoordPointer(2, GL_FLOAT, 0, (GLvoid *)(VBO_size_vertices+VBO_size_normals+VBO_size_colours));
    glDrawElements(GL_TRIANGLES, indices, INDEX_SIZE, 0);
}

unsigned int VboObject::reference_count = 0;
