#include "texture.h"

Texture::Texture() {}
Texture::~Texture() {}

void Texture::freeTO() {
    glDeleteTextures(1, &TO);
}

void Texture::Bind() {
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TO);
}

GLuint Texture::TO = 0;
unsigned int Texture::count = 0;
