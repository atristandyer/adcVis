#ifndef GLSHADER_H
#define GLSHADER_H

#include <map>
#include <string>
#include "../OpenGL/GLCamera.h"


/**
 * @brief A virtual class that defines the generic behavior of a Shader
 *
 * GLShader is a virtual class that defines the generic behavior of all shaders that
 * can be used in the Adcirc Visualization Tool. In order to create a shader that
 * can be used in the program, you must subclass GLShader and define (at a minimum)
 * the SetUniforms(), CompileShader() and UpdateUniforms() functions.
 *
 * Shader source can either be provided by a custom function or hard coded into the subclassed
 * shader.
 *
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


		/**
		 * @brief GLShader::SetUniforms Sets all of the uniform values of a subclassed GLShader
		 *
		 * This function takes a list of floating point values and copies them into
		 * the appropriate variables (the shader uniforms) of the subclassed shader.
		 * It is up to the programmer to define the order of the values for the
		 * particular shader they are creating.
		 *
		 *
		 * Note: enforce loaded == true and cameraSet == true before reading values.
		 *
		 * Note: set flag the flag uniformsSet = true after successfully reading in all values.
		 *
		 * @param size The number of values in the uniforms array
		 * @param uniforms An array of uniform values
		 *
		 */
		virtual void SetUniforms(int size, float *uniforms) = 0;

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

		/**
		 * @brief GLShader::CompileShader Compiles the full shader program
		 *
		 * This function, defined in a subclass of GLShader, compiles all parts of the shader
		 * program for use in the OpenGL context. Upon completion of compiling/linking, the
		 * programID value should be set.
		 *
		 */
		virtual void	CompileShader() = 0;

		/**
		 * @brief GLShader::UpdateUniforms Updates the shader uniforms in the OpenGL context
		 *
		 * This function, defined in a subclass of GLShader, transfers all appropriate values
		 * from the shader object to the shader program in the OpenGL context using the
		 * glGetUniformLocation() and glUniform*() functions.
		 *
		 */
		virtual void	UpdateUniforms() = 0;
};

#endif
