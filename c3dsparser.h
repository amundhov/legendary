#ifndef C3DSPARSER_H
#define C3DSPARSER_H
#include <stdint.h>
#include <string>
#include <stdio.h>

using namespace std;

typedef struct { uint16_t a,b,c; } face;
typedef struct { uint8_t r,g,b; } color;
typedef struct { color diffuse,specular; } material;

typedef struct __attribute__ ((__packed__)) chunkHeader {
        unsigned short chunkId;
        unsigned int length;
        long int offset;
} chunkHeader;

class C3dsParser {
public:
        //C3dsParser(void);
        C3dsParser(string filename);
        ~C3dsParser(void);

        /* ChunkID	   2 bytes
         * ChunkLength     4 bytes
         * 	Data 	   m bytes
         * 	Sub chunks n bytes
         */

        // Read and skip past header 6 bytes
        void  enterChunk(void);
        // Skip the whole current chunk, we're at end of header ( n+m-6 )
        void skipChunk(void);
        unsigned short getChunkId(void);
        unsigned int getChunkLength(void);
    long int getChunkOffset(void);
        // Skip ahead past null-byte terminating string
        void skipStrData(void);
        // Determine length of string at current offset
        unsigned int getStrDataLength(void);
        // Get strData and skip past
        char*  extractStrData(void);
        bool loadFile(string filename);
        bool eof(void);

        inline void skip(long int skip){
                fseek(m_file, skip, SEEK_CUR);
        }

        inline unsigned int extractCount(){
            uint16_t ret;
                fread(&ret, sizeof(ret), 1, m_file);
                return ret;
        }

        template <typename T> T* extractArray( unsigned int count, unsigned int tailSkip = 0 ){
                T* ret = new T[count];
                if ( tailSkip == 0 ){
                        fread(ret, sizeof(T), count, m_file);
                }
                else {
                        for ( int i=0; i<count; i++ ){
                                fread(&ret[i], sizeof(T), 1, m_file);
                                skip(tailSkip);
                        }
                }
                return ret;
        }

        template <typename T> T extractValue(){
                T ret;
                fread(&ret, sizeof(T), 1, m_file);
                return ret;
        }

private:
        chunkHeader m_currentHeader;
        FILE *m_file;
        long int m_fileLength;
};

#endif//C3DSPARSER_H
