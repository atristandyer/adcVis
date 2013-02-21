#ifndef LAYER_H
#define LAYER_H

#include "adcData.h"
#include "../Shaders/GLShader.h"


/**
 * @brief An abstract class that defines the generic behavior of an ADCIRC layer
 *
 *
 *
 */
class Layer
{
	public:
		Layer();

		void	Draw();
		void	Update();
		void	Update(int);

		// Getter Methods
		unsigned int	GetID();
		unsigned int	GetNumLayers();

	protected:

		// Flags
		bool	glLoaded;

		// OpenGL Variables
		GLuint		vaoID;			/**< The vertex array object ID */
		GLuint		vboID;			/**< The vertex buffer object ID */
		GLuint		iboID;			/**< The index buffer object ID */
		GLShader	*outlineShader;		/**< Pointer to the shader used for drawing outlines */
		GLShader	*fillShader;		/**< Pointer to the shader used for drawing fill */

		// Protected Functions
		virtual void	LoadDataToGPU() = 0;


	private:

		static unsigned int	layerCount;	/**< A running count of the number of Layer objects */
		unsigned int		layerID;	/**< A unique unsigned integer that identifies the layer */


};

#endif // LAYER_H
