#ifndef GLSHADER_H
#define GLSHADER_H

#include <map>
#include <string>
#include "../OpenGL/GLCamera.h"


/**
 * @brief A virtual class that defines the generic behavior of a Shader
 */
class GLShader
{
	public:

		// Constructor/Destructor
		GLShader();
		~GLShader();

		// Public functions common to all shaders
		int	Use();
		void	SetCamera(GLCamera *newCam);
		bool	IsLoaded();
		bool	CameraSet();
		bool	UniformsSet();

		// Public Virtual Functions (must be implemented by a subclass)
		virtual int	SetUniforms(float *uniforms) = 0;

	protected:

		// Variables common to all shaders
		GLuint		programID;
		GLCamera	*camera;

		// Source text
		std::string	vertexShaderSource;
		std::string	fragmentShaderSource;

		// Flags
		bool	loaded;
		bool	cameraSet;
		bool	uniformsSet;

		// Protected Functions
		GLuint	CompileShaderPart(std::string source, GLenum shaderType);

		// Protected Virtual Funtions (must be implemeneted by a subclass)
		virtual void	UpdateUniforms() = 0;
};

#endif
