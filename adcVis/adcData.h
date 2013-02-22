/** @file */

#ifndef ADCDATA_H
#define ADCDATA_H

#include <stdio.h>

/** QT_DEBUG Macro used for displaying debug output
 *
 * This macro will only print output if compiling/running from the Debug version of the code.
 * It accepts either a single string to output or a formatted string followed by a list of
 * values to print.
 *
 */
#ifdef QT_DEBUG
#define DEBUG(format, ...) fprintf(stdout, format, ## __VA_ARGS__)
#else
#define DEBUG(format, ...) do {} while (0)
#endif


#define EARTH_RADIUS 6378206.4

/**
 * @brief Defines an ADCIRC node (See fort.14 in ADCIRC manual)
 *
 * Typically, Nodes will be stored in a std::map using the <Node number, Node> format, where the Node number
 * is the value defined in the fort.14 file. std::map containers keep their elements ordered at all times,
 * so iterating through the nodes in order is possible while keeping [] operator access logarithmic, which
 * is useful for very large datasets.
 *
 * If iteration through the Nodes is not needed, it may be more useful to store the Nodes in a
 * std::unordered_map, which has constant [] operator access time on average.
 *
 */
typedef struct {
		float x;	/**< First location coordinate defined in fort.14 file (typically longitude) */
		float y;	/**< Second location coordinate defined in the fort.14 file (typically latitude) */
		float z;	/**< Third location coordinate defined in the fort.14 file (depth with respect to GEOID, + is down, - is up) */
} Node;


/**
 * @brief Defines an ADCIRC element (See fort.14 in ADCIRC manual)
 *
 * Typically, Elements will be stored in a std::map using the <Element number, Element> format, where the
 * Element number is the value defined in the fort.14 file. std::map containers keep their elements
 * ordered at all times, so iterating through the elements in order is possible while keeping [] operator
 * access logarithmic, which is useful for very large datasets.
 *
 * If iteration through the Elements is not needed, it may be more useful to store the Elements in a
 * std::unordered_map, which has constant [] operator access time on average.
 *
 */
typedef struct {
		unsigned int n1;	/**< nodeNumber of the first Node specified in the fort.14 file */
		unsigned int n2;	/**< nodeNumber of the second Node specified in the fort.14 file */
		unsigned int n3;	/**< nodeNumber of the third Node specified in the fort.14 file */
} Element;

#endif
