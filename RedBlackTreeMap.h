#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
#include <iostream>
using namespace std;

template <typename TKey, typename TValue>
class RedBlackTreeMap
{
private:
	class Node
	{
	public:
		TKey mKey;
		TValue mValue;
		Node* mParent;
		Node* mLeft;
		Node* mRight;
		bool mIsRed;

		Node(const TKey &key, const TValue &value, bool isRed)
			: mKey(key), mValue(value), mIsRed(isRed), mParent(nullptr),
			mLeft(&NIL_NODE), mRight(&NIL_NODE)
		{
		}
	};

	Node *mRoot;
	int mCount;
	static Node NIL_NODE;

	Node* bstFind(const TKey &key, Node *currentNode)
	{
		if (currentNode->mKey > key)
			bstFind(key, currentNode->mLeft);
		else if (currentNode->mKey < key)
			bstFind(key, currentNode->mRight);
		else if (currentNode->mKey == key)
			return currentNode;
		else
			return nullptr;
	}

	Node* getGrandparent(Node *n)
	{
		return n->mParent->mParent;
	}

	// Gets the uncle (parent's sibling) of n.
	Node* getUncle(Node *n)
	{
		if (getGrandparent(n)->mLeft == n->mParent)
			return getGrandparent(n)->mRight;
		else if (getGrandparent(n)->mRight == n->mParent)
			return getGrandparent(n)->mLeft;
		else
			return &NIL_NODE;
	}

	// Rotate the tree right at the given node.
	void singleRotateRight(Node* n)
	{
		Node *l = n->mLeft,
			*lr = l->mRight,
			*p = n->mParent;

		n->mLeft = lr;
		lr->mParent = n;

		l->mRight = n;
		if (p == nullptr)
		{
			mRoot = l;
		}
		else if (p->mLeft == n)
		{
			p->mLeft = l;
		}
		else
		{
			p->mRight = l;
		}
		n->mParent = l;
		l->mParent = p;
	}

	// Rotate the tree left at the given node.
	void singleRotateLeft(Node *n)
	{
		Node *l = n->mRight,
			*lr = l->mLeft,
			*p = n->mParent;

		n->mRight = lr;
		lr->mParent = n;

		l->mLeft = n;
		if (p == nullptr)
		{
			mRoot = l;
		}
		else if (p->mRight == n)
		{
			p->mRight = l;
		}
		else
		{
			p->mLeft = l;
		}
		n->mParent = l;
		l->mParent = p;
	}

	// This method is used by insert. It is complete.
	// Inserts the key/value into the BST, and returns true if the key wasn't
	// previously in the tree.
	bool bstInsert(Node* newNode, Node* currentNode)
	{
		if (mRoot == nullptr)
		{
			// case 1
			mRoot = newNode;
			return true;
		}
		else
		{
			if (currentNode->mKey < newNode->mKey)
			{
				// newNode is larger; go right.
				if (currentNode->mRight != &NIL_NODE)
					return bstInsert(newNode, currentNode->mRight);
				else
				{
					currentNode->mRight = newNode;
					newNode->mParent = currentNode;
					mCount++;
					return true;
				}
			}
			else if (currentNode->mKey > newNode->mKey)
			{
				if (currentNode->mLeft != &NIL_NODE)
					return bstInsert(newNode, currentNode->mLeft);
				else
				{
					currentNode->mLeft = newNode;
					newNode->mParent = currentNode;
					mCount++;
					return true;
				}
			}
			else
			{
				// found a node with the given key; update value.
				currentNode->mValue = newNode->mValue;
				return false; // did NOT insert a new node.
			}
		}
	}

	// Applies rules 1-5 to check the balance of a tree with newly inserted
	// node n.
	void checkBalance(Node *n)
	{
		if (n == mRoot)//case 1: n is the root
		{
			n->mIsRed = false;
		}

		else if (n->mParent->mIsRed == false);//case2: parent is black
		
		else if (n->mParent->mIsRed == true && getUncle(n)->mIsRed == true)//case 3: parent and uncle are red
		{
			n->mParent->mIsRed = false;
			getUncle(n)->mIsRed = false;
			getGrandparent(n)->mIsRed = true;

			checkBalance(getGrandparent(n));
		}
		
		else
		{
			if (getGrandparent(n)->mLeft == n->mParent && n->mParent->mRight == n)//case 4: n is lr or rl of G
			{
				singleRotateLeft(n->mParent);
				singleRotateRight(n->mParent);//case 5: n is ll or rr of G

				n->mIsRed = n->mRight->mIsRed;
				n->mRight->mIsRed = !n->mIsRed;
			}

			else if (getGrandparent(n)->mRight == n->mParent && n->mParent->mLeft == n)//case 4: n is lr or rl of G
			{
				singleRotateRight(n->mParent);
				singleRotateLeft(n->mParent);//case 5: n is ll or rr of G
				
				n->mIsRed = n->mLeft->mIsRed;
				n->mLeft->mIsRed = !n->mIsRed;
			}

			else if (getGrandparent(n)->mLeft == n->mParent && n->mParent->mLeft == n)//case 5: n is ll or rr of G
			{
				singleRotateRight(getGrandparent(n));
				
				n->mParent->mIsRed = n->mParent->mRight->mIsRed;
				n->mParent->mRight->mIsRed = !n->mParent->mIsRed;
			}

			else if (getGrandparent(n)->mRight == n->mParent && n->mParent->mRight == n)//case 5: n is ll or rr of G
			{
				singleRotateLeft(getGrandparent(n));
				
				n->mParent->mIsRed = n->mParent->mLeft->mIsRed;
				n->mParent->mLeft->mIsRed = !n->mParent->mIsRed;
			}
		}
	}

public:

	RedBlackTreeMap() : mRoot(nullptr), mCount(0) {
	}

	inline int count() const
	{
		return mCount;
	}

	// Inserts a key/value pair into the tree, updating the red/black balance
	// of nodes as necessary. Starts with a normal BST insert, then adjusts.
	void insert(const TKey &key, const TValue &value)
	{
		Node* n = new Node(key, value, true);
		// the node starts red, with null parent, left, and right.

		// normal BST insert; n will be placed into its initial position.
		// returns false if an existing node was updated (no rebalancing needed)
		bool insertedNew = bstInsert(n, mRoot);
		if (!insertedNew)
			return;

		// check cases 1-5 for balance.
		checkBalance(n);
	}

	TValue &find(const TKey &key)
	{
		Node *n = bstFind(key, mRoot);
		if (n == nullptr || n == &NIL_NODE)
		{
			throw std::out_of_range("Key not found");
		}
		return n->mValue;
	}

	// Returns true if the given key is in the tree.
	bool containsKey(const TKey &key) const
	{
		if (bstFind(key, mRoot) == nullptr)
			return false;
		return true;
	}

	// Prints a pre-order traversal of the tree's nodes, printing the key, value,
	// and color of each node.
	void printStructure()
	{
		cout << mRoot->mKey << " : " << mRoot->mValue << " (";
		mRoot->mIsRed ? cout << "Red)" << endl : cout << "Black)" << endl;

		if (mRoot->mLeft != &NIL_NODE)
			printStructure(mRoot->mLeft);
		if (mRoot->mRight != &NIL_NODE)
			printStructure(mRoot->mRight);
	}

	void printStructure(Node *n)
	{
		cout << n->mKey << " : " << n->mValue << " (";
		n->mIsRed ? cout << "Red)" << endl : cout << "Black)" << endl;

		if (n->mLeft != &NIL_NODE)
			printStructure(n->mLeft);
		if (n->mRight != &NIL_NODE)
			printStructure(n->mRight);
	}
};

template <typename TK, typename TV>
typename RedBlackTreeMap<TK, TV>::Node RedBlackTreeMap<TK, TV>::NIL_NODE{ TK(), TV(), false };