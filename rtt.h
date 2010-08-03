#ifndef __RTT_H_
#define __RTT_H_

#include <GL/glew.h>
#include "base_texture.h"

class CRenderToTextureMaterial : public CBaseTexture {
public:
    CRenderToTextureMaterial();
    ~CRenderToTextureMaterial();

    void Bind();

protected:
    virtual void genTO();
};

#endif
