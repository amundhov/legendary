#include "cube.h"

cube::cube() : vbo_object() {
	mat = new CTexture("legendary.raw");
}

cube::~cube() {
	delete mat;
}

void cube::draw() {
	mat->Bind();
	vbo_object::draw();
}

float* cube::getVertices() {
	float vcube[] = 
			{	-50.0, -50.0,  50.0, 	// 4 Front	0
				50.0,  50.0,  50.0,		// 1
				-50.0,  50.0,  50.0,	// 0		2
				50.0, -50.0,  50.0,		// 5
				
				50.0, -50.0,  50.0, 	// 5 Right	4
				50.0, -50.0, -50.0,		// 7
				50.0,  50.0, -50.0,		// 3		6
				50.0,  50.0,  50.0,		// 1
				
				-50.0, -50.0, -50.0, 	// 6 Bottom	8
				50.0, -50.0, -50.0,		// 7
				50.0, -50.0,  50.0,		// 5		10
				-50.0, -50.0,  50.0,	// 4
				
				-50.0, -50.0, -50.0, 	// 6 Left	12
				-50.0, -50.0,  50.0,	// 4
				-50.0,  50.0,  50.0,	// 0		14
				-50.0,  50.0, -50.0,	// 2
				
				50.0, -50.0, -50.0, 	// 7 Back	16
				-50.0, -50.0, -50.0,	// 6
				50.0,  50.0, -50.0,		// 3		18
				-50.0,  50.0, -50.0,	// 2
				
				-50.0,  50.0,  50.0, 	// 0 Top	20
				50.0,  50.0,  50.0,		// 1
				50.0,  50.0, -50.0,		// 3		22
				-50.0,  50.0, -50.0};	// 2
	float *ret = new float[sizeof(vcube)];
	for ( int i=0; i < sizeof(vcube); i++ ) {
		ret[i] = vcube[i];
	}
	return ret;
}
			

int* cube::getIndices() {
	unsigned int icube[] = {
				0, 1, 2,		1, 0, 3,
				4, 5, 6,		4, 6, 7,
				8, 9, 10,		8, 10, 11,
				12, 13, 14,		12, 14, 15,
				16, 17, 18,		18, 17, 23, 
				20, 21, 22,		22, 23, 20};
	int *ret = new int[sizeof(icube)];
	for ( int i=0; i < sizeof(icube); i++ ) {
		ret[i] = icube[i];
	}
	return ret;
}

unsigned char* cube::getColours() {
	unsigned char ccube[] = {
				000, 000, 000,  255, 255, 255,  255, 255, 255,  000, 000, 000, // Front
				000, 000, 000,  000, 000, 000,  000, 000, 000,  255, 255, 255, // Right
				000, 000, 000,  000, 000, 000,  000, 000, 000,  000, 000, 000, // Bottom
				000, 000, 000,  000, 000, 000,  255, 255, 255,  000, 000, 000, // Left
				000, 000, 000,  255, 255, 255,  255, 255, 255,  000, 000, 000, // Back
				255, 255, 255,  255, 255, 255,  000, 000, 000,  000, 000, 000};// Top
	unsigned char *ret = new unsigned char[sizeof(ccube)];
	for ( int i=0; i < sizeof(ccube); i++ ) {
		ret[i] = ccube[i];
	}
	return ret;
}

float* cube::getCoords() {
	float tcube[] = 
			{	0.0, 1.0,  1.0, 0.0,  0.0, 0.0,  1.0, 1.0, 
				0.0, 1.0,  1.0, 1.0,  1.0, 0.0,  0.0, 0.0, 
				0.0, 1.0,  1.0, 1.0,  1.0, 0.0,  0.0, 0.0, 
				0.0, 1.0,  1.0, 1.0,  1.0, 0.0,  0.0, 0.0, 
				0.0, 1.0,  1.0, 1.0,  0.0, 0.0,  1.0, 0.0, 
				0.0, 1.0,  1.0, 1.0,  1.0, 0.0,  0.0, 0.0};
	float *ret = new float[sizeof(tcube)];
	for ( int i=0; i < sizeof(tcube); i++ ) {
		ret[i] = tcube[i];
	}
	return ret;
}
