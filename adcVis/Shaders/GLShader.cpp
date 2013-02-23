#include "GLShader.h"

/**
 * @brief GLShader::GLShader Constructor initializes all variables to default values
 */
GLShader::GLShader()
{
	programID = 0;
	camera = 0;

	vertexShaderSource = "";
	fragmentShaderSource = "";

	loaded = false;
	uniformsSet = false;
	cameraSet = false;
}


/**
 * @brief GLShader::~GLShader Deconstructor that deletes the shader program from the OpenGL context
 */
GLShader::~GLShader()
{
	if (loaded)
	{
		glUseProgram(0);
		glDeleteProgram(programID);
	}
}


/**
 * @brief GLShader::Use Tells the OpenGL context to use this shader program
 *
 * Tells the OpenGL context to use this shader program for all subsequent
 * drawing operations.
 *
 * @return 0 if command successfully sent to OpenGL context
 * @return 1 if uniforms have not been set
 * @return 2 if the shader has not been successfully compiled
 * @return 3 if the camera object has not been set
 */
int GLShader::Use()
{
	if (cameraSet)
		if (loaded)
			if (uniformsSet)
			{
				UpdateUniforms();
				return 0;
			}
			else
				return 1;
		else
			return 2;
	else
		return 3;
}


/**
 * @brief GLShader::SetCamera Sets the camera to be used for subsequent use of this shader
 * @param newCam A pointer to the new Camera to be used
 *
 * Sets the camera to be used to subsequent use of this shader. The shader program uses the
 * Model-View-Projection Matrix provided by the camera to perform a transformation on
 * every Node in the scene. Updates the uniforms after setting the shader's camera pointer by
 * calling UpdateUniforms().
 *
 * Note: The shader does not take ownership of the camera object
 *
 */
void GLShader::SetCamera(GLCamera *newCam)
{
	if (newCam != 0)
	{
		camera = newCam;
		cameraSet = true;
		UpdateUniforms();
	}
}


/**
 * @brief GLShader::CompileShaderPart
 *
 * This function will be used by the virtual CompileShader() function to compile the various shader
 * programs (eg. vertex shader, fragment shader, etc.) in the OpenGL context.
 *
 * @param source Standard string containing the full source code for the shader
 *
 * @param shaderType Specifies the type of shader to be created. Must be one of GL_VERTEX_SHADER,
 * GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, or GL_FRAGMENT_SHADER.
 *
 * @return An unsigned integer value that can be used to reference the compiled shader in the
 * OpenGL context
 */
GLuint GLShader::CompileShaderPart(std::string source, GLenum shaderType)
{
	const char *src = source.data();
	GLuint shaderID = glCreateShader(shaderType);

	if (shaderID != 0)
	{
		glShaderSource(shaderID, 1, &src, NULL);
		glCompileShader(shaderID);

		GLint compileResult;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileResult);
		if (compileResult != GL_TRUE)
		{
			DEBUG("Error Compiling Shader");
			return 0;
		} else {
			return shaderID;
		}
	} else {
		DEBUG("Error Creating Shader");
		return 0;
	}
}

