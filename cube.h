#ifndef __CUBE_H
#define __CUBE_H

#include <GL/glew.h>
#include "material.h"
#include "rtt.h"

typedef struct vec3 {
	float x,y,z;
} vec3;

class cube {
	public:
		cube();
		~cube();

		bool genBO();
		bool freeBO();
		void draw();
		
		void locate(float x, float y, float z);

	private:
		vec3 loc;
		float pitch;
		float roll;
		float yaw;

		CMaterial *mat;
		//CRenderToTextureMaterial *mat;
		
		static GLuint VBO;
		static GLuint IBO;
		
		static int VBO_size_vertex;
		static int VBO_size_colour;
		static int VBO_size_coord;
		
		static unsigned int count;
};

#endif
