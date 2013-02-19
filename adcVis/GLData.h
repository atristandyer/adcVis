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


#endif // GLDATA_H
