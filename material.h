#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>


#define IMAGEOFFSET 0
#define NORMALOFFSET 2
#define SHADOWOFFSET 4


class Material {
public:
    Material();
    virtual ~Material();

    void Bind();

protected:
    void freeTO();
    virtual void genTO() = 0;

    static GLuint TO;
    static unsigned int count;
};

#endif//TEXTURE_H
