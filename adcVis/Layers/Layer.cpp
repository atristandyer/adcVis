#include "Layer.h"


// Initialize static members
unsigned int Layer::layerCount = 0;


Layer::Layer()
{
	layerCount++;
	layerID = layerCount;
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
