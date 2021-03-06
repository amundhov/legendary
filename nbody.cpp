#include <cstdlib>
#include <fstream>
#include <cmath>
#include "msg.h"
#include "nbody.h"

nbody::nbody(int nodes) {
	randSeed = 1;
	locate(0,0,0);
	//glEnable(GL_POINT_SMOOTH);
	this->nodes = nodes;
	pos = new vec3[nodes];
	vel = new vec3[nodes];
	acc = new vec3[nodes];
	accT = new vec3[nodes];
	reset();
	Log("Nbody allocated");
}

nbody::~nbody() {
	delete[] pos;
	delete[] vel;

}

float nbody::sfrand(void){
    unsigned int a;
    randSeed *= 16807;
    a = (randSeed&0x007fffff) | 0x40000000; // fix exponent to 128
    return( *((float*)&a) - 3.0f );       // float [-1,1]
}

void nbody::tick(){

	vec3 accTdt;

	for (int i=0; i<nodes; i++){
		pos[i].x += dt * vel[i].x + 2.0f*accT[i].x*dt*dt/3.0f - acc[i].x *dt*dt/6.0f;
		pos[i].y += dt * vel[i].y + 2.0f*accT[i].y*dt*dt/3.0f - acc[i].y *dt*dt/6.0f;
		pos[i].z += dt * vel[i].z + 2.0f*accT[i].z*dt*dt/3.0f - acc[i].z *dt*dt/6.0f;
	}
	for (int i=0; i<nodes; i++){
		accTdt = {0,0,0};
		accel(i,accTdt);
		vel[i].x += accTdt.x*dt/3.0f + 5.0f*accT[i].x*dt/6.0f - acc[i].x*dt/6.0f;
		vel[i].y += accTdt.y*dt/3.0f + 5.0f*accT[i].y*dt/6.0f - acc[i].y*dt/6.0f;
		vel[i].z += accTdt.z*dt/3.0f + 5.0f*accT[i].z*dt/6.0f - acc[i].z*dt/6.0f;
		//vel[i] += accTdt*dt/3.0f + 5.0f*accT[i]*dt/6.0f - acc[i]*dt/6.0f;
		acc[i] = accT[i];
		accT[i] = accTdt;
	}
}

inline void nbody::accel(int i, vec3 &acc){
	vec3 origo = {0,0,-1};
	selfGravitation(i,acc);
	acc += 2000*force(pos[i],origo);
}

inline void nbody::selfGravitation(int i, vec3 &acc){
	for ( int j=0; j<nodes; j++){
		acc += 100*force(pos[i],pos[j]);
	}
}

inline vec3 nbody::force(vec3 &a, vec3 &b){
	vec3 acc = {0,0,0};
	float dx = b.x - a.x;
	float dy = b.y - a.y;
	float dz = b.z - a.z;
	float len2x = pow(dx,2);
	float len2y = pow(dy,2);
	float len2z = pow(dz,2);
	float invlen = 1/(pow(len2x+len2y+len2z,1.5f)+1E-6);
	acc.x += dx*invlen;
	acc.y += dy*invlen;
	acc.z += dz*invlen;
	return acc;
}

void nbody::reset(){
	for (int i=0;i<15;i++) sfrand();
	for ( int i=0; i<nodes; i++){
		float r = (sfrand()+1.0f)/2;
		float phi = sfrand() * M_PI;
		Log("R: %f PHI: %f\n", r,phi);
		pos[i].x = r*cos(phi);
		pos[i].y = r*sin(phi);
		pos[i].z = -1.0f;
		vel[i].x = -10.0f*sin(phi)/(r+1E-8)-1.0*cos(phi)*(sfrand()+1);
		vel[i].y = 10.0f*cos(phi)/(r+1E-8)-1.0*sin(phi)*(sfrand()+1);
		vel[i].z =0;
		acc[i].x =0;
		acc[i].y =0;
		acc[i].z =0;
		accT[i].x = 0;
		accT[i].y = 0;
		accT[i].z = 0;
	}
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
