#ifndef __nbody_H
#define __nbody_H

#include <GL/glew.h>
#include "types.h"

class nbody {
	public:
		nbody(int nodes);
		~nbody();

		void draw();
		void reset();
		void tick();
		void locate(float x, float y, float z);

	private:
		vec3 loc;
		vec3 *pos;
		vec3 *vel;
		int nodes;
		//float pitch;
		//float roll;
		//float yaw;

		//GLuint VBO;
		//GLuint IBO;

		//int VBO_size_vertex;
		//int VBO_size_colour;
		//int VBO_size_coord;
		float sfrand(void);
		unsigned int mirand;
		inline static double force(float,float);
		static const float dt = 0.0001f;
};

#endif
