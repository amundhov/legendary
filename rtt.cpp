#include "rtt.h"
#include "msg.h"

RenderToTextureMaterial::RenderToTextureMaterial() {
    if (!count)
        genTO();
    count++;
}

RenderToTextureMaterial::~RenderToTextureMaterial() {
    if (!--count)
        freeTO();
}

void RenderToTextureMaterial::genTO() {
    GLuint FBO;
    GLuint RBO;

    LOG("Generating texture");

    glGenTextures(1, &TO);
    glBindTexture(GL_TEXTURE_2D, TO);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenRenderbuffersEXT(1, &RBO);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, RBO);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, 512, 512);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

    glGenFramebuffersEXT(1, &FBO);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBO);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, TO, 0);
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, RBO);
    if (glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) != GL_FRAMEBUFFER_COMPLETE_EXT)
        LOG("Framebuffer panic!\n");

    glPushAttrib(GL_VIEWPORT_BIT);
    glViewport(0, 0, 512, 512);
    glClearColor(1.0,1.0,1.0,0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3b(0xff, 0xaa, 0x00);
    glVertex3f(0.0, 0.8, 0.0);
    glVertex3f(-0.8, -0.8, 0.0);
    glVertex3f(0.8, -0.8, 0.0);
    glEnd();
    glClearColor(0.0,0.0,0.0,0.0f);
    glPopAttrib();
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

    glDeleteFramebuffersEXT(1, &FBO);
    glDeleteRenderbuffersEXT(1, &RBO);
}
