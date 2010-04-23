#ifndef __RTT_H_
#define __RTT_H_

#include <GL/glew.h>

class CRenderToTextureMaterial {
	public:
		CRenderToTextureMaterial();
		~CRenderToTextureMaterial();
		
		void Bind();
		
	private:
		void genTO();
		void freeTO();
		
		static GLuint TO;		
		static unsigned int count;
};

#endif
