#pragma once

#include "Node.h"
template <typename T>	
class List
{

public:
	Node<T>* head,*tail;
	List(){
		head = NULL;
		tail = NULL;
	}
	
	~List(){
		head = NULL;
		tail = NULL;
	}
	void insertToFront(T& item){
		if(head == NULL){
			head = new Node<T>(item);
			return;
		}

		Node<T>* new_node = new Node<T>(item);
		new_node->next = head;
		head = new_node;
		return;
	}
	
};