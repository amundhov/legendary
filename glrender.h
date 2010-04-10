#ifndef __glRender_h_
#define __glRender_h_

#include <gl/glew.h>

class glRender
{
	public:
		glRender();
		~glRender();
		
		void DrawFrame();
		
		void SetViewport(int x, int y);
		void SetFrustum();
		
		void ToggleFrame();
		
		int getResX()		{ return xRes; };
		int getResY()		{ return yRes; };
		
	private:
		bool		fill;				//Filled triangles? (For wireframe mode feature)
		
		int			xRes, yRes;
		float		xPos, yPos, zPos;
		
		float		zNear, zFar;
		float		fov;
};

#endif
