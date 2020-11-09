#pragma once

#include "BST.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h> 
#include <string.h> 
#define _CRT_SECURE_NO_WARNINGS



class DataAnalysis
{
private:
	BST mTreeSold;
	BST mTreePurchased;
	std::ifstream mCsvStream;
	bool readFile(std::string filename){
		mCsvStream.open(filename);
		if(mCsvStream.is_open()){
			return true;
		}
		return false;
	}
	std::vector<std::string> splitLine(std::string line){
		char *token = strtok((char*)line.c_str(), ","); 
    
	    // Keep printing tokens while one of the 
	    // delimiters present in str[].
	    std::vector<std::string> res; 
	    while (token != NULL) 
	    { 
	        res.push_back(token);
	        token = strtok(NULL, ","); 
	    } 
	    return res;
	}
	void loopAll(){
		std::string line;
		std::getline (mCsvStream,line);
		while ( std::getline (mCsvStream,line) )
	    {
	      std::vector<std::string> vec;
	      vec = splitLine(line);
	      insertToBST(vec);
	      // std::cout << line << '\n';
	    }
	    std::cout << "\nPurchased Tree: \n";
	    mTreePurchased.inOrderTraversal();
	    std::cout << "\nSold Tree: \n";
	    mTreeSold.inOrderTraversal();
	    mCsvStream.close();
	}
	void insertToBST(std::vector<std::string> vec){
		int units = atoi(vec[0].c_str());
		std::string data = vec[1];
		std::string type = vec[2];
		if(type.find("Purchased") != std::string::npos ){
			mTreePurchased.insert(data, units);
		}
		else{
			mTreeSold.insert(data, units);
		}
	}
	void printTrends(){
		std::cout << std::endl;
		TransactionNode t = mTreePurchased.findSmallest();
		std::cout << "minimum units Purchased: " << t.getUnits() << std::endl;
		t = mTreePurchased.findLargest();
		std::cout << "maximum units Purchased: " << t.getUnits() << std::endl;
		t = mTreeSold.findSmallest();
		std::cout << "minimum units Sold: " << t.getUnits() << std::endl;
		t = mTreeSold.findLargest();
		std::cout << "maximum units Sold: " << t.getUnits() << std::endl;
		
	}

public:
	void runAnalysis(){
		readFile("data.csv");
		loopAll();
		printTrends();
	}	
};