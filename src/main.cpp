
#include <iostream>
#include "JsonCodeGenerator.h"
#include <fstream>

int main() {
	
	std::fstream file;
	file.open("C:\\Users\\Natha\\source\\vs\\JsonCodeGenerator\\metaObject\\Classes.json");

	std::fstream codefile;
	codefile.open("C:\\Users\\Natha\\source\\vs\\JsonCodeGenerator\\metaObject\\Code.hpp");

	if (!file.is_open()) {
		return -1;
	}

	/*std::string buffer;
	while (std::getline(file, buffer)) {
		std::cout << buffer << std::endl;
		buffer.clear();
	}*/

	Generator g1;

	g1.Generate(file, codefile);

	return 0;
}