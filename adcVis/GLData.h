#ifndef GLDATA_H
#define GLDATA_H

#include "OpenGL/glew.h"


/**
 * Defines a generic 4x4 matrix
 */
typedef struct {
		float m[16]; /**< The matrix in row-major order */
} Matrix;


/**
 * @brief PI The value of pi
 */
static const double PI = 3.14159625358979323846;


/**
 * The 4x4 Identity Matrix
 */
static const Matrix IDENTITY_MATRIX = {{
					       1.0, 0.0, 0.0, 0.0,
					       0.0, 1.0, 0.0, 0.0,
					       0.0, 0.0, 1.0, 0.0,
					       0.0, 0.0, 0.0, 1.0
				       }};


/**
 * @brief The UniformColors struct provides a standardized format for
 * passing color data to a generic GLShader.
 *
 * Every GLShader must get its color information through the GLShader::SetUniforms()
 * function. This color information is passed using a UniformColors struct.
 *
 * All color values are initialized to -1.0
 *
 */
struct UniformColors {

		float Color1[4]; // 16 bytes
		float Color2[4]; // 16 bytes
		float Color3[4]; // 16 bytes
		float Color4[4]; // 16 bytes
		float Color5[4]; // 16 bytes
		float Color6[4]; // 16 bytes
		float Color7[4]; // 16 bytes
		float Color8[4]; // 16 bytes
				 // 128 bytes total
		UniformColors()
		{
			Color1[0] = -1.0; Color1[1] = -1.0; Color1[2] = -1.0; Color1[3] = -1.0;
			Color2[0] = -1.0; Color2[1] = -1.0; Color2[2] = -1.0; Color2[3] = -1.0;
			Color3[0] = -1.0; Color3[1] = -1.0; Color3[2] = -1.0; Color3[3] = -1.0;
			Color4[0] = -1.0; Color4[1] = -1.0; Color4[2] = -1.0; Color4[3] = -1.0;
			Color5[0] = -1.0; Color5[1] = -1.0; Color5[2] = -1.0; Color5[3] = -1.0;
			Color6[0] = -1.0; Color6[1] = -1.0; Color6[2] = -1.0; Color6[3] = -1.0;
		}
};


/**
 * @brief The UniformValues struct provides a standardized format for passing
 * generic data to a GLShader.
 *
 * Every GLShader must get its generic data through the GLShader::SetUniforms() function.
 * This data is passed using a UniformValues struct. For example, a minimum and maximum
 * elevation that need to be passed to the GLShader every timestep would be passed from
 * the water layer to the shader using this struct.
 *
 * All values are initialized to -99999.0
 *
 */
struct UniformValues {

		float Value1;	 // 4 bytes
		float Value2;	 // 4 bytes
		float Value3;	 // 4 bytes
		float Value4;	 // 4 bytes
		float Value5;	 // 4 bytes
		float Value6;	 // 4 bytes
		float Value7;	 // 4 bytes
		float Value8;	 // 4 bytes
				 // 32 bytes total
		UniformValues()
		{
			Value1 = -99999.0;
			Value2 = -99999.0;
			Value3 = -99999.0;
			Value4 = -99999.0;
			Value5 = -99999.0;
			Value6 = -99999.0;
			Value7 = -99999.0;
			Value8 = -99999.0;
		}
};


#endif // GLDATA_H
