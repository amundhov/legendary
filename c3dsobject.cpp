#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c3dsobject.h"
#include "chunks.def"
#include "msg.h"

C3dsScene::C3dsScene(std::string fileName) : VboObject(),
    m_colours(NULL),
    m_coords(NULL),
    m_normals(NULL)
{
    if (count == 1)
    {
        VBO_indices=0;
        VBO_size_colours=0;
        VBO_size_coords=0;
        VBO_size_indices=0;
        VBO_size_vertices=0;
        INDEX_SIZE = GL_UNSIGNED_SHORT;

        parseFile(fileName);

        genBO();
    }

}

unsigned char* C3dsScene::getColours()
{
    return m_colours;
}

float* C3dsScene::getCoords()
{
    return m_coords;
}

int* C3dsScene::getIndices()
{
    return m_indices;
}

float* C3dsScene::getVertices()
{
    return m_vertices;
}

float* C3dsScene::getNormals()
{
    return m_normals;
}

void C3dsScene::parseFile(string filename)
{
    C3dsParser parser(filename);

    string currentMesh, currentMaterial, mat;
    uint16_t numFaces;
    map<string, face*>    faces;
    map<string, vec3*> vertices;
    map<string, vec3*> normals;
    map<string, int>      vertCount;
    map<string, int>      faceCount;
    map<string, color>   faceMaterial;
    map<string, color>    colors;

    int totalVertCount = 0;
    int totalFaceCount = 0;

    while ( !parser.eof() ) {
        parser.enterChunk();
        switch ( parser.getChunkId() ){
            case MAIN_CHUNK:
               break;

            case MAIN_VERSION:
               parser.skipChunk();
               break;

            case EDITOR_CHUNK:
               break;

            case OBJECT_BLOCK:
               currentMesh = parser.extractStrData();
               Log("Mesh: %s\n", currentMesh.c_str());
               break;

            case TRIANGULAR_MESH:
                break;

            case VERTICES_LIST:
                vertCount[currentMesh] = parser.extractCount();
                totalVertCount += vertCount[currentMesh];
                vertices[currentMesh] = parser.extractArray<vec3>(vertCount[currentMesh]);
                break;

            case FACES_LIST:
                faceCount[currentMesh] = parser.extractCount();
                totalFaceCount += faceCount[currentMesh];
                faces[currentMesh] = parser.extractArray<face>(faceCount[currentMesh],2);
                break;

            case MATERIAL_BLOCK:
                break;

            case MATERIAL_NAME:
                currentMaterial = parser.extractStrData();
                parser.skipChunk();
                break;

            case DIFFUSE_COLOR:
                break;

            case RGB1:
                colors[currentMaterial] = parser.extractValue<color>();
                parser.skipChunk();
                break;

            case FACES_MATERIAL:
                mat = parser.extractStrData();
                numFaces = parser.extractValue<uint16_t>();
                faceMaterial[currentMesh] = colors[mat];
                parser.skipChunk();
                break;

            default:
                Log("Unkown chunk %04x of length %u\n", parser.getChunkId(), parser.getChunkLength());
                parser.skipChunk();
                break;

        }
    }

    LOG("Finished parsing!");

    VBO_size_vertices = totalFaceCount*sizeof(vec3);
    VBO_size_indices = totalFaceCount*sizeof(face);
    VBO_size_normals = totalVertCount*sizeof(vec3);
    VBO_size_colours = 0;
    VBO_size_coords = 0;
    VBO_indices = totalFaceCount*3;
    m_vertices = new float[VBO_size_vertices];
    m_indices  = new int[VBO_size_indices];

    //for (map<string, int>::iterator it = normals.begin(); it != normals.end(); it++) {
//
    //}

    int offset = 0;
    void *vertDestination = m_vertices;
    void *indexDestination = m_indices;
    for (map<string, int>::iterator it = vertCount.begin(); it != vertCount.end(); it++) {
        int indices = faceCount[it->first]*3;
        indexCounts.push_back(indices);

        memcpy(vertDestination, vertices[it->first], it->second*sizeof(vec3));
        memcpy(indexDestination, faces[it->first], faceCount[it->first]*sizeof(face));
        vertDestination += it->second*sizeof(vec3);
        indexDestination += faceCount[it->first]*sizeof(face);
        vertexOffsets.push_back(offset);
        offset += it->second*sizeof(vec3);
    }

}

void C3dsScene::drawElements() {
    //VboObject::drawElements();
    int indexStart = 0;
    int i=0;
    vector<short int>::iterator it = indexCounts.begin();
    for (i=0 ; it != indexCounts.end(); it++, i++){
        glVertexPointer(3, GL_FLOAT, 0, (GLvoid*)vertexOffsets.at(i));
        glDrawElements(GL_TRIANGLES, *it, INDEX_SIZE, 0);
        Log("Drawing %i vertices, pointer offset %x\n",*it, vertexOffsets.at(i));
        //glDrawRangeElements(GL_TRIANGLES, 0 , *it, *it, INDEX_SIZE, 0);
   }
}

    // int i=0;
    // for (map<string, vec3*>::iterator it = vertices.begin(); it != vertices.end(); it++) {
    //     m_indices[i/3] = i;
    //     m_vertices[i++] = (*it).second->x;
    //     m_vertices[i++] = (*it).second->y;
    //     m_vertices[i++] = (*it).second->z;
    //     printf("%f\n", (*it).second->x);
    // }

    //VBO_size_colours = colors.size();
    //m_colours = new unsigned char[VBO_size_colours * 3];
    //i = 0;
    //for (map<string, color>::iterator it = colors.begin(); it != colors.end(); it++) {
    //    m_colours[i++] = (*it).second.r;
    //    m_colours[i++] = (*it).second.g;
    //    m_colours[i++] = (*it).second.b;
    //}




    /*vec3 *vertex;
    face *cface;
    vec3 normal;
    GLuint list;
    GLfloat color[3];

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.0 };
    for (map<string, vec3*>::iterator it = vertices.begin(); it != vertices.end(); it++) {
        list = glGenLists(1);
        glNewList(list, GL_COMPILE);
        m_callLists.push_back(list);

        vertex = vertices[(*it).first];
        cface = faces[(*it).first];

        for (int i=0; i<faceCount[(*it).first]; i++) {
            normal = vec3::normal(vertex[cface[i].a], vertex[cface[i].b], vertex[cface[i].c]);
            glBegin(GL_TRIANGLES);
            color[0] = faceMaterial[(*it).first].r/255.0f;
            color[1] = faceMaterial[(*it).first].g/255.0f;
            color[2] = faceMaterial[(*it).first].b/255.0f;
            glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
            glNormal3f(normal.x, normal.y, normal.z);
            glVertex3fv((GLfloat*)&vertex[cface[i].a]);
            glVertex3fv((GLfloat*)&vertex[cface[i].b]);
            glVertex3fv((GLfloat*)&vertex[cface[i].c]);
            glEnd();
        }
        glEndList();
    }*/
