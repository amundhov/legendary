#include "material.h"

Material::Material() {}
Material::~Material() {}

void Material::freeTO() {
    glDeleteTextures(1, &TO);
}

void Material::Bind() {
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TO);
}

GLuint Material::TO = 0;
unsigned int Material::count = 0;
