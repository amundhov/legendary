#include "msg.h"
#include "cube.h"

cube::cube() {
	if(!count) {
		genBO();
		genTO();
	}
	
	loc.x = 0.0;
	loc.y = 0.0;
	loc.z = 0.0;

	count++;
}

cube::~cube() {
	if(!--count) {
		freeBO();
		freeTO();
	}
}

bool cube::genTO() {
	glGenTextures(1, &TO);
	glBindTexture(GL_TEXTURE_2D, TO);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	#define height 512
	#define width 512
	
	FILE *tex_file;	
	char *tex_buf;
	tex_buf = new char[height*width*3];
	
	if(!(tex_file = fopen("legendary.raw", "r+"))) Log("fopen fail.\n");
	fread(tex_buf, height*width*3, 1, tex_file);
	fclose(tex_file);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, height, width, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_buf);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	free(tex_buf);
	return true;
}

bool cube::freeTO() {
	glDeleteTextures(1, &TO);
	return true;
}

void cube::locate(float x, float y, float z) {
	loc.x = x;
	loc.y = y;
	loc.z = z;
}

bool cube::genBO() {					
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
				
	unsigned char ccube[] = {
				000, 000, 000,  255, 255, 255,  255, 255, 255,  000, 000, 000, // Front
				000, 000, 000,  000, 000, 000,  000, 000, 000,  255, 255, 255, // Right
				000, 000, 000,  000, 000, 000,  000, 000, 000,  000, 000, 000, // Bottom
				000, 000, 000,  000, 000, 000,  255, 255, 255,  000, 000, 000, // Left
				000, 000, 000,  255, 255, 255,  255, 255, 255,  000, 000, 000, // Back
				255, 255, 255,  255, 255, 255,  000, 000, 000,  000, 000, 000};// Top
	
	unsigned int icube[] = {
				0, 1, 2,		1, 0, 3,
				4, 5, 6,		4, 6, 7,
				8, 9, 10,		8, 10, 11,
				12, 13, 14,		12, 14, 15,
				16, 17, 18,		18, 17, 23, 
				20, 21, 22,		22, 23, 20};
				
	float tcube[] = 
			{	0.0, 1.0,  1.0, 0.0,  0.0, 0.0,  1.0, 1.0, 
				0.0, 1.0,  1.0, 1.0,  1.0, 0.0,  0.0, 0.0, 
				0.0, 1.0,  1.0, 1.0,  1.0, 0.0,  0.0, 0.0, 
				0.0, 1.0,  1.0, 1.0,  1.0, 0.0,  0.0, 0.0, 
				0.0, 1.0,  1.0, 1.0,  0.0, 0.0,  1.0, 0.0, 
				0.0, 1.0,  1.0, 1.0,  1.0, 0.0,  0.0, 0.0};
	
	VBO_size_vertex = sizeof(vcube);
	VBO_size_colour = sizeof(ccube);
	VBO_size_coord = sizeof(tcube);
	
	glGenBuffersARB(1, &VBO);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, VBO);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vcube) + sizeof(ccube) + sizeof(tcube), NULL, GL_STATIC_DRAW);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, sizeof(vcube), vcube);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vcube), sizeof(ccube), ccube);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vcube) + sizeof(ccube), sizeof(tcube), tcube);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	
	glGenBuffersARB(1, &IBO);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, IBO);
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(icube), icube, GL_STATIC_DRAW);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
	
	//Log("Generated the Buffer Objects. VBO: %i IBO: %i\n", VBO, IBO);
}

bool cube::freeBO() {
	//Log("Freeing the Buffer Objects.\n");
	if(VBO) glDeleteBuffersARB(1, &VBO);
	if(IBO) glDeleteBuffersARB(1, &IBO);
	return true;
}

void cube::draw() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, TO);
	//glDisable(GL_TEXTURE_2D);
	
	GLfloat transform[16] = {
	1,			0,		0,		0,
	0,			1,		0,		0,
	0,			0,		1,		0,
	loc.x,		loc.y,	loc.z,	1};	
	glLoadMatrixf(transform);
	
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, VBO);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, IBO);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, 0);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, (GLvoid *)VBO_size_vertex);
	glTexCoordPointer(2, GL_FLOAT, 0, (GLvoid *)(VBO_size_vertex+VBO_size_colour));
	glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, 0);

	glDisableClientState(GL_VERTEX_ARRAY);	
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
}

int unsigned cube::count = 0;
GLuint cube::VBO = 0;
GLuint cube::IBO = 0;
GLuint cube::TO  = 0;
int cube::VBO_size_vertex = 0;
int cube::VBO_size_colour = 0;
int cube::VBO_size_coord = 0;
