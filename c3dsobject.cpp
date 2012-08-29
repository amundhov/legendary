#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c3dsobject.h"
#include "chunks.def"
#include "msg.h"

C3dsObject::C3dsObject(std::string fileName) : VboObject(),
    m_colours(NULL),
    m_coords(NULL),
    m_normals(NULL)
{
    if (reference_count == 1)
    {
        IBO_indices=0;
        VBO_size_colours=0;
        VBO_size_coords=0;
        IBO_size_indices=0;
        VBO_size_vertices=0;
        INDEX_SIZE = GL_UNSIGNED_SHORT;

        parseFile(fileName);

        VboObject::genBO();
    }

}

unsigned char* C3dsObject::getColours()
{
    return m_colours;
}

float* C3dsObject::getCoords()
{
    return m_coords;
}

unsigned short int* C3dsObject::getIndices()
{
    return (C3dsParser::index*)m_indices;
}

vec3* C3dsObject::getVertices()
{
    return m_vertices;
}

vec3* C3dsObject::getNormals()
{
    return m_normals;
}

void C3dsObject::parseFile(string filename)
{
    C3dsParser parser(filename);

    string currentMesh, currentMaterial, mat;
    uint16_t numFaces;
    map<string, C3dsParser::face*>    faces;
    map<string, vec3*> vertices;
    map<string, vec3*> normals;
    map<string, int>      vertCount;
    map<string, int>      faceCount;
    map<string, C3dsParser::color>   faceMaterial;
    map<string, C3dsParser::color>    colors;

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
               LOG("Mesh:" << currentMesh.c_str());
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
                faces[currentMesh] = parser.extractArray<C3dsParser::face>(faceCount[currentMesh],2);
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
                colors[currentMaterial] = parser.extractValue<C3dsParser::color>();
                parser.skipChunk();
                break;

            case FACES_MATERIAL:
                mat = parser.extractStrData();
                numFaces = parser.extractValue<uint16_t>();
                LOG("Faces: " << numFaces);
                faceMaterial[currentMesh] = colors[mat];
                parser.skipChunk();
                break;

            default:
                LOG("Unkown chunk " << parser.getChunkId() << " of length " << parser.getChunkLength());
                parser.skipChunk();
                break;

        }
    }

    LOG("Finished parsing!");

    VBO_size_vertices = totalVertCount*sizeof(vec3);
    IBO_size_indices = totalFaceCount*sizeof(C3dsParser::face);
    //VBO_size_normals = totalVertCount*sizeof(vec3);
    VBO_size_normals = 0;
    VBO_size_colours = 0;
    VBO_size_coords = 0;
    IBO_indices = totalFaceCount*3;
    m_vertices = new vec3[totalFaceCount];
    m_indices  = new C3dsParser::face [totalFaceCount];

    LOG("Total face count: " << totalFaceCount << "\nTotal vertex count: " << totalVertCount);

    vec3 *vertexOffset = 0;
    C3dsParser::face *indexOffset = 0;
    vec3 *vertDestination = m_vertices;
    C3dsParser::face *indexDestination = m_indices;
    for (map<string, int>::iterator it = vertCount.begin(); it != vertCount.end(); it++) {
        indexCounts.push_back(faceCount[it->first]*3);

        memcpy(vertDestination, vertices[it->first], it->second*sizeof(vec3));
        memcpy(indexDestination, faces[it->first], faceCount[it->first]*sizeof(C3dsParser::face));

        vertDestination += it->second;
        indexDestination += faceCount[it->first];

        vertexOffsets.push_back(vertexOffset);
        vertexOffset += it->second;

        indexOffsets.push_back(indexOffset);
        indexOffset += faceCount[it->first];
    }

}

void C3dsObject::drawElements() {
    //VboObject::drawElements();
    vector<unsigned short int>::iterator it = indexCounts.begin();
    for (int i=0 ; it != indexCounts.end(); it++, i++){
        glVertexPointer(3, GL_FLOAT, 0, (GLvoid*)vertexOffsets.at(i));
        glDrawElements(GL_TRIANGLES, *it, INDEX_SIZE, indexOffsets.at(i));
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
