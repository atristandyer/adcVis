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
 * drawing operations. Updates the uniforms before use by calling UpdateUniforms()
 *
 * @return 0 if command successfully sent to OpenGL context
 * @return 1 if uniforms have not been set
 */
int GLShader::Use()
{
	UpdateUniforms();
	if (uniformsSet)
	{
		glUseProgram(programID);
		return 0;
	}
	return 1;
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
 * @brief GLShader::IsLoaded Queries object to see if the shader program has been loaded or not
 *
 * The shader being loaded only guarantees that the shader has successfully compiled in the
 * OpenGL context.
 *
 * @return true if shader program has been loaded
 * @return false if shader program has not been loaded
 */
bool GLShader::IsLoaded()
{
	return loaded;
}


/**
 * @brief GLShader::CameraSet Queries the object to see if the camera pointer has been set
 *
 * The camera being set only guarantees that the pointer to the camera object has been set.
 *
 * @return true if the camera has been set
 * @return false if the camera has not been set
 */
bool GLShader::CameraSet()
{
	return cameraSet;
}


/**
 * @brief GLShader::UniformsSet Queries object to see if the shader uniforms have been set
 *
 * If the uniforms are set, the shader is guaranteed to be compiled with the camera set, and
 * is therefore ready to be used.
 *
 * @return true if the uniforms have been set
 * @return false if the uniforms have not been set
 */
bool GLShader::UniformsSet()
{
	return uniformsSet;
}



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

