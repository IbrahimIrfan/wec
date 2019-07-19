#ifndef TREE_H
#define TREE_H

#include<string>
#include<vector>
#include<algorithm>

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
	TreeNode *head;

	TreeNode* getDeepestNode(TreeNode* root, int level) {
		if (root == nullptr || level == 1) {
			return root;
		}
		
		TreeNode* leftDeepest = getDeepestNode(root->left, level - 1);
		TreeNode* rightDeepest = getDeepestNode(root->right, level - 1);

		return leftDeepest ? leftDeepest : rightDeepest;
	}
	
	int height(TreeNode* root) {
		if (root == nullptr) return 0;

		return 1 + max(height(root->left), height(root->right));
	}

public:
	Tree() : head{nullptr} {}

	Match& getNextMatch() {
		return getDeepestNode(head, height(head)).first->match;
	}

	void constructTree(vector<Player&> players);
};

#endif
