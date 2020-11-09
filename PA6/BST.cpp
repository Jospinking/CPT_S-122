#include "BST.h"
#include <iostream>
using namespace std;

BST::BST(string filename) {

	std::ifstream ifs(filename.c_str(), std::ifstream::in);

	count = 0;
	root = NULL;

	Node* treeNode = new Node(' ');
	insert(root, treeNode, 0);

	char c = ifs.get();
	// treeNode = new Node(c);
	// insert(root, treeNode, 0);
	while (ifs.good()) {
		if (c != '\n') { 
			treeNode = new Node(c);
			insert(root, treeNode, 0);
		}
		c = ifs.get();
	}

}

void BST::insert(Node* &node, Node* treeNode, int index)
{

	if (!node)
	{
		node = treeNode;
		return;
	}
	else
	{
		if (index<treeNode->morse.size() && treeNode->morse[index] == '.')
		{
			index++;
			insert(node->left, treeNode, index);
		}
		else if (treeNode->morse[index] == '-')
		{
			index++;
			insert(node->right, treeNode, index);
		}
	}
}


void BST::print(Node* node) const
{
	if (node == NULL)
		return;
	print(node->left);
	std::cout << node->eng << "   " << node->morse << std::endl;
	print(node->right);

}


string BST::search(char c) const
{

	c = tolower(c);
	Node *temp = root;
	Node n(c);
	string str = n.morse;
	int i = 0;

	while (temp != NULL)
	{
		if (temp->eng == c)
			break;

		if (str[i] == '-')
			temp = temp->right;

		else if (str[i] == '.')
			temp = temp->left;
		i++;
	}

	if (temp == NULL)
		return "Not found";
	else if (temp->eng == c)
		return temp->morse;
}



void BST::DestroyRecursive(Node* node)
{
	if (node)
	{
		DestroyRecursive(node->left);
		DestroyRecursive(node->right);
		delete node;
	}
}

BST::~BST()
{
	DestroyRecursive(root);
}

