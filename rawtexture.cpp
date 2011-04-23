#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rawtexture.h"
#include "msg.h"
#include "file.h"

RawTexture::RawTexture(const char *filename) {
    if (!count) {
        m_texturefile = new char[strlen(filename)];
        strcpy(m_texturefile, filename);

        genTO();
    }
    count++;
}

RawTexture::~RawTexture() {
    if (!--count)
        freeTO();
}

void RawTexture::genTO() {
    glGenTextures(1, &TO);
    glBindTexture(GL_TEXTURE_2D, TO);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

#define height 512
#define width 512

    char *tex_buf;
    tex_buf = File::readFile(m_texturefile);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, height, width, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_buf);
    //glGenerateMipmap(GL_TEXTURE_2D);

    delete [] tex_buf;
}

