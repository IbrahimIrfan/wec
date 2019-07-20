#ifndef TREE_H
#define TREE_H

#include<string>
#include<vector>
#include<algorithm>
#include <math.h>

#include "tournament.h"

using namespace std;

const int nSpacesPerHeight = 10;

class TreeNode {
public:
	Match *match;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent;

	TreeNode(Match *match, TreeNode* left=nullptr, TreeNode* right=nullptr, TreeNode* parent=nullptr) : match{match}, left{left}, right{right}, parent{parent}  {}

	bool isLeaf() {
		return left == nullptr && right == nullptr;
	}

	void print(int heightOfNode) {
		if (heightOfNode == 0) {
			if (match == nullptr) {
				cout << match << endl;
			} else {
				cout << endl;
			}
		}

		if (left != nullptr) {
			left->print(heightOfNode-1);
		} else {
			int pow2 = 1 << (heightOfNode-1);
			for (int i = 0; i < pow2; ++i) {
				cout << endl;
			}
		}

		cout << string(nSpacesPerHeight*heightOfNode, ' ');
		if (match != nullptr) {
			cout << *match;
		}
		cout << endl;

		if (right != nullptr) {
			right->print(heightOfNode-1);
		} else {
			int pow2 = 1 << (heightOfNode-1);
			for (int i = 0; i < pow2; ++i) {
				cout << endl;
			}
		}
	}
};

class Tree {
	TreeNode *head;
	int matchId = 0;
	int curMatch = 0;

	TreeNode* getDeepestNode(TreeNode* root, int level) {
		if (root == nullptr) return nullptr;
		if (level == 1 && root->match != nullptr && !root->match->isOver()) {
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

	TreeNode* findByMatchId(int matchId) {
		return findByMatchId(matchId, head);
	}

	TreeNode* findByMatchId(int matchId, TreeNode* node) {
		if (node == nullptr) {
			return nullptr;
		}
		
		if (node->match != nullptr && node->match->getMatchId() == matchId) {
			return node;
		}

		TreeNode* leftFind = findByMatchId(matchId, node->left);
		TreeNode* rightFind = findByMatchId(matchId, node->right);

		if (leftFind != nullptr) {
			return leftFind;
		} else {
			return rightFind;
		}
	}

public:
	Tree() : head{nullptr} {}

	bool hasNextMatch() {
		// dead tree
		if (head == nullptr) return false;
		// final not yet set
		if (head->match == nullptr) return true;
		// partial final
		return !head->match->isOver();
	}

	Match& getNextMatch() {
		return *(getDeepestNode(head, height(head))->match);
	}

    void addGameScore(int matchId, int score1, int score2) {
		TreeNode* node = findByMatchId(matchId);
		Match* matchNode = node->match;
		if (matchNode == nullptr) {
			std::cout << matchId << std::endl;
		}

		matchNode->addGameScore(score1, score2);
		if (matchNode->isOver()){
			Player winner = matchNode->getPlayer(matchNode->winner());
			
			// tourney is done, don't update any parent
			if (head != nullptr && matchNode == head->match) {
				return;
			}

			Match *parentMatch = node->parent->match;
			if (parentMatch == nullptr) {
				std::cout << "parent was null" << std::endl;
				// start a partial match with dummy player
				node->parent->match = new Match(winner, Player("", 0), matchId++, matchNode->getFirstTo());
			} else {
                std::cout << "AHHHHHHHHH REEE" << std::endl;
				node->parent->match->setP2(winner);
			}
		}
	}

	TreeNode* createTreeOfSize(int numNodes, TreeNode* parent = nullptr) {
		if (numNodes == 0) {
			return nullptr;
		}
		TreeNode* thisNode = new TreeNode(nullptr, nullptr, nullptr, parent);
		TreeNode* leftNode = createTreeOfSize((numNodes - 1) / 2, thisNode);
		TreeNode* rightNode = createTreeOfSize((numNodes - 1) / 2, thisNode);
		thisNode->left = leftNode;
		thisNode->right = rightNode;
		return thisNode;
	}

	void setLeaves(vector<Match> matches) {
		setLeaves(matches, head);
	}

	void setLeaves(vector<Match> matches, TreeNode* curNode) {
		if (curNode == nullptr) {
			return;
		}

		if (curNode->isLeaf()) {
			Match m = matches[curMatch++];
			curNode->match = new Match(m);
		}

		setLeaves(matches, curNode->left);
		setLeaves(matches, curNode->right);
	}

	void constructTree(vector<Player> players) {
		// highest seeds play lowest seeds
		vector<Match> matches;	
		int numPlayers = (int)players.size();
		
		for (int i = 0; i < numPlayers / 2; i++) {
			matches.emplace_back(players[i], players[numPlayers - i - 1], matchId++);
		} 

		int numNodes = 2*matches.size() - 1;
		head = createTreeOfSize(numNodes);
		setLeaves(matches);
	}

	void printTree(TreeNode* cur) {
		if (cur == nullptr) {
			return;
		}

		if (cur->match == nullptr) {
			std::cout << "empty" << std::endl;
		} else {
			std::cout << *cur->match << std::endl;
		}

		std::cout << "going left" << std::endl;
		printTree(cur->left);
		std::cout << "back up, going right" << std::endl;
		printTree(cur->right);
	}

	void print() {
		if (head == nullptr) {
			return;
		}

		int treeHeight = height(getDeepestNode(head, 0));

		head->print(treeHeight);
	}
};


#endif
