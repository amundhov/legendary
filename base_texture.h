#ifndef __material_h_
#define __material_h_

#include <GL/glew.h>

class CBaseTexture {
public:
    CBaseTexture();
    ~CBaseTexture();

    void Bind();

protected:
    void freeTO();
    virtual void genTO() = 0;

    static GLuint TO;
    static unsigned int count;
};

#endif
