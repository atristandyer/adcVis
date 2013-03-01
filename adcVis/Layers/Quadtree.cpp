#include "Quadtree.h"

Quadtree::Quadtree(std::vector<Node> nodes, int size, float minX, float maxX, float minY, float maxY)
{
	nodeList = nodes;
	binSize = size;

	// Create the root branch
	root = newBranch(minX, maxX, minY, maxY);

	if (binSize > 0)
		for (unsigned int i=0; i<nodeList.size(); i++)
			addNode(&nodeList[i], root);
}


Quadtree::~Quadtree()
{
	for (unsigned int i=0; i<leafList.size(); i++)
		if (leafList[i] != 0)
			delete leafList[i];
	for (unsigned int i=0; i<branchList.size(); i++)
		if (branchList[i] != 0)
			delete branchList[i];
}


Node* Quadtree::FindNode(float x, float y, branch *currBranch)
{
	// Searching is initiated with currBranch=0 by the user
	if (currBranch == 0)
		return FindNode(x, y, root);

	// If the point falls into a sub-branch, start recursion by calling this function
	// on that sub-branch.
	for (int i=0; i<4; i++)
		if (currBranch->branches[i] != 0 && pointIsInside(currBranch->branches[i], x, y))
			return FindNode(x, y, currBranch->branches[i]);

	// If the point falls into a leaf, find the Node closest to the provided point,
	// and return that Node
	for (int i=0; i<4; i++)
	{
		if (currBranch->leaves[i] != 0 && pointIsInside(currBranch->leaves[i], x, y) && currBranch->leaves[i]->nodes.size() > 0)
		{
			Node *currClosest = currBranch->leaves[i]->nodes[0];
			float newDistance, currDistance = distance(currBranch->leaves[i]->nodes[0], x, y);
			for (unsigned int j=1; j<currBranch->leaves[i]->nodes.size(); j++)
			{
				newDistance = distance(currBranch->leaves[i]->nodes[j], x, y);
				if (newDistance < currDistance)
				{
					currClosest = currBranch->leaves[i]->nodes[j];
					currDistance = newDistance;
				}
			}
			return currClosest;
		}
	}

	// The point is not inside the quadtree bounds or there are no nodes in the
	// deepest level reached (possible improvements -- continue searching other
	// leaves/branches if the parser reaches a leaf with no nodes
	return 0;
}


leaf* Quadtree::newLeaf(float l, float r, float b, float t)
{
	// Create leaf in heap and put pointer into leaf list
	leaf *currLeaf = new leaf;
	leafList.push_back(currLeaf);

	// Set the boundaries of the leaf
	currLeaf->bounds[0] = l;
	currLeaf->bounds[1] = r;
	currLeaf->bounds[2] = b;
	currLeaf->bounds[3] = t;

	return currLeaf;
}
