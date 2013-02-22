#ifndef LAYER_H
#define LAYER_H

#include "adcData.h"
#include "../Shaders/GLShader.h"

#include <map>

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
		float		GetMinZ();
		float		GetMaxZ();
		Node		*GetNode(unsigned int nodeNumber);
		Element		*GetElement(unsigned int elementNumber);

	protected:

		// Generic Variables
		std::map<unsigned int, Node>	nodes;			/**< Map of <Node number, Node> */
		std::map<unsigned int, Element>	elements;		/**< Map of <Element number, Element */
		unsigned int			numNodes;		/**< The number of nodes in the Layer */
		unsigned int			numElements;		/**< The number of elements in the Layer */
		float				minZ;			/**< The elevation of the lowest Node */
		float				maxZ;			/**< The elevation of the highest Node */

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
		unsigned int		layerID;	/**< A unique unsigned integer that identifies the Layer */


};

#endif // LAYER_H
