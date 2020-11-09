#include <iostream>
#include <string>
#include <fstream>
#include "BST.h"

using namespace std;


int main() {

	const BST tree("MorseTable.txt");

	ifstream inp;
	inp.open("Convert.txt");
	char c;
	while (inp.get(c))
	{

		if (c == '\n')
			std::cout << "\n";
		else
			std::cout << tree.search(c) << " ";
	}

	cout << endl << "Press \"enter\" to continue.";
	getchar();

	return 0;
}