#ifndef DEFAULTSHADER_H
#define DEFAULTSHADER_H


#include "GLShader.h"


/**
 * @brief A basic single color shader
 *
 * DefaultShader is a simple shader that provides a single color for all drawing operations.
 *
 */
class DefaultShader : public GLShader
{
	public:

		DefaultShader();
		void SetUniforms(UniformColors *colors, UniformValues *values);

	protected:

		GLfloat rgba[4];	/**< RGBA color to be used (0.0 - 1.0)*/

		void CompileShader();
		void UpdateUniforms();


};

#endif // DEFAULTSHADER_H
