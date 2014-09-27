#include "types.h"

vec3 vec3::operator+(const vec3 &other) const{
	vec3 ret = { 0,0,0};
	ret.x = this->x + other.x;
	ret.y = this->y + other.y;
	ret.z = this->z + other.z;

	return ret;
}

vec3 vec3::operator-(const vec3 &other) const{
	vec3 ret = { 0,0,0};
	ret.x = this->x - other.x;
	ret.y = this->y - other.y;
	ret.z = this->z - other.z;

	return ret;
}

vec3 operator *(const double foo, const vec3 &vec){
	vec3 ret = vec;
	ret.x = ret.x * foo;
	ret.y = ret.y * foo;
	ret.z = ret.z * foo;

	return ret;
}

vec3 vec3::operator*(const double foo) const{
	vec3 ret = { 0,0,0};
	ret.x = this->x * foo;
	ret.y = this->y * foo;
	ret.z = this->z * foo;

	return ret;
}

vec3 vec3::operator/(const double foo) const{
	vec3 ret = { 0,0,0};
	ret.x = this->x / foo;
	ret.y = this->y / foo;
	ret.z = this->z / foo;

	return ret;
}

vec3 vec3::operator+=(const vec3 &other){
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;

	return *this;
}

vec3 vec3::operator-=(const vec3 &other){
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;

	return *this;
}

