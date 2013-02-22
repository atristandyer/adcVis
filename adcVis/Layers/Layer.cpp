#include "Layer.h"


// Initialize static members
unsigned int Layer::layerCount = 0;


Layer::Layer()
{
	layerCount++;
	layerID = layerCount;

	minX = 0.0;
	maxX = 0.0;
	minY = 0.0;
	maxY = 0.0;
	minZ = 0.0;
	maxZ = 0.0;

	vaoID = 0;
	vboID = 0;
	iboID = 0;
	outlineShader = 0;
	fillShader = 0;
	offsetValue = 0;
}


/**
 * @brief Layer::Draw This function is used to draw the layer in the OpenGL context.
 *
 * This function first checks that data has been loaded to the OpenGL context and that
 * both shaders have been set before binding the Layer's vertex array object and
 * drawing the Layer.
 *
 */
void Layer::Draw()
{

}


/**
 * @brief Layer::Update
 */
void Layer::Update()
{

}


/**
 * @brief Layer::Update
 * @param value
 */
void Layer::Update(int value)
{

}


/**
 * @brief Layer::GetID returns the unique ID associated with the Layer object.
 * @return The unique ID associated with the Layer object.
 */
unsigned int Layer::GetID()
{
	return layerID;
}


/**
 * @brief Layer::GetNumLayers returns the total number of Layer objects that have
 * been created.
 * @return The total number of Layer objects that have been created.
 */
unsigned int Layer::GetNumLayers()
{
	return layerCount;
}


/**
  * @brief Layer::GetMinZ returns the z-coordinate of the lowest Node
  *
  * @return The minimum z-value in Layer::nodes
  */
float Layer::GetMinZ()
{
	return minZ;
}


/**
  * @brief Layer::GetMaxZ() returns the z-coordinate of the highest Node
  *
  * @return The maximum z-value in Layer::nodes
  */
float Layer::GetMaxZ()
{
	return maxZ;
}


/**
 * @brief Layer::GetNode returns a pointer to the requested Node.
 *
 * This function is meant to be implemented by a subclass of Layer. Specifically,
 * Layers that are modeling terrain should typically be able to return specific
 * Nodes. Layers that are modeling water, on the other hand, will usually only
 * contain a list of z-coordinates in order to keep memory footprint low, and
 * therefore will not be able to return a Node.
 *
 * If it is not overridden, this function will always return 0.
 *
 * @param nodeNumber The node number as defined in the fort.14 file.
 * @return A pointer to the Node object if the node number is valid.
 * @return 0 otherwise.
 */
Node* Layer::GetNode(unsigned int nodeNumber)
{
	return 0;
}


/**
 * @brief Layer::GetElement returns a pointer to the requested Element.
 *
 * This function is meant to be implemented by a subclass of Layer. Specifically,
 * Layers that are modeling terrain should typically be able to return specific
 * Elements. Layers that are modeling water, on the other hand, will usually only
 * contain a list of z-coordinates in order to keep memory footprint low, and
 * therefore will not be able to return an Element.
 *
 * If it is not overridden, this function will always return 0.
 *
 * @param elementNumber The element number as defined in the fort.14 file.
 * @return A pointer to the Element object if the element number is valid.
 * @return 0 otherwise.
 */
Element* Layer::GetElement(unsigned int elementNumber)
{
	return 0;
}


/**
 * @brief LoadDataToGPU Transfers node and element data to the OpenGL context.
 *
 * This function is used to pass Node and Element data to the OpenGL context in order to
 * be rendered. Node location data is densely packed in order:
 * - [x1, y1, z1, 1.0, x2, y2, z2, 1.0, ...]
 * .
 * Element data is also densely packed in order:
 * - [e1n1, e1n2, e1n3, e2n1, e2n2, e2n3, ...]
 * .
 *
 * We make use of Vertex Array Objects, so once the Node data is put into a Vertex
 * Buffer Object and Element data is put into an Index Buffer Object, the OpenGL state
 * is saved in the VAO state.
 *
 */
void Layer::LoadDataToGPU()
{

}
