#pragma once
#include "data.h"

class QueueNode
{
public: // Member functions
	QueueNode(Data *data);
	~QueueNode();

	Data* getData();
	void setData(Data *data);

	QueueNode* getNext();
	void setNext(QueueNode* next);

	void freeData();


private:
	Data *pData;    
	QueueNode *pNext;
};

QueueNode::QueueNode(Data *data) {
	this->pData = data;
	this->pNext = nullptr;
}

QueueNode::~QueueNode() {
	delete this->pData;

}


Data* QueueNode::getData() {

	return this->pData;

}

// Mutator for the data pointer
void QueueNode::setData(Data *data) {
	this->pData = data;
}

// accessor for next    
QueueNode* QueueNode::getNext() {
	return this->pNext;
}

// Mutator for next
void QueueNode::setNext(QueueNode* next) {
	this->pNext = next;
}

void QueueNode::freeData() {
	delete this->pData;
}