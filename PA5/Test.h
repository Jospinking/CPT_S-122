#pragma once
#include "queue.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

class Test {
public:
	void test_case1();
	void test_case2();
	void test_case3();
	void test_case4();
	void test_case5(int n_minutes);
};


void Test::test_case1() {
	std::cout << "Test Case 1: Performing first test case, enqueue operation on empty queue" << std::endl;

	Queue queue;
	std::cout << "Test Case 1: Queue constructed" << std::endl;
	queue.printQueue();
	std::cout << "Test Case 1: Going to perform enqueue operation" << std::endl;
	// constructing a data object 
	Data *data1 = new Data(1, 3, 0);
	// doing enqueue operation on empty queue
	queue.enqueue(data1);
	std::cout << "Test Case 1: Enqueue done... " << std::endl;
	// Now printing the queue
	std::cout << "Test Case 1: Printing the queue " << std::endl;
	queue.printQueue();

}
void Test::test_case2() {
	std::cout << "Test Case 2: Performing the second test case, enqueue operation with one node in the queue" << std::endl;
	Queue queue;

	// constructing a data object
	Data *data1 = new Data(1, 3, 0);
	// inserting a node 
	std::cout << "Test Case 2: The queue contains one node now: " << std::endl;
	queue.enqueue(data1);

	// constructing some more nodes and doing enqueue
	Data *data2 = new Data(2, 4, 7);
	queue.enqueue(data2);

	Data *data3 = new Data(3, 5, 12);
	std::cout << "Test Case2: doing enqueue" << std::endl;
	queue.enqueue(data2);

	// printing the queue
	std::cout << "Test Case2: Queue after doing second enqueue " << std::endl;
	queue.printQueue();
}
void Test::test_case3() {
	Queue queue;
	std::cout << "Test Case 3: Performing the third test case, enqueue and dequeue operation with one node in the queue" << std::endl;
	Data *data1 = new Data(1, 3, 0);
	
	queue.enqueue(data1);
	std::cout << "Test Case3: The queue contains one node as follows: " << std::endl;
	queue.printQueue();

	std::cout << "Test Case 3: Going to perform dequeue operation: " << std::endl;

	// first dequeue
	Data* temp1 = queue.dequeue();
	std::cout << "Test Case 3: The node content that was deleted is as follows: " << std::endl;
	temp1->printData();
	// deleting this data now
	delete temp1;
	std::cout << "Test Case 3: The queue after first deletetion: " << std::endl;
	queue.printQueue();
	std::cout << "------------------------------------" << std::endl;

	// second dequeue
	Data* temp2 = queue.dequeue();
	if (temp2 == nullptr) {
		std::cout << "Test Case3: Empty queue test case passed" << std::endl;
	}
	else {
		std::cout << "Test Case 3: Empty queue test case failed" << std::endl;
	}
}
void Test::test_case4() {
	std::cout << "Test Case 4: Performing the fourth test case, dequeue operation with two node in the queue" << std::endl;
	Queue queue;

	// constructing a data object
	Data *data1 = new Data(1, 3, 0);
	// inserting a node 
	queue.enqueue(data1);

	// constructing some more nodes and doing enqueue
	Data *data2 = new Data(2, 4, 7);
	queue.enqueue(data2);
	// printing the queue
	std::cout << "Test Case 4: The content of the queue is as follows: " << std::endl;
	queue.printQueue();
	std::cout << "------------------------------------" << std::endl;

	std::cout << "Test Case 4: Going to perform dequeue operation: " << std::endl;

	// first dequeue
	std::cout << "Test Case 4: going to perform first dequeue" << std::endl;
	Data* temp1 = queue.dequeue();
	std::cout << "Test Case 4: The node content that was deleted is as follows: " << std::endl;
	temp1->printData();
	// deleting this data now
	delete temp1;
	std::cout << "Test Case 4: The queue after first deletetion: " << std::endl;
	queue.printQueue();
	std::cout << "------------------------------------" << std::endl;

	// second dequeue
	std::cout << "Test Case 4: going to perform second dequeue" << std::endl;
	Data* temp2 = queue.dequeue();
	std::cout << "Test Case 4: The node content that was deleted is as follows: " << std::endl;
	temp2->printData();
	// deleting this data
	delete temp2;
	std::cout << "The queue after second dequeue: " << std::endl;
	queue.printQueue();
	std::cout << "------------------------------------" << std::endl;

}


int getRandom(int min, int max) {
	return (rand() % (max + 1 - min)) + min;
}

void Test::test_case5(int n_minutes) {
	
	srand(time(0));
	Queue expressQ;   
	Queue normalQ;  
	
	int expressArrivalTime = getRandom(1, 5);
	int normalArrivalTime = getRandom(3, 8);
	int customerNumber = 1;
	int timeElapsed = 0;
	int lastExpressServiceProvided = 1;
	int lastNormalServiceProvided = 1;

	while (timeElapsed <= n_minutes) {

		if (timeElapsed == expressArrivalTime) {
			std::cout << "On minute: " << timeElapsed << std::endl;
			std::cout << "Express customer arrived: " << std::endl;
			int serviceTime = getRandom(1, 5);
			int totalTime = expressQ.getLastTotalTime() + serviceTime;
			Data* expressCustomer = new Data(customerNumber++, serviceTime, totalTime);

			expressCustomer->printData();

			std::cout << std::endl;
			// insert the customer into the queue
			expressQ.enqueue(expressCustomer);
			
			expressArrivalTime = getRandom(1, 5) + expressArrivalTime;
		}

		// when the customer for the normal Q arives
		if (timeElapsed == normalArrivalTime) {
			std::cout << "On minute: " << timeElapsed << std::endl;
			std::cout << "Normal customer arived: " << std::endl;
			// get the service time of the customer
			int serviceTime = getRandom(3, 8);
			// Calculate the total time
			int totalTime = normalQ.getLastTotalTime() + serviceTime;
			// construct the data object
			Data* normalCustomer = new Data(customerNumber++, serviceTime, totalTime);
			normalCustomer->printData();
			std::cout << std::endl;

			// perform the enqueue for this normal customer
			normalQ.enqueue(normalCustomer);
			// get the arival time for the next customer.
			normalArrivalTime = getRandom(3, 8) + normalArrivalTime;
		}
		// now we need to check if any services are to be delivered...
		if (lastExpressServiceProvided == expressQ.getFirstServiceTime()) {  
			std::cout << "On minute: " << timeElapsed << std::endl;
			// process the front customer of express queue
			Data* data = expressQ.dequeue();
			std::cout << "Processing an express customer: " << std::endl;

			data->printData();
			delete data;

			lastExpressServiceProvided = 1;
		}

		if (lastNormalServiceProvided == normalQ.getFirstServiceTime()) {  
			std::cout << "On minute: " << timeElapsed << std::endl;

			Data* data = normalQ.dequeue();
			std::cout << "Processing a normal customer: " << std::endl;
			data->printData();
			delete data;
			lastNormalServiceProvided = 1;
		}

		// on every 10 minutes, we need to print the entire queue for both the queue
		if ((timeElapsed + 1) % 10 == 0) {
			std::cout << std::endl;
			std::cout << "Printing the express queue" << std::endl;
			expressQ.printQueue();

			std::cout << std::endl;
			std::cout << "Printing the normal queue" << std::endl;
			normalQ.printQueue();

		}

		++timeElapsed;
		++lastExpressServiceProvided;
		++lastNormalServiceProvided;
		// on 24 hours, we need to reset the customer number
		if (timeElapsed == 24 * 60) {
			std::cout << "24 hours elapsed, customer number reset to 1" << std::endl;
			customerNumber = 1;
		}
	}




}