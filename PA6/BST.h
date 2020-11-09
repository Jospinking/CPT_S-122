#ifndef _BST
#define _BST

#include "Node.h"
#include <fstream>
#include <stdio.h>
#include <ctype.h>

class BST
{
private:
	int count;

public:
	Node* root;
	BST(string filename);
	void insert(Node * &node, Node* treeNode, int index);
	void print(Node* n) const;
	// void printchar(Node* n, ostream&  p);
	string search(char c) const;
	void DestroyRecursive(Node* node);
	~BST();



};
#endif