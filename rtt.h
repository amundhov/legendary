#ifndef __RTT_H_
#define __RTT_H_

#include <GL/glew.h>
#include "material.h"

class CRenderToTextureMaterial : public Material {
public:
    CRenderToTextureMaterial();
    ~CRenderToTextureMaterial();

    void Bind();

protected:
    virtual void genTO();
};

#endif
