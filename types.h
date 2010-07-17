#ifndef __types_h_
#define __types_h_

#include "GL/glew.h"


class vec3 {
public:
	float x,y,z;
	vec3 operator+(const vec3 &other) const;
	vec3 operator-(const vec3 &other) const;
	vec3 operator+=(const vec3 &other);
	vec3 operator*(const double foo) const;
	vec3 operator/(const double foo) const;

	friend vec3 operator *(const double foo, const vec3 &vec);

};

vec3 operator *(const double foo, const vec3 &vec);

typedef struct Vertex {
	unsigned char r, g, b, a;
	GLfloat x, y, z;
} Vertex;

#endif
