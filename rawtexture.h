#ifndef RAWTEXTURE_H
#define RAWTEXTURE_H

#include <GL/glew.h>
#include "texture.h"
#include <string>

class RawTexture : public Texture {
public:
    RawTexture(const char *filename);
    ~RawTexture();

    void Bind();

protected:
    void genTO();

    char *m_texturefile;
};

#endif//RAWTEXTURE_H
