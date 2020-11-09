
// ifstream constructor.
#include <iostream>     
#include <fstream>     
int main() {

	char ch;
	fstream fin("MorseTable.txt", fstream::in);
	while (fin >> noskipws >> ch) {
		std::cout << ch;
	}

	return 0;
}