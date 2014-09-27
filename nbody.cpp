#include <cstdlib>
#include <fstream>
#include <cmath>
#include "msg.h"
#include "nbody.h"

nbody::nbody(int nodes, int edgenum) {
	randSeed = 1;
	locate(0,0,0);
	this->nodes = nodes;
    this->edgenum = edgenum;
	pos = new vec3[nodes];
	vel = new vec3[nodes];
	acc = new vec3[nodes];
	accT = new vec3[nodes];
    edges = new edge[edgenum];
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

static float t = 0;
void nbody::tick(){

    for (int i=0; i<nodes; i++) {
        vec3 v = pos[i];
        vec3 force = {0, 0, 0};
        force = -1 * v / (fabs(v.x) + fabs(v.y) + fabs(v.z));

        for (int j=0; j<nodes; j++) {
            if (i == j) continue;

            vec3 dist = v - pos[j];

            force += 5 * dist / (dist.x * dist.x + dist.y * dist.y + dist.z * dist.z);
        }
        for (int j=0; j<edgenum; j++) {
            edge e = edges[j];
            if (e.node1 != i && e.node2 != i) continue;

            vec3 u;
            if (e.node1 == i) u = pos[e.node2];
            else u = pos[e.node1];
            vec3 dist = u - v;
            force += dist * 0.06;
        }

        pos[i] += force;
    }

    t += 0.1;
    if (t > 360) t = 0;

    if (rand() % 100 > 98) {
        int cnt = 5;
        for (int j=0; j < cnt; j++) {
            int i = rand() % nodes;
            float r = (sfrand()+1.0f)/2;
            float phi = sfrand() * M_PI;
            Log("R: %f PHI: %f\n", r,phi);
            pos[i].x = r*cos(phi);
            pos[i].y = r*sin(phi);
            pos[i].z = -1.0f;
        }
    }
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
	}
    for (int i=0; i<edgenum; i++) {
        edges[i].node1 = rand() % nodes;
        edges[i].node2 = rand() % nodes;
    }
}

void nbody::locate(float x, float y, float z) {
	loc.x = x;
	loc.y = y;
	loc.z = z;
}

void nbody::draw() {
	GLfloat transform[16] = {
	1,			0,		0,		0,
	0,			1,		0,		0,
	0,			0,		1,		0,
	loc.x,		loc.y,	loc.z,	1};	
	glLoadMatrixf(transform);

    glTranslatef(0, 0, -40);
    glRotatef(t, 1, 1, 1);


	glBegin(GL_POINTS);
	for (int i=0; i<nodes; i++){
		glVertex3f(pos[i].x,pos[i].y, pos[i].z);
	}
	glEnd();
	glBegin(GL_LINES);
	for (int i=0; i<edgenum; i++){
        int node1 = edges[i].node1;
        int node2 = edges[i].node2;
		glVertex3f(pos[node1].x,pos[node1].y ,pos[node1].z);
		glVertex3f(pos[node2].x,pos[node2].y ,pos[node2].z);
	}
	glEnd();
}
