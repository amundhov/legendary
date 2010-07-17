#ifndef __vbo_object_h_
#define __vbo_object_h_

#include "types.h"

class vbo_object {
	public:
		vbo_object();
		~vbo_object();

		bool genBO();
		bool freeBO();
		virtual float* getVertices()=0;
		virtual int* getIndices()=0;
		virtual unsigned char* getColours()=0;
		virtual float* getCoords()=0;
		void draw();

		void locate(float x, float y, float z);

	private:
		vec3 loc;
		float pitch;
		float roll;
		float yaw;

		static GLuint VBO;
		static GLuint IBO;

	protected:
		static int VBO_size_vertices;
		static int VBO_size_colours;
		static int VBO_size_indices;
		static int VBO_size_coords;

	static unsigned int count;
};

#endif
