#ifndef TREE_H
#define TREE_H

#include<string>
#include<vector>
#include<algorithm>

#include "tournament.h"

using namespace std;

const int nSpacesPerHeight = 10;

class TreeNode {
public:
	Match *match;
	TreeNode *left;
	TreeNode *right;

	TreeNode(Match *match) : match{match}, left{nullptr}, right{nullptr}  {}

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

	Match* findByMatchId(int matchId) {
		return findByMatchId(matchId, head);
	}

	Match* findByMatchId(int matchId, TreeNode* node) {
		if (node == nullptr) {
			return nullptr;
		}
		
		if (node->match != nullptr && node->match->getMatchId() == matchId) {
			return node->match;
		}

		Match* leftFind = findByMatchId(matchId, node->left);
		Match* rightFind = findByMatchId(matchId, node->right);

		if (!leftFind) {
			return leftFind;
		} else {
			return rightFind;
		}
	}

	Match* getMatchParent(int matchId) {
		return getMatchParent(matchId, head, nullptr);
	}

	Match* getMatchParent(int matchId, TreeNode* node, TreeNode* parent) {
		if (node == nullptr) {
			return nullptr;
		}

		if (node->match != nullptr && node->match->getMatchId() == matchId) {
			return parent->match;
		}

		Match* leftFind = findByMatchId(matchId, node->left, node);
		Match* rightFind = findByMatchId(matchId, node->right, node);

		if (!leftFind) {
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
		return head->match->isOver();
	}

	Match& getNextMatch() {
		return getDeepestNode(head, height(head))->match;
	}

    void addGameScore(int matchId, int score1, int score2) {
		Match* matchNode = findByMatchId(matchId);
		if (!matchNode) {
			throw "Match not found";
		}

		matchNode->addGameScore(score1, score2);
		if (matchNode->isOver()){
			Player winner = matchNode->getPlayer(matchNode->winner());
			
			// tourney is done, don't update any parent
			if (matchNode == head) {
				return;
			}

			Match *parentMatch = getMatchParent(matchId);
			if (parentMatch == nullptr) {
				// start a partial match with dummy player
				parentMatch = new Match(winner, Player("", 0));
			} else {
				parentMatch->setP2(winner);
			}
		}
	}

	void constructTree(vector<Player> players);

	void print() {
		if (head == nullptr) {
			return;
		}

		int height = height(getDeepestNode(head, 0));

		head->print();
	}
};


#endif
