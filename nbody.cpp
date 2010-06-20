#include <cstdlib>
#include <fstream>
#include <cmath>
#include "msg.h"
#include "nbody.h"

nbody::nbody(int nodes) {
	mirand = 1;
	locate(0,0,0);
	//glEnable(GL_POINT_SMOOTH);
	this->nodes = nodes;
	pos = new vec3[nodes];
	vel = new vec3[nodes];
	reset();
	Log("Nobdy allocated");
}

nbody::~nbody() {
	delete[] pos;
	delete[] vel;
	
}

float nbody::sfrand(void){
    unsigned int a;
    mirand *= 16807;
    a = (mirand&0x007fffff) | 0x40000000; // fix exponent to 128
    return( *((float*)&a) - 3.0f );       // float [-1,1]
}

void nbody::tick(){

	float accx;
	float accy;
	float accz;
	for (int i=0; i<nodes; i++){
		accx = 0;
		accy = 0;
		accz = 0;
		//Log("Pos (%f,%f)\n", pos[i].x,pos[i].y);
		for ( int j=0; j<nodes; j++){
			float len2x = pow((pos[j].x - pos[i].x),2);
			float len2y = pow((pos[j].y - pos[i].y),2);
			float len2z = pow((pos[j].z - pos[i].z),2);
			float invlen = 1/(pow(len2x+len2y+len2z,1.5f)+1E-4);
			float dx = pos[j].x - pos[i].x;
			float dy = pos[j].y - pos[i].y;
			float dz = pos[j].z - pos[i].z;
			accx += dx*invlen;
			accy += dy*invlen;
			accz += dz*invlen;
			//Log("invlen: %f, dx: %f, force x %f\n",invlen,dx,accx);
		}
		vel[i].x += accx*dt;
		vel[i].y += accy*dt;
		vel[i].z += accz*dt;
		pos[i].x += dt * vel[i].x;
		pos[i].y += dt * vel[i].y;
		pos[i].z += dt * vel[i].z;
	}
}

inline double nbody::force(float x, float y){
	float dividend = y-x;
	float divisor = (pow(abs(dividend),3) + 1E-20)*100;
	double ret = dividend / divisor;
	return ret;
}

void nbody::reset(){
	for (int i=0;i<45;i++) sfrand();
	for ( int i=0; i<nodes; i++){
		pos[i].x = pow(sfrand(),1);
		pos[i].y = pow(sfrand(),1)/2;
		pos[i].z = -1.0f;
		vel[i].x =0;//sfrand()*pos[i].y*40.0f;
		vel[i].y =0;//sfrand()*pos[i].x*-40.0f;
		vel[i].z =0;
		Log("position %f %f %f\n",pos[i].x, pos[i].y, pos[i].z);
	}
	//pos[0].x = -1;
	//pos[0].y = 0;
	//pos[0].z = -1;
	//pos[1].x = 1;
	//pos[1].y = 0;
	//pos[1].z = -1;
	//vel[0].x = 0;
	//vel[0].y = 0;
	//vel[0].z = 0;
	//vel[1].x = 0;
	//vel[1].y = 0;
	//vel[1].z = 0;
}

void nbody::locate(float x, float y, float z) {
	loc.x = x;
	loc.y = y;
	loc.z = z;
}

void nbody::draw() {
	//glDisable(GL_TEXTURE_2D);
	GLfloat transform[16] = {
	1,			0,		0,		0,
	0,			1,		0,		0,
	0,			0,		1,		0,
	loc.x,		loc.y,	loc.z,	1};	
	glLoadMatrixf(transform);

	glBegin(GL_POINTS);
	glPointSize(30);
	glColor3ub(255,255,255);
	for (int i=0; i<nodes; i++){
		glVertex3f(pos[i].x,pos[i].y ,pos[i].z);
	}
	glEnd();
}
