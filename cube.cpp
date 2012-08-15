#include "cube.h"

#include "msg.h"
#include "rawtexture.h"

Cube::Cube() : VboObject() {
    if (reference_count == 1) {
        genBO();
        m_material = new RawTexture("legendary.raw");
        //mat = new CRenderToTextureMaterial;
        LOG("Cube VBO generated\n");
    }
}

Cube::~Cube() {
    delete m_material;
}

void Cube::draw() {
    m_material->Bind();
    VboObject::draw();
}

float* Cube::getVertices() {
    float vcube[] =
        {	-1.0, -1.0,  1.0, 	// 4 Front	0
          1.0,  1.0,  1.0,		// 1
          -1.0,  1.0,  1.0,	// 0		2
          1.0, -1.0,  1.0,		// 5

          1.0, -1.0,  1.0, 	// 5 Right	4
          1.0, -1.0, -1.0,		// 7
          1.0,  1.0, -1.0,		// 3		6
          1.0,  1.0,  1.0,		// 1

          -1.0, -1.0, -1.0, 	// 6 Bottom	8
          1.0, -1.0, -1.0,		// 7
          1.0, -1.0,  1.0,		// 5		10
          -1.0, -1.0,  1.0,	// 4

          -1.0, -1.0, -1.0, 	// 6 Left	12
          -1.0, -1.0,  1.0,	// 4
          -1.0,  1.0,  1.0,	// 0		14
          -1.0,  1.0, -1.0,	// 2

          1.0, -1.0, -1.0, 	// 7 Back	16
          -1.0, -1.0, -1.0,	// 6
          1.0,  1.0, -1.0,		// 3		18
          -1.0,  1.0, -1.0,	// 2

          -1.0,  1.0,  1.0, 	// 0 Top	20
          1.0,  1.0,  1.0,		// 1
          1.0,  1.0, -1.0,		// 3		22
          -1.0,  1.0, -1.0
        };	// 2
    VBO_size_vertices = sizeof(vcube);
    int vertices = sizeof(vcube)/sizeof(float);
    float *ret = new float[vertices];
    for ( int i=0; i < vertices; i++ ) {
        ret[i] = vcube[i];
    }
    return ret;
}

unsigned int* Cube::getIndices() {
    unsigned short int icube[] = {
        0, 1, 2,		1, 0, 3,
        4, 5, 6,		4, 6, 7,
        8, 9, 10,		8, 10, 11,
        12, 13, 14,		12, 14, 15,
        16, 17, 18,		18, 17, 23,
        20, 21, 22,		22, 23, 20
    };
    IBO_size_indices = sizeof(icube);
    indices = sizeof(icube)/sizeof(unsigned short int);
    unsigned short int *ret = new unsigned short int[indices];
    for ( int i=0; i < indices; i++ ) {
        ret[i] = icube[i];
    }
    return (unsigned int*)ret;
}

unsigned char* Cube::getColours() {
    unsigned char ccube[] = {
        200, 000, 000,  055, 255, 000,  255, 255, 255,  050, 000, 050, // Front
        000, 000, 100,  100, 000, 000,  000, 200, 000,  255, 255, 255, // Right
        000, 100, 000,  100, 000, 200,  200, 000, 000,  100, 000, 200, // Bottom
        150, 200, 000,  100, 200, 000,  255, 255, 255,  000, 100, 100, // Left
        000, 220, 000,  255, 255, 255,  255, 255, 255,  100, 100, 200, // Back
        255, 255, 255,  255, 255, 255,  200, 000, 100,  000, 050, 200  // Top
    };// Top
    VBO_size_colours = sizeof(ccube);
    int colours = sizeof(ccube)/sizeof(unsigned char);
    unsigned char *ret = new unsigned char[colours];
    for ( int i=0; i < colours; i++ ) {
        ret[i] = ccube[i];
    }
    return ret;
}

float* Cube::getCoords() {
    float tcube[] =
        {	0.0, 1.0,  1.0, 0.0,  0.0, 0.0,  1.0, 1.0,
          0.0, 1.0,  1.0, 1.0,  1.0, 0.0,  0.0, 0.0,
          0.0, 1.0,  1.0, 1.0,  1.0, 0.0,  0.0, 0.0,
          0.0, 1.0,  1.0, 1.0,  1.0, 0.0,  0.0, 0.0,
          0.0, 1.0,  1.0, 1.0,  0.0, 0.0,  1.0, 0.0,
          0.0, 1.0,  1.0, 1.0,  1.0, 0.0,  0.0, 0.0
        };
    VBO_size_coords = sizeof(tcube);
    int coords = sizeof(tcube)/sizeof(float);
    float *ret = new float[coords];
    for ( int i=0; i < coords; i++ ) {
        ret[i] = tcube[i];
    }
    return ret;
}


float* Cube::getNormals() {
    return NULL;
}
