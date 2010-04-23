#ifndef __material_h_
#define __material_h_

#include <GL/glew.h>

class CMaterial {
	public: 
		CMaterial(char *filename);
		~CMaterial();
		
		void Bind();
		
	private:
		void genTO();
		void freeTO();
		
		char *texturefile;
	
		static GLuint TO;		
		static unsigned int count;
};

#endif
