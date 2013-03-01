#ifndef TERRAINLAYER_H
#define TERRAINLAYER_H

#include "Layer.h"
#include "../Shaders/DefaultShader.h"
#include "../IO/FileReader.h"
#include <string>

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
		unsigned int		GetSelectedNode();
		unsigned int		GetSelectedElement();

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
		unsigned int	selectedNode;		/**< The currently selected Node */
		unsigned int	selectedElement;	/**< The currently selected Element */
};

#endif // TERRAINLAYER_H
