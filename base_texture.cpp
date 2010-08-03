#include "base_texture.h"

CBaseTexture::CBaseTexture() {}
CBaseTexture::~CBaseTexture() {}

void CBaseTexture::freeTO() {
    glDeleteTextures(1, &TO);
}

void CBaseTexture::Bind() {
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TO);
}

GLuint CBaseTexture::TO = 0;
unsigned int CBaseTexture::count = 0;
