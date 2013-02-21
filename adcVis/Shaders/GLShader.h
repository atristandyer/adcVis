#ifndef GLSHADER_H
#define GLSHADER_H

#include <map>
#include <string>
#include "../OpenGL/GLCamera.h"


/**
 * @brief A virtual class that defines the generic behavior of a Shader
 *
 * GLShader is an abstract class that defines the generic behavior of all shaders that
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


		/**
		 * @brief GLShader::SetUniforms Sets all of the uniform values of a subclassed GLShader
		 *
		 * This function takes a UniformColors struct and UniformValues struct, which it
		 * uses to update all of the variables that are passed to the shader program
		 * as uniform values. It is up to the programmer to define how the shader will
		 * interpret the values passed in.
		 *
		 * Some general guidelines:
		 * - Passing in 0 for either parameter means all values in that set do not need to be updated
		 * - Fill the structs with generic data first (eg. basic color in Color1, minZ/maxZ in Value1/Value2)
		 * and then fill in with more specialized data
		 * - A value of -1.0 for a color means the color does not need to be updated
		 * - A value of -99999.0 for a generic value means the value does not need to be updated
		 * .
		 *
		 * Note: set the uniformsSet flag to true after successfully reading in all values.
		 *
		 * @param colors A UniformColors struct with updated color values
		 * @param values A UniformValues struct with updated generic values
		 *
		 */
		virtual void SetUniforms(UniformColors *colors, UniformValues *values) = 0;

	protected:

		// Variables common to all shaders
		GLuint		programID;		/**< Integer reference to the compiled program in the OpenGL context */
		GLCamera	*camera;		/**< Pointer to the camera object that is used to retrieve the Model-View-Projection Matrix */
		int		numUniforms;		/**< The number of shader uniforms accessible by the user */

		// Source text
		std::string	vertexShaderSource;	/**< Full source code for the vertex shader */
		std::string	fragmentShaderSource;	/**< Full source code for the fragment shader */

		// Flags
		bool	loaded;		/**< Set to true after successfully setting programID */
		bool	cameraSet;	/**< Set to true when the camera pointer has been set */
		bool	uniformsSet;	/**< Set to true when all user-accessible uniforms have been set to expected values*/

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
		 * Note: You must call glUseProgram(programID) to update the uniforms. This is required
		 * by OpenGL and by the subclassed Shader object as a part of the Use() functionality.
		 *
		 */
		virtual void	UpdateUniforms() = 0;
};

#endif
