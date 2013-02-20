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
 * @brief The UniformBundle struct provides a standardized format for
 * passing data from a generic Layer to a generic GLShader.
 *
 * UniformBundle provides a standardized data structure that
 * can be passed between Layers and GLShaders.
 *
 * Every subclass of Layer must decide how much information will be
 * sent to it's shaders. It passes these values through a UniformBundle.
 *
 * Every sublass of GLShader must be able to parse a UniformBundle of any
 * state and provide and determine if a valid set of uniforms can be
 * passed to the shader program in the OpenGL context.
 *
 */
struct UniformBundle {
		float Value1;	 // 4 bytes
		float Value2;	 // 4 bytes
		float Value3;	 // 4 bytes
		float Value4;	 // 4 bytes
		float Value5;	 // 4 bytes
		float Value6;	 // 4 bytes
		float Value7;	 // 4 bytes
		float Value8;	 // 4 bytes
		float Color1[4]; // 16 bytes
		float Color2[4]; // 16 bytes
		float Color3[4]; // 16 bytes
		float Color4[4]; // 16 bytes
		float Color5[4]; // 16 bytes
		float Color6[4]; // 16 bytes
				 // 128 bytes total
		UniformBundle()
		{
			Value1 = -99999.0;
			Value2 = -99999.0;
			Value3 = -99999.0;
			Value4 = -99999.0;
			Value5 = -99999.0;
			Value6 = -99999.0;
			Value7 = -99999.0;
			Value8 = -99999.0;
			Color1[0] = -1.0; Color1[1] = -1.0; Color1[2] = -1.0; Color1[3] = -1.0;
			Color2[0] = -1.0; Color2[1] = -1.0; Color2[2] = -1.0; Color2[3] = -1.0;
			Color3[0] = -1.0; Color3[1] = -1.0; Color3[2] = -1.0; Color3[3] = -1.0;
			Color4[0] = -1.0; Color4[1] = -1.0; Color4[2] = -1.0; Color4[3] = -1.0;
			Color5[0] = -1.0; Color5[1] = -1.0; Color5[2] = -1.0; Color5[3] = -1.0;
			Color6[0] = -1.0; Color6[1] = -1.0; Color6[2] = -1.0; Color6[3] = -1.0;
		}
};


#endif // GLDATA_H
