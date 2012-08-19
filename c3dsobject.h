#ifndef C3DS_OBJECT_H
#define C3DS_OBJECT_H

#include "vboobject.h"

#include "c3dsparser.h"

#include <stdio.h>
#include <vector>
#include <map>

using std::string;

class C3dsScene : public VboObject
{
public:
    C3dsScene(string fileName);

    vec3* getVertices();
    vec3* getNormals();
    unsigned short int* getIndices();
    unsigned char* getColours();
    float* getCoords();

private:
    void parseFile(string fileName);
    void drawElements();

    vec3 *m_vertices;
    C3dsParser::face *m_indices;
    unsigned char *m_colours;
    float *m_coords;
    vec3 *m_normals;

    vector<C3dsParser::index> indexCounts;
    vector<GLvoid*> indexOffsets;
    vector<GLvoid*> vertexOffsets;


};

#endif // C3DS_OBJECT_H
