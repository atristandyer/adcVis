#include "Layer.h"


// Initialize static members
unsigned int	Layer::layerCount = 0;
GLfloat		Layer::outlineOffset = 1.0;


Layer::Layer()
{
	layerCount++;
	layerID = layerCount;

	numNodes = 0;
	numElements = 0;
	numTimesteps = 0;

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
	offsetValue = 0.0;
}


/**
 * @brief Layer::Draw Used to draw the layer in the OpenGL context.
 *
 * This function first checks that data has been loaded to the OpenGL context and that
 * both shaders have been set before binding the Layer's vertex array object and
 * drawing the Layer.
 *
 */
void Layer::Draw()
{
	// Note to self: Get this code from old adcVis, it should work for all Layers
}


/**
 * @brief Layer::UpdateTimestep Used to inform the Layer object that the current timestep has
 * changed.
 *
 * This function is meant to be overridden by subclasses of Layer that need to know the
 * current timestep (eg. water layers). Default behavior is to do nothing.
 *
 * @param timestep The new current timestep.
 */
void Layer::UpdateTimestep(int timestep)
{
	return;
}


/**
 * @brief Layer::GetID Returns the unique ID associated with the Layer object.
 * @return The unique ID associated with the Layer object.
 */
unsigned int Layer::GetID()
{
	return layerID;
}


/**
 * @brief Layer::GetNumLayers Returns the total number of Layer objects that have
 * been created.
 * @return The total number of Layer objects that have been created.
 */
unsigned int Layer::GetNumLayers()
{
	return layerCount;
}


/**
 * @brief Layer::GetMinX Returns the smallest x-coordinate.
 * @return The minimum x-coordinate in Layer::nodes
 */
float Layer::GetMinX()
{
	return minX;
}


/**
 * @brief Layer::GetMaxX Returns the largest x-coordinate.
 * @return The maximum x-coordinate in Layer::nodes
 */
float Layer::GetMaxX()
{
	return maxX;
}


/**
 * @brief Layer::GetMinY Returns the smallest y-coordinate.
 * @return The minimum y-coordinate in Layer::nodes
 */
float Layer::GetMinY()
{
	return minY;
}


/**
 * @brief Layer::GetMaxY Returns the largest y-coordinate.
 * @return The maximum y-coordinate in Layer::nodes
 */
float Layer::GetMaxY()
{
	return maxY;
}


/**
  * @brief Layer::GetMinZ Returns the smallest z-coordinate.
  * @return The minimum z-coordinate in Layer::nodes
  */
float Layer::GetMinZ()
{
	return minZ;
}


/**
  * @brief Layer::GetMaxZ() Returns the largest z-coordinate.
  *
  * @return The maximum z-coordinate in Layer::nodes
  */
float Layer::GetMaxZ()
{
	return maxZ;
}


/**
 * @brief Layer::GetNode Returns a pointer to the requested Node.
 *
 * This function is meant to be implemented by a subclass of Layer. Specifically,
 * Layers that are modeling terrain should typically be able to return specific
 * Nodes. Layers that are modeling water, on the other hand, will usually only
 * contain a list of z-coordinates in order to keep memory footprint low, and
 * therefore will not be able to return a Node.
 *
 * This version of the overloaded function should return the Node with the
 * given node number.
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
 * @brief Layer::GetNode Returns a pointer to the requested Node.
 *
 * This function is meant to be implemented by a subclass of Layer. Specifically,
 * Layers that are modeling terrain should typically be able to return specific
 * Nodes. Layers that are modeling water, on the other hand, will usually only
 * contain a list of z-coordinates in order to keep memory footprint low, and
 * therefore will not be able to return a Node.
 *
 * This version of the overloaded function should return the Node closest to the
 * given (x, y) coordinatesof a mouse click in the OpenGL context.
 *
 * If it is not overridden, this function will always return 0.
 *
 * @param x The x-coordinate of the mouse click in the OpenGL context
 * @param y The y-coordinate of the mouse click in the OpenGL context
 * @return A pointer to the Node object closest to the (x, y) mouse click.
 * @return 0 otherwise.
 */
Node* Layer::GetNode(float x, float y)
{
	return 0;
}


/**
 * @brief Layer::GetElement Returns a pointer to the requested Element.
 *
 * This function is meant to be implemented by a subclass of Layer. Specifically,
 * Layers that are modeling terrain should typically be able to return specific
 * Elements. Layers that are modeling water, on the other hand, will usually only
 * contain a list of z-coordinates in order to keep memory footprint low, and
 * therefore will not be able to return an Element.
 *
 * This version of the overloaded function should return the Element with the
 * given element number.
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
 * @brief Layer::GetElement Returns a pointer to the requested Element.
 *
 * This function is meant to be implemented by a subclass of Layer. Specifically,
 * Layers that are modeling terrain should typically be able to return specific
 * Elements. Layers that are modeling water, on the other hand, will usually only
 * contain a list of z-coordinates in order to keep memory footprint low, and
 * therefore will not be able to return an Element.
 *
 * This version of the overloaded function should return the Element closest to the
 * given (x, y) coordinates of a mouse click in the OpenGL context.
 *
 * If it is not overridden, this function will always return 0.
 *
 * @param x The x-coordinate of the mouse click in the OpenGL context
 * @param y The y-coordinate of the mouse click in the OpenGL context
 * @return A pointer to the Element object closest to the (x, y) mouse click.
 * @return 0 otherwise.
 */
Element* Layer::GetElement(float x, float y)
{
	return 0;
}


/**
 * @brief Layer::SetOutlineShader Sets the outline shader.
 * @param newShader Pointer to the outline shader to be used when drawing.
 */
void Layer::SetOutlineShader(GLShader *newShader)
{
	outlineShader = newShader;
}


/**
 * @brief Layer::SetFillShader Sets the fill shader.
 * @param newShader Pointer to the fill shader to be used when drawing.
 */
void Layer::SetFillShader(GLShader *newShader)
{
	fillShader = newShader;
}


/**
 * @brief Layer::SetOffsetValue Sets the offset that will be used during drawing operations.
 *
 * The offset value is used to prevent z-fighting when drawing multiple layers in the same
 * OpenGL context. The glPolygonOffset function is used to slightly modify the z-values of
 * polygons during draw operations so that layers that have very similar z-values (eg. the fill
 * and outline use the exact same values to draw so z-fighting will always occur without using
 * an offset) will appear with the correct layer on top.
 *
 * The value passed in here is used to relate Layer objects to other Layer objects. Offsetting
 * the outline from the fill is done automatically using the static Layer::outlineOffset value.
 *
 * @param newOffset The new offset value.
 */
void Layer::SetOffsetValue(GLfloat newOffset)
{
	offsetValue = newOffset;
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
