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

    float* getVertices();
    float* getNormals();
    int* getIndices();
    unsigned char* getColours();
    float* getCoords();

private:
    void parseFile(string fileName);
    void drawElements();

    float *m_vertices;
    int *m_indices;
    unsigned char *m_colours;
    float *m_coords;
    float *m_normals;

    vector<short int> indexCounts;
    vector<int> vertexOffsets;


};

#endif // C3DS_OBJECT_H
