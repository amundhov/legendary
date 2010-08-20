#ifndef __texture_h_
#define __texture_h_

#include <GL/glew.h>
#include "base_texture.h"

class CTexture : public CBaseTexture {
public:
    CTexture(const char *filename);
    ~CTexture();

    void Bind();

protected:
    void genTO();

    char *texturefile;
};

#endif
