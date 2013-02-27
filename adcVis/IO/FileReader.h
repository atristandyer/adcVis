#ifndef FILEREADER_H
#define FILEREADER_H

#include "adcData.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

/**
 * @brief A set of functions that can be used to read ADCIRC data
 *
 * This class provides a set of static functions that can be used to read ADCIRC data.
 * There is no data associated with the FileReader class, so users do not need
 * to instantiate an object to use the functions.
 *
 */
class FileReader
{
	public:

		FileReader();

		static int ReadFort14(std::string fileLoc, std::vector<Node> *nodes, std::vector<Element> *elements, unsigned int *numNodes, unsigned int *numElements);
};

#endif // FILEREADER_H
