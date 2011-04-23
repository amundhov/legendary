#ifndef __RTT_H_
#define __RTT_H_

#include <GL/glew.h>
#include "texture.h"

class CRenderToTextureMaterial : public Texture {
public:
    CRenderToTextureMaterial();
    ~CRenderToTextureMaterial();

    void Bind();

protected:
    virtual void genTO();
};

#endif
