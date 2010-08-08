#include "c3ds_object.h"

#include "chunks.def"
#include "msg.h"

c3ds_object::c3ds_object(std::string fileName)
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

unsigned char* c3ds_object::getColours()
{
    return colours;
}

float* c3ds_object::getCoords()
{
    return coords;
}

int* c3ds_object::getIndices()
{
    return (int*)indices;
}

float* c3ds_object::getVertices()
{
    return vertices;
}

void c3ds_object::parseFile(string fileName)
{

    C3dsParser *parser = new C3dsParser(fileName);

    int currCount;
    string currentMesh, currentMaterial;
    //map<string,int> vertCount;
    //map<string,int> faceCount;

    while ( !parser->eof() ) {
        parser->enterChunk();
        switch ( parser->getChunkId() ){
        case MAIN_CHUNK:
            break;
        case EDITOR_CHUNK:
            break;
        case OBJECT_BLOCK:
            parser->skipStrData();
            break;
            case TRIANGULAR_MESH:
                break;
                case VERTICES_LIST:
                    VBO_size_vertices += parser->extractCount()*sizeof(vec3);
                    parser->skipChunk();
                    break;
                case FACES_LIST:
                    VBO_indices += parser->extractCount()*3;
                    parser->skipChunk();
                    break;

        default:
            parser->skipChunk();
            break;
        }
    }

    vertices = new float[VBO_size_vertices/sizeof(float)];
    indices = new uint16_t[VBO_indices];
    VBO_size_indices = VBO_indices*sizeof(int);

    vec3 *vertexPointer = (vec3*)vertices;
    uint16_t *indexPointer = indices;

    parser->rewind();

    while ( !parser->eof() ) {
        parser->enterChunk();
        switch ( parser->getChunkId() ){
        case MAIN_CHUNK:
            Log("Found main identifier %04x, length is %u bytes\n",parser->getChunkId(), parser->getChunkLength());
            break;

        case MAIN_VERSION:
            Log("3DS version: %u\n", parser->extractValue<unsigned short>()  );
            parser->skipChunk();
            break;

        case EDITOR_CHUNK:
            Log("Found editor chunk length %u\n",parser->getChunkId(), parser->getChunkLength());
            break;

        case OBJECT_BLOCK:
            currentMesh = parser->extractStrData();
            //meshNames.push_back(currentMesh);
            //Log("Object block, name %s\n", currentMesh.c_str());
            break;

            case TRIANGULAR_MESH:
                Log("   Triangular mesh\n");
                break;

                case VERTICES_LIST:
                    currCount = parser->extractCount();
                    //vertexCount.push_back(parser->extractCount());
                    //Log(" found %u vertices\n", vertexCount.back());
                    parser->extractArray<float>(currCount*3,(float*)vertexPointer);
                    vertexPointer += currCount*3;
                    parser->skipChunk();
                    break;

                case FACES_LIST:
                    currCount = parser->extractCount();
                    //VBO_indices += faceCount.back()*3;
                    //Log(" found %u faces\n", faceCount.back());
                    Log("Offset: %x\n", parser->getChunkOffset());
                    //parser->extractArray<face>(currCount, (face*)indexPointer, 2);
                    parser->extractArray<uint16_t>(currCount*3,indexPointer,2);
                    indexPointer += currCount*3;
                    parser->skipChunk();
                    break;

                    case FACES_MATERIAL:
                       Log(parser->extractStrData());
                       Log("Faces material count: %u\n",parser->extractValue<uint16_t>());
                       parser->skipChunk();
                       //faceMaterial[currentMesh] = new color[numFaces];
                       //Log("Colored faces: %hu\n", numFaces);
                       //for (uint16_t i=0; i<numFaces; i++) {
                       //    faceMaterial[currentMesh][i] = colors[mat];
                       //}
                       break;

        case MATERIAL_BLOCK:
            Log("Material block length %u\n", parser->getChunkLength());
            break;

            case MATERIAL_NAME:
                currentMaterial = parser->extractStrData();
                Log("Material name: %s\n", currentMaterial.c_str());
                parser->skipChunk();
                break;

            case DIFFUSE_COLOR:
                break;

                case RGB1:
                    //colors[currentMaterial] = parser->extractValue<color>();
                    //Log("Diffuse color: r:%i, g:%i, b:%i\n", colors[currentMaterial]);
                    parser->skipChunk();
                    break;

        default:
            Log("Unkown chunk %04x of length %u\n", parser->getChunkId(), parser->getChunkLength());
            parser->skipChunk();
            break;
        }
    }

    Log("Finished parsing!\n");

    delete parser;
}
