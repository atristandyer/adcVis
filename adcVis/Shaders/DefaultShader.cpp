#include "DefaultShader.h"


/**
 * @brief DefaultShader::DefaultShader Constructor initializes the color to white
 *
 * The constructor initializes the color to white (rgba = {1.0, 1.0, 1.0, 1.0}),
 * sets the number of shader uniforms available to the user to 4,  hard-codes
 * the vertex and fragment shader source, and finally attempts to compile the
 * shader program.
 *
 */
DefaultShader::DefaultShader()
{
	rgba[0] = 1.0;
	rgba[1] = 1.0;
	rgba[2] = 1.0;
	rgba[3] = 1.0;
	numUniforms = 4;

	uniformsSet = true;

	vertexShaderSource = "";
	fragmentShaderSource ="";
}


/**
 * @brief DefaultShader::SetUniforms Sets the color to be used by the shader.
 *
 * This function is called by the user in order to change the color used by the shader
 * in all subsequent OpenGL drawing operations.
 *
 * @param size The number of values in the uniforms array. Must be equal to 4.
 * @param uniforms Must be an array of 4 floats.
 */
void DefaultShader::SetUniforms(int size, float *uniforms)
{
	if (size == numUniforms)
	{
		rgba[0] = uniforms[0];
		rgba[1] = uniforms[1];
		rgba[2] = uniforms[2];
		rgba[3] = uniforms[3];
		uniformsSet = true;
	} else {
		uniformsSet = false;
	}
}


/**
 * @brief DefaultShader::CompileShader Attempts to compile and link the shader program.
 *
 * This shader only requires a vertex shader and a fragment shader. CompileShader attempts
 * to compile and link the shader program from the hard-coded source. Successful compilation
 * results in a non-zero value for programID and sets loaded equal to true.
 *
 */
void DefaultShader::CompileShader()
{
	GLuint vertexShaderID = CompileShaderPart(vertexShaderSource, GL_VERTEX_SHADER);
	GLuint fragmentShaderID = CompileShaderPart(fragmentShaderSource, GL_FRAGMENT_SHADER);

	if (vertexShaderID && fragmentShaderID)
	{
		programID = glCreateProgram();
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, fragmentShaderID);
		glLinkProgram(programID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);

		GLint result;
		glGetProgramiv(programID, GL_LINK_STATUS, &result);
		if (result == GL_TRUE)
			loaded = true;
		else
			loaded = false;

	}
}


/**
 * @brief DefaultShader::UpdateUniforms Transfers all shader uniform values to the
 * shader object in the OpenGL context.
 *
 * This function transers the Model-View-Matrix and the color to the shader object
 * in the OpenGL context, only if the shader is in full working order.
 *
 */
void DefaultShader::UpdateUniforms()
{
	if (uniformsSet && loaded && cameraSet)
	{
		glUseProgram(programID);

		GLint MVPUniform = glGetUniformLocation(programID, "MVPMatrix");
		GLint ColorUniform = glGetUniformLocation(programID, "ColorVector");

		glUniformMatrix4fv(MVPUniform, 1, GL_FALSE, camera->MVPMatrix.m);
		glUniform4fv(ColorUniform, 1, rgba);
	}
}
