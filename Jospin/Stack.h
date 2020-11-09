#pragma once

#include <vector>
#include <ctime>
#include <stdexcept>

class Stack
{
public:
	std::vector< std::tm* > time_arr;
	int size() const { return time_arr.size(); }
    bool empty() const { return time_arr.empty();}
    void push(std::tm* & t);
    std::tm* pop();
    std::tm* peek();

};

void Stack::push(std::tm* & t) {
    time_arr.push_back(t);
}



std::tm* Stack::pop() {
    if (empty()) {
        return nullptr;
    }
    auto x = time_arr.back();  
    time_arr.pop_back();
    return x;
}


std::tm* Stack::peek() {
    if (empty()) {
        return nullptr;
    }
    return time_arr.back();
}