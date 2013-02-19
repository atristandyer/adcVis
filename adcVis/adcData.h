#ifndef ADCDATA_H
#define ADCDATA_H

#define EARTH_RADIUS 6378206.4

/**
 *	Defines an ADCIRC node (See fort.14 in ADCIRC manual)
 */
typedef struct {
		int nodeNumber;	/**< Node number specified in fort.14 file */
		float x;	/**< First location coordinate defined in fort.14 file (typically longitude) */
		float y;	/**< Second location coordinate defined in the fort.14 file (typically latitude) */
		float z;	/**< Third location coordinate defined in the fort.14 file (depth with respect to GEOID, + is down, - is up) */
} Node;


/**
 *	Defines an ADCIRC element (See fort.14 in ADCIRC manual)
 */
typedef struct {
		int elementNumber;	/**< Element number specified in fort.14 file */
		unsigned int n1;	/**< nodeNumber of the first Node specified in the fort.14 file */
		unsigned int n2;	/**< nodeNumber of the second Node specified in the fort.14 file */
		unsigned int n3;	/**< nodeNumber of the third Node specified in the fort.14 file */
} Element;

#endif
