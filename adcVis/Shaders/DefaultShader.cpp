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

	vertexShaderSource = "#version 330\n"
			     "layout(location=0) in vec4 in_Position;"
			     "out vec4 ex_Color;"
			     "uniform mat4 MVPMatrix;"
			     "uniform vec4 ColorVector;"
			     "void main(void)"
			     "{"
				     "gl_Position = MVPMatrix*in_Position;"
				     "ex_Color = ColorVector;"
			     "}";

	fragmentShaderSource = "#version 330\n"
			       "in vec4 ex_Color;"
			       "out vec4 out_Color;"
			       "void main(void)"
			       "{"
				       "out_Color = ex_Color;"
			       "}";
}


/**
 * @brief DefaultShader::SetUniforms Sets the color to be used by the shader.
 *
 * This function is called by the user in order to change the color used by the shader
 * in all subsequent OpenGL drawing operations.
 *
 * Only Color1 in the UniformColors struct is used.
 *
 * @param colors The UniformColors struct with updated values
 * @param values Ignored
 */
void DefaultShader::SetUniforms(UniformColors *colors, UniformValues *values)
{
	if (colors != 0)
	{
		if (colors->Color1[0] != -99999.0)
			rgba[0] = colors->Color1[0];
		if (colors->Color1[1] != -99999.0)
			rgba[1] = colors->Color1[1];
		if (colors->Color1[2] != -99999.0)
			rgba[2] = colors->Color1[2];
		if (colors->Color1[3] != -99999.0)
			rgba[3] = colors->Color1[3];
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
