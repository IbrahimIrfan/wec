#ifndef TREE_H
#define TREE_H

#include<string>
#include<vector>
#include "tournament.h"

using namespace std;

class TreeNode {
public:
	TreeNode *left;
	TreeNode *right;
	Match match;

	TreeNode(Match match) : match{match}, left{nullptr}, right{nullptr}  {}
};

class Tree {
public:
	Match& getNextMatch();

	// create the initial tournament tree
	Tree(vector<string> name, bool seeded=true);
};

#endif
