#pragma once

#include "TransactionNode.h"

class BST
{
private:
	Node* mpRoot;
	void destroyTree(Node* node)  
	{ 
    	if (node == nullptr) return; 
  
	    /* first delete both subtrees */
	    destroyTree(node->getmpleft()); 
	    destroyTree(node->getmpright()); 
	    
	    delete(node); 
	}
	TransactionNode* newNode(const std::string data, const int units) 
	{ 
	    TransactionNode* temp = new TransactionNode(data, units);	    
	    return temp; 
	}

	TransactionNode* insert(TransactionNode* root, const std::string data, const int units) 
	{ 
	    /* If the tree is empty, return a new node */
	    if (root == nullptr) return newNode(data, units); 
	  
	    /* Otherwise, recur down the tree */
	    if (units < root->getUnits()) 
	        root->setmpleft(insert(dynamic_cast<TransactionNode*>(root->getmpleft()), data, units)); 
	    else if (units > root->getUnits()) 
	        root->setmpright(insert(dynamic_cast<TransactionNode*>(root->getmpright()), data, units) );    
	  
	    /* return the (unchanged) node pointer */
	    return root; 
	}

	void inOrderTraversal(TransactionNode* root) const
	{
		if (root != nullptr)
		{
			inOrderTraversal(dynamic_cast<TransactionNode*>(root->getmpleft()));
			// visits the node and displays the item
			root->printData();
			inOrderTraversal(dynamic_cast<TransactionNode*>(root->getmpright()));
		}
	}

	

public:
	BST(){
		mpRoot = nullptr;
	}
	~BST(){
		destroyTree(mpRoot);
		mpRoot = nullptr;
	}
	void insert(const std::string data, const int units){
		mpRoot = insert(dynamic_cast<TransactionNode*>(mpRoot), data, units);	
	}

	void inOrderTraversal() const{
		inOrderTraversal(dynamic_cast<TransactionNode*>(mpRoot) );
	}

	TransactionNode& findSmallest()
	{
		
		Node* curr = mpRoot;
		while(curr->getmpleft() != nullptr){
			curr = curr->getmpleft();
		}
		return *dynamic_cast<TransactionNode*>(curr);
	}

	TransactionNode& findLargest()
	{
		
		Node* curr = mpRoot;
		while(curr->getmpright() != nullptr){
			curr = curr->getmpright();
		}
		return *dynamic_cast<TransactionNode*>(curr);
	}
	
};