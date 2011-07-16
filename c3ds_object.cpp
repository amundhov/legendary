#include <stdio.h>
#include <stdlib.h>
#include "c3ds_object.h"

#include "chunks.def"
#include "msg.h"

c3ds_scene::c3ds_scene(std::string fileName) : vbo_object(),
    m_colours(0),
    m_coords(0)
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

unsigned char* c3ds_scene::getColours()
{
    return m_colours;
}

float* c3ds_scene::getCoords()
{
    return m_coords;
}

int* c3ds_scene::getIndices()
{
    return m_indices;
}

float* c3ds_scene::getVertices()
{
    return m_vertices;
}

void c3ds_scene::parseFile(string filename)
{
    C3dsParser parser(filename);

    string currentMesh, currentMaterial, mat;
    uint16_t numFaces;
    map<string, face*>    faces;
    map<string, vec3*> vertices;
    map<string, int>      vertCount;
    map<string, int>      faceCount;
    map<string, color>   faceMaterial;
    map<string, color>    colors;

    /* Do a speed run accumulating counts */

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
               break;

            case TRIANGULAR_MESH:
                break;

            case VERTICES_LIST:
                vertCount[currentMesh] = parser.extractCount();
                vertices[currentMesh] = parser.extractArray<vec3>(vertCount[currentMesh]);
                break;

            case FACES_LIST:
                faceCount[currentMesh] = parser.extractCount();
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
                printf("Unkown chunk %04x of length %u\n", parser.getChunkId(), parser.getChunkLength());
                parser.skipChunk();
                break;

        }
    }

    string foo = string("fkLogo_None");
    VBO_size_vertices = vertCount[foo]*sizeof(vec3);
    VBO_size_indices = faceCount[foo]*sizeof(face);
    VBO_size_colours = 0;
    VBO_size_coords = 0;
    VBO_indices = faceCount[foo]*3;
    m_vertices = (float*)vertices[foo];
    m_indices =  (int*)faces[foo];

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



    printf("Finished parsing!\n");

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
}
