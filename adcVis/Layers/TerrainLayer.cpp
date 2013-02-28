#include "TerrainLayer.h"

TerrainLayer::TerrainLayer()
{
	flipZValue = true;
	normalizeCoords = true;
	fileLoaded = false;

	pickingShader = new DefaultShader();
}


TerrainLayer::~TerrainLayer()
{
	if (pickingShader)
		delete pickingShader;
}


/**
 * @brief Calls Layer::Draw() and then draws the selected node/element
 *
 * This function draws the TerrainLayer in the OpenGL context. It first calls the
 * Layer::Draw() function, which draws the fill and outline, and then draws the
 * selected node and/or element using a shader that is owned by the TerrainLayer
 * object.
 *
 */
void TerrainLayer::Draw()
{
	Layer::Draw();
	if (glLoaded && vaoID != 0 && pickingShader && pickingShader->Use() == 0)
	{
		// Draw selected node
		if (selectedNode > 0)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			glPolygonOffset(0, 0);
			glDrawArrays(GL_POINTS, selectedNode-1, 1);
		}

		// Draw selected element
		if (selectedElement > 0)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glPolygonOffset(0, 0);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLuint*)0+3*(selectedElement-1));
		}
	}
}


/**
 * @brief Returns the fort.14 file location
 * @return The fort.14 file location
 */
std::string TerrainLayer::GetFort14Location()
{
	return fort14Location;
}


/**
 * @brief Returns a pointer to the Node with the corresponding node number
 *
 * This function provides access to Nodes in the node list through node number.
 * The Node is first looked up on the assumption that the Node list is ordered,
 * but if the list is not ordered, a linear lookup on the Node list is performed
 * until the correct Node is found.
 *
 * @param nodeNumber The node number as defined in the fort.14 file
 * @return A pointer to the Node with the corresponding node number
 * @return 0 if the Node is not in the node list
 */
Node* TerrainLayer::GetNode(unsigned int nodeNumber)
{
	if (nodes.size() > 0)
	{
		if (nodeNumber <= nodes.size() && nodeNumber == nodes[nodeNumber-1].nodeNumber)
			return &nodes[nodeNumber-1];
		else
		{
			for (unsigned int i=0; i<nodes.size(); i++)
				if (nodes[i].nodeNumber == nodeNumber)
					return &nodes[i];
		}
	}
	return 0;
}


/**
 * @brief Returns a pointer to the Node closest to the provided x-y coordinates
 *
 * This function provides access to Nodes in the node list by finding the Node
 * with the x-y coordinates closest to the provided x-y coordinates. A quick
 * lookup is possible by parsing the Quadtree used to map the Node data.
 *
 * @param x The x-coordinate
 * @param y The y-coordinate
 * @return A pointer to the Node closest to the provided x-y coordinates
 * @return 0 if the Node list is empty
 */
Node* TerrainLayer::GetNode(float x, float y)
{
	return 0;
}


/**
 * @brief TerrainLayer::GetElement
 * @param elementNumber
 * @return
 */
Element* TerrainLayer::GetElement(unsigned int elementNumber)
{

}


/**
 * @brief TerrainLayer::GetElement
 * @param x
 * @param y
 * @return
 */
Element* TerrainLayer::GetElement(float x, float y)
{

}


/**
 * @brief TerrainLayer::GetSelectedNode
 * @return
 */
unsigned int TerrainLayer::GetSelectedNode()
{

}


/**
 * @brief TerrainLayer::GetSelectedElement
 * @return
 */
unsigned int TerrainLayer::GetSelectedElement()
{

}


/**
 * @brief TerrainLayer::SetFort14Location
 */
void TerrainLayer::SetFort14Location()
{

}


/**
 * @brief Sets the color used when drawing the selected Node or Element
 * @param r Red (0.0 - 1.0)
 * @param g Green (0.0 - 1.0)
 * @param b Blue (0.0 - 1.0)
 * @param a Alpha (0.0 - 1.0)
 */
void TerrainLayer::SetPickingColor(float r, float g, float b, float a)
{
	UniformColors colors;
	colors.Color1[0] = r;
	colors.Color1[1] = g;
	colors.Color1[2] = b;
	colors.Color1[3] = a;
	if (pickingShader)
		pickingShader->SetUniforms(&colors, 0);
}
