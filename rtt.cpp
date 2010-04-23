#include "rtt.h"
#include "msg.h"

CRenderToTextureMaterial::CRenderToTextureMaterial() {
	if(!count)
		genTO();
	count++;
}

CRenderToTextureMaterial::~CRenderToTextureMaterial() {
	if(!--count) 
		freeTO();
}

void CRenderToTextureMaterial::genTO() {
	GLuint FBO;
	GLuint RBO;

	Log("Generating texture\n");
	
	glGenTextures(1, &TO);
	glBindTexture(GL_TEXTURE_2D, TO);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 512, 512);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TO, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO);
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		Log("Framebuffer panic!\n");
	
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
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	glDeleteFramebuffers(1, &FBO);
	glDeleteRenderbuffers(1, &RBO);
}

void CRenderToTextureMaterial::freeTO() {
	glDeleteTextures(1, &TO);
}

void CRenderToTextureMaterial::Bind() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, TO);
}

GLuint CRenderToTextureMaterial::TO = 0;
unsigned int CRenderToTextureMaterial::count = 0;
