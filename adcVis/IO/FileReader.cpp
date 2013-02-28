#include "FileReader.h"

FileReader::FileReader()
{

}


/**
 * @brief Reads Node and Element data from fort.14
 *
 * This function can be used to read only node and element data from a fort.14 file. Any data
 * that is already in the node and element lists will be cleared before reading, unless the
 * file path is invalid.
 *
 * @param fileLoc The fort.14 file location
 * @param nodes A pointer to the node list
 * @param elements A pointer to the element list
 *
 * @return 0 if fort.14 successfully read
 * @return 1 if an error occurred
 */
int FileReader::ReadFort14(std::string fileLoc,
			   std::vector<Node> *nodes,
			   std::vector<Element> *elements)
{
	return ReadFort14(fileLoc, nodes, elements, 0, 0);
}


/**
 * @brief Reads Node data, Element data, number of nodes and number of elements from fort.14
 *
 * This function can be used to read the node and element data from a fort.14 file, as well
 * as the number of nodes and number of elements in the mesh. Any data that is already in the
 * node and element lists will be cleared before reading, unless the file path is invalid.
 *
 * @param fileLoc The fort.14 file location
 * @param nodes A pointer to the node list
 * @param elements A pointer to the element list
 * @param numNodes A pointer to the variable that will hold the number of nodes
 * @param numElements A pointer to the variable that will hold the number of elements
 *
 * @return 0 if fort.14 successfully read
 * @return 1 if an error occurred
 */
int FileReader::ReadFort14(std::string fileLoc,
			   std::vector<Node> *nodes,
			   std::vector<Element> *elements,
			   unsigned int *numNodes,
			   unsigned int *numElements)
{
	std::ifstream fort14 (fileLoc.data());
	if (fort14.is_open())
	{
		unsigned int nn, ne, trash;
		std::string line;

		// Get the number of nodes and number of elements
		std::getline(fort14, line);
		std::getline(fort14, line);
		std::stringstream(line) >> ne >> nn;
		if (numElements)
			*numElements = ne;
		if (numNodes)
			*numNodes = nn;


		// Clear the vectors of all data
		if (nodes)
			nodes->clear();
		if (elements)
			elements->clear();


		// Read the node data
		Node currNode;
		for (unsigned int i=0; i<nn; i++)
		{
			fort14 >> currNode.nodeNumber;
			fort14 >> currNode.x;
			fort14 >> currNode.y;
			fort14 >> currNode.z;
			if (nodes)
				nodes->push_back(currNode);
		}

		// Read the element data
		if (elements)
		{
			Element currElement;
			for (unsigned int i=0; i<ne; i++)
			{
				fort14 >> currElement.elementNumber;
				fort14 >> trash;
				fort14 >> currElement.n1;
				fort14 >> currElement.n2;
				fort14 >> currElement.n3;
				elements->push_back(currElement);
			}
		}


		// Close the file and return successfully
		fort14.close();
		return 0;
	} else {
		return 1;
	}
}


/**
 * @brief Reads Node data, Element data, and number of nodes and elements from fort.14, and
 * keeps track of all min and max values.
 *
 * This function can be used to read the node and element data from a fort.14 file, as well
 * as the number of nodes and number of elements in the mesh. As nodes are read from the file,
 * the function keeps track of the the min and max values for all three coordinates, and stores
 * the results into their associated variables. Any data that is already in the node and element
 * lists will be cleared before reading, unless the file path is invalid.
 *
 * If any of the min/max values are not needed, pass in 0 as the parameter for the unneeded value.
 *
 * The value -99999 is excluded from all minimum z-value comparisons.
 *
 * @param fileLoc The fort.14 file location
 * @param nodes A pointer to the node list
 * @param elements A pointer to the element list
 * @param numNodes A pointer to the variable that will hold the number of nodes
 * @param numElements A pointer to the variable that will hold the number of elements
 * @param minX A pointer to the variable that will hold the minimum x-value
 * @param maxX A pointer to the variable that will hold the maximum x-value
 * @param minY A pointer to the variable that will hold the minimum y-value
 * @param maxY A pointer to the variable that will hold the maximum y-value
 * @param minZ A pointer to the variable that will hold the minimum z-value
 * @param maxZ A pointer to the variable that will hold the maximum z-value
 * @return 0 if fort.14 successfully read
 * @return 1 if an error occurred
 */
int FileReader::ReadFort14(std::string fileLoc,
			   std::vector<Node> *nodes,
			   std::vector<Element> *elements,
			   unsigned int *numNodes,
			   unsigned int *numElements,
			   float *minX,
			   float *maxX,
			   float *minY,
			   float *maxY,
			   float *minZ,
			   float *maxZ)
{
	std::ifstream fort14 (fileLoc.data());
	if (fort14.is_open())
	{
		unsigned int nn, ne, trash;
		std::string line;

		// Get the number of nodes and number of elements
		std::getline(fort14, line);
		std::getline(fort14, line);
		std::stringstream(line) >> ne >> nn;
		if (numElements)
			*numElements = ne;
		if (numNodes)
			*numNodes = nn;


		// Clear the vectors of all data
		if (nodes)
			nodes->clear();
		if (elements)
			elements->clear();


		// Read the node data
		Node currNode;
		float miX, maX, miY, maY, miZ, maZ;
		miX = miY = miZ = 99999.0;
		maX = maY = maZ = -99999.0;
		for (unsigned int i=0; i<nn; i++)
		{
			fort14 >> currNode.nodeNumber;
			fort14 >> currNode.x;
			fort14 >> currNode.y;
			fort14 >> currNode.z;
			if (nodes)
				nodes->push_back(currNode);
			if (currNode.x > maX)
				maX = currNode.x;
			else if (currNode.x < miX)
				miX = currNode.x;
			if (currNode.y > maY)
				maY = currNode.y;
			else if (currNode.y < miY)
				miY = currNode.y;
			if (currNode.z > maZ)
				maZ = currNode.z;
			else if (currNode.z != -99999 && currNode.z < miZ)
				miZ = currNode.z;
		}

		// Set the min/max values
		if (minX)
			*minX = miX;
		if (maxX)
			*maxX = maX;
		if (minY)
			*minY = miY;
		if (maxY)
			*maxY = maY;
		if (minZ)
			*minZ = miZ;
		if (maxZ)
			*maxZ = maZ;

		// Read the element data
		if (elements)
		{
			Element currElement;
			for (unsigned int i=0; i<ne; i++)
			{
				fort14 >> currElement.elementNumber;
				fort14 >> trash;
				fort14 >> currElement.n1;
				fort14 >> currElement.n2;
				fort14 >> currElement.n3;
				elements->push_back(currElement);
			}
		}


		// Close the file and return successfully
		fort14.close();
		return 0;
	} else {
		return 1;
	}
}
