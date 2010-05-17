#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "texture.h"
#include "msg.h"

CTexture::CTexture(char *filename) {
	if(!count) {
		int len = strlen(filename);
		texturefile = (char*)malloc(len);
		strcpy(texturefile, filename);
	
		Log("CTexture :: Filename: %s\n", texturefile);
		genTO();
	}
	count++;
}

CTexture::~CTexture() {
	if(!--count) 
		freeTO();
	if(texturefile)
		free(texturefile);
}

void CTexture::genTO() {
	glGenTextures(1, &TO);
	glBindTexture(GL_TEXTURE_2D, TO);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	#define height 512
	#define width 512
	
	FILE *tex_file;	
	char *tex_buf;
	tex_buf = new char[height*width*3];
	
	if(!(tex_file = fopen(texturefile, "r"))) Log("fopen fail.\n");
	fread(tex_buf, height*width*3, 1, tex_file);
	fclose(tex_file);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, height, width, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_buf);
	//glGenerateMipmap(GL_TEXTURE_2D);
	
	free(tex_buf);
}
