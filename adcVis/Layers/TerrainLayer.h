#ifndef TERRAINLAYER_H
#define TERRAINLAYER_H

#include "Layer.h"
#include "Quadtree.h"
#include "../Shaders/DefaultShader.h"
#include "../IO/FileReader.h"
#include <string>


/**
 * @brief A subclass of Layer that defines a drawable terrain layer based on fort.14 data
 *
 * This subclass of Layer provides a framework for reading the node and element data from
 * a fort.14 file and displaying the defined mesh in an OpenGL context. It also provides
 * support for Node and Element picking.
 *
 * TODO: Find the number of nodes where quadtree becomes more efficient than linear search
 * and only use quadtree if the number of nodes in the layer is higher than that number.
 *
 */
class TerrainLayer : public Layer
{
	public:
		TerrainLayer();
		~TerrainLayer();

		virtual void	Draw();

		// Getter Methods
		std::string		GetFort14Location();
		virtual Node*		GetNode(unsigned int nodeNumber);
		virtual Node*		GetNode(float x, float y);
		virtual Element*	GetElement(unsigned int elementNumber);
		virtual Element*	GetElement(float x, float y);

		// Setter Methods
		void	SetFort14Location(std::string newLocation);
		void	SetPickingColor(float r, float g, float b, float a);


	protected:

		// Terrain Specific Variables
		std::string	fort14Location;	/**< The fort.14 file location */

		// Terrain Specific OpenGL Variables
		DefaultShader	*pickingShader; /**< The fill shader used to draw the selected node/element */

		// Flags
		bool	flipZValue;		/**< Flag that determines if the z-value is multiplied by -1.0 before being loaded to the GPU */
		bool	normalizeCoords;	/**< Flag that determines if the xy-coords will be normalized before being loaded to the GPU */
		bool	fileLoaded;		/**< Flag that shows if data has been successfully read from fort.14 */

		// Picking variables
		Quadtree*	quadtree;		/**< The quadtree used to find the Node closest to the clicked point */

};

#endif // TERRAINLAYER_H
