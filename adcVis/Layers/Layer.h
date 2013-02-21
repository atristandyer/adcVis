#ifndef LAYER_H
#define LAYER_H

#include "adcData.h"
#include "../Shaders/GLShader.h"

class Layer
{
	public:
		Layer();

		void	Draw();
		void	Update();
		void	Update(int);

	protected:

		// Flags
		bool	glLoaded;

		// OpenGL Variables
		GLuint		VAOId;
		GLuint		VBOId;
		GLuint		IBOId;
		GLShader	*outlineShader;
		GLShader	*fillShader;

		// Protected Functions
		virtual void	LoadDataToGPU() = 0;

};

#endif // LAYER_H
