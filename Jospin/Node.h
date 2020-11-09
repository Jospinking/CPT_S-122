#pragma once

#include "Data.h"

template <typename T>
class Node
{
public:
	T data;
	Node* next;	
	Node(T& data) {
		this->data = data;
		next = NULL;

	}
	Node(){
		data=nullptr;
		next = nullptr;
	}
};