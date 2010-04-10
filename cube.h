#ifndef __CUBE_H
#define __CUBE_H

#include <gl/glew.h>

typedef struct vec3 {
	float x,y,z;
} vec3;

class cube {
	public:
		cube();
		~cube();

		bool genBO();
		bool freeBO();
		bool genTO();
		bool freeTO();
		void draw();
		
		void locate(float x, float y, float z);

	private:
		vec3 loc;
		float pitch;
		float roll;
		float yaw;
		
		static GLuint VBO;
		static GLuint IBO;
		static GLuint TO;
		
		static int VBO_size_vertex;
		static int VBO_size_colour;
		static int VBO_size_coord;
		
		static unsigned int count;
};

#endif
