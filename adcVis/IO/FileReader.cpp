#include "FileReader.h"

FileReader::FileReader()
{

}


/**
 * @brief Reads Node and Element data from fort.14
 *
 * This function can be used to read the node and element data from a fort.14 file. Any
 * data that is already in the node and element lists will be cleared before reading, unless
 * the file path is invalid. Any value or set of values that needs to be read from fort.14
 * can be individually retrieved by passing in 0 for values that are not needed.
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
