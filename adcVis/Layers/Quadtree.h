#ifndef QUADTREE_H
#define QUADTREE_H

#include "adcData.h"
#include <vector>
#include <math.h>

struct leaf
{
		float			bounds[4];
		std::vector<Node*>	nodes;
};


typedef struct branch {
		float		bounds[4];
		leaf		*leaves[4];
		struct branch	*branches[4];
} branch;


class Quadtree
{
	public:

		// Constructor/Destructor
		Quadtree(std::vector<Node> nodes, int size, float minX, float maxX, float minY, float maxY);
		~Quadtree();

		// Public Functions
		Node*	FindNode(float x, float y, branch *currBranch);

	protected:

		// Data Variables
		int			binSize;
		std::vector<Node>	nodeList;
		std::vector<branch*>	branchList;
		std::vector<leaf*>	leafList;
		branch*			root;

		// Building functions
		leaf*	newLeaf(float l, float r, float b, float t);
		branch*	newBranch(float l, float r, float b, float t);
		branch*	leafTobranch(leaf *currLeaf);
		branch*	addNode(Node *currNode, leaf *currLeaf);
		void	addNode(Node *currNode, branch *currBranch);
		bool	nodeIsInside(Node *currNode, leaf *currLeaf);
		bool	nodeIsInside(Node *currNode, branch *currBranch);

		// Parsing functions
		float	distance(Node *currNode, float x, float y);
		bool	pointIsInside(leaf *currLeaf, float x, float y);
		bool	pointIsInside(branch *currBranch, float x, float y);
};

#endif // QUADTREE_H
