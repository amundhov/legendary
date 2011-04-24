#ifndef __RTT_H_
#define __RTT_H_

#include <GL/glew.h>
#include "material.h"

class RenderToTextureMaterial : public Material {
public:
    RenderToTextureMaterial();
    ~RenderToTextureMaterial();

    void Bind();

protected:
    virtual void genTO();
};

#endif
