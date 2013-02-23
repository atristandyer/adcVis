#ifndef LAYER_H
#define LAYER_H

#include "adcData.h"
#include "../Shaders/GLShader.h"

#include <vector>

/**
 * @brief A generic class that defines the behavior of an ADCIRC layer
 *
 *
 *
 */
class Layer
{
	public:
		Layer();

		void	Draw();
		void	UpdateTimestep(int timestep);

		// Getter Methods
		unsigned int	GetID();
		unsigned int	GetNumLayers();
		float		GetMinX();
		float		GetMaxX();
		float		GetMinY();
		float		GetMaxY();
		float		GetMinZ();
		float		GetMaxZ();
		Node*		GetNode(unsigned int nodeNumber);
		Node*		GetNode(float x, float y);
		Element*	GetElement(unsigned int elementNumber);
		Element*	GetElement(float x, float y);

		// Setter Methods
		void		SetOutlineShader(GLShader* newShader);
		void		SetFillShader(GLShader* newShader);
		void		SetOffsetValue(GLfloat newOffset);

	protected:

		// Generic Variables
		std::vector<Node>	nodes;		/**< List of all Nodes in the Layer */
		std::vector<Element>	elements;	/**< List of all Elements in the Layer */
		unsigned int		numNodes;	/**< The number of Nodes in the Layer as specified in fort.14 */
		unsigned int		numElements;	/**< The number of Elements in the Layer as specified in fort.14 */
		unsigned int		numTimesteps;	/**< The number of timesteps in the Layer as specified in fort.63/64 */
		float			minX;		/**< The minimum x-coordinate out of all Nodes */
		float			maxX;		/**< The maximum x-coordinate out of all Nodes */
		float			minY;		/**< The minimum y-coordinate out of all Nodes */
		float			maxY;		/**< The maximum y-coordinate out of all Nodes */
		float			minZ;		/**< The elevation of the lowest Node */
		float			maxZ;		/**< The elevation of the highest Node */

		// Flags
		bool	glLoaded;			/**< Flag shows if the data has been loaded to the OpenGL context */

		// OpenGL Variables
		GLuint		vaoID;			/**< The vertex array object ID */
		GLuint		vboID;			/**< The vertex buffer object ID */
		GLuint		iboID;			/**< The index buffer object ID */
		GLShader*	outlineShader;		/**< Pointer to the shader used for drawing outlines */
		GLShader*	fillShader;		/**< Pointer to the shader used for drawing fill */
		GLfloat		offsetValue;		/**< The value used to prevent z-fighting during draw operations */
		static GLfloat	outlineOffset;		/**< The value used to prevent z-fighting between the fill and outline */

		// Protected Functions
		void	LoadDataToGPU();


	private:

		static unsigned int	layerCount;	/**< A running count of the number of Layer objects */
		unsigned int		layerID;	/**< A unique unsigned integer that identifies the Layer */


};

#endif // LAYER_H
