#include "Layer.h"


// Initialize static members
unsigned int Layer::layerCount = 0;


Layer::Layer()
{
	layerCount++;
	layerID = layerCount;

	minZ = 0.0;
	maxZ = 0.0;
}


void Layer::Draw()
{

}


void Layer::Update()
{

}


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
 * @param nodeNumber The node number as defined in the fort.14 file.
 * @return A pointer to the Node object if the node number is valid.
 * @return 0 otherwise.
 */
Node* Layer::GetNode(unsigned int nodeNumber)
{

}


/**
 * @brief Layer::GetElement returns a pointer to the requested Element.
 * @param elementNumber The element number as defined in the fort.14 file.
 * @return A pointer to the Element object if the element number is valid.
 * @return 0 otherwise.
 */
Element* Layer::GetElement(unsigned int elementNumber)
{

}
