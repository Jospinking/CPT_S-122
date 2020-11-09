#pragma once
#include "queuenode.h"
class Queue
{
public: // Member functions
	Queue();
	~Queue();

	void enqueue(Data* pData);
	Data* dequeue();
	void printQueue();

	int getLastTotalTime();

	int getFirstTotalTime();

	int getFirstServiceTime();

private:
	QueueNode *pHead;
	QueueNode *pTail;
};


Queue::Queue() {
	pHead = nullptr;
	pTail = nullptr;
}

Queue::~Queue() {
	// continue with dequeue until the head is null
	while (this->pHead != nullptr) {
		dequeue();
	}
}

void Queue::enqueue(Data *pData) {
	// construct a queue node
	QueueNode *node = new QueueNode(pData);

	if (pHead == nullptr) {
		//  both the head and tail will point this node
		pHead = pTail = node;
	}
	else {
		
		pTail->setNext(node);
		pTail = node;
	}

}

Data* Queue::dequeue() {
	Data *tempData = nullptr;
	if (this->pHead == nullptr) {
		tempData = nullptr;
	}
	else if (this->pHead == this->pTail) {
		tempData = this->pHead->getData();
		this->pHead = this->pTail = nullptr;
	}
	else {
		QueueNode *tempNode = pHead;
		tempData = tempNode->getData();
		pHead = pHead->getNext();
	}
	return tempData;
}


void Queue::printQueue() {
	if (this->pHead == nullptr) {
		std::cout << "No customer in the line" << std::endl;
		return;
	}

	QueueNode *t = this->pHead;
	while (t != nullptr) {
		Data *customer = t->getData();
		customer->printData();
		std::cout << std::endl;
		t = t->getNext();
	}


}

int Queue::getLastTotalTime() {
	if (pTail == nullptr)
		return 0;
	else {
		Data* data = pTail->getData();
		return data->getTotalTime();
	}
}

int Queue::getFirstTotalTime() {
	if (pHead == nullptr)
		return 0;
	else {
		Data* data = pHead->getData();
		return data->getTotalTime();
	}
}

int Queue::getFirstServiceTime() {
	if (pHead == nullptr) {
		return 0;
	}
	else {
		return pHead->getData()->getServiceTime();
	}
}