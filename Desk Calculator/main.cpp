#include "Token_stream.h"
#include <iostream>
#include <sstream>
void calculate();
int error(const string &s);

Token_stream ts{ std::cin };


int main(int argc, char *argv[]) {
	switch (argc) {
	case 1:
		break;
	case 2:
		ts.set_input(new std::istringstream{ argv[1] });
		break;
	default:
		error("too many arguments");
		return 1;
	}
	
	calculate();
	return 0;
}