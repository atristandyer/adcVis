#include "TerrainLayer.h"

TerrainLayer::TerrainLayer()
{
	flipZValue = true;
	normalizeCoords = true;
	fileLoaded = false;
}


/**
 * @brief Calls Layer::Draw() and then draws the selected node/element
 *
 *
 *
 */
void TerrainLayer::Draw()
{
	Layer::Draw();
}


/**
 * @brief TerrainLayer::GetFort14Location
 * @return
 */
std::string TerrainLayer::GetFort14Location()
{

}


/**
 * @brief TerrainLayer::GetNode
 * @param nodeNumber
 * @return
 */
Node* TerrainLayer::GetNode(unsigned int nodeNumber)
{

}


/**
 * @brief TerrainLayer::GetNode
 * @param x
 * @param y
 * @return
 */
Node* TerrainLayer::GetNode(float x, float y)
{

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
