#pragma once
#include "GroupNode.h"
#include "DrawNode.h"
#include "Quad.h"

#include <map>

//Class that handles the topology and transformations of the RubikCube
/*
	When naming/mapping nodes to rubikParts, it's according to the following convention:
	Think of RubikCube as a 3x3x3 cube, where coordinate 2,2,2 should be thought of as the origin (the middle-most cube)
	The following examples should give an idea how coordinates map when viewing the RubikCube fron front facing side:
	1,1,1: left-bottom-front
	3,1,1: right-bottom-front
	1,3,1: left-upper-front
	3,1,3: right-bottom-back
	3,3,3: right-upper-back
	Notice that there are 27 total permutations representing the 27 mini-cubes making up a RubikCube. However, the mini-cubes are not really cubes, they are just GroupNodes made of 1,2 or 3 Quads.
	Since the middle-most mini-cube is never rendered (coordinate 2,2,2), there are a total of 26 GroupNodes in the RubikCube.
	During rotations, the RubikCube handles swaping Groupnodes to their appropriate coordinates in the rubikParts	
*/

class RubikCube : public GroupNode{
public:
	RubikCube();
	~RubikCube() {};




private:
	std::map<std::tuple<int, int, int>, GroupNode*> rubikParts;

};

